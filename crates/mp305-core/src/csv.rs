//! Implements: DD-CSV-001, DD-CSV-002
//!
//! The one CSV format for readings (SR-037), written to any `Write` sink
//! the product opens. The app's recording and the Python helper produce
//! byte-identical files because both go through [`header`] and
//! [`format_row`], the whole format; [`Writer`] only moves their output to
//! a sink and flushes after every line. The module opens no files and adds
//! no error type: a failure is the sink's own `io::Error`.
//!
//! One row per reading, fields in header order, separated by `,`, ended by
//! `\n`, UTF-8, `.` as the decimal point and no quoting (no field can hold
//! `,`, `"` or a line break):
//!
//! | Column | Source | Form | Example |
//! |---|---|---|---|
//! | `time_iso` | `wall` | RFC 3339, UTC, milliseconds, truncated | `2026-10-01T10:00:00.250Z` |
//! | `t_s` | `wall` minus the origin, in ms | seconds with three decimals, signed | `12.250`, `-1.000` |
//! | `voltage_V` | `raw.voltage`, 10 mV | `<int>.<two digits>` | `13.00` |
//! | `current_A` | `raw.current`, 1 mA | `<int>.<three digits>` | `1.000` |
//! | `power_W` | `raw.power`, 10 mW | `<int>.<two digits>` | `6.17` |
//! | `set_voltage_V` | `raw.set_voltage`, 10 mV | `<int>.<two digits>` | `13.00` |
//! | `set_current_A` | `raw.set_current`, 1 mA | `<int>.<three digits>` | `1.000` |
//! | `output` | `output_on` | `1` or `0` | `0` |
//! | `mode` | `regulation` | `off`, `cv`, `cc`, `held_above`, `unknown_<n>` | `cv` |
//! | `faults` | `faults` | `Fault` names in bit order joined by `;`, empty when none | `reversed output;over current` |
//!
//! The electrical columns come from the raw integers by integer division
//! and remainder, never through floats, so no rounding artefact can appear;
//! the precisions are the device's resolutions (docs/research/device-model.md,
//! section 8). Both time columns come from one truncated millisecond count.
//!
//! ```
//! use mp305_core::csv::{self, Writer};
//!
//! let writer = Writer::new(Vec::new())?;
//! assert_eq!(writer.rows(), 0);
//! assert_eq!(writer.into_inner(), csv::header().as_bytes());
//! # Ok::<(), std::io::Error>(())
//! ```

use std::io::{self, Write};
use std::time::SystemTime;

use crate::civil;
use crate::protocol::ops::telemetry::RegulationMode;
use crate::session::TimedReading;

/// The header line, with its `\n`.
const HEADER: &str =
    "time_iso,t_s,voltage_V,current_A,power_W,set_voltage_V,set_current_A,output,mode,faults\n";

/// The header line of every CSV file, with its `\n`.
#[must_use]
pub fn header() -> &'static str {
    HEADER
}

/// The row of `reading`, with its `\n`, in the form of the module table.
///
/// `t_s` is the time of `reading.wall` after `origin` in seconds, negative
/// for a reading before it. Both times are first truncated to whole
/// milliseconds since the Unix epoch (0 for a time before the epoch).
#[must_use]
pub fn format_row(reading: &TimedReading, origin: SystemTime) -> String {
    let ms = civil::unix_millis(reading.wall);
    let origin_ms = civil::unix_millis(origin);
    let view = &reading.reading;
    let raw = &view.raw;
    let faults: Vec<String> = view.faults.iter().map(|f| f.to_string()).collect();
    format!(
        "{},{},{},{},{},{},{},{},{},{}\n",
        civil::rfc3339_millis(ms),
        seconds_since(ms, origin_ms),
        hundredths(raw.voltage),
        thousandths(raw.current),
        hundredths(raw.power),
        hundredths(raw.set_voltage),
        thousandths(raw.set_current),
        if view.output_on { "1" } else { "0" },
        mode(view.regulation),
        faults.join(";"),
    )
}

/// The `t_s` column: `ms` minus `origin_ms` in seconds with three decimals,
/// signed, by integer division and remainder of the absolute difference.
/// A zero difference has no sign, so `-0.000` cannot occur.
fn seconds_since(ms: u64, origin_ms: u64) -> String {
    let d = ms.abs_diff(origin_ms);
    let sign = if ms < origin_ms { "-" } else { "" };
    format!("{sign}{}.{:03}", d / 1_000, d % 1_000)
}

