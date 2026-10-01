//! Implements: DD-SESS-013, DD-SESS-022, DD-SESS-031, DD-SESS-033,
//! DD-SESS-002 (the limit check), DD-SESS-032 (guard 7, the limits on the
//! setpoints a frame copies).
//!
//! The pure parts of the session: the link and the remote-control state
//! machines, the freshness rule for the reading a `0xC8` is built from, the
//! check of the user's limits, the reason given for a rejected command, and
//! the setpoint comparison after a failed command. Nothing here does I/O or
//! reads a clock.

use tokio::time::Instant;

use crate::error::Error;
use crate::protocol::ops::telemetry::RawReading;
use crate::protocol::timing;
use crate::protocol::units::{
    self, Limits, AMP_SCALE, SUPPLY_MAX_RAW_CURRENT, SUPPLY_MAX_RAW_VOLTAGE, VOLT_SCALE,
};
use crate::session::{LinkState, RemoteState};
use crate::transport::description::Kind;

/// What the task feeds the link state machine.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum LinkInput {
    /// The connector returned a transport of this kind.
    Connected(Kind),
    /// The bind started (Bluetooth only).
    BindStarted,
    /// The bind gave `19 00`, or over USB the `0xE1` arrived.
    Allowed,
    /// The first reading arrived and polling is on.
    Ready,
    /// The bind was denied.
    Denied,
    /// The link was lost, or a reconnection attempt failed.
    Lost,
    /// A reconnection is scheduled.
    RetryScheduled,
    /// The reconnection gave up.
    GaveUp,
    /// The host closed the session.
    Closed,
}

/// The link state machine of DD-SESS-013: a total transition table. It
/// keeps the kind the connector reported, since the bind is a Bluetooth
/// step and the `Connected + Allowed` pair a USB one.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct LinkMachine {
    /// The current state.
    pub state: LinkState,
    /// The kind of the current connection, once connected.
    pub kind: Option<Kind>,
}

impl LinkMachine {
    /// A machine in `Connecting` with no kind yet.
    #[must_use]
    pub fn new() -> Self {
        Self {
            state: LinkState::Connecting,
            kind: None,
        }
    }

    /// The state after `input`, or `Err` with the unchanged state for a pair
    /// the table does not list.
    ///
    /// # Errors
    ///
    /// The unchanged state for a pair outside the table.
    pub fn on(self, input: LinkInput) -> Result<LinkState, LinkState> {
        use LinkInput as I;
        use LinkState as S;
        let ble = self.kind == Some(Kind::Ble);
        let hid = self.kind == Some(Kind::Hid);
        match (self.state, input) {
            (S::Closed, _) => Err(S::Closed),
            (_, I::Closed) => Ok(S::Closed),
            (S::Connecting, I::Connected(_)) => Ok(S::Connected),
            (S::Connected, I::BindStarted) if ble => Ok(S::Binding),
            (S::Connected, I::Allowed) if hid => Ok(S::Allowed),
            (S::Binding, I::Allowed) => Ok(S::Allowed),
            (S::Binding, I::Denied) => Ok(S::Denied),
            (S::Allowed, I::Ready) => Ok(S::Ready),
            (S::Connecting | S::Connected | S::Binding | S::Allowed | S::Ready, I::Lost) => {
                Ok(S::Lost)
            }
            (S::Lost, I::RetryScheduled) => Ok(S::Reconnecting),
            (S::Reconnecting, I::Ready) => Ok(S::Ready),
            (S::Reconnecting, I::Lost) => Ok(S::Reconnecting),
            (S::Reconnecting, I::GaveUp | I::Denied) => Ok(S::Lost),
            (state, _) => Err(state),
        }
    }

    /// Feeds `input` and keeps the result; a `Connected(kind)` that was
    /// accepted also records the kind.
    ///
    /// # Errors
    ///
    /// The unchanged state for a pair outside the table.
    pub fn apply(&mut self, input: LinkInput) -> Result<LinkState, LinkState> {
        let next = self.on(input)?;
        if let LinkInput::Connected(kind) = input {
            self.kind = Some(kind);
        }
        self.state = next;
        Ok(next)
    }
}

impl Default for LinkMachine {
    fn default() -> Self {
        Self::new()
    }
}

/// What the task feeds the remote-control state machine.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum RemoteInput {
    /// A request for remote control is sent.
    Request,
    /// The request was granted (`0xC9` 0).
    Granted,
    /// The request was denied (`0xC9` 1).
    DeniedByReply,
    /// The request's prompt timed out.
    DeniedByTimeout,
    /// The request failed otherwise: a USB `FF`, another status or a
    /// timeout.
    RequestFailed,
    /// A release was accepted.
    Released,
    /// A command was answered with status 1.
    StatusOne,
    /// The link was lost.
    LinkLost,
    /// A reconnection succeeded.
    Reconnected,
}

