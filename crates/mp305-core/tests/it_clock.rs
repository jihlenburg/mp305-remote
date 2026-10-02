//! Integration test IT-003 (AR-003), step 3 only (steps 1 and 2 are the
//! Python and app tests of the entry): the 70 s scenario of IT-027, an
//! unanswered Bluetooth remote request that ends as a denial after 70 s, on
//! a paused Tokio clock driven by `advance`, completes in under 1 s of wall
//! time.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    missing_docs
)]

mod common;

use std::time::Instant as WallInstant;

use tokio::time::advance;

use mp305_core::error::Error;
use mp305_core::protocol::timing;
use mp305_core::session::RemoteState;
use mp305_core::transport::description::Kind;

use common::{ms, reply, script, secs, silent, start};

/// Test: IT-003
#[tokio::test(start_paused = true)]
async fn step3_the_70_s_scenario_of_it_027_runs_in_under_1_s_of_wall_time() {
    let wall = WallInstant::now();
    let ble = Kind::Ble;
    let rig = start(
        "IT-003-clock",
        ble,
        script(
            ble,
            vec![
                silent(0xC8, Some(1), ms(0)),
                reply(ble, 0xC8, ms(100), &[0x00]),
            ],
        ),
    );
    // The clock moves only through `advance`, in steps of 50 ms.
    let ready = {
        let session = std::sync::Arc::clone(&rig.session);
        tokio::spawn(async move { session.ready().await })
    };
    while !ready.is_finished() {
        advance(ms(50)).await;
    }
    ready.await.unwrap().unwrap();
    let call = rig.call_at(rig.now(), |s| async move { s.set_voltage(1.7).await });
    while !call.is_finished() {
        advance(ms(50)).await;
    }
    let (returned, result) = call.await.unwrap();
    assert_eq!(result, Err(Error::RemoteControlDenied));
    assert_eq!(rig.session.remote_state(), RemoteState::Denied);
    let requested_at = rig.c8s_after(ms(0))[0].0;
    assert!(
        returned >= requested_at + timing::REMOTE_PROMPT,
        "{returned:?}"
    );
    assert!(returned < requested_at + timing::REMOTE_PROMPT + secs(1));
    assert!(rig.c2_times().len() > 100);
    let elapsed = wall.elapsed();
    assert!(elapsed < secs(1), "{elapsed:?}");
}
