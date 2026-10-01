//! A scripted transport for tests: replies per opcode with delays on the
//! Tokio clock, timed injections, timed send errors, a stop and a close
//! time, decoded through the real decoders. Compiled for tests and the
//! `mock` feature only.
//!
//! Implements: DD-TRANS-030, DD-TRANS-031, DD-TRANS-032.

use std::sync::atomic::{AtomicUsize, Ordering};
use std::sync::{Arc, Mutex};

use core::time::Duration;

use tokio::sync::mpsc;
use tokio::time::{sleep, Instant};

use crate::error::Error;
use crate::protocol::ble::{self, BleRoute, Route};
use crate::protocol::frame::Frame;
use crate::protocol::hid;
use crate::transport::description::{Description, Kind};
use crate::transport::{RawIncoming, Transport};

/// A scripted reply to requests with one opcode.
///
/// Among the entries for an opcode that still have uses left and whose
/// `from` has passed, the one with the latest `from` answers; entries with
/// the same `from` are used in list order. A script can so switch the reply
/// it gives at a chosen time.
#[derive(Clone, Debug)]
pub struct Reply {
    /// The request opcode this reply answers.
    pub request: u8,
    /// How long after the request the deliveries start.
    pub after: Duration,
    /// The route the deliveries arrive on.
    pub route: Route,
    /// The on-air units, each a notification value (Ble) or the stream bytes
    /// of one input report (Hid).
    pub deliveries: Vec<Vec<u8>>,
    /// How many requests this reply serves; `None` forever.
    pub repeat: Option<usize>,
    /// Offset from the mock's creation from which this reply is eligible.
    pub from: Duration,
}

impl Default for Reply {
    /// A reply to opcode 0 on AF01 with no deliveries, at once, forever,
    /// eligible from the mock's creation.
    fn default() -> Self {
        Self {
            request: 0,
            after: Duration::ZERO,
            route: Route::Ble(BleRoute::Af01),
            deliveries: Vec::new(),
            repeat: None,
            from: Duration::ZERO,
        }
    }
}

/// A delivery at a fixed time, regardless of requests.
#[derive(Clone, Debug)]
pub struct Injection {
    /// Offset from the mock's creation.
    pub at: Duration,
    /// The route it arrives on.
    pub route: Route,
    /// The on-air unit.
    pub delivery: Vec<u8>,
}

/// A send failure for one opcode from a given time on.
#[derive(Clone, Debug)]
pub struct SendError {
    /// The opcode whose sends fail.
    pub opcode: u8,
    /// Offset from the mock's creation from which they fail.
    pub from: Duration,
}

/// What the mock does; times are offsets from its creation.
#[derive(Clone, Debug, Default)]
pub struct Script {
    /// Replies per opcode, used in order per opcode.
    pub replies: Vec<Reply>,
    /// Timed deliveries.
    pub injections: Vec<Injection>,
    /// Timed send failures.
    pub send_errors: Vec<SendError>,
    /// After this time no reply is delivered.
    pub stop_replying_at: Option<Duration>,
    /// At this time the mock drops its sender.
    pub close_at: Option<Duration>,
}

/// One accepted send.
#[derive(Clone, Debug)]
pub struct Sent {
    /// When it was sent.
    pub at: Instant,
    /// The route it went on.
    pub route: Route,
    /// The frame.
    pub frame: Frame,
    /// The on-air bytes.
    pub wire: Vec<u8>,
}

/// What a test can still see of a mock after it moved into a `Guarded` and
/// into the link task: the sends and the close calls. Cloneable.
#[derive(Clone, Debug, Default)]
pub struct MockHandle {
    /// Every accepted send, shared with the mock.
    sent: Arc<Mutex<Vec<Sent>>>,
    /// How often `close` was called.
    closes: Arc<AtomicUsize>,
}

impl MockHandle {
    /// Every accepted send, in order: the same record as [`Mock::sent`].
    #[must_use]
    pub fn sent(&self) -> Vec<Sent> {
        self.sent.lock().map(|s| s.clone()).unwrap_or_default()
    }

