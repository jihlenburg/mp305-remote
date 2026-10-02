//! Integration test IT-012 (AR-012, AR-015): every opcode from 0 to 255
//! through `Guarded<Mock>`, and the opcode policy of `protocol::policy`.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    missing_docs
)]

use std::collections::BTreeSet;

use mp305_core::error::Error;
use mp305_core::protocol::ble::{self, BleRoute, Route};
use mp305_core::protocol::error::Reason;
use mp305_core::protocol::fixtures;
use mp305_core::protocol::frame::Frame;
use mp305_core::protocol::ops::bind::{self, HostId};
use mp305_core::protocol::ops::control::Command;
use mp305_core::protocol::ops::{self, info, telemetry};
use mp305_core::protocol::policy;
use mp305_core::transport::description::Kind;
use mp305_core::transport::guarded::Guarded;
use mp305_core::transport::mock::{Mock, Script};

/// The four request opcodes of the allowlist.
const ALLOWED: [u8; 4] = [0x18, 0xC2, 0xC8, 0xE0];

/// A frame with `opcode` and `payload`, obtained through the AF02 decoder
/// (the frame constructor is private to the crate).
fn frame(opcode: u8, payload: &[u8]) -> Frame {
    let mut bytes = vec![opcode];
    bytes.extend_from_slice(payload);
    ble::decode(&bytes, BleRoute::Af02).unwrap()
}

/// The frames tried for `opcode`: the request builder's frame for the four
/// allowed opcodes, else the opcode with no payload and with 11 and 18
/// payload bytes (the lengths of the allowed `0xC8` and `0x18`), so that
/// only the opcode can be what the guard refuses.
fn frames_for(opcode: u8) -> Vec<Frame> {
    match opcode {
        0x18 => vec![bind::request(&HostId::new([7; 16]).unwrap(), true)],
        0xE0 => vec![info::request()],
        0xC2 => vec![telemetry::request()],
        0xC8 => {
            let reading = telemetry::parse_payload(&fixtures::C3_CAPTURE).unwrap();
            vec![Command::from_reading(&reading).unwrap().encode()]
        }
        _ => vec![
            frame(opcode, &[]),
            frame(opcode, &[0; 11]),
            frame(opcode, &[0; 18]),
        ],
    }
}

/// The route a request with `opcode` goes on over a transport of `kind`.
fn route(kind: Kind, opcode: u8) -> Route {
    match kind {
        Kind::Ble => Route::Ble(ops::route(opcode)),
        Kind::Hid => Route::Hid,
    }
}

/// Test: IT-012
#[tokio::test(start_paused = true)]
async fn only_the_four_v1_requests_reach_the_mock() {
    for kind in [Kind::Ble, Kind::Hid] {
        let mock = Mock::new(kind, "IT-012", Script::default());
        let handle = mock.handle();
        let guard: Guarded<Mock> = Guarded::new(mock);
        for opcode in 0u8..=255 {
            for frame in frames_for(opcode) {
                let before = handle.sent().len();
                let result = guard.send(&frame, route(kind, opcode)).await;
                if ALLOWED.contains(&opcode) {
                    assert_eq!(result, Ok(()), "{kind} 0x{opcode:02x}");
                    assert_eq!(handle.sent().len(), before + 1);
                } else {
                    assert_eq!(
                        result,
                        Err(Error::Protocol(Reason::NotAllowed(opcode))),
                        "{kind} 0x{opcode:02x}"
                    );
                    assert_eq!(handle.sent().len(), before, "{kind} 0x{opcode:02x}");
                }
            }
        }
        let reached: Vec<u8> = handle.sent().iter().map(|s| s.frame.opcode()).collect();
        assert_eq!(reached, ALLOWED.to_vec(), "{kind}");
    }
}

/// Test: IT-012
#[test]
fn the_policy_lists_the_four_requests_and_a_reason_for_every_never_send_opcode() {
    let allowed: BTreeSet<u8> = policy::ALLOWED.iter().map(|(op, _)| *op).collect();
    assert_eq!(allowed, ALLOWED.into_iter().collect());
    let mut never: Vec<u8> = vec![0x10, 0xC0, 0xBE, 0x20];
    never.extend(0xF0..=0xFE);
    for opcode in &never {
        let reason = policy::never_reason(*opcode);
        assert!(
            reason.is_some_and(|r| !r.trim().is_empty()),
            "0x{opcode:02x} has no reason"
        );
        assert!(!allowed.contains(opcode));
    }
    let listed: BTreeSet<u8> = policy::NEVER.iter().map(|(op, _)| *op).collect();
    assert_eq!(listed, never.into_iter().collect());
}
