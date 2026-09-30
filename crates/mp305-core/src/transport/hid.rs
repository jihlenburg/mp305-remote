//! USB HID through `hidapi`: one thread owns the device, writes arrive as
//! jobs, reads feed the frame decoder. Nothing testable lives here; report
//! packing is in `hid_report` and the framing in `protocol::hid`.
//!
//! Coverage: this file is excluded from the measurement under ADR-0013.
//! Every function is verified by inspection (IT-017, UT-TRANS-021) and by
//! the system tests on the supply (ST-040).
//!
//! Implements: DD-TRANS-020, DD-TRANS-022, DD-TRANS-023, DD-TRANS-026.

use std::ffi::CStr;
use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::mpsc as std_mpsc;
use std::sync::{Arc, Mutex};
use std::thread::JoinHandle;

use hidapi::{HidApi, HidDevice};
use tokio::runtime::Handle;
use tokio::sync::{mpsc, oneshot};
use tokio::time::Instant;

use crate::error::Error;
use crate::protocol::ble::Route;
use crate::protocol::frame::Frame;
use crate::protocol::hid as framing;
use crate::transport::description::{Description, Kind};
use crate::transport::guarded::LOG_TARGET;
use crate::transport::hid_report::{pack_out, unpack_in, REPORT_LEN};
use crate::transport::{RawIncoming, Transport};

/// The read timeout of the I/O thread's loop, in milliseconds.
const READ_TIMEOUT_MS: i32 = 10;

/// One frame's reports, written together, acknowledged when done.
struct Job {
    /// The output reports of one frame, in order.
    reports: Vec<[u8; REPORT_LEN]>,
    /// Where the outcome goes.
    done: oneshot::Sender<Result<(), Error>>,
}

/// A supply over USB HID. The module is crate-private: a `Hid` exists
/// only inside a `Guarded` (DD-TRANS-022).
pub struct Hid {
    /// Kind and HID path.
    description: Description,
    /// Where write jobs go.
    jobs: std_mpsc::Sender<Job>,
    /// Set to end the I/O thread.
    stop: Arc<AtomicBool>,
    /// The I/O thread, joined on close.
    thread: Mutex<Option<JoinHandle<()>>>,
    /// The channel the I/O thread delivers on.
    rx: mpsc::UnboundedReceiver<RawIncoming>,
}

/// Maps a `hidapi` error to the crate error. (ADR-0013: inspection.)
fn transport_error(error: hidapi::HidError) -> Error {
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

/// The I/O thread: drains write jobs, then reads one report, until stopped.
/// (ADR-0013: inspection, IT-017, ST-040.)
fn io_loop(
    device: HidDevice,
    jobs: &std_mpsc::Receiver<Job>,
    tx: &mpsc::UnboundedSender<RawIncoming>,
    stop: &AtomicBool,
    runtime: &Handle,
) {
    let _guard = runtime.enter();
    let mut decoder = framing::Decoder::new();
    let mut buffer = [0u8; REPORT_LEN];
    while !stop.load(Ordering::Relaxed) {
        while let Ok(job) = jobs.try_recv() {
            let mut outcome = Ok(());
            for report in &job.reports {
                log::trace!(target: LOG_TARGET, "wire tx hid {}", hex(report));
                match device.write(report) {
                    Ok(n) if n == report.len() => {}
                    Ok(n) => {
                        outcome = Err(Error::Transport {
                            message: format!("short write: {n} of {}", report.len()),
                        });
                        break;
                    }
                    Err(error) => {
                        outcome = Err(transport_error(error));
                        break;
                    }
                }
            }
            let _ = job.done.send(outcome);
        }
        match device.read_timeout(&mut buffer, READ_TIMEOUT_MS) {
            Ok(0) => continue,
            Ok(n) => {
                let at = Instant::now();
                let report = buffer.get(..n).unwrap_or(&[]);
                log::trace!(target: LOG_TARGET, "wire rx hid {}", hex(report));
                match unpack_in(report) {
                    Ok(stream) => {
                        for item in decoder.push(stream) {
                            if tx
                                .send(RawIncoming {
                                    route: Route::Hid,
                                    at,
                                    item,
                                })
                                .is_err()
                            {
                                return;
                            }
                        }
                    }
                    Err(reason) => {
                        if tx
                            .send(RawIncoming {
                                route: Route::Hid,
                                at,
                                item: Err(reason),
                            })
                            .is_err()
                        {
                            return;
                        }
                    }
                }
            }
            Err(error) => {
                log::warn!(target: LOG_TARGET, "hid read failed: {error}");
                return;
            }
        }
    }
    // Dropping `tx` and the device on return signals the lost link (DD-TRANS-004).
}

impl Hid {
    /// Opens the device at `path` with the given `hidapi` context and starts
    /// the I/O thread. Must be called inside a Tokio runtime. (ADR-0013:
    /// inspection, IT-017.)
    ///
    /// # Errors
    ///
    /// [`Error::Transport`] when the device cannot be opened or no runtime is
    /// current.
    pub(crate) fn open(api: &HidApi, path: &CStr) -> Result<Self, Error> {
        let device = api.open_path(path).map_err(transport_error)?;
        let runtime = Handle::try_current().map_err(|_| Error::Transport {
            message: "no Tokio runtime for the HID reader".to_string(),
        })?;
        let (jobs_tx, jobs_rx) = std_mpsc::channel();
        let (tx, rx) = mpsc::unbounded_channel();
        let stop = Arc::new(AtomicBool::new(false));
        let stop_for_thread = Arc::clone(&stop);
        let thread = std::thread::Builder::new()
            .name("mp305-hid".to_string())
            .spawn(move || io_loop(device, &jobs_rx, &tx, &stop_for_thread, &runtime))
            .map_err(|error| Error::Transport {
                message: error.to_string(),
            })?;
        Ok(Self {
            description: Description {
                kind: Kind::Hid,
                identifier: path.to_string_lossy().into_owned(),
            },
            jobs: jobs_tx,
            stop,
            thread: Mutex::new(Some(thread)),
            rx,
        })
    }

    /// Submits one frame as a single job and awaits its outcome.
    /// (ADR-0013: inspection, ST-040.)
    pub(crate) async fn write_frame(&self, frame: &Frame, route: Route) -> Result<(), Error> {
        if route != Route::Hid {
            return Err(Error::Transport {
                message: "Bluetooth route on a HID link".to_string(),
            });
        }
        let reports = framing::encode(frame)
            .iter()
            .map(|payload| pack_out(payload).map_err(Error::Protocol))
            .collect::<Result<Vec<_>, _>>()?;
        let (done, outcome) = oneshot::channel();
        self.jobs
            .send(Job { reports, done })
            .map_err(|_| Error::Transport {
                message: "HID thread ended".to_string(),
            })?;
        outcome.await.unwrap_or_else(|_| {
            Err(Error::Transport {
                message: "HID thread ended".to_string(),
            })
        })
    }

    /// Stops the I/O thread and joins it off the runtime. (ADR-0013: inspection.)
    pub(crate) async fn shut_down(&self) -> Result<(), Error> {
        self.stop.store(true, Ordering::Relaxed);
        let thread = self.thread.lock().ok().and_then(|mut t| t.take());
        if let Some(thread) = thread {
            let _ = tokio::task::spawn_blocking(move || thread.join()).await;
        }
        Ok(())
    }
}

impl Transport for Hid {
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

impl Drop for Hid {
    /// Asks the I/O thread to stop; it exits within one read timeout.
    /// (ADR-0013: inspection.)
    fn drop(&mut self) {
        self.stop.store(true, Ordering::Relaxed);
    }
}
