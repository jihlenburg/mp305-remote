//! Implements: DD-SESS-010, DD-SESS-011, DD-SESS-012, DD-SESS-020,
//! DD-SESS-021, DD-SESS-030, DD-SESS-031, DD-SESS-032, DD-SESS-033,
//! DD-SESS-034, DD-SESS-035, DD-SESS-040, DD-SESS-041, DD-SESS-042,
//! DD-SESS-050, DD-SESS-051, DD-SESS-053, DD-SESS-062.
//!
//! The session task: one loop over a `biased` select of five arms, in this
//! order: the link's events, the priority channel (`output_off`, `close`),
//! the step in progress (with the caller of a control command watched while
//! it waits), the reconnect timer, and the command channel. A step is one
//! awaited future ([`Step`]) with a tag that says what its result means
//! ([`Then`]); the operation it belongs to ([`Op`]) keeps the rest of its
//! data. The connect flow, every control command, the output-off and the
//! close run as steps, so readings, queries and the priority channel are
//! served while a step waits, for example during the 30 s bind wait, the
//! 70 s remote prompt or the settle wait after a `0xC9`.
//!
//! The task never awaits the event channels: readings go on a bounded
//! channel with `try_send` and are counted when dropped, everything else on
//! an unbounded one.

use std::collections::VecDeque;
use std::sync::atomic::Ordering;
use std::sync::Arc;
use std::time::SystemTime;

use core::future::{poll_fn, Future};
use core::pin::Pin;
use core::task::{Context, Poll};
use core::time::Duration;

use futures::future::BoxFuture;
use tokio::sync::{mpsc, oneshot, watch};
use tokio::time::{sleep_until, Instant, Sleep};

use crate::error::Error;
use crate::link::{DeviceEvent, Events, Link, LossReason, Outcome, Pending, Requested};
use crate::protocol::frame::Frame;
use crate::protocol::ops::bind::{self, BindReply, HostId};
use crate::protocol::ops::control::{self, Command as ControlCommand, ControlReply, RemoteCon};
use crate::protocol::ops::events::DeviceFrame;
use crate::protocol::ops::info::{self, Info};
use crate::protocol::ops::telemetry::{self, Faults, RawReading, Reading};
use crate::protocol::timing;
use crate::protocol::units::{self, Limits, RawCurrent, RawVoltage};
use crate::session::state::{
    check_copied, freshness, rejection_reason, setpoints_differ, Freshness, LinkInput, LinkMachine,
    RemoteInput, RemoteMachine,
};
use crate::session::{
    lock, texts, Command, CommandKind, Connector, LinkState, Markers, Priority, PromptKind,
    ReadyState, Registration, RemoteState, SessionEvent, Shared, TimedReading, LOG_TARGET,
};
use crate::transport::description::Kind;
use crate::transport::guarded::Guarded;
use crate::transport::AnyTransport;

/// The interval at which the unclean-exit marker is rewritten while the
/// output is on (DD-SESS-042).
const MARKER_INTERVAL: Duration = Duration::from_secs(1);

/// The reason given to commands an output-off drained from the queue.
const SUPERSEDED: &str = "superseded by an output-off";

/// The reason given to the command an output-off cancelled in progress.
const SUPERSEDED_IN_PROGRESS: &str = "superseded by an output-off; it may have been applied";

/// The reason given to a `close(true)` while a `close(false)` runs
/// (DD-SESS-053).
const CLOSE_RUNNING: &str = "a close without output-off is already running";

/// The answer channel of a call.
type Reply = oneshot::Sender<Result<(), Error>>;

/// Everything the task starts with.
pub(crate) struct Setup {
    /// Turns the identifier into a transport.
    pub(crate) connector: Arc<dyn Connector>,
    /// The identifier.
    pub(crate) identifier: String,
    /// The host ID presented at every bind.
    pub(crate) host_id: HostId,
    /// The marker store.
    pub(crate) markers: Arc<dyn Markers>,
    /// The fixed wall-clock origin, for tests.
    pub(crate) wall_origin: Option<SystemTime>,
    /// What the handle reads.
    pub(crate) shared: Arc<Shared>,
    /// The ready state.
    pub(crate) ready: watch::Sender<ReadyState>,
    /// Every event but readings.
    pub(crate) events: mpsc::UnboundedSender<SessionEvent>,
    /// Readings.
    pub(crate) readings: mpsc::Sender<SessionEvent>,
    /// Control commands.
    pub(crate) commands: mpsc::UnboundedReceiver<Command>,
    /// Output-off and close.
    pub(crate) priority: mpsc::UnboundedReceiver<Priority>,
    /// The registry entry.
    pub(crate) registration: Registration,
}

/// The one future the task awaits besides its channels, with the tag that
/// says what its result means. Every variant is `Unpin` (the sleep is
/// boxed), so the arm polls it in place.
enum Step {
    /// The connector's future.
    Connect(
        BoxFuture<'static, Result<Guarded<AnyTransport>, Error>>,
        Then,
    ),
    /// A request to the link.
    Request(Requested, Then),
    /// A deferred request's answer.
    Pending(Pending, Then),
    /// A wait until the settle time (DD-SESS-031).
    Sleep(Pin<Box<Sleep>>, Then),
    /// The link's close.
    CloseLink(BoxFuture<'static, Result<(), Error>>, Then),
}

/// What a step resolved with.
enum Done {
    /// The connector's result.
    Connect(Result<Guarded<AnyTransport>, Error>),
    /// A request's outcome.
    Request(Result<Outcome, Error>),
    /// A deferred request's answer and its arrival stamp.
    Pending(Result<(Frame, Instant), Error>),
    /// The settle time was reached.
    Slept,
    /// The link's close result.
    CloseLink(Result<(), Error>),
}

/// What a step's result is: the continuation tag of [`Step`].
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum Then {
    /// The connector returned.
    Connector,
    /// The fast bind's `0x19`.
    FastBind,
    /// The prompt bind was written (or failed).
    PromptBind,
    /// The prompt bind's `0x19`.
    BindWait,
    /// The `0xE1`.
    Info,
    /// The first reading of a connection.
    FirstReading,
    /// The link closed after a failed connect flow.
    ConnectClose,
    /// The settle time before a poll a command or the close needs.
    Settle,
    /// A `0xC2` for a reading a command, an output-off or the close needs.
    Poll,
    /// The remote request's `0xC8` (USB: its `0xC9`; Bluetooth: deferred).
    RemoteRequest,
    /// The remote request's deferred `0xC9`.
    RemoteWait,
    /// A command's `0xC9`.
    Command,
    /// The output-off's `0xC9`.
    OffCommand,
    /// The settle time before the reading after an output-off.
    OffSettle,
    /// The reading after an output-off.
    OffPoll,
    /// The release's `0xC9` during a close.
    Release,
    /// The link closed during a close.
    CloseLink,
}

impl Step {
    /// The continuation tag.
    fn then(&self) -> Then {
        match self {
            Step::Connect(_, then)
            | Step::Request(_, then)
            | Step::Pending(_, then)
            | Step::Sleep(_, then)
            | Step::CloseLink(_, then) => *then,
        }
    }

    /// Polls the future in place.
    fn poll_done(&mut self, cx: &mut Context<'_>) -> Poll<Done> {
        match self {
            Step::Connect(fut, _) => fut.as_mut().poll(cx).map(Done::Connect),
            Step::Request(fut, _) => Pin::new(fut).poll(cx).map(Done::Request),
            Step::Pending(fut, _) => Pin::new(fut).poll(cx).map(Done::Pending),
            Step::Sleep(fut, _) => fut.as_mut().poll(cx).map(|()| Done::Slept),
            Step::CloseLink(fut, _) => fut.as_mut().poll(cx).map(Done::CloseLink),
        }
    }
}

/// The operation a step belongs to.
enum Op {
    /// The connect flow or a reconnection attempt.
    Connect(ConnectOp),
    /// A control command.
    Control(ControlOp),
    /// An output-off.
    Off(OffOp),
    /// A close.
    Close(CloseOp),
}

/// The connect flow (DD-SESS-010).
#[derive(Debug)]
struct ConnectOp {
    /// A reconnection attempt rather than the first connection.
    reconnect: bool,
    /// The error the flow ends with once the link is closed.
    failure: Option<Error>,
}

/// A control command (DD-SESS-031 to DD-SESS-033).
#[derive(Debug)]
struct ControlOp {
    /// What the caller asked for.
    kind: CommandKind,
    /// The user's limits at the call.
    limits: Limits,
    /// The caller's answer channel.
    reply: Reply,
    /// The validated voltage of `set_voltage`.
    voltage: Option<RawVoltage>,
    /// The validated current of `set_current_limit`.
    current: Option<RawCurrent>,
    /// The reading the command is built from.
    reading: Option<RawReading>,
    /// The implicit remote request was made.
    requested: bool,
    /// The two raw setpoints the `0xC8` carries, once it is built.
    sent: Option<(u16, u16)>,
}

/// Why an output-off polls.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum OffNeed {
    /// For its start: the mode check and what the remote state asks for.
    Start,
    /// For the remote request it makes first.
    Request,
    /// For its own `0xC8`.
    Command,
}

/// An output-off (DD-SESS-035), alone or as part of a close.
#[derive(Debug)]
struct OffOp {
    /// The caller's answer channel; `None` inside a close, and once the
    /// caller was answered at the `0xC9`.
    reply: Option<Reply>,
    /// The output-off was retried after a status 1.
    retried: bool,
    /// What the pending poll is for.
    need: OffNeed,
    /// The reading the `0xC8` is built from, with the setpoints of
    /// `accepted` laid over it where DD-SESS-035 says.
    built: Option<RawReading>,
    /// The output-off belongs to a close.
    in_close: bool,
    /// When it began, on the Tokio clock.
    started_at: Instant,
    /// It ended with `Error::Mode` while a remote request was open: it only
    /// waits for that request, so that its outcome is applied to the state
    /// (DD-SESS-003), and sends nothing.
    only_await: bool,
}

/// Where a close is (DD-SESS-053).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum ClosePhase {
    /// Waiting for an open remote request.
    AwaitGrant,
    /// Waiting for the reading that decides the output-off.
    OffReading,
    /// Waiting for the reading the release is built from.
    ReleaseReading,
    /// Waiting for the release's `0xC9`.
    Release,
    /// Waiting for the link's close.
    Link,
}

/// A close in progress.
#[derive(Debug)]
struct CloseOp {
    /// Where it is.
    phase: ClosePhase,
}

/// How a remote request went.
enum RemoteStep {
    /// Granted.
    Granted,
    /// Waiting for the deferred answer; the step is set.
    Waiting,
    /// Failed with this error.
    Failed(Error),
}

/// What woke the loop.
enum Turn {
    /// The link's events: an event, or `None` when they ended.
    Event(Option<DeviceEvent>),
    /// The priority channel.
    Priority(Option<Priority>),
    /// The step resolved.
    Step(Done),
    /// The caller of the control command in progress left while its step
    /// waited (DD-SESS-003).
    CallerLeft,
    /// The reconnect timer fired.
    Tick,
    /// The command channel.
    Command(Option<Command>),
}

/// The reconnection schedule (DD-SESS-051).
#[derive(Clone, Copy, Debug)]
struct Reconnect {
    /// When the link was lost.
    loss_at: Instant,
    /// The attempts made so far.
    attempts: u32,
}

/// The setpoints of the last `0xC8` the supply accepted from this
/// connection, with the arrival of its `0xC9` (`accepted`, DD-SESS-033).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
struct Accepted {
    /// The raw voltage setpoint the `0xC8` carried.
    voltage: u16,
    /// The raw current limit the `0xC8` carried.
    current: u16,
    /// The arrival stamp of its `0xC9`.
    at: Instant,
}

