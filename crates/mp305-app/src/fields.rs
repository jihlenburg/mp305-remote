//! Implements: DD-APP-013.
//!
//! The setpoint and limit fields. A field is parsed with the core's own
//! conversion (`RawVoltage::from_volts`, `RawCurrent::from_amps`), so the
//! field and the session (SR-024) cannot disagree at a rounding edge, and
//! a value outside the supply's range or the user's limits is refused in
//! the field with the core's text. Nothing is sent while typing.

use mp305_core::protocol::units::{
    self, RawCurrent, RawVoltage, SUPPLY_MAX_RAW_CURRENT, SUPPLY_MAX_RAW_VOLTAGE,
};

use crate::model::Limits;
use crate::texts;

/// Which field.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum FieldKind {
    /// The voltage setpoint.
    Voltage,
    /// The current limit.
    Current,
    /// The user's maximum voltage.
    MaxVoltage,
    /// The user's maximum current.
    MaxCurrent,
}

/// What a field's text parses to.
#[derive(Clone, Debug, PartialEq)]
pub enum FieldState {
    /// Nothing typed.
    Empty,
    /// A value within range.
    Valid {
        /// The value in V or A.
        value: f64,
        /// The value in the device's raw steps (10 mV or 1 mA).
        raw: u16,
    },
    /// Not a value, or out of range; the text says why.
    Invalid(String),
}

/// One field.
#[derive(Clone, Debug, PartialEq)]
pub struct Field {
    /// The text in the field.
    pub text: String,
    /// What the text parses to.
    pub state: FieldState,
    /// Whether the user typed into it since it last followed the supply.
    pub edited: bool,
}

impl Default for Field {
    fn default() -> Self {
        Field {
            text: String::new(),
            state: FieldState::Empty,
            edited: false,
        }
    }
}

/// Parses `text` for `kind` under `limits` (DD-APP-013): the text is
/// trimmed; empty is `Empty`; a `,` is refused with
/// [`texts::DECIMAL_POINT`]; the rest must be an optional sign, digits and
/// at most one `.` with at least one digit, else [`texts::NOT_A_NUMBER`]
/// (so `1e1`, `nan` and `inf` are refused); the number then goes through
/// the core's conversion, under `limits` for a setpoint and under no
/// limits for a limit field, and a refusal carries the core's text.
#[must_use]
pub fn parse(text: &str, kind: FieldKind, limits: &Limits) -> FieldState {
    let text = text.trim();
    if text.is_empty() {
        return FieldState::Empty;
    }
    if text.contains(',') {
        return FieldState::Invalid(texts::DECIMAL_POINT.to_string());
    }
    if !is_decimal(text) {
        return FieldState::Invalid(texts::NOT_A_NUMBER.to_string());
    }
    let Ok(value) = text.parse::<f64>() else {
        return FieldState::Invalid(texts::NOT_A_NUMBER.to_string());
    };
    let none = Limits::none();
    let raw = match kind {
        FieldKind::Voltage => RawVoltage::from_volts(value, limits).map(RawVoltage::raw),
        FieldKind::Current => RawCurrent::from_amps(value, limits).map(RawCurrent::raw),
        FieldKind::MaxVoltage => RawVoltage::from_volts(value, &none).map(RawVoltage::raw),
        FieldKind::MaxCurrent => RawCurrent::from_amps(value, &none).map(RawCurrent::raw),
    };
    match raw {
        Ok(raw) => FieldState::Valid { value, raw },
        Err(e) => FieldState::Invalid(e.to_string()),
    }
}

/// Whether `text` is an optional `+` or `-`, then digits and at most one
/// `.`, with at least one digit.
fn is_decimal(text: &str) -> bool {
    let body = text.strip_prefix(['+', '-']).unwrap_or(text);
    let mut digit = false;
    let mut points = 0u8;
    for c in body.chars() {
        if c.is_ascii_digit() {
            digit = true;
        } else if c == '.' {
            points = points.saturating_add(1);
        } else {
            return false;
        }
    }
    digit && points <= 1
}

/// Whether `kind` is a voltage field.
fn is_voltage(kind: FieldKind) -> bool {
    matches!(kind, FieldKind::Voltage | FieldKind::MaxVoltage)
}

/// A raw value at the device's resolution: `13.00` for a voltage (10 mV
/// steps), `1.000` for a current (1 mA steps), by integer division.
#[must_use]
pub fn display(kind: FieldKind, raw: u16) -> String {
    if is_voltage(kind) {
        format!("{}.{:02}", raw / 100, raw % 100)
    } else {
        format!("{}.{:03}", raw / 1_000, raw % 1_000)
    }
}

impl Field {
    /// The range hint of a field under `limits`: `0 to 30 V` or `0 to 5 A`,
    /// followed by `, your limit <n> V` (or `A`) when that limit is set;
    /// `, empty for no limit` for the limit fields.
    #[must_use]
    pub fn hint(kind: FieldKind, limits: &Limits) -> String {
        let volts = units::volts(SUPPLY_MAX_RAW_VOLTAGE);
        let amps = units::amps(SUPPLY_MAX_RAW_CURRENT);
        match kind {
            FieldKind::Voltage => match limits.max_volts {
                Some(v) => format!("0 to {volts} V, your limit {v} V"),
                None => format!("0 to {volts} V"),
            },
            FieldKind::Current => match limits.max_amps {
                Some(a) => format!("0 to {amps} A, your limit {a} A"),
                None => format!("0 to {amps} A"),
            },
            FieldKind::MaxVoltage => format!("0 to {volts} V, empty for no limit"),
            FieldKind::MaxCurrent => format!("0 to {amps} A, empty for no limit"),
        }
    }

