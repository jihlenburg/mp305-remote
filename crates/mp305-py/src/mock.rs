//! Implements: DD-PY-034
//!
//! The mock bridge: script dicts from Python become `transport::mock`
//! scripts (or connector outcomes), one mock per connection attempt, and
//! the `MockHandles` class keeps every mock's handle for the test. Plus the
//! test support functions: the capture fixtures, `c3`, `on_air` and
//! `sample_events`.
//!
//! A script dict is `{"error": text}`, `{"not_found": True}`, or has `kind`
//! (`"ble"` or `"hid"`) and optionally `replies`, `injections`,
//! `send_errors`, `stop_replying_at_s` and `close_at_s`; times are seconds
//! from that mock's creation (DD-TRANS-030).

use core::time::Duration;
use std::collections::VecDeque;
use std::sync::{Arc, Mutex};

use mp305_core::discovery;
use mp305_core::error::Error;
use mp305_core::protocol::ble::{self, BleRoute, Route};
use mp305_core::protocol::fixtures as core_fixtures;
use mp305_core::protocol::ops::settings;
use mp305_core::protocol::ops::telemetry::{self, Faults, Reading};
use mp305_core::session::doubles::MockConnector;
use mp305_core::session::texts;
use mp305_core::session::{Connector, PromptKind, RemoteState, SessionEvent, TimedReading};
use mp305_core::transport::description::Kind;
use mp305_core::transport::mock::{Injection, Mock, MockHandle, Reply, Script, SendError};
use pyo3::exceptions::PyValueError;
use pyo3::prelude::*;
use pyo3::types::{PyBytes, PyDict, PyList, PyTuple};

use crate::convert;
use crate::feed::lock;
use crate::runtime;

/// The host ID of a mock session without a state directory: the bytes 01
/// to 10.
pub const MOCK_HOST_ID: [u8; 16] = [
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
];

/// What one connection attempt does.
#[derive(Clone, Debug)]
pub enum Attempt {
    /// A mock of this kind following this script.
    Script(Kind, Script),
    /// The attempt fails with `Error::Transport { message }`.
    Error(String),
    /// The attempt fails with `discovery::not_found()`.
    NotFound,
}

/// The handles of the mocks a session made, with the creation instant of
/// the list.
#[derive(Debug)]
pub struct MockList {
    /// The handles, one per mock, in attempt order.
    handles: Mutex<Vec<MockHandle>>,
    /// When the list was made.
    created: tokio::time::Instant,
}

impl MockList {
    /// An empty list made now.
    #[must_use]
    pub fn new() -> Self {
        MockList {
            handles: Mutex::new(Vec::new()),
            created: tokio::time::Instant::now(),
        }
    }

    /// Appends the handle of a new mock.
    fn push(&self, handle: MockHandle) {
        lock(&self.handles).push(handle);
    }

    /// A copy of the handles.
    fn handles(&self) -> Vec<MockHandle> {
        lock(&self.handles).clone()
    }
}

impl Default for MockList {
    fn default() -> Self {
        MockList::new()
    }
}

/// The connector of a mock session: per attempt the next script makes a
/// mock on the session task (so each script's clock starts at its own
/// attempt), whose handle goes into `list`; when the scripts are used up
/// an attempt fails with `transport: no more mock scripts`.
#[must_use]
pub fn connector(
    attempts: Vec<Attempt>,
    identifier: String,
    list: Arc<MockList>,
) -> Arc<dyn Connector> {
    let mut queue: VecDeque<Attempt> = attempts.into();
    Arc::new(MockConnector::new(move || match queue.pop_front() {
        Some(Attempt::Script(kind, script)) => {
            let mock = Mock::new(kind, &identifier, script);
            list.push(mock.handle());
            Ok(mock)
        }
        Some(Attempt::Error(message)) => Err(Error::Transport { message }),
        Some(Attempt::NotFound) => Err(discovery::not_found()),
        None => Err(Error::Transport {
            message: "no more mock scripts".to_string(),
        }),
    }))
}

/// A `ValueError` naming the script index and the key.
fn bad(index: usize, key: &str, what: &str) -> PyErr {
    PyValueError::new_err(format!("script {index}: {key}: {what}"))
}

/// The keys of a script with a `kind`.
const SCRIPT_KEYS: [&str; 6] = [
    "kind",
    "replies",
    "injections",
    "send_errors",
    "stop_replying_at_s",
    "close_at_s",
];
/// The keys of a reply.
const REPLY_KEYS: [&str; 6] = [
    "request",
    "after_s",
    "deliveries",
    "repeat",
    "from_s",
    "route",
];
/// The keys of an injection.
const INJECTION_KEYS: [&str; 3] = ["at_s", "delivery", "route"];
/// The keys of a send error.
const SEND_ERROR_KEYS: [&str; 2] = ["opcode", "from_s"];

