//! Implements: DD-DISC-001, DD-DISC-004, DD-DISC-005, DD-DISC-010,
//! DD-DISC-011, DD-DISC-020.
//!
//! Discovery: finds supplies over Bluetooth LE and USB HID and turns an
//! identifier into a guarded transport for the session (the [`Connector`]
//! implementation).
//!
//! Everything decidable lives in pure functions in [`classify`] (the two
//! classifiers, the sighting accumulator, the name choice, the identifier
//! shape test, the connect plan and the USB target choice) and here (the
//! power-state verdict, which connect needs Bluetooth, and the lazy
//! adapter slot). The vendor calls live in the two glue files `ble` and
//! `hid`, which only move OS data to and from the pure part and are
//! excluded from the coverage measurement under ADR-0014, and in
//! `hid_owner`, the bounded owner thread of the USB calls. This file makes
//! no vendor call of its own and names no vendor type.

mod ble;
pub mod classify;
mod hid;
mod hid_owner;

use core::fmt;
use core::time::Duration;
use std::sync::Arc;

use futures::future::BoxFuture;
use tokio::sync::Mutex;

use crate::discovery::classify::{Plan, Purpose};
use crate::error::Error;
use crate::protocol::timing;
use crate::session::Connector;
use crate::transport::description::Kind;
use crate::transport::guarded::Guarded;
use crate::transport::AnyTransport;

/// The log target of discovery.
pub const LOG_TARGET: &str = "mp305_core::discovery";

/// The four states of SR-005 in which a supply does not advertise, in
/// SR-005's order, as one text.
const CAUSES: &str = "the supply is off or out of range; \
                      another app (WebLink in a browser, ISDT's Polying app) is connected to it; \
                      a USB host is talking to it; \
                      remote control is disabled on the supply";

/// The field name of a scan time outside its bound.
const SCAN_TIME_FIELD: &str = "scan time (s)";

/// A supply that discovery found.
///
/// `identifier` is what [`Session::connect`](crate::session::Session::connect)
/// and the [`Connector`] take: over Bluetooth the
/// OS peripheral identifier's text (a lowercase hyphenated UUID on macOS,
/// `AA:BB:CC:DD:EE:FF` on Windows, `hci0/dev_AA_BB_CC_DD_EE_FF` on Linux),
/// over USB the HID device path. Identifiers are compared as exact text.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Found {
    /// The link the supply was found on.
    pub transport: Kind,
    /// The identifier to connect with.
    pub identifier: String,
    /// The unit characters: the last three characters of a 29-character
    /// advertised name over Bluetooth (empty for any other name), the HID
    /// path over USB.
    pub unit_id: String,
    /// The advertised name over Bluetooth (empty when none was advertised),
    /// the product string over USB.
    pub name: String,
    /// The received signal strength in dBm, over Bluetooth when the OS
    /// reported one.
    pub rssi: Option<i16>,
    /// Whether the advertised name carries the remote-control flag `S` at
    /// index 12: `None` for any name that is not 29 characters long, for no
    /// name, and over USB.
    pub remote_flag: Option<bool>,
}

impl fmt::Display for Found {
    /// `<kind> <identifier> <name or "(no name)"> (unit <unit_id or "?">)`.
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let name = if self.name.is_empty() {
            "(no name)"
        } else {
            &self.name
        };
        let unit = if self.unit_id.is_empty() {
            "?"
        } else {
            &self.unit_id
        };
        write!(
            f,
            "{} {} {name} (unit {unit})",
            self.transport, self.identifier
        )
    }
}

