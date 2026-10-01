//! Implements: DD-DISC-010, DD-DISC-011, DD-DISC-012.
//!
//! The Bluetooth LE side of discovery through `btleplug`: the adapter
//! probe, the scan loop that feeds `classify::Sightings`, the reads of
//! `properties()` that feed `classify::advertisement`, the `find` that
//! looks for one identifier, and the bounded connect behind `Guarded`.
//! Nothing decidable lives here; which events count, which sightings match
//! and how an identifier is reached are decided in `classify`.
//!
//! The scan lock is held from before `start_scan` until after `stop_scan`,
//! because CoreBluetooth, the BlueZ session and the Windows watcher each
//! keep one discovery state per client, so a second scan's `stop_scan`
//! would end the first. When a scan future is dropped early, a guard issues
//! `stop_scan` on a spawned task and releases the lock only after it.
//!
//! Coverage: this file is excluded from the measurement under ADR-0014.
//! Every function is verified by inspection (UT-DISC-010), the accumulator
//! and the classification it feeds by IT-032, and the whole by the system
//! tests on the supply (ST-001 to ST-003).

use core::fmt::Write as _;
use core::time::Duration;
use std::collections::{BTreeSet, HashMap};
use std::sync::Arc;

use btleplug::api::{Central as _, CentralEvent, Manager as _, Peripheral as _, ScanFilter};
use btleplug::platform::{Manager, Peripheral, PeripheralId};
use futures::StreamExt;
use tokio::runtime::Handle;
use tokio::sync::{Mutex, OwnedMutexGuard};

use crate::discovery::classify::{self, SightingEvent, Sightings};
use crate::discovery::{Found, LOG_TARGET};
use crate::error::Error;
use crate::protocol::timing;
use crate::transport::guarded::Guarded;
use crate::transport::AnyTransport;

/// The Bluetooth adapter type, named here so that the rest of discovery
/// never names the vendor library.
pub(crate) type Adapter = btleplug::platform::Adapter;

/// Maps a `btleplug` error to the crate error. (ADR-0014: inspection
/// UT-DISC-010.)
fn transport_error(error: btleplug::Error) -> Error {
    Error::Transport {
        message: error.to_string(),
    }
}

/// The text of a peripheral id, written with `fmt::Write` so that a
/// `Display` that fails skips the id instead of panicking as `to_string`
/// would. (ADR-0014: inspection UT-DISC-010.)
fn id_text(id: &PeripheralId) -> Option<String> {
    let mut text = String::new();
    match write!(text, "{id}") {
        Ok(()) => Some(text),
        Err(_) => {
            log::debug!(target: LOG_TARGET, "a peripheral id without a text skipped");
            None
        }
    }
}

/// The `Manager` and its first adapter. A failing `Manager::new`, an
/// `adapters()` error and an empty list all count as no adapter and are
/// logged at WARN. (ADR-0014: inspection UT-DISC-010, ST-001.)
pub(crate) async fn adapter() -> Option<Adapter> {
    let manager = match Manager::new().await {
        Ok(manager) => manager,
        Err(error) => {
            log::warn!(target: LOG_TARGET, "no Bluetooth: the manager failed: {error}");
            return None;
        }
    };
    match manager.adapters().await {
        Ok(adapters) => {
            let first = adapters.into_iter().next();
            if first.is_none() {
                log::warn!(target: LOG_TARGET, "no Bluetooth: no adapter");
            }
            first
        }
        Err(error) => {
            log::warn!(target: LOG_TARGET, "no Bluetooth: listing the adapters failed: {error}");
            None
        }
    }
}

/// The text of every id the adapter holds now. (ADR-0014: inspection
/// UT-DISC-010.)
///
/// # Errors
///
/// [`Error::Transport`] when `peripherals()` fails.
pub(crate) async fn known_ids(adapter: &Adapter) -> Result<Vec<String>, Error> {
    Ok(adapter
        .peripherals()
        .await
        .map_err(transport_error)?
        .iter()
        .filter_map(|peripheral| id_text(&peripheral.id()))
        .collect())
}

/// The peripheral an event is about and what it is to the accumulator:
/// the four kinds that can count, every other event about a peripheral
/// `Other`, and nothing for an adapter state change. (ADR-0014: inspection
/// UT-DISC-010.)
fn sighting(event: &CentralEvent) -> Option<(&PeripheralId, SightingEvent)> {
    match event {
        CentralEvent::DeviceDiscovered(id) => Some((id, SightingEvent::Discovered)),
        CentralEvent::DeviceUpdated(id) => Some((id, SightingEvent::Updated)),
        CentralEvent::RssiUpdate { id, .. } => Some((id, SightingEvent::Rssi)),
        CentralEvent::ManufacturerDataAdvertisement { id, .. } => {
            Some((id, SightingEvent::ManufacturerData))
        }
        CentralEvent::DeviceConnected(id)
        | CentralEvent::DeviceDisconnected(id)
        | CentralEvent::DeviceServicesModified(id)
        | CentralEvent::ServiceDataAdvertisement { id, .. }
        | CentralEvent::ServicesAdvertisement { id, .. } => Some((id, SightingEvent::Other)),
        CentralEvent::StateUpdate(_) => None,
    }
}

