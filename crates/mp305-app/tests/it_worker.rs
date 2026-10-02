//! Implements: nothing; the integration tests of the app's worker: IT-003
//! step 2 and the worker part of IT-041 (docs/v-model/6-integration-tests.md).
//!
//! The worker runs through `mp305_app::worker::start`, as the app's shell
//! runs it, over the core's scripted mock (`MockConnector`, `MemoryMarkers`)
//! on a paused Tokio clock, and only public items of the crate are used. The
//! base script, built with the public mock API: Bluetooth; `0x18` answered
//! `19 00` after 50 ms; `0xE0` answered `E1_BLE` after 100 ms; `0xC2`
//! answered `C3_CAPTURE` (output off) after 130 ms; `0xC8` answered
//! `0xC9 00` after 100 ms; every reply forever. Limits 30 V and 5 A,
//! reconnect off, host ID sixteen bytes `01`. The fixtures are the core's
//! (`mp305_core::protocol::fixtures`): `C3_CAPTURE` is the payload of the
//! first `0xC3` of `2026-09-29T193614-ble-readonly.jsonl` (t = 12.8857,
//! AF01), `E1_BLE` the payload of the `0xE1` of the same capture
//! (t = 12.6162, AF02); `c3_with` changes the output byte of `C3_CAPTURE`.

#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::panic,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects
)]

use core::time::Duration;
use std::sync::Arc;

use futures::future::BoxFuture;
use mp305_app::model::{Found, Kind, Limits};
use mp305_app::worker::{self, AppEvent, Command, Deps, Scanner, UiReading, UiSender, What};
use mp305_core::discovery::ScanOptions;
use mp305_core::error::Error;
use mp305_core::protocol::fixtures::{self, on_air, reply_route};
use mp305_core::protocol::ops::bind::HostId;
use mp305_core::session::doubles::{MemoryMarkers, MockConnector};
use mp305_core::session::{Connector, Markers, RemoteState, SessionEvent};
use mp305_core::transport::mock::{Mock, MockHandle, Reply, Script};
use tokio::sync::mpsc;
use tokio::sync::mpsc::error::TryRecvError;
use tokio::task::JoinHandle;
use tokio::time::{sleep, sleep_until, timeout, Instant};

/// Milliseconds as a duration.
fn ms(n: u64) -> Duration {
    Duration::from_millis(n)
}

/// `at` plus `d`, through `checked_add` (no operator on `Instant`, as in
/// the crate, DD-APP-050).
fn after(at: Instant, d: Duration) -> Instant {
    at.checked_add(d).unwrap()
}

/// The limits of the tests: 30 V and 5 A.
fn limits() -> Limits {
    Limits {
        max_volts: Some(30.0),
        max_amps: Some(5.0),
    }
}

/// A Bluetooth reply to `request` with `payload`, `delay` after the
/// request, forever, eligible from `from` after the mock's creation.
fn reply_from(request: u8, delay: Duration, payload: &[u8], from: Duration) -> Reply {
    let opcode = request.wrapping_add(1);
    Reply {
        request,
        after: delay,
        route: reply_route(Kind::Ble, opcode),
        deliveries: vec![on_air(Kind::Ble, opcode, payload)],
        repeat: None,
        from,
    }
}

/// [`reply_from`] eligible from the mock's creation.
fn reply(request: u8, delay: Duration, payload: &[u8]) -> Reply {
    reply_from(request, delay, payload, Duration::ZERO)
}

/// The base script of the module doc with every opcode `overrides`
/// answers taken out and `overrides` appended.
fn script(overrides: Vec<Reply>) -> Script {
    let base = vec![
        reply(0x18, ms(50), &[0x00]),
        reply(0xE0, ms(100), &fixtures::E1_BLE),
        reply(0xC2, ms(130), &fixtures::C3_CAPTURE),
        reply(0xC8, ms(100), &[0x00]),
    ];
    let mut replies: Vec<Reply> = base
        .into_iter()
        .filter(|b| overrides.iter().all(|o| o.request != b.request))
        .collect();
    replies.extend(overrides);
    Script {
        replies,
        ..Script::default()
    }
}

/// A scanner that answers at once with `found`.
struct ScriptedScanner {
    /// The supplies it finds.
    found: Vec<Found>,
}

impl Scanner for ScriptedScanner {
    fn scan(&self, _options: ScanOptions) -> BoxFuture<'_, Result<Vec<Found>, Error>> {
        let found = self.found.clone();
        Box::pin(async move { Ok(found) })
    }
}

/// The scan row of the supply with `identifier`: Bluetooth, name `MP305B`.
fn found(identifier: &str) -> Found {
    Found {
        transport: Kind::Ble,
        identifier: identifier.into(),
        unit_id: identifier.into(),
        name: "MP305B".into(),
        rssi: Some(-60),
        remote_flag: Some(true),
    }
}

