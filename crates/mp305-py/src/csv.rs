//! Implements: DD-PY-033
//!
//! The pure helpers the Python layer uses without a session: the CSV header
//! and row of SR-037 (one implementation, `mp305_core::csv`), and the
//! core's setpoint rounding and range text, against which the Python checks
//! are tested (UT-PY-028).

use mp305_core::csv;
use mp305_core::error::Error;
use mp305_core::protocol::ops::telemetry::{self, Reading};
use mp305_core::protocol::units::{Limits, RawCurrent, RawVoltage};
use mp305_core::session::TimedReading;
use pyo3::exceptions::PyValueError;
use pyo3::prelude::*;

use crate::convert;
use crate::errors;

/// The fields a range text may name; `Error::SetpointRange` takes a
/// `&'static str`.
const FIELDS: [&str; 5] = [
    "voltage",
    "current",
    "voltage limit",
    "current limit",
    "scan time (s)",
];

/// `csv_header() -> str`: the header line with its `\n`.
#[pyfunction]
#[must_use]
pub fn csv_header() -> &'static str {
    csv::header()
}

/// The CSV row of a `0xC3` payload with the wall time `wall_ns` and the
/// `t_s` origin `origin_ns` (both ns since the epoch).
///
/// # Errors
///
/// A text for a payload that is not 36 bytes or a negative time.
pub fn row(raw: &[u8], wall_ns: i64, origin_ns: i64) -> Result<String, String> {
    let parsed =
        telemetry::parse_payload(raw).map_err(|reason| format!("not a 0xC3 payload: {reason}"))?;
    let wall = convert::wall(wall_ns)
        .map_err(|_| format!("wall_ns must be a time from the epoch on, got {wall_ns}"))?;
    let origin = convert::wall(origin_ns)
        .map_err(|_| format!("origin_ns must be a time from the epoch on, got {origin_ns}"))?;
    // `at` is a placeholder: DD-CSV-002 reads only `wall` and `reading`.
    let reading = TimedReading {
        at: tokio::time::Instant::now(),
        wall,
        reading: Reading::from_raw(&parsed),
    };
    Ok(csv::format_row(&reading, origin))
}

/// `format_csv_row(raw, wall_ns, origin_ns) -> str`: [`row`].
///
/// # Errors
///
/// `ValueError` with the text of [`row`].
#[pyfunction]
pub fn format_csv_row(raw: &[u8], wall_ns: i64, origin_ns: i64) -> PyResult<String> {
    row(raw, wall_ns, origin_ns).map_err(PyValueError::new_err)
}

/// `raw_voltage(volts, max_voltage) -> int`: `RawVoltage::from_volts`.
///
/// # Errors
///
/// `SetpointRangeError` as the core raises it.
#[pyfunction]
#[pyo3(signature = (volts, max_voltage))]
pub fn raw_voltage(py: Python<'_>, volts: f64, max_voltage: Option<f64>) -> PyResult<u16> {
    let limits = Limits {
        max_volts: max_voltage,
        max_amps: None,
    };
    RawVoltage::from_volts(volts, &limits)
        .map(RawVoltage::raw)
        .map_err(|e| errors::to_py(py, &e))
}

/// `raw_current(amps, max_current) -> int`: `RawCurrent::from_amps`.
///
/// # Errors
///
/// `SetpointRangeError` as the core raises it.
#[pyfunction]
#[pyo3(signature = (amps, max_current))]
pub fn raw_current(py: Python<'_>, amps: f64, max_current: Option<f64>) -> PyResult<u16> {
    let limits = Limits {
        max_volts: None,
        max_amps: max_current,
    };
    RawCurrent::from_amps(amps, &limits)
        .map(RawCurrent::raw)
        .map_err(|e| errors::to_py(py, &e))
}

/// The `Display` of `Error::SetpointRange` with these fields, or `None`
/// for a field the core does not name.
#[must_use]
pub fn range_text(field: &str, value: f64, minimum: f64, maximum: f64) -> Option<String> {
    let field = FIELDS.iter().find(|f| **f == field)?;
    Some(
        Error::SetpointRange {
            field,
            value,
            min: minimum,
            max: maximum,
        }
        .to_string(),
    )
}

/// `setpoint_range_text(field, value, minimum, maximum) -> str`: the
/// `Display` of `Error::SetpointRange` with those fields.
///
/// # Errors
///
/// `ValueError` for a field other than `voltage`, `current`, `voltage
/// limit`, `current limit` and `scan time (s)`.
#[pyfunction]
pub fn setpoint_range_text(
    field: &str,
    value: f64,
    minimum: f64,
    maximum: f64,
) -> PyResult<String> {
    range_text(field, value, minimum, maximum)
        .ok_or_else(|| PyValueError::new_err(format!("unknown field {field:?}")))
}

#[cfg(test)]
mod tests {
    use super::*;
    use mp305_core::protocol::fixtures::C3_CAPTURE;

    /// Test: UT-PY-016 (a), in Rust
    #[test]
    fn rows_from_integer_nanoseconds() {
        assert_eq!(
            row(
                &C3_CAPTURE,
                1_790_848_800_250_000_000,
                1_790_848_800_000_000_000
            ),
            Ok("2026-10-01T10:00:00.250Z,0.250,0.00,0.000,0.00,13.00,1.000,0,off,\n".to_string())
        );
        assert_eq!(
            row(
                &C3_CAPTURE,
                1_790_848_800_123_999_999,
                1_790_848_800_000_000_000
            ),
            Ok("2026-10-01T10:00:00.123Z,0.123,0.00,0.000,0.00,13.00,1.000,0,off,\n".to_string())
        );
        assert!(row(b"short", 0, 0)
            .unwrap_err()
            .starts_with("not a 0xC3 payload"));
        assert!(row(&C3_CAPTURE, -1, 0).is_err());
        assert!(row(&C3_CAPTURE, 0, -1).is_err());
        assert_eq!(csv_header(), csv::header());
    }

    /// Test: UT-PY-028, in Rust
    #[test]
    fn range_texts() {
        assert_eq!(
            range_text("voltage", 31.0, 0.0, 30.0).as_deref(),
            Some("voltage 31 is outside 0 to 30")
        );
        assert_eq!(
            range_text("voltage limit", f64::NAN, 0.0, 30.0).as_deref(),
            Some("voltage limit NaN is outside 0 to 30")
        );
        assert_eq!(
            range_text("voltage", 1e-7, 0.0, 30.0).as_deref(),
            Some("voltage 0.0000001 is outside 0 to 30")
        );
        assert_eq!(range_text("power", 1.0, 0.0, 30.0), None);
    }
}
