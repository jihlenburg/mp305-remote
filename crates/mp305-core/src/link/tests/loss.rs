//! Task tests: loss detection, close and drop.
//!
//! Implements: nothing; holds the tests of UT-LINK-021 to 025 and part of UT-LINK-028.

use super::*;
use crate::link::LossReason;
use crate::protocol::ops::info;
use crate::protocol::timing;
use crate::transport::guarded::Item;
use crate::transport::test_log;
use log::Level;

/// Collects every event with its delivery time until `Events` yields `None`.
fn collect(mut events: Events) -> JoinHandle<Vec<(Instant, DeviceEvent)>> {
    tokio::spawn(async move {
        let mut all = Vec::new();
        while let Some(event) = events.next().await {
            all.push((Instant::now(), event));
        }
        all
    })
}

/// The text of `LossReason::Unanswered`.
const UNANSWERED: &str = "three requests in a row went unanswered";

/// The flow of UT-LINK-021: the supply falls silent while polling, with a
/// deferred bind open and two requests from the caller.
pub(super) async fn flow_021() {
    let r = rig(Kind::Ble, Duration::ZERO);
    let (_, result) = track(r.link.request(bind_request(false))).await.unwrap();
    let Ok(Outcome::Deferred(bind)) = result else {
        panic!("expected a deferred bind")
    };
    let bind = tokio::spawn(bind);
    r.link.set_polling(true);
    r.auto_reply(ms(130), ms(2_000), answer_c2);
    let Rig {
        link,
        events,
        sends,
        stub,
        start,
        ..
    } = r;
    let events = collect(events);
    // The last C2 before 2 s goes out at 1.84 s, its reading arrives at t.
    let t = ms(1_970);
    sleep_until(start + t + ms(500)).await;
    let info_req = track(link.request(info::request()));
    sleep_until(start + t + ms(2_500)).await;
    let tel_req = track(link.request(telemetry::request()));
    let events = events.await.unwrap();
    let readings: Vec<Duration> = events
        .iter()
        .filter_map(|(_, e)| match e {
            DeviceEvent::Reading { at, .. } => Some(*at - start),
            _ => None,
        })
        .collect();
    assert_eq!(readings.last(), Some(&t));
    let (lost_at, last) = events.last().unwrap();
    assert_eq!(
        *last,
        DeviceEvent::LinkLost {
            reason: LossReason::Unanswered
        }
    );
    assert_eq!(*lost_at - start, t + ms(3_100));
    assert!(*lost_at - start - t <= timing::LINK_LOSS_REPORT);
    let (when, result) = info_req.await.unwrap();
    assert_eq!(when - start, t + ms(2_100));
    assert!(matches!(result, Err(Error::Timeout { opcode: 0xE0, .. })));
    let lost = Error::LinkLost {
        text: UNANSWERED.to_string(),
    };
    assert_eq!(tel_req.await.unwrap().1.unwrap_err(), lost);
    assert_eq!(bind.await.unwrap().unwrap_err(), lost);
    sleep(ms(1)).await;
    assert_eq!(stub.closes(), 1);
    let after_t: Vec<(Duration, u8)> = sends
        .lock()
        .unwrap()
        .iter()
        .map(|(at, _, f)| (*at - start, f.opcode()))
        .filter(|(at, _)| *at > t)
        .collect();
    assert_eq!(
        after_t,
        vec![
            (t + ms(100), 0xC2),
            (t + ms(1_100), 0xE0),
            (t + ms(2_100), 0xC2)
        ]
    );
    assert_eq!(link.request(info::request()).await.unwrap_err(), lost);
}

/// Test: UT-LINK-021
#[tokio::test(start_paused = true)]
async fn three_unanswered_requests_end_the_link_within_four_seconds() {
    flow_021().await;
}

