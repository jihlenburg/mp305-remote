//! The settings reply `0xC5`, which the device also sends on its own when a
//! setting changes on the front panel.
//!
//! Implements: DD-PROTO-031.

use crate::protocol::error::Reason;
use crate::protocol::frame::Frame;
use crate::protocol::ops::{expect_reply, u16_at, u8_at};

/// The settings reply opcode (the request `0xC4` is not sent in v1).
pub const REPLY: u8 = 0xC5;
/// Payload length of the reply.
pub const LEN: usize = 11;

/// The supply's settings as `0xC5` reports them.
///
/// | Offset | Type | Field |
/// |---|---|---|
/// | 0 | u8 | `charge_limit`, % |
/// | 1 | u8 | `volume` |
/// | 2 | u8 | `screen_off` |
/// | 3 | u8 | `shutdown`, min |
/// | 4 | u8 | `screen_direction` |
/// | 5 | u16 | `ramp_step`, mV per 100 ms |
/// | 7 | u16 | `ocp_delay`, ms |
/// | 9 | u16 | `usb_line_drop` |
///
/// See docs/research/protocol.md, section 4.3.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct Settings {
    /// Battery charge limit, percent.
    pub charge_limit: u8,
    /// Buzzer volume, 0 to 3.
    pub volume: u8,
    /// Screen-off setting.
    pub screen_off: u8,
    /// Auto shutdown, minutes.
    pub shutdown: u8,
    /// Display orientation.
    pub screen_direction: u8,
    /// Ramp step, mV per 100 ms.
    pub ramp_step: u16,
    /// OCP delay, ms.
    pub ocp_delay: u16,
    /// USB line drop compensation.
    pub usb_line_drop: u16,
}

/// Parses a `0xC5` frame.
///
/// # Errors
///
/// [`Reason::WrongOpcode`] or a length error.
pub fn parse(frame: &Frame) -> Result<Settings, Reason> {
    let p = expect_reply(frame, REPLY, LEN)?;
    Ok(Settings {
        charge_limit: u8_at(p, 0),
        volume: u8_at(p, 1),
        screen_off: u8_at(p, 2),
        shutdown: u8_at(p, 3),
        screen_direction: u8_at(p, 4),
        ramp_step: u16_at(p, 5),
        ocp_delay: u16_at(p, 7),
        usb_line_drop: u16_at(p, 9),
    })
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::protocol::error::Reason;
    use crate::protocol::frame::Frame;

    /// Test: UT-PROTO-030
    #[test]
    fn parse_reads_the_capture() {
        // 2026-09-29T193614-ble-readonly.jsonl, the `0xC5` reply.
        let s = parse(
            &Frame::new(
                0xC5,
                vec![
                    0x5A, 0x02, 0x00, 0x00, 0x01, 0xF4, 0x01, 0x32, 0x00, 0x00, 0x00,
                ],
            )
            .unwrap(),
        )
        .unwrap();
        assert_eq!(s.charge_limit, 90);
        assert_eq!(s.volume, 2);
        assert_eq!(s.screen_off, 0);
        assert_eq!(s.shutdown, 0);
        assert_eq!(s.screen_direction, 1);
        assert_eq!(s.ramp_step, 500);
        assert_eq!(s.ocp_delay, 50);
        assert_eq!(s.usb_line_drop, 0);
        assert_eq!(
            parse(&Frame::new(0xC5, vec![0; 10]).unwrap()).unwrap_err(),
            Reason::Short {
                needed: 11,
                got: 10
            }
        );
    }
}