    /// How often `close` was called.
    #[must_use]
    pub fn closes(&self) -> usize {
        self.closes.load(Ordering::SeqCst)
    }
}

/// Makes a fresh mock for each connection attempt.
pub type MockFactory = Box<dyn FnMut() -> Mock + Send>;

/// A reply with its remaining uses.
#[derive(Clone, Debug)]
struct ReplyState {
    /// The scripted reply.
    reply: Reply,
    /// Uses left; `None` forever.
    remaining: Option<usize>,
}

/// The sender the delivery tasks share; taken at the close time.
type SharedSender = Arc<Mutex<Option<mpsc::UnboundedSender<RawIncoming>>>>;

/// The scripted transport.
pub struct Mock {
    /// Kind and identifier.
    description: Description,
    /// The replies with their remaining uses.
    replies: Mutex<Vec<ReplyState>>,
    /// Timed send failures.
    send_errors: Vec<SendError>,
    /// After this time no reply is delivered.
    stop_replying_at: Option<Duration>,
    /// The mock's creation time; script times are offsets from it.
    created: Instant,
    /// The sender the deliveries use.
    tx: SharedSender,
    /// The channel the consumer reads.
    rx: mpsc::UnboundedReceiver<RawIncoming>,
    /// Every accepted send and the close count, shared with the handles.
    handle: MockHandle,
    /// The one HID decoder kept across deliveries.
    decoder: Arc<Mutex<hid::Decoder>>,
}

/// Decodes one on-air unit and delivers the results.
fn deliver(
    kind: Kind,
    route: Route,
    unit: &[u8],
    at: Instant,
    decoder: &Arc<Mutex<hid::Decoder>>,
    tx: &SharedSender,
) {
    let Ok(guard) = tx.lock() else { return };
    let Some(sender) = guard.as_ref() else { return };
    let hex: Vec<String> = unit.iter().map(|b| format!("{b:02x}")).collect();
    log::trace!(target: super::guarded::LOG_TARGET, "wire rx {route:?} {}", hex.join(" "));
    match (kind, route) {
        (Kind::Ble, Route::Ble(ble_route)) => {
            let item = ble::decode(unit, ble_route);
            let _ = sender.send(RawIncoming { route, at, item });
        }
        (Kind::Hid, Route::Hid) => {
            if let Ok(mut decoder) = decoder.lock() {
                for item in decoder.push(unit) {
                    let _ = sender.send(RawIncoming { route, at, item });
                }
            }
        }
        _ => {}
    }
}

impl Mock {
    /// A mock of the given kind and identifier that follows `script`.
    #[must_use]
    pub fn new(kind: Kind, identifier: &str, script: Script) -> Self {
        let (tx, rx) = mpsc::unbounded_channel();
        let tx: SharedSender = Arc::new(Mutex::new(Some(tx)));
        let decoder = Arc::new(Mutex::new(hid::Decoder::new()));
        let created = Instant::now();
        for injection in script.injections {
            let (tx, decoder) = (Arc::clone(&tx), Arc::clone(&decoder));
            tokio::spawn(async move {
                sleep(injection.at).await;
                deliver(
                    kind,
                    injection.route,
                    &injection.delivery,
                    created.checked_add(injection.at).unwrap_or(created),
                    &decoder,
                    &tx,
                );
            });
        }
        if let Some(close_at) = script.close_at {
            let tx = Arc::clone(&tx);
            tokio::spawn(async move {
                sleep(close_at).await;
                if let Ok(mut guard) = tx.lock() {
                    guard.take();
                }
            });
        }
        Self {
            description: Description {
                kind,
                identifier: identifier.to_string(),
            },
            replies: Mutex::new(
                script
                    .replies
                    .into_iter()
                    .map(|reply| ReplyState {
                        remaining: reply.repeat,
                        reply,
                    })
                    .collect(),
            ),
            send_errors: script.send_errors,
            stop_replying_at: script.stop_replying_at,
            created,
            tx,
            rx,
            handle: MockHandle::default(),
            decoder,
        }
    }

