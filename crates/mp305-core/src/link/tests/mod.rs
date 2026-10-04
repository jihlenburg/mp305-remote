//! The task tests of `link` (link DD section 8), compiled under
//! `cfg(test)` as submodules of `link` so that they reach `Frame::new`, the
//! capture reading and the log collector. Every test runs on a paused Tokio
//! clock; times are relative to the link's start.
//!
//! Implements: nothing; the tests name their UT IDs.

mod block;
mod deferred;
mod loss;
mod poll;
mod task;

use std::sync::Arc;

use core::time::Duration;

use tokio::sync::mpsc;
use tokio::task::JoinHandle;
use tokio::time::{sleep, sleep_until, Instant};

use crate::error::Error;
use crate::link::{DeviceEvent, Events, Link, Outcome, Requested};
use crate::protocol::ble::{BleRoute, Route};
use crate::protocol::error::Reason;
use crate::protocol::frame::Frame;
use crate::protocol::ops::bind;
use crate::protocol::ops::telemetry;
use crate::transport::description::Kind;
use crate::transport::guarded::Guarded;
use crate::transport::stub::{Sends, Stub, StubHandle};
use crate::transport::RawIncoming;

/// The log target of the link.
const TARGET: &str = "mp305_core::link";

/// A started link on a stub, with everything a test needs to drive it.
struct Rig {
    /// The handle.
    link: Link,
    /// The event receiver.
    events: Events,
    /// The sender the stub's channel is fed from.
    tx: mpsc::UnboundedSender<RawIncoming>,
    /// The stub's record of sends.
    sends: Sends,
    /// The stub's failure switch, close counter and close delay.
    stub: StubHandle,
    /// The link's start, also `connected_at`.
    start: Instant,
    /// The stub's kind.
    kind: Kind,
}

/// Milliseconds as a duration.
fn ms(n: u64) -> Duration {
    Duration::from_millis(n)
}

/// A link on a stub of `kind` whose sends take `delay`.
fn rig(kind: Kind, delay: Duration) -> Rig {
    rig_with(kind, delay, |_| {})
}

/// As [`rig`], with the stub configured by `configure` before it is wrapped.
fn rig_with(kind: Kind, delay: Duration, configure: impl FnOnce(&Stub)) -> Rig {
    let (stub, tx, sends) = Stub::new(kind, "stub", delay);
    configure(&stub);
    let handle = stub.handle();
    let start = Instant::now();
    let (link, events) = Link::start(Guarded::new(stub), start).unwrap();
    Rig {
        link,
        events,
        tx,
        sends,
        stub: handle,
        start,
        kind,
    }
}

impl Rig {
    /// The clock time `d` after the start.
    fn at(&self, d: Duration) -> Instant {
        self.start + d
    }

    /// Sleeps until `d` after the start.
    async fn until(&self, d: Duration) {
        sleep_until(self.at(d)).await;
    }

    /// The sends so far as (time since start, route, opcode).
    fn sent(&self) -> Vec<(Duration, Route, u8)> {
        self.sends
            .lock()
            .unwrap()
            .iter()
            .map(|(at, route, f)| (*at - self.start, *route, f.opcode()))
            .collect()
    }

    /// The write times of the sends with `opcode`.
    fn sent_times(&self, opcode: u8) -> Vec<Duration> {
        self.sent()
            .into_iter()
            .filter(|(_, _, op)| *op == opcode)
            .map(|(t, _, _)| t)
            .collect()
    }

    /// Feeds `frame` at `d` after the start, stamped with that time.
    fn feed_at(&self, d: Duration, frame: Frame) {
        let (tx, when, route) = (self.tx.clone(), self.at(d), reply_route(self.kind, &frame));
        tokio::spawn(async move {
            sleep_until(when).await;
            let _ = tx.send(RawIncoming {
                route,
                at: when,
                item: Ok(frame),
            });
        });
    }

    /// Feeds a decode error at `d` after the start.
    fn feed_error_at(&self, d: Duration, reason: Reason) {
        let (tx, when) = (self.tx.clone(), self.at(d));
        tokio::spawn(async move {
            sleep_until(when).await;
            let _ = tx.send(RawIncoming {
                route: Route::Ble(BleRoute::Af01),
                at: when,
                item: Err(reason),
            });
        });
    }

