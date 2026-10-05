//! Implements: DD-STORE-004 (the write-behind of `set` and `clear`).
//!
//! The marker writes of a [`Store`](super::Store) leave the caller's thread:
//! the session rewrites a marker about once per second on the task that
//! also serves Output OFF and close, and a write ends with a `sync_all`,
//! which a slow or stalled disk can hold up for seconds. `set` and `clear`
//! therefore record the operation here and return at once; one writer
//! thread per store applies the operations in order. For one identifier
//! only the latest pending operation matters, so a newer one replaces an
//! older one that has not started yet. `present` answers from a pending or
//! running operation of its identifier before it reads the disk, so a read
//! observes every earlier `set` and `clear` of the same store.
//!
//! [`Behind::flush`] waits, bounded, until everything is on disk. Dropping
//! the last clone of the store drains the queue and joins the thread,
//! bounded by [`DROP_BOUND`]; after that the thread is left to finish on
//! its own, so a stalled disk never blocks the drop for longer.

use std::collections::VecDeque;
use std::path::PathBuf;
use std::sync::{Arc, Condvar, Mutex, MutexGuard, PoisonError};
use std::thread::{self, JoinHandle};
use std::time::{Duration, Instant, SystemTime, UNIX_EPOCH};

use crate::error::{duration_text, Error};

use super::LOG_TARGET;

/// How long dropping the last clone of a store waits for its pending
/// marker writes before it leaves the writer thread to finish alone. The
/// same as `protocol::timing::CLOSE`, the bound of the session's own wait
/// at a close.
pub(crate) const DROP_BOUND: Duration = Duration::from_secs(5);

/// The name of the writer thread, for debuggers and panic messages.
const THREAD_NAME: &str = "mp305-markers";

/// A marker operation.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub(crate) enum Op {
    /// Write the marker with this time.
    Set(SystemTime),
    /// Remove the marker.
    Clear,
}

impl Op {
    /// What `present` gives while this operation is pending or running:
    /// the time in whole seconds (a time before the epoch as the epoch), as
    /// the file will give it back, or `None` for a clear.
    pub(crate) fn present(self) -> Option<SystemTime> {
        match self {
            Op::Set(at) => {
                let seconds = at.duration_since(UNIX_EPOCH).map_or(0, |d| d.as_secs());
                UNIX_EPOCH.checked_add(Duration::from_secs(seconds))
            }
            Op::Clear => None,
        }
    }

    /// The word of the WARN line for a failed write: `set` or `clear`, as
    /// the session's synchronous path logged it.
    fn word(self) -> &'static str {
        match self {
            Op::Set(_) => "set",
            Op::Clear => "clear",
        }
    }
}

/// How the writer thread applies one operation: `(dir, identifier, op)`.
pub(crate) type Apply = fn(&std::path::Path, &str, Op) -> Result<(), Error>;

/// What the store and its writer thread share.
#[derive(Debug, Default)]
struct Queue {
    /// The operations and the thread's progress.
    state: Mutex<State>,
    /// Signalled when an operation is queued, when one finished, and at
    /// the stop.
    changed: Condvar,
}

/// The queue's state.
#[derive(Debug, Default)]
struct State {
    /// Operations not started yet, oldest first, at most one per
    /// identifier.
    pending: VecDeque<(String, Op)>,
    /// The operation the thread applies right now.
    running: Option<(String, Op)>,
    /// The store was dropped: the thread ends once `pending` is empty.
    stop: bool,
}

impl State {
    /// Whether every queued operation has been applied.
    fn idle(&self) -> bool {
        self.pending.is_empty() && self.running.is_none()
    }
}

/// The write-behind of one store and its clones.
#[derive(Debug)]
pub(crate) struct Behind {
    /// The store directory.
    dir: PathBuf,
    /// How an operation is applied; a seam for the tests.
    apply: Apply,
    /// Shared with the writer thread.
    queue: Arc<Queue>,
    /// The writer thread, started with the first operation.
    thread: Mutex<Option<JoinHandle<()>>>,
    /// How long the drop waits: [`DROP_BOUND`], shorter in tests.
    drop_bound: Duration,
}

