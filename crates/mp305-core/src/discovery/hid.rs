//! Implements: DD-DISC-013.
//!
//! The USB HID side of discovery through `hidapi`: the probe, the
//! enumeration that feeds `classify::hid`, and the open behind `Guarded`.
//! Nothing decidable lives here; the classification is in `classify` and
//! the connect plan in `classify::connect_plan`.
//!
//! Every call builds a fresh `HidApi::new()` inside `spawn_blocking`
//! (enumeration can be slow on Windows because of the stalling serial
//! request, TBD-013), so no context is stored and no `std::sync` guard is
//! ever held across an `.await`. `HidApi::new_without_enumerate` is never
//! used: it sets a process-wide flag and panics after an enumerating
//! context exists.
//!
//! Coverage: this file is excluded from the measurement under ADR-0014.
//! Every function is verified by inspection (UT-DISC-011), the
//! classification it feeds by IT-032, and the whole by the system tests on
//! the supply (ST-001 to ST-003).

use std::collections::BTreeSet;
use std::ffi::{CStr, CString};

use hidapi::HidApi;
use tokio::task::{spawn_blocking, JoinError};

use crate::discovery::{classify, Found, LOG_TARGET};
use crate::error::Error;
use crate::transport::guarded::Guarded;
use crate::transport::AnyTransport;

/// One enumerated HID device: the path as text (`to_string_lossy`, the
/// identifier), the path as the OS returned it (for the open), the vendor
/// identifier, the product identifier and the product string.
pub(crate) type Enumerated = (String, CString, u16, u16, Option<String>);

/// Maps a `hidapi` error to the crate error. (ADR-0014: inspection
/// UT-DISC-011.)
fn transport_error(error: hidapi::HidError) -> Error {
    Error::Transport {
        message: error.to_string(),
    }
}

/// Maps a failed blocking task to the crate error. (ADR-0014: inspection
/// UT-DISC-011.)
fn join_error(error: JoinError) -> Error {
    Error::Transport {
        message: format!("HID task failed: {error}"),
    }
}

/// Probes the USB side: whether a `hidapi` context can be built. A failure
/// is logged at WARN. (ADR-0014: inspection UT-DISC-010, ST-003.)
pub(crate) async fn available() -> bool {
    let probe = spawn_blocking(|| HidApi::new().map(drop).map_err(transport_error))
        .await
        .map_err(join_error)
        .and_then(|outcome| outcome);
    match probe {
        Ok(()) => true,
        Err(error) => {
            log::warn!(target: LOG_TARGET, "no USB HID backend: {error}");
            false
        }
    }
}

/// Enumerates the HID devices with a fresh context inside `spawn_blocking`,
/// de-duplicated by path text, first entry kept. (ADR-0014: inspection
/// UT-DISC-011, ST-003.)
///
/// # Errors
///
/// [`Error::Transport`] when the context cannot be built or the blocking
/// task fails.
pub(crate) async fn enumerate() -> Result<Vec<Enumerated>, Error> {
    spawn_blocking(|| {
        let api = HidApi::new().map_err(transport_error)?;
        let mut paths = BTreeSet::new();
        Ok(api
            .device_list()
            .map(|device| {
                (
                    device.path().to_string_lossy().into_owned(),
                    device.path().to_owned(),
                    device.vendor_id(),
                    device.product_id(),
                    device.product_string().map(str::to_string),
                )
            })
            .filter(|(text, ..)| paths.insert(text.clone()))
            .collect())
    })
    .await
    .map_err(join_error)?
}

/// The USB scan: the enumeration fed through `classify::hid` with vendor,
/// product, product string and path. (ADR-0014: inspection UT-DISC-011,
/// IT-032, ST-003.)
///
/// # Errors
///
/// Whatever [`enumerate`] reports.
pub(crate) async fn scan() -> Result<Vec<Found>, Error> {
    Ok(enumerate()
        .await?
        .into_iter()
        .filter_map(|(text, _, vendor_id, product_id, product)| {
            classify::hid(vendor_id, product_id, product.as_deref(), &text)
        })
        .collect())
}

/// Opens the device at `path` (the `CString` the enumeration returned)
/// through `Guarded::open_hid`, with a fresh context, inside
/// `spawn_blocking`. (ADR-0014: inspection UT-DISC-011, ST-003.)
///
/// # Errors
///
/// [`Error::Transport`] when the context cannot be built, the device cannot
/// be opened, or the blocking task fails.
pub(crate) async fn open(path: &CStr) -> Result<Guarded<AnyTransport>, Error> {
    let path = path.to_owned();
    spawn_blocking(move || {
        let api = HidApi::new().map_err(transport_error)?;
        Guarded::open_hid(&api, &path)
    })
    .await
    .map_err(join_error)?
}
