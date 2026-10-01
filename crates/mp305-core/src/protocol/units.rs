//! Conversions between the device's raw units and SI units, and setpoint
//! validation.
//!
//! Implements: DD-PROTO-050, DD-PROTO-051, DD-PROTO-052.

use crate::error::Error;

/// The supply's voltage range as a raw value: 0 to 30.00 V. The firmware
/// itself accepts up to 3050 (30.50 V, device-model.md 9); the rated value
/// is used until TBD-003 settles what the output does above it.
pub const SUPPLY_MAX_RAW_VOLTAGE: u16 = 3000;
/// The supply's current range as a raw value: 0 to 5.000 A. The firmware
/// accepts up to 5100 (5.100 A); see [`SUPPLY_MAX_RAW_VOLTAGE`].
pub const SUPPLY_MAX_RAW_CURRENT: u16 = 5000;

/// The user's own limits (UR-007), applied on top of the supply's range.
#[derive(Clone, Copy, Debug, PartialEq, Default)]
pub struct Limits {
    /// The highest voltage the user allows, in V.
    pub max_volts: Option<f64>,
    /// The highest current limit the user allows, in A.
    pub max_amps: Option<f64>,
}

impl Limits {
    /// No user limits.
    #[must_use]
    pub fn none() -> Self {
        Self::default()
    }
}

/// A voltage setpoint in the device's 10 mV steps, within range.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct RawVoltage(u16);

/// A current limit in the device's 1 mA steps, within range.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct RawCurrent(u16);

/// The scale of a raw voltage: raw 10 mV steps per volt.
pub(crate) const VOLT_SCALE: f64 = 100.0;
/// The scale of a raw current: raw 1 mA steps per ampere.
pub(crate) const AMP_SCALE: f64 = 1000.0;

/// Scales `value` by `scale`, rounds to six decimals first and then to the
/// nearest integer with halves away from zero. The pre-rounding removes
/// binary-float artefacts such as `1.005 * 100 = 100.49999999999999`. The
/// session uses it to hold a copied raw setpoint against a user limit
/// through the same path as a value the user names.
pub(crate) fn to_raw(value: f64, scale: f64) -> f64 {
    ((value * scale * 1e6).round() / 1e6).round()
}

/// Validates `value` (finite, not negative, at most `supply_max` raw units,
/// at most `user_max`) and returns the raw value.
fn validate(
    field: &'static str,
    value: f64,
    scale: f64,
    supply_max: u16,
    user_max: Option<f64>,
) -> Result<u16, Error> {
    let supply_max_si = f64::from(supply_max) / scale;
    let range = |max: f64| Error::SetpointRange {
        field,
        value,
        min: 0.0,
        max,
    };
    if !value.is_finite() || value < 0.0 {
        return Err(range(supply_max_si));
    }
    let raw = to_raw(value, scale);
    if raw > f64::from(supply_max) {
        return Err(range(supply_max_si));
    }
    if let Some(max) = user_max {
        if raw > to_raw(max, scale) {
            return Err(range(max));
        }
    }
    // `raw` is a non-negative integer at most `supply_max`, so the cast is exact.
    #[allow(clippy::cast_possible_truncation, clippy::cast_sign_loss)]
    Ok(raw as u16)
}

impl RawVoltage {
    /// Converts volts to raw 10 mV steps, rejecting values that are not
    /// finite, negative, above the supply's range or above `limits`.
    ///
    /// # Errors
    ///
    /// [`Error::SetpointRange`] with the field `voltage`.
    pub fn from_volts(volts: f64, limits: &Limits) -> Result<Self, Error> {
        validate(
            "voltage",
            volts,
            VOLT_SCALE,
            SUPPLY_MAX_RAW_VOLTAGE,
            limits.max_volts,
        )
        .map(Self)
    }

    /// The raw 10 mV value.
    #[must_use]
    pub fn raw(self) -> u16 {
        self.0
    }

    /// A raw value without validation, for tests only.
    #[cfg(test)]
    pub(crate) fn for_tests(raw: u16) -> Self {
        Self(raw)
    }
}

