//! DC control request `0xC8` and reply `0xC9`.
//!
//! Implements: DD-PROTO-028, DD-PROTO-029, DD-PROTO-030.

use crate::error::Error;
use crate::protocol::error::Reason;
use crate::protocol::frame::Frame;
use crate::protocol::ops::expect_reply;
use crate::protocol::ops::telemetry::RawReading;
use crate::protocol::units::{RawCurrent, RawVoltage};

/// The control request opcode.
pub const REQUEST: u8 = 0xC8;
/// The control reply opcode.
pub const REPLY: u8 = 0xC9;
/// Payload length of the request.
pub const LEN: usize = 11;
/// The highest `setVoltage` the firmware itself accepts (30.50 V).
const DEVICE_MAX_VOLTAGE: u16 = 3050;
/// The highest `setCurrent` the firmware itself accepts (5.100 A).
const DEVICE_MAX_CURRENT: u16 = 5100;

/// The `remoteCon` byte.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
#[repr(u8)]
pub enum RemoteCon {
    /// 0: release remote control.
    Release = 0,
    /// 1: a command under remote control.
    Active = 1,
    /// 2: request remote control.
    Request = 2,
}

/// A `0xC8` command. It can only be built from a reading, so it always
/// carries the supply's whole current state with one field changed
/// (SR-019), and it has no way to set `model` or `refresh`.
///
/// | Offset | Type | Field |
/// |---|---|---|
/// | 0 | u8 | `remoteCon`: 0 release, 1 active, 2 request |
/// | 1 | u16 | `setVoltage`, 10 mV |
/// | 3 | u16 | `setCurrent`, 1 mA |
/// | 5 | u8 | `realChange` |
/// | 6 | u8 | `voltageSlow` |
/// | 7 | u8 | `currentOver` |
/// | 8 | u8 | `output` |
/// | 9 | u8 | `model`, always 0 |
/// | 10 | u8 | `refresh`, always 0 |
///
/// See docs/research/protocol.md, section 4.2.
///
/// The three examples below must not compile (Test: UT-PROTO-029).
///
/// ```compile_fail
/// use mp305_core::protocol::ops::control::Command;
/// let cmd = Command { remote_con: 1 };
/// ```
///
/// ```compile_fail
/// use mp305_core::protocol::ops::control::Command;
/// let cmd = Command::default();
/// ```
///
/// ```compile_fail
/// # use mp305_core::protocol::ops::control::Command;
/// # use mp305_core::protocol::ops::telemetry::RawReading;
/// fn change(mut cmd: Command) { cmd.model = 1; }
/// ```
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct Command {
    /// The `remoteCon` byte.
    remote_con: RemoteCon,
    /// The voltage setpoint, raw.
    set_voltage: u16,
    /// The current limit, raw.
    set_current: u16,
    /// Copied from the reading.
    real_change: u8,
    /// Copied from the reading.
    voltage_slow: u8,
    /// Copied from the reading.
    current_over: u8,
    /// 0 off, 1 on.
    output: u8,
}

/// Checks that a copied field is within the bounds the firmware applies.
fn bounded(field: &'static str, value: u16, max: u16) -> Result<(), Error> {
    if value > max {
        return Err(Error::Protocol(Reason::Value {
            field,
            value: i64::from(value),
        }));
    }
    Ok(())
}

impl Command {
    /// Copies the supply's state from `reading` with `remoteCon = 1`. Fails
    /// unless the reading is in DC mode and its fields are within the bounds
    /// the firmware itself applies, so that a copied value can never make
    /// the supply apply part of a command and reject the rest.
    ///
    /// # Errors
    ///
    /// [`Error::Mode`] for a reading in another mode; [`Error::Protocol`] with
    /// [`Reason::Value`] for a field out of bounds.
    pub fn from_reading(reading: &RawReading) -> Result<Self, Error> {
        if reading.model != 0 {
            return Err(Error::Mode {
                live_mode: reading.model,
            });
        }
        bounded("setVoltage", reading.set_voltage, DEVICE_MAX_VOLTAGE)?;
        bounded("setCurrent", reading.set_current, DEVICE_MAX_CURRENT)?;
        bounded("realChange", u16::from(reading.real_change), 3)?;
        bounded("voltageSlow", u16::from(reading.voltage_slow), 1)?;
        bounded("currentOver", u16::from(reading.current_over), 1)?;
        bounded("output", u16::from(reading.output), 1)?;
        Ok(Self {
            remote_con: RemoteCon::Active,
            set_voltage: reading.set_voltage,
            set_current: reading.set_current,
            real_change: reading.real_change,
            voltage_slow: reading.voltage_slow,
            current_over: reading.current_over,
            output: reading.output,
        })
    }

    /// Sets the `remoteCon` byte.
    #[must_use]
    pub fn remote_con(mut self, remote_con: RemoteCon) -> Self {
        self.remote_con = remote_con;
        self
    }

    /// Sets the voltage setpoint.
    #[must_use]
    pub fn set_voltage(mut self, voltage: RawVoltage) -> Self {
        self.set_voltage = voltage.raw();
        self
    }

