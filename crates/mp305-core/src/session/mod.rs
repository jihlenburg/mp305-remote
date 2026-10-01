//! Implements: DD-SESS-001, DD-SESS-002, DD-SESS-003, DD-SESS-004,
//! DD-SESS-052.
//!
//! The session: the device API the app and the Python library use. It owns
//! one `link::Link` at a time, runs the link state machine (connect, bind,
//! ready) and the remote-control state machine, builds and guards every
//! `0xC8`, turns readings and device frames into [`SessionEvent`]s, keeps
//! the unclean-exit marker current, handles link loss and reconnection, and
//! allows one session per identifier in the process.
//!
//! The handle [`Session`] talks to a task that owns the link (`task`). Every
//! frame is built through `protocol::ops` and sent through `link`, so the
//! allowlist and the one-request rule hold here by construction. How an
//! identifier becomes a transport ([`Connector`]) and where the marker lives
//! ([`Markers`]) come from outside.

#[cfg(any(test, feature = "mock"))]
pub mod doubles;
pub mod state;
mod task;
#[cfg(test)]
mod tests;
pub mod texts;

use core::fmt;
use std::collections::BTreeSet;
use std::sync::atomic::{AtomicBool, AtomicU64, Ordering};
use std::sync::{Arc, Mutex, MutexGuard, PoisonError};
use std::time::SystemTime;

use futures::future::BoxFuture;
use tokio::runtime::Handle;
use tokio::sync::{mpsc, oneshot, watch};
use tokio::task::AbortHandle;
use tokio::time::Instant;

use crate::error::Error;
use crate::link::Counters;
use crate::protocol::ops::bind::HostId;
use crate::protocol::ops::info::Info;
use crate::protocol::ops::settings::Settings;
use crate::protocol::ops::telemetry::{Faults, Reading};
use crate::protocol::units::Limits;
use crate::transport::description::Kind;
use crate::transport::guarded::Guarded;
use crate::transport::AnyTransport;

/// The log target of the session.
pub const LOG_TARGET: &str = "mp305_core::session";

/// The capacity of the reading channel; readings beyond it are dropped and
/// counted (DD-SESS-004).
const READING_CAPACITY: usize = 1024;

/// How an identifier becomes a guarded transport: discovery implements it
/// for real devices, `doubles::MockConnector` (under the `mock` feature) over the scripted mock.
/// Called once at [`Session::connect`] and once per reconnection attempt.
pub trait Connector: Send + Sync + 'static {
    /// Connects to the supply with `identifier`.
    ///
    /// # Errors
    ///
    /// Whatever the backend reports; the session ends its connect flow (or
    /// the reconnection attempt) with it.
    fn connect<'a>(
        &'a self,
        identifier: &'a str,
    ) -> BoxFuture<'a, Result<Guarded<AnyTransport>, Error>>;
}

/// Where the unclean-exit marker lives: the store module implements it,
/// `doubles::MemoryMarkers` is the test double. The calls are synchronous
/// and run on the session task; a failing call is logged at WARN and never
/// fails the session call that caused it.
pub trait Markers: Send + Sync + 'static {
    /// The time of the marker for `identifier`, if one is present.
    ///
    /// # Errors
    ///
    /// The store's error.
    fn present(&self, identifier: &str) -> Result<Option<SystemTime>, Error>;

    /// Writes the marker for `identifier` with the time `at`.
    ///
    /// # Errors
    ///
    /// The store's error.
    fn set(&self, identifier: &str, at: SystemTime) -> Result<(), Error>;

    /// Removes the marker for `identifier`.
    ///
    /// # Errors
    ///
    /// The store's error.
    fn clear(&self, identifier: &str) -> Result<(), Error>;
}

/// The options of a session.
///
/// Build it with [`Options::new`], or from [`Options::default`] (no
/// reconnection, no user limits) with the public fields assigned; a struct
/// literal does not compile outside this module, since the wall-clock
/// origin for tests is a private field, set through
/// `Options::with_wall_origin` under the `mock` feature.
#[derive(Clone, Copy, Debug, Default, PartialEq)]
pub struct Options {
    /// Whether a lost link is reconnected (AR-029); can be changed later
    /// with [`Session::set_reconnect`].
    pub reconnect: bool,
    /// The user's limits (UR-007), applied to every setpoint; can be
    /// changed later with [`Session::set_limits`].
    pub limits: Limits,
    /// A fixed wall-clock origin for the reading times, for tests.
    wall_origin: Option<SystemTime>,
}

