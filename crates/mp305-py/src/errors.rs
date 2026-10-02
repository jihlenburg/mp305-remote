//! Implements: DD-PY-011
//!
//! The mapping from `mp305_core::Error` to the Python exceptions of
//! `mp305.errors`. The class and the keyword attributes of each variant are
//! decided by two pure functions, [`class_of`] and [`attributes`], whose
//! `match`es have no wildcard arm, so a new core variant fails to compile
//! here. [`to_py`] builds the exception object from them.

use mp305_core::error::Error;
use pyo3::exceptions::PyRuntimeError;
use pyo3::prelude::*;
use pyo3::sync::PyOnceLock;
use pyo3::types::{PyDict, PyModule};

/// The Python class an error maps to, by its name in `mp305.errors`.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum ErrorClass {
    /// `NotFoundError`.
    NotFound,
    /// `ConnectionDeniedError`.
    ConnectionDenied,
    /// `RemoteControlDeniedError`.
    RemoteControlDenied,
    /// `RemoteControlLostError`.
    RemoteControlLost,
    /// `SetpointRangeError`.
    SetpointRange,
    /// `CommandRejectedError`.
    CommandRejected,
    /// `ModeError`.
    Mode,
    /// `FaultActiveError`.
    FaultActive,
    /// `Mp305TimeoutError`.
    Timeout,
    /// `LinkLostError`.
    LinkLost,
    /// The base class `Mp305Error`.
    Base,
}

impl ErrorClass {
    /// The class name in `mp305.errors`.
    #[must_use]
    pub const fn name(self) -> &'static str {
        match self {
            ErrorClass::NotFound => "NotFoundError",
            ErrorClass::ConnectionDenied => "ConnectionDeniedError",
            ErrorClass::RemoteControlDenied => "RemoteControlDeniedError",
            ErrorClass::RemoteControlLost => "RemoteControlLostError",
            ErrorClass::SetpointRange => "SetpointRangeError",
            ErrorClass::CommandRejected => "CommandRejectedError",
            ErrorClass::Mode => "ModeError",
            ErrorClass::FaultActive => "FaultActiveError",
            ErrorClass::Timeout => "Mp305TimeoutError",
            ErrorClass::LinkLost => "LinkLostError",
            ErrorClass::Base => "Mp305Error",
        }
    }
}

/// The class of `e` (AR-050). Total over the enum, without a wildcard arm.
#[must_use]
pub fn class_of(e: &Error) -> ErrorClass {
    match e {
        Error::NotFound { .. } => ErrorClass::NotFound,
        Error::ConnectionDenied => ErrorClass::ConnectionDenied,
        Error::RemoteControlDenied => ErrorClass::RemoteControlDenied,
        Error::RemoteControlLost => ErrorClass::RemoteControlLost,
        Error::SetpointRange { .. } => ErrorClass::SetpointRange,
        Error::CommandRejected { .. } => ErrorClass::CommandRejected,
        Error::Mode { .. } => ErrorClass::Mode,
        Error::FaultActive { .. } => ErrorClass::FaultActive,
        Error::Timeout { .. } => ErrorClass::Timeout,
        Error::LinkLost { .. } | Error::Transport { .. } => ErrorClass::LinkLost,
        Error::NotReady
        | Error::Store { .. }
        | Error::Protocol(_)
        | Error::AlreadyOpen { .. }
        | Error::Cancelled { .. } => ErrorClass::Base,
    }
}

/// The value of one keyword attribute of an exception.
#[derive(Clone, Debug, PartialEq)]
pub enum Attribute {
    /// An integer.
    Int(i64),
    /// A float.
    Float(f64),
    /// A text.
    Text(String),
    /// The `Faults` word, turned into a `frozenset[Fault]` by
    /// `mp305.types.faults_from_word`.
    Faults(u16),
}

