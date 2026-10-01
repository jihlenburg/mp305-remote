//! Implements: DD-STORE-001, DD-STORE-002, DD-STORE-003, DD-STORE-004,
//! DD-STORE-006.
//!
//! The per-installation state on disk: the 16-byte host ID the bind
//! presents (SR-049) and one unclean-exit marker per supply identifier
//! (SR-046). [`Store`] implements [`Markers`] for the session and hands the
//! host ID to the product, which passes it to `Session::connect`.
//!
//! The product chooses the directory (AR-033); the store never decides a
//! path itself. The layout under it:
//!
//! | File | Content |
//! |---|---|
//! | `host_id` | 32 lowercase hex characters and a newline |
//! | `markers/<name>.marker` | the marker time as decimal seconds since the Unix epoch, a newline, the supply identifier as given, a newline |
//!
//! `<name>` comes from [`names::marker_name`]. Every write replaces the
//! file in one step or creates it only if absent (`files`), so that a crash
//! never leaves a part of a file and two processes on one directory end
//! with one host ID. Every I/O failure is [`Error::Store`] with the path
//! and the OS error text; a corrupt host ID is replaced with a warning, and
//! a corrupt marker is dropped with a warning, since a marker is advisory
//! (UR-030).

pub(crate) mod files;
pub mod names;

use std::fs;
use std::io;
use std::path::{Path, PathBuf};
use std::time::{Duration, SystemTime, UNIX_EPOCH};

use crate::error::Error;
use crate::protocol::ops::bind::HostId;
use crate::session::Markers;

/// The log target of the store (DD-STORE-006).
pub const LOG_TARGET: &str = "mp305_core::store";

/// The name of the host ID file in the store directory.
const HOST_ID_FILE: &str = "host_id";
/// The number of hex characters of a stored host ID.
const HOST_ID_HEX_LEN: usize = 32;
/// The name of the marker subdirectory.
const MARKERS_DIR: &str = "markers";
/// The extension of a marker file.
const MARKER_EXTENSION: &str = "marker";
/// How many times generation fills the 16 bytes before it gives up.
const GENERATE_ATTEMPTS: usize = 3;

/// The per-installation state in one directory: the host ID and the
/// unclean-exit markers.
///
/// Nothing is cached: every call reads or writes the files, so the app and
/// a script that share a directory see each other's changes.
///
/// ```
/// use mp305_core::session::Markers;
/// use mp305_core::store::Store;
///
/// let dir = tempfile::tempdir()?;
/// let store = Store::new(dir.path());
/// let id = store.host_id()?;
/// assert_eq!(store.host_id()?, id);
/// assert_eq!(store.present("AB12")?, None);
/// # Ok::<(), Box<dyn std::error::Error>>(())
/// ```
#[derive(Clone, Debug)]
pub struct Store {
    /// The directory the product chose; created on the first write.
    dir: PathBuf,
}

impl Store {
    /// A store in `dir`. Does no I/O: the directory and its `markers`
    /// subdirectory are created on the first write that needs them.
    #[must_use]
    pub fn new(dir: impl Into<PathBuf>) -> Store {
        Store { dir: dir.into() }
    }

    /// The host ID of this installation (SR-049): read from `host_id` on
    /// every call, never all zero and never WebLink's constant.
    ///
    /// A missing file is created with a new ID from the OS random source
    /// (logged at INFO). If another process creates it at the same moment,
    /// its ID is adopted, so both end with one ID. A file whose content is
    /// not a valid ID is replaced by a new one (logged at WARN with the
    /// reason).
    ///
    /// # Errors
    ///
    /// [`Error::Store`] when the file cannot be read for a reason other
    /// than its absence (then nothing is written, so that a transient error
    /// never destroys a valid ID), when the directory or the file cannot be
    /// written, or when the OS random source fails.
    pub fn host_id(&self) -> Result<HostId, Error> {
        let path = self.dir.join(HOST_ID_FILE);
        match fs::read(&path) {
            Ok(content) => match parse_host_id(&content) {
                Ok(id) => Ok(id),
                Err(reason) => {
                    let id = generate_with(getrandom::fill).map_err(|e| at_path(&path, e))?;
                    replace(&path, id, &reason)
                }
            },
            Err(error) if error.kind() == io::ErrorKind::NotFound => {
                let id = generate_with(getrandom::fill).map_err(|e| at_path(&path, e))?;
                fs::create_dir_all(&self.dir).map_err(|e| io_error(&self.dir, &e))?;
                create_or_adopt(&path, id)
            }
            Err(error) => Err(io_error(&path, &error)),
        }
    }