/// Reads a script dict field by field, naming the script and the key in
/// every error.
struct Reader<'a, 'py> {
    /// The script index.
    index: usize,
    /// The key path of the dict, for nested dicts.
    path: String,
    /// The dict.
    dict: &'a Bound<'py, PyDict>,
}

impl<'py> Reader<'_, 'py> {
    /// The full name of `key` for an error.
    fn name(&self, key: &str) -> String {
        if self.path.is_empty() {
            key.to_string()
        } else {
            format!("{}.{key}", self.path)
        }
    }

    /// A `ValueError` for `key`.
    fn bad(&self, key: &str, what: &str) -> PyErr {
        bad(self.index, &self.name(key), what)
    }

    /// Fails on a key outside `allowed`.
    fn only(&self, allowed: &[&str]) -> PyResult<()> {
        for key in self.dict.keys() {
            let key: String = key
                .extract()
                .map_err(|_| bad(self.index, &self.path, "keys must be strings"))?;
            if !allowed.contains(&key.as_str()) {
                return Err(self.bad(&key, "unknown key"));
            }
        }
        Ok(())
    }

    /// The value of `key`, `None` when absent or `None`.
    fn get(&self, key: &str) -> PyResult<Option<Bound<'py, PyAny>>> {
        let value = self
            .dict
            .get_item(key)
            .map_err(|_| self.bad(key, "cannot be read"))?;
        Ok(value.filter(|v| !v.is_none()))
    }

    /// The required value of `key`.
    fn required(&self, key: &str) -> PyResult<Bound<'py, PyAny>> {
        self.get(key)?.ok_or_else(|| self.bad(key, "is required"))
    }

    /// `key` as seconds through `convert::seconds`, `default` when absent.
    fn seconds(&self, key: &str, default: Option<Duration>) -> PyResult<Duration> {
        let Some(value) = self.get(key)? else {
            return default.ok_or_else(|| self.bad(key, "is required"));
        };
        let value: f64 = value
            .extract()
            .map_err(|_| self.bad(key, "must be a number of seconds"))?;
        convert::seconds(value)
            .map_err(|_| self.bad(key, "must be a finite number of seconds from 0 to 60"))
    }

    /// `key` as an opcode, 0 to 255.
    fn opcode(&self, key: &str) -> PyResult<u8> {
        self.required(key)?
            .extract()
            .map_err(|_| self.bad(key, "must be an opcode from 0 to 255"))
    }

    /// `key` as bytes.
    fn bytes(&self, key: &str, value: &Bound<'py, PyAny>) -> PyResult<Vec<u8>> {
        value
            .cast::<PyBytes>()
            .map(|b| b.as_bytes().to_vec())
            .map_err(|_| self.bad(key, "must be bytes"))
    }

    /// `key` as a route of `kind`, `default` when absent.
    fn route(&self, kind: Kind, default: Route) -> PyResult<Route> {
        let Some(value) = self.get("route")? else {
            return Ok(default);
        };
        let text: String = value
            .extract()
            .map_err(|_| self.bad("route", "must be \"af01\", \"af02\" or \"hid\""))?;
        let route = match text.as_str() {
            "af01" => Route::Ble(BleRoute::Af01),
            "af02" => Route::Ble(BleRoute::Af02),
            "hid" => Route::Hid,
            _ => return Err(self.bad("route", "must be \"af01\", \"af02\" or \"hid\"")),
        };
        match (kind, route) {
            (Kind::Ble, Route::Ble(_)) | (Kind::Hid, Route::Hid) => Ok(route),
            _ => Err(self.bad("route", &format!("does not match the kind {kind}"))),
        }
    }

    /// The list of dicts under `key`, each read by `read`.
    fn list<T>(
        &self,
        key: &str,
        read: impl Fn(&Reader<'_, 'py>) -> PyResult<T>,
    ) -> PyResult<Vec<T>> {
        let Some(value) = self.get(key)? else {
            return Ok(Vec::new());
        };
        let list = value
            .cast::<PyList>()
            .map_err(|_| self.bad(key, "must be a list of dicts"))?;
        let mut out = Vec::with_capacity(list.len());
        for (i, item) in list.iter().enumerate() {
            let path = format!("{}[{i}]", self.name(key));
            let dict = item
                .cast::<PyDict>()
                .map_err(|_| bad(self.index, &path, "must be a dict"))?;
            out.push(read(&Reader {
                index: self.index,
                path,
                dict,
            })?);
        }
        Ok(out)
    }
}

