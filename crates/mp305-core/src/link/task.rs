//! The link task: one loop over a `biased` select of the guard, the command
//! channel and the earliest deadline, followed by the send step. It owns
//! the `Guarded` and every piece of link state; only the counters and the
//! loss text are shared with the handle.
//!
//! Implements: DD-LINK-020, DD-LINK-021, DD-LINK-022, DD-LINK-023,
//! DD-LINK-024, DD-LINK-030, DD-LINK-031, DD-LINK-040, DD-LINK-041,
//! DD-LINK-042, DD-LINK-051.

use std::collections::VecDeque;
use std::sync::Arc;

use core::time::Duration;

use tokio::sync::{mpsc, oneshot};
use tokio::time::{sleep_until, timeout, Instant};

use crate::error::{duration_text, Error};
use crate::link::class::{
    dispatch, eligible, Bound, Candidate, Class, DispatchState, Disposition, EligibilityState,
};
use crate::link::queue::{Internal, Queue, Queued, Responder};
use crate::link::{
    Command, Counter, DeviceEvent, LossReason, Outcome, Pending, Shared, CLOSED_BY_HOST, LOG_TARGET,
};
use crate::protocol::ble::Route;
use crate::protocol::frame::Frame;
use crate::protocol::ops::{self, control, events, info, telemetry};
use crate::protocol::timing;
use crate::transport::description::Kind;
use crate::transport::guarded::{Guarded, Incoming, Item};
use crate::transport::Transport;

/// Consecutive immediate timeouts that end the link (DD-LINK-023).
const UNANSWERED_LIMIT: u8 = 3;

/// The immediate request in flight.
#[derive(Debug)]
struct InFlight {
    /// The request opcode.
    opcode: u8,
    /// The reply opcode that completes it.
    reply: u8,
    /// Its reply bound.
    timeout: Duration,
    /// When its write started.
    write_start: Instant,
    /// `write_start + timeout`.
    deadline: Instant,
    /// Who is told how it ended.
    responder: Responder,
}

/// An open expectation of a deferred request (DD-LINK-024).
#[derive(Debug)]
struct Expectation {
    /// The request opcode.
    request: u8,
    /// The reply opcode that completes it.
    reply: u8,
    /// The length of its bound, for the timeout error.
    bound: Duration,
    /// When it expires.
    deadline: Instant,
    /// The `Pending`'s channel; closed when the `Pending` was dropped.
    tx: oneshot::Sender<Result<(Frame, Instant), Error>>,
}

/// Why the loop stopped.
#[derive(Debug)]
enum End {
    /// The link was lost (DD-LINK-040). `failed` is the responder of an
    /// entry whose write just failed.
    Lost {
        /// Why.
        reason: LossReason,
        /// The entry whose write failed, if that was the cause.
        failed: Option<Responder>,
    },
    /// The host closed the link (DD-LINK-041); `None` when the handle was
    /// dropped and nobody waits for the answer.
    Close(Option<oneshot::Sender<Result<(), Error>>>),
}

/// Everything the task owns except the guard and the command receiver.
#[derive(Debug)]
struct State {
    /// The transport's kind: decides routes and the keepalive.
    kind: Kind,
    /// When the transport was connected; origin of the bind bound.
    connected_at: Instant,
    /// Counters and loss text shared with the handle.
    shared: Arc<Shared>,
    /// The event sender; taken when the link ends.
    events: Option<mpsc::UnboundedSender<DeviceEvent>>,
    /// The two-level queue.
    queue: Queue,
    /// The immediate request in flight, if any.
    in_flight: Option<InFlight>,
    /// The open expectations, at most one per reply opcode.
    expectations: VecDeque<Expectation>,
    /// Whether the poll is on.
    polling: bool,
    /// The `0xC8` block (DD-LINK-023).
    block: bool,
    /// Consecutive immediate timeouts.
    count: u8,
    /// Arrival stamp of the last good `0xC3`.
    last_reply_at: Option<Instant>,
    /// Write start of the last successful write; the link's start at first.
    last_sent_at: Instant,
}

