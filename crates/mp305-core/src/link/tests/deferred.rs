//! Task tests: deferred requests and their expectations.
//!
//! Implements: nothing; holds the tests of UT-LINK-012 to 015.

use super::*;
use crate::link::Pending;
use crate::protocol::ops::info;
use crate::transport::test_log;
use log::Level;

/// The `Pending` of a deferred outcome.
fn pending_of(result: Result<Outcome, Error>) -> Pending {
    match result {
        Ok(Outcome::Deferred(pending)) => pending,
        other => panic!("expected a deferred outcome, got {other:?}"),
    }
}

/// What a `Pending` resolved with, and when.
type Resolved = (Instant, Result<(Frame, Instant), Error>);

/// Awaits a `Pending` in a task and records when it resolved.
fn track_pending(pending: Pending) -> JoinHandle<Resolved> {
    tokio::spawn(async move {
        let result = pending.await;
        (Instant::now(), result)
    })
}

/// Test: UT-LINK-012
#[tokio::test(start_paused = true)]
async fn a_prompt_bind_is_deferred_while_the_poll_runs() {
    let log = test_log::install();
    let mut r = rig(Kind::Ble, Duration::ZERO);
    let bind = track(r.link.request(bind_request(false)));
    r.link.set_polling(true);
    r.auto_reply(ms(130), ms(12_000), answer_c2);
    r.feed_at(ms(12_000), r19(0));
    let (when, result) = bind.await.unwrap();
    assert_eq!(when, r.start);
    let pending = pending_of(result);
    assert_eq!(pending.opcode(), 0x18);
    assert_eq!(pending.deadline(), r.at(ms(30_000)));
    let pending = track_pending(pending);
    let (when, result) = pending.await.unwrap();
    assert_eq!(when - r.start, ms(12_000));
    let (frame, at) = result.unwrap();
    assert_eq!(frame, r19(0));
    assert_eq!(at - r.start, ms(12_000));
    let sent = r.sent();
    assert_eq!(sent[0], (Duration::ZERO, Route::Ble(BleRoute::Af02), 0x18));
    assert_eq!(sent[1], (Duration::ZERO, Route::Ble(BleRoute::Af01), 0xC2));
    let polls = r
        .sent_times(0xC2)
        .into_iter()
        .filter(|t| *t <= ms(12_000))
        .count();
    assert!(polls >= 40, "{polls}");
    let events = r.drain_events();
    let readings = events
        .iter()
        .filter(|e| matches!(e, DeviceEvent::Reading { at, .. } if *at - r.start <= ms(12_000)))
        .count();
    assert!(readings >= 40, "{readings}");
    assert!(!events
        .iter()
        .any(|e| matches!(e, DeviceEvent::LateReply { .. })));
    assert!(logged(&log, Level::Debug, "deferred 0x18 until +30000"));
}

/// Test: UT-LINK-013
#[tokio::test(start_paused = true)]
async fn a_prompt_bind_times_out_thirty_seconds_after_the_connection() {
    let r = rig(Kind::Ble, Duration::ZERO);
    r.until(ms(5_000)).await;
    let (when, result) = track(r.link.request(bind_request(false))).await.unwrap();
    assert_eq!(when - r.start, ms(5_000));
    let (when, result) = track_pending(pending_of(result)).await.unwrap();
    assert_eq!(when - r.start, ms(30_000));
    let error = result.unwrap_err();
    assert_eq!(
        error,
        Error::Timeout {
            opcode: 0x18,
            after: ms(30_000)
        }
    );
    assert_eq!(error.to_string(), "no reply to 0x18 within 30.0 s");
}

/// Test: UT-LINK-013
#[tokio::test(start_paused = true)]
async fn a_remote_request_times_out_after_seventy_seconds_and_sets_the_block() {
    let r = rig(Kind::Ble, Duration::ZERO);
    let (_, result) = track(r.link.request(c8(2, 0))).await.unwrap();
    let (when, result) = track_pending(pending_of(result)).await.unwrap();
    assert_eq!(when - r.start, ms(70_000));
    let error = result.unwrap_err();
    assert_eq!(
        error,
        Error::Timeout {
            opcode: 0xC8,
            after: ms(70_000)
        }
    );
    assert_eq!(error.to_string(), "no reply to 0xc8 within 70.0 s");
    let next = track(r.link.request(c8(1, 1)));
    r.feed_at(ms(70_130), c3());
    r.feed_at(ms(70_200), c9(0));
    reply_of(next.await.unwrap().1);
    let sent: Vec<(Duration, u8)> = r.sent().into_iter().map(|(t, _, op)| (t, op)).collect();
    assert_eq!(
        sent,
        vec![
            (Duration::ZERO, 0xC8),
            (ms(70_000), 0xC2),
            (ms(70_130), 0xC8)
        ]
    );
}