/// Issues `stop_scan`; its error is logged at WARN, not returned.
/// (ADR-0014: inspection UT-DISC-010.)
async fn stop(adapter: &Adapter) {
    if let Err(error) = adapter.stop_scan().await {
        log::warn!(target: LOG_TARGET, "stop_scan failed: {error}");
    }
}

/// Holds the scan lock and, from the call of `start_scan`, the adapter to
/// stop. Dropped before [`ScanStop::finish`] completes (the scan future was
/// cancelled), it issues `stop_scan` on a spawned task and moves the lock
/// guard into that task, so the lock is released only after the stop.
/// (ADR-0014: inspection UT-DISC-010.)
struct ScanStop {
    /// The adapter whose scan may be running; `None` before `start_scan` is
    /// called, when it failed, and after the stop.
    adapter: Option<Adapter>,
    /// The scan lock, held until the scan is stopped.
    lock: Option<OwnedMutexGuard<()>>,
}

impl ScanStop {
    /// Stops the scan and then releases the lock. If this future is itself
    /// dropped during the stop, the drop issues the stop again.
    /// (ADR-0014: inspection UT-DISC-010.)
    async fn finish(mut self) {
        if let Some(adapter) = &self.adapter {
            stop(adapter).await;
        }
        self.adapter = None;
        self.lock = None;
    }
}

impl Drop for ScanStop {
    /// Issues `stop_scan` on a spawned task when the scan was cancelled,
    /// releasing the lock after it. (ADR-0014: inspection UT-DISC-010.)
    fn drop(&mut self) {
        let Some(adapter) = self.adapter.take() else {
            return;
        };
        let lock = self.lock.take();
        match Handle::try_current() {
            Ok(handle) => {
                handle.spawn(async move {
                    stop(&adapter).await;
                    drop(lock);
                });
            }
            Err(_) => {
                log::warn!(target: LOG_TARGET, "scan cancelled outside a runtime; stop_scan not issued");
            }
        }
    }
}

/// The scan loop shared by [`scan`] and [`find`]: takes the scan lock,
/// snapshots the ids the adapter holds into [`Sightings::new`], takes the
/// event stream, starts the scan, feeds every event to
/// [`Sightings::note`] for `bound` (or until the stream ends), and stops
/// the scan. With `wanted`, the loop ends at the first `note` that counts
/// `wanted` and returns its id. (ADR-0014: inspection UT-DISC-010, IT-032,
/// ST-001.)
///
/// # Errors
///
/// [`Error::Transport`] when `peripherals()`, `events()` or `start_scan`
/// fails.
async fn watch(
    adapter: &Adapter,
    lock: Arc<Mutex<()>>,
    wanted: Option<&str>,
    bound: Duration,
) -> Result<(Sightings, Option<PeripheralId>), Error> {
    let mut scan = ScanStop {
        adapter: None,
        lock: Some(lock.lock_owned().await),
    };
    let known: BTreeSet<String> = known_ids(adapter).await?.into_iter().collect();
    let mut sightings = Sightings::new(known);
    // The event stream before the scan starts, so that no early event is lost.
    let mut events = adapter.events().await.map_err(transport_error)?;
    // Armed before the call, so that a cancellation during `start_scan` still
    // issues `stop_scan`; disarmed when the scan did not start.
    scan.adapter = Some(adapter.clone());
    if let Err(error) = adapter.start_scan(ScanFilter::default()).await {
        scan.adapter = None;
        return Err(transport_error(error));
    }
    let mut hit = None;
    let window = tokio::time::sleep(bound);
    tokio::pin!(window);
    loop {
        let event = tokio::select! {
            () = &mut window => break,
            event = events.next() => event,
        };
        let Some(event) = event else { break };
        let Some((id, kind)) = sighting(&event) else {
            // An adapter state change names no peripheral, so the
            // accumulator cannot be fed with it.
            log::debug!(target: LOG_TARGET, "event {event:?} not counted");
            continue;
        };
        let Some(text) = id_text(id) else { continue };
        if sightings.note(&text, kind) && wanted == Some(text.as_str()) {
            hit = Some(id.clone());
            break;
        }
    }
    scan.finish().await;
    Ok((sightings, hit))
}