/// The task. Runs the loop until the link is lost or closed, then ends it.
pub(crate) async fn run<T: Transport>(
    mut guard: Guarded<T>,
    mut commands: mpsc::UnboundedReceiver<Command>,
    events: mpsc::UnboundedSender<DeviceEvent>,
    shared: Arc<Shared>,
    connected_at: Instant,
    started: Instant,
) {
    let mut state = State {
        kind: guard.description().kind,
        connected_at,
        shared,
        events: Some(events),
        queue: Queue::default(),
        in_flight: None,
        expectations: VecDeque::new(),
        polling: false,
        block: false,
        count: 0,
        last_reply_at: None,
        last_sent_at: started,
    };
    match state.run_loop(&mut guard, &mut commands).await {
        End::Lost { reason, failed } => state.end_lost(reason, failed, guard, &mut commands),
        End::Close(caller) => state.end_closed(caller, &guard, &mut commands).await,
    }
}

/// The internal request of `kind`: a `0xC2` for the poll and the block, an
/// `0xE0` for the keepalive.
fn internal(kind: Internal) -> Queued {
    let frame = match kind {
        Internal::Poll | Internal::Block => telemetry::request(),
        Internal::Keepalive => info::request(),
    };
    Queued {
        class: Class::Immediate {
            reply: ops::reply_opcode(frame.opcode()),
            timeout: timing::REPLY,
        },
        frame,
        responder: Responder::Internal(kind),
    }
}

/// The candidate view of a queued entry.
fn candidate(entry: &Queued) -> Candidate {
    Candidate {
        opcode: entry.frame.opcode(),
        class: entry.class,
    }
}

/// `at + d`, an overflow meaning already due (`at`).
fn after(at: Instant, d: Duration) -> Instant {
    at.checked_add(d).unwrap_or(at)
}

impl State {
    /// The loop of DD-LINK-020: one biased select, then the send step.
    async fn run_loop<T: Transport>(
        &mut self,
        guard: &mut Guarded<T>,
        commands: &mut mpsc::UnboundedReceiver<Command>,
    ) -> End {
        loop {
            let deadline = self.next_deadline(Instant::now());
            let wake = deadline.unwrap_or_else(Instant::now);
            let step = tokio::select! {
                biased;
                incoming = guard.recv() => self.on_incoming(incoming),
                command = commands.recv() => self.on_command(command),
                () = sleep_until(wake), if deadline.is_some() => self.on_deadline(Instant::now()),
            };
            if let Some(end) = step {
                return end;
            }
            if let Some(end) = self.send_step(guard).await {
                return end;
            }
        }
    }

    /// The earliest of: the in-flight deadline, every expectation deadline,
    /// and, while the link is free, the `0xC2` pacing time when a `0xC2`
    /// waits for it and the keepalive due time on a `Hid` kind. Due times
    /// are included only while still ahead, so a due time can never make the
    /// loop spin.
    fn next_deadline(&self, now: Instant) -> Option<Instant> {
        let mut times: Vec<Instant> = self.expectations.iter().map(|e| e.deadline).collect();
        match &self.in_flight {
            Some(flight) => times.push(flight.deadline),
            None => {
                if let Some(pace) = self.pace_due() {
                    if pace > now && self.c2_waiting() {
                        times.push(pace);
                    }
                }
                if self.kind == Kind::Hid {
                    let keepalive = after(self.last_sent_at, timing::USB_KEEPALIVE);
                    if keepalive > now {
                        times.push(keepalive);
                    }
                }
            }
        }
        times.into_iter().min()
    }

    /// When the next `0xC2` may go out, if a `0xC3` has arrived.
    fn pace_due(&self) -> Option<Instant> {
        self.last_reply_at.map(|at| after(at, timing::POLL_PAUSE))
    }

