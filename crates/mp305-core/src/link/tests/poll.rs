//! Task tests: the poll and the USB keepalive.
//!
//! Implements: nothing; holds the tests of UT-LINK-019 and UT-LINK-020.

use super::*;
use crate::transport::test_log;
use log::Level;

/// Test: UT-LINK-019
#[tokio::test(start_paused = true)]
async fn every_poll_keeps_its_distance_from_the_previous_reading() {
    let log = test_log::install();
    let mut r = rig(Kind::Ble, Duration::ZERO);
    r.link.set_polling(true);
    r.auto_reply(ms(130), ms(10_000), answer_c2);
    r.until(ms(5_000)).await;
    let explicit = track(r.link.request(telemetry::request()));
    r.until(ms(10_000)).await;
    r.link.set_polling(false);
    let (when, result) = explicit.await.unwrap();
    let (_, at) = reply_of(result);
    assert!(when - r.start > ms(5_000));
    r.until(ms(15_000)).await;
    let writes = r.sent_times(0xC2);
    let readings: Vec<Duration> = r
        .drain_events()
        .into_iter()
        .filter_map(|e| match e {
            DeviceEvent::Reading { at, .. } => Some(at - r.start),
            _ => None,
        })
        .collect();
    // Every 0xC2 after the first goes out exactly 100 ms after the previous
    // reading, the explicit one included.
    for (write, previous) in writes.iter().skip(1).zip(readings.iter()) {
        assert_eq!(*write, *previous + ms(100), "{writes:?} {readings:?}");
    }
    assert!(readings.contains(&(at - r.start)));
    assert!(readings.iter().filter(|t| **t <= ms(10_000)).count() >= 40);
    assert!(writes.iter().all(|t| *t <= ms(10_000)), "{writes:?}");
    assert!(logged(&log, Level::Debug, "poll on"));
    assert!(logged(&log, Level::Debug, "poll off"));
}

/// Test: UT-LINK-020
#[tokio::test(start_paused = true)]
async fn usb_is_kept_alive_every_two_seconds_while_idle() {
    let log = test_log::install();
    let mut r = rig(Kind::Hid, Duration::ZERO);
    r.auto_reply(ms(50), ms(11_000), |f, _| (f.opcode() == 0xE0).then(e1));
    r.until(ms(10_001)).await;
    assert_eq!(
        r.sent(),
        (1..=5)
            .map(|i| (ms(2_000 * i), Route::Hid, 0xE0))
            .collect::<Vec<_>>()
    );
    assert!(r.drain_events().is_empty());
    assert!(logged(&log, Level::Debug, "keepalive"));
}

/// Test: UT-LINK-020
#[tokio::test(start_paused = true)]
async fn bluetooth_sends_nothing_on_its_own() {
    let r = rig(Kind::Ble, Duration::ZERO);
    r.until(ms(10_001)).await;
    assert!(r.sent().is_empty());
}

/// Test: UT-LINK-020
#[tokio::test(start_paused = true)]
async fn usb_polling_needs_no_keepalive() {
    let r = rig(Kind::Hid, Duration::ZERO);
    r.link.set_polling(true);
    r.auto_reply(ms(130), ms(11_000), answer_c2);
    r.until(ms(10_000)).await;
    let sent = r.sent();
    assert!(sent.iter().all(|(_, _, op)| *op == 0xC2));
    let mut previous = Duration::ZERO;
    for (t, _, _) in &sent {
        assert!(*t - previous <= ms(2_000));
        previous = *t;
    }
    assert!(ms(10_000) - previous <= ms(2_000));
}

/// Test: UT-LINK-019
#[tokio::test(start_paused = true)]
async fn an_explicit_poll_keeps_its_distance_with_polling_off() {
    let r = rig(Kind::Ble, Duration::ZERO);
    r.auto_reply(ms(130), ms(1_000), answer_c2);
    reply_of(r.link.request(telemetry::request()).await);
    // Issued at 130 ms, right after the reading: held back by the pause
    // alone, with no poll to wake the link.
    let (when, result) =
        tokio::time::timeout(ms(2_000), track(r.link.request(telemetry::request())))
            .await
            .expect("the explicit 0xC2 was never written")
            .unwrap();
    reply_of(result);
    assert_eq!(when - r.start, ms(360));
    assert_eq!(r.sent_times(0xC2), vec![Duration::ZERO, ms(230)]);
}