/// The keyword attributes of `e`, in the order the class takes them; empty
/// for the variants without attributes (a core `NotFound` therefore has
/// `found == ()`).
#[must_use]
pub fn attributes(e: &Error) -> Vec<(&'static str, Attribute)> {
    match e {
        Error::CommandRejected { status, reason } => vec![
            ("status", Attribute::Int(i64::from(*status))),
            ("reason", Attribute::Text(reason.clone())),
        ],
        Error::FaultActive { faults } => vec![("faults", Attribute::Faults(faults.0))],
        Error::SetpointRange {
            field,
            value,
            min,
            max,
        } => vec![
            ("field", Attribute::Text((*field).to_string())),
            ("value", Attribute::Float(*value)),
            ("minimum", Attribute::Float(*min)),
            ("maximum", Attribute::Float(*max)),
        ],
        Error::Mode { live_mode } => vec![("live_mode_raw", Attribute::Int(i64::from(*live_mode)))],
        Error::NotFound { .. }
        | Error::ConnectionDenied
        | Error::RemoteControlDenied
        | Error::RemoteControlLost
        | Error::Timeout { .. }
        | Error::LinkLost { .. }
        | Error::Transport { .. }
        | Error::NotReady
        | Error::Store { .. }
        | Error::Protocol(_)
        | Error::AlreadyOpen { .. }
        | Error::Cancelled { .. } => Vec::new(),
    }
}

/// `mp305.errors`, imported once per process.
static ERRORS: PyOnceLock<Py<PyModule>> = PyOnceLock::new();
/// `mp305.types`, imported once per process.
static TYPES: PyOnceLock<Py<PyModule>> = PyOnceLock::new();

/// The module `name` from `cell`, imported on first use; a failed import
/// is a `RuntimeError` naming the module.
fn module<'py>(
    py: Python<'py>,
    cell: &PyOnceLock<Py<PyModule>>,
    name: &str,
) -> PyResult<Bound<'py, PyModule>> {
    cell.get_or_try_init(py, || py.import(name).map(Bound::unbind))
        .map(|m| m.bind(py).clone())
        .map_err(|e| PyRuntimeError::new_err(format!("cannot import {name}: {e}")))
}

