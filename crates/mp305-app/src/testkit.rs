//! Implements: nothing; the shared fixtures of the unit tests (app DD,
//! section 9), compiled under `cfg(test)` only.
//!
//! `t0` is one fixed instant for the whole test binary; times in the test
//! entries are offsets from it. `r(output, model, faults, set_v, set_a,
//! at)` is a reading with that `at`, `wall` 2026-10-01T10:00:00Z plus `at`
//! minus `t0`, and the reading of `c3_with(output, model, faults, set_v,
//! set_a)` through `telemetry::parse_payload` and `Reading::from_raw`.

use core::time::Duration;
use std::path::PathBuf;
use std::sync::OnceLock;
use std::time::{SystemTime, UNIX_EPOCH};

use mp305_core::protocol::ble::{self, BleRoute};
use mp305_core::protocol::fixtures;
use mp305_core::protocol::ops::{info as info_op, settings as settings_op, telemetry};
use tokio::time::Instant;

use crate::actions::{handle, Clock, IdSource, UiAction};
use crate::model::{Found, Info, Kind, Model, Reading, Settings, TimedReading};
use crate::worker::{AppEvent, UiReading, What};

/// The records the test logger kept: (thread, level, message), for the
/// app's own targets at INFO and above.
static LOG_RECORDS: std::sync::Mutex<Vec<(std::thread::ThreadId, log::Level, String)>> =
    std::sync::Mutex::new(Vec::new());

/// The test logger: keeps the app's records by thread, so that a test reads
/// the lines its own thread (and the runtime on it) wrote.
struct Collector;

impl log::Log for Collector {
    fn enabled(&self, metadata: &log::Metadata<'_>) -> bool {
        metadata.target().starts_with("mp305_app")
    }

    fn log(&self, record: &log::Record<'_>) {
        if self.enabled(record.metadata()) {
            if let Ok(mut records) = LOG_RECORDS.lock() {
                records.push((
                    std::thread::current().id(),
                    record.level(),
                    record.args().to_string(),
                ));
            }
        }
    }

    fn flush(&self) {}
}

/// Installs the test logger once per test binary.
pub(crate) fn capture_log() {
    /// The one logger.
    static COLLECTOR: Collector = Collector;
    /// Installs it once.
    static INSTALL: std::sync::Once = std::sync::Once::new();
    INSTALL.call_once(|| {
        let _ = log::set_logger(&COLLECTOR);
        log::set_max_level(log::LevelFilter::Info);
    });
}

/// The app's log lines at `level` this thread wrote so far.
pub(crate) fn logged_here(level: log::Level) -> Vec<String> {
    let here = std::thread::current().id();
    LOG_RECORDS
        .lock()
        .unwrap()
        .iter()
        .filter(|(thread, l, _)| *thread == here && *l == level)
        .map(|(_, _, text)| text.clone())
        .collect()
}

/// The fixed instant the test times count from.
pub(crate) fn t0() -> Instant {
    /// The instant, taken once.
    static T0: OnceLock<Instant> = OnceLock::new();
    *T0.get_or_init(Instant::now)
}

/// 2026-10-01T10:00:00Z.
pub(crate) fn wall0() -> SystemTime {
    UNIX_EPOCH + Duration::from_secs(1_790_848_800)
}

/// `at` plus `d`, through `checked_add` (DD-APP-050 keeps operators off
/// `Instant` in the whole crate, tests included).
pub(crate) fn after(at: Instant, d: Duration) -> Instant {
    at.checked_add(d).unwrap()
}

/// `t0` plus `ms` milliseconds.
pub(crate) fn at_ms(ms: u64) -> Instant {
    after(t0(), Duration::from_millis(ms))
}

/// `t0` plus `s` seconds, to the millisecond.
pub(crate) fn at_s(s: f64) -> Instant {
    at_ms((s * 1000.0).round() as u64)
}

