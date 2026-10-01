//! Task tests: requests, replies, timeouts, dispatch, cancellation.
//!
//! Implements: nothing; holds the tests of UT-LINK-005 to 011 and UT-LINK-027.

use super::*;
use crate::link::Counters;
use crate::protocol::ops::events::DeviceFrame;
use crate::protocol::ops::info;
use crate::transport::test_log;
use log::Level;
use tokio::time::advance;

/// The flow of UT-LINK-005: one `0xC2` answered at 130 ms.
pub(super) async fn flow_005() {
    let mut r = rig(Kind::Ble, Duration::ZERO);
    let req = track(r.link.request(telemetry::request()));
    r.feed_at(ms(130), c3());
    let (when, result) = req.await.unwrap();
    let (frame, at) = reply_of(result);
    assert_eq!(frame, c3());
    assert_eq!(at - r.start, ms(130));
    assert_eq!(when - r.start, ms(130));
    assert_eq!(
        r.sent(),
        vec![(Duration::ZERO, Route::Ble(BleRoute::Af01), 0xC2)]
    );
    let events = r.drain_events();
    assert_eq!(events.len(), 1);
    assert!(
        matches!(&events[0], DeviceEvent::Reading { at, .. } if *at - r.start == ms(130)),
        "{events:?}"
    );
    assert_eq!(r.link.counters(), Counters::default());
    assert_eq!(r.link.description().to_string(), "ble stub");
}

/// The flow of UT-LINK-007: an unanswered `0xE0`, then a `0xC2`.
pub(super) async fn flow_007() {
    let mut r = rig(Kind::Ble, Duration::ZERO);
    let first = track(r.link.request(info::request()));
    let second = track(r.link.request(telemetry::request()));
    r.feed_at(ms(1100), c3());
    let (when, result) = first.await.unwrap();
    assert_eq!(when - r.start, ms(1000));
    assert_eq!(
        result.unwrap_err(),
        Error::Timeout {
            opcode: 0xE0,
            after: ms(1000)
        }
    );
    let (when, result) = second.await.unwrap();
    assert_eq!(when - r.start, ms(1100));
    reply_of(result);
    assert_eq!(r.sent_times(0xC2), vec![ms(1000)]);
    assert!(r
        .drain_events()
        .iter()
        .all(|e| !matches!(e, DeviceEvent::LinkLost { .. })));
}

/// Test: UT-LINK-005
#[tokio::test(start_paused = true)]
async fn a_request_is_written_and_resolved_with_its_reply() {
    flow_005().await;
}

/// Test: UT-LINK-005
#[test]
fn start_outside_a_runtime_fails() {
    let (stub, _tx, _sends) = Stub::new(Kind::Ble, "s", Duration::ZERO);
    let result = Link::start(Guarded::new(stub), Instant::now());
    assert!(matches!(result, Err(Error::Transport { .. })));
}

/// Test: UT-LINK-006
#[tokio::test(start_paused = true)]
async fn requests_go_out_one_at_a_time_in_order() {
    let r = rig(Kind::Ble, ms(50));
    let first = r.link.request(info::request());
    let second = r.link.request(telemetry::request());
    r.feed_at(ms(300), e1());
    r.feed_at(ms(600), c3());
    let (a, b) = tokio::join!(first, second);
    reply_of(a);
    reply_of(b);
    let sent: Vec<(Duration, u8)> = r.sent().into_iter().map(|(t, _, op)| (t, op)).collect();
    assert_eq!(sent, vec![(Duration::ZERO, 0xE0), (ms(300), 0xC2)]);
}

/// Test: UT-LINK-007
#[tokio::test(start_paused = true)]
async fn an_unanswered_request_times_out_after_one_second() {
    flow_007().await;
}