/// A reply dict.
fn reply(r: &Reader<'_, '_>, kind: Kind) -> PyResult<Reply> {
    r.only(&REPLY_KEYS)?;
    let request = r.opcode("request")?;
    let deliveries_value = r.required("deliveries")?;
    let deliveries_list = deliveries_value
        .cast::<PyList>()
        .map_err(|_| r.bad("deliveries", "must be a list of bytes"))?;
    let mut deliveries = Vec::with_capacity(deliveries_list.len());
    for item in deliveries_list.iter() {
        deliveries.push(r.bytes("deliveries", &item)?);
    }
    let repeat = match r.get("repeat")? {
        Some(value) => Some(
            value
                .extract::<usize>()
                .map_err(|_| r.bad("repeat", "must be a count or None"))?,
        ),
        None => None,
    };
    let default = core_fixtures::reply_route(kind, request.wrapping_add(1));
    Ok(Reply {
        request,
        after: r.seconds("after_s", None)?,
        route: r.route(kind, default)?,
        deliveries,
        repeat,
        from: r.seconds("from_s", Some(Duration::ZERO))?,
    })
}

/// An injection dict.
fn injection(r: &Reader<'_, '_>, kind: Kind) -> PyResult<Injection> {
    r.only(&INJECTION_KEYS)?;
    let default = match kind {
        Kind::Ble => Route::Ble(BleRoute::Af01),
        Kind::Hid => Route::Hid,
    };
    let delivery = r.required("delivery")?;
    Ok(Injection {
        at: r.seconds("at_s", None)?,
        route: r.route(kind, default)?,
        delivery: r.bytes("delivery", &delivery)?,
    })
}

/// A send error dict.
fn send_error(r: &Reader<'_, '_>) -> PyResult<SendError> {
    r.only(&SEND_ERROR_KEYS)?;
    Ok(SendError {
        opcode: r.opcode("opcode")?,
        from: r.seconds("from_s", Some(Duration::ZERO))?,
    })
}

/// Converts script `index`, with the GIL held.
///
/// # Errors
///
/// `ValueError` naming the script index and the key for an unknown key, a
/// wrong type, a time `convert::seconds` rejects, a route that does not
/// match the kind, or an opcode outside 0 to 255.
pub fn script_from_py(index: usize, script: &Bound<'_, PyAny>) -> PyResult<Attempt> {
    let dict = script
        .cast::<PyDict>()
        .map_err(|_| bad(index, "script", "must be a dict"))?;
    let r = Reader {
        index,
        path: String::new(),
        dict,
    };
    if dict.contains("error").unwrap_or(false) {
        r.only(&["error"])?;
        let text: String = r
            .required("error")?
            .extract()
            .map_err(|_| r.bad("error", "must be a text"))?;
        return Ok(Attempt::Error(text));
    }
    if dict.contains("not_found").unwrap_or(false) {
        r.only(&["not_found"])?;
        let on: bool = r
            .required("not_found")?
            .extract()
            .map_err(|_| r.bad("not_found", "must be True"))?;
        if !on {
            return Err(r.bad("not_found", "must be True"));
        }
        return Ok(Attempt::NotFound);
    }
    r.only(&SCRIPT_KEYS)?;
    let kind_text: String = r
        .required("kind")?
        .extract()
        .map_err(|_| r.bad("kind", "must be \"ble\" or \"hid\""))?;
    let kind = match kind_text.as_str() {
        "ble" => Kind::Ble,
        "hid" => Kind::Hid,
        _ => return Err(r.bad("kind", "must be \"ble\" or \"hid\"")),
    };
    let optional = |key: &str| -> PyResult<Option<Duration>> {
        match r.get(key)? {
            Some(_) => r.seconds(key, None).map(Some),
            None => Ok(None),
        }
    };
    let script = Script {
        replies: r.list("replies", |r| reply(r, kind))?,
        injections: r.list("injections", |r| injection(r, kind))?,
        send_errors: r.list("send_errors", send_error)?,
        stop_replying_at: optional("stop_replying_at_s")?,
        close_at: optional("close_at_s")?,
    };
    Ok(Attempt::Script(kind, script))
}

