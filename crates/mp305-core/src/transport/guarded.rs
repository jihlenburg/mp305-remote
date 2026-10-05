//! The wrapper every transport sits behind: allowlist, one write in flight,
//! timestamps, counting and the frame log.
//!
//! Implements: DD-TRANS-003, DD-TRANS-004, DD-TRANS-005, DD-TRANS-026.

use std::sync::Arc;

use tokio::sync::{mpsc, Semaphore};
use tokio::time::Instant;

use crate::error::Error;
use crate::protocol::ble::{BleRoute, Route};
use crate::protocol::error::Reason;
use crate::protocol::frame::Frame;
use crate::protocol::{ops, policy};
use crate::transport::description::{Description, Kind};
use crate::transport::{ble, hid, AnyTransport, RawIncoming, Transport};

/// The log target of the frame log.
pub const LOG_TARGET: &str = "mp305_core::frames";

/// What arrived, as `link` sees it.
#[derive(Debug)]
pub enum Item {
    /// A decoded frame.
    Frame(Frame),
    /// Bytes that did not decode, with the reason; counted and logged.
    Error(Reason),
    /// The transport closed the link; delivered once, then the guard yields
    /// nothing more.
    LinkClosed,
}

/// One incoming item with its route and arrival time.
#[derive(Debug)]
pub struct Incoming {
    /// The characteristic or report path it arrived on.
    pub route: Route,
    /// When the producer received it.
    pub at: Instant,
    /// What arrived.
    pub item: Item,
}

/// The wrapper every path to a supply goes through.
///
/// It refuses any frame outside the allowlist (and, over Bluetooth, on the
/// wrong characteristic) before the transport sees it, allows one write in
/// flight, keeps the permit with the write even when the caller gives up
/// waiting, and writes the frame log.
pub struct Guarded<T: Transport> {
    /// The transport, shared with the tasks that carry out writes.
    inner: Arc<T>,
    /// The channel taken from the transport.
    rx: mpsc::UnboundedReceiver<RawIncoming>,
    /// The one write permit.
    permit: Arc<Semaphore>,
    /// When this guard was created, for the log offsets.
    created: Instant,
    /// Parse errors seen so far.
    errors: u64,
    /// The link was reported closed.
    closed: bool,
}

/// The name of a route in the log.
fn route_name(route: Route) -> &'static str {
    match route {
        Route::Ble(BleRoute::Af01) => "ble AF01",
        Route::Ble(BleRoute::Af02) => "ble AF02",
        Route::Hid => "hid",
    }
}

impl Guarded<AnyTransport> {
    /// Connects to a supply over Bluetooth LE. The only way to obtain a
    /// Bluetooth transport, so every frame goes through the guard.
    ///
    /// # Errors
    ///
    /// [`Error::Transport`] when the peripheral is not known to the adapter, a
    /// `btleplug` call fails, the negotiated MTU is below 74, or a
    /// characteristic is missing.
    pub async fn connect_ble(
        adapter: &btleplug::platform::Adapter,
        os_id: &btleplug::platform::PeripheralId,
    ) -> Result<Self, Error> {
        Ok(Self::new(AnyTransport::ble(
            ble::Ble::connect(adapter, os_id).await?,
        )))
    }

    /// Opens a supply over USB HID. The only way to obtain a HID transport.
    ///
    /// # Errors
    ///
    /// [`Error::Transport`] when the device cannot be opened or its I/O
    /// thread cannot be started. No Tokio runtime needs to be current.
    pub fn open_hid(api: &hidapi::HidApi, path: &std::ffi::CStr) -> Result<Self, Error> {
        Ok(Self::new(AnyTransport::hid(hid::Hid::open(api, path)?)))
    }
}

impl<T: Transport> Guarded<T> {
    /// Wraps `inner`, taking over its channel.
    #[must_use]
    pub fn new(mut inner: T) -> Self {
        let (_never, replacement) = mpsc::unbounded_channel();
        let rx = core::mem::replace(inner.incoming(), replacement);
        Self {
            inner: Arc::new(inner),
            rx,
            permit: Arc::new(Semaphore::new(1)),
            created: Instant::now(),
            errors: 0,
            closed: false,
        }
    }

    /// Milliseconds since the guard was created, for the log.
    fn offset_ms(&self) -> u128 {
        self.created.elapsed().as_millis()
    }

    /// Milliseconds between the guard's creation and `at`, for the log.
    fn offset_of(&self, at: Instant) -> u128 {
        at.saturating_duration_since(self.created).as_millis()
    }

    /// Sends `frame` on `route` after checking the policy and the route,
    /// holding the single write permit until the write completes even if
    /// this future is dropped.
    ///
    /// # Errors
    ///
    /// [`Error::Protocol`] for an opcode outside the allowlist or a wrong
    /// payload length; [`Error::Transport`] for a route that does not match
    /// the frame's characteristic or the transport's kind, or a failed write.
    pub async fn send(&self, frame: &Frame, route: Route) -> Result<(), Error> {
        let result = self.checked_send(frame, route).await;
        if let Err(error) = &result {
            log::warn!(target: LOG_TARGET, "tx {} +{} failed: {error}", route_name(route), self.offset_ms());
        }
        result
    }

