//! Bind request `0x18` and reply `0x19`.
//!
//! Implements: DD-PROTO-020, DD-PROTO-021.

use crate::protocol::ble::BleRoute;
use crate::protocol::error::Reason;
use crate::protocol::frame::Frame;
use crate::protocol::ops::expect_reply;

/// The bind request opcode.
pub const REQUEST: u8 = 0x18;
/// The bind reply opcode.
pub const REPLY: u8 = 0x19;
/// The bind is the one v1 request written to AF02.
pub const ROUTE: BleRoute = BleRoute::Af02;
/// The constant host ID WebLink sends from every browser. It is refused so
/// that this software is never mistaken for WebLink by a supply that
/// remembers hosts.
const WEBLINK_ID: [u8; 16] = [
    0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00,
];

/// The 16-byte identifier a host presents at every bind, so that a supply
/// which has allowed it once recognises it again (device-model.md 4.1).
#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub struct HostId([u8; 16]);

impl HostId {
    /// Wraps an ID. Fails for the all-zero ID and for WebLink's constant ID.
    ///
    /// # Errors
    ///
    /// [`Reason::Value`] with the field `host_id`.
    pub fn new(bytes: [u8; 16]) -> Result<Self, Reason> {
        if bytes == [0; 16] || bytes == WEBLINK_ID {
            return Err(Reason::Value {
                field: "host_id",
                value: 0,
            });
        }
        Ok(Self(bytes))
    }

    /// Wraps a stored ID of exactly 16 bytes, with the checks of [`HostId::new`].
    ///
    /// # Errors
    ///
    /// [`Reason::Short`] or [`Reason::BadLength`] for another length, and the
    /// errors of [`HostId::new`].
    pub fn from_bytes(bytes: &[u8]) -> Result<Self, Reason> {
        let array: [u8; 16] = bytes.try_into().map_err(|_| {
            if bytes.len() < 16 {
                Reason::Short {
                    needed: 16,
                    got: bytes.len(),
                }
            } else {
                Reason::BadLength {
                    expected: 16,
                    got: bytes.len(),
                }
            }
        })?;
        Self::new(array)
    }

    /// The 16 bytes, for storage.
    #[must_use]
    pub fn as_bytes(&self) -> &[u8; 16] {
        &self.0
    }
}

/// The device's answer to a bind.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum BindReply {
    /// `19 00`: the host is allowed.
    Allowed,
    /// `19 FF`: the host is denied.
    Denied,
}

/// The bind request: `0x18`, the host ID, one zero byte and the fast flag
/// (18 payload bytes, the length of the captured WebLink frame).
///
/// With `fast` set the Bluetooth chip answers from its remembered IDs without
/// a prompt; with it clear the request reaches the supply's screen
/// (device-model.md 3 and 4.1).
#[must_use]
pub fn request(host_id: &HostId, fast: bool) -> Frame {
    let mut payload = Vec::with_capacity(18);
    payload.extend_from_slice(host_id.as_bytes());
    payload.push(0x00);
    payload.push(u8::from(fast));
    // 18 bytes never exceed the frame's limit.
    Frame::new(REQUEST, payload).unwrap_or_else(|_| Frame::empty(REQUEST))
}

/// Parses a `0x19` reply.
///
/// # Errors
///
/// [`Reason::WrongOpcode`], a length error, or [`Reason::Value`] for a status
/// byte other than `00` and `FF`.
pub fn parse(frame: &Frame) -> Result<BindReply, Reason> {
    let payload = expect_reply(frame, REPLY, 1)?;
    match payload.first().copied() {
        Some(0x00) => Ok(BindReply::Allowed),
        Some(0xFF) => Ok(BindReply::Denied),
        other => Err(Reason::Value {
            field: "bind",
            value: i64::from(other.unwrap_or(0)),
        }),
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::protocol::error::Reason;
    use crate::protocol::frame::Frame;

    const ID: [u8; 16] = [
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE,
        0xAF,
    ];

    /// Test: UT-PROTO-020
    #[test]
    fn request_is_id_one_zero_and_the_flag() {
        let id = HostId::new(ID).unwrap();
        let fast = request(&id, true);
        assert_eq!(fast.opcode(), 0x18);
        let mut expected = ID.to_vec();
        expected.extend_from_slice(&[0x00, 0x01]);
        assert_eq!(fast.payload(), expected.as_slice());
        let slow = request(&id, false);
        expected[17] = 0x00;
        assert_eq!(slow.payload(), expected.as_slice());
        assert_eq!(slow.payload().len(), 18);
    }

    /// Test: UT-PROTO-020
    #[test]
    fn host_id_rejects_zero_and_weblinks_constant() {
        let weblink = [
            0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
            0x08, 0x00,
        ];
        assert_eq!(
            HostId::new([0; 16]).unwrap_err(),
            Reason::Value {
                field: "host_id",
                value: 0
            }
        );
        assert_eq!(
            HostId::new(weblink).unwrap_err(),
            Reason::Value {
                field: "host_id",
                value: 0
            }
        );
        assert_eq!(
            HostId::from_bytes(&weblink).unwrap_err(),
            Reason::Value {
                field: "host_id",
                value: 0
            }
        );
        assert_eq!(
            HostId::from_bytes(&ID[..15]).unwrap_err(),
            Reason::Short {
                needed: 16,
                got: 15
            }
        );
    }

    /// Test: UT-PROTO-020
    #[test]
    fn host_id_round_trips_through_bytes() {
        let id = HostId::new(ID).unwrap();
        assert_eq!(HostId::from_bytes(id.as_bytes()).unwrap(), id);
    }

    /// Test: UT-PROTO-021
    #[test]
    fn parse_maps_the_two_replies_and_rejects_the_rest() {
        // 2026-09-29T193614-ble-readonly.jsonl: `19 00`; 2026-09-29T194319: `19 ff`.
        assert_eq!(
            parse(&Frame::new(0x19, vec![0x00]).unwrap()).unwrap(),
            BindReply::Allowed
        );
        assert_eq!(
            parse(&Frame::new(0x19, vec![0xFF]).unwrap()).unwrap(),
            BindReply::Denied
        );
        assert_eq!(
            parse(&Frame::new(0x19, vec![0x01]).unwrap()).unwrap_err(),
            Reason::Value {
                field: "bind",
                value: 1
            }
        );
        assert_eq!(
            parse(&Frame::new(0x18, vec![0x00]).unwrap()).unwrap_err(),
            Reason::WrongOpcode {
                expected: 0x19,
                got: 0x18
            }
        );
        assert_eq!(
            parse(&Frame::new(0x19, vec![]).unwrap()).unwrap_err(),
            Reason::Short { needed: 1, got: 0 }
        );
        assert_eq!(
            parse(&Frame::new(0x19, vec![0, 0]).unwrap()).unwrap_err(),
            Reason::BadLength {
                expected: 1,
                got: 2
            }
        );
    }
}