/// The worker under test with the UI's ends of its channels.
struct Rig {
    /// The command channel, the UI's end.
    commands: mpsc::UnboundedSender<Command>,
    /// The event channel, the UI's end.
    events: mpsc::UnboundedReceiver<AppEvent>,
    /// The reading channel, the UI's end.
    readings: mpsc::Receiver<UiReading>,
    /// The connector, for the mock handles.
    connector: Arc<MockConnector>,
    /// The worker task; kept so that it is not detached unnoticed.
    _worker: JoinHandle<()>,
}

impl Rig {
    /// A worker whose connections follow `script` and whose scans find the
    /// supply `identifier`, spawned through `worker::start` with the
    /// channels of DD-APP-008.
    fn new(identifier: &str, script: Script) -> Rig {
        let id = identifier.to_string();
        let connector = Arc::new(MockConnector::new(move || {
            Ok(Mock::new(Kind::Ble, &id, script.clone()))
        }));
        let deps = Deps {
            connector: Arc::clone(&connector) as Arc<dyn Connector>,
            scanner: Arc::new(ScriptedScanner {
                found: vec![found(identifier)],
            }),
            markers: Arc::new(MemoryMarkers::new()) as Arc<dyn Markers>,
            host_id: HostId::new([1; 16]).unwrap(),
        };
        let (commands, command_rx) = mpsc::unbounded_channel();
        let (event_tx, events) = mpsc::unbounded_channel();
        let (reading_tx, readings) = mpsc::channel(worker::READING_CAPACITY);
        let build: BoxFuture<'static, Result<Deps, String>> = Box::pin(async move { Ok(deps) });
        let worker = tokio::spawn(worker::start(
            build,
            command_rx,
            UiSender::new(event_tx, reading_tx),
            Arc::new(|| {}),
        ));
        Rig {
            commands,
            events,
            readings,
            connector,
            _worker: worker,
        }
    }

    /// Sends `command`.
    fn send(&self, command: Command) {
        self.commands.send(command).unwrap();
    }

    /// The next event, failing after 120 s of the paused clock without one.
    async fn event(&mut self) -> AppEvent {
        timeout(Duration::from_secs(120), self.events.recv())
            .await
            .expect("no event in time")
            .expect("the event channel closed")
    }

    /// Events up to and including the first that `stop` accepts.
    async fn until(&mut self, stop: impl Fn(&AppEvent) -> bool) -> Vec<AppEvent> {
        let mut out = Vec::new();
        loop {
            let event = self.event().await;
            let done = stop(&event);
            out.push(event);
            if done {
                return out;
            }
        }
    }

    /// The handle of the `n`th mock the connector handed out.
    fn mock(&self, n: usize) -> MockHandle {
        self.connector.handles()[n].clone()
    }

    /// The `0xC8` payloads the first mock was sent at or after `from`.
    fn c8s(&self, from: Instant) -> Vec<Vec<u8>> {
        self.mock(0)
            .sent()
            .into_iter()
            .filter(|s| s.frame.opcode() == 0xC8 && s.at >= from)
            .map(|s| s.frame.payload().to_vec())
            .collect()
    }
}

/// `remoteCon` (payload byte 0) and `output` (payload byte 8) of a `0xC8`
/// payload (protocol.md, the `0xC8` layout).
fn shape(payload: &[u8]) -> (u8, u8) {
    (payload[0], payload[8])
}

/// Whether `event` answers a command or reports the connection (every
/// event but `Session` and `ReadingsDropped`).
fn answer_or_connection(event: &AppEvent) -> bool {
    !matches!(
        event,
        AppEvent::Session { .. } | AppEvent::ReadingsDropped { .. }
    )
}

/// The position of the first event in `events` that `pick` accepts.
fn position(events: &[AppEvent], pick: impl Fn(&AppEvent) -> bool) -> usize {
    events
        .iter()
        .position(pick)
        .unwrap_or_else(|| panic!("not found in {events:?}"))
}