    /// The body of [`Guarded::send`], without the failure log line.
    async fn checked_send(&self, frame: &Frame, route: Route) -> Result<(), Error> {
        policy::check(frame)?;
        if self.inner.description().kind == Kind::Ble
            && route != Route::Ble(ops::route(frame.opcode()))
        {
            return Err(Error::Transport {
                message: format!(
                    "opcode 0x{:02x} does not go on {}",
                    frame.opcode(),
                    route_name(route)
                ),
            });
        }
        let permit = Arc::clone(&self.permit)
            .acquire_owned()
            .await
            .map_err(|_| Error::Transport {
                message: "write permit closed".to_string(),
            })?;
        log::trace!(target: LOG_TARGET, "tx {} +{} {frame:?}", route_name(route), self.offset_ms());
        let inner = Arc::clone(&self.inner);
        let owned = frame.clone();
        let write = tokio::spawn(async move {
            let result = inner.send(&owned, route).await;
            drop(permit);
            result
        });
        match write.await {
            Ok(result) => result,
            Err(join) => Err(Error::Transport {
                message: format!("write task failed: {join}"),
            }),
        }
    }

    /// The next item, or `None` once the link was reported closed.
    pub async fn recv(&mut self) -> Option<Incoming> {
        if self.closed {
            return None;
        }
        match self.rx.recv().await {
            Some(RawIncoming {
                route,
                at,
                item: Ok(frame),
            }) => {
                log::trace!(target: LOG_TARGET, "rx {} +{} {frame:?}", route_name(route), self.offset_of(at));
                Some(Incoming {
                    route,
                    at,
                    item: Item::Frame(frame),
                })
            }
            Some(RawIncoming {
                route,
                at,
                item: Err(reason),
            }) => {
                self.errors = self.errors.saturating_add(1);
                log::warn!(target: LOG_TARGET, "rx {} +{} error: {reason}", route_name(route), self.offset_of(at));
                Some(Incoming {
                    route,
                    at,
                    item: Item::Error(reason),
                })
            }
            None => {
                self.closed = true;
                let route = match self.inner.description().kind {
                    Kind::Ble => Route::Ble(BleRoute::Af01),
                    Kind::Hid => Route::Hid,
                };
                log::trace!(target: LOG_TARGET, "rx {} +{} link closed", route_name(route), self.offset_ms());
                Some(Incoming {
                    route,
                    at: Instant::now(),
                    item: Item::LinkClosed,
                })
            }
        }
    }

    /// Parse errors seen so far.
    #[must_use]
    pub fn errors(&self) -> u64 {
        self.errors
    }

    /// Closes the underlying transport.
    ///
    /// # Errors
    ///
    /// Whatever the transport's `close` reports.
    pub async fn close(&self) -> Result<(), Error> {
        self.inner.close().await
    }