impl Options {
    /// Options with reconnection on or off and the user's limits; the
    /// limits are checked when the session is opened (DD-SESS-002).
    #[must_use]
    pub fn new(reconnect: bool, limits: Limits) -> Self {
        Self {
            reconnect,
            limits,
            wall_origin: None,
        }
    }

    /// Fixes the wall-clock time that corresponds to the start of the
    /// session task, so that a paused test clock gives deterministic
    /// wall-clock times (DD-SESS-004).
    #[cfg(any(test, feature = "mock"))]
    #[must_use]
    pub fn with_wall_origin(mut self, origin: SystemTime) -> Self {
        self.wall_origin = Some(origin);
        self
    }
}

/// The link state of DD-SESS-013.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum LinkState {
    /// The connector is connecting.
    Connecting,
    /// The transport is connected; nothing sent yet.
    Connected,
    /// The bind is in progress (Bluetooth).
    Binding,
    /// The supply allowed the host; info and the first reading follow.
    Allowed,
    /// Control is possible.
    Ready,
    /// The supply denied the connection.
    Denied,
    /// The link was lost, or the connect flow failed.
    Lost,
    /// A reconnection is scheduled or running.
    Reconnecting,
    /// The host closed the session.
    Closed,
}

impl fmt::Display for LinkState {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(match self {
            LinkState::Connecting => "connecting",
            LinkState::Connected => "connected",
            LinkState::Binding => "binding",
            LinkState::Allowed => "allowed",
            LinkState::Ready => "ready",
            LinkState::Denied => "denied",
            LinkState::Lost => "lost",
            LinkState::Reconnecting => "reconnecting",
            LinkState::Closed => "closed",
        })
    }
}

/// The remote-control state of DD-SESS-022.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum RemoteState {
    /// Not requested on this connection.
    None,
    /// A request is pending.
    Requested,
    /// The supply granted remote control.
    Granted,
    /// The supply denied it, or its prompt timed out.
    Denied,
    /// The grant was lost (a status 1, or the link was lost).
    Lost,
}

impl fmt::Display for RemoteState {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(match self {
            RemoteState::None => "none",
            RemoteState::Requested => "requested",
            RemoteState::Granted => "granted",
            RemoteState::Denied => "denied",
            RemoteState::Lost => "lost",
        })
    }
}

/// Which prompt the supply shows.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum PromptKind {
    /// Confirm the connection (the prompt bind, 30 s).
    ConfirmConnection,
    /// Allow remote control (the Bluetooth remote request, 70 s).
    AllowRemoteControl,
}

/// A reading with its arrival stamp and wall-clock time.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct TimedReading {
    /// When the transport received it, on the Tokio clock.
    pub at: Instant,
    /// The wall-clock time derived from `at` (DD-SESS-004).
    pub wall: SystemTime,
    /// The SI view, which keeps the raw reading.
    pub reading: Reading,
}

/// What the session tells the product (AR-028).
#[derive(Clone, Debug, PartialEq)]
pub enum SessionEvent {
    /// A reading arrived.
    Reading(TimedReading),
    /// The set of active faults changed; `reading` shows the change.
    FaultsChanged {
        /// The active faults.
        faults: Faults,
        /// The reading that shows them.
        reading: TimedReading,
    },
    /// A setting changed on the front panel.
    SettingsChanged(Settings),
    /// The bind succeeded; `recognised` when the fast bind did.
    BindResult {
        /// Whether the supply remembered this host.
        recognised: bool,
    },
    /// The remote-control state changed.
    RemoteControl(RemoteState),
    /// The supply shows a prompt the user must answer.
    Prompt {
        /// Which prompt.
        kind: PromptKind,
        /// How long the prompt waits, in seconds.
        bound_s: u32,
        /// The text to show.
        text: &'static str,
    },
    /// After a failed command, a setpoint differs from what was expected.
    SetpointsChanged {
        /// The voltage setpoint the supply reports, in V.
        set_volts: f64,
        /// The current limit the supply reports, in A.
        set_amps: f64,
        /// The voltage setpoint expected, in V.
        expected_volts: f64,
        /// The current limit expected, in A.
        expected_amps: f64,
    },
    /// A previous session may have left the output on (SR-046).
    UncleanExitWarning {
        /// When the marker was written.
        since: SystemTime,
        /// The warning text.
        text: String,
    },
    /// The link was lost.
    LinkLost {
        /// What happened and what it means for the output.
        text: String,
    },
    /// A reconnection succeeded.
    Reconnected,
    /// The reconnection gave up.
    ReconnectGaveUp {
        /// Why.
        text: String,
    },
}

