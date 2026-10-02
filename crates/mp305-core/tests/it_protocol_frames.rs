//! Integration test IT-010 (AR-010): the two wire forms of `protocol`.
//! `protocol::ble` against the capture frames of both characteristics,
//! `protocol::hid` against the `C8_170` fixture, a 70-byte frame and broken
//! streams, and random frames through both forms and every report split.
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
use mp305_core::protocol::frame::Frame;
use mp305_core::protocol::hid::{self, Decoder};
use proptest::prelude::*;

/// The address of a request stream (source 1, destination 2).
const REQUEST: u8 = 0x12;
/// The address of a reply stream.
const REPLY: u8 = 0x21;
/// The most stream bytes one report carries.
const REPORT: usize = 62;

/// `2026-09-29T193614-ble-readonly.jsonl`, t = 12.6165, TX on AF01.
const C4_TX_AF01: [u8; 2] = [0x12, 0xC4];
/// `2026-09-29T193614-ble-readonly.jsonl`, t = 12.7497, RX on AF01.
const C5_RX_AF01: [u8; 13] = [
    0x31, 0xC5, 0x5A, 0x02, 0x00, 0x00, 0x01, 0xF4, 0x01, 0x32, 0x00, 0x00, 0x00,
];
/// `2026-09-29T193614-ble-readonly.jsonl`, t = 12.486, TX on AF02.
const E0_TX_AF02: [u8; 1] = [0xE0];
/// `2026-09-29T193614-ble-readonly.jsonl`, t = 12.6162, RX on AF02
/// (`E1_BLE` with its opcode).
const E1_RX_AF02: [u8; 17] = [
    0xE1, 0x01, 0x06, 0x00, 0x28, 0x4D, 0x50, 0x33, 0x30, 0x35, 0x42, 0x00, 0x00, 0x02, 0x00, 0x02,
    0x00,
];

/// The payload of `C8_170` as the entry writes its stream
/// (`AA 12 0C C8 01 AA AA 00 64 00 00 00 00 00 00 00 <sum>`): `remoteCon` 1,
/// 1.70 V (raw 170 = `0xAA`), 0.100 A (raw 100 = `0x64`), the six bytes
/// after the current all 0. A command built from `C3_CAPTURE` would carry
/// its `realChange` 3 at offset 5; the test follows the bytes the entry
/// writes out (the discrepancy is reported with the test).
const C8_170_PAYLOAD: [u8; 11] = [
    0x01, 0xAA, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
];

/// A frame with `opcode` and `payload`. `Frame::new` is private to the
/// crate; the AF02 form carries `opcode payload` unchanged, so its decoder
/// is the public way to obtain an arbitrary frame.
fn frame(opcode: u8, payload: &[u8]) -> Frame {
    let mut bytes = vec![opcode];
    bytes.extend_from_slice(payload);
    ble::decode(&bytes, BleRoute::Af02).unwrap()
}

/// The framed stream of protocol.md 2.2, written here independently of
/// `protocol::hid`: `AA`, the address, the length (opcode through the last
/// payload byte), the opcode, the payload and the 8-bit sum of the
/// unstuffed bytes from the address on; every `AA` after the first doubled.
fn stream(address: u8, opcode: u8, payload: &[u8]) -> Vec<u8> {
    let length = u8::try_from(payload.len() + 1).unwrap();
    let mut unstuffed = vec![address, length, opcode];
    unstuffed.extend_from_slice(payload);
    let sum = unstuffed.iter().fold(0u8, |s, b| s.wrapping_add(*b));
    unstuffed.push(sum);
    let mut out = vec![0xAA];
    for byte in unstuffed {
        out.push(byte);
        if byte == 0xAA {
            out.push(0xAA);
        }
    }
    out
}

/// Feeds `pieces` to a fresh decoder and returns every result.
fn decode_pieces<'a>(pieces: impl IntoIterator<Item = &'a [u8]>) -> Vec<Result<Frame, Reason>> {
    let mut decoder = Decoder::new();
    pieces.into_iter().flat_map(|p| decoder.push(p)).collect()
}

/// Asserts that `bytes` decodes to exactly `[Ok(expected)]` however it is
/// split: in two at every position, and in reports of every size from 1
/// to 62 bytes.
fn decodes_in_every_split(bytes: &[u8], expected: &Frame) {
    for at in 0..=bytes.len() {
        let (a, b) = bytes.split_at(at);
        assert_eq!(
            decode_pieces([a, b]),
            vec![Ok(expected.clone())],
            "split at {at}"
        );
    }
    for size in 1..=REPORT {
        assert_eq!(
            decode_pieces(bytes.chunks(size)),
            vec![Ok(expected.clone())],
            "reports of {size} bytes"
        );
    }
}

