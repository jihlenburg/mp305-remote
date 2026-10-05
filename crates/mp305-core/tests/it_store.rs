//! Integration test IT-033 (AR-033): `Store` on a temporary directory: the
//! host ID is stable, valid and not WebLink's; a corrupt host ID file is
//! replaced and logged; a marker survives reopening the store and is gone
//! after its removal.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    missing_docs
)]

use std::fs;
use std::sync::{Mutex, OnceLock};
use std::thread::{self, ThreadId};
use std::time::{Duration, UNIX_EPOCH};

use mp305_core::session::Markers;
use mp305_core::store::{Store, LOG_TARGET};

/// WebLink's constant host ID (`00 08*14 00`, protocol DD).
const WEBLINK: [u8; 16] = [0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0];

/// Every record the collector kept: (thread, target, level, message).
type Records = Mutex<Vec<(ThreadId, String, log::Level, String)>>;

/// The records of this test binary.
static RECORDS: OnceLock<Records> = OnceLock::new();

/// A logger that keeps every record, so the test can read the store's.
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

/// Installs the collector, once per binary.
fn collect_logs() {
    if RECORDS.set(Mutex::new(Vec::new())).is_ok() {
        log::set_logger(&COLLECTOR).unwrap();
        log::set_max_level(log::LevelFilter::Trace);
    }
}

/// The store's log lines written on this thread, as (level, message).
fn store_log_here() -> Vec<(log::Level, String)> {
    let here = thread::current().id();
    RECORDS
        .get()
        .unwrap()
        .lock()
        .unwrap()
        .iter()
        .filter(|(id, target, _, _)| *id == here && target == LOG_TARGET)
        .map(|(_, _, level, message)| (*level, message.clone()))
        .collect()
}

/// Test: IT-033
#[test]
fn the_host_id_is_stable_and_a_corrupt_file_is_replaced_and_logged() {
    collect_logs();
    let dir = tempfile::tempdir().unwrap();
    let store = Store::new(dir.path());
    let first = store.host_id().unwrap();
    let second = store.host_id().unwrap();
    assert_eq!(first, second);
    assert_eq!(first.as_bytes().len(), 16);
    assert_ne!(first.as_bytes(), &[0u8; 16]);
    assert_ne!(first.as_bytes(), &WEBLINK);

    // Corrupt the file: a new ID replaces it, and the replacement is logged.
    let file = dir.path().join("host_id");
    fs::write(&file, b"not a host id\n").unwrap();
    let replaced = store.host_id().unwrap();
    assert_ne!(replaced, first);
    assert_ne!(replaced.as_bytes(), &[0u8; 16]);
    assert_ne!(replaced.as_bytes(), &WEBLINK);
    assert_eq!(store.host_id().unwrap(), replaced);
    let hex: String = replaced
        .as_bytes()
        .iter()
        .map(|b| format!("{b:02x}"))
        .collect();
    assert_eq!(fs::read_to_string(&file).unwrap().trim(), hex);
    let lines = store_log_here();
    assert!(
        lines
            .iter()
            .any(|(level, m)| *level == log::Level::Warn && m.starts_with("host id replaced: ")),
        "{lines:?}"
    );
}

/// Test: IT-033
#[test]
fn a_marker_survives_reopening_the_store_and_is_gone_after_removal() {
    let dir = tempfile::tempdir().unwrap();
    let identifier = "72de66a3-1b2c-4d5e-8f90-abcdef123456";
    let at = UNIX_EPOCH + Duration::from_secs(1_790_848_800);
    let store = Store::new(dir.path());
    assert_eq!(store.present(identifier).unwrap(), None);
    store.set(identifier, at).unwrap();
    drop(store);
    let reopened = Store::new(dir.path());
    assert_eq!(reopened.present(identifier).unwrap(), Some(at));
    reopened.clear(identifier).unwrap();
    assert_eq!(reopened.present(identifier).unwrap(), None);
    // The removal is written behind: another store sees it once flushed.
    assert!(reopened.flush(Duration::from_secs(30)));
    assert_eq!(Store::new(dir.path()).present(identifier).unwrap(), None);
}