/// Locks `mutex`, ignoring poisoning: the state stays consistent because
/// every critical section only moves whole values.
fn lock<T>(mutex: &Mutex<T>) -> MutexGuard<'_, T> {
    mutex.lock().unwrap_or_else(PoisonError::into_inner)
}

impl Behind {
    /// The write-behind for the store in `dir`, applying operations with
    /// `apply`. Starts no thread yet.
    pub(crate) fn new(dir: PathBuf, apply: Apply) -> Self {
        Self {
            dir,
            apply,
            queue: Arc::new(Queue::default()),
            thread: Mutex::new(None),
            drop_bound: DROP_BOUND,
        }
    }

    /// Queues `op` for `identifier`, replacing a pending operation of the
    /// same identifier, and starts the writer thread if it is not running.
    /// When the OS refuses a thread, `op` is applied here instead and its
    /// result returned, so that a marker is never lost silently.
    ///
    /// # Errors
    ///
    /// Only on that fallback: the error of the write.
    pub(crate) fn submit(&self, identifier: &str, op: Op) -> Result<(), Error> {
        let mut thread = lock(&self.thread);
        if thread.is_none() {
            let queue = Arc::clone(&self.queue);
            let dir = self.dir.clone();
            let apply = self.apply;
            match thread::Builder::new()
                .name(THREAD_NAME.to_string())
                .spawn(move || run(&queue, &dir, apply))
            {
                Ok(handle) => *thread = Some(handle),
                Err(error) => {
                    drop(thread);
                    log::warn!(target: LOG_TARGET, "marker writer not started: {error}");
                    return (self.apply)(&self.dir, identifier, op);
                }
            }
        }
        drop(thread);
        let mut state = lock(&self.queue.state);
        state.pending.retain(|(id, _)| id != identifier);
        state.pending.push_back((identifier.to_string(), op));
        drop(state);
        self.queue.changed.notify_all();
        Ok(())
    }

    /// The latest operation for `identifier` that is pending or running,
    /// if any: a read answers from it, since the disk does not show it yet.
    pub(crate) fn latest(&self, identifier: &str) -> Option<Op> {
        let state = lock(&self.queue.state);
        state
            .pending
            .iter()
            .rev()
            .find(|(id, _)| id == identifier)
            .or(state.running.as_ref().filter(|(id, _)| id == identifier))
            .map(|(_, op)| *op)
    }

    /// Waits up to `bound` until every operation queued so far has been
    /// applied; `true` when it has, `false` when `bound` expired first.
    pub(crate) fn flush(&self, bound: Duration) -> bool {
        let start = Instant::now();
        let mut state = lock(&self.queue.state);
        loop {
            if state.idle() {
                return true;
            }
            let left = bound.saturating_sub(start.elapsed());
            if left.is_zero() {
                return false;
            }
            state = match self.queue.changed.wait_timeout(state, left) {
                Ok((state, _)) => state,
                Err(poisoned) => poisoned.into_inner().0,
            };
        }
    }
}

/// The last clone of the store is gone: the thread is told to stop once
/// the queue is empty, the drop waits up to [`DROP_BOUND`] for that and
/// joins it; if the bound expires (a stalled disk), the thread is left to
/// finish alone and a WARN says how many operations were still waiting.
impl Drop for Behind {
    fn drop(&mut self) {
        let Some(handle) = lock(&self.thread).take() else {
            return;
        };
        lock(&self.queue.state).stop = true;
        self.queue.changed.notify_all();
        if self.flush(self.drop_bound) {
            // The thread ends right after the queue ran empty; a panic in
            // it was already reported by the runtime.
            let _ = handle.join();
        } else {
            let state = lock(&self.queue.state);
            let left = state
                .pending
                .len()
                .saturating_add(usize::from(state.running.is_some()));
            log::warn!(
                target: LOG_TARGET,
                "markers not written within {}: {left} left to the writer thread",
                duration_text(self.drop_bound)
            );
        }
    }
}