    /// Sets the current limit.
    #[must_use]
    pub fn set_current(mut self, current: RawCurrent) -> Self {
        self.set_current = current.raw();
        self
    }

    /// Sets the output state.
    #[must_use]
    pub fn output(mut self, on: bool) -> Self {
        self.output = u8::from(on);
        self
    }

    /// The `0xC8` frame.
    #[must_use]
    pub fn encode(&self) -> Frame {
        let mut payload = Vec::with_capacity(LEN);
        payload.push(self.remote_con as u8);
        payload.extend_from_slice(&self.set_voltage.to_le_bytes());
        payload.extend_from_slice(&self.set_current.to_le_bytes());
        payload.extend_from_slice(&[
            self.real_change,
            self.voltage_slow,
            self.current_over,
            self.output,
            0,
            0,
        ]);
        // 11 bytes never exceed the frame's limit.
        Frame::new(REQUEST, payload).unwrap_or_else(|_| Frame::empty(REQUEST))
    }
}

/// The device's answer to a `0xC8`.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum ControlReply {
    /// 0: accepted, or the request stored.
    Accepted,
    /// 1: remote control is not granted, or the deferred "denied" reply.
    NotGranted,
    /// `0xFF`: rejected (mode, range, fault or busy).
    Rejected,
    /// Any other status byte.
    Other(u8),
}

/// Parses a `0xC9` reply.
///
/// # Errors
///
/// [`Reason::WrongOpcode`] or a length error.
pub fn parse(frame: &Frame) -> Result<ControlReply, Reason> {
    let payload = expect_reply(frame, REPLY, 1)?;
    Ok(match payload.first().copied().unwrap_or(0) {
        0x00 => ControlReply::Accepted,
        0x01 => ControlReply::NotGranted,
        0xFF => ControlReply::Rejected,
        other => ControlReply::Other(other),
    })
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::error::Error;
    use crate::protocol::error::Reason;
    use crate::protocol::frame::Frame;
    use crate::protocol::ops::telemetry::tests::capture_reading;
    use crate::protocol::units::{RawCurrent, RawVoltage};

    /// Test: UT-PROTO-027
    #[test]
    fn command_copies_the_reading_and_changes_one_field() {
        let reading = capture_reading();
        let base = [
            0x01, 0x14, 0x05, 0xE8, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
        ];
        let plain = Command::from_reading(&reading).unwrap().encode();
        assert_eq!((plain.opcode(), plain.payload()), (0xC8, &base[..]));
        let volt = Command::from_reading(&reading)
            .unwrap()
            .set_voltage(RawVoltage::for_tests(170))
            .encode();
        assert_eq!(
            volt.payload(),
            &[0x01, 0xAA, 0x00, 0xE8, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00]
        );
        let on = Command::from_reading(&reading)
            .unwrap()
            .output(true)
            .encode();
        assert_eq!(
            on.payload(),
            &[0x01, 0x14, 0x05, 0xE8, 0x03, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00]
        );
        let amp = Command::from_reading(&reading)
            .unwrap()
            .set_current(RawCurrent::for_tests(5000))
            .encode();
        assert_eq!(
            amp.payload(),
            &[0x01, 0x14, 0x05, 0x88, 0x13, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00]
        );
        let req = Command::from_reading(&reading)
            .unwrap()
            .remote_con(RemoteCon::Request)
            .encode();
        assert_eq!(
            req.payload(),
            &[0x02, 0x14, 0x05, 0xE8, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00]
        );
    }

    /// Test: UT-PROTO-027
    #[test]
    fn from_reading_refuses_other_modes_and_out_of_bounds_flags() {
        let mut pd = capture_reading();
        pd.model = 2;
        assert!(matches!(
            Command::from_reading(&pd),
            Err(Error::Mode { .. })
        ));
        let mut flag = capture_reading();
        flag.real_change = 4;
        assert!(matches!(
            Command::from_reading(&flag),
            Err(Error::Protocol(Reason::Value {
                field: "realChange",
                value: 4
            }))
        ));
        let mut high = capture_reading();
        high.set_voltage = 3051;
        assert!(matches!(
            Command::from_reading(&high),
            Err(Error::Protocol(Reason::Value {
                field: "setVoltage",
                value: 3051
            }))
        ));
        let mut top = capture_reading();
        top.set_voltage = 3050;
        top.set_current = 5100;
        assert!(Command::from_reading(&top).is_ok());
    }

    /// Test: UT-PROTO-028
    #[test]
    fn parse_maps_the_status_byte() {
        let p = |b: &[u8]| parse(&Frame::new(0xC9, b.to_vec()).unwrap());
        assert_eq!(p(&[0x00]).unwrap(), ControlReply::Accepted);
        assert_eq!(p(&[0x01]).unwrap(), ControlReply::NotGranted);
        assert_eq!(p(&[0xFF]).unwrap(), ControlReply::Rejected);
        assert_eq!(p(&[0x07]).unwrap(), ControlReply::Other(7));
        assert_eq!(p(&[]).unwrap_err(), Reason::Short { needed: 1, got: 0 });
    }
}
