//! Integration test IT-011 (AR-011): the typed reply parsers on the capture
//! payloads and the constructed USB `0xE1`, each also truncated by one
//! byte, and the four request builders with every field at its bounds.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    missing_docs
)]

use mp305_core::error::Error;
use mp305_core::protocol::ble::{self, BleRoute};
use mp305_core::protocol::error::Reason;
use mp305_core::protocol::fixtures;
use mp305_core::protocol::frame::Frame;
use mp305_core::protocol::hid::Decoder;
use mp305_core::protocol::ops::bind::{self, HostId};
use mp305_core::protocol::ops::control::{Command, RemoteCon};
use mp305_core::protocol::ops::info::{self, Version};
use mp305_core::protocol::ops::settings;
use mp305_core::protocol::ops::telemetry::{self, RawReading, Reading};
use mp305_core::protocol::units::{Limits, RawCurrent, RawVoltage};

/// `2026-09-29T193614-ble-readonly.jsonl`, t = 12.8857, RX on AF01: the
/// first `0xC3` (`C3_CAPTURE` behind `31 c3`).
const C3_NOTIFICATION: [u8; 38] = [
    0x31, 0xC3, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x14, 0x05, 0x00, 0x00, 0xE8, 0x03, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1A, 0x00,
    0x00, 0x01, 0x40, 0x06, 0x00, 0x00,
];
/// `2026-09-29T193614-ble-readonly.jsonl`, t = 12.7497, RX on AF01: the
/// captured `0xC5` (`c5 5a 02 00 00 01 f4 01 32 00 00 00` behind the tag).
const C5_NOTIFICATION: [u8; 13] = [
    0x31, 0xC5, 0x5A, 0x02, 0x00, 0x00, 0x01, 0xF4, 0x01, 0x32, 0x00, 0x00, 0x00,
];
/// `2026-09-29T193614-ble-readonly.jsonl`, t = 12.6162, RX on AF02: the
/// 17-byte `E1_BLE`.
const E1_BLE_NOTIFICATION: [u8; 17] = [
    0xE1, 0x01, 0x06, 0x00, 0x28, 0x4D, 0x50, 0x33, 0x30, 0x35, 0x42, 0x00, 0x00, 0x02, 0x00, 0x02,
    0x00,
];
/// A constructed fixture, never captured (TBD-010): `E1_USB`, the 31-byte
/// layout of protocol.md 4.4 (opcode and 30 payload bytes): model `MP305B`,
/// eight placeholder bootloader bytes, version `01 06 00 33`, name `MP305B`.
const E1_USB_FRAME: [u8; 31] = [
    0xE1, 0x4D, 0x50, 0x33, 0x30, 0x35, 0x42, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x01, 0x06, 0x00, 0x33, 0x4D, 0x50, 0x33, 0x30, 0x35, 0x42, 0x00, 0x00, 0x00, 0x00,
];

/// Offsets in the `0xC3` payload (protocol.md 4.1) that the bound tests set.
const SET_VOLTAGE: usize = 5;
/// See [`SET_VOLTAGE`].
const SET_CURRENT: usize = 9;
/// See [`SET_VOLTAGE`].
const CURRENT_OVER: usize = 21;
/// See [`SET_VOLTAGE`].
const REAL_CHANGE: usize = 22;
/// See [`SET_VOLTAGE`].
const VOLTAGE_SLOW: usize = 23;
/// See [`SET_VOLTAGE`].
const OUTPUT: usize = 24;

/// The USB `0xE1` as the supply streams it over HID (protocol.md 2.2:
/// address 0x21, the length, the frame, the sum of the unstuffed bytes,
/// every `AA` after the first doubled), decoded by the stream decoder.
fn e1_usb_from_hid(frame_bytes: &[u8]) -> Frame {
    let length = u8::try_from(frame_bytes.len()).unwrap();
    let mut unstuffed = vec![0x21, length];
    unstuffed.extend_from_slice(frame_bytes);
    let sum = unstuffed.iter().fold(0u8, |s, b| s.wrapping_add(*b));
    unstuffed.push(sum);
    let mut stream = vec![0xAA];
    for byte in unstuffed {
        stream.push(byte);
        if byte == 0xAA {
            stream.push(0xAA);
        }
    }
    let mut results = Decoder::new().push(&stream);
    assert_eq!(results.len(), 1);
    results.remove(0).unwrap()
}

