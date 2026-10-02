//! Implements: DD-APP-001, DD-APP-002, DD-APP-003, DD-APP-004 (the
//! recorder's place in the loop), DD-APP-005, DD-APP-006, DD-APP-008.
//!
//! The worker: one task on the Tokio runtime that owns the session and does
//! all device I/O for the app. It takes [`Command`]s from the UI, hands the
//! session calls over in the order they arrive, forwards the session's
//! events and readings to the UI, runs the scan, and drives the recorder.
//! This is the only file that names `session::Session`,
//! `discovery::Discovery` or `store::Store` (DD-APP-050).
//!
//! The loop awaits nothing but its four sources (the command channel, the
//! session's events, the calls in flight and the recorder's reports) and
//! makes no file call, so a command is taken as soon as the loop is free
//! (SR-041).

use core::fmt;
use core::task::Poll;
use core::time::Duration;
use std::path::PathBuf;
use std::sync::Arc;

use futures::future::BoxFuture;
use futures::stream::{FuturesUnordered, StreamExt};
use futures::FutureExt;
use mp305_core::discovery::{self, Discovery, ScanOptions};
use mp305_core::error::Error;
use mp305_core::protocol::ops::bind::HostId;
use mp305_core::protocol::timing;
use mp305_core::session::{
    Connector, LinkState, Markers, Options, Session, SessionEvent, SessionEvents,
};
use mp305_core::store::Store;
use tokio::sync::{mpsc, watch};
use tokio::time::Instant;

use crate::model::{Found, Info, Kind, Limits, TimedReading};
use crate::paths;
use crate::recording::{self, Recorder, RecorderReport};
use crate::texts::{self, DepsStep};

/// The log target of the worker.
pub const LOG_TARGET: &str = "mp305_app::worker";

/// The capacity of the reading channel to the UI (DD-APP-008).
pub const READING_CAPACITY: usize = 4096;

/// How often at most a [`AppEvent::ReadingsDropped`] goes out
/// (DD-APP-008).
const DROP_REPORT_SPACING: Duration = Duration::from_secs(1);

/// Wakes the UI after an event was sent; the UI passes a call of
/// `egui::Context::request_repaint` (DD-APP-001).
pub type Wake = Arc<dyn Fn() + Send + Sync>;

/// What a scan is to the worker: discovery for real supplies, a scripted
/// scanner in the tests (DD-APP-001).
pub trait Scanner: Send + Sync {
    /// Scans for supplies with `options`.
    ///
    /// # Errors
    ///
    /// The backend's error; the worker reports its text in the
    /// [`AppEvent::ScanResult`].
    fn scan(&self, options: ScanOptions) -> BoxFuture<'_, Result<Vec<Found>, Error>>;
}

impl Scanner for Discovery {
    fn scan(&self, options: ScanOptions) -> BoxFuture<'_, Result<Vec<Found>, Error>> {
        Box::pin(Discovery::scan(self, options))
    }
}

/// What the worker takes from outside (DD-APP-001).
#[derive(Clone)]
pub struct Deps {
    /// Turns an identifier into a transport for the session.
    pub connector: Arc<dyn Connector>,
    /// Finds supplies.
    pub scanner: Arc<dyn Scanner>,
    /// The unclean-exit markers.
    pub markers: Arc<dyn Markers>,
    /// The host ID the bind presents.
    pub host_id: HostId,
}

/// The real dependencies, built on the runtime (DD-APP-001): the state
/// directory, the store and its host ID, then discovery. One
/// `Arc<Discovery>` serves as connector and scanner (one per process, one
/// scan lock, DD-DISC-010), and the store as the markers.
///
/// # Errors
///
/// `texts::deps_failed(step, text)` for the step that failed.
#[must_use]
pub fn real_deps() -> BoxFuture<'static, Result<Deps, String>> {
    Box::pin(async {
        let dir = paths::state_dir()
            .map_err(|text| texts::deps_failed(DepsStep::StateDirectory, &text))?;
        let store = Arc::new(Store::new(dir));
        let host_id = store
            .host_id()
            .map_err(|e| texts::deps_failed(DepsStep::HostId, &e.to_string()))?;
        let discovery = Arc::new(
            Discovery::new()
                .await
                .map_err(|e| texts::deps_failed(DepsStep::Discovery, &e.to_string()))?,
        );
        Ok(Deps {
            connector: Arc::clone(&discovery) as Arc<dyn Connector>,
            scanner: discovery as Arc<dyn Scanner>,
            markers: store as Arc<dyn Markers>,
            host_id,
        })
    })
}

/// A command from the UI; each carries an `id` the UI assigns
/// (DD-APP-002).
#[derive(Clone, Debug, PartialEq)]
pub enum Command {
    /// Scan for supplies.
    Scan {
        /// The command's id.
        id: u64,
        /// What to scan and for how long.
        options: ScanOptions,
    },
    /// Connect to a supply.
    Connect {
        /// The command's id.
        id: u64,
        /// The supply's identifier.
        identifier: String,
        /// Whether a lost link is reconnected.
        reconnect: bool,
        /// The user's limits.
        limits: Limits,
    },
    /// Close the open session and connect to the same supply again.
    Reconnect {
        /// The command's id.
        id: u64,
        /// Whether a lost link is reconnected.
        reconnect: bool,
        /// The user's limits.
        limits: Limits,
    },
    /// Set the voltage setpoint.
    SetVoltage {
        /// The command's id.
        id: u64,
        /// The setpoint in V.
        volts: f64,
    },
    /// Set the current limit.
    SetCurrentLimit {
        /// The command's id.
        id: u64,
        /// The limit in A.
        amps: f64,
    },
    /// Switch the output on.
    OutputOn {
        /// The command's id.
        id: u64,
    },
    /// Switch the output off.
    OutputOff {
        /// The command's id.
        id: u64,
    },
    /// Request remote control.
    RequestRemoteControl {
        /// The command's id.
        id: u64,
    },
    /// Release remote control.
    ReleaseRemoteControl {
        /// The command's id.
        id: u64,
    },
    /// Set the user's limits.
    SetLimits {
        /// The command's id.
        id: u64,
        /// The new limits.
        limits: Limits,
    },
    /// Switch reconnection on or off.
    SetReconnect {
        /// The command's id.
        id: u64,
        /// Whether a lost link is reconnected.
        on: bool,
    },
    /// Close the session, switching the output off first when asked.
    Disconnect {
        /// The command's id.
        id: u64,
        /// Whether the output is switched off first.
        output_off: bool,
    },
    /// A disconnect from a phase in which the app could not ask
    /// (`Connecting`, `Lost`); [`unasked`] decides between a close and a
    /// drop (DD-APP-005).
    DisconnectUnasked {
        /// The command's id.
        id: u64,
    },
    /// Start a recording to a new file.
    StartRecording {
        /// The command's id.
        id: u64,
        /// The file, which must not exist.
        path: PathBuf,
    },
    /// Stop the recording.
    StopRecording {
        /// The command's id.
        id: u64,
    },
}

