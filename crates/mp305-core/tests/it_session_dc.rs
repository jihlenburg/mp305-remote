//! Integration test IT-025 (AR-025): a full DC session on the scripted mock
//! with `C3_CAPTURE` as the reading, and the cases around it: a stale
//! reading, the mode and fault guards, a rejected command, status 1, a
//! timeout, an output-off behind three setpoint calls, and the unclean-exit
//! marker at connect and while the output is on.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    missing_docs
)]

mod common;

use std::sync::Arc;
use std::time::{Duration, SystemTime};

use tokio::time::{sleep, Instant};

use mp305_core::error::Error;
use mp305_core::protocol::fixtures;
use mp305_core::protocol::ops::info::Version;
use mp305_core::protocol::ops::telemetry::Faults;
use mp305_core::session::doubles::{MarkerCall, MemoryMarkers};
use mp305_core::session::{texts, RemoteState, SessionEvent};
use mp305_core::transport::description::Kind;

use common::{
    granted, host_id, ms, one_mock, options, output, remote_con, reply, reply_with, script, secs,
    setpoints, silent, start, start_with, timed, Rig, C3_CAPTURE, T0,
};

/// The `0xC8` payload a command copied from `C3_CAPTURE` carries, with
/// `remoteCon`, the two setpoints and `output` as given: `realChange` 3,
/// `voltageSlow` 0 and `currentOver` 0 from the reading, `model` and
/// `refresh` 0.
fn copied(remote_con: u8, volts_raw: u16, amps_raw: u16, output: u8) -> Vec<u8> {
    let mut payload = vec![remote_con];
    payload.extend_from_slice(&volts_raw.to_le_bytes());
    payload.extend_from_slice(&amps_raw.to_le_bytes());
    payload.extend_from_slice(&[C3_CAPTURE[22], C3_CAPTURE[23], C3_CAPTURE[21]]);
    payload.extend_from_slice(&[output, 0, 0]);
    payload
}

/// The fields of `payload` that differ from the reading it copies
/// (`C3_CAPTURE`: 1300, 1000, output 0), by name.
fn changed_fields(payload: &[u8]) -> Vec<&'static str> {
    let mut changed = Vec::new();
    let (v, a) = setpoints(payload);
    if v != 1300 {
        changed.push("setVoltage");
    }
    if a != 1000 {
        changed.push("setCurrent");
    }
    if output(payload) != 0 {
        changed.push("output");
    }
    changed
}

/// The `SetpointsChanged` events so far.
fn setpoint_changes(rig: &Rig) -> Vec<SessionEvent> {
    rig.events
        .non_reading_events()
        .into_iter()
        .filter(|e| matches!(e, SessionEvent::SetpointsChanged { .. }))
        .collect()
}

/// Test: IT-025
#[tokio::test(start_paused = true)]
async fn a_full_dc_session_builds_every_c8_from_the_latest_reading() {
    assert_eq!(C3_CAPTURE, fixtures::C3_CAPTURE);
    let ble = Kind::Ble;
    let rig = start("IT-025-full", ble, script(ble, vec![]));
    // connect, info, first reading.
    let info = rig.session.ready().await.unwrap();
    assert_eq!(rig.now(), T0);
    assert_eq!(info.model, "MP305B");
    assert_eq!(info.version, Version([1, 6, 0, 40]));
    assert_eq!(rig.session.info(), Some(info));
    let first = rig.session.latest_reading().unwrap();
    assert_eq!(first.reading.raw.raw, C3_CAPTURE);
    assert_eq!(
        (first.reading.set_volts, first.reading.set_amps),
        (13.0, 1.0)
    );
    // The control calls, then release and close.
    assert_eq!(rig.session.set_voltage(1.7).await, Ok(()));
    assert_eq!(rig.session.set_current_limit(0.1).await, Ok(()));
    assert_eq!(rig.session.output_on().await, Ok(()));
    assert_eq!(rig.session.output_off().await, Ok(()));
    assert_eq!(rig.session.release_remote_control().await, Ok(()));
    assert_eq!(rig.session.close(true).await, Ok(()));
    assert_eq!(rig.mock(0).closes(), 1);

    let c8s: Vec<Vec<u8>> = rig.c8s_after(ms(0)).into_iter().map(|(_, p)| p).collect();
    assert_eq!(
        c8s,
        vec![
            // set_voltage in `None`: the request first.
            copied(2, 1300, 1000, 0),
            copied(1, 170, 1000, 0),
            copied(1, 1300, 100, 0),
            copied(1, 1300, 1000, 1),
            copied(1, 1300, 1000, 0),
            // release, then the close's release.
            copied(0, 1300, 1000, 0),
            copied(0, 1300, 1000, 0),
        ]
    );
    // Every 0xC8 copies the reading and changes at most the one field its
    // call names; model and refresh are 0; output 1 only from output_on.
    let named: [&[&str]; 7] = [
        &[],
        &["setVoltage"],
        &["setCurrent"],
        &["output"],
        &[],
        &[],
        &[],
    ];
    for (payload, fields) in c8s.iter().zip(named) {
        assert_eq!(changed_fields(payload), fields.to_vec(), "{payload:02x?}");
        assert_eq!(&payload[9..], &[0, 0]);
    }
    let on: Vec<usize> = c8s
        .iter()
        .enumerate()
        .filter(|(_, p)| output(p) == 1)
        .map(|(i, _)| i)
        .collect();
    assert_eq!(on, vec![3]);
}

