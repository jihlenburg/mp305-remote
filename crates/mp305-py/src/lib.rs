//! Implements: DD-PY-004, DD-PY-063, AR-001 (crate layout)
//!
//! `mp305-py`: the native module `mp305._native` of the Python library, a
//! thin synchronous face on `mp305_core::session`. It holds the runtime,
//! the blocking wait, the feed that buffers the session's events, the
//! safety calls, the log bridge and the conversions; the pure Python
//! package `mp305` holds everything a user reads. No protocol knowledge and
//! no device rule lives here.
//!
//! Every `#[pyclass]` is `frozen` and keeps its state behind `Arc`,
//! atomics or a leaf `Mutex`, so the classes are `Sync` and usable from
//! several Python threads. No code path may panic: PyO3 would turn a panic
//! into `PanicException`, which `except Exception` does not catch. The
//! crate has no `ffi` module; PyO3's macros need no `unsafe` in user code.

#![deny(unsafe_code)]
#![deny(missing_docs)]
#![warn(clippy::missing_docs_in_private_items)]
#![deny(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::panic,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects
)]
#![cfg_attr(
    test,
    allow(
        clippy::unwrap_used,
        clippy::expect_used,
        clippy::panic,
        clippy::indexing_slicing,
        clippy::arithmetic_side_effects
    )
)]

pub mod convert;
pub mod csv;
pub mod discover;
pub mod errors;
pub mod feed;
pub mod logbridge;
pub mod mock;
pub mod runtime;
pub mod safety;
pub mod session;
pub mod wait;

use mp305_core::protocol::units::{SUPPLY_MAX_RAW_CURRENT, SUPPLY_MAX_RAW_VOLTAGE};
use pyo3::prelude::*;
use pyo3::types::PyBytes;

/// The native module `mp305._native`; its init symbol `PyInit__native` is
/// what `module-name = "mp305._native"` needs.
#[pymodule(name = "_native")]
fn native(m: &Bound<'_, PyModule>) -> PyResult<()> {
    logbridge::install();
    let py = m.py();
    m.add("SCAN_DEFAULT_S", discover::scan_default_s())?;
    m.add("SCAN_MIN_S", discover::scan_min_s())?;
    m.add("SCAN_MAX_S", discover::scan_max_s())?;
    m.add("WAIT_SLICE_S", wait::wait_slice_s())?;
    m.add("SUPPLY_MAX_RAW_VOLTAGE", SUPPLY_MAX_RAW_VOLTAGE)?;
    m.add("SUPPLY_MAX_RAW_CURRENT", SUPPLY_MAX_RAW_CURRENT)?;
    m.add("MOCK_HOST_ID", PyBytes::new(py, &mock::MOCK_HOST_ID))?;
    m.add_class::<session::Session>()?;
    m.add_class::<mock::MockHandles>()?;
    m.add_function(wrap_pyfunction!(discover::discover, m)?)?;
    m.add_function(wrap_pyfunction!(discover::not_found_text, m)?)?;
    m.add_function(wrap_pyfunction!(csv::csv_header, m)?)?;
    m.add_function(wrap_pyfunction!(csv::format_csv_row, m)?)?;
    m.add_function(wrap_pyfunction!(csv::raw_voltage, m)?)?;
    m.add_function(wrap_pyfunction!(csv::raw_current, m)?)?;
    m.add_function(wrap_pyfunction!(csv::setpoint_range_text, m)?)?;
    m.add_function(wrap_pyfunction!(session::default_state_dir, m)?)?;
    m.add_function(wrap_pyfunction!(session::host_id, m)?)?;
    m.add_function(wrap_pyfunction!(logbridge::set_gate, m)?)?;
    m.add_function(wrap_pyfunction!(logbridge::log_wait, m)?)?;
    m.add_function(wrap_pyfunction!(logbridge::log_test, m)?)?;
    m.add_function(wrap_pyfunction!(safety::pending_safety, m)?)?;
    m.add_function(wrap_pyfunction!(safety::wait_safety, m)?)?;
    m.add_function(wrap_pyfunction!(mock::fixtures, m)?)?;
    m.add_function(wrap_pyfunction!(mock::c3, m)?)?;
    m.add_function(wrap_pyfunction!(mock::on_air, m)?)?;
    m.add_function(wrap_pyfunction!(mock::sample_events, m)?)?;
    Ok(())
}
