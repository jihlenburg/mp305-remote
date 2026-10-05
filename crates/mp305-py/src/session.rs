//! Implements: DD-PY-005, DD-PY-008 (the session's safety calls),
//! DD-PY-009, DD-PY-031, DD-PY-032, DD-PY-034 (`Session.from_mock`)
//!
//! The native `Session`: one method per call of `mp305_core::session`,
//! plus the feed access the Python class builds on. It owns `Arc`s of the
//! core session and of the feed and stores no Python object, so no
//! reference cycle passes through it; the dispatcher is an argument of each
//! blocking call. Dropping it aborts the forwarder and drops its `Arc` of
//! the core session, which ends the session task unless a safety task still
//! holds one.

use std::path::PathBuf;
use std::sync::Arc;
use std::time::Instant;

use mp305_core::error::Error;
use mp305_core::protocol::ops::bind::HostId;
use mp305_core::protocol::units::Limits;
use mp305_core::session::doubles::MemoryMarkers;
use mp305_core::session::{Connector, Markers, Options, Session as CoreSession, SessionEvents};
use mp305_core::store::Store;
use pyo3::exceptions::PyRuntimeError;
use pyo3::prelude::*;
use pyo3::types::{PyBytes, PyTuple};
use tokio::task::JoinHandle;

use crate::convert;
use crate::discover;
use crate::errors;
use crate::feed::Feed;
use crate::mock::{self, MockHandles, MockList, MOCK_HOST_ID};
use crate::runtime;
use crate::safety;
use crate::wait;

/// The log target of the native session.
const LOG_TARGET: &str = "mp305_py::session";

/// The default state directory of the user: the core's rule
/// (`mp305_core::store::default_dir`), which the app uses too, so one user
/// has one host ID and one marker directory.
///
/// # Errors
///
/// A text when the OS gives no home directory.
pub fn default_dir() -> Result<PathBuf, &'static str> {
    mp305_core::store::default_dir().ok_or("no home directory for the state directory")
}

/// `default_state_dir() -> pathlib.Path`.
///
/// # Errors
///
/// `Mp305Error("no home directory for the state directory")`.
#[pyfunction]
pub fn default_state_dir(py: Python<'_>) -> PyResult<PathBuf> {
    default_dir().map_err(|text| errors::mp305_error(py, text))
}

/// The state directory `state_dir`, or the default.
fn state_dir(py: Python<'_>, state_dir: Option<PathBuf>) -> PyResult<PathBuf> {
    match state_dir {
        Some(dir) => Ok(dir),
        None => default_state_dir(py),
    }
}