/// The remote-control state machine of DD-SESS-022, total.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct RemoteMachine(pub RemoteState);

impl RemoteMachine {
    /// The state after `input`; a pair outside the table leaves it
    /// unchanged.
    #[must_use]
    pub fn on(self, input: RemoteInput) -> RemoteState {
        use RemoteInput as I;
        use RemoteState as S;
        match (self.0, input) {
            (_, I::StatusOne | I::LinkLost) => S::Lost,
            (_, I::Reconnected) => S::None,
            (S::None | S::Denied | S::Lost | S::Requested, I::Request) => S::Requested,
            (S::Requested, I::Granted) => S::Granted,
            (S::Requested, I::DeniedByReply | I::DeniedByTimeout) => S::Denied,
            (S::Requested, I::RequestFailed) => S::None,
            // A release accepted in `Denied` or `Lost` also ends at `None`
            // (DD-SESS-021: "on 0xC9 0 moves to None").
            (S::Granted | S::Denied | S::Lost, I::Released) => S::None,
            (state, _) => state,
        }
    }
}

/// Whether the latest reading can be copied into a `0xC8`.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Freshness {
    /// It arrived at or after `settle_until` and at most `timing::REPLY`
    /// ago.
    Fresh,
    /// It arrived before `settle_until` or is too old; the text says which.
    Stale(&'static str),
    /// There is no reading yet.
    None,
}

/// The freshness rule of DD-SESS-031 for a reading that arrived at
/// `reading_at`, with the settle time `settle_until` (the later of the last
/// handled `0xC9` plus `timing::SETTLE` and the end of the wait after a
/// cancelled command), at `now`.
#[must_use]
pub fn freshness(
    reading_at: Option<Instant>,
    settle_until: Option<Instant>,
    now: Instant,
) -> Freshness {
    let Some(at) = reading_at else {
        return Freshness::None;
    };
    if settle_until.is_some_and(|until| at < until) {
        return Freshness::Stale("the reading arrived before the settle time");
    }
    if now.saturating_duration_since(at) > timing::REPLY {
        return Freshness::Stale("the reading is older than 1 s");
    }
    Freshness::Fresh
}

/// Checks the user's limits (DD-SESS-002): each limit that is set must be
/// finite and not negative. A NaN limit would otherwise switch the limit
/// off, since no comparison with NaN is true.
///
/// # Errors
///
/// [`Error::SetpointRange`] naming the limit (`voltage limit` or
/// `current limit`), with the bounds 0 and infinity.
pub fn check_limits(limits: &Limits) -> Result<(), Error> {
    for (field, limit) in [
        ("voltage limit", limits.max_volts),
        ("current limit", limits.max_amps),
    ] {
        if let Some(value) = limit {
            if !value.is_finite() || value < 0.0 {
                return Err(Error::SetpointRange {
                    field,
                    value,
                    min: 0.0,
                    max: f64::INFINITY,
                });
            }
        }
    }
    Ok(())
}

/// Guard (7) of DD-SESS-032: the two raw setpoints a frame with `output` 1
/// carries, held against the user's limits through the same rounding as a
/// value the user names (`units::to_raw`). Only the user's limits apply
/// here; the supply's own bounds on a copied field are checked when the
/// command is built.
///
/// # Errors
///
/// [`Error::SetpointRange`] naming the field (`voltage` or `current`), the
/// copied value in V or A, and the limit it exceeds.
pub fn check_copied(set_voltage: u16, set_current: u16, limits: &Limits) -> Result<(), Error> {
    let fields = [
        ("voltage", set_voltage, VOLT_SCALE, limits.max_volts),
        ("current", set_current, AMP_SCALE, limits.max_amps),
    ];
    for (field, raw, scale, limit) in fields {
        if let Some(max) = limit {
            if f64::from(raw) > units::to_raw(max, scale) {
                return Err(Error::SetpointRange {
                    field,
                    value: f64::from(raw) / scale,
                    min: 0.0,
                    max,
                });
            }
        }
    }
    Ok(())
}