/// What a scan looks for and for how long.
///
/// The scan time is private, so the bound of 1 s to 60 s (SR-002) cannot be
/// bypassed: [`ScanOptions::with_duration`] is the only way to change it.
///
/// ```
/// use core::time::Duration;
/// use mp305_core::discovery::ScanOptions;
/// let options = ScanOptions::default().with_duration(Duration::from_secs(30))?;
/// assert_eq!(options.duration(), Duration::from_secs(30));
/// assert!(ScanOptions::default().with_duration(Duration::ZERO).is_err());
/// # Ok::<(), mp305_core::error::Error>(())
/// ```
///
/// The two examples below must not compile (Test: UT-DISC-005).
///
/// ```compile_fail,E0451
/// use core::time::Duration;
/// use mp305_core::discovery::ScanOptions;
/// let options = ScanOptions { bluetooth: true, usb: true, duration: Duration::ZERO };
/// ```
///
/// ```compile_fail,E0616
/// use core::time::Duration;
/// use mp305_core::discovery::ScanOptions;
/// let mut options = ScanOptions::default();
/// options.duration = Duration::ZERO;
/// ```
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct ScanOptions {
    /// Scan over Bluetooth LE.
    pub bluetooth: bool,
    /// Enumerate USB HID devices.
    pub usb: bool,
    /// How long the Bluetooth scan runs.
    duration: Duration,
}

impl Default for ScanOptions {
    /// Both transports, [`timing::SCAN_DEFAULT`].
    fn default() -> Self {
        Self {
            bluetooth: true,
            usb: true,
            duration: timing::SCAN_DEFAULT,
        }
    }
}

impl ScanOptions {
    /// The same options with the scan time `duration`.
    ///
    /// # Errors
    ///
    /// [`Error::SetpointRange`] with the field `scan time (s)` when
    /// `duration` is outside [`timing::SCAN_MIN`] to [`timing::SCAN_MAX`].
    pub fn with_duration(self, duration: Duration) -> Result<Self, Error> {
        if duration < timing::SCAN_MIN || duration > timing::SCAN_MAX {
            return Err(Error::SetpointRange {
                field: SCAN_TIME_FIELD,
                value: duration.as_secs_f64(),
                min: timing::SCAN_MIN.as_secs_f64(),
                max: timing::SCAN_MAX.as_secs_f64(),
            });
        }
        Ok(Self { duration, ..self })
    }

    /// The scan time.
    #[must_use]
    pub fn duration(&self) -> Duration {
        self.duration
    }
}

/// The error for "no supply found", with the four causes of SR-005. The
/// products return it when a scan finds nothing; [`Discovery`]'s connect
/// returns it when the identifier is not found.
#[must_use]
pub fn not_found() -> Error {
    Error::NotFound {
        causes: CAUSES.to_string(),
    }
}

/// The message of a Bluetooth scan or connect while the adapter reports
/// that it is powered off.
const SWITCHED_OFF: &str = "Bluetooth is switched off on this computer";

/// The power state of the Bluetooth adapter, as the glue read it.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub(crate) enum Radio {
    /// The adapter reports that it is powered on.
    On,
    /// The adapter reports that it is powered off.
    Off,
    /// The adapter reports no state, or the read failed.
    Unknown,
}

/// The verdict on the adapter's power state before a Bluetooth scan or
/// connect: only [`Radio::Off`] stops it; an unknown state proceeds.
///
/// # Errors
///
/// [`Error::Transport`] with the message `Bluetooth is switched off on this
/// computer` for [`Radio::Off`].
fn radio_check(radio: Radio) -> Result<(), Error> {
    match radio {
        Radio::Off => Err(Error::Transport {
            message: SWITCHED_OFF.to_string(),
        }),
        Radio::On | Radio::Unknown => Ok(()),
    }
}

/// Whether a connect to `identifier` needs Bluetooth: only an identifier
/// with a Bluetooth shape ([`classify::looks_like_ble_id`]) does; a HID
/// path never touches Bluetooth.
fn connect_needs_bluetooth(identifier: &str) -> bool {
    classify::looks_like_ble_id(identifier)
}

/// A value looked up on first need and kept once found. A lookup that
/// found nothing is not kept, so the next need looks again.
///
/// The lock is held during the lookup, so that two needs at once start one
/// lookup (one Bluetooth manager), not two.
struct Lazy<A> {
    /// The value once found.
    slot: Mutex<Option<A>>,
}

impl<A: Clone> Lazy<A> {
    /// An empty slot.
    fn new() -> Self {
        Self {
            slot: Mutex::new(None),
        }
    }

    /// The kept value, else the result of `lookup`, kept when it is `Some`.
    async fn get<F, Fut>(&self, lookup: F) -> Option<A>
    where
        F: FnOnce() -> Fut,
        Fut: core::future::Future<Output = Option<A>>,
    {
        let mut slot = self.slot.lock().await;
        if let Some(value) = slot.as_ref() {
            return Some(value.clone());
        }
        let found = lookup().await;
        slot.clone_from(&found);
        found
    }
}

