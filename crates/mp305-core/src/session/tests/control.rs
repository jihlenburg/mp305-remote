//! Implements: nothing; holds the tests of UT-SESS-020 to UT-SESS-029,
//! UT-SESS-045, UT-SESS-049 to UT-SESS-051, UT-SESS-053, UT-SESS-055,
//! UT-SESS-056 and UT-SESS-060.
//!
//! Task tests: control commands, the remote-control flow, the output-off,
//! late replies, cancellation, and serving events while a command waits.

use super::*;
use crate::protocol::ops::telemetry::Faults;
use crate::protocol::units::Limits;
use crate::session::{texts, LinkState, PromptKind, RemoteState};
use crate::transport::test_log;
use log::Level;

/// The sends of the first mock after `from` as (time, opcode).
fn ops_after(rig: &Rig, from: Duration) -> Vec<(Duration, u8)> {
    rig.sent()
        .into_iter()
        .filter(|(t, _, _)| *t >= from)
        .map(|(t, op, _)| (t, op))
        .collect()
}

/// Whether a `0xC2` was sent in `[from, to)`.
fn polled_between(rig: &Rig, from: Duration, to: Duration) -> bool {
    rig.sent()
        .iter()
        .any(|(t, op, _)| *op == 0xC2 && *t >= from && *t < to)
}

/// The time of the first event matching `f` in `events`.
fn time_of(events: &Recorder, f: impl Fn(&SessionEvent) -> bool) -> Option<Duration> {
    events.all().into_iter().find(|(_, e)| f(e)).map(|(t, _)| t)
}

/// The time of the last `0xC2` the first mock was sent before `t`.
fn last_c2_before(rig: &Rig, t: Duration) -> Duration {
    rig.sent()
        .iter()
        .filter(|(at, op, _)| *op == 0xC2 && *at < t)
        .map(|(at, _, _)| *at)
        .max()
        .unwrap()
}

/// Test: UT-SESS-020
#[tokio::test(start_paused = true)]
async fn a_setpoint_requests_control_then_sends_the_command() {
    let log = test_log::install();
    let ble = Kind::Ble;
    let mut rig = start(
        "UT-SESS-020",
        ble,
        script(ble, vec![c9_once(ble, 0x00, ms(5_000), ms(0)), c9_ok(ble)]),
    );
    rig.session.ready().await.unwrap();
    rig.drain();
    let events = rig.record();
    let polls = count_logged(&log, "poll first");
    let voltage = rig.call_at(T0 + ms(50), |s| async move { s.set_voltage(1.7).await });
    let current = rig.call_at(
        T0 + ms(1_000),
        |s| async move { s.set_current_limit(0.1).await },
    );
    let (v_at, v) = voltage.await.unwrap();
    let (c_at, c) = current.await.unwrap();
    assert_eq!(v, Ok(()));
    assert_eq!(c, Ok(()));
    assert!(v_at < c_at);
    let c8s = rig.c8s_after(T0);
    assert_eq!(c8s.len(), 3, "{c8s:?}");
    // The request at t0 + 50 ms copies the capture; no poll before it.
    let (request_at, request) = &c8s[0];
    assert_eq!(*request_at, T0 + ms(50));
    assert!(!polled_between(&rig, T0, T0 + ms(50)));
    assert_eq!(remote_con(request), 2);
    assert_eq!(setpoints(request), (1300, 1000));
    assert_eq!(output(request), 0);
    let non_readings = events.non_readings();
    assert_eq!(
        non_readings[0].1,
        SessionEvent::RemoteControl(RemoteState::Requested)
    );
    assert_eq!(
        non_readings[1].1,
        SessionEvent::Prompt {
            kind: PromptKind::AllowRemoteControl,
            bound_s: 70,
            text: texts::ALLOW_REMOTE_CONTROL,
        }
    );
    let granted_at = time_of(&events, |e| {
        *e == SessionEvent::RemoteControl(RemoteState::Granted)
    })
    .unwrap();
    assert_eq!(granted_at, T0 + ms(5_050));
    let during = events
        .reading_times()
        .into_iter()
        .filter(|t| *t > T0 + ms(50) && *t < granted_at)
        .count();
    assert!(during >= 15, "{during}");
    // Nothing for the second call before the grant.
    assert!(c8s[1].0 > granted_at);
    // The voltage: the session's own `0xC2`, not before the grant plus the
    // settle time, then the command.
    let (v_sent, v_frame) = &c8s[1];
    assert!(last_c2_before(&rig, *v_sent) >= granted_at + ms(100));
    assert_eq!(remote_con(v_frame), 1);
    assert_eq!(setpoints(v_frame), (170, 1000));
    assert_eq!(output(v_frame), 0);
    assert_eq!((v_frame[9], v_frame[10]), (0, 0));
    // The current: stale by the `0xC9` rule, so a `0xC2` after the settle
    // time again, then the command.
    let (c_sent, c_frame) = &c8s[2];
    assert!(last_c2_before(&rig, *c_sent) >= *v_sent + ms(200));
    assert_eq!(setpoints(c_frame), (1300, 100));
    assert_eq!(remote_con(c_frame), 1);
    // One `poll first` per command, the voltage's naming the settle wait.
    let lines: Vec<String> = log
        .lines_here(crate::session::LOG_TARGET)
        .into_iter()
        .map(|(_, m)| m)
        .filter(|m| m.starts_with("poll first"))
        .collect();
    assert_eq!(lines.len(), polls + 2, "{lines:?}");
    assert!(lines[polls].contains("settle wait"), "{lines:?}");
}

/// Test: UT-SESS-021
#[tokio::test(start_paused = true)]
async fn a_denied_request_blocks_commands_until_requested_again() {
    let ble = Kind::Ble;
    let mut rig = start(
        "UT-SESS-021",
        ble,
        script(ble, vec![c9_once(ble, 0x01, ms(1_000), ms(0)), c9_ok(ble)]),
    );
    rig.session.ready().await.unwrap();
    let events = rig.record();
    assert_eq!(
        rig.session.set_voltage(1.7).await,
        Err(Error::RemoteControlDenied)
    );
    assert!(events
        .non_readings()
        .iter()
        .any(|(_, e)| *e == SessionEvent::RemoteControl(RemoteState::Denied)));
    rig.until(T0 + ms(2_000)).await;
    let before = rig.c8s_after(ms(0)).len();
    assert_eq!(
        rig.session.set_current_limit(0.1).await,
        Err(Error::RemoteControlDenied)
    );
    assert_eq!(rig.now(), T0 + ms(2_000));
    rig.until(T0 + ms(3_000)).await;
    assert_eq!(rig.c8s_after(ms(0)).len(), before);
    assert_eq!(rig.session.request_remote_control().await, Ok(()));
    assert_eq!(rig.session.remote_state(), RemoteState::Granted);
    let c8s = rig.c8s_after(T0 + ms(3_000));
    assert_eq!(c8s.len(), 1);
    assert_eq!(remote_con(&c8s[0].1), 2);
    // In `Granted` a request returns `Ok` without sending.
    assert_eq!(rig.session.request_remote_control().await, Ok(()));
    assert_eq!(rig.c8s_after(T0 + ms(3_000)).len(), 1);
}

/// Test: UT-SESS-021
#[tokio::test(start_paused = true)]
async fn an_unanswered_prompt_is_a_denial_after_70_s() {
    let ble = Kind::Ble;
    let mut rig = start(
        "UT-SESS-021-timeout",
        ble,
        script(ble, vec![c8_unanswered(ms(0))]),
    );
    rig.session.ready().await.unwrap();
    let events = rig.record();
    let (at, result) = rig
        .call_at(T0, |s| async move { s.set_voltage(1.7).await })
        .await
        .unwrap();
    assert_eq!(result, Err(Error::RemoteControlDenied));
    assert_eq!(at, T0 + Duration::from_secs(70));
    assert_eq!(
        events.non_readings().last().unwrap().1,
        SessionEvent::RemoteControl(RemoteState::Denied)
    );
    let late = events
        .reading_times()
        .into_iter()
        .filter(|t| *t > T0 + Duration::from_secs(60))
        .count();
    assert!(late >= 40, "{late}");
}

/// Test: UT-SESS-022
#[tokio::test(start_paused = true)]
async fn usb_grants_at_once() {
    let hid = Kind::Hid;
    let mut rig = start("UT-SESS-022", hid, script(hid, vec![]));
    rig.session.ready().await.unwrap();
    let events = rig.record();
    let (at, result) = rig
        .call_at(T0, |s| async move { s.set_voltage(1.7).await })
        .await
        .unwrap();
    assert_eq!(result, Ok(()));
    assert!(at < T0 + ms(1_000), "{at:?}");
    let non_readings: Vec<SessionEvent> =
        events.non_readings().into_iter().map(|(_, e)| e).collect();
    assert_eq!(
        non_readings,
        vec![
            SessionEvent::RemoteControl(RemoteState::Requested),
            SessionEvent::RemoteControl(RemoteState::Granted),
        ]
    );
    let c8s = rig.c8s_after(T0);
    assert_eq!(c8s.len(), 2);
    assert_eq!(remote_con(&c8s[0].1), 2);
    assert!(polled_between(&rig, c8s[0].0 + ms(100), c8s[1].0));
    assert_eq!(remote_con(&c8s[1].1), 1);
    assert_eq!(setpoints(&c8s[1].1), (170, 1000));
}

/// Test: UT-SESS-022
#[tokio::test(start_paused = true)]
async fn usb_request_without_an_answer_times_out() {
    let hid = Kind::Hid;
    let rig = start(
        "UT-SESS-022-timeout",
        hid,
        script(hid, vec![c8_unanswered(ms(0))]),
    );
    rig.session.ready().await.unwrap();
    assert_eq!(
        rig.session.set_voltage(1.7).await,
        Err(Error::Timeout {
            opcode: 0xC8,
            after: Duration::from_secs(1)
        })
    );
    assert_eq!(rig.session.remote_state(), RemoteState::None);
}

/// Test: UT-SESS-023
#[tokio::test(start_paused = true)]
async fn a_command_right_after_the_grant_polls_first() {
    let log = test_log::install();
    let rig = granted("UT-SESS-023-1", vec![], vec![]).await;
    let granted_at = rig.now();
    let polls = count_logged(&log, "poll first");
    assert_eq!(rig.session.set_voltage(1.0).await, Ok(()));
    assert_eq!(count_logged(&log, "poll first"), polls + 1);
    let after_grant = ops_after(&rig, granted_at);
    let first_c8 = after_grant.iter().position(|(_, op)| *op == 0xC8).unwrap();
    assert!(after_grant[..first_c8].iter().any(|(_, op)| *op == 0xC2));
    // The session's own `0xC2` went out after the settle time.
    let c8 = rig.c8s_after(granted_at)[0].0;
    assert!(last_c2_before(&rig, c8) >= granted_at + ms(100));
}

