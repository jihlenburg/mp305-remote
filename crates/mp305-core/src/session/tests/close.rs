//! Implements: nothing; holds the tests of UT-SESS-044, UT-SESS-050 (with
//! a close), UT-SESS-054 and UT-SESS-057 to UT-SESS-059.
//!
//! Task tests: the close sequence.

use super::*;
use crate::session::doubles::MarkerCall;
use crate::session::{CommandKind, LinkState, Markers, RemoteState};
use crate::transport::test_log;
use log::Level;

/// The error of a call after the close.
fn closed() -> Error {
    Error::LinkLost {
        text: "closed by the host".to_string(),
    }
}

/// A reading with the output on, in DC mode, at the capture's setpoints.
fn output_on() -> Vec<u8> {
    fixtures::c3_with(1, 0, 0, 1300, 1000)
}

/// Asserts that every `0xC8` in `c8s` was preceded by a `0xC2` sent after
/// the previous one (or after `from`).
fn each_polled_first(rig: &Rig, from: Duration, c8s: &[(Duration, Vec<u8>)]) {
    let mut previous = from;
    for (sent, _) in c8s {
        assert!(
            rig.sent()
                .iter()
                .any(|(t, op, _)| *op == 0xC2 && *t >= previous && t < sent),
            "no 0xC2 before the 0xC8 at {sent:?}"
        );
        previous = *sent;
    }
}

/// Whether the store holds a marker for `id`.
fn marker_present(rig: &Rig, id: &str) -> bool {
    rig.markers.present(id).unwrap().is_some()
}

/// Test: UT-SESS-044
#[tokio::test(start_paused = true)]
async fn close_switches_off_releases_and_disconnects() {
    let log = test_log::install();
    let ble = Kind::Ble;
    let mut rig = granted(
        "UT-SESS-044-1",
        vec![reply(ble, 0xC2, ms(130), &output_on())],
        vec![],
    )
    .await;
    let events = rig.record();
    assert_eq!(rig.session.set_voltage(1.7).await, Ok(()));
    let t1 = rig.now();
    // The reading is stale by the `0xC9` rule: the close waits for the
    // settle time and polls before it decides (a `poll first` line).
    let polls = count_logged(&log, "poll first");
    assert_eq!(rig.session.close(true).await, Ok(()));
    assert_eq!(count_logged(&log, "poll first"), polls + 1);
    let c8s = rig.c8s_after(t1);
    assert_eq!(shape(&c8s), vec![(1, 0), (0, 0)]);
    each_polled_first(&rig, t1, &c8s);
    assert_eq!(rig.mock(0).closes(), 1);
    assert_eq!(
        rig.markers.calls().last().map(|(_, c)| *c),
        Some(MarkerCall::Clear)
    );
    tokio::time::sleep(ms(1)).await;
    assert!(events.ended());
    assert_eq!(rig.session.link_state(), LinkState::Closed);
    assert_eq!(rig.session.ready().await, Err(closed()));
    assert_eq!(rig.session.set_voltage(1.0).await, Err(closed()));
    assert_eq!(rig.session.output_off().await, Err(closed()));
}

/// Test: UT-SESS-044
#[tokio::test(start_paused = true)]
async fn close_without_output_off_still_releases() {
    let log = test_log::install();
    let ble = Kind::Ble;
    let rig = granted(
        "UT-SESS-044-2",
        vec![reply(ble, 0xC2, ms(130), &output_on())],
        vec![],
    )
    .await;
    assert_eq!(rig.session.set_voltage(1.7).await, Ok(()));
    let t1 = rig.now();
    let polls = count_logged(&log, "poll first");
    assert_eq!(rig.session.close(false).await, Ok(()));
    assert_eq!(count_logged(&log, "poll first"), polls + 1);
    let c8s = rig.c8s_after(t1);
    assert_eq!(shape(&c8s), vec![(0, 1)]);
    each_polled_first(&rig, t1, &c8s);
}