/// Test: IT-025
#[tokio::test(start_paused = true)]
async fn a_reading_older_than_1_s_makes_the_call_poll_first() {
    let ble = Kind::Ble;
    // From 1 s on the supply answers each 0xC2 after 950 ms, so with the
    // 100 ms pause the reading is up to 1.05 s old before the next one.
    let rig = granted(
        "IT-025-stale",
        ble,
        script(
            ble,
            vec![
                reply(ble, 0xC2, ms(130), &C3_CAPTURE),
                reply_with(ble, 0xC2, ms(950), &C3_CAPTURE, None, secs(1)),
            ],
        ),
    )
    .await;
    rig.until(secs(3)).await;
    // Wait for a moment when the latest reading is older than 1 s.
    loop {
        let age = Instant::now() - rig.session.latest_reading().unwrap().at;
        if age > ms(1_010) {
            break;
        }
        sleep(ms(1)).await;
    }
    let call = rig.now();
    let c8s_before = rig.c8s_after(ms(0)).len();
    assert_eq!(rig.session.set_voltage(1.7).await, Ok(()));
    let c8s = rig.c8s_after(call);
    assert_eq!(c8s.len(), 1);
    assert_eq!(rig.c8s_after(ms(0)).len(), c8s_before + 1);
    let (c8_at, payload) = &c8s[0];
    assert_eq!(payload, &copied(1, 170, 1000, 0));
    // A 0xC2 went out after the call, and the 0xC8 waited for its reply.
    let c2_after_call = *rig.c2_times().iter().find(|t| **t >= call).unwrap();
    assert!(
        *c8_at >= c2_after_call + ms(950),
        "{c2_after_call:?} {c8_at:?}"
    );
}

/// Test: IT-025
#[tokio::test(start_paused = true)]
async fn a_reading_outside_dc_mode_and_an_active_fault_send_nothing() {
    let ble = Kind::Ble;
    // The reading says PD mode (`model` 2) from 1 s on.
    let pd = fixtures::c3_with(0, 2, 0, 1300, 1000);
    let rig = start(
        "IT-025-mode",
        ble,
        script(
            ble,
            vec![
                reply(ble, 0xC2, ms(130), &C3_CAPTURE),
                reply_with(ble, 0xC2, ms(130), &pd, None, secs(1)),
            ],
        ),
    );
    rig.session.ready().await.unwrap();
    rig.until(secs(2)).await;
    assert_eq!(
        rig.session.set_voltage(1.7).await,
        Err(Error::Mode { live_mode: 2 })
    );
    assert!(rig.c8s_after(ms(0)).is_empty());

    // Fault bit 5 (over current) from 1 s on.
    let faulty = fixtures::c3_with(0, 0, 1 << 5, 1300, 1000);
    let rig = start(
        "IT-025-fault",
        ble,
        script(
            ble,
            vec![
                reply(ble, 0xC2, ms(130), &C3_CAPTURE),
                reply_with(ble, 0xC2, ms(130), &faulty, None, secs(1)),
            ],
        ),
    );
    rig.session.ready().await.unwrap();
    rig.until(secs(2)).await;
    assert_eq!(
        rig.session.output_on().await,
        Err(Error::FaultActive {
            faults: Faults(1 << 5)
        })
    );
    assert!(rig.c8s_after(ms(0)).is_empty());
}

