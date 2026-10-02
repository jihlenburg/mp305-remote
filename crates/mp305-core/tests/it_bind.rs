//! Integration test IT-026 (AR-026): the link state machine of the session
//! on the scripted mock. Over Bluetooth the fast bind with the stored host
//! ID, the prompt bind after `19 FF`, a denial, the 30 s bound, a link drop
//! during the wait and a control call before the first reading; over USB a
//! full connect without a bind.
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
use mp305_core::link::LossReason;
use mp305_core::protocol::ble::{BleRoute, Route};
use mp305_core::protocol::ops::bind::HostId;
use mp305_core::protocol::ops::info::Version;
use mp305_core::session::doubles::MemoryMarkers;
use mp305_core::session::{texts, LinkState, PromptKind, SessionEvent};
use mp305_core::store::Store;
use mp305_core::transport::description::Kind;
use mp305_core::transport::mock::Script;

use common::{
    ms, one_mock, options, reply, reply_with, script, secs, silent, start_with, Rig, C3_CAPTURE,
};

/// A session to `id` over one Bluetooth mock following `script`, presenting
/// the host ID of a fresh store; returns the rig and the stored ID.
fn ble_session(id: &str, script: Script) -> (Rig, HostId, tempfile::TempDir) {
    let dir = tempfile::tempdir().unwrap();
    let host_id = Store::new(dir.path()).host_id().unwrap();
    let rig = start_with(
        id,
        one_mock(id, Kind::Ble, script),
        MemoryMarkers::new(),
        options(false),
        host_id,
    );
    (rig, host_id, dir)
}

/// The bind payload: the 16-byte ID, `00`, the fast flag.
fn bind_payload(host_id: &HostId, fast: bool) -> Vec<u8> {
    let mut payload = host_id.as_bytes().to_vec();
    payload.extend_from_slice(&[0x00, u8::from(fast)]);
    payload
}

/// Asserts that the first mock was sent exactly `binds` (fast flags, in
/// order) before `until`, each a bind on AF02 with the stored ID.
fn only_binds_before(rig: &Rig, host_id: &HostId, binds: &[bool], until: Duration) {
    let before: Vec<_> = rig
        .mock(0)
        .sent()
        .into_iter()
        .filter(|s| s.at - rig.start < until)
        .collect();
    assert_eq!(before.len(), binds.len(), "{before:?}");
    for (sent, fast) in before.iter().zip(binds) {
        assert_eq!(sent.frame.opcode(), 0x18);
        assert_eq!(sent.route, Route::Ble(BleRoute::Af02));
        assert_eq!(
            sent.frame.payload(),
            bind_payload(host_id, *fast).as_slice()
        );
        let mut wire = vec![0x18];
        wire.extend_from_slice(&bind_payload(host_id, *fast));
        assert_eq!(sent.wire, wire);
    }
}

/// The prompt bind's `Prompt` event.
fn confirm_prompt() -> SessionEvent {
    SessionEvent::Prompt {
        kind: PromptKind::ConfirmConnection,
        bound_s: 30,
        text: texts::CONFIRM_CONNECTION,
    }
}

/// Test: IT-026
#[tokio::test(start_paused = true)]
async fn a_fast_bind_answered_19_00_is_allowed_and_recognised() {
    let (rig, host_id, _dir) = ble_session("IT-026-fast", script(Kind::Ble, vec![]));
    rig.until(ms(60)).await;
    assert_eq!(rig.session.link_state(), LinkState::Allowed);
    rig.session.ready().await.unwrap();
    assert_eq!(
        rig.events.non_readings(),
        vec![(ms(50), SessionEvent::BindResult { recognised: true })]
    );
    only_binds_before(&rig, &host_id, &[true], ms(50));
    assert_eq!(rig.session.link_state(), LinkState::Ready);
}

/// Test: IT-026
#[tokio::test(start_paused = true)]
async fn a_fast_bind_answered_19_ff_is_followed_by_the_prompt_bind() {
    let ble = Kind::Ble;
    let (rig, host_id, _dir) = ble_session(
        "IT-026-prompt",
        script(
            ble,
            vec![
                reply_with(ble, 0x18, ms(50), &[0xFF], Some(1), ms(0)),
                reply(ble, 0x18, ms(3_000), &[0x00]),
            ],
        ),
    );
    rig.until(ms(1_000)).await;
    assert_eq!(rig.session.link_state(), LinkState::Binding);
    rig.until(ms(3_060)).await;
    assert_eq!(rig.session.link_state(), LinkState::Allowed);
    rig.session.ready().await.unwrap();
    assert_eq!(
        rig.events.non_readings(),
        vec![
            (ms(50), confirm_prompt()),
            (ms(3_050), SessionEvent::BindResult { recognised: false }),
        ]
    );
    only_binds_before(&rig, &host_id, &[true, false], ms(3_050));
}

