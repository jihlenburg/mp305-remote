//! The link: the one layer between `session` and a guarded transport. It
//! owns the one request in flight, the two-level queue, the deferred
//! expectations, the poll, the USB keepalive and loss detection, and turns
//! every incoming frame into exactly one of: the reply to the request in
//! flight, the completion of an expectation, a device event, a late reply,
//! or a counted and logged stray.
//!
//! The handle [`Link`] talks to a task that owns the [`Guarded`]
//! transport; only [`Link::start`] and the task are generic over the
//! transport. Every frame that leaves `link` goes through the guard.
//!
//! Implements: DD-LINK-001, DD-LINK-002, DD-LINK-003, DD-LINK-004.

pub mod class;
pub(crate) mod queue;
mod task;
#[cfg(test)]
mod tests;

use core::fmt;
use core::future::Future;
use core::pin::Pin;
use core::task::{Context, Poll};
use std::sync::atomic::{AtomicU64, Ordering};
use std::sync::{Arc, OnceLock};

use tokio::runtime::Handle;
use tokio::sync::{mpsc, oneshot};
use tokio::task::AbortHandle;
use tokio::time::Instant;

use crate::error::Error;
use crate::protocol::error::Reason;
use crate::protocol::frame::Frame;
use crate::protocol::ops::control;
use crate::protocol::ops::events::DeviceFrame;
use crate::protocol::ops::telemetry::RawReading;
use crate::transport::description::Description;
use crate::transport::guarded::Guarded;
use crate::transport::Transport;
use class::Class;
use queue::{Queued, Responder};

/// The log target of the link.
pub const LOG_TARGET: &str = "mp305_core::link";

/// The loss text when the host closed or dropped the link (DD-LINK-041).
pub(crate) const CLOSED_BY_HOST: &str = "closed by the host";

/// Offset of `output` in the `0xC8` payload.
const OUTPUT: usize = 8;

/// Offset of `remoteCon` in the `0xC8` payload.
const REMOTE_CON: usize = 0;

/// What a request resolved with.
#[derive(Debug)]
pub enum Outcome {
    /// The reply arrived.
    Reply {
        /// The reply frame.
        frame: Frame,
        /// Its arrival stamp, taken by the transport.
        at: Instant,
    },
    /// A deferred request was written; its answer comes through the
    /// [`Pending`].
    Deferred(Pending),
}

/// Why the link ended.
#[derive(Clone, Debug, PartialEq, Eq)]
pub enum LossReason {
    /// The transport reported the link closed (an OS disconnect).
    Disconnected,
    /// A write failed or did not complete within `timing::REPLY`; the text
    /// says which.
    Transport(String),
    /// Three immediate requests in a row went unanswered.
    Unanswered,
}

impl fmt::Display for LossReason {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            LossReason::Disconnected => write!(f, "the transport reported the link closed"),
            LossReason::Transport(text) => write!(f, "transport error: {text}"),
            LossReason::Unanswered => write!(f, "three requests in a row went unanswered"),
        }
    }
}

/// Something the device did on its own, or failed to do, delivered through
/// [`Events`].
#[derive(Clone, Debug, PartialEq, Eq)]
pub enum DeviceEvent {
    /// A well-formed `0xC3` that completed a `0xC2`, with its arrival stamp.
    Reading {
        /// The reading, every field raw.
        reading: RawReading,
        /// When the transport received it.
        at: Instant,
    },
    /// A `0xC5`, `0xDD`, `0xE5`, `0xEB` or `0xDB`.
    Device(DeviceFrame),
    /// A `0x19` or `0xC9` that completed no request and no awaited
    /// expectation.
    LateReply {
        /// The frame.
        frame: Frame,
        /// When the transport received it.
        at: Instant,
    },
    /// The link ended; always the last event.
    LinkLost {
        /// Why.
        reason: LossReason,
    },
}

/// A snapshot of the link's counters.
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct Counters {
    /// Frames the link dropped: decode errors from the guard, malformed
    /// `0xC3` replies, malformed device frames.
    pub dropped_frames: u64,
    /// Frames that were neither a reply, an expectation, an event nor late.
    pub ignored: u64,
    /// Late replies delivered as [`DeviceEvent::LateReply`].
    pub late_replies: u64,
}

