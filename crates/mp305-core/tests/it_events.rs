//! Integration test IT-028 (AR-028): the `SessionEvent`s of the scenarios
//! of IT-022, IT-025, IT-026 and IT-027 on the scripted mock, each once
//! where its scenario says; the `Prompt` and `LinkLost` texts against
//! SR-008, SR-028 and SR-053; one event for a new fault bit and one for a
//! `0xC5`. `Reconnected` and `ReconnectGaveUp`, which none of those four
//! scenarios produces, are checked on the scenarios of IT-029 so that every
//! event of AR-028 is covered.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    missing_docs
)]

mod common;

use std::time::{Duration, SystemTime};

use mp305_core::error::Error;
use mp305_core::link::LossReason;
use mp305_core::protocol::fixtures;
use mp305_core::protocol::ops::settings::Settings;
use mp305_core::protocol::ops::telemetry::{Fault, Faults};
use mp305_core::session::doubles::MemoryMarkers;
use mp305_core::session::{texts, PromptKind, RemoteState, SessionEvent};
use mp305_core::transport::description::Kind;
use mp305_core::transport::mock::{Mock, Script};

use common::{
    granted, host_id, inject, ms, one_mock, options, reply, reply_with, script, scripted_connector,
    secs, silent, start, start_with, Rig, C3_CAPTURE, C5_SETTINGS, T0,
};

/// SR-008's prompt text.
const SR_008: &str = "Confirm the connection on the supply's screen within 30 seconds";
/// SR-053's prompt text.
const SR_053: &str = "Allow remote control on the supply's screen";

/// Asserts that the readings were delivered once each: their arrival
/// stamps strictly increase, and there is one per `0xC3` the mock sent
/// back by now.
fn readings_once(rig: &Rig, n: usize) {
    let times = rig.events.reading_times(rig.start);
    assert!(!times.is_empty());
    assert!(times.windows(2).all(|p| p[0] < p[1]), "{times:?}");
    let now = rig.now();
    let answered = rig
        .sent_of(n)
        .iter()
        .filter(|(t, op, _)| *op == 0xC2 && *t + ms(130) <= now)
        .count();
    assert_eq!(times.len(), answered);
}

/// Test: IT-028
#[tokio::test(start_paused = true)]
async fn the_bind_scenarios_give_bind_result_and_the_prompt_once() {
    let ble = Kind::Ble;
    // Fast bind answered `19 00`.
    let rig = start("IT-028-fast", ble, script(ble, vec![]));
    rig.session.ready().await.unwrap();
    rig.until(secs(2)).await;
    assert_eq!(
        rig.events.non_readings(),
        vec![(ms(50), SessionEvent::BindResult { recognised: true })]
    );
    readings_once(&rig, 0);

    // `19 FF`, then the prompt bind answered `19 00` after 3 s.
    let rig = start(
        "IT-028-prompt",
        ble,
        script(
            ble,
            vec![
                reply_with(ble, 0x18, ms(50), &[0xFF], Some(1), ms(0)),
                reply(ble, 0x18, secs(3), &[0x00]),
            ],
        ),
    );
    rig.session.ready().await.unwrap();
    assert_eq!(
        rig.events.non_readings(),
        vec![
            (
                ms(50),
                SessionEvent::Prompt {
                    kind: PromptKind::ConfirmConnection,
                    bound_s: 30,
                    text: SR_008,
                }
            ),
            (ms(3_050), SessionEvent::BindResult { recognised: false }),
        ]
    );
    assert_eq!(texts::CONFIRM_CONNECTION, SR_008);
}