    /// The user typed `text`: re-parsed and marked edited.
    pub fn edit(&mut self, text: String, kind: FieldKind, limits: &Limits) {
        self.state = parse(&text, kind, limits);
        self.text = text;
        self.edited = true;
    }

    /// Re-parses the text under `limits`, keeping `edited`.
    pub fn reparse(&mut self, kind: FieldKind, limits: &Limits) {
        self.state = parse(&self.text, kind, limits);
    }

    /// The supply reports the raw setpoint `raw`: an edited field that
    /// holds it stops being edited, then a field that is not edited shows
    /// it.
    pub fn follow(&mut self, kind: FieldKind, raw: u16, limits: &Limits) {
        if self.edited && matches!(self.state, FieldState::Valid { raw: held, .. } if held == raw) {
            self.edited = false;
        }
        if !self.edited {
            self.text = display(kind, raw);
            self.state = parse(&self.text, kind, limits);
        }
    }

    /// Empties the field and clears `edited`.
    pub fn reset(&mut self) {
        *self = Field::default();
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// A valid state with `raw`, whatever the value.
    fn raw_of(state: &FieldState) -> Option<u16> {
        match state {
            FieldState::Valid { raw, .. } => Some(*raw),
            _ => None,
        }
    }

    /// An invalid state with `text`.
    fn invalid(text: &str) -> FieldState {
        FieldState::Invalid(text.to_string())
    }

    /// Test: UT-APP-002
    #[test]
    fn parse_of_voltages_without_limits() {
        let none = Limits::none();
        let v = |text: &str| parse(text, FieldKind::Voltage, &none);
        assert_eq!(v(""), FieldState::Empty);
        assert_eq!(raw_of(&v("4.5")), Some(450));
        assert_eq!(raw_of(&v(" 4.5 ")), Some(450));
        assert_eq!(raw_of(&v("+4.5")), Some(450));
        assert_eq!(raw_of(&v("4.")), Some(400));
        assert_eq!(raw_of(&v(".5")), Some(50));
        assert_eq!(v("4,5"), invalid("use . as the decimal point"));
        for text in ["abc", ".", "4.5.1", "nan", "1e1"] {
            assert_eq!(v(text), invalid("not a number"), "{text}");
        }
        assert_eq!(v("-1"), invalid("voltage -1 is outside 0 to 30"));
        assert_eq!(raw_of(&v("30")), Some(3000));
        assert_eq!(raw_of(&v("30.004")), Some(3000));
        assert_eq!(v("30.005"), invalid("voltage 30.005 is outside 0 to 30"));
        assert_eq!(v("30.01"), invalid("voltage 30.01 is outside 0 to 30"));
        assert_eq!(raw_of(&v("4.567")), Some(457));
        assert_eq!(raw_of(&v("1.005")), Some(101));
    }

    /// Test: UT-APP-002
    #[test]
    fn parse_under_limits_of_currents_and_of_the_limit_fields() {
        let five = Limits {
            max_volts: Some(5.0),
            max_amps: None,
        };
        let v = |text: &str| parse(text, FieldKind::Voltage, &five);
        assert_eq!(raw_of(&v("5")), Some(500));
        assert_eq!(raw_of(&v("5.004")), Some(500));
        assert_eq!(v("5.01"), invalid("voltage 5.01 is outside 0 to 5"));
        let none = Limits::none();
        let a = |text: &str| parse(text, FieldKind::Current, &none);
        assert_eq!(a("5.001"), invalid("current 5.001 is outside 0 to 5"));
        assert_eq!(raw_of(&a("0.1234")), Some(123));
        assert_eq!(raw_of(&a("0.1235")), Some(124));
        // The limit fields take no limits of their own.
        assert_eq!(
            parse("31", FieldKind::MaxVoltage, &five),
            invalid("voltage 31 is outside 0 to 30")
        );
        assert_eq!(
            parse("12", FieldKind::MaxVoltage, &five),
            FieldState::Valid {
                value: 12.0,
                raw: 1200
            }
        );
    }

    /// Test: UT-APP-002
    #[test]
    fn display_and_hints() {
        assert_eq!(display(FieldKind::Voltage, 457), "4.57");
        assert_eq!(display(FieldKind::Current, 100), "0.100");
        let twelve = Limits {
            max_volts: Some(12.0),
            max_amps: None,
        };
        assert_eq!(
            Field::hint(FieldKind::Voltage, &twelve),
            "0 to 30 V, your limit 12 V"
        );
        assert_eq!(Field::hint(FieldKind::Current, &Limits::none()), "0 to 5 A");
        assert_eq!(
            Field::hint(FieldKind::MaxVoltage, &twelve),
            "0 to 30 V, empty for no limit"
        );
        assert_eq!(
            Field::hint(FieldKind::MaxCurrent, &twelve),
            "0 to 5 A, empty for no limit"
        );
        let both = Limits {
            max_volts: None,
            max_amps: Some(1.5),
        };
        assert_eq!(
            Field::hint(FieldKind::Current, &both),
            "0 to 5 A, your limit 1.5 A"
        );
    }
}