/// Test: UT-SESS-044
#[tokio::test(start_paused = true)]
async fn close_without_remote_control_releases_anyway() {
    let rig = start("UT-SESS-044-3", Kind::Ble, script(Kind::Ble, vec![]));
    rig.session.ready().await.unwrap();
    assert_eq!(rig.session.remote_state(), RemoteState::None);
    let t1 = rig.now();
    assert_eq!(rig.session.close(true).await, Ok(()));
    let c8s = rig.c8s_after(t1);
    assert_eq!(shape(&c8s), vec![(0, 0)]);
    assert_eq!(rig.mock(0).closes(), 1);
}

/// Test: UT-SESS-044
#[tokio::test(start_paused = true)]
async fn close_in_denied_logs_the_release_status() {
    let log = test_log::install();
    let ble = Kind::Ble;
    let rig = start(
        "UT-SESS-044-4",
        ble,
        script(ble, vec![reply(ble, 0xC8, ms(100), &[0x01])]),
    );
    rig.session.ready().await.unwrap();
    assert_eq!(
        rig.session.request_remote_control().await,
        Err(Error::RemoteControlDenied)
    );
    let t1 = rig.now();
    assert_eq!(rig.session.close(true).await, Ok(()));
    let c8s = rig.c8s_after(t1);
    assert_eq!(shape(&c8s), vec![(0, 0)]);
    assert!(logged(&log, Level::Info, "release status Ok(NotGranted)"));
}

/// Test: UT-SESS-044
#[tokio::test(start_paused = true)]
async fn close_after_a_loss_sends_nothing_and_keeps_the_marker() {
    let id = "UT-SESS-044-5";
    let ble = Kind::Ble;
    let mut script = script(ble, vec![reply(ble, 0xC2, ms(130), &output_on())]);
    script.close_at = Some(ms(1_500));
    let rig = start(id, ble, script);
    rig.session.ready().await.unwrap();
    rig.session.request_remote_control().await.unwrap();
    rig.until(Duration::from_secs(2)).await;
    assert_eq!(rig.session.link_state(), LinkState::Lost);
    // A marker was written while the output was on; the loss leaves it.
    assert!(rig
        .markers
        .calls()
        .iter()
        .any(|(_, c)| matches!(c, MarkerCall::Set(_))));
    let calls = rig.markers.calls().len();
    let sent = rig.sent().len();
    assert_eq!(rig.session.close(true).await, Ok(()));
    assert_eq!(rig.sent().len(), sent);
    // No `Clear` on the loss or on the close in `Lost` (DD-SESS-042,
    // DD-SESS-053).
    assert!(!rig.markers.calls()[..calls]
        .iter()
        .any(|(_, c)| *c == MarkerCall::Clear));
    assert_eq!(rig.markers.calls().len(), calls);
    assert!(marker_present(&rig, id));
    let again = start(
        id,
        Kind::Ble,
        crate::session::tests::script(Kind::Ble, vec![]),
    );
    assert!(again.session.ready().await.is_ok());
}