/// Looks for the first Bluetooth adapter; `None` when there is none.
type AdapterLookup = Box<dyn Fn() -> BoxFuture<'static, Option<ble::Adapter>> + Send + Sync>;

/// Finds supplies over Bluetooth LE and USB HID, and connects to one by
/// its identifier (the session's [`Connector`]). One per process.
///
/// Bluetooth is started on first need: a scan with `bluetooth` set, or a
/// connect to an identifier with a Bluetooth shape. A USB-only scan and a
/// connect by HID path never touch it. The first adapter found is kept for
/// the life of the `Discovery`; when none is found, the next need looks
/// again, so an adapter that appears later is used. It also holds the scan
/// lock that keeps a second scan from ending the first. It is `Send` and
/// `Sync`.
pub struct Discovery {
    /// The first Bluetooth adapter, once found.
    adapter: Lazy<ble::Adapter>,
    /// How the adapter is looked for.
    lookup: AdapterLookup,
    /// The scan lock, held from before the Bluetooth scan starts until
    /// after it stops.
    lock: Arc<Mutex<()>>,
}

impl Discovery {
    /// Probes the USB side; a failed probe is logged at WARN and a later
    /// USB scan or connect reports its own error. Bluetooth is not started
    /// here (see [`Discovery`]), so a missing adapter is found out at the
    /// first need.
    ///
    /// # Errors
    ///
    /// None at present; the `Result` is kept for the callers.
    pub async fn new() -> Result<Self, Error> {
        // A failure is logged inside, at WARN.
        let _ = hid::available().await;
        Ok(Self {
            adapter: Lazy::new(),
            lookup: Box::new(|| Box::pin(ble::adapter())),
            lock: Arc::new(Mutex::new(())),
        })
    }

    /// The Bluetooth adapter: the kept one, else a new lookup.
    async fn adapter(&self) -> Option<ble::Adapter> {
        self.adapter.get(|| (self.lookup)()).await
    }

    /// Scans for supplies: over Bluetooth for `options.duration()` when
    /// `options.bluetooth` is set and an adapter exists, and over USB when
    /// `options.usb` is set, both at once. The results are concatenated,
    /// Bluetooth first. A backend that fails is logged at WARN and the
    /// other's results are returned; so are an adapter that is switched off
    /// (`Bluetooth is switched off on this computer`) and a USB enumeration
    /// that does not complete within `timing::FIND`. An enabled transport
    /// without a backend is skipped with a WARN log when another one ran. An
    /// empty list means no supply was found (or no transport was enabled);
    /// the products then show [`not_found`].
    ///
    /// # Errors
    ///
    /// [`Error::Transport`] when every backend that ran failed, and when a
    /// transport was enabled but none of the enabled ones had a backend to
    /// run, so that a missing adapter is not reported as "no supply found".
    pub async fn scan(&self, options: ScanOptions) -> Result<Vec<Found>, Error> {
        log::info!(target: LOG_TARGET, "scan start {options:?}");
        let bluetooth = async {
            if !options.bluetooth {
                return None;
            }
            let Some(adapter) = self.adapter().await else {
                log::warn!(target: LOG_TARGET, "Bluetooth scan skipped: no adapter");
                return None;
            };
            if let Err(error) = radio_check(ble::radio(&adapter).await) {
                return Some(Err(error));
            }
            Some(ble::scan(&adapter, Arc::clone(&self.lock), options.duration).await)
        };
        let usb = async {
            if options.usb {
                Some(hid::scan().await)
            } else {
                None
            }
        };
        let (bluetooth, usb) = tokio::join!(bluetooth, usb);
        // The USB side has a backend whenever it is enabled, so only the
        // Bluetooth side can be enabled and unable to run.
        if options.bluetooth && bluetooth.is_none() && usb.is_none() {
            return Err(Error::Transport {
                message: "no backend for the enabled transports: Bluetooth".to_string(),
            });
        }
        let found = merge(bluetooth, usb)?;
        for supply in &found {
            log::info!(target: LOG_TARGET, "found {supply}");
        }
        log::info!(target: LOG_TARGET, "scan done {} found", found.len());
        Ok(found)
    }