    /// The marker file for `identifier`, and its name for the log.
    fn marker_path(&self, identifier: &str) -> (PathBuf, String) {
        let name = names::marker_name(identifier);
        let path = self
            .dir
            .join(MARKERS_DIR)
            .join(format!("{name}.{MARKER_EXTENSION}"));
        (path, name)
    }
}

/// A new host ID from `fill`: fills 16 bytes up to three times until
/// [`HostId::new`] accepts them. The rejected values (all zero and
/// WebLink's constant) have a probability of 2 to the power of minus 127
/// from a real random source, so a third rejection means a broken source.
///
/// # Errors
///
/// [`Error::Store`] when `fill` fails (its text included) or after the
/// third rejected value.
pub(crate) fn generate_with(
    mut fill: impl FnMut(&mut [u8]) -> Result<(), getrandom::Error>,
) -> Result<HostId, Error> {
    for _ in 0..GENERATE_ATTEMPTS {
        let mut bytes = [0u8; 16];
        fill(&mut bytes).map_err(|error| Error::Store {
            message: format!("random source: {error}"),
        })?;
        if let Ok(id) = HostId::new(bytes) {
            return Ok(id);
        }
    }
    Err(Error::Store {
        message: format!("random source: {GENERATE_ATTEMPTS} values rejected"),
    })
}

/// The first write of a host ID: creates `path` with `generated` if it
/// does not exist yet (logged at INFO), or adopts the ID another process
/// wrote there first. An existing file that is not a valid ID is replaced
/// with `generated`; two processes that both find a corrupt file both
/// replace it and the last one wins, an accepted window.
///
/// # Errors
///
/// [`Error::Store`] when the file cannot be created, read or replaced.
pub(crate) fn create_or_adopt(path: &Path, generated: HostId) -> Result<HostId, Error> {
    let created = files::write_if_absent(path, encode_host_id(&generated).as_bytes())
        .map_err(|e| io_error(path, &e))?;
    if created {
        log::info!(target: LOG_TARGET, "host id created {}", path.display());
        return Ok(generated);
    }
    let content = fs::read(path).map_err(|e| io_error(path, &e))?;
    match parse_host_id(&content) {
        Ok(id) => Ok(id),
        Err(reason) => replace(path, generated, &reason),
    }
}

/// Replaces a corrupt host ID file with `id` in one step and logs why.
///
/// # Errors
///
/// [`Error::Store`] when the write fails; nothing is logged then.
fn replace(path: &Path, id: HostId, reason: &str) -> Result<HostId, Error> {
    files::write_atomic(path, encode_host_id(&id).as_bytes()).map_err(|e| io_error(path, &e))?;
    log::warn!(target: LOG_TARGET, "host id replaced: {reason}");
    Ok(id)
}

/// Parses the content of a host ID file (DD-STORE-002): UTF-8, ASCII
/// whitespace trimmed, 32 hex characters of either case, and a value
/// [`HostId::new`] accepts.
///
/// # Errors
///
/// The reason for the log line: `not utf-8`, `length <n>`, `not hex` or
/// `rejected`.
fn parse_host_id(content: &[u8]) -> Result<HostId, String> {
    let text = core::str::from_utf8(content)
        .map_err(|_| "not utf-8".to_string())?
        .trim_ascii();
    if text.len() != HOST_ID_HEX_LEN {
        return Err(format!("length {}", text.len()));
    }
    if !text.bytes().all(|b| b.is_ascii_hexdigit()) {
        return Err("not hex".to_string());
    }
    let mut bytes = [0u8; 16];
    for (byte, pair) in bytes.iter_mut().zip(text.as_bytes().chunks_exact(2)) {
        // Every pair is two ASCII hex digits after the check above, so
        // neither step fails; the error keeps the code free of panics.
        *byte = core::str::from_utf8(pair)
            .ok()
            .and_then(|pair| u8::from_str_radix(pair, 16).ok())
            .ok_or_else(|| "not hex".to_string())?;
    }
    HostId::new(bytes).map_err(|_| "rejected".to_string())
}

