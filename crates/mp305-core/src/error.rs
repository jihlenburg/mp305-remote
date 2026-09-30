//! The crate-wide error type.
//!
//! Implements: AR-050 (the variants the protocol module needs; the others
//! follow with their modules).

use core::fmt;

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
}