/// Test: IT-003
#[tokio::test(start_paused = true)]
async fn ui_side_calls_return_at_once_while_the_worker_waits_in_a_2_s_reply_delay() {
    // Step 2: the mock delays every reply by 2 s.
    let delay = Duration::from_secs(2);
    let slow = script(vec![
        reply(0x18, delay, &[0x00]),
        reply(0xE0, delay, &fixtures::E1_BLE),
        reply(0xC2, delay, &fixtures::C3_CAPTURE),
        reply(0xC8, delay, &[0x00]),
    ]);
    let mut rig = Rig::new("IT-003", slow);
    rig.send(Command::Connect {
        id: 1,
        identifier: "IT-003".into(),
        reconnect: false,
        limits: limits(),
    });
    assert_eq!(
        rig.event().await,
        AppEvent::Done {
            id: 1,
            what: What::Connect,
            result: Ok(())
        }
    );
    assert_eq!(
        rig.event().await,
        AppEvent::Connecting {
            sid: 1,
            identifier: "IT-003".into()
        }
    );
    sleep(ms(500)).await;
    // The worker is inside the delay: the bind went out, its reply is not
    // due yet.
    let sent = rig.mock(0).sent();
    assert_eq!(sent.len(), 1, "{sent:?}");
    assert_eq!(sent[0].frame.opcode(), 0x18);
    let due = after(sent[0].at, delay);
    assert!(Instant::now() < due);

    // The UI side, on a thread of its own outside the runtime as the app's
    // UI thread is: send a command, then `try_recv` on the event channel.
    // The runtime's one thread waits for it, so the clock stays inside the
    // delay throughout.
    let commands = rig.commands.clone();
    let events = &mut rig.events;
    let (send_took, recv_took, received) = std::thread::scope(|s| {
        s.spawn(move || {
            let t = std::time::Instant::now();
            let sent = commands.send(Command::SetLimits {
                id: 2,
                limits: limits(),
            });
            let send_took = t.elapsed();
            assert!(sent.is_ok());
            let t = std::time::Instant::now();
            let received = events.try_recv();
            let recv_took = t.elapsed();
            (send_took, recv_took, received)
        })
        .join()
        .unwrap()
    });
    assert!(send_took <= ms(1), "send took {send_took:?}");
    assert!(recv_took <= ms(1), "try_recv took {recv_took:?}");
    assert!(matches!(received, Err(TryRecvError::Empty)), "{received:?}");

    // The worker takes the command while its request still waits.
    assert_eq!(
        rig.event().await,
        AppEvent::Done {
            id: 2,
            what: What::SetLimits,
            result: Ok(())
        }
    );
    assert!(Instant::now() < due);
}

