//! Unit tests of the scripted mock transport.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    missing_docs
)]

use core::time::Duration;

use mp305_core::error::Error;
use mp305_core::protocol::ble::{BleRoute, Route};
use mp305_core::protocol::ops::{info, telemetry};
use mp305_core::transport::description::Kind;
use mp305_core::transport::mock::{Injection, Mock, MockFactory, Reply, Script, SendError};
use mp305_core::transport::Transport;
use tokio::time::{sleep, Instant};

const AF01: Route = Route::Ble(BleRoute::Af01);

/// 2026-09-29T193614-ble-readonly.jsonl, t = 12.8857: the `0xC3` notification on AF01.
const C3_NOTIFICATION: [u8; 38] = [
    0x31, 0xC3, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x14, 0x05, 0x00, 0x00, 0xE8, 0x03, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1A, 0x00,
    0x00, 0x01, 0x40, 0x06, 0x00, 0x00,
];
/// The same capture: the `0xC5` notification on AF01.
const C5_NOTIFICATION: [u8; 13] = [
    0x31, 0xC5, 0x5A, 0x02, 0x00, 0x00, 0x01, 0xF4, 0x01, 0x32, 0x00, 0x00, 0x00,
];

/// The `0xC3` reply as a HID stream (address 0x21, checksum over the unstuffed bytes).
fn c3_stream() -> Vec<u8> {
    let payload = &C3_NOTIFICATION[2..];
    let mut body = vec![0xC3];
    body.extend_from_slice(payload);
    let sum = mp305_core::protocol::hid::checksum(0x21, body.len() as u8, &body);
    let mut stream = vec![0xAA, 0x21, body.len() as u8];
    stream.extend(body);
    stream.push(sum);
    stream
}

/// Test: UT-TRANS-030
#[tokio::test(start_paused = true)]
async fn ble_mock_replies_injects_and_fails_as_scripted() {
    let script = Script {
        replies: vec![Reply {
            request: 0xC2,
            after: Duration::from_millis(200),
            route: AF01,
            deliveries: vec![C3_NOTIFICATION.to_vec()],
            repeat: Some(1),
            ..Reply::default()
        }],
        injections: vec![Injection {
            at: Duration::from_millis(300),
            route: AF01,
            delivery: C5_NOTIFICATION.to_vec(),
        }],
        send_errors: vec![SendError {
            opcode: 0xE0,
            from: Duration::ZERO,
        }],
        ..Script::default()
    };
    let mut mock = Mock::new(Kind::Ble, "m1", script);
    let start = Instant::now();
    mock.send(&telemetry::request(), AF01).await.unwrap();
    sleep(Duration::from_millis(10)).await;
    assert!(matches!(
        mock.send(&info::request(), AF01).await,
        Err(Error::Transport { .. })
    ));
    assert!(matches!(
        mock.send(&telemetry::request(), Route::Hid).await,
        Err(Error::Transport { .. })
    ));
    sleep(Duration::from_millis(340)).await;
    mock.send(&telemetry::request(), AF01).await.unwrap();
    sleep(Duration::from_millis(50)).await;
    let first = mock.incoming().recv().await.unwrap();
    assert_eq!(first.at - start, Duration::from_millis(200));
    assert_eq!(first.route, AF01);
    assert_eq!(first.item.unwrap().opcode(), 0xC3);
    let second = mock.incoming().recv().await.unwrap();
    assert_eq!(second.at - start, Duration::from_millis(300));
    assert_eq!(second.item.unwrap().opcode(), 0xC5);
    assert!(
        mock.incoming().try_recv().is_err(),
        "the second 0xC2 must get no reply"
    );
}

/// Test: UT-TRANS-031
#[tokio::test(start_paused = true)]
async fn hid_mock_decodes_across_reports_stops_and_closes() {
    let stream = c3_stream();
    assert_eq!(stream.len(), 41);
    let script = Script {
        replies: vec![Reply {
            request: 0xC2,
            after: Duration::ZERO,
            route: Route::Hid,
            deliveries: vec![stream[..30].to_vec(), stream[30..].to_vec()],
            repeat: None,
            ..Reply::default()
        }],
        stop_replying_at: Some(Duration::from_secs(2)),
        close_at: Some(Duration::from_secs(3)),
        ..Script::default()
    };
    let mut mock = Mock::new(Kind::Hid, "m2", script);
    let start = Instant::now();
    mock.send(&telemetry::request(), Route::Hid).await.unwrap();
    sleep(Duration::from_secs(1)).await;
    mock.send(&telemetry::request(), Route::Hid).await.unwrap();
    sleep(Duration::from_millis(1500)).await;
    mock.send(&telemetry::request(), Route::Hid).await.unwrap();
    let a = mock.incoming().recv().await.unwrap();
    assert_eq!(
        (a.at - start, a.item.unwrap().opcode()),
        (Duration::ZERO, 0xC3)
    );
    let b = mock.incoming().recv().await.unwrap();
    assert_eq!(
        (b.at - start, b.item.unwrap().opcode()),
        (Duration::from_secs(1), 0xC3)
    );
    sleep(Duration::from_secs(1)).await;
    assert!(
        mock.incoming().recv().await.is_none(),
        "closed at 3 s, nothing after 2 s"
    );
}