/// The task's state.
pub(super) struct Task {
    /// Turns the identifier into a transport.
    connector: Arc<dyn Connector>,
    /// The identifier.
    identifier: String,
    /// The host ID.
    host_id: HostId,
    /// The marker store.
    markers: Arc<dyn Markers>,
    /// What the handle reads.
    shared: Arc<Shared>,
    /// The ready state.
    ready: watch::Sender<ReadyState>,
    /// Every event but readings; `None` once closed.
    events: Option<mpsc::UnboundedSender<SessionEvent>>,
    /// Readings; `None` once closed.
    readings: Option<mpsc::Sender<SessionEvent>>,
    /// Control commands.
    commands: mpsc::UnboundedReceiver<Command>,
    /// Output-off and close.
    priority: mpsc::UnboundedReceiver<Priority>,
    /// The registry entry.
    registration: Registration,
    /// The wall-clock time of `instant_origin`.
    wall_origin: SystemTime,
    /// The Tokio time the task started.
    instant_origin: Instant,
    /// The link, while one exists.
    link: Option<Link>,
    /// The link's events, until they ended or the link was dropped.
    link_events: Option<Events>,
    /// The kind of the current or last connection.
    kind: Option<Kind>,
    /// The link state machine.
    link_state: LinkMachine,
    /// The remote-control state.
    remote: RemoteState,
    /// The info of the current connection.
    info: Option<Info>,
    /// The latest reading with its arrival stamp.
    reading: Option<(RawReading, Instant)>,
    /// The faults of the previous reading of this connection.
    prev_faults: Option<Faults>,
    /// The settle time: a reading is fresh only if it arrived at or after
    /// it (DD-SESS-031, the terms of the session DD).
    settle_until: Option<Instant>,
    /// Resynchronising (DD-SESS-036): a `0xC8` timed out or a possibly
    /// written one was dropped; no reading is fresh until one more reading
    /// arrived, whose arrival plus `timing::SETTLE` becomes `settle_until`.
    resync: bool,
    /// The output state is unknown since a resynchronisation began, until a
    /// fresh reading arrived (DD-SESS-036).
    output_unknown: bool,
    /// The session reached `Ready` at least once (DD-SESS-053).
    was_ready: bool,
    /// The last accepted `0xC8` of this connection.
    accepted: Option<Accepted>,
    /// The raw setpoints the user set and the supply accepted.
    expected: (Option<u16>, Option<u16>),
    /// Compare the next settled reading with the expected setpoints; the
    /// reading the failed command was built from.
    compare_next: Option<RawReading>,
    /// A marker was set in this session or found at connect.
    marker_active: bool,
    /// When the marker was last written.
    marker_written: Option<Instant>,
    /// When the marker was last cleared, unless it was written since.
    marker_cleared_at: Option<Instant>,
    /// The text of the last loss, for the `LinkLost` answers.
    loss_text: String,
    /// The current generation.
    generation: u64,
    /// The operation in progress.
    op: Option<Op>,
    /// The step in progress.
    step: Option<Step>,
    /// Output-offs waiting for the one in progress.
    queued_offs: VecDeque<(u64, Reply)>,
    /// The next reconnect tick.
    tick: Option<Instant>,
    /// The reconnection schedule, while reconnecting.
    reconnect: Option<Reconnect>,
    /// A close has started.
    closing: bool,
    /// The state was `Ready` when the close started.
    close_from_ready: bool,
    /// The callers of `close`; all get the close's result.
    close_waiters: Vec<Reply>,
    /// The first error met by the close.
    close_error: Option<Error>,
    /// When the close started, on the Tokio clock.
    close_started_at: Option<Instant>,
    /// The close is to switch the output off.
    close_output_off: bool,
    /// The output state was unknown when the close started (after its own
    /// cancellations in (a)): its output-off goes out whatever the reading
    /// shows (DD-SESS-036, DD-SESS-053 (b)).
    close_output_unknown: bool,
    /// The close could not confirm the output off: its output-off failed,
    /// it was skipped outside DC mode with the output on, the reading for
    /// the decision could not be taken, or the link was lost (DD-SESS-053
    /// (c)).
    close_unconfirmed: bool,
    /// The task is done.
    finished: bool,
}

/// The task.
pub(crate) async fn run(setup: Setup) {
    let mut task = Task::new(setup);
    task.begin_connect(false);
    while !task.finished {
        task.turn().await;
    }
    task.answer_leftovers();
}

/// The next link event, or never when there is no link.
async fn next_event(events: &mut Option<Events>) -> Option<DeviceEvent> {
    match events {
        Some(events) => events.next().await,
        None => core::future::pending().await,
    }
}

/// Polls the step in place, or never resolves when there is none. While a
/// control command waits in a settle wait, a poll or for its `0xC9`, its
/// caller's answer channel is watched too, so that a command still queued
/// in the link is cancelled as soon as its caller is gone (DD-SESS-003).
fn poll_step(step: &mut Option<Step>, op: &mut Option<Op>, cx: &mut Context<'_>) -> Poll<Turn> {
    let Some(current) = step else {
        return Poll::Pending;
    };
    if let Poll::Ready(done) = current.poll_done(cx) {
        return Poll::Ready(Turn::Step(done));
    }
    let watched = matches!(current.then(), Then::Settle | Then::Poll | Then::Command);
    if let (true, Some(Op::Control(control))) = (watched, op) {
        if control.reply.poll_closed(cx).is_ready() {
            return Poll::Ready(Turn::CallerLeft);
        }
    }
    Poll::Pending
}

/// `at + d`, an overflow meaning `at`.
fn after(at: Instant, d: Duration) -> Instant {
    at.checked_add(d).unwrap_or(at)
}

/// The later of `current` and `candidate`.
fn later(current: Option<Instant>, candidate: Instant) -> Instant {
    current.map_or(candidate, |at| at.max(candidate))
}

/// The text of a `0xC9` other than 0 and 1 for [`Error::CommandRejected`].
fn status_text(status: u8) -> String {
    format!("status {status}")
}

/// The error a caller gets after the session was closed.
fn closed_error() -> Error {
    Error::LinkLost {
        text: texts::CLOSED_BY_HOST.to_string(),
    }
}

/// The error for a step result that does not fit its tag; the link's API
/// makes this unreachable.
fn unexpected(then: Then) -> Error {
    Error::Transport {
        message: format!("unexpected result for {then:?}"),
    }
}

impl Task {
    /// The task's state at start.
    fn new(setup: Setup) -> Self {
        Self {
            connector: setup.connector,
            identifier: setup.identifier,
            host_id: setup.host_id,
            markers: setup.markers,
            shared: setup.shared,
            ready: setup.ready,
            events: Some(setup.events),
            readings: Some(setup.readings),
            commands: setup.commands,
            priority: setup.priority,
            registration: setup.registration,
            wall_origin: setup.wall_origin.unwrap_or_else(SystemTime::now),
            instant_origin: Instant::now(),
            link: None,
            link_events: None,
            kind: None,
            link_state: LinkMachine::new(),
            remote: RemoteState::None,
            info: None,
            reading: None,
            prev_faults: None,
            settle_until: None,
            resync: false,
            output_unknown: false,
            was_ready: false,
            accepted: None,
            expected: (None, None),
            compare_next: None,
            marker_active: false,
            marker_written: None,
            marker_cleared_at: None,
            loss_text: String::new(),
            generation: 1,
            op: None,
            step: None,
            queued_offs: VecDeque::new(),
            tick: None,
            reconnect: None,
            closing: false,
            close_from_ready: false,
            close_waiters: Vec::new(),
            close_error: None,
            close_started_at: None,
            close_output_off: false,
            close_output_unknown: false,
            close_unconfirmed: false,
            finished: false,
        }
    }

    // ----- The loop -----

    /// One turn of the loop: the next turn of the select, handled, and the
    /// counters copied for the queries.
    pub(super) async fn turn(&mut self) {
        let turn = self.next_turn().await;
        self.handle(turn);
        self.refresh_counters();
    }

    /// Whether the command arm is enabled: no control-command step (a
    /// command or an output-off) is in progress. While a close runs the arm
    /// is enabled, so that every command is answered at once with "closed
    /// by the host" (DD-SESS-030, the closing flag).
    fn commands_enabled(&self) -> bool {
        self.closing || !matches!(self.op, Some(Op::Control(_) | Op::Off(_) | Op::Close(_)))
    }

    /// Waits for the next turn: the biased select of DD-SESS-030.
    async fn next_turn(&mut self) -> Turn {
        let events_on = self.link_events.is_some();
        let step_on = self.step.is_some();
        let tick = self.tick;
        let commands_on = self.commands_enabled();
        let link_events = &mut self.link_events;
        let step = &mut self.step;
        let op = &mut self.op;
        let priority = &mut self.priority;
        let commands = &mut self.commands;
        tokio::select! {
            biased;
            event = next_event(link_events), if events_on => Turn::Event(event),
            message = priority.recv() => Turn::Priority(message),
            turn = poll_fn(|cx| poll_step(step, op, cx)), if step_on => turn,
            () = sleep_until(tick.unwrap_or_else(Instant::now)), if tick.is_some() => Turn::Tick,
            command = commands.recv(), if commands_on => Turn::Command(command),
        }
    }

    /// Handles one turn.
    fn handle(&mut self, turn: Turn) {
        match turn {
            Turn::Event(Some(event)) => self.on_event(event),
            Turn::Event(None) => self.on_link_gone(&LossReason::Disconnected),
            Turn::Priority(Some(Priority::OutputOff { generation, reply })) => {
                self.on_output_off(generation, reply);
            }
            Turn::Priority(Some(Priority::Close { output_off, reply })) => {
                self.on_close(output_off, reply);
            }
            Turn::Step(done) => {
                if let Some(step) = self.step.take() {
                    self.on_done(step.then(), done);
                }
            }
            Turn::CallerLeft => self.on_caller_left(),
            Turn::Tick => self.on_tick(),
            Turn::Command(Some(command)) => self.on_command(command),
            // The handle was dropped; its drop aborts the task anyway.
            Turn::Priority(None) | Turn::Command(None) => self.finished = true,
        }
    }

    /// Copies the link's counters into the snapshot.
    fn refresh_counters(&self) {
        if let Some(link) = &self.link {
            lock(&self.shared.snapshot).counters = Some(link.counters());
        }
    }

    /// Answers what is left in the channels once the task ends: commands
    /// and output-offs with `LinkLost`, closes with the close's result.
    fn answer_leftovers(&mut self) {
        self.commands.close();
        self.priority.close();
        while let Ok(command) = self.commands.try_recv() {
            let _ = command.reply.send(Err(closed_error()));
        }
        let closed = lock(&self.shared.close_result)
            .clone()
            .unwrap_or_else(|| Err(closed_error()));
        while let Ok(message) = self.priority.try_recv() {
            match message {
                Priority::OutputOff { reply, .. } => {
                    let _ = reply.send(Err(closed_error()));
                }
                Priority::Close { reply, .. } => {
                    let _ = reply.send(closed.clone());
                }
            }
        }
    }

    /// Routes a step's result to the operation it belongs to.
    fn on_done(&mut self, then: Then, done: Done) {
        match self.op.take() {
            Some(Op::Connect(op)) => self.connect_done(op, then, done),
            Some(Op::Control(op)) => self.control_done(op, then, done),
            Some(Op::Off(op)) => self.off_done(op, then, done),
            Some(Op::Close(op)) => self.close_done(op, then, done),
            None => {
                log::debug!(target: LOG_TARGET, "step {then:?} without an operation");
            }
        }
    }

