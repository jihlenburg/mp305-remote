//! Request classes, eligibility and the dispatch decision. Pure: nothing
//! here reads a clock or touches a channel; the task passes the time and
//! its state in.
//!
//! Implements: DD-LINK-010, DD-LINK-012, DD-LINK-013.

use core::time::Duration;

use tokio::time::Instant;

use crate::protocol::frame::Frame;
use crate::protocol::ops::{self, bind, control, telemetry};
use crate::protocol::timing;
use crate::transport::description::Kind;

/// The two reply opcodes that can answer a deferred request.
const DEFERRED_REPLIES: [u8; 2] = [bind::REPLY, control::REPLY];

/// The opcodes the device sends on its own (`protocol::ops::events`).
const EVENT_OPCODES: [u8; 5] = [0xC5, 0xDD, 0xE5, 0xEB, 0xDB];

/// Offset of the fast flag in the `0x18` payload.
const BIND_FAST_FLAG: usize = 17;

/// Offset of `remoteCon` in the `0xC8` payload.
const REMOTE_CON: usize = 0;

/// The `remoteCon` value that requests remote control.
const REMOTE_CON_REQUEST: u8 = 2;

/// Where a deferred request's deadline is measured from.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Bound {
    /// From the instant the transport was connected (the bind, SR-009).
    FromConnection(Duration),
    /// From the write start of the request (the remote request, SR-053).
    FromWrite(Duration),
}

impl Bound {
    /// The length of the bound.
    #[must_use]
    pub fn duration(self) -> Duration {
        match self {
            Bound::FromConnection(d) | Bound::FromWrite(d) => d,
        }
    }

    /// The deadline: `connected_at + d` or `write_start + d`. An overflow
    /// means the deadline has already passed, so the origin is returned.
    #[must_use]
    pub fn deadline(self, connected_at: Instant, write_start: Instant) -> Instant {
        let (origin, d) = match self {
            Bound::FromConnection(d) => (connected_at, d),
            Bound::FromWrite(d) => (write_start, d),
        };
        origin.checked_add(d).unwrap_or(origin)
    }
}

/// How a request is answered.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Class {
    /// Answered within `timeout` by the reply opcode; occupies the link
    /// until then.
    Immediate {
        /// The reply opcode.
        reply: u8,
        /// How long the reply may take from the write start.
        timeout: Duration,
    },
    /// Answered when a person acts; frees the link as soon as it is written
    /// and is completed later by an expectation.
    Deferred {
        /// The reply opcode.
        reply: u8,
        /// The deadline rule.
        bound: Bound,
    },
}

impl Class {
    /// The class of `frame` on a transport of `kind` (DD-LINK-010).
    ///
    /// A payload too short for the byte a rule reads counts as the flag
    /// clear (`0x18`) or as `remoteCon` not 2 (`0xC8`); the guard refuses
    /// such a frame by length before it is written.
    #[must_use]
    pub fn of(frame: &Frame, kind: Kind) -> Class {
        let opcode = frame.opcode();
        let byte = |offset: usize| frame.payload().get(offset).copied();
        if opcode == bind::REQUEST && byte(BIND_FAST_FLAG).unwrap_or(0) == 0 {
            return Class::Deferred {
                reply: bind::REPLY,
                bound: Bound::FromConnection(timing::BIND),
            };
        }
        if opcode == control::REQUEST
            && kind == Kind::Ble
            && byte(REMOTE_CON) == Some(REMOTE_CON_REQUEST)
        {
            return Class::Deferred {
                reply: control::REPLY,
                bound: Bound::FromWrite(timing::REMOTE_PROMPT),
            };
        }
        Class::Immediate {
            reply: ops::reply_opcode(opcode),
            timeout: timing::REPLY,
        }
    }

    /// The class of an `output_off` frame: immediate, with the output-off
    /// acknowledgment bound.
    #[must_use]
    pub fn output_off() -> Class {
        Class::Immediate {
            reply: control::REPLY,
            timeout: timing::OUTPUT_OFF_ACK,
        }
    }