/// The clocks at `s` seconds after `t0`.
pub(crate) fn clock_s(s: f64) -> Clock {
    let now = at_s(s);
    Clock {
        now,
        wall: wall0()
            .checked_add(now.saturating_duration_since(t0()))
            .unwrap(),
    }
}

/// The reading of `c3_with(output, model, faults, set_v, set_a)` at `at`.
pub(crate) fn r(
    output: u8,
    model: u8,
    faults: u16,
    set_v: u16,
    set_a: u16,
    at: Instant,
) -> TimedReading {
    let payload = fixtures::c3_with(output, model, faults, set_v, set_a);
    let raw = telemetry::parse_payload(&payload).unwrap();
    TimedReading {
        at,
        wall: wall0()
            .checked_add(at.saturating_duration_since(t0()))
            .unwrap(),
        reading: Reading::from_raw(&raw),
    }
}

/// The capture reading with `wall`, its `at` the same offset from `t0`.
pub(crate) fn r_wall(wall: SystemTime) -> TimedReading {
    let offset = wall.duration_since(wall0()).unwrap();
    r(0, 0, 0, 1300, 1000, after(t0(), offset))
}

/// `A`: Bluetooth, identifier `A`, name `MP305B`, unit `ABC`.
pub(crate) fn found_a() -> Found {
    Found {
        transport: Kind::Ble,
        identifier: "A".into(),
        unit_id: "ABC".into(),
        name: "MP305B".into(),
        rssi: Some(-60),
        remote_flag: Some(true),
    }
}

/// `B`: USB, identifier `B`.
pub(crate) fn found_b() -> Found {
    Found {
        transport: Kind::Hid,
        identifier: "B".into(),
        unit_id: "B".into(),
        name: "MP305B".into(),
        rssi: None,
        remote_flag: None,
    }
}

/// `E1_BLE` parsed.
pub(crate) fn info() -> Info {
    let wire = fixtures::on_air(Kind::Ble, info_op::REPLY, &fixtures::E1_BLE);
    info_op::parse(&ble::decode(&wire, BleRoute::Af01).unwrap()).unwrap()
}

/// `C5_SETTINGS` parsed.
pub(crate) fn settings() -> Settings {
    let wire = fixtures::on_air(Kind::Ble, settings_op::REPLY, &fixtures::C5_SETTINGS);
    settings_op::parse(&ble::decode(&wire, BleRoute::Af01).unwrap()).unwrap()
}

/// "The connected model": after `Select("A")`, `Connect` (id 1),
/// `Connecting { 1, "A" }`, `Done { 1, Connect, Ok }`, `UiReading { 1,
/// r(0, 0, 0, 1300, 1000, 0 s) }` and `Ready { 1, info, Some(that
/// reading), Some(Ble) }`, with no limits and remote `None`.
pub(crate) fn connected_model() -> Model {
    let mut m = Model::new(PathBuf::from("/rec"), t0());
    m.found = vec![found_a(), found_b()];
    let mut ids = IdSource::new();
    let c = clock_s(0.0);
    handle(&mut m, UiAction::Select("A".into()), c, &mut ids);
    let sent = handle(&mut m, UiAction::Connect, c, &mut ids);
    assert_eq!(sent.len(), 1);
    m.apply(
        AppEvent::Connecting {
            sid: 1,
            identifier: "A".into(),
        },
        at_s(0.0),
    );
    m.apply(
        AppEvent::Done {
            id: 1,
            what: What::Connect,
            result: Ok(()),
        },
        at_s(0.0),
    );
    let first = r(0, 0, 0, 1300, 1000, at_s(0.0));
    m.apply(
        UiReading {
            sid: 1,
            reading: first,
        },
        at_s(0.0),
    );
    m.apply(
        AppEvent::Ready {
            sid: 1,
            info: info(),
            reading: Some(first),
            transport: Some(Kind::Ble),
        },
        at_s(0.0),
    );
    m
}
