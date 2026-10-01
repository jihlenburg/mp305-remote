//! Implements: nothing; holds the tests of UT-SESS-040 to UT-SESS-043 and
//! UT-SESS-048 (during a reconnection).
//!
//! Task tests: link loss, reconnection and the registry.

use super::*;
use crate::link::LossReason;
use crate::session::{texts, LinkState, Markers, RemoteState};

/// A connector whose attempts come from `attempts` in order (the last one
/// repeating), recording the time of every call.
fn scripted_connector(
    attempts: Vec<Box<dyn Fn() -> Result<Mock, Error> + Send>>,
) -> (MockConnector, Arc<std::sync::Mutex<Vec<Instant>>>) {
    let calls: Arc<std::sync::Mutex<Vec<Instant>>> = Arc::default();
    let log = Arc::clone(&calls);
    let mut n = 0;
    let connector = MockConnector::new(move || {
        log.lock().unwrap().push(Instant::now());
        let attempt = &attempts[n.min(attempts.len() - 1)];
        n += 1;
        attempt()
    });
    (connector, calls)
}

/// An attempt that fails with a transport error.
fn no_adapter() -> Box<dyn Fn() -> Result<Mock, Error> + Send> {
    Box::new(|| {
        Err(Error::Transport {
            message: "no adapter".to_string(),
        })
    })
}

/// An attempt that yields a Bluetooth mock following `script`.
fn mock_attempt(id: &'static str, script: Script) -> Box<dyn Fn() -> Result<Mock, Error> + Send> {
    Box::new(move || Ok(Mock::new(Kind::Ble, id, script.clone())))
}

/// The options with reconnection on.
fn reconnecting() -> Options {
    Options {
        reconnect: true,
        ..options()
    }
}

/// Test: UT-SESS-040
#[tokio::test(start_paused = true)]
async fn a_loss_fails_everything_once_and_keeps_the_events_open() {
    let ble = Kind::Ble;
    let mut script = script(
        ble,
        vec![c9_once(ble, 0x00, ms(100), ms(0)), c8_unanswered(ms(0))],
    );
    script.close_at = Some(T0 + ms(500));
    let mut rig = granted_with_script("UT-SESS-040", script).await;
    let events = rig.record();
    let in_progress = rig.call_at(rig.now(), |s| async move { s.set_voltage(1.0).await });
    let queued = rig.call_at(
        T0 + ms(490),
        |s| async move { s.set_current_limit(0.1).await },
    );
    let (_, voltage) = in_progress.await.unwrap();
    let (_, current) = queued.await.unwrap();
    let text = texts::link_lost(&LossReason::Disconnected, Kind::Ble);
    assert_eq!(
        text,
        "The transport reported the link closed. The output is still in its last state \
         and the supply has released remote control. A USB host talking to the supply is \
         one possible cause."
    );
    assert_eq!(
        voltage,
        Err(Error::LinkLost {
            text: "the transport reported the link closed".to_string()
        })
    );
    let session_error = Error::LinkLost { text: text.clone() };
    assert_eq!(current, Err(session_error.clone()));
    let sent = rig.sent().len();
    assert_eq!(rig.session.output_on().await, Err(session_error.clone()));
    rig.until(T0 + ms(3_000)).await;
    assert_eq!(rig.sent().len(), sent);
    assert_eq!(rig.session.link_state(), LinkState::Lost);
    assert_eq!(rig.session.ready().await, Err(session_error.clone()));
    let non_readings: Vec<SessionEvent> =
        events.non_readings().into_iter().map(|(_, e)| e).collect();
    assert_eq!(
        non_readings,
        vec![
            SessionEvent::RemoteControl(RemoteState::Lost),
            SessionEvent::LinkLost { text },
        ]
    );
    // The events stay open until the close.
    assert!(!events.ended());
    // A `close(true)` after a loss in `Ready` could not switch the output
    // off: it reports the loss (DD-SESS-053, revision 5).
    assert_eq!(rig.session.close(true).await, Err(session_error));
    sleep_until(rig.start + T0 + ms(3_100)).await;
    assert!(events.ended());
}

/// A ready and granted session over one mock following `script`.
async fn granted_with_script(id: &str, script: Script) -> Rig {
    let mut rig = start(id, Kind::Ble, script);
    rig.session.ready().await.unwrap();
    rig.session.request_remote_control().await.unwrap();
    rig.drain();
    rig
}

