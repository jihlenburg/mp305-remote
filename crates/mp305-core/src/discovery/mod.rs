//! Implements: DD-DISC-001, DD-DISC-004, DD-DISC-005, DD-DISC-010,
//! DD-DISC-011, DD-DISC-020.
//!
//! Discovery: finds supplies over Bluetooth LE and USB HID and turns an
//! identifier into a guarded transport for the session (the [`Connector`]
//! implementation).
//!
//! Everything decidable lives in pure functions in [`classify`]: the two
//! classifiers, the sighting accumulator, the name choice, the identifier
//! shape test and the connect plan. The vendor calls live in the two glue
//! files `ble` and `hid`, which only move OS data to and from the pure part
//! and are excluded from the coverage measurement under ADR-0014. This file
//! makes no vendor call of its own and names no vendor type.

mod ble;
pub mod classify;
mod hid;

use core::fmt;
use core::time::Duration;
use std::sync::Arc;

use futures::future::BoxFuture;
use tokio::sync::Mutex;

use crate::discovery::classify::Plan;
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

/// Finds supplies over Bluetooth LE and USB HID, and connects to one by
/// its identifier (the session's [`Connector`]). One per process.
///
/// It holds the first Bluetooth adapter, when the OS has one, and the scan
/// lock that keeps a second scan from ending the first. It is `Send` and
/// `Sync`.
pub struct Discovery {
    /// The first Bluetooth adapter; `None` when there is none.
    adapter: Option<ble::Adapter>,
    /// The scan lock, held from before the Bluetooth scan starts until
    /// after it stops.
    lock: Arc<Mutex<()>>,
}

impl Discovery {
    /// Opens the backends: the first Bluetooth adapter and a probe of the
    /// USB side. A missing backend is logged at WARN.
    ///
    /// # Errors
    ///
    /// [`Error::Transport`] when neither a Bluetooth adapter nor the USB
    /// backend is available.
    pub async fn new() -> Result<Self, Error> {
        let (adapter, usb) = tokio::join!(ble::adapter(), hid::available());
        if adapter.is_none() && !usb {
            return Err(Error::Transport {
                message: "no Bluetooth adapter and no USB HID backend".to_string(),
            });
        }
        Ok(Self {
            adapter,
            lock: Arc::new(Mutex::new(())),
        })
    }

    /// Scans for supplies: over Bluetooth for `options.duration()` when
    /// `options.bluetooth` is set and an adapter exists, and over USB when
    /// `options.usb` is set, both at once. The results are concatenated,
    /// Bluetooth first. A backend that fails is logged at WARN and the
    /// other's results are returned; an enabled transport without a backend
    /// is skipped with a WARN log. An empty list means no supply was found;
    /// the products then show [`not_found`].
    ///
    /// # Errors
    ///
    /// [`Error::Transport`] when every backend that ran failed.
    pub async fn scan(&self, options: ScanOptions) -> Result<Vec<Found>, Error> {
        log::info!(target: LOG_TARGET, "scan start {options:?}");
        let bluetooth = async {
            if !options.bluetooth {
                return None;
            }
            let Some(adapter) = &self.adapter else {
                log::warn!(target: LOG_TARGET, "Bluetooth scan skipped: no adapter");
                return None;
            };
            Some(ble::scan(adapter, Arc::clone(&self.lock), options.duration).await)
        };
        let usb = async {
            if options.usb {
                Some(hid::scan().await)
            } else {
                None
            }
        };
        let (bluetooth, usb) = tokio::join!(bluetooth, usb);
        let found = merge(bluetooth, usb)?;
        for supply in &found {
            log::info!(target: LOG_TARGET, "found {supply}");
        }
        log::info!(target: LOG_TARGET, "scan done {} found", found.len());
        Ok(found)
    }

    /// The connect flow without the outer bound: the ids the adapter holds,
    /// the USB enumeration only for an identifier without a Bluetooth
    /// shape, the plan of [`classify::connect_plan`], then a `find` before
    /// every Bluetooth connect, or the open of the HID path.
    ///
    /// # Errors
    ///
    /// [`not_found`] when the identifier is not found or not seen
    /// advertising within `timing::FIND`; [`Error::Transport`] when the USB
    /// enumeration fails, a Bluetooth identifier has no adapter, or the
    /// backend's connect or open fails.
    async fn reach(&self, identifier: &str) -> Result<Guarded<AnyTransport>, Error> {
        let ble_known = match &self.adapter {
            Some(adapter) => ble::known_ids(adapter).await.unwrap_or_else(|error| {
                log::warn!(target: LOG_TARGET, "the adapter's peripherals could not be listed: {error}");
                Vec::new()
            }),
            None => Vec::new(),
        };
        let usb = if classify::looks_like_ble_id(identifier) {
            Vec::new()
        } else {
            hid::enumerate().await?
        };
        let hid_paths: Vec<String> = usb.iter().map(|(text, ..)| text.clone()).collect();
        let plan = classify::connect_plan(identifier, &ble_known, &hid_paths);
        log::info!(target: LOG_TARGET, "connect {identifier} {plan:?}");
        match plan {
            Plan::BleKnown | Plan::BleFind => {
                let Some(adapter) = &self.adapter else {
                    return Err(Error::Transport {
                        message: format!("no Bluetooth adapter to reach {identifier}"),
                    });
                };
                match ble::find(adapter, Arc::clone(&self.lock), identifier, timing::FIND).await? {
                    Some(id) => ble::connect(adapter, &id).await,
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
            Plan::HidPath => match usb.into_iter().find(|(text, ..)| text == identifier) {
                Some((_, path, ..)) => hid::open(&path).await,
                None => Err(not_found()),
            },
            Plan::NotFound => Err(not_found()),
        }
    }
}

impl Connector for Discovery {
    /// Connects to the supply with `identifier` under the bound
    /// `timing::FIND + timing::CONNECT` as a whole, the wait for the scan
    /// lock included.
    fn connect<'a>(
        &'a self,
        identifier: &'a str,
    ) -> BoxFuture<'a, Result<Guarded<AnyTransport>, Error>> {
        Box::pin(async move {
            let bound = timing::FIND.saturating_add(timing::CONNECT);
            tokio::time::timeout(bound, self.reach(identifier))
                .await
                .unwrap_or_else(|_| {
                    Err(Error::Transport {
                        message: format!(
                            "connect to {identifier} did not complete within {} s",
                            bound.as_secs()
                        ),
                    })
                })
        })
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

    /// A `Discovery` with no Bluetooth adapter. The tests that use it reach
    /// no backend: the USB side is disabled or the identifier has a
    /// Bluetooth shape, so no enumeration runs.
    fn no_backend() -> Discovery {
        Discovery {
            adapter: None,
            lock: Arc::new(Mutex::new(())),
        }
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
        assert_eq!(discovery.scan(options).await, Ok(vec![]));
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
}
