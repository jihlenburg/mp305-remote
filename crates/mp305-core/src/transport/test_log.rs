//! A log collector for tests: one static logger per test binary that keeps
//! every record by target.
//!
//! Implements: nothing; supports UT-TRANS-004 and UT-TRANS-030.

use std::sync::{Mutex, Once, OnceLock};

/// The records collected so far: (target, level, message).
type Records = Mutex<Vec<(String, log::Level, String)>>;

/// The one collector.
struct Collector;

/// Where the collector keeps its records.
static RECORDS: OnceLock<Records> = OnceLock::new();
/// Installs the collector once.
static INSTALL: Once = Once::new();

impl log::Log for Collector {
    fn enabled(&self, _: &log::Metadata<'_>) -> bool {
        true
    }

    fn log(&self, record: &log::Record<'_>) {
        if let Some(records) = RECORDS.get() {
            if let Ok(mut r) = records.lock() {
                r.push((
                    record.target().to_string(),
                    record.level(),
                    record.args().to_string(),
                ));
            }
        }
    }

    fn flush(&self) {}
}

/// A handle to the collected records.
pub struct Log;

impl Log {
    /// The (level, message) pairs logged under `target`, in order.
    pub fn lines(&self, target: &str) -> Vec<(log::Level, String)> {
        RECORDS
            .get()
            .and_then(|r| r.lock().ok())
            .map(|r| {
                r.iter()
                    .filter(|(t, _, _)| t == target)
                    .map(|(_, l, m)| (*l, m.clone()))
                    .collect()
            })
            .unwrap_or_default()
    }
}

/// Installs the collector (once per binary) and returns a handle.
pub fn install() -> Log {
    INSTALL.call_once(|| {
        let _ = RECORDS.set(Mutex::new(Vec::new()));
        let _ = log::set_logger(&Collector);
        log::set_max_level(log::LevelFilter::Trace);
    });
    Log
}