/// Test: UT-LINK-013
#[tokio::test(start_paused = true)]
async fn a_prompt_bind_after_thirty_seconds_is_not_written() {
    let r = rig(Kind::Ble, Duration::ZERO);
    r.until(ms(31_000)).await;
    let (when, result) = track(r.link.request(bind_request(false))).await.unwrap();
    assert_eq!(when - r.start, ms(31_000));
    assert_eq!(
        result.unwrap_err(),
        Error::Timeout {
            opcode: 0x18,
            after: ms(30_000)
        }
    );
    sleep(ms(1)).await;
    assert!(r.sent().is_empty());
}

/// Test: UT-LINK-014
#[tokio::test(start_paused = true)]
async fn nothing_waits_on_an_open_expectation_for_its_reply() {
    let r = rig(Kind::Ble, Duration::ZERO);
    let (_, result) = track(r.link.request(c8(2, 0))).await.unwrap();
    let remote = track_pending(pending_of(result));
    r.until(ms(100)).await;
    let command = track(r.link.request(c8(1, 1)));
    r.until(ms(200)).await;
    let info_req = track(r.link.request(info::request()));
    r.feed_at(ms(3_000), c9(0));
    r.feed_at(ms(3_200), c9(0));
    r.feed_at(ms(3_400), e1());
    let (when, result) = remote.await.unwrap();
    assert_eq!(when - r.start, ms(3_000));
    assert_eq!(result.unwrap().0, c9(0));
    let (when, result) = command.await.unwrap();
    assert_eq!(when - r.start, ms(3_200));
    reply_of(result);
    let (when, result) = info_req.await.unwrap();
    assert_eq!(when - r.start, ms(3_400));
    reply_of(result);
    let sent: Vec<(Duration, u8)> = r.sent().into_iter().map(|(t, _, op)| (t, op)).collect();
    assert_eq!(
        sent,
        vec![(Duration::ZERO, 0xC8), (ms(3_000), 0xC8), (ms(3_200), 0xE0)]
    );
}

/// Test: UT-LINK-014
#[tokio::test(start_paused = true)]
async fn a_fast_bind_waits_for_an_open_prompt_bind() {
    let r = rig(Kind::Ble, Duration::ZERO);
    let (_, result) = track(r.link.request(bind_request(false))).await.unwrap();
    let prompt = track_pending(pending_of(result));
    r.until(ms(100)).await;
    let fast = track(r.link.request(bind_request(true)));
    r.feed_at(ms(1_000), r19(0));
    r.feed_at(ms(1_100), r19(0));
    let (when, result) = prompt.await.unwrap();
    assert_eq!(when - r.start, ms(1_000));
    result.unwrap();
    let (when, result) = fast.await.unwrap();
    assert_eq!(when - r.start, ms(1_100));
    reply_of(result);
    assert_eq!(r.sent_times(0x18), vec![Duration::ZERO, ms(1_000)]);
}

/// Test: UT-LINK-015
#[tokio::test(start_paused = true)]
async fn a_reply_to_a_dropped_pending_becomes_a_late_reply() {
    let log = test_log::install();
    let mut r = rig(Kind::Ble, Duration::ZERO);
    let (_, result) = track(r.link.request(bind_request(false))).await.unwrap();
    let pending = pending_of(result);
    r.until(ms(1_000)).await;
    drop(pending);
    r.feed_at(ms(2_000), r19(0));
    r.until(ms(3_000)).await;
    let _second = r.link.request(bind_request(false));
    sleep(ms(1)).await;
    let events = r.drain_events();
    assert!(
        matches!(&events[..], [DeviceEvent::LateReply { frame, at }]
            if *frame == r19(0) && *at - r.start == ms(2_000)),
        "{events:?}"
    );
    assert_eq!(r.link.counters().late_replies, 1);
    assert!(logged(&log, Level::Warn, "late reply 0x19 (unawaited)"));
    assert_eq!(r.sent_times(0x18), vec![Duration::ZERO, ms(3_000)]);
}