/// Test: UT-LINK-022
#[tokio::test(start_paused = true)]
async fn only_consecutive_timeouts_count() {
    let log = test_log::install();
    let mut r = rig(Kind::Ble, Duration::ZERO);
    r.link.set_polling(true);
    r.auto_reply(ms(130), ms(8_000), |f, at| {
        (f.opcode() == 0xC2 && at >= ms(1_500) && at < ms(2_100)).then(c3)
    });
    r.until(ms(3_500)).await;
    r.link.set_polling(false);
    r.until(ms(4_500)).await;
    let info_req = track(r.link.request(info::request()));
    r.feed_at(ms(4_600), e1());
    reply_of(info_req.await.unwrap().1);
    r.until(ms(5_000)).await;
    r.link.set_polling(true);
    r.until(ms(6_500)).await;
    r.link.set_polling(false);
    r.until(ms(9_000)).await;
    assert!(r
        .drain_events()
        .iter()
        .all(|e| !matches!(e, DeviceEvent::LinkLost { .. })));
    let timeouts = log
        .lines_here(TARGET)
        .iter()
        .filter(|(l, m)| *l == Level::Debug && m.starts_with("timeout 0xc2"))
        .count();
    assert_eq!(timeouts, 6, "{:?}", log.lines_here(TARGET));
    let polls: Vec<Duration> = r.sent_times(0xC2);
    assert_eq!(
        polls,
        vec![
            Duration::ZERO,
            ms(1_000),
            ms(2_000),
            ms(2_230),
            ms(3_230),
            ms(5_000),
            ms(6_000)
        ]
    );
}

/// Test: UT-LINK-023
#[tokio::test(start_paused = true)]
async fn a_closed_transport_ends_the_link() {
    let r = rig(Kind::Ble, Duration::ZERO);
    let Rig {
        link,
        events,
        tx,
        sends,
        stub,
        start,
        ..
    } = r;
    let events = collect(events);
    let first = track(link.request(info::request()));
    sleep_until(start + ms(100)).await;
    let second = track(link.request(telemetry::request()));
    sleep_until(start + ms(500)).await;
    drop(tx);
    let events = events.await.unwrap();
    let (at, last) = events.last().unwrap();
    assert_eq!(*at - start, ms(500));
    assert_eq!(
        *last,
        DeviceEvent::LinkLost {
            reason: LossReason::Disconnected
        }
    );
    let lost = Error::LinkLost {
        text: "the transport reported the link closed".to_string(),
    };
    assert_eq!(first.await.unwrap().1.unwrap_err(), lost);
    assert_eq!(second.await.unwrap().1.unwrap_err(), lost);
    sleep(ms(1_000)).await;
    assert_eq!(sends.lock().unwrap().len(), 1);
    assert_eq!(stub.closes(), 1);
}

/// Test: UT-LINK-023
#[tokio::test(start_paused = true)]
async fn a_failed_write_ends_the_link() {
    let r = rig_with(Kind::Ble, Duration::ZERO, |s| s.fail_next_send("boom"));
    let Rig {
        link,
        events,
        sends,
        stub,
        start,
        ..
    } = r;
    let events = collect(events);
    let first = track(link.request(info::request()));
    let second = track(link.request(telemetry::request()));
    let events = events.await.unwrap();
    let (at, last) = events.last().unwrap();
    assert_eq!(*at, start);
    assert_eq!(
        *last,
        DeviceEvent::LinkLost {
            reason: LossReason::Transport("transport: boom".to_string())
        }
    );
    assert!(matches!(
        first.await.unwrap().1,
        Err(Error::LinkLost { .. })
    ));
    assert!(matches!(
        second.await.unwrap().1,
        Err(Error::LinkLost { .. })
    ));
    sleep(ms(1_000)).await;
    assert!(sends.lock().unwrap().is_empty());
    assert_eq!(stub.closes(), 1);
}