/// Test: UT-SESS-040
#[tokio::test(start_paused = true)]
async fn a_silent_supply_is_reported_within_4_s() {
    let ble = Kind::Ble;
    let mut script = script(ble, vec![]);
    script.stop_replying_at = Some(T0 + ms(1_000));
    let mut rig = start("UT-SESS-040-B", ble, script);
    rig.session.ready().await.unwrap();
    let events = rig.record();
    rig.until(T0 + ms(6_000)).await;
    let last_reading = *events.reading_times().last().unwrap();
    let (lost_at, text) = events
        .all()
        .into_iter()
        .find_map(|(t, e)| match e {
            SessionEvent::LinkLost { text } => Some((t, text)),
            _ => None,
        })
        .unwrap();
    assert!(
        text.starts_with("Three requests in a row went unanswered."),
        "{text}"
    );
    assert!(lost_at - last_reading <= Duration::from_secs(4));
}

/// Test: UT-SESS-041
#[tokio::test(start_paused = true)]
async fn reconnection_retries_every_5_s_and_starts_afresh() {
    let id = "UT-SESS-041";
    let ble = Kind::Ble;
    let mut first = script(ble, vec![reply(ble, 0xC8, ms(300), &[0x00])]);
    first.close_at = Some(T0 + ms(1_000));
    let (connector, calls) = scripted_connector(vec![
        mock_attempt(id, first),
        no_adapter(),
        no_adapter(),
        mock_attempt(id, script(ble, vec![])),
    ]);
    let mut rig = start_with(id, connector, MemoryMarkers::new(), reconnecting());
    rig.session.ready().await.unwrap();
    rig.drain();
    let events = rig.record();
    let queued = rig.call_at(T0 + ms(900), |s| async move { s.set_voltage(1.0).await });
    assert!(matches!(
        queued.await.unwrap().1,
        Err(Error::LinkLost { .. })
    ));
    let lost = Error::LinkLost {
        text: texts::link_lost(&LossReason::Disconnected, Kind::Ble),
    };
    let lost_at = events
        .all()
        .into_iter()
        .find(|(_, e)| matches!(e, SessionEvent::LinkLost { .. }))
        .unwrap()
        .0;
    assert_eq!(lost_at, T0 + ms(1_000));
    rig.until(T0 + ms(8_000)).await;
    assert_eq!(rig.session.link_state(), LinkState::Reconnecting);
    let pending = tokio::time::timeout(ms(1), rig.session.ready()).await;
    assert!(pending.is_err(), "ready() must wait while reconnecting");
    // A control call during `Reconnecting` gets `LinkLost` at once.
    assert_eq!(rig.session.set_voltage(1.0).await, Err(lost.clone()));
    assert_eq!(rig.session.output_off().await, Err(lost));
    // Answered at once (the 1 ms is the `ready()` probe above).
    assert_eq!(rig.now(), T0 + ms(8_001));
    let info = rig.session.ready().await.unwrap();
    assert_eq!(info.model, "MP305B");
    let times: Vec<Duration> = calls
        .lock()
        .unwrap()
        .iter()
        .map(|t| *t - rig.start)
        .collect();
    assert_eq!(
        times,
        vec![ms(0), T0 + ms(6_000), T0 + ms(11_000), T0 + ms(16_000)]
    );
    let reconnected_at = events
        .all()
        .into_iter()
        .find(|(_, e)| *e == SessionEvent::Reconnected)
        .unwrap()
        .0;
    assert_eq!(reconnected_at, T0 + ms(16_000) + T0);
    let fourth = rig.sent_of(1);
    let ops: Vec<u8> = fourth.iter().map(|(_, op, _)| *op).collect();
    assert_eq!(ops, vec![0x18, 0xE0, 0xC2]);
    assert_eq!(fourth[0].2[17], 0x01);
    assert_eq!(rig.session.link_state(), LinkState::Ready);
    assert_eq!(rig.session.remote_state(), RemoteState::None);
    assert!(!events
        .all()
        .iter()
        .any(|(_, e)| matches!(e, SessionEvent::UncleanExitWarning { .. })));
    // Nothing issued before the loss reached the fourth mock.
    assert!(!rig.sent_of(1).iter().any(|(_, op, _)| *op == 0xC8));
    // No marker check on a reconnection: one `Present`, at the first
    // connection.
    assert_eq!(
        rig.markers.calls(),
        vec![(id.to_string(), crate::session::doubles::MarkerCall::Present)]
    );
    rig.until(reconnected_at + ms(1_000)).await;
    assert!(
        rig.sent_of(1)
            .iter()
            .filter(|(_, op, _)| *op == 0xC2)
            .count()
            >= 4
    );
    let log = crate::transport::test_log::install();
    let polls = count_logged(&log, "poll first");
    assert_eq!(rig.session.set_voltage(1.0).await, Ok(()));
    // A new remote request, then, after its `0xC9`, a poll of its own
    // before the `0xC8` with the voltage.
    assert_eq!(count_logged(&log, "poll first"), polls + 1);
    let c8s: Vec<Vec<u8>> = rig
        .sent_of(1)
        .into_iter()
        .filter(|(_, op, _)| *op == 0xC8)
        .map(|(_, _, p)| p)
        .collect();
    assert_eq!(c8s.len(), 2);
    assert_eq!(remote_con(&c8s[0]), 2);
    assert_eq!(remote_con(&c8s[1]), 1);
}

