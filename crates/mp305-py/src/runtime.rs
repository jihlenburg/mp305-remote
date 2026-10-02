//! Implements: DD-PY-001
//!
//! The one Tokio runtime of the process (ADR-0007). It is built on first
//! use and stored with the process ID it was built in. A build failure is
//! raised and not cached, so the next call retries. A process forked after
//! the runtime started inherits its state but not its threads, so every
//! call there is refused before anything else.
//!
//! Rule of the crate: every native function or method that touches a
//! session, the feed, a `MockHandles` or the runtime takes
//! `let _rt = runtime::enter()?;` as its first statement. The guard is a
//! local of the Python thread, is never captured by a `detach` closure (it
//! is not `Send`) and drops last, so timers, spawns and the drop of a
//! cancelled future all see the runtime.

use std::io;
use std::sync::OnceLock;

use pyo3::prelude::*;
use tokio::runtime::{Builder, EnterGuard, Runtime};

use crate::errors;

/// The runtime of the process and the ID of the process it was built in.
static RT: OnceLock<(Runtime, u32)> = OnceLock::new();

/// The text of the error in a process forked after the runtime started.
pub const FORKED: &str = "mp305 cannot be used in a process forked after it started; \
                          use the multiprocessing start method spawn or forkserver";

/// Builds the runtime: two workers named `mp305-rt`, every driver Tokio
/// has compiled in (the time driver, and the I/O driver that the BlueZ
/// backend needs on Linux).
fn build() -> io::Result<Runtime> {
    Builder::new_multi_thread()
        .worker_threads(2)
        .thread_name("mp305-rt")
        .enable_all()
        .build()
}

/// The runtime of the process, built on first use.
///
/// # Errors
///
/// `Mp305Error` naming the fork in a forked child, or
/// `Mp305Error("cannot start the runtime: <io error>")` when the build
/// fails (not cached; the next call retries).
pub fn get() -> PyResult<&'static Runtime> {
    get_from(&RT, build)
}

/// [`get`] over any cell and builder: if `cell` holds a runtime, that one
/// (after the fork check); else `build` runs and the result is stored with
/// `OnceLock::get_or_init`. A racing first call may build a second runtime,
/// which is dropped at once.
///
/// # Errors
///
/// As [`get`].
pub fn get_from<F>(cell: &OnceLock<(Runtime, u32)>, build: F) -> PyResult<&Runtime>
where
    F: FnOnce() -> io::Result<Runtime>,
{
    if let Some((rt, pid)) = cell.get() {
        return checked(rt, *pid);
    }
    let built = build()
        .map_err(|e| errors::mp305_error_unattached(&format!("cannot start the runtime: {e}")))?;
    let (rt, pid) = cell.get_or_init(|| (built, std::process::id()));
    checked(rt, *pid)
}

/// `rt` when it was built in this process.
fn checked(rt: &Runtime, pid: u32) -> PyResult<&Runtime> {
    if pid == std::process::id() {
        Ok(rt)
    } else {
        Err(errors::mp305_error_unattached(FORKED))
    }
}

/// Enters the runtime on the calling thread; the guard must be dropped on
/// the same thread.
///
/// # Errors
///
/// As [`get`].
pub fn enter() -> PyResult<EnterGuard<'static>> {
    Ok(get()?.enter())
}

/// Whether this is a process forked after the runtime started.
#[must_use]
pub fn forked() -> bool {
    RT.get().is_some_and(|(_, pid)| *pid != std::process::id())
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::sync::atomic::{AtomicUsize, Ordering};

    /// Test: UT-PY-021 (a)
    #[test]
    fn get_returns_one_runtime() {
        let first = get().unwrap();
        let second = get().unwrap();
        assert!(std::ptr::eq(first, second));
        assert!(!forked());
    }

    /// Test: UT-PY-021 (b)
    #[test]
    fn the_io_driver_is_on() {
        let bound = get()
            .unwrap()
            .block_on(async { tokio::net::TcpListener::bind("127.0.0.1:0").await });
        assert!(bound.is_ok());
    }

    /// A future whose drop spawns a task, as DD-DISC-012's drop guard does.
    struct SpawnOnDrop;

    impl core::future::Future for SpawnOnDrop {
        type Output = ();
        fn poll(
            self: core::pin::Pin<&mut Self>,
            _cx: &mut core::task::Context<'_>,
        ) -> core::task::Poll<()> {
            core::task::Poll::Pending
        }
    }

    impl Drop for SpawnOnDrop {
        fn drop(&mut self) {
            drop(tokio::spawn(async {}));
        }
    }

    /// Test: UT-PY-021 (c)
    #[test]
    fn a_future_dropped_under_the_guard_can_spawn() {
        let _rt = enter().unwrap();
        let future = SpawnOnDrop;
        drop(future);
    }

    /// Test: UT-PY-021 (f)
    #[test]
    fn a_failed_build_is_not_cached() {
        let cell = OnceLock::new();
        let runs = AtomicUsize::new(0);
        let builder = || {
            if runs.fetch_add(1, Ordering::SeqCst) == 0 {
                Err(io::Error::other("no threads"))
            } else {
                build()
            }
        };
        assert!(get_from(&cell, builder).is_err());
        assert!(get_from(&cell, builder).is_ok());
        assert_eq!(runs.load(Ordering::SeqCst), 2);
    }
}
