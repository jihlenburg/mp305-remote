//! Telemetry request `0xC2` and reply `0xC3`, its raw and its SI view, the
//! regulation and live modes and the fault bits.
//!
//! Implements: DD-PROTO-024, DD-PROTO-025, DD-PROTO-026, DD-PROTO-027, DD-PROTO-053.

use core::fmt;

use crate::protocol::error::Reason;
use crate::protocol::frame::Frame;
use crate::protocol::ops::{expect_reply, u16_at, u32_at, u8_at};
use crate::protocol::units;

/// The telemetry request opcode.
pub const REQUEST: u8 = 0xC2;
/// The telemetry reply opcode.
pub const REPLY: u8 = 0xC3;
/// Payload length of the reply.
pub const LEN: usize = 36;

/// The `0xC3` payload with every field as the raw integer the device sent.
///
/// | Offset | Type | Field | Raw unit |
/// |---|---|---|---|
/// | 0 | u8 | `out_state` | 0 off, 1 CV, 2 CC, 3 held above setpoint |
/// | 1 | u8 | `battery_state` | 0 on battery, 1 external input, 2 charge held |
/// | 2 | u8 | `percentage` | % |
/// | 3 | u16 | `voltage` | 10 mV |
/// | 5 | u16 | `set_voltage` | 10 mV |
/// | 7 | u16 | `current` | 1 mA |
/// | 9 | u16 | `set_current` | 1 mA |
/// | 11 | u32 | `working_time` | s |
/// | 15 | u32 | `energy` | 0.1 Wh |
/// | 19 | u16 | `power` | 10 mW |
/// | 21 | u8 | `current_over` | 0 limit, 1 trip |
/// | 22 | u8 | `real_change` | bit 0 voltage, bit 1 current |
/// | 23 | u8 | `voltage_slow` | 0 step, 1 ramp |
/// | 24 | u8 | `output` | 0 off, 1 on |
/// | 25 | u8 | `model` | 0 DC, 1 program, 2 PD, 3 charge |
/// | 26 | u8 | `voltage_board` | UI flag |
/// | 27 | u8 | `current_board` | UI flag |
/// | 28 | i8 | `temperature` | °C |
/// | 29 | u16 | `charge_error` | fault bits |
/// | 31 | u8 | `wave_pause` | raw |
/// | 32 | u32 | `wave_time` | ms |
///
/// See docs/research/protocol.md, section 4.1.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct RawReading {
    /// Regulation state: 0 off, 1 CV, 2 CC, 3 held above the setpoint.
    pub out_state: u8,
    /// 0 on battery, 1 external input charging, 2 charge held.
    pub battery_state: u8,
    /// Internal battery state of charge, percent.
    pub percentage: u8,
    /// Measured output voltage, 10 mV.
    pub voltage: u16,
    /// Voltage setpoint, 10 mV.
    pub set_voltage: u16,
    /// Measured output current, 1 mA.
    pub current: u16,
    /// Current limit, 1 mA.
    pub set_current: u16,
    /// Output-on time, seconds.
    pub working_time: u32,
    /// Energy delivered, 0.1 Wh.
    pub energy: u32,
    /// Output power, 10 mW.
    pub power: u16,
    /// 0 constant-current limit, 1 trip after the OCP delay.
    pub current_over: u8,
    /// Bit 0 voltage, bit 1 current: front-panel edits apply live.
    pub real_change: u8,
    /// 0 step, 1 ramp at the ramp step.
    pub voltage_slow: u8,
    /// 0 off, 1 on (the actual power-stage state).
    pub output: u8,
    /// Live mode: 0 DC, 1 program, 2 PD, 3 charge.
    pub model: u8,
    /// UI entry-mode flag, kept raw.
    pub voltage_board: u8,
    /// UI entry-mode flag, kept raw.
    pub current_board: u8,
    /// Battery protection temperature, °C.
    pub temperature: i8,
    /// Fault bits, see [`Faults`].
    pub charge_error: u16,
    /// Kept raw; 1 in every state found.
    pub wave_pause: u8,
    /// Raw output-on time in ms.
    pub wave_time: u32,
    /// The 36 payload bytes as received.
    pub raw: [u8; LEN],
}

/// The telemetry request: `0xC2` with no payload.
#[must_use]
pub fn request() -> Frame {
    Frame::empty(REQUEST)
}