    /// Whether some `0xC2` candidate exists: the poll, a queued `0xC2` at
    /// the normal head, or the block's `0xC2` for a blocked `0xC8` head.
    fn c2_waiting(&self) -> bool {
        let head_c2 = self
            .queue
            .normal_head()
            .is_some_and(|q| q.frame.opcode() == telemetry::REQUEST);
        let block_c2 = self.block
            && self
                .queue
                .peek()
                .is_some_and(|q| q.frame.opcode() == control::REQUEST);
        self.polling || head_c2 || block_c2
    }

    /// The reply opcodes of the open expectations.
    fn open_replies(&self) -> Vec<u8> {
        self.expectations.iter().map(|e| e.reply).collect()
    }

    /// Delivers an event, unless the link has ended.
    fn emit(&self, event: DeviceEvent) {
        if let Some(tx) = &self.events {
            // `Events` may have been dropped; the link goes on without it.
            let _ = tx.send(event);
        }
    }

    /// Handles what the guard delivered (DD-LINK-021).
    fn on_incoming(&mut self, incoming: Option<Incoming>) -> Option<End> {
        let Some(Incoming { at, item, .. }) = incoming else {
            // The guard yields `None` only after `LinkClosed`.
            return Some(End::Lost {
                reason: LossReason::Disconnected,
                failed: None,
            });
        };
        match item {
            Item::Frame(frame) => {
                self.on_frame(frame, at);
                None
            }
            Item::Error(_) => {
                // The guard has logged it already.
                self.shared.count(Counter::Dropped);
                None
            }
            Item::LinkClosed => Some(End::Lost {
                reason: LossReason::Disconnected,
                failed: None,
            }),
        }
    }

    /// Applies the disposition of an incoming frame (DD-LINK-021).
    fn on_frame(&mut self, frame: Frame, at: Instant) {
        let opcode = frame.opcode();
        let open = self.open_replies();
        let state = DispatchState {
            in_flight_reply: self.in_flight.as_ref().map(|f| f.reply),
            open_expectations: &open,
        };
        match dispatch(&state, opcode) {
            Disposition::Reply => self.on_reply(frame, at),
            Disposition::Expectation => self.on_expectation(frame, at),
            Disposition::Event => match events::classify(&frame) {
                Ok(Some(device)) => self.emit(DeviceEvent::Device(device)),
                Ok(None) => self.ignore(opcode),
                Err(reason) => {
                    self.shared.count(Counter::Dropped);
                    log::warn!(target: LOG_TARGET, "dropped 0x{opcode:02x}: {reason}");
                }
            },
            Disposition::Late => {
                self.shared.count(Counter::Late);
                log::warn!(target: LOG_TARGET, "late reply 0x{opcode:02x}");
                if opcode == control::REPLY {
                    self.block = true;
                }
                self.emit(DeviceEvent::LateReply { frame, at });
            }
            Disposition::Ignore => self.ignore(opcode),
        }
    }

    /// Counts and logs a frame nobody asked for.
    fn ignore(&self, opcode: u8) {
        self.shared.count(Counter::Ignored);
        log::warn!(target: LOG_TARGET, "ignored 0x{opcode:02x}");
    }

    /// The reply to the request in flight. A malformed `0xC3` is dropped
    /// and the request stays in flight.
    fn on_reply(&mut self, frame: Frame, at: Instant) {
        let opcode = frame.opcode();
        if opcode == telemetry::REPLY {
            match telemetry::parse(&frame) {
                Ok(reading) => {
                    self.emit(DeviceEvent::Reading { reading, at });
                    self.last_reply_at = Some(self.last_reply_at.map_or(at, |last| last.max(at)));
                    self.block = false;
                }
                Err(reason) => {
                    self.shared.count(Counter::Dropped);
                    log::warn!(target: LOG_TARGET, "dropped 0xc3: {reason}");
                    return;
                }
            }
        }
        if let Some(flight) = self.in_flight.take() {
            log::debug!(
                target: LOG_TARGET,
                "reply 0x{opcode:02x} +{}",
                at.saturating_duration_since(flight.write_start).as_millis()
            );
            self.count = 0;
            flight.responder.resolve(Ok(Outcome::Reply { frame, at }));
        }
    }

