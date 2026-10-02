//! Implements: DD-PY-006
//!
//! The bridge from the `log` crate to Python's `logging`. One `log::Log`
//! is installed per process; it queues every record at or above a gate
//! (default WARN) with the time of the Rust call, and never touches Python.
//! Records reach `logging` only on Python threads: in the pump of a
//! blocking call, or on the delivery thread `mp305-log` that loops
//! `log_wait`. One emitter at a time (the log token) keeps the order.
//!
//! Logger names: the target with `::` replaced by `.`, the prefix
//! `mp305_core` replaced by `mp305.core`, `mp305_py` by `mp305.native`,
//! and any other target prefixed with `mp305.deps.`. Levels: TRACE 5,
//! DEBUG 10, INFO 20, WARN 30, ERROR 40.

use core::time::Duration;
use std::collections::VecDeque;
use std::sync::atomic::{AtomicBool, AtomicU64, AtomicUsize, Ordering};
use std::sync::{Mutex, Once};
use std::time::SystemTime;

use log::{Level, LevelFilter, Log, Metadata};
use pyo3::exceptions::PyException;
use pyo3::prelude::*;
use pyo3::sync::PyOnceLock;
use pyo3::types::{PyModule, PyTuple};

use crate::convert;
use crate::feed::lock;
use crate::runtime;
use crate::wait;

/// The records the queue holds; the oldest is dropped when full.
pub const CAPACITY: usize = 4096;

/// One queued record.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Record {
    /// The level.
    pub level: Level,
    /// The `log` target.
    pub target: String,
    /// The formatted message.
    pub message: String,
    /// The time of the Rust call.
    pub time: SystemTime,
}

/// The queue of records not yet delivered, with the count of dropped ones.
#[derive(Debug)]
pub struct Queue {
    /// The records, oldest first.
    records: VecDeque<Record>,
    /// Records dropped: pushed out when full, or swallowed by `logging`.
    dropped: u64,
}

impl Queue {
    /// An empty queue.
    #[must_use]
    pub const fn new() -> Self {
        Queue {
            records: VecDeque::new(),
            dropped: 0,
        }
    }

    /// Appends `record`, dropping (and counting) the oldest when full.
    pub fn push(&mut self, record: Record) {
        self.records.push_back(record);
        self.trim();
    }

    /// Drops the oldest records beyond [`CAPACITY`] and counts them.
    fn trim(&mut self) {
        while self.records.len() > CAPACITY {
            self.records.pop_front();
            self.dropped = self.dropped.saturating_add(1);
        }
    }
}

impl Default for Queue {
    fn default() -> Self {
        Queue::new()
    }
}

/// The process-wide queue.
static QUEUE: Mutex<Queue> = Mutex::new(Queue::new());
/// The gate as a `LevelFilter` discriminant; records above it are not
/// queued.
static GATE: AtomicUsize = AtomicUsize::new(LevelFilter::Warn as usize);
/// Notified on every push.
static ARRIVED: tokio::sync::Notify = tokio::sync::Notify::const_new();
/// The log token: held by the one thread that emits.
static TOKEN: AtomicBool = AtomicBool::new(false);
/// The dropped count already reported.
static REPORTED: AtomicU64 = AtomicU64::new(0);
/// Installs the logger once per process.
static INSTALL: Once = Once::new();
/// `logging`, imported once per process.
static LOGGING: PyOnceLock<Py<PyModule>> = PyOnceLock::new();

/// The logger of the crate.
#[derive(Debug)]
struct Bridge;

/// The one instance.
static BRIDGE: Bridge = Bridge;

impl Log for Bridge {
    fn enabled(&self, metadata: &Metadata<'_>) -> bool {
        metadata.level() as usize <= GATE.load(Ordering::Relaxed)
    }

    fn log(&self, record: &log::Record<'_>) {
        if !self.enabled(record.metadata()) {
            return;
        }
        let record = Record {
            level: record.level(),
            target: record.target().to_string(),
            message: record.args().to_string(),
            time: SystemTime::now(),
        };
        lock(&QUEUE).push(record);
        ARRIVED.notify_waiters();
    }

