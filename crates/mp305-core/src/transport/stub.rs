//! A test double for `Transport`: the test feeds its channel and reads what
//! it was asked to send. Compiled for tests and the `mock` feature only.
//!
//! Implements: nothing; supports the unit tests of `guarded` (UT-TRANS-002
//! to 005, 041) and UT-TRANS-006.

use std::sync::{Arc, Mutex};

use core::time::Duration;

use tokio::sync::mpsc;
use tokio::time::Instant;

use crate::error::Error;
use crate::protocol::ble::Route;
use crate::protocol::frame::Frame;
use crate::transport::description::{Description, Kind};
use crate::transport::{RawIncoming, Transport};

/// Every send the stub accepted: when, where, what.
pub type Sends = Arc<Mutex<Vec<(Instant, Route, Frame)>>>;

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
        };
        (stub, tx, sends)
    }
}

impl Transport for Stub {
    async fn send(&self, frame: &Frame, route: Route) -> Result<(), Error> {
        let at = Instant::now();
        tokio::time::sleep(self.delay).await;
        if let Ok(mut sends) = self.sends.lock() {
            sends.push((at, route, frame.clone()));
        }
        Ok(())
    }

    fn incoming(&mut self) -> &mut mpsc::UnboundedReceiver<RawIncoming> {
        &mut self.rx
    }

    async fn close(&self) -> Result<(), Error> {
        Ok(())
    }

    fn description(&self) -> &Description {
        &self.description
    }
}