    /// The connect flow without the outer bound. An identifier without a
    /// Bluetooth shape is a HID path: one owner-thread job lists the USB
    /// devices, chooses the target with [`classify::hid_target`] for
    /// `purpose` and opens it, within `timing::CONNECT`. A Bluetooth
    /// identifier needs the adapter and its power state, then the ids the
    /// adapter holds, the plan of [`classify::connect_plan`], and a `find`
    /// before the connect; `purpose` does not change it.
    ///
    /// # Errors
    ///
    /// [`not_found`] when the identifier is not found or not seen
    /// advertising within `timing::FIND`; [`Error::Transport`] when the USB
    /// side fails or does not answer in time, a Bluetooth identifier has no
    /// adapter or the adapter is switched off, or the backend's connect or
    /// open fails.
    async fn reach(
        &self,
        identifier: &str,
        purpose: Purpose,
    ) -> Result<Guarded<AnyTransport>, Error> {
        if !connect_needs_bluetooth(identifier) {
            return hid::connect(identifier, purpose).await;
        }
        let Some(adapter) = self.adapter().await else {
            return Err(Error::Transport {
                message: format!("no Bluetooth adapter to reach {identifier}"),
            });
        };
        radio_check(ble::radio(&adapter).await)?;
        let ble_known = ble::known_ids(&adapter).await.unwrap_or_else(|error| {
            log::warn!(target: LOG_TARGET, "the adapter's peripherals could not be listed: {error}");
            Vec::new()
        });
        let plan = classify::connect_plan(identifier, &ble_known, &[]);
        log::info!(target: LOG_TARGET, "connect {identifier} {plan:?}");
        match plan {
            Plan::BleKnown | Plan::BleFind => {
                match ble::find(&adapter, Arc::clone(&self.lock), identifier, timing::FIND).await? {
                    Some(id) => ble::connect(&adapter, &id).await,
                    None => {
                        log::warn!(
                            target: LOG_TARGET,
                            "{identifier} not seen advertising within {} s",
                            timing::FIND.as_secs()
                        );
                        Err(not_found())
                    }
                }
            }
            // A Bluetooth-shaped identifier with no HID paths given plans
            // neither of these.
            Plan::HidPath | Plan::NotFound => Err(not_found()),
        }
    }

    /// [`Discovery::reach`] under the bound
    /// `timing::FIND + timing::CONNECT + timing::CLOSE` as a whole (the
    /// find, the connect and the cancel of a connect that expired or
    /// failed), the wait for the scan lock included.
    async fn bounded(
        &self,
        identifier: &str,
        purpose: Purpose,
    ) -> Result<Guarded<AnyTransport>, Error> {
        let bound = timing::FIND
            .saturating_add(timing::CONNECT)
            .saturating_add(timing::CLOSE);
        tokio::time::timeout(bound, self.reach(identifier, purpose))
            .await
            .unwrap_or_else(|_| {
                Err(Error::Transport {
                    message: format!(
                        "connect to {identifier} did not complete within {} s",
                        bound.as_secs()
                    ),
                })
            })
    }

    /// Connects again to the supply with `identifier`, for the session's
    /// automatic reconnection after a link loss: as [`Connector::connect`],
    /// with the same bound and error texts, except that over USB a supply
    /// whose HID path changed is reached when it is the only supply listed
    /// (see [`classify::hid_target`]; logged at WARN with the old and the
    /// new path). Bluetooth identifiers are reached as by a first connect.
    ///
    /// # Errors
    ///
    /// As [`Connector::connect`].
    pub async fn connect_again(&self, identifier: &str) -> Result<Guarded<AnyTransport>, Error> {
        self.bounded(identifier, Purpose::Again).await
    }
}

