//! Integration test IT-029 (AR-029): the reconnect policy of the session on
//! the scripted mock: off, a reconnection at the third attempt after a loss
//! with a setpoint pending, a `19 FF` that ends the attempts, and ten
//! minutes without success.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    missing_docs
)]

mod common;

use core::time::Duration;

use tokio::time::Instant;

use mp305_core::error::Error;
use mp305_core::protocol::timing;
use mp305_core::session::doubles::MemoryMarkers;
use mp305_core::session::{texts, LinkState, SessionEvent};
use mp305_core::transport::description::Kind;
use mp305_core::transport::mock::{Mock, Script};

use common::{
    host_id, ms, options, reply, script, scripted_connector, secs, silent, start_with, Rig, T0,
};

/// An attempt that yields a Bluetooth mock named `id` following `script`.
fn attempt(id: &'static str, script: Script) -> Box<dyn Fn() -> Result<Mock, Error> + Send> {
    Box::new(move || Ok(Mock::new(Kind::Ble, id, script.clone())))
}

/// The default script, with the link closed (an OS disconnect) at `at`.
fn lost_at(at: Duration) -> Script {
    let mut first = script(Kind::Ble, vec![]);
    first.close_at = Some(at);
    first
}

/// A script whose fast bind gets no answer.
fn bind_unanswered() -> Script {
    script(Kind::Ble, vec![silent(0x18, None, ms(0))])
}

/// The times of the connector's calls since the session's start.
fn call_times(calls: &std::sync::Mutex<Vec<Instant>>, rig: &Rig) -> Vec<Duration> {
    calls
        .lock()
        .unwrap()
        .iter()
        .map(|t| *t - rig.start)
        .collect()
}

/// The `ReconnectGaveUp` events so far, with their times.
fn gave_up(rig: &Rig) -> Vec<(Duration, SessionEvent)> {
    rig.events
        .non_readings()
        .into_iter()
        .filter(|(_, e)| matches!(e, SessionEvent::ReconnectGaveUp { .. }))
        .collect()
}

/// Test: IT-029
#[tokio::test(start_paused = true)]
async fn with_reconnection_off_a_loss_is_not_reconnected() {
    let id = "IT-029-off";
    let (connector, calls) = scripted_connector(vec![
        attempt(id, lost_at(T0 + secs(1))),
        attempt(id, script(Kind::Ble, vec![])),
    ]);
    let rig = start_with(
        id,
        connector,
        MemoryMarkers::new(),
        options(false),
        host_id(),
    );
    rig.session.ready().await.unwrap();
    rig.until(T0 + secs(60)).await;
    assert_eq!(call_times(&calls, &rig), vec![ms(0)]);
    assert_eq!(rig.session.link_state(), LinkState::Lost);
    assert!(rig.events.non_reading_events().iter().all(|e| !matches!(
        e,
        SessionEvent::Reconnected | SessionEvent::ReconnectGaveUp { .. }
    )));
}