/// The receiver of [`SessionEvent`]s. Events travel on two channels the
/// task never waits on: an unbounded one for every event but readings, and
/// a bounded one for readings, which drops readings when full.
#[derive(Debug)]
pub struct SessionEvents {
    /// Every event but `Reading`.
    events: mpsc::UnboundedReceiver<SessionEvent>,
    /// `Reading` events.
    readings: mpsc::Receiver<SessionEvent>,
}

impl SessionEvents {
    /// The next event; an event other than a reading is taken first when
    /// both channels hold one. `None` after the task ended.
    pub async fn next(&mut self) -> Option<SessionEvent> {
        tokio::select! {
            biased;
            Some(event) = self.events.recv() => Some(event),
            Some(event) = self.readings.recv() => Some(event),
            else => None,
        }
    }

    /// The next event if one is waiting, without waiting.
    #[cfg(test)]
    pub(crate) fn try_next(&mut self) -> Option<SessionEvent> {
        self.events
            .try_recv()
            .ok()
            .or_else(|| self.readings.try_recv().ok())
    }
}

/// What `ready()` reads (DD-SESS-002).
#[derive(Clone, Debug, PartialEq)]
pub(crate) enum ReadyState {
    /// Connecting or reconnecting.
    Pending,
    /// Ready with this info.
    Ready(Info),
    /// The connect flow failed, the link was lost, the reconnection gave
    /// up, or the session was closed.
    Failed(Error),
}

/// A control command.
#[derive(Clone, Copy, Debug, PartialEq)]
pub(crate) enum CommandKind {
    /// Set the voltage, in V.
    SetVoltage(f64),
    /// Set the current limit, in A.
    SetCurrent(f64),
    /// Switch the output on.
    OutputOn,
    /// Request remote control.
    Request,
    /// Release remote control.
    Release,
}

/// A command from the handle with its answer channel and generation.
#[derive(Debug)]
pub(crate) struct Command {
    /// What to do.
    pub(crate) kind: CommandKind,
    /// The user's limits when the call was made.
    pub(crate) limits: Limits,
    /// The generation current when the call was made.
    pub(crate) generation: u64,
    /// Where the answer goes.
    pub(crate) reply: oneshot::Sender<Result<(), Error>>,
}

/// A message on the priority channel.
#[derive(Debug)]
pub(crate) enum Priority {
    /// Switch the output off (DD-SESS-035).
    OutputOff {
        /// The generation current when the call was made.
        generation: u64,
        /// Where the answer goes.
        reply: oneshot::Sender<Result<(), Error>>,
    },
    /// Close the session (DD-SESS-053).
    Close {
        /// Whether to switch the output off first.
        output_off: bool,
        /// Where the answer goes.
        reply: oneshot::Sender<Result<(), Error>>,
    },
}

/// What the queries read: kept by the task behind a mutex.
#[derive(Clone, Debug)]
pub(crate) struct Snapshot {
    /// The info of the current connection.
    pub(crate) info: Option<Info>,
    /// The latest reading.
    pub(crate) reading: Option<TimedReading>,
    /// The link state.
    pub(crate) link_state: LinkState,
    /// The remote-control state.
    pub(crate) remote_state: RemoteState,
    /// The kind, once the connector returned.
    pub(crate) kind: Option<Kind>,
    /// The link's counters as of the task's last turn.
    pub(crate) counters: Option<Counters>,
}