impl Command {
    /// The command's id.
    #[must_use]
    pub fn id(&self) -> u64 {
        match self {
            Command::Scan { id, .. }
            | Command::Connect { id, .. }
            | Command::Reconnect { id, .. }
            | Command::SetVoltage { id, .. }
            | Command::SetCurrentLimit { id, .. }
            | Command::OutputOn { id }
            | Command::OutputOff { id }
            | Command::RequestRemoteControl { id }
            | Command::ReleaseRemoteControl { id }
            | Command::SetLimits { id, .. }
            | Command::SetReconnect { id, .. }
            | Command::Disconnect { id, .. }
            | Command::DisconnectUnasked { id }
            | Command::StartRecording { id, .. }
            | Command::StopRecording { id } => *id,
        }
    }

    /// The command's kind.
    #[must_use]
    pub fn what(&self) -> What {
        match self {
            Command::Scan { .. } => What::Scan,
            Command::Connect { .. } => What::Connect,
            Command::Reconnect { .. } => What::Reconnect,
            Command::SetVoltage { .. } => What::SetVoltage,
            Command::SetCurrentLimit { .. } => What::SetCurrentLimit,
            Command::OutputOn { .. } => What::OutputOn,
            Command::OutputOff { .. } => What::OutputOff,
            Command::RequestRemoteControl { .. } => What::RequestRemoteControl,
            Command::ReleaseRemoteControl { .. } => What::ReleaseRemoteControl,
            Command::SetLimits { .. } => What::SetLimits,
            Command::SetReconnect { .. } => What::SetReconnect,
            Command::Disconnect { .. } | Command::DisconnectUnasked { .. } => What::Disconnect,
            Command::StartRecording { .. } => What::StartRecording,
            Command::StopRecording { .. } => What::StopRecording,
        }
    }
}

/// The kind of a command, with `Display` in lowercase words
/// (DD-APP-002).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum What {
    /// `scan`.
    Scan,
    /// `connect`.
    Connect,
    /// `reconnect`.
    Reconnect,
    /// `set voltage`.
    SetVoltage,
    /// `set current limit`.
    SetCurrentLimit,
    /// `output on`.
    OutputOn,
    /// `output off`.
    OutputOff,
    /// `request remote control`.
    RequestRemoteControl,
    /// `release remote control`.
    ReleaseRemoteControl,
    /// `set limits`.
    SetLimits,
    /// `set reconnect`.
    SetReconnect,
    /// `disconnect`.
    Disconnect,
    /// `start recording`.
    StartRecording,
    /// `stop recording`.
    StopRecording,
}

impl fmt::Display for What {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(match self {
            What::Scan => "scan",
            What::Connect => "connect",
            What::Reconnect => "reconnect",
            What::SetVoltage => "set voltage",
            What::SetCurrentLimit => "set current limit",
            What::OutputOn => "output on",
            What::OutputOff => "output off",
            What::RequestRemoteControl => "request remote control",
            What::ReleaseRemoteControl => "release remote control",
            What::SetLimits => "set limits",
            What::SetReconnect => "set reconnect",
            What::Disconnect => "disconnect",
            What::StartRecording => "start recording",
            What::StopRecording => "stop recording",
        })
    }
}

/// The kind of an error: one variant per core [`Error`] variant, plus
/// `App` for the texts of DD-APP-014 (DD-APP-002).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum ErrorKind {
    /// [`Error::Protocol`].
    Protocol,
    /// [`Error::SetpointRange`].
    SetpointRange,
    /// [`Error::Mode`].
    Mode,
    /// [`Error::Transport`].
    Transport,
    /// [`Error::Timeout`].
    Timeout,
    /// [`Error::LinkLost`].
    LinkLost,
    /// [`Error::ConnectionDenied`].
    ConnectionDenied,
    /// [`Error::RemoteControlDenied`].
    RemoteControlDenied,
    /// [`Error::RemoteControlLost`].
    RemoteControlLost,
    /// [`Error::CommandRejected`].
    CommandRejected,
    /// [`Error::FaultActive`].
    FaultActive,
    /// [`Error::NotReady`].
    NotReady,
    /// [`Error::Store`].
    Store,
    /// [`Error::AlreadyOpen`].
    AlreadyOpen,
    /// [`Error::Cancelled`].
    Cancelled,
    /// [`Error::NotFound`].
    NotFound,
    /// A refusal of the app itself, with a text of DD-APP-014.
    App,
}

impl ErrorKind {
    /// The kind of `error`. The match has no wildcard, so a new core
    /// variant does not compile until it is mapped.
    #[must_use]
    pub fn of(error: &Error) -> ErrorKind {
        match error {
            Error::Protocol(_) => ErrorKind::Protocol,
            Error::SetpointRange { .. } => ErrorKind::SetpointRange,
            Error::Mode { .. } => ErrorKind::Mode,
            Error::Transport { .. } => ErrorKind::Transport,
            Error::Timeout { .. } => ErrorKind::Timeout,
            Error::LinkLost { .. } => ErrorKind::LinkLost,
            Error::ConnectionDenied => ErrorKind::ConnectionDenied,
            Error::RemoteControlDenied => ErrorKind::RemoteControlDenied,
            Error::RemoteControlLost => ErrorKind::RemoteControlLost,
            Error::CommandRejected { .. } => ErrorKind::CommandRejected,
            Error::FaultActive { .. } => ErrorKind::FaultActive,
            Error::NotReady => ErrorKind::NotReady,
            Error::Store { .. } => ErrorKind::Store,
            Error::AlreadyOpen { .. } => ErrorKind::AlreadyOpen,
            Error::Cancelled { .. } => ErrorKind::Cancelled,
            Error::NotFound { .. } => ErrorKind::NotFound,
        }
    }
}

/// An error as the UI shows it: the core error's `Display` or a text of
/// DD-APP-014, and its kind (DD-APP-002).
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct ErrorText {
    /// The text.
    pub text: String,
    /// The kind.
    pub kind: ErrorKind,
}

impl ErrorText {
    /// The text and kind of a core error.
    #[must_use]
    pub fn of(error: &Error) -> ErrorText {
        ErrorText {
            text: error.to_string(),
            kind: ErrorKind::of(error),
        }
    }

