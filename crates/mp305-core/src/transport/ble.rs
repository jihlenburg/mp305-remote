//! Bluetooth LE through `btleplug`: the glue between the `AF00` service and
//! the `Transport` trait. Nothing testable lives here; the route mapping is
//! in `ble_route`, the MTU verdict in `ble_mtu` and the framing in
//! `protocol::ble`.
//!
//! Coverage: this file is excluded from the measurement under ADR-0013.
//! Every function is verified by inspection (IT-016, UT-TRANS-011) and by
//! the system tests on the supply (ST-008, ST-039).
//!
//! Implements: DD-TRANS-010, DD-TRANS-011, DD-TRANS-012, DD-TRANS-026.

use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::Arc;

use btleplug::api::{
    Central, CentralEvent, Characteristic, Peripheral as _, ValueNotification, WriteType,
};
use btleplug::platform::{Adapter, Peripheral, PeripheralId};
use futures::StreamExt;
use tokio::sync::mpsc;
use tokio::task::JoinHandle;
use tokio::time::Instant;

use crate::error::Error;
use crate::protocol::ble::{self as framing, BleRoute, Route};
use crate::protocol::frame::Frame;
use crate::transport::ble_mtu::{mtu_verdict, MtuVerdict, MIN_MTU, MTU_STEP};
use crate::transport::ble_route::{route_of, AF01, AF02};
use crate::transport::description::{Description, Kind};
use crate::transport::guarded::LOG_TARGET;
use crate::transport::{RawIncoming, Transport};

/// A connected supply over Bluetooth LE. The module is crate-private:
/// a `Ble` exists only inside a `Guarded` (DD-TRANS-012).
pub struct Ble {
    /// Kind and OS identifier.
    description: Description,
    /// The connected peripheral.
    peripheral: Arc<Peripheral>,
    /// The command characteristic.
    af01: Characteristic,
    /// The bind characteristic.
    af02: Characteristic,
    /// The reader task; aborted on close and on drop.
    reader: JoinHandle<()>,
    /// The channel the reader delivers on.
    rx: mpsc::UnboundedReceiver<RawIncoming>,
    /// Set once [`Ble::shut_down`] issued the disconnect and it returned
    /// without error, so that `Drop` does not disconnect again.
    disconnected: AtomicBool,
}

/// Maps a `btleplug` error to the crate error. (ADR-0013: inspection.)
fn transport_error(error: btleplug::Error) -> Error {
    Error::Transport {
        message: error.to_string(),
    }
}

/// The hex of `bytes` for the wire log. (ADR-0013: inspection.)
fn hex(bytes: &[u8]) -> String {
    bytes
        .iter()
        .map(|b| format!("{b:02x}"))
        .collect::<Vec<_>>()
        .join(" ")
}

impl Ble {
    /// Connects to the peripheral `os_id` on `adapter`, verifies the
    /// negotiated MTU ([`check_mtu`]), subscribes to AF01 and AF02, and
    /// starts the reader. (ADR-0013: inspection, IT-016, ST-008.)
    ///
    /// # Errors
    ///
    /// [`Error::Transport`] when the peripheral is not known to the adapter,
    /// a `btleplug` call fails, a negotiated MTU is below [`MIN_MTU`], or a
    /// characteristic is missing.
    pub(crate) async fn connect(adapter: &Adapter, os_id: &PeripheralId) -> Result<Self, Error> {
        // The event stream first, so that a disconnect during connect is seen.
        let mut events = adapter.events().await.map_err(transport_error)?;
        let peripheral = adapter
            .peripherals()
            .await
            .map_err(transport_error)?
            .into_iter()
            .find(|p| p.id() == *os_id)
            .ok_or_else(|| Error::Transport {
                message: format!("peripheral {os_id} not found"),
            })?;
        // The notification stream before subscribing, so that no early notification is lost.
        let mut notifications = peripheral.notifications().await.map_err(transport_error)?;
        peripheral.connect().await.map_err(transport_error)?;
        peripheral
            .discover_services()
            .await
            .map_err(transport_error)?;
        if let Err(error) = check_mtu(&peripheral, os_id).await {
            let _ = peripheral.disconnect().await;
            return Err(error);
        }
        let characteristics = peripheral.characteristics();
        let find = |uuid| {
            characteristics
                .iter()
                .find(|c| c.uuid == uuid)
                .cloned()
                .ok_or_else(|| Error::Transport {
                    message: format!("characteristic {uuid} missing"),
                })
        };
        let af01 = find(AF01)?;
        let af02 = find(AF02)?;
        peripheral.subscribe(&af01).await.map_err(transport_error)?;
        peripheral.subscribe(&af02).await.map_err(transport_error)?;
        let (tx, rx) = mpsc::unbounded_channel();
        let this_id = os_id.clone();
        let reader = tokio::spawn(async move {
            loop {
                tokio::select! {
                    notification = notifications.next() => {
                        let Some(ValueNotification { uuid, value, .. }) = notification else { break };
                        let at = Instant::now();
                        log::trace!(target: LOG_TARGET, "wire rx ble {uuid} {}", hex(&value));
                        let Some(route) = route_of(&uuid) else {
                            log::debug!(target: LOG_TARGET, "notification from {uuid} dropped");
                            continue;
                        };
                        let item = framing::decode(&value, route);
                        if tx.send(RawIncoming { route: Route::Ble(route), at, item }).is_err() {
                            break;
                        }
                    }
                    event = events.next() => {
                        match event {
                            Some(CentralEvent::DeviceDisconnected(id)) if id == this_id => break,
                            Some(_) => continue,
                            None => break,
                        }
                    }
                }
            }
            // Dropping `tx` here signals the lost link (DD-TRANS-004).
        });
        Ok(Self {
            description: Description {
                kind: Kind::Ble,
                identifier: os_id.to_string(),
            },
            peripheral: Arc::new(peripheral),
            af01,
            af02,
            reader,
            rx,
            disconnected: AtomicBool::new(false),
        })
    }

