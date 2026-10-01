//! Implements: nothing; holds the tests of UT-SESS-010 to UT-SESS-014,
//! UT-SESS-048 (before `Ready`) and UT-SESS-052.
//!
//! Task tests: the connect flow, the bind, USB, and the marker check.

use super::*;
use crate::protocol::ops::info::Version;
use crate::session::{texts, LinkState, PromptKind};

/// Test: UT-SESS-010
#[tokio::test(start_paused = true)]
async fn connect_binds_reads_info_and_a_reading_then_is_ready() {
    let mut rig = start("UT-SESS-010", Kind::Ble, script(Kind::Ble, vec![]));
    let info = rig.session.ready().await.unwrap();
    assert_eq!(rig.now(), T0);
    assert_eq!(info.model, "MP305B");
    assert_eq!(info.version, Version([1, 6, 0, 40]));
    let sent = rig.mock(0).sent();
    assert_eq!(sent.len(), 3, "{sent:?}");
    let mut bind = host_id().as_bytes().to_vec();
    bind.extend_from_slice(&[0x00, 0x01]);
    assert_eq!(sent[0].frame.opcode(), 0x18);
    assert_eq!(sent[0].route, Route::Ble(BleRoute::Af02));
    assert_eq!(sent[0].frame.payload(), bind.as_slice());
    assert_eq!(sent[1].frame.opcode(), 0xE0);
    assert_eq!(sent[2].frame.opcode(), 0xC2);
    let events = rig.drain();
    assert_eq!(events.len(), 2, "{events:?}");
    assert_eq!(events[0], SessionEvent::BindResult { recognised: true });
    assert!(matches!(events[1], SessionEvent::Reading(_)));
    assert_eq!(rig.session.link_state(), LinkState::Ready);
    assert_eq!(rig.session.transport(), Some(Kind::Ble));
    assert_eq!(rig.session.info(), Some(info.clone()));
    assert_eq!(rig.session.identifier(), "UT-SESS-010");
    rig.until(T0 + ms(150)).await;
    let c2: Vec<Duration> = rig
        .sent()
        .into_iter()
        .filter(|(_, op, _)| *op == 0xC2)
        .map(|(t, _, _)| t)
        .collect();
    assert_eq!(c2[1], T0 + ms(100));
    assert_eq!(rig.session.ready().await.unwrap(), info);
    assert!(rig.session.counters().is_some());
}

/// Test: UT-SESS-010
#[test]
fn connect_outside_a_runtime_fails_and_registers_nothing() {
    let connector = Arc::new(MockConnector::new(|| {
        Err(Error::Transport {
            message: "unused".to_string(),
        })
    }));
    let markers = Arc::new(MemoryMarkers::new());
    let outside = Session::connect(
        Arc::clone(&connector) as Arc<dyn crate::session::Connector>,
        "UT-SESS-010-outside",
        host_id(),
        Arc::clone(&markers) as Arc<dyn crate::session::Markers>,
        options(),
    );
    assert!(matches!(outside, Err(Error::Transport { .. })));
    let runtime = tokio::runtime::Builder::new_current_thread()
        .enable_all()
        .start_paused(true)
        .build()
        .unwrap();
    runtime.block_on(async {
        let inside = Session::connect(
            connector,
            "UT-SESS-010-outside",
            host_id(),
            markers,
            options(),
        );
        assert!(inside.is_ok());
    });
}

