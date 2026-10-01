//! The device's timing bounds, defined once (device-model.md 12).
//!
//! Implements: DD-PROTO-060.

use core::time::Duration;

/// The Bluetooth chip drops an unbound link about 30 s after it connected
/// (device-model.md 4.1).
pub const BIND: Duration = Duration::from_secs(30);
/// The remote-control prompt closes as denied after about 60 s; 70 s leaves
/// margin (device-model.md 5).
pub const REMOTE_PROMPT: Duration = Duration::from_secs(70);
/// An immediate reply is expected within 1 s (SR-023).
pub const REPLY: Duration = Duration::from_secs(1);
/// The output-off acknowledgment must arrive within 0.5 s (SR-022).
pub const OUTPUT_OFF_ACK: Duration = Duration::from_millis(500);
/// The next poll is sent no earlier than 100 ms after the previous reply
/// (SR-013).
pub const POLL_PAUSE: Duration = Duration::from_millis(100);
/// Over USB a frame goes out at least every 2 s, since 8 s of silence drops
/// the link (device-model.md 4.4, SR-051).
pub const USB_KEEPALIVE: Duration = Duration::from_secs(2);
/// A link loss is reported within 4 s of the last reply (SR-028).
pub const LINK_LOSS_REPORT: Duration = Duration::from_secs(4);
/// Reconnection retries every 5 s (SR-055).
pub const RECONNECT_RETRY: Duration = Duration::from_secs(5);
/// Reconnection gives up after 10 min (SR-055).
pub const RECONNECT_GIVE_UP: Duration = Duration::from_secs(600);
/// A reading is trusted only from 100 ms after the last `0xC9`, since the
/// supply publishes a command's setpoints and output flag into `0xC3` on a
/// later pass of its UI task (SR-019; the real lag is TBD-023).
pub const SETTLE: Duration = Duration::from_millis(100);
/// A scan runs 10 s unless the user sets another time (SR-002).
pub const SCAN_DEFAULT: Duration = Duration::from_secs(10);
/// The shortest scan time the user can set (SR-002).
pub const SCAN_MIN: Duration = Duration::from_secs(1);
/// The longest scan time the user can set (SR-002).
pub const SCAN_MAX: Duration = Duration::from_secs(60);
/// The scan for one known identifier before a connect gives up (the
/// discovery DD, DD-DISC-011).
pub const FIND: Duration = Duration::from_secs(4);
/// The bound on the OS connect, which has no timeout of its own (the
/// discovery DD, DD-DISC-011).
pub const CONNECT: Duration = Duration::from_secs(10);

#[cfg(test)]
mod tests {
    use super::*;
    use core::time::Duration;

    /// Test: UT-PROTO-060
    #[test]
    fn the_nine_bounds_have_their_values() {
        assert_eq!(BIND, Duration::from_secs(30));
        assert_eq!(REMOTE_PROMPT, Duration::from_secs(70));
        assert_eq!(REPLY, Duration::from_secs(1));
        assert_eq!(OUTPUT_OFF_ACK, Duration::from_millis(500));
        assert_eq!(POLL_PAUSE, Duration::from_millis(100));
        assert_eq!(USB_KEEPALIVE, Duration::from_secs(2));
        assert_eq!(LINK_LOSS_REPORT, Duration::from_secs(4));
        assert_eq!(RECONNECT_RETRY, Duration::from_secs(5));
        assert_eq!(RECONNECT_GIVE_UP, Duration::from_secs(600));
    }

    /// Test: UT-PROTO-060
    #[test]
    fn the_bounds_added_by_ar_014_revision_7_have_their_values() {
        assert_eq!(SETTLE, Duration::from_millis(100));
        assert_eq!(SCAN_DEFAULT, Duration::from_secs(10));
        assert_eq!(SCAN_MIN, Duration::from_secs(1));
        assert_eq!(SCAN_MAX, Duration::from_secs(60));
        assert_eq!(FIND, Duration::from_secs(4));
        assert_eq!(CONNECT, Duration::from_secs(10));
    }
}