impl Connector for Discovery {
    /// Connects to the supply with `identifier` under the bound
    /// `timing::FIND + timing::CONNECT + timing::CLOSE` as a whole (the
    /// find, the connect and the cancel of a connect that expired or
    /// failed), the wait for the scan lock included. Over USB only the
    /// exact HID path is reached (SR-004).
    fn connect<'a>(
        &'a self,
        identifier: &'a str,
    ) -> BoxFuture<'a, Result<Guarded<AnyTransport>, Error>> {
        Box::pin(self.bounded(identifier, Purpose::First))
    }

    /// Connects again for the session's automatic reconnection: as
    /// [`Discovery::connect_again`], so over USB a supply whose HID path
    /// changed is reached when it is the only supply listed.
    fn reconnect<'a>(
        &'a self,
        identifier: &'a str,
    ) -> BoxFuture<'a, Result<Guarded<AnyTransport>, Error>> {
        Box::pin(self.connect_again(identifier))
    }
}

/// Concatenates the results of the two backends, Bluetooth first. `None`
/// is a backend that did not run. A failed backend is logged at WARN; the
/// scan fails only when every backend that ran failed.
fn merge(
    bluetooth: Option<Result<Vec<Found>, Error>>,
    usb: Option<Result<Vec<Found>, Error>>,
) -> Result<Vec<Found>, Error> {
    let mut found = Vec::new();
    let mut failures = Vec::new();
    let mut succeeded = false;
    for (backend, outcome) in [("Bluetooth", bluetooth), ("USB", usb)] {
        match outcome {
            None => {}
            Some(Ok(list)) => {
                succeeded = true;
                found.extend(list);
            }
            Some(Err(error)) => {
                log::warn!(target: LOG_TARGET, "{backend} scan failed: {error}");
                failures.push(format!("{backend}: {error}"));
            }
        }
    }
    if !succeeded && !failures.is_empty() {
        return Err(Error::Transport {
            message: format!("every scan failed: {}", failures.join("; ")),
        });
    }
    Ok(found)
}

#[cfg(test)]
mod tests {
    use std::sync::atomic::{AtomicUsize, Ordering};

    use super::*;
    use crate::discovery::classify::tests::{capture_data, CAPTURE_NAME};

    /// Test: UT-DISC-004
    #[test]
    fn display_of_found() {
        let id1 =
            classify::advertisement("id1", Some(CAPTURE_NAME), &capture_data(), Some(-61)).unwrap();
        let id3 = classify::advertisement("id3", None, &capture_data(), Some(-70)).unwrap();
        let usb = classify::hid(0x28E9, 0x028A, Some("MP305B"), "/dev/hidraw3").unwrap();
        assert_eq!(
            id1.to_string(),
            "ble id1 0000MP305B  S             E!K (unit E!K)"
        );
        assert_eq!(id3.to_string(), "ble id3 (no name) (unit ?)");
        assert_eq!(
            usb.to_string(),
            "hid /dev/hidraw3 MP305B (unit /dev/hidraw3)"
        );
    }

    /// Test: UT-DISC-005
    #[test]
    fn scan_options_default_and_the_bounded_scan_time() {
        let default = ScanOptions::default();
        assert!(default.bluetooth);
        assert!(default.usb);
        assert_eq!(default.duration(), Duration::from_secs(10));
        let one = default.with_duration(Duration::from_secs(1)).unwrap();
        assert_eq!(one.duration(), Duration::from_secs(1));
        let sixty = default.with_duration(Duration::from_secs(60)).unwrap();
        assert_eq!(sixty.duration(), Duration::from_secs(60));
        let short = default
            .with_duration(Duration::from_millis(500))
            .unwrap_err();
        assert_eq!(
            short,
            Error::SetpointRange {
                field: "scan time (s)",
                value: 0.5,
                min: 1.0,
                max: 60.0
            }
        );
        assert_eq!(short.to_string(), "scan time (s) 0.5 is outside 1 to 60");
        let long = default.with_duration(Duration::from_secs(61)).unwrap_err();
        assert_eq!(
            long,
            Error::SetpointRange {
                field: "scan time (s)",
                value: 61.0,
                min: 1.0,
                max: 60.0
            }
        );
        assert_eq!(long.to_string(), "scan time (s) 61 is outside 1 to 60");
    }