    /// The completion of an open expectation; a late reply when its
    /// `Pending` was dropped.
    fn on_expectation(&mut self, frame: Frame, at: Instant) {
        let opcode = frame.opcode();
        let Some(position) = self.expectations.iter().position(|e| e.reply == opcode) else {
            self.ignore(opcode);
            return;
        };
        let Some(expectation) = self.expectations.remove(position) else {
            return;
        };
        match expectation.tx.send(Ok((frame, at))) {
            Ok(()) => {
                log::debug!(
                    target: LOG_TARGET,
                    "expectation 0x{:02x} resolved",
                    expectation.request
                );
            }
            Err(unsent) => {
                self.shared.count(Counter::Late);
                log::warn!(target: LOG_TARGET, "late reply 0x{opcode:02x} (unawaited)");
                if let Ok((frame, at)) = unsent {
                    self.emit(DeviceEvent::LateReply { frame, at });
                }
            }
        }
    }

    /// Handles a command from the handle. A closed channel means the handle
    /// was dropped without `close`.
    fn on_command(&mut self, command: Option<Command>) -> Option<End> {
        match command {
            None => Some(End::Close(None)),
            Some(Command::Request(entry)) => {
                self.queue.push_normal(entry);
                None
            }
            Some(Command::OutputOff(entry)) => {
                self.queue.push_urgent(entry);
                None
            }
            Some(Command::SetPolling(on)) => {
                self.polling = on;
                log::debug!(target: LOG_TARGET, "{}", if on { "poll on" } else { "poll off" });
                None
            }
            Some(Command::Close(caller)) => Some(End::Close(Some(caller))),
        }
    }

    /// Handles every deadline that has passed: expired expectations
    /// (DD-LINK-024) and the in-flight timeout (DD-LINK-023).
    fn on_deadline(&mut self, now: Instant) -> Option<End> {
        let (expired, open): (VecDeque<Expectation>, VecDeque<Expectation>) =
            self.expectations.drain(..).partition(|e| e.deadline <= now);
        self.expectations = open;
        for expectation in expired {
            log::debug!(
                target: LOG_TARGET,
                "expectation 0x{:02x} timed out",
                expectation.request
            );
            if expectation.reply == control::REPLY {
                self.block = true;
            }
            // A dropped `Pending` does not need to hear about it.
            let _ = expectation.tx.send(Err(Error::Timeout {
                opcode: expectation.request,
                after: expectation.bound,
            }));
        }
        let flight = self.in_flight.take_if(|f| f.deadline <= now)?;
        log::debug!(
            target: LOG_TARGET,
            "timeout 0x{:02x} after {}",
            flight.opcode,
            flight.timeout.as_millis()
        );
        if flight.opcode == control::REQUEST {
            self.block = true;
        }
        self.count = self.count.saturating_add(1);
        flight.responder.resolve(Err(Error::Timeout {
            opcode: flight.opcode,
            after: flight.timeout,
        }));
        (self.count >= UNANSWERED_LIMIT).then_some(End::Lost {
            reason: LossReason::Unanswered,
            failed: None,
        })
    }

    /// Removes normal heads whose future was dropped (DD-LINK-022).
    fn drop_cancelled(&mut self) {
        while self
            .queue
            .normal_head()
            .is_some_and(|q| q.responder.is_cancelled())
        {
            if let Some(entry) = self.queue.pop_normal() {
                log::debug!(target: LOG_TARGET, "cancelled 0x{:02x}", entry.frame.opcode());
            }
        }
    }

