//! Implements: DD-APP-004.
//!
//! The recorder: a thread named `mp305-recorder` that writes the readings
//! to a CSV file through the core's one format (`csv::Writer`, SR-037).
//! Every file call runs on this thread, out of the loop that hands over
//! Output OFF (SR-041) and out of Tokio's blocking pool, for which a
//! runtime shutdown would wait. Rows reach it on a bounded queue of 256
//! readings, so a stuck disk cannot grow memory; an overflow ends the
//! recording and is reported, not hidden.

use std::fs::{File, OpenOptions};
use std::io::{self, BufWriter, Write};
use std::path::{Path, PathBuf};
use std::sync::mpsc::{sync_channel, Receiver, SyncSender, TrySendError};
use std::time::SystemTime;

use mp305_core::csv;
use tokio::sync::mpsc::UnboundedSender;

use crate::model::TimedReading;
use crate::texts;
use crate::worker::RecordingEvent;

/// The length of the queue to the thread, in readings.
pub const QUEUE: usize = 256;

/// The thread's name.
const THREAD_NAME: &str = "mp305-recorder";

/// A `Progress` report goes out after every this many rows.
const PROGRESS_EVERY: u64 = 4;

/// The log target of the recorder.
pub const LOG_TARGET: &str = "mp305_app::recording";

/// A report of the recorder thread.
#[derive(Clone, Debug, PartialEq, Eq)]
pub enum RecorderReport {
    /// The file is open and its header written.
    Opened,
    /// Rows written so far, after every 4th row.
    Progress {
        /// The row count.
        rows: u64,
    },
    /// The thread ended: the queue was closed and empty, or a write failed.
    Ended {
        /// The rows written.
        rows: u64,
        /// The error, if one ended it.
        error: Option<String>,
    },
}

/// The handle of a recording.
#[derive(Debug)]
pub struct Recorder {
    /// The file.
    path: PathBuf,
    /// The queue to the thread; `None` once stopped or overflowed.
    sender: Option<SyncSender<TimedReading>>,
    /// Whether a reading found the queue full.
    overflowed: bool,
}

/// Opens a new file for a recording: `write` and `create_new`, so an
/// existing file is never overwritten, inside a `BufWriter`.
///
/// # Errors
///
/// The OS error; `AlreadyExists` for an existing file.
pub fn open_file(path: &Path) -> io::Result<BufWriter<File>> {
    OpenOptions::new()
        .write(true)
        .create_new(true)
        .open(path)
        .map(BufWriter::new)
}

impl Recorder {
    /// Spawns the thread, which calls `open(&path)`, writes the header with
    /// `origin` as the `t_s` origin, and then one row per reading; returns
    /// at once. A thread that cannot be spawned is reported as `Ended` with
    /// its error.
    pub fn start<F, W>(
        path: PathBuf,
        open: F,
        origin: SystemTime,
        reports: UnboundedSender<RecorderReport>,
    ) -> Recorder
    where
        F: FnOnce(&Path) -> io::Result<W> + Send + 'static,
        W: Write + Send + 'static,
    {
        let (sender, queue) = sync_channel(QUEUE);
        let thread_path = path.clone();
        let thread_reports = reports.clone();
        let spawned = std::thread::Builder::new()
            .name(THREAD_NAME.to_string())
            .spawn(move || record(open(&thread_path), origin, queue, &thread_reports));
        let sender = match spawned {
            Ok(_) => Some(sender),
            Err(e) => {
                let _ = reports.send(RecorderReport::Ended {
                    rows: 0,
                    error: Some(e.to_string()),
                });
                None
            }
        };
        Recorder {
            path,
            sender,
            overflowed: false,
        }
    }

    /// Queues `reading` without waiting: a full queue ends the recording
    /// (the sender is dropped and the overflow remembered), a closed one
    /// (the thread ended) is ignored.
    pub fn push(&mut self, reading: &TimedReading) {
        let Some(sender) = &self.sender else {
            return;
        };
        match sender.try_send(*reading) {
            Ok(()) | Err(TrySendError::Disconnected(_)) => {}
            Err(TrySendError::Full(_)) => {
                log::warn!(target: LOG_TARGET, "{}", texts::ROWS_DROPPED);
                self.sender = None;
                self.overflowed = true;
            }
        }
    }

    /// Closes the queue; the thread writes what it holds and ends.
    pub fn stop(&mut self) {
        self.sender = None;
    }

    /// The file.
    #[must_use]
    pub fn path(&self) -> &Path {
        &self.path
    }

