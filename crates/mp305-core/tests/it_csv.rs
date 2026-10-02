//! Integration test IT-034 (AR-034): three readings written through `csv`
//! into a `Vec<u8>`, one of them with two faults: the header and rows of
//! SR-037, the faults joined as the format says, a flush after each row.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    missing_docs
)]

use std::io::{self, Write};
use std::time::{Duration, SystemTime, UNIX_EPOCH};

use tokio::time::Instant;

use mp305_core::csv::Writer;
use mp305_core::protocol::ops::telemetry::{self, Reading};
use mp305_core::session::TimedReading;

/// `2026-09-29T193614-ble-readonly.jsonl`, t = 12.8857, RX on AF01: the
/// payload of the first `0xC3` (`C3_CAPTURE`): output off, setpoints 1300
/// and 1000, no fault.
const C3_CAPTURE: [u8; 36] = [
    0x00, 0x00, 0x5A, 0x00, 0x00, 0x14, 0x05, 0x00, 0x00, 0xE8, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1A, 0x00, 0x00, 0x01,
    0x40, 0x06, 0x00, 0x00,
];

/// SR-037's header.
const HEADER: &str =
    "time_iso,t_s,voltage_V,current_A,power_W,set_voltage_V,set_current_A,output,mode,faults\n";

/// A `Vec<u8>` sink that records its length at every flush.
#[derive(Default)]
struct Flushes {
    /// The bytes written.
    bytes: Vec<u8>,
    /// The length of `bytes` at each flush.
    at_flush: Vec<usize>,
}

impl Write for Flushes {
    fn write(&mut self, buf: &[u8]) -> io::Result<usize> {
        self.bytes.write(buf)
    }

    fn flush(&mut self) -> io::Result<()> {
        self.at_flush.push(self.bytes.len());
        Ok(())
    }
}

/// The capture reading with `out_state`, `voltage`, `current`, `power`,
/// `output` and `chargeError` set, at `wall`.
fn reading(
    wall: SystemTime,
    out_state: u8,
    voltage: u16,
    current: u16,
    power: u16,
    output: u8,
    charge_error: u16,
) -> TimedReading {
    let mut p = C3_CAPTURE;
    p[0] = out_state;
    p[3..5].copy_from_slice(&voltage.to_le_bytes());
    p[7..9].copy_from_slice(&current.to_le_bytes());
    p[19..21].copy_from_slice(&power.to_le_bytes());
    p[24] = output;
    p[29..31].copy_from_slice(&charge_error.to_le_bytes());
    TimedReading {
        at: Instant::now(),
        wall,
        reading: Reading::from_raw(&telemetry::parse_payload(&p).unwrap()),
    }
}

/// Test: IT-034
#[tokio::test(start_paused = true)]
async fn three_readings_are_written_in_the_sr_037_format_and_flushed_per_row() {
    let t0 = UNIX_EPOCH + Duration::from_secs(1_790_848_800);
    let rows = [
        reading(t0, 0, 0, 0, 0, 0, 0),
        reading(t0 + Duration::from_millis(250), 1, 1300, 475, 617, 1, 0),
        // Reversed output (bit 0) and over current (bit 5).
        reading(
            t0 + Duration::from_millis(12_250),
            2,
            1299,
            1000,
            1299,
            1,
            0b10_0001,
        ),
    ];
    let expected = [
        HEADER,
        "2026-10-01T10:00:00.000Z,0.000,0.00,0.000,0.00,13.00,1.000,0,off,\n",
        "2026-10-01T10:00:00.250Z,0.250,13.00,0.475,6.17,13.00,1.000,1,cv,\n",
        "2026-10-01T10:00:12.250Z,12.250,12.99,1.000,12.99,13.00,1.000,1,cc,reversed output;over current\n",
    ]
    .concat();

    // Into a plain Vec<u8>.
    let mut writer = Writer::new(Vec::new()).unwrap();
    for r in &rows {
        writer.write(r).unwrap();
    }
    assert_eq!(writer.rows(), 3);
    let bytes = writer.into_inner();
    assert_eq!(String::from_utf8(bytes).unwrap(), expected);

    // The same through a Vec<u8> that notes its flushes: one after the
    // header and one after each row, each at a line end.
    let mut writer = Writer::new(Flushes::default()).unwrap();
    for r in &rows {
        writer.write(r).unwrap();
    }
    let sink = writer.into_inner();
    assert_eq!(sink.bytes, expected.as_bytes());
    let line_ends: Vec<usize> = expected
        .bytes()
        .enumerate()
        .filter(|(_, b)| *b == b'\n')
        .map(|(i, _)| i + 1)
        .collect();
    assert_eq!(sink.at_flush, line_ends);
}