/// Test: IT-028
#[tokio::test(start_paused = true)]
async fn the_remote_control_scenarios_give_their_states_and_the_prompt_once() {
    let ble = Kind::Ble;
    // Granted 5 s after the request.
    let rig = start(
        "IT-028-grant",
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
    assert_eq!(rig.session.set_voltage(1.7).await, Ok(()));
    let request_at = rig.c8s_after(ms(0))[0].0;
    assert_eq!(
        rig.events.non_readings(),
        vec![
            (ms(50), SessionEvent::BindResult { recognised: true }),
            (
                request_at,
                SessionEvent::RemoteControl(RemoteState::Requested)
            ),
            (
                request_at,
                SessionEvent::Prompt {
                    kind: PromptKind::AllowRemoteControl,
                    bound_s: 70,
                    text: SR_053,
                }
            ),
            (
                request_at + secs(5),
                SessionEvent::RemoteControl(RemoteState::Granted)
            ),
        ]
    );
    assert_eq!(texts::ALLOW_REMOTE_CONTROL, SR_053);

    // Denied by status 1.
    let rig = start(
        "IT-028-denied",
        ble,
        script(ble, vec![reply(ble, 0xC8, ms(100), &[0x01])]),
    );
    rig.session.ready().await.unwrap();
    assert_eq!(
        rig.session.set_voltage(1.7).await,
        Err(Error::RemoteControlDenied)
    );
    let events = rig.events.non_reading_events();
    assert_eq!(
        events[1..],
        [
            SessionEvent::RemoteControl(RemoteState::Requested),
            SessionEvent::Prompt {
                kind: PromptKind::AllowRemoteControl,
                bound_s: 70,
                text: SR_053,
            },
            SessionEvent::RemoteControl(RemoteState::Denied),
        ]
    );
}

/// Test: IT-028
#[tokio::test(start_paused = true)]
async fn the_dc_session_scenarios_give_the_warning_and_setpoints_changed_once() {
    let ble = Kind::Ble;
    let id = "IT-028-dc";
    let since = SystemTime::UNIX_EPOCH + Duration::from_secs(1_790_845_200);
    // A marker at connect; the request and a voltage accepted, then a
    // command rejected with FF.
    let rig = start_with(
        id,
        one_mock(
            id,
            ble,
            script(
                ble,
                vec![
                    reply_with(ble, 0xC8, ms(100), &[0x00], Some(2), ms(0)),
                    reply_with(ble, 0xC8, ms(100), &[0xFF], Some(1), ms(0)),
                    reply(ble, 0xC8, ms(100), &[0x00]),
                ],
            ),
        ),
        MemoryMarkers::holding(id, since),
        options(false),
        host_id(),
    );
    rig.session.ready().await.unwrap();
    assert_eq!(rig.session.set_voltage(1.7).await, Ok(()));
    assert!(matches!(
        rig.session.set_current_limit(0.2).await,
        Err(Error::CommandRejected { status: 0xFF, .. })
    ));
    rig.until(rig.now() + secs(2)).await;
    assert_eq!(
        rig.events.non_reading_events(),
        vec![
            SessionEvent::BindResult { recognised: true },
            SessionEvent::UncleanExitWarning {
                since,
                text: texts::unclean_exit(since)
            },
            SessionEvent::RemoteControl(RemoteState::Requested),
            SessionEvent::Prompt {
                kind: PromptKind::AllowRemoteControl,
                bound_s: 70,
                text: SR_053,
            },
            SessionEvent::RemoteControl(RemoteState::Granted),
            SessionEvent::SetpointsChanged {
                set_volts: 13.0,
                set_amps: 1.0,
                expected_volts: 1.7,
                expected_amps: 1.0,
            },
        ]
    );
    readings_once(&rig, 0);
}

/// Test: IT-028
#[tokio::test(start_paused = true)]
async fn the_loss_scenario_gives_remote_control_lost_and_the_sr_028_text_once() {
    let ble = Kind::Ble;
    // Granted, then the supply stops answering (the silence of IT-022).
    let mut silent_later = script(ble, vec![]);
    silent_later.stop_replying_at = Some(secs(2));
    let rig = granted("IT-028-loss", ble, silent_later).await;
    rig.until(secs(10)).await;
    let text = texts::link_lost(&LossReason::Unanswered, Kind::Ble);
    let events = rig.events.non_reading_events();
    assert_eq!(
        events[events.len() - 2..],
        [
            SessionEvent::RemoteControl(RemoteState::Lost),
            SessionEvent::LinkLost { text: text.clone() },
        ]
    );
    assert_eq!(
        events
            .iter()
            .filter(|e| matches!(e, SessionEvent::LinkLost { .. }))
            .count(),
        1
    );
    // SR-028: the output is still in its last state and the supply has
    // released remote control; AR-030: over Bluetooth, the USB host hint.
    assert_eq!(
        text,
        "Three requests in a row went unanswered. The output is still in its last state and \
         the supply has released remote control. A USB host talking to the supply is one \
         possible cause."
    );
}

/// Test: IT-028
#[tokio::test(start_paused = true)]
async fn a_new_fault_bit_and_a_c5_give_one_event_each() {
    let ble = Kind::Ble;
    let reversed = fixtures::c3_with(0, 0, 1, 1300, 1000);
    let mut s = script(
        ble,
        vec![
            reply(ble, 0xC2, ms(130), &C3_CAPTURE),
            reply_with(ble, 0xC2, ms(130), &reversed, None, secs(2)),
        ],
    );
    s.injections = vec![inject(ble, secs(3), 0xC5, &C5_SETTINGS)];
    let rig = start("IT-028-fault", ble, s);
    rig.session.ready().await.unwrap();
    rig.until(secs(5)).await;
    let events = rig.events.non_reading_events();
    let faults: Vec<&SessionEvent> = events
        .iter()
        .filter(|e| matches!(e, SessionEvent::FaultsChanged { .. }))
        .collect();
    assert_eq!(faults.len(), 1, "{events:?}");
    match faults[0] {
        SessionEvent::FaultsChanged { faults, reading } => {
            assert_eq!(*faults, Faults(1));
            assert_eq!(
                faults.iter().collect::<Vec<_>>(),
                vec![Fault::ReversedOutput]
            );
            assert_eq!(reading.reading.faults, Faults(1));
            // The first reading of a 0xC2 written from 2 s on.
            assert!(reading.at - rig.start > secs(2));
        }
        _ => unreachable!(),
    }
    let settings: Vec<&SessionEvent> = events
        .iter()
        .filter(|e| matches!(e, SessionEvent::SettingsChanged(_)))
        .collect();
    assert_eq!(
        settings,
        vec![&SessionEvent::SettingsChanged(Settings {
            charge_limit: 90,
            volume: 2,
            screen_off: 0,
            shutdown: 0,
            screen_direction: 1,
            ramp_step: 500,
            ocp_delay: 50,
            usb_line_drop: 0,
        })]
    );
}

/// Test: IT-028
#[tokio::test(start_paused = true)]
async fn the_reconnect_scenarios_give_reconnected_and_reconnect_gave_up_once() {
    let ble = Kind::Ble;
    // A loss at t0 + 1 s, then a reconnection at the first attempt.
    let id = "IT-028-reconnected";
    let mut first = script(ble, vec![]);
    first.close_at = Some(T0 + secs(1));
    let again = script(ble, vec![]);
    let (connector, _) = scripted_connector(vec![
        Box::new(move || Ok(Mock::new(ble, id, first.clone()))),
        Box::new(move || Ok(Mock::new(ble, id, again.clone()))),
    ]);
    let rig = start_with(
        id,
        connector,
        MemoryMarkers::new(),
        options(true),
        host_id(),
    );
    rig.session.ready().await.unwrap();
    rig.until(T0 + secs(10)).await;
    // The loss moves the remote state to `Lost`, the reconnection's fast
    // bind is recognised, and the reconnection resets the remote state.
    assert_eq!(
        rig.events.non_reading_events(),
        vec![
            SessionEvent::BindResult { recognised: true },
            SessionEvent::RemoteControl(RemoteState::Lost),
            SessionEvent::LinkLost {
                text: texts::link_lost(&LossReason::Disconnected, Kind::Ble)
            },
            SessionEvent::BindResult { recognised: true },
            SessionEvent::Reconnected,
            SessionEvent::RemoteControl(RemoteState::None),
        ]
    );

    // A loss, then no attempt succeeds: one `ReconnectGaveUp`.
    let id = "IT-028-gave-up";
    let mut first = script(ble, vec![]);
    first.close_at = Some(T0 + secs(1));
    let quiet: Script = script(ble, vec![silent(0x18, None, ms(0))]);
    let (connector, _) = scripted_connector(vec![
        Box::new(move || Ok(Mock::new(ble, id, first.clone()))),
        Box::new(move || Ok(Mock::new(ble, id, quiet.clone()))),
    ]);
    let rig = start_with(
        id,
        connector,
        MemoryMarkers::new(),
        options(true),
        host_id(),
    );
    rig.session.ready().await.unwrap();
    rig.until(T0 + secs(700)).await;
    let gave_up: Vec<SessionEvent> = rig
        .events
        .non_reading_events()
        .into_iter()
        .filter(|e| matches!(e, SessionEvent::ReconnectGaveUp { .. }))
        .collect();
    assert_eq!(
        gave_up,
        vec![SessionEvent::ReconnectGaveUp {
            text: texts::GAVE_UP_TIMEOUT.to_string()
        }]
    );
}
