//! The check of the ATT MTU after a Bluetooth connect: when the reported
//! value passes, when it is read again, when the link is refused and when
//! the connect goes on with a warning.
//!
//! `btleplug` 0.13 reports 23, the ATT default, until the operating system
//! told it the negotiated value: on BlueZ when the characteristics carry no
//! MTU property (older BlueZ), on Windows until the asynchronous
//! `MaxPduSizeChanged` callback arrived, on macOS when CoreBluetooth gives
//! a maximum write length of 0. So 23 can mean "not known yet" as well as a
//! real MTU of 23.
//!
//! Implements: DD-TRANS-010 (the pure part of the MTU check).

use core::time::Duration;

/// The smallest ATT MTU that carries the longest reply (70 bytes plus the
/// route tag, plus the 3-byte ATT header).
pub const MIN_MTU: u16 = 74;

/// The value `btleplug` reports while the operating system has not reported
/// the MTU (its `DEFAULT_MTU_SIZE`, the ATT default).
pub const UNREPORTED_MTU: u16 = 23;

/// How long a value below [`MIN_MTU`] is read again before the verdict is
/// final.
pub const MTU_WAIT: Duration = Duration::from_secs(1);

/// The pause between two reads of the MTU during [`MTU_WAIT`].
pub const MTU_STEP: Duration = Duration::from_millis(100);

/// What the connect does with the MTU it read.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum MtuVerdict {
    /// At least [`MIN_MTU`]: go on.
    Pass,
    /// Below [`MIN_MTU`] before [`MTU_WAIT`] ran out: read it again after
    /// [`MTU_STEP`].
    Wait,
    /// Below [`MIN_MTU`] at the end of the wait and not [`UNREPORTED_MTU`]:
    /// a negotiated MTU that is too small. Refuse the link.
    Refuse,
    /// Still [`UNREPORTED_MTU`] at the end of the wait: the operating
    /// system may not report the MTU. Log at WARN and go on; a link that
    /// really is that small fails afterwards, since truncated notifications
    /// fail the frame check and the requests time out.
    Unreported,
}

/// The verdict on `mtu`, read when `waited` of [`MTU_WAIT`] has passed
/// since the first read.
#[must_use]
pub fn mtu_verdict(mtu: u16, waited: Duration) -> MtuVerdict {
    if mtu >= MIN_MTU {
        MtuVerdict::Pass
    } else if waited < MTU_WAIT {
        MtuVerdict::Wait
    } else if mtu == UNREPORTED_MTU {
        MtuVerdict::Unreported
    } else {
        MtuVerdict::Refuse
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Test: UT-TRANS-042
    #[test]
    fn the_verdict_at_the_first_read_and_at_the_end_of_the_wait() {
        assert_eq!(MIN_MTU, 74);
        assert_eq!(UNREPORTED_MTU, 23);
        assert_eq!(MTU_WAIT, Duration::from_secs(1));
        assert_eq!(MTU_STEP, Duration::from_millis(100));
        let values = [23, 24, 73, 74, 185];
        assert_eq!(
            values.map(|mtu| mtu_verdict(mtu, Duration::ZERO)),
            [
                MtuVerdict::Wait,
                MtuVerdict::Wait,
                MtuVerdict::Wait,
                MtuVerdict::Pass,
                MtuVerdict::Pass
            ]
        );
        assert_eq!(
            values.map(|mtu| mtu_verdict(mtu, Duration::from_millis(900))),
            [
                MtuVerdict::Wait,
                MtuVerdict::Wait,
                MtuVerdict::Wait,
                MtuVerdict::Pass,
                MtuVerdict::Pass
            ]
        );
        assert_eq!(
            values.map(|mtu| mtu_verdict(mtu, MTU_WAIT)),
            [
                MtuVerdict::Unreported,
                MtuVerdict::Refuse,
                MtuVerdict::Refuse,
                MtuVerdict::Pass,
                MtuVerdict::Pass
            ]
        );
    }
}
