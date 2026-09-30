//! Property tests of the framing round trips (in-crate, so that they can
//! build frames through the crate-private constructor).
//!
//! Implements: nothing; tests UT-PROTO-003 and UT-PROTO-014.

use proptest::prelude::*;

use crate::protocol::ble::{self, BleRoute};
use crate::protocol::frame::Frame;
use crate::protocol::hid;

/// Any frame with a payload the framed form can carry.
fn any_frame() -> impl Strategy<Value = Frame> {
    (any::<u8>(), proptest::collection::vec(any::<u8>(), 0..=254))
        .prop_map(|(opcode, payload)| Frame::new(opcode, payload).unwrap())
}

proptest! {
    #![proptest_config(ProptestConfig { cases: 512, ..ProptestConfig::default() })]

    /// Test: UT-PROTO-003
    #[test]
    fn ble_round_trip_on_both_routes(frame in any_frame()) {
        let mut on_air = ble::encode(&frame, BleRoute::Af01);
        // The bridge discards the placeholder and prepends the tag on the way back.
        on_air[0] = 0x31;
        prop_assert_eq!(ble::decode(&on_air, BleRoute::Af01).unwrap(), frame.clone());
        let on_air = ble::encode(&frame, BleRoute::Af02);
        prop_assert_eq!(ble::decode(&on_air, BleRoute::Af02).unwrap(), frame);
    }

    /// Test: UT-PROTO-014
    #[test]
    fn hid_round_trip_in_random_splits(frame in any_frame(), seed in any::<u64>()) {
        // Rebuild the stream the bridge would send: address 0x21, same doubling rule.
        let mut body = vec![frame.opcode()];
        body.extend_from_slice(frame.payload());
        let length = (body.len()) as u8;
        let sum = hid::checksum(hid::REPLY_ADDRESS, length, &body);
        let mut stream = vec![0xAA];
        for byte in [hid::REPLY_ADDRESS, length].into_iter().chain(body).chain([sum]) {
            stream.push(byte);
            if byte == 0xAA { stream.push(0xAA); }
        }
        let mut decoder = hid::Decoder::new();
        let mut results = Vec::new();
        let mut rest = stream.as_slice();
        let mut state = seed | 1;
        while !rest.is_empty() {
            state ^= state << 13; state ^= state >> 7; state ^= state << 17;
            let take = ((state % 64) as usize + 1).min(rest.len());
            let (head, tail) = rest.split_at(take);
            results.extend(decoder.push(head));
            rest = tail;
        }
        prop_assert_eq!(results, vec![Ok(frame)]);
    }
}