/// Test: UT-SESS-042
#[tokio::test(start_paused = true)]
async fn an_unrecognised_host_ends_the_reconnection() {
    let id = "UT-SESS-042-A";
    let ble = Kind::Ble;
    let mut first = script(ble, vec![]);
    first.close_at = Some(Duration::from_secs(1));
    let (connector, _) = scripted_connector(vec![
        mock_attempt(id, first),
        mock_attempt(id, script(ble, vec![reply(ble, 0x18, ms(50), &[0xFF])])),
    ]);
    let mut rig = start_with(id, connector, MemoryMarkers::new(), reconnecting());
    rig.session.ready().await.unwrap();
    rig.drain();
    let events = rig.record();
    rig.until(Duration::from_secs(10)).await;
    let gave_up = events
        .all()
        .into_iter()
        .find_map(|(t, e)| match e {
            SessionEvent::ReconnectGaveUp { text } => Some((t, text)),
            _ => None,
        })
        .unwrap();
    assert_eq!(gave_up.0, Duration::from_secs(6) + ms(50));
    assert_eq!(gave_up.1, texts::GAVE_UP_UNRECOGNISED);
    assert_eq!(rig.sent_of(1).len(), 1);
    assert_eq!(rig.mock(1).closes(), 1);
    assert_eq!(rig.session.link_state(), LinkState::Lost);
    assert!(matches!(
        rig.session.ready().await,
        Err(Error::LinkLost { .. })
    ));
}

/// Test: UT-SESS-042
#[tokio::test(start_paused = true)]
async fn the_reconnection_gives_up_after_10_minutes() {
    let id = "UT-SESS-042-B";
    let mut first = script(Kind::Ble, vec![]);
    first.close_at = Some(Duration::from_secs(1));
    let (connector, calls) = scripted_connector(vec![mock_attempt(id, first), no_adapter()]);
    let mut rig = start_with(id, connector, MemoryMarkers::new(), reconnecting());
    rig.session.ready().await.unwrap();
    rig.drain();
    let events = rig.record();
    rig.until(Duration::from_secs(700)).await;
    let loss = Duration::from_secs(1);
    let attempts: Vec<Duration> = calls
        .lock()
        .unwrap()
        .iter()
        .skip(1)
        .map(|t| *t - rig.start - loss)
        .collect();
    assert_eq!(attempts.len(), 119);
    assert_eq!(attempts.first(), Some(&Duration::from_secs(5)));
    assert_eq!(attempts.last(), Some(&Duration::from_secs(595)));
    let gave_up: Vec<(Duration, SessionEvent)> = events
        .non_readings()
        .into_iter()
        .filter(|(_, e)| matches!(e, SessionEvent::ReconnectGaveUp { .. }))
        .collect();
    assert_eq!(
        gave_up,
        vec![(
            loss + Duration::from_secs(600),
            SessionEvent::ReconnectGaveUp {
                text: texts::GAVE_UP_TIMEOUT.to_string()
            }
        )]
    );
    assert_eq!(rig.session.link_state(), LinkState::Lost);
}