    /// The transport's description.
    #[must_use]
    pub fn description(&self) -> &Description {
        self.inner.description()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::protocol::ble::BleRoute;
    use crate::protocol::error::Reason;
    use crate::protocol::frame::Frame;
    use crate::protocol::ops::{bind, telemetry};
    use crate::transport::description::Kind;
    use crate::transport::stub::Stub;
    use crate::transport::test_log;
    use core::time::Duration;
    use tokio::time::{advance, timeout, Instant};

    const AF01: Route = Route::Ble(BleRoute::Af01);

    fn c3() -> Frame {
        Frame::new(0xC3, telemetry::tests::C3_PAYLOAD.to_vec()).unwrap()
    }

    /// Test: UT-TRANS-002
    #[tokio::test(start_paused = true)]
    async fn send_refuses_foreign_opcodes_wrong_lengths_and_wrong_routes() {
        let (stub, _tx, sent) = Stub::new(Kind::Ble, "s", Duration::ZERO);
        let guarded = Guarded::new(stub);
        guarded.send(&telemetry::request(), AF01).await.unwrap();
        let c6 = Frame::new(0xC6, vec![0; 12]).unwrap();
        assert_eq!(
            guarded.send(&c6, AF01).await.unwrap_err(),
            Error::Protocol(Reason::NotAllowed(0xC6))
        );
        let short = Frame::new(0xC8, vec![0; 10]).unwrap();
        assert_eq!(
            guarded.send(&short, AF01).await.unwrap_err(),
            Error::Protocol(Reason::BadLength {
                expected: 11,
                got: 10
            })
        );
        let id = bind::HostId::new([1; 16]).unwrap();
        assert!(matches!(
            guarded.send(&bind::request(&id, true), AF01).await,
            Err(Error::Transport { .. })
        ));
        assert_eq!(sent.lock().unwrap().len(), 1);
    }

    /// Test: UT-TRANS-003
    #[tokio::test(start_paused = true)]
    async fn sends_are_serialised_even_when_one_is_cancelled() {
        let (stub, _tx, sent) = Stub::new(Kind::Ble, "s", Duration::from_millis(100));
        let guarded = Guarded::new(stub);
        let start = Instant::now();
        let req = telemetry::request();
        let a = guarded.send(&req, AF01);
        let b = guarded.send(&req, AF01);
        let (ra, rb) = tokio::join!(a, b);
        ra.unwrap();
        rb.unwrap();
        let times: Vec<_> = sent
            .lock()
            .unwrap()
            .iter()
            .map(|(at, _, _)| *at - start)
            .collect();
        assert_eq!(times, vec![Duration::ZERO, Duration::from_millis(100)]);
        // A send cancelled by a timeout still completes its write and holds the permit.
        let t = Instant::now();
        assert!(timeout(
            Duration::from_millis(10),
            guarded.send(&telemetry::request(), AF01)
        )
        .await
        .is_err());
        guarded.send(&telemetry::request(), AF01).await.unwrap();
        let times: Vec<_> = sent
            .lock()
            .unwrap()
            .iter()
            .skip(2)
            .map(|(at, _, _)| *at - t)
            .collect();
        assert_eq!(times, vec![Duration::ZERO, Duration::from_millis(100)]);
    }

    /// Test: UT-TRANS-004
    #[tokio::test(start_paused = true)]
    async fn recv_stamps_counts_and_logs() {
        let log = test_log::install();
        let (stub, tx, _sent) = Stub::new(Kind::Ble, "s", Duration::ZERO);
        let mut guarded = Guarded::new(stub);
        let start = Instant::now();
        guarded.send(&telemetry::request(), AF01).await.unwrap();
        tx.send(RawIncoming {
            route: AF01,
            at: Instant::now(),
            item: Ok(c3()),
        })
        .unwrap();
        advance(Duration::from_millis(50)).await;
        tx.send(RawIncoming {
            route: AF01,
            at: Instant::now(),
            item: Err(Reason::Short {
                needed: 36,
                got: 35,
            }),
        })
        .unwrap();
        let first = guarded.recv().await.unwrap();
        let second = guarded.recv().await.unwrap();
        assert_eq!(first.at - start, Duration::ZERO);
        assert!(matches!(first.item, Item::Frame(ref f) if f.opcode() == 0xC3));
        assert_eq!(second.at - start, Duration::from_millis(50));
        assert!(matches!(second.item, Item::Error(Reason::Short { .. })));
        assert_eq!(guarded.errors(), 1);
        let c6 = Frame::new(0xC6, vec![]).unwrap();
        let _ = guarded.send(&c6, AF01).await;
        let lines = log.lines("mp305_core::frames");
        assert!(
            lines
                .iter()
                .any(|(lvl, m)| *lvl == log::Level::Trace && m.starts_with("tx ble AF01 +0 c2")),
            "{lines:?}"
        );
        assert!(
            lines
                .iter()
                .any(|(lvl, m)| *lvl == log::Level::Trace && m.starts_with("rx ble AF01 +0 c3 ")),
            "{lines:?}"
        );
        assert!(
            lines.iter().any(
                |(lvl, m)| *lvl == log::Level::Warn && m.starts_with("rx ble AF01 +50 error: ")
            ),
            "{lines:?}"
        );
        assert!(
            lines
                .iter()
                .any(|(lvl, m)| *lvl == log::Level::Warn
                    && m.starts_with("tx ble AF01 +50 failed: ")),
            "{lines:?}"
        );
    }

    /// Test: UT-TRANS-005
    #[tokio::test(start_paused = true)]
    async fn a_dropped_sender_becomes_one_link_closed_then_none() {
        let (stub, tx, _sent) = Stub::new(Kind::Hid, "h", Duration::ZERO);
        let mut guarded = Guarded::new(stub);
        drop(tx);
        assert!(matches!(
            guarded.recv().await,
            Some(Incoming {
                item: Item::LinkClosed,
                ..
            })
        ));
        assert!(guarded.recv().await.is_none());
        assert!(guarded.recv().await.is_none());
    }

    /// Test: UT-TRANS-041
    #[tokio::test(start_paused = true)]
    async fn timestamps_come_from_the_producer_not_the_reader() {
        let (stub, tx, _sent) = Stub::new(Kind::Ble, "s", Duration::from_millis(200));
        let mut guarded = Guarded::new(stub);
        let start = Instant::now();
        let tx2 = tx.clone();
        let feeder = tokio::spawn(async move {
            tx2.send(RawIncoming {
                route: AF01,
                at: Instant::now(),
                item: Ok(c3()),
            })
            .unwrap();
            tokio::time::sleep(Duration::from_millis(50)).await;
            tx2.send(RawIncoming {
                route: AF01,
                at: Instant::now(),
                item: Ok(c3()),
            })
            .unwrap();
        });
        guarded.send(&telemetry::request(), AF01).await.unwrap();
        feeder.await.unwrap();
        let a = guarded.recv().await.unwrap();
        let b = guarded.recv().await.unwrap();
        assert_eq!(a.at - start, Duration::ZERO);
        assert_eq!(b.at - start, Duration::from_millis(50));
    }
}
