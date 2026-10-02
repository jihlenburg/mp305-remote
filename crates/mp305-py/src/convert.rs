//! Implements: DD-PY-022, DD-PY-021 (the event boundary)
//!
//! Conversions across the Python boundary: float seconds to a `Duration`
//! without a panic, integer nanoseconds to and from `SystemTime`, and the
//! tuples and dicts the native API hands to Python (the reading, info,
//! found, counters and event tuples of `_native.pyi`).
//!
//! The reading tuple, in order (`ReadingTuple` in the stub):
//!
//! | # | Field | Source |
//! |---|---|---|
//! | 0 | `wall_ns: int` | `TimedReading::wall`, ns since the epoch |
//! | 1 | `raw: bytes` | `raw.raw`, the 36 payload bytes |
//! | 2 | `voltage: float` | `volts`, V |
//! | 3 | `current: float` | `amps`, A |
//! | 4 | `power: float` | `watts`, W |
//! | 5 | `set_voltage: float` | `set_volts`, V |
//! | 6 | `set_current: float` | `set_amps`, A |
//! | 7 | `output_on: bool` | `output_on` |
//! | 8 | `mode: str` | `regulation`: `off`, `cv`, `cc`, `held_above`, `unknown` |
//! | 9 | `mode_raw: int` | `raw.out_state` |
//! | 10 | `mode_text: str` | `regulation`'s `Display` |
//! | 11 | `live_mode: str` | `live_mode`: `dc`, `program`, `pd`, `charge`, `unknown` |
//! | 12 | `live_mode_raw: int` | `raw.model` |
//! | 13 | `faults: int` | `faults.0` |
//! | 14 | `temperature: int` | `temperature_c`, °C |
//! | 15 | `energy: float` | `watt_hours`, Wh |
//! | 16 | `working_time: int` | `working_time_s`, s |

use core::time::Duration;
use std::time::{SystemTime, UNIX_EPOCH};

use mp305_core::discovery::Found;
use mp305_core::link::Counters;
use mp305_core::protocol::ops::info::Info;
use mp305_core::protocol::ops::settings::Settings;
use mp305_core::protocol::ops::telemetry::{LiveMode, RegulationMode};
use mp305_core::session::{PromptKind, SessionEvent, TimedReading};
use pyo3::exceptions::PyValueError;
use pyo3::prelude::*;
use pyo3::types::{PyBytes, PyDict, PyTuple};
use pyo3::BoundObject;

/// The longest time, in seconds, any float time of the native API may
/// carry.
const MAX_SECONDS: f64 = 60.0;

/// A float time or an integer wall time outside its range.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct BadTime;

/// `value` seconds as a `Duration`: `Ok` only for a finite value from 0 to
/// 60 (`-0.0` is 0), through `Duration::try_from_secs_f64`, which never
/// panics.
///
/// # Errors
///
/// [`BadTime`] for anything else.
pub fn seconds(value: f64) -> Result<Duration, BadTime> {
    if !value.is_finite() || !(0.0..=MAX_SECONDS).contains(&value) {
        return Err(BadTime);
    }
    // `-0.0` passes the range check; its absolute value is 0.
    Duration::try_from_secs_f64(value.abs()).map_err(|_| BadTime)
}

/// [`seconds`] for an argument called `name`.
///
/// # Errors
///
/// `ValueError("<name> must be a finite number of seconds from 0 to 60, got <value>")`.
pub fn seconds_arg(name: &str, value: f64) -> PyResult<Duration> {
    seconds(value).map_err(|_| {
        PyValueError::new_err(format!(
            "{name} must be a finite number of seconds from 0 to 60, got {value}"
        ))
    })
}

/// The wall time `ns` nanoseconds after the epoch.
///
/// # Errors
///
/// [`BadTime`] for a negative `ns`.
pub fn wall(ns: i64) -> Result<SystemTime, BadTime> {
    let ns = u64::try_from(ns).map_err(|_| BadTime)?;
    UNIX_EPOCH
        .checked_add(Duration::from_nanos(ns))
        .ok_or(BadTime)
}