    /// A refusal of the app with `text`.
    #[must_use]
    pub fn app(text: &str) -> ErrorText {
        ErrorText {
            text: text.to_string(),
            kind: ErrorKind::App,
        }
    }
}

/// What the recording did (DD-APP-002, DD-APP-004).
#[derive(Clone, Debug, PartialEq, Eq)]
pub enum RecordingEvent {
    /// The file is open and its header written.
    On {
        /// The file.
        path: PathBuf,
    },
    /// Rows written so far.
    Progress {
        /// The row count.
        rows: u64,
    },
    /// The recording ended.
    Off {
        /// The file.
        path: PathBuf,
        /// The rows written.
        rows: u64,
        /// Why it ended, when not on request.
        error: Option<String>,
    },
}

/// An event on the event channel to the UI (DD-APP-002).
#[derive(Clone, Debug, PartialEq)]
pub enum AppEvent {
    /// The answer to a `Scan`.
    ScanResult {
        /// The `Scan`'s id.
        id: u64,
        /// The supplies found.
        found: Vec<Found>,
        /// Why nothing was found, when nothing was.
        message: Option<String>,
    },
    /// A connection attempt started.
    Connecting {
        /// The attempt's number.
        sid: u64,
        /// The supply's identifier.
        identifier: String,
    },
    /// A session event other than a reading.
    Session {
        /// The attempt it belongs to.
        sid: u64,
        /// The event.
        event: SessionEvent,
    },
    /// The session is ready for control.
    Ready {
        /// The attempt it belongs to.
        sid: u64,
        /// The supply's info.
        info: Info,
        /// The latest reading.
        reading: Option<TimedReading>,
        /// The transport kind.
        transport: Option<Kind>,
    },
    /// The connection attempt failed.
    ConnectFailed {
        /// The attempt it belongs to.
        sid: u64,
        /// Why.
        text: String,
    },
    /// The answer to every command but `Scan` and `Disconnect`.
    Done {
        /// The command's id.
        id: u64,
        /// The command's kind.
        what: What,
        /// The outcome.
        result: Result<(), ErrorText>,
    },
    /// The answer to a `Disconnect`, and the report of a session that
    /// ended.
    Disconnected {
        /// The attempt it belongs to; `None` when there was no session.
        sid: Option<u64>,
        /// The close error's text.
        text: Option<String>,
        /// Whether the output was to be switched off.
        off_requested: bool,
        /// The output state of a reading that arrived at most 1 s before
        /// the close started, if there was one.
        output_on: Option<bool>,
    },
    /// What the recording did.
    Recording(RecordingEvent),
    /// Readings dropped because the UI fell behind, in total.
    ReadingsDropped {
        /// The count since the start.
        total: u64,
    },
    /// The worker cannot work.
    Fatal(String),
}

/// A reading on the reading channel to the UI (DD-APP-008).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct UiReading {
    /// The attempt it belongs to.
    pub sid: u64,
    /// The reading.
    pub reading: TimedReading,
}

/// The worker's ends of the two channels to the UI (DD-APP-008): events go
/// on an unbounded channel, readings on a bounded one with `try_send`; a
/// full reading channel drops the reading and counts it.
#[derive(Debug)]
pub struct UiSender {
    /// The event channel.
    events: mpsc::UnboundedSender<AppEvent>,
    /// The reading channel.
    readings: mpsc::Sender<UiReading>,
    /// Readings dropped so far.
    dropped: u64,
    /// The total in the last `ReadingsDropped` sent.
    reported: u64,
    /// When the last `ReadingsDropped` went out.
    last_report: Option<Instant>,
}

impl UiSender {
    /// The worker's ends of the two channels.
    #[must_use]
    pub fn new(
        events: mpsc::UnboundedSender<AppEvent>,
        readings: mpsc::Sender<UiReading>,
    ) -> UiSender {
        UiSender {
            events,
            readings,
            dropped: 0,
            reported: 0,
            last_report: None,
        }
    }

    /// Sends `event`; a closed channel is ignored.
    fn event(&self, event: AppEvent) {
        let _ = self.events.send(event);
    }

    /// Sends `reading` without waiting: a full channel drops and counts it,
    /// a closed one is ignored. Returns a `ReadingsDropped` to send when
    /// the count changed and none went out in the last second.
    fn reading(&mut self, reading: UiReading) -> Option<AppEvent> {
        if let Err(mpsc::error::TrySendError::Full(_)) = self.readings.try_send(reading) {
            self.dropped = self.dropped.saturating_add(1);
        }
        let now = Instant::now();
        let due = self
            .last_report
            .is_none_or(|last| now.saturating_duration_since(last) >= DROP_REPORT_SPACING);
        if self.dropped != self.reported && due {
            self.reported = self.dropped;
            self.last_report = Some(now);
            return Some(AppEvent::ReadingsDropped {
                total: self.dropped,
            });
        }
        None
    }
}

/// What a call in `tasks` completes with (DD-APP-001).
enum Completion {
    /// A scan ended.
    Scan {
        /// The `Scan`'s id.
        id: u64,
        /// The supplies, or the error.
        result: Result<Vec<Found>, Error>,
    },
    /// The ready wait of an attempt ended.
    Ready {
        /// The attempt.
        sid: u64,
        /// The info, or why the connect flow failed.
        result: Result<Info, Error>,
    },
    /// A session control call ended.
    Call {
        /// The attempt whose session made the call.
        sid: u64,
        /// The command's id.
        id: u64,
        /// The command's kind.
        what: What,
        /// The outcome.
        result: Result<(), Error>,
    },
    /// The close of an attempt ended.
    Closed {
        /// The attempt.
        sid: u64,
        /// The outcome.
        result: Result<(), Error>,
    },
}

/// What follows a close (DD-APP-005).
#[derive(Clone, Debug, PartialEq)]
enum Then {
    /// Report the close with `Disconnected`.
    Report,
    /// Report the failed connect flow with `ConnectFailed`.
    ConnectFailed(String),
    /// Connect again (a `Reconnect`).
    Connect(ConnectArgs),
}

/// The arguments of a connection that follows a close (DD-APP-005).
#[derive(Clone, Debug, PartialEq)]
struct ConnectArgs {
    /// The id of the `Reconnect` it came from.
    id: u64,
    /// The supply's identifier.
    identifier: String,
    /// Whether a lost link is reconnected.
    reconnect: bool,
    /// The user's limits.
    limits: Limits,
}