/// Test: UT-SESS-011
#[tokio::test(start_paused = true)]
async fn an_unrecognised_host_gets_the_prompt_bind() {
    let ble = Kind::Ble;
    let mut rig = start(
        "UT-SESS-011",
        ble,
        script(
            ble,
            vec![
                Reply {
                    repeat: Some(1),
                    ..reply(ble, 0x18, ms(50), &[0xFF])
                },
                reply(ble, 0x18, ms(3_000), &[0x00]),
            ],
        ),
    );
    let events = rig.record();
    rig.until(ms(1_000)).await;
    assert_eq!(rig.session.set_voltage(1.0).await, Err(Error::NotReady));
    let info = rig.session.ready().await.unwrap();
    assert_eq!(info.model, "MP305B");
    assert_eq!(rig.now(), ms(3_050 + 100 + 130));
    let non_readings = events.non_readings();
    assert_eq!(
        non_readings[0],
        (
            ms(50),
            SessionEvent::Prompt {
                kind: PromptKind::ConfirmConnection,
                bound_s: 30,
                text: texts::CONFIRM_CONNECTION,
            }
        )
    );
    assert_eq!(
        non_readings[1],
        (ms(3_050), SessionEvent::BindResult { recognised: false })
    );
    assert_eq!(events.reading_times(), vec![ms(3_280)]);
    let sent = rig.sent();
    let ops: Vec<u8> = sent.iter().map(|(_, op, _)| *op).collect();
    assert_eq!(ops, vec![0x18, 0x18, 0xE0, 0xC2]);
    assert_eq!(sent[1].2[17], 0x00);
    assert_eq!(sent[2].0, ms(3_050));
    assert_eq!(rig.session.link_state(), LinkState::Ready);
}

/// Runs the connect flow of UT-SESS-012 on `script` and returns the rig
/// once `ready()` answered, with the answer and its time.
async fn denied(id: &str, script: Script) -> (Rig, Result<(), Error>, Duration) {
    let rig = start(id, Kind::Ble, script);
    let result = rig.session.ready().await.map(|_| ());
    let at = rig.now();
    tokio::time::sleep(ms(1)).await;
    (rig, result, at)
}

/// Test: UT-SESS-012
#[tokio::test(start_paused = true)]
async fn a_denied_bind_closes_the_link() {
    let ble = Kind::Ble;
    // A: 19 FF for both bind requests.
    let (rig, result, _) = denied(
        "UT-SESS-012-A",
        script(ble, vec![reply(ble, 0x18, ms(50), &[0xFF])]),
    )
    .await;
    assert_eq!(result, Err(Error::ConnectionDenied));
    assert_eq!(rig.session.link_state(), LinkState::Denied);
    assert_eq!(rig.mock(0).closes(), 1);
    assert_eq!(rig.opcodes(), vec![0x18, 0x18]);
    assert_eq!(
        rig.session.set_voltage(1.0).await,
        Err(Error::ConnectionDenied)
    );
    // E: 19 07 to the fast bind.
    let (rig, result, _) = denied(
        "UT-SESS-012-E",
        script(ble, vec![reply(ble, 0x18, ms(50), &[0x07])]),
    )
    .await;
    assert_eq!(result, Err(Error::ConnectionDenied));
    assert_eq!(rig.session.link_state(), LinkState::Denied);
    assert_eq!(rig.mock(0).closes(), 1);
    assert_eq!(rig.opcodes(), vec![0x18]);
}

/// Test: UT-SESS-012
#[tokio::test(start_paused = true)]
async fn a_bind_without_an_answer_times_out() {
    let ble = Kind::Ble;
    // B: 19 FF, then no second reply.
    let (rig, result, at) = denied(
        "UT-SESS-012-B",
        script(
            ble,
            vec![Reply {
                repeat: Some(1),
                ..reply(ble, 0x18, ms(50), &[0xFF])
            }],
        ),
    )
    .await;
    assert_eq!(
        result,
        Err(Error::Timeout {
            opcode: 0x18,
            after: Duration::from_secs(30)
        })
    );
    assert_eq!(at, Duration::from_secs(30));
    assert_eq!(rig.mock(0).closes(), 1);
    // C: no reply to the fast bind at all.
    let mut quiet = script(ble, vec![]);
    quiet.replies.retain(|r| r.request != 0x18);
    let (rig, result, at) = denied("UT-SESS-012-C", quiet).await;
    assert_eq!(
        result,
        Err(Error::Timeout {
            opcode: 0x18,
            after: Duration::from_secs(1)
        })
    );
    assert_eq!(at, Duration::from_secs(1));
    assert_eq!(rig.mock(0).closes(), 1);
    assert_eq!(rig.opcodes(), vec![0x18]);
}