/// [`wall`] for an argument called `name`.
///
/// # Errors
///
/// `ValueError("<name> must be a time from the epoch on, in ns, got <ns>")`.
pub fn wall_arg(name: &str, ns: i64) -> PyResult<SystemTime> {
    wall(ns).map_err(|_| {
        PyValueError::new_err(format!(
            "{name} must be a time from the epoch on, in ns, got {ns}"
        ))
    })
}

/// Nanoseconds since the epoch of `t`: 0 before the epoch, saturating at
/// `i64::MAX`.
#[must_use]
pub fn wall_ns(t: SystemTime) -> i64 {
    t.duration_since(UNIX_EPOCH)
        .map_or(0, |d| i64::try_from(d.as_nanos()).unwrap_or(i64::MAX))
}

/// Seconds since the epoch of `t` as a float, 0.0 before the epoch.
#[must_use]
pub fn wall_seconds(t: SystemTime) -> f64 {
    t.duration_since(UNIX_EPOCH)
        .map_or(0.0, |d| d.as_secs_f64())
}

/// The spelling of a regulation mode in the reading tuple (the values of
/// `mp305.Mode`, DD-CSV-002's spellings).
#[must_use]
pub fn regulation_name(mode: RegulationMode) -> &'static str {
    match mode {
        RegulationMode::Off => "off",
        RegulationMode::Cv => "cv",
        RegulationMode::Cc => "cc",
        RegulationMode::HeldAboveSetpoint => "held_above",
        RegulationMode::Unknown(_) => "unknown",
    }
}

/// The spelling of a live mode in the reading tuple (the values of
/// `mp305.LiveMode`).
#[must_use]
pub fn live_mode_name(mode: LiveMode) -> &'static str {
    match mode {
        LiveMode::Dc => "dc",
        LiveMode::Program => "program",
        LiveMode::Pd => "pd",
        LiveMode::Charge => "charge",
        LiveMode::Unknown(_) => "unknown",
    }
}

/// The spelling of a prompt kind (the `PromptKind` literal).
#[must_use]
pub fn prompt_name(kind: PromptKind) -> &'static str {
    match kind {
        PromptKind::ConfirmConnection => "confirm_connection",
        PromptKind::AllowRemoteControl => "allow_remote_control",
    }
}

/// The kind name of an event (the values of `mp305.EventKind`).
#[must_use]
pub fn event_kind(event: &SessionEvent) -> &'static str {
    match event {
        SessionEvent::Reading(_) => "reading",
        SessionEvent::FaultsChanged { .. } => "faults_changed",
        SessionEvent::SettingsChanged(_) => "settings_changed",
        SessionEvent::BindResult { .. } => "bind_result",
        SessionEvent::RemoteControl(_) => "remote_control",
        SessionEvent::Prompt { .. } => "prompt",
        SessionEvent::SetpointsChanged { .. } => "setpoints_changed",
        SessionEvent::UncleanExitWarning { .. } => "unclean_exit_warning",
        SessionEvent::LinkLost { .. } => "link_lost",
        SessionEvent::Reconnected => "reconnected",
        SessionEvent::ReconnectGaveUp { .. } => "reconnect_gave_up",
    }
}

/// Builds a tuple from already converted items.
fn tuple<'py>(py: Python<'py>, items: Vec<Bound<'py, PyAny>>) -> PyResult<Bound<'py, PyTuple>> {
    PyTuple::new(py, items)
}

/// Converts one value to a Python object.
fn obj<'py, T>(py: Python<'py>, value: T) -> PyResult<Bound<'py, PyAny>>
where
    T: IntoPyObject<'py>,
{
    value
        .into_pyobject(py)
        .map(BoundObject::into_any)
        .map(BoundObject::into_bound)
        .map_err(Into::into)
}