/// `host_id(state_dir) -> bytes`: reads or creates the host ID of the store
/// in `state_dir` (or the default) with the GIL released. It does not pump,
/// so the store's log records reach `logging` through the delivery thread.
///
/// # Errors
///
/// `Mp305Error` with the store's text.
#[pyfunction]
#[pyo3(signature = (state_dir))]
pub fn host_id(py: Python<'_>, state_dir: Option<PathBuf>) -> PyResult<Bound<'_, PyBytes>> {
    let dir = self::state_dir(py, state_dir)?;
    let store = Store::new(dir);
    let id = py
        .detach(|| store.host_id())
        .map_err(|e| errors::to_py(py, &e))?;
    Ok(PyBytes::new(py, id.as_bytes()))
}

/// What a native session holds; dropped at once, or leaked in a forked
/// child.
#[derive(Debug)]
struct Inner {
    /// The core session, shared with running safety tasks.
    core: Arc<CoreSession>,
    /// The feed, shared with the forwarder.
    feed: Arc<Feed>,
    /// The forwarder, aborted on drop.
    forwarder: JoinHandle<()>,
    /// The handle list of a mock session, kept for the life of the session.
    _mock: Option<Arc<MockList>>,
    /// The identifier.
    identifier: String,
    /// When the native session was created.
    created: Instant,
}

/// The native session (`mp305._native.Session`).
#[pyclass(frozen, module = "mp305._native")]
#[derive(Debug)]
pub struct Session {
    /// The state; `None` only while being dropped.
    inner: Option<Inner>,
}

impl Drop for Session {
    fn drop(&mut self) {
        let Some(inner) = self.inner.take() else {
            return;
        };
        if runtime::forked() {
            // The descriptors and tasks belong to the parent (DD-PY-009).
            core::mem::forget(inner);
            return;
        }
        inner.forwarder.abort();
        log::debug!(
            target: LOG_TARGET,
            "released {} after {} s",
            inner.identifier,
            inner.created.elapsed().as_secs()
        );
    }
}

/// The user's limits.
fn limits(max_voltage: Option<f64>, max_current: Option<f64>) -> Limits {
    Limits {
        max_volts: max_voltage,
        max_amps: max_current,
    }
}

impl Session {
    /// A native session over `core`, with its feed and the forwarder
    /// spawned. Needs the runtime entered.
    fn start(
        core: CoreSession,
        events: SessionEvents,
        mock: Option<Arc<MockList>>,
        identifier: String,
    ) -> Session {
        let (feed, forwarder) = Feed::start(events);
        Session {
            inner: Some(Inner {
                core: Arc::new(core),
                feed,
                forwarder,
                _mock: mock,
                identifier,
                created: Instant::now(),
            }),
        }
    }

    /// The state.
    fn inner(&self) -> PyResult<&Inner> {
        self.inner
            .as_ref()
            .ok_or_else(|| PyRuntimeError::new_err("the native session was released"))
    }

    /// Runs a control call of the core session as a blocking call.
    fn control<'py, F, Fut>(
        &self,
        py: Python<'py>,
        dispatch: Option<&Bound<'py, PyAny>>,
        call: F,
    ) -> PyResult<()>
    where
        F: FnOnce(Arc<CoreSession>) -> Fut,
        Fut: core::future::Future<Output = Result<(), Error>> + Send,
    {
        let _rt = runtime::enter()?;
        let inner = self.inner()?;
        let pump = dispatch.map(|d| (&*inner.feed, d));
        wait::block(py, pump, call(Arc::clone(&inner.core)))
    }
}

#[pymethods]
impl Session {
    /// `Session.connect(identifier, state_dir, reconnect, max_voltage,
    /// max_current)`: a blocking call without dispatcher that reads the
    /// host ID, obtains the process-wide `Discovery`, opens the core session
    /// and returns without waiting for the connect flow.
    #[staticmethod]
    #[pyo3(signature = (identifier, state_dir, reconnect, max_voltage, max_current))]
    fn connect(
        py: Python<'_>,
        identifier: String,
        state_dir: Option<PathBuf>,
        reconnect: bool,
        max_voltage: Option<f64>,
        max_current: Option<f64>,
    ) -> PyResult<Session> {
        let _rt = runtime::enter()?;
        let store = Arc::new(Store::new(self::state_dir(py, state_dir)?));
        let options = Options::new(reconnect, limits(max_voltage, max_current));
        let id = identifier.clone();
        let (core, events) = wait::block(py, None, async move {
            let host_id = store.host_id()?;
            let discovery = discover::discovery().await?;
            CoreSession::connect(
                discovery as Arc<dyn Connector>,
                &id,
                host_id,
                store as Arc<dyn Markers>,
                options,
            )
        })?;
        Ok(Session::start(core, events, None, identifier))
    }

