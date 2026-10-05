//! Implements: DD-APP-015.
//!
//! Local display names keyed by exact connection identity. The file worker
//! owns disk access; the UI only queues requests and polls reports. Names
//! never change the identifier sent to the device worker.

use std::collections::BTreeMap;
use std::io::{Read as _, Write as _};
use std::path::{Path, PathBuf};
use std::sync::mpsc::{self, Receiver, SyncSender};

use crate::model::{Found, Kind};
use crate::worker::Wake;

/// Saved aliases, indexed by an encoded identity rather than by display name.
pub type Map = BTreeMap<String, String>;
/// Maximum UTF-8 file size accepted from disk.
const MAX_FILE_BYTES: u64 = 1_048_576;
/// Maximum characters in a friendly name.
pub const MAX_NAME_CHARS: usize = 48;

/// One validated, local save request.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Save {
    /// Complete identity key, including the boot for macOS USB.
    pub key: String,
    /// Trimmed name; empty removes this alias.
    pub name: String,
}

/// A result from the file worker.
#[derive(Clone, Debug, PartialEq, Eq)]
pub enum Report {
    /// Initial load; an unavailable boot identity disables USB name writes.
    Loaded(Result<Map, String>, Option<String>),
    /// Save completed. Only success changes the visible name.
    Saved(Save, Result<(), String>),
}

/// Presentation state, separate from device state and command eligibility.
#[derive(Clone, Debug, Default, PartialEq, Eq)]
pub struct State {
    /// Names known to have been read or written successfully.
    pub saved: Map,
    /// Host boot identity used for USB keys on macOS.
    pub boot: Option<String>,
    /// Initial file load succeeded.
    pub loaded: bool,
    /// The currently edited exact identity.
    pub target: Option<String>,
    /// Name text being edited.
    pub draft: String,
    /// An outstanding save, retained until its report.
    pub saving: Option<Save>,
    /// Request for the app core to hand to the file worker.
    pub queued: Option<Save>,
    /// A visible loading or saving error.
    pub error: Option<String>,
}

/// Checks input before trimming, so control characters cannot be hidden.
///
/// # Errors
/// Invalid control characters or more than 48 characters after trimming.
pub fn validate(text: &str) -> Result<String, String> {
    if text.chars().any(char::is_control) {
        return Err("Names cannot contain control characters.".into());
    }
    let name = text.trim();
    if name.chars().count() > MAX_NAME_CHARS {
        return Err(format!("Use at most {MAX_NAME_CHARS} characters."));
    }
    Ok(name.into())
}

impl State {
    /// Exact key for a supply. USB naming is unavailable without a scope.
    #[must_use]
    pub fn key(&self, found: &Found) -> Option<String> {
        match found.transport {
            Kind::Ble => Some(format!("ble:{}", found.identifier)),
            Kind::Hid => self
                .boot
                .as_ref()
                .map(|boot| format!("usb:{}:{boot}:{}", boot.len(), found.identifier)),
        }
    }

    /// Saved alias for this exact endpoint, if any.
    #[must_use]
    pub fn alias(&self, found: &Found) -> Option<&str> {
        self.key(found)
            .and_then(|key| self.saved.get(&key).map(String::as_str))
    }

    /// Switches the editing target without transferring another unit's draft.
    pub fn select(&mut self, found: Option<&Found>) {
        let key = found.and_then(|found| self.key(found));
        if self.target != key {
            self.draft = key
                .as_ref()
                .and_then(|key| self.saved.get(key))
                .cloned()
                .unwrap_or_default();
            self.target = key;
        }
    }

    /// A save is meaningful, valid and not already in flight.
    #[must_use]
    pub fn can_save(&self) -> bool {
        self.loaded
            && self.saving.is_none()
            && self.target.as_ref().is_some_and(|key| {
                validate(&self.draft)
                    .is_ok_and(|name| name != self.saved.get(key).map_or("", String::as_str))
            })
    }

    /// Queues a validated local change; never creates a device command.
    pub fn request_save(&mut self) {
        if !self.can_save() {
            return;
        }
        if let (Some(key), Ok(name)) = (&self.target, validate(&self.draft)) {
            let request = Save {
                key: key.clone(),
                name,
            };
            self.draft.clone_from(&request.name);
            self.error = None;
            self.saving = Some(request.clone());
            self.queued = Some(request);
        }
    }

    /// Applies only a successful save to the name map.
    pub fn apply(&mut self, report: Report) {
        match report {
            Report::Loaded(result, boot) => {
                self.boot = boot;
                match result {
                    Ok(map) => {
                        self.saved = map;
                        self.target = None;
                        self.loaded = true;
                        self.error = None;
                    }
                    Err(error) => self.error = Some(error),
                }
            }
            Report::Saved(request, result) => {
                if self.saving.as_ref() != Some(&request) {
                    return;
                }
                self.saving = None;
                match result {
                    Ok(()) => {
                        update(&mut self.saved, &request);
                        if self.target.as_ref() == Some(&request.key) {
                            self.draft.clone_from(&request.name);
                        }
                        self.error = None;
                    }
                    Err(error) => self.error = Some(error),
                }
            }
        }
    }
}