/// The Bluetooth scan: [`watch`] for `duration`, then `properties()` for
/// each counted id in `seen()` order, the advertised name chosen by
/// `classify::advertised_name`, and the sighting classified by
/// `classify::advertisement`. An id the adapter no longer holds after the
/// scan is skipped at DEBUG. (ADR-0014: inspection UT-DISC-010, IT-032,
/// ST-001, ST-002.)
///
/// # Errors
///
/// [`Error::Transport`] when a `btleplug` call fails.
pub(crate) async fn scan(
    adapter: &Adapter,
    lock: Arc<Mutex<()>>,
    duration: Duration,
) -> Result<Vec<Found>, Error> {
    let (sightings, _) = watch(adapter, lock, None, duration).await?;
    let held: HashMap<String, Peripheral> = adapter
        .peripherals()
        .await
        .map_err(transport_error)?
        .into_iter()
        .filter_map(|peripheral| id_text(&peripheral.id()).map(|text| (text, peripheral)))
        .collect();
    let mut found = Vec::new();
    for id in sightings.seen() {
        let Some(peripheral) = held.get(&id) else {
            log::debug!(target: LOG_TARGET, "{id} no longer held by the adapter");
            continue;
        };
        let properties = peripheral
            .properties()
            .await
            .map_err(transport_error)?
            .unwrap_or_default();
        let name = classify::advertised_name(
            properties.advertisement_name.as_deref(),
            properties.local_name.as_deref(),
        );
        if let Some(supply) = classify::advertisement(
            &id,
            name.as_deref(),
            &properties.manufacturer_data,
            properties.rssi,
        ) {
            found.push(supply);
        }
    }
    Ok(found)
}

/// Looks for `identifier` advertising for at most `bound`: [`watch`]
/// ending at the first counted sighting of it, with the scan stopped before
/// returning. `None` when it was not seen. (ADR-0014: inspection
/// UT-DISC-010, ST-001.)
///
/// # Errors
///
/// [`Error::Transport`] when a `btleplug` call fails.
pub(crate) async fn find(
    adapter: &Adapter,
    lock: Arc<Mutex<()>>,
    identifier: &str,
    bound: Duration,
) -> Result<Option<PeripheralId>, Error> {
    let (_, hit) = watch(adapter, lock, Some(identifier), bound).await?;
    Ok(hit)
}

/// A connect still in flight. Dropped while armed (the connect timed out,
/// or the caller's bound cancelled it), it fetches the peripheral and
/// calls `disconnect()` on a spawned task, logged at WARN, so that an OS
/// connect request left pending cannot complete later and hold the supply.
/// (ADR-0014: inspection UT-DISC-010.)
struct PendingConnect {
    /// The adapter; `None` once the connect completed.
    adapter: Option<Adapter>,
    /// The peripheral being connected.
    id: PeripheralId,
}

impl Drop for PendingConnect {
    /// Issues the best-effort disconnect when still armed. (ADR-0014:
    /// inspection UT-DISC-010.)
    fn drop(&mut self) {
        let Some(adapter) = self.adapter.take() else {
            return;
        };
        let id = self.id.clone();
        let Ok(handle) = Handle::try_current() else {
            log::warn!(target: LOG_TARGET, "connect to {id} abandoned outside a runtime; no disconnect issued");
            return;
        };
        handle.spawn(async move {
            let outcome = match adapter.peripheral(&id).await {
                Ok(peripheral) => peripheral.disconnect().await,
                Err(error) => Err(error),
            };
            match outcome {
                Ok(()) => {
                    log::warn!(target: LOG_TARGET, "connect to {id} abandoned; disconnect issued");
                }
                Err(error) => {
                    log::warn!(target: LOG_TARGET, "connect to {id} abandoned; disconnect failed: {error}");
                }
            }
        });
    }
}

/// Connects to the peripheral `id` through `Guarded::connect_ble` under
/// `timing::CONNECT`, with the best-effort disconnect of
/// [`PendingConnect`] after an expiry. (ADR-0014: inspection UT-DISC-010,
/// ST-001.)
///
/// # Errors
///
/// [`Error::Transport`] when the connect fails or does not complete within
/// `timing::CONNECT`.
pub(crate) async fn connect(
    adapter: &Adapter,
    id: &PeripheralId,
) -> Result<Guarded<AnyTransport>, Error> {
    let mut pending = PendingConnect {
        adapter: Some(adapter.clone()),
        id: id.clone(),
    };
    match tokio::time::timeout(timing::CONNECT, Guarded::connect_ble(adapter, id)).await {
        Ok(outcome) => {
            pending.adapter = None;
            outcome
        }
        Err(_) => Err(Error::Transport {
            message: format!(
                "connect did not complete within {} s",
                timing::CONNECT.as_secs()
            ),
        }),
    }
}
