//! Integration test IT-013 (AR-013): `protocol::units` converts the raw
//! fixtures to SI units, alone and through a parsed `0xC3`, and validates
//! and rounds setpoints against the supply's range and a user limit.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    clippy::float_cmp,
    missing_docs
)]

use mp305_core::error::Error;
use mp305_core::protocol::ops::telemetry::{self, Reading};
use mp305_core::protocol::units::{self, Limits, RawCurrent, RawVoltage};

/// `2026-09-29T193614-ble-readonly.jsonl`, t = 12.8857, RX on AF01: the
/// payload of the first `0xC3` (`C3_CAPTURE`), the base the fixture
/// fields are written into.
const C3_CAPTURE: [u8; 36] = [
    0x00, 0x00, 0x5A, 0x00, 0x00, 0x14, 0x05, 0x00, 0x00, 0xE8, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1A, 0x00, 0x00, 0x01,
    0x40, 0x06, 0x00, 0x00,
];

/// Test: IT-013
#[test]
fn the_raw_fixtures_convert_to_si_units() {
    // The conversions one by one.
    assert_eq!(units::volts(1300), 13.0);
    assert_eq!(units::amps(1000), 1.0);
    assert_eq!(units::watts(25), 0.25);
    assert_eq!(units::watt_hours(123), 12.3);
    assert_eq!(units::seconds(3600), 3600);
    assert_eq!(units::celsius(i8::from_le_bytes([0xFA])), -6);

    // The same fixtures in their fields of a 0xC3 payload (protocol.md
    // 4.1), parsed and converted as the session does.
    let mut payload = C3_CAPTURE;
    payload[3..5].copy_from_slice(&1300u16.to_le_bytes());
    payload[7..9].copy_from_slice(&1000u16.to_le_bytes());
    payload[11..15].copy_from_slice(&3600u32.to_le_bytes());
    payload[15..19].copy_from_slice(&123u32.to_le_bytes());
    payload[19..21].copy_from_slice(&25u16.to_le_bytes());
    payload[28] = 0xFA;
    let reading = Reading::from_raw(&telemetry::parse_payload(&payload).unwrap());
    assert_eq!(reading.volts, 13.0);
    assert_eq!(reading.amps, 1.0);
    assert_eq!(reading.watts, 0.25);
    assert_eq!(reading.temperature_c, -6);
    assert_eq!(reading.watt_hours, 12.3);
    assert_eq!(reading.working_time_s, 3600);
}

/// Test: IT-013
#[test]
fn setpoints_are_validated_and_rounded_halves_away_from_zero() {
    let none = Limits::none();
    for bad in [f64::NAN, f64::INFINITY, -0.01, 30.01] {
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
    let raw = |v: f64| RawVoltage::from_volts(v, &none).unwrap().raw();
    assert_eq!((raw(1.004), raw(1.005), raw(1.006)), (100, 101, 101));

    let raw = |a: f64| RawCurrent::from_amps(a, &none).unwrap().raw();
    assert_eq!((raw(1.0004), raw(1.0005)), (1000, 1001));
    assert!(matches!(
        RawCurrent::from_amps(5.001, &none),
        Err(Error::SetpointRange {
            field: "current",
            ..
        })
    ));

    let user = Limits {
        max_volts: Some(4.0),
        max_amps: None,
    };
    assert_eq!(
        RawVoltage::from_volts(4.01, &user),
        Err(Error::SetpointRange {
            field: "voltage",
            value: 4.01,
            min: 0.0,
            max: 4.0
        })
    );
}