/// What the handle and the task share.
#[derive(Debug)]
pub(crate) struct Shared {
    /// The query state.
    pub(crate) snapshot: Mutex<Snapshot>,
    /// The reconnect flag.
    pub(crate) reconnect: AtomicBool,
    /// The user's limits.
    pub(crate) limits: Mutex<Limits>,
    /// The current generation.
    pub(crate) generation: AtomicU64,
    /// Readings dropped because the reading channel was full.
    pub(crate) dropped_readings: AtomicU64,
    /// The result of the close, once the task finished it; later calls of
    /// `close` get it (DD-SESS-053).
    pub(crate) close_result: Mutex<Option<Result<(), Error>>>,
    /// Test support: every link state the task published and every event it
    /// emitted on the unbounded channel, in order (a watch on the shared
    /// state for UT-SESS-065).
    #[cfg(test)]
    pub(crate) trace: Mutex<Vec<String>>,
}

/// Locks `mutex`, recovering the data of a poisoned lock.
pub(crate) fn lock<T>(mutex: &Mutex<T>) -> MutexGuard<'_, T> {
    mutex.lock().unwrap_or_else(PoisonError::into_inner)
}

/// The identifiers with an open session in this process (AR-030).
static REGISTRY: Mutex<BTreeSet<String>> = Mutex::new(BTreeSet::new());

/// The registry entry of one session; removes the entry when dropped or
/// released.
#[derive(Debug)]
pub(crate) struct Registration {
    /// The identifier, until released.
    identifier: Option<String>,
}

impl Registration {
    /// Inserts `identifier`, or fails when a session to it is open.
    fn register(identifier: &str) -> Result<Self, Error> {
        if !lock(&REGISTRY).insert(identifier.to_string()) {
            return Err(Error::AlreadyOpen {
                identifier: identifier.to_string(),
            });
        }
        Ok(Self {
            identifier: Some(identifier.to_string()),
        })
    }

    /// Removes the entry now.
    pub(crate) fn release(&mut self) {
        if let Some(identifier) = self.identifier.take() {
            lock(&REGISTRY).remove(&identifier);
        }
    }
}

impl Drop for Registration {
    fn drop(&mut self) {
        self.release();
    }
}

/// The handle of a session. Not generic, `Send + Sync`; its methods take
/// `&self`. Dropping it without [`Session::close`] aborts the task, which
/// releases the link, the transport and the registry entry.
#[derive(Debug)]
pub struct Session {
    /// The identifier the session was opened with.
    identifier: String,
    /// Control commands to the task.
    commands: mpsc::UnboundedSender<Command>,
    /// Output-off and close to the task.
    priority: mpsc::UnboundedSender<Priority>,
    /// The ready state.
    ready: watch::Receiver<ReadyState>,
    /// What the queries read.
    shared: Arc<Shared>,
    /// Aborts the task on drop.
    abort: AbortHandle,
}

impl Session {
    /// Opens a session to `identifier` and returns at once; the connect
    /// flow runs in the background and [`Session::ready`] tells how it
    /// ended.
    ///
    /// # Errors
    ///
    /// [`Error::SetpointRange`] when a limit in `options` is NaN, infinite
    /// or negative, [`Error::Transport`] when no Tokio runtime is current,
    /// [`Error::AlreadyOpen`] when a session to `identifier` is open in this
    /// process. Nothing is registered and the connector is not called then.
    pub fn connect(
        connector: Arc<dyn Connector>,
        identifier: &str,
        host_id: HostId,
        markers: Arc<dyn Markers>,
        options: Options,
    ) -> Result<(Session, SessionEvents), Error> {
        state::check_limits(&options.limits)?;
        let runtime = Handle::try_current().map_err(|e| Error::Transport {
            message: format!("no Tokio runtime: {e}"),
        })?;
        let registration = Registration::register(identifier)?;
        let (commands, command_rx) = mpsc::unbounded_channel();
        let (priority, priority_rx) = mpsc::unbounded_channel();
        let (event_tx, events) = mpsc::unbounded_channel();
        let (reading_tx, readings) = mpsc::channel(READING_CAPACITY);
        let (ready_tx, ready) = watch::channel(ReadyState::Pending);
        let shared = Arc::new(Shared {
            snapshot: Mutex::new(Snapshot {
                info: None,
                reading: None,
                link_state: LinkState::Connecting,
                remote_state: RemoteState::None,
                kind: None,
                counters: None,
            }),
            reconnect: AtomicBool::new(options.reconnect),
            limits: Mutex::new(options.limits),
            generation: AtomicU64::new(1),
            dropped_readings: AtomicU64::new(0),
            close_result: Mutex::new(None),
            #[cfg(test)]
            trace: Mutex::new(Vec::new()),
        });
        let task = runtime.spawn(task::run(task::Setup {
            connector,
            identifier: identifier.to_string(),
            host_id,
            markers,
            wall_origin: options.wall_origin,
            shared: Arc::clone(&shared),
            ready: ready_tx,
            events: event_tx,
            readings: reading_tx,
            commands: command_rx,
            priority: priority_rx,
            registration,
        }));
        Ok((
            Session {
                identifier: identifier.to_string(),
                commands,
                priority,
                ready,
                shared,
                abort: task.abort_handle(),
            },
            SessionEvents { events, readings },
        ))
    }