    fn flush(&self) {}
}

/// Installs the bridge as the process's logger, once. A `SetLoggerError`
/// (another logger, or this one from an earlier initialisation of the
/// module) is ignored.
pub fn install() {
    INSTALL.call_once(|| {
        if log::set_logger(&BRIDGE).is_ok() {
            log::set_max_level(LevelFilter::Trace);
        }
    });
}

/// The `log` level a Python level gates at: TRACE for 5 and below, DEBUG
/// for 6 to 10, INFO for 11 to 20 and WARN above 20, so WARN and ERROR
/// always pass.
#[must_use]
pub fn gate_for(level: i64) -> LevelFilter {
    if level <= 5 {
        LevelFilter::Trace
    } else if level <= 10 {
        LevelFilter::Debug
    } else if level <= 20 {
        LevelFilter::Info
    } else {
        LevelFilter::Warn
    }
}

/// The Python level of a `log` level.
#[must_use]
pub fn python_level(level: Level) -> i32 {
    match level {
        Level::Trace => 5,
        Level::Debug => 10,
        Level::Info => 20,
        Level::Warn => 30,
        Level::Error => 40,
    }
}

/// The `log` level of a Python level, for `log_test`: TRACE for 5 and
/// below, then DEBUG, INFO, WARN up to 10, 20, 30, and ERROR above.
fn level_of(level: i64) -> Level {
    if level <= 5 {
        Level::Trace
    } else if level <= 10 {
        Level::Debug
    } else if level <= 20 {
        Level::Info
    } else if level <= 30 {
        Level::Warn
    } else {
        Level::Error
    }
}

/// The Python logger name of a `log` target.
#[must_use]
pub fn logger_name(target: &str) -> String {
    let dotted = target.replace("::", ".");
    for (prefix, name) in [("mp305_core", "mp305.core"), ("mp305_py", "mp305.native")] {
        if dotted == prefix {
            return name.to_string();
        }
        if let Some(rest) = dotted.strip_prefix(prefix) {
            if rest.starts_with('.') {
                return format!("{name}{rest}");
            }
        }
    }
    format!("mp305.deps.{dotted}")
}

/// How emitting one record ended, other than `Ok`.
#[derive(Debug)]
pub enum Emit<E> {
    /// `logging` raised an `Exception`: the record counts as dropped and
    /// delivery goes on.
    Swallowed,
    /// Any other `BaseException`: delivery stops and the error propagates.
    Abort(E),
}

/// Delivers the records of `queue` through `emit`: at most two times it
/// swaps the queue out under its lock and, with no lock held, emits each
/// record. A swallowed record counts as dropped. On an abort, the record
/// that raised counts as emitted, the records not yet emitted go back to
/// the front of the queue in their order, and the error is returned.
///
/// # Errors
///
/// The error of an [`Emit::Abort`].
pub fn deliver_from<E>(
    queue: &Mutex<Queue>,
    mut emit: impl FnMut(&Record) -> Result<(), Emit<E>>,
) -> Result<(), E> {
    for _ in 0..2 {
        let batch = core::mem::take(&mut lock(queue).records);
        if batch.is_empty() {
            break;
        }
        let mut rest = batch.into_iter();
        while let Some(record) = rest.next() {
            match emit(&record) {
                Ok(()) => {}
                Err(Emit::Swallowed) => {
                    let mut q = lock(queue);
                    q.dropped = q.dropped.saturating_add(1);
                }
                Err(Emit::Abort(error)) => {
                    let mut q = lock(queue);
                    for record in rest.rev() {
                        q.records.push_front(record);
                    }
                    q.trim();
                    return Err(error);
                }
            }
        }
    }
    Ok(())
}

/// Releases the log token when dropped.
struct TokenGuard;

impl Drop for TokenGuard {
    fn drop(&mut self) {
        TOKEN.store(false, Ordering::Release);
    }
}

/// Takes the log token, or `None` when another thread emits.
fn take_token() -> Option<TokenGuard> {
    TOKEN
        .compare_exchange(false, true, Ordering::AcqRel, Ordering::Acquire)
        .ok()
        .map(|_| TokenGuard)
}