    // ----- Events, state and logging -----

    /// Sends an event on the unbounded channel.
    fn emit(&self, event: SessionEvent) {
        #[cfg(test)]
        lock(&self.shared.trace).push(format!("event {event:?}"));
        if let Some(events) = &self.events {
            // A product that dropped its receiver gets nothing more.
            let _ = events.send(event);
        }
    }

    /// Feeds the link state machine, logs a change and updates the
    /// snapshot.
    fn link_input(&mut self, input: LinkInput) {
        if let Some(new) = self.link_apply(input) {
            self.publish_link_state(new);
        }
    }

    /// Feeds the link state machine and logs a change, without updating the
    /// snapshot; the new state, or `None` for a pair outside the table.
    fn link_apply(&mut self, input: LinkInput) -> Option<LinkState> {
        let old = self.link_state.state;
        match self.link_state.apply(input) {
            Ok(new) => {
                if new != old {
                    log::info!(target: LOG_TARGET, "link {old} -> {new}");
                }
                Some(new)
            }
            Err(state) => {
                log::debug!(target: LOG_TARGET, "link {state}: {input:?} ignored");
                None
            }
        }
    }

    /// Copies `state` into the snapshot the queries read.
    fn publish_link_state(&self, state: LinkState) {
        let mut snapshot = lock(&self.shared.snapshot);
        #[cfg(test)]
        if snapshot.link_state != state {
            lock(&self.shared.trace).push(format!("state {state}"));
        }
        snapshot.link_state = state;
    }

    /// Feeds the remote-control state machine; a change is logged, emitted
    /// and copied into the snapshot.
    fn remote_input(&mut self, input: RemoteInput) {
        let old = self.remote;
        let new = RemoteMachine(old).on(input);
        if new != old {
            self.remote = new;
            log::info!(target: LOG_TARGET, "remote {old} -> {new}");
            lock(&self.shared.snapshot).remote_state = new;
            self.emit(SessionEvent::RemoteControl(new));
        }
    }

    /// Sets the ready state.
    fn set_ready(&self, state: ReadyState) {
        self.ready.send_replace(state);
    }

    /// The error a command gets while the link is lost.
    fn lost_error(&self) -> Error {
        Error::LinkLost {
            text: self.loss_text.clone(),
        }
    }

    /// Logs the USB host hint with a Bluetooth timeout (DD-SESS-050).
    fn note_error(&self, error: &Error) {
        if matches!(error, Error::Timeout { .. }) && self.kind == Some(Kind::Ble) {
            log::warn!(target: LOG_TARGET, "{error}.{}", texts::USB_HOST_HINT);
        }
    }

    /// Records a handled `0xC9` that arrived at `at`: the settle time moves
    /// to `at + timing::SETTLE` unless it is later already.
    fn note_c9(&mut self, at: Instant) {
        self.settle_until = Some(later(self.settle_until, after(at, timing::SETTLE)));
    }

    /// A command or an output-off whose `0xC8` may have been written was
    /// cancelled: its effect is unknown, so the setpoints are compared with
    /// the next settled reading (`built_from` being the reading it was built
    /// from) and the session resynchronises (DD-SESS-035 (b), DD-SESS-036).
    fn cancel_possibly_written(&mut self, built_from: Option<RawReading>) {
        self.setpoints_unknown(built_from);
        self.resynchronise();
    }

    /// Resynchronisation (DD-SESS-036): the supply may still apply a `0xC8`
    /// that timed out or was dropped. No reading is fresh until one more
    /// reading arrived (the link writes no request before the old frame was
    /// answered or timed out, so that reading was requested after it), and
    /// the output state is unknown until a fresh reading arrived.
    fn resynchronise(&mut self) {
        log::debug!(target: LOG_TARGET, "resynchronising: a 0xc8 may still be applied");
        self.resync = true;
        self.output_unknown = true;
    }

    /// Calls `f` on the marker store and logs a failure at WARN.
    fn marker_call(&self, what: &str, f: impl FnOnce(&dyn Markers, &str) -> Result<(), Error>) {
        if let Err(error) = f(self.markers.as_ref(), &self.identifier) {
            log::warn!(target: LOG_TARGET, "marker {what} failed: {error}");
        }
    }

    /// Clears the marker and forgets that one is active.
    fn clear_marker(&mut self) {
        self.marker_call("clear", |m, id| m.clear(id));
        self.marker_active = false;
        self.marker_written = None;
        self.marker_cleared_at = Some(Instant::now());
    }

    /// Whether the marker was cleared at or after `since` and not written
    /// again: an output-off or a close that began at `since` then leaves the
    /// store alone, so that it clears the marker once.
    fn cleared_since(&self, since: Instant) -> bool {
        self.marker_cleared_at.is_some_and(|at| at >= since)
    }

    /// The wall-clock time of the Tokio instant `at` (DD-SESS-004).
    fn wall(&self, at: Instant) -> SystemTime {
        at.checked_duration_since(self.instant_origin)
            .and_then(|d| self.wall_origin.checked_add(d))
            .unwrap_or(self.wall_origin)
    }

    /// Handles one event of the link.
    fn on_event(&mut self, event: DeviceEvent) {
        match event {
            DeviceEvent::Reading { reading, at } => self.on_reading(reading, at),
            DeviceEvent::Device(DeviceFrame::Settings(settings)) => {
                self.emit(SessionEvent::SettingsChanged(settings));
            }
            DeviceEvent::Device(other) => {
                log::debug!(target: LOG_TARGET, "ignored device frame {other:?}");
            }
            DeviceEvent::LateReply { frame, at } => {
                log::warn!(
                    target: LOG_TARGET,
                    "late reply 0x{:02x} status {:?} ignored",
                    frame.opcode(),
                    frame.payload().first()
                );
                // A late `0xC9` belongs to a `0xC8` the supply has just
                // handled: it moves the settle time like any `0xC9`
                // (DD-SESS-034).
                if frame.opcode() == control::REPLY {
                    self.note_c9(at);
                }
            }
            DeviceEvent::LinkLost { reason } => self.on_link_gone(&reason),
        }
    }

    /// A reading from the link (DD-SESS-040, DD-SESS-042). The first reading
    /// of a resynchronisation ends it and sets the settle time from its
    /// arrival (DD-SESS-036); a reading at or after the settle time is fresh
    /// and makes the output state known again. The comparison after a
    /// failed command runs on the first fresh reading, so that it sees the
    /// command's effect.
    fn on_reading(&mut self, raw: RawReading, at: Instant) {
        let timed = TimedReading {
            at,
            wall: self.wall(at),
            reading: Reading::from_raw(&raw),
        };
        self.reading = Some((raw, at));
        lock(&self.shared.snapshot).reading = Some(timed);
        if let Some(readings) = &self.readings {
            if let Err(mpsc::error::TrySendError::Full(_)) =
                readings.try_send(SessionEvent::Reading(timed))
            {
                let _ = self.shared.dropped_readings.fetch_update(
                    Ordering::SeqCst,
                    Ordering::SeqCst,
                    |n| Some(n.saturating_add(1)),
                );
            }
        }
        let faults = Faults(raw.charge_error);
        let changed = match self.prev_faults {
            Some(previous) => previous != faults,
            None => !faults.is_empty(),
        };
        self.prev_faults = Some(faults);
        if changed {
            self.emit(SessionEvent::FaultsChanged {
                faults,
                reading: timed,
            });
        }
        let settled = if self.resync {
            self.resync = false;
            self.settle_until = Some(later(self.settle_until, after(at, timing::SETTLE)));
            false
        } else {
            self.settle_until.is_none_or(|until| at >= until)
        };
        if settled {
            self.output_unknown = false;
            if let Some(built_from) = self.compare_next.take() {
                if let Some((sv, sc, ev, ec)) = setpoints_differ(&raw, self.expected, &built_from) {
                    self.emit(SessionEvent::SetpointsChanged {
                        set_volts: units::volts(sv),
                        set_amps: units::amps(sc),
                        expected_volts: units::volts(ev),
                        expected_amps: units::amps(ec),
                    });
                }
            }
        }
        if self.remote == RemoteState::Granted && raw.output != 0 {
            let due = self
                .marker_written
                .is_none_or(|last| at >= after(last, MARKER_INTERVAL));
            if due {
                let wall = timed.wall;
                self.marker_call("set", |m, id| m.set(id, wall));
                self.marker_written = Some(at);
                self.marker_cleared_at = None;
                self.marker_active = true;
            }
        } else if raw.output == 0 && self.marker_active {
            self.clear_marker();
        }
    }

    /// Marks the setpoints unknown: the next settled reading is compared
    /// with the expected ones (DD-SESS-033).
    fn setpoints_unknown(&mut self, built_from: Option<RawReading>) {
        self.compare_next = built_from.or_else(|| self.reading.map(|(raw, _)| raw));
    }

    // ----- Readings for commands (DD-SESS-031) -----

    /// Starts a `0xC2` whose reply the operation in progress uses, tagged
    /// `then`.
    fn start_poll(&mut self, then: Then) -> Result<(), Error> {
        let link = self.link.as_ref().ok_or_else(|| self.lost_error())?;
        self.step = Some(Step::Request(link.request(telemetry::request()), then));
        Ok(())
    }

    /// The reading the latest reading cannot be: waits until the settle
    /// time if it is still ahead (a `Sleep` step tagged [`Then::Settle`]),
    /// else starts the poll at once (tagged [`Then::Poll`]); while the
    /// session resynchronises the poll goes at once, since its reply is the
    /// reading that ends the resynchronisation. `poll first: <why>` is
    /// logged.
    fn need_reading(&mut self, why: &str) -> Result<(), Error> {
        if self.link.is_none() {
            return Err(self.lost_error());
        }
        let now = Instant::now();
        match self
            .settle_until
            .filter(|until| !self.resync && *until > now)
        {
            Some(until) => {
                log::debug!(
                    target: LOG_TARGET,
                    "poll first: {why}; settle wait {} ms",
                    until.saturating_duration_since(now).as_millis()
                );
                self.step = Some(Step::Sleep(Box::pin(sleep_until(until)), Then::Settle));
                Ok(())
            }
            None => {
                log::debug!(target: LOG_TARGET, "poll first: {why}");
                self.start_poll(Then::Poll)
            }
        }
    }

    /// After a wait for the settle time (tagged `settle`): waits again if
    /// the settle time moved further (a late `0xC9`, DD-SESS-034), else
    /// starts the poll (tagged `poll`); while the session resynchronises
    /// the poll goes at once.
    fn settle_then_poll(&mut self, settle: Then, poll: Then) -> Result<(), Error> {
        if self.link.is_none() {
            return Err(self.lost_error());
        }
        let now = Instant::now();
        match self
            .settle_until
            .filter(|until| !self.resync && *until > now)
        {
            Some(until) => {
                self.step = Some(Step::Sleep(Box::pin(sleep_until(until)), settle));
                Ok(())
            }
            None => self.start_poll(poll),
        }
    }

    /// The reading of a polled `0xC2` with its arrival stamp.
    fn polled_reading(&self, done: Done) -> Result<(RawReading, Instant), Error> {
        match done {
            Done::Request(Ok(Outcome::Reply { frame, at })) => telemetry::parse(&frame)
                .map(|raw| (raw, at))
                .map_err(Error::Protocol),
            Done::Request(Err(error)) => {
                self.note_error(&error);
                Err(error)
            }
            _ => Err(unexpected(Then::Poll)),
        }
    }

