//! Integration test IT-050 (AR-050), the core part (`it_errors.rs`): every
//! variant of the one `Error` enum is triggered through the public API on
//! the scripted mock, and `NotFound` carries the four causes of SR-005.
//! The mapping of each variant to its Python exception and to the app's
//! message lives in `mp305-py` and `mp305-app`, which this crate's tests
//! cannot depend on; the entry's other test file,
//! `tests/integration/test_exceptions.py`, covers the Python mapping.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    missing_docs
)]

mod common;

use std::collections::BTreeSet;
use std::sync::Arc;

use mp305_core::discovery;
use mp305_core::error::Error;
use mp305_core::protocol::ble::{self, BleRoute, Route};
use mp305_core::protocol::fixtures;
use mp305_core::protocol::ops::telemetry;
use mp305_core::session::doubles::{MemoryMarkers, MockConnector};
use mp305_core::session::{Connector, Markers, Session};
use mp305_core::store::Store;
use mp305_core::transport::description::Kind;
use mp305_core::transport::guarded::Guarded;
use mp305_core::transport::mock::{Mock, Script, SendError};

use common::{
    granted, host_id, ms, options, reply, reply_with, script, secs, start, start_with, T0,
};

/// The variant's name. The match has no wildcard arm, so a variant added
/// to `Error` does not compile here until this test triggers it too.
fn variant(error: &Error) -> &'static str {
    match error {
        Error::Protocol(_) => "Protocol",
        Error::SetpointRange { .. } => "SetpointRange",
        Error::Mode { .. } => "Mode",
        Error::Transport { .. } => "Transport",
        Error::Timeout { .. } => "Timeout",
        Error::LinkLost { .. } => "LinkLost",
        Error::ConnectionDenied => "ConnectionDenied",
        Error::RemoteControlDenied => "RemoteControlDenied",
        Error::RemoteControlLost => "RemoteControlLost",
        Error::CommandRejected { .. } => "CommandRejected",
        Error::FaultActive { .. } => "FaultActive",
        Error::NotReady => "NotReady",
        Error::Store { .. } => "Store",
        Error::AlreadyOpen { .. } => "AlreadyOpen",
        Error::Cancelled { .. } => "Cancelled",
        Error::NotFound { .. } => "NotFound",
    }
}

/// AR-050's sixteen variants.
const AR_050: [&str; 16] = [
    "NotFound",
    "ConnectionDenied",
    "RemoteControlDenied",
    "RemoteControlLost",
    "SetpointRange",
    "CommandRejected",
    "Mode",
    "FaultActive",
    "NotReady",
    "Timeout",
    "LinkLost",
    "Transport",
    "Store",
    "Protocol",
    "AlreadyOpen",
    "Cancelled",
];