/// Test: IT-029
#[tokio::test(start_paused = true)]
async fn a_reconnection_at_the_third_attempt_starts_afresh_and_replays_nothing() {
    let id = "IT-029-on";
    let loss = T0 + secs(1);
    // The first link drops at t0 + 1 s while a setpoint call waits for its
    // 0xC9; the first two attempts get no answer to the fast bind, the
    // third one is accepted.
    let mut first = script(Kind::Ble, vec![reply(Kind::Ble, 0xC8, ms(300), &[0x00])]);
    first.close_at = Some(loss);
    let (connector, calls) = scripted_connector(vec![
        attempt(id, first),
        attempt(id, bind_unanswered()),
        attempt(id, bind_unanswered()),
        attempt(id, script(Kind::Ble, vec![])),
    ]);
    let rig = start_with(
        id,
        connector,
        MemoryMarkers::new(),
        options(true),
        host_id(),
    );
    rig.session.ready().await.unwrap();
    // A setpoint call waiting for its grant, and one queued behind it.
    let pending = rig.call_at(loss - ms(100), |s| async move { s.set_voltage(1.0).await });
    let queued = rig.call_at(
        loss - ms(50),
        |s| async move { s.set_current_limit(0.1).await },
    );
    for call in [pending, queued] {
        let (at, result) = call.await.unwrap();
        assert!(matches!(result, Err(Error::LinkLost { .. })), "{result:?}");
        assert_eq!(at, loss);
    }
    rig.until(loss + secs(20)).await;

    // Retries every 5 s; the third attempt reconnects.
    assert_eq!(
        call_times(&calls, &rig),
        vec![
            ms(0),
            loss + timing::RECONNECT_RETRY,
            loss + timing::RECONNECT_RETRY * 2,
            loss + timing::RECONNECT_RETRY * 3,
        ]
    );
    assert_eq!(rig.mocks(), 4);
    let reconnected: Vec<Duration> = rig
        .events
        .non_readings()
        .into_iter()
        .filter(|(_, e)| *e == SessionEvent::Reconnected)
        .map(|(t, _)| t)
        .collect();
    assert_eq!(reconnected.len(), 1);
    assert!(reconnected[0] > loss + timing::RECONNECT_RETRY * 3);
    assert_eq!(rig.session.link_state(), LinkState::Ready);
    // Every attempt sent the fast bind only; the third repeated 0xE0 and
    // 0xC2; no attempt sent a 0xC8, so the setpoint was not replayed.
    for n in 1..4 {
        let sent = rig.sent_of(n);
        assert_eq!(sent[0].1, 0x18, "attempt {n}");
        assert_eq!(sent[0].2[17], 0x01, "attempt {n}");
        assert!(
            sent.iter()
                .filter(|(_, op, _)| *op == 0x18)
                .all(|(_, _, p)| p[17] == 0x01),
            "attempt {n}"
        );
        assert!(!sent.iter().any(|(_, op, _)| *op == 0xC8), "attempt {n}");
    }
    assert_eq!(rig.sent_of(1).len(), 1);
    assert_eq!(rig.sent_of(2).len(), 1);
    let third: Vec<u8> = rig.sent_of(3).iter().map(|(_, op, _)| *op).collect();
    assert_eq!(&third[..3], &[0x18, 0xE0, 0xC2]);
    assert!(third[3..].iter().all(|op| *op == 0xC2), "{third:02x?}");
}

/// Test: IT-029
#[tokio::test(start_paused = true)]
async fn a_19_ff_during_a_reconnection_gives_up() {
    let id = "IT-029-ff";
    let loss = T0 + secs(1);
    let (connector, calls) = scripted_connector(vec![
        attempt(id, lost_at(loss)),
        attempt(
            id,
            script(Kind::Ble, vec![reply(Kind::Ble, 0x18, ms(50), &[0xFF])]),
        ),
    ]);
    let rig = start_with(
        id,
        connector,
        MemoryMarkers::new(),
        options(true),
        host_id(),
    );
    rig.session.ready().await.unwrap();
    rig.until(loss + secs(30)).await;
    assert_eq!(
        gave_up(&rig),
        vec![(
            loss + timing::RECONNECT_RETRY + ms(50),
            SessionEvent::ReconnectGaveUp {
                text: texts::GAVE_UP_UNRECOGNISED.to_string()
            }
        )]
    );
    assert_eq!(call_times(&calls, &rig).len(), 2);
    assert_eq!(rig.sent_of(1).len(), 1);
    assert_eq!(rig.session.link_state(), LinkState::Lost);
}

/// Test: IT-029
#[tokio::test(start_paused = true)]
async fn ten_minutes_without_success_give_up() {
    let id = "IT-029-10min";
    let loss = T0 + secs(1);
    let (connector, calls) = scripted_connector(vec![
        attempt(id, lost_at(loss)),
        attempt(id, bind_unanswered()),
    ]);
    let rig = start_with(
        id,
        connector,
        MemoryMarkers::new(),
        options(true),
        host_id(),
    );
    rig.session.ready().await.unwrap();
    rig.until(loss + secs(700)).await;
    assert_eq!(
        gave_up(&rig),
        vec![(
            loss + timing::RECONNECT_GIVE_UP,
            SessionEvent::ReconnectGaveUp {
                text: texts::GAVE_UP_TIMEOUT.to_string()
            }
        )]
    );
    let attempts: Vec<Duration> = call_times(&calls, &rig)
        .into_iter()
        .skip(1)
        .map(|t| t - loss)
        .collect();
    assert_eq!(attempts.first(), Some(&timing::RECONNECT_RETRY));
    assert!(attempts
        .windows(2)
        .all(|p| p[1] - p[0] == timing::RECONNECT_RETRY));
    assert!(*attempts.last().unwrap() < timing::RECONNECT_GIVE_UP);
    assert_eq!(rig.session.link_state(), LinkState::Lost);
    assert!(rig
        .events
        .non_reading_events()
        .iter()
        .all(|e| *e != SessionEvent::Reconnected));
}
