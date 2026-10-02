//! Integration test IT-020 (AR-020): the link's dispatch of incoming frames
//! and its order of requests on the scripted mock: a reply among a device
//! frame, a late reply, a deferred `0xC8` completed while polling runs, the
//! `0xC8` block after a timeout, and the urgent output-off.
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
use mp305_core::link::{DeviceEvent, Outcome};
use mp305_core::protocol::ops::control::{Command, RemoteCon};
use mp305_core::protocol::ops::events::DeviceFrame;
use mp305_core::protocol::ops::telemetry;
use mp305_core::protocol::timing;
use mp305_core::transport::description::Kind;
use mp305_core::transport::mock::Script;

use common::{
    c8, c8_volts, capture_reading, inject, link_rig, ms, reply, reply_with, secs, setpoints,
    silent, track, C3_CAPTURE, C5_SETTINGS,
};

/// Test: IT-020
#[tokio::test(start_paused = true)]
async fn step1_a_c5_during_a_read_is_an_event_and_the_c3_completes_the_read() {
    let ble = Kind::Ble;
    let rig = link_rig(
        ble,
        "IT-020-1",
        Script {
            replies: vec![reply(ble, 0xC2, ms(200), &C3_CAPTURE)],
            injections: vec![inject(ble, ms(100), 0xC5, &C5_SETTINGS)],
            ..Script::default()
        },
    );
    let outcome = rig.link.request(telemetry::request()).await.unwrap();
    match outcome {
        Outcome::Reply { frame, at } => {
            assert_eq!((frame.opcode(), frame.payload()), (0xC3, &C3_CAPTURE[..]));
            assert_eq!(at - rig.start, ms(200));
        }
        other => panic!("expected the reply, got {other:?}"),
    }
    tokio::time::sleep(ms(1)).await;
    let events = rig.events();
    assert_eq!(events.len(), 2, "{events:?}");
    match &events[0] {
        (t, DeviceEvent::Device(DeviceFrame::Settings(s))) => {
            assert_eq!(*t, ms(100));
            assert_eq!((s.charge_limit, s.volume, s.ocp_delay), (90, 2, 50));
        }
        other => panic!("expected the 0xC5 event, got {other:?}"),
    }
    assert_eq!(
        events[1],
        (
            ms(200),
            DeviceEvent::Reading {
                reading: capture_reading(),
                at: rig.start + ms(200)
            }
        )
    );
}

/// Test: IT-020
#[tokio::test(start_paused = true)]
async fn step2_a_c9_with_nothing_in_flight_is_a_late_reply() {
    let ble = Kind::Ble;
    let rig = link_rig(
        ble,
        "IT-020-2",
        Script {
            injections: vec![inject(ble, ms(500), 0xC9, &[0x00])],
            ..Script::default()
        },
    );
    rig.until(ms(600)).await;
    let events = rig.events();
    assert_eq!(events.len(), 1, "{events:?}");
    match &events[0] {
        (t, DeviceEvent::LateReply { frame, at }) => {
            assert_eq!(*t, ms(500));
            assert_eq!(*at - rig.start, ms(500));
            assert_eq!((frame.opcode(), frame.payload()), (0xC9, &[0x00][..]));
        }
        other => panic!("expected a late reply, got {other:?}"),
    }
    assert_eq!(rig.link.counters().late_replies, 1);
    assert!(rig.sent().is_empty());
}

/// Test: IT-020
#[tokio::test(start_paused = true)]
async fn step3_a_deferred_c8_is_completed_by_its_c9_while_readings_go_on() {
    let ble = Kind::Ble;
    let rig = link_rig(
        ble,
        "IT-020-3",
        Script {
            replies: vec![reply(ble, 0xC2, ms(130), &C3_CAPTURE)],
            injections: vec![inject(ble, secs(20) + ms(50), 0xC9, &[0x00])],
            ..Script::default()
        },
    );
    // The remote request over Bluetooth: deferred, the link is free once
    // it is written.
    let outcome = rig.link.request(c8(RemoteCon::Request)).await.unwrap();
    let pending = match outcome {
        Outcome::Deferred(pending) => pending,
        other => panic!("expected a deferred outcome, got {other:?}"),
    };
    assert_eq!(rig.now(), ms(0));
    assert_eq!(pending.opcode(), 0xC8);
    assert_eq!(pending.deadline() - rig.start, timing::REMOTE_PROMPT);
    // 20 s of polling, then the 0xC9.
    rig.link.set_polling(true);
    let (frame, at) = pending.await.unwrap();
    assert_eq!((frame.opcode(), frame.payload()), (0xC9, &[0x00][..]));
    assert_eq!(at - rig.start, secs(20) + ms(50));
    // Readings arrived all through the 20 s, never more than one poll cycle
    // (130 ms reply, 100 ms pause) apart.
    let readings = rig.reading_times();
    let during: Vec<Duration> = readings.into_iter().filter(|t| *t <= secs(20)).collect();
    assert!(during.len() >= 80, "{}", during.len());
    assert!(*during.last().unwrap() > secs(20) - ms(300));
    for pair in during.windows(2) {
        assert!(pair[1] - pair[0] <= ms(230), "{pair:?}");
    }
    assert!(!rig
        .events()
        .iter()
        .any(|(_, e)| matches!(e, DeviceEvent::LateReply { .. })));
}