/// Parses a `0xC3` reply.
///
/// # Errors
///
/// [`Reason::WrongOpcode`] or a length error.
pub fn parse(frame: &Frame) -> Result<RawReading, Reason> {
    let p = expect_reply(frame, REPLY, LEN)?;
    let mut raw = [0u8; LEN];
    raw.copy_from_slice(p);
    // The byte reinterpreted as a two's-complement signed value.
    let temperature = i8::from_le_bytes([u8_at(p, 28)]);
    Ok(RawReading {
        out_state: u8_at(p, 0),
        battery_state: u8_at(p, 1),
        percentage: u8_at(p, 2),
        voltage: u16_at(p, 3),
        set_voltage: u16_at(p, 5),
        current: u16_at(p, 7),
        set_current: u16_at(p, 9),
        working_time: u32_at(p, 11),
        energy: u32_at(p, 15),
        power: u16_at(p, 19),
        current_over: u8_at(p, 21),
        real_change: u8_at(p, 22),
        voltage_slow: u8_at(p, 23),
        output: u8_at(p, 24),
        model: u8_at(p, 25),
        voltage_board: u8_at(p, 26),
        current_board: u8_at(p, 27),
        temperature,
        charge_error: u16_at(p, 29),
        wave_pause: u8_at(p, 31),
        wave_time: u32_at(p, 32),
        raw,
    })
}

/// How the output is regulating, from `out_state`.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum RegulationMode {
    /// 0: the output is off.
    Off,
    /// 1: constant voltage.
    Cv,
    /// 2: constant current.
    Cc,
    /// 3: the measured voltage is held above the setpoint at low current
    /// (inferred, device-model.md 8).
    HeldAboveSetpoint,
    /// Any other value.
    Unknown(u8),
}

impl RegulationMode {
    /// Maps the raw `out_state` byte.
    #[must_use]
    pub fn from_raw(raw: u8) -> Self {
        match raw {
            0 => Self::Off,
            1 => Self::Cv,
            2 => Self::Cc,
            3 => Self::HeldAboveSetpoint,
            other => Self::Unknown(other),
        }
    }
}

impl fmt::Display for RegulationMode {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::Off => write!(f, "off"),
            Self::Cv => write!(f, "CV"),
            Self::Cc => write!(f, "CC"),
            Self::HeldAboveSetpoint => write!(f, "held above setpoint"),
            Self::Unknown(v) => write!(f, "unknown ({v})"),
        }
    }
}

/// The supply's live mode, from `model`.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum LiveMode {
    /// 0: DC supply, the only mode v1 controls.
    Dc,
    /// 1: program mode.
    Program,
    /// 2: USB-PD source mode.
    Pd,
    /// 3: charger mode.
    Charge,
    /// Any other value.
    Unknown(u8),
}

impl LiveMode {
    /// Maps the raw `model` byte.
    #[must_use]
    pub fn from_raw(raw: u8) -> Self {
        match raw {
            0 => Self::Dc,
            1 => Self::Program,
            2 => Self::Pd,
            3 => Self::Charge,
            other => Self::Unknown(other),
        }
    }
}

impl fmt::Display for LiveMode {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::Dc => write!(f, "DC"),
            Self::Program => write!(f, "program"),
            Self::Pd => write!(f, "PD"),
            Self::Charge => write!(f, "charge"),
            Self::Unknown(v) => write!(f, "unknown ({v})"),
        }
    }
}

/// One fault bit of `charge_error` (device-model.md 8, bits 0 to 8; the
/// device never sets bits 9 to 15 in `0xC3`).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Fault {
    /// Bit 0: the output is connected in reverse.
    ReversedOutput,
    /// Bit 1: the internal battery is low.
    LowBattery,
    /// Bit 2: the battery is too cold.
    BatteryTooCold,
    /// Bit 3: the battery is overheating.
    BatteryOverheat,
    /// Bit 4: the power stage is overheating.
    SystemOverheat,
    /// Bit 5: over-current, tripped after the OCP delay in OCP mode.
    OverCurrent,
    /// Bit 6: over-voltage.
    OverVoltage,
    /// Bit 7: the power stage failed to start.
    PowerStageStart,
    /// Bit 8: the two output voltage measurements disagree.
    OutputVoltageSensor,
    /// A bit the firmware does not define (9 to 15).
    Unknown(u8),
}

impl Fault {
    /// The fault of bit `bit`.
    fn from_bit(bit: u8) -> Self {
        match bit {
            0 => Self::ReversedOutput,
            1 => Self::LowBattery,
            2 => Self::BatteryTooCold,
            3 => Self::BatteryOverheat,
            4 => Self::SystemOverheat,
            5 => Self::OverCurrent,
            6 => Self::OverVoltage,
            7 => Self::PowerStageStart,
            8 => Self::OutputVoltageSensor,
            other => Self::Unknown(other),
        }
    }
}

