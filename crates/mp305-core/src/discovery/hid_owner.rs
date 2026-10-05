//! The one thread that makes every `hidapi` context call of the process:
//! the probe, the enumeration and the open.
//!
//! On macOS `hidapi` keeps one device manager for the whole process and
//! schedules it on the run loop of the thread that initialises the library.
//! When that thread ends, its run loop is freed, and the next enumeration,
//! from any thread, schedules the devices on the freed run loop. The app
//! crashed that way on 2026-10-05 (LOGBOOK of that day, "The app crashes in
//! the USB enumeration"). Tokio ends the idle threads of its blocking pool,
//! so the context calls cannot run there. This module starts one thread on
//! first use, never ends it, and runs every call on it, one after the
//! other. That also keeps `hidapi`'s shared state away from concurrent
//! callers on every platform.
//!
//! Implements: DD-DISC-013.

use std::panic::{catch_unwind, AssertUnwindSafe};
use std::sync::mpsc::{channel, Sender};
use std::sync::OnceLock;

use tokio::sync::oneshot;

use crate::discovery::LOG_TARGET;
use crate::error::Error;

/// The name of the owner thread, as debuggers and crash reports show it.
pub(crate) const THREAD_NAME: &str = "mp305-hidapi";

/// One call for the owner thread: the work together with the delivery of
/// its result.
type Job = Box<dyn FnOnce() + Send>;

/// The queue of the owner thread, or the reason the thread could not be
/// started. It is set once. The sender it holds lives as long as the
/// process, so the thread's loop never runs out of senders and never ends.
static OWNER: OnceLock<Result<Sender<Job>, String>> = OnceLock::new();

/// Starts the owner thread and returns its queue.
fn start() -> Result<Sender<Job>, String> {
    let (jobs, queue) = channel::<Job>();
    std::thread::Builder::new()
        .name(THREAD_NAME.to_string())
        .spawn(move || {
            for job in queue {
                // A panic in a vendor call must not end the thread: a new
                // thread would meet the freed run loop the module comment
                // describes. The caller sees the dropped reply as an error.
                if catch_unwind(AssertUnwindSafe(job)).is_err() {
                    log::error!(target: LOG_TARGET, "a USB HID call panicked");
                }
            }
        })
        .map(|_| jobs)
        .map_err(|error| format!("no thread for USB HID: {error}"))
}

/// The error of a call whose result never arrived.
fn unanswered() -> Error {
    Error::Transport {
        message: "the USB HID call did not complete".to_string(),
    }
}

/// Runs `work` on the owner thread and returns what it returned. Calls run
/// one after the other, in the order they were submitted. A caller that
/// stops waiting does not stop its call: the work runs to its end and the
/// result is dropped on the owner thread.
///
/// # Errors
///
/// [`Error::Transport`] when the thread could not be started or the work
/// panicked; otherwise whatever `work` returns.
pub(crate) async fn run<T, F>(work: F) -> Result<T, Error>
where
    T: Send + 'static,
    F: FnOnce() -> Result<T, Error> + Send + 'static,
{
    let jobs = OWNER
        .get_or_init(start)
        .as_ref()
        .map_err(|message| Error::Transport {
            message: message.clone(),
        })?;
    let (reply, outcome) = oneshot::channel();
    jobs.send(Box::new(move || {
        // The receiver is gone when the caller stopped waiting. The result
        // is then dropped here, which closes a device the work opened.
        let _ = reply.send(work());
    }))
    .map_err(|_| unanswered())?;
    outcome.await.map_err(|_| unanswered())?
}

#[cfg(test)]
mod tests {
    use std::sync::atomic::{AtomicBool, Ordering};
    use std::sync::Arc;
    use std::thread::ThreadId;
    use std::time::Duration;

    use super::*;

    /// The identifier and the name of the thread a call runs on.
    fn whereabouts() -> Result<(ThreadId, Option<String>), Error> {
        let thread = std::thread::current();
        Ok((thread.id(), thread.name().map(str::to_string)))
    }

    /// Makes one call from a new thread with its own runtime. Both have
    /// ended when this returns, as a thread of Tokio's blocking pool would.
    fn from_a_thread_that_ends() -> (ThreadId, Option<String>) {
        std::thread::spawn(|| {
            tokio::runtime::Builder::new_current_thread()
                .build()
                .unwrap()
                .block_on(run(whereabouts))
                .unwrap()
        })
        .join()
        .unwrap()
    }

    /// Test: UT-DISC-012
    #[test]
    fn every_call_runs_on_the_one_named_thread() {
        let first = from_a_thread_that_ends();
        let second = from_a_thread_that_ends();
        assert_eq!(first, second);
        assert_eq!(first.1.as_deref(), Some(THREAD_NAME));
        assert_ne!(first.0, std::thread::current().id());
    }

    /// Test: UT-DISC-012
    #[tokio::test]
    async fn a_panicking_call_is_an_error_and_the_thread_lives_on() {
        let before = run(whereabouts).await.unwrap();
        let outcome: Result<(), Error> = run(|| panic!("a vendor call panics")).await;
        assert!(
            matches!(outcome, Err(Error::Transport { ref message }) if message.contains("did not complete"))
        );
        assert_eq!(run(whereabouts).await.unwrap(), before);
    }

    /// Test: UT-DISC-012
    #[tokio::test]
    async fn a_call_whose_caller_went_away_still_runs_and_keeps_its_place() {
        let ran = Arc::new(AtomicBool::new(false));
        let flag = Arc::clone(&ran);
        // The timeout polls the call once, which submits it, and then drops
        // it while the work is still asleep.
        let abandoned = tokio::time::timeout(
            Duration::ZERO,
            run(move || {
                std::thread::sleep(Duration::from_millis(30));
                flag.store(true, Ordering::SeqCst);
                Ok(())
            }),
        )
        .await;
        assert!(abandoned.is_err());
        run(|| Ok(())).await.unwrap();
        assert!(ran.load(Ordering::SeqCst));
    }
}