/// Test: IT-010
#[test]
fn step1_the_capture_frames_map_both_ways_on_af01_and_af02() {
    // AF01 out: the frame 0xC4 is written with the placeholder 0x12, and
    // the same frame comes back from the tagged form.
    let c4 = frame(0xC4, &[]);
    assert_eq!(ble::encode(&c4, BleRoute::Af01), C4_TX_AF01);
    let mut c4_in = vec![0x31];
    c4_in.extend_from_slice(&C4_TX_AF01[1..]);
    assert_eq!(ble::decode(&c4_in, BleRoute::Af01).unwrap(), c4);

    // AF01 in: the captured notification is the frame 0xC5 with the 11
    // bytes after the tag and the opcode, and that frame is written with
    // the placeholder in place of the tag.
    let c5 = ble::decode(&C5_RX_AF01, BleRoute::Af01).unwrap();
    assert_eq!((c5.opcode(), c5.payload()), (0xC5, &C5_RX_AF01[2..]));
    let mut c5_out = vec![0x12];
    c5_out.extend_from_slice(&C5_RX_AF01[1..]);
    assert_eq!(ble::encode(&c5, BleRoute::Af01), c5_out);

    // AF02, both directions: no placeholder, no tag.
    let e0 = frame(0xE0, &[]);
    assert_eq!(ble::encode(&e0, BleRoute::Af02), E0_TX_AF02);
    assert_eq!(ble::decode(&E0_TX_AF02, BleRoute::Af02).unwrap(), e0);
    let e1 = ble::decode(&E1_RX_AF02, BleRoute::Af02).unwrap();
    assert_eq!((e1.opcode(), e1.payload()), (0xE1, &E1_RX_AF02[1..]));
    assert_eq!(ble::encode(&e1, BleRoute::Af02), E1_RX_AF02);
}

/// Test: IT-010
#[test]
fn step2_c8_170_and_a_70_byte_frame_are_encoded_into_reports() {
    // C8_170: `AA 12 0C C8 01 AA AA 00 64 00 00 00 00 00 00 00 <sum>`, the
    // sum computed here from the unstuffed bytes.
    let c8_170 = frame(0xC8, &C8_170_PAYLOAD);
    let unstuffed = [
        0x12u8, 0x0C, 0xC8, 0x01, 0xAA, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    ];
    let sum = unstuffed.iter().fold(0u8, |s, b| s.wrapping_add(*b));
    let mut expected = vec![
        0xAA, 0x12, 0x0C, 0xC8, 0x01, 0xAA, 0xAA, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00,
    ];
    expected.push(sum);
    assert_eq!(hid::encode(&c8_170), vec![expected]);

    // A 70-byte frame: the longest reply, `0xDF`, is 70 bytes from the
    // opcode through the payload (device-model.md 2.1). Its stream does not
    // fit one report: the first report carries 62 bytes and the second the
    // rest, together the whole stream. The entry's "62 and 10" is left out:
    // a 70-byte frame gives a 74-byte stream (62 and 12); 62 and 10 needs a
    // 72-byte stream (reported with the test).
    let payload: Vec<u8> = (0u8..69).map(|i| i % 0x50).collect();
    let long = frame(0xDF, &payload);
    assert_eq!(1 + long.payload().len(), 70);
    let reports = hid::encode(&long);
    let whole = stream(REQUEST, 0xDF, &payload);
    assert_eq!(reports.len(), 2);
    assert_eq!(reports[0].len(), REPORT);
    assert_eq!(reports[1].len(), whole.len() - REPORT);
    assert_eq!(reports.concat(), whole);
}

/// Test: IT-010
#[test]
fn step2_c8_170_reply_streams_decode_in_every_report_split() {
    // The C8_170 frame in the reply form (address 0x21), with its doubled
    // AA, and the reply to it, `0xC9 00`.
    let c8_170 = frame(0xC8, &C8_170_PAYLOAD);
    let as_reply = stream(REPLY, 0xC8, &C8_170_PAYLOAD);
    assert_eq!(&as_reply[..7], &[0xAA, 0x21, 0x0C, 0xC8, 0x01, 0xAA, 0xAA]);
    decodes_in_every_split(&as_reply, &c8_170);
    let c9 = frame(0xC9, &[0x00]);
    decodes_in_every_split(&stream(REPLY, 0xC9, &[0x00]), &c9);
}