/// Test: IT-020
#[tokio::test(start_paused = true)]
async fn step4_after_a_c8_timeout_the_late_c9_cannot_complete_the_next_c8() {
    let ble = Kind::Ble;
    let rig = link_rig(
        ble,
        "IT-020-4",
        Script {
            replies: vec![
                // The first 0xC8 gets no reply in time, every later one a
                // `0xC9 00` after 100 ms.
                silent(0xC8, Some(1), Duration::ZERO),
                reply_with(ble, 0xC8, ms(100), &[0x00], None, Duration::ZERO),
                reply(ble, 0xC2, ms(130), &C3_CAPTURE),
            ],
            // The late 0xC9 of the first 0xC8, during the next 0xC2.
            injections: vec![inject(ble, ms(1_050), 0xC9, &[0x00])],
            ..Script::default()
        },
    );
    // An immediate 0xC8 that times out.
    let first = rig.link.request(c8_volts(1.0)).await;
    assert_eq!(
        first.unwrap_err(),
        Error::Timeout {
            opcode: 0xC8,
            after: timing::REPLY
        }
    );
    assert_eq!(rig.now(), ms(1_000));
    // set_voltage again: a new 0xC8 with another voltage.
    let second = track(rig.link.request(c8_volts(1.7)), rig.start);
    let (resolved, result) = second.await.unwrap();
    // No 0xC8 before a 0xC3 arrived: the block's 0xC2 went first.
    let sent: Vec<(Duration, u8)> = rig.sent().iter().map(|(t, op, _)| (*t, *op)).collect();
    assert_eq!(
        sent,
        vec![(ms(0), 0xC8), (ms(1_000), 0xC2), (ms(1_130), 0xC8)]
    );
    let first_reading = rig.reading_times()[0];
    assert_eq!(first_reading, ms(1_130));
    let second_c8 = rig.sent_times(0xC8)[1];
    assert!(second_c8 >= first_reading);
    assert_eq!(setpoints(&rig.sent()[2].2), (170, 1000));
    // The late 0xC9 is a late reply and does not complete the new request,
    // which is answered by its own 0xC9 100 ms after its write.
    let late: Vec<Duration> = rig
        .events()
        .iter()
        .filter_map(|(t, e)| match e {
            DeviceEvent::LateReply { frame, .. } if frame.opcode() == 0xC9 => Some(*t),
            _ => None,
        })
        .collect();
    assert_eq!(late, vec![ms(1_050)]);
    match result.unwrap() {
        Outcome::Reply { frame, at } => {
            assert_eq!(frame.opcode(), 0xC9);
            assert_eq!(at - rig.start, second_c8 + ms(100));
        }
        other => panic!("expected the reply, got {other:?}"),
    }
    assert_eq!(resolved, second_c8 + ms(100));
}

/// Test: IT-020
#[tokio::test(start_paused = true)]
async fn step5_the_output_off_goes_before_the_queued_normal_requests() {
    let ble = Kind::Ble;
    let rig = link_rig(
        ble,
        "IT-020-5",
        Script {
            replies: vec![reply(ble, 0xC8, ms(100), &[0x00])],
            ..Script::default()
        },
    );
    let off = Command::from_reading(&capture_reading())
        .unwrap()
        .output(false)
        .encode();
    // Three normal requests and one output-off, queued at once.
    let a = track(rig.link.request(c8_volts(1.0)), rig.start);
    let b = track(rig.link.request(c8_volts(2.0)), rig.start);
    let c = track(rig.link.request(c8_volts(3.0)), rig.start);
    let o = track(rig.link.output_off(off.clone()), rig.start);
    for handle in [a, b, c, o] {
        assert!(matches!(handle.await.unwrap().1, Ok(Outcome::Reply { .. })));
    }
    let order: Vec<Vec<u8>> = rig.sent().into_iter().map(|(_, _, p)| p).collect();
    let position = |payload: &[u8]| order.iter().position(|p| p == payload).unwrap();
    let off_at = position(off.payload());
    let queued = [c8_volts(1.0), c8_volts(2.0), c8_volts(3.0)];
    // At most one of the three was already in flight; the output-off went
    // out before every other.
    assert!(off_at <= 1, "{order:?}");
    let before: Vec<usize> = queued
        .iter()
        .map(|f| position(f.payload()))
        .filter(|p| *p < off_at)
        .collect();
    assert!(before.len() <= 1, "{order:?}");
    assert_eq!(order.len(), 4);
}
