//! The `Transport` trait exercised generically with every double.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    missing_docs
)]

use core::time::Duration;

use mp305_core::protocol::ble::{BleRoute, Route};
use mp305_core::protocol::ops::telemetry;
use mp305_core::transport::description::Kind;
use mp305_core::transport::mock::{Mock, Reply, Script};
use mp305_core::transport::stub::Stub;
use mp305_core::transport::{AnyTransport, RawIncoming, Transport};
use tokio::time::Instant;

const AF01: Route = Route::Ble(BleRoute::Af01);

async fn exercise<T: Transport>(mut t: T) -> (u8, String) {
    t.send(&telemetry::request(), AF01).await.unwrap();
    let item = t.incoming().recv().await.unwrap();
    let opcode = item.item.unwrap().opcode();
    let description = t.description().to_string();
    t.close().await.unwrap();
    (opcode, description)
}

/// Test: UT-TRANS-006
#[tokio::test(start_paused = true)]
async fn stub_mock_and_any_transport_implement_the_trait() {
    let (stub, tx, sent) = Stub::new(Kind::Hid, "h", Duration::ZERO);
    tx.send(RawIncoming {
        route: Route::Hid,
        at: Instant::now(),
        item: Ok(telemetry::request()),
    })
    .unwrap();
    assert_eq!(exercise(stub).await, (0xC2, "hid h".to_string()));
    assert_eq!(sent.lock().unwrap().len(), 1);

    let reply = Reply {
        request: 0xC2,
        after: Duration::ZERO,
        route: AF01,
        deliveries: vec![vec![0x31, 0xC3, 0x00]],
        repeat: None,
    };
    let mock = Mock::new(
        Kind::Ble,
        "m",
        Script {
            replies: vec![reply.clone()],
            ..Script::default()
        },
    );
    assert_eq!(exercise(mock).await, (0xC3, "ble m".to_string()));

    let any = AnyTransport::Mock(Mock::new(
        Kind::Ble,
        "a",
        Script {
            replies: vec![reply],
            ..Script::default()
        },
    ));
    assert_eq!(exercise(any).await, (0xC3, "ble a".to_string()));
}