    /// Answers every send recorded before `until` (since the start) for which
    /// `reply` returns a frame, `after` its write start. `reply` gets the
    /// sent frame and its write time since the start.
    fn auto_reply(
        &self,
        after: Duration,
        until: Duration,
        reply: impl Fn(&Frame, Duration) -> Option<Frame> + Send + 'static,
    ) -> JoinHandle<()> {
        let (sends, tx, start, kind) = (
            Arc::clone(&self.sends),
            self.tx.clone(),
            self.start,
            self.kind,
        );
        tokio::spawn(async move {
            let mut seen = 0;
            loop {
                let new: Vec<(Instant, Frame)> = {
                    let s = sends.lock().unwrap();
                    let new = s[seen..]
                        .iter()
                        .map(|(at, _, f)| (*at, f.clone()))
                        .collect();
                    seen = s.len();
                    new
                };
                for (at, frame) in new {
                    let since = at - start;
                    if since >= until {
                        continue;
                    }
                    if let Some(answer) = reply(&frame, since) {
                        let (tx, when) = (tx.clone(), at + after);
                        tokio::spawn(async move {
                            sleep_until(when).await;
                            let _ = tx.send(RawIncoming {
                                route: reply_route(kind, &answer),
                                at: when,
                                item: Ok(answer),
                            });
                        });
                    }
                }
                if Instant::now() - start > until + after {
                    break;
                }
                sleep(ms(1)).await;
            }
        })
    }

    /// Every event delivered so far, without waiting.
    fn drain_events(&mut self) -> Vec<DeviceEvent> {
        std::iter::from_fn(|| self.events.try_next()).collect()
    }
}

/// The route a reply arrives on: `0x19` on AF02 and the rest on AF01 over
/// Bluetooth, the report path over USB.
fn reply_route(kind: Kind, frame: &Frame) -> Route {
    match kind {
        Kind::Ble if frame.opcode() == 0x19 => Route::Ble(BleRoute::Af02),
        Kind::Ble => Route::Ble(BleRoute::Af01),
        Kind::Hid => Route::Hid,
    }
}

/// Awaits a request in a task and records when it resolved.
fn track(request: Requested) -> JoinHandle<(Instant, Result<Outcome, Error>)> {
    tokio::spawn(async move {
        let result = request.await;
        (Instant::now(), result)
    })
}

/// Awaits a request and returns its reply frame and arrival stamp.
fn reply_of(result: Result<Outcome, Error>) -> (Frame, Instant) {
    match result {
        Ok(Outcome::Reply { frame, at }) => (frame, at),
        other => panic!("expected a reply, got {other:?}"),
    }
}

/// A good `0xC3`: the capture reading of `telemetry::tests::C3_PAYLOAD`.
fn c3() -> Frame {
    Frame::new(0xC3, telemetry::tests::C3_PAYLOAD.to_vec()).unwrap()
}

/// An `0xE1`; the link does not parse it.
fn e1() -> Frame {
    Frame::new(0xE1, vec![0; 20]).unwrap()
}

/// A `0xC9` with `status`.
fn c9(status: u8) -> Frame {
    Frame::new(0xC9, vec![status]).unwrap()
}

/// A `0x19` with `status`.
fn r19(status: u8) -> Frame {
    Frame::new(0x19, vec![status]).unwrap()
}

/// A `0xC8` with the given `remoteCon` and `output` bytes (layout of
/// `protocol::ops::control::Command`: 12.00 V, 1.000 A).
fn c8(remote_con: u8, output: u8) -> Frame {
    Frame::new(
        0xC8,
        vec![remote_con, 0xB0, 0x04, 0xE8, 0x03, 0, 0, 0, output, 0, 0],
    )
    .unwrap()
}

/// A bind request with a fixed host ID.
fn bind_request(fast: bool) -> Frame {
    bind::request(&bind::HostId::new([7; 16]).unwrap(), fast)
}

/// The answer the stub gives to every `0xC2` (a good `0xC3`).
fn answer_c2(frame: &Frame, _: Duration) -> Option<Frame> {
    (frame.opcode() == 0xC2).then(c3)
}

/// Whether the logged lines under the link's target on this thread hold
/// `level` and a line starting with `prefix`.
fn logged(log: &crate::transport::test_log::Log, level: log::Level, prefix: &str) -> bool {
    log.lines_here(TARGET)
        .iter()
        .any(|(l, m)| *l == level && m.starts_with(prefix))
}