/// Test: IT-025
#[tokio::test(start_paused = true)]
async fn a_rejected_command_is_busy_and_the_next_reading_is_compared() {
    let ble = Kind::Ble;
    // The request and the voltage are accepted, the next command gets FF,
    // every later one 00.
    let rig = granted(
        "IT-025-busy",
        ble,
        script(
            ble,
            vec![
                reply_with(ble, 0xC8, ms(100), &[0x00], Some(2), ms(0)),
                reply_with(ble, 0xC8, ms(100), &[0xFF], Some(1), ms(0)),
                reply(ble, 0xC8, ms(100), &[0x00]),
            ],
        ),
    )
    .await;
    assert_eq!(rig.session.set_voltage(1.7).await, Ok(()));
    assert_eq!(
        rig.session.set_current_limit(0.2).await,
        Err(Error::CommandRejected {
            status: 0xFF,
            reason: "busy".to_string()
        })
    );
    let rejected_at = rig.c8s_after(ms(0))[2].0 + ms(100);
    rig.until(rejected_at + secs(1)).await;
    // The setpoints were marked unknown: the next settled reading (still
    // 13.00 V) is compared with what the user last set (1.70 V).
    assert_eq!(
        setpoint_changes(&rig),
        vec![SessionEvent::SetpointsChanged {
            set_volts: 13.0,
            set_amps: 1.0,
            expected_volts: 1.7,
            expected_amps: 1.0,
        }]
    );
    // A 0xC3 is read before the next control call's 0xC8.
    assert_eq!(rig.session.set_current_limit(0.1).await, Ok(()));
    let next = rig.c8s_after(rejected_at)[0].0;
    let c2 = *rig.c2_times().iter().find(|t| **t >= rejected_at).unwrap();
    assert!(c2 + ms(130) <= next, "{c2:?} {next:?}");
}

/// Test: IT-025
#[tokio::test(start_paused = true)]
async fn status_one_is_remote_control_lost_and_control_stays_refused() {
    let ble = Kind::Ble;
    let rig = granted(
        "IT-025-lost",
        ble,
        script(
            ble,
            vec![
                reply_with(ble, 0xC8, ms(100), &[0x00], Some(1), ms(0)),
                reply(ble, 0xC8, ms(100), &[0x01]),
            ],
        ),
    )
    .await;
    assert_eq!(
        rig.session.set_voltage(1.7).await,
        Err(Error::RemoteControlLost)
    );
    assert_eq!(rig.session.remote_state(), RemoteState::Lost);
    let sent = rig.c8s_after(ms(0)).len();
    assert_eq!(
        rig.session.set_current_limit(0.1).await,
        Err(Error::RemoteControlLost)
    );
    assert_eq!(rig.session.output_on().await, Err(Error::RemoteControlLost));
    rig.until(rig.now() + secs(1)).await;
    assert_eq!(rig.c8s_after(ms(0)).len(), sent);
}

/// Test: IT-025
#[tokio::test(start_paused = true)]
async fn a_c8_timeout_marks_the_setpoints_unknown() {
    let ble = Kind::Ble;
    let rig = granted(
        "IT-025-timeout",
        ble,
        script(
            ble,
            vec![
                reply_with(ble, 0xC8, ms(100), &[0x00], Some(2), ms(0)),
                silent(0xC8, Some(1), ms(0)),
                reply(ble, 0xC8, ms(100), &[0x00]),
            ],
        ),
    )
    .await;
    assert_eq!(rig.session.set_voltage(1.7).await, Ok(()));
    assert_eq!(
        rig.session.set_current_limit(0.2).await,
        Err(Error::Timeout {
            opcode: 0xC8,
            after: secs(1)
        })
    );
    rig.until(rig.now() + secs(2)).await;
    assert_eq!(
        setpoint_changes(&rig),
        vec![SessionEvent::SetpointsChanged {
            set_volts: 13.0,
            set_amps: 1.0,
            expected_volts: 1.7,
            expected_amps: 1.0,
        }]
    );
}