/// Emits one record through `logging`: `getLogger(name)`, and when
/// `isEnabledFor(level)`, `makeRecord` with `created` and `msecs` set from
/// the record's time, then `handle`.
fn emit_one(
    py: Python<'_>,
    logging: &Bound<'_, PyModule>,
    name: &str,
    level: i32,
    message: &str,
    time: SystemTime,
) -> PyResult<()> {
    let logger = logging.call_method1("getLogger", (name,))?;
    if !logger.call_method1("isEnabledFor", (level,))?.is_truthy()? {
        return Ok(());
    }
    let record = logger.call_method1(
        "makeRecord",
        (name, level, "", 0, message, PyTuple::empty(py), py.None()),
    )?;
    let ns = convert::wall_ns(time);
    let millis = u32::try_from(ns.rem_euclid(1_000_000_000) / 1_000_000).unwrap_or(0);
    record.setattr("created", convert::wall_seconds(time))?;
    record.setattr("msecs", f64::from(millis))?;
    logger.call_method1("handle", (record,))?;
    Ok(())
}

/// Sorts an error of `logging` into swallowed (`Exception`) or abort.
fn classify(py: Python<'_>, error: PyErr) -> Emit<PyErr> {
    if error.is_instance_of::<PyException>(py) {
        Emit::Swallowed
    } else {
        Emit::Abort(error)
    }
}

/// Delivers the queued records to `logging` on the calling thread, unless
/// another thread holds the log token. A dropped count that rose since the
/// last report is emitted once at WARNING on `mp305.native`.
///
/// # Errors
///
/// A `BaseException` that is not an `Exception`, raised by a handler.
pub fn deliver(py: Python<'_>) -> PyResult<()> {
    let Some(_token) = take_token() else {
        return Ok(());
    };
    let (empty, dropped) = {
        let q = lock(&QUEUE);
        (q.records.is_empty(), q.dropped)
    };
    if empty && dropped <= REPORTED.load(Ordering::Acquire) {
        return Ok(());
    }
    let logging = LOGGING
        .get_or_try_init(py, || py.import("logging").map(Bound::unbind))?
        .bind(py)
        .clone();
    deliver_from(&QUEUE, |r| {
        emit_one(
            py,
            &logging,
            &logger_name(&r.target),
            python_level(r.level),
            &r.message,
            r.time,
        )
        .map_err(|e| classify(py, e))
    })?;
    let dropped = lock(&QUEUE).dropped;
    let reported = REPORTED.swap(dropped, Ordering::AcqRel);
    if dropped > reported {
        let text = format!(
            "{} log records were dropped",
            dropped.saturating_sub(reported)
        );
        let outcome = emit_one(
            py,
            &logging,
            "mp305.native",
            python_level(Level::Warn),
            &text,
            SystemTime::now(),
        );
        if let Err(error) = outcome {
            if let Emit::Abort(error) = classify(py, error) {
                return Err(error);
            }
        }
    }
    Ok(())
}

/// Waits until the queue is not empty or `wait` passed.
pub async fn wait_for_records(wait: Duration) {
    let arrived = ARRIVED.notified();
    tokio::pin!(arrived);
    arrived.as_mut().enable();
    if !lock(&QUEUE).records.is_empty() {
        return;
    }
    let _ = tokio::time::timeout(wait, arrived).await;
}

/// `set_gate(level)`: sets the gate for the Python `level` ([`gate_for`]).
#[pyfunction]
pub fn set_gate(level: i64) {
    GATE.store(gate_for(level) as usize, Ordering::Relaxed);
}

/// `log_wait(wait_s)`: a blocking call without feed or dispatcher that
/// waits until a record is queued or `wait_s` (0 to 60 s) passed, then
/// delivers.
///
/// # Errors
///
/// `ValueError` for a `wait_s` outside 0 to 60 s, and the errors of a
/// blocking call.
#[pyfunction]
pub fn log_wait(py: Python<'_>, wait_s: f64) -> PyResult<()> {
    let _rt = runtime::enter()?;
    let wait = convert::seconds_arg("wait_s", wait_s)?;
    wait::block(py, None, async move {
        wait_for_records(wait).await;
        Ok(())
    })
}

