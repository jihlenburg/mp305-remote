//! The v1 opcodes: one submodule per request and reply pair, plus the two
//! rules shared by all of them, the reply opcode and the Bluetooth route.
//!
//! Implements: DD-PROTO-002 (route and reply opcode).

pub mod bind;
pub mod control;
pub mod events;
pub mod info;
pub mod settings;
pub mod telemetry;

use crate::protocol::error::Reason;
use crate::protocol::frame::Frame;

/// Checks that `frame` is the reply `expected` with exactly `len` payload
/// bytes and returns the payload.
///
/// # Errors
///
/// [`Reason::WrongOpcode`], [`Reason::Short`] or [`Reason::BadLength`].
pub(crate) fn expect_reply(frame: &Frame, expected: u8, len: usize) -> Result<&[u8], Reason> {
    expect_opcode(frame, expected)?;
    expect_len(frame.payload(), len)
}

/// Checks that `frame` carries the opcode `expected`.
///
/// # Errors
///
/// [`Reason::WrongOpcode`].
pub(crate) fn expect_opcode(frame: &Frame, expected: u8) -> Result<(), Reason> {
    if frame.opcode() == expected {
        Ok(())
    } else {
        Err(Reason::WrongOpcode {
            expected,
            got: frame.opcode(),
        })
    }
}

/// Checks that `payload` has exactly `len` bytes and returns it.
///
/// # Errors
///
/// [`Reason::Short`] or [`Reason::BadLength`].
pub(crate) fn expect_len(payload: &[u8], len: usize) -> Result<&[u8], Reason> {
    let got = payload.len();
    if got < len {
        return Err(Reason::Short { needed: len, got });
    }
    if got > len {
        return Err(Reason::BadLength { expected: len, got });
    }
    Ok(payload)
}

/// Reads the little-endian `u16` at `offset`. The callers have checked the
/// payload length against their layout, so a missing byte reads as 0.
pub(crate) fn u16_at(payload: &[u8], offset: usize) -> u16 {
    let lo = payload.get(offset).copied().unwrap_or(0);
    let hi = payload.get(offset.saturating_add(1)).copied().unwrap_or(0);
    u16::from_le_bytes([lo, hi])
}

/// Reads the little-endian `u32` at `offset`, as [`u16_at`] does.
pub(crate) fn u32_at(payload: &[u8], offset: usize) -> u32 {
    let mut bytes = [0u8; 4];
    for (i, b) in bytes.iter_mut().enumerate() {
        *b = payload.get(offset.saturating_add(i)).copied().unwrap_or(0);
    }
    u32::from_le_bytes(bytes)
}

/// Reads the byte at `offset`, 0 when missing (see [`u16_at`]).
pub(crate) fn u8_at(payload: &[u8], offset: usize) -> u8 {
    payload.get(offset).copied().unwrap_or(0)
}

use crate::protocol::ble::BleRoute;

/// The opcode of the bind request, the only v1 request written to AF02.
const BIND: u8 = 0x18;

/// The characteristic a v1 request is written to: the bind on AF02, every
/// other request on AF01, as the captures of 2026-09-29 show.
#[must_use]
pub fn route(opcode: u8) -> BleRoute {
    if opcode == BIND {
        BleRoute::Af02
    } else {
        BleRoute::Af01
    }
}

/// The opcode of the reply to `request`: the request plus one for every v1
/// opcode. (The device's `0x20` block write replies with `0x20`; it is not a
/// v1 opcode and is never sent.)
#[must_use]
pub fn reply_opcode(request: u8) -> u8 {
    request.wrapping_add(1)
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::protocol::ble::BleRoute;

    /// Test: UT-PROTO-002
    #[test]
    fn bind_goes_on_af02_everything_else_on_af01() {
        assert_eq!(route(0x18), BleRoute::Af02);
        assert_eq!(route(0xE0), BleRoute::Af01);
        assert_eq!(route(0xC2), BleRoute::Af01);
        assert_eq!(route(0xC8), BleRoute::Af01);
    }

    /// Test: UT-PROTO-033
    #[test]
    fn reply_opcode_is_request_plus_one() {
        assert_eq!(reply_opcode(0x18), 0x19);
        assert_eq!(reply_opcode(0xE0), 0xE1);
        assert_eq!(reply_opcode(0xC2), 0xC3);
        assert_eq!(reply_opcode(0xC8), 0xC9);
    }
}