/// `raw` in hundredths as `<int>.<two digits>`.
fn hundredths(raw: u16) -> String {
    format!("{}.{:02}", raw / 100, raw % 100)
}

/// `raw` in thousandths as `<int>.<three digits>`.
fn thousandths(raw: u16) -> String {
    format!("{}.{:03}", raw / 1_000, raw % 1_000)
}

/// The `mode` column's spelling of `regulation`.
fn mode(regulation: RegulationMode) -> String {
    match regulation {
        RegulationMode::Off => "off".to_owned(),
        RegulationMode::Cv => "cv".to_owned(),
        RegulationMode::Cc => "cc".to_owned(),
        RegulationMode::HeldAboveSetpoint => "held_above".to_owned(),
        RegulationMode::Unknown(n) => format!("unknown_{n}"),
    }
}

/// Writes the header and then one row per reading to a sink, flushing after
/// each line.
///
/// The origin of `t_s` is the one given to [`Writer::with_origin`], or the
/// `wall` of the first reading written.
#[derive(Debug)]
pub struct Writer<W: Write> {
    /// Where the lines go.
    sink: W,
    /// The `t_s` origin; `None` until the first `write` when none was given.
    origin: Option<SystemTime>,
    /// Rows whose `write_all` succeeded, saturating at `u64::MAX`.
    rows: u64,
}

impl<W: Write> Writer<W> {
    /// Writes the header to `sink` and flushes it; the `t_s` origin is set
    /// by the first reading written.
    ///
    /// # Errors
    ///
    /// The sink's `io::Error` from writing or flushing the header,
    /// unchanged.
    pub fn new(sink: W) -> io::Result<Self> {
        Self::start(sink, None)
    }

    /// Writes the header to `sink` and flushes it, with `origin` fixed in
    /// advance as the `t_s` origin.
    ///
    /// When the user starts a recording, the app passes the `wall` of the
    /// latest reading, not `SystemTime::now()`: `wall` is derived from the
    /// session's instant origin (DD-SESS-004), and a clock step between the
    /// two would shift every `t_s`.
    ///
    /// # Errors
    ///
    /// The sink's `io::Error` from writing or flushing the header,
    /// unchanged.
    pub fn with_origin(sink: W, origin: SystemTime) -> io::Result<Self> {
        Self::start(sink, Some(origin))
    }

    /// Writes the header to `sink`, flushes it, and keeps `origin`.
    fn start(mut sink: W, origin: Option<SystemTime>) -> io::Result<Self> {
        sink.write_all(HEADER.as_bytes())?;
        sink.flush()?;
        Ok(Self {
            sink,
            origin,
            rows: 0,
        })
    }

    /// Writes the row of `reading` with one `write_all`, so that a failed
    /// write cannot split a row across two attempts, then flushes. The
    /// first call without a fixed origin makes `reading.wall` the origin.
    ///
    /// # Errors
    ///
    /// The sink's `io::Error` from the write or the flush, unchanged. A row
    /// counts in [`Writer::rows`] once its `write_all` succeeded, even if
    /// the flush then fails. After an error the writer stays usable, and a
    /// partial line may remain in the sink; the product recovers by
    /// starting a new file.
    pub fn write(&mut self, reading: &TimedReading) -> io::Result<()> {
        let origin = *self.origin.get_or_insert(reading.wall);
        let row = format_row(reading, origin);
        self.sink.write_all(row.as_bytes())?;
        self.rows = self.rows.saturating_add(1);
        self.sink.flush()
    }

    /// The number of rows written, the header not included.
    #[must_use]
    pub fn rows(&self) -> u64 {
        self.rows
    }

