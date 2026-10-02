//! Integration test IT-027 (AR-027): the remote-control state machine of
//! the session on the scripted mock: the Bluetooth request with its prompt,
//! a second call during the wait, a denial by status 1 and by the 70 s
//! bound, a call in `Denied`, a new explicit request, the immediate grant
//! over USB, and the release in DC mode and in PD mode.
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

use mp305_core::error::Error;
use mp305_core::protocol::fixtures;
use mp305_core::session::{texts, PromptKind, RemoteState, SessionEvent};
use mp305_core::transport::description::Kind;

use common::{
    granted, ms, remote_con, reply, reply_with, script, secs, setpoints, silent, start, C3_CAPTURE,
    T0,
};

/// The Bluetooth remote request's `Prompt` event.
fn allow_prompt() -> SessionEvent {
    SessionEvent::Prompt {
        kind: PromptKind::AllowRemoteControl,
        bound_s: 70,
        text: texts::ALLOW_REMOTE_CONTROL,
    }
}

/// Test: IT-027
#[tokio::test(start_paused = true)]
async fn a_bluetooth_request_waits_for_the_grant_while_polls_continue() {
    let ble = Kind::Ble;
    // The request is granted 5 s after it was written; every later 0xC8 is
    // answered after 100 ms.
    let rig = start(
        "IT-027-grant",
        ble,
        script(
            ble,
            vec![
                reply_with(ble, 0xC8, secs(5), &[0x00], Some(1), ms(0)),
                reply(ble, 0xC8, ms(100), &[0x00]),
            ],
        ),
    );
    rig.session.ready().await.unwrap();
    let voltage = rig.call_at(T0 + ms(50), |s| async move { s.set_voltage(1.7).await });
    let current = rig.call_at(
        T0 + ms(1_000),
        |s| async move { s.set_current_limit(0.1).await },
    );
    rig.until(T0 + secs(2)).await;
    assert_eq!(rig.session.remote_state(), RemoteState::Requested);
    assert_eq!(voltage.await.unwrap().1, Ok(()));
    assert_eq!(current.await.unwrap().1, Ok(()));

    let c8s = rig.c8s_after(ms(0));
    assert_eq!(c8s.len(), 3, "{c8s:?}");
    let (requested_at, request) = &c8s[0];
    assert_eq!(remote_con(request), 2);
    let granted_at = rig
        .events
        .time_of(|e| *e == SessionEvent::RemoteControl(RemoteState::Granted))
        .unwrap();
    assert_eq!(granted_at, *requested_at + secs(5));
    let events: Vec<(Duration, SessionEvent)> = rig
        .events
        .non_readings()
        .into_iter()
        .filter(|(t, _)| *t >= *requested_at)
        .collect();
    assert_eq!(
        events,
        vec![
            (
                *requested_at,
                SessionEvent::RemoteControl(RemoteState::Requested)
            ),
            (*requested_at, allow_prompt()),
            (
                granted_at,
                SessionEvent::RemoteControl(RemoteState::Granted)
            ),
        ]
    );
    // The poll went on during the wait.
    let polls = rig
        .c2_times()
        .into_iter()
        .filter(|t| *t > *requested_at && *t < granted_at)
        .count();
    assert!(polls >= 15, "{polls}");
    // The second call sent nothing until the grant, then both setpoints
    // went out.
    assert!(c8s[1].0 > granted_at);
    assert_eq!(
        (remote_con(&c8s[1].1), setpoints(&c8s[1].1)),
        (1, (170, 1000))
    );
    assert_eq!(
        (remote_con(&c8s[2].1), setpoints(&c8s[2].1)),
        (1, (1300, 100))
    );
}

/// Test: IT-027
#[tokio::test(start_paused = true)]
async fn status_1_to_the_request_is_a_denial() {
    let ble = Kind::Ble;
    let rig = start(
        "IT-027-status-1",
        ble,
        script(ble, vec![reply(ble, 0xC8, ms(1_000), &[0x01])]),
    );
    rig.session.ready().await.unwrap();
    assert_eq!(
        rig.session.set_voltage(1.7).await,
        Err(Error::RemoteControlDenied)
    );
    assert_eq!(rig.session.remote_state(), RemoteState::Denied);
    assert_eq!(
        rig.events.non_reading_events().last(),
        Some(&SessionEvent::RemoteControl(RemoteState::Denied))
    );
    // Only the request went out.
    let c8s = rig.c8s_after(ms(0));
    assert_eq!(c8s.len(), 1);
    assert_eq!(remote_con(&c8s[0].1), 2);
}

