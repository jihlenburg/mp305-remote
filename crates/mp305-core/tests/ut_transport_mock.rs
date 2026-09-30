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
