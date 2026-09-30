//! The transports: the `Transport` trait, the `Guarded` wrapper that every
//! path to a supply goes through, the Bluetooth LE and USB HID
//! implementations, and the scripted mock for tests.
//!
//! Implements: DD-TRANS-001 (module tree).

pub mod ble;
pub mod ble_route;
pub mod description;
pub mod guarded;
pub mod hid;
pub mod hid_report;
#[cfg(any(test, feature = "mock"))]
pub mod mock;
#[cfg(any(test, feature = "mock"))]
pub mod stub;
#[cfg(test)]
pub(crate) mod test_log;

use core::future::Future;

use tokio::sync::mpsc;
use tokio::time::Instant;

use crate::error::Error;
use crate::protocol::ble::Route;
use crate::protocol::error::Reason;
use crate::protocol::frame::Frame;
use description::Description;

/// One item a transport produced: a decoded frame or the reason it could
/// not decode one, with the route it came on and the time it arrived.
#[derive(Debug)]
pub struct RawIncoming {
    /// The characteristic or report path the item arrived on.
    pub route: Route,
    /// When the producer received it.
    pub at: Instant,
    /// The frame, or why it could not be decoded.
    pub item: Result<Frame, Reason>,
}

/// A link to a supply. Implementations decode what arrives and deliver it
/// in order on an unbounded channel; they know nothing about opcodes,
/// binding or remote control. A lost link is signalled by dropping the
/// channel's sender.
///
/// The trait is not object safe; `link` is generic over it and the products
/// use [`AnyTransport`].
pub trait Transport: Send + Sync + 'static {
    /// Writes one frame on the given route.
    fn send(&self, frame: &Frame, route: Route) -> impl Future<Output = Result<(), Error>> + Send;

    /// The channel the transport delivers on.
    fn incoming(&mut self) -> &mut mpsc::UnboundedReceiver<RawIncoming>;

    /// Closes the link. Errors on a link already lost are ignored.
    fn close(&self) -> impl Future<Output = Result<(), Error>> + Send;

    /// The kind and identifier of this link.
    fn description(&self) -> &Description;
}

/// One concrete type over every transport, for the products.
#[allow(clippy::large_enum_variant)]
pub enum AnyTransport {
    /// Bluetooth LE.
    Ble(ble::Ble),
    /// USB HID.
    Hid(hid::Hid),
    /// The scripted mock (tests and the Python test constructor).
    #[cfg(any(test, feature = "mock"))]
    Mock(mock::Mock),
}

impl Transport for AnyTransport {
    async fn send(&self, frame: &Frame, route: Route) -> Result<(), Error> {
        match self {
            AnyTransport::Ble(t) => t.send(frame, route).await,
            AnyTransport::Hid(t) => t.send(frame, route).await,
            #[cfg(any(test, feature = "mock"))]
            AnyTransport::Mock(t) => t.send(frame, route).await,
        }
    }

    fn incoming(&mut self) -> &mut mpsc::UnboundedReceiver<RawIncoming> {
        match self {
            AnyTransport::Ble(t) => t.incoming(),
            AnyTransport::Hid(t) => t.incoming(),
            #[cfg(any(test, feature = "mock"))]
            AnyTransport::Mock(t) => t.incoming(),
        }
    }

    async fn close(&self) -> Result<(), Error> {
        match self {
            AnyTransport::Ble(t) => t.close().await,
            AnyTransport::Hid(t) => t.close().await,
            #[cfg(any(test, feature = "mock"))]
            AnyTransport::Mock(t) => t.close().await,
        }
    }

    fn description(&self) -> &Description {
        match self {
            AnyTransport::Ble(t) => t.description(),
            AnyTransport::Hid(t) => t.description(),
            #[cfg(any(test, feature = "mock"))]
            AnyTransport::Mock(t) => t.description(),
        }
    }
}