/// Test: UT-SESS-012
#[tokio::test(start_paused = true)]
async fn a_loss_during_the_bind_wait_is_a_lost_link() {
    let ble = Kind::Ble;
    // D: 19 FF, then the link closes at 10 s.
    let mut script = script(
        ble,
        vec![Reply {
            repeat: Some(1),
            ..reply(ble, 0x18, ms(50), &[0xFF])
        }],
    );
    script.close_at = Some(Duration::from_secs(10));
    let (mut rig, result, at) = denied("UT-SESS-012-D", script).await;
    let text = texts::lost_while_connecting(&crate::link::LossReason::Disconnected);
    assert_eq!(result, Err(Error::LinkLost { text: text.clone() }));
    assert_eq!(at, Duration::from_secs(10));
    assert_eq!(rig.session.link_state(), LinkState::Lost);
    let events = rig.drain_non_readings();
    assert!(
        events.contains(&SessionEvent::LinkLost { text }),
        "{events:?}"
    );
}

/// Test: UT-SESS-013
#[tokio::test(start_paused = true)]
async fn usb_needs_no_bind() {
    let hid = Kind::Hid;
    let rig = start("UT-SESS-013", hid, script(hid, vec![]));
    let info = rig.session.ready().await.unwrap();
    assert_eq!(info.version, Version([1, 6, 0, 51]));
    assert_eq!(info.bootloader_raw, Some([1, 2, 3, 4, 5, 6, 7, 8]));
    assert_eq!(info.name.as_deref(), Some("MP305B"));
    let sent = rig.mock(0).sent();
    let ops: Vec<(u8, Route)> = sent.iter().map(|s| (s.frame.opcode(), s.route)).collect();
    assert_eq!(ops, vec![(0xE0, Route::Hid), (0xC2, Route::Hid)]);
    assert_eq!(rig.session.link_state(), LinkState::Ready);
    assert_eq!(rig.session.transport(), Some(Kind::Hid));
}

/// Test: UT-SESS-014
#[tokio::test(start_paused = true)]
async fn a_marker_found_at_connect_is_reported_then_cleared() {
    use crate::session::doubles::MarkerCall;
    let id = "UT-SESS-014";
    let since = UNIX_EPOCH + Duration::from_secs(1_790_845_200);
    let connector =
        MockConnector::new(move || Ok(Mock::new(Kind::Ble, id, script(Kind::Ble, vec![]))));
    let mut rig = start_with(id, connector, MemoryMarkers::holding(id, since), options());
    let events = rig.record();
    rig.session.ready().await.unwrap();
    assert_eq!(rig.now(), T0);
    tokio::time::sleep(ms(1)).await;
    let warning = SessionEvent::UncleanExitWarning {
        since,
        text: texts::unclean_exit(since),
    };
    // The first reading arrives at t0; the warning is delivered at t0 too,
    // so after the first reading (the marker check follows the info and the
    // first reading) and before `ready()` returned to the caller.
    let at_warning = events
        .all()
        .into_iter()
        .find(|(_, e)| *e == warning)
        .map(|(t, _)| t);
    assert_eq!(at_warning, Some(T0));
    assert_eq!(events.reading_times().first(), Some(&T0));
    let first = events.all().into_iter().find_map(|(_, e)| match e {
        SessionEvent::Reading(r) => Some(r.at - rig.start),
        _ => None,
    });
    assert_eq!(first, Some(T0));
    // The first reading shows the output off: the marker is cleared at
    // once, and only once.
    assert_eq!(
        rig.markers.calls(),
        vec![
            (id.to_string(), MarkerCall::Present),
            (id.to_string(), MarkerCall::Clear),
        ]
    );
    rig.until(T0 + ms(1_000)).await;
    assert_eq!(rig.markers.calls().len(), 2);
}