/// The reading tuple of `r` (the table of the module documentation).
///
/// # Errors
///
/// A Python error from building the tuple.
pub fn reading<'py>(py: Python<'py>, r: &TimedReading) -> PyResult<Bound<'py, PyTuple>> {
    let v = &r.reading;
    tuple(
        py,
        vec![
            obj(py, wall_ns(r.wall))?,
            PyBytes::new(py, &v.raw.raw).into_any(),
            obj(py, v.volts)?,
            obj(py, v.amps)?,
            obj(py, v.watts)?,
            obj(py, v.set_volts)?,
            obj(py, v.set_amps)?,
            obj(py, v.output_on)?,
            obj(py, regulation_name(v.regulation))?,
            obj(py, v.raw.out_state)?,
            obj(py, v.regulation.to_string())?,
            obj(py, live_mode_name(v.live_mode))?,
            obj(py, v.raw.model)?,
            obj(py, v.faults.0)?,
            obj(py, v.temperature_c)?,
            obj(py, v.watt_hours)?,
            obj(py, v.working_time_s)?,
        ],
    )
}

/// The info tuple `(model, version, hardware, bootloader, name)`, the
/// versions as `a.b.c.d` text.
///
/// # Errors
///
/// A Python error from building the tuple.
pub fn info<'py>(py: Python<'py>, i: &Info) -> PyResult<Bound<'py, PyTuple>> {
    let bootloader = match &i.bootloader_raw {
        Some(bytes) => PyBytes::new(py, bytes).into_any(),
        None => py.None().into_bound(py),
    };
    tuple(
        py,
        vec![
            obj(py, i.model.as_str())?,
            obj(py, i.version.to_string())?,
            obj(py, i.hardware.map(|v| v.to_string()))?,
            bootloader,
            obj(py, i.name.as_deref())?,
        ],
    )
}

/// The found tuple `(transport, identifier, unit_id, name, rssi,
/// remote_flag, description)`, `description` being the core's `Display`.
///
/// # Errors
///
/// A Python error from building the tuple.
pub fn found<'py>(py: Python<'py>, f: &Found) -> PyResult<Bound<'py, PyTuple>> {
    tuple(
        py,
        vec![
            obj(py, f.transport.to_string())?,
            obj(py, f.identifier.as_str())?,
            obj(py, f.unit_id.as_str())?,
            obj(py, f.name.as_str())?,
            obj(py, f.rssi)?,
            obj(py, f.remote_flag)?,
            obj(py, f.to_string())?,
        ],
    )
}

/// The counters tuple `(dropped_frames, ignored, late_replies)`.
///
/// # Errors
///
/// A Python error from building the tuple.
pub fn counters<'py>(py: Python<'py>, c: &Counters) -> PyResult<Bound<'py, PyTuple>> {
    tuple(
        py,
        vec![
            obj(py, c.dropped_frames)?,
            obj(py, c.ignored)?,
            obj(py, c.late_replies)?,
        ],
    )
}

/// The eight `Settings` fields as a dict with the core's field names.
fn settings<'py>(py: Python<'py>, s: &Settings) -> PyResult<Bound<'py, PyDict>> {
    let d = PyDict::new(py);
    d.set_item("charge_limit", s.charge_limit)?;
    d.set_item("volume", s.volume)?;
    d.set_item("screen_off", s.screen_off)?;
    d.set_item("shutdown", s.shutdown)?;
    d.set_item("screen_direction", s.screen_direction)?;
    d.set_item("ramp_step", s.ramp_step)?;
    d.set_item("ocp_delay", s.ocp_delay)?;
    d.set_item("usb_line_drop", s.usb_line_drop)?;
    Ok(d)
}