/// Converts every script.
///
/// # Errors
///
/// As [`script_from_py`].
pub fn scripts_from_py(scripts: &[Bound<'_, PyAny>]) -> PyResult<Vec<Attempt>> {
    scripts
        .iter()
        .enumerate()
        .map(|(i, s)| script_from_py(i, s))
        .collect()
}

/// The text of a route in a sent tuple.
fn route_name(route: Route) -> &'static str {
    match route {
        Route::Ble(BleRoute::Af01) => "af01",
        Route::Ble(BleRoute::Af02) => "af02",
        Route::Hid => "hid",
    }
}

/// `MockHandles()`: the handles of the mocks a mock session made. Made empty
/// by the caller; valid before, during and after the session's life, also
/// when `from_mock` or `ready` failed.
#[pyclass(frozen, module = "mp305._native")]
#[derive(Debug)]
pub struct MockHandles {
    /// The list the session's connector appends to.
    pub list: Arc<MockList>,
}

#[pymethods]
impl MockHandles {
    /// An empty list.
    #[new]
    fn py_new() -> PyResult<Self> {
        let _rt = runtime::enter()?;
        Ok(MockHandles {
            list: Arc::new(MockList::new()),
        })
    }

    /// `sent() -> list[SentTuple]`: `(attempt, time_s, route, opcode,
    /// payload)` for every accepted send, `attempt` being the mock's index
    /// and `time_s` its time after the list was made (0.0 if earlier).
    fn sent<'py>(&self, py: Python<'py>) -> PyResult<Vec<Bound<'py, PyTuple>>> {
        let _rt = runtime::enter()?;
        let mut out = Vec::new();
        for (attempt, handle) in self.list.handles().iter().enumerate() {
            for sent in handle.sent() {
                let time_s = sent
                    .at
                    .checked_duration_since(self.list.created)
                    .map_or(0.0, |d| d.as_secs_f64());
                let items: Vec<Bound<'py, PyAny>> = vec![
                    attempt.into_pyobject(py)?.into_any(),
                    time_s.into_pyobject(py)?.into_any(),
                    route_name(sent.route).into_pyobject(py)?.into_any(),
                    sent.frame.opcode().into_pyobject(py)?.into_any(),
                    PyBytes::new(py, sent.frame.payload()).into_any(),
                ];
                out.push(PyTuple::new(py, items)?);
            }
        }
        Ok(out)
    }

    /// `closes() -> int`: the `close` calls over every mock.
    fn closes(&self) -> PyResult<usize> {
        let _rt = runtime::enter()?;
        Ok(self
            .list
            .handles()
            .iter()
            .map(MockHandle::closes)
            .fold(0, usize::saturating_add))
    }

    /// `attempts() -> int`: the mocks made (failed attempts are not
    /// counted).
    fn attempts(&self) -> PyResult<usize> {
        let _rt = runtime::enter()?;
        Ok(self.list.handles().len())
    }
}

/// `fixtures() -> dict[str, bytes]`: the capture payloads.
///
/// # Errors
///
/// A Python error from building the dict.
#[pyfunction]
pub fn fixtures(py: Python<'_>) -> PyResult<Bound<'_, PyDict>> {
    let d = PyDict::new(py);
    d.set_item("C3_CAPTURE", PyBytes::new(py, &core_fixtures::C3_CAPTURE))?;
    d.set_item("E1_BLE", PyBytes::new(py, &core_fixtures::E1_BLE))?;
    d.set_item("E1_USB", PyBytes::new(py, &core_fixtures::E1_USB))?;
    d.set_item("C5_SETTINGS", PyBytes::new(py, &core_fixtures::C5_SETTINGS))?;
    Ok(d)
}

/// `c3(output, model, charge_error, set_voltage, set_current) -> bytes`:
/// `core_fixtures::c3_with`.
#[pyfunction]
pub fn c3(
    py: Python<'_>,
    output: u8,
    model: u8,
    charge_error: u16,
    set_voltage: u16,
    set_current: u16,
) -> Bound<'_, PyBytes> {
    PyBytes::new(
        py,
        &core_fixtures::c3_with(output, model, charge_error, set_voltage, set_current),
    )
}

/// The kind named `kind`.
fn kind_of(kind: &str) -> PyResult<Kind> {
    match kind {
        "ble" => Ok(Kind::Ble),
        "hid" => Ok(Kind::Hid),
        _ => Err(PyValueError::new_err(format!(
            "kind must be \"ble\" or \"hid\", got {kind:?}"
        ))),
    }
}

/// `on_air(kind, opcode, payload) -> bytes`: `core_fixtures::on_air`, the
/// on-air bytes of a frame from the supply.
///
/// # Errors
///
/// `ValueError` for a kind other than `ble` and `hid`.
#[pyfunction]
pub fn on_air<'py>(
    py: Python<'py>,
    kind: &str,
    opcode: u8,
    payload: &[u8],
) -> PyResult<Bound<'py, PyBytes>> {
    Ok(PyBytes::new(
        py,
        &core_fixtures::on_air(kind_of(kind)?, opcode, payload),
    ))
}