/// Test: IT-050
#[tokio::test(start_paused = true)]
async fn every_error_variant_occurs_on_the_mock() {
    let ble = Kind::Ble;
    let mut seen: Vec<Error> = Vec::new();
    let af01 = Route::Ble(BleRoute::Af01);

    // Protocol: a foreign opcode through the guard.
    let mock = Mock::new(
        ble,
        "IT-050-guard",
        Script {
            send_errors: vec![SendError {
                opcode: 0xC2,
                from: ms(0),
            }],
            ..Script::default()
        },
    );
    let guard: Guarded<Mock> = Guarded::new(mock);
    let foreign = ble::decode(&[0xC6], BleRoute::Af02).unwrap();
    seen.push(guard.send(&foreign, af01).await.unwrap_err());
    // Transport: a write that the transport fails.
    seen.push(guard.send(&telemetry::request(), af01).await.unwrap_err());

    // NotReady, then (once ready) SetpointRange.
    let rig = start(
        "IT-050-ready",
        ble,
        script(ble, vec![reply(ble, 0xC2, ms(800), &fixtures::C3_CAPTURE)]),
    );
    rig.until(ms(200)).await;
    seen.push(rig.session.set_voltage(1.7).await.unwrap_err());
    rig.session.ready().await.unwrap();
    seen.push(rig.session.set_voltage(31.0).await.unwrap_err());

    // AlreadyOpen: a second session to the same identifier.
    let second = Session::connect(
        Arc::new(MockConnector::new(|| {
            Ok(Mock::new(Kind::Ble, "unused", Script::default()))
        })) as Arc<dyn Connector>,
        "IT-050-ready",
        host_id(),
        Arc::new(MemoryMarkers::new()) as Arc<dyn Markers>,
        options(false),
    );
    seen.push(second.map(|_| ()).unwrap_err());

    // Mode: the reading says PD mode.
    let pd = fixtures::c3_with(0, 2, 0, 1300, 1000);
    let rig = start(
        "IT-050-mode",
        ble,
        script(ble, vec![reply(ble, 0xC2, ms(130), &pd)]),
    );
    rig.session.ready().await.unwrap();
    seen.push(rig.session.set_voltage(1.7).await.unwrap_err());

    // FaultActive: output-on with fault bit 5.
    let faulty = fixtures::c3_with(0, 0, 1 << 5, 1300, 1000);
    let rig = start(
        "IT-050-fault",
        ble,
        script(ble, vec![reply(ble, 0xC2, ms(130), &faulty)]),
    );
    rig.session.ready().await.unwrap();
    seen.push(rig.session.output_on().await.unwrap_err());

    // Timeout: no 0xE1 to the info request.
    let mut quiet = script(ble, vec![]);
    quiet.replies.retain(|r| r.request != 0xE0);
    let rig = start("IT-050-timeout", ble, quiet);
    seen.push(rig.session.ready().await.unwrap_err());

    // ConnectionDenied: `19 FF` to both binds.
    let rig = start(
        "IT-050-denied",
        ble,
        script(ble, vec![reply(ble, 0x18, ms(50), &[0xFF])]),
    );
    seen.push(rig.session.ready().await.unwrap_err());

    // RemoteControlDenied: status 1 to the request.
    let rig = start(
        "IT-050-rc-denied",
        ble,
        script(ble, vec![reply(ble, 0xC8, ms(100), &[0x01])]),
    );
    rig.session.ready().await.unwrap();
    seen.push(rig.session.set_voltage(1.7).await.unwrap_err());

    // RemoteControlLost and CommandRejected: status 1 and FF to commands.
    for (id, status) in [("IT-050-rc-lost", 0x01), ("IT-050-rejected", 0xFF)] {
        let rig = granted(
            id,
            ble,
            script(
                ble,
                vec![
                    reply_with(ble, 0xC8, ms(100), &[0x00], Some(1), ms(0)),
                    reply(ble, 0xC8, ms(100), &[status]),
                ],
            ),
        )
        .await;
        seen.push(rig.session.set_voltage(1.7).await.unwrap_err());
    }

    // Cancelled: a command waiting while an output-off arrives.
    let rig = granted(
        "IT-050-cancelled",
        ble,
        script(
            ble,
            vec![
                reply_with(ble, 0xC8, ms(100), &[0x00], Some(1), ms(0)),
                reply(ble, 0xC8, ms(300), &[0x00]),
            ],
        ),
    )
    .await;
    let s = Arc::clone(&rig.session);
    let (first, queued, off) = tokio::join!(s.set_voltage(1.0), s.set_voltage(2.0), s.output_off());
    assert_eq!(off, Ok(()));
    assert!(matches!(first, Err(Error::Cancelled { .. })), "{first:?}");
    seen.push(queued.unwrap_err());

    // LinkLost: a call after the link dropped.
    let mut dropped = script(ble, vec![]);
    dropped.close_at = Some(T0 + ms(500));
    let rig = start("IT-050-lost", ble, dropped);
    rig.session.ready().await.unwrap();
    rig.until(T0 + secs(1)).await;
    seen.push(rig.session.set_voltage(1.7).await.unwrap_err());

    // NotFound: the connector reports that no supply was found, as
    // discovery does when the identifier is not advertising.
    let rig = start_with(
        "IT-050-not-found",
        MockConnector::new(|| Err(discovery::not_found())),
        MemoryMarkers::new(),
        options(false),
        host_id(),
    );
    seen.push(rig.session.ready().await.unwrap_err());

    // Store: a store whose directory cannot be created.
    let dir = tempfile::tempdir().unwrap();
    let file = dir.path().join("a-file");
    std::fs::write(&file, b"").unwrap();
    seen.push(Store::new(file.join("store")).host_id().unwrap_err());

    // Every variant of AR-050 occurred, each with a message of its own.
    let names: BTreeSet<&str> = seen.iter().map(variant).collect();
    assert_eq!(names, AR_050.into_iter().collect(), "{seen:#?}");
    assert_eq!(seen.len(), AR_050.len(), "{seen:#?}");
    let messages: BTreeSet<String> = seen.iter().map(ToString::to_string).collect();
    assert_eq!(messages.len(), seen.len());
    assert!(messages.iter().all(|m| !m.is_empty()));

    // NotFound carries the four causes of SR-005.
    let not_found = seen
        .iter()
        .find_map(|e| match e {
            Error::NotFound { causes } => Some(causes.clone()),
            _ => None,
        })
        .unwrap();
    for cause in [
        "the supply is off or out of range",
        "another app (WebLink in a browser, ISDT's Polying app) is connected to it",
        "a USB host is talking to it",
        "remote control is disabled on the supply",
    ] {
        assert!(not_found.contains(cause), "{cause} missing in {not_found}");
    }
}