/// A session and its events, as the slot holds them.
struct Held {
    /// The attempt's number.
    sid: u64,
    /// The session, shared with the calls in flight.
    session: Arc<Session>,
    /// Its events; `None` once they ended.
    events: Option<SessionEvents>,
    /// When the last `OutputOn` call of this session completed, with any
    /// result (DD-APP-005): a reading from before that plus
    /// `timing::SETTLE` cannot show what the command did.
    output_on_done: Option<Instant>,
    /// Set to `true` when the session is dropped without `close`: the
    /// session's futures in `tasks` then end at once and release their
    /// clones of it, so that its task is aborted.
    stop: watch::Sender<bool>,
}

impl Held {
    /// A newly opened session of attempt `sid`.
    fn new(sid: u64, session: Arc<Session>, events: SessionEvents) -> Held {
        Held {
            sid,
            session,
            events: Some(events),
            output_on_done: None,
            stop: watch::channel(false).0,
        }
    }

    /// `future`, which belongs to this session, ended with `dropped`
    /// instead as soon as the session is dropped without `close`.
    fn guard(
        &self,
        future: BoxFuture<'static, Completion>,
        dropped: Completion,
    ) -> BoxFuture<'static, Completion> {
        let mut stop = self.stop.subscribe();
        Box::pin(async move {
            let stopped = async move {
                // A sender dropped without the stop (the slot moved on in
                // order) never ends the future early.
                if stop.wait_for(|stopped| *stopped).await.is_err() {
                    core::future::pending::<()>().await;
                }
            };
            tokio::select! {
                biased;
                completion = future => completion,
                () = stopped => dropped,
            }
        })
    }

    /// Whether `reading` arrived at or after `output_on_done` plus
    /// `timing::SETTLE`, if that is set (the first condition of a witness,
    /// DD-APP-005).
    fn settled(&self, reading: &TimedReading) -> bool {
        self.output_on_done.is_none_or(|done| {
            reading
                .at
                .checked_duration_since(done)
                .is_some_and(|since| since >= timing::SETTLE)
        })
    }

    /// DD-APP-006's test: the latest reading arrived at most
    /// `timing::REPLY` before `now`, shows the output off and is settled,
    /// and no `OutputOn` call is in flight.
    fn off_confirmed(&self, now: Instant, output_on_calls: usize) -> bool {
        output_on_calls == 0
            && self.session.latest_reading().is_some_and(|r| {
                now.saturating_duration_since(r.at) <= timing::REPLY
                    && !r.reading.output_on
                    && self.settled(&r)
            })
    }

    /// The output state the close of this session reports (DD-APP-005):
    /// the latest reading's, when it is a witness: settled, and arrived no
    /// earlier than `timing::REPLY` before `close_started`, or, for a close
    /// that was asked to switch the output off and failed, at or after
    /// `close_started`.
    fn witnessed_output(&self, close_started: Instant, failed_switch_off: bool) -> Option<bool> {
        let reading = self.session.latest_reading()?;
        let in_time = if failed_switch_off {
            reading.at >= close_started
        } else {
            close_started.saturating_duration_since(reading.at) <= timing::REPLY
        };
        (in_time && self.settled(&reading)).then_some(reading.reading.output_on)
    }
}

/// The error the calls of a session dropped without `close` end with; the
/// `Disconnected` that reports the drop says why.
fn dropped_error() -> Error {
    Error::LinkLost {
        text: texts::DISCONNECT_UNASKED.to_string(),
    }
}

/// The worker's session slot (DD-APP-005).
enum Slot {
    /// No session.
    Empty,
    /// The connect flow runs; the ready wait is in `tasks`.
    Starting {
        /// The session.
        held: Held,
        /// The supply's identifier.
        identifier: String,
    },
    /// The session is ready, or lost and maybe reconnecting.
    Open {
        /// The session.
        held: Held,
        /// The supply's identifier.
        identifier: String,
    },
    /// The close runs; it is in `tasks`.
    Closing {
        /// The session.
        held: Held,
        /// Whether the output was to be switched off.
        off_requested: bool,
        /// When the close was started.
        close_started: Instant,
        /// What follows the close.
        then: Then,
        /// The text the report carries instead of the close error's, for
        /// a session that ended unexpectedly (DD-APP-005).
        report_text: Option<String>,
    },
}

/// The kind of the slot, for [`on_events_end`].
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum SlotKind {
    /// No session.
    Empty,
    /// The connect flow runs.
    Starting,
    /// The session is ready, or lost.
    Open,
    /// The close runs.
    Closing,
}

/// How the end of a session's events is taken (DD-APP-005).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum EventsEnd {
    /// The close dropped the sender.
    Expected,
    /// A session ended without `close`, which the session design does not
    /// do; handled as `Disconnect { output_off: false }`.
    Unexpected,
}

/// What a disconnect that could not ask does with an open or starting
/// session (DD-APP-005, DD-APP-006).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Unasked {
    /// `close(false)`: outside `Ready` nothing was sent and the session
    /// keeps the marker; with the output confirmed off, clearing it is
    /// right.
    Close,
    /// Drop the session without `close`: the link drops, the supply clears
    /// the grant, the output and the marker stay as they are.
    Drop,
}

/// Decides a disconnect that could not ask (DD-APP-005): `Drop` only for a
/// `Ready` link whose output is not confirmed off.
#[must_use]
pub fn unasked(link_ready: bool, off_confirmed: bool) -> Unasked {
    if link_ready && !off_confirmed {
        Unasked::Drop
    } else {
        Unasked::Close
    }
}

/// Classifies the end of the slot's events (DD-APP-005): `Closing` (and an
/// empty slot, which holds no events) gives `Expected`, `Starting` and
/// `Open` give `Unexpected`.
#[must_use]
pub fn on_events_end(slot: SlotKind) -> EventsEnd {
    match slot {
        SlotKind::Empty | SlotKind::Closing => EventsEnd::Expected,
        SlotKind::Starting | SlotKind::Open => EventsEnd::Unexpected,
    }
}

impl Slot {
    /// The slot's kind.
    fn kind(&self) -> SlotKind {
        match self {
            Slot::Empty => SlotKind::Empty,
            Slot::Starting { .. } => SlotKind::Starting,
            Slot::Open { .. } => SlotKind::Open,
            Slot::Closing { .. } => SlotKind::Closing,
        }
    }

    /// The session and its events, mutably, unless the slot is empty.
    fn held_mut(&mut self) -> Option<&mut Held> {
        match self {
            Slot::Empty => None,
            Slot::Starting { held, .. } | Slot::Open { held, .. } | Slot::Closing { held, .. } => {
                Some(held)
            }
        }
    }

    /// The next event of the slot's session, or pending forever while the
    /// slot holds no events that have not ended. `None` when they ended.
    async fn next_event(&mut self) -> (u64, Option<SessionEvent>) {
        match self.held_mut() {
            Some(Held {
                sid,
                events: Some(events),
                ..
            }) => (*sid, events.next().await),
            _ => core::future::pending().await,
        }
    }
}