/// What the handle and the task share: the counters and the loss text.
#[derive(Debug, Default)]
pub(crate) struct Shared {
    /// See [`Counters::dropped_frames`].
    dropped_frames: AtomicU64,
    /// See [`Counters::ignored`].
    ignored: AtomicU64,
    /// See [`Counters::late_replies`].
    late_replies: AtomicU64,
    /// The reason that ended the link, once it ended.
    loss: OnceLock<String>,
}

/// Which counter to grow.
#[derive(Clone, Copy, Debug)]
pub(crate) enum Counter {
    /// [`Counters::dropped_frames`].
    Dropped,
    /// [`Counters::ignored`].
    Ignored,
    /// [`Counters::late_replies`].
    Late,
}

impl Shared {
    /// Grows one counter by one, saturating.
    pub(crate) fn count(&self, counter: Counter) {
        let cell = match counter {
            Counter::Dropped => &self.dropped_frames,
            Counter::Ignored => &self.ignored,
            Counter::Late => &self.late_replies,
        };
        // The closure always returns `Some`, so the update cannot fail.
        let _ = cell.fetch_update(Ordering::SeqCst, Ordering::SeqCst, |n| {
            Some(n.saturating_add(1))
        });
    }

    /// A snapshot of the counters.
    fn counters(&self) -> Counters {
        Counters {
            dropped_frames: self.dropped_frames.load(Ordering::SeqCst),
            ignored: self.ignored.load(Ordering::SeqCst),
            late_replies: self.late_replies.load(Ordering::SeqCst),
        }
    }

    /// Stores the reason that ended the link; the first one stays.
    pub(crate) fn set_loss(&self, text: &str) {
        let _ = self.loss.set(text.to_string());
    }

    /// The reason that ended the link. A link whose task ended without
    /// storing one was dropped by the host.
    fn loss_text(&self) -> String {
        self.loss
            .get()
            .cloned()
            .unwrap_or_else(|| CLOSED_BY_HOST.to_string())
    }

    /// The error a caller gets once the link has ended.
    fn lost(&self) -> Error {
        Error::LinkLost {
            text: self.loss_text(),
        }
    }
}

/// A command from the handle to the task.
#[derive(Debug)]
pub(crate) enum Command {
    /// Queue at normal priority.
    Request(Queued),
    /// Queue at urgent priority.
    OutputOff(Queued),
    /// Switch the poll on or off.
    SetPolling(bool),
    /// End the link and answer with the result of closing the transport.
    Close(oneshot::Sender<Result<(), Error>>),
}

/// The handle of a running link. Not generic: the transport type stays
/// inside the task. Dropping it aborts the task, which drops the guard and
/// with it the transport.
#[derive(Debug)]
pub struct Link {
    /// Commands to the task.
    commands: mpsc::UnboundedSender<Command>,
    /// Aborts the task on drop.
    abort: AbortHandle,
    /// The counters and the loss text.
    shared: Arc<Shared>,
    /// The transport's kind and identifier.
    description: Description,
}

/// The receiver of [`DeviceEvent`]s.
#[derive(Debug)]
pub struct Events {
    /// The unbounded channel from the task.
    rx: mpsc::UnboundedReceiver<DeviceEvent>,
}

impl Events {
    /// The next event, in order; `None` after the last one.
    pub async fn next(&mut self) -> Option<DeviceEvent> {
        self.rx.recv().await
    }

    /// The next event if one is waiting, without waiting.
    #[cfg(test)]
    pub(crate) fn try_next(&mut self) -> Option<DeviceEvent> {
        self.rx.try_recv().ok()
    }
}

/// The future of [`Link::request`] and [`Link::output_off`]: `Send`,
/// `'static`, and cancelling the request when dropped before its write.
#[derive(Debug)]
pub struct Requested {
    /// Where the result comes from.
    state: RequestedState,
}

/// The two ways a [`Requested`] resolves.
#[derive(Debug)]
enum RequestedState {
    /// Resolved before anything was queued; `None` once taken.
    Ready(Option<Result<Outcome, Error>>),
    /// Waiting for the task.
    Waiting {
        /// The task's answer.
        rx: oneshot::Receiver<Result<Outcome, Error>>,
        /// For the loss text when the task ends without answering.
        shared: Arc<Shared>,
    },
}