    /// `Session.from_mock(scripts, state_dir, reconnect, max_voltage,
    /// max_current, identifier, handles)`: the scripts are converted first;
    /// without a state directory the session uses `MemoryMarkers` and
    /// `MOCK_HOST_ID` and touches no file. No wait.
    #[staticmethod]
    #[pyo3(signature = (scripts, state_dir, reconnect, max_voltage, max_current, identifier, handles))]
    #[allow(clippy::too_many_arguments)]
    fn from_mock(
        py: Python<'_>,
        scripts: Vec<Bound<'_, PyAny>>,
        state_dir: Option<PathBuf>,
        reconnect: bool,
        max_voltage: Option<f64>,
        max_current: Option<f64>,
        identifier: String,
        handles: &Bound<'_, MockHandles>,
    ) -> PyResult<Session> {
        let _rt = runtime::enter()?;
        let attempts = mock::scripts_from_py(&scripts)?;
        let list = Arc::clone(&handles.get().list);
        let connector = mock::connector(attempts, identifier.clone(), Arc::clone(&list));
        let (markers, host_id): (Arc<dyn Markers>, HostId) = match state_dir {
            None => {
                let id = HostId::new(MOCK_HOST_ID)
                    .map_err(|r| errors::to_py(py, &Error::Protocol(r)))?;
                (Arc::new(MemoryMarkers::new()), id)
            }
            Some(dir) => {
                let store = Store::new(dir);
                let id = py
                    .detach(|| store.host_id())
                    .map_err(|e| errors::to_py(py, &e))?;
                (Arc::new(store), id)
            }
        };
        let options = Options::new(reconnect, limits(max_voltage, max_current));
        let (core, events) =
            CoreSession::connect(connector, &identifier, host_id, markers, options)
                .map_err(|e| errors::to_py(py, &e))?;
        Ok(Session::start(core, events, Some(list), identifier))
    }