    /// The first eligible candidate of DD-LINK-022, removed from the queue
    /// when it is a queued one.
    fn pick(&mut self, now: Instant) -> Option<Queued> {
        self.drop_cancelled();
        let open = self.open_replies();
        let rules = EligibilityState {
            open_expectations: &open,
            block: self.block,
            last_reply_at: self.last_reply_at,
            now,
        };
        let ok = |entry: &Queued| eligible(&candidate(entry), &rules);
        // (1) The urgent head.
        if self.queue.urgent_head().is_some_and(ok) {
            return self.queue.pop_urgent();
        }
        // (2) The block's 0xC2, for a 0xC8 head held back only by the block.
        let unblocked = EligibilityState {
            block: false,
            ..rules
        };
        let held_by_block = self.queue.peek().is_some_and(|head| {
            head.frame.opcode() == control::REQUEST
                && self.block
                && eligible(&candidate(head), &unblocked)
        });
        let block_c2 = internal(Internal::Block);
        if held_by_block && ok(&block_c2) {
            return Some(block_c2);
        }
        // (3) The normal head.
        if self.queue.normal_head().is_some_and(ok) {
            return self.queue.pop_normal();
        }
        // (4) The poll.
        let poll = internal(Internal::Poll);
        if self.polling && ok(&poll) {
            return Some(poll);
        }
        // (5) The USB keepalive.
        let keepalive = internal(Internal::Keepalive);
        if self.kind == Kind::Hid
            && after(self.last_sent_at, timing::USB_KEEPALIVE) <= now
            && ok(&keepalive)
        {
            return Some(keepalive);
        }
        None
    }

    /// The send step (DD-LINK-022): writes eligible candidates until the
    /// link is not free or nothing is eligible.
    async fn send_step<T: Transport>(&mut self, guard: &Guarded<T>) -> Option<End> {
        loop {
            if self.in_flight.is_some() {
                return None;
            }
            let now = Instant::now();
            let entry = self.pick(now)?;
            if let Class::Deferred {
                bound: bound @ Bound::FromConnection(_),
                ..
            } = entry.class
            {
                if bound.deadline(self.connected_at, now) <= now {
                    // Past its deadline: not written (DD-LINK-010).
                    let opcode = entry.frame.opcode();
                    entry.responder.resolve(Err(Error::Timeout {
                        opcode,
                        after: bound.duration(),
                    }));
                    continue;
                }
            }
            if let Some(end) = self.write(guard, entry).await {
                return Some(end);
            }
        }
    }

    /// Writes one entry and registers what it waits for.
    async fn write<T: Transport>(&mut self, guard: &Guarded<T>, entry: Queued) -> Option<End> {
        let opcode = entry.frame.opcode();
        let route = match self.kind {
            Kind::Ble => Route::Ble(ops::route(opcode)),
            Kind::Hid => Route::Hid,
        };
        let write_start = Instant::now();
        match timeout(timing::REPLY, guard.send(&entry.frame, route)).await {
            Err(_) => {
                return Some(End::Lost {
                    reason: LossReason::Transport(format!(
                        "the write of 0x{opcode:02x} did not complete within {}",
                        duration_text(timing::REPLY)
                    )),
                    failed: Some(entry.responder),
                })
            }
            Ok(Err(Error::Protocol(reason))) => {
                // Refused by the guard: nothing was written.
                entry.responder.resolve(Err(Error::Protocol(reason)));
                return None;
            }
            Ok(Err(error)) => {
                return Some(End::Lost {
                    reason: LossReason::Transport(error.to_string()),
                    failed: Some(entry.responder),
                })
            }
            Ok(Ok(())) => {}
        }
        self.last_sent_at = write_start;
        log::debug!(
            target: LOG_TARGET,
            "sent 0x{opcode:02x} {}",
            entry.responder.word(&entry.class)
        );
        if matches!(entry.responder, Responder::Internal(Internal::Keepalive)) {
            log::debug!(target: LOG_TARGET, "keepalive");
        }
        match entry.class {
            Class::Immediate { reply, timeout } => {
                self.in_flight = Some(InFlight {
                    opcode,
                    reply,
                    timeout,
                    write_start,
                    deadline: after(write_start, timeout),
                    responder: entry.responder,
                });
            }
            Class::Deferred { reply, bound } => {
                let deadline = bound.deadline(self.connected_at, write_start);
                let (tx, rx) = oneshot::channel();
                self.expectations.push_back(Expectation {
                    request: opcode,
                    reply,
                    bound: bound.duration(),
                    deadline,
                    tx,
                });
                log::debug!(
                    target: LOG_TARGET,
                    "deferred 0x{opcode:02x} until +{}",
                    deadline.saturating_duration_since(write_start).as_millis()
                );
                entry.responder.resolve(Ok(Outcome::Deferred(Pending {
                    opcode,
                    deadline,
                    rx,
                    shared: Arc::clone(&self.shared),
                })));
            }
        }
        None
    }