    /// The reply opcode of either class.
    #[must_use]
    pub fn reply(&self) -> u8 {
        match self {
            Class::Immediate { reply, .. } | Class::Deferred { reply, .. } => *reply,
        }
    }
}

/// What the task does with an incoming frame (DD-LINK-012).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Disposition {
    /// The reply to the request in flight.
    Reply,
    /// The completion of an open expectation.
    Expectation,
    /// A frame the device sends on its own.
    Event,
    /// A `0x19` or `0xC9` that completes nothing.
    Late,
    /// Anything else; counted and logged.
    Ignore,
}

/// The part of the task's state the dispatch decision reads.
#[derive(Clone, Copy, Debug)]
pub struct DispatchState<'a> {
    /// The reply opcode of the request in flight, if any.
    pub in_flight_reply: Option<u8>,
    /// The reply opcodes of the open expectations.
    pub open_expectations: &'a [u8],
}

/// Decides what an incoming frame with `opcode` is, in the fixed order of
/// DD-LINK-012: reply, expectation, event, late, ignore.
#[must_use]
pub fn dispatch(state: &DispatchState<'_>, opcode: u8) -> Disposition {
    if state.in_flight_reply == Some(opcode) {
        Disposition::Reply
    } else if DEFERRED_REPLIES.contains(&opcode) && state.open_expectations.contains(&opcode) {
        Disposition::Expectation
    } else if EVENT_OPCODES.contains(&opcode) {
        Disposition::Event
    } else if DEFERRED_REPLIES.contains(&opcode) {
        Disposition::Late
    } else {
        Disposition::Ignore
    }
}

/// A frame that could be written next: its opcode and class.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct Candidate {
    /// The request opcode.
    pub opcode: u8,
    /// Its class.
    pub class: Class,
}

/// The part of the task's state the eligibility rules read.
#[derive(Clone, Copy, Debug)]
pub struct EligibilityState<'a> {
    /// The reply opcodes of the open expectations.
    pub open_expectations: &'a [u8],
    /// The `0xC8` block (DD-LINK-023).
    pub block: bool,
    /// The arrival stamp of the last good `0xC3`, if any arrived.
    pub last_reply_at: Option<Instant>,
    /// The current time.
    pub now: Instant,
}

