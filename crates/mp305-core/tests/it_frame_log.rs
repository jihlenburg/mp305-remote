//! Integration test IT-018 (AR-018): with TRACE logging on, a connect
//! through `Guarded<Mock>` writes every frame to the frame log once, with
//! its direction, its time since the guard was created, its route and its
//! bytes in hex.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    missing_docs
)]

mod common;

use std::sync::{Mutex, OnceLock};
use std::thread::{self, ThreadId};

use core::time::Duration;

use mp305_core::protocol::ble::{BleRoute, Route};
use mp305_core::protocol::fixtures::reply_route;
use mp305_core::transport::description::Kind;
use mp305_core::transport::guarded::LOG_TARGET;

use common::{ms, script, start, C3_CAPTURE, E1_BLE, E1_USB};

/// Every record the collector kept: (thread, target, level, message).
type Records = Mutex<Vec<(ThreadId, String, log::Level, String)>>;

/// The records of this test binary.
static RECORDS: OnceLock<Records> = OnceLock::new();

/// A logger that keeps every record, so the test can read the frame log.
struct Collector;

impl log::Log for Collector {
    fn enabled(&self, _: &log::Metadata<'_>) -> bool {
        true
    }

    fn log(&self, record: &log::Record<'_>) {
        if let Some(records) = RECORDS.get() {
            records.lock().unwrap().push((
                thread::current().id(),
                record.target().to_string(),
                record.level(),
                record.args().to_string(),
            ));
        }
    }

    fn flush(&self) {}
}

/// The one collector.
static COLLECTOR: Collector = Collector;

/// Enables TRACE logging into the collector, once per binary.
fn enable_trace() {
    if RECORDS.set(Mutex::new(Vec::new())).is_ok() {
        log::set_logger(&COLLECTOR).unwrap();
        log::set_max_level(log::LevelFilter::Trace);
    }
}

/// The frame-log lines this thread wrote at TRACE. A `#[tokio::test]` runs
/// its runtime and its tasks on its own thread, which keeps the tests of
/// this binary apart.
fn frame_log_here() -> Vec<String> {
    let here = thread::current().id();
    RECORDS
        .get()
        .unwrap()
        .lock()
        .unwrap()
        .iter()
        .filter(|(id, target, level, _)| {
            *id == here && target == LOG_TARGET && *level == log::Level::Trace
        })
        .map(|(_, _, _, message)| message.clone())
        .collect()
}

/// The name of a route in the frame log.
fn route_name(route: Route) -> &'static str {
    match route {
        Route::Ble(BleRoute::Af01) => "ble AF01",
        Route::Ble(BleRoute::Af02) => "ble AF02",
        Route::Hid => "hid",
    }
}

/// An opcode and its payload in lower-case hex, separated by spaces.
fn hex(opcode: u8, payload: &[u8]) -> String {
    let mut out = format!("{opcode:02x}");
    for byte in payload {
        out.push_str(&format!(" {byte:02x}"));
    }
    out
}

/// Runs a connect on a mock of `kind` and checks the frame log of the
/// frames up to the first reading.
async fn connect_and_check(id: &str, kind: Kind) {
    enable_trace();
    let rig = start(id, kind, script(kind, vec![]));
    rig.session.ready().await.unwrap();
    let ready = rig.now();
    tokio::time::sleep(ms(1)).await;
    // The mock wraps every connection in a guard created at the `connect`
    // call, so the log's offsets count from `rig.start`.
    let lines: Vec<String> = frame_log_here()
        .into_iter()
        .filter(|l| l.starts_with("tx ") || l.starts_with("rx "))
        .collect();
    let at_most = |line: &String, limit: Duration| {
        let offset: u64 = line
            .split(' ')
            .find_map(|w| w.strip_prefix('+'))
            .unwrap()
            .parse()
            .unwrap();
        ms(offset) <= limit
    };
    let lines: Vec<String> = lines.into_iter().filter(|l| at_most(l, ready)).collect();

    // What went out: every frame the mock was sent up to the first reading.
    let mut expected: Vec<String> = Vec::new();
    for sent in rig.mock(0).sent() {
        let offset = sent.at - rig.start;
        if offset <= ready {
            expected.push(format!(
                "tx {} +{} {}",
                route_name(sent.route),
                offset.as_millis(),
                hex(sent.frame.opcode(), sent.frame.payload())
            ));
        }
    }
    // What came in: the script's replies, at their arrival times.
    let e1: &[u8] = match kind {
        Kind::Ble => &E1_BLE,
        Kind::Hid => &E1_USB,
    };
    let mut replies: Vec<(u8, &[u8], Duration)> = Vec::new();
    match kind {
        Kind::Ble => {
            replies.push((0x19, &[0x00], ms(50)));
            replies.push((0xE1, e1, ms(150)));
        }
        Kind::Hid => replies.push((0xE1, e1, ms(100))),
    }
    replies.push((0xC3, &C3_CAPTURE, ready));
    for (opcode, payload, at) in replies {
        expected.push(format!(
            "rx {} +{} {}",
            route_name(reply_route(kind, opcode)),
            at.as_millis(),
            hex(opcode, payload)
        ));
    }
    // Each expected line appears exactly once, and the log holds no other
    // frame line in that time.
    for line in &expected {
        let count = lines.iter().filter(|l| *l == line).count();
        assert_eq!(count, 1, "{line} appears {count} times in {lines:#?}");
    }
    assert_eq!(lines.len(), expected.len(), "{lines:#?}");
}

/// Test: IT-018
#[tokio::test(start_paused = true)]
async fn a_bluetooth_connect_logs_every_frame_once() {
    connect_and_check("IT-018-ble", Kind::Ble).await;
}

/// Test: IT-018
#[tokio::test(start_paused = true)]
async fn a_usb_connect_logs_every_frame_once() {
    connect_and_check("IT-018-usb", Kind::Hid).await;
}