impl Requested {
    /// A future that resolves at once with `result`.
    fn ready(result: Result<Outcome, Error>) -> Self {
        Self {
            state: RequestedState::Ready(Some(result)),
        }
    }
}

impl Future for Requested {
    type Output = Result<Outcome, Error>;

    fn poll(mut self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<Self::Output> {
        match &mut self.state {
            RequestedState::Ready(result) => Poll::Ready(result.take().unwrap_or_else(|| {
                Err(Error::LinkLost {
                    text: "request polled after it resolved".to_string(),
                })
            })),
            RequestedState::Waiting { rx, shared } => match Pin::new(rx).poll(cx) {
                Poll::Ready(Ok(result)) => Poll::Ready(result),
                Poll::Ready(Err(_)) => Poll::Ready(Err(shared.lost())),
                Poll::Pending => Poll::Pending,
            },
        }
    }
}

/// The handle of a deferred request. Resolves with the matching reply and
/// its arrival stamp, with [`Error::Timeout`] when the deadline passes, or
/// with [`Error::LinkLost`] when the link ends first. Dropping it does not
/// cancel the expectation: a reply that arrives later is delivered as
/// [`DeviceEvent::LateReply`].
#[derive(Debug)]
pub struct Pending {
    /// The request opcode.
    opcode: u8,
    /// When the expectation expires.
    deadline: Instant,
    /// The task's answer.
    rx: oneshot::Receiver<Result<(Frame, Instant), Error>>,
    /// For the loss text when the task ends without answering.
    shared: Arc<Shared>,
}

impl Pending {
    /// The request opcode.
    #[must_use]
    pub fn opcode(&self) -> u8 {
        self.opcode
    }

    /// When the expectation expires.
    #[must_use]
    pub fn deadline(&self) -> Instant {
        self.deadline
    }
}

impl Future for Pending {
    type Output = Result<(Frame, Instant), Error>;

    fn poll(mut self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<Self::Output> {
        let this = &mut *self;
        match Pin::new(&mut this.rx).poll(cx) {
            Poll::Ready(Ok(result)) => Poll::Ready(result),
            Poll::Ready(Err(_)) => Poll::Ready(Err(this.shared.lost())),
            Poll::Pending => Poll::Pending,
        }
    }
}

/// Checks that `frame` is an output-off command: opcode `0xC8`, the full
/// payload length, `remoteCon` 1 and `output` 0.
fn check_output_off(frame: &Frame) -> Result<(), Reason> {
    if frame.opcode() != control::REQUEST {
        return Err(Reason::WrongOpcode {
            expected: control::REQUEST,
            got: frame.opcode(),
        });
    }
    let payload = frame.payload();
    if payload.len() != control::LEN {
        return Err(Reason::BadLength {
            expected: control::LEN,
            got: payload.len(),
        });
    }
    let byte = |offset: usize| i64::from(payload.get(offset).copied().unwrap_or(0));
    if byte(REMOTE_CON) != 1 {
        return Err(Reason::Value {
            field: "remoteCon",
            value: byte(REMOTE_CON),
        });
    }
    if byte(OUTPUT) != 0 {
        return Err(Reason::Value {
            field: "output",
            value: byte(OUTPUT),
        });
    }
    Ok(())
}

impl Link {
    /// Starts the link task on the current Tokio runtime. `connected_at` is
    /// the instant the transport was connected, the origin of the bind
    /// bound. Polling is off until [`Link::set_polling`] switches it on.
    ///
    /// # Errors
    ///
    /// [`Error::Transport`] when no Tokio runtime is current.
    pub fn start<T: Transport>(
        guard: Guarded<T>,
        connected_at: Instant,
    ) -> Result<(Link, Events), Error> {
        let runtime = Handle::try_current().map_err(|e| Error::Transport {
            message: format!("no Tokio runtime: {e}"),
        })?;
        let (commands, command_rx) = mpsc::unbounded_channel();
        let (event_tx, rx) = mpsc::unbounded_channel();
        let shared = Arc::new(Shared::default());
        let description = guard.description().clone();
        let task = runtime.spawn(task::run(
            guard,
            command_rx,
            event_tx,
            Arc::clone(&shared),
            connected_at,
            Instant::now(),
        ));
        Ok((
            Link {
                commands,
                abort: task.abort_handle(),
                shared,
                description,
            },
            Events { rx },
        ))
    }