    /// Waits until the session is ready and returns the supply's info, or
    /// the error the connect flow, a loss, the reconnection or the close
    /// ended with. Can be awaited by several callers and again later.
    ///
    /// # Errors
    ///
    /// [`Error::ConnectionDenied`], [`Error::Timeout`],
    /// [`Error::LinkLost`], [`Error::Protocol`], [`Error::Transport`], or
    /// the connector's error.
    pub async fn ready(&self) -> Result<Info, Error> {
        let mut rx = self.ready.clone();
        let waited = rx
            .wait_for(|s| !matches!(s, ReadyState::Pending))
            .await
            .map(|state| state.clone());
        let state = waited.unwrap_or_else(|_| rx.borrow().clone());
        match state {
            ReadyState::Ready(info) => Ok(info),
            ReadyState::Failed(error) => Err(error),
            ReadyState::Pending => Err(closed()),
        }
    }

    /// Sends `kind` to the task with the user's limits and the generation
    /// current now, and awaits the answer.
    async fn call(&self, kind: CommandKind) -> Result<(), Error> {
        let (reply, rx) = oneshot::channel();
        let command = Command {
            kind,
            limits: self.limits(),
            generation: self.shared.generation.load(Ordering::SeqCst),
            reply,
        };
        if self.commands.send(command).is_err() {
            return Err(closed());
        }
        rx.await.unwrap_or_else(|_| Err(closed()))
    }

    /// The user's limits as they are now.
    fn limits(&self) -> Limits {
        *lock(&self.shared.limits)
    }

    /// Sets the voltage setpoint, in V, copying every other field from a
    /// fresh reading; requests remote control first when it is not held.
    ///
    /// # Errors
    ///
    /// [`Error::SetpointRange`] for a value outside the supply's range or
    /// the user's limits, and every error of the guards of DD-SESS-032 and
    /// the outcomes of DD-SESS-033.
    pub async fn set_voltage(&self, volts: f64) -> Result<(), Error> {
        self.call(CommandKind::SetVoltage(volts)).await
    }

    /// Sets the current limit, in A, as [`Session::set_voltage`] does.
    ///
    /// # Errors
    ///
    /// As [`Session::set_voltage`].
    pub async fn set_current_limit(&self, amps: f64) -> Result<(), Error> {
        self.call(CommandKind::SetCurrent(amps)).await
    }

    /// Switches the output on.
    ///
    /// # Errors
    ///
    /// [`Error::FaultActive`] while a fault is active, and the errors of
    /// [`Session::set_voltage`].
    pub async fn output_on(&self) -> Result<(), Error> {
        self.call(CommandKind::OutputOn).await
    }

    /// Switches the output off. Goes ahead of every queued command, which
    /// fails with [`Error::Cancelled`], and requests remote control first
    /// when it is not held.
    ///
    /// # Errors
    ///
    /// [`Error::RemoteControlDenied`], [`Error::RemoteControlLost`],
    /// [`Error::Mode`], [`Error::CommandRejected`], [`Error::Timeout`]
    /// (500 ms), and the link-state errors.
    pub async fn output_off(&self) -> Result<(), Error> {
        let (reply, rx) = oneshot::channel();
        let message = Priority::OutputOff {
            generation: self.shared.generation.load(Ordering::SeqCst),
            reply,
        };
        if self.priority.send(message).is_err() {
            return Err(closed());
        }
        rx.await.unwrap_or_else(|_| Err(closed()))
    }

    /// Requests remote control; `Ok` at once when it is held.
    ///
    /// # Errors
    ///
    /// [`Error::RemoteControlDenied`], [`Error::Mode`], [`Error::Timeout`],
    /// and the link-state errors.
    pub async fn request_remote_control(&self) -> Result<(), Error> {
        self.call(CommandKind::Request).await
    }