/// The event tuple `(seq, kind, payload)` of DD-PY-021, the payload keys per
/// kind exactly as the design lists them. A `Reading` (which the feed never
/// hands here) has the kind `reading` and the key `reading`.
///
/// # Errors
///
/// A Python error from building the tuple.
pub fn event<'py>(py: Python<'py>, seq: u64, e: &SessionEvent) -> PyResult<Bound<'py, PyTuple>> {
    let d = PyDict::new(py);
    match e {
        SessionEvent::Reading(r) => d.set_item("reading", reading(py, r)?)?,
        SessionEvent::FaultsChanged { faults, reading: r } => {
            d.set_item("faults", faults.0)?;
            d.set_item("reading", reading(py, r)?)?;
        }
        SessionEvent::SettingsChanged(s) => d.set_item("settings", settings(py, s)?)?,
        SessionEvent::BindResult { recognised } => d.set_item("recognised", *recognised)?,
        SessionEvent::RemoteControl(state) => d.set_item("remote_state", state.to_string())?,
        SessionEvent::Prompt {
            kind,
            bound_s,
            text,
        } => {
            d.set_item("prompt", prompt_name(*kind))?;
            d.set_item("bound_s", *bound_s)?;
            d.set_item("text", *text)?;
        }
        SessionEvent::SetpointsChanged {
            set_volts,
            set_amps,
            expected_volts,
            expected_amps,
        } => {
            d.set_item("set_voltage", *set_volts)?;
            d.set_item("set_current", *set_amps)?;
            d.set_item("expected_voltage", *expected_volts)?;
            d.set_item("expected_current", *expected_amps)?;
        }
        SessionEvent::UncleanExitWarning { since, text } => {
            d.set_item("since", wall_seconds(*since))?;
            d.set_item("text", text.as_str())?;
        }
        SessionEvent::LinkLost { text } | SessionEvent::ReconnectGaveUp { text } => {
            d.set_item("text", text.as_str())?;
        }
        SessionEvent::Reconnected => {}
    }
    tuple(
        py,
        vec![obj(py, seq)?, obj(py, event_kind(e))?, d.into_any()],
    )
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Test: UT-PY-021 (d)
    #[test]
    fn seconds_accepts_0_to_60_and_rejects_the_rest() {
        for bad in [-1.0, 60.0001, f64::NAN, f64::INFINITY, 1e30] {
            assert_eq!(seconds(bad), Err(BadTime), "{bad}");
        }
        assert_eq!(seconds(-0.0), Ok(Duration::ZERO));
        assert_eq!(seconds(0.0), Ok(Duration::ZERO));
        assert_eq!(seconds(0.5), Ok(Duration::from_millis(500)));
        assert_eq!(seconds(60.0), Ok(Duration::from_secs(60)));
    }

    /// Test: UT-PY-021 (d)
    #[test]
    fn wall_and_wall_ns() {
        assert_eq!(wall(-1), Err(BadTime));
        assert_eq!(wall(0), Ok(UNIX_EPOCH));
        assert_eq!(
            wall(1_790_848_800_123_999_999),
            Ok(UNIX_EPOCH + Duration::from_nanos(1_790_848_800_123_999_999))
        );
        assert_eq!(wall_ns(UNIX_EPOCH - Duration::from_secs(1)), 0);
        assert_eq!(
            wall_ns(UNIX_EPOCH + Duration::from_nanos(1_790_848_800_123_999_999)),
            1_790_848_800_123_999_999
        );
        assert_eq!(wall_seconds(UNIX_EPOCH - Duration::from_secs(1)), 0.0);
    }

    /// Test: UT-PY-021 (d) (the spellings of the reading tuple)
    #[test]
    fn mode_spellings() {
        let modes: Vec<&str> = [0, 1, 2, 3, 9]
            .into_iter()
            .map(|raw| regulation_name(RegulationMode::from_raw(raw)))
            .collect();
        assert_eq!(modes, ["off", "cv", "cc", "held_above", "unknown"]);
        let live: Vec<&str> = [0, 1, 2, 3, 7]
            .into_iter()
            .map(|raw| live_mode_name(LiveMode::from_raw(raw)))
            .collect();
        assert_eq!(live, ["dc", "program", "pd", "charge", "unknown"]);
        assert_eq!(
            prompt_name(PromptKind::ConfirmConnection),
            "confirm_connection"
        );
        assert_eq!(
            prompt_name(PromptKind::AllowRemoteControl),
            "allow_remote_control"
        );
    }
}
