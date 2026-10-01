//! Implements: nothing; shared test fixtures named in the protocol DD's module tree
//!
//! Payloads from the hardware captures and a builder for `0xC3` variants,
//! shared by the unit tests of the modules above `protocol` and by the
//! integration tests. Compiled for tests and the `mock` feature only. The
//! protocol module's own fixture tests keep their frames inline with their
//! capture citations (protocol DD section 8); the tests below hold this
//! copy equal to theirs.

use crate::protocol::ops::telemetry;

/// The payload of the first `0xC3` of
/// `2026-09-29T193614-ble-readonly.jsonl` (t = 12.8857, AF01): DC mode,
/// output off, no faults, setpoints 1300 and 1000 (13.00 V and 1.000 A).
pub const C3_CAPTURE: [u8; telemetry::LEN] = [
    0x00, 0x00, 0x5A, 0x00, 0x00, 0x14, 0x05, 0x00, 0x00, 0xE8, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1A, 0x00, 0x00, 0x01,
    0x40, 0x06, 0x00, 0x00,
];

/// The payload of the `0xE1` of `2026-09-29T193614-ble-readonly.jsonl`
/// (t = 12.6162, AF02, 17 bytes on air, the answer to an `0xE0` written on
/// AF02; the same payload arrives on AF01 at t = 17.4292 for an `0xE0`
/// written on AF01): version 1.6.0.40, model `MP305B`, hardware 2.0.2.0.
pub const E1_BLE: [u8; 16] = [
    0x01, 0x06, 0x00, 0x28, 0x4D, 0x50, 0x33, 0x30, 0x35, 0x42, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00,
];

/// The 30-byte USB layout of `0xE1` from protocol.md 4.4, constructed
/// (never captured, TBD-010): model `MP305B`, bootloader bytes 1 to 8,
/// version 1.6.0.51, name `MP305B`.
pub const E1_USB: [u8; 30] = [
    0x4D, 0x50, 0x33, 0x30, 0x35, 0x42, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x01, 0x06, 0x00, 0x33, 0x4D, 0x50, 0x33, 0x30, 0x35, 0x42, 0x00, 0x00, 0x00, 0x00,
];

/// The payload of the `0xC5` of `2026-09-29T193614-ble-readonly.jsonl`
/// (t = 12.7497, AF01): charge limit 90 %, volume 2, screen direction 1,
/// ramp step 500, OCP delay 50.
pub const C5_SETTINGS: [u8; 11] = [
    0x5A, 0x02, 0x00, 0x00, 0x01, 0xF4, 0x01, 0x32, 0x00, 0x00, 0x00,
];

/// Offset of `set_voltage` in the `0xC3` payload.
const SET_VOLTAGE: usize = 5;
/// Offset of `set_current` in the `0xC3` payload.
const SET_CURRENT: usize = 9;
/// Offset of `output` in the `0xC3` payload.
const OUTPUT: usize = 24;
/// Offset of `model` (the live mode) in the `0xC3` payload.
const MODEL: usize = 25;
/// Offset of `chargeError` (the fault bits) in the `0xC3` payload.
const CHARGE_ERROR: usize = 29;

/// Writes `bytes` into `payload` from `offset`; offsets outside the payload
/// are skipped.
fn put(payload: &mut [u8], offset: usize, bytes: &[u8]) {
    for (i, byte) in bytes.iter().enumerate() {
        if let Some(slot) = payload.get_mut(offset.saturating_add(i)) {
            *slot = *byte;
        }
    }
}

/// A variant of [`C3_CAPTURE`] with `output` (offset 24), `model` (25),
/// `chargeError` (29 and 30), `set_voltage` (5 and 6) and `set_current`
/// (9 and 10) replaced, the multi-byte fields little-endian.
#[must_use]
pub fn c3_with(
    output: u8,
    model: u8,
    charge_error: u16,
    set_voltage: u16,
    set_current: u16,
) -> Vec<u8> {
    let mut payload = C3_CAPTURE.to_vec();
    put(&mut payload, OUTPUT, &[output]);
    put(&mut payload, MODEL, &[model]);
    put(&mut payload, CHARGE_ERROR, &charge_error.to_le_bytes());
    put(&mut payload, SET_VOLTAGE, &set_voltage.to_le_bytes());
    put(&mut payload, SET_CURRENT, &set_current.to_le_bytes());
    payload
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::protocol::frame::Frame;
    use crate::protocol::ops::{info, settings};

    /// Test: UT-PROTO-024
    #[test]
    fn the_shared_c3_equals_the_inline_capture_and_c3_with_writes_its_fields() {
        assert_eq!(C3_CAPTURE, telemetry::tests::C3_PAYLOAD);
        let variant = c3_with(1, 2, 0x0120, 1234, 4321);
        let r = telemetry::parse(&Frame::new(0xC3, variant.clone()).unwrap()).unwrap();
        assert_eq!(
            (
                r.output,
                r.model,
                r.charge_error,
                r.set_voltage,
                r.set_current
            ),
            (1, 2, 0x0120, 1234, 4321)
        );
        // Every other byte is the capture's.
        let changed = [5, 6, 9, 10, 24, 25, 29, 30];
        for (i, (a, b)) in variant.iter().zip(C3_CAPTURE.iter()).enumerate() {
            if !changed.contains(&i) {
                assert_eq!(a, b, "offset {i}");
            }
        }
    }

    /// Test: UT-PROTO-022
    #[test]
    fn the_shared_e1_payloads_equal_the_inline_ones() {
        assert_eq!(E1_BLE, info::tests::E1_BLE);
        assert_eq!(E1_USB.to_vec(), info::tests::e1_usb());
    }

    /// Test: UT-PROTO-030
    #[test]
    fn the_shared_c5_equals_the_inline_capture() {
        assert_eq!(C5_SETTINGS, settings::tests::C5_PAYLOAD);
    }
}
