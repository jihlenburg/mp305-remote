//! Integration test IT-030 (AR-030): one session per identifier in the
//! process, and the loss text over Bluetooth naming an active USB host as a
//! possible cause.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    missing_docs
)]

mod common;

use std::sync::Arc;

use mp305_core::error::Error;
use mp305_core::session::doubles::{MemoryMarkers, MockConnector};
use mp305_core::session::{texts, Connector, Markers, Session, SessionEvent};
use mp305_core::transport::description::Kind;
use mp305_core::transport::mock::{Mock, Script};

use common::{host_id, options, script, secs, start, T0};

/// Test: IT-030
#[tokio::test(start_paused = true)]
async fn a_second_session_is_refused_and_a_silent_bluetooth_link_names_a_usb_host() {
    let id = "IT-030";
    // The supply stops answering 1 s after the session is ready.
    let mut silent_later = script(Kind::Ble, vec![]);
    silent_later.stop_replying_at = Some(T0 + secs(1));
    let rig = start(id, Kind::Ble, silent_later);
    rig.session.ready().await.unwrap();

    // A second session to the same identifier, from another task.
    let second = Arc::new(MockConnector::new(|| {
        Ok(Mock::new(Kind::Ble, "unused", Script::default()))
    }));
    let connector = Arc::clone(&second);
    let result = tokio::spawn(async move {
        Session::connect(
            connector as Arc<dyn Connector>,
            "IT-030",
            host_id(),
            Arc::new(MemoryMarkers::new()) as Arc<dyn Markers>,
            options(false),
        )
        .map(|_| ())
    })
    .await
    .unwrap();
    let error = result.unwrap_err();
    assert_eq!(
        error,
        Error::AlreadyOpen {
            identifier: id.to_string()
        }
    );
    assert!(error.to_string().contains(id), "{error}");
    assert!(second.handles().is_empty());

    // The silence ends in a loss whose text names an active USB host.
    rig.until(T0 + secs(10)).await;
    let texts_seen: Vec<String> = rig
        .events
        .non_reading_events()
        .into_iter()
        .filter_map(|e| match e {
            SessionEvent::LinkLost { text } => Some(text),
            _ => None,
        })
        .collect();
    assert_eq!(texts_seen.len(), 1, "{texts_seen:?}");
    assert!(
        texts_seen[0].ends_with(texts::USB_HOST_HINT),
        "{}",
        texts_seen[0]
    );
    assert!(texts_seen[0].contains("A USB host talking to the supply is one possible cause."));
}