/// The recorder that exists, with its report channel (DD-APP-004).
struct Recording {
    /// The recorder.
    recorder: Recorder,
    /// Its reports.
    reports: mpsc::UnboundedReceiver<RecorderReport>,
}

/// The next report of the recorder, or pending forever while none exists.
async fn next_report(recording: &mut Option<Recording>) -> Option<RecorderReport> {
    match recording {
        Some(r) => r.reports.recv().await,
        None => core::future::pending().await,
    }
}

/// The next completion of a call in flight, or pending forever while none
/// is in flight.
async fn next_completion(
    tasks: &mut FuturesUnordered<BoxFuture<'static, Completion>>,
) -> Completion {
    if tasks.is_empty() {
        return core::future::pending().await;
    }
    match tasks.next().await {
        Some(completion) => completion,
        None => core::future::pending().await,
    }
}

/// The next command, or pending forever once the channel closed (the
/// loop then takes the exit path).
async fn next_command(commands: &mut Option<mpsc::UnboundedReceiver<Command>>) -> Option<Command> {
    match commands {
        Some(rx) => rx.recv().await,
        None => core::future::pending().await,
    }
}

/// Polls `future` once with the caller's context: `Some` with its output
/// when it completed at once, else `None`, the future being pending.
async fn poll_once<T>(future: &mut BoxFuture<'static, T>) -> Option<T> {
    core::future::poll_fn(|cx| match future.as_mut().poll(cx) {
        Poll::Ready(value) => Poll::Ready(Some(value)),
        Poll::Pending => Poll::Ready(None),
    })
    .await
}

/// Runs the worker (DD-APP-001): awaits `build`; on `Err(text)` emits
/// `Fatal(text)` and answers every command with that text until the
/// channel closes; on `Ok(deps)` runs [`run`].
pub async fn start(
    build: BoxFuture<'static, Result<Deps, String>>,
    mut commands: mpsc::UnboundedReceiver<Command>,
    ui: UiSender,
    wake: Wake,
) {
    match build.await {
        Ok(deps) => run(deps, commands, ui, wake).await,
        Err(text) => {
            log::error!(target: LOG_TARGET, "{}", texts::fatal(&text));
            ui.event(AppEvent::Fatal(text.clone()));
            wake();
            while let Some(command) = commands.recv().await {
                let answer = match command {
                    Command::Scan { id, .. } => AppEvent::ScanResult {
                        id,
                        found: Vec::new(),
                        message: Some(text.clone()),
                    },
                    Command::Disconnect { output_off, .. } => AppEvent::Disconnected {
                        sid: None,
                        text: None,
                        off_requested: output_off,
                        output_on: None,
                    },
                    // DD-APP-001 lists only `Disconnect` here; DD-APP-002
                    // (rev 3) answers `DisconnectUnasked` with one
                    // `Disconnected` too, which ends the model's `Closing`.
                    Command::DisconnectUnasked { .. } => AppEvent::Disconnected {
                        sid: None,
                        text: None,
                        off_requested: false,
                        output_on: None,
                    },
                    other => AppEvent::Done {
                        id: other.id(),
                        what: other.what(),
                        result: Err(ErrorText::app(&text)),
                    },
                };
                ui.event(answer);
                wake();
            }
        }
    }
}

/// The worker's state (DD-APP-001).
struct Worker {
    /// What it takes from outside.
    deps: Deps,
    /// The channels to the UI.
    ui: UiSender,
    /// Wakes the UI.
    wake: Wake,
    /// The session slot.
    slot: Slot,
    /// The number of the last connection attempt.
    sid: u64,
    /// The calls, the ready wait, the close and the scan in flight.
    tasks: FuturesUnordered<BoxFuture<'static, Completion>>,
    /// Whether a scan is in `tasks`.
    scanning: bool,
    /// How many `OutputOn` calls are in `tasks` (DD-APP-006).
    output_on_calls: usize,
    /// The recorder, while one exists.
    recording: Option<Recording>,
}

/// Runs the worker loop over `deps` until the command channel closed and
/// the exit of DD-APP-006 is done; the futures still in flight are then
/// dropped.
pub async fn run(deps: Deps, commands: mpsc::UnboundedReceiver<Command>, ui: UiSender, wake: Wake) {
    let mut worker = Worker {
        deps,
        ui,
        wake,
        slot: Slot::Empty,
        sid: 0,
        tasks: FuturesUnordered::new(),
        scanning: false,
        output_on_calls: 0,
        recording: None,
    };
    let mut commands = Some(commands);
    let mut exiting = false;
    loop {
        if exiting && matches!(worker.slot, Slot::Empty) && worker.recording.is_none() {
            break;
        }
        tokio::select! {
            biased;
            command = next_command(&mut commands) => match command {
                Some(command) => worker.command(command).await,
                None => {
                    commands = None;
                    exiting = true;
                    worker.exit().await;
                }
            },
            (sid, event) = worker.slot.next_event() => worker.session_event(sid, event).await,
            completion = next_completion(&mut worker.tasks) => worker.completion(completion).await,
            report = next_report(&mut worker.recording) => worker.recorder_report(report),
        }
    }
    log::info!(target: LOG_TARGET, "worker ended");
}

impl Worker {
    /// Sends `event` to the UI and wakes it.
    fn emit(&self, event: AppEvent) {
        self.ui.event(event);
        (self.wake)();
    }

    /// Sends `reading` to the UI (and a `ReadingsDropped` when one is due)
    /// and wakes it.
    fn send_reading(&mut self, reading: UiReading) {
        let dropped = self.ui.reading(reading);
        (self.wake)();
        if let Some(event) = dropped {
            self.emit(event);
        }
    }

    /// Answers a command with `Done`.
    fn done(&self, id: u64, what: What, result: Result<(), ErrorText>) {
        self.emit(AppEvent::Done { id, what, result });
    }

    /// Polls `future` once inside the loop and pushes it into `tasks` when
    /// it is pending; a call the session answered at once is handled at
    /// once (DD-APP-003).
    async fn launch(&mut self, mut future: BoxFuture<'static, Completion>) {
        match poll_once(&mut future).await {
            Some(completion) => Box::pin(self.completion(completion)).await,
            None => self.tasks.push(future),
        }
    }

