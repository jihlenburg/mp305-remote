//! Packing and unpacking of the USB HID reports, without a device.
//!
//! Implements: DD-TRANS-021.

use crate::protocol::error::Reason;
use crate::protocol::hid::REPORT_PAYLOAD;

/// The output report ID, host to device.
pub const OUT_ID: u8 = 0x01;
/// The input report ID, device to host.
pub const IN_ID: u8 = 0x02;
/// The buffer `hidapi` reads and writes: the report ID plus 64 bytes.
pub const REPORT_LEN: usize = 65;

/// The output report carrying `payload` (1 to 62 stream bytes): the report
/// ID, the count, the bytes, zero padding.
///
/// # Errors
///
/// [`Reason::BadLength`] for an empty payload or one above 62 bytes.
pub fn pack_out(payload: &[u8]) -> Result<[u8; REPORT_LEN], Reason> {
    if payload.is_empty() {
        return Err(Reason::BadLength {
            expected: 1,
            got: 0,
        });
    }
    if payload.len() > REPORT_PAYLOAD {
        return Err(Reason::BadLength {
            expected: REPORT_PAYLOAD,
            got: payload.len(),
        });
    }
    let mut report = [0u8; REPORT_LEN];
    report[0] = OUT_ID;
    // The length is at most 62, so it fits a byte.
    report[1] = u8::try_from(payload.len()).unwrap_or(u8::MAX);
    if let Some(slot) = report.get_mut(2..2usize.saturating_add(payload.len())) {
        slot.copy_from_slice(payload);
    }
    Ok(report)
}

/// The stream bytes of an input report: the buffer must start with the
/// input report ID, then the count, then that many bytes.
///
/// # Errors
///
/// [`Reason::BadPrefix`] when the buffer does not start with the input
/// report ID; [`Reason::BadLength`] when the count is above 62 or beyond the
/// buffer.
pub fn unpack_in(report: &[u8]) -> Result<&[u8], Reason> {
    if report.first() != Some(&IN_ID) {
        return Err(Reason::BadPrefix);
    }
    let count = usize::from(report.get(1).copied().unwrap_or(0));
    if count > REPORT_PAYLOAD {
        return Err(Reason::BadLength {
            expected: REPORT_PAYLOAD,
            got: count,
        });
    }
    let available = report.len().saturating_sub(2);
    report
        .get(2..2usize.saturating_add(count))
        .ok_or(Reason::BadLength {
            expected: count,
            got: available,
        })
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::protocol::error::Reason;

    /// Test: UT-TRANS-020
    #[test]
    fn pack_out_puts_the_report_id_and_the_count_first() {
        let report = pack_out(&[0xAA, 0x12, 0x01, 0xC4, 0xD7]).unwrap();
        assert_eq!(report.len(), 65);
        assert_eq!(&report[..7], &[0x01, 5, 0xAA, 0x12, 0x01, 0xC4, 0xD7]);
        assert!(report[7..].iter().all(|b| *b == 0));
        let full = pack_out(&[7; 62]).unwrap();
        assert_eq!(&full[..2], &[0x01, 62]);
        assert_eq!(&full[2..64], &[7; 62]);
        assert_eq!(full[64], 0);
    }

    /// Test: UT-TRANS-020
    #[test]
    fn pack_out_rejects_empty_and_oversized_payloads() {
        assert_eq!(
            pack_out(&[]).unwrap_err(),
            Reason::BadLength {
                expected: 1,
                got: 0
            }
        );
        assert_eq!(
            pack_out(&[0; 63]).unwrap_err(),
            Reason::BadLength {
                expected: 62,
                got: 63
            }
        );
    }

    /// Test: UT-TRANS-020
    #[test]
    fn unpack_in_returns_the_counted_stream_bytes() {
        assert_eq!(
            unpack_in(&[0x02, 0x03, 0xAA, 0x21, 0x01, 0, 0]).unwrap(),
            &[0xAA, 0x21, 0x01]
        );
        assert_eq!(
            unpack_in(&[0x03, 0x03, 0xAA, 0x21, 0x01]).unwrap_err(),
            Reason::BadPrefix
        );
        assert_eq!(unpack_in(&[0x02, 0, 0]).unwrap(), &[]);
        let mut big = vec![0x02, 63];
        big.extend([0u8; 64]);
        assert_eq!(
            unpack_in(&big).unwrap_err(),
            Reason::BadLength {
                expected: 62,
                got: 63
            }
        );
        assert_eq!(
            unpack_in(&[0x02, 5, 1, 2]).unwrap_err(),
            Reason::BadLength {
                expected: 5,
                got: 2
            }
        );
        assert_eq!(unpack_in(&[]).unwrap_err(), Reason::BadPrefix);
    }
}