/// Test: UT-SESS-044
#[tokio::test(start_paused = true)]
async fn close_during_a_command_fails_it_and_closes() {
    let ble = Kind::Ble;
    // The request at t0 is answered after 100 ms, the voltage `0xC8` after
    // 2 s (once, from 300 ms on), every later `0xC8` after 100 ms.
    let rig = granted(
        "UT-SESS-044-6",
        vec![
            c9_once(ble, 0x00, ms(100), ms(0)),
            c9_once(ble, 0x00, ms(2_000), ms(300)),
            c9_ok(ble),
        ],
        vec![],
    )
    .await;
    let t1 = rig.now();
    let r = rig.reading_after(t1 + ms(100)).await;
    let call = rig.call_at(r, |s| async move { s.set_voltage(1.0).await });
    let close = rig.call_at(r + ms(50), |s| async move { s.close(true).await });
    assert_eq!(call.await.unwrap().1, Err(closed()));
    let (closed_at, result) = close.await.unwrap();
    assert_eq!(result, Ok(()));
    let c8s = rig.c8s_after(t1);
    let written = c8s[0].0;
    // `reading_after` notices the reading within 1 ms.
    assert!(written >= r && written <= r + ms(1), "{written:?}");
    // The voltage `0xC8` (in flight), then, since a command that may have
    // been applied was cancelled, the output-off whatever the reading shows,
    // then the release with `output` 0.
    assert_eq!(shape(&c8s), vec![(1, 0), (1, 0), (0, 0)]);
    assert_eq!(setpoints(&c8s[0].1), (100, 1000));
    // The close is done before the voltage's late `0xC9` could arrive, so
    // the release was answered by its own `0xC9`.
    assert!(closed_at < written + ms(2_000), "{closed_at:?}");
    // The decision waited for the reply bound and the settle time after the
    // cancellation, and was taken on a reading polled after it.
    assert!(c8s[1].0 >= r + ms(50) + ms(1_100));
    assert_eq!(rig.mock(0).closes(), 1);
}

/// Test: UT-SESS-044
#[tokio::test(start_paused = true)]
async fn close_twice_answers_both_with_the_first_result() {
    let rig = start("UT-SESS-044-7", Kind::Ble, script(Kind::Ble, vec![]));
    rig.session.ready().await.unwrap();
    let first = rig.call_at(T0, |s| async move { s.close(true).await });
    let second = rig.call_at(T0, |s| async move { s.close(true).await });
    assert_eq!(first.await.unwrap().1, Ok(()));
    assert_eq!(second.await.unwrap().1, Ok(()));
    assert_eq!(rig.session.close(true).await, Ok(()));
    assert_eq!(rig.mock(0).closes(), 1);
}

/// Test: UT-SESS-044
#[tokio::test(start_paused = true)]
async fn close_waits_for_an_open_remote_request() {
    let ble = Kind::Ble;
    let mut script = script(ble, vec![c9_once(ble, 0x00, ms(2_000), ms(0)), c9_ok(ble)]);
    script.replies.retain(|r| r.request != 0xC2);
    script.replies.push(reply(ble, 0xC2, ms(130), &output_on()));
    let mut rig = start("UT-SESS-044-8", ble, script);
    rig.session.ready().await.unwrap();
    rig.drain();
    let call = rig.call_at(T0, |s| async move { s.set_voltage(1.0).await });
    let close = rig.call_at(T0 + ms(1_000), |s| async move { s.close(true).await });
    assert_eq!(call.await.unwrap().1, Err(closed()));
    let (closed_at, result) = close.await.unwrap();
    assert_eq!(result, Ok(()));
    assert!(closed_at > T0 + ms(2_000));
    let c8s = rig.c8s_after(T0);
    assert_eq!(shape(&c8s), vec![(2, 1), (1, 0), (0, 0)]);
    assert!(c8s[1].0 > T0 + ms(2_000));
}

/// Test: UT-SESS-044
#[tokio::test(start_paused = true)]
async fn close_during_the_connect_flow_closes_the_link() {
    let ble = Kind::Ble;
    let rig = start(
        "UT-SESS-044-connecting",
        ble,
        script(
            ble,
            vec![Reply {
                repeat: Some(1),
                ..reply(ble, 0x18, ms(50), &[0xFF])
            }],
        ),
    );
    rig.until(ms(1_000)).await;
    assert_eq!(rig.session.link_state(), LinkState::Binding);
    assert_eq!(rig.session.close(true).await, Ok(()));
    assert_eq!(rig.session.ready().await, Err(closed()));
    assert_eq!(rig.session.link_state(), LinkState::Closed);
    assert_eq!(rig.mock(0).closes(), 1);
    assert_eq!(rig.opcodes(), vec![0x18, 0x18]);
}

