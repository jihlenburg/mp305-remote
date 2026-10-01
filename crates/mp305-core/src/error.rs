//! The crate-wide error type.
//!
//! Implements: AR-050 (the variants the protocol module needs; the others
//! follow with their modules), DD-TRANS-040, DD-LINK-050, DD-SESS-060.

use core::fmt;
use core::time::Duration;

use crate::protocol::error::Reason;
use crate::protocol::ops::telemetry::Faults;

/// Every way an operation of this crate fails. The Python exceptions and the
/// app's messages map from these variants one to one.
#[derive(Clone, Debug, PartialEq)]
pub enum Error {
    /// A frame or a payload the protocol layer rejected.
    Protocol(Reason),
    /// A value outside its allowed range: a setpoint outside the supply's
    /// range or the user's limits, or another bounded value. `min` and
    /// `max` are the bounds, in the unit of `field`.
    SetpointRange {
        /// What the value is, for example `voltage` or `current`.
        field: &'static str,
        /// The value that was given.
        value: f64,
        /// The lowest allowed value; 0 for a setpoint.
        min: f64,
        /// The bound it exceeded, in the unit of `field` (V or A for a
        /// setpoint).
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
    /// The supply answered the bind with anything but `19 00`.
    ConnectionDenied,
    /// The supply denied remote control, or the prompt timed out.
    RemoteControlDenied,
    /// The supply answered a command with status 1: remote control is not
    /// held.
    RemoteControlLost,
    /// The supply answered a command with `0xFF` or another status.
    CommandRejected {
        /// The status byte of the `0xC9`.
        status: u8,
        /// `mode`, `range`, `fault`, `busy` or `status <n>`.
        reason: String,
    },
    /// The latest reading shows a fault, so the output is not switched on.
    FaultActive {
        /// The active faults.
        faults: Faults,
    },
    /// The session has not reached the ready state yet.
    NotReady,
    /// The marker store (and later the store module) failed.
    Store {
        /// What went wrong.
        message: String,
    },
    /// A session to this identifier is already open in this process.
    AlreadyOpen {
        /// The identifier.
        identifier: String,
    },
    /// The command was cancelled before it completed.
    Cancelled {
        /// Why.
        reason: String,
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
            Error::SetpointRange {
                field,
                value,
                min,
                max,
            } => {
                write!(f, "{field} {value} is outside {min} to {max}")
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
            Error::ConnectionDenied => write!(f, "the supply denied the connection"),
            Error::RemoteControlDenied => write!(f, "the supply denied remote control"),
            Error::RemoteControlLost => {
                write!(f, "remote control is not held; request it again")
            }
            Error::CommandRejected { status, reason } => write!(
                f,
                "the supply rejected the command (status 0x{status:02x}, {reason})"
            ),
            Error::FaultActive { faults } => {
                write!(f, "the supply reports a fault: ")?;
                for (i, fault) in faults.iter().enumerate() {
                    if i > 0 {
                        write!(f, ", ")?;
                    }
                    write!(f, "{fault}")?;
                }
                Ok(())
            }
            Error::NotReady => write!(f, "the session is not ready for control"),
            Error::Store { message } => write!(f, "store: {message}"),
            Error::AlreadyOpen { identifier } => write!(
                f,
                "a session to {identifier} is already open in this process"
            ),
            Error::Cancelled { reason } => write!(f, "the command was cancelled: {reason}"),
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
                min: 0.0,
                max: 30.0
            }
            .to_string(),
            "voltage 31 is outside 0 to 30"
        );
        assert_eq!(
            Error::SetpointRange {
                field: "scan time (s)",
                value: 0.5,
                min: 1.0,
                max: 60.0
            }
            .to_string(),
            "scan time (s) 0.5 is outside 1 to 60"
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

    /// Test: UT-SESS-006
    #[test]
    fn display_of_the_session_variants() {
        use crate::protocol::ops::telemetry::Faults;
        let text = |e: Error| e.to_string();
        assert_eq!(
            text(Error::ConnectionDenied),
            "the supply denied the connection"
        );
        assert_eq!(
            text(Error::RemoteControlDenied),
            "the supply denied remote control"
        );
        assert_eq!(
            text(Error::RemoteControlLost),
            "remote control is not held; request it again"
        );
        assert_eq!(
            text(Error::CommandRejected {
                status: 0xFF,
                reason: "busy".to_string()
            }),
            "the supply rejected the command (status 0xff, busy)"
        );
        assert_eq!(
            text(Error::FaultActive {
                faults: Faults(0b10_0001)
            }),
            "the supply reports a fault: reversed output, over current"
        );
        assert_eq!(
            text(Error::NotReady),
            "the session is not ready for control"
        );
        assert_eq!(
            text(Error::Store {
                message: "disk full".to_string()
            }),
            "store: disk full"
        );
        assert_eq!(
            text(Error::AlreadyOpen {
                identifier: "AB12".to_string()
            }),
            "a session to AB12 is already open in this process"
        );
        assert_eq!(
            text(Error::Cancelled {
                reason: "superseded by an output-off".to_string()
            }),
            "the command was cancelled: superseded by an output-off"
        );
    }
}
