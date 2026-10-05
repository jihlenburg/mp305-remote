//! Implements: DD-DISC-013.
//!
//! The USB HID side of discovery through `hidapi`: the probe, the
//! enumeration that feeds `classify::hid`, and the open behind `Guarded`.
//! Nothing decidable lives here; the classification is in `classify` and
//! the connect plan in `classify::connect_plan`.
//!
//! Every call builds a fresh `HidApi::new()` on the one owner thread of
//! `hid_owner`, never on a thread of Tokio's blocking pool: on macOS
//! `hidapi` ties its process-wide device manager to the thread that first
//! used it, and that thread must not end (see `hid_owner`). The calls are
//! awaited, so a slow enumeration (Windows, the stalling serial request,
//! TBD-013) blocks no runtime thread, no context is stored and no
//! `std::sync` guard is ever held across an `.await`.
//! `HidApi::new_without_enumerate` is never used: it sets a process-wide
//! flag and panics after an enumerating context exists.
//!
//! Coverage: this file is excluded from the measurement under ADR-0014.
//! Every function is verified by inspection (UT-DISC-011), the
//! classification it feeds by IT-032, and the whole by the system tests on
//! the supply (ST-001 to ST-003).

use std::collections::BTreeSet;
use std::ffi::{CStr, CString};

use hidapi::HidApi;
use tokio::runtime::Handle;

use crate::discovery::{classify, hid_owner, Found, LOG_TARGET};
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

/// Probes the USB side: whether a `hidapi` context can be built. A failure
/// is logged at WARN. (ADR-0014: inspection UT-DISC-010, ST-003.)
pub(crate) async fn available() -> bool {
    let probe = hid_owner::run(|| HidApi::new().map(drop).map_err(transport_error)).await;
    match probe {
        Ok(()) => true,
        Err(error) => {
            log::warn!(target: LOG_TARGET, "no USB HID backend: {error}");
            false
        }
    }
}

/// Enumerates the HID devices with a fresh context on the owner thread,
/// de-duplicated by path text, first entry kept. (ADR-0014: inspection
/// UT-DISC-011, ST-003.)
///
/// # Errors
///
/// [`Error::Transport`] when the context cannot be built or the owner
/// thread does not answer.
pub(crate) async fn enumerate() -> Result<Vec<Enumerated>, Error> {
    hid_owner::run(|| {
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
/// through `Guarded::open_hid`, with a fresh context, on the owner thread.
/// The owner thread belongs to no runtime, so the work enters the caller's
/// runtime, which the transport's reader needs. (ADR-0014: inspection
/// UT-DISC-011, ST-003.)
///
/// # Errors
///
/// [`Error::Transport`] when no Tokio runtime is current, the context
/// cannot be built, the device cannot be opened, or the owner thread does
/// not answer.
pub(crate) async fn open(path: &CStr) -> Result<Guarded<AnyTransport>, Error> {
    let path = path.to_owned();
    let runtime = Handle::try_current().map_err(|_| Error::Transport {
        message: "no Tokio runtime for the HID reader".to_string(),
    })?;
    hid_owner::run(move || {
        let _entered = runtime.enter();
        let api = HidApi::new().map_err(transport_error)?;
        Guarded::open_hid(&api, &path)
    })
    .await
}