/// Test: IT-025
#[tokio::test(start_paused = true)]
async fn an_output_off_behind_three_setpoint_calls_goes_out_first() {
    let ble = Kind::Ble;
    let rig = granted("IT-025-off", ble, script(ble, vec![])).await;
    let s = Arc::clone(&rig.session);
    let calls = rig.now();
    // The three setpoint calls are handed over first, then the output-off,
    // all before the session task runs again.
    let (a, b, c, off) = tokio::join!(
        timed(rig.start, s.set_voltage(1.0)),
        timed(rig.start, s.set_voltage(2.0)),
        timed(rig.start, s.set_current_limit(0.2)),
        timed(rig.start, s.output_off()),
    );
    let cancelled = Err(Error::Cancelled {
        reason: "superseded by an output-off".to_string(),
    });
    assert_eq!(
        (a.1, b.1, c.1),
        (cancelled.clone(), cancelled.clone(), cancelled)
    );
    assert_eq!(off.1, Ok(()));
    // The output-off is the first 0xC8 after the calls; no setpoint went out.
    let c8s = rig.c8s_after(calls);
    assert_eq!(c8s.len(), 1, "{c8s:?}");
    let (off_at, payload) = &c8s[0];
    assert_eq!((remote_con(payload), output(payload)), (1, 0));
    // Its 0xC9 was awaited within 0.5 s of its write.
    assert!(off.0 - *off_at <= ms(500), "{off_at:?} {:?}", off.0);
    // Then a 0xC3 is read.
    rig.until(off.0 + secs(1)).await;
    let c2 = *rig.c2_times().iter().find(|t| **t >= off.0).unwrap();
    let readings = rig.events.reading_times(rig.start);
    assert!(readings.iter().any(|t| *t > c2), "{c2:?}");
}

/// Test: IT-025
#[tokio::test(start_paused = true)]
async fn a_marker_present_at_connect_warns_before_the_first_c8() {
    let id = "IT-025-marker";
    let since = SystemTime::UNIX_EPOCH + Duration::from_secs(1_790_845_200);
    let rig = start_with(
        id,
        one_mock(id, Kind::Ble, script(Kind::Ble, vec![])),
        MemoryMarkers::holding(id, since),
        options(false),
        host_id(),
    );
    rig.session.ready().await.unwrap();
    assert_eq!(rig.session.set_voltage(1.7).await, Ok(()));
    let warning = SessionEvent::UncleanExitWarning {
        since,
        text: texts::unclean_exit(since),
    };
    let warned = rig.events.time_of(|e| *e == warning).unwrap();
    let first_c8 = rig.c8s_after(ms(0))[0].0;
    assert!(warned <= T0, "{warned:?}");
    assert!(warned <= first_c8, "{warned:?} {first_c8:?}");
}

/// Test: IT-025
#[tokio::test(start_paused = true)]
async fn the_marker_follows_the_output_while_control_is_held() {
    let ble = Kind::Ble;
    let id = "IT-025-on-off";
    let on = fixtures::c3_with(1, 0, 0, 1300, 1000);
    // Output off, on from 1 s, off again from 4 s.
    let rig = granted(
        id,
        ble,
        script(
            ble,
            vec![
                reply(ble, 0xC2, ms(130), &C3_CAPTURE),
                reply_with(ble, 0xC2, ms(130), &on, None, secs(1)),
                reply_with(ble, 0xC2, ms(130), &C3_CAPTURE, None, secs(4)),
            ],
        ),
    )
    .await;
    // The first output-on reading writes the marker with its wall time.
    let first_on = loop {
        let r = rig.session.latest_reading().unwrap();
        if r.reading.output_on {
            break r;
        }
        sleep(ms(1)).await;
    };
    assert_eq!(
        rig.markers.calls().last(),
        Some(&(id.to_string(), MarkerCall::Set(first_on.wall)))
    );
    // It is refreshed while the readings show the output on.
    rig.until(secs(3) + ms(900)).await;
    let sets: Vec<SystemTime> = rig
        .markers
        .calls()
        .iter()
        .filter_map(|(_, c)| match c {
            MarkerCall::Set(at) => Some(*at),
            _ => None,
        })
        .collect();
    assert!(sets.len() >= 2, "{sets:?}");
    for pair in sets.windows(2) {
        assert!(pair[1].duration_since(pair[0]).unwrap() >= secs(1));
    }
    // The first reading with the output off removes it.
    loop {
        if !rig.session.latest_reading().unwrap().reading.output_on {
            break;
        }
        sleep(ms(1)).await;
    }
    assert_eq!(
        rig.markers.calls().last(),
        Some(&(id.to_string(), MarkerCall::Clear))
    );
    // The close removes it as well.
    let before = rig.markers.calls().len();
    assert_eq!(rig.session.close(true).await, Ok(()));
    let after = rig.markers.calls();
    assert!(
        after[before..].iter().any(|(_, c)| *c == MarkerCall::Clear),
        "{after:?}"
    );
}
