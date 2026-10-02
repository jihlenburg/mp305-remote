//! Integration test IT-022 (AR-022): the link declares the link lost after
//! three unanswered immediate requests within 4 s of the last reply (a
//! deferred request does not count), and at once on a transport error or
//! an OS disconnect; then every pending and queued request fails with
//! `Error::LinkLost` and nothing more is sent.
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

use mp305_core::error::Error;
use mp305_core::link::{DeviceEvent, LossReason, Outcome};
use mp305_core::protocol::ops::control::RemoteCon;
use mp305_core::protocol::ops::{info, telemetry};
use mp305_core::protocol::timing;
use mp305_core::transport::description::Kind;
use mp305_core::transport::mock::{Script, SendError};

use common::{c8, c8_volts, link_rig, ms, reply, secs, track, LinkRig, C3_CAPTURE, E1_BLE};

/// The loss events so far, with their times.
fn losses(rig: &LinkRig) -> Vec<(Duration, LossReason)> {
    rig.events()
        .into_iter()
        .filter_map(|(t, e)| match e {
            DeviceEvent::LinkLost { reason } => Some((t, reason)),
            _ => None,
        })
        .collect()
}

/// Asserts that `result` is `Error::LinkLost` with `text`.
fn lost_with(result: &Result<Outcome, Error>, text: &str) {
    match result {
        Err(Error::LinkLost { text: t }) => assert_eq!(t, text),
        other => panic!("expected LinkLost ({text}), got {other:?}"),
    }
}

/// Test: IT-022
#[tokio::test(start_paused = true)]
async fn case1_silence_with_a_deferred_c8_open_is_reported_within_4_s() {
    let ble = Kind::Ble;
    let rig = link_rig(
        ble,
        "IT-022-1",
        Script {
            replies: vec![
                reply(ble, 0xC2, ms(130), &C3_CAPTURE),
                reply(ble, 0xE0, ms(100), &E1_BLE),
            ],
            // The 0xC8 is never answered; from 5 s on nothing is.
            stop_replying_at: Some(secs(5)),
            ..Script::default()
        },
    );
    // A deferred 0xC8 open from the start, then the poll.
    let pending = match rig.link.request(c8(RemoteCon::Request)).await.unwrap() {
        Outcome::Deferred(pending) => pending,
        other => panic!("expected a deferred outcome, got {other:?}"),
    };
    let pending = tokio::spawn(pending);
    rig.link.set_polling(true);
    // A request from the session during the silence.
    rig.until(ms(5_500)).await;
    let session_request = track(rig.link.request(info::request()), rig.start);
    // A request queued shortly before the loss.
    rig.until(ms(8_000)).await;
    let queued = track(rig.link.request(telemetry::request()), rig.start);
    rig.until(secs(20)).await;

    let lost = losses(&rig);
    assert_eq!(lost.len(), 1, "{lost:?}");
    let (lost_at, reason) = lost[0].clone();
    assert_eq!(reason, LossReason::Unanswered);
    let last_reply = *rig.reading_times().last().unwrap();
    assert!(
        lost_at - last_reply <= timing::LINK_LOSS_REPORT,
        "last reply {last_reply:?}, lost {lost_at:?}"
    );
    // Exactly three immediate requests went out after the last reply, and
    // the loss came one reply time after the third.
    let immediate: Vec<(Duration, u8)> = rig
        .sent()
        .into_iter()
        .filter(|(t, op, _)| *t > last_reply && *op != 0xC8)
        .map(|(t, op, _)| (t, op))
        .collect();
    assert_eq!(immediate.len(), 3, "{immediate:?}");
    assert_eq!(lost_at, immediate[2].0 + timing::REPLY);
    // The deferred request did not count: it was written at the start, its
    // 70 s bound had not passed, and it ended with the link.
    assert_eq!(rig.sent_times(0xC8), vec![ms(0)]);
    let text = LossReason::Unanswered.to_string();
    match pending.await.unwrap() {
        Err(Error::LinkLost { text: t }) => assert_eq!(t, text),
        other => panic!("expected LinkLost, got {other:?}"),
    }
    // The session's request timed out or failed with the loss.
    let (_, result) = session_request.await.unwrap();
    assert!(
        matches!(
            result,
            Err(Error::Timeout {
                opcode: 0xE0,
                after
            }) if after == timing::REPLY
        ) || matches!(result, Err(Error::LinkLost { .. })),
        "{result:?}"
    );
    // The queued request failed with the loss, and nothing was sent after
    // it, also not for a request made later.
    let (_, result) = queued.await.unwrap();
    lost_with(&result, &text);
    let after = rig.link.request(telemetry::request()).await;
    lost_with(&after, &text);
    assert!(rig.sent().iter().all(|(t, _, _)| *t < lost_at));
}

/// Test: IT-022
#[tokio::test(start_paused = true)]
async fn case2_a_transport_error_ends_the_link_at_once() {
    let ble = Kind::Ble;
    let rig = link_rig(
        ble,
        "IT-022-2",
        Script {
            replies: vec![reply(ble, 0xE0, ms(200), &E1_BLE)],
            send_errors: vec![SendError {
                opcode: 0xC8,
                from: Duration::ZERO,
            }],
            ..Script::default()
        },
    );
    // One request in flight, the one whose write fails queued behind it,
    // and one more queued behind that.
    let in_flight = track(rig.link.request(info::request()), rig.start);
    let failing = track(rig.link.request(c8_volts(1.0)), rig.start);
    let queued = track(rig.link.request(telemetry::request()), rig.start);
    rig.until(secs(5)).await;

    assert!(matches!(
        in_flight.await.unwrap(),
        (t, Ok(Outcome::Reply { .. })) if t == ms(200)
    ));
    let lost = losses(&rig);
    let text = "transport: scripted send error for 0xc8".to_string();
    assert_eq!(lost, vec![(ms(200), LossReason::Transport(text.clone()))]);
    let reason = LossReason::Transport(text).to_string();
    let (at, result) = failing.await.unwrap();
    assert_eq!(at, ms(200));
    lost_with(&result, &reason);
    let (at, result) = queued.await.unwrap();
    assert_eq!(at, ms(200));
    lost_with(&result, &reason);
    let sent: Vec<(Duration, u8)> = rig.sent().iter().map(|(t, op, _)| (*t, *op)).collect();
    assert_eq!(sent, vec![(ms(0), 0xE0)]);
}

/// Test: IT-022
#[tokio::test(start_paused = true)]
async fn case3_an_os_disconnect_ends_the_link_at_once() {
    let ble = Kind::Ble;
    let rig = link_rig(
        ble,
        "IT-022-3",
        Script {
            replies: vec![reply(ble, 0xE0, ms(300), &E1_BLE)],
            close_at: Some(ms(150)),
            ..Script::default()
        },
    );
    let in_flight = track(rig.link.request(info::request()), rig.start);
    let queued = track(rig.link.request(telemetry::request()), rig.start);
    rig.until(secs(5)).await;

    assert_eq!(losses(&rig), vec![(ms(150), LossReason::Disconnected)]);
    let reason = LossReason::Disconnected.to_string();
    let (at, result) = in_flight.await.unwrap();
    assert_eq!(at, ms(150));
    lost_with(&result, &reason);
    let (at, result) = queued.await.unwrap();
    assert_eq!(at, ms(150));
    lost_with(&result, &reason);
    let sent: Vec<(Duration, u8)> = rig.sent().iter().map(|(t, op, _)| (*t, *op)).collect();
    assert_eq!(sent, vec![(ms(0), 0xE0)]);
}
