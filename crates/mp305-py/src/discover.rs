//! Implements: DD-PY-030
//!
//! `discover()` and the process-wide `Discovery`. The scan time is checked
//! before anything else; only then is the `Discovery` obtained, inside the
//! wait, from a `tokio::sync::OnceCell`, so that a failed `Discovery::new`
//! is not cached and two threads racing on first use share one instance
//! and one scan lock.

use core::future::Future;
use std::sync::Arc;

use mp305_core::discovery::{self, Discovery, ScanOptions};
use mp305_core::error::Error;
use mp305_core::protocol::timing;
use pyo3::prelude::*;
use pyo3::types::PyTuple;
use tokio::sync::OnceCell;

use crate::convert;
use crate::errors;
use crate::runtime;
use crate::wait;

/// The process-wide `Discovery`, created on first use.
pub static DISCOVERY: OnceCell<Arc<Discovery>> = OnceCell::const_new();

/// The field name of the scan time in its range error.
const SCAN_TIME_FIELD: &str = "scan time (s)";

/// The value of `cell`, filled by `init` on first use; a failed `init` is
/// not cached, and concurrent first callers run one `init`.
///
/// # Errors
///
/// The error of `init`.
pub async fn shared<V, F, Fut>(cell: &OnceCell<V>, init: F) -> Result<V, Error>
where
    V: Clone,
    F: FnOnce() -> Fut,
    Fut: Future<Output = Result<V, Error>>,
{
    cell.get_or_try_init(init).await.cloned()
}

/// The process-wide `Discovery` (for `discover` and `Session.connect`).
///
/// # Errors
///
/// The error of `Discovery::new`.
pub async fn discovery() -> Result<Arc<Discovery>, Error> {
    shared(&DISCOVERY, || async {
        Discovery::new().await.map(Arc::new)
    })
    .await
}

/// The scan time in seconds as a float.
fn as_seconds(d: core::time::Duration) -> f64 {
    d.as_secs_f64()
}

/// `SCAN_DEFAULT_S`, the default scan time in seconds.
#[must_use]
pub fn scan_default_s() -> f64 {
    as_seconds(timing::SCAN_DEFAULT)
}

/// `SCAN_MIN_S`, the shortest scan time in seconds.
#[must_use]
pub fn scan_min_s() -> f64 {
    as_seconds(timing::SCAN_MIN)
}

/// `SCAN_MAX_S`, the longest scan time in seconds.
#[must_use]
pub fn scan_max_s() -> f64 {
    as_seconds(timing::SCAN_MAX)
}

/// The scan options for `scan_time_s`, checked first.
///
/// # Errors
///
/// [`Error::SetpointRange`] (the text of DD-DISC-004) for a time that is
/// not finite or outside 1 to 60 s.
pub fn options(scan_time_s: f64, bluetooth: bool, usb: bool) -> Result<ScanOptions, Error> {
    let (min, max) = (scan_min_s(), scan_max_s());
    let range = Error::SetpointRange {
        field: SCAN_TIME_FIELD,
        value: scan_time_s,
        min,
        max,
    };
    if !scan_time_s.is_finite() || scan_time_s < min || scan_time_s > max {
        return Err(range);
    }
    let duration = convert::seconds(scan_time_s).map_err(|_| range)?;
    let mut options = ScanOptions::default().with_duration(duration)?;
    options.bluetooth = bluetooth;
    options.usb = usb;
    Ok(options)
}

/// `discover(scan_time_s, bluetooth, usb) -> list[FoundTuple]`: a blocking
/// call without feed or dispatcher. An interrupt drops the scan future under
/// the runtime guard, so the discovery's drop guard can stop the scan.
///
/// # Errors
///
/// `SetpointRangeError` for a bad scan time (nothing else runs then), the
/// errors of `Discovery::new` and of the scan, and those of a blocking
/// call.
#[pyfunction]
pub fn discover<'py>(
    py: Python<'py>,
    scan_time_s: f64,
    bluetooth: bool,
    usb: bool,
) -> PyResult<Vec<Bound<'py, PyTuple>>> {
    let _rt = runtime::enter()?;
    let options = options(scan_time_s, bluetooth, usb).map_err(|e| errors::to_py(py, &e))?;
    let found = wait::block(py, None, async move {
        let discovery = discovery().await?;
        discovery.scan(options).await
    })?;
    found.iter().map(|f| convert::found(py, f)).collect()
}

/// `not_found_text() -> str`: the text of "no supply found" with the four
/// causes of SR-005.
#[pyfunction]
#[must_use]
pub fn not_found_text() -> String {
    discovery::not_found().to_string()
}

#[cfg(test)]
mod tests {
    use super::*;
    use core::time::Duration;
    use std::sync::atomic::{AtomicUsize, Ordering};

    /// Test: UT-PY-021 (g)
    #[tokio::test(flavor = "multi_thread", worker_threads = 2)]
    async fn shared_runs_init_once_for_racing_callers() {
        let cell: Arc<OnceCell<Arc<usize>>> = Arc::new(OnceCell::new());
        let runs = Arc::new(AtomicUsize::new(0));
        let task = || {
            let (cell, runs) = (Arc::clone(&cell), Arc::clone(&runs));
            tokio::spawn(async move {
                shared(&cell, || async {
                    tokio::time::sleep(Duration::from_millis(50)).await;
                    Ok(Arc::new(runs.fetch_add(1, Ordering::SeqCst)))
                })
                .await
            })
        };
        let (a, b) = (task(), task());
        let a = a.await.unwrap().unwrap();
        let b = b.await.unwrap().unwrap();
        assert_eq!(runs.load(Ordering::SeqCst), 1);
        assert!(Arc::ptr_eq(&a, &b));
    }

    /// Test: UT-PY-021 (g)
    #[tokio::test]
    async fn a_failed_init_is_not_cached() {
        let cell: OnceCell<Arc<u8>> = OnceCell::new();
        let runs = AtomicUsize::new(0);
        let init = || async {
            if runs.fetch_add(1, Ordering::SeqCst) == 0 {
                Err(Error::Transport {
                    message: "no adapter".to_string(),
                })
            } else {
                Ok(Arc::new(1))
            }
        };
        assert!(shared(&cell, init).await.is_err());
        assert_eq!(shared(&cell, init).await.map(|v| *v), Ok(1));
        assert_eq!(runs.load(Ordering::SeqCst), 2);
    }

    /// Test: UT-PY-011 (the scan time is checked first, in Rust)
    #[test]
    fn options_check_the_scan_time() {
        for bad in [0.5, 61.0, -1.0, f64::NAN, f64::INFINITY] {
            let error = options(bad, true, true).unwrap_err();
            assert!(matches!(
                error,
                Error::SetpointRange {
                    field: "scan time (s)",
                    min: 1.0,
                    max: 60.0,
                    ..
                }
            ));
        }
        assert_eq!(
            options(0.5, true, true).unwrap_err().to_string(),
            "scan time (s) 0.5 is outside 1 to 60"
        );
        let ok = options(2.5, false, true).unwrap();
        assert_eq!(ok.duration(), Duration::from_millis(2500));
        assert!(!ok.bluetooth);
        assert!(ok.usb);
        assert_eq!(
            (scan_default_s(), scan_min_s(), scan_max_s()),
            (10.0, 1.0, 60.0)
        );
    }
}