    /// The characteristic of a route. (ADR-0013: inspection.)
    fn characteristic(&self, route: Route) -> Result<&Characteristic, Error> {
        match route {
            Route::Ble(BleRoute::Af01) => Ok(&self.af01),
            Route::Ble(BleRoute::Af02) => Ok(&self.af02),
            Route::Hid => Err(Error::Transport {
                message: "HID route on a Bluetooth link".to_string(),
            }),
        }
    }

    /// Writes one frame with response. (ADR-0013: inspection, ST-039.)
    pub(crate) async fn write_frame(&self, frame: &Frame, route: Route) -> Result<(), Error> {
        let characteristic = self.characteristic(route)?;
        let Route::Ble(ble_route) = route else {
            return Err(Error::Transport {
                message: "HID route on a Bluetooth link".to_string(),
            });
        };
        let bytes = framing::encode(frame, ble_route);
        log::trace!(target: LOG_TARGET, "wire tx ble {} {}", characteristic.uuid, hex(&bytes));
        self.peripheral
            .write(characteristic, &bytes, WriteType::WithResponse)
            .await
            .map_err(transport_error)
    }

    /// Unsubscribes, disconnects and stops the reader; errors on a link
    /// already lost are ignored. A disconnect that returned without error
    /// is recorded, so that `Drop` does not repeat it; after a failed one
    /// `Drop` tries again. (ADR-0013: inspection.)
    pub(crate) async fn shut_down(&self) -> Result<(), Error> {
        let _ = self.peripheral.unsubscribe(&self.af01).await;
        let _ = self.peripheral.unsubscribe(&self.af02).await;
        if self.peripheral.disconnect().await.is_ok() {
            self.disconnected.store(true, Ordering::Release);
        }
        self.reader.abort();
        Ok(())
    }
}

/// Reads the ATT MTU after the service discovery and applies
/// [`mtu_verdict`]: a value at or above [`MIN_MTU`] passes at once; a lower
/// one is read again every [`MTU_STEP`] for up to `ble_mtu::MTU_WAIT`. At
/// the end, a value of exactly 23 is logged at WARN and the connect goes on
/// (the operating system may not report the MTU), and any other value below
/// [`MIN_MTU`] refuses the link. The value is logged at TRACE.
/// (ADR-0013: inspection, UT-TRANS-042, ST-008.)
///
/// # Errors
///
/// [`Error::Transport`] with `ATT MTU <n> below 74` for a refused value.
async fn check_mtu(peripheral: &Peripheral, os_id: &PeripheralId) -> Result<(), Error> {
    let mut waited = core::time::Duration::ZERO;
    loop {
        let mtu = peripheral.mtu();
        match mtu_verdict(mtu, waited) {
            MtuVerdict::Pass => {
                log::trace!(target: LOG_TARGET, "ble {os_id}: negotiated ATT MTU {mtu}");
                return Ok(());
            }
            MtuVerdict::Wait => {
                tokio::time::sleep(MTU_STEP).await;
                waited = waited.saturating_add(MTU_STEP);
            }
            MtuVerdict::Unreported => {
                log::warn!(
                    target: LOG_TARGET,
                    "ATT MTU reported as {mtu}; the operating system may not report it, continuing"
                );
                return Ok(());
            }
            MtuVerdict::Refuse => {
                log::trace!(target: LOG_TARGET, "ble {os_id}: negotiated ATT MTU {mtu}");
                return Err(Error::Transport {
                    message: format!("ATT MTU {mtu} below {MIN_MTU}"),
                });
            }
        }
    }
}

impl Transport for Ble {
    async fn send(&self, frame: &Frame, route: Route) -> Result<(), Error> {
        self.write_frame(frame, route).await
    }

    fn incoming(&mut self) -> &mut mpsc::UnboundedReceiver<RawIncoming> {
        &mut self.rx
    }

    async fn close(&self) -> Result<(), Error> {
        self.shut_down().await
    }

    fn description(&self) -> &Description {
        &self.description
    }
}

impl Drop for Ble {
    /// Stops the reader and, unless [`Ble::shut_down`] already disconnected,
    /// disconnects on a best-effort basis when a runtime is available.
    /// (ADR-0013: inspection.)
    fn drop(&mut self) {
        self.reader.abort();
        if self.disconnected.load(Ordering::Acquire) {
            return;
        }
        if let Ok(handle) = tokio::runtime::Handle::try_current() {
            let peripheral = Arc::clone(&self.peripheral);
            handle.spawn(async move {
                let _ = peripheral.disconnect().await;
            });
        }
    }
}
