//! The one frame type the layers above the transports see.
//!
//! Implements: DD-PROTO-001.

use core::fmt;

use crate::protocol::error::Reason;

/// The longest payload the framed form can carry: opcode plus payload must
/// fit the one-byte length field.
pub const MAX_PAYLOAD: usize = 254;

/// One request or reply: an opcode and its payload, independent of the
/// transport's framing.
///
/// Frames are obtained from the request builders in `protocol::ops` and from
/// the decoders; the constructor is crate-private so that no short or
/// foreign frame can be built outside the protocol module (SR-052).
#[derive(Clone, PartialEq, Eq)]
pub struct Frame {
    /// The opcode byte.
    opcode: u8,
    /// The payload bytes after the opcode.
    payload: Vec<u8>,
}

impl Frame {
    /// Builds a frame. Fails with [`Reason::TooLong`] when the payload is
    /// longer than [`MAX_PAYLOAD`].
    pub(crate) fn new(opcode: u8, payload: Vec<u8>) -> Result<Self, Reason> {
        if payload.len() > MAX_PAYLOAD {
            return Err(Reason::TooLong);
        }
        Ok(Self { opcode, payload })
    }

    /// A frame without payload; it can never exceed the length limit.
    #[must_use]
    pub(crate) fn empty(opcode: u8) -> Self {
        Self {
            opcode,
            payload: Vec::new(),
        }
    }

    /// The opcode byte.
    #[must_use]
    pub fn opcode(&self) -> u8 {
        self.opcode
    }

    /// The payload bytes after the opcode.
    #[must_use]
    pub fn payload(&self) -> &[u8] {
        &self.payload
    }
}

impl fmt::Debug for Frame {
    /// Prints the opcode and the payload as space-separated lower-case hex.
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{:02x}", self.opcode)?;
        for byte in &self.payload {
            write!(f, " {byte:02x}")?;
        }
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::protocol::error::Reason;

    /// Test: UT-PROTO-001
    #[test]
    fn new_accepts_up_to_254_payload_bytes() {
        assert_eq!(Frame::new(0xC4, vec![]).unwrap().payload(), &[]);
        let f = Frame::new(0xC8, vec![0; 254]).unwrap();
        assert_eq!(f.opcode(), 0xC8);
        assert_eq!(f.payload().len(), 254);
    }

    /// Test: UT-PROTO-001
    #[test]
    fn new_rejects_255_payload_bytes() {
        assert_eq!(Frame::new(0xC8, vec![0; 255]).unwrap_err(), Reason::TooLong);
    }

    /// Test: UT-PROTO-001
    #[test]
    fn debug_prints_hex() {
        assert_eq!(format!("{:?}", Frame::new(0xC4, vec![]).unwrap()), "c4");
        assert_eq!(
            format!("{:?}", Frame::new(0x19, vec![0x00, 0xFF]).unwrap()),
            "19 00 ff"
        );
    }
}