/// Test: UT-SESS-042
#[tokio::test(start_paused = true)]
async fn switching_reconnection_off_gives_up_at_the_next_tick() {
    let id = "UT-SESS-042-C";
    let mut first = script(Kind::Ble, vec![]);
    first.close_at = Some(Duration::from_secs(1));
    let (connector, calls) = scripted_connector(vec![mock_attempt(id, first), no_adapter()]);
    let mut rig = start_with(id, connector, MemoryMarkers::new(), reconnecting());
    rig.session.ready().await.unwrap();
    rig.drain();
    let events = rig.record();
    rig.until(Duration::from_secs(9)).await;
    rig.session.set_reconnect(false);
    rig.until(Duration::from_secs(20)).await;
    let attempts: Vec<Duration> = calls
        .lock()
        .unwrap()
        .iter()
        .skip(1)
        .map(|t| *t - rig.start)
        .collect();
    assert_eq!(attempts, vec![Duration::from_secs(6)]);
    let gave_up: Vec<(Duration, SessionEvent)> = events
        .non_readings()
        .into_iter()
        .filter(|(_, e)| matches!(e, SessionEvent::ReconnectGaveUp { .. }))
        .collect();
    assert_eq!(
        gave_up,
        vec![(
            Duration::from_secs(11),
            SessionEvent::ReconnectGaveUp {
                text: texts::GAVE_UP_SWITCHED_OFF.to_string()
            }
        )]
    );
}

/// Test: UT-SESS-043
#[tokio::test(start_paused = true)]
async fn one_session_per_identifier() {
    let id = "UT-SESS-043";
    let rig = start(id, Kind::Ble, script(Kind::Ble, vec![]));
    let second_connector = Arc::new(MockConnector::new(|| {
        Ok(Mock::new(Kind::Ble, "unused", Script::default()))
    }));
    let other = Arc::clone(&second_connector);
    let second = tokio::spawn(async move {
        Session::connect(
            other,
            "UT-SESS-043",
            host_id(),
            Arc::new(MemoryMarkers::new()),
            options(),
        )
        .map(|_| ())
    })
    .await
    .unwrap();
    assert_eq!(
        second,
        Err(Error::AlreadyOpen {
            identifier: id.to_string()
        })
    );
    assert!(second_connector.handles().is_empty());
    rig.session.ready().await.unwrap();
    assert_eq!(rig.session.close(true).await, Ok(()));
    let again = start(id, Kind::Ble, script(Kind::Ble, vec![]));
    again.session.ready().await.unwrap();
    // Dropped without a close: the entry goes with the task.
    drop(again);
    tokio::time::sleep(ms(10)).await;
    let third = start(id, Kind::Ble, script(Kind::Ble, vec![]));
    assert!(third.session.ready().await.is_ok());
}

/// Test: UT-SESS-048
#[tokio::test(start_paused = true)]
async fn an_output_off_during_a_reconnection_attempt_leaves_it_running() {
    let id = "UT-SESS-048-attempt";
    let ble = Kind::Ble;
    let mut first = script(ble, vec![]);
    first.close_at = Some(T0 + ms(1_000));
    let slow_info = script(ble, vec![reply(ble, 0xE0, ms(900), &fixtures::E1_BLE)]);
    let (connector, calls) =
        scripted_connector(vec![mock_attempt(id, first), mock_attempt(id, slow_info)]);
    let mut rig = start_with(id, connector, MemoryMarkers::new(), reconnecting());
    rig.session.ready().await.unwrap();
    rig.drain();
    let events = rig.record();
    // The attempt starts at t0 + 6 s; its 0xE0 is answered after 900 ms.
    let (at, result) = rig
        .call_at(T0 + ms(6_500), |s| async move { s.output_off().await })
        .await
        .unwrap();
    assert_eq!(at, T0 + ms(6_500));
    assert_eq!(
        result,
        Err(Error::LinkLost {
            text: texts::link_lost(&LossReason::Disconnected, Kind::Ble)
        })
    );
    rig.until(T0 + ms(20_000)).await;
    let reconnected: Vec<Duration> = events
        .all()
        .into_iter()
        .filter(|(_, e)| *e == SessionEvent::Reconnected)
        .map(|(t, _)| t)
        .collect();
    assert_eq!(reconnected, vec![T0 + ms(6_000 + 50 + 900 + 130)]);
    let times: Vec<Duration> = calls
        .lock()
        .unwrap()
        .iter()
        .map(|t| *t - rig.start)
        .collect();
    assert_eq!(times, vec![ms(0), T0 + ms(6_000)]);
    assert_eq!(rig.session.link_state(), LinkState::Ready);
}

