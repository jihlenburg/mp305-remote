//! Implements: nothing; holds the tests of UT-SESS-030 to UT-SESS-033 and
//! UT-SESS-046.
//!
//! Task tests: readings and their times, faults, settings, the marker, the
//! bounded reading channel, and the log lines.

use super::*;
use crate::protocol::frame::Frame;
use crate::protocol::ops::settings;
use crate::protocol::ops::telemetry::{Fault, Faults};
use crate::session::doubles::MarkerCall;
use crate::session::{texts, RemoteState, TimedReading};
use crate::transport::test_log;
use log::Level;

/// The readings among `events`.
fn readings(events: &[SessionEvent]) -> Vec<TimedReading> {
    events
        .iter()
        .filter_map(|e| match e {
            SessionEvent::Reading(r) => Some(*r),
            _ => None,
        })
        .collect()
}

/// Test: UT-SESS-030
#[tokio::test(start_paused = true)]
async fn readings_carry_their_times_and_fault_changes_are_reported() {
    let ble = Kind::Ble;
    let reversed = fixtures::c3_with(0, 0, 1, 1300, 1000);
    let mut rig = start(
        "UT-SESS-030",
        ble,
        script(
            ble,
            vec![
                reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
                c3_from(ble, &reversed, ms(1_300)),
                c3_from(ble, &fixtures::C3_CAPTURE, ms(2_300)),
            ],
        ),
    );
    rig.session.ready().await.unwrap();
    rig.until(ms(3_500)).await;
    let events = rig.drain();
    let all = readings(&events);
    // Every reading arrived 130 ms after a 0xC2 the mock was sent.
    let c2_times: Vec<Duration> = rig
        .sent()
        .into_iter()
        .filter(|(_, op, _)| *op == 0xC2)
        .map(|(t, _, _)| t + ms(130))
        .collect();
    for r in &all {
        let offset = r.at - rig.start;
        assert!(c2_times.contains(&offset), "{offset:?}");
        assert_eq!(r.wall, wall0() + offset);
    }
    let faults: Vec<(Faults, TimedReading)> = events
        .iter()
        .filter_map(|e| match e {
            SessionEvent::FaultsChanged { faults, reading } => Some((*faults, *reading)),
            _ => None,
        })
        .collect();
    assert_eq!(faults.len(), 2, "{faults:?}");
    let first_faulty = all.iter().find(|r| !r.reading.faults.is_empty()).unwrap();
    assert_eq!(faults[0].0, Faults(1));
    assert_eq!(
        faults[0].0.iter().collect::<Vec<_>>(),
        vec![Fault::ReversedOutput]
    );
    assert_eq!(faults[0].1, *first_faulty);
    let first_clean_again = all
        .iter()
        .find(|r| r.at > first_faulty.at && r.reading.faults.is_empty())
        .unwrap();
    assert_eq!(faults[1].0, Faults(0));
    assert_eq!(faults[1].1, *first_clean_again);
    assert!(first_clean_again.at - rig.start > ms(2_300));
    assert_eq!(rig.session.latest_reading(), all.last().copied());
}

/// Test: UT-SESS-031
#[tokio::test(start_paused = true)]
async fn settings_frames_become_events_and_other_frames_are_logged() {
    let log = test_log::install();
    let ble = Kind::Ble;
    let mut script = script(ble, vec![]);
    script.injections = vec![
        inject(ble, T0 + ms(1_000), 0xC5, &fixtures::C5_SETTINGS),
        inject(ble, T0 + ms(2_000), 0xDD, &[0x01, 0x02]),
    ];
    let mut rig = start("UT-SESS-031", ble, script);
    rig.session.ready().await.unwrap();
    rig.until(T0 + ms(2_500)).await;
    let expected =
        settings::parse(&Frame::new(0xC5, fixtures::C5_SETTINGS.to_vec()).unwrap()).unwrap();
    let non_readings = rig.drain_non_readings();
    assert_eq!(
        non_readings,
        vec![
            SessionEvent::BindResult { recognised: true },
            SessionEvent::SettingsChanged(expected),
        ]
    );
    assert!(logged(&log, Level::Debug, "ignored device frame"));
}