/// The reason given for a `0xFF` (DD-SESS-033): `mode` if `reading` is not
/// in DC mode, `range` if a raw setpoint the command set is above the
/// supply's rated maximum, `fault` if `reading` shows a fault, else `busy`.
#[must_use]
pub fn rejection_reason(
    reading: &RawReading,
    raw_voltage: Option<u16>,
    raw_current: Option<u16>,
) -> &'static str {
    if reading.model != 0 {
        "mode"
    } else if raw_voltage.is_some_and(|v| v > SUPPLY_MAX_RAW_VOLTAGE)
        || raw_current.is_some_and(|c| c > SUPPLY_MAX_RAW_CURRENT)
    {
        "range"
    } else if reading.charge_error != 0 {
        "fault"
    } else {
        "busy"
    }
}

/// The comparison after a failed command (DD-SESS-033): `reading`'s raw
/// setpoints against the expected ones where the user set one and against
/// `built_from`'s otherwise. `Some((set_voltage, set_current,
/// expected_voltage, expected_current))`, all raw, when either differs.
#[must_use]
pub fn setpoints_differ(
    reading: &RawReading,
    expected: (Option<u16>, Option<u16>),
    built_from: &RawReading,
) -> Option<(u16, u16, u16, u16)> {
    let volts = expected.0.unwrap_or(built_from.set_voltage);
    let amps = expected.1.unwrap_or(built_from.set_current);
    (reading.set_voltage != volts || reading.set_current != amps).then_some((
        reading.set_voltage,
        reading.set_current,
        volts,
        amps,
    ))
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::error::Error;
    use crate::protocol::fixtures;
    use crate::protocol::frame::Frame;
    use crate::protocol::ops::telemetry;
    use crate::protocol::units::Limits;
    use core::time::Duration;

    fn reading(payload: Vec<u8>) -> RawReading {
        telemetry::parse(&Frame::new(0xC3, payload).unwrap()).unwrap()
    }

    /// Test: UT-SESS-001
    #[test]
    fn link_machine_follows_the_table() {
        use LinkInput as I;
        use LinkState as S;
        let ble = |s: S| LinkMachine {
            state: s,
            kind: Some(Kind::Ble),
        };
        let hid = |s: S| LinkMachine {
            state: s,
            kind: Some(Kind::Hid),
        };
        let on = |s: S, i: I| ble(s).on(i);
        let fresh = LinkMachine::new();
        assert_eq!(fresh.on(I::Connected(Kind::Ble)), Ok(S::Connected));
        assert_eq!(fresh.on(I::Connected(Kind::Hid)), Ok(S::Connected));
        assert_eq!(on(S::Connected, I::BindStarted), Ok(S::Binding));
        assert_eq!(hid(S::Connected).on(I::Allowed), Ok(S::Allowed));
        assert_eq!(on(S::Connected, I::Allowed), Err(S::Connected));
        assert_eq!(on(S::Binding, I::Allowed), Ok(S::Allowed));
        assert_eq!(on(S::Binding, I::Denied), Ok(S::Denied));
        assert_eq!(on(S::Allowed, I::Ready), Ok(S::Ready));
        for s in [
            S::Connecting,
            S::Connected,
            S::Binding,
            S::Allowed,
            S::Ready,
        ] {
            assert_eq!(on(s, I::Lost), Ok(S::Lost), "{s}");
        }
        assert_eq!(on(S::Lost, I::RetryScheduled), Ok(S::Reconnecting));
        assert_eq!(on(S::Reconnecting, I::Ready), Ok(S::Ready));
        assert_eq!(on(S::Reconnecting, I::Lost), Ok(S::Reconnecting));
        assert_eq!(on(S::Reconnecting, I::GaveUp), Ok(S::Lost));
        assert_eq!(on(S::Reconnecting, I::Denied), Ok(S::Lost));
        for s in [
            S::Connecting,
            S::Connected,
            S::Binding,
            S::Allowed,
            S::Ready,
            S::Denied,
            S::Lost,
            S::Reconnecting,
        ] {
            assert_eq!(on(s, I::Closed), Ok(S::Closed), "{s}");
        }
        // Pairs outside the table.
        assert_eq!(on(S::Connecting, I::Allowed), Err(S::Connecting));
        assert_eq!(on(S::Lost, I::Ready), Err(S::Lost));
        let mut usb = LinkMachine::new();
        assert_eq!(usb.apply(I::Connected(Kind::Hid)), Ok(S::Connected));
        assert_eq!(usb.apply(I::BindStarted), Err(S::Connected));
        assert_eq!(usb.state, S::Connected);
        assert_eq!(on(S::Closed, I::Lost), Err(S::Closed));
        assert_eq!(on(S::Closed, I::Closed), Err(S::Closed));
    }

    /// Test: UT-SESS-002
    #[test]
    fn remote_machine_follows_the_table() {
        use RemoteInput as I;
        let inputs = [
            I::Request,
            I::Granted,
            I::StatusOne,
            I::Request,
            I::DeniedByTimeout,
            I::Request,
            I::DeniedByReply,
            I::Request,
            I::Granted,
            I::Released,
            I::LinkLost,
            I::Reconnected,
            I::Request,
            I::RequestFailed,
            I::Released,
        ];
        let mut state = RemoteState::None;
        let mut seen = Vec::new();
        for input in inputs {
            state = RemoteMachine(state).on(input);
            seen.push(state);
        }
        use RemoteState as S;
        assert_eq!(
            seen,
            [
                S::Requested,
                S::Granted,
                S::Lost,
                S::Requested,
                S::Denied,
                S::Requested,
                S::Denied,
                S::Requested,
                S::Granted,
                S::None,
                S::Lost,
                S::None,
                S::Requested,
                S::None,
                S::None,
            ]
        );
        // `Released` from `Denied` and from `Lost` (DD-SESS-022, revision 4).
        assert_eq!(RemoteMachine(S::Denied).on(I::Released), S::None);
        assert_eq!(RemoteMachine(S::Lost).on(I::Released), S::None);
        assert_eq!(RemoteMachine(S::Granted).on(I::Request), S::Granted);
        assert_eq!(RemoteMachine(S::Requested).on(I::Request), S::Requested);
        assert_eq!(RemoteMachine(S::None).on(I::Granted), S::None);
    }

    /// Test: UT-SESS-003
    #[test]
    fn freshness_needs_a_recent_reading_from_the_settle_time_on() {
        let now = Instant::now() + Duration::from_secs(10);
        let ago = |ms: u64| Some(now - Duration::from_millis(ms));
        // 0.5 s old, arrived after `settle_until`.
        assert_eq!(freshness(ago(500), ago(800), now), Freshness::Fresh);
        // 1.5 s old.
        assert_eq!(
            freshness(ago(1_500), ago(2_000), now),
            Freshness::Stale("the reading is older than 1 s")
        );
        // Arrived before `settle_until`, although only 0.1 s old.
        assert_eq!(
            freshness(ago(100), ago(50), now),
            Freshness::Stale("the reading arrived before the settle time")
        );
        // Arrived exactly at `settle_until`.
        assert_eq!(freshness(ago(300), ago(300), now), Freshness::Fresh);
        assert_eq!(freshness(None, ago(50), now), Freshness::None);
        // No `0xC9` yet.
        assert_eq!(freshness(ago(500), None, now), Freshness::Fresh);
    }

    /// Test: UT-SESS-003
    #[test]
    fn check_limits_refuses_nan_infinite_and_negative_limits() {
        let limits = |max_volts, max_amps| Limits {
            max_volts,
            max_amps,
        };
        assert_eq!(check_limits(&limits(None, None)), Ok(()));
        assert_eq!(check_limits(&limits(Some(12.0), Some(1.0))), Ok(()));
        let refused = |l: Limits| matches!(check_limits(&l), Err(Error::SetpointRange { .. }));
        assert!(refused(limits(Some(f64::NAN), None)));
        assert!(refused(limits(None, Some(-1.0))));
        assert!(refused(limits(Some(f64::INFINITY), None)));
        assert_eq!(
            check_limits(&limits(None, Some(-1.0))),
            Err(Error::SetpointRange {
                field: "current limit",
                value: -1.0,
                min: 0.0,
                max: f64::INFINITY,
            })
        );
        let text = check_limits(&limits(Some(f64::NAN), None))
            .unwrap_err()
            .to_string();
        assert_eq!(text, "voltage limit NaN is outside 0 to inf");
    }

    /// Test: UT-SESS-004
    #[test]
    fn rejection_reason_and_setpoint_comparison() {
        let pd = reading(fixtures::c3_with(0, 2, 0, 1300, 1000));
        let dc = reading(fixtures::C3_CAPTURE.to_vec());
        let fault = reading(fixtures::c3_with(0, 0, 1 << 5, 1300, 1000));
        assert_eq!(rejection_reason(&pd, None, None), "mode");
        assert_eq!(rejection_reason(&dc, Some(3001), None), "range");
        assert_eq!(rejection_reason(&dc, None, Some(5001)), "range");
        assert_eq!(rejection_reason(&fault, None, None), "fault");
        assert_eq!(rejection_reason(&dc, Some(170), None), "busy");
        let now = reading(fixtures::c3_with(0, 0, 0, 150, 1000));
        assert_eq!(
            setpoints_differ(&now, (Some(170), None), &dc),
            Some((150, 1000, 170, 1000))
        );
        assert_eq!(setpoints_differ(&dc, (None, None), &dc), None);
    }
}