    /// Whether a reading that arrived at `at` is fresh now: no
    /// resynchronisation is pending and it arrived at or after the settle
    /// time, at most `timing::REPLY` ago. A polled reading is normally
    /// fresh by construction; it is not when a resynchronisation or a late
    /// `0xC9` moved the settle time past it.
    fn fresh_at(&self, at: Instant) -> bool {
        !self.resync && freshness(Some(at), self.settle_until, Instant::now()) == Freshness::Fresh
    }

    /// The latest reading if it is fresh (DD-SESS-031), else why not.
    fn fresh_reading(&self) -> Result<RawReading, &'static str> {
        if self.resync {
            return Err("resynchronising after a 0xc8 that may have been applied");
        }
        let at = self.reading.map(|(_, at)| at);
        match freshness(at, self.settle_until, Instant::now()) {
            Freshness::Fresh => self.reading.map(|(raw, _)| raw).ok_or("no reading"),
            Freshness::Stale(why) => Err(why),
            Freshness::None => Err("no reading"),
        }
    }

    // ----- The connect flow (DD-SESS-010 to DD-SESS-012, DD-SESS-051) -----

    /// Starts the connect flow; a reconnection attempt takes a new
    /// generation. The fault comparison and `accepted` start afresh.
    fn begin_connect(&mut self, reconnect: bool) {
        if reconnect {
            self.new_generation();
        }
        self.prev_faults = None;
        self.accepted = None;
        let connector = Arc::clone(&self.connector);
        let identifier = self.identifier.clone();
        self.step = Some(Step::Connect(
            Box::pin(async move { connector.connect(&identifier).await }),
            Then::Connector,
        ));
        self.op = Some(Op::Connect(ConnectOp {
            reconnect,
            failure: None,
        }));
    }

    /// Increments the generation, here and for the handle.
    fn new_generation(&mut self) {
        self.generation = self.generation.saturating_add(1);
        self.shared
            .generation
            .store(self.generation, Ordering::SeqCst);
    }

    /// Sends `frame` as a connect-flow request with the tag `then`.
    fn connect_request(&mut self, op: ConnectOp, frame: Frame, then: Then) {
        match &self.link {
            Some(link) => {
                self.step = Some(Step::Request(link.request(frame), then));
                self.op = Some(Op::Connect(op));
            }
            None => {
                let lost = self.lost_error();
                self.end_connect(op, lost);
            }
        }
    }

    /// Handles a step of the connect flow.
    fn connect_done(&mut self, op: ConnectOp, then: Then, done: Done) {
        match (then, done) {
            (Then::Connector, Done::Connect(Ok(guard))) => self.connected(op, guard),
            (Then::Connector, Done::Connect(Err(error))) => self.end_connect(op, error),
            (Then::FastBind, Done::Request(result)) => self.fast_bind_done(op, result),
            (Then::PromptBind, Done::Request(Ok(Outcome::Deferred(pending)))) => {
                log::warn!(target: LOG_TARGET, "{}", texts::CONFIRM_CONNECTION);
                self.emit(SessionEvent::Prompt {
                    kind: PromptKind::ConfirmConnection,
                    bound_s: 30,
                    text: texts::CONFIRM_CONNECTION,
                });
                self.step = Some(Step::Pending(pending, Then::BindWait));
                self.op = Some(Op::Connect(op));
            }
            (Then::PromptBind, Done::Request(Ok(Outcome::Reply { frame, .. })))
            | (Then::BindWait, Done::Pending(Ok((frame, _)))) => match bind::parse(&frame) {
                Ok(BindReply::Allowed) => self.allowed(op, false),
                _ => self.fail_connect(op, Error::ConnectionDenied),
            },
            (Then::PromptBind, Done::Request(Err(error)))
            | (Then::BindWait, Done::Pending(Err(error))) => {
                self.note_error(&error);
                let error = match error {
                    Error::Timeout { opcode, .. } => Error::Timeout {
                        opcode,
                        after: timing::BIND,
                    },
                    other => other,
                };
                self.connect_error(op, error);
            }
            (Then::Info, Done::Request(Ok(Outcome::Reply { frame, .. }))) => {
                match info::parse(&frame) {
                    Ok(info) => self.got_info(op, info),
                    Err(reason) => self.fail_connect(op, Error::Protocol(reason)),
                }
            }
            (Then::FirstReading, Done::Request(Ok(Outcome::Reply { frame, at }))) => {
                match telemetry::parse(&frame) {
                    Ok(raw) => self.first_reading(op, raw, at),
                    Err(reason) => self.fail_connect(op, Error::Protocol(reason)),
                }
            }
            (Then::Info | Then::FirstReading, Done::Request(Err(error))) => {
                self.note_error(&error);
                self.connect_error(op, error);
            }
            (Then::ConnectClose, Done::CloseLink(_)) => {
                let error = op.failure.clone().unwrap_or_else(|| self.lost_error());
                self.end_connect(op, error);
            }
            (then, _) => self.fail_connect(op, unexpected(then)),
        }
    }

    /// The connector returned a transport: start the link, then the bind
    /// (Bluetooth) or the info request (USB).
    fn connected(&mut self, op: ConnectOp, guard: Guarded<AnyTransport>) {
        let description = guard.description().clone();
        let (link, events) = match Link::start(guard, Instant::now()) {
            Ok(started) => started,
            Err(error) => {
                self.end_connect(op, error);
                return;
            }
        };
        let kind = description.kind;
        self.kind = Some(kind);
        lock(&self.shared.snapshot).kind = Some(kind);
        log::info!(target: LOG_TARGET, "connected {description}");
        self.link = Some(link);
        self.link_events = Some(events);
        if !op.reconnect {
            self.link_input(LinkInput::Connected(kind));
        }
        match kind {
            Kind::Ble => {
                if !op.reconnect {
                    self.link_input(LinkInput::BindStarted);
                }
                let frame = bind::request(&self.host_id, true);
                self.connect_request(op, frame, Then::FastBind);
            }
            Kind::Hid => self.connect_request(op, info::request(), Then::Info),
        }
    }

    /// The fast bind's outcome (DD-SESS-011): `19 00` allows, `19 FF` on the
    /// first connection asks for the prompt bind, any other reply denies.
    fn fast_bind_done(&mut self, op: ConnectOp, result: Result<Outcome, Error>) {
        match result {
            Ok(Outcome::Reply { frame, .. }) => match bind::parse(&frame) {
                Ok(BindReply::Allowed) => self.allowed(op, true),
                Ok(BindReply::Denied) if !op.reconnect => {
                    let frame = bind::request(&self.host_id, false);
                    self.connect_request(op, frame, Then::PromptBind);
                }
                _ => self.fail_connect(op, Error::ConnectionDenied),
            },
            Ok(Outcome::Deferred(_)) => self.fail_connect(op, unexpected(Then::FastBind)),
            Err(error) => {
                self.note_error(&error);
                let error = match error {
                    Error::Timeout { opcode, .. } => Error::Timeout {
                        opcode,
                        after: timing::REPLY,
                    },
                    other => other,
                };
                self.connect_error(op, error);
            }
        }
    }

    /// The bind gave `19 00`: on to the info request.
    fn allowed(&mut self, op: ConnectOp, recognised: bool) {
        if !op.reconnect {
            self.link_input(LinkInput::Allowed);
        }
        self.emit(SessionEvent::BindResult { recognised });
        self.connect_request(op, info::request(), Then::Info);
    }

    /// The `0xE1` arrived: store it (over USB it is the "allowed" signal)
    /// and ask for the first reading.
    fn got_info(&mut self, op: ConnectOp, info: Info) {
        if !op.reconnect && self.kind == Some(Kind::Hid) {
            self.link_input(LinkInput::Allowed);
        }
        lock(&self.shared.snapshot).info = Some(info.clone());
        self.info = Some(info);
        self.connect_request(op, telemetry::request(), Then::FirstReading);
    }

    /// The first reading arrived (the event path stored it already): the
    /// marker check on the first connection, polling on, `Ready`. A marker
    /// found while the first reading shows the output off is cleared at
    /// once (DD-SESS-042).
    fn first_reading(&mut self, op: ConnectOp, raw: RawReading, at: Instant) {
        if self.reading.is_none_or(|(_, stored)| stored < at) {
            self.reading = Some((raw, at));
        }
        if !op.reconnect {
            match self.markers.present(&self.identifier) {
                Ok(Some(since)) => {
                    self.marker_active = true;
                    self.emit(SessionEvent::UncleanExitWarning {
                        since,
                        text: texts::unclean_exit(since),
                    });
                    if raw.output == 0 {
                        self.clear_marker();
                    }
                }
                Ok(None) => {}
                Err(error) => {
                    log::warn!(target: LOG_TARGET, "marker present failed: {error}");
                }
            }
        }
        if let Some(link) = &self.link {
            link.set_polling(true);
        }
        self.was_ready = true;
        self.link_input(LinkInput::Ready);
        let info = self.info.clone();
        if let Some(info) = &info {
            log::info!(target: LOG_TARGET, "ready {} {}", info.model, info.version);
            self.set_ready(ReadyState::Ready(info.clone()));
        }
        if op.reconnect {
            self.reconnect = None;
            self.tick = None;
            self.emit(SessionEvent::Reconnected);
            self.remote_input(RemoteInput::Reconnected);
        }
    }

    /// A request of the flow failed with `error`. An `Error::LinkLost`
    /// means the link is ending: its `DeviceEvent::LinkLost` (or the end of
    /// its events) follows, and the loss is handled once, there
    /// (DD-SESS-010, DD-SESS-050). The flow waits for it without a step,
    /// whichever of the two the task saw first. Any other error ends the
    /// flow.
    fn connect_error(&mut self, op: ConnectOp, error: Error) {
        if matches!(error, Error::LinkLost { .. }) {
            log::debug!(target: LOG_TARGET, "connect flow: {error}; handled as the loss");
            self.op = Some(Op::Connect(op));
            if self.link_events.is_none() {
                // The events ended already; that is a disconnect.
                self.on_link_gone(&LossReason::Disconnected);
            }
            return;
        }
        self.fail_connect(op, error);
    }

    /// Ends the flow with `error`, closing the link first.
    fn fail_connect(&mut self, mut op: ConnectOp, error: Error) {
        self.link_events = None;
        match self.link.take() {
            Some(link) => {
                op.failure = Some(error);
                self.step = Some(Step::CloseLink(Box::pin(link.close()), Then::ConnectClose));
                self.op = Some(Op::Connect(op));
            }
            None => self.end_connect(op, error),
        }
    }

    /// The flow ended with `error` and the link is gone. On the first
    /// connection the state is `Denied` after a deny and `Lost` otherwise,
    /// with the error's text as the loss text and no `LinkLost` event
    /// (DD-SESS-010).
    fn end_connect(&mut self, op: ConnectOp, error: Error) {
        self.link = None;
        self.link_events = None;
        if op.reconnect {
            log::info!(target: LOG_TARGET, "reconnect attempt failed: {error}");
            if error == Error::ConnectionDenied {
                self.link_input(LinkInput::Denied);
                self.give_up(texts::GAVE_UP_UNRECOGNISED);
                return;
            }
            self.link_input(LinkInput::Lost);
            let expired = self
                .reconnect
                .is_some_and(|r| Instant::now() >= after(r.loss_at, timing::RECONNECT_GIVE_UP));
            if expired {
                self.give_up(texts::GAVE_UP_TIMEOUT);
            }
            return;
        }
        if error == Error::ConnectionDenied {
            self.link_input(LinkInput::Denied);
        } else {
            self.link_input(LinkInput::Lost);
        }
        self.loss_text = error.to_string();
        self.set_ready(ReadyState::Failed(error));
    }

    // ----- Loss and reconnection (DD-SESS-050, DD-SESS-051) -----

    /// The link's events reported a loss or ended: handled once per
    /// connection, and never after the session closed the link itself. A
    /// loss during a close only means the close cannot confirm the output
    /// off (DD-SESS-053 (c)); its steps resolve with the link's error.
    fn on_link_gone(&mut self, reason: &LossReason) {
        self.link_events = None;
        self.link = None;
        if self.closing {
            self.close_unconfirmed = true;
            self.loss_text = reason.to_string();
            return;
        }
        match self.op.take() {
            Some(Op::Connect(op)) if op.reconnect => {
                self.step = None;
                self.end_connect(
                    op,
                    Error::LinkLost {
                        text: reason.to_string(),
                    },
                );
            }
            Some(Op::Connect(_)) => {
                self.step = None;
                let text = texts::lost_while_connecting(reason);
                log::warn!(target: LOG_TARGET, "{text}");
                self.link_input(LinkInput::Lost);
                self.loss_text.clone_from(&text);
                self.set_ready(ReadyState::Failed(Error::LinkLost { text: text.clone() }));
                self.emit(SessionEvent::LinkLost { text });
            }
            other => self.lost(reason, other),
        }
    }

    /// Loss handling after the session was ready (DD-SESS-050).
    fn lost(&mut self, reason: &LossReason, op: Option<Op>) {
        let kind = self.kind.unwrap_or(Kind::Ble);
        let text = texts::link_lost(reason, kind);
        log::warn!(target: LOG_TARGET, "{text}");
        self.loss_text.clone_from(&text);
        let session_error = self.lost_error();
        // The command in progress gets the link's error if its step already
        // resolved with it, else the session's text.
        let link_error = self.step.take().and_then(|mut step| {
            let mut cx = Context::from_waker(core::task::Waker::noop());
            match step.poll_done(&mut cx) {
                Poll::Ready(Done::Request(Err(error)) | Done::Pending(Err(error))) => Some(error),
                _ => None,
            }
        });
        let answer = link_error.unwrap_or_else(|| session_error.clone());
        match op {
            Some(Op::Control(op)) => {
                let _ = op.reply.send(Err(answer));
            }
            Some(Op::Off(op)) => {
                if let Some(reply) = op.reply {
                    let _ = reply.send(Err(answer));
                }
            }
            _ => {}
        }
        // The loss and the reconnect decision update the shared state as
        // one step: with reconnection the queries see `Reconnecting`
        // directly, never `Lost` in between (DD-SESS-050).
        let reconnect = self.shared.reconnect.load(Ordering::SeqCst);
        if reconnect {
            self.link_apply(LinkInput::Lost);
            self.link_input(LinkInput::RetryScheduled);
        } else {
            self.link_input(LinkInput::Lost);
        }
        self.remote_input(RemoteInput::LinkLost);
        while let Ok(command) = self.commands.try_recv() {
            let _ = command.reply.send(Err(session_error.clone()));
        }
        for (_, reply) in self.queued_offs.drain(..) {
            let _ = reply.send(Err(session_error.clone()));
        }
        self.setpoints_unknown(None);
        self.new_generation();
        if reconnect {
            let now = Instant::now();
            self.set_ready(ReadyState::Pending);
            self.reconnect = Some(Reconnect {
                loss_at: now,
                attempts: 0,
            });
            self.tick = Some(after(now, timing::RECONNECT_RETRY));
        } else {
            self.set_ready(ReadyState::Failed(session_error));
        }
        // After the state update.
        self.emit(SessionEvent::LinkLost { text });
    }

    /// The reconnect timer fired (DD-SESS-051).
    fn on_tick(&mut self) {
        let Some(mut schedule) = self.reconnect else {
            self.tick = None;
            return;
        };
        let now = Instant::now();
        let fired = self.tick.unwrap_or(now);
        self.tick = Some(after(fired, timing::RECONNECT_RETRY));
        let attempt_running = matches!(self.op, Some(Op::Connect(_)));
        if !self.shared.reconnect.load(Ordering::SeqCst) {
            self.op = None;
            self.step = None;
            self.link = None;
            self.link_events = None;
            self.give_up(texts::GAVE_UP_SWITCHED_OFF);
            return;
        }
        if now >= after(schedule.loss_at, timing::RECONNECT_GIVE_UP) {
            if attempt_running {
                // The attempt may finish; a failure then gives up.
                self.tick = None;
            } else {
                self.give_up(texts::GAVE_UP_TIMEOUT);
            }
            return;
        }
        if attempt_running {
            log::debug!(target: LOG_TARGET, "reconnect tick skipped: an attempt is running");
            return;
        }
        schedule.attempts = schedule.attempts.saturating_add(1);
        self.reconnect = Some(schedule);
        log::info!(target: LOG_TARGET, "reconnect attempt {}", schedule.attempts);
        self.begin_connect(true);
    }

    /// Ends the reconnection with the give-up `text`.
    fn give_up(&mut self, text: &str) {
        self.reconnect = None;
        self.tick = None;
        self.link_input(LinkInput::GaveUp);
        log::warn!(target: LOG_TARGET, "{text}");
        self.set_ready(ReadyState::Failed(self.lost_error()));
        self.emit(SessionEvent::ReconnectGaveUp {
            text: text.to_string(),
        });
    }

    // ----- Commands (DD-SESS-030 to DD-SESS-033, DD-SESS-020, DD-SESS-021) -----

    /// Guard (1) of DD-SESS-032: the link-state answers and the generation.
    fn link_guard(&self, generation: u64) -> Result<(), Error> {
        if self.closing {
            return Err(closed_error());
        }
        match self.link_state.state {
            LinkState::Connecting
            | LinkState::Connected
            | LinkState::Binding
            | LinkState::Allowed => Err(Error::NotReady),
            LinkState::Lost | LinkState::Reconnecting => Err(self.lost_error()),
            LinkState::Denied => Err(Error::ConnectionDenied),
            LinkState::Closed => Err(closed_error()),
            LinkState::Ready if generation < self.generation => Err(self.lost_error()),
            LinkState::Ready => Ok(()),
        }
    }

    /// A command from the channel: discarded if its caller left, answered
    /// at once by the link state unless ready, else started.
    fn on_command(&mut self, command: Command) {
        if command.reply.is_closed() {
            log::debug!(target: LOG_TARGET, "cancelled: {:?}, the caller is gone", command.kind);
            return;
        }
        if let Err(error) = self.link_guard(command.generation) {
            let _ = command.reply.send(Err(error));
            return;
        }
        self.begin_control(command);
    }

    /// Guards (2) and (3), then the reading.
    fn begin_control(&mut self, command: Command) {
        let Command {
            kind,
            limits,
            reply,
            ..
        } = command;
        let early = match (kind, self.remote) {
            (CommandKind::Request, RemoteState::Granted)
            | (CommandKind::Release, RemoteState::None) => Some(Ok(())),
            (CommandKind::Request | CommandKind::Release, _) => None,
            (_, RemoteState::Denied) => Some(Err(Error::RemoteControlDenied)),
            (_, RemoteState::Lost) => Some(Err(Error::RemoteControlLost)),
            _ => None,
        };
        if let Some(result) = early {
            log::debug!(target: LOG_TARGET, "command {kind:?}: {result:?}");
            let _ = reply.send(result);
            return;
        }
        let setpoint = match kind {
            CommandKind::SetVoltage(volts) => {
                RawVoltage::from_volts(volts, &limits).map(|v| (Some(v), None))
            }
            CommandKind::SetCurrent(amps) => {
                RawCurrent::from_amps(amps, &limits).map(|c| (None, Some(c)))
            }
            _ => Ok((None, None)),
        };
        match setpoint {
            Ok((voltage, current)) => self.control_reading(ControlOp {
                kind,
                limits,
                reply,
                voltage,
                current,
                reading: None,
                requested: false,
                sent: None,
            }),
            Err(error) => {
                log::debug!(target: LOG_TARGET, "command {kind:?}: {error}");
                let _ = reply.send(Err(error));
            }
        }
    }

    /// Answers a command and ends it.
    fn finish_control(&mut self, op: ControlOp, result: Result<(), Error>) {
        log::debug!(target: LOG_TARGET, "command {:?}: {result:?}", op.kind);
        let _ = op.reply.send(result);
    }

    /// Whether the caller left; logs the cancellation (DD-SESS-003).
    fn caller_gone(op: &ControlOp) -> bool {
        let gone = op.reply.is_closed();
        if gone {
            log::debug!(target: LOG_TARGET, "cancelled: {:?}, the caller is gone", op.kind);
        }
        gone
    }

    /// The caller of the command in progress left while its step waited
    /// (DD-SESS-003): the step is dropped, so a request still queued in the
    /// link is cancelled there (DD-LINK-022). A dropped `0xC8` may have been
    /// written already: its effect is treated as DD-SESS-035 (b) says.
    fn on_caller_left(&mut self) {
        match self.op.take() {
            Some(Op::Control(op)) => {
                log::debug!(target: LOG_TARGET, "cancelled: {:?}, the caller is gone", op.kind);
                self.drop_cancelled_step(op.reading);
            }
            other => self.op = other,
        }
    }

    /// Guard (4): a fresh reading, waited and polled for when needed.
    fn control_reading(&mut self, op: ControlOp) {
        match self.fresh_reading() {
            Ok(reading) => self.control_checks(op, reading),
            Err(why) => {
                if Self::caller_gone(&op) {
                    return;
                }
                match self.need_reading(why) {
                    Ok(()) => self.op = Some(Op::Control(op)),
                    Err(error) => self.finish_control(op, Err(error)),
                }
            }
        }
    }

    /// The two raw setpoints the command's `0xC8` carries when it is built
    /// from `reading`.
    fn frame_setpoints(op: &ControlOp, reading: &RawReading) -> (u16, u16) {
        (
            op.voltage.map_or(reading.set_voltage, RawVoltage::raw),
            op.current.map_or(reading.set_current, RawCurrent::raw),
        )
    }

    /// Guards (5) to (8), then the command.
    fn control_checks(&mut self, mut op: ControlOp, reading: RawReading) {
        op.reading = Some(reading);
        // (5) DC mode.
        if reading.model != 0 {
            let error = Error::Mode {
                live_mode: reading.model,
            };
            self.finish_control(op, Err(error));
            return;
        }
        // (6) No fault for an output-on.
        if op.kind == CommandKind::OutputOn && reading.charge_error != 0 {
            let faults = Faults(reading.charge_error);
            self.finish_control(op, Err(Error::FaultActive { faults }));
            return;
        }
        // (7) The user limits on what a frame with `output` 1 carries.
        let output_on = match op.kind {
            CommandKind::OutputOn => true,
            CommandKind::SetVoltage(_) | CommandKind::SetCurrent(_) => reading.output != 0,
            CommandKind::Request | CommandKind::Release => false,
        };
        if output_on {
            let (voltage, current) = Self::frame_setpoints(&op, &reading);
            if let Err(error) = check_copied(voltage, current, &op.limits) {
                self.finish_control(op, Err(error));
                return;
            }
        }
        // (8) The implicit request in `None`.
        let request = match op.kind {
            CommandKind::Request => true,
            CommandKind::Release => false,
            _ => self.remote == RemoteState::None && !op.requested,
        };
        if request {
            if Self::caller_gone(&op) {
                return;
            }
            match self.start_remote_request(&reading) {
                Ok(()) => self.op = Some(Op::Control(op)),
                Err(error) => self.finish_control(op, Err(error)),
            }
        } else {
            self.control_send(op, reading);
        }
    }

    /// Guard (9) and the command itself (10).
    fn control_send(&mut self, mut op: ControlOp, reading: RawReading) {
        if Self::caller_gone(&op) {
            return;
        }
        let built = ControlCommand::from_reading(&reading).map(|command| {
            let command = match (op.voltage, op.current) {
                (Some(voltage), _) => command.set_voltage(voltage),
                (_, Some(current)) => command.set_current(current),
                _ => command,
            };
            match op.kind {
                CommandKind::OutputOn => command.output(true),
                CommandKind::Request => command.remote_con(RemoteCon::Request),
                CommandKind::Release => command.remote_con(RemoteCon::Release),
                CommandKind::SetVoltage(..) | CommandKind::SetCurrent(..) => command,
            }
        });
        let frame = match built {
            Ok(command) => command.encode(),
            Err(error) => {
                self.finish_control(op, Err(error));
                return;
            }
        };
        op.sent = Some(Self::frame_setpoints(&op, &reading));
        match &self.link {
            Some(link) => {
                self.step = Some(Step::Request(link.request(frame), Then::Command));
                self.op = Some(Op::Control(op));
            }
            None => {
                let lost = self.lost_error();
                self.finish_control(op, Err(lost));
            }
        }
    }

    /// Handles a step of a control command.
    fn control_done(&mut self, mut op: ControlOp, then: Then, done: Done) {
        match then {
            Then::Settle => {
                if Self::caller_gone(&op) {
                    return;
                }
                match self.settle_then_poll(Then::Settle, Then::Poll) {
                    Ok(()) => self.op = Some(Op::Control(op)),
                    Err(error) => self.finish_control(op, Err(error)),
                }
            }
            Then::Poll => match self.polled_reading(done) {
                // A reading that a resynchronisation or a late `0xC9` made
                // stale is not used: wait and poll again.
                Ok((reading, at)) if self.fresh_at(at) => self.control_checks(op, reading),
                Ok(_) => self.control_reading(op),
                Err(error) => self.finish_control(op, Err(error)),
            },
            Then::RemoteRequest | Then::RemoteWait => {
                let reading = op.reading;
                match self.remote_done(then, done, reading.as_ref()) {
                    RemoteStep::Waiting => self.op = Some(Op::Control(op)),
                    RemoteStep::Failed(error) => self.finish_control(op, Err(error)),
                    RemoteStep::Granted if op.kind == CommandKind::Request => {
                        self.finish_control(op, Ok(()));
                    }
                    RemoteStep::Granted => {
                        // (8) The grant's 0xC9 moved the settle time: a new
                        // fresh reading, with (5) to (7) checked again.
                        op.requested = true;
                        self.control_reading(op);
                    }
                }
            }
            Then::Command => {
                let result = self.command_result(&op, done);
                self.finish_control(op, result);
            }
            other => self.finish_control(op, Err(unexpected(other))),
        }
    }

    /// The `0xC9` of a command (DD-SESS-033).
    fn command_result(&mut self, op: &ControlOp, done: Done) -> Result<(), Error> {
        let voltage = op.voltage.map(RawVoltage::raw);
        let current = op.current.map(RawCurrent::raw);
        let (frame, at) = match done {
            Done::Request(Ok(Outcome::Reply { frame, at })) => {
                self.note_c9(at);
                (frame, at)
            }
            Done::Request(Err(error)) => {
                self.note_error(&error);
                if matches!(error, Error::Timeout { .. }) {
                    // The supply may still apply it (DD-SESS-036).
                    self.setpoints_unknown(op.reading);
                    self.resynchronise();
                }
                return Err(error);
            }
            _ => return Err(unexpected(Then::Command)),
        };
        let parsed = control::parse(&frame);
        if !matches!(parsed, Ok(ControlReply::Accepted)) {
            self.setpoints_unknown(op.reading);
        }
        match parsed {
            Ok(ControlReply::Accepted) => {
                match op.kind {
                    CommandKind::SetVoltage(..) => self.expected.0 = voltage,
                    CommandKind::SetCurrent(..) => self.expected.1 = current,
                    CommandKind::Release => self.remote_input(RemoteInput::Released),
                    CommandKind::OutputOn | CommandKind::Request => {}
                }
                // Only a `0xC8` with `remoteCon` 1 applies its fields; a
                // release applies none (DD-SESS-033).
                let applies = matches!(
                    op.kind,
                    CommandKind::SetVoltage(..)
                        | CommandKind::SetCurrent(..)
                        | CommandKind::OutputOn
                );
                if let (true, Some((voltage, current))) = (applies, op.sent) {
                    self.accepted = Some(Accepted {
                        voltage,
                        current,
                        at,
                    });
                }
                Ok(())
            }
            Ok(ControlReply::NotGranted) => {
                self.remote_input(RemoteInput::StatusOne);
                Err(Error::RemoteControlLost)
            }
            Ok(ControlReply::Rejected) => {
                let reason = op
                    .reading
                    .map_or("busy", |r| rejection_reason(&r, voltage, current));
                Err(Error::CommandRejected {
                    status: 0xFF,
                    reason: reason.to_string(),
                })
            }
            Ok(ControlReply::Other(status)) => Err(Error::CommandRejected {
                status,
                reason: status_text(status),
            }),
            Err(reason) => Err(Error::Protocol(reason)),
        }
    }

    // ----- The remote request (DD-SESS-020) -----

    /// Sends the request for remote control built from `reading`; over USB
    /// the state is `Requested` from now on.
    fn start_remote_request(&mut self, reading: &RawReading) -> Result<(), Error> {
        let frame = ControlCommand::from_reading(reading)?
            .remote_con(RemoteCon::Request)
            .encode();
        let request = self
            .link
            .as_ref()
            .map(|link| link.request(frame))
            .ok_or_else(|| self.lost_error())?;
        if self.kind == Some(Kind::Hid) {
            self.remote_input(RemoteInput::Request);
        }
        self.step = Some(Step::Request(request, Then::RemoteRequest));
        Ok(())
    }

    /// Whether the step in progress is a remote request: its `0xC8` handed
    /// to the link (queued, being written, or written with its outcome not
    /// yet taken) or its deferred `0xC9` awaited. Such a step is never
    /// dropped (DD-SESS-020): an output-off or a close takes it over.
    fn remote_step_open(&self) -> bool {
        matches!(
            self.step,
            Some(Step::Request(_, Then::RemoteRequest) | Step::Pending(_, Then::RemoteWait))
        )
    }

    /// The outcome of a remote request's step. A request that was rejected,
    /// answered with another status or not answered marks the setpoints
    /// unknown: it carried a full copy of them (DD-SESS-020, DD-SESS-033).
    fn remote_done(&mut self, then: Then, done: Done, reading: Option<&RawReading>) -> RemoteStep {
        match (then, done) {
            (Then::RemoteRequest, Done::Request(Ok(Outcome::Deferred(pending)))) => {
                self.remote_input(RemoteInput::Request);
                log::warn!(target: LOG_TARGET, "{}", texts::ALLOW_REMOTE_CONTROL);
                self.emit(SessionEvent::Prompt {
                    kind: PromptKind::AllowRemoteControl,
                    bound_s: 70,
                    text: texts::ALLOW_REMOTE_CONTROL,
                });
                self.step = Some(Step::Pending(pending, Then::RemoteWait));
                RemoteStep::Waiting
            }
            (Then::RemoteRequest, Done::Request(Ok(Outcome::Reply { frame, at })))
            | (Then::RemoteWait, Done::Pending(Ok((frame, at)))) => {
                self.note_c9(at);
                if self.remote != RemoteState::Requested {
                    self.remote_input(RemoteInput::Request);
                }
                match control::parse(&frame) {
                    Ok(ControlReply::Accepted) => {
                        self.remote_input(RemoteInput::Granted);
                        RemoteStep::Granted
                    }
                    Ok(ControlReply::NotGranted) => {
                        self.remote_input(RemoteInput::DeniedByReply);
                        RemoteStep::Failed(Error::RemoteControlDenied)
                    }
                    Ok(ControlReply::Rejected) => {
                        self.remote_input(RemoteInput::RequestFailed);
                        self.setpoints_unknown(reading.copied());
                        let reason = reading.map_or("busy", |r| rejection_reason(r, None, None));
                        RemoteStep::Failed(Error::CommandRejected {
                            status: 0xFF,
                            reason: reason.to_string(),
                        })
                    }
                    Ok(ControlReply::Other(status)) => {
                        self.remote_input(RemoteInput::RequestFailed);
                        self.setpoints_unknown(reading.copied());
                        RemoteStep::Failed(Error::CommandRejected {
                            status,
                            reason: status_text(status),
                        })
                    }
                    Err(reason) => {
                        self.remote_input(RemoteInput::RequestFailed);
                        self.setpoints_unknown(reading.copied());
                        RemoteStep::Failed(Error::Protocol(reason))
                    }
                }
            }
            (Then::RemoteWait, Done::Pending(Err(error))) => {
                self.note_error(&error);
                if matches!(error, Error::Timeout { .. }) {
                    self.remote_input(RemoteInput::DeniedByTimeout);
                    self.setpoints_unknown(reading.copied());
                    RemoteStep::Failed(Error::RemoteControlDenied)
                } else {
                    RemoteStep::Failed(error)
                }
            }
            (Then::RemoteRequest, Done::Request(Err(error))) => {
                self.note_error(&error);
                if matches!(error, Error::Timeout { .. }) {
                    self.remote_input(RemoteInput::RequestFailed);
                    self.setpoints_unknown(reading.copied());
                }
                RemoteStep::Failed(error)
            }
            (then, _) => RemoteStep::Failed(unexpected(then)),
        }
    }

    // ----- Cancellation (DD-SESS-003, DD-SESS-035 (b), DD-SESS-053 (a)) -----

    /// Drops the step of a cancelled command or output-off, keeping a
    /// remote request (DD-SESS-020). A dropped step that may hold a written
    /// `0xC8` (a command's or an output-off's, whose reply is still awaited)
    /// is treated as DD-SESS-035 (b) says: setpoints unknown from
    /// `built_from`, the settle time moved. Returns whether it was such a
    /// step.
    fn drop_cancelled_step(&mut self, built_from: Option<RawReading>) -> bool {
        if self.remote_step_open() {
            return false;
        }
        let written = matches!(
            self.step.as_ref().map(Step::then),
            Some(Then::Command | Then::OffCommand)
        );
        self.step = None;
        if written {
            self.cancel_possibly_written(built_from);
        }
        written
    }

    // ----- The output-off (DD-SESS-035) -----

    /// An output-off from the priority channel.
    fn on_output_off(&mut self, generation: u64, reply: Reply) {
        if self.closing {
            let _ = reply.send(Err(closed_error()));
            return;
        }
        // (a) Every waiting command is superseded, on the arrival of every
        // output-off, also one that then waits behind another: the commands
        // in the channel now were all issued before it.
        while let Ok(command) = self.commands.try_recv() {
            log::debug!(target: LOG_TARGET, "cancelled: {:?}, {SUPERSEDED}", command.kind);
            let _ = command.reply.send(Err(Error::Cancelled {
                reason: SUPERSEDED.to_string(),
            }));
        }
        if matches!(self.op, Some(Op::Off(_))) {
            self.queued_offs.push_back((generation, reply));
            return;
        }
        // (b) The command in progress is cancelled; its remote request, if
        // it has one, is kept for the output-off. Any other operation (the
        // connect flow or a reconnection attempt) goes on untouched, and
        // guard (1) answers the output-off.
        match self.op.take() {
            Some(Op::Control(op)) => {
                log::debug!(target: LOG_TARGET, "cancelled: {:?}, {SUPERSEDED_IN_PROGRESS}", op.kind);
                let _ = op.reply.send(Err(Error::Cancelled {
                    reason: SUPERSEDED_IN_PROGRESS.to_string(),
                }));
                self.setpoints_unknown(op.reading);
                self.drop_cancelled_step(op.reading);
            }
            other => self.op = other,
        }
        self.begin_off(generation, reply);
    }

    /// Starts an output-off after guard (1).
    fn begin_off(&mut self, generation: u64, reply: Reply) {
        if let Err(error) = self.link_guard(generation) {
            log::debug!(target: LOG_TARGET, "output-off: {error}");
            let _ = reply.send(Err(error));
            self.next_off();
            return;
        }
        self.start_off(OffOp {
            reply: Some(reply),
            retried: false,
            need: OffNeed::Start,
            built: None,
            in_close: false,
            started_at: Instant::now(),
            only_await: false,
        });
    }

    /// The start of an output-off (DD-SESS-035): the latest reading whatever
    /// its age (a poll only if there is none) and the mode check, with
    /// nothing sent; then what the remote state asks for: the open request
    /// awaited, a request first, or straight to the frame.
    fn start_off(&mut self, op: OffOp) {
        let Some((mut op, raw, _)) = self.off_latest(op, OffNeed::Start) else {
            return;
        };
        if raw.model != 0 {
            let error = Error::Mode {
                live_mode: raw.model,
            };
            // A close has awaited any open request before its output-off
            // (DD-SESS-053 (b)), so it never takes the first branch; should
            // it ever get here, the error must reach `end_off`, which keeps
            // the marker, and must not be dropped with the caller's reply.
            if self.remote_step_open() && !op.in_close {
                // The caller gets the error now; the open request is still
                // awaited, so that its outcome reaches the state
                // (DD-SESS-003), and nothing is sent after it.
                log::debug!(target: LOG_TARGET, "output-off: {error}");
                if let Some(reply) = op.reply.take() {
                    let _ = reply.send(Err(error));
                }
                op.only_await = true;
                self.op = Some(Op::Off(op));
            } else {
                self.end_off(op, Err(error));
            }
            return;
        }
        if self.remote_step_open() {
            // The request a cancelled command made is the output-off's: its
            // outcome brings the usual events and the grant.
            self.op = Some(Op::Off(op));
            return;
        }
        match self.remote {
            RemoteState::Granted => self.off_reading(op),
            RemoteState::Requested => {
                self.remote_input(RemoteInput::RequestFailed);
                self.off_request(op);
            }
            RemoteState::None | RemoteState::Denied | RemoteState::Lost => self.off_request(op),
        }
    }

    /// The latest reading whatever its age, with its arrival; polled (for
    /// `need`) when there is none.
    fn off_latest(&mut self, mut op: OffOp, need: OffNeed) -> Option<(OffOp, RawReading, Instant)> {
        if let Some((reading, at)) = self.reading {
            return Some((op, reading, at));
        }
        op.need = need;
        match self.start_poll(Then::Poll) {
            Ok(()) => self.op = Some(Op::Off(op)),
            Err(error) => self.end_off(op, Err(error)),
        }
        None
    }

    /// The request for control an output-off makes first (SR-022), built
    /// from the latest reading.
    fn off_request(&mut self, op: OffOp) {
        let Some((op, reading, _)) = self.off_latest(op, OffNeed::Request) else {
            return;
        };
        match self.start_remote_request(&reading) {
            Ok(()) => self.op = Some(Op::Off(op)),
            Err(error) => self.end_off(op, Err(error)),
        }
    }

    /// `raw`, which arrived at `at`, with the setpoints of `accepted` laid
    /// over it when it arrived before the `accepted` record's time plus
    /// `timing::SETTLE`, so that it may not show that command yet
    /// (DD-SESS-035): an output-off right after an accepted setpoint keeps
    /// that setpoint.
    fn with_accepted(&self, raw: RawReading, at: Instant) -> RawReading {
        match self.accepted {
            Some(accepted) if at < after(accepted.at, timing::SETTLE) => RawReading {
                set_voltage: accepted.voltage,
                set_current: accepted.current,
                ..raw
            },
            _ => raw,
        }
    }

    /// The reading, the mode check and the output-off command.
    fn off_reading(&mut self, op: OffOp) {
        let Some((mut op, raw, at)) = self.off_latest(op, OffNeed::Command) else {
            return;
        };
        if raw.model != 0 {
            let error = Error::Mode {
                live_mode: raw.model,
            };
            self.end_off(op, Err(error));
            return;
        }
        let built = self.with_accepted(raw, at);
        let frame = match ControlCommand::from_reading(&built) {
            Ok(command) => command.remote_con(RemoteCon::Active).output(false).encode(),
            Err(error) => {
                self.end_off(op, Err(error));
                return;
            }
        };
        op.built = Some(built);
        match &self.link {
            Some(link) => {
                self.step = Some(Step::Request(link.output_off(frame), Then::OffCommand));
                self.op = Some(Op::Off(op));
            }
            None => {
                let lost = self.lost_error();
                self.end_off(op, Err(lost));
            }
        }
    }

    /// Handles a step of an output-off.
    fn off_done(&mut self, op: OffOp, then: Then, done: Done) {
        match then {
            Then::Poll => match self.polled_reading(done) {
                Ok(_) => match op.need {
                    OffNeed::Start => self.start_off(op),
                    OffNeed::Request => self.off_request(op),
                    OffNeed::Command => self.off_reading(op),
                },
                Err(error) => self.end_off(op, Err(error)),
            },
            Then::RemoteRequest | Then::RemoteWait => {
                let reading = self.reading.map(|(raw, _)| raw);
                match self.remote_done(then, done, reading.as_ref()) {
                    RemoteStep::Waiting => self.op = Some(Op::Off(op)),
                    // Answered with `Mode` already: nothing is sent.
                    RemoteStep::Granted | RemoteStep::Failed(_) if op.only_await => {
                        self.end_off(op, Ok(()));
                    }
                    RemoteStep::Granted => self.off_reading(op),
                    RemoteStep::Failed(error) => self.end_off(op, Err(error)),
                }
            }
            Then::OffCommand => self.off_answered(op, done),
            Then::OffSettle => self.off_follow_up(op),
            Then::OffPoll => match self.polled_reading(done) {
                Ok((reading, at)) if self.fresh_at(at) => {
                    if reading.output == 0 {
                        // The event path may have cleared it on this very
                        // reading already.
                        if !self.cleared_since(op.started_at) {
                            self.clear_marker();
                        }
                        if op.in_close {
                            // A reading after the output-off shows it off.
                            self.close_unconfirmed = false;
                        }
                    }
                    self.end_off(op, Ok(()));
                }
                // Not fresh (a resynchronisation or a late `0xC9`): wait
                // and poll again.
                Ok(_) => self.off_follow_up(op),
                Err(error) => {
                    log::debug!(target: LOG_TARGET, "reading after the output-off: {error}");
                    self.end_off(op, Ok(()));
                }
            },
            other => self.end_off(op, Err(unexpected(other))),
        }
    }

    /// The `0xC9` outcome of the output-off's `0xC8` is known: a status 1
    /// re-takes control once; otherwise the caller is answered now, and the
    /// reading after the settle time follows. A timeout resynchronises
    /// (DD-SESS-036).
    fn off_answered(&mut self, mut op: OffOp, done: Done) {
        let result = match done {
            Done::Request(Ok(Outcome::Reply { frame, at })) => {
                self.note_c9(at);
                match control::parse(&frame) {
                    Ok(ControlReply::Accepted) => {
                        if let Some(built) = op.built {
                            self.accepted = Some(Accepted {
                                voltage: built.set_voltage,
                                current: built.set_current,
                                at,
                            });
                        }
                        Ok(())
                    }
                    Ok(ControlReply::NotGranted) => {
                        self.remote_input(RemoteInput::StatusOne);
                        if !op.retried {
                            op.retried = true;
                            self.off_request(op);
                            return;
                        }
                        Err(Error::RemoteControlLost)
                    }
                    Ok(ControlReply::Rejected) => {
                        let reason = op
                            .built
                            .map_or("busy", |r| rejection_reason(&r, None, None));
                        Err(Error::CommandRejected {
                            status: 0xFF,
                            reason: reason.to_string(),
                        })
                    }
                    Ok(ControlReply::Other(status)) => Err(Error::CommandRejected {
                        status,
                        reason: status_text(status),
                    }),
                    Err(reason) => Err(Error::Protocol(reason)),
                }
            }
            Done::Request(Err(error)) => {
                self.note_error(&error);
                if matches!(error, Error::Timeout { .. }) {
                    self.resynchronise();
                }
                Err(error)
            }
            _ => Err(unexpected(Then::OffCommand)),
        };
        log::debug!(target: LOG_TARGET, "output-off: {result:?}");
        // Whatever the outcome, the next settled reading tells what the
        // supply applied.
        self.setpoints_unknown(op.built);
        // The caller learns the outcome of the `0xC9` now; the reading that
        // follows, a loss or a close cannot change it.
        if let Some(reply) = op.reply.take() {
            let _ = reply.send(result.clone());
        }
        if op.in_close {
            if let Err(error) = &result {
                self.close_unconfirmed = true;
                self.close_failed(error.clone());
            }
        }
        if self.link.is_none() || matches!(result, Err(Error::LinkLost { .. })) {
            self.end_off(op, Ok(()));
            return;
        }
        self.off_follow_up(op);
    }

    /// The reading after the output-off: a fresh one, waited for until the
    /// settle time (or polled for at once while the session
    /// resynchronises).
    fn off_follow_up(&mut self, op: OffOp) {
        log::debug!(target: LOG_TARGET, "reading after the output-off");
        match self.settle_then_poll(Then::OffSettle, Then::OffPoll) {
            Ok(()) => self.op = Some(Op::Off(op)),
            Err(error) => {
                log::debug!(target: LOG_TARGET, "reading after the output-off: {error}");
                self.end_off(op, Ok(()));
            }
        }
    }

    /// Ends an output-off: answers its caller if that has not happened yet
    /// and starts the next one, or goes on with the close it belongs to.
    fn end_off(&mut self, mut op: OffOp, result: Result<(), Error>) {
        if op.in_close {
            if let Err(error) = result {
                self.close_unconfirmed = true;
                self.close_failed(error);
            }
            self.close_release();
            return;
        }
        if let Some(reply) = op.reply.take() {
            log::debug!(target: LOG_TARGET, "output-off: {result:?}");
            let _ = reply.send(result);
        }
        self.next_off();
    }

    /// Starts the next queued output-off, if any.
    fn next_off(&mut self) {
        if let Some((generation, reply)) = self.queued_offs.pop_front() {
            self.begin_off(generation, reply);
        }
    }

    // ----- The close (DD-SESS-053) -----

    /// A close from the priority channel.
    fn on_close(&mut self, output_off: bool, reply: Reply) {
        if self.closing {
            if output_off && !self.close_output_off {
                log::debug!(target: LOG_TARGET, "close(true): {CLOSE_RUNNING}");
                let _ = reply.send(Err(Error::Cancelled {
                    reason: CLOSE_RUNNING.to_string(),
                }));
            } else {
                self.close_waiters.push(reply);
            }
            return;
        }
        self.close_waiters.push(reply);
        self.closing = true;
        self.close_started_at = Some(Instant::now());
        self.close_output_off = output_off;
        self.close_from_ready = self.link_state.state == LinkState::Ready;
        self.tick = None;
        self.reconnect = None;
        // (a) Every waiting and in-progress command fails; an open remote
        // request is kept for (b).
        while let Ok(command) = self.commands.try_recv() {
            let _ = command.reply.send(Err(closed_error()));
        }
        for (_, reply) in self.queued_offs.drain(..) {
            let _ = reply.send(Err(closed_error()));
        }
        match self.op.take() {
            Some(Op::Control(op)) => {
                let _ = op.reply.send(Err(closed_error()));
                self.drop_cancelled_step(op.reading);
            }
            Some(Op::Off(op)) => {
                // An output-off already answered at its `0xC9` keeps that
                // answer; only its follow-up reading is dropped.
                if let Some(reply) = op.reply {
                    let _ = reply.send(Err(closed_error()));
                }
                self.drop_cancelled_step(op.built);
            }
            Some(Op::Connect(_)) => self.step = None,
            Some(Op::Close(_)) | None => {}
        }
        // A cancellation in (a), or one before the close, leaves the output
        // state unknown: the output-off then goes out whatever the reading
        // shows (DD-SESS-036).
        self.close_output_unknown = self.output_unknown;
        if !self.close_from_ready || self.link.is_none() {
            // After a connection that had been ready, a lost link means the
            // output could not be switched off (DD-SESS-053).
            let lost = matches!(
                self.link_state.state,
                LinkState::Lost | LinkState::Reconnecting
            );
            if output_off && self.was_ready && lost {
                let error = self.lost_error();
                self.close_failed(error);
            }
            self.step = None;
            self.close_link();
            return;
        }
        // (b) In `Ready`: an open remote request is awaited first, also one
        // whose `0xC8` is still with the link.
        if self.remote_step_open() {
            self.op = Some(Op::Close(CloseOp {
                phase: ClosePhase::AwaitGrant,
            }));
            return;
        }
        if self.remote == RemoteState::Requested {
            self.remote_input(RemoteInput::RequestFailed);
        }
        self.close_off();
    }

    /// Records the first error the close meets.
    fn close_failed(&mut self, error: Error) {
        log::warn!(target: LOG_TARGET, "close: {error}");
        if self.close_error.is_none() {
            self.close_error = Some(error);
        }
    }

    /// Waits and polls for a fresh reading in the close phase `phase`, the
    /// latest one being stale for the reason `why`.
    fn close_need(&mut self, phase: ClosePhase, why: &str) {
        match self.need_reading(why) {
            Ok(()) => self.op = Some(Op::Close(CloseOp { phase })),
            Err(error) => self.close_reading_failed(phase, error),
        }
    }

    /// The reading the close needed in `phase` could not be taken. While
    /// the link is still up the close goes on with the latest reading
    /// whatever its age: for the decision, the output-off is then sent in
    /// DC mode whatever that reading shows (DD-SESS-053 (b)); for the
    /// release, it is built from it. Without the decision's fresh reading
    /// the output cannot be confirmed off unless a later reading shows it.
    fn close_reading_failed(&mut self, phase: ClosePhase, error: Error) {
        let link_up = self.link.is_some() && !matches!(error, Error::LinkLost { .. });
        if phase == ClosePhase::OffReading {
            self.close_unconfirmed = true;
        }
        self.close_failed(error);
        let latest = self.reading.map(|(raw, _)| raw);
        match (link_up, latest, phase) {
            (true, Some(reading), ClosePhase::OffReading) => self.close_off_decide(reading, true),
            (true, Some(reading), ClosePhase::ReleaseReading) => {
                self.close_release_send(reading);
            }
            _ => self.close_link(),
        }
    }

    /// The output-off of the close, when asked for: decided on a fresh
    /// reading.
    fn close_off(&mut self) {
        if !self.close_output_off {
            self.close_release();
            return;
        }
        match self.fresh_reading() {
            Ok(reading) => self.close_off_decide(reading, false),
            Err(why) => self.close_need(ClosePhase::OffReading, why),
        }
    }

    /// Switches the output off if `reading` shows DC mode and the output on,
    /// or the output state is unknown (DD-SESS-036), or `no_fresh` (the
    /// fresh reading could not be obtained and `reading` is the latest one
    /// whatever its age); outside DC mode the output-off and the release
    /// are skipped with a WARN log.
    fn close_off_decide(&mut self, reading: RawReading, no_fresh: bool) {
        if reading.model != 0 {
            if reading.output != 0 || no_fresh {
                self.close_unconfirmed = true;
            }
            self.close_not_dc(reading.model);
            return;
        }
        if reading.output != 0 || no_fresh || self.close_output_unknown {
            self.start_off(OffOp {
                reply: None,
                retried: false,
                need: OffNeed::Start,
                built: None,
                in_close: true,
                started_at: Instant::now(),
                only_await: false,
            });
        } else {
            self.close_release();
        }
    }

    /// Logs the skipped output-off and release outside DC mode and goes on
    /// to the link's close.
    fn close_not_dc(&mut self, model: u8) {
        log::warn!(
            target: LOG_TARGET,
            "close: the supply is not in DC mode (mode {model}); output-off and release skipped"
        );
        self.close_link();
    }

    /// The release of the close, built from a fresh reading in DC mode.
    fn close_release(&mut self) {
        if self.link.is_none() {
            self.close_link();
            return;
        }
        match self.fresh_reading() {
            Ok(reading) => self.close_release_send(reading),
            Err(why) => self.close_need(ClosePhase::ReleaseReading, why),
        }
    }

    /// Sends the release built from `reading` (`output` 0 for
    /// `close(true)`, copied for `close(false)`), or skips it outside DC
    /// mode.
    fn close_release_send(&mut self, reading: RawReading) {
        if reading.model != 0 {
            if self.close_output_off && reading.output != 0 {
                self.close_unconfirmed = true;
            }
            self.close_not_dc(reading.model);
            return;
        }
        let output_off = self.close_output_off;
        let frame = match ControlCommand::from_reading(&reading) {
            Ok(command) => {
                let release = command.remote_con(RemoteCon::Release);
                if output_off {
                    release.output(false).encode()
                } else {
                    release.encode()
                }
            }
            Err(error) => {
                self.close_failed(error);
                self.close_link();
                return;
            }
        };
        match &self.link {
            Some(link) => {
                self.step = Some(Step::Request(link.request(frame), Then::Release));
                self.op = Some(Op::Close(CloseOp {
                    phase: ClosePhase::Release,
                }));
            }
            None => self.close_link(),
        }
    }

    /// Handles a step of the close.
    fn close_done(&mut self, op: CloseOp, then: Then, done: Done) {
        match (op.phase, then) {
            (ClosePhase::AwaitGrant, _) => {
                let reading = self.reading.map(|(raw, _)| raw);
                match self.remote_done(then, done, reading.as_ref()) {
                    RemoteStep::Waiting => self.op = Some(Op::Close(op)),
                    RemoteStep::Granted | RemoteStep::Failed(_) => self.close_off(),
                }
            }
            (phase @ (ClosePhase::OffReading | ClosePhase::ReleaseReading), Then::Settle) => {
                match self.settle_then_poll(Then::Settle, Then::Poll) {
                    Ok(()) => self.op = Some(Op::Close(op)),
                    Err(error) => self.close_reading_failed(phase, error),
                }
            }
            (ClosePhase::OffReading, _) => match self.polled_reading(done) {
                Ok((reading, at)) if self.fresh_at(at) => self.close_off_decide(reading, false),
                // Not fresh (a resynchronisation or a late `0xC9`): wait and
                // poll again.
                Ok(_) => self.close_off(),
                Err(error) => self.close_reading_failed(ClosePhase::OffReading, error),
            },
            (ClosePhase::ReleaseReading, _) => match self.polled_reading(done) {
                Ok((reading, at)) if self.fresh_at(at) => self.close_release_send(reading),
                Ok(_) => self.close_release(),
                Err(error) => self.close_reading_failed(ClosePhase::ReleaseReading, error),
            },
            (ClosePhase::Release, _) => {
                match done {
                    Done::Request(Ok(Outcome::Reply { frame, at })) => {
                        self.note_c9(at);
                        log::info!(
                            target: LOG_TARGET,
                            "release status {:?}",
                            control::parse(&frame)
                        );
                    }
                    Done::Request(Err(error)) => {
                        self.note_error(&error);
                        if matches!(error, Error::Timeout { .. }) {
                            self.resynchronise();
                        }
                        self.close_failed(error);
                    }
                    _ => self.close_failed(unexpected(then)),
                }
                self.close_link();
            }
            (ClosePhase::Link, _) => {
                if let Done::CloseLink(Err(error)) = done {
                    self.close_failed(error);
                }
                self.finish_close();
            }
        }
    }

    /// (c) the marker, in `Ready` only: cleared unless the close was to
    /// switch the output off and could not confirm it, or its output-off
    /// cleared it already; then (d) the link's close.
    fn close_link(&mut self) {
        let cleared = self
            .close_started_at
            .is_some_and(|since| self.cleared_since(since));
        let keep = self.close_output_off && self.close_unconfirmed;
        if self.close_from_ready {
            if keep {
                log::warn!(
                    target: LOG_TARGET,
                    "close: the output could not be confirmed off; the unclean-exit marker stays"
                );
            } else if !cleared {
                self.clear_marker();
            }
        }
        self.link_events = None;
        match self.link.take() {
            Some(link) => {
                self.step = Some(Step::CloseLink(Box::pin(link.close()), Then::CloseLink));
                self.op = Some(Op::Close(CloseOp {
                    phase: ClosePhase::Link,
                }));
            }
            None => self.finish_close(),
        }
    }

    /// (e) `Closed`, the ready state, the event senders and the registry
    /// entry; every caller of `close` gets the first error met, and later
    /// calls find it in the shared state.
    fn finish_close(&mut self) {
        self.op = None;
        self.step = None;
        self.link_input(LinkInput::Closed);
        self.set_ready(ReadyState::Failed(closed_error()));
        self.events = None;
        self.readings = None;
        self.registration.release();
        log::info!(target: LOG_TARGET, "closed");
        let result = match self.close_error.take() {
            Some(error) => Err(error),
            None => Ok(()),
        };
        *lock(&self.shared.close_result) = Some(result.clone());
        for waiter in self.close_waiters.drain(..) {
            let _ = waiter.send(result.clone());
        }
        self.finished = true;
    }
}