/// A connector whose first call yields `first` at once and whose every
/// later call fails with a transport error after `delay`: a reconnection
/// attempt that is still running when the next tick (or the give-up time)
/// comes. Records the time of every call.
struct SlowConnector {
    /// The mock of the first connection, taken by the first call.
    first: std::sync::Mutex<Option<Mock>>,
    /// How long every later call takes.
    delay: Duration,
    /// The times of the calls.
    calls: std::sync::Mutex<Vec<Instant>>,
}

impl crate::session::Connector for SlowConnector {
    fn connect<'a>(
        &'a self,
        _identifier: &'a str,
    ) -> futures::future::BoxFuture<
        'a,
        Result<crate::transport::guarded::Guarded<crate::transport::AnyTransport>, Error>,
    > {
        self.calls.lock().unwrap().push(Instant::now());
        let first = self.first.lock().unwrap().take();
        let delay = self.delay;
        Box::pin(async move {
            match first {
                Some(mock) => Ok(crate::transport::guarded::Guarded::new(
                    crate::transport::AnyTransport::from(mock),
                )),
                None => {
                    tokio::time::sleep(delay).await;
                    Err(Error::Transport {
                        message: "no adapter".to_string(),
                    })
                }
            }
        })
    }
}

/// Test: UT-SESS-048
#[tokio::test(start_paused = true)]
async fn an_output_off_during_the_last_attempt_still_gives_up() {
    let id = "UT-SESS-048-give-up";
    let mut first = script(Kind::Ble, vec![]);
    first.close_at = Some(Duration::from_secs(1));
    let connector = Arc::new(SlowConnector {
        first: std::sync::Mutex::new(Some(Mock::new(Kind::Ble, id, first))),
        delay: Duration::from_secs(6),
        calls: std::sync::Mutex::new(Vec::new()),
    });
    let start = Instant::now();
    let (session, mut events) = Session::connect(
        Arc::clone(&connector) as Arc<dyn crate::session::Connector>,
        id,
        host_id(),
        Arc::new(MemoryMarkers::new()),
        reconnecting(),
    )
    .unwrap();
    session.ready().await.unwrap();
    // Lost at 1 s; every attempt takes 6 s, so attempts start at 6, 16,
    // ... 596 s and the one at 596 s still runs at the give-up time, 601 s:
    // that tick ends the schedule and leaves the attempt to finish at 602 s.
    sleep_until(start + Duration::from_millis(601_500)).await;
    assert_eq!(session.link_state(), LinkState::Reconnecting);
    assert_eq!(
        session.output_off().await,
        Err(Error::LinkLost {
            text: texts::link_lost(&LossReason::Disconnected, Kind::Ble)
        })
    );
    sleep_until(start + Duration::from_secs(700)).await;
    assert_eq!(session.link_state(), LinkState::Lost);
    let calls: Vec<Duration> = connector
        .calls
        .lock()
        .unwrap()
        .iter()
        .map(|t| *t - start)
        .collect();
    assert_eq!(calls.len(), 61, "{calls:?}");
    assert_eq!(calls.last(), Some(&Duration::from_secs(596)));
    let mut gave_up = Vec::new();
    while let Ok(Some(event)) = tokio::time::timeout(ms(1), events.next()).await {
        if let SessionEvent::ReconnectGaveUp { text } = event {
            gave_up.push(text);
        }
    }
    assert_eq!(gave_up, vec![texts::GAVE_UP_TIMEOUT.to_string()]);
    assert!(matches!(session.ready().await, Err(Error::LinkLost { .. })));
}

