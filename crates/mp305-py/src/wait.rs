//! Implements: DD-PY-002, DD-PY-003
//!
//! The blocking wait and the pump. A blocking call polls its future on the
//! calling thread, detached from the interpreter, in slices of at most
//! `WAIT_SLICE`. Between slices it checks for Ctrl-C first and then pumps:
//! it delivers queued log records and dispatches the session's events to
//! the Python dispatcher. The pump runs outside `block_on`, so a blocking
//! call made from the dispatcher or from a logging handler is a new wait,
//! never nested inside a `block_on`.
//!
//! Lock rules of the crate: (a) leaf locks guard plain Rust data for a copy
//! or a push, are never held across an `.await`, a `detach` or a call into
//! Python, and never while another lock is taken; a poisoned one is
//! recovered; (b) the dispatch token and the log token are the only state
//! held while Python code runs, and nothing ever waits for them; (c) no
//! `MutexGuard` lives inside a future or a `detach` closure.

use core::future::Future;

use mp305_core::error::Error;
use mp305_core::protocol::timing::WAIT_SLICE;
use pyo3::prelude::*;

use crate::convert;
use crate::errors;
use crate::feed::Feed;
use crate::logbridge;
use crate::runtime;

/// Waits for `fut` in slices with the GIL released; called under the guard
/// of `runtime::enter`. After each slice that did not finish, pending
/// signals are checked (an interrupt drops the future under the guard,
/// which cancels a core control command, DD-SESS-003) and then the pump
/// runs. When the future finishes the pump runs once more, then its result
/// is returned, an `Err` through `errors::to_py`; an exception raised by
/// that last pump propagates instead.
///
/// # Errors
///
/// The future's error as its Python exception, `KeyboardInterrupt` (main
/// thread only), or an exception raised by the dispatcher or a logging
/// handler.
pub fn block<T, F>(
    py: Python<'_>,
    pump_with: Option<(&Feed, &Bound<'_, PyAny>)>,
    fut: F,
) -> PyResult<T>
where
    T: Send,
    F: Future<Output = Result<T, Error>> + Send,
{
    let rt = runtime::get()?;
    let mut fut = core::pin::pin!(fut);
    let (feed, dispatch) = match pump_with {
        Some((feed, dispatch)) => (Some(feed), Some(dispatch)),
        None => (None, None),
    };
    loop {
        let slice = py
            .detach(|| rt.block_on(async { tokio::time::timeout(WAIT_SLICE, fut.as_mut()).await }));
        match slice {
            Ok(result) => {
                pump(py, feed, dispatch)?;
                return result.map_err(|e| errors::to_py(py, &e));
            }
            Err(_) => {
                py.check_signals()?;
                pump(py, feed, dispatch)?;
            }
        }
    }
}

/// The pump: (1) log delivery; (2) when both a feed and a dispatcher are
/// given, event dispatch. Dispatch takes the feed's dispatch token; a
/// thread that finds it taken skips dispatch, since another dispatcher (on
/// another thread, or further up this thread's stack) delivers the events
/// in order. The holder notes the newest event number and dispatches every
/// undispatched event up to it, one call of `dispatch(event_tuple)` each;
/// an exception from a call returns at once and leaves the later events
/// for the next pump.
///
/// # Errors
///
/// An exception raised by a logging handler that is not an `Exception`, or
/// any exception raised by `dispatch`.
pub fn pump(
    py: Python<'_>,
    feed: Option<&Feed>,
    dispatch: Option<&Bound<'_, PyAny>>,
) -> PyResult<()> {
    logbridge::deliver(py)?;
    let (Some(feed), Some(dispatch)) = (feed, dispatch) else {
        return Ok(());
    };
    let Some(_token) = feed.try_dispatch() else {
        return Ok(());
    };
    let noted = feed.newest_event();
    while let Some((seq, event)) = feed.take_for_dispatch(noted) {
        let tuple = convert::event(py, seq, &event)?;
        dispatch.call1((tuple,))?;
    }
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;
    use mp305_core::discovery::{Discovery, ScanOptions};
    use mp305_core::session::{Session, SessionEvents};

    /// Requires `Send`; called only to make the compiler check the bound.
    fn send<T: Send>(_: &T) {}

    /// The compile-time assertions of DD-PY-002: every core future the
    /// crate waits on is `Send`, as `Python::detach` requires.
    fn core_futures_are_send(
        session: &Session,
        events: &mut SessionEvents,
        feed: &Feed,
        discovery: &Discovery,
    ) {
        send(&session.ready());
        send(&session.set_voltage(1.0));
        send(&session.set_current_limit(1.0));
        send(&session.output_on());
        send(&session.output_off());
        send(&session.request_remote_control());
        send(&session.release_remote_control());
        send(&session.close(true));
        send(&events.next());
        send(&feed.wait(0, core::time::Duration::ZERO));
        send(&feed.flush());
        send(&discovery.scan(ScanOptions::default()));
        send(&Discovery::new());
        send(&crate::safety::idle());
        send(&crate::logbridge::wait_for_records(
            core::time::Duration::ZERO,
        ));
    }

    /// Test: UT-PY-021 (e)
    #[test]
    fn the_core_futures_are_send() {
        // Naming the function makes the compiler check its body.
        let check: fn(&Session, &mut SessionEvents, &Feed, &Discovery) = core_futures_are_send;
        let _ = check;
    }
}