/// Test: IT-010
#[test]
fn step2_broken_streams_give_their_reason_and_the_decoder_resynchronises() {
    let good = stream(REPLY, 0xC8, &C8_170_PAYLOAD);
    let c8_170 = frame(0xC8, &C8_170_PAYLOAD);
    let as_error = |r: &Result<Frame, Reason>| Error::from(r.clone().unwrap_err());

    // A bad checksum, then the next frame at its AA.
    let mut bad_sum = good.clone();
    let expected_sum = *bad_sum.last().unwrap();
    *bad_sum.last_mut().unwrap() = expected_sum.wrapping_add(1);
    let mut decoder = Decoder::new();
    let results = decoder.push(&bad_sum);
    assert_eq!(results.len(), 1);
    assert_eq!(
        as_error(&results[0]),
        Error::Protocol(Reason::BadChecksum {
            expected: expected_sum,
            got: expected_sum.wrapping_add(1)
        })
    );
    assert_eq!(decoder.push(&good), vec![Ok(c8_170.clone())]);

    // A wrong length: the length byte 0, which no frame can have (the
    // decoder trusts any other length and catches a wrong one through the
    // checksum). The bytes after it are skipped up to the next AA.
    let mut decoder = Decoder::new();
    let results = decoder.push(&[0xAA, 0x21, 0x00, 0xC9, 0x00, 0xEA]);
    assert_eq!(results.len(), 1);
    assert_eq!(
        as_error(&results[0]),
        Error::Protocol(Reason::BadLength {
            expected: 1,
            got: 0
        })
    );
    assert_eq!(
        decoder.push(&good),
        vec![Err(Reason::Skipped(3)), Ok(c8_170.clone())]
    );

    // A lone AA in the body: the frame is cut after its first payload byte
    // and the next frame starts; the decoder restarts at that AA.
    let mut lone = good[..5].to_vec();
    lone.extend_from_slice(&good);
    let results = decode_pieces([lone.as_slice()]);
    assert_eq!(results.len(), 2);
    assert_eq!(as_error(&results[0]), Error::Protocol(Reason::Restarted));
    assert_eq!(results[1], Ok(c8_170.clone()));

    // Leading garbage before the AA is skipped and counted.
    let mut garbage = vec![0x01, 0x02, 0x03, 0x55];
    garbage.extend_from_slice(&good);
    let mut decoder = Decoder::new();
    assert_eq!(
        decoder.push(&garbage),
        vec![Err(Reason::Skipped(4)), Ok(c8_170)]
    );
    assert_eq!(decoder.skipped_total(), 4);
}

/// A random frame: any opcode, a payload of up to 254 bytes (the most the
/// length byte allows).
fn any_frame() -> impl Strategy<Value = (u8, Vec<u8>)> {
    (any::<u8>(), prop::collection::vec(any::<u8>(), 0..=254))
}

proptest! {
    /// Test: IT-010
    #[test]
    fn step3_random_frames_round_trip_through_both_forms_and_every_report_split(
        (opcode, payload) in any_frame()
    ) {
        let f = frame(opcode, &payload);
        // AF02: the same bytes both ways.
        prop_assert_eq!(ble::decode(&ble::encode(&f, BleRoute::Af02), BleRoute::Af02).unwrap(), f.clone());
        // AF01: written behind the placeholder, received behind the tag.
        let out = ble::encode(&f, BleRoute::Af01);
        prop_assert_eq!(out[0], 0x12);
        let mut tagged = vec![0x31];
        tagged.extend_from_slice(&out[1..]);
        prop_assert_eq!(ble::decode(&tagged, BleRoute::Af01).unwrap(), f.clone());
        // HID out: the request stream, cut into reports of 62 bytes and a
        // last one of at most 62.
        let reports = hid::encode(&f);
        prop_assert_eq!(reports.concat(), stream(REQUEST, opcode, &payload));
        for (i, report) in reports.iter().enumerate() {
            prop_assert!(!report.is_empty() && report.len() <= REPORT);
            if i + 1 < reports.len() {
                prop_assert_eq!(report.len(), REPORT);
            }
        }
        // HID in: the decoder accepts replies (address 0x21) only, so the
        // round trip goes through the reply form of the same frame, split
        // at every report size and at every position.
        let reply = stream(REPLY, opcode, &payload);
        for size in 1..=REPORT {
            prop_assert_eq!(decode_pieces(reply.chunks(size)), vec![Ok(f.clone())]);
        }
        for at in 0..=reply.len() {
            let (a, b) = reply.split_at(at);
            prop_assert_eq!(decode_pieces([a, b]), vec![Ok(f.clone())]);
        }
    }
}
