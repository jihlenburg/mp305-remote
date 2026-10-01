//! A test double for `Transport`: the test feeds its channel and reads what
//! it was asked to send. Compiled for tests and the `mock` feature only.
//!
//! Implements: nothing; supports the unit tests of `guarded` (UT-TRANS-002
//! to 005, 041), UT-TRANS-006 and the task tests of `link` (UT-LINK-005 to
//! 028), as the transport DD's section 7 preamble describes.

use std::sync::atomic::{AtomicUsize, Ordering};
use std::sync::{Arc, Mutex};

use core::time::Duration;

use tokio::sync::mpsc;
use tokio::time::Instant;

use crate::error::Error;
use crate::protocol::ble::Route;
use crate::protocol::frame::Frame;
use crate::transport::description::{Description, Kind};
use crate::transport::{RawIncoming, Transport};

/// Every send the stub accepted: when the write started, where, what.
pub type Sends = Arc<Mutex<Vec<(Instant, Route, Frame)>>>;

/// The switches and counters of a [`Stub`] that stay reachable after the
/// stub was moved into a `Guarded`.
#[derive(Clone, Debug, Default)]
pub struct StubHandle {
    /// The error text the next send fails with, if set.
    fail_next: Arc<Mutex<Option<String>>>,
    /// How often `close` was called.
    closes: Arc<AtomicUsize>,
}

impl StubHandle {
    /// Makes the next send fail with `Error::Transport { message: text }`
    /// without recording it.
    pub fn fail_next_send(&self, text: &str) {
        if let Ok(mut next) = self.fail_next.lock() {
            *next = Some(text.to_string());
        }
    }

    /// How often `close` was called.
    #[must_use]
    pub fn closes(&self) -> usize {
        self.closes.load(Ordering::SeqCst)
    }
}

/// The double.
pub struct Stub {
    /// The kind and identifier it reports.
    description: Description,
    /// How long each send takes on the Tokio clock.
    delay: Duration,
    /// The sends it accepted.
    sends: Sends,
    /// The channel the test feeds.
    rx: mpsc::UnboundedReceiver<RawIncoming>,
    /// The failure switch and the close counter.
    handle: StubHandle,
}

impl Stub {
    /// A stub of the given kind whose sends take `delay`; returns the stub,
    /// the sender the test feeds, and the record of sends.
    #[must_use]
    pub fn new(
        kind: Kind,
        identifier: &str,
        delay: Duration,
    ) -> (Self, mpsc::UnboundedSender<RawIncoming>, Sends) {
        let (tx, rx) = mpsc::unbounded_channel();
        let sends: Sends = Arc::new(Mutex::new(Vec::new()));
        let stub = Self {
            description: Description {
                kind,
                identifier: identifier.to_string(),
            },
            delay,
            sends: Arc::clone(&sends),
            rx,
            handle: StubHandle::default(),
        };
        (stub, tx, sends)
    }

    /// A handle to the failure switch and the close counter.
    #[must_use]
    pub fn handle(&self) -> StubHandle {
        self.handle.clone()
    }

    /// Makes the next send fail (see [`StubHandle::fail_next_send`]).
    pub fn fail_next_send(&self, text: &str) {
        self.handle.fail_next_send(text);
    }

    /// How often `close` was called.
    #[must_use]
    pub fn closes(&self) -> usize {
        self.handle.closes()
    }
}

impl Transport for Stub {
    async fn send(&self, frame: &Frame, route: Route) -> Result<(), Error> {
        let failure = self
            .handle
            .fail_next
            .lock()
            .ok()
            .and_then(|mut next| next.take());
        if let Some(message) = failure {
            return Err(Error::Transport { message });
        }
        // Recorded at the write start, so the record is readable while the
        // write is still in progress.
        if let Ok(mut sends) = self.sends.lock() {
            sends.push((Instant::now(), route, frame.clone()));
        }
        tokio::time::sleep(self.delay).await;
        Ok(())
    }

    fn incoming(&mut self) -> &mut mpsc::UnboundedReceiver<RawIncoming> {
        &mut self.rx
    }

    async fn close(&self) -> Result<(), Error> {
        self.handle.closes.fetch_add(1, Ordering::SeqCst);
        Ok(())
    }

    fn description(&self) -> &Description {
        &self.description
    }
}