    /// `ready(dispatch) -> InfoTuple`: waits for the connect flow, then
    /// flushes the feed, so every event emitted before it resolved has been
    /// dispatched when it returns.
    #[pyo3(signature = (dispatch))]
    fn ready<'py>(
        &self,
        py: Python<'py>,
        dispatch: Option<Bound<'py, PyAny>>,
    ) -> PyResult<Bound<'py, PyTuple>> {
        let _rt = runtime::enter()?;
        let inner = self.inner()?;
        let pump = dispatch.as_ref().map(|d| (&*inner.feed, d));
        let (core, feed) = (Arc::clone(&inner.core), Arc::clone(&inner.feed));
        let info = wait::block(py, pump, async move {
            let info = core.ready().await?;
            feed.flush().await;
            Ok(info)
        })?;
        convert::info(py, &info)
    }

    /// `set_voltage(volts, dispatch)`.
    #[pyo3(signature = (volts, dispatch))]
    fn set_voltage(
        &self,
        py: Python<'_>,
        volts: f64,
        dispatch: Option<Bound<'_, PyAny>>,
    ) -> PyResult<()> {
        self.control(py, dispatch.as_ref(), |s| async move {
            s.set_voltage(volts).await
        })
    }

    /// `set_current_limit(amps, dispatch)`.
    #[pyo3(signature = (amps, dispatch))]
    fn set_current_limit(
        &self,
        py: Python<'_>,
        amps: f64,
        dispatch: Option<Bound<'_, PyAny>>,
    ) -> PyResult<()> {
        self.control(py, dispatch.as_ref(), |s| async move {
            s.set_current_limit(amps).await
        })
    }

    /// `request_remote_control(dispatch)`.
    #[pyo3(signature = (dispatch))]
    fn request_remote_control(
        &self,
        py: Python<'_>,
        dispatch: Option<Bound<'_, PyAny>>,
    ) -> PyResult<()> {
        self.control(py, dispatch.as_ref(), |s| async move {
            s.request_remote_control().await
        })
    }

    /// `release_remote_control(dispatch)`.
    #[pyo3(signature = (dispatch))]
    fn release_remote_control(
        &self,
        py: Python<'_>,
        dispatch: Option<Bound<'_, PyAny>>,
    ) -> PyResult<()> {
        self.control(py, dispatch.as_ref(), |s| async move {
            s.release_remote_control().await
        })
    }

    /// `output_on(dispatch)`.
    #[pyo3(signature = (dispatch))]
    fn output_on(&self, py: Python<'_>, dispatch: Option<Bound<'_, PyAny>>) -> PyResult<()> {
        self.control(
            py,
            dispatch.as_ref(),
            |s| async move { s.output_on().await },
        )
    }

    /// `output_off(dispatch)`: a safety call. The output-off runs as a task
    /// on the runtime; an interrupt or a dispatcher exception ends only the
    /// wait.
    #[pyo3(signature = (dispatch))]
    fn output_off(&self, py: Python<'_>, dispatch: Option<Bound<'_, PyAny>>) -> PyResult<()> {
        let _rt = runtime::enter()?;
        let inner = self.inner()?;
        let core = Arc::clone(&inner.core);
        let name = format!("output-off {}", inner.identifier);
        let rx = safety::spawn(name.clone(), async move { core.output_off().await });
        let pump = dispatch.as_ref().map(|d| (&*inner.feed, d));
        wait::block(py, pump, async move { safety::result(rx, &name).await })
    }

    /// `close(output_off, dispatch)`: a safety call. The close runs as a task
    /// on the runtime; then the feed is flushed. An interrupt or a
    /// dispatcher exception ends only the wait; a later `close` gets the
    /// first close's result from the core.
    #[pyo3(signature = (output_off, dispatch))]
    fn close(
        &self,
        py: Python<'_>,
        output_off: bool,
        dispatch: Option<Bound<'_, PyAny>>,
    ) -> PyResult<()> {
        let _rt = runtime::enter()?;
        let inner = self.inner()?;
        let core = Arc::clone(&inner.core);
        let feed = Arc::clone(&inner.feed);
        let name = format!("close {}", inner.identifier);
        let rx = safety::spawn(name.clone(), async move { core.close(output_off).await });
        let pump = dispatch.as_ref().map(|d| (&*inner.feed, d));
        wait::block(py, pump, async move {
            let result = safety::result(rx, &name).await;
            feed.flush().await;
            result
        })
    }

    /// `close_start(output_off)`: starts the close as a safety task and
    /// returns at once; its outcome is logged.
    fn close_start(&self, output_off: bool) -> PyResult<()> {
        let _rt = runtime::enter()?;
        let inner = self.inner()?;
        let core = Arc::clone(&inner.core);
        let name = format!("close {}", inner.identifier);
        drop(safety::spawn(
            name,
            async move { core.close(output_off).await },
        ));
        Ok(())
    }

    /// `wait_feed(after, wait_s) -> int`: waits until the newest sequence
    /// number is above `after`, the feed ended or `wait_s` passed; returns
    /// the newest sequence number.
    fn wait_feed(&self, py: Python<'_>, after: u64, wait_s: f64) -> PyResult<u64> {
        let _rt = runtime::enter()?;
        let inner = self.inner()?;
        let wait = convert::seconds_arg("wait_s", wait_s)?;
        let feed = Arc::clone(&inner.feed);
        wait::block(py, None, async move { Ok(feed.wait(after, wait).await) })
    }

    /// `flush()`: waits until everything the core queued is in the feed.
    fn flush(&self, py: Python<'_>) -> PyResult<()> {
        let _rt = runtime::enter()?;
        let feed = Arc::clone(&self.inner()?.feed);
        wait::block(py, None, async move {
            feed.flush().await;
            Ok(())
        })
    }

    /// `pump(dispatch)`: the pump of a blocking call without a wait.
    #[pyo3(signature = (dispatch))]
    fn pump(&self, py: Python<'_>, dispatch: Option<Bound<'_, PyAny>>) -> PyResult<()> {
        let _rt = runtime::enter()?;
        let inner = self.inner()?;
        wait::pump(py, Some(&inner.feed), dispatch.as_ref())
    }

    /// `info() -> Optional[InfoTuple]`.
    fn info<'py>(&self, py: Python<'py>) -> PyResult<Option<Bound<'py, PyTuple>>> {
        let _rt = runtime::enter()?;
        self.inner()?
            .core
            .info()
            .map(|i| convert::info(py, &i))
            .transpose()
    }

    /// `latest_reading() -> Optional[ReadingTuple]`: the session's one
    /// current reading.
    fn latest_reading<'py>(&self, py: Python<'py>) -> PyResult<Option<Bound<'py, PyTuple>>> {
        let _rt = runtime::enter()?;
        self.inner()?
            .core
            .latest_reading()
            .map(|r| convert::reading(py, &r))
            .transpose()
    }

    /// `link_state() -> str`.
    fn link_state(&self) -> PyResult<String> {
        let _rt = runtime::enter()?;
        Ok(self.inner()?.core.link_state().to_string())
    }

    /// `remote_state() -> str`.
    fn remote_state(&self) -> PyResult<String> {
        let _rt = runtime::enter()?;
        Ok(self.inner()?.core.remote_state().to_string())
    }

    /// `identifier() -> str`.
    fn identifier(&self) -> PyResult<String> {
        let _rt = runtime::enter()?;
        Ok(self.inner()?.core.identifier().to_string())
    }

    /// `transport() -> Optional[str]`: `ble` or `hid` once the connector
    /// returned.
    fn transport(&self) -> PyResult<Option<String>> {
        let _rt = runtime::enter()?;
        Ok(self.inner()?.core.transport().map(|k| k.to_string()))
    }

    /// `counters() -> Optional[CountersTuple]`.
    fn counters<'py>(&self, py: Python<'py>) -> PyResult<Option<Bound<'py, PyTuple>>> {
        let _rt = runtime::enter()?;
        self.inner()?
            .core
            .counters()
            .map(|c| convert::counters(py, &c))
            .transpose()
    }

    /// `dropped_readings() -> int`: the core's count.
    fn dropped_readings(&self) -> PyResult<u64> {
        let _rt = runtime::enter()?;
        Ok(self.inner()?.core.dropped_readings())
    }

    /// `feed_seq() -> int`: the newest sequence number.
    fn feed_seq(&self) -> PyResult<u64> {
        let _rt = runtime::enter()?;
        Ok(self.inner()?.feed.seq())
    }

    /// `newest_reading() -> int`: the newest reading number.
    fn newest_reading(&self) -> PyResult<u64> {
        let _rt = runtime::enter()?;
        Ok(self.inner()?.feed.newest_reading())
    }

    /// `readings_after(cursor, limit) -> (readings, new_cursor, skipped)`.
    fn readings_after<'py>(
        &self,
        py: Python<'py>,
        cursor: u64,
        limit: usize,
    ) -> PyResult<(Vec<Bound<'py, PyTuple>>, u64, u64)> {
        let _rt = runtime::enter()?;
        let (readings, cursor, skipped) = self.inner()?.feed.readings_after(cursor, limit);
        let tuples = readings
            .iter()
            .map(|r| convert::reading(py, r))
            .collect::<PyResult<Vec<_>>>()?;
        Ok((tuples, cursor, skipped))
    }

    /// `events_take(limit) -> list[EventTuple]`: the events not yet
    /// returned, in order.
    fn events_take<'py>(
        &self,
        py: Python<'py>,
        limit: usize,
    ) -> PyResult<Vec<Bound<'py, PyTuple>>> {
        let _rt = runtime::enter()?;
        self.inner()?
            .feed
            .events_take(limit)
            .iter()
            .map(|(seq, event)| convert::event(py, *seq, event))
            .collect()
    }

    /// `events_overwritten() -> int`.
    fn events_overwritten(&self) -> PyResult<u64> {
        let _rt = runtime::enter()?;
        Ok(self.inner()?.feed.events_overwritten())
    }

    /// `loss_text() -> Optional[str]`.
    fn loss_text(&self) -> PyResult<Option<String>> {
        let _rt = runtime::enter()?;
        Ok(self.inner()?.feed.loss_text())
    }

    /// `set_reconnect(on)`.
    fn set_reconnect(&self, on: bool) -> PyResult<()> {
        let _rt = runtime::enter()?;
        self.inner()?.core.set_reconnect(on);
        Ok(())
    }

    /// `set_limits(max_voltage, max_current)`: replaces both limits.
    #[pyo3(signature = (max_voltage, max_current))]
    fn set_limits(
        &self,
        py: Python<'_>,
        max_voltage: Option<f64>,
        max_current: Option<f64>,
    ) -> PyResult<()> {
        let _rt = runtime::enter()?;
        self.inner()?
            .core
            .set_limits(limits(max_voltage, max_current))
            .map_err(|e| errors::to_py(py, &e))
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Test: UT-PY-010, in Rust: the default state directory
    #[test]
    fn the_default_state_dir_is_absolute_and_named_mp305() {
        let dir = default_dir().unwrap();
        assert!(dir.is_absolute());
        assert!(dir.components().any(|c| c.as_os_str() == "mp305"));
    }
}