    /// Resolves the in-flight request, every open expectation and every
    /// queued entry with `error`, and stops the poll and the keepalive.
    fn resolve_all(&mut self, error: &Error) {
        if let Some(flight) = self.in_flight.take() {
            flight.responder.resolve(Err(error.clone()));
        }
        for expectation in self.expectations.drain(..) {
            let _ = expectation.tx.send(Err(error.clone()));
        }
        self.queue.drain(error);
        self.polling = false;
    }

    /// Ends the link on loss, in the order of DD-LINK-040.
    fn end_lost<T: Transport>(
        &mut self,
        reason: LossReason,
        failed: Option<Responder>,
        guard: Guarded<T>,
        commands: &mut mpsc::UnboundedReceiver<Command>,
    ) {
        let text = reason.to_string();
        let lost = Error::LinkLost { text: text.clone() };
        if let Some(responder) = failed {
            responder.resolve(Err(lost.clone()));
        }
        self.resolve_all(&lost);
        self.shared.set_loss(&text);
        log::debug!(target: LOG_TARGET, "lost: {reason}");
        if let Some(tx) = self.events.take() {
            let _ = tx.send(DeviceEvent::LinkLost { reason });
        }
        tokio::spawn(async move {
            // Best effort: the link is already reported lost.
            let _ = timeout(timing::REPLY, guard.close()).await;
        });
        answer_leftovers(commands, &lost, &Ok(()));
    }

    /// Ends the link on the host's request (DD-LINK-041).
    async fn end_closed<T: Transport>(
        &mut self,
        caller: Option<oneshot::Sender<Result<(), Error>>>,
        guard: &Guarded<T>,
        commands: &mut mpsc::UnboundedReceiver<Command>,
    ) {
        let lost = Error::LinkLost {
            text: CLOSED_BY_HOST.to_string(),
        };
        self.resolve_all(&lost);
        self.shared.set_loss(CLOSED_BY_HOST);
        // Dropped without a `LinkLost` event.
        self.events = None;
        let result = match timeout(timing::REPLY, guard.close()).await {
            Ok(result) => result,
            Err(_) => Err(Error::Transport {
                message: format!(
                    "the close did not complete within {}",
                    duration_text(timing::REPLY)
                ),
            }),
        };
        log::debug!(target: LOG_TARGET, "closed");
        answer_leftovers(commands, &lost, &result);
        if let Some(caller) = caller {
            let _ = caller.send(result);
        }
    }
}

/// Closes the command channel and answers what is still in it: requests
/// with `lost`, a `close` with `closed`.
fn answer_leftovers(
    commands: &mut mpsc::UnboundedReceiver<Command>,
    lost: &Error,
    closed: &Result<(), Error>,
) {
    commands.close();
    while let Ok(command) = commands.try_recv() {
        match command {
            Command::Request(entry) | Command::OutputOff(entry) => {
                entry.responder.resolve(Err(lost.clone()));
            }
            Command::Close(caller) => {
                let _ = caller.send(closed.clone());
            }
            Command::SetPolling(_) => {}
        }
    }
}
