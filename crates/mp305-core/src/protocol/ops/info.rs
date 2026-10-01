//! Device info request `0xE0` and reply `0xE1`, in its Bluetooth and its USB layout.
//!
//! Implements: DD-PROTO-022, DD-PROTO-023.

use core::fmt;

use crate::protocol::error::Reason;
use crate::protocol::frame::Frame;
use crate::protocol::ops::expect_reply;

/// The info request opcode.
pub const REQUEST: u8 = 0xE0;
/// The info reply opcode.
pub const REPLY: u8 = 0xE1;
/// Payload length of the Bluetooth layout.
const BLE_LEN: usize = 16;
/// Payload length of the USB layout.
const USB_LEN: usize = 30;

/// A four-part version `a.b.c.d` as the device reports it.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct Version(pub [u8; 4]);

impl fmt::Display for Version {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let [a, b, c, d] = self.0;
        write!(f, "{a}.{b}.{c}.{d}")
    }
}

/// What `0xE1` tells about the supply.
///
/// | Layout | Bytes | Fields |
/// |---|---|---|
/// | Bluetooth | 16 | version (4), model (8), hardware (4) |
/// | USB | 30 | model (8), bootloader block (8, kept raw), version (4), name (10) |
///
/// See docs/research/protocol.md, section 4.4.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Info {
    /// The model string, `MP305B`.
    pub model: String,
    /// The application version of the main MCU.
    pub version: Version,
    /// The hardware revision; only the Bluetooth layout carries it.
    pub hardware: Option<Version>,
    /// The eight bytes the USB layout reads from the bootloader; never
    /// captured, so kept raw (TBD-010).
    pub bootloader_raw: Option<[u8; 8]>,
    /// The name field of the USB layout.
    pub name: Option<String>,
}

/// The info request: `0xE0` with no payload.
#[must_use]
pub fn request() -> Frame {
    Frame::empty(REQUEST)
}

/// Reads a NUL-padded ASCII field.
fn ascii(bytes: &[u8], field: &'static str) -> Result<String, Reason> {
    let mut out = String::with_capacity(bytes.len());
    for &b in bytes {
        if b == 0 {
            break;
        }
        if !(0x20..=0x7E).contains(&b) {
            return Err(Reason::Value {
                field,
                value: i64::from(b),
            });
        }
        out.push(char::from(b));
    }
    Ok(out)
}

/// Reads a four-byte version at `offset`.
fn version(payload: &[u8], offset: usize) -> Version {
    let mut v = [0u8; 4];
    for (i, b) in v.iter_mut().enumerate() {
        *b = payload.get(offset.saturating_add(i)).copied().unwrap_or(0);
    }
    Version(v)
}

/// Parses a `0xE1` reply in either layout.
///
/// # Errors
///
/// [`Reason::WrongOpcode`], a length error against the nearer layout, or
/// [`Reason::Value`] for a non-ASCII model or name.
pub fn parse(frame: &Frame) -> Result<Info, Reason> {
    let len = frame.payload().len();
    let layout = if len <= BLE_LEN || (len > BLE_LEN && len < (BLE_LEN.saturating_add(USB_LEN)) / 2)
    {
        BLE_LEN
    } else {
        USB_LEN
    };
    let payload = expect_reply(frame, REPLY, layout)?;
    if layout == BLE_LEN {
        Ok(Info {
            model: ascii(payload.get(4..12).unwrap_or(&[]), "model")?,
            version: version(payload, 0),
            hardware: Some(version(payload, 12)),
            bootloader_raw: None,
            name: None,
        })
    } else {
        let mut boot = [0u8; 8];
        boot.copy_from_slice(payload.get(8..16).unwrap_or(&[0; 8]));
        Ok(Info {
            model: ascii(payload.get(0..8).unwrap_or(&[]), "model")?,
            version: version(payload, 16),
            hardware: None,
            bootloader_raw: Some(boot),
            name: Some(ascii(payload.get(20..30).unwrap_or(&[]), "name")?),
        })
    }
}

#[cfg(test)]
pub(crate) mod tests {
    use super::*;
    use crate::protocol::error::Reason;
    use crate::protocol::frame::Frame;

    /// 2026-09-29T193614-ble-readonly.jsonl, the `0xE1` reply on AF02 (17 bytes on air,
    /// t = 12.6162).
    pub(crate) const E1_BLE: [u8; 16] = [
        0x01, 0x06, 0x00, 0x28, 0x4D, 0x50, 0x33, 0x30, 0x35, 0x42, 0x00, 0x00, 0x02, 0x00, 0x02,
        0x00,
    ];

    /// The 30-byte USB layout of protocol.md 4.4, constructed (never captured, TBD-010).
    pub(crate) fn e1_usb() -> Vec<u8> {
        let mut p = b"MP305B\0\0".to_vec();
        p.extend_from_slice(&[1, 2, 3, 4, 5, 6, 7, 8]);
        p.extend_from_slice(&[0x01, 0x06, 0x00, 0x33]);
        p.extend_from_slice(b"MP305B\0\0\0\0");
        p
    }

    /// Test: UT-PROTO-022
    #[test]
    fn request_is_an_empty_e0() {
        let f = request();
        assert_eq!((f.opcode(), f.payload()), (0xE0, &[][..]));
    }

    /// Test: UT-PROTO-022
    #[test]
    fn parse_reads_the_bluetooth_layout() {
        let info = parse(&Frame::new(0xE1, E1_BLE.to_vec()).unwrap()).unwrap();
        assert_eq!(info.version, Version([1, 6, 0, 40]));
        assert_eq!(info.version.to_string(), "1.6.0.40");
        assert_eq!(info.model, "MP305B");
        assert_eq!(info.hardware, Some(Version([2, 0, 2, 0])));
        assert_eq!(info.bootloader_raw, None);
        assert_eq!(info.name, None);
    }

    /// Test: UT-PROTO-022
    #[test]
    fn parse_reads_the_usb_layout() {
        let info = parse(&Frame::new(0xE1, e1_usb()).unwrap()).unwrap();
        assert_eq!(info.model, "MP305B");
        assert_eq!(info.version, Version([1, 6, 0, 51]));
        assert_eq!(info.hardware, None);
        assert_eq!(info.bootloader_raw, Some([1, 2, 3, 4, 5, 6, 7, 8]));
        assert_eq!(info.name.as_deref(), Some("MP305B"));
    }

    /// Test: UT-PROTO-022
    #[test]
    fn parse_rejects_other_lengths_and_non_ascii() {
        let err = |n: usize| parse(&Frame::new(0xE1, vec![0x41; n]).unwrap()).unwrap_err();
        assert_eq!(
            err(15),
            Reason::Short {
                needed: 16,
                got: 15
            }
        );
        assert_eq!(
            err(17),
            Reason::BadLength {
                expected: 16,
                got: 17
            }
        );
        assert_eq!(
            err(29),
            Reason::Short {
                needed: 30,
                got: 29
            }
        );
        let mut bad = E1_BLE;
        bad[4] = 0xFF;
        assert_eq!(
            parse(&Frame::new(0xE1, bad.to_vec()).unwrap()).unwrap_err(),
            Reason::Value {
                field: "model",
                value: 0xFF
            }
        );
        assert_eq!(
            parse(&Frame::new(0xE0, E1_BLE.to_vec()).unwrap()).unwrap_err(),
            Reason::WrongOpcode {
                expected: 0xE1,
                got: 0xE0
            }
        );
    }
}