    /// Takes one command (DD-APP-003, DD-APP-005).
    async fn command(&mut self, command: Command) {
        log::debug!(target: LOG_TARGET, "command {command:?}");
        match command {
            Command::Scan { id, options } => self.scan(id, options),
            Command::Connect {
                id,
                identifier,
                reconnect,
                limits,
            } => {
                if matches!(self.slot, Slot::Empty) {
                    self.done(id, What::Connect, Ok(()));
                    self.connect(identifier, reconnect, limits).await;
                } else {
                    self.done(
                        id,
                        What::Connect,
                        Err(ErrorText::app(texts::ALREADY_CONNECTED)),
                    );
                }
            }
            Command::Reconnect {
                id,
                reconnect,
                limits,
            } => self.reconnect(id, reconnect, limits).await,
            Command::SetVoltage { id, volts } => {
                self.control(id, What::SetVoltage, move |s| {
                    Box::pin(async move { s.set_voltage(volts).await })
                })
                .await;
            }
            Command::SetCurrentLimit { id, amps } => {
                self.control(id, What::SetCurrentLimit, move |s| {
                    Box::pin(async move { s.set_current_limit(amps).await })
                })
                .await;
            }
            Command::OutputOn { id } => {
                self.control(id, What::OutputOn, |s| {
                    Box::pin(async move { s.output_on().await })
                })
                .await;
            }
            Command::OutputOff { id } => {
                self.control(id, What::OutputOff, |s| {
                    Box::pin(async move { s.output_off().await })
                })
                .await;
            }
            Command::RequestRemoteControl { id } => {
                self.control(id, What::RequestRemoteControl, |s| {
                    Box::pin(async move { s.request_remote_control().await })
                })
                .await;
            }
            Command::ReleaseRemoteControl { id } => {
                self.control(id, What::ReleaseRemoteControl, |s| {
                    Box::pin(async move { s.release_remote_control().await })
                })
                .await;
            }
            Command::SetLimits { id, limits } => self.set_limits(id, limits),
            Command::SetReconnect { id, on } => self.set_reconnect(id, on),
            Command::Disconnect { output_off, .. } => self.disconnect(output_off, None).await,
            Command::DisconnectUnasked { .. } => self.disconnect_unasked().await,
            Command::StartRecording { id, path } => self.start_recording(id, path),
            Command::StopRecording { id } => {
                self.stop_recording();
                self.done(id, What::StopRecording, Ok(()));
            }
        }
    }

    /// `Scan` (DD-APP-003): one scan at a time.
    fn scan(&mut self, id: u64, options: ScanOptions) {
        if self.scanning {
            self.emit(AppEvent::ScanResult {
                id,
                found: Vec::new(),
                message: Some(texts::SCAN_RUNNING.to_string()),
            });
            return;
        }
        self.scanning = true;
        let scanner = Arc::clone(&self.deps.scanner);
        self.tasks.push(Box::pin(async move {
            let result = scanner.scan(options).await;
            Completion::Scan { id, result }
        }));
    }

    /// A control command (DD-APP-003): the session call with the slot
    /// `Open`, else `NotReady`.
    async fn control<F>(&mut self, id: u64, what: What, call: F)
    where
        F: FnOnce(Arc<Session>) -> BoxFuture<'static, Result<(), Error>>,
    {
        let future = match &self.slot {
            Slot::Open { held, .. } => {
                let sid = held.sid;
                let call = call(Arc::clone(&held.session));
                let dropped = Completion::Call {
                    sid,
                    id,
                    what,
                    result: Err(dropped_error()),
                };
                held.guard(
                    Box::pin(async move {
                        let result = call.await;
                        Completion::Call {
                            sid,
                            id,
                            what,
                            result,
                        }
                    }),
                    dropped,
                )
            }
            _ => {
                self.done(id, what, Err(ErrorText::of(&Error::NotReady)));
                return;
            }
        };
        if what == What::OutputOn {
            self.output_on_calls = self.output_on_calls.saturating_add(1);
        }
        self.launch(future).await;
    }

    /// `SetLimits` (DD-APP-003).
    fn set_limits(&mut self, id: u64, limits: Limits) {
        let result = match &mut self.slot {
            Slot::Starting { held, .. } | Slot::Open { held, .. } => held
                .session
                .set_limits(limits)
                .map_err(|e| ErrorText::of(&e)),
            Slot::Closing {
                then: Then::Connect(args),
                ..
            } => {
                args.limits = limits;
                Ok(())
            }
            Slot::Empty | Slot::Closing { .. } => Ok(()),
        };
        self.done(id, What::SetLimits, result);
    }

    /// `SetReconnect` (DD-APP-003).
    fn set_reconnect(&mut self, id: u64, on: bool) {
        match &mut self.slot {
            Slot::Starting { held, .. } | Slot::Open { held, .. } => {
                held.session.set_reconnect(on);
            }
            Slot::Closing {
                then: Then::Connect(args),
                ..
            } => args.reconnect = on,
            Slot::Empty | Slot::Closing { .. } => {}
        }
        self.done(id, What::SetReconnect, Ok(()));
    }

    /// The next attempt's number.
    fn next_sid(&mut self) -> u64 {
        self.sid = self.sid.saturating_add(1);
        self.sid
    }

    /// Opens a session with the slot `Empty` (DD-APP-005); the `Done` was
    /// sent by the caller.
    async fn connect(&mut self, identifier: String, reconnect: bool, limits: Limits) {
        let sid = self.next_sid();
        self.emit(AppEvent::Connecting {
            sid,
            identifier: identifier.clone(),
        });
        match Session::connect(
            Arc::clone(&self.deps.connector),
            &identifier,
            self.deps.host_id,
            Arc::clone(&self.deps.markers),
            Options::new(reconnect, limits),
        ) {
            Err(e) => self.emit(AppEvent::ConnectFailed {
                sid,
                text: e.to_string(),
            }),
            Ok((session, events)) => {
                let session = Arc::new(session);
                let waiting = Arc::clone(&session);
                let held = Held::new(sid, session, events);
                let ready = held.guard(
                    Box::pin(async move {
                        let result = waiting.ready().await;
                        Completion::Ready { sid, result }
                    }),
                    Completion::Ready {
                        sid,
                        result: Err(dropped_error()),
                    },
                );
                self.slot = Slot::Starting { held, identifier };
                self.launch(ready).await;
            }
        }
    }

    /// `Reconnect` (DD-APP-005).
    async fn reconnect(&mut self, id: u64, reconnect: bool, limits: Limits) {
        let Slot::Open { identifier, .. } = &self.slot else {
            self.done(
                id,
                What::Reconnect,
                Err(ErrorText::app(texts::NO_CONNECTION_TO_RENEW)),
            );
            return;
        };
        let args = ConnectArgs {
            id,
            identifier: identifier.clone(),
            reconnect,
            limits,
        };
        self.done(id, What::Reconnect, Ok(()));
        self.stop_recording();
        self.begin_close(false, Then::Connect(args), None).await;
    }