/// Changes just one key, including removal when the name is empty.
fn update(map: &mut Map, request: &Save) {
    if request.name.is_empty() {
        map.remove(&request.key);
    } else {
        map.insert(request.key.clone(), request.name.clone());
    }
}

/// Read-only startup load. A malformed file is never treated as empty.
fn load(path: &Path) -> Result<Map, String> {
    let file = match std::fs::File::open(path) {
        Ok(file) => file,
        Err(error) if error.kind() == std::io::ErrorKind::NotFound => return Ok(Map::new()),
        Err(error) => return Err(format!("Could not load device names: {error}")),
    };
    let mut text = String::new();
    file.take(MAX_FILE_BYTES.saturating_add(1))
        .read_to_string(&mut text)
        .map_err(|error| format!("Could not read device names: {error}"))?;
    if u64::try_from(text.len()).unwrap_or(u64::MAX) > MAX_FILE_BYTES {
        return Err("Device names file is too large.".into());
    }
    let map: Map = serde_json::from_str(&text)
        .map_err(|error| format!("Device names file is invalid: {error}"))?;
    for name in map.values() {
        validate(name)?;
    }
    Ok(map)
}

/// Replaces the whole file atomically, without damaging it on failure.
fn save(path: &Path, map: &Map) -> Result<(), String> {
    let parent = path.parent().ok_or("No directory for device names.")?;
    let write = || -> Result<(), Box<dyn std::error::Error>> {
        std::fs::create_dir_all(parent)?;
        let mut file = tempfile::NamedTempFile::new_in(parent)?;
        serde_json::to_writer_pretty(file.as_file_mut(), map)?;
        file.write_all(b"\n")?;
        file.as_file().sync_all()?;
        file.persist(path)?;
        Ok(())
    };
    write().map_err(|error| format!("Could not save device name: {error}"))
}

/// Boot token, obtained only on the file thread. Failure disables USB naming.
#[cfg(target_os = "macos")]
fn boot_scope() -> Option<String> {
    let output = std::process::Command::new("/usr/sbin/sysctl")
        .args(["-n", "kern.bootsessionuuid"])
        .output()
        .ok()?;
    let value = String::from_utf8(output.stdout).ok()?;
    let value = value.trim();
    (output.status.success() && !value.is_empty()).then(|| value.to_string())
}

/// Other backends use their full OS endpoint path; it is not a device serial.
#[cfg(not(target_os = "macos"))]
fn boot_scope() -> Option<String> {
    Some(std::env::consts::OS.into())
}

/// Channels to a dedicated file thread; no method below waits for disk I/O.
#[derive(Debug)]
pub struct Service {
    /// Bounded request queue; the model permits only one pending request.
    tx: SyncSender<Save>,
    /// Reports polled by the frame logic.
    rx: Receiver<Report>,
}

impl Service {
    /// Starts the worker and its initial load.
    ///
    /// # Errors
    /// The OS could not start the file thread.
    pub fn start(directory: Result<PathBuf, String>, wake: Wake) -> Result<Self, String> {
        let (tx, requests) = mpsc::sync_channel::<Save>(1);
        let (reports, rx) = mpsc::channel();
        std::thread::Builder::new()
            .name("mp305-device-names".into())
            .spawn(move || {
                let path = directory.map(|dir| dir.join("device-names.json"));
                let initial = path.as_ref().map_err(Clone::clone).and_then(|p| load(p));
                let _ = reports.send(Report::Loaded(initial.clone(), boot_scope()));
                wake();
                let Ok(mut map) = initial else { return };
                let Ok(path) = path else { return };
                while let Ok(request) = requests.recv() {
                    let mut next = map.clone();
                    let result = validate(&request.name).and_then(|_| {
                        update(&mut next, &request);
                        save(&path, &next)
                    });
                    if result.is_ok() {
                        map = next;
                    }
                    if reports.send(Report::Saved(request, result)).is_err() {
                        break;
                    }
                    wake();
                }
            })
            .map_err(|error| format!("Could not start device names: {error}"))?;
        Ok(Self { tx, rx })
    }

    /// Sends a save without waiting.
    ///
    /// # Errors
    /// The worker stopped or already has a queued request.
    pub fn send(&self, request: Save) -> Result<(), String> {
        self.tx
            .try_send(request)
            .map_err(|error| format!("Could not save device name: {error}"))
    }