/// Test: UT-SESS-044
#[tokio::test(start_paused = true)]
async fn close_during_an_output_off_fails_it_and_switches_off_again() {
    let ble = Kind::Ble;
    let rig = granted(
        "UT-SESS-044-off",
        vec![
            reply(ble, 0xC2, ms(130), &output_on()),
            c9_once(ble, 0x00, ms(100), ms(0)),
            reply(ble, 0xC8, ms(400), &[0x00]),
        ],
        vec![],
    )
    .await;
    let t1 = rig.now();
    let off = rig.call_at(t1, |s| async move { s.output_off().await });
    let close = rig.call_at(t1 + ms(50), |s| async move { s.close(true).await });
    assert_eq!(off.await.unwrap().1, Err(closed()));
    assert_eq!(close.await.unwrap().1, Ok(()));
    // The cancelled output-off (written by the link in any case), the
    // close's own output-off, the release with `output` 0.
    assert_eq!(shape(&rig.c8s_after(t1)), vec![(1, 0), (1, 0), (0, 0)]);
    assert_eq!(rig.mock(0).closes(), 1);
}

/// Test: UT-SESS-044
#[tokio::test(start_paused = true)]
async fn close_with_the_output_on_and_no_grant_requests_control_first() {
    let ble = Kind::Ble;
    // `None`: the close's output-off requests control (with the prompt),
    // then switches off, then releases.
    let mut rig = start(
        "UT-SESS-044-none-on",
        ble,
        script(ble, vec![reply(ble, 0xC2, ms(130), &output_on())]),
    );
    rig.session.ready().await.unwrap();
    rig.drain();
    assert_eq!(rig.session.close(true).await, Ok(()));
    assert_eq!(shape(&rig.c8s_after(T0)), vec![(2, 1), (1, 0), (0, 0)]);
    assert!(prompted(&rig.drain_non_readings()));
    // `Denied` after a denied request: the same, the request granted now.
    let mut rig = start(
        "UT-SESS-044-denied-on",
        ble,
        script(
            ble,
            vec![
                c9_once(ble, 0x01, ms(100), ms(0)),
                c9_ok(ble),
                reply(ble, 0xC2, ms(130), &output_on()),
            ],
        ),
    );
    rig.session.ready().await.unwrap();
    assert_eq!(
        rig.session.request_remote_control().await,
        Err(Error::RemoteControlDenied)
    );
    let t1 = rig.now();
    rig.drain();
    assert_eq!(rig.session.close(true).await, Ok(()));
    assert_eq!(shape(&rig.c8s_after(t1)), vec![(2, 1), (1, 0), (0, 0)]);
    assert!(prompted(&rig.drain_non_readings()));
}

/// Test: UT-SESS-044
#[tokio::test(start_paused = true)]
async fn a_close_fails_the_waiting_commands_and_output_offs() {
    let ble = Kind::Ble;
    let rig = granted(
        "UT-SESS-044-waiting",
        vec![
            c9_once(ble, 0x00, ms(100), ms(0)),
            reply(ble, 0xC8, ms(400), &[0x00]),
        ],
        vec![],
    )
    .await;
    let t1 = rig.now();
    let first_off = rig.call_at(t1, |s| async move { s.output_off().await });
    let second_off = rig.call_at(t1 + ms(10), |s| async move { s.output_off().await });
    let voltage = rig.call_at(t1 + ms(20), |s| async move { s.set_voltage(1.0).await });
    let close = rig.call_at(t1 + ms(30), |s| async move { s.close(false).await });
    for call in [first_off, second_off, voltage] {
        let (at, result) = call.await.unwrap();
        assert_eq!(result, Err(closed()));
        assert_eq!(at, t1 + ms(30));
    }
    assert_eq!(close.await.unwrap().1, Ok(()));
}