/// Whether `candidate` may be written now (DD-LINK-013): no open
/// expectation for its reply opcode; not a `0xC8` while the block is set;
/// not a `0xC2` before `last_reply_at + timing::POLL_PAUSE`.
#[must_use]
pub fn eligible(candidate: &Candidate, state: &EligibilityState<'_>) -> bool {
    if state.open_expectations.contains(&candidate.class.reply()) {
        return false;
    }
    if candidate.opcode == control::REQUEST && state.block {
        return false;
    }
    if candidate.opcode == telemetry::REQUEST {
        if let Some(at) = state.last_reply_at {
            // An overflow means the pause has already passed.
            if let Some(due) = at.checked_add(timing::POLL_PAUSE) {
                return state.now >= due;
            }
        }
    }
    true
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::protocol::frame::Frame;
    use crate::protocol::ops::{bind, info, telemetry};
    use crate::protocol::timing::{BIND, POLL_PAUSE, REMOTE_PROMPT, REPLY};
    use crate::transport::description::Kind;
    use core::time::Duration;
    use tokio::time::Instant;

    fn c8(remote_con: u8) -> Frame {
        let mut p = vec![0u8; 11];
        p[0] = remote_con;
        Frame::new(0xC8, p).unwrap()
    }

    /// Test: UT-LINK-001
    #[test]
    fn classes_of_the_v1_requests() {
        let id = bind::HostId::new([1; 16]).unwrap();
        let imm = |reply| Class::Immediate {
            reply,
            timeout: REPLY,
        };
        assert_eq!(Class::of(&bind::request(&id, true), Kind::Ble), imm(0x19));
        assert_eq!(
            Class::of(&bind::request(&id, false), Kind::Ble),
            Class::Deferred {
                reply: 0x19,
                bound: Bound::FromConnection(BIND)
            }
        );
        assert_eq!(
            Class::of(&c8(2), Kind::Ble),
            Class::Deferred {
                reply: 0xC9,
                bound: Bound::FromWrite(REMOTE_PROMPT)
            }
        );
        assert_eq!(Class::of(&c8(2), Kind::Hid), imm(0xC9));
        assert_eq!(Class::of(&c8(1), Kind::Ble), imm(0xC9));
        assert_eq!(Class::of(&telemetry::request(), Kind::Ble), imm(0xC3));
        assert_eq!(Class::of(&info::request(), Kind::Ble), imm(0xE1));
        let short_bind = Frame::new(0x18, vec![1, 2, 3]).unwrap();
        assert!(matches!(
            Class::of(&short_bind, Kind::Ble),
            Class::Deferred { reply: 0x19, .. }
        ));
        let empty_c8 = Frame::new(0xC8, vec![]).unwrap();
        assert!(matches!(
            Class::of(&empty_c8, Kind::Ble),
            Class::Immediate { reply: 0xC9, .. }
        ));
    }

    /// Test: UT-LINK-003
    #[test]
    fn dispatch_decides_in_the_designed_order() {
        let open = [0xC9];
        let state = DispatchState {
            in_flight_reply: Some(0xC3),
            open_expectations: &open,
        };
        let expected = [
            (0xC3, Disposition::Reply),
            (0xC9, Disposition::Expectation),
            (0x19, Disposition::Late),
            (0xC5, Disposition::Event),
            (0xDD, Disposition::Event),
            (0xE5, Disposition::Event),
            (0xEB, Disposition::Event),
            (0xDB, Disposition::Event),
            (0xE3, Disposition::Ignore),
            (0x77, Disposition::Ignore),
        ];
        for (opcode, disposition) in expected {
            assert_eq!(dispatch(&state, opcode), disposition, "{opcode:02x}");
        }
        let state = DispatchState {
            in_flight_reply: Some(0xC9),
            open_expectations: &open,
        };
        assert_eq!(dispatch(&state, 0xC9), Disposition::Reply);
    }

    /// Test: UT-LINK-004
    #[test]
    fn eligibility_rules() {
        let now = Instant::now() + Duration::from_secs(10);
        let state = |open: &'static [u8], block, last_reply_at| EligibilityState {
            open_expectations: open,
            block,
            last_reply_at,
            now,
        };
        let c8_imm = Candidate {
            opcode: 0xC8,
            class: Class::Immediate {
                reply: 0xC9,
                timeout: REPLY,
            },
        };
        assert!(!eligible(&c8_imm, &state(&[], true, None)));
        assert!(eligible(&c8_imm, &state(&[], false, None)));
        let bind_deferred = Candidate {
            opcode: 0x18,
            class: Class::Deferred {
                reply: 0x19,
                bound: Bound::FromConnection(BIND),
            },
        };
        assert!(!eligible(&bind_deferred, &state(&[0x19], false, None)));
        assert!(eligible(&bind_deferred, &state(&[], false, None)));
        let bind_fast = Candidate {
            opcode: 0x18,
            class: Class::Immediate {
                reply: 0x19,
                timeout: REPLY,
            },
        };
        assert!(!eligible(&bind_fast, &state(&[0x19], false, None)));
        let c2 = Candidate {
            opcode: 0xC2,
            class: Class::Immediate {
                reply: 0xC3,
                timeout: REPLY,
            },
        };
        let ago = |ms| Some(now - Duration::from_millis(ms));
        assert!(!eligible(&c2, &state(&[], false, ago(50))));
        assert!(eligible(&c2, &state(&[], false, ago(100))));
        assert!(eligible(&c2, &state(&[], false, None)));
        assert_eq!(POLL_PAUSE, Duration::from_millis(100));
        let e0 = Candidate {
            opcode: 0xE0,
            class: Class::Immediate {
                reply: 0xE1,
                timeout: REPLY,
            },
        };
        assert!(eligible(&e0, &state(&[], true, None)));
    }
}