/// Test support: the loop of [`run`] taken one turn at a time, so that a
/// test can order what the task sees (the session DD, section 10).
#[cfg(test)]
impl Task {
    /// A task over `setup` with its connect flow started, as [`run`]
    /// starts it.
    pub(super) fn started(setup: Setup) -> Self {
        let mut task = Self::new(setup);
        task.begin_connect(false);
        task
    }

    /// Waits for the step in progress and handles its result before any
    /// link event: the reverse of the select's order, which a multi-thread
    /// runtime can produce (UT-SESS-052).
    pub(super) async fn step_first(&mut self) {
        let step = &mut self.step;
        let op = &mut self.op;
        let turn = poll_fn(|cx| poll_step(step, op, cx)).await;
        self.handle(turn);
        self.refresh_counters();
    }

    /// The setpoints of `accepted`, for assertions.
    pub(super) fn accepted_setpoints(&self) -> Option<(u16, u16)> {
        self.accepted.map(|a| (a.voltage, a.current))
    }

    /// What the operation in progress is, for assertions.
    pub(super) fn op_name(&self) -> Option<&'static str> {
        self.op.as_ref().map(|op| match op {
            Op::Connect(_) => "connect",
            Op::Control(_) => "control",
            Op::Off(_) => "off",
            Op::Close(_) => "close",
        })
    }
}