/// `log_test(target, level, message, count)`: test support that logs
/// `count` records through `log::log!` with the GIL held, so that no
/// delivery runs in between.
#[pyfunction]
pub fn log_test(target: &str, level: i64, message: &str, count: u64) {
    let level = level_of(level);
    for _ in 0..count {
        log::log!(target: target, level, "{message}");
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// A record with `message`.
    fn record(message: &str) -> Record {
        Record {
            level: Level::Warn,
            target: "t".to_string(),
            message: message.to_string(),
            time: SystemTime::UNIX_EPOCH,
        }
    }

    /// Test: UT-PY-002
    #[test]
    fn levels_names_and_gates() {
        let levels: Vec<i32> = [
            Level::Trace,
            Level::Debug,
            Level::Info,
            Level::Warn,
            Level::Error,
        ]
        .into_iter()
        .map(python_level)
        .collect();
        assert_eq!(levels, [5, 10, 20, 30, 40]);
        assert_eq!(logger_name("mp305_core::frames"), "mp305.core.frames");
        assert_eq!(logger_name("mp305_core::session"), "mp305.core.session");
        assert_eq!(logger_name("mp305_py::safety"), "mp305.native.safety");
        assert_eq!(
            logger_name("btleplug::corebluetooth::adapter"),
            "mp305.deps.btleplug.corebluetooth.adapter"
        );
        let gates: Vec<LevelFilter> = [0, 5, 10, 15, 20, 30, 40, 50]
            .into_iter()
            .map(gate_for)
            .collect();
        assert_eq!(
            gates,
            [
                LevelFilter::Trace,
                LevelFilter::Trace,
                LevelFilter::Debug,
                LevelFilter::Info,
                LevelFilter::Info,
                LevelFilter::Warn,
                LevelFilter::Warn,
                LevelFilter::Warn,
            ]
        );
    }

    /// Test: UT-PY-002
    #[test]
    fn the_queue_keeps_4096_and_counts_the_dropped() {
        let mut queue = Queue::new();
        for n in 0..=4096 {
            queue.push(record(&n.to_string()));
        }
        assert_eq!(queue.records.len(), 4096);
        assert_eq!(queue.records.front().map(|r| r.message.as_str()), Some("1"));
        assert_eq!(queue.dropped, 1);
    }

    /// Test: UT-PY-002
    #[test]
    fn install_twice_installs_one_logger() {
        install();
        install();
        let installed: *const dyn Log = log::logger();
        assert!(core::ptr::addr_eq(installed, &raw const BRIDGE));
    }

    /// Test: UT-PY-002
    #[test]
    fn deliver_from_swallows_and_aborts() {
        let queue = Mutex::new(Queue::new());
        for n in 1..=5 {
            lock(&queue).push(record(&n.to_string()));
        }
        let mut seen = Vec::new();
        let outcome = deliver_from(&queue, |r| {
            seen.push(r.message.clone());
            match r.message.as_str() {
                "1" => Ok(()),
                "2" => Err(Emit::Swallowed),
                _ => Err(Emit::Abort("abort")),
            }
        });
        assert_eq!(outcome, Err("abort"));
        assert_eq!(seen, ["1", "2", "3"]);
        let q = lock(&queue);
        assert_eq!(q.dropped, 1);
        let left: Vec<&str> = q.records.iter().map(|r| r.message.as_str()).collect();
        assert_eq!(left, ["4", "5"]);
    }

    /// Test: UT-PY-002 (the level of `log_test`)
    #[test]
    fn level_of_python_levels() {
        let levels: Vec<Level> = [5, 10, 20, 30, 40].into_iter().map(level_of).collect();
        assert_eq!(
            levels,
            [
                Level::Trace,
                Level::Debug,
                Level::Info,
                Level::Warn,
                Level::Error
            ]
        );
    }
}