/// Test: UT-SESS-010
#[tokio::test(start_paused = true)]
async fn a_failed_connect_flow_leaves_lost_with_the_error_text() {
    let ble = Kind::Ble;
    // The connector's error.
    let id = "UT-SESS-010-connector";
    let connector = MockConnector::new(|| {
        Err(Error::Transport {
            message: "no adapter".to_string(),
        })
    });
    let mut rig = start_with(id, connector, MemoryMarkers::new(), options());
    let failed = Error::Transport {
        message: "no adapter".to_string(),
    };
    assert_eq!(rig.session.ready().await, Err(failed.clone()));
    assert_eq!(rig.session.link_state(), LinkState::Lost);
    assert_eq!(rig.session.transport(), None);
    assert_eq!(
        rig.session.set_voltage(1.0).await,
        Err(Error::LinkLost {
            text: failed.to_string()
        })
    );
    assert!(!rig
        .drain()
        .iter()
        .any(|e| matches!(e, SessionEvent::LinkLost { .. })));
    // An `0xE1` that does not parse: `Protocol`, the link closed.
    let mut short = script(ble, vec![reply(ble, 0xE0, ms(100), &[0x01, 0x06, 0x00])]);
    short.replies.retain(|r| r.request != 0xC2);
    let mut rig = start("UT-SESS-010-short-e1", ble, short);
    let result = rig.session.ready().await;
    assert!(matches!(result, Err(Error::Protocol(_))), "{result:?}");
    tokio::time::sleep(ms(1)).await;
    assert_eq!(rig.session.link_state(), LinkState::Lost);
    assert_eq!(rig.mock(0).closes(), 1);
    assert_eq!(rig.opcodes(), vec![0x18, 0xE0]);
    assert_eq!(
        rig.session.set_voltage(1.0).await,
        Err(Error::LinkLost {
            text: result.unwrap_err().to_string()
        })
    );
    assert!(!rig
        .drain()
        .iter()
        .any(|e| matches!(e, SessionEvent::LinkLost { .. })));
    // No `0xE1`: the info request times out after 1 s.
    let mut quiet = script(ble, vec![]);
    quiet.replies.retain(|r| r.request != 0xE0);
    let rig = start("UT-SESS-010-no-e1", ble, quiet);
    let timeout = Error::Timeout {
        opcode: 0xE0,
        after: Duration::from_secs(1),
    };
    assert_eq!(rig.session.ready().await, Err(timeout.clone()));
    assert_eq!(rig.now(), ms(50) + Duration::from_secs(1));
    tokio::time::sleep(ms(1)).await;
    assert_eq!(rig.session.link_state(), LinkState::Lost);
    assert_eq!(rig.mock(0).closes(), 1);
    assert_eq!(
        rig.session.output_on().await,
        Err(Error::LinkLost {
            text: timeout.to_string()
        })
    );
    // No `0xC3`: the first reading times out after 1 s.
    let mut quiet = script(ble, vec![]);
    quiet.replies.retain(|r| r.request != 0xC2);
    let rig = start("UT-SESS-010-no-c3", ble, quiet);
    assert_eq!(
        rig.session.ready().await,
        Err(Error::Timeout {
            opcode: 0xC2,
            after: Duration::from_secs(1),
        })
    );
    tokio::time::sleep(ms(1)).await;
    assert_eq!(rig.session.link_state(), LinkState::Lost);
    assert_eq!(rig.mock(0).closes(), 1);
}

/// Test: UT-SESS-012
#[tokio::test(start_paused = true)]
async fn a_prompt_bind_answered_other_than_19_00_is_a_deny() {
    let ble = Kind::Ble;
    // `19 07`, and a `0x19` of two status bytes, to the prompt bind.
    for (id, answer) in [
        ("UT-SESS-012-prompt-07", vec![0x07]),
        ("UT-SESS-012-prompt-long", vec![0x00, 0x00]),
    ] {
        let (rig, result, _) = denied(
            id,
            script(
                ble,
                vec![
                    Reply {
                        repeat: Some(1),
                        ..reply(ble, 0x18, ms(50), &[0xFF])
                    },
                    reply(ble, 0x18, ms(1_000), &answer),
                ],
            ),
        )
        .await;
        assert_eq!(result, Err(Error::ConnectionDenied), "{id}");
        assert_eq!(rig.session.link_state(), LinkState::Denied);
        assert_eq!(rig.mock(0).closes(), 1);
        assert_eq!(rig.opcodes(), vec![0x18, 0x18]);
    }
}