/// Test: IT-027
#[tokio::test(start_paused = true)]
async fn an_unanswered_request_is_denied_after_70_s_and_only_a_new_request_lifts_it() {
    let ble = Kind::Ble;
    // The first request is never answered; a later one gets `0xC9 00`.
    let rig = start(
        "IT-027-silent",
        ble,
        script(
            ble,
            vec![
                silent(0xC8, Some(1), ms(0)),
                reply(ble, 0xC8, ms(100), &[0x00]),
            ],
        ),
    );
    rig.session.ready().await.unwrap();
    let call = rig.call_at(T0, |s| async move { s.set_voltage(1.7).await });
    rig.until(T0 + secs(71)).await;
    let (returned, result) = call.await.unwrap();
    assert_eq!(result, Err(Error::RemoteControlDenied));
    let requested_at = rig.c8s_after(ms(0))[0].0;
    assert_eq!(returned, requested_at + secs(70));
    assert_eq!(rig.session.remote_state(), RemoteState::Denied);
    // A control call in `Denied` raises at once and sends nothing.
    let sent = rig.c8s_after(ms(0)).len();
    let before = rig.now();
    assert_eq!(
        rig.session.set_current_limit(0.1).await,
        Err(Error::RemoteControlDenied)
    );
    assert_eq!(
        rig.session.output_on().await,
        Err(Error::RemoteControlDenied)
    );
    assert_eq!(rig.now(), before);
    rig.until(before + secs(1)).await;
    assert_eq!(rig.c8s_after(ms(0)).len(), sent);
    // The explicit request succeeds.
    assert_eq!(rig.session.request_remote_control().await, Ok(()));
    assert_eq!(rig.session.remote_state(), RemoteState::Granted);
    let c8s = rig.c8s_after(before);
    assert_eq!(c8s.len(), 1);
    assert_eq!(remote_con(&c8s[0].1), 2);
}

/// Test: IT-027
#[tokio::test(start_paused = true)]
async fn usb_grants_at_once() {
    let hid = Kind::Hid;
    let rig = start("IT-027-usb", hid, script(hid, vec![]));
    rig.session.ready().await.unwrap();
    let call = rig.call_at(ms(300), |s| async move { s.set_voltage(1.7).await });
    let (returned, result) = call.await.unwrap();
    assert_eq!(result, Ok(()));
    let c8s = rig.c8s_after(ms(0));
    assert_eq!(c8s.len(), 2);
    assert_eq!(remote_con(&c8s[0].1), 2);
    let granted_at = rig
        .events
        .time_of(|e| *e == SessionEvent::RemoteControl(RemoteState::Granted))
        .unwrap();
    // Granted by the 0xC9 100 ms after the request, no prompt.
    assert_eq!(granted_at, c8s[0].0 + ms(100));
    assert!(returned < ms(300) + secs(1), "{returned:?}");
    assert_eq!(
        rig.events.non_reading_events(),
        vec![
            SessionEvent::RemoteControl(RemoteState::Requested),
            SessionEvent::RemoteControl(RemoteState::Granted),
        ]
    );
    assert_eq!(
        (remote_con(&c8s[1].1), setpoints(&c8s[1].1)),
        (1, (170, 1000))
    );
}

/// Test: IT-027
#[tokio::test(start_paused = true)]
async fn the_release_is_sent_in_dc_mode_and_refused_in_pd_mode() {
    let ble = Kind::Ble;
    // DC mode: the release goes out and the state returns to `None`.
    let rig = granted("IT-027-release-dc", ble, script(ble, vec![])).await;
    let t = rig.now();
    assert_eq!(rig.session.release_remote_control().await, Ok(()));
    let c8s = rig.c8s_after(t);
    assert_eq!(c8s.len(), 1);
    assert_eq!(remote_con(&c8s[0].1), 0);
    assert_eq!(rig.session.remote_state(), RemoteState::None);

    // PD mode from 2 s on: `ModeError`, nothing sent, control still held.
    let pd = fixtures::c3_with(0, 2, 0, 1300, 1000);
    let rig = granted(
        "IT-027-release-pd",
        ble,
        script(
            ble,
            vec![
                reply(ble, 0xC2, ms(130), &C3_CAPTURE),
                reply_with(ble, 0xC2, ms(130), &pd, None, secs(2)),
            ],
        ),
    )
    .await;
    rig.until(secs(3)).await;
    let sent = rig.c8s_after(ms(0)).len();
    assert_eq!(
        rig.session.release_remote_control().await,
        Err(Error::Mode { live_mode: 2 })
    );
    assert_eq!(rig.c8s_after(ms(0)).len(), sent);
    assert_eq!(rig.session.remote_state(), RemoteState::Granted);
}