/// Builds the exception object of `class` with `message` and `attributes`.
fn build(
    py: Python<'_>,
    class: ErrorClass,
    message: &str,
    attributes: Vec<(&'static str, Attribute)>,
) -> PyResult<PyErr> {
    let errors = module(py, &ERRORS, "mp305.errors")?;
    let class = errors.getattr(class.name())?;
    let kwargs = PyDict::new(py);
    for (key, value) in attributes {
        match value {
            Attribute::Int(v) => kwargs.set_item(key, v)?,
            Attribute::Float(v) => kwargs.set_item(key, v)?,
            Attribute::Text(v) => kwargs.set_item(key, v)?,
            Attribute::Faults(word) => {
                let types = module(py, &TYPES, "mp305.types")?;
                let faults = types.getattr("faults_from_word")?.call1((word,))?;
                kwargs.set_item(key, faults)?;
            }
        }
    }
    let instance = class.call((message,), Some(&kwargs))?;
    Ok(PyErr::from_value(instance))
}

/// The Python exception of `e`: the class of [`class_of`] called with the
/// error's `Display` text and the keywords of [`attributes`]. A failure to
/// build it (a failed import) is returned instead.
#[must_use]
pub fn to_py(py: Python<'_>, e: &Error) -> PyErr {
    build(py, class_of(e), &e.to_string(), attributes(e)).unwrap_or_else(|err| err)
}

/// An `Mp305Error` raised by the native layer itself, with `message`.
#[must_use]
pub fn mp305_error(py: Python<'_>, message: &str) -> PyErr {
    build(py, ErrorClass::Base, message, Vec::new()).unwrap_or_else(|err| err)
}

/// [`mp305_error`] for a caller without the `Python` token: attaches for
/// the build, or, when the interpreter is not available (a Rust test
/// without Python), a `RuntimeError` with the same message.
#[must_use]
pub fn mp305_error_unattached(message: &str) -> PyErr {
    Python::try_attach(|py| mp305_error(py, message))
        .unwrap_or_else(|| PyRuntimeError::new_err(message.to_string()))
}

#[cfg(test)]
mod tests {
    use super::*;
    use core::time::Duration;
    use mp305_core::protocol::error::Reason;
    use mp305_core::protocol::ops::telemetry::Faults;

    /// One case: an error, its class and its attributes.
    type Case = (Error, ErrorClass, Vec<(&'static str, Attribute)>);

    /// Test: UT-PY-001
    #[test]
    fn every_variant_has_its_class_and_attributes() {
        let text = |s: &str| s.to_string();
        let cases: Vec<Case> = vec![
            (
                Error::NotFound { causes: text("c") },
                ErrorClass::NotFound,
                vec![],
            ),
            (
                Error::ConnectionDenied,
                ErrorClass::ConnectionDenied,
                vec![],
            ),
            (
                Error::RemoteControlDenied,
                ErrorClass::RemoteControlDenied,
                vec![],
            ),
            (
                Error::RemoteControlLost,
                ErrorClass::RemoteControlLost,
                vec![],
            ),
            (
                Error::SetpointRange {
                    field: "voltage",
                    value: 31.0,
                    min: 0.0,
                    max: 30.0,
                },
                ErrorClass::SetpointRange,
                vec![
                    ("field", Attribute::Text(text("voltage"))),
                    ("value", Attribute::Float(31.0)),
                    ("minimum", Attribute::Float(0.0)),
                    ("maximum", Attribute::Float(30.0)),
                ],
            ),
            (
                Error::CommandRejected {
                    status: 0xFF,
                    reason: text("busy"),
                },
                ErrorClass::CommandRejected,
                vec![
                    ("status", Attribute::Int(255)),
                    ("reason", Attribute::Text(text("busy"))),
                ],
            ),
            (
                Error::Mode { live_mode: 2 },
                ErrorClass::Mode,
                vec![("live_mode_raw", Attribute::Int(2))],
            ),
            (
                Error::FaultActive {
                    faults: Faults(0x21),
                },
                ErrorClass::FaultActive,
                vec![("faults", Attribute::Faults(33))],
            ),
            (Error::NotReady, ErrorClass::Base, vec![]),
            (
                Error::Timeout {
                    opcode: 0xC8,
                    after: Duration::from_secs(1),
                },
                ErrorClass::Timeout,
                vec![],
            ),
            (
                Error::LinkLost { text: text("t") },
                ErrorClass::LinkLost,
                vec![],
            ),
            (
                Error::Transport { message: text("m") },
                ErrorClass::LinkLost,
                vec![],
            ),
            (
                Error::Store { message: text("s") },
                ErrorClass::Base,
                vec![],
            ),
            (
                Error::Protocol(Reason::Short { needed: 2, got: 1 }),
                ErrorClass::Base,
                vec![],
            ),
            (
                Error::AlreadyOpen {
                    identifier: text("x"),
                },
                ErrorClass::Base,
                vec![],
            ),
            (
                Error::Cancelled { reason: text("r") },
                ErrorClass::Base,
                vec![],
            ),
        ];
        assert_eq!(cases.len(), 16);
        for (error, class, attrs) in cases {
            assert_eq!(class_of(&error), class, "{error:?}");
            assert_eq!(attributes(&error), attrs, "{error:?}");
        }
    }

    /// Test: UT-PY-001 (the class names are those of `mp305.errors`)
    #[test]
    fn class_names() {
        let names: Vec<&str> = [
            ErrorClass::NotFound,
            ErrorClass::ConnectionDenied,
            ErrorClass::RemoteControlDenied,
            ErrorClass::RemoteControlLost,
            ErrorClass::SetpointRange,
            ErrorClass::CommandRejected,
            ErrorClass::Mode,
            ErrorClass::FaultActive,
            ErrorClass::Timeout,
            ErrorClass::LinkLost,
            ErrorClass::Base,
        ]
        .iter()
        .map(|c| c.name())
        .collect();
        assert_eq!(
            names,
            [
                "NotFoundError",
                "ConnectionDeniedError",
                "RemoteControlDeniedError",
                "RemoteControlLostError",
                "SetpointRangeError",
                "CommandRejectedError",
                "ModeError",
                "FaultActiveError",
                "Mp305TimeoutError",
                "LinkLostError",
                "Mp305Error",
            ]
        );
    }
}
