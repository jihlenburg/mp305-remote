//! Implements: DD-PY-008
//!
//! The safety calls `output_off` and `close` run their core sequence as a
//! task on the runtime, which holds its own `Arc` of the core session. The
//! Python caller only waits for the task's answer, so an interrupt or a
//! dispatcher exception ends the wait and never the sequence (decision 17).
//! A process-wide registry lists the running sequences, so that the exit
//! hook can wait for them.

use core::future::Future;
use std::collections::BTreeMap;
use std::sync::Mutex;

use mp305_core::error::Error;
use pyo3::prelude::*;
use tokio::sync::{oneshot, Notify};

use crate::feed::lock;
use crate::runtime;
use crate::wait;

/// The log target of the safety tasks (`mp305.native.safety` in Python).
pub const LOG_TARGET: &str = "mp305_py::safety";

/// The running sequences by registration number.
#[derive(Debug)]
struct Registry {
    /// The number of the next registration.
    next: u64,
    /// The names of the running sequences.
    running: BTreeMap<u64, String>,
}

/// The process-wide registry of running safety sequences.
static REGISTRY: Mutex<Registry> = Mutex::new(Registry {
    next: 0,
    running: BTreeMap::new(),
});

/// Notified whenever a sequence leaves the registry.
static LEFT: Notify = Notify::const_new();

/// Adds `name` to the registry and returns its number.
fn register(name: &str) -> u64 {
    let mut registry = lock(&REGISTRY);
    let id = registry.next;
    registry.next = id.saturating_add(1);
    registry.running.insert(id, name.to_string());
    id
}

/// Removes entry `id` and wakes the waiters.
fn unregister(id: u64) {
    lock(&REGISTRY).running.remove(&id);
    LEFT.notify_waiters();
}

/// The record a finished sequence logs (DD-PY-008): a failure always, at
/// ERROR, whether or not the waiter is still there, since an interrupt or a
/// dispatcher exception in the very slice in which the sequence completes
/// replaces the error the waiter would have raised; a success at INFO only
/// when the waiter is gone.
#[must_use]
pub fn outcome_record(
    name: &str,
    result: &Result<(), Error>,
    waiter_gone: bool,
) -> Option<(log::Level, String)> {
    match result {
        Err(error) => Some((log::Level::Error, format!("{name} failed: {error}"))),
        Ok(()) if waiter_gone => Some((log::Level::Info, format!("{name} finished"))),
        Ok(()) => None,
    }
}

/// Logs the record of [`outcome_record`], if any.
fn log_outcome(name: &str, result: &Result<(), Error>, waiter_gone: bool) {
    if let Some((level, text)) = outcome_record(name, result, waiter_gone) {
        log::log!(target: LOG_TARGET, level, "{text}");
    }
}

/// Spawns `sequence` on the current runtime under `name` (`output-off
/// <identifier>` or `close <identifier>`), registered until it ends, and
/// returns the receiver of its result. The outcome is logged before the
/// entry leaves the registry, so a waiter that sees the registry empty also
/// finds the record queued. Needs the runtime entered.
pub fn spawn<F>(name: String, sequence: F) -> oneshot::Receiver<Result<(), Error>>
where
    F: Future<Output = Result<(), Error>> + Send + 'static,
{
    let id = register(&name);
    let (reply, rx) = oneshot::channel();
    drop(tokio::spawn(async move {
        let result = sequence.await;
        let gone = reply.is_closed();
        log_outcome(&name, &result, gone);
        unregister(id);
        if !gone {
            if let Err(result) = reply.send(result) {
                // The waiter left after the check: a success is logged now;
                // a failure was logged above already.
                if result.is_ok() {
                    log_outcome(&name, &result, true);
                }
            }
        }
    }));
    rx
}

/// The result a waiter gets: the sequence's, or an error when the task
/// ended without answering (it cannot, short of a runtime shutdown).
pub async fn result(rx: oneshot::Receiver<Result<(), Error>>, name: &str) -> Result<(), Error> {
    rx.await.unwrap_or_else(|_| {
        Err(Error::Cancelled {
            reason: format!("{name} ended without a result"),
        })
    })
}

/// The names of the running sequences, oldest first; empty in a process
/// forked after the runtime started (DD-PY-008).
#[must_use]
pub fn pending() -> Vec<String> {
    pending_unless(runtime::forked())
}