impl fmt::Display for Fault {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::ReversedOutput => write!(f, "reversed output"),
            Self::LowBattery => write!(f, "low battery"),
            Self::BatteryTooCold => write!(f, "battery too cold"),
            Self::BatteryOverheat => write!(f, "battery overheat"),
            Self::SystemOverheat => write!(f, "system overheat"),
            Self::OverCurrent => write!(f, "over current"),
            Self::OverVoltage => write!(f, "over voltage"),
            Self::PowerStageStart => write!(f, "power stage start failure"),
            Self::OutputVoltageSensor => write!(f, "output voltage sensor failure"),
            Self::Unknown(bit) => write!(f, "unknown fault bit {bit}"),
        }
    }
}

/// The `charge_error` word.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Default)]
pub struct Faults(pub u16);

impl Faults {
    /// No fault bit set.
    #[must_use]
    pub fn is_empty(&self) -> bool {
        self.0 == 0
    }

    /// The active faults in bit order.
    pub fn iter(&self) -> impl Iterator<Item = Fault> + '_ {
        (0u8..16)
            .filter(move |bit| self.0 & (1u16 << bit) != 0)
            .map(Fault::from_bit)
    }
}

/// The SI view of a reading, without the arrival timestamp (`link` adds it).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Reading {
    /// Measured output voltage in V.
    pub volts: f64,
    /// Voltage setpoint in V.
    pub set_volts: f64,
    /// Measured output current in A.
    pub amps: f64,
    /// Current limit in A.
    pub set_amps: f64,
    /// Output power in W.
    pub watts: f64,
    /// Energy delivered in Wh.
    pub watt_hours: f64,
    /// Output-on time in seconds.
    pub working_time_s: u32,
    /// The regulation mode.
    pub regulation: RegulationMode,
    /// The supply's live mode.
    pub live_mode: LiveMode,
    /// Whether the power stage output is on.
    pub output_on: bool,
    /// The active faults.
    pub faults: Faults,
    /// The battery protection temperature in °C.
    pub temperature_c: i8,
    /// The internal battery's state of charge in percent.
    pub battery_percent: u8,
    /// The raw reading this view was made from.
    pub raw: RawReading,
}

impl Reading {
    /// Converts every field of `raw` through [`units`].
    #[must_use]
    pub fn from_raw(raw: &RawReading) -> Self {
        Self {
            volts: units::volts(raw.voltage),
            set_volts: units::volts(raw.set_voltage),
            amps: units::amps(raw.current),
            set_amps: units::amps(raw.set_current),
            watts: units::watts(raw.power),
            watt_hours: units::watt_hours(raw.energy),
            working_time_s: units::seconds(raw.working_time),
            regulation: RegulationMode::from_raw(raw.out_state),
            live_mode: LiveMode::from_raw(raw.model),
            output_on: raw.output != 0,
            faults: Faults(raw.charge_error),
            temperature_c: units::celsius(raw.temperature),
            battery_percent: raw.percentage,
            raw: *raw,
        }
    }
}

#[cfg(test)]
pub(crate) mod tests {
    use super::*;
    use crate::protocol::error::Reason;
    use crate::protocol::frame::Frame;

    /// The payload of the first `0xC3` of `2026-09-29T193614-ble-readonly.jsonl` (t = 12.8857).
    pub(crate) const C3_PAYLOAD: [u8; 36] = [
        0x00, 0x00, 0x5A, 0x00, 0x00, 0x14, 0x05, 0x00, 0x00, 0xE8, 0x03, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1A, 0x00,
        0x00, 0x01, 0x40, 0x06, 0x00, 0x00,
    ];

    pub(crate) fn capture_reading() -> RawReading {
        parse(&Frame::new(0xC3, C3_PAYLOAD.to_vec()).unwrap()).unwrap()
    }

    /// Test: UT-PROTO-024
    #[test]
    fn request_is_an_empty_c2() {
        let f = request();
        assert_eq!((f.opcode(), f.payload()), (0xC2, &[][..]));
    }