/// The writer thread: applies the oldest pending operation until the store
/// is dropped and the queue is empty. A failure is logged at WARN as
/// `marker set failed: <error>` or `marker clear failed: <error>`, the
/// texts the session used when the store wrote synchronously.
fn run(queue: &Queue, dir: &std::path::Path, apply: Apply) {
    loop {
        let mut state = lock(&queue.state);
        while state.pending.is_empty() && !state.stop {
            state = match queue.changed.wait(state) {
                Ok(state) => state,
                Err(poisoned) => poisoned.into_inner(),
            };
        }
        let Some((identifier, op)) = state.pending.pop_front() else {
            // Stopped with nothing left.
            return;
        };
        state.running = Some((identifier.clone(), op));
        drop(state);
        if let Err(error) = apply(dir, &identifier, op) {
            log::warn!(target: LOG_TARGET, "marker {} failed: {error}", op.word());
        }
        lock(&queue.state).running = None;
        queue.changed.notify_all();
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::path::Path;

    /// The bound of a wait that is expected to succeed.
    const LONG: Duration = Duration::from_secs(30);

    /// `seconds` after the Unix epoch.
    fn at(seconds: u64) -> SystemTime {
        UNIX_EPOCH + Duration::from_secs(seconds)
    }

    /// A gate that holds the writer thread inside `apply` until opened, and
    /// the record of what it applied. Each test has its own static, since
    /// `apply` is a plain function.
    struct Gate {
        /// Open, and the operations applied (or entered) so far.
        state: Mutex<(bool, Vec<(String, Op)>)>,
        /// Signalled on every change.
        changed: Condvar,
    }

    impl Gate {
        /// A closed gate.
        const fn new() -> Self {
            Self {
                state: Mutex::new((false, Vec::new())),
                changed: Condvar::new(),
            }
        }

        /// Records the operation, then waits until the gate is open.
        fn pass(&self, identifier: &str, op: Op) {
            let mut state = self.state.lock().unwrap();
            state.1.push((identifier.to_string(), op));
            self.changed.notify_all();
            while !state.0 {
                state = self.changed.wait(state).unwrap();
            }
        }

        /// Waits until `n` operations have entered `apply`.
        fn entered(&self, n: usize) {
            let mut state = self.state.lock().unwrap();
            while state.1.len() < n {
                state = self.changed.wait(state).unwrap();
            }
        }

        /// Opens the gate.
        fn open(&self) {
            self.state.lock().unwrap().0 = true;
            self.changed.notify_all();
        }

        /// The operations recorded so far.
        fn record(&self) -> Vec<(String, Op)> {
            self.state.lock().unwrap().1.clone()
        }
    }

    /// Test: UT-STORE-012
    ///
    /// Operations are applied in order; a newer pending operation of an
    /// identifier replaces the older one (and takes its place at the end);
    /// a read sees the latest pending or running operation; `flush` waits
    /// until everything is applied and gives `false` while the writer is
    /// held.
    #[test]
    fn operations_apply_in_order_and_the_latest_wins() {
        static GATE: Gate = Gate::new();
        fn gated(_: &Path, identifier: &str, op: Op) -> Result<(), Error> {
            GATE.pass(identifier, op);
            Ok(())
        }
        let behind = Behind::new(PathBuf::from("unused"), gated);
        behind.submit("a", Op::Set(at(1))).unwrap();
        GATE.entered(1);
        assert_eq!(behind.latest("a"), Some(Op::Set(at(1))), "running");
        behind.submit("b", Op::Set(at(2))).unwrap();
        behind.submit("a", Op::Clear).unwrap();
        behind.submit("b", Op::Clear).unwrap();
        behind.submit("c", Op::Set(at(3))).unwrap();
        behind.submit("b", Op::Set(at(4))).unwrap();
        assert_eq!(behind.latest("a"), Some(Op::Clear));
        assert_eq!(behind.latest("b"), Some(Op::Set(at(4))));
        assert_eq!(behind.latest("c"), Some(Op::Set(at(3))));
        assert_eq!(behind.latest("z"), None);
        assert!(!behind.flush(Duration::from_millis(20)), "held");
        GATE.open();
        assert!(behind.flush(LONG));
        assert_eq!(behind.latest("a"), None);
        assert_eq!(
            GATE.record(),
            vec![
                ("a".to_string(), Op::Set(at(1))),
                ("a".to_string(), Op::Clear),
                ("c".to_string(), Op::Set(at(3))),
                ("b".to_string(), Op::Set(at(4))),
            ]
        );
    }

    /// Test: UT-STORE-012
    ///
    /// A pending set reads back in whole seconds, as the file would give
    /// it, and a time before the epoch as the epoch.
    #[test]
    fn a_pending_set_reads_as_the_file_would() {
        assert_eq!(
            Op::Set(at(5) + Duration::from_millis(750)).present(),
            Some(at(5))
        );
        assert_eq!(
            Op::Set(UNIX_EPOCH - Duration::from_secs(1)).present(),
            Some(UNIX_EPOCH)
        );
        assert_eq!(Op::Clear.present(), None);
    }

    /// Test: UT-STORE-012
    ///
    /// Dropping the store drains what is pending and joins the thread.
    #[test]
    fn the_drop_drains_the_queue() {
        static GATE: Gate = Gate::new();
        fn gated(_: &Path, identifier: &str, op: Op) -> Result<(), Error> {
            GATE.pass(identifier, op);
            Ok(())
        }
        GATE.open();
        let behind = Behind::new(PathBuf::from("unused"), gated);
        for n in 0..20u64 {
            behind.submit(&format!("m{n}"), Op::Set(at(n))).unwrap();
        }
        drop(behind);
        assert_eq!(GATE.record().len(), 20);
    }

    /// Test: UT-STORE-012
    ///
    /// A drop whose writer is stalled returns after the bound and leaves
    /// the thread to finish alone, with a WARN.
    #[test]
    fn a_stalled_drop_returns_after_the_bound() {
        static GATE: Gate = Gate::new();
        fn gated(_: &Path, identifier: &str, op: Op) -> Result<(), Error> {
            GATE.pass(identifier, op);
            Ok(())
        }
        let log = crate::transport::test_log::install();
        let mut behind = Behind::new(PathBuf::from("unused"), gated);
        behind.drop_bound = Duration::from_millis(50);
        behind.submit("s", Op::Set(at(1))).unwrap();
        GATE.entered(1);
        behind.submit("t", Op::Clear).unwrap();
        let start = Instant::now();
        drop(behind);
        let took = start.elapsed();
        assert!(took >= Duration::from_millis(50), "{took:?}");
        assert!(took < Duration::from_secs(10), "{took:?}");
        let lines = log.lines_here(LOG_TARGET);
        assert!(
            lines.contains(&(
                log::Level::Warn,
                "markers not written within 50 ms: 2 left to the writer thread".to_string()
            )),
            "{lines:?}"
        );
        GATE.open();
    }

    /// Test: UT-STORE-012
    ///
    /// A failed write is logged at WARN with the text the session logged
    /// for a synchronous failure, and the writer goes on.
    #[test]
    fn a_failed_write_is_logged_and_the_writer_goes_on() {
        fn failing(_: &Path, identifier: &str, _: Op) -> Result<(), Error> {
            Err(Error::Store {
                message: format!("{identifier}: disk full"),
            })
        }
        let log = crate::transport::test_log::install();
        let behind = Behind::new(PathBuf::from("unused"), failing);
        behind.submit("behind-fail-1", Op::Set(at(1))).unwrap();
        behind.submit("behind-fail-2", Op::Clear).unwrap();
        assert!(behind.flush(LONG));
        let lines = log.lines(LOG_TARGET);
        for expected in [
            "marker set failed: store: behind-fail-1: disk full",
            "marker clear failed: store: behind-fail-2: disk full",
        ] {
            assert!(
                lines.contains(&(log::Level::Warn, expected.to_string())),
                "{expected}: {lines:?}"
            );
        }
    }
}