    /// The sink, giving up the writer.
    pub fn into_inner(self) -> W {
        self.sink
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use core::time::Duration;
    use std::cell::RefCell;
    use std::rc::Rc;
    use std::time::UNIX_EPOCH;

    use tokio::time::Instant;

    use crate::protocol::fixtures::{c3_with, C3_CAPTURE};
    use crate::protocol::frame::Frame;
    use crate::protocol::ops::telemetry::{self, RawReading, Reading};

    /// 2026-10-01T10:00:00Z in milliseconds since the Unix epoch.
    const TEN_MS: u64 = 1_790_848_800_000;

    /// The wall-clock time `ms` milliseconds after the Unix epoch.
    fn wall_ms(ms: u64) -> SystemTime {
        UNIX_EPOCH + Duration::from_millis(ms)
    }

    /// The raw reading of a `0xC3` payload.
    fn raw_of(payload: Vec<u8>) -> RawReading {
        telemetry::parse(&Frame::new(telemetry::REPLY, payload).unwrap()).unwrap()
    }

    /// The capture reading (`C3_CAPTURE`) as a raw reading.
    fn capture() -> RawReading {
        raw_of(C3_CAPTURE.to_vec())
    }

    /// `raw` as a timed reading at `wall`.
    fn timed(raw: &RawReading, wall: SystemTime) -> TimedReading {
        TimedReading {
            at: Instant::now(),
            wall,
            reading: Reading::from_raw(raw),
        }
    }

    /// What a [`CountingSink`] received and what it is told to do next.
    #[derive(Debug, Default)]
    struct SinkState {
        /// Every byte accepted by `write`.
        bytes: Vec<u8>,
        /// How often `flush` was called, failing calls included.
        flushes: usize,
        /// Fail the next `write` with "disk full".
        fail_write: bool,
        /// Fail the next `flush` with "flush failed".
        fail_flush: bool,
    }

    /// A `Write` over a `Vec<u8>` that counts `flush` calls and can be told
    /// to fail its next `write` or its next `flush`. Clones share one
    /// state, so a test keeps a handle while the writer owns the sink.
    #[derive(Clone, Debug, Default)]
    struct CountingSink(Rc<RefCell<SinkState>>);

    impl CountingSink {
        /// The bytes received so far, as text.
        fn text(&self) -> String {
            String::from_utf8(self.0.borrow().bytes.clone()).unwrap()
        }

        /// The number of `flush` calls so far.
        fn flushes(&self) -> usize {
            self.0.borrow().flushes
        }

        /// Makes the next `write` fail.
        fn fail_next_write(&self) {
            self.0.borrow_mut().fail_write = true;
        }

        /// Makes the next `flush` fail.
        fn fail_next_flush(&self) {
            self.0.borrow_mut().fail_flush = true;
        }
    }

    impl Write for CountingSink {
        fn write(&mut self, buf: &[u8]) -> io::Result<usize> {
            let mut state = self.0.borrow_mut();
            if std::mem::take(&mut state.fail_write) {
                return Err(io::Error::other("disk full"));
            }
            state.bytes.extend_from_slice(buf);
            Ok(buf.len())
        }

        fn flush(&mut self) -> io::Result<()> {
            let mut state = self.0.borrow_mut();
            state.flushes += 1;
            if std::mem::take(&mut state.fail_flush) {
                return Err(io::Error::other("flush failed"));
            }
            Ok(())
        }
    }

    /// Test: UT-CSV-001
    #[test]
    fn new_writes_the_header_and_flushes_once() {
        assert_eq!(
            header(),
            "time_iso,t_s,voltage_V,current_A,power_W,set_voltage_V,set_current_A,output,mode,faults\n"
        );
        let sink = CountingSink::default();
        let writer = Writer::new(sink.clone()).unwrap();
        assert_eq!(sink.text(), header());
        assert_eq!(sink.flushes(), 1);
        assert_eq!(writer.rows(), 0);
        let inner = writer.into_inner();
        assert!(Rc::ptr_eq(&inner.0, &sink.0));
    }

    /// Test: UT-CSV-002
    #[test]
    fn rows_of_the_capture_and_of_a_faulted_capture() {
        let sink = CountingSink::default();
        let mut writer = Writer::new(sink.clone()).unwrap();
        writer
            .write(&timed(&capture(), wall_ms(TEN_MS + 250)))
            .unwrap();
        let faulted = raw_of(c3_with(0, 0, 0b10_0001, 1300, 1000));
        writer
            .write(&timed(&faulted, wall_ms(TEN_MS + 500)))
            .unwrap();
        assert_eq!(
            sink.text(),
            format!(
                "{}{}{}",
                header(),
                "2026-10-01T10:00:00.250Z,0.000,0.00,0.000,0.00,13.00,1.000,0,off,\n",
                "2026-10-01T10:00:00.500Z,0.250,0.00,0.000,0.00,13.00,1.000,0,off,\
                 reversed output;over current\n"
            )
        );
        assert_eq!(sink.flushes(), 3);
        assert_eq!(writer.rows(), 2);
    }

    /// The rows after the header in `text`, each split into its fields.
    fn rows_of(text: &str) -> Vec<Vec<String>> {
        let body = text.strip_prefix(header()).unwrap();
        body.lines()
            .map(|line| line.split(',').map(str::to_owned).collect())
            .collect()
    }

    /// Test: UT-CSV-003
    #[test]
    fn a_fixed_origin_signs_t_s_and_mode_and_output_follow_the_reading() {
        let sink = CountingSink::default();
        let mut writer = Writer::with_origin(sink.clone(), wall_ms(TEN_MS)).unwrap();
        let mut cc_on = capture();
        cc_on.output = 1;
        cc_on.out_state = 2;
        let mut unknown = capture();
        unknown.out_state = 7;
        let half_ms = UNIX_EPOCH + Duration::new(1_790_848_800, 250_500_000);
        let mut cv = capture();
        cv.out_state = 1;
        let mut held_above = capture();
        held_above.out_state = 3;
        for reading in [
            timed(&capture(), wall_ms(TEN_MS + 12_250)),
            timed(&capture(), wall_ms(TEN_MS - 1_000)),
            timed(&cc_on, wall_ms(TEN_MS + 1_000)),
            timed(&unknown, wall_ms(TEN_MS + 2_000)),
            timed(&capture(), half_ms),
            timed(&cv, wall_ms(TEN_MS + 3_000)),
            timed(&held_above, wall_ms(TEN_MS + 4_000)),
        ] {
            writer.write(&reading).unwrap();
        }
        assert_eq!(writer.rows(), 7);
        let rows = rows_of(&sink.text());
        assert_eq!(rows.len(), 7);
        assert_eq!(rows[0][0], "2026-10-01T10:00:12.250Z");
        assert_eq!(rows[0][1], "12.250");
        assert_eq!(rows[1][0], "2026-10-01T09:59:59.000Z");
        assert_eq!(rows[1][1], "-1.000");
        assert_eq!((rows[2][7].as_str(), rows[2][8].as_str()), ("1", "cc"));
        assert_eq!(
            (rows[3][7].as_str(), rows[3][8].as_str()),
            ("0", "unknown_7")
        );
        assert!(rows[4][0].ends_with(".250Z"), "{}", rows[4][0]);
        assert_eq!(rows[4][1], "0.250");
        assert_eq!(rows[5][8], "cv");
        assert_eq!(rows[6][8], "held_above");
    }

    /// The `voltage_V,current_A,power_W` columns of the row of `raw`.
    fn measured(raw: &RawReading) -> String {
        let wall = wall_ms(TEN_MS);
        let row = format_row(&timed(raw, wall), wall);
        let fields: Vec<&str> = row.trim_end_matches('\n').split(',').collect();
        fields[2..5].join(",")
    }

    /// Test: UT-CSV-004
    #[test]
    fn measured_columns_come_from_the_raw_integers() {
        let mut small = capture();
        small.voltage = 1234;
        small.current = 5;
        small.power = 617;
        assert_eq!(measured(&small), "12.34,0.005,6.17");
        let mut full = capture();
        full.voltage = 65_535;
        full.current = 65_535;
        full.power = 65_535;
        assert_eq!(measured(&full), "655.35,65.535,655.35");
    }

    /// Test: UT-CSV-006
    #[test]
    fn a_failed_write_counts_no_row_and_a_failed_flush_counts_it() {
        let sink = CountingSink::default();
        let mut writer = Writer::new(sink.clone()).unwrap();
        let reading = timed(&capture(), wall_ms(TEN_MS));

        sink.fail_next_write();
        let err = writer.write(&reading).unwrap_err();
        assert_eq!(err.kind(), io::ErrorKind::Other);
        assert_eq!(err.to_string(), "disk full");
        assert_eq!(writer.rows(), 0);
        assert_eq!(sink.text(), header());

        writer.write(&reading).unwrap();
        assert_eq!(writer.rows(), 1);

        sink.fail_next_flush();
        let err = writer.write(&reading).unwrap_err();
        assert_eq!(err.to_string(), "flush failed");
        assert_eq!(writer.rows(), 2);
        assert_eq!(rows_of(&sink.text()).len(), 2);
    }

    /// Test: UT-CSV-007
    #[test]
    fn every_fault_in_bit_order_joined_by_semicolons() {
        let mut all = capture();
        all.charge_error = 0b1_0001_1111_1111;
        let wall = wall_ms(TEN_MS);
        let row = format_row(&timed(&all, wall), wall);
        let fields: Vec<&str> = row.trim_end_matches('\n').split(',').collect();
        assert_eq!(fields.len(), 10);
        assert_eq!(
            fields[9],
            "reversed output;low battery;battery too cold;battery overheat;system overheat;\
             over current;over voltage;power stage start failure;\
             output voltage sensor failure;unknown fault bit 12"
        );
    }
}