/// Test: UT-TRANS-032
#[tokio::test(start_paused = true)]
async fn mock_records_sends_and_the_factory_yields_fresh_mocks() {
    let mock = Mock::new(Kind::Ble, "m3", Script::default());
    let start = Instant::now();
    mock.send(&telemetry::request(), AF01).await.unwrap();
    sleep(Duration::from_millis(100)).await;
    mock.send(&info::request(), AF01).await.unwrap();
    sleep(Duration::from_millis(150)).await;
    mock.send(&telemetry::request(), AF01).await.unwrap();
    let sent = mock.sent();
    let times: Vec<_> = sent.iter().map(|s| s.at - start).collect();
    assert_eq!(
        times,
        vec![
            Duration::ZERO,
            Duration::from_millis(100),
            Duration::from_millis(250)
        ]
    );
    assert_eq!(sent[1].wire, vec![0x12, 0xE0]);
    assert_eq!(sent[0].frame.opcode(), 0xC2);
    let mut factory: MockFactory = Box::new(|| Mock::new(Kind::Ble, "f", Script::default()));
    let a = factory();
    let b = factory();
    assert!(!core::ptr::eq(&a, &b));
    assert_eq!(a.description().identifier, "f");
}

/// A reply to `0xC2` on AF01 at once, delivering an `0xC3` whose one payload
/// byte is `tag`, eligible from `from`, serving `repeat` requests.
fn tagged_c3(tag: u8, from: Duration, repeat: Option<usize>) -> Reply {
    Reply {
        request: 0xC2,
        after: Duration::ZERO,
        route: AF01,
        deliveries: vec![vec![0x31, 0xC3, tag]],
        repeat,
        from,
    }
}

/// Sends a `0xC2` and returns the tag of the `0xC3` that answers it.
async fn answer_tag(mock: &mut Mock) -> u8 {
    mock.send(&telemetry::request(), AF01).await.unwrap();
    let incoming = mock.incoming().recv().await.unwrap();
    let frame = incoming.item.unwrap();
    assert_eq!(frame.opcode(), 0xC3);
    frame.payload()[0]
}

/// Test: UT-TRANS-033
#[tokio::test(start_paused = true)]
async fn the_reply_with_the_latest_eligible_from_answers() {
    let second = Duration::from_secs(1);
    let script = Script {
        replies: vec![
            tagged_c3(0xA, Duration::ZERO, None),
            tagged_c3(0xB, second, Some(1)),
            tagged_c3(0xC, second, None),
        ],
        ..Script::default()
    };
    let start = Instant::now();
    let mut mock = Mock::new(Kind::Ble, "m4", script.clone());
    let mut tags = Vec::new();
    for at in [500, 1_200, 1_400, 2_000] {
        tokio::time::sleep_until(start + Duration::from_millis(at)).await;
        tags.push(answer_tag(&mut mock).await);
    }
    assert_eq!(tags, vec![0xA, 0xB, 0xC, 0xC]);
    // `from` counts from each mock's own creation.
    tokio::time::sleep_until(start + Duration::from_secs(3)).await;
    let mut later = Mock::new(Kind::Ble, "m5", script);
    sleep(Duration::from_millis(500)).await;
    assert_eq!(answer_tag(&mut later).await, 0xA);
}

/// Test: UT-TRANS-034
#[tokio::test(start_paused = true)]
async fn the_handle_sees_sends_and_closes_after_the_mock_moved_into_a_guard() {
    use mp305_core::transport::guarded::Guarded;
    use mp305_core::transport::AnyTransport;
    let start = Instant::now();
    let mock = Mock::new(Kind::Ble, "m6", Script::default());
    let handle = mock.handle();
    let guard = Guarded::new(AnyTransport::from(mock));
    // A twin that stays outside a guard and gets the same sends at the same
    // times: its `sent()` is what the moved mock's would have been.
    let twin = Mock::new(Kind::Ble, "m7", Script::default());
    guard.send(&telemetry::request(), AF01).await.unwrap();
    twin.send(&telemetry::request(), AF01).await.unwrap();
    sleep(Duration::from_millis(100)).await;
    guard.send(&info::request(), AF01).await.unwrap();
    twin.send(&info::request(), AF01).await.unwrap();
    let seen = handle.sent();
    let expected = twin.sent();
    assert_eq!(seen.len(), 2);
    assert_eq!(expected.len(), 2);
    for (s, e) in seen.iter().zip(&expected) {
        assert_eq!(
            (s.at, s.route, &s.frame, &s.wire),
            (e.at, e.route, &e.frame, &e.wire)
        );
    }
    assert_eq!(
        seen.iter().map(|s| s.at - start).collect::<Vec<_>>(),
        vec![Duration::ZERO, Duration::from_millis(100)]
    );
    assert_eq!(seen[0].wire, vec![0x12, 0xC2]);
    assert_eq!(seen[1].wire, vec![0x12, 0xE0]);
    assert_eq!(handle.closes(), 0);
    guard.close().await.unwrap();
    guard.close().await.unwrap();
    assert_eq!(handle.closes(), 2);
}