/// Test: UT-LINK-023
#[tokio::test(start_paused = true)]
async fn an_overlong_write_ends_the_link() {
    let r = rig(Kind::Ble, ms(2_000));
    let Rig {
        link,
        events,
        sends,
        stub,
        start,
        ..
    } = r;
    let events = collect(events);
    let req = track(link.request(info::request()));
    let events = events.await.unwrap();
    let (at, last) = events.last().unwrap();
    assert_eq!(*at - start, ms(1_000));
    assert_eq!(
        *last,
        DeviceEvent::LinkLost {
            reason: LossReason::Transport(
                "the write of 0xe0 did not complete within 1.0 s".to_string()
            )
        }
    );
    assert!(matches!(req.await.unwrap().1, Err(Error::LinkLost { .. })));
    sleep(ms(3_000)).await;
    assert_eq!(sends.lock().unwrap().len(), 1);
    assert_eq!(stub.closes(), 1);
}

/// Test: UT-LINK-024
#[tokio::test(start_paused = true)]
async fn undecodable_frames_are_dropped_and_the_link_goes_on() {
    let mut r = rig(Kind::Ble, Duration::ZERO);
    r.link.set_polling(true);
    r.auto_reply(ms(130), ms(3_000), answer_c2);
    let bad = Reason::BadChecksum {
        expected: 0x7F,
        got: 0,
    };
    r.feed_error_at(ms(300), bad.clone());
    r.feed_error_at(ms(700), bad);
    r.until(ms(2_000)).await;
    assert_eq!(r.link.counters().dropped_frames, 2);
    let events = r.drain_events();
    assert!(events
        .iter()
        .all(|e| !matches!(e, DeviceEvent::LinkLost { .. })));
    assert!(events
        .iter()
        .any(|e| matches!(e, DeviceEvent::Reading { at, .. } if *at - r.start > ms(1_500))));
}

/// Test: UT-LINK-025
#[tokio::test(start_paused = true)]
async fn close_resolves_everything_and_closes_the_transport() {
    let log = test_log::install();
    let r = rig(Kind::Ble, Duration::ZERO);
    let Rig {
        link,
        mut events,
        stub,
        start,
        ..
    } = r;
    let first = track(link.request(info::request()));
    let second = track(link.request(telemetry::request()));
    sleep_until(start + ms(200)).await;
    link.close().await.unwrap();
    assert_eq!(Instant::now() - start, ms(200));
    let lost = Error::LinkLost {
        text: "closed by the host".to_string(),
    };
    assert_eq!(first.await.unwrap().1.unwrap_err(), lost);
    assert_eq!(second.await.unwrap().1.unwrap_err(), lost);
    assert_eq!(events.next().await, None);
    assert_eq!(stub.closes(), 1);
    assert!(logged(&log, Level::Debug, "closed"));
}

/// Test: UT-LINK-025
#[tokio::test(start_paused = true)]
async fn dropping_the_link_ends_it() {
    let r = rig(Kind::Ble, Duration::ZERO);
    let Rig {
        link, mut events, ..
    } = r;
    let req = track(link.request(info::request()));
    sleep(ms(100)).await;
    drop(link);
    assert_eq!(events.next().await, None);
    assert!(matches!(req.await.unwrap().1, Err(Error::LinkLost { .. })));
}

/// Test: UT-LINK-028
#[tokio::test(start_paused = true)]
async fn dropped_frames_agree_with_the_guard_for_a_decode_error() {
    let bad = || RawIncoming {
        route: Route::Ble(BleRoute::Af01),
        at: Instant::now(),
        item: Err(Reason::BadPrefix),
    };
    let (stub, tx, _) = Stub::new(Kind::Ble, "g", Duration::ZERO);
    let mut guarded = Guarded::new(stub);
    tx.send(bad()).unwrap();
    assert!(matches!(
        guarded.recv().await.unwrap().item,
        Item::Error(Reason::BadPrefix)
    ));
    let r = rig(Kind::Ble, Duration::ZERO);
    r.tx.send(bad()).unwrap();
    sleep(ms(1)).await;
    assert_eq!(guarded.errors(), 1);
    assert_eq!(r.link.counters().dropped_frames, guarded.errors());
}
