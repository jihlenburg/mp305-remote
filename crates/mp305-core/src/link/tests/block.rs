//! Task tests: the `0xC8` block and `output_off`.
//!
//! Implements: nothing; holds the tests of UT-LINK-016 to 018.

use super::*;
use crate::protocol::ops::info;

/// Test: UT-LINK-016
#[tokio::test(start_paused = true)]
async fn after_a_control_timeout_a_poll_cycle_precedes_the_next_control() {
    let mut r = rig(Kind::Ble, Duration::ZERO);
    let (when, result) = track(r.link.request(c8(1, 1))).await.unwrap();
    assert_eq!(when - r.start, ms(1_000));
    assert_eq!(
        result.unwrap_err(),
        Error::Timeout {
            opcode: 0xC8,
            after: ms(1_000)
        }
    );
    let next = track(r.link.request(c8(1, 1)));
    r.feed_at(ms(1_050), c9(0));
    r.feed_at(ms(1_200), c3());
    r.feed_at(ms(1_400), c9(0));
    let (when, result) = next.await.unwrap();
    assert_eq!(when - r.start, ms(1_400));
    let (frame, at) = reply_of(result);
    assert_eq!(frame, c9(0));
    assert_eq!(at - r.start, ms(1_400));
    let sent: Vec<(Duration, u8)> = r.sent().into_iter().map(|(t, _, op)| (t, op)).collect();
    assert_eq!(
        sent,
        vec![(Duration::ZERO, 0xC8), (ms(1_000), 0xC2), (ms(1_200), 0xC8)]
    );
    let events = r.drain_events();
    assert_eq!(events.len(), 2, "{events:?}");
    assert!(matches!(&events[0], DeviceEvent::LateReply { frame, at }
        if frame.opcode() == 0xC9 && *at - r.start == ms(1_050)));
    assert!(matches!(&events[1], DeviceEvent::Reading { at, .. } if *at - r.start == ms(1_200)));
}

/// Test: UT-LINK-017
#[tokio::test(start_paused = true)]
async fn the_block_applies_to_output_off_too() {
    let mut r = rig(Kind::Ble, Duration::ZERO);
    let (_, result) = track(r.link.request(c8(1, 1))).await.unwrap();
    assert!(matches!(result, Err(Error::Timeout { opcode: 0xC8, .. })));
    let off = track(r.link.output_off(c8(1, 0)));
    r.feed_at(ms(1_150), c3());
    r.feed_at(ms(1_400), c9(0));
    let (when, result) = off.await.unwrap();
    assert_eq!(when - r.start, ms(1_400));
    let (frame, at) = reply_of(result);
    assert_eq!(frame, c9(0));
    assert_eq!(at - r.start, ms(1_400));
    let (when, result) = track(r.link.output_off(c8(1, 0))).await.unwrap();
    assert_eq!(when - r.start, ms(1_900));
    assert_eq!(
        result.unwrap_err(),
        Error::Timeout {
            opcode: 0xC8,
            after: ms(500)
        }
    );
    let sent: Vec<(Duration, u8)> = r.sent().into_iter().map(|(t, _, op)| (t, op)).collect();
    assert_eq!(
        sent,
        vec![
            (Duration::ZERO, 0xC8),
            (ms(1_000), 0xC2),
            (ms(1_150), 0xC8),
            (ms(1_400), 0xC8)
        ]
    );
    assert!(r
        .drain_events()
        .iter()
        .all(|e| !matches!(e, DeviceEvent::LinkLost { .. })));
}

/// Test: UT-LINK-018
#[tokio::test(start_paused = true)]
async fn output_off_refuses_other_frames_and_jumps_the_queue() {
    let r = rig(Kind::Ble, Duration::ZERO);
    assert_eq!(
        r.link.output_off(c8(1, 1)).await.unwrap_err(),
        Error::Protocol(Reason::Value {
            field: "output",
            value: 1
        })
    );
    assert_eq!(
        r.link.output_off(c8(2, 0)).await.unwrap_err(),
        Error::Protocol(Reason::Value {
            field: "remoteCon",
            value: 2
        })
    );
    assert_eq!(
        r.link.output_off(telemetry::request()).await.unwrap_err(),
        Error::Protocol(Reason::WrongOpcode {
            expected: 0xC8,
            got: 0xC2
        })
    );
    sleep(ms(1)).await;
    assert!(r.sent().is_empty());
    let r = rig(Kind::Ble, Duration::ZERO);
    r.auto_reply(ms(200), ms(5_000), |frame, _| match frame.opcode() {
        0xE0 => Some(e1()),
        0xC8 => Some(c9(0)),
        _ => None,
    });
    let infos: Vec<_> = (0..3)
        .map(|_| track(r.link.request(info::request())))
        .collect();
    r.until(ms(100)).await;
    let off = track(r.link.output_off(c8(1, 0)));
    reply_of(off.await.unwrap().1);
    for i in infos {
        reply_of(i.await.unwrap().1);
    }
    let sent: Vec<(Duration, u8)> = r.sent().into_iter().map(|(t, _, op)| (t, op)).collect();
    assert_eq!(
        sent,
        vec![
            (Duration::ZERO, 0xE0),
            (ms(200), 0xC8),
            (ms(400), 0xE0),
            (ms(600), 0xE0)
        ]
    );
}