/// Test: IT-041
#[tokio::test(start_paused = true)]
async fn a_command_sequence_reaches_the_ui_in_order_and_disconnect_switches_off_releases_and_closes(
) {
    // The worker part. The supply reports the output off until `on_from`,
    // on from then, and off again from `off_from`, when the test sends the
    // disconnect; its setpoints stay 13.00 V and 1.000 A, the values the
    // sequence sets. Offsets are from the mock's creation, which is the
    // instant the worker takes `Connect` (the clock is paused).
    let on_from = Duration::from_secs(3);
    let off_from = Duration::from_secs(5);
    let on = fixtures::c3_with(1, 0, 0, 1300, 1000);
    let mut rig = Rig::new(
        "IT-041",
        script(vec![
            reply(0xC2, ms(130), &fixtures::C3_CAPTURE),
            reply_from(0xC2, ms(130), &on, on_from),
            reply_from(0xC2, ms(130), &fixtures::C3_CAPTURE, off_from),
        ]),
    );
    let mut events = Vec::new();

    // A scan, then `Connect` to the supply it found (a user selection).
    rig.send(Command::Scan {
        id: 1,
        options: ScanOptions::default(),
    });
    events.extend(
        rig.until(|e| matches!(e, AppEvent::ScanResult { .. }))
            .await,
    );
    let identifier = match events.last() {
        Some(AppEvent::ScanResult { found, .. }) => found[0].identifier.clone(),
        other => panic!("{other:?}"),
    };
    let start = Instant::now();
    rig.send(Command::Connect {
        id: 2,
        identifier,
        reconnect: false,
        limits: limits(),
    });
    events.extend(
        rig.until(|e| matches!(e, AppEvent::Ready { .. } | AppEvent::ConnectFailed { .. }))
            .await,
    );
    let ready = Instant::now();

    // Four control commands sent at once, without waiting for answers.
    rig.send(Command::RequestRemoteControl { id: 3 });
    rig.send(Command::SetVoltage { id: 4, volts: 13.0 });
    rig.send(Command::SetCurrentLimit { id: 5, amps: 1.0 });
    rig.send(Command::OutputOn { id: 6 });
    events.extend(
        rig.until(|e| matches!(e, AppEvent::Done { id: 6, .. }))
            .await,
    );
    assert!(
        Instant::now() < after(start, on_from),
        "the output-on was answered after the supply already showed the output on"
    );

    // With the output on: a reading that shows it.
    let shown_on = loop {
        let reading = timeout(Duration::from_secs(10), rig.readings.recv())
            .await
            .expect("no reading in time")
            .expect("the reading channel closed");
        if reading.reading.reading.output_on {
            break reading.reading.at;
        }
    };
    assert!(shown_on >= after(start, on_from));

    // `Disconnect { output_off: true }` at `off_from`. While its answer is
    // awaited, the 0xC8 count since the disconnect and the mock's close
    // count are sampled at every event and every millisecond.
    sleep_until(after(start, off_from)).await;
    let from = Instant::now();
    let sample = |rig: &Rig| (rig.c8s(from).len(), rig.mock(0).closes());
    rig.send(Command::Disconnect {
        id: 7,
        output_off: true,
    });
    let deadline = after(from, Duration::from_secs(10));
    let mut samples = vec![sample(&rig)];
    loop {
        assert!(Instant::now() < deadline, "no Disconnected in time");
        match timeout(ms(1), rig.events.recv()).await {
            Ok(Some(event)) => {
                samples.push(sample(&rig));
                let done = matches!(event, AppEvent::Disconnected { .. });
                events.push(event);
                if done {
                    break;
                }
            }
            Ok(None) => panic!("the event channel closed"),
            Err(_) => samples.push(sample(&rig)),
        }
    }

    // Events arrive on the UI channel in order: every answer in the order
    // of its command, the connection's events in their order.
    let answers: Vec<AppEvent> = events
        .iter()
        .filter(|e| answer_or_connection(e))
        .cloned()
        .collect();
    assert_eq!(answers.len(), 9, "{answers:?}");
    assert_eq!(
        answers[0],
        AppEvent::ScanResult {
            id: 1,
            found: vec![found("IT-041")],
            message: None
        }
    );
    assert_eq!(
        answers[1],
        AppEvent::Done {
            id: 2,
            what: What::Connect,
            result: Ok(())
        }
    );
    assert_eq!(
        answers[2],
        AppEvent::Connecting {
            sid: 1,
            identifier: "IT-041".into()
        }
    );
    assert!(
        matches!(
            answers[3],
            AppEvent::Ready {
                sid: 1,
                transport: Some(Kind::Ble),
                ..
            }
        ),
        "{:?}",
        answers[3]
    );
    let expected_dones = [
        (3, What::RequestRemoteControl),
        (4, What::SetVoltage),
        (5, What::SetCurrentLimit),
        (6, What::OutputOn),
    ];
    for (k, (id, what)) in expected_dones.into_iter().enumerate() {
        assert_eq!(
            answers[4 + k],
            AppEvent::Done {
                id,
                what,
                result: Ok(())
            }
        );
    }
    assert_eq!(
        answers[8],
        AppEvent::Disconnected {
            sid: Some(1),
            text: None,
            off_requested: true,
            output_on: Some(false)
        }
    );
    let connecting = position(&events, |e| matches!(e, AppEvent::Connecting { .. }));
    let bound = position(&events, |e| {
        matches!(
            e,
            AppEvent::Session {
                sid: 1,
                event: SessionEvent::BindResult { recognised: true }
            }
        )
    });
    let ready_at = position(&events, |e| matches!(e, AppEvent::Ready { .. }));
    let granted = position(&events, |e| {
        matches!(
            e,
            AppEvent::Session {
                sid: 1,
                event: SessionEvent::RemoteControl(RemoteState::Granted)
            }
        )
    });
    let request_done = position(&events, |e| matches!(e, AppEvent::Done { id: 3, .. }));
    assert!(connecting < bound && bound < ready_at, "{events:?}");
    assert!(ready_at < granted && granted < request_done, "{events:?}");
    assert!(
        !events
            .iter()
            .any(|e| matches!(e, AppEvent::ReadingsDropped { .. })),
        "{events:?}"
    );

    // The commands reached the supply in the order sent: the request
    // (remoteCon 2), the two setpoints and the output-on (remoteCon 1).
    let control: Vec<(u8, u8)> = rig
        .mock(0)
        .sent()
        .into_iter()
        .filter(|s| s.frame.opcode() == 0xC8 && s.at >= ready && s.at < from)
        .map(|s| shape(s.frame.payload()))
        .collect();
    assert_eq!(control, vec![(2, 0), (1, 0), (1, 0), (1, 1)]);

    // The disconnect sequence: `0xC8` with output 0, then `0xC8` with
    // remoteCon 0, then the close.
    let shapes: Vec<(u8, u8)> = rig.c8s(from).iter().map(|p| shape(p)).collect();
    assert_eq!(shapes, vec![(1, 0), (0, 0)]);
    assert_eq!(rig.mock(0).closes(), 1);
    assert!(
        samples.iter().any(|&(c8, closes)| c8 == 2 && closes == 0),
        "the close was not seen after the release: {samples:?}"
    );
    assert!(
        samples.iter().all(|&(c8, closes)| closes == 0 || c8 == 2),
        "the close came before both 0xC8 frames: {samples:?}"
    );
    assert!(
        samples
            .windows(2)
            .all(|w| w[0].0 <= w[1].0 && w[0].1 <= w[1].1),
        "{samples:?}"
    );
}