/// A host ID as the file holds it: 32 lowercase hex characters and a
/// newline.
fn encode_host_id(id: &HostId) -> String {
    let mut text: String = id.as_bytes().iter().map(|b| format!("{b:02x}")).collect();
    text.push('\n');
    text
}

/// Why a marker file is ignored (DD-STORE-004).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum Ignored {
    /// Not exactly two lines.
    Malformed,
    /// The first line is not a `u64` in ASCII digits.
    NotANumber,
    /// The second line is another identifier, whose name collided.
    Mismatch,
    /// The seconds lie outside the range of `SystemTime`.
    OutOfRange,
}

impl Ignored {
    /// The reason for the log line.
    fn reason(self) -> &'static str {
        match self {
            Ignored::Malformed => "malformed",
            Ignored::NotANumber => "not a number",
            Ignored::Mismatch => "identifier mismatch",
            Ignored::OutOfRange => "out of range",
        }
    }

    /// Whether the file is removed. A mismatched file is left alone: it
    /// belongs to another identifier.
    fn removes(self) -> bool {
        self != Ignored::Mismatch
    }
}

/// Parses the content of the marker file of `identifier`: after
/// `trim_ascii`, exactly two lines (`\n` or `\r\n`), the first ASCII digits
/// that fit a `u64`, the second equal to `identifier`, and the seconds
/// within the range of `SystemTime`.
///
/// # Errors
///
/// Why the file is ignored, checked in that order.
fn parse_marker(content: &[u8], identifier: &str) -> Result<SystemTime, Ignored> {
    let lines: Vec<&[u8]> = content
        .trim_ascii()
        .split(|&b| b == b'\n')
        .map(|line| line.strip_suffix(b"\r").unwrap_or(line))
        .collect();
    let [seconds, name] = lines.as_slice() else {
        return Err(Ignored::Malformed);
    };
    if seconds.is_empty() || !seconds.iter().all(u8::is_ascii_digit) {
        return Err(Ignored::NotANumber);
    }
    let seconds = core::str::from_utf8(seconds)
        .ok()
        .and_then(|s| s.parse::<u64>().ok())
        .ok_or(Ignored::NotANumber)?;
    if *name != identifier.as_bytes() {
        return Err(Ignored::Mismatch);
    }
    UNIX_EPOCH
        .checked_add(Duration::from_secs(seconds))
        .ok_or(Ignored::OutOfRange)
}

/// [`Error::Store`] for an I/O failure on `path`: `<path>: <os error>`.
fn io_error(path: &Path, error: &io::Error) -> Error {
    Error::Store {
        message: format!("{}: {error}", path.display()),
    }
}

/// Puts `path` in front of the message of a store error that has none,
/// so that every message names the file it is about.
fn at_path(path: &Path, error: Error) -> Error {
    match error {
        Error::Store { message } => Error::Store {
            message: format!("{}: {message}", path.display()),
        },
        other => other,
    }
}