/// A parser's error as the crate reports it.
fn protocol_error<T: core::fmt::Debug>(result: Result<T, Reason>) -> Error {
    Error::from(result.unwrap_err())
}

/// Test: IT-011
#[test]
fn the_captured_and_constructed_replies_decode_to_their_values() {
    // The shared fixtures are the bytes inlined here.
    assert_eq!(&C3_NOTIFICATION[2..], &fixtures::C3_CAPTURE[..]);
    assert_eq!(&C5_NOTIFICATION[2..], &fixtures::C5_SETTINGS[..]);
    assert_eq!(&E1_BLE_NOTIFICATION[1..], &fixtures::E1_BLE[..]);
    assert_eq!(&E1_USB_FRAME[1..], &fixtures::E1_USB[..]);

    // C3_CAPTURE: 13.00 V, 1.000 A, output off, 90 %.
    let c3 = ble::decode(&C3_NOTIFICATION, BleRoute::Af01).unwrap();
    let reading = Reading::from_raw(&telemetry::parse(&c3).unwrap());
    assert_eq!(reading.set_volts, 13.0);
    assert_eq!(reading.set_amps, 1.0);
    assert!(!reading.output_on);
    assert_eq!(reading.battery_percent, 90);

    // The captured 0xC5: charge limit 90, volume 2, OCP delay 50.
    let c5 = ble::decode(&C5_NOTIFICATION, BleRoute::Af01).unwrap();
    let s = settings::parse(&c5).unwrap();
    assert_eq!((s.charge_limit, s.volume, s.ocp_delay), (90, 2, 50));

    // E1_BLE: version 1.6.0.40, model MP305B, hardware 2.0.2.0.
    let e1 = ble::decode(&E1_BLE_NOTIFICATION, BleRoute::Af02).unwrap();
    let i = info::parse(&e1).unwrap();
    assert_eq!(i.version.to_string(), "1.6.0.40");
    assert_eq!(i.model, "MP305B");
    assert_eq!(
        i.hardware.map(|h| h.to_string()).as_deref(),
        Some("2.0.2.0")
    );

    // E1_USB (constructed): the USB layout's fields.
    let i = info::parse(&e1_usb_from_hid(&E1_USB_FRAME)).unwrap();
    assert_eq!(i.model, "MP305B");
    assert_eq!(i.version, Version([1, 6, 0, 51]));
    assert_eq!(i.bootloader_raw, Some([1, 2, 3, 4, 5, 6, 7, 8]));
    assert_eq!(i.name.as_deref(), Some("MP305B"));
    assert_eq!(i.hardware, None);
}

/// Test: IT-011
#[test]
fn every_reply_truncated_by_one_byte_is_short_and_gives_no_value() {
    let c3 = ble::decode(&C3_NOTIFICATION[..37], BleRoute::Af01).unwrap();
    assert_eq!(
        protocol_error(telemetry::parse(&c3)),
        Error::Protocol(Reason::Short {
            needed: 36,
            got: 35
        })
    );
    let c5 = ble::decode(&C5_NOTIFICATION[..12], BleRoute::Af01).unwrap();
    assert_eq!(
        protocol_error(settings::parse(&c5)),
        Error::Protocol(Reason::Short {
            needed: 11,
            got: 10
        })
    );
    let e1 = ble::decode(&E1_BLE_NOTIFICATION[..16], BleRoute::Af02).unwrap();
    assert_eq!(
        protocol_error(info::parse(&e1)),
        Error::Protocol(Reason::Short {
            needed: 16,
            got: 15
        })
    );
    let e1 = e1_usb_from_hid(&E1_USB_FRAME[..30]);
    assert_eq!(
        protocol_error(info::parse(&e1)),
        Error::Protocol(Reason::Short {
            needed: 30,
            got: 29
        })
    );
}