    /// Sends `command` built around a fresh responder and returns the
    /// future of its result.
    fn enqueue(
        &self,
        command: impl FnOnce(oneshot::Sender<Result<Outcome, Error>>) -> Command,
    ) -> Requested {
        let (tx, rx) = oneshot::channel();
        if self.commands.send(command(tx)).is_err() {
            return Requested::ready(Err(self.shared.lost()));
        }
        Requested {
            state: RequestedState::Waiting {
                rx,
                shared: Arc::clone(&self.shared),
            },
        }
    }

    /// Queues `frame` at normal priority at once and returns the future of
    /// its outcome: [`Outcome::Reply`] for an immediate request,
    /// [`Outcome::Deferred`] for a deferred one as soon as it was written.
    /// Dropping the future before the write cancels the request.
    ///
    /// The future resolves with [`Error::Protocol`] when the guard refuses
    /// the frame, [`Error::Timeout`] when no reply arrives in time, and
    /// [`Error::LinkLost`] when the link ends first or had already ended.
    pub fn request(&self, frame: Frame) -> Requested {
        let class = Class::of(&frame, self.description.kind);
        self.enqueue(|tx| {
            Command::Request(Queued {
                frame,
                class,
                responder: Responder::Caller(tx),
            })
        })
    }

    /// Queues an output-off command at urgent priority. `frame` must be a
    /// `0xC8` with `remoteCon` 1 and `output` 0; anything else resolves at
    /// once with [`Error::Protocol`] and nothing is queued. The frame is
    /// written even if the future is dropped, and resolves only with
    /// [`Outcome::Reply`] (or the errors of [`Link::request`]), with the
    /// output-off acknowledgment bound of 0.5 s.
    pub fn output_off(&self, frame: Frame) -> Requested {
        if let Err(reason) = check_output_off(&frame) {
            return Requested::ready(Err(Error::Protocol(reason)));
        }
        self.enqueue(|tx| {
            Command::OutputOff(Queued {
                frame,
                class: Class::output_off(),
                responder: Responder::OutputOff(tx),
            })
        })
    }

    /// Switches the poll on or off. A poll in flight completes normally.
    pub fn set_polling(&self, on: bool) {
        // A link that has ended polls nothing either way.
        let _ = self.commands.send(Command::SetPolling(on));
    }

    /// A snapshot of the counters.
    #[must_use]
    pub fn counters(&self) -> Counters {
        self.shared.counters()
    }

    /// The transport's kind and identifier.
    #[must_use]
    pub fn description(&self) -> &Description {
        &self.description
    }

    /// Ends the link: every queued and in-flight request and every open
    /// expectation resolves with [`Error::LinkLost`] ("closed by the host"),
    /// no `LinkLost` event is delivered, and the transport is closed.
    ///
    /// # Errors
    ///
    /// The transport's close error, [`Error::Transport`] when the close does
    /// not complete within `timing::REPLY`, or [`Error::LinkLost`] when the
    /// task ended before it could answer. A link that had already ended
    /// closes with `Ok`.
    pub async fn close(self) -> Result<(), Error> {
        let (tx, rx) = oneshot::channel();
        if self.commands.send(Command::Close(tx)).is_err() {
            return Ok(());
        }
        rx.await.unwrap_or_else(|_| Err(self.shared.lost()))
    }
}

impl Drop for Link {
    fn drop(&mut self) {
        self.abort.abort();
    }
}

#[cfg(test)]
mod loss_reason_tests {
    use super::*;

    /// Test: UT-LINK-028
    #[test]
    fn loss_reasons_display_their_texts() {
        assert_eq!(
            LossReason::Disconnected.to_string(),
            "the transport reported the link closed"
        );
        assert_eq!(
            LossReason::Transport("transport: boom".to_string()).to_string(),
            "transport error: transport: boom"
        );
        assert_eq!(
            LossReason::Unanswered.to_string(),
            "three requests in a row went unanswered"
        );
    }
}