/// Test: UT-SESS-044
#[tokio::test(start_paused = true)]
async fn close_outside_dc_mode_skips_the_release() {
    let log = test_log::install();
    let ble = Kind::Ble;
    let pd = fixtures::c3_with(0, 2, 0, 1300, 1000);
    let rig = granted(
        "UT-SESS-044-pd",
        vec![
            reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            c3_from(ble, &pd, T0 + ms(500)),
        ],
        vec![],
    )
    .await;
    rig.until(T0 + ms(1_500)).await;
    let t1 = rig.now();
    assert_eq!(rig.session.close(true).await, Ok(()));
    assert!(rig.c8s_after(t1).is_empty());
    assert!(logged(
        &log,
        Level::Warn,
        "close: the supply is not in DC mode"
    ));
    assert_eq!(rig.mock(0).closes(), 1);
}

/// UT-SESS-050: as `output_off_meets_a_remote_request` in the control
/// tests, with `close(true)` in place of the output-off and readings that
/// show the output on.
async fn close_meets_a_remote_request(id: &str, written: bool) {
    let ble = Kind::Ble;
    let mut d = driven(
        id,
        ble,
        script(
            ble,
            vec![
                c9_once(ble, 0x00, ms(2_000), ms(0)),
                c9_ok(ble),
                reply(ble, 0xC2, ms(130), &output_on()),
            ],
        ),
    );
    d.until_ready().await;
    let mut voltage = d.command(CommandKind::SetVoltage(1.0));
    d.task.turn().await;
    assert_eq!(d.task.op_name(), Some("control"));
    if written {
        d.until_sent(|s| s.frame.opcode() == 0xC8).await;
    }
    let mut close = d.close(true);
    let (_, voltage_result) = d.drive(&mut voltage).await;
    assert_eq!(voltage_result, Err(closed()));
    let (_, close_result) = d.drive(&mut close).await;
    assert_eq!(close_result, Ok(()));
    let c8s = d.c8s();
    assert_eq!(shape(&c8s), vec![(2, 1), (1, 0), (0, 0)], "{c8s:?}");
    assert!(c8s[1].0 >= c8s[0].0 + ms(2_000));
    let events: Vec<SessionEvent> = std::iter::from_fn(|| d.events.try_next())
        .filter(|e| {
            matches!(
                e,
                SessionEvent::Prompt { .. } | SessionEvent::RemoteControl(_)
            )
        })
        .collect();
    assert_eq!(
        events,
        vec![
            SessionEvent::RemoteControl(RemoteState::Requested),
            SessionEvent::Prompt {
                kind: crate::session::PromptKind::AllowRemoteControl,
                bound_s: 70,
                text: crate::session::texts::ALLOW_REMOTE_CONTROL,
            },
            SessionEvent::RemoteControl(RemoteState::Granted),
        ]
    );
}

/// Test: UT-SESS-050
#[tokio::test(start_paused = true)]
async fn a_close_takes_over_a_remote_request_not_yet_written() {
    close_meets_a_remote_request("UT-SESS-050-close-queued", false).await;
}

/// Test: UT-SESS-050
#[tokio::test(start_paused = true)]
async fn a_close_takes_over_a_remote_request_just_written() {
    close_meets_a_remote_request("UT-SESS-050-close-written", true).await;
}

/// Test: UT-SESS-054
#[tokio::test(start_paused = true)]
async fn a_command_during_a_close_is_answered_at_once() {
    let ble = Kind::Ble;
    let rig = start(
        "UT-SESS-054",
        ble,
        script(ble, vec![c9_once(ble, 0x00, ms(2_000), ms(0)), c9_ok(ble)]),
    );
    rig.session.ready().await.unwrap();
    let voltage = rig.call_at(T0, |s| async move { s.set_voltage(1.0).await });
    let close = rig.call_at(T0 + ms(500), |s| async move { s.close(true).await });
    let current = rig.call_at(
        T0 + ms(600),
        |s| async move { s.set_current_limit(0.1).await },
    );
    let (at, result) = current.await.unwrap();
    assert_eq!(result, Err(closed()));
    assert_eq!(at, T0 + ms(600));
    let (closed_at, result) = close.await.unwrap();
    assert_eq!(result, Ok(()));
    assert!(closed_at > T0 + ms(2_000), "{closed_at:?}");
    assert_eq!(voltage.await.unwrap().1, Err(closed()));
}