    /// Every accepted send, in order.
    #[must_use]
    pub fn sent(&self) -> Vec<Sent> {
        self.handle.sent()
    }

    /// A handle that keeps the sends and the close count reachable after
    /// the mock moved into a `Guarded`.
    #[must_use]
    pub fn handle(&self) -> MockHandle {
        self.handle.clone()
    }

    /// The reply that answers a request for `opcode` at `elapsed` after the
    /// creation, consuming one use: among the entries with uses left whose
    /// `from` has passed, the one with the latest `from`, the first in list
    /// order on a tie.
    fn take_reply(&self, opcode: u8, elapsed: Duration) -> Option<Reply> {
        let mut replies = self.replies.lock().ok()?;
        let mut chosen: Option<&mut ReplyState> = None;
        for state in replies.iter_mut() {
            let eligible = state.reply.request == opcode
                && state.remaining.is_none_or(|n| n > 0)
                && state.reply.from <= elapsed;
            let later = chosen
                .as_ref()
                .is_none_or(|best| state.reply.from > best.reply.from);
            if eligible && later {
                chosen = Some(state);
            }
        }
        let state = chosen?;
        if let Some(n) = state.remaining.as_mut() {
            *n = n.saturating_sub(1);
        }
        Some(state.reply.clone())
    }
}

impl Transport for Mock {
    async fn send(&self, frame: &Frame, route: Route) -> Result<(), Error> {
        let elapsed = self.created.elapsed();
        let kind_matches = matches!(
            (self.description.kind, route),
            (Kind::Ble, Route::Ble(_)) | (Kind::Hid, Route::Hid)
        );
        if !kind_matches {
            return Err(Error::Transport {
                message: format!("route {route:?} on a {} mock", self.description),
            });
        }
        if self
            .send_errors
            .iter()
            .any(|e| e.opcode == frame.opcode() && elapsed >= e.from)
        {
            return Err(Error::Transport {
                message: format!("scripted send error for 0x{:02x}", frame.opcode()),
            });
        }
        let wire = match route {
            Route::Ble(ble_route) => ble::encode(frame, ble_route),
            Route::Hid => hid::encode(frame).concat(),
        };
        let hex: Vec<String> = wire.iter().map(|b| format!("{b:02x}")).collect();
        log::trace!(target: super::guarded::LOG_TARGET, "wire tx {route:?} {}", hex.join(" "));
        if let Ok(mut sent) = self.handle.sent.lock() {
            sent.push(Sent {
                at: Instant::now(),
                route,
                frame: frame.clone(),
                wire,
            });
        }
        if self.stop_replying_at.is_some_and(|stop| elapsed >= stop) {
            return Ok(());
        }
        if let Some(reply) = self.take_reply(frame.opcode(), elapsed) {
            let (kind, tx, decoder) = (
                self.description.kind,
                Arc::clone(&self.tx),
                Arc::clone(&self.decoder),
            );
            let now = Instant::now();
            let at = now.checked_add(reply.after).unwrap_or(now);
            tokio::spawn(async move {
                sleep(reply.after).await;
                for unit in &reply.deliveries {
                    deliver(kind, reply.route, unit, at, &decoder, &tx);
                }
            });
        }
        Ok(())
    }

    fn incoming(&mut self) -> &mut mpsc::UnboundedReceiver<RawIncoming> {
        &mut self.rx
    }

    async fn close(&self) -> Result<(), Error> {
        let _ = self
            .handle
            .closes
            .fetch_update(Ordering::SeqCst, Ordering::SeqCst, |n| {
                Some(n.saturating_add(1))
            });
        if let Ok(mut guard) = self.tx.lock() {
            guard.take();
        }
        Ok(())
    }

    fn description(&self) -> &Description {
        &self.description
    }
}