/// Test: UT-SESS-023
#[tokio::test(start_paused = true)]
async fn bad_setpoints_are_refused_before_anything_is_sent() {
    let log = test_log::install();
    let rig = granted("UT-SESS-023-2", vec![], vec![]).await;
    let c8s = rig.c8s_after(ms(0)).len();
    let polls = count_logged(&log, "poll first");
    let range = |r: Result<(), Error>| matches!(r, Err(Error::SetpointRange { .. }));
    assert!(range(rig.session.set_voltage(31.0).await));
    assert!(range(rig.session.set_voltage(f64::NAN).await));
    assert!(range(rig.session.set_current_limit(-1.0).await));
    rig.session
        .set_limits(Limits {
            max_volts: Some(12.0),
            ..Limits::none()
        })
        .unwrap();
    assert_eq!(
        rig.session.set_voltage(20.0).await,
        Err(Error::SetpointRange {
            field: "voltage",
            value: 20.0,
            min: 0.0,
            max: 12.0
        })
    );
    assert_eq!(rig.c8s_after(ms(0)).len(), c8s);
    assert_eq!(count_logged(&log, "poll first"), polls);
}

/// Test: UT-SESS-023
#[tokio::test(start_paused = true)]
async fn a_command_outside_dc_mode_is_refused() {
    let log = test_log::install();
    let pd = fixtures::c3_with(0, 2, 0, 1300, 1000);
    let rig = granted(
        "UT-SESS-023-3",
        vec![
            reply(Kind::Ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            c3_from(Kind::Ble, &pd, T0 + ms(2_000)),
        ],
        vec![],
    )
    .await;
    rig.until(T0 + ms(3_000)).await;
    let c8s = rig.c8s_after(ms(0)).len();
    let polls = count_logged(&log, "poll first");
    assert_eq!(
        rig.session.set_voltage(1.0).await,
        Err(Error::Mode { live_mode: 2 })
    );
    assert!(count_logged(&log, "poll first") <= polls + 1);
    assert_eq!(rig.c8s_after(ms(0)).len(), c8s);
}

/// Test: UT-SESS-023
#[tokio::test(start_paused = true)]
async fn a_fault_blocks_only_output_on() {
    let faulty = fixtures::c3_with(0, 0, 1 << 5, 1300, 1000);
    let rig = granted(
        "UT-SESS-023-4",
        vec![
            reply(Kind::Ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            c3_from(Kind::Ble, &faulty, T0 + ms(2_000)),
        ],
        vec![],
    )
    .await;
    rig.until(T0 + ms(3_000)).await;
    let c8s = rig.c8s_after(ms(0)).len();
    let result = rig.session.output_on().await;
    assert_eq!(
        result,
        Err(Error::FaultActive {
            faults: Faults(1 << 5)
        })
    );
    assert!(result.unwrap_err().to_string().contains("over current"));
    assert_eq!(rig.c8s_after(ms(0)).len(), c8s);
    assert_eq!(rig.session.set_voltage(1.0).await, Ok(()));
    assert_eq!(rig.c8s_after(ms(0)).len(), c8s + 1);
}

/// Test: UT-SESS-024
#[tokio::test(start_paused = true)]
async fn every_command_copies_the_reading_and_changes_one_field() {
    let log = test_log::install();
    let on = fixtures::c3_with(1, 0, 0, 500, 2000);
    let rig = granted(
        "UT-SESS-024",
        vec![
            reply(Kind::Ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            c3_from(Kind::Ble, &on, T0),
        ],
        vec![],
    )
    .await;
    let granted_at = rig.now();
    let polls = count_logged(&log, "poll first");
    assert_eq!(rig.session.set_voltage(1.0).await, Ok(()));
    assert_eq!(rig.session.set_current_limit(0.1).await, Ok(()));
    assert_eq!(rig.session.output_on().await, Ok(()));
    // Each of the three polled itself (stale by the 0xC9 rule).
    assert_eq!(count_logged(&log, "poll first"), polls + 3);
    assert_eq!(rig.session.output_off().await, Ok(()));
    assert_eq!(count_logged(&log, "poll first"), polls + 3);
    let c8s = rig.c8s_after(granted_at);
    assert_eq!(c8s.len(), 4, "{c8s:?}");
    let outputs: Vec<u8> = c8s.iter().map(|(_, p)| output(p)).collect();
    assert_eq!(outputs, vec![1, 1, 1, 0]);
    let sets: Vec<(u16, u16)> = c8s.iter().map(|(_, p)| setpoints(p)).collect();
    assert_eq!(
        sets,
        vec![(100, 2000), (500, 100), (500, 2000), (500, 2000)]
    );
    for (_, payload) in &c8s {
        assert_eq!(remote_con(payload), 1);
        // realChange, voltageSlow and currentOver from the reading, model
        // and refresh 0.
        assert_eq!(&payload[5..8], &[on[22], on[23], on[21]]);
        assert_eq!((payload[9], payload[10]), (0, 0));
    }
    let mut previous = granted_at;
    for (sent, _) in &c8s[..3] {
        // The session's `0xC2`, after the previous `0xC9` (100 ms after its
        // `0xC8`) plus the settle time.
        assert!(
            last_c2_before(&rig, *sent) >= previous + ms(100),
            "{sent:?}"
        );
        previous = *sent + ms(100);
    }
}

/// Test: UT-SESS-025
#[tokio::test(start_paused = true)]
async fn a_rejected_command_compares_the_next_reading() {
    let ble = Kind::Ble;
    let low = fixtures::c3_with(0, 0, 0, 150, 1000);
    let mut rig = granted(
        "UT-SESS-025",
        vec![
            c9_ok(ble),
            c9_once(ble, 0xFF, ms(100), ms(1_200)),
            reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            c3_from(ble, &low, ms(1_300)),
        ],
        vec![],
    )
    .await;
    assert_eq!(rig.session.set_voltage(1.7).await, Ok(()));
    assert!(rig.now() < ms(1_200));
    let events = rig.record();
    let (_, result) = rig
        .call_at(
            T0 + ms(1_000),
            |s| async move { s.set_current_limit(0.2).await },
        )
        .await
        .unwrap();
    assert_eq!(
        result,
        Err(Error::CommandRejected {
            status: 0xFF,
            reason: "busy".to_string()
        })
    );
    let rejected_at = rig.now();
    let log = test_log::install();
    let polls = count_logged(&log, "poll first");
    assert_eq!(rig.session.set_voltage(1.7).await, Ok(()));
    assert_eq!(count_logged(&log, "poll first"), polls + 1);
    let changes: Vec<(Duration, SessionEvent)> = events
        .all()
        .into_iter()
        .filter(|(_, e)| matches!(e, SessionEvent::SetpointsChanged { .. }))
        .collect();
    assert_eq!(changes.len(), 1, "{changes:?}");
    assert!(changes[0].0 > rejected_at - ms(1));
    assert_eq!(
        changes[0].1,
        SessionEvent::SetpointsChanged {
            set_volts: 1.5,
            set_amps: 1.0,
            expected_volts: 1.7,
            expected_amps: 1.0,
        }
    );
    let c8s = rig.c8s_after(rejected_at);
    assert_eq!(c8s.len(), 1);
    assert!(polled_between(&rig, rejected_at, c8s[0].0));
}

/// Test: UT-SESS-025
#[tokio::test(start_paused = true)]
async fn status_one_other_status_and_timeout() {
    let ble = Kind::Ble;
    // Status 1: the grant was lost.
    let mut rig = granted(
        "UT-SESS-025-1",
        vec![c9_ok(ble), c9_once(ble, 0x01, ms(100), ms(600))],
        vec![],
    )
    .await;
    rig.until(ms(1_000)).await;
    rig.drain();
    assert_eq!(
        rig.session.set_voltage(1.7).await,
        Err(Error::RemoteControlLost)
    );
    assert!(rig
        .drain_non_readings()
        .contains(&SessionEvent::RemoteControl(RemoteState::Lost)));
    let c8s = rig.c8s_after(ms(0)).len();
    assert_eq!(
        rig.session.set_voltage(1.7).await,
        Err(Error::RemoteControlLost)
    );
    assert_eq!(rig.c8s_after(ms(0)).len(), c8s);
    // Status 7.
    let rig = granted(
        "UT-SESS-025-7",
        vec![c9_ok(ble), c9_once(ble, 0x07, ms(100), ms(600))],
        vec![],
    )
    .await;
    rig.until(ms(1_000)).await;
    assert_eq!(
        rig.session.set_voltage(1.7).await,
        Err(Error::CommandRejected {
            status: 7,
            reason: "status 7".to_string()
        })
    );
    // No 0xC9 at all.
    let mut rig = granted(
        "UT-SESS-025-none",
        vec![c9_ok(ble), c8_unanswered(ms(600))],
        vec![],
    )
    .await;
    rig.until(ms(1_000)).await;
    rig.drain();
    assert_eq!(
        rig.session.set_voltage(1.7).await,
        Err(Error::Timeout {
            opcode: 0xC8,
            after: Duration::from_secs(1)
        })
    );
    rig.until(rig.now() + ms(1_000)).await;
    assert!(!rig
        .drain_non_readings()
        .iter()
        .any(|e| matches!(e, SessionEvent::SetpointsChanged { .. })));
}

/// Test: UT-SESS-026
#[tokio::test(start_paused = true)]
async fn output_off_uses_the_latest_reading_whatever_its_age() {
    let log = test_log::install();
    // The default script: the readings keep reporting 1300 and 1000.
    let mut rig = granted("UT-SESS-026-1", vec![], vec![]).await;
    assert_eq!(rig.session.set_voltage(1.7).await, Ok(()));
    let t1 = rig.now();
    rig.drain();
    let events = rig.record();
    let polls = count_logged(&log, "poll first");
    let (off_returned, result) = rig
        .call_at(t1, |s| async move { s.output_off().await })
        .await
        .unwrap();
    assert_eq!(result, Ok(()));
    // No `poll first`: the latest reading is used although it is stale by
    // the `0xC9` rule.
    assert_eq!(count_logged(&log, "poll first"), polls);
    let c8s = rig.c8s_after(t1);
    assert_eq!(c8s.len(), 1);
    let (off_at, off) = &c8s[0];
    assert_eq!((remote_con(off), output(off)), (1, 0));
    // `set_voltage` 170 from `accepted`, although the reading says 1300;
    // the current and the rest from the stale reading.
    assert_eq!(setpoints(off), (170, 1000));
    assert_eq!(&off[5..8], &[0x03, 0x00, 0x00]);
    // At most one `0xC2` (the link's own poll) between the voltage's
    // `0xC9` and the output-off.
    let between = rig
        .sent()
        .iter()
        .filter(|(t, op, _)| *op == 0xC2 && *t >= t1 && t < off_at)
        .count();
    assert!(between <= 1, "{between}");
    // `Ok` at the `0xC9`, 100 ms after the write.
    assert_eq!(off_returned, *off_at + ms(100));
    // Then, from the settle time on, the session's own `0xC2`.
    rig.until(off_returned + ms(1_000)).await;
    assert!(logged(&log, Level::Debug, "reading after the output-off"));
    let follow_up = rig
        .sent()
        .iter()
        .filter(|(t, op, _)| *op == 0xC2 && *t >= off_returned + ms(100))
        .count();
    assert!(follow_up >= 1);
    // The default script keeps reporting 1300: one `SetpointsChanged`.
    let changes: Vec<SessionEvent> = events
        .non_readings()
        .into_iter()
        .map(|(_, e)| e)
        .filter(|e| matches!(e, SessionEvent::SetpointsChanged { .. }))
        .collect();
    assert_eq!(
        changes,
        vec![SessionEvent::SetpointsChanged {
            set_volts: 13.0,
            set_amps: 1.0,
            expected_volts: 1.7,
            expected_amps: 1.0,
        }]
    );
    let calls = rig.markers.calls();
    assert_eq!(
        calls.last().map(|(_, c)| *c),
        Some(crate::session::doubles::MarkerCall::Clear)
    );
}

/// Test: UT-SESS-026
#[tokio::test(start_paused = true)]
async fn output_off_requests_control_first() {
    let ble = Kind::Ble;
    let mut rig = start(
        "UT-SESS-026-2",
        ble,
        script(ble, vec![c9_once(ble, 0x00, ms(2_000), ms(0)), c9_ok(ble)]),
    );
    rig.session.ready().await.unwrap();
    let events = rig.record();
    assert_eq!(rig.session.output_off().await, Ok(()));
    let prompt_at = time_of(&events, |e| matches!(e, SessionEvent::Prompt { .. })).unwrap();
    let c8s = rig.c8s_after(T0);
    assert_eq!(c8s.len(), 2);
    assert_eq!(remote_con(&c8s[0].1), 2);
    assert!(prompt_at <= c8s[1].0);
    assert!(c8s[1].0 >= T0 + ms(2_000));
    assert_eq!((remote_con(&c8s[1].1), output(&c8s[1].1)), (1, 0));
}

/// Test: UT-SESS-026
#[tokio::test(start_paused = true)]
async fn output_off_cancels_queued_and_in_progress_commands() {
    let ble = Kind::Ble;
    let rig = granted(
        "UT-SESS-026-3",
        vec![
            c9_once(ble, 0x00, ms(100), ms(0)),
            reply(ble, 0xC8, ms(300), &[0x00]),
        ],
        vec![],
    )
    .await;
    let t1 = rig.now();
    let r = rig.reading_after(t1).await;
    let first = rig.call_at(r, |s| async move { s.set_voltage(1.0).await });
    let second = rig.call_at(r, |s| async move { s.set_voltage(2.0).await });
    let third = rig.call_at(r, |s| async move { s.set_voltage(3.0).await });
    let off = rig.call_at(r + ms(50), |s| async move { s.output_off().await });
    let in_progress = Error::Cancelled {
        reason: "superseded by an output-off; it may have been applied".to_string(),
    };
    let queued = Error::Cancelled {
        reason: "superseded by an output-off".to_string(),
    };
    assert_eq!(first.await.unwrap().1, Err(in_progress));
    assert_eq!(second.await.unwrap().1, Err(queued.clone()));
    assert_eq!(third.await.unwrap().1, Err(queued));
    assert_eq!(off.await.unwrap().1, Ok(()));
    let c8s = rig.c8s_after(t1);
    assert_eq!(c8s.len(), 2, "{c8s:?}");
    assert_eq!(setpoints(&c8s[0].1), (100, 1000));
    assert_eq!(output(&c8s[1].1), 0);
}

/// Test: UT-SESS-026
#[tokio::test(start_paused = true)]
async fn output_off_retakes_a_lost_grant_once() {
    let ble = Kind::Ble;
    let rig = granted(
        "UT-SESS-026-4",
        vec![c9_ok(ble), c9_once(ble, 0x01, ms(100), ms(1_000))],
        vec![],
    )
    .await;
    rig.until(ms(1_500)).await;
    assert_eq!(rig.session.output_off().await, Ok(()));
    let c8s = rig.c8s_after(ms(1_500));
    let shape: Vec<(u8, u8)> = c8s
        .iter()
        .map(|(_, p)| (remote_con(p), output(p)))
        .collect();
    assert_eq!(shape, vec![(1, 0), (2, 0), (1, 0)]);
}

/// Test: UT-SESS-026
#[tokio::test(start_paused = true)]
async fn an_unacknowledged_output_off_times_out_after_500_ms() {
    let ble = Kind::Ble;
    let rig = granted(
        "UT-SESS-026-5",
        vec![c9_once(ble, 0x00, ms(100), ms(0))],
        vec![],
    )
    .await;
    let t1 = rig.now();
    assert_eq!(
        rig.session.output_off().await,
        Err(Error::Timeout {
            opcode: 0xC8,
            after: ms(500)
        })
    );
    let returned = rig.now();
    let c8s = rig.c8s_after(t1);
    assert_eq!(c8s.len(), 1);
    assert_eq!(returned, c8s[0].0 + ms(500));
    // The follow-up reading comes after the answer.
    rig.until(returned + ms(1_000)).await;
    assert!(polled_between(&rig, returned, rig.now()));
}

/// Test: UT-SESS-027
#[tokio::test(start_paused = true)]
async fn release_sends_remote_con_zero_once() {
    let log = test_log::install();
    let mut rig = granted("UT-SESS-027", vec![], vec![]).await;
    let t1 = rig.now();
    rig.drain();
    let polls = count_logged(&log, "poll first");
    assert_eq!(rig.session.release_remote_control().await, Ok(()));
    assert_eq!(count_logged(&log, "poll first"), polls + 1);
    let c8s = rig.c8s_after(t1);
    assert_eq!(c8s.len(), 1);
    // The session's own `0xC2`, after the grant's `0xC9` plus the settle
    // time.
    assert!(last_c2_before(&rig, c8s[0].0) >= t1 + ms(100));
    assert_eq!(remote_con(&c8s[0].1), 0);
    assert_eq!(setpoints(&c8s[0].1), (1300, 1000));
    assert_eq!(output(&c8s[0].1), 0);
    assert!(rig
        .drain_non_readings()
        .contains(&SessionEvent::RemoteControl(RemoteState::None)));
    assert_eq!(rig.session.release_remote_control().await, Ok(()));
    assert_eq!(rig.c8s_after(t1).len(), 1);
}

/// Test: UT-SESS-027
#[tokio::test(start_paused = true)]
async fn release_outside_dc_mode_and_with_status_one() {
    let ble = Kind::Ble;
    let pd = fixtures::c3_with(0, 2, 0, 1300, 1000);
    let rig = granted(
        "UT-SESS-027-pd",
        vec![
            reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            c3_from(ble, &pd, T0 + ms(1_000)),
        ],
        vec![],
    )
    .await;
    rig.until(T0 + ms(2_000)).await;
    let c8s = rig.c8s_after(ms(0)).len();
    assert_eq!(
        rig.session.release_remote_control().await,
        Err(Error::Mode { live_mode: 2 })
    );
    assert_eq!(rig.c8s_after(ms(0)).len(), c8s);

    let rig = granted(
        "UT-SESS-027-1",
        vec![c9_ok(ble), c9_once(ble, 0x01, ms(100), ms(1_000))],
        vec![],
    )
    .await;
    rig.until(ms(1_500)).await;
    assert_eq!(
        rig.session.release_remote_control().await,
        Err(Error::RemoteControlLost)
    );
    assert_eq!(rig.session.remote_state(), RemoteState::Lost);
}

/// Test: UT-SESS-027
#[tokio::test(start_paused = true)]
async fn release_in_denied_is_sent_and_ends_at_none() {
    let ble = Kind::Ble;
    let rig = start(
        "UT-SESS-027-denied",
        ble,
        script(ble, vec![c9_once(ble, 0x01, ms(100), ms(0)), c9_ok(ble)]),
    );
    rig.session.ready().await.unwrap();
    assert_eq!(
        rig.session.request_remote_control().await,
        Err(Error::RemoteControlDenied)
    );
    assert_eq!(rig.session.remote_state(), RemoteState::Denied);
    let t1 = rig.now();
    assert_eq!(rig.session.release_remote_control().await, Ok(()));
    let c8s = rig.c8s_after(t1);
    assert_eq!(c8s.len(), 1);
    assert_eq!(remote_con(&c8s[0].1), 0);
    assert_eq!(rig.session.remote_state(), RemoteState::None);
}

/// Test: UT-SESS-028
#[tokio::test(start_paused = true)]
async fn late_replies_are_logged_and_ignored() {
    let log = test_log::install();
    let ble = Kind::Ble;
    let mut script = script(ble, vec![]);
    script.injections = vec![
        inject(ble, T0 + ms(1_000), 0xC9, &[0x00]),
        inject(ble, T0 + ms(2_000), 0x19, &[0x00]),
    ];
    let rig = start("UT-SESS-028", ble, script);
    rig.session.ready().await.unwrap();
    let mut rig = rig;
    rig.drain();
    let events = rig.record();
    rig.until(T0 + ms(2_500)).await;
    assert!(logged(&log, Level::Warn, "late reply 0xc9"));
    assert!(logged(&log, Level::Warn, "late reply 0x19"));
    assert_eq!(rig.session.remote_state(), RemoteState::None);
    assert_eq!(rig.session.link_state(), LinkState::Ready);
    assert!(
        events.non_readings().is_empty(),
        "{:?}",
        events.non_readings()
    );
}

/// Test: UT-SESS-029
#[tokio::test(start_paused = true)]
async fn a_call_dropped_before_the_task_took_it_sends_nothing() {
    let ble = Kind::Ble;
    let rig = start(
        "UT-SESS-029-1",
        ble,
        script(ble, vec![c9_once(ble, 0x00, ms(500), ms(0)), c9_ok(ble)]),
    );
    rig.session.ready().await.unwrap();
    let request = rig.call_at(T0, |s| async move { s.request_remote_control().await });
    rig.until(T0 + ms(10)).await;
    let dropped = tokio::time::timeout(ms(10), rig.session.set_voltage(1.0)).await;
    assert!(dropped.is_err());
    assert_eq!(request.await.unwrap().1, Ok(()));
    rig.until(T0 + ms(2_000)).await;
    let c8s = rig.c8s_after(T0);
    assert_eq!(c8s.len(), 1);
    assert_eq!(remote_con(&c8s[0].1), 2);
}

/// Test: UT-SESS-029
#[tokio::test(start_paused = true)]
async fn a_call_dropped_after_its_write_completes() {
    let log = test_log::install();
    let ble = Kind::Ble;
    // The voltage reaches the supply: from 520 ms on the readings show it.
    let rig = granted(
        "UT-SESS-029-2",
        vec![
            c9_once(ble, 0x00, ms(100), ms(0)),
            reply(ble, 0xC8, ms(300), &[0x00]),
            reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            c3_from(ble, &fixtures::c3_with(0, 0, 0, 100, 1000), ms(520)),
        ],
        vec![],
    )
    .await;
    let mut rig = rig;
    let events = rig.record();
    let t1 = rig.now();
    rig.reading_after(t1 + ms(100)).await;
    let called = rig.now();
    let dropped = tokio::time::timeout(ms(100), rig.session.set_voltage(1.0)).await;
    assert!(dropped.is_err());
    let left = rig.now();
    assert_eq!(left, called + ms(100));
    // One `0xC8` is on the wire: it was already written when the caller
    // left (its `0xC9` comes 300 ms after it).
    rig.until(left + ms(10)).await;
    let c8s = rig.c8s_after(t1);
    assert_eq!(c8s.len(), 1);
    assert_eq!(c8s[0].0, called);
    assert_eq!(setpoints(&c8s[0].1), (100, 1000));
    // The step was dropped with its caller: the `0xC9` is not handled.
    assert!(logged(
        &log,
        Level::Debug,
        "cancelled: SetVoltage(1.0), the caller is gone"
    ));
    assert!(!logged(&log, Level::Debug, "command SetVoltage(1.0)"));
    // The session resynchronises: the next command waits for a reading
    // after the drop and then the settle time.
    assert_eq!(rig.session.set_current_limit(0.1).await, Ok(()));
    let first_after = events
        .reading_times()
        .into_iter()
        .find(|t| *t > left)
        .unwrap();
    let next = rig.c8s_after(left + ms(1))[0].0;
    assert!(
        last_c2_before(&rig, next) >= first_after + ms(100),
        "{next:?} {first_after:?}"
    );
    // The setpoints were unknown: a settled reading showing the voltage is
    // reported against the reading the command was built from, since no
    // `expected` was recorded for the dropped call.
    assert_eq!(
        setpoint_changes(
            &events
                .non_readings()
                .into_iter()
                .map(|(_, e)| e)
                .collect::<Vec<_>>()
        ),
        vec![SessionEvent::SetpointsChanged {
            set_volts: 1.0,
            set_amps: 1.0,
            expected_volts: 13.0,
            expected_amps: 1.0,
        }]
    );
}

/// Test: UT-SESS-029
#[tokio::test(start_paused = true)]
async fn a_call_dropped_during_the_prompt_keeps_the_grant() {
    let ble = Kind::Ble;
    let rig = start(
        "UT-SESS-029-3",
        ble,
        script(ble, vec![c9_once(ble, 0x00, ms(2_000), ms(0)), c9_ok(ble)]),
    );
    rig.session.ready().await.unwrap();
    let dropped = tokio::time::timeout(ms(1_000), rig.session.set_voltage(1.0)).await;
    assert!(dropped.is_err());
    rig.until(T0 + ms(4_000)).await;
    assert_eq!(rig.session.remote_state(), RemoteState::Granted);
    let c8s = rig.c8s_after(T0);
    assert_eq!(c8s.len(), 1);
    assert_eq!(remote_con(&c8s[0].1), 2);
}

/// Test: UT-SESS-045
#[tokio::test(start_paused = true)]
async fn events_and_queries_are_served_while_a_command_waits() {
    let ble = Kind::Ble;
    let mut script = script(ble, vec![c9_once(ble, 0x00, ms(5_000), ms(0)), c9_ok(ble)]);
    script.injections = vec![inject(ble, T0 + ms(2_000), 0xC5, &fixtures::C5_SETTINGS)];
    let mut rig = start("UT-SESS-045", ble, script);
    rig.session.ready().await.unwrap();
    let events = rig.record();
    let call = rig.call_at(T0, |s| async move { s.set_voltage(1.0).await });
    let (session, start) = (Arc::clone(&rig.session), rig.start);
    let reads = tokio::spawn(async move {
        sleep_until(start + T0 + ms(1_000)).await;
        let first = session.latest_reading().unwrap().at;
        sleep_until(start + T0 + ms(3_000)).await;
        let second = session.latest_reading().unwrap().at;
        (first, second)
    });
    let (first, second) = reads.await.unwrap();
    assert!(second > first);
    let (returned, result) = call.await.unwrap();
    assert_eq!(result, Ok(()));
    let settings_at = time_of(&events, |e| matches!(e, SessionEvent::SettingsChanged(_))).unwrap();
    assert_eq!(settings_at, T0 + ms(2_000));
    assert!(settings_at < returned);
    assert!(returned >= T0 + ms(5_000), "{returned:?}");
}

/// Test: UT-SESS-022
#[tokio::test(start_paused = true)]
async fn usb_request_rejected_returns_to_none() {
    let hid = Kind::Hid;
    for (id, status, expected) in [
        (
            "UT-SESS-022-ff",
            0xFF,
            Error::CommandRejected {
                status: 0xFF,
                reason: "busy".to_string(),
            },
        ),
        (
            "UT-SESS-022-07",
            0x07,
            Error::CommandRejected {
                status: 7,
                reason: "status 7".to_string(),
            },
        ),
    ] {
        let rig = start(
            id,
            hid,
            script(hid, vec![c9_once(hid, status, ms(100), ms(0)), c9_ok(hid)]),
        );
        rig.session.ready().await.unwrap();
        assert_eq!(rig.session.set_voltage(1.7).await, Err(expected));
        assert_eq!(rig.session.remote_state(), RemoteState::None);
        assert_eq!(rig.c8s_after(ms(0)).len(), 1);
    }
}

/// Test: UT-SESS-026
#[tokio::test(start_paused = true)]
async fn a_second_output_off_runs_after_the_first() {
    let rig = granted("UT-SESS-026-twice", vec![], vec![]).await;
    let t1 = rig.now();
    let first = rig.call_at(t1, |s| async move { s.output_off().await });
    let second = rig.call_at(t1, |s| async move { s.output_off().await });
    assert_eq!(first.await.unwrap().1, Ok(()));
    assert_eq!(second.await.unwrap().1, Ok(()));
    let c8s = rig.c8s_after(t1);
    let shape: Vec<(u8, u8)> = c8s
        .iter()
        .map(|(_, p)| (remote_con(p), output(p)))
        .collect();
    assert_eq!(shape, vec![(1, 0), (1, 0)]);
}

/// Test: UT-SESS-026
#[tokio::test(start_paused = true)]
async fn output_off_rejected_or_outside_dc_mode() {
    let ble = Kind::Ble;
    let rig = granted(
        "UT-SESS-026-ff",
        vec![c9_ok(ble), c9_once(ble, 0xFF, ms(100), ms(1_000))],
        vec![],
    )
    .await;
    rig.until(ms(1_500)).await;
    assert_eq!(
        rig.session.output_off().await,
        Err(Error::CommandRejected {
            status: 0xFF,
            reason: "busy".to_string()
        })
    );
    let pd = fixtures::c3_with(0, 2, 0, 1300, 1000);
    let rig = granted(
        "UT-SESS-026-pd",
        vec![
            reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            c3_from(ble, &pd, T0 + ms(1_000)),
        ],
        vec![],
    )
    .await;
    rig.until(T0 + ms(2_000)).await;
    let c8s = rig.c8s_after(ms(0)).len();
    assert_eq!(
        rig.session.output_off().await,
        Err(Error::Mode { live_mode: 2 })
    );
    assert_eq!(rig.c8s_after(ms(0)).len(), c8s);
}

/// Test: UT-SESS-049
#[tokio::test(start_paused = true)]
async fn a_second_output_off_cancels_the_commands_queued_before_it() {
    let ble = Kind::Ble;
    let rig = granted(
        "UT-SESS-049",
        vec![
            c9_once(ble, 0x00, ms(100), ms(0)),
            reply(ble, 0xC8, ms(300), &[0x00]),
        ],
        vec![],
    )
    .await;
    let t1 = rig.now();
    let r = rig.reading_after(t1).await;
    let first_off = rig.call_at(r, |s| async move { s.output_off().await });
    let on = rig.call_at(r + ms(50), |s| async move { s.output_on().await });
    let second_off = rig.call_at(r + ms(100), |s| async move { s.output_off().await });
    assert_eq!(
        on.await.unwrap().1,
        Err(Error::Cancelled {
            reason: "superseded by an output-off".to_string()
        })
    );
    assert_eq!(first_off.await.unwrap().1, Ok(()));
    assert_eq!(second_off.await.unwrap().1, Ok(()));
    rig.until(rig.now() + ms(2_000)).await;
    let c8s = rig.c8s_after(t1);
    let shape: Vec<(u8, u8)> = c8s
        .iter()
        .map(|(_, p)| (remote_con(p), output(p)))
        .collect();
    assert_eq!(shape, vec![(1, 0), (1, 0)]);
}

/// Every event the driven task delivered so far that is not a reading.
fn driven_non_readings(d: &mut Driven) -> Vec<SessionEvent> {
    std::iter::from_fn(|| d.events.try_next())
        .filter(|e| !matches!(e, SessionEvent::Reading(_)))
        .collect()
}

/// UT-SESS-050: on Bluetooth in `None`, a `set_voltage` starts the remote
/// request; `output_off()` arrives either before the link took the request
/// (`written` false) or after the link wrote it and resolved its
/// `Outcome::Deferred`, before the task took that step (`written` true).
async fn output_off_meets_a_remote_request(id: &str, written: bool) {
    let ble = Kind::Ble;
    let mut d = driven(
        id,
        ble,
        script(ble, vec![c9_once(ble, 0x00, ms(2_000), ms(0)), c9_ok(ble)]),
    );
    d.until_ready().await;
    let _ = driven_non_readings(&mut d);
    let mut voltage = d.command(CommandKind::SetVoltage(1.0));
    d.task.turn().await;
    assert_eq!(d.task.op_name(), Some("control"));
    if written {
        d.until_sent(|s| s.frame.opcode() == 0xC8).await;
    }
    let mut off = d.output_off();
    let (_, voltage_result) = d.drive(&mut voltage).await;
    assert_eq!(voltage_result, Err(cancelled(true)));
    let (off_at, off_result) = d.drive(&mut off).await;
    assert_eq!(off_result, Ok(()));
    let c8s = d.c8s();
    assert_eq!(shape(&c8s), vec![(2, 0), (1, 0)], "{c8s:?}");
    let requested_at = c8s[0].0;
    assert!(c8s[1].0 >= requested_at + ms(2_000));
    assert!(off_at > c8s[1].0);
    let events = driven_non_readings(&mut d);
    let prompts = events
        .iter()
        .filter(|e| matches!(e, SessionEvent::Prompt { .. }))
        .count();
    assert_eq!(prompts, 1, "{events:?}");
    assert_eq!(
        events
            .iter()
            .filter(|e| matches!(e, SessionEvent::RemoteControl(_)))
            .collect::<Vec<_>>(),
        vec![
            &SessionEvent::RemoteControl(RemoteState::Requested),
            &SessionEvent::RemoteControl(RemoteState::Granted),
        ]
    );
}

/// Test: UT-SESS-050
#[tokio::test(start_paused = true)]
async fn an_output_off_takes_over_a_remote_request_not_yet_written() {
    output_off_meets_a_remote_request("UT-SESS-050-off-queued", false).await;
}

/// Test: UT-SESS-050
#[tokio::test(start_paused = true)]
async fn an_output_off_takes_over_a_remote_request_just_written() {
    output_off_meets_a_remote_request("UT-SESS-050-off-written", true).await;
}

/// The time of the first `0xC8` the first mock was sent at or after `from`.
fn c8_at(rig: &Rig, from: Duration) -> Duration {
    rig.c8s_after(from)[0].0
}

/// UT-SESS-051: a granted session whose next `0xC8` (the output-off) is
/// answered by `c9`, with the transport closing at `close_at`. The link
/// polls from the grant at t0 + 100 ms: replies at t0 + 230, 460, 690 ms,
/// so it is free between t0 + 460 and t0 + 560 ms.
async fn granted_for_the_output_off(id: &str, c9: Reply, close_at: Option<Duration>) -> Rig {
    let ble = Kind::Ble;
    let mut script = script(ble, vec![c9_once(ble, 0x00, ms(100), ms(0)), c9]);
    script.close_at = close_at;
    let rig = start(id, ble, script);
    rig.session.ready().await.unwrap();
    rig.session.request_remote_control().await.unwrap();
    assert_eq!(rig.now(), T0 + ms(100));
    rig
}

/// Test: UT-SESS-051
#[tokio::test(start_paused = true)]
async fn an_output_off_is_answered_at_its_0xc9() {
    let ble = Kind::Ble;
    let rig = granted_for_the_output_off("UT-SESS-051-a", c9_ok(ble), None).await;
    let (at, result) = rig
        .call_at(T0 + ms(470), |s| async move { s.output_off().await })
        .await
        .unwrap();
    let written = c8_at(&rig, T0 + ms(470));
    assert_eq!(written, T0 + ms(470));
    assert_eq!(result, Ok(()));
    assert_eq!(at, written + ms(100));
    // The follow-up reading comes after the answer.
    rig.until(at + ms(1_000)).await;
    assert!(rig.sent().iter().any(|(t, op, _)| *op == 0xC2 && *t >= at));
}

/// Test: UT-SESS-051
#[tokio::test(start_paused = true)]
async fn an_accepted_output_off_stays_ok_when_the_link_drops_before_the_follow_up() {
    let ble = Kind::Ble;
    // The 0xC9 at t0 + 570 ms, the transport closes 50 ms later.
    let rig = granted_for_the_output_off("UT-SESS-051-b", c9_ok(ble), Some(T0 + ms(620))).await;
    let (at, result) = rig
        .call_at(T0 + ms(470), |s| async move { s.output_off().await })
        .await
        .unwrap();
    assert_eq!(c8_at(&rig, T0 + ms(470)), T0 + ms(470));
    assert_eq!(result, Ok(()));
    assert_eq!(at, T0 + ms(570));
    rig.until(T0 + ms(1_000)).await;
    assert_eq!(rig.session.link_state(), LinkState::Lost);
}

/// Test: UT-SESS-051
#[tokio::test(start_paused = true)]
async fn an_accepted_output_off_stays_ok_when_a_close_follows() {
    let ble = Kind::Ble;
    let rig = granted_for_the_output_off("UT-SESS-051-c", c9_ok(ble), None).await;
    let off = rig.call_at(T0 + ms(470), |s| async move { s.output_off().await });
    let close = rig.call_at(T0 + ms(620), |s| async move { s.close(false).await });
    let (at, result) = off.await.unwrap();
    assert_eq!(c8_at(&rig, T0 + ms(470)), T0 + ms(470));
    assert_eq!(result, Ok(()));
    assert_eq!(at, T0 + ms(570));
    assert_eq!(close.await.unwrap().1, Ok(()));
}

/// Test: UT-SESS-051
#[tokio::test(start_paused = true)]
async fn an_unacknowledged_output_off_is_answered_500_ms_after_its_write() {
    let rig = granted_for_the_output_off("UT-SESS-051-d", c8_unanswered(ms(0)), None).await;
    let (at, result) = rig
        .call_at(T0 + ms(470), |s| async move { s.output_off().await })
        .await
        .unwrap();
    let written = c8_at(&rig, T0 + ms(470));
    assert_eq!(written, T0 + ms(470));
    assert_eq!(
        result,
        Err(Error::Timeout {
            opcode: 0xC8,
            after: ms(500)
        })
    );
    assert_eq!(at, written + ms(500));
    rig.until(at + ms(1_000)).await;
    assert!(rig.sent().iter().any(|(t, op, _)| *op == 0xC2 && *t >= at));
}

/// Test: UT-SESS-023
#[tokio::test(start_paused = true)]
async fn the_guards_refuse_before_the_implicit_request() {
    let ble = Kind::Ble;
    // Guard (1) before guard (3): not ready yet.
    let rig = start("UT-SESS-023-none-1", ble, script(ble, vec![]));
    assert_eq!(rig.session.set_voltage(31.0).await, Err(Error::NotReady));
    // Guard (3) before (7): no request, no prompt.
    let mut rig = start("UT-SESS-023-none-3", ble, script(ble, vec![]));
    rig.session.ready().await.unwrap();
    assert!(matches!(
        rig.session.set_voltage(31.0).await,
        Err(Error::SetpointRange { .. })
    ));
    assert!(matches!(
        rig.session.set_current_limit(-1.0).await,
        Err(Error::SetpointRange { .. })
    ));
    rig.until(T0 + ms(500)).await;
    assert!(rig.c8s_after(ms(0)).is_empty());
    assert!(!prompted(&rig.drain_non_readings()));
    assert_eq!(rig.session.remote_state(), RemoteState::None);
    // Guard (5) before (7): a PD-mode reading.
    let pd = fixtures::c3_with(0, 2, 0, 1300, 1000);
    let mut rig = start(
        "UT-SESS-023-none-5",
        ble,
        script(
            ble,
            vec![
                reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
                c3_from(ble, &pd, T0 + ms(1_000)),
            ],
        ),
    );
    rig.session.ready().await.unwrap();
    rig.until(T0 + ms(2_000)).await;
    assert_eq!(
        rig.session.set_voltage(1.0).await,
        Err(Error::Mode { live_mode: 2 })
    );
    rig.until(T0 + ms(2_500)).await;
    assert!(rig.c8s_after(ms(0)).is_empty());
    assert!(!prompted(&rig.drain_non_readings()));
    // Guard (6) before (7): an output-on with a fault.
    let faulty = fixtures::c3_with(0, 0, 1 << 5, 1300, 1000);
    let mut rig = start(
        "UT-SESS-023-none-6",
        ble,
        script(ble, vec![reply(ble, 0xC2, ms(130), &faulty)]),
    );
    rig.session.ready().await.unwrap();
    assert_eq!(
        rig.session.output_on().await,
        Err(Error::FaultActive {
            faults: Faults(1 << 5)
        })
    );
    rig.until(T0 + ms(500)).await;
    assert!(rig.c8s_after(ms(0)).is_empty());
    assert!(!prompted(&rig.drain_non_readings()));
}

/// Test: UT-SESS-023
#[tokio::test(start_paused = true)]
async fn denied_and_lost_are_refused_before_the_range_check() {
    let ble = Kind::Ble;
    let rig = start(
        "UT-SESS-023-denied",
        ble,
        script(ble, vec![c9_once(ble, 0x01, ms(100), ms(0)), c9_ok(ble)]),
    );
    rig.session.ready().await.unwrap();
    assert_eq!(
        rig.session.request_remote_control().await,
        Err(Error::RemoteControlDenied)
    );
    assert_eq!(
        rig.session.set_voltage(31.0).await,
        Err(Error::RemoteControlDenied)
    );
    let rig = granted(
        "UT-SESS-023-lost",
        vec![c9_ok(ble), c9_once(ble, 0x01, ms(100), ms(600))],
        vec![],
    )
    .await;
    rig.until(ms(1_000)).await;
    assert_eq!(
        rig.session.set_voltage(1.7).await,
        Err(Error::RemoteControlLost)
    );
    assert_eq!(
        rig.session.set_voltage(31.0).await,
        Err(Error::RemoteControlLost)
    );
}

/// Test: UT-SESS-023
#[tokio::test(start_paused = true)]
async fn the_mode_and_fault_checks_run_again_after_the_grant() {
    let ble = Kind::Ble;
    // The request at t0 is built from a DC reading; the reading turns PD
    // during the prompt; the grant comes at t0 + 2 s.
    let pd = fixtures::c3_with(0, 2, 0, 1300, 1000);
    let rig = start(
        "UT-SESS-023-recheck-5",
        ble,
        script(
            ble,
            vec![
                c9_once(ble, 0x00, ms(2_000), ms(0)),
                c9_ok(ble),
                reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
                c3_from(ble, &pd, T0 + ms(1_000)),
            ],
        ),
    );
    rig.session.ready().await.unwrap();
    assert_eq!(
        rig.session.set_voltage(1.0).await,
        Err(Error::Mode { live_mode: 2 })
    );
    assert_eq!(rig.session.remote_state(), RemoteState::Granted);
    let c8s = rig.c8s_after(ms(0));
    assert_eq!(c8s.len(), 1, "{c8s:?}");
    assert_eq!(remote_con(&c8s[0].1), 2);
    // The same with a fault and output_on.
    let faulty = fixtures::c3_with(0, 0, 1 << 5, 1300, 1000);
    let rig = start(
        "UT-SESS-023-recheck-6",
        ble,
        script(
            ble,
            vec![
                c9_once(ble, 0x00, ms(2_000), ms(0)),
                c9_ok(ble),
                reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
                c3_from(ble, &faulty, T0 + ms(1_000)),
            ],
        ),
    );
    rig.session.ready().await.unwrap();
    assert_eq!(
        rig.session.output_on().await,
        Err(Error::FaultActive {
            faults: Faults(1 << 5)
        })
    );
    let c8s = rig.c8s_after(ms(0));
    assert_eq!(c8s.len(), 1, "{c8s:?}");
    assert_eq!(remote_con(&c8s[0].1), 2);
}

/// Test: UT-SESS-023
#[tokio::test(start_paused = true)]
async fn a_copied_field_out_of_bounds_and_a_failing_poll_are_returned() {
    let ble = Kind::Ble;
    // Guard (8): the reading's voltage setpoint is above the firmware's
    // bound, so the copy fails.
    let high = fixtures::c3_with(0, 0, 0, 5000, 1000);
    let rig = granted(
        "UT-SESS-023-8",
        vec![
            reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            c3_from(ble, &high, T0 + ms(500)),
        ],
        vec![],
    )
    .await;
    rig.until(T0 + ms(1_500)).await;
    let c8s = rig.c8s_after(ms(0)).len();
    assert_eq!(
        rig.session.set_current_limit(0.1).await,
        Err(Error::Protocol(crate::protocol::error::Reason::Value {
            field: "setVoltage",
            value: 5000
        }))
    );
    assert_eq!(rig.c8s_after(ms(0)).len(), c8s);
    // Guard (4): the command's own 0xC2 gets no reply. The grant's 0xC9
    // at t0 + 100 ms makes the reading stale; the link's poll goes at
    // t0 + 100 ms, the session's at t0 + 330 ms, unanswered.
    let rig = granted(
        "UT-SESS-023-4-poll",
        vec![
            reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            Reply {
                request: 0xC2,
                deliveries: Vec::new(),
                repeat: Some(1),
                from: T0 + ms(300),
                ..Reply::default()
            },
        ],
        vec![],
    )
    .await;
    let c8s = rig.c8s_after(ms(0)).len();
    assert_eq!(
        rig.session.set_voltage(1.0).await,
        Err(Error::Timeout {
            opcode: 0xC2,
            after: Duration::from_secs(1)
        })
    );
    assert_eq!(rig.c8s_after(ms(0)).len(), c8s);
}

/// Test: UT-SESS-024
#[tokio::test(start_paused = true)]
async fn output_on_sets_the_output_byte() {
    let rig = granted("UT-SESS-024-on", vec![], vec![]).await;
    let t1 = rig.now();
    assert_eq!(rig.session.output_on().await, Ok(()));
    let c8s = rig.c8s_after(t1);
    assert_eq!(c8s.len(), 1);
    // The reading shows the output off; the command switches it on.
    assert_eq!((remote_con(&c8s[0].1), output(&c8s[0].1)), (1, 1));
    assert_eq!(setpoints(&c8s[0].1), (1300, 1000));
}

/// The `SetpointsChanged` of a supply now at 5.00 V and 1.000 A after a
/// failed command built from the capture (13.00 V, 1.000 A).
fn changed_to_5_v() -> SessionEvent {
    SessionEvent::SetpointsChanged {
        set_volts: 5.0,
        set_amps: 1.0,
        expected_volts: 13.0,
        expected_amps: 1.0,
    }
}

/// Test: UT-SESS-025
#[tokio::test(start_paused = true)]
async fn status_one_other_status_and_timeout_mark_the_setpoints_unknown() {
    let ble = Kind::Ble;
    let five = fixtures::c3_with(0, 0, 0, 500, 1000);
    // The failing 0xC8 is written at 1 s; the readings show 5.00 V from
    // 1.05 s on (the supply may have applied it).
    for (id, c9) in [
        (
            "UT-SESS-025-1-changed",
            c9_once(ble, 0x01, ms(100), ms(600)),
        ),
        (
            "UT-SESS-025-7-changed",
            c9_once(ble, 0x07, ms(100), ms(600)),
        ),
        ("UT-SESS-025-none-changed", c8_unanswered(ms(600))),
    ] {
        let mut rig = granted(
            id,
            vec![
                c9_ok(ble),
                c9,
                reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
                c3_from(ble, &five, ms(1_050)),
            ],
            vec![],
        )
        .await;
        rig.until(ms(1_000)).await;
        rig.drain();
        assert!(rig.session.set_voltage(1.7).await.is_err());
        rig.until(rig.now() + ms(1_500)).await;
        assert_eq!(
            setpoint_changes(&rig.drain_non_readings()),
            vec![changed_to_5_v()],
            "{id}"
        );
    }
}

/// Test: UT-SESS-025
#[tokio::test(start_paused = true)]
async fn an_accepted_current_limit_is_the_expected_one() {
    let ble = Kind::Ble;
    let mut rig = granted(
        "UT-SESS-025-current",
        vec![c9_ok(ble), c9_once(ble, 0xFF, ms(100), ms(1_200))],
        vec![],
    )
    .await;
    assert_eq!(rig.session.set_current_limit(0.2).await, Ok(()));
    rig.until(ms(1_200)).await;
    rig.drain();
    assert!(matches!(
        rig.session.set_voltage(1.7).await,
        Err(Error::CommandRejected { status: 0xFF, .. })
    ));
    rig.until(rig.now() + ms(1_000)).await;
    // The supply still reports 1.000 A; the user set 0.2 A.
    assert_eq!(
        setpoint_changes(&rig.drain_non_readings()),
        vec![SessionEvent::SetpointsChanged {
            set_volts: 13.0,
            set_amps: 1.0,
            expected_volts: 13.0,
            expected_amps: 0.2,
        }]
    );
}

/// Test: UT-SESS-026
#[tokio::test(start_paused = true)]
async fn the_setpoints_are_unknown_after_a_cancellation() {
    let ble = Kind::Ble;
    let at_1_v = fixtures::c3_with(0, 0, 0, 100, 1000);
    // As UT-SESS-026 (3): the grant at t0 + 100 ms, the voltage 0xC8 at
    // t0 + 230 ms (answered after 300 ms), the output-off 50 ms later; the
    // readings show the voltage applied from t0 + 300 ms on.
    let mut rig = granted(
        "UT-SESS-026-3-changed",
        vec![
            c9_once(ble, 0x00, ms(100), ms(0)),
            reply(ble, 0xC8, ms(300), &[0x00]),
            reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            c3_from(ble, &at_1_v, T0 + ms(300)),
        ],
        vec![],
    )
    .await;
    let t1 = rig.now();
    let r = rig.reading_after(t1).await;
    rig.drain();
    let voltage = rig.call_at(r, |s| async move { s.set_voltage(1.0).await });
    let off = rig.call_at(r + ms(50), |s| async move { s.output_off().await });
    assert_eq!(voltage.await.unwrap().1, Err(cancelled(true)));
    assert_eq!(off.await.unwrap().1, Ok(()));
    rig.until(rig.now() + ms(1_500)).await;
    assert_eq!(
        setpoint_changes(&rig.drain_non_readings()),
        vec![SessionEvent::SetpointsChanged {
            set_volts: 1.0,
            set_amps: 1.0,
            expected_volts: 13.0,
            expected_amps: 1.0,
        }]
    );
}

/// Test: UT-SESS-026
#[tokio::test(start_paused = true)]
async fn the_reading_after_an_output_off_is_compared() {
    let ble = Kind::Ble;
    let five = fixtures::c3_with(0, 0, 0, 500, 1000);
    let mut rig = granted(
        "UT-SESS-026-1-changed",
        vec![
            reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            c3_from(ble, &five, ms(1_050)),
        ],
        vec![],
    )
    .await;
    rig.until(ms(1_000)).await;
    rig.drain();
    assert_eq!(rig.session.output_off().await, Ok(()));
    rig.until(rig.now() + ms(1_500)).await;
    assert_eq!(
        setpoint_changes(&rig.drain_non_readings()),
        vec![changed_to_5_v()]
    );
}

/// Test: UT-SESS-026
#[tokio::test(start_paused = true)]
async fn an_output_off_during_an_open_prompt_awaits_it() {
    let ble = Kind::Ble;
    // Granted: the command is cancelled, the output-off waits for the
    // grant and then switches off.
    let rig = start(
        "UT-SESS-026-prompt-granted",
        ble,
        script(ble, vec![c9_once(ble, 0x00, ms(2_000), ms(0)), c9_ok(ble)]),
    );
    rig.session.ready().await.unwrap();
    let voltage = rig.call_at(T0, |s| async move { s.set_voltage(1.0).await });
    let off = rig.call_at(T0 + ms(1_000), |s| async move { s.output_off().await });
    assert_eq!(voltage.await.unwrap().1, Err(cancelled(true)));
    let (off_at, result) = off.await.unwrap();
    assert_eq!(result, Ok(()));
    let c8s = rig.c8s_after(T0);
    assert_eq!(shape(&c8s), vec![(2, 0), (1, 0)]);
    assert!(c8s[1].0 >= T0 + ms(2_000));
    assert!(off_at >= T0 + ms(2_000));
    // Denied: the output-off returns the denial and sends nothing more.
    let rig = start(
        "UT-SESS-026-prompt-denied",
        ble,
        script(ble, vec![c9_once(ble, 0x01, ms(2_000), ms(0)), c9_ok(ble)]),
    );
    rig.session.ready().await.unwrap();
    let voltage = rig.call_at(T0, |s| async move { s.set_voltage(1.0).await });
    let off = rig.call_at(T0 + ms(1_000), |s| async move { s.output_off().await });
    assert_eq!(voltage.await.unwrap().1, Err(cancelled(true)));
    assert_eq!(off.await.unwrap().1, Err(Error::RemoteControlDenied));
    rig.until(T0 + ms(3_000)).await;
    assert_eq!(shape(&rig.c8s_after(T0)), vec![(2, 0)]);
    assert_eq!(rig.session.remote_state(), RemoteState::Denied);
}

/// Test: UT-SESS-026
#[tokio::test(start_paused = true)]
async fn an_output_off_in_denied_or_lost_requests_control_first() {
    let ble = Kind::Ble;
    // Denied after a denied request.
    let mut rig = start(
        "UT-SESS-026-denied",
        ble,
        script(ble, vec![c9_once(ble, 0x01, ms(100), ms(0)), c9_ok(ble)]),
    );
    rig.session.ready().await.unwrap();
    assert_eq!(
        rig.session.request_remote_control().await,
        Err(Error::RemoteControlDenied)
    );
    let t1 = rig.now();
    rig.drain();
    assert_eq!(rig.session.output_off().await, Ok(()));
    assert_eq!(shape(&rig.c8s_after(t1)), vec![(2, 0), (1, 0)]);
    assert!(prompted(&rig.drain_non_readings()));
    // Lost after a status 1.
    let rig = granted(
        "UT-SESS-026-lost",
        vec![c9_ok(ble), c9_once(ble, 0x01, ms(100), ms(600))],
        vec![],
    )
    .await;
    rig.until(ms(1_000)).await;
    assert_eq!(
        rig.session.set_voltage(1.7).await,
        Err(Error::RemoteControlLost)
    );
    let t1 = rig.now();
    assert_eq!(rig.session.output_off().await, Ok(()));
    assert_eq!(shape(&rig.c8s_after(t1)), vec![(2, 0), (1, 0)]);
    assert_eq!(rig.session.remote_state(), RemoteState::Granted);
}

/// Test: UT-SESS-026
#[tokio::test(start_paused = true)]
async fn an_output_off_retries_once_only() {
    let ble = Kind::Ble;
    // Status 1 to the output-off, the request granted, status 1 again
    // (three entries eligible from 1 s on, used in list order).
    let rig = granted(
        "UT-SESS-026-4-twice",
        vec![
            c9_ok(ble),
            c9_once(ble, 0x01, ms(100), ms(1_000)),
            c9_once(ble, 0x00, ms(100), ms(1_000)),
            c9_once(ble, 0x01, ms(100), ms(1_000)),
        ],
        vec![],
    )
    .await;
    rig.until(ms(1_500)).await;
    let c8s = rig.c8s_after(ms(0)).len();
    assert_eq!(
        rig.session.output_off().await,
        Err(Error::RemoteControlLost)
    );
    rig.until(rig.now() + ms(2_000)).await;
    assert_eq!(
        shape(&rig.c8s_after(ms(0))[c8s..]),
        vec![(1, 0), (2, 0), (1, 0)]
    );
    assert_eq!(rig.session.remote_state(), RemoteState::Lost);
}

/// The options of UT-SESS-060: limits 12 V and 1 A.
fn tight() -> crate::session::Options {
    crate::session::Options::new(
        false,
        Limits {
            max_volts: Some(12.0),
            max_amps: Some(1.0),
        },
    )
    .with_wall_origin(wall0())
}

/// A session to `id` on Bluetooth with the limits of UT-SESS-060 whose
/// readings are `payload`.
fn tight_session(id: &str, payload: &[u8]) -> Rig {
    let ble = Kind::Ble;
    let id_owned = id.to_string();
    let mut script = Some(script(ble, vec![reply(ble, 0xC2, ms(130), payload)]));
    let connector = MockConnector::new(move || {
        Ok(Mock::new(ble, &id_owned, script.take().unwrap_or_default()))
    });
    start_with(id, connector, MemoryMarkers::new(), tight())
}

/// The error of guard (7) for a copied voltage of 20 V against 12 V.
fn copied_20_v() -> Error {
    Error::SetpointRange {
        field: "voltage",
        value: 20.0,
        min: 0.0,
        max: 12.0,
    }
}

/// Test: UT-SESS-060
#[tokio::test(start_paused = true)]
async fn the_user_limits_apply_to_the_copied_setpoints_of_a_frame_with_the_output_on() {
    // (1) Output off, setpoints (2000, 500): output_on would switch on at 20 V.
    let mut rig = tight_session("UT-SESS-060-1", &fixtures::c3_with(0, 0, 0, 2000, 500));
    rig.session.ready().await.unwrap();
    rig.drain();
    assert_eq!(rig.session.output_on().await, Err(copied_20_v()));
    rig.until(T0 + ms(1_000)).await;
    assert!(rig.c8s_after(ms(0)).is_empty());
    assert!(!prompted(&rig.drain_non_readings()));
    assert_eq!(rig.session.remote_state(), RemoteState::None);
    // (2) Output on: a current change would keep 20 V on the output.
    let mut rig = tight_session("UT-SESS-060-2", &fixtures::c3_with(1, 0, 0, 2000, 500));
    rig.session.ready().await.unwrap();
    rig.drain();
    assert_eq!(rig.session.set_current_limit(0.5).await, Err(copied_20_v()));
    rig.until(T0 + ms(1_000)).await;
    assert!(rig.c8s_after(ms(0)).is_empty());
    assert!(!prompted(&rig.drain_non_readings()));
    // (3) The same reading with the output off: the command is sent.
    let rig = tight_session("UT-SESS-060-3", &fixtures::c3_with(0, 0, 0, 2000, 500));
    rig.session.ready().await.unwrap();
    assert_eq!(rig.session.set_current_limit(0.5).await, Ok(()));
    let c8s = rig.c8s_after(ms(0));
    assert_eq!(shape(&c8s), vec![(2, 0), (1, 0)]);
    assert_eq!(setpoints(&c8s[1].1), (2000, 500));
}

/// Test: UT-SESS-060
#[tokio::test(start_paused = true)]
async fn invalid_limits_are_refused_at_connect_and_by_set_limits() {
    let nan = crate::session::Options::new(
        false,
        Limits {
            max_volts: Some(f64::NAN),
            max_amps: None,
        },
    );
    let connector = Arc::new(MockConnector::new(|| {
        Ok(Mock::new(Kind::Ble, "UT-SESS-060-4", Script::default()))
    }));
    let result = Session::connect(
        Arc::clone(&connector) as Arc<dyn crate::session::Connector>,
        "UT-SESS-060-4",
        host_id(),
        Arc::new(MemoryMarkers::new()),
        nan,
    );
    assert!(
        matches!(
            result,
            Err(Error::SetpointRange {
                field: "voltage limit",
                ..
            })
        ),
        "{result:?}"
    );
    tokio::task::yield_now().await;
    assert!(connector.handles().is_empty());
    // Nothing was registered either: the identifier opens normally.
    let rig = tight_session("UT-SESS-060-4", &fixtures::C3_CAPTURE);
    let before = *crate::session::lock(&rig.session.shared.limits);
    assert_eq!(
        rig.session.set_limits(Limits {
            max_volts: Some(12.0),
            max_amps: Some(-1.0),
        }),
        Err(Error::SetpointRange {
            field: "current limit",
            value: -1.0,
            min: 0.0,
            max: f64::INFINITY,
        })
    );
    assert_eq!(*crate::session::lock(&rig.session.shared.limits), before);
    assert_eq!(
        rig.session.set_limits(Limits {
            max_volts: Some(5.0),
            max_amps: None,
        }),
        Ok(())
    );
    assert_eq!(
        *crate::session::lock(&rig.session.shared.limits),
        Limits {
            max_volts: Some(5.0),
            max_amps: None,
        }
    );
}

/// Test: UT-SESS-053
#[tokio::test(start_paused = true)]
async fn a_command_whose_caller_left_while_queued_in_the_link_is_never_written() {
    let log = test_log::install();
    let rig = granted("UT-SESS-053", vec![], vec![]).await;
    let t1 = rig.now();
    // A reading after the settle time; the link's next poll goes 100 ms
    // after it and is answered 130 ms later.
    let r = rig.reading_after(t1 + ms(100)).await;
    rig.until(r + ms(110)).await;
    let poll_at = last_c2_before(&rig, rig.now() + ms(1));
    assert!(poll_at > r, "a poll must be in flight");
    assert!(rig.session.latest_reading().unwrap().at - rig.start < poll_at);
    // The reading is fresh, so the `0xC8` goes to the link at once and waits
    // behind the poll; the caller leaves before the poll's reply.
    let dropped = tokio::time::timeout(ms(30), rig.session.set_voltage(1.0)).await;
    assert!(dropped.is_err());
    assert!(rig.now() < poll_at + ms(130));
    rig.until(rig.now() + ms(2_000)).await;
    assert!(rig.c8s_after(t1).is_empty(), "{:?}", rig.c8s_after(t1));
    assert!(logged(
        &log,
        Level::Debug,
        "cancelled: SetVoltage(1.0), the caller is gone"
    ));
    // The session goes on: a later command is sent.
    assert_eq!(rig.session.set_voltage(2.0).await, Ok(()));
    assert_eq!(setpoints(&rig.c8s_after(t1)[0].1), (200, 1000));
}

/// A USB reply to `request` after 2 ms.
fn usb_fast(request: u8, payload: &[u8]) -> Reply {
    reply(Kind::Hid, request, ms(2), payload)
}

/// Test: UT-SESS-055
#[tokio::test(start_paused = true)]
async fn a_command_after_a_0xc9_waits_for_the_settle_time() {
    let log = test_log::install();
    let hid = Kind::Hid;
    // Replies after 2 ms; the supply's `0xC3` shows the effect of a command
    // only 50 ms after its `0xC9`. The `0xC9`s come at 472, 618 and 882 ms
    // (checked below), so the readings switch at 522, 668 and 932 ms.
    let script = script(
        hid,
        vec![
            usb_fast(0xE0, &fixtures::E1_USB),
            usb_fast(0xC8, &[0x00]),
            usb_fast(0xC2, &fixtures::C3_CAPTURE),
            Reply {
                from: ms(522),
                ..usb_fast(0xC2, &fixtures::c3_with(0, 0, 0, 170, 1000))
            },
            Reply {
                from: ms(668),
                ..usb_fast(0xC2, &fixtures::c3_with(0, 0, 0, 170, 100))
            },
            Reply {
                from: ms(932),
                ..usb_fast(0xC2, &fixtures::c3_with(1, 0, 0, 170, 100))
            },
        ],
    );
    let rig = start("UT-SESS-055", hid, script);
    rig.session.ready().await.unwrap();
    rig.session.request_remote_control().await.unwrap();
    // The link polls every 102 ms; at 470 ms the reading (412 ms) is fresh
    // and 58 ms old.
    let voltage = rig.call_at(ms(470), |s| async move { s.set_voltage(1.7).await });
    assert_eq!(voltage.await.unwrap().1, Ok(()));
    let polls = count_logged(&log, "poll first");
    assert_eq!(rig.session.set_current_limit(0.1).await, Ok(()));
    let c8s = rig.c8s_after(ms(470));
    assert_eq!(c8s[0].0, ms(470));
    // The current command waited until 100 ms after the voltage's `0xC9`
    // (472 ms), polled, and copies the new voltage, not 1300.
    assert!(last_c2_before(&rig, c8s[1].0) >= ms(572), "{c8s:?}");
    assert_eq!(setpoints(&c8s[1].1), (170, 100));
    let lines: Vec<String> = log
        .lines_here(crate::session::LOG_TARGET)
        .into_iter()
        .map(|(_, m)| m)
        .filter(|m| m.starts_with("poll first"))
        .collect();
    assert_eq!(lines.len(), polls + 1);
    assert!(lines[polls].contains("settle wait"), "{lines:?}");
    // The output-on, built from a fresh reading 60 ms old, is accepted at
    // 882 ms; the voltage right after it waits too and copies `output` 1.
    let on = rig.call_at(ms(880), |s| async move { s.output_on().await });
    assert_eq!(on.await.unwrap().1, Ok(()));
    assert_eq!(rig.session.set_voltage(2.0).await, Ok(()));
    let c8s = rig.c8s_after(ms(880));
    assert_eq!(c8s[0].0, ms(880));
    assert_eq!(output(&c8s[0].1), 1);
    assert!(last_c2_before(&rig, c8s[1].0) >= ms(982), "{c8s:?}");
    assert_eq!(setpoints(&c8s[1].1), (200, 100));
    assert_eq!(output(&c8s[1].1), 1);
}

/// Test: UT-SESS-056
#[tokio::test(start_paused = true)]
async fn an_output_off_right_after_accepted_setpoints_keeps_them() {
    let ble = Kind::Ble;
    // Granted at 380 ms. The voltage `0xC8` is written at 740 ms (`0xC9` at
    // 840 ms), the current `0xC8` at 1200 ms (`0xC9` at 1300 ms); the script
    // reports each accepted setpoint from 100 ms after its `0xC9`.
    let rig = granted(
        "UT-SESS-056",
        vec![
            reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            c3_from(ble, &fixtures::c3_with(0, 0, 0, 170, 1000), ms(940)),
            c3_from(ble, &fixtures::c3_with(0, 0, 0, 170, 100), ms(1_400)),
        ],
        vec![],
    )
    .await;
    let t1 = rig.now();
    assert_eq!(rig.session.set_voltage(1.7).await, Ok(()));
    assert_eq!(rig.session.set_current_limit(0.1).await, Ok(()));
    assert_eq!(rig.session.output_off().await, Ok(()));
    let c8s = rig.c8s_after(t1);
    assert_eq!(shape(&c8s), vec![(1, 0), (1, 0), (1, 0)]);
    assert_eq!((c8s[0].0, c8s[1].0), (ms(740), ms(1_200)));
    assert_eq!(setpoints(&c8s[1].1), (170, 100));
    // The latest reading (1200 ms) still says 1.000 A; the frame takes both
    // setpoints from `accepted`.
    assert_eq!(setpoints(&c8s[2].1), (170, 100));
}

/// Test: UT-SESS-056
#[tokio::test(start_paused = true)]
async fn an_output_off_within_the_settle_time_of_an_accepted_command_uses_it() {
    let hid = Kind::Hid;
    // USB, replies after 2 ms: ready at 4 ms, granted at 6 ms, the link
    // polls at 104, 206, ... 410 ms (replies 2 ms later). The voltage `0xC8`
    // at 511 ms is accepted at T = 513 ms; the link's own poll, due at
    // 512 ms, goes right after it and is answered at T + 2 ms with 1300.
    let script = script(
        hid,
        vec![
            usb_fast(0xE0, &fixtures::E1_USB),
            usb_fast(0xC8, &[0x00]),
            usb_fast(0xC2, &fixtures::C3_CAPTURE),
        ],
    );
    let rig = start("UT-SESS-056-usb", hid, script);
    rig.session.ready().await.unwrap();
    rig.session.request_remote_control().await.unwrap();
    let voltage = rig.call_at(ms(511), |s| async move { s.set_voltage(1.7).await });
    let (accepted_at, result) = voltage.await.unwrap();
    assert_eq!(result, Ok(()));
    assert_eq!(accepted_at, ms(513));
    let off = rig.call_at(ms(533), |s| async move { s.output_off().await });
    assert_eq!(off.await.unwrap().1, Ok(()));
    let latest = last_c2_before(&rig, ms(533));
    assert_eq!(latest, ms(513));
    let c8s = rig.c8s_after(ms(533));
    // The reading (515 ms) arrived after the `0xC9` but within its settle
    // time: the frame carries 170 from `accepted`.
    assert_eq!(shape(&c8s), vec![(1, 0)]);
    assert_eq!(setpoints(&c8s[0].1), (170, 1000));
}

/// Test: UT-SESS-056
#[tokio::test(start_paused = true)]
async fn a_release_does_not_replace_accepted() {
    let ble = Kind::Ble;
    let mut d = driven("UT-SESS-056-release", ble, script(ble, vec![]));
    d.until_ready().await;
    let mut rx = d.command(CommandKind::Request);
    assert_eq!(d.drive(&mut rx).await.1, Ok(()));
    let mut rx = d.command(CommandKind::SetVoltage(1.7));
    assert_eq!(d.drive(&mut rx).await.1, Ok(()));
    assert_eq!(d.task.accepted_setpoints(), Some((170, 1000)));
    let mut rx = d.command(CommandKind::Release);
    assert_eq!(d.drive(&mut rx).await.1, Ok(()));
    // The release carried the reading's (1300, 1000); it applies no field.
    assert_eq!(setpoints(&d.c8s().last().unwrap().1), (1300, 1000));
    assert_eq!(d.task.accepted_setpoints(), Some((170, 1000)));
    let mut off = d.output_off();
    assert_eq!(d.drive(&mut off).await.1, Ok(()));
    assert_eq!(
        shape(&d.c8s()),
        vec![(2, 0), (1, 0), (0, 0), (2, 0), (1, 0)]
    );
}

/// Test: UT-SESS-056
#[tokio::test(start_paused = true)]
async fn an_output_off_after_a_settled_front_panel_change_respects_it() {
    let ble = Kind::Ble;
    // The front panel sets (500, 2000) from 1.5 s on.
    let rig = granted(
        "UT-SESS-056-panel",
        vec![
            reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            c3_from(ble, &fixtures::c3_with(0, 0, 0, 500, 2000), ms(1_500)),
        ],
        vec![],
    )
    .await;
    assert_eq!(rig.session.set_voltage(1.7).await, Ok(()));
    let t1 = rig.now();
    assert!(t1 < ms(1_500));
    // A reading newer than the settle time shows the change.
    let r = rig.reading_after(ms(1_500)).await;
    assert_eq!(
        rig.session
            .latest_reading()
            .unwrap()
            .reading
            .raw
            .set_voltage,
        500
    );
    // It arrived at least 200 ms after the last accepted `0xC9`.
    assert!(r >= t1 + ms(200), "{r:?} {t1:?}");
    assert_eq!(rig.session.output_off().await, Ok(()));
    let c8s = rig.c8s_after(t1);
    assert_eq!(c8s.len(), 1);
    assert_eq!(setpoints(&c8s[0].1), (500, 2000));
}

/// Test: UT-SESS-022
#[tokio::test(start_paused = true)]
async fn a_rejected_usb_request_marks_the_setpoints_unknown() {
    let hid = Kind::Hid;
    // Ready at 230 ms over USB; the request is answered `FF` at 330 ms; the
    // readings report 5.00 V for every `0xC2` from 300 ms on (the request
    // carried a full copy of the state), so the first settled reading
    // (460 ms) shows it.
    let mut rig = start(
        "UT-SESS-022-unknown",
        hid,
        script(
            hid,
            vec![
                c9_once(hid, 0xFF, ms(100), ms(0)),
                c9_ok(hid),
                reply(hid, 0xC2, ms(130), &fixtures::C3_CAPTURE),
                c3_from(hid, &fixtures::c3_with(0, 0, 0, 500, 1000), ms(300)),
            ],
        ),
    );
    rig.session.ready().await.unwrap();
    rig.drain();
    assert!(matches!(
        rig.session.set_voltage(1.7).await,
        Err(Error::CommandRejected { status: 0xFF, .. })
    ));
    rig.until(T0 + ms(1_500)).await;
    assert_eq!(
        setpoint_changes(&rig.drain_non_readings()),
        vec![SessionEvent::SetpointsChanged {
            set_volts: 5.0,
            set_amps: 1.0,
            expected_volts: 13.0,
            expected_amps: 1.0,
        }]
    );
}

/// Test: UT-SESS-061
#[tokio::test(start_paused = true)]
async fn after_a_timed_out_output_off_a_command_waits_for_a_reading_after_the_late_0xc9() {
    let log = test_log::install();
    let hid = Kind::Hid;
    let on = fixtures::c3_with(1, 0, 0, 1300, 1000);
    let off = fixtures::c3_with(0, 0, 0, 1300, 1000);
    // USB, replies after 2 ms, the output on. The output-off `0xC8` at
    // 450 ms gets no `0xC9` within 500 ms (it times out at 950 ms); the
    // next `0xC2` (the link's, at 950 ms) is answered at 952 ms with the
    // output still on; the late `0xC9 00` arrives 50 ms after that reading
    // (1002 ms) and the output reads off from 20 ms after it (1022 ms).
    let script = script(
        hid,
        vec![
            usb_fast(0xE0, &fixtures::E1_USB),
            usb_fast(0xC8, &[0x00]),
            Reply {
                repeat: Some(1),
                from: ms(400),
                ..reply(hid, 0xC8, ms(552), &[0x00])
            },
            usb_fast(0xC2, &on),
            Reply {
                from: ms(1_022),
                ..usb_fast(0xC2, &off)
            },
        ],
    );
    let rig = start("UT-SESS-061-1", hid, script);
    rig.session.ready().await.unwrap();
    rig.session.request_remote_control().await.unwrap();
    let off_call = rig.call_at(ms(450), |s| async move { s.output_off().await });
    let voltage = rig.call_at(ms(951), |s| async move { s.set_voltage(1.0).await });
    assert_eq!(
        off_call.await.unwrap(),
        (
            ms(950),
            Err(Error::Timeout {
                opcode: 0xC8,
                after: ms(500)
            })
        )
    );
    assert_eq!(voltage.await.unwrap().1, Ok(()));
    assert!(logged(&log, Level::Warn, "late reply 0xc9"));
    let c8s = rig.c8s_after(ms(450));
    assert_eq!(shape(&c8s), vec![(1, 0), (1, 0)], "{c8s:?}");
    // The voltage frame was built from a reading that arrived at least
    // 100 ms after the late `0xC9` (1002 ms): its `0xC2` went out at or
    // after 1102 ms, and it carries `output` 0.
    let late = ms(1_002);
    assert!(
        last_c2_before(&rig, c8s[1].0) + ms(2) >= late + ms(100),
        "{c8s:?}"
    );
    assert_eq!(setpoints(&c8s[1].1), (100, 1000));
    // From the output-off on, no `0xC8` carries `output` 1.
    assert!(!rig.c8s_after(ms(450)).iter().any(|(_, p)| output(p) == 1));
}

/// Test: UT-SESS-061
#[tokio::test(start_paused = true)]
async fn after_a_timed_out_command_the_next_waits_for_a_reading_and_the_settle_time() {
    // Granted at 380 ms; the voltage `0xC8` at 510 ms gets no `0xC9` and
    // times out at 1510 ms; the link's next `0xC2` goes at 1510 ms and its
    // reading arrives at R = 1640 ms. A command issued right after R waits
    // until R + 100 ms.
    let rig = granted(
        "UT-SESS-061-3",
        vec![c9_ok(Kind::Ble), c8_unanswered(ms(500))],
        vec![],
    )
    .await;
    let r0 = rig.reading_after(T0 + ms(200)).await;
    let voltage = rig.call_at(r0, |s| async move { s.set_voltage(1.0).await });
    let (timed_out, result) = voltage.await.unwrap();
    assert_eq!(
        result,
        Err(Error::Timeout {
            opcode: 0xC8,
            after: Duration::from_secs(1)
        })
    );
    let r = rig.reading_after(timed_out).await;
    assert!(r > timed_out);
    let called = rig.now();
    assert_eq!(rig.session.set_current_limit(0.1).await, Ok(()));
    let next = rig.c8s_after(called)[0].0;
    assert!(last_c2_before(&rig, next) >= r + ms(100), "{next:?} {r:?}");
}

/// Test: UT-SESS-063
#[tokio::test(start_paused = true)]
async fn an_output_off_outside_dc_mode_requests_nothing() {
    let ble = Kind::Ble;
    let pd = fixtures::c3_with(0, 2, 0, 1300, 1000);
    let mut rig = start(
        "UT-SESS-063",
        ble,
        script(ble, vec![reply(ble, 0xC2, ms(130), &pd)]),
    );
    rig.session.ready().await.unwrap();
    assert_eq!(rig.session.remote_state(), RemoteState::None);
    rig.drain();
    assert_eq!(
        rig.session.output_off().await,
        Err(Error::Mode { live_mode: 2 })
    );
    rig.until(T0 + ms(2_000)).await;
    assert!(rig.c8s_after(ms(0)).is_empty());
    assert!(!prompted(&rig.drain_non_readings()));
    assert_eq!(rig.session.remote_state(), RemoteState::None);
}

/// Test: UT-SESS-064
#[tokio::test(flavor = "multi_thread", worker_threads = 2)]
async fn calls_are_taken_in_the_order_of_their_first_poll() {
    use futures::FutureExt;
    let rig = granted("UT-SESS-064-order", vec![], vec![]).await;
    let t1 = rig.now();
    let session = Arc::clone(&rig.session);
    let mut on = Box::pin(session.output_on());
    let mut voltage = Box::pin(session.set_voltage(1.0));
    let mut off = Box::pin(session.output_off());
    assert!(on.as_mut().now_or_never().is_none());
    assert!(voltage.as_mut().now_or_never().is_none());
    assert!(off.as_mut().now_or_never().is_none());
    let (on, voltage, off) = tokio::join!(on, voltage, off);
    assert_eq!(off, Ok(()));
    // The output-off cancels the two before it or follows them.
    for result in [on, voltage] {
        assert!(
            matches!(result, Ok(()) | Err(Error::Cancelled { .. })),
            "{result:?}"
        );
    }
    let c8s = rig.c8s_after(t1);
    let (_, last) = c8s.last().unwrap();
    assert_eq!((remote_con(last), output(last)), (1, 0), "{c8s:?}");
}