/// Test: UT-SESS-044
#[tokio::test(start_paused = true)]
async fn a_close_clears_the_marker_once() {
    let ble = Kind::Ble;
    let off = fixtures::c3_with(0, 0, 0, 1300, 1000);
    // Output on until t0 + 1 s, off from then on; the close at t0 + 900 ms
    // switches the output off and its follow-up reading shows it off.
    let rig = granted(
        "UT-SESS-044-marker",
        vec![
            reply(ble, 0xC2, ms(130), &output_on()),
            c3_from(ble, &off, T0 + ms(1_000)),
        ],
        vec![],
    )
    .await;
    rig.until(T0 + ms(900)).await;
    assert!(rig
        .markers
        .calls()
        .iter()
        .any(|(_, c)| matches!(c, MarkerCall::Set(_))));
    let before = rig.markers.calls().len();
    let t1 = rig.now();
    assert_eq!(rig.session.close(true).await, Ok(()));
    assert_eq!(shape(&rig.c8s_after(t1)), vec![(1, 0), (0, 0)]);
    let calls = rig.markers.calls();
    let clears = calls[before..]
        .iter()
        .filter(|(_, c)| *c == MarkerCall::Clear)
        .count();
    assert_eq!(clears, 1, "{calls:?}");
}

/// Test: UT-SESS-044
#[tokio::test(start_paused = true)]
async fn close_reports_a_task_that_ended_without_closing() {
    let rig = start("UT-SESS-044-ended", Kind::Ble, script(Kind::Ble, vec![]));
    rig.session.ready().await.unwrap();
    let ended = Error::LinkLost {
        text: "the session task ended".to_string(),
    };
    // The close is on the priority channel when the task is aborted.
    let mut close = Box::pin(rig.session.close(true));
    assert!(futures::poll!(close.as_mut()).is_pending());
    rig.session.abort.abort();
    assert_eq!(close.await, Err(ended.clone()));
    // And a close after that finds no task.
    assert_eq!(rig.session.close(true).await, Err(ended));
}

/// Test: UT-SESS-057
#[tokio::test(start_paused = true)]
async fn a_close_after_a_cancelled_output_on_switches_off_whatever_the_reading_shows() {
    let ble = Kind::Ble;
    let on = fixtures::c3_with(1, 0, 0, 1300, 1000);
    // `applied`: the script reports `output` 1 from the output-on's `0xC9`
    // on (the entry); not applied: it keeps reporting 0, so only the
    // cancelled command makes the close switch off.
    for (id, applied) in [("UT-SESS-057", true), ("UT-SESS-057-not-applied", false)] {
        // The request at t0 is answered after 100 ms; the output-on (written
        // at t0 + 230 ms) after 300 ms; every later `0xC8` after 100 ms.
        let mut overrides = vec![
            c9_once(ble, 0x00, ms(100), ms(0)),
            c9_once(ble, 0x00, ms(300), ms(400)),
            c9_ok(ble),
            reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
        ];
        if applied {
            overrides.push(c3_from(ble, &on, T0 + ms(530)));
        }
        let rig = granted(id, overrides, vec![]).await;
        let r = rig.reading_after(T0 + ms(200)).await;
        assert_eq!(r, T0 + ms(230));
        let on_call = rig.call_at(r, |s| async move { s.output_on().await });
        let close = rig.call_at(r + ms(50), |s| async move { s.close(true).await });
        assert_eq!(on_call.await.unwrap().1, Err(closed()));
        assert_eq!(close.await.unwrap().1, Ok(()));
        let c8s = rig.c8s_after(r);
        // `reading_after` notices the reading within 1 ms.
        assert!(c8s[0].0 <= r + ms(1), "{c8s:?}");
        // The output-on, the close's output-off, the release with `output` 0.
        assert_eq!(shape(&c8s), vec![(1, 1), (1, 0), (0, 0)], "{id}");
    }
}