/// One `SessionEvent` of each variant but `Reading`, both prompt kinds
/// included, with the values UT-PY-005 lists.
///
/// # Errors
///
/// A text for a fixture that does not parse (it always does).
pub fn sample() -> Result<Vec<SessionEvent>, String> {
    let raw = telemetry::parse_payload(&core_fixtures::C3_CAPTURE).map_err(|e| e.to_string())?;
    let at = tokio::time::Instant::now();
    let wall = convert::wall(1_790_848_800_000_000_000).map_err(|_| "bad time".to_string())?;
    let since = convert::wall(1_790_845_200_000_000_000).map_err(|_| "bad time".to_string())?;
    let reading = TimedReading {
        at,
        wall,
        reading: Reading::from_raw(&raw),
    };
    let c5 = core_fixtures::on_air(Kind::Ble, settings::REPLY, &core_fixtures::C5_SETTINGS);
    let frame = ble::decode(&c5, BleRoute::Af01).map_err(|e| e.to_string())?;
    let parsed = settings::parse(&frame).map_err(|e| e.to_string())?;
    Ok(vec![
        SessionEvent::FaultsChanged {
            faults: Faults(0x0821),
            reading,
        },
        SessionEvent::SettingsChanged(parsed),
        SessionEvent::BindResult { recognised: false },
        SessionEvent::RemoteControl(RemoteState::Granted),
        SessionEvent::Prompt {
            kind: PromptKind::ConfirmConnection,
            bound_s: 30,
            text: texts::CONFIRM_CONNECTION,
        },
        SessionEvent::Prompt {
            kind: PromptKind::AllowRemoteControl,
            bound_s: 70,
            text: texts::ALLOW_REMOTE_CONTROL,
        },
        SessionEvent::SetpointsChanged {
            set_volts: 1.5,
            set_amps: 1.0,
            expected_volts: 1.7,
            expected_amps: 1.0,
        },
        SessionEvent::UncleanExitWarning {
            since,
            text: "u".to_string(),
        },
        SessionEvent::LinkLost {
            text: "t".to_string(),
        },
        SessionEvent::Reconnected,
        SessionEvent::ReconnectGaveUp {
            text: "g".to_string(),
        },
    ])
}

/// `sample_events() -> list[EventTuple]`: [`sample`] through
/// `convert::event`, numbered from 1.
///
/// # Errors
///
/// `ValueError` if a fixture does not parse, or a Python error from the
/// conversion.
#[pyfunction]
pub fn sample_events(py: Python<'_>) -> PyResult<Vec<Bound<'_, PyTuple>>> {
    let events = sample().map_err(PyValueError::new_err)?;
    events
        .iter()
        .zip(1u64..)
        .map(|(event, seq)| convert::event(py, seq, event))
        .collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Test: UT-PY-005 (a), in Rust: one event of each variant but
    /// `Reading`, in order
    #[test]
    fn sample_has_every_kind_in_order() {
        let kinds: Vec<&str> = sample().unwrap().iter().map(convert::event_kind).collect();
        assert_eq!(
            kinds,
            [
                "faults_changed",
                "settings_changed",
                "bind_result",
                "remote_control",
                "prompt",
                "prompt",
                "setpoints_changed",
                "unclean_exit_warning",
                "link_lost",
                "reconnected",
                "reconnect_gave_up",
            ]
        );
    }

    /// Test: UT-PY-019 (a), in Rust: the attempts of the connector
    #[tokio::test]
    async fn the_connector_follows_the_attempts() {
        let list = Arc::new(MockList::new());
        let connector = connector(
            vec![
                Attempt::Error("boom".to_string()),
                Attempt::NotFound,
                Attempt::Script(Kind::Ble, Script::default()),
            ],
            "m".to_string(),
            Arc::clone(&list),
        );
        assert_eq!(
            connector.connect("m").await.err(),
            Some(Error::Transport {
                message: "boom".to_string()
            })
        );
        assert_eq!(
            connector.connect("m").await.err(),
            Some(discovery::not_found())
        );
        assert!(connector.connect("m").await.is_ok());
        assert_eq!(list.handles().len(), 1);
        assert_eq!(
            connector.connect("m").await.err(),
            Some(Error::Transport {
                message: "no more mock scripts".to_string()
            })
        );
        assert_eq!(route_name(Route::Hid), "hid");
    }
}