/// The names of the running sequences, or an empty list without taking the
/// registry lock when `forked`: the sequences are the parent's, and the
/// lock may have been held by a parent thread at the fork.
#[must_use]
pub fn pending_unless(forked: bool) -> Vec<String> {
    if forked {
        return Vec::new();
    }
    lock(&REGISTRY).running.values().cloned().collect()
}

/// Returns once the registry is empty.
pub async fn idle() {
    loop {
        let left = LEFT.notified();
        tokio::pin!(left);
        left.as_mut().enable();
        if lock(&REGISTRY).running.is_empty() {
            return;
        }
        left.await;
    }
}

/// `pending_safety() -> list[str]`: the running safety sequences.
#[pyfunction]
pub fn pending_safety() -> Vec<String> {
    pending()
}

/// `wait_safety(dispatch=None)`: a blocking call that returns when no safety
/// sequence runs. It has no feed, so its pump only delivers log records;
/// `dispatch` is accepted for the signature of DD-PY-008 and not called.
///
/// # Errors
///
/// `KeyboardInterrupt` and the other errors of a blocking call.
#[pyfunction]
#[pyo3(signature = (dispatch=None))]
pub fn wait_safety(py: Python<'_>, dispatch: Option<Bound<'_, PyAny>>) -> PyResult<()> {
    let _rt = runtime::enter()?;
    // DD-PY-008 names a `dispatch` argument, but the call has no feed whose
    // events it could dispatch (DD-PY-003 dispatches only with both).
    drop(dispatch);
    wait::block(py, None, async {
        idle().await;
        Ok(())
    })
}

#[cfg(test)]
mod tests {
    use super::*;
    use core::time::Duration;

    /// Test: UT-PY-024 (in Rust: a failure is logged at ERROR always, a
    /// success at INFO only when the waiter is gone, DD-PY-008 rev 3)
    #[test]
    fn the_outcome_log_rule() {
        let failed = Err(Error::Timeout {
            opcode: 0xC8,
            after: Duration::from_millis(500),
        });
        let text = "output-off m failed: no reply to 0xc8 within 500 ms".to_string();
        for waiter_gone in [false, true] {
            assert_eq!(
                outcome_record("output-off m", &failed, waiter_gone),
                Some((log::Level::Error, text.clone()))
            );
        }
        assert_eq!(outcome_record("close m", &Ok(()), false), None);
        assert_eq!(
            outcome_record("close m", &Ok(()), true),
            Some((log::Level::Info, "close m finished".to_string()))
        );
    }

    /// Test: UT-PY-024 (in Rust: in a forked child the list is empty and the
    /// registry lock is not taken, DD-PY-008 rev 3)
    #[test]
    fn pending_in_a_forked_child_takes_no_lock() {
        let id = register("close forked-test");
        let held = lock(&REGISTRY);
        let (tx, rx) = std::sync::mpsc::channel();
        std::thread::spawn(move || {
            let _ = tx.send(pending_unless(true));
        });
        let listed = rx.recv_timeout(Duration::from_secs(1));
        drop(held);
        assert_eq!(listed, Ok(Vec::new()));
        assert!(pending_unless(false).contains(&"close forked-test".to_string()));
        unregister(id);
    }

    /// Test: UT-PY-024 (the registry in Rust: a sequence is listed until it
    /// ends)
    #[test]
    fn a_sequence_is_listed_until_it_ends() {
        let rt = runtime::get().unwrap();
        let _guard = rt.enter();
        let (go, wait) = oneshot::channel::<()>();
        let rx = spawn("close UT-PY-021-safety".to_string(), async move {
            let _ = wait.await;
            Ok(())
        });
        assert!(pending().contains(&"close UT-PY-021-safety".to_string()));
        go.send(()).unwrap();
        let outcome = rt.block_on(async {
            let outcome = result(rx, "close").await;
            tokio::time::timeout(Duration::from_secs(1), async {
                while pending().contains(&"close UT-PY-021-safety".to_string()) {
                    tokio::task::yield_now().await;
                }
            })
            .await
            .unwrap();
            outcome
        });
        assert_eq!(outcome, Ok(()));
    }
}