/// Test: UT-SESS-041
#[tokio::test(start_paused = true)]
async fn a_reconnection_keeps_the_marker_and_compares_faults_and_setpoints_afresh() {
    let id = "UT-SESS-041-afresh";
    let ble = Kind::Ble;
    // Both connections report the output on with the reversed-output fault;
    // the first at the capture's setpoints, the second at (500, 1000).
    let before = fixtures::c3_with(1, 0, 1, 1300, 1000);
    let after = fixtures::c3_with(1, 0, 1, 500, 1000);
    let mut first = script(ble, vec![reply(ble, 0xC2, ms(130), &before)]);
    first.close_at = Some(T0 + ms(1_500));
    let (connector, _) = scripted_connector(vec![
        mock_attempt(id, first),
        mock_attempt(id, script(ble, vec![reply(ble, 0xC2, ms(130), &after)])),
    ]);
    let mut rig = start_with(id, connector, MemoryMarkers::new(), reconnecting());
    rig.session.ready().await.unwrap();
    rig.session.request_remote_control().await.unwrap();
    let events = rig.record();
    rig.until(T0 + ms(1_400)).await;
    // The output is on and control is held: a marker is written.
    let calls = rig.markers.calls();
    assert!(calls
        .iter()
        .any(|(_, c)| matches!(c, crate::session::doubles::MarkerCall::Set(_))));
    rig.until(T0 + ms(3_000)).await;
    assert_eq!(rig.session.link_state(), LinkState::Reconnecting);
    // A command stamped before the loss never runs after it, even once
    // the session is ready again (the generation rule).
    let generation = rig
        .session
        .shared
        .generation
        .load(std::sync::atomic::Ordering::SeqCst);
    let info = rig.session.ready().await.unwrap();
    assert_eq!(info.model, "MP305B");
    let reconnected_at = rig.now();
    let (reply, answer) = tokio::sync::oneshot::channel();
    rig.session
        .commands
        .send(crate::session::Command {
            kind: crate::session::CommandKind::OutputOn,
            limits: limits(),
            generation: generation.saturating_sub(1),
            reply,
        })
        .unwrap();
    assert!(matches!(answer.await.unwrap(), Err(Error::LinkLost { .. })));
    rig.until(reconnected_at + ms(1_000)).await;
    assert!(!rig.sent_of(1).iter().any(|(_, op, _)| *op == 0xC8));
    // The loss and the reconnection left the marker alone, and nothing
    // checked it again.
    let calls = rig.markers.calls();
    let present = calls
        .iter()
        .filter(|(_, c)| *c == crate::session::doubles::MarkerCall::Present)
        .count();
    assert_eq!(present, 1);
    assert!(!calls
        .iter()
        .any(|(_, c)| *c == crate::session::doubles::MarkerCall::Clear));
    assert!(rig.markers.present(id).unwrap().is_some());
    let after_reconnection: Vec<SessionEvent> = events
        .non_readings()
        .into_iter()
        .filter(|(t, _)| *t >= reconnected_at)
        .map(|(_, e)| e)
        .collect();
    assert!(!after_reconnection
        .iter()
        .any(|e| matches!(e, SessionEvent::UncleanExitWarning { .. })));
    // The same fault on the first reading of the new connection is
    // reported again: the comparison starts afresh.
    let faults: Vec<&SessionEvent> = after_reconnection
        .iter()
        .filter(|e| matches!(e, SessionEvent::FaultsChanged { .. }))
        .collect();
    assert_eq!(faults.len(), 1, "{after_reconnection:?}");
    // The setpoints were unknown since the loss: the first reading of the
    // new connection is compared with the last one of the old.
    assert_eq!(
        setpoint_changes(&after_reconnection),
        vec![SessionEvent::SetpointsChanged {
            set_volts: 5.0,
            set_amps: 1.0,
            expected_volts: 13.0,
            expected_amps: 1.0,
        }]
    );
}

/// Test: UT-SESS-040
#[tokio::test(start_paused = true)]
async fn a_loss_keeps_the_marker_and_names_no_usb_host_over_usb() {
    use crate::session::doubles::MarkerCall;
    // Bluetooth, control held, the output on: a marker is written; the loss
    // leaves it in place.
    let id = "UT-SESS-040-marker";
    let ble = Kind::Ble;
    let on = fixtures::c3_with(1, 0, 0, 1300, 1000);
    let mut first = script(ble, vec![reply(ble, 0xC2, ms(130), &on)]);
    first.close_at = Some(T0 + ms(1_500));
    let rig = start(id, ble, first);
    rig.session.ready().await.unwrap();
    rig.session.request_remote_control().await.unwrap();
    rig.until(T0 + ms(3_000)).await;
    assert_eq!(rig.session.link_state(), LinkState::Lost);
    let calls = rig.markers.calls();
    assert!(calls.iter().any(|(_, c)| matches!(c, MarkerCall::Set(_))));
    assert!(!calls.iter().any(|(_, c)| *c == MarkerCall::Clear));
    assert!(rig.markers.present(id).unwrap().is_some());
    // USB: the loss text has no USB host hint.
    let hid = Kind::Hid;
    let mut usb = script(hid, vec![]);
    usb.close_at = Some(T0 + ms(500));
    let mut rig = start("UT-SESS-040-usb", hid, usb);
    rig.session.ready().await.unwrap();
    rig.until(T0 + ms(1_000)).await;
    let text = "The transport reported the link closed. The output is still in its last state \
                and the supply has released remote control."
        .to_string();
    assert_eq!(texts::link_lost(&LossReason::Disconnected, hid), text);
    assert!(rig
        .drain_non_readings()
        .contains(&SessionEvent::LinkLost { text: text.clone() }));
    assert_eq!(
        rig.session.set_voltage(1.0).await,
        Err(Error::LinkLost { text })
    );
}

