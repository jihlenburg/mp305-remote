//! The crate-wide error type.
//!
//! Implements: AR-050 (the variants the protocol module needs; the others
//! follow with their modules), DD-TRANS-040, DD-LINK-050.

use core::fmt;
use core::time::Duration;

use crate::protocol::error::Reason;

/// Every way an operation of this crate fails. The Python exceptions and the
/// app's messages map from these variants one to one.
#[derive(Clone, Debug, PartialEq)]
pub enum Error {
    /// A frame or a payload the protocol layer rejected.
    Protocol(Reason),
    /// A setpoint outside the supply's range or the user's limits. `max` is
    /// the bound that was exceeded, in the unit of `field`.
    SetpointRange {
        /// `voltage` or `current`.
        field: &'static str,
        /// The value that was given.
        value: f64,
        /// The bound it exceeded, in V or A.
        max: f64,
    },
    /// The supply is not in DC mode, the only mode v1 controls.
    Mode {
        /// The raw live mode the reading reported.
        live_mode: u8,
    },
    /// A transport failed: the vendor library's error text, or the
    /// transport's own reason.
    Transport {
        /// What went wrong.
        message: String,
    },
    /// No reply arrived for a request within its bound: `timing::REPLY` or
    /// `timing::OUTPUT_OFF_ACK` for an immediate request, the bind or the
    /// remote-prompt bound for a deferred one.
    Timeout {
        /// The request opcode.
        opcode: u8,
        /// The bound that passed.
        after: Duration,
    },
    /// The link ended before the request completed, or had already ended.
    LinkLost {
        /// Why the link ended.
        text: String,
    },
}

/// Writes a duration as `<n> ms` below 1 s and as `<n> s` with one decimal
/// from 1 s on (DD-LINK-050).
pub(crate) fn fmt_duration(f: &mut fmt::Formatter<'_>, d: Duration) -> fmt::Result {
    if d < Duration::from_secs(1) {
        write!(f, "{} ms", d.as_millis())
    } else {
        write!(f, "{:.1} s", d.as_secs_f64())
    }
}

/// A duration as [`fmt_duration`] writes it.
pub(crate) fn duration_text(d: Duration) -> String {
    /// Adapter so that `fmt_duration` can write into a `String`.
    struct Text(Duration);
    impl fmt::Display for Text {
        fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
            fmt_duration(f, self.0)
        }
    }
    Text(d).to_string()
}

impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Error::Protocol(reason) => write!(f, "protocol: {reason}"),
            Error::SetpointRange { field, value, max } => {
                write!(f, "{field} {value} is outside 0 to {max}")
            }
            Error::Mode { live_mode } => {
                write!(f, "the supply is not in DC mode (mode {live_mode})")
            }
            Error::Transport { message } => write!(f, "transport: {message}"),
            Error::Timeout { opcode, after } => {
                write!(f, "no reply to 0x{opcode:02x} within ")?;
                fmt_duration(f, *after)
            }
            Error::LinkLost { text } => write!(f, "link lost: {text}"),
        }
    }
}

impl std::error::Error for Error {}

impl From<Reason> for Error {
    fn from(reason: Reason) -> Self {
        Error::Protocol(reason)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::protocol::error::Reason;

    /// Test: UT-TRANS-040
    #[test]
    fn display_of_transport() {
        assert_eq!(
            Error::Transport {
                message: "x".to_string()
            }
            .to_string(),
            "transport: x"
        );
    }

    /// Test: UT-PROTO-004 (the protocol variants' `Display`)
    #[test]
    fn display_of_the_protocol_variants() {
        assert_eq!(
            Error::Protocol(Reason::TooLong).to_string(),
            "protocol: payload longer than 254 bytes"
        );
        assert_eq!(
            Error::SetpointRange {
                field: "voltage",
                value: 31.0,
                max: 30.0
            }
            .to_string(),
            "voltage 31 is outside 0 to 30"
        );
        assert_eq!(
            Error::Mode { live_mode: 2 }.to_string(),
            "the supply is not in DC mode (mode 2)"
        );
    }

    /// Test: UT-LINK-026
    #[test]
    fn display_of_timeout_and_link_lost() {
        use core::time::Duration;
        let timeout = |opcode, after| Error::Timeout { opcode, after }.to_string();
        assert_eq!(
            timeout(0xC2, Duration::from_secs(1)),
            "no reply to 0xc2 within 1.0 s"
        );
        assert_eq!(
            timeout(0xC8, Duration::from_millis(500)),
            "no reply to 0xc8 within 500 ms"
        );
        assert_eq!(
            timeout(0x18, Duration::from_secs(30)),
            "no reply to 0x18 within 30.0 s"
        );
        assert_eq!(
            Error::LinkLost {
                text: "x".to_string()
            }
            .to_string(),
            "link lost: x"
        );
    }
}