/// Test: UT-LINK-008
#[tokio::test(start_paused = true)]
async fn incoming_frames_are_dispatched_counted_and_logged() {
    let log = test_log::install();
    let mut r = rig(Kind::Ble, Duration::ZERO);
    let req = track(r.link.request(telemetry::request()));
    let c5 = Frame::new(
        0xC5,
        vec![
            0x5A, 0x02, 0x00, 0x00, 0x01, 0xF4, 0x01, 0x32, 0x00, 0x00, 0x00,
        ],
    )
    .unwrap();
    let frames = [
        c5,
        Frame::new(0xDD, vec![1, 6]).unwrap(),
        Frame::new(0xE5, vec![7]).unwrap(),
        Frame::new(0xEB, vec![0; 20]).unwrap(),
        Frame::new(0xDB, vec![0]).unwrap(),
        c9(0),
        Frame::new(0x77, vec![]).unwrap(),
        Frame::new(0xC5, vec![0; 3]).unwrap(),
        Frame::new(0xC3, vec![0; 35]).unwrap(),
        c3(),
    ];
    for (i, frame) in frames.into_iter().enumerate() {
        r.feed_at(ms(10 * (i as u64 + 1)), frame);
    }
    let (when, result) = req.await.unwrap();
    assert_eq!(when - r.start, ms(100));
    assert_eq!(reply_of(result).0, c3());
    let events = r.drain_events();
    assert_eq!(events.len(), 7, "{events:?}");
    assert!(matches!(
        events[0],
        DeviceEvent::Device(DeviceFrame::Settings(_))
    ));
    assert!(matches!(
        events[1],
        DeviceEvent::Device(DeviceFrame::SelectedProgram(_))
    ));
    assert!(matches!(
        events[2],
        DeviceEvent::Device(DeviceFrame::ActivePdProfile(_))
    ));
    assert!(matches!(
        events[3],
        DeviceEvent::Device(DeviceFrame::ChargeSettings(_))
    ));
    assert!(matches!(
        events[4],
        DeviceEvent::Device(DeviceFrame::ProgramStepsSaved(_))
    ));
    assert!(matches!(&events[5], DeviceEvent::LateReply { frame, .. } if frame.opcode() == 0xC9));
    assert!(matches!(events[6], DeviceEvent::Reading { .. }));
    assert_eq!(
        r.link.counters(),
        Counters {
            dropped_frames: 2,
            ignored: 1,
            late_replies: 1
        }
    );
    assert!(logged(&log, Level::Warn, "ignored 0x77"));
    assert!(logged(&log, Level::Warn, "dropped 0xc5: "));
    assert!(logged(&log, Level::Warn, "dropped 0xc3: "));
}

/// One round of UT-LINK-009's first case: the `0xE1` stamped with the
/// deadline instant is in the channel when the clock reaches the deadline.
/// Returns whether the request resolved with the reply.
async fn reply_at_the_deadline() -> bool {
    let r = rig(Kind::Ble, Duration::ZERO);
    let req = track(r.link.request(info::request()));
    let (tx, deadline) = (r.tx.clone(), r.at(ms(1000)));
    // Fed from a spawned task, so that the scheduler turns the timer driver
    // after it and before the link task runs.
    tokio::spawn(async move {
        sleep_until(deadline - ms(1)).await;
        tx.send(RawIncoming {
            route: Route::Ble(BleRoute::Af01),
            at: deadline,
            item: Ok(e1()),
        })
        .unwrap();
        advance(ms(1)).await;
    });
    let (_, result) = req.await.unwrap();
    matches!(result, Ok(Outcome::Reply { at, .. }) if at - r.start == ms(1000))
}

/// Test: UT-LINK-009
#[test]
fn a_reply_at_the_deadline_instant_wins_over_the_deadline() {
    // `event_interval(1)` makes the scheduler turn the timer driver after
    // every task it polls, so the deadline has fired by the time the link
    // task sees the frame: both select arms are ready at once and only the
    // bias decides. Twenty rounds make an unbiased select fail with near
    // certainty.
    let runtime = tokio::runtime::Builder::new_current_thread()
        .enable_time()
        .start_paused(true)
        .event_interval(1)
        .build()
        .unwrap();
    runtime.block_on(async {
        let log = test_log::install();
        for round in 0..20 {
            assert!(reply_at_the_deadline().await, "round {round}");
        }
        assert!(!logged(&log, Level::Debug, "timeout 0xe0"));
    });
}

