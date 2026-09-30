//! The opcode policy: what the system may send, and what it must never send.
//!
//! Implements: DD-PROTO-040, DD-PROTO-041.

use crate::protocol::error::Reason;
use crate::protocol::frame::Frame;
use crate::protocol::ops::{bind, control, info, telemetry};

/// The requests the system may send, with their exact payload lengths.
pub const ALLOWED: [(u8, usize); 4] = [
    (bind::REQUEST, 18),
    (info::REQUEST, 0),
    (telemetry::REQUEST, 0),
    (control::REQUEST, control::LEN),
];

/// Opcodes the system must never send, with the reason (device-model.md 11).
pub const NEVER: &[(u8, &str)] = &[
    (0x10, "rewrites the Bluetooth chip's advertising data"),
    (0xC0, "rewrites the Bluetooth chip's advertising data"),
    (0xBE, "accessory input, reaches the front-panel input path"),
    (0x20, "block write"),
    (0xF0, "maintenance and update"),
    (0xF1, "maintenance reply opcode"),
    (0xF2, "maintenance and update"),
    (0xF3, "maintenance reply opcode"),
    (0xF4, "maintenance and update"),
    (0xF5, "maintenance reply opcode"),
    (0xF6, "maintenance and update"),
    (0xF7, "maintenance reply opcode"),
    (0xF8, "maintenance and update"),
    (0xF9, "maintenance reply opcode"),
    (0xFA, "maintenance and update"),
    (0xFB, "maintenance reply opcode"),
    (0xFC, "maintenance and update"),
    (0xFD, "maintenance reply opcode"),
    (0xFE, "factory reset with reboot"),
];

/// Checks that `frame` is one of the allowed requests with its exact length.
///
/// # Errors
///
/// [`Reason::NotAllowed`] for any other opcode, [`Reason::BadLength`] for a
/// wrong payload length.
pub fn check(frame: &Frame) -> Result<(), Reason> {
    let (_, expected) = ALLOWED
        .iter()
        .find(|(opcode, _)| *opcode == frame.opcode())
        .ok_or(Reason::NotAllowed(frame.opcode()))?;
    let got = frame.payload().len();
    if got != *expected {
        return Err(Reason::BadLength {
            expected: *expected,
            got,
        });
    }
    Ok(())
}

/// Why `opcode` must never be sent, if it is on the never list.
#[must_use]
pub fn never_reason(opcode: u8) -> Option<&'static str> {
    NEVER
        .iter()
        .find(|(o, _)| *o == opcode)
        .map(|(_, reason)| *reason)
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::protocol::error::Reason;
    use crate::protocol::frame::Frame;

    /// Test: UT-PROTO-040
    #[test]
    fn only_the_four_v1_opcodes_pass_with_their_exact_length() {
        for opcode in 0u8..=255 {
            let result = check(&Frame::new(opcode, vec![]).unwrap());
            match opcode {
                0xE0 | 0xC2 => assert_eq!(result, Ok(()), "{opcode:02x}"),
                0x18 => assert_eq!(
                    result,
                    Err(Reason::BadLength {
                        expected: 18,
                        got: 0
                    })
                ),
                0xC8 => assert_eq!(
                    result,
                    Err(Reason::BadLength {
                        expected: 11,
                        got: 0
                    })
                ),
                _ => assert_eq!(result, Err(Reason::NotAllowed(opcode)), "{opcode:02x}"),
            }
        }
        for (opcode, ok, others) in [(0x18u8, 18usize, [17usize, 19]), (0xC8, 11, [10, 12])] {
            assert_eq!(check(&Frame::new(opcode, vec![0; ok]).unwrap()), Ok(()));
            for n in others {
                assert_eq!(
                    check(&Frame::new(opcode, vec![0; n]).unwrap()),
                    Err(Reason::BadLength {
                        expected: ok,
                        got: n
                    })
                );
            }
        }
    }

    /// Test: UT-PROTO-040
    #[test]
    fn the_never_list_names_a_reason_for_every_entry() {
        let mut listed: Vec<u8> = vec![0x10, 0xC0, 0xBE, 0x20];
        listed.extend(0xF0..=0xFE);
        for opcode in listed {
            assert!(
                never_reason(opcode).is_some_and(|r| !r.is_empty()),
                "{opcode:02x}"
            );
            assert_eq!(
                check(&Frame::new(opcode, vec![]).unwrap()),
                Err(Reason::NotAllowed(opcode))
            );
        }
        assert_eq!(never_reason(0xC2), None);
        assert_eq!(never_reason(0xFE), Some("factory reset with reboot"));
    }
}