    /// `Disconnect` (DD-APP-005); `report_text` replaces the close error's
    /// text in the report (a session that ended unexpectedly).
    async fn disconnect(&mut self, output_off: bool, report_text: Option<String>) {
        match &mut self.slot {
            Slot::Empty => self.emit(AppEvent::Disconnected {
                sid: None,
                text: None,
                off_requested: output_off,
                output_on: None,
            }),
            Slot::Starting { .. } | Slot::Open { .. } => {
                self.stop_recording();
                self.begin_close(output_off, Then::Report, report_text)
                    .await;
            }
            Slot::Closing { then, .. } => {
                // A `Reconnect` closing the old session: no connection
                // follows, and the close's report answers this command.
                if matches!(then, Then::Connect(_)) {
                    *then = Then::Report;
                }
            }
        }
    }

    /// The decision of [`unasked`] for the slot's session, in `Starting` and
    /// `Open` (DD-APP-005, DD-APP-006); `None` in the other slots.
    fn decide_unasked(&self) -> Option<Unasked> {
        match &self.slot {
            Slot::Starting { held, .. } | Slot::Open { held, .. } => Some(unasked(
                held.session.link_state() == LinkState::Ready,
                held.off_confirmed(Instant::now(), self.output_on_calls),
            )),
            Slot::Empty | Slot::Closing { .. } => None,
        }
    }

    /// `DisconnectUnasked` (DD-APP-005): a `Disconnect { output_off: false }`
    /// unless [`unasked`] says to drop a `Ready` session whose output is
    /// not confirmed off.
    async fn disconnect_unasked(&mut self) {
        if self.decide_unasked() != Some(Unasked::Drop) {
            self.disconnect(false, None).await;
            return;
        }
        self.stop_recording();
        log::warn!(target: LOG_TARGET, "{}", texts::DISCONNECT_UNASKED);
        if let Some(sid) = self.drop_session() {
            self.emit(AppEvent::Disconnected {
                sid: Some(sid),
                text: Some(texts::DISCONNECT_UNASKED.to_string()),
                off_requested: false,
                output_on: None,
            });
        }
    }

    /// Drops the slot's session and its receiver without `close`: its
    /// futures in `tasks` end at once and release their clones, so that the
    /// session's task is aborted, the link drops, the supply clears the
    /// grant, and the output and the marker stay as they are. Returns the
    /// attempt's number; the slot is `Empty`.
    fn drop_session(&mut self) -> Option<u64> {
        let held = match core::mem::replace(&mut self.slot, Slot::Empty) {
            Slot::Starting { held, .. } | Slot::Open { held, .. } => held,
            other => {
                self.slot = other;
                return None;
            }
        };
        held.stop.send_replace(true);
        Some(held.sid)
    }

    /// Starts `close(output_off)` of the slot's session, first-polled, and
    /// makes the slot `Closing` with `then`.
    async fn begin_close(&mut self, output_off: bool, then: Then, report_text: Option<String>) {
        let held = match core::mem::replace(&mut self.slot, Slot::Empty) {
            Slot::Starting { held, .. } | Slot::Open { held, .. } => held,
            other => {
                self.slot = other;
                return;
            }
        };
        let session = Arc::clone(&held.session);
        let sid = held.sid;
        self.slot = Slot::Closing {
            held,
            off_requested: output_off,
            close_started: Instant::now(),
            then,
            report_text,
        };
        self.launch(Box::pin(async move {
            let result = session.close(output_off).await;
            Completion::Closed { sid, result }
        }))
        .await;
    }

    /// `StartRecording` (DD-APP-003, DD-APP-004).
    fn start_recording(&mut self, id: u64, path: PathBuf) {
        if self.recording.is_some() {
            self.done(
                id,
                What::StartRecording,
                Err(ErrorText::app(texts::ALREADY_RECORDING)),
            );
            return;
        }
        let latest = match &self.slot {
            Slot::Open { held, .. } => held.session.latest_reading(),
            _ => None,
        };
        let Some(latest) = latest else {
            self.done(
                id,
                What::StartRecording,
                Err(ErrorText::app(texts::NOT_CONNECTED)),
            );
            return;
        };
        let (reports_tx, reports) = mpsc::unbounded_channel();
        let recorder = Recorder::start(path, recording::open_file, latest.wall, reports_tx);
        self.recording = Some(Recording { recorder, reports });
        self.done(id, What::StartRecording, Ok(()));
    }

    /// Stops the recorder, if there is one; its `Ended` follows.
    fn stop_recording(&mut self) {
        if let Some(recording) = &mut self.recording {
            recording.recorder.stop();
        }
    }

    /// A report of the recorder (DD-APP-004).
    fn recorder_report(&mut self, report: Option<RecorderReport>) {
        match report {
            Some(RecorderReport::Opened) => {
                if let Some(recording) = &self.recording {
                    let path = recording.recorder.path().to_path_buf();
                    self.emit(AppEvent::Recording(RecordingEvent::On { path }));
                }
            }
            Some(RecorderReport::Progress { rows }) => {
                self.emit(AppEvent::Recording(RecordingEvent::Progress { rows }));
            }
            Some(RecorderReport::Ended { rows, error }) => {
                if let Some(recording) = self.recording.take() {
                    let event = recording.recorder.finish(rows, error);
                    self.emit(AppEvent::Recording(event));
                }
            }
            None => {
                // The thread ended without `Ended`; the recording is over.
                if let Some(recording) = self.recording.take() {
                    let event = recording
                        .recorder
                        .finish(0, Some(texts::RECORDER_ENDED.to_string()));
                    self.emit(AppEvent::Recording(event));
                }
            }
        }
    }

    /// Forwards one event of the slot's session (DD-APP-003), or handles
    /// the end of its events (DD-APP-005).
    async fn session_event(&mut self, sid: u64, event: Option<SessionEvent>) {
        match event {
            Some(event) => self.forward(sid, event),
            None => {
                if let Some(held) = self.slot.held_mut() {
                    held.events = None;
                }
                match on_events_end(self.slot.kind()) {
                    EventsEnd::Expected => {}
                    EventsEnd::Unexpected => {
                        log::warn!(target: LOG_TARGET, "{}", texts::SESSION_ENDED);
                        self.disconnect(false, Some(texts::SESSION_ENDED.to_string()))
                            .await;
                    }
                }
            }
        }
    }