    /// The next available report, without waiting.
    pub fn poll(&self) -> Option<Report> {
        self.rx.try_recv().ok()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::testkit::{found_a, found_b};
    use std::sync::Arc;
    use std::time::Duration;

    /// Test: UT-APP-032
    #[test]
    fn identities_are_exact_and_usb_is_scoped_to_the_boot() {
        let mut state = State {
            loaded: true,
            boot: Some("boot-one".into()),
            ..State::default()
        };
        let a = found_a();
        let mut other = a.clone();
        other.identifier = "second-bluetooth".into();
        let b = found_b();
        let mut usb = b.clone();
        usb.identifier = "second-usb".into();
        let keys: std::collections::BTreeSet<_> =
            [&a, &other, &b, &usb].map(|f| state.key(f).unwrap()).into();
        assert_eq!(keys.len(), 4);
        state.select(Some(&b));
        state.draft = " Bench lamp ".into();
        state.request_save();
        let request = state.queued.take().unwrap();
        state.apply(Report::Saved(request, Ok(())));
        assert_eq!(state.alias(&b), Some("Bench lamp"));
        state.boot = Some("boot-two".into());
        assert_eq!(state.alias(&b), None);
        assert_eq!(state.key(&a), Some("ble:A".into()));
        state.boot = None;
        assert_eq!(state.key(&b), None);
    }

    /// Test: UT-APP-032
    #[test]
    fn names_round_trip_and_failed_writes_preserve_the_file() {
        let dir = tempfile::tempdir().unwrap();
        let path = dir.path().join("names.json");
        assert!(load(&path).unwrap().is_empty());
        let mut map = Map::from([
            ("ble:A".into(), "Bench".into()),
            ("ble:B".into(), "Bench".into()),
        ]);
        save(&path, &map).unwrap();
        assert_eq!(load(&path).unwrap(), map);
        update(
            &mut map,
            &Save {
                key: "ble:A".into(),
                name: String::new(),
            },
        );
        save(&path, &map).unwrap();
        assert_eq!(
            load(&path).unwrap(),
            Map::from([("ble:B".into(), "Bench".into())])
        );
        let before = std::fs::read(&path).unwrap();
        assert!(save(&path.join("child"), &map).is_err());
        assert_eq!(std::fs::read(&path).unwrap(), before);
        assert!(load(dir.path()).is_err());
        std::fs::write(&path, "{broken").unwrap();
        assert!(load(&path).is_err());
        assert_eq!(std::fs::read_to_string(&path).unwrap(), "{broken");
    }

    /// Test: UT-APP-032
    #[test]
    fn invalid_names_and_save_errors_never_replace_a_saved_alias() {
        assert_eq!(validate("  Lamp  ").unwrap(), "Lamp");
        assert_eq!(validate("   ").unwrap(), "");
        assert!(validate("Lamp\n").is_err());
        assert!(validate(&"x".repeat(49)).is_err());
        assert!(validate(&"é".repeat(48)).is_ok());
        let mut state = State::default();
        state.apply(Report::Loaded(Err("corrupt".into()), Some("boot".into())));
        state.select(Some(&found_a()));
        state.draft = "Lamp".into();
        assert!(!state.can_save());
        state.apply(Report::Loaded(
            Ok(Map::from([("ble:A".into(), "Old".into())])),
            Some("boot".into()),
        ));
        state.select(Some(&found_a()));
        state.draft = "Lamp".into();
        state.request_save();
        let request = state.queued.take().unwrap();
        assert!(!state.can_save());
        state.apply(Report::Saved(request, Err("disk full".into())));
        assert_eq!(state.alias(&found_a()), Some("Old"));
        assert_eq!(state.error.as_deref(), Some("disk full"));
        state.draft = "\t".into();
        state.request_save();
        assert!(state.queued.is_none());
        state.select(Some(&found_b()));
        assert!(state.draft.is_empty());
    }

    /// Test: UT-APP-032
    #[test]
    fn the_file_service_loads_saves_and_reopens_without_device_io() {
        let dir = tempfile::tempdir().unwrap();
        let service = Service::start(Ok(dir.path().into()), Arc::new(|| {})).unwrap();
        assert!(matches!(
            service.rx.recv_timeout(Duration::from_secs(3)).unwrap(),
            Report::Loaded(Ok(_), _)
        ));
        let request = Save {
            key: "ble:A".into(),
            name: "Lamp".into(),
        };
        service.send(request.clone()).unwrap();
        assert_eq!(
            service.rx.recv_timeout(Duration::from_secs(3)).unwrap(),
            Report::Saved(request, Ok(()))
        );
        drop(service);
        let reopened = Service::start(Ok(dir.path().into()), Arc::new(|| {})).unwrap();
        assert!(
            matches!(reopened.rx.recv_timeout(Duration::from_secs(3)).unwrap(), Report::Loaded(Ok(map), _) if map.get("ble:A").map(String::as_str) == Some("Lamp"))
        );
        assert!(reopened.poll().is_none());
        let failed = Service::start(Err("no home".into()), Arc::new(|| {})).unwrap();
        assert!(matches!(
            failed.rx.recv_timeout(Duration::from_secs(3)).unwrap(),
            Report::Loaded(Err(_), _)
        ));
    }
}