/// Test: UT-SESS-058
#[tokio::test(start_paused = true)]
async fn the_marker_stays_when_the_close_cannot_confirm_the_output_off() {
    let ble = Kind::Ble;
    let pd_on = fixtures::c3_with(1, 2, 0, 1300, 1000);
    // Granted at t0 + 100 ms, `output` 1 from the start: the marker is set
    // at t0 + 230 ms. The close comes at t0 + 1 s; its output-off `0xC8`
    // is the next `0xC8` from then on.
    let cases: Vec<(&str, bool, Vec<Reply>, Option<Duration>)> = vec![
        // (a) No `0xC9` to the output-off.
        (
            "UT-SESS-058-a",
            true,
            vec![c8_unanswered(T0 + ms(900))],
            None,
        ),
        // (b) `0xC9 00`.
        ("UT-SESS-058-b", true, vec![], None),
        // (c) `close(false)`.
        ("UT-SESS-058-c", false, vec![], None),
        // (d) The transport closes while the output-off waits for its
        // `0xC9` (answered after 400 ms).
        (
            "UT-SESS-058-d",
            true,
            vec![c9_once(ble, 0x00, ms(400), T0 + ms(900))],
            Some(T0 + ms(1_200)),
        ),
        // (e) PD mode with `output` 1 from t0 + 500 ms.
        (
            "UT-SESS-058-e",
            true,
            vec![c3_from(ble, &pd_on, T0 + ms(500))],
            None,
        ),
    ];
    for (id, output_off, extra, close_at) in cases {
        let log = test_log::install();
        let mut overrides = vec![
            c9_once(ble, 0x00, ms(100), ms(0)),
            c9_ok(ble),
            reply(ble, 0xC2, ms(130), &output_on()),
        ];
        overrides.extend(extra);
        let mut script = script(ble, overrides);
        script.close_at = close_at;
        let rig = start(id, ble, script);
        rig.session.ready().await.unwrap();
        rig.session.request_remote_control().await.unwrap();
        rig.until(T0 + ms(1_000)).await;
        assert!(marker_present(&rig, id), "{id}");
        let result = rig.session.close(output_off).await;
        let c8s = rig.c8s_after(T0 + ms(1_000));
        match id {
            "UT-SESS-058-a" => {
                assert_eq!(
                    result,
                    Err(Error::Timeout {
                        opcode: 0xC8,
                        after: ms(500)
                    })
                );
                // The release is still sent and the link closed.
                assert_eq!(shape(&c8s), vec![(1, 0), (0, 0)]);
                assert_eq!(rig.mock(0).closes(), 1);
                assert_eq!(rig.session.link_state(), LinkState::Closed);
                assert!(marker_present(&rig, id));
                assert!(logged(
                    &log,
                    Level::Warn,
                    "close: the output could not be confirmed off"
                ));
            }
            "UT-SESS-058-b" => {
                assert_eq!(result, Ok(()));
                assert!(!marker_present(&rig, id));
            }
            "UT-SESS-058-c" => {
                assert_eq!(result, Ok(()));
                assert_eq!(shape(&c8s), vec![(0, 1)]);
                assert!(!marker_present(&rig, id));
            }
            "UT-SESS-058-d" => {
                assert!(matches!(result, Err(Error::LinkLost { .. })), "{result:?}");
                assert_eq!(shape(&c8s), vec![(1, 0)]);
                assert!(marker_present(&rig, id));
            }
            _ => {
                assert_eq!(result, Ok(()));
                assert!(c8s.is_empty(), "{c8s:?}");
                assert!(logged(
                    &log,
                    Level::Warn,
                    "close: the supply is not in DC mode"
                ));
                assert!(marker_present(&rig, id));
            }
        }
    }
}