/// Test: UT-SESS-032
#[tokio::test(start_paused = true)]
async fn the_marker_is_kept_current_while_the_output_is_on() {
    let ble = Kind::Ble;
    let on = fixtures::c3_with(1, 0, 0, 1300, 1000);
    let rig = granted(
        "UT-SESS-032",
        vec![
            reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            c3_from(ble, &on, T0 + ms(100)),
            c3_from(ble, &fixtures::C3_CAPTURE, T0 + ms(3_100)),
        ],
        vec![],
    )
    .await;
    let mut rig = rig;
    let events = rig.record();
    rig.until(T0 + ms(4_000)).await;
    // The first `Set` carries the wall time of the first output-on reading.
    let first_on = events
        .all()
        .into_iter()
        .find_map(|(_, e)| match e {
            SessionEvent::Reading(r) if r.reading.output_on => Some(r.wall),
            _ => None,
        })
        .unwrap();
    let calls = rig.markers.calls();
    let sets: Vec<SystemTime> = calls
        .iter()
        .filter_map(|(_, c)| match c {
            MarkerCall::Set(at) => Some(*at),
            _ => None,
        })
        .collect();
    assert!((3..=4).contains(&sets.len()), "{calls:?}");
    assert_eq!(sets[0], first_on);
    for pair in sets.windows(2) {
        assert!(pair[1].duration_since(pair[0]).unwrap() >= Duration::from_secs(1));
    }
    let clears: Vec<usize> = calls
        .iter()
        .enumerate()
        .filter(|(_, (_, c))| *c == MarkerCall::Clear)
        .map(|(i, _)| i)
        .collect();
    assert_eq!(clears.len(), 1, "{calls:?}");
    assert_eq!(clears[0], calls.len() - 1);
}