    /// Test: UT-DISC-006
    #[test]
    fn not_found_names_the_four_causes() {
        let causes = "the supply is off or out of range; \
                      another app (WebLink in a browser, ISDT's Polying app) is connected to it; \
                      a USB host is talking to it; \
                      remote control is disabled on the supply";
        assert_eq!(
            not_found(),
            Error::NotFound {
                causes: causes.to_string()
            }
        );
        assert_eq!(
            not_found().to_string(),
            "no supply found: the supply is off or out of range; another app (WebLink in a \
             browser, ISDT's Polying app) is connected to it; a USB host is talking to it; \
             remote control is disabled on the supply"
        );
    }

    /// A `Discovery` whose adapter lookup finds none and counts its calls
    /// in `lookups`. The tests that use it reach no backend: the USB side
    /// is disabled or the identifier has a Bluetooth shape, so no
    /// enumeration runs, and no Bluetooth manager is ever created.
    fn counting(lookups: &Arc<AtomicUsize>) -> Discovery {
        let lookups = Arc::clone(lookups);
        Discovery {
            adapter: Lazy::new(),
            lookup: Box::new(move || {
                lookups.fetch_add(1, Ordering::SeqCst);
                Box::pin(async { None })
            }),
            lock: Arc::new(Mutex::new(())),
        }
    }

    /// A `Discovery` with no Bluetooth adapter, as [`counting`].
    fn no_backend() -> Discovery {
        counting(&Arc::new(AtomicUsize::new(0)))
    }

    /// A supply found over Bluetooth with the capture name and data.
    fn supply(id: &str) -> Found {
        classify::advertisement(id, Some(CAPTURE_NAME), &capture_data(), None).unwrap()
    }

    /// Test: UT-DISC-009
    #[test]
    fn merge_returns_the_other_backend_and_fails_only_when_every_one_failed() {
        let failed = || {
            Err(Error::Transport {
                message: "x".to_string(),
            })
        };
        assert_eq!(
            merge(Some(Ok(vec![supply("a")])), Some(Ok(vec![supply("b")]))),
            Ok(vec![supply("a"), supply("b")])
        );
        assert_eq!(
            merge(Some(failed()), Some(Ok(vec![supply("b")]))),
            Ok(vec![supply("b")])
        );
        assert_eq!(
            merge(Some(Ok(vec![supply("a")])), Some(failed())),
            Ok(vec![supply("a")])
        );
        assert_eq!(merge(None, Some(Ok(vec![]))), Ok(vec![]));
        assert_eq!(merge(None, None), Ok(vec![]));
        assert_eq!(
            merge(Some(failed()), Some(failed())),
            Err(Error::Transport {
                message: "every scan failed: Bluetooth: transport: x; USB: transport: x"
                    .to_string()
            })
        );
        assert!(merge(None, Some(failed())).is_err());
    }

    /// Test: UT-DISC-009
    #[tokio::test]
    async fn scan_without_an_adapter_skips_bluetooth() {
        let log = crate::transport::test_log::install();
        let discovery = no_backend();
        let options = ScanOptions {
            usb: false,
            ..ScanOptions::default()
        };
        assert_eq!(
            discovery.scan(options).await,
            Err(Error::Transport {
                message: "no backend for the enabled transports: Bluetooth".to_string()
            })
        );
        let none = ScanOptions {
            bluetooth: false,
            usb: false,
            ..ScanOptions::default()
        };
        assert_eq!(discovery.scan(none).await, Ok(vec![]));
        let lines = log.lines_here(LOG_TARGET);
        assert!(lines
            .iter()
            .any(|(l, m)| *l == log::Level::Warn && m == "Bluetooth scan skipped: no adapter"));
        assert!(lines
            .iter()
            .any(|(l, m)| *l == log::Level::Info && m == "scan done 0 found"));
    }

    /// Test: UT-DISC-009
    #[tokio::test]
    async fn connect_to_a_bluetooth_identifier_without_an_adapter() {
        let discovery = no_backend();
        let id = "72de66a3-1b2c-4d5e-8f90-abcdef123456";
        assert_eq!(
            discovery.connect(id).await.err(),
            Some(Error::Transport {
                message: format!("no Bluetooth adapter to reach {id}")
            })
        );
    }

