//! Reasons a frame or a payload is rejected by the protocol layer.
//!
//! Implements: DD-PROTO-003.

use core::fmt;

/// Why the protocol layer rejected a frame or a payload.
///
/// A parser given fewer bytes than its layout needs returns [`Reason::Short`];
/// given more, [`Reason::BadLength`]. Parsers never return a partial value.
#[derive(Clone, Debug, PartialEq, Eq)]
pub enum Reason {
    /// Fewer bytes than the layout needs.
    Short {
        /// Bytes the layout needs.
        needed: usize,
        /// Bytes that were given.
        got: usize,
    },
    /// A length that does not match the layout (more bytes than it takes,
    /// or a length field the framing cannot accept).
    BadLength {
        /// The length the layout expects.
        expected: usize,
        /// The length that was given.
        got: usize,
    },
    /// A payload longer than the one-byte length field of the framed form
    /// can carry (254 bytes).
    TooLong,
    /// An AF01 notification that does not start with the route tag `0x31`.
    BadPrefix,
    /// The checksum of a framed reply does not match its bytes.
    BadChecksum {
        /// The checksum computed over the received bytes.
        expected: u8,
        /// The checksum byte that was received.
        got: u8,
    },
    /// A framed reply whose address byte is not `0x21`.
    BadAddress(u8),
    /// A frame in progress was dropped because a new frame started.
    Restarted,
    /// Bytes skipped between frames, reported before the next result.
    Skipped(u64),
    /// An opcode the system is not allowed to send.
    NotAllowed(u8),
    /// A reply whose opcode is not the one the parser expects.
    WrongOpcode {
        /// The opcode the parser expects.
        expected: u8,
        /// The opcode that was received.
        got: u8,
    },
    /// A field holds a value the layout does not allow.
    Value {
        /// The field's name as protocol.md names it.
        field: &'static str,
        /// The offending value.
        value: i64,
    },
}

impl fmt::Display for Reason {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Reason::Short { needed, got } => {
                write!(f, "frame too short: needed {needed} bytes, got {got}")
            }
            Reason::BadLength { expected, got } => {
                write!(f, "wrong length: expected {expected} bytes, got {got}")
            }
            Reason::TooLong => write!(f, "payload longer than 254 bytes"),
            Reason::BadPrefix => {
                write!(f, "notification does not start with the AF01 tag 0x31")
            }
            Reason::BadChecksum { expected, got } => {
                write!(
                    f,
                    "bad checksum: expected 0x{expected:02x}, got 0x{got:02x}"
                )
            }
            Reason::BadAddress(address) => write!(f, "unexpected frame address 0x{address:02x}"),
            Reason::Restarted => write!(f, "frame dropped: a new frame started"),
            Reason::Skipped(count) => write!(f, "{count} bytes skipped before a frame"),
            Reason::NotAllowed(opcode) => {
                write!(f, "opcode 0x{opcode:02x} is not on the allowlist")
            }
            Reason::WrongOpcode { expected, got } => {
                write!(
                    f,
                    "wrong opcode: expected 0x{expected:02x}, got 0x{got:02x}"
                )
            }
            Reason::Value { field, value } => {
                write!(f, "field {field} has the unexpected value {value}")
            }
        }
    }
}

impl std::error::Error for Reason {}

#[cfg(test)]
mod tests {
    use super::*;

    /// Test: UT-PROTO-004
    #[test]
    fn display_names_the_variant_and_its_fields() {
        let cases: [(Reason, &str); 11] = [
            (
                Reason::Short {
                    needed: 36,
                    got: 35,
                },
                "frame too short: needed 36 bytes, got 35",
            ),
            (
                Reason::BadLength {
                    expected: 36,
                    got: 37,
                },
                "wrong length: expected 36 bytes, got 37",
            ),
            (Reason::TooLong, "payload longer than 254 bytes"),
            (
                Reason::BadPrefix,
                "notification does not start with the AF01 tag 0x31",
            ),
            (
                Reason::BadChecksum {
                    expected: 0x7F,
                    got: 0,
                },
                "bad checksum: expected 0x7f, got 0x00",
            ),
            (Reason::BadAddress(0x12), "unexpected frame address 0x12"),
            (Reason::Restarted, "frame dropped: a new frame started"),
            (Reason::Skipped(7), "7 bytes skipped before a frame"),
            (
                Reason::NotAllowed(0xC6),
                "opcode 0xc6 is not on the allowlist",
            ),
            (
                Reason::WrongOpcode {
                    expected: 0x19,
                    got: 0x18,
                },
                "wrong opcode: expected 0x19, got 0x18",
            ),
            (
                Reason::Value {
                    field: "bind",
                    value: 1,
                },
                "field bind has the unexpected value 1",
            ),
        ];
        for (reason, text) in cases {
            assert_eq!(reason.to_string(), text);
        }
    }
}
