//! Implements: DD-DISC-013.
//!
//! The USB HID side of discovery through `hidapi`: the probe, the
//! enumeration that feeds `classify::hid`, and the connect that opens a
//! device behind `Guarded`. Nothing decidable lives here; the
//! classification is in `classify::hid` and the choice of the device a
//! connect opens in `classify::hid_target`.
//!
//! Every call builds a fresh `HidApi::new()` on the one owner thread of
//! `hid_owner`, never on a thread of Tokio's blocking pool: on macOS
//! `hidapi` ties its process-wide device manager to the thread that first
//! used it, and that thread must not end (see `hid_owner`). The calls are
//! awaited under a bound (`timing::FIND` for the probe and the enumeration,
//! `timing::CONNECT` for the connect), so a slow or stalled enumeration
//! (Windows, the stalling serial request, TBD-013) blocks no runtime thread
//! and no caller for longer than its bound; no context is stored and no
//! `std::sync` guard is ever held across an `.await`. A connect is one
//! owner-thread job: one context lists the devices and opens the chosen one.
//! `HidApi::new_without_enumerate` is never used: it sets a process-wide
//! flag and panics after an enumerating context exists.
//!
//! Coverage: this file is excluded from the measurement under ADR-0014.
//! Every function is verified by inspection (UT-DISC-011), the
//! classification it feeds by IT-032 and UT-DISC-015, and the whole by the
//! system tests on the supply (ST-001 to ST-003).

use std::collections::BTreeSet;
use std::ffi::CString;

use hidapi::HidApi;

use crate::discovery::classify::{self, HidEntry, HidTarget, Purpose};
use crate::discovery::{hid_owner, not_found, Found, LOG_TARGET};
use crate::error::Error;
use crate::protocol::timing;
use crate::transport::guarded::Guarded;
use crate::transport::AnyTransport;

/// Maps a `hidapi` error to the crate error. (ADR-0014: inspection
/// UT-DISC-011.)
fn transport_error(error: hidapi::HidError) -> Error {
    Error::Transport {
        message: error.to_string(),
    }
}

/// Probes the USB side: whether a `hidapi` context can be built within
/// `timing::FIND`. A failure is logged at WARN. (ADR-0014: inspection
/// UT-DISC-010, ST-003.)
pub(crate) async fn available() -> bool {
    let probe = hid_owner::run(timing::FIND, || {
        HidApi::new().map(drop).map_err(transport_error)
    })
    .await;
    match probe {
        Ok(()) => true,
        Err(error) => {
            log::warn!(target: LOG_TARGET, "no USB HID backend: {error}");
            false
        }
    }
}

/// The devices `api` lists, each with the path as the OS returned it (for
/// the open), de-duplicated by path text, first entry kept. Runs on the
/// owner thread. (ADR-0014: inspection UT-DISC-011.)
fn list(api: &HidApi) -> Vec<(HidEntry, CString)> {
    let mut paths = BTreeSet::new();
    api.device_list()
        .map(|device| {
            (
                HidEntry {
                    path: device.path().to_string_lossy().into_owned(),
                    vendor_id: device.vendor_id(),
                    product_id: device.product_id(),
                    product: device.product_string().map(str::to_string),
                },
                device.path().to_owned(),
            )
        })
        .filter(|(entry, _)| paths.insert(entry.path.clone()))
        .collect()
}

/// The USB scan: a fresh context on the owner thread within
/// `timing::FIND`, its list fed through `classify::hid` with vendor,
/// product, product string and path. (ADR-0014: inspection UT-DISC-011,
/// IT-032, ST-003.)
///
/// # Errors
///
/// [`Error::Transport`] when the context cannot be built or the owner
/// thread does not answer within `timing::FIND`.
pub(crate) async fn scan() -> Result<Vec<Found>, Error> {
    let listed = hid_owner::run(timing::FIND, || {
        let api = HidApi::new().map_err(transport_error)?;
        Ok(list(&api))
    })
    .await?;
    Ok(listed
        .into_iter()
        .filter_map(|(entry, _)| {
            classify::hid(
                entry.vendor_id,
                entry.product_id,
                entry.product.as_deref(),
                &entry.path,
            )
        })
        .collect())
}

/// Connects to the supply at the HID path `identifier` in one job on the
/// owner thread, within `timing::CONNECT`: a fresh context lists the
/// devices, `classify::hid_target` chooses the device for `purpose`, and
/// the same context opens it through `Guarded::open_hid`. The choice is
/// logged at INFO. An opened device whose caller stopped waiting is dropped
/// on the owner thread, which closes it. (ADR-0014: inspection UT-DISC-011,
/// ST-003.)
///
/// # Errors
///
/// [`not_found`] when no device is chosen; [`Error::Transport`] when the
/// context cannot be built, the device cannot be opened, or the owner
/// thread does not answer within `timing::CONNECT`.
pub(crate) async fn connect(
    identifier: &str,
    purpose: Purpose,
) -> Result<Guarded<AnyTransport>, Error> {
    let identifier = identifier.to_string();
    hid_owner::run(timing::CONNECT, move || {
        let api = HidApi::new().map_err(transport_error)?;
        let listed = list(&api);
        let target =
            classify::hid_target(&identifier, listed.iter().map(|(entry, _)| entry), purpose);
        log::info!(target: LOG_TARGET, "connect {identifier} {purpose:?} {target:?}");
        let wanted = match &target {
            HidTarget::Exact => identifier.as_str(),
            HidTarget::Moved { path } => path.as_str(),
            HidTarget::NotFound => return Err(not_found()),
        };
        let path = listed
            .iter()
            .find(|(entry, _)| entry.path == wanted)
            .map(|(_, path)| path)
            .ok_or_else(not_found)?;
        Guarded::open_hid(&api, path)
    })
    .await
}