    /// The event of the ended recording, with the thread's row count and
    /// error; after an overflow the error is [`texts::ROWS_DROPPED`].
    #[must_use]
    pub fn finish(self, rows: u64, error: Option<String>) -> RecordingEvent {
        let error = if self.overflowed {
            Some(texts::ROWS_DROPPED.to_string())
        } else {
            error
        };
        RecordingEvent::Off {
            path: self.path,
            rows,
            error,
        }
    }
}

/// The thread's body: the header through `csv::Writer::with_origin`, one
/// row and one flush per reading, `Progress` after every 4th row, and
/// `Ended` when the queue is closed and empty or at the first error, after
/// which nothing more is written.
fn record<W: Write>(
    sink: io::Result<W>,
    origin: SystemTime,
    queue: Receiver<TimedReading>,
    reports: &UnboundedSender<RecorderReport>,
) {
    let ended = |rows: u64, error: Option<String>| {
        let _ = reports.send(RecorderReport::Ended { rows, error });
    };
    let sink = match sink {
        Ok(sink) => sink,
        Err(e) => return ended(0, Some(e.to_string())),
    };
    let mut writer = match csv::Writer::with_origin(sink, origin) {
        Ok(writer) => writer,
        Err(e) => return ended(0, Some(e.to_string())),
    };
    let _ = reports.send(RecorderReport::Opened);
    let mut error = None;
    while let Ok(reading) = queue.recv() {
        if let Err(e) = writer.write(&reading) {
            error = Some(e.to_string());
            break;
        }
        let rows = writer.rows();
        if rows % PROGRESS_EVERY == 0 {
            let _ = reports.send(RecorderReport::Progress { rows });
        }
    }
    drop(queue);
    ended(writer.rows(), error);
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::testkit::{r_wall, wall0};
    use core::time::Duration;
    use std::sync::{Arc, Condvar, Mutex};
    use tokio::sync::mpsc::{unbounded_channel, UnboundedReceiver};

    /// A sink over a shared buffer.
    #[derive(Clone, Default)]
    struct Shared(Arc<Mutex<Vec<u8>>>);

    impl Write for Shared {
        fn write(&mut self, buf: &[u8]) -> io::Result<usize> {
            self.0.lock().unwrap().extend_from_slice(buf);
            Ok(buf.len())
        }
        fn flush(&mut self) -> io::Result<()> {
            Ok(())
        }
    }

    /// A sink whose `write` fails from its `fail_from`th call on.
    struct Failing {
        /// Calls so far.
        calls: usize,
        /// The first call that fails.
        fail_from: usize,
    }

    impl Write for Failing {
        fn write(&mut self, buf: &[u8]) -> io::Result<usize> {
            self.calls += 1;
            if self.calls >= self.fail_from {
                Err(io::Error::other("disk full"))
            } else {
                Ok(buf.len())
            }
        }
        fn flush(&mut self) -> io::Result<()> {
            Ok(())
        }
    }

    /// A gate a sink blocks on: (blocked, open).
    type Gate = Arc<(Mutex<(bool, bool)>, Condvar)>;

    /// A sink whose second `write` blocks until the gate opens.
    struct Gated {
        /// Calls so far.
        calls: usize,
        /// The gate.
        gate: Gate,
    }

    impl Write for Gated {
        fn write(&mut self, buf: &[u8]) -> io::Result<usize> {
            self.calls += 1;
            if self.calls == 2 {
                let (lock, cv) = &*self.gate;
                let mut state = lock.lock().unwrap();
                state.0 = true;
                cv.notify_all();
                while !state.1 {
                    state = cv.wait(state).unwrap();
                }
            }
            Ok(buf.len())
        }
        fn flush(&mut self) -> io::Result<()> {
            Ok(())
        }
    }

    /// Every report until `Ended`, waiting for each.
    fn reports_until_ended(rx: &mut UnboundedReceiver<RecorderReport>) -> Vec<RecorderReport> {
        let mut out = Vec::new();
        while let Some(report) = rx.blocking_recv() {
            let ended = matches!(report, RecorderReport::Ended { .. });
            out.push(report);
            if ended {
                break;
            }
        }
        out
    }

    /// The reading `k` times 230 ms after W0.
    fn reading(k: u32) -> TimedReading {
        r_wall(wall0() + Duration::from_millis(230) * k)
    }

    /// Test: UT-APP-016
    #[test]
    fn rows_reach_the_sink_with_progress_reports() {
        let shared = Shared::default();
        let sink = shared.clone();
        let (tx, mut rx) = unbounded_channel();
        let mut recorder = Recorder::start(PathBuf::from("a.csv"), move |_| Ok(sink), wall0(), tx);
        let readings: Vec<TimedReading> = (1..=5).map(reading).collect();
        for r in &readings {
            recorder.push(r);
        }
        recorder.stop();
        assert_eq!(
            reports_until_ended(&mut rx),
            vec![
                RecorderReport::Opened,
                RecorderReport::Progress { rows: 4 },
                RecorderReport::Ended {
                    rows: 5,
                    error: None
                },
            ]
        );
        let text = String::from_utf8(shared.0.lock().unwrap().clone()).unwrap();
        let mut expected = csv::header().to_string();
        for r in &readings {
            expected.push_str(&csv::format_row(r, wall0()));
        }
        assert_eq!(text, expected);
        let t_s: Vec<&str> = text
            .lines()
            .skip(1)
            .map(|l| l.split(',').nth(1).unwrap())
            .collect();
        assert_eq!(t_s, vec!["0.230", "0.460", "0.690", "0.920", "1.150"]);
    }

    /// Test: UT-APP-016
    #[test]
    fn a_write_error_ends_the_recording_with_the_rows_written() {
        let (tx, mut rx) = unbounded_channel();
        let mut recorder = Recorder::start(
            PathBuf::from("b.csv"),
            |_| {
                Ok(Failing {
                    calls: 0,
                    fail_from: 4,
                })
            },
            wall0(),
            tx,
        );
        for k in 1..=5 {
            recorder.push(&reading(k));
        }
        let reports = reports_until_ended(&mut rx);
        assert_eq!(
            reports.last(),
            Some(&RecorderReport::Ended {
                rows: 2,
                error: Some("disk full".to_string())
            })
        );
        assert_eq!(
            recorder.finish(2, Some("disk full".to_string())),
            RecordingEvent::Off {
                path: PathBuf::from("b.csv"),
                rows: 2,
                error: Some("disk full".to_string())
            }
        );
    }

    /// Test: UT-APP-016
    #[test]
    fn a_file_that_does_not_open_ends_without_opened() {
        let (tx, mut rx) = unbounded_channel();
        let _recorder = Recorder::start(
            PathBuf::from("c.csv"),
            |_| -> io::Result<Shared> {
                Err(io::Error::new(io::ErrorKind::NotFound, "no such directory"))
            },
            wall0(),
            tx,
        );
        assert_eq!(
            reports_until_ended(&mut rx),
            vec![RecorderReport::Ended {
                rows: 0,
                error: Some("no such directory".to_string())
            }]
        );
    }

    /// Test: UT-APP-016
    #[test]
    fn a_full_queue_overflows_and_is_reported() {
        let gate: Gate = Arc::new((Mutex::new((false, false)), Condvar::new()));
        let sink_gate = Arc::clone(&gate);
        let (tx, mut rx) = unbounded_channel();
        let mut recorder = Recorder::start(
            PathBuf::from("d.csv"),
            move |_| {
                Ok(Gated {
                    calls: 0,
                    gate: sink_gate,
                })
            },
            wall0(),
            tx,
        );
        recorder.push(&reading(1));
        {
            let (lock, cv) = &*gate;
            let state = lock.lock().unwrap();
            let (state, waited) = cv
                .wait_timeout_while(state, Duration::from_secs(5), |s| !s.0)
                .unwrap();
            assert!(state.0 && !waited.timed_out(), "the sink never blocked");
        }
        for k in 2..=257 {
            recorder.push(&reading(k));
            assert!(!recorder.overflowed, "push {k}");
        }
        recorder.push(&reading(258));
        assert!(recorder.overflowed);
        {
            let (lock, cv) = &*gate;
            lock.lock().unwrap().1 = true;
            cv.notify_all();
        }
        recorder.stop();
        let reports = reports_until_ended(&mut rx);
        assert_eq!(
            reports.last(),
            Some(&RecorderReport::Ended {
                rows: 257,
                error: None
            })
        );
        assert_eq!(
            recorder.finish(257, None),
            RecordingEvent::Off {
                path: PathBuf::from("d.csv"),
                rows: 257,
                error: Some("rows were dropped: the file is not keeping up".to_string())
            }
        );
    }

    /// Test: UT-APP-016
    #[test]
    fn open_file_never_overwrites() {
        let dir = tempfile::tempdir().unwrap();
        let path = dir.path().join("x.csv");
        std::fs::write(&path, b"keep").unwrap();
        let error = open_file(&path).err().unwrap();
        assert_eq!(error.kind(), io::ErrorKind::AlreadyExists);
        assert_eq!(std::fs::read(&path).unwrap(), b"keep");
    }
}