/// Test: UT-LINK-009
#[tokio::test(start_paused = true)]
async fn a_reply_after_the_deadline_is_ignored() {
    let r = rig(Kind::Ble, Duration::ZERO);
    let req = track(r.link.request(info::request()));
    let late = r.at(ms(1000)) + Duration::from_nanos(1);
    sleep_until(late).await;
    r.tx.send(RawIncoming {
        route: Route::Ble(BleRoute::Af01),
        at: late,
        item: Ok(e1()),
    })
    .unwrap();
    let (when, result) = req.await.unwrap();
    assert_eq!(when - r.start, ms(1000));
    assert!(matches!(result, Err(Error::Timeout { opcode: 0xE0, .. })));
    sleep(ms(1)).await;
    assert_eq!(r.link.counters().ignored, 1);
}

/// Test: UT-LINK-010
#[tokio::test(start_paused = true)]
async fn a_request_dropped_before_its_write_is_never_written() {
    let log = test_log::install();
    let r = rig(Kind::Ble, ms(100));
    let first = track(r.link.request(info::request()));
    r.feed_at(ms(300), e1());
    r.until(ms(50)).await;
    let dropped = r.link.request(telemetry::request());
    r.until(ms(100)).await;
    drop(dropped);
    let (when, result) = first.await.unwrap();
    assert_eq!(when - r.start, ms(300));
    reply_of(result);
    let again = track(r.link.request(info::request()));
    r.feed_at(ms(500), e1());
    reply_of(again.await.unwrap().1);
    let sent: Vec<(Duration, u8)> = r.sent().into_iter().map(|(t, _, op)| (t, op)).collect();
    assert_eq!(sent, vec![(Duration::ZERO, 0xE0), (ms(300), 0xE0)]);
    assert!(logged(&log, Level::Debug, "cancelled 0xc2"));
}

/// Test: UT-LINK-010
#[tokio::test(start_paused = true)]
async fn an_output_off_is_written_although_its_future_was_dropped() {
    let r = rig(Kind::Ble, Duration::ZERO);
    drop(r.link.output_off(c8(1, 0)));
    sleep(ms(1)).await;
    assert_eq!(r.sent_times(0xC8), vec![Duration::ZERO]);
}

/// Test: UT-LINK-011
#[tokio::test(start_paused = true)]
async fn a_frame_the_guard_refuses_fails_alone() {
    let r = rig(Kind::Ble, Duration::ZERO);
    let refused = r.link.request(Frame::new(0xC6, vec![]).unwrap());
    let info_req = track(r.link.request(info::request()));
    r.feed_at(ms(100), e1());
    assert_eq!(
        refused.await.unwrap_err(),
        Error::Protocol(Reason::NotAllowed(0xC6))
    );
    reply_of(info_req.await.unwrap().1);
    let sent: Vec<(Duration, u8)> = r.sent().into_iter().map(|(t, _, op)| (t, op)).collect();
    assert_eq!(sent, vec![(Duration::ZERO, 0xE0)]);
}

/// Test: UT-LINK-027
#[tokio::test(start_paused = true)]
async fn the_link_log_names_what_happened() {
    let log = test_log::install();
    flow_005().await;
    flow_007().await;
    super::loss::flow_021().await;
    for (level, line) in [
        (Level::Debug, "sent 0xc2 immediate"),
        (Level::Debug, "reply 0xc3 +130"),
        (Level::Debug, "timeout 0xe0 after 1000"),
        (Level::Debug, "poll on"),
        (
            Level::Debug,
            "lost: three requests in a row went unanswered",
        ),
    ] {
        assert!(
            log.lines_here(TARGET)
                .iter()
                .any(|(l, m)| *l == level && m == line),
            "{line}: {:?}",
            log.lines_here(TARGET)
        );
    }
}