/// Test: UT-SESS-041
#[tokio::test(start_paused = true)]
async fn a_loss_during_an_attempt_waits_for_the_next_tick() {
    let id = "UT-SESS-041-attempt-lost";
    let ble = Kind::Ble;
    let mut first = script(ble, vec![]);
    first.close_at = Some(Duration::from_secs(1));
    // The second mock drops its link 30 ms into the attempt (during the
    // fast bind); the third is fine.
    let mut dropping = script(ble, vec![]);
    dropping.close_at = Some(ms(30));
    let (connector, calls) = scripted_connector(vec![
        mock_attempt(id, first),
        mock_attempt(id, dropping),
        mock_attempt(id, script(ble, vec![])),
    ]);
    let mut rig = start_with(id, connector, MemoryMarkers::new(), reconnecting());
    rig.session.ready().await.unwrap();
    rig.drain();
    let events = rig.record();
    rig.until(Duration::from_secs(20)).await;
    let times: Vec<Duration> = calls
        .lock()
        .unwrap()
        .iter()
        .map(|t| *t - rig.start)
        .collect();
    assert_eq!(
        times,
        vec![ms(0), Duration::from_secs(6), Duration::from_secs(11)]
    );
    // One loss event (the first link's); the attempt's loss is logged only.
    let non_readings: Vec<SessionEvent> =
        events.non_readings().into_iter().map(|(_, e)| e).collect();
    let losses = non_readings
        .iter()
        .filter(|e| matches!(e, SessionEvent::LinkLost { .. }))
        .count();
    assert_eq!(losses, 1, "{non_readings:?}");
    assert!(non_readings.contains(&SessionEvent::Reconnected));
    assert_eq!(rig.session.link_state(), LinkState::Ready);
}

/// The link states the session published and the events it emitted, in
/// order, from entry `from` on (the test watch on the shared state).
fn trace_from(rig: &Rig, from: usize) -> Vec<String> {
    crate::session::lock(&rig.session.shared.trace)
        .iter()
        .skip(from)
        .cloned()
        .collect()
}

/// Test: UT-SESS-065
#[tokio::test(start_paused = true)]
async fn with_reconnection_the_state_goes_from_ready_to_reconnecting_directly() {
    let ble = Kind::Ble;
    for (id, reconnect) in [("UT-SESS-065-on", true), ("UT-SESS-065-off", false)] {
        let mut first = script(ble, vec![]);
        first.close_at = Some(T0 + ms(1_000));
        let (connector, _) = scripted_connector(vec![mock_attempt(id, first), no_adapter()]);
        let options = if reconnect { reconnecting() } else { options() };
        let rig = start_with(id, connector, MemoryMarkers::new(), options);
        rig.session.ready().await.unwrap();
        let from = crate::session::lock(&rig.session.shared.trace).len();
        rig.until(T0 + ms(2_000)).await;
        let trace = trace_from(&rig, from);
        let states: Vec<&String> = trace.iter().filter(|t| t.starts_with("state ")).collect();
        let lost_event = trace
            .iter()
            .position(|t| t.starts_with("event LinkLost"))
            .unwrap();
        if reconnect {
            assert_eq!(states, vec!["state reconnecting"], "{trace:?}");
            let shown = trace
                .iter()
                .position(|t| t == "state reconnecting")
                .unwrap();
            assert!(shown < lost_event, "{trace:?}");
            assert_eq!(rig.session.link_state(), LinkState::Reconnecting);
        } else {
            assert_eq!(states, vec!["state lost"], "{trace:?}");
            let shown = trace.iter().position(|t| t == "state lost").unwrap();
            assert!(shown < lost_event, "{trace:?}");
            assert_eq!(rig.session.link_state(), LinkState::Lost);
        }
    }
}
