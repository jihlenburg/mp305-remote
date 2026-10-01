//! A log collector for tests: one static logger per test binary that keeps
//! every record by target.
//!
//! Implements: nothing; supports UT-TRANS-004, UT-TRANS-030 and the task
//! tests of `link` (UT-LINK-008 to 027).

use std::sync::{Mutex, Once, OnceLock};
use std::thread::{self, ThreadId};

/// The records collected so far: (thread, target, level, message).
type Records = Mutex<Vec<(ThreadId, String, log::Level, String)>>;

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
                    thread::current().id(),
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
                    .filter(|(_, t, _, _)| t == target)
                    .map(|(_, _, l, m)| (*l, m.clone()))
                    .collect()
            })
            .unwrap_or_default()
    }

    /// The (level, message) pairs logged under `target` on the calling
    /// thread, in order. A `#[tokio::test]` runs its runtime and every task
    /// it spawns on its own thread, so this isolates one test's lines from
    /// the tests running in parallel.
    pub fn lines_here(&self, target: &str) -> Vec<(log::Level, String)> {
        let here = thread::current().id();
        RECORDS
            .get()
            .and_then(|r| r.lock().ok())
            .map(|r| {
                r.iter()
                    .filter(|(id, t, _, _)| *id == here && t == target)
                    .map(|(_, _, l, m)| (*l, m.clone()))
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