impl Markers for Store {
    /// The marker time for `identifier`, in whole seconds. A missing file
    /// is `None`. A file that cannot be read, or whose content is not a
    /// marker of `identifier`, is logged at WARN and is `None`; a corrupt
    /// one is also removed, while a file of another identifier whose name
    /// collided is left alone. An identifier that cannot be stored
    /// ([`names::storable`]) has no marker: `None`, and no file is touched.
    fn present(&self, identifier: &str) -> Result<Option<SystemTime>, Error> {
        if names::storable(identifier).is_err() {
            return Ok(None);
        }
        let (path, _) = self.marker_path(identifier);
        let content = match fs::read(&path) {
            Ok(content) => content,
            Err(error) if error.kind() == io::ErrorKind::NotFound => return Ok(None),
            Err(_) => {
                log::warn!(target: LOG_TARGET, "marker ignored {}: unreadable", path.display());
                return Ok(None);
            }
        };
        match parse_marker(&content, identifier) {
            Ok(at) => Ok(Some(at)),
            Err(ignored) => {
                log::warn!(
                    target: LOG_TARGET,
                    "marker ignored {}: {}",
                    path.display(),
                    ignored.reason()
                );
                if ignored.removes() {
                    if let Err(error) = fs::remove_file(&path) {
                        log::warn!(
                            target: LOG_TARGET,
                            "marker not removed {}: {error}",
                            path.display()
                        );
                    }
                }
                Ok(None)
            }
        }
    }

    /// Writes the marker for `identifier` in one step: `at` in whole
    /// seconds since the Unix epoch (a time before the epoch as 0) and the
    /// identifier. Creates the directories if needed. An identifier that
    /// cannot be stored ([`names::storable`]) is [`Error::Store`]
    /// `marker identifier <identifier, Debug form> cannot be stored:
    /// <reason>`, and nothing is written.
    fn set(&self, identifier: &str, at: SystemTime) -> Result<(), Error> {
        names::storable(identifier).map_err(|reason| Error::Store {
            message: format!("marker identifier {identifier:?} cannot be stored: {reason}"),
        })?;
        let seconds = at.duration_since(UNIX_EPOCH).map_or(0, |d| d.as_secs());
        let markers = self.dir.join(MARKERS_DIR);
        fs::create_dir_all(&markers).map_err(|e| io_error(&markers, &e))?;
        let (path, name) = self.marker_path(identifier);
        files::write_atomic(&path, format!("{seconds}\n{identifier}\n").as_bytes())
            .map_err(|e| io_error(&path, &e))?;
        log::debug!(target: LOG_TARGET, "marker set {name}");
        Ok(())
    }