    /// Forwards a session event: a reading to the reading channel and the
    /// recorder, every other event to the event channel.
    fn forward(&mut self, sid: u64, event: SessionEvent) {
        match event {
            SessionEvent::Reading(reading) => {
                if let Some(recording) = &mut self.recording {
                    recording.recorder.push(&reading);
                }
                self.send_reading(UiReading { sid, reading });
            }
            event => self.emit(AppEvent::Session { sid, event }),
        }
    }

    /// Forwards every event the slot's session holds now, without waiting
    /// (DD-APP-005).
    fn drain(&mut self) {
        loop {
            let Some(held) = self.slot.held_mut() else {
                return;
            };
            let sid = held.sid;
            let Some(events) = &mut held.events else {
                return;
            };
            // Unconstrained, so that Tokio's cooperative budget cannot make
            // a waiting event look absent.
            match tokio::task::unconstrained(events.next()).now_or_never() {
                Some(Some(event)) => self.forward(sid, event),
                Some(None) => {
                    held.events = None;
                    return;
                }
                None => return,
            }
        }
    }

    /// A call in flight completed.
    async fn completion(&mut self, completion: Completion) {
        match completion {
            Completion::Scan { id, result } => {
                self.scanning = false;
                let (found, message) = match result {
                    Ok(found) if found.is_empty() => {
                        (found, Some(discovery::not_found().to_string()))
                    }
                    Ok(found) => (found, None),
                    Err(e) => (Vec::new(), Some(e.to_string())),
                };
                self.emit(AppEvent::ScanResult { id, found, message });
            }
            Completion::Call {
                sid,
                id,
                what,
                result,
            } => {
                if what == What::OutputOn {
                    self.output_on_calls = self.output_on_calls.saturating_sub(1);
                    // Answered, with any result: the output may be on until
                    // a reading shows the command's effect (DD-APP-005).
                    if let Some(held) = self.slot.held_mut() {
                        if held.sid == sid {
                            held.output_on_done = Some(Instant::now());
                        }
                    }
                }
                self.done(id, what, result.map_err(|e| ErrorText::of(&e)));
            }
            Completion::Ready { sid, result } => self.ready(sid, result).await,
            Completion::Closed { sid, result } => self.closed(sid, result).await,
        }
    }

    /// The ready wait of attempt `sid` ended (DD-APP-005).
    async fn ready(&mut self, sid: u64, result: Result<Info, Error>) {
        let starting = matches!(&self.slot, Slot::Starting { held, .. } if held.sid == sid);
        if !starting {
            log::debug!(target: LOG_TARGET, "ready of {sid} ignored: {result:?}");
            return;
        }
        match result {
            Ok(info) => {
                self.drain();
                let Slot::Starting { held, identifier } =
                    core::mem::replace(&mut self.slot, Slot::Empty)
                else {
                    return;
                };
                let reading = held.session.latest_reading();
                let transport = held.session.transport();
                self.slot = Slot::Open { held, identifier };
                self.emit(AppEvent::Ready {
                    sid,
                    info,
                    reading,
                    transport,
                });
            }
            Err(e) => {
                self.begin_close(false, Then::ConnectFailed(e.to_string()), None)
                    .await;
            }
        }
    }

    /// The close of attempt `sid` ended (DD-APP-005).
    async fn closed(&mut self, sid: u64, result: Result<(), Error>) {
        let closing = matches!(&self.slot, Slot::Closing { held, .. } if held.sid == sid);
        if !closing {
            log::debug!(target: LOG_TARGET, "close of {sid} ignored: {result:?}");
            return;
        }
        self.drain();
        let Slot::Closing {
            held,
            off_requested,
            close_started,
            then,
            report_text,
        } = core::mem::replace(&mut self.slot, Slot::Empty)
        else {
            return;
        };
        let output_on = held.witnessed_output(close_started, off_requested && result.is_err());
        drop(held);
        match then {
            Then::Report => {
                let text = report_text.or_else(|| result.err().map(|e| e.to_string()));
                self.emit(AppEvent::Disconnected {
                    sid: Some(sid),
                    text,
                    off_requested,
                    output_on,
                });
            }
            Then::ConnectFailed(text) => self.emit(AppEvent::ConnectFailed { sid, text }),
            Then::Connect(args) => {
                if let Err(e) = result {
                    log::warn!(target: LOG_TARGET, "close before the reconnect: {e}");
                }
                log::debug!(target: LOG_TARGET, "reconnect {} follows", args.id);
                Box::pin(self.connect(args.identifier, args.reconnect, args.limits)).await;
            }
        }
    }

    /// The command channel closed (DD-APP-006): the recorder stops and the
    /// session is closed, or dropped without `close` when the output is on
    /// or unknown.
    async fn exit(&mut self) {
        log::info!(target: LOG_TARGET, "the UI is gone");
        self.stop_recording();
        match self.slot.kind() {
            SlotKind::Empty => {}
            SlotKind::Closing => {
                if let Slot::Closing { then, .. } = &mut self.slot {
                    if matches!(then, Then::Connect(_)) {
                        *then = Then::Report;
                    }
                }
            }
            // `Starting` is asked too: the session can be `Ready` before the
            // worker has seen it (DD-APP-006).
            SlotKind::Starting | SlotKind::Open => match self.decide_unasked() {
                Some(Unasked::Drop) => {
                    log::warn!(target: LOG_TARGET, "{}", texts::EXIT_WITHOUT_QUESTION);
                    self.drop_session();
                    // The UI is gone: no call needs its answer, so the
                    // futures go at once, and with them their clones of the
                    // session.
                    self.tasks.clear();
                    self.output_on_calls = 0;
                    self.scanning = false;
                }
                Some(Unasked::Close) | None => {
                    self.begin_close(false, Then::Report, None).await;
                }
            },
        }
    }
}

#[cfg(test)]
#[path = "worker_tests.rs"]
pub(crate) mod worker_tests;

#[cfg(test)]
mod tests {
    use super::*;

    /// Test: UT-APP-027
    #[test]
    fn an_unasked_disconnect_drops_only_a_ready_link_not_confirmed_off() {
        assert_eq!(unasked(true, false), Unasked::Drop);
        assert_eq!(unasked(true, true), Unasked::Close);
        assert_eq!(unasked(false, false), Unasked::Close);
        assert_eq!(unasked(false, true), Unasked::Close);
    }

    /// Test: UT-APP-019
    #[test]
    fn the_end_of_the_events_is_unexpected_unless_closing() {
        assert_eq!(on_events_end(SlotKind::Starting), EventsEnd::Unexpected);
        assert_eq!(on_events_end(SlotKind::Open), EventsEnd::Unexpected);
        assert_eq!(on_events_end(SlotKind::Closing), EventsEnd::Expected);
    }
}