    /// Releases remote control; `Ok` at once when it was never requested.
    ///
    /// # Errors
    ///
    /// [`Error::Mode`], [`Error::RemoteControlLost`],
    /// [`Error::CommandRejected`], [`Error::Timeout`], and the link-state
    /// errors.
    pub async fn release_remote_control(&self) -> Result<(), Error> {
        self.call(CommandKind::Release).await
    }

    /// Closes the session (DD-SESS-053): switches the output off when
    /// `output_off` is true and a fresh reading shows it on (or a command
    /// that may have been applied was cancelled), releases remote control,
    /// clears the marker unless the output could not be confirmed off, and
    /// closes the link. A second call gets the first one's result, except
    /// that `close(true)` while a `close(false)` runs is refused.
    ///
    /// # Errors
    ///
    /// The first error met on the way; the session is closed in any case.
    /// [`Error::Cancelled`] for a `close(true)` while a `close(false)` runs.
    /// [`Error::LinkLost`] naming the ended task when the task ended
    /// without closing the session, so that nothing it skipped is
    /// reported as done.
    pub async fn close(&self, output_off: bool) -> Result<(), Error> {
        let (reply, rx) = oneshot::channel();
        if self
            .priority
            .send(Priority::Close { output_off, reply })
            .is_err()
        {
            return self.close_result();
        }
        // The task answers every close it takes; a reply dropped unanswered
        // means it ended, after a close or without one.
        match rx.await {
            Ok(result) => result,
            Err(_) => self.close_result(),
        }
    }

    /// The result of the close the task finished, or the error of a task
    /// that ended without closing the session.
    fn close_result(&self) -> Result<(), Error> {
        lock(&self.shared.close_result)
            .clone()
            .unwrap_or_else(|| Err(task_ended()))
    }

    /// The info of the current connection.
    #[must_use]
    pub fn info(&self) -> Option<Info> {
        lock(&self.shared.snapshot).info.clone()
    }

    /// The latest reading.
    #[must_use]
    pub fn latest_reading(&self) -> Option<TimedReading> {
        lock(&self.shared.snapshot).reading
    }

    /// The link state.
    #[must_use]
    pub fn link_state(&self) -> LinkState {
        lock(&self.shared.snapshot).link_state
    }

    /// The remote-control state.
    #[must_use]
    pub fn remote_state(&self) -> RemoteState {
        lock(&self.shared.snapshot).remote_state
    }

    /// The identifier the session was opened with.
    #[must_use]
    pub fn identifier(&self) -> &str {
        &self.identifier
    }

    /// The transport kind, once the connector returned.
    #[must_use]
    pub fn transport(&self) -> Option<Kind> {
        lock(&self.shared.snapshot).kind
    }

    /// The link's counters, once a link exists.
    #[must_use]
    pub fn counters(&self) -> Option<Counters> {
        lock(&self.shared.snapshot).counters
    }

    /// Readings dropped because nobody drained the events.
    #[must_use]
    pub fn dropped_readings(&self) -> u64 {
        self.shared.dropped_readings.load(Ordering::SeqCst)
    }

    /// Switches reconnection on or off; read at the moment of a loss and
    /// between attempts.
    pub fn set_reconnect(&self, on: bool) {
        self.shared.reconnect.store(on, Ordering::SeqCst);
    }

    /// Sets the user's limits for later calls, after the check of
    /// [`Session::connect`].
    ///
    /// # Errors
    ///
    /// [`Error::SetpointRange`] naming a limit that is NaN, infinite or
    /// negative; the limits stay as they were.
    pub fn set_limits(&self, limits: Limits) -> Result<(), Error> {
        state::check_limits(&limits)?;
        *lock(&self.shared.limits) = limits;
        Ok(())
    }
}

impl Drop for Session {
    fn drop(&mut self) {
        self.abort.abort();
    }
}

/// The error of a call made after the session was closed.
fn closed() -> Error {
    Error::LinkLost {
        text: texts::CLOSED_BY_HOST.to_string(),
    }
}

/// The text of [`task_ended`].
const TASK_ENDED: &str = "the session task ended";

/// The error of a close whose task ended without closing the session.
fn task_ended() -> Error {
    Error::LinkLost {
        text: TASK_ENDED.to_string(),
    }
}