/// Test: UT-SESS-032
#[tokio::test(start_paused = true)]
async fn no_marker_without_a_grant_and_a_failing_store_is_only_logged() {
    let ble = Kind::Ble;
    let on = fixtures::c3_with(1, 0, 0, 1300, 1000);
    let rig = start(
        "UT-SESS-032-none",
        ble,
        script(ble, vec![reply(ble, 0xC2, ms(130), &on)]),
    );
    rig.session.ready().await.unwrap();
    rig.until(T0 + ms(3_000)).await;
    assert_eq!(rig.session.remote_state(), RemoteState::None);
    assert!(!rig
        .markers
        .calls()
        .iter()
        .any(|(_, c)| matches!(c, MarkerCall::Set(_))));

    let log = test_log::install();
    let rig = granted(
        "UT-SESS-032-fail",
        vec![
            reply(ble, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            c3_from(ble, &on, T0 + ms(500)),
        ],
        vec![],
    )
    .await;
    rig.markers.fail_next(Error::Store {
        message: "disk full".to_string(),
    });
    let before = rig.session.latest_reading().unwrap().at;
    rig.until(T0 + ms(2_000)).await;
    assert!(logged(
        &log,
        Level::Warn,
        "marker set failed: store: disk full"
    ));
    assert!(rig.session.latest_reading().unwrap().at > before + ms(1_000));
}

/// Test: UT-SESS-033
#[tokio::test(start_paused = true)]
async fn undrained_readings_are_dropped_and_counted() {
    let ble = Kind::Ble;
    let mut script = script(ble, vec![]);
    script.injections = vec![inject(
        ble,
        Duration::from_secs(300),
        0xC5,
        &fixtures::C5_SETTINGS,
    )];
    let mut rig = start("UT-SESS-033", ble, script);
    rig.session.ready().await.unwrap();
    rig.until(Duration::from_secs(400)).await;
    let total = rig
        .sent()
        .iter()
        .filter(|(t, op, _)| *op == 0xC2 && *t + ms(130) <= Duration::from_secs(400))
        .count() as u64;
    assert!((1_700..1_780).contains(&total), "{total}");
    let dropped = rig.session.dropped_readings();
    assert_eq!(dropped, total - 1024);
    assert!((690..760).contains(&dropped), "{dropped}");
    let latest = rig.session.latest_reading().unwrap().at - rig.start;
    assert!(latest > Duration::from_secs(400) - ms(300), "{latest:?}");
    // Read through `next()`, which prefers the unbounded channel.
    let mut events = Vec::new();
    while let Ok(Some(event)) = tokio::time::timeout(ms(1), rig.events.next()).await {
        events.push(event);
    }
    assert_eq!(events[0], SessionEvent::BindResult { recognised: true });
    assert!(matches!(events[1], SessionEvent::SettingsChanged(_)));
    assert_eq!(readings(&events[2..]).len(), 1024);
    assert_eq!(events.len(), 1026);
}

/// Test: UT-SESS-046
#[tokio::test(start_paused = true)]
async fn state_changes_prompts_and_the_loss_are_logged() {
    let log = test_log::install();
    let ble = Kind::Ble;
    let mut script = script(ble, vec![]);
    script.close_at = Some(Duration::from_secs(3));
    let rig = start("UT-SESS-046", ble, script);
    rig.session.ready().await.unwrap();
    assert_eq!(rig.session.set_voltage(1.7).await, Ok(()));
    rig.until(Duration::from_secs(4)).await;
    let lines = log.lines_here(crate::session::LOG_TARGET);
    let has = |level: Level, text: &str| lines.iter().any(|(l, m)| *l == level && m == text);
    assert!(
        has(Level::Info, "link connecting -> connected"),
        "{lines:?}"
    );
    assert!(has(Level::Info, "link allowed -> ready"));
    assert!(has(Level::Info, "remote none -> requested"));
    assert!(has(Level::Info, "remote requested -> granted"));
    assert!(has(Level::Info, "ready MP305B 1.6.0.40"));
    assert!(has(Level::Info, "connected ble UT-SESS-046"));
    assert!(has(Level::Warn, texts::ALLOW_REMOTE_CONTROL));
    let loss = texts::link_lost(&crate::link::LossReason::Disconnected, Kind::Ble);
    assert!(has(Level::Warn, &loss));
}

/// Test: UT-SESS-030
#[tokio::test(start_paused = true)]
async fn a_fault_on_the_first_reading_is_reported() {
    let ble = Kind::Ble;
    let reversed = fixtures::c3_with(0, 0, 1, 1300, 1000);
    let mut rig = start(
        "UT-SESS-030-first",
        ble,
        script(ble, vec![reply(ble, 0xC2, ms(130), &reversed)]),
    );
    rig.session.ready().await.unwrap();
    rig.until(T0 + ms(1_000)).await;
    let events = rig.drain();
    let faults: Vec<(Faults, Duration)> = events
        .iter()
        .filter_map(|e| match e {
            SessionEvent::FaultsChanged { faults, reading } => {
                Some((*faults, reading.at - rig.start))
            }
            _ => None,
        })
        .collect();
    // Once, with the first reading; the later ones show the same set.
    assert_eq!(faults, vec![(Faults(1), T0)]);
}

/// Test: UT-SESS-046
#[tokio::test(start_paused = true)]
async fn a_bluetooth_timeout_is_logged_with_the_usb_host_hint() {
    let log = test_log::install();
    let hint =
        "no reply to 0xc8 within 1.0 s. A USB host talking to the supply is one possible cause.";
    for (id, kind, hinted) in [
        ("UT-SESS-046-ble", Kind::Ble, true),
        ("UT-SESS-046-usb", Kind::Hid, false),
    ] {
        let rig = granted_on(id, kind, vec![c9_ok(kind), c8_unanswered(ms(600))], vec![]).await;
        rig.until(ms(1_000)).await;
        let before = log
            .lines_here(crate::session::LOG_TARGET)
            .iter()
            .filter(|(l, m)| *l == Level::Warn && m == hint)
            .count();
        assert_eq!(
            rig.session.set_voltage(1.7).await,
            Err(Error::Timeout {
                opcode: 0xC8,
                after: Duration::from_secs(1)
            })
        );
        let after = log
            .lines_here(crate::session::LOG_TARGET)
            .iter()
            .filter(|(l, m)| *l == Level::Warn && m == hint)
            .count();
        assert_eq!(after, before + usize::from(hinted), "{id}");
    }
}