/// Test: UT-SESS-048
#[tokio::test(start_paused = true)]
async fn an_output_off_during_the_bind_wait_leaves_the_connect_flow_running() {
    let ble = Kind::Ble;
    let rig = start(
        "UT-SESS-048-bind",
        ble,
        script(
            ble,
            vec![
                Reply {
                    repeat: Some(1),
                    ..reply(ble, 0x18, ms(50), &[0xFF])
                },
                reply(ble, 0x18, ms(3_000), &[0x00]),
            ],
        ),
    );
    let (at, result) = rig
        .call_at(ms(1_000), |s| async move { s.output_off().await })
        .await
        .unwrap();
    assert_eq!(result, Err(Error::NotReady));
    assert_eq!(at, ms(1_000));
    let ready = tokio::time::timeout(Duration::from_secs(60), rig.session.ready()).await;
    let info = ready
        .expect("ready() must resolve when the 19 00 arrives")
        .unwrap();
    assert_eq!(info.model, "MP305B");
    assert_eq!(rig.now(), ms(3_050 + 100 + 130));
    assert_eq!(rig.session.link_state(), LinkState::Ready);
    assert_eq!(rig.opcodes(), vec![0x18, 0x18, 0xE0, 0xC2]);
}

/// Test: UT-SESS-048
#[tokio::test(start_paused = true)]
async fn an_output_off_while_usb_connects_leaves_the_connect_flow_running() {
    let hid = Kind::Hid;
    let rig = start("UT-SESS-048-usb", hid, script(hid, vec![]));
    let (at, result) = rig
        .call_at(ms(50), |s| async move { s.output_off().await })
        .await
        .unwrap();
    assert_eq!(result, Err(Error::NotReady));
    assert_eq!(at, ms(50));
    let ready = tokio::time::timeout(Duration::from_secs(60), rig.session.ready()).await;
    let info = ready
        .expect("ready() must resolve after the first reading")
        .unwrap();
    assert_eq!(info.version, Version([1, 6, 0, 51]));
    assert_eq!(rig.now(), ms(100 + 130));
    assert_eq!(rig.session.link_state(), LinkState::Ready);
}

/// Test: UT-SESS-052
#[tokio::test(start_paused = true)]
async fn a_loss_seen_first_as_the_step_error_is_handled_once() {
    let ble = Kind::Ble;
    let mut script = script(
        ble,
        vec![Reply {
            repeat: Some(1),
            ..reply(ble, 0x18, ms(50), &[0xFF])
        }],
    );
    script.close_at = Some(Duration::from_secs(10));
    let mut d = driven("UT-SESS-052", ble, script);
    // Up to the bind wait: the prompt bind is written and awaited.
    let mut seen = Vec::new();
    while !seen
        .iter()
        .any(|e| matches!(e, SessionEvent::Prompt { .. }))
    {
        d.task.turn().await;
        seen.extend(std::iter::from_fn(|| d.events.try_next()));
    }
    assert_eq!(d.link_state(), LinkState::Binding);
    // The link ends at 10 s: it fails the bind wait with `LinkLost` and
    // then delivers its `LinkLost` event; the task sees the step first.
    sleep_until(d.start + Duration::from_secs(10) + ms(1)).await;
    d.task.step_first().await;
    for _ in 0..10 {
        if d.ready_state() != ReadyState::Pending {
            break;
        }
        tokio::select! {
            biased;
            () = d.task.turn() => {}
            () = tokio::time::sleep(Duration::from_secs(5)) => break,
        }
    }
    let text = texts::lost_while_connecting(&crate::link::LossReason::Disconnected);
    assert_eq!(
        d.ready_state(),
        ReadyState::Failed(Error::LinkLost { text: text.clone() })
    );
    assert_eq!(d.link_state(), LinkState::Lost);
    seen.extend(std::iter::from_fn(|| d.events.try_next()));
    let losses: Vec<&SessionEvent> = seen
        .iter()
        .filter(|e| matches!(e, SessionEvent::LinkLost { .. }))
        .collect();
    assert_eq!(losses, vec![&SessionEvent::LinkLost { text }]);
}
