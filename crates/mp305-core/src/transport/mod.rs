//! The transports: the `Transport` trait, the `Guarded` wrapper that every
//! path to a supply goes through, the Bluetooth LE and USB HID
//! implementations, and the scripted mock for tests.
//!
//! Implements: DD-TRANS-001 (module tree, `AnyTransport`).

pub(crate) mod ble;
pub mod ble_mtu;
pub mod ble_route;
pub mod description;
pub mod guarded;
pub(crate) mod hid;
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
///
/// It is opaque: the products obtain one through
/// [`guarded::Guarded::connect_ble`] or [`guarded::Guarded::open_hid`] and
/// never see the transport inside. The `ble` and `hid` modules are
/// crate-private, so a `Ble` or a `Hid` can be neither named nor obtained
/// outside this crate, and the unguarded `Transport::send` of a real
/// transport stays out of reach (SR-006). Under the `mock` feature,
/// `From<Mock>` wraps the scripted mock.
///
/// The three examples below must not compile (Test: UT-TRANS-007).
///
/// ```compile_fail,E0603
/// use mp305_core::transport::ble::Ble;
/// ```
///
/// ```compile_fail,E0603
/// use mp305_core::transport::hid::Hid;
/// ```
///
/// ```compile_fail,E0603
/// fn unwrap(t: mp305_core::transport::AnyTransport) {
///     let mp305_core::transport::AnyTransport(inner) = t;
/// }
/// ```
pub struct AnyTransport(Inner);

/// The transport inside an [`AnyTransport`]. Private, so that no code
/// outside this crate can reach the wrapped transport.
// The glue types are much larger than the mock; boxing them buys nothing.
#[allow(clippy::large_enum_variant)]
enum Inner {
    /// Bluetooth LE.
    Ble(ble::Ble),
    /// USB HID.
    Hid(hid::Hid),
    /// The scripted mock (tests and the Python test constructor).
    #[cfg(any(test, feature = "mock"))]
    Mock(mock::Mock),
}

impl AnyTransport {
    /// Wraps a Bluetooth transport. Only `Guarded::connect_ble` calls it.
    pub(crate) fn ble(transport: ble::Ble) -> Self {
        Self(Inner::Ble(transport))
    }

    /// Wraps a HID transport. Only `Guarded::open_hid` calls it.
    pub(crate) fn hid(transport: hid::Hid) -> Self {
        Self(Inner::Hid(transport))
    }
}

#[cfg(any(test, feature = "mock"))]
impl From<mock::Mock> for AnyTransport {
    fn from(mock: mock::Mock) -> Self {
        Self(Inner::Mock(mock))
    }
}

impl Transport for AnyTransport {
    async fn send(&self, frame: &Frame, route: Route) -> Result<(), Error> {
        match &self.0 {
            Inner::Ble(t) => t.send(frame, route).await,
            Inner::Hid(t) => t.send(frame, route).await,
            #[cfg(any(test, feature = "mock"))]
            Inner::Mock(t) => t.send(frame, route).await,
        }
    }

    fn incoming(&mut self) -> &mut mpsc::UnboundedReceiver<RawIncoming> {
        match &mut self.0 {
            Inner::Ble(t) => t.incoming(),
            Inner::Hid(t) => t.incoming(),
            #[cfg(any(test, feature = "mock"))]
            Inner::Mock(t) => t.incoming(),
        }
    }

    async fn close(&self) -> Result<(), Error> {
        match &self.0 {
            Inner::Ble(t) => t.close().await,
            Inner::Hid(t) => t.close().await,
            #[cfg(any(test, feature = "mock"))]
            Inner::Mock(t) => t.close().await,
        }
    }

    fn description(&self) -> &Description {
        match &self.0 {
            Inner::Ble(t) => t.description(),
            Inner::Hid(t) => t.description(),
            #[cfg(any(test, feature = "mock"))]
            Inner::Mock(t) => t.description(),
        }
    }
}
