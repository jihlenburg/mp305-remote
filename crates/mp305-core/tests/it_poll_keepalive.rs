//! Integration test IT-021 (AR-021): the poll paces every `0xC2` at least
//! 100 ms after the previous `0xC3`; over USB a frame goes out at least
//! every 2 s, `0xE0` while the poll is paused; over Bluetooth the link
//! sends nothing on its own while the poll is paused.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    missing_docs
)]

mod common;

use core::time::Duration;

use mp305_core::protocol::timing;
use mp305_core::transport::description::Kind;
use mp305_core::transport::mock::Script;

use common::{link_rig, ms, reply, LinkRig, C3_CAPTURE, E1_BLE, E1_USB};

/// When the poll is paused.
const PAUSE: Duration = Duration::from_secs(10);
/// The end of the observation.
const END: Duration = Duration::from_secs(20);

/// A link on a mock of `kind` that answers `0xC2` after 130 ms and `0xE0`
/// after 100 ms, polled for 10 s and then paused for 10 s.
async fn poll_then_pause(kind: Kind, id: &str) -> LinkRig {
    let e1: &[u8] = match kind {
        Kind::Ble => &E1_BLE,
        Kind::Hid => &E1_USB,
    };
    let rig = link_rig(
        kind,
        id,
        Script {
            replies: vec![
                reply(kind, 0xC2, ms(130), &C3_CAPTURE),
                reply(kind, 0xE0, ms(100), e1),
            ],
            ..Script::default()
        },
    );
    rig.link.set_polling(true);
    rig.until(PAUSE).await;
    rig.link.set_polling(false);
    rig.until(END).await;
    rig
}

/// Checks the pacing of every `0xC2` against the readings: each one at
/// least `timing::POLL_PAUSE` after the latest `0xC3` before it.
fn every_c2_paced(rig: &LinkRig) {
    let c2s = rig.sent_times(0xC2);
    let c3s = rig.reading_times();
    assert!(c2s.len() >= 40, "{}", c2s.len());
    for c2 in &c2s[1..] {
        let previous = c3s.iter().filter(|c3| *c3 <= c2).max().unwrap();
        assert!(
            *c2 - *previous >= timing::POLL_PAUSE,
            "0xC2 at {c2:?}, 0xC3 at {previous:?}"
        );
    }
    // The gaps between consecutive 0xC2s while polling: one reply time plus
    // the pause.
    for pair in c2s.windows(2) {
        assert!(
            pair[1] - pair[0] >= ms(130) + timing::POLL_PAUSE,
            "{pair:?}"
        );
    }
    assert!(c2s.iter().all(|t| *t < PAUSE));
}

/// Test: IT-021
#[tokio::test(start_paused = true)]
async fn usb_sends_a_frame_at_least_every_2_s_and_e0_while_the_poll_is_paused() {
    let rig = poll_then_pause(Kind::Hid, "IT-021-usb").await;
    every_c2_paced(&rig);
    // No gap over 2 s between consecutive frames, nor before the end.
    let mut times: Vec<Duration> = rig.sent().iter().map(|(t, _, _)| *t).collect();
    times.push(END);
    for pair in times.windows(2) {
        assert!(pair[1] - pair[0] <= timing::USB_KEEPALIVE, "{pair:?}");
    }
    // During the pause the frames are 0xE0s.
    let paused: Vec<u8> = rig
        .sent()
        .iter()
        .filter(|(t, _, _)| *t > PAUSE)
        .map(|(_, op, _)| *op)
        .collect();
    assert!(paused.len() >= 4, "{paused:?}");
    assert!(paused.iter().all(|op| *op == 0xE0), "{paused:?}");
}

/// Test: IT-021
#[tokio::test(start_paused = true)]
async fn bluetooth_sends_nothing_while_the_poll_is_paused() {
    let rig = poll_then_pause(Kind::Ble, "IT-021-ble").await;
    every_c2_paced(&rig);
    let after: Vec<(Duration, u8, Vec<u8>)> = rig
        .sent()
        .into_iter()
        .filter(|(t, _, _)| *t > PAUSE)
        .collect();
    assert!(after.is_empty(), "{after:?}");
    assert!(rig.sent().iter().all(|(_, op, _)| *op == 0xC2));
}