impl RawCurrent {
    /// Converts amperes to raw 1 mA steps, with the checks of
    /// [`RawVoltage::from_volts`].
    ///
    /// # Errors
    ///
    /// [`Error::SetpointRange`] with the field `current`.
    pub fn from_amps(amps: f64, limits: &Limits) -> Result<Self, Error> {
        validate(
            "current",
            amps,
            AMP_SCALE,
            SUPPLY_MAX_RAW_CURRENT,
            limits.max_amps,
        )
        .map(Self)
    }

    /// The raw 1 mA value.
    #[must_use]
    pub fn raw(self) -> u16 {
        self.0
    }

    /// A raw value without validation, for tests only.
    #[cfg(test)]
    pub(crate) fn for_tests(raw: u16) -> Self {
        Self(raw)
    }
}

/// Volts from a raw 10 mV value.
#[must_use]
pub fn volts(raw: u16) -> f64 {
    f64::from(raw) / VOLT_SCALE
}

/// Amperes from a raw 1 mA value.
#[must_use]
pub fn amps(raw: u16) -> f64 {
    f64::from(raw) / AMP_SCALE
}

/// Watts from a raw 10 mW value.
#[must_use]
pub fn watts(raw: u16) -> f64 {
    f64::from(raw) / 100.0
}

/// Watt-hours from a raw 0.1 Wh value.
#[must_use]
pub fn watt_hours(raw: u32) -> f64 {
    f64::from(raw) / 10.0
}

/// Seconds from the raw working time, which is already in seconds.
#[must_use]
pub fn seconds(raw: u32) -> u32 {
    raw
}

/// Degrees Celsius from the raw signed byte, which is already in °C.
#[must_use]
pub fn celsius(raw: i8) -> i8 {
    raw
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::error::Error;

    /// Test: UT-PROTO-050
    #[test]
    fn raw_to_si() {
        assert_eq!(volts(1300), 13.0);
        assert_eq!(amps(1000), 1.0);
        assert_eq!(watts(25), 0.25);
        assert_eq!(watt_hours(123), 12.3);
        assert_eq!(seconds(3600), 3600);
        assert_eq!(celsius(-6), -6);
    }

    /// Test: UT-PROTO-051
    #[test]
    fn voltage_setpoints_are_validated_and_rounded() {
        let none = Limits::none();
        for bad in [f64::NAN, f64::INFINITY, -0.01, 30.005] {
            assert!(
                matches!(
                    RawVoltage::from_volts(bad, &none),
                    Err(Error::SetpointRange {
                        field: "voltage",
                        ..
                    })
                ),
                "{bad}"
            );
        }
        assert_eq!(RawVoltage::from_volts(30.004, &none).unwrap().raw(), 3000);
        assert_eq!(RawVoltage::from_volts(1.004, &none).unwrap().raw(), 100);
        assert_eq!(RawVoltage::from_volts(1.005, &none).unwrap().raw(), 101);
        assert_eq!(RawVoltage::from_volts(1.006, &none).unwrap().raw(), 101);
        let user = Limits {
            max_volts: Some(4.0),
            max_amps: None,
        };
        assert!(
            matches!(RawVoltage::from_volts(4.5, &user), Err(Error::SetpointRange { field: "voltage", max, .. }) if max == 4.0)
        );
        assert_eq!(RawVoltage::from_volts(4.0, &user).unwrap().raw(), 400);
    }

    /// Test: UT-PROTO-051
    #[test]
    fn current_setpoints_are_validated_and_rounded() {
        let none = Limits::none();
        assert_eq!(RawCurrent::from_amps(1.0004, &none).unwrap().raw(), 1000);
        assert_eq!(RawCurrent::from_amps(1.0005, &none).unwrap().raw(), 1001);
        assert_eq!(RawCurrent::from_amps(5.0004, &none).unwrap().raw(), 5000);
        assert!(matches!(
            RawCurrent::from_amps(5.0005, &none),
            Err(Error::SetpointRange {
                field: "current",
                ..
            })
        ));
        let user = Limits {
            max_volts: None,
            max_amps: Some(0.05),
        };
        assert!(matches!(
            RawCurrent::from_amps(0.06, &user),
            Err(Error::SetpointRange {
                field: "current",
                ..
            })
        ));
        assert_eq!(SUPPLY_MAX_RAW_VOLTAGE, 3000);
        assert_eq!(SUPPLY_MAX_RAW_CURRENT, 5000);
    }
}