    /// Removes the marker for `identifier`; a missing one is not an error.
    /// An identifier that cannot be stored ([`names::storable`]) has no
    /// marker: `Ok`, and no file is touched.
    fn clear(&self, identifier: &str) -> Result<(), Error> {
        if names::storable(identifier).is_err() {
            return Ok(());
        }
        let (path, name) = self.marker_path(identifier);
        match fs::remove_file(&path) {
            Ok(()) => {
                log::debug!(target: LOG_TARGET, "marker cleared {name}");
                Ok(())
            }
            Err(error) if error.kind() == io::ErrorKind::NotFound => Ok(()),
            Err(error) => Err(io_error(&path, &error)),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::fs;
    use std::ops::Deref;
    use std::sync::Arc;
    use std::time::{Duration, UNIX_EPOCH};

    use log::Level;

    use crate::transport::test_log::{self, Log};

    /// 2026-10-01T10:00:00Z in seconds since the Unix epoch.
    const AT: u64 = 1_790_848_800;
    /// WebLink's constant host ID (DD-PROTO), as hex.
    const WEBLINK_HEX: &str = "00080808080808080808080808080800";
    /// WebLink's constant host ID (DD-PROTO).
    const WEBLINK: [u8; 16] = [0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0];
    /// A valid ID.
    const VALID: [u8; 16] = [
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE,
        0xAF,
    ];

    /// `seconds` after the Unix epoch.
    fn at(seconds: u64) -> SystemTime {
        UNIX_EPOCH + Duration::from_secs(seconds)
    }

    /// An ID as 32 lowercase hex characters and a newline, as the store
    /// writes it.
    fn id_text(id: &HostId) -> String {
        let mut text: String = id.as_bytes().iter().map(|b| format!("{b:02x}")).collect();
        text.push('\n');
        text
    }

    /// Whether `text` is 32 lowercase hex characters and a newline.
    fn is_id_text(text: &str) -> bool {
        text.len() == 33
            && text.ends_with('\n')
            && text[..32]
                .bytes()
                .all(|b| b.is_ascii_digit() || (b'a'..=b'f').contains(&b))
    }

    /// The names of the entries in `dir`, sorted.
    fn entries(dir: &Path) -> Vec<String> {
        let mut names: Vec<String> = fs::read_dir(dir)
            .unwrap()
            .map(|e| e.unwrap().file_name().to_string_lossy().into_owned())
            .collect();
        names.sort();
        names
    }

    /// The marker file of `identifier` in the store at `dir`.
    fn marker_file(dir: &Path, identifier: &str) -> PathBuf {
        dir.join("markers")
            .join(format!("{}.marker", names::marker_name(identifier)))
    }

    /// Writes `content` into the marker file of `identifier`.
    fn write_marker(dir: &Path, identifier: &str, content: &[u8]) -> PathBuf {
        let path = marker_file(dir, identifier);
        fs::create_dir_all(path.parent().unwrap()).unwrap();
        fs::write(&path, content).unwrap();
        path
    }

    /// The lines the store logged on this thread.
    fn store_lines(log: &Log) -> Vec<(Level, String)> {
        log.lines_here(LOG_TARGET)
    }

    /// How many lines the store logged on this thread at `level` that are
    /// exactly `text`.
    fn count(log: &Log, level: Level, text: &str) -> usize {
        store_lines(log)
            .iter()
            .filter(|(l, m)| *l == level && m == text)
            .count()
    }

    /// How many lines the store logged on this thread at WARN.
    fn warnings(log: &Log) -> usize {
        store_lines(log)
            .iter()
            .filter(|(l, _)| *l == Level::Warn)
            .count()
    }

    /// The text of a store error, or a panic for any other result.
    fn store_error_text<T: core::fmt::Debug>(result: Result<T, Error>) -> String {
        match result {
            Err(error @ Error::Store { .. }) => error.to_string(),
            other => panic!("expected Error::Store, got {other:?}"),
        }
    }

    /// The sequence of UT-STORE-004 on the markers `open` returns; `open`
    /// is called again to reopen the store on the same directory.
    fn marker_sequence<P, M>(dir: &Path, open: impl Fn() -> P)
    where
        P: Deref<Target = M>,
        M: Markers + ?Sized,
    {
        let store = open();
        assert_eq!(store.present("a").unwrap(), None);
        store.set("a", at(AT)).unwrap();
        let file = dir.join("markers").join("a-af63dc4c8601ec8c.marker");
        assert_eq!(fs::read(&file).unwrap(), b"1790848800\na\n");
        assert_eq!(store.present("a").unwrap(), Some(at(AT)));
        let reopened = open();
        assert_eq!(reopened.present("a").unwrap(), Some(at(AT)));
        reopened.clear("a").unwrap();
        assert_eq!(reopened.present("a").unwrap(), None);
        reopened.clear("a").unwrap();
        assert!(!file.exists());
    }

    /// Restores the modes of a store directory and its `host_id` so that
    /// `tempdir` can clean up, also when the test fails.
    #[cfg(unix)]
    struct RestoreModes {
        /// The store directory.
        dir: PathBuf,
        /// Its `host_id`.
        file: PathBuf,
    }

    #[cfg(unix)]
    impl Drop for RestoreModes {
        fn drop(&mut self) {
            use std::os::unix::fs::PermissionsExt;
            let _ = fs::set_permissions(&self.dir, fs::Permissions::from_mode(0o700));
            let _ = fs::set_permissions(&self.file, fs::Permissions::from_mode(0o600));
        }
    }

    /// Test: UT-STORE-001
    #[test]
    fn host_id_is_created_on_first_use_and_then_read() {
        let log = test_log::install();
        let dir = tempfile::tempdir().unwrap();
        let store = Store::new(dir.path());
        let path = dir.path().join("host_id");

        let first = store.host_id().unwrap();
        let text = fs::read_to_string(&path).unwrap();
        assert!(is_id_text(&text), "{text:?}");
        assert_eq!(text, id_text(&first));
        let created = format!("host id created {}", path.display());
        assert_eq!(count(&log, Level::Info, &created), 1);

        let second = store.host_id().unwrap();
        assert_eq!(first, second);
        assert_ne!(first.as_bytes(), &[0; 16]);
        assert_ne!(first.as_bytes(), &WEBLINK);
        assert_eq!(count(&log, Level::Info, &created), 1);
        assert_eq!(fs::read_to_string(&path).unwrap(), text);
        assert_eq!(entries(dir.path()), vec!["host_id".to_string()]);
    }

    /// Test: UT-STORE-002
    #[test]
    fn a_corrupt_host_id_is_replaced_and_a_valid_one_kept() {
        let log = test_log::install();
        let dir = tempfile::tempdir().unwrap();
        let store = Store::new(dir.path());
        let path = dir.path().join("host_id");

        let mut not_utf8 = vec![0xFF, 0xFE];
        not_utf8.extend_from_slice(b"0123456789abcdef0123456789abcd");
        let cases: [(&str, Vec<u8>, &str); 5] = [
            ("a", "g".repeat(32).into_bytes(), "not hex"),
            ("b", "0".repeat(32).into_bytes(), "rejected"),
            ("c", WEBLINK_HEX.as_bytes().to_vec(), "rejected"),
            ("d", b"0123456789abcdef0123456789abcd".to_vec(), "length 30"),
            ("f", not_utf8, "not utf-8"),
        ];
        for (case, content, reason) in cases {
            fs::write(&path, &content).unwrap();
            let replaced = format!("host id replaced: {reason}");
            let before = count(&log, Level::Warn, &replaced);
            let id = store.host_id().unwrap();
            assert_eq!(
                fs::read_to_string(&path).unwrap(),
                id_text(&id),
                "case {case}"
            );
            assert_eq!(
                count(&log, Level::Warn, &replaced),
                before + 1,
                "case {case}"
            );
        }
        assert_eq!(entries(dir.path()), vec!["host_id".to_string()]);

        let upper = b"A0A1A2A3A4A5A6A7A8A9AAABACADAEAF \n";
        fs::write(&path, upper).unwrap();
        let before = warnings(&log);
        assert_eq!(store.host_id().unwrap().as_bytes(), &VALID);
        assert_eq!(fs::read(&path).unwrap(), upper);
        assert_eq!(warnings(&log), before);
    }

    /// Test: UT-STORE-003
    #[test]
    fn a_host_id_that_cannot_be_read_is_an_error() {
        let dir = tempfile::tempdir().unwrap();
        let file = dir.path().join("file");
        fs::write(&file, b"x").unwrap();
        let store_dir = file.join("store");
        let text = store_error_text(Store::new(&store_dir).host_id());
        assert!(text.starts_with("store: "), "{text}");
        assert!(text.contains(&store_dir.display().to_string()), "{text}");
        assert_eq!(fs::read(&file).unwrap(), b"x");
    }

    /// Test: UT-STORE-003
    #[cfg(unix)]
    #[test]
    fn an_unreadable_host_id_is_an_error_and_left_alone() {
        use std::os::unix::fs::PermissionsExt;

        let dir = tempfile::tempdir().unwrap();
        let store_dir = dir.path().join("store");
        fs::create_dir(&store_dir).unwrap();
        let path = store_dir.join("host_id");
        let content = "a0a1a2a3a4a5a6a7a8a9aaabacadaeaf\n";
        fs::write(&path, content).unwrap();

        let guard = RestoreModes {
            dir: store_dir.clone(),
            file: path.clone(),
        };
        fs::set_permissions(&path, fs::Permissions::from_mode(0o000)).unwrap();
        fs::set_permissions(&store_dir, fs::Permissions::from_mode(0o500)).unwrap();
        if fs::read(&path).is_ok() {
            // Skipped: the current user reads the file despite mode 0o000
            // (root does), so the unreadable case cannot be produced here.
            // The parent-is-a-file case of this entry still runs in
            // `a_host_id_that_cannot_be_read_is_an_error`.
            eprintln!("skipped: the current user can read a file with mode 0o000");
            return;
        }

        let text = store_error_text(Store::new(&store_dir).host_id());
        assert!(text.starts_with("store: "), "{text}");
        assert!(text.contains(&path.display().to_string()), "{text}");

        drop(guard);
        assert_eq!(fs::read_to_string(&path).unwrap(), content);
        assert_eq!(entries(&store_dir), vec!["host_id".to_string()]);
    }

    /// Test: UT-STORE-004
    #[test]
    fn markers_are_set_read_and_cleared() {
        let dir = tempfile::tempdir().unwrap();
        marker_sequence(dir.path(), || Box::new(Store::new(dir.path())));
    }

    /// Test: UT-STORE-005
    #[test]
    fn corrupt_markers_are_dropped_and_times_are_whole_seconds() {
        let log = test_log::install();
        let dir = tempfile::tempdir().unwrap();
        let store = Store::new(dir.path());
        let warned = |path: &Path, reason: &str| {
            count(
                &log,
                Level::Warn,
                &format!("marker ignored {}: {reason}", path.display()),
            )
        };

        let path = write_marker(dir.path(), "b", b"nope\nb\n");
        assert_eq!(store.present("b").unwrap(), None);
        assert!(!path.exists());
        assert_eq!(warned(&path, "not a number"), 1);

        let path = write_marker(dir.path(), "b", b"9223372036854775808\nb\n");
        assert_eq!(store.present("b").unwrap(), None);
        assert!(!path.exists());
        assert_eq!(warned(&path, "out of range"), 1);

        let path = write_marker(dir.path(), "b", b"1790848800\nother\n");
        assert_eq!(store.present("b").unwrap(), None);
        assert_eq!(fs::read(&path).unwrap(), b"1790848800\nother\n");
        assert_eq!(warned(&path, "identifier mismatch"), 1);

        let path = write_marker(dir.path(), "b", b"1790848800\n");
        assert_eq!(store.present("b").unwrap(), None);
        assert!(!path.exists());
        assert_eq!(warned(&path, "malformed"), 1);

        let before_epoch = UNIX_EPOCH - Duration::from_secs(1);
        store.set("c", before_epoch).unwrap();
        assert_eq!(fs::read(marker_file(dir.path(), "c")).unwrap(), b"0\nc\n");
        assert_eq!(store.present("c").unwrap(), Some(UNIX_EPOCH));

        store.set("d", at(AT) + Duration::from_millis(750)).unwrap();
        assert_eq!(store.present("d").unwrap(), Some(at(AT)));
    }

    /// Test: UT-STORE-005
    #[test]
    fn an_unreadable_marker_is_ignored() {
        let log = test_log::install();
        let dir = tempfile::tempdir().unwrap();
        let path = marker_file(dir.path(), "e");
        fs::create_dir_all(&path).unwrap();
        assert_eq!(Store::new(dir.path()).present("e").unwrap(), None);
        let unreadable = format!("marker ignored {}: unreadable", path.display());
        assert_eq!(count(&log, Level::Warn, &unreadable), 1);
        assert!(path.is_dir());
    }

    /// Test: UT-STORE-011
    #[test]
    fn identifiers_that_cannot_be_stored_have_no_marker() {
        let dir = tempfile::tempdir().unwrap();
        let store = Store::new(dir.path());
        let cases = [
            ("", "\"\"", "empty"),
            (" a", "\" a\"", "surrounding whitespace"),
            ("a\nb", "\"a\\nb\"", "line break"),
        ];
        for (identifier, debug, reason) in cases {
            match store.set(identifier, at(AT)) {
                Err(Error::Store { message }) => assert_eq!(
                    message,
                    format!("marker identifier {debug} cannot be stored: {reason}")
                ),
                other => panic!("{identifier:?}: expected Error::Store, got {other:?}"),
            }
        }
        assert_eq!(entries(dir.path()), Vec::<String>::new());
        for (identifier, _, _) in cases {
            assert_eq!(store.present(identifier).unwrap(), None, "{identifier:?}");
            store.clear(identifier).unwrap();
        }
        assert_eq!(entries(dir.path()), Vec::<String>::new());

        // Neither `present` nor `clear` touches a file: a marker that would
        // otherwise read back as valid is neither read nor removed.
        let planted = write_marker(dir.path(), " a", b"1790848800\n a\n");
        assert_eq!(store.present(" a").unwrap(), None);
        store.clear(" a").unwrap();
        assert_eq!(fs::read(&planted).unwrap(), b"1790848800\n a\n");
    }

    /// Test: UT-STORE-008
    #[test]
    fn markers_work_through_the_trait_object() {
        let dir = tempfile::tempdir().unwrap();
        marker_sequence(dir.path(), || -> Arc<dyn Markers> {
            Arc::new(Store::new(dir.path()))
        });
    }

    /// Test: UT-STORE-009
    #[test]
    fn log_lines_and_error_texts() {
        let log = test_log::install();
        let dir = tempfile::tempdir().unwrap();
        let store = Store::new(dir.path());
        let path = dir.path().join("host_id");

        store.host_id().unwrap();
        fs::write(&path, "g".repeat(32)).unwrap();
        store.host_id().unwrap();
        for content in [
            &b"nope\nb\n"[..],
            &b"9223372036854775808\nb\n"[..],
            &b"1790848800\nother\n"[..],
        ] {
            write_marker(dir.path(), "b", content);
            assert_eq!(store.present("b").unwrap(), None);
        }

        let marker = marker_file(dir.path(), "b");
        let expected = vec![
            (Level::Info, format!("host id created {}", path.display())),
            (Level::Warn, "host id replaced: not hex".to_string()),
            (
                Level::Warn,
                format!("marker ignored {}: not a number", marker.display()),
            ),
            (
                Level::Warn,
                format!("marker ignored {}: out of range", marker.display()),
            ),
            (
                Level::Warn,
                format!("marker ignored {}: identifier mismatch", marker.display()),
            ),
        ];
        assert_eq!(store_lines(&log), expected);

        let file = dir.path().join("file");
        fs::write(&file, b"x").unwrap();
        let store_dir = file.join("store");
        let text = store_error_text(Store::new(&store_dir).host_id());
        assert!(text.starts_with("store: "), "{text}");
        assert!(text.contains(&store_dir.display().to_string()), "{text}");
    }

    /// Test: UT-STORE-010
    #[test]
    fn generation_retries_rejected_values_and_reports_failures() {
        let mut values = [[0u8; 16], WEBLINK, VALID].into_iter();
        let mut calls = 0;
        let id = generate_with(|buf| {
            calls += 1;
            buf.copy_from_slice(&values.next().unwrap());
            Ok(())
        })
        .unwrap();
        assert_eq!(id.as_bytes(), &VALID);
        assert_eq!(calls, 3);

        let mut calls = 0;
        let result = generate_with(|buf| {
            calls += 1;
            buf.fill(0);
            Ok(())
        });
        store_error_text(result);
        assert_eq!(calls, 3);

        let text = store_error_text(generate_with(|_| Err(getrandom::Error::UNSUPPORTED)));
        assert!(
            text.contains(&getrandom::Error::UNSUPPORTED.to_string()),
            "{text}"
        );
    }

    /// Test: UT-STORE-010
    #[test]
    fn create_or_adopt_adopts_an_existing_valid_id() {
        let dir = tempfile::tempdir().unwrap();
        let path = dir.path().join("host_id");
        let content = "a0a1a2a3a4a5a6a7a8a9aaabacadaeaf\n";
        fs::write(&path, content).unwrap();
        let generated = HostId::new([0x11; 16]).unwrap();
        let id = create_or_adopt(&path, generated).unwrap();
        assert_eq!(id.as_bytes(), &VALID);
        assert_eq!(fs::read_to_string(&path).unwrap(), content);
        assert_eq!(entries(dir.path()), vec!["host_id".to_string()]);
    }
}