    /// Test: UT-DISC-015
    #[tokio::test]
    async fn connect_again_to_a_bluetooth_identifier_without_an_adapter() {
        let discovery = no_backend();
        let id = "72de66a3-1b2c-4d5e-8f90-abcdef123456";
        assert_eq!(
            discovery.connect_again(id).await.err(),
            Some(Error::Transport {
                message: format!("no Bluetooth adapter to reach {id}")
            })
        );
    }

    /// Test: UT-DISC-014
    #[test]
    fn discovery_is_send_and_sync() {
        fn send_sync<T: Send + Sync>() {}
        send_sync::<Discovery>();
    }

    /// Test: UT-DISC-014
    #[tokio::test]
    async fn bluetooth_is_looked_up_only_when_needed_and_again_after_none() {
        let lookups = Arc::new(AtomicUsize::new(0));
        let discovery = counting(&lookups);
        let neither = ScanOptions {
            bluetooth: false,
            usb: false,
            ..ScanOptions::default()
        };
        assert_eq!(discovery.scan(neither).await, Ok(vec![]));
        assert_eq!(lookups.load(Ordering::SeqCst), 0);
        let bluetooth_only = ScanOptions {
            usb: false,
            ..ScanOptions::default()
        };
        assert!(discovery.scan(bluetooth_only).await.is_err());
        assert_eq!(lookups.load(Ordering::SeqCst), 1);
        // "No adapter" is not kept: the next need looks again.
        assert!(discovery.scan(bluetooth_only).await.is_err());
        assert_eq!(lookups.load(Ordering::SeqCst), 2);
        let id = "AA:BB:CC:DD:EE:FF";
        assert!(discovery.connect(id).await.is_err());
        assert!(discovery.connect_again(id).await.is_err());
        assert_eq!(lookups.load(Ordering::SeqCst), 4);
    }

    /// Test: UT-DISC-014
    #[test]
    fn a_connect_needs_bluetooth_only_for_a_bluetooth_identifier() {
        for id in [
            "72de66a3-1b2c-4d5e-8f90-abcdef123456",
            "AA:BB:CC:DD:EE:FF",
            "hci0/dev_AA_BB_CC_DD_EE_FF",
        ] {
            assert!(connect_needs_bluetooth(id), "{id}");
        }
        for id in [
            "/dev/hidraw3",
            "DevSrvsID:4294969336",
            r"\\?\hid#vid_28e9&pid_028a#7&2a3b4c5d&0&0000#{4d1e55b2-f16f-11cf-88cb-001111000030}",
        ] {
            assert!(!connect_needs_bluetooth(id), "{id}");
        }
    }

    /// Test: UT-DISC-014
    #[tokio::test]
    async fn a_found_value_is_kept_and_none_is_looked_up_again() {
        let lookups = AtomicUsize::new(0);
        let slot = Lazy::new();
        let lookup = |answer: Option<u32>| {
            lookups.fetch_add(1, Ordering::SeqCst);
            async move { answer }
        };
        assert_eq!(slot.get(|| lookup(None)).await, None);
        assert_eq!(slot.get(|| lookup(Some(7))).await, Some(7));
        assert_eq!(slot.get(|| lookup(Some(8))).await, Some(7));
        assert_eq!(slot.get(|| lookup(None)).await, Some(7));
        assert_eq!(lookups.load(Ordering::SeqCst), 2);
    }

    /// Test: UT-DISC-014
    #[test]
    fn only_a_switched_off_adapter_stops_bluetooth() {
        assert_eq!(radio_check(Radio::On), Ok(()));
        assert_eq!(radio_check(Radio::Unknown), Ok(()));
        let off = radio_check(Radio::Off).unwrap_err();
        assert_eq!(
            off,
            Error::Transport {
                message: "Bluetooth is switched off on this computer".to_string()
            }
        );
        // In a scan it is a failing backend: the other's results remain.
        let usb = classify::hid(0x28E9, 0x028A, Some("MP305B"), "/dev/hidraw3").unwrap();
        assert_eq!(
            merge(Some(Err(off.clone())), Some(Ok(vec![usb.clone()]))),
            Ok(vec![usb])
        );
        assert_eq!(
            merge(Some(Err(off)), None),
            Err(Error::Transport {
                message: "every scan failed: Bluetooth: transport: Bluetooth is switched off \
                          on this computer"
                    .to_string()
            })
        );
    }
}
