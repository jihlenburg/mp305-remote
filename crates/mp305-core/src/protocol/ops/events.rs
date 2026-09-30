//! Frames the device sends on its own: the settings and four opaque events.
//!
//! Implements: DD-PROTO-032.

use crate::protocol::error::Reason;
use crate::protocol::frame::Frame;
use crate::protocol::ops::settings::{self, Settings};

/// A frame the device sends without a request (device-model.md 6).
#[derive(Clone, Debug, PartialEq, Eq)]
pub enum DeviceFrame {
    /// `0xC5`: a setting changed on the front panel.
    Settings(Settings),
    /// `0xDD`: the selected program changed; payload kept as bytes.
    SelectedProgram(Vec<u8>),
    /// `0xE5`: the active PD profile changed; payload kept as bytes.
    ActivePdProfile(Vec<u8>),
    /// `0xEB`: a charge ended; payload kept as bytes.
    ChargeSettings(Vec<u8>),
    /// `0xDB`: program steps were saved; payload kept as bytes.
    ProgramStepsSaved(Vec<u8>),
}

/// Classifies `frame` as one of the device's own frames, `None` for any
/// other opcode.
///
/// # Errors
///
/// The parse error of a malformed `0xC5`, so the caller counts and logs it.
pub fn classify(frame: &Frame) -> Result<Option<DeviceFrame>, Reason> {
    let payload = frame.payload().to_vec();
    Ok(match frame.opcode() {
        settings::REPLY => Some(DeviceFrame::Settings(settings::parse(frame)?)),
        0xDD => Some(DeviceFrame::SelectedProgram(payload)),
        0xE5 => Some(DeviceFrame::ActivePdProfile(payload)),
        0xEB => Some(DeviceFrame::ChargeSettings(payload)),
        0xDB => Some(DeviceFrame::ProgramStepsSaved(payload)),
        _ => None,
    })
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::protocol::error::Reason;
    use crate::protocol::frame::Frame;

    /// Test: UT-PROTO-031
    #[test]
    fn classify_maps_the_five_event_opcodes_and_nothing_else() {
        let c5 = Frame::new(
            0xC5,
            vec![
                0x5A, 0x02, 0x00, 0x00, 0x01, 0xF4, 0x01, 0x32, 0x00, 0x00, 0x00,
            ],
        )
        .unwrap();
        assert!(
            matches!(classify(&c5), Ok(Some(DeviceFrame::Settings(s))) if s.charge_limit == 90)
        );
        assert_eq!(
            classify(&Frame::new(0xC5, vec![0; 10]).unwrap()).unwrap_err(),
            Reason::Short {
                needed: 11,
                got: 10
            }
        );
        assert_eq!(
            classify(&Frame::new(0xDD, vec![1, 6]).unwrap()).unwrap(),
            Some(DeviceFrame::SelectedProgram(vec![1, 6]))
        );
        assert_eq!(
            classify(&Frame::new(0xE5, vec![7]).unwrap()).unwrap(),
            Some(DeviceFrame::ActivePdProfile(vec![7]))
        );
        assert_eq!(
            classify(&Frame::new(0xEB, vec![0; 20]).unwrap()).unwrap(),
            Some(DeviceFrame::ChargeSettings(vec![0; 20]))
        );
        assert_eq!(
            classify(&Frame::new(0xDB, vec![0]).unwrap()).unwrap(),
            Some(DeviceFrame::ProgramStepsSaved(vec![0]))
        );
        assert_eq!(
            classify(&Frame::new(0xC3, vec![0; 36]).unwrap()).unwrap(),
            None
        );
        assert_eq!(classify(&Frame::new(0x00, vec![]).unwrap()).unwrap(), None);
    }
}