/// A reading parsed from `C3_CAPTURE` with the given bytes written at
/// their offsets.
fn reading_with(bytes: &[(usize, &[u8])]) -> RawReading {
    let mut payload = C3_NOTIFICATION[2..].to_vec();
    for (offset, value) in bytes {
        payload[*offset..*offset + value.len()].copy_from_slice(value);
    }
    telemetry::parse_payload(&payload).unwrap()
}

/// Test: IT-011
#[test]
fn the_requests_are_built_with_every_field_at_its_bounds() {
    // The bind: `18`, the 16-byte ID, `00`, the fast flag; the ID at its
    // lowest (all zero is refused, so one bit set) and its highest value.
    for id in [
        [
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x01,
        ],
        [0xFF; 16],
    ] {
        for fast in [false, true] {
            let request = bind::request(&HostId::new(id).unwrap(), fast);
            let mut expected = id.to_vec();
            expected.extend_from_slice(&[0x00, u8::from(fast)]);
            assert_eq!(request.opcode(), 0x18);
            assert_eq!(request.payload(), expected.as_slice());
            assert_eq!(request.payload().len(), 18);
        }
    }

    // 0xE0 and 0xC2 have no field. The entry's payload length 1 for both is
    // left out: DD-PROTO-022, DD-PROTO-024 and DD-PROTO-040 give them an
    // empty payload, and the builders follow that (reported with the test).
    assert_eq!(info::request().opcode(), 0xE0);
    assert_eq!(telemetry::request().opcode(), 0xC2);

    // 0xC8, copied from readings at the bounds the firmware applies, with
    // the setpoints at the supply's range and every remoteCon value.
    let none = Limits::none();
    let low = reading_with(&[
        (SET_VOLTAGE, &[0, 0]),
        (SET_CURRENT, &[0, 0]),
        (CURRENT_OVER, &[0]),
        (REAL_CHANGE, &[0]),
        (VOLTAGE_SLOW, &[0]),
        (OUTPUT, &[0]),
    ]);
    let high = reading_with(&[
        (SET_VOLTAGE, &3050u16.to_le_bytes()),
        (SET_CURRENT, &5100u16.to_le_bytes()),
        (CURRENT_OVER, &[1]),
        (REAL_CHANGE, &[3]),
        (VOLTAGE_SLOW, &[1]),
        (OUTPUT, &[1]),
    ]);
    let low_frame = Command::from_reading(&low)
        .unwrap()
        .remote_con(RemoteCon::Release)
        .encode();
    assert_eq!(low_frame.opcode(), 0xC8);
    assert_eq!(low_frame.payload(), &[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]);
    let high_frame = Command::from_reading(&high)
        .unwrap()
        .remote_con(RemoteCon::Request)
        .encode();
    assert_eq!(
        high_frame.payload(),
        &[0x02, 0xEA, 0x0B, 0xEC, 0x13, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00]
    );
    for (volts, amps, on) in [(0.0, 0.0, false), (30.0, 5.0, true)] {
        let frame = Command::from_reading(&low)
            .unwrap()
            .remote_con(RemoteCon::Active)
            .set_voltage(RawVoltage::from_volts(volts, &none).unwrap())
            .set_current(RawCurrent::from_amps(amps, &none).unwrap())
            .output(on)
            .encode();
        let v = RawVoltage::from_volts(volts, &none).unwrap().raw();
        let a = RawCurrent::from_amps(amps, &none).unwrap().raw();
        let mut expected = vec![0x01];
        expected.extend_from_slice(&v.to_le_bytes());
        expected.extend_from_slice(&a.to_le_bytes());
        expected.extend_from_slice(&[0, 0, 0, u8::from(on), 0, 0]);
        assert_eq!(frame.payload(), expected.as_slice());
        assert_eq!(frame.payload().len(), 11);
    }
    assert_eq!(RawVoltage::from_volts(30.0, &none).unwrap().raw(), 3000);
    assert_eq!(RawCurrent::from_amps(5.0, &none).unwrap().raw(), 5000);
    for frame in [&low_frame, &high_frame] {
        assert_eq!(frame.payload().len(), 11);
        // model and refresh are 0 whatever the reading.
        assert_eq!(&frame.payload()[9..], &[0, 0]);
    }
}