/// Test: UT-SESS-059
#[tokio::test(start_paused = true)]
async fn a_close_with_output_off_during_one_without_is_refused() {
    let ble = Kind::Ble;
    let rig = start(
        "UT-SESS-059",
        ble,
        script(ble, vec![c9_once(ble, 0x00, ms(2_000), ms(0)), c9_ok(ble)]),
    );
    rig.session.ready().await.unwrap();
    // A remote request pending for 2 s holds the close(false).
    let voltage = rig.call_at(T0, |s| async move { s.set_voltage(1.0).await });
    let first = rig.call_at(T0 + ms(500), |s| async move { s.close(false).await });
    let second = rig.call_at(T0 + ms(600), |s| async move { s.close(true).await });
    let third = rig.call_at(T0 + ms(700), |s| async move { s.close(false).await });
    let (at, result) = second.await.unwrap();
    assert_eq!(
        result,
        Err(Error::Cancelled {
            reason: "a close without output-off is already running".to_string()
        })
    );
    assert_eq!(at, T0 + ms(600));
    let (first_at, first_result) = first.await.unwrap();
    let (third_at, third_result) = third.await.unwrap();
    assert_eq!(first_result, Ok(()));
    assert_eq!(third_result, first_result);
    assert_eq!(third_at, first_at);
    assert!(first_at > T0 + ms(2_000));
    assert_eq!(voltage.await.unwrap().1, Err(closed()));
    // No output-off was sent: only the request and the release.
    assert_eq!(shape(&rig.c8s_after(T0)), vec![(2, 0), (0, 0)]);
    // A close after the end gets the first one's result too.
    assert_eq!(rig.session.close(true).await, Ok(()));
}

/// Test: UT-SESS-044
#[tokio::test(start_paused = true)]
async fn a_close_returns_the_first_error_and_still_disconnects() {
    let id = "UT-SESS-044-errors";
    let ble = Kind::Ble;
    // `close(true)` whose decision poll gets no reply: the output cannot be
    // confirmed off, so the `Timeout` is returned, no release is built from
    // a reading the close does not have, the link is closed and the
    // marker stays.
    let rig = granted(
        id,
        vec![
            reply(ble, 0xC2, ms(130), &output_on()),
            Reply {
                request: 0xC2,
                deliveries: Vec::new(),
                from: T0 + ms(800),
                ..Reply::default()
            },
        ],
        vec![],
    )
    .await;
    rig.until(T0 + ms(800)).await;
    assert!(marker_present(&rig, id));
    // The latest reading is fresh: wait until it is not.
    rig.until(T0 + ms(2_000)).await;
    let t1 = rig.now();
    assert_eq!(
        rig.session.close(true).await,
        Err(Error::Timeout {
            opcode: 0xC2,
            after: Duration::from_secs(1)
        })
    );
    assert!(rig.c8s_after(t1).is_empty());
    assert_eq!(rig.session.link_state(), LinkState::Closed);
    assert!(marker_present(&rig, id));
    // `close(false)` whose release gets no `0xC9`: the `Timeout` is the
    // close's result, the link is still closed, the marker cleared (the
    // user chose to leave the output as it is).
    let id = "UT-SESS-044-release";
    let rig = granted(
        id,
        vec![
            c9_once(ble, 0x00, ms(100), ms(0)),
            c8_unanswered(ms(300)),
            reply(ble, 0xC2, ms(130), &output_on()),
        ],
        vec![],
    )
    .await;
    rig.until(T0 + ms(800)).await;
    assert!(marker_present(&rig, id));
    assert_eq!(
        rig.session.close(false).await,
        Err(Error::Timeout {
            opcode: 0xC8,
            after: Duration::from_secs(1)
        })
    );
    assert_eq!(rig.mock(0).closes(), 1);
    assert!(!marker_present(&rig, id));
}
