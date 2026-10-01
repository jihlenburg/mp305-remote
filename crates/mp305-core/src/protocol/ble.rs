//! The Bluetooth LE wire forms: the AF01 form with its placeholder and route
//! tag, and the bare AF02 form.
//!
//! Implements: DD-PROTO-002.

use crate::protocol::error::Reason;
use crate::protocol::frame::Frame;

/// The placeholder the bridge discards from every AF01 write.
const AF01_PLACEHOLDER: u8 = 0x12;
/// The route tag the bridge prepends to every AF01 notification.
pub(crate) const AF01_TAG: u8 = 0x31;

/// The two characteristics of the `AF00` service.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum BleRoute {
    /// Commands and replies: `0x12, opcode, payload` out, `0x31, opcode, payload` in.
    Af01,
    /// Bind and its reply: `opcode, payload` both ways.
    Af02,
}

/// Where a frame goes or came from, as the transport layer sees it.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Route {
    /// One of the two Bluetooth characteristics.
    Ble(BleRoute),
    /// The USB HID report path.
    Hid,
}

/// The bytes to write for `frame` on the given characteristic.
///
/// On AF01 the bridge discards the first byte unread, so a placeholder
/// (`0x12`) precedes the opcode (device-model.md 2.1). On AF02 the opcode
/// comes first.
#[must_use]
pub fn encode(frame: &Frame, route: BleRoute) -> Vec<u8> {
    let mut out = Vec::with_capacity(frame.payload().len().saturating_add(2));
    if route == BleRoute::Af01 {
        out.push(AF01_PLACEHOLDER);
    }
    out.push(frame.opcode());
    out.extend_from_slice(frame.payload());
    out
}

/// The frame carried by a notification on the given characteristic.
///
/// # Errors
///
/// [`Reason::Short`] for a notification without an opcode, and
/// [`Reason::BadPrefix`] for an AF01 notification that does not start with
/// the route tag `0x31`.
pub fn decode(bytes: &[u8], route: BleRoute) -> Result<Frame, Reason> {
    let body = match route {
        BleRoute::Af01 => {
            if bytes.len() < 2 {
                return Err(Reason::Short {
                    needed: 2,
                    got: bytes.len(),
                });
            }
            let (tag, body) = bytes.split_at(1);
            if tag != [AF01_TAG] {
                return Err(Reason::BadPrefix);
            }
            body
        }
        BleRoute::Af02 => {
            if bytes.is_empty() {
                return Err(Reason::Short { needed: 1, got: 0 });
            }
            bytes
        }
    };
    let (opcode, payload) = body.split_at(1);
    let opcode = opcode
        .first()
        .copied()
        .ok_or(Reason::Short { needed: 1, got: 0 })?;
    Frame::new(opcode, payload.to_vec())
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::protocol::error::Reason;
    use crate::protocol::frame::Frame;

    /// Test: UT-PROTO-002
    #[test]
    fn encode_adds_the_placeholder_on_af01_only() {
        let c4 = Frame::new(0xC4, vec![]).unwrap();
        let e0 = Frame::new(0xE0, vec![]).unwrap();
        assert_eq!(encode(&c4, BleRoute::Af01), vec![0x12, 0xC4]);
        assert_eq!(encode(&e0, BleRoute::Af02), vec![0xE0]);
    }

    /// Test: UT-PROTO-002
    #[test]
    fn decode_strips_the_tag_on_af01_and_nothing_on_af02() {
        // 2026-09-29T193614-ble-readonly.jsonl, the 0xC5 notification on AF01.
        let af01 = [
            0x31, 0xC5, 0x5A, 0x02, 0x00, 0x00, 0x01, 0xF4, 0x01, 0x32, 0x00, 0x00, 0x00,
        ];
        let frame = decode(&af01, BleRoute::Af01).unwrap();
        assert_eq!(frame.opcode(), 0xC5);
        assert_eq!(frame.payload().len(), 11);
        // Same capture, the 0x19 reply on AF02.
        let af02 = [0x19, 0x00];
        let frame = decode(&af02, BleRoute::Af02).unwrap();
        assert_eq!(frame.opcode(), 0x19);
        assert_eq!(frame.payload(), &[0x00]);
    }

    /// Test: UT-PROTO-002
    #[test]
    fn decode_rejects_a_missing_tag_and_empty_input() {
        let no_tag = [0xC5, 0x5A, 0x02];
        assert_eq!(
            decode(&no_tag, BleRoute::Af01).unwrap_err(),
            Reason::BadPrefix
        );
        assert_eq!(
            decode(&[], BleRoute::Af01).unwrap_err(),
            Reason::Short { needed: 2, got: 0 }
        );
        assert_eq!(
            decode(&[], BleRoute::Af02).unwrap_err(),
            Reason::Short { needed: 1, got: 0 }
        );
        assert_eq!(
            decode(&[0x31], BleRoute::Af01).unwrap_err(),
            Reason::Short { needed: 2, got: 1 }
        );
    }
}