/// Test: IT-026
#[tokio::test(start_paused = true)]
async fn a_prompt_bind_answered_19_ff_is_denied_and_the_transport_closed() {
    let ble = Kind::Ble;
    let (rig, host_id, _dir) = ble_session(
        "IT-026-denied",
        script(
            ble,
            vec![
                reply_with(ble, 0x18, ms(50), &[0xFF], Some(1), ms(0)),
                reply(ble, 0x18, ms(1_000), &[0xFF]),
            ],
        ),
    );
    assert_eq!(rig.session.ready().await, Err(Error::ConnectionDenied));
    tokio::time::sleep(ms(1)).await;
    assert_eq!(rig.session.link_state(), LinkState::Denied);
    assert_eq!(rig.mock(0).closes(), 1);
    rig.until(secs(5)).await;
    only_binds_before(&rig, &host_id, &[true, false], secs(5));
}

/// Test: IT-026
#[tokio::test(start_paused = true)]
async fn a_prompt_bind_without_an_answer_times_out_after_30_s() {
    let ble = Kind::Ble;
    let (rig, host_id, _dir) = ble_session(
        "IT-026-timeout",
        script(
            ble,
            vec![
                reply_with(ble, 0x18, ms(50), &[0xFF], Some(1), ms(0)),
                silent(0x18, None, ms(0)),
            ],
        ),
    );
    let result = rig.session.ready().await;
    assert_eq!(rig.now(), secs(30));
    let error = result.unwrap_err();
    assert_eq!(
        error,
        Error::Timeout {
            opcode: 0x18,
            after: secs(30)
        }
    );
    assert!(error.to_string().contains("30.0 s"), "{error}");
    rig.until(secs(31)).await;
    assert_eq!(rig.mock(0).closes(), 1);
    only_binds_before(&rig, &host_id, &[true, false], secs(31));
}

/// Test: IT-026
#[tokio::test(start_paused = true)]
async fn a_link_drop_during_the_bind_wait_is_a_lost_link() {
    let ble = Kind::Ble;
    let mut script = script(
        ble,
        vec![
            reply_with(ble, 0x18, ms(50), &[0xFF], Some(1), ms(0)),
            silent(0x18, None, ms(0)),
        ],
    );
    script.close_at = Some(secs(10));
    let (rig, _, _dir) = ble_session("IT-026-drop", script);
    let text = texts::lost_while_connecting(&LossReason::Disconnected);
    assert_eq!(
        rig.session.ready().await,
        Err(Error::LinkLost { text: text.clone() })
    );
    assert_eq!(rig.now(), secs(10));
    tokio::time::sleep(ms(1)).await;
    assert_eq!(rig.session.link_state(), LinkState::Lost);
    assert!(rig
        .events
        .non_reading_events()
        .contains(&SessionEvent::LinkLost { text }));
}

/// Test: IT-026
#[tokio::test(start_paused = true)]
async fn a_control_call_before_the_first_reading_is_not_ready() {
    let ble = Kind::Ble;
    // The first reading arrives 800 ms after its 0xC2, at 950 ms.
    let (rig, _, _dir) = ble_session(
        "IT-026-not-ready",
        script(ble, vec![reply(ble, 0xC2, ms(800), &C3_CAPTURE)]),
    );
    rig.until(ms(200)).await;
    assert_eq!(rig.session.link_state(), LinkState::Allowed);
    assert_eq!(rig.session.set_voltage(1.7).await, Err(Error::NotReady));
    assert_eq!(rig.session.output_on().await, Err(Error::NotReady));
    assert_eq!(rig.now(), ms(200));
    rig.session.ready().await.unwrap();
    assert_eq!(rig.now(), ms(950));
    rig.until(secs(2)).await;
    assert!(rig.c8s_after(ms(0)).is_empty());
}

/// Test: IT-026
#[tokio::test(start_paused = true)]
async fn usb_is_allowed_after_the_e1_without_a_bind() {
    let hid = Kind::Hid;
    let id = "IT-026-usb";
    let rig = start_with(
        id,
        one_mock(id, hid, script(hid, vec![])),
        MemoryMarkers::new(),
        options(false),
        common::host_id(),
    );
    // The 0xE1 arrives at 100 ms, the first reading at 230 ms.
    rig.until(ms(150)).await;
    assert_eq!(rig.session.link_state(), LinkState::Allowed);
    let info = rig.session.ready().await.unwrap();
    assert_eq!(rig.now(), ms(230));
    assert_eq!(info.version, Version([1, 6, 0, 51]));
    assert_eq!(info.model, "MP305B");
    let sent: Vec<(Duration, u8, Route)> = rig
        .mock(0)
        .sent()
        .iter()
        .map(|s| (s.at - rig.start, s.frame.opcode(), s.route))
        .collect();
    assert_eq!(
        sent,
        vec![(ms(0), 0xE0, Route::Hid), (ms(100), 0xC2, Route::Hid)]
    );
    rig.until(secs(2)).await;
    assert!(!rig.opcodes().contains(&0x18));
    assert!(!rig.events.non_reading_events().iter().any(|e| matches!(
        e,
        SessionEvent::BindResult { .. } | SessionEvent::Prompt { .. }
    )));
}