    /// Test: UT-PROTO-024
    #[test]
    fn parse_reads_every_field_of_the_capture() {
        let r = capture_reading();
        assert_eq!(r.out_state, 0);
        assert_eq!(r.battery_state, 0);
        assert_eq!(r.percentage, 90);
        assert_eq!(r.voltage, 0);
        assert_eq!(r.set_voltage, 1300);
        assert_eq!(r.current, 0);
        assert_eq!(r.set_current, 1000);
        assert_eq!(r.working_time, 1);
        assert_eq!(r.energy, 0);
        assert_eq!(r.power, 0);
        assert_eq!(r.current_over, 0);
        assert_eq!(r.real_change, 3);
        assert_eq!(r.voltage_slow, 0);
        assert_eq!(r.output, 0);
        assert_eq!(r.model, 0);
        assert_eq!(r.voltage_board, 0);
        assert_eq!(r.current_board, 1);
        assert_eq!(r.temperature, 26);
        assert_eq!(r.charge_error, 0);
        assert_eq!(r.wave_pause, 1);
        assert_eq!(r.wave_time, 1600);
        assert_eq!(r.raw, C3_PAYLOAD);
    }

    /// Test: UT-PROTO-024
    #[test]
    fn parse_reads_a_negative_temperature_and_rejects_other_lengths() {
        let mut cold = C3_PAYLOAD;
        cold[28] = 0xFA;
        assert_eq!(
            parse(&Frame::new(0xC3, cold.to_vec()).unwrap())
                .unwrap()
                .temperature,
            -6
        );
        assert_eq!(
            parse(&Frame::new(0xC3, vec![0; 35]).unwrap()).unwrap_err(),
            Reason::Short {
                needed: 36,
                got: 35
            }
        );
        assert_eq!(
            parse(&Frame::new(0xC3, vec![0; 37]).unwrap()).unwrap_err(),
            Reason::BadLength {
                expected: 36,
                got: 37
            }
        );
        assert_eq!(
            parse(&Frame::new(0xC5, vec![0; 36]).unwrap()).unwrap_err(),
            Reason::WrongOpcode {
                expected: 0xC3,
                got: 0xC5
            }
        );
    }

    /// Test: UT-PROTO-025
    #[test]
    fn modes_map_the_raw_values() {
        let reg: Vec<_> = (0..5).map(RegulationMode::from_raw).collect();
        assert_eq!(
            reg,
            [
                RegulationMode::Off,
                RegulationMode::Cv,
                RegulationMode::Cc,
                RegulationMode::HeldAboveSetpoint,
                RegulationMode::Unknown(4)
            ]
        );
        assert_eq!(
            reg.iter().map(ToString::to_string).collect::<Vec<_>>(),
            ["off", "CV", "CC", "held above setpoint", "unknown (4)"]
        );
        let live: Vec<_> = (0..5).map(LiveMode::from_raw).collect();
        assert_eq!(
            live,
            [
                LiveMode::Dc,
                LiveMode::Program,
                LiveMode::Pd,
                LiveMode::Charge,
                LiveMode::Unknown(4)
            ]
        );
        assert_eq!(
            live.iter().map(ToString::to_string).collect::<Vec<_>>(),
            ["DC", "program", "PD", "charge", "unknown (4)"]
        );
    }

    /// Test: UT-PROTO-026
    #[test]
    fn faults_decode_bits_in_order() {
        assert!(Faults(0).is_empty());
        assert_eq!(Faults(0).iter().count(), 0);
        assert_eq!(
            Faults(0b1_0010_0001).iter().collect::<Vec<_>>(),
            [
                Fault::ReversedOutput,
                Fault::OverCurrent,
                Fault::OutputVoltageSensor
            ]
        );
        assert_eq!(
            Faults(0xFE00).iter().collect::<Vec<_>>(),
            (9..16).map(Fault::Unknown).collect::<Vec<_>>()
        );
        assert_eq!(Fault::OverCurrent.to_string(), "over current");
        assert_eq!(Fault::Unknown(11).to_string(), "unknown fault bit 11");
    }

    /// Test: UT-PROTO-032
    #[test]
    fn reading_from_raw_converts_the_capture() {
        let r = Reading::from_raw(&capture_reading());
        assert_eq!(r.volts, 0.0);
        assert_eq!(r.set_volts, 13.0);
        assert_eq!(r.amps, 0.0);
        assert_eq!(r.set_amps, 1.0);
        assert_eq!(r.watts, 0.0);
        assert_eq!(r.watt_hours, 0.0);
        assert_eq!(r.working_time_s, 1);
        assert_eq!(r.regulation, RegulationMode::Off);
        assert_eq!(r.live_mode, LiveMode::Dc);
        assert!(!r.output_on);
        assert!(r.faults.is_empty());
        assert_eq!(r.temperature_c, 26);
        assert_eq!(r.battery_percent, 90);
        assert_eq!(r.raw.set_voltage, 1300);
    }
}
