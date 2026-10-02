//! Implements: nothing; the worker tests (app DD, section 9), a submodule
//! of `worker` compiled under `cfg(test)`.
//!
//! Every test runs `worker::run` on the scripted mock of the core. The test
//! script, built with the public mock API like the default script of the
//! session tests: Bluetooth; `0x18` answered `19 00` after 50 ms; `0xE0`
//! answered `E1_BLE` after 100 ms; `0xC2` answered `C3_CAPTURE` after
//! 130 ms, forever; `0xC8` answered `0xC9 00` after 100 ms, forever;
//! `MemoryMarkers` empty; limits 30 V and 5 A; reconnect off; the host ID
//! sixteen bytes `01`; the identifier the UT ID with a letter per case. On
//! it `Ready` comes 280 ms after `Connect` and readings follow every
//! 230 ms.

use core::time::Duration;
use std::sync::atomic::{AtomicUsize, Ordering};
use std::sync::{Arc, Condvar, Mutex};

use futures::future::BoxFuture;
use mp305_core::discovery::ScanOptions;
use mp305_core::error::Error;
use mp305_core::link::LossReason;
use mp305_core::protocol::fixtures::{self, on_air, reply_route};
use mp305_core::protocol::ops::bind::HostId;
use mp305_core::session::doubles::{MarkerCall, MemoryMarkers, MockConnector};
use mp305_core::session::{
    self, Connector, Markers, Options, PromptKind, RemoteState, SessionEvent,
};
use mp305_core::transport::mock::{Mock, MockHandle, Reply, Script};
use tokio::sync::mpsc;
use tokio::task::JoinHandle;
use tokio::time::{sleep, sleep_until, timeout, Instant};

use super::{
    run, AppEvent, Command, Deps, ErrorKind, ErrorText, Scanner, UiReading, UiSender, What,
};
use crate::model::{Found, Kind, Limits};
use crate::testkit::after;
use crate::texts;

/// Milliseconds as a duration.
pub(crate) fn ms(n: u64) -> Duration {
    Duration::from_millis(n)
}

/// The limits of the test script: 30 V and 5 A.
pub(crate) fn limits() -> Limits {
    Limits {
        max_volts: Some(30.0),
        max_amps: Some(5.0),
    }
}

/// The host ID of every test: sixteen bytes `01`.
pub(crate) fn host_id() -> HostId {
    HostId::new([1; 16]).unwrap()
}

/// A Bluetooth reply to `request` with `payload` `after` the request,
/// forever, from the mock's creation.
pub(crate) fn reply(request: u8, after: Duration, payload: &[u8]) -> Reply {
    let opcode = request.wrapping_add(1);
    Reply {
        request,
        after,
        route: reply_route(Kind::Ble, opcode),
        deliveries: vec![on_air(Kind::Ble, opcode, payload)],
        repeat: None,
        from: Duration::ZERO,
    }
}

/// `reply` for `repeat` requests.
pub(crate) fn reply_n(request: u8, after: Duration, payload: &[u8], repeat: usize) -> Reply {
    Reply {
        repeat: Some(repeat),
        ..reply(request, after, payload)
    }
}

/// A reply to `request` that never comes, forever.
pub(crate) fn never(request: u8) -> Reply {
    Reply {
        request,
        deliveries: Vec::new(),
        ..Reply::default()
    }
}

/// The test script with every opcode `overrides` answers taken out and
/// `overrides` appended.
pub(crate) fn script(overrides: Vec<Reply>) -> Script {
    script_with(overrides, [50, 100, 130, 100])
}

/// The test script with every delay 5 ms.
pub(crate) fn fast_script(overrides: Vec<Reply>) -> Script {
    script_with(overrides, [5, 5, 5, 5])
}

/// A script with the delays of `0x18`, `0xE0`, `0xC2` and `0xC8`.
fn script_with(overrides: Vec<Reply>, delays: [u64; 4]) -> Script {
    let [bind, info, c2, c8] = delays;
    let defaults = vec![
        reply(0x18, ms(bind), &[0x00]),
        reply(0xE0, ms(info), &fixtures::E1_BLE),
        reply(0xC2, ms(c2), &fixtures::C3_CAPTURE),
        reply(0xC8, ms(c8), &[0x00]),
    ];
    let mut replies: Vec<Reply> = defaults
        .into_iter()
        .filter(|d| overrides.iter().all(|o| o.request != d.request))
        .collect();
    replies.extend(overrides);
    Script {
        replies,
        ..Script::default()
    }
}

/// `0xC2` answered with `payload` after 130 ms, forever.
pub(crate) fn c2_always(payload: &[u8]) -> Reply {
    reply(0xC2, ms(130), payload)
}

/// A connector whose attempts follow `scripts` in order, then the test
/// script.
pub(crate) fn connector(identifier: &str, scripts: Vec<Script>) -> MockConnector {
    let id = identifier.to_string();
    let mut scripts = scripts.into_iter();
    MockConnector::new(move || {
        let script = scripts.next().unwrap_or_else(|| script(Vec::new()));
        Ok(Mock::new(Kind::Ble, &id, script))
    })
}

/// A scanner that answers after `delay` with `result`.
pub(crate) struct ScriptedScanner {
    /// The delay.
    pub(crate) delay: Duration,
    /// The answer.
    pub(crate) result: Result<Vec<Found>, Error>,
}

impl Scanner for ScriptedScanner {
    fn scan(&self, _options: ScanOptions) -> BoxFuture<'_, Result<Vec<Found>, Error>> {
        Box::pin(async move {
            sleep(self.delay).await;
            self.result.clone()
        })
    }
}

/// `F`, the `Found` a scripted scanner returns.
pub(crate) fn found_f() -> Found {
    Found {
        transport: Kind::Ble,
        identifier: "F".into(),
        unit_id: "FFF".into(),
        name: "MP305B".into(),
        rssi: Some(-50),
        remote_flag: Some(true),
    }
}

/// A scanner that returns `[F]` at once.
pub(crate) fn scanner_f() -> Arc<dyn Scanner> {
    Arc::new(ScriptedScanner {
        delay: Duration::ZERO,
        result: Ok(vec![found_f()]),
    })
}

/// The dependencies over `connector` and `markers`.
pub(crate) fn deps(
    connector: &Arc<MockConnector>,
    markers: &Arc<MemoryMarkers>,
    scanner: Arc<dyn Scanner>,
) -> Deps {
    Deps {
        connector: Arc::clone(connector) as Arc<dyn Connector>,
        scanner,
        markers: Arc::clone(markers) as Arc<dyn Markers>,
        host_id: host_id(),
    }
}

/// A `Wake` that counts its calls.
pub(crate) fn counting_wake() -> (super::Wake, Arc<AtomicUsize>) {
    let count = Arc::new(AtomicUsize::new(0));
    let inner = Arc::clone(&count);
    let wake: super::Wake = Arc::new(move || {
        inner.fetch_add(1, Ordering::SeqCst);
    });
    (wake, count)
}

/// A worker under test with what a test needs to drive and observe it.
pub(crate) struct Rig {
    /// The command channel; `None` once dropped.
    pub(crate) commands: Option<mpsc::UnboundedSender<Command>>,
    /// The event channel.
    pub(crate) events: mpsc::UnboundedReceiver<AppEvent>,
    /// The reading channel.
    pub(crate) readings: mpsc::Receiver<UiReading>,
    /// The connector, for the mock handles.
    pub(crate) connector: Arc<MockConnector>,
    /// The markers.
    pub(crate) markers: Arc<MemoryMarkers>,
    /// How often the worker woke the UI.
    pub(crate) wakes: Arc<AtomicUsize>,
    /// The worker task.
    pub(crate) worker: Option<JoinHandle<()>>,
    /// The identifier `Connect` uses.
    pub(crate) identifier: String,
    /// When the last `Connect` was sent.
    pub(crate) start: Instant,
    /// The ids handed out so far.
    next_id: u64,
    /// Events received, counted for the wake check.
    received: usize,
}

impl Rig {
    /// A worker over `connector`, `markers` and `scanner`, spawned.
    pub(crate) fn with(
        identifier: &str,
        connector: MockConnector,
        markers: MemoryMarkers,
        scanner: Arc<dyn Scanner>,
    ) -> Rig {
        let connector = Arc::new(connector);
        let markers = Arc::new(markers);
        let (commands, command_rx) = mpsc::unbounded_channel();
        let (event_tx, events) = mpsc::unbounded_channel();
        let (reading_tx, readings) = mpsc::channel(super::READING_CAPACITY);
        let (wake, wakes) = counting_wake();
        let worker = tokio::spawn(run(
            deps(&connector, &markers, scanner),
            command_rx,
            UiSender::new(event_tx, reading_tx),
            wake,
        ));
        Rig {
            commands: Some(commands),
            events,
            readings,
            connector,
            markers,
            wakes,
            worker: Some(worker),
            identifier: identifier.to_string(),
            start: Instant::now(),
            next_id: 0,
            received: 0,
        }
    }

    /// A worker whose attempts follow `scripts`, then the test script.
    pub(crate) fn new(identifier: &str, scripts: Vec<Script>) -> Rig {
        Rig::with(
            identifier,
            connector(identifier, scripts),
            MemoryMarkers::new(),
            scanner_f(),
        )
    }

    /// The next id.
    pub(crate) fn id(&mut self) -> u64 {
        self.next_id += 1;
        self.next_id
    }

    /// Sends `command`.
    pub(crate) fn send(&self, command: Command) {
        self.commands.as_ref().unwrap().send(command).unwrap();
    }

    /// Drops the command sender.
    pub(crate) fn drop_commands(&mut self) {
        self.commands = None;
    }

    /// The next event, failing after 120 s without one.
    pub(crate) async fn event(&mut self) -> AppEvent {
        self.event_within(Duration::from_secs(120)).await
    }

    /// The next event, failing after `bound` without one.
    pub(crate) async fn event_within(&mut self, bound: Duration) -> AppEvent {
        let event = timeout(bound, self.events.recv())
            .await
            .expect("no event in time")
            .expect("the event channel closed");
        self.received += 1;
        event
    }

    /// Events up to and including the first that `stop` accepts.
    pub(crate) async fn until(&mut self, stop: impl Fn(&AppEvent) -> bool) -> Vec<AppEvent> {
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

    /// Sends `Connect` and returns the events up to `Ready` or
    /// `ConnectFailed`.
    pub(crate) async fn connect(&mut self) -> Vec<AppEvent> {
        let id = self.id();
        self.start = Instant::now();
        self.send(Command::Connect {
            id,
            identifier: self.identifier.clone(),
            reconnect: false,
            limits: limits(),
        });
        self.until(|e| matches!(e, AppEvent::Ready { .. } | AppEvent::ConnectFailed { .. }))
            .await
    }

    /// Sends `RequestRemoteControl` and waits for its `Done` with `Ok`.
    pub(crate) async fn grant(&mut self) {
        let id = self.id();
        self.send(Command::RequestRemoteControl { id });
        let events = self
            .until(|e| matches!(e, AppEvent::Done { id: i, .. } if *i == id))
            .await;
        assert!(
            matches!(events.last(), Some(AppEvent::Done { result: Ok(()), .. })),
            "{events:?}"
        );
    }

    /// The `Done` of `id`, waiting for it.
    pub(crate) async fn done_of(&mut self, id: u64) -> Result<(), ErrorText> {
        let events = self
            .until(|e| matches!(e, AppEvent::Done { id: i, .. } if *i == id))
            .await;
        match events.last() {
            Some(AppEvent::Done { result, .. }) => result.clone(),
            other => panic!("{other:?}"),
        }
    }

    /// The `Done` results of `ids`, in whatever order they come, and every
    /// event up to the last of them.
    pub(crate) async fn dones(
        &mut self,
        ids: &[u64],
    ) -> (
        std::collections::BTreeMap<u64, Result<(), ErrorText>>,
        Vec<AppEvent>,
    ) {
        let mut results = std::collections::BTreeMap::new();
        let mut events = Vec::new();
        while results.len() < ids.len() {
            let event = self.event().await;
            if let AppEvent::Done { id, result, .. } = &event {
                if ids.contains(id) {
                    results.insert(*id, result.clone());
                }
            }
            events.push(event);
        }
        (results, events)
    }

    /// The handle of the `n`th mock.
    pub(crate) fn mock(&self, n: usize) -> MockHandle {
        self.connector.handles()[n].clone()
    }

    /// The `0xC8` payloads the `n`th mock was sent at or after `from`.
    pub(crate) fn c8s(&self, n: usize, from: Instant) -> Vec<Vec<u8>> {
        self.mock(n)
            .sent()
            .into_iter()
            .filter(|s| s.frame.opcode() == 0xC8 && s.at >= from)
            .map(|s| s.frame.payload().to_vec())
            .collect()
    }

    /// The frames the `n`th mock was sent at or after `from`.
    pub(crate) fn frames(&self, n: usize, from: Instant) -> usize {
        self.mock(n)
            .sent()
            .into_iter()
            .filter(|s| s.at >= from)
            .count()
    }

    /// The marker calls.
    pub(crate) fn marker_calls(&self) -> Vec<MarkerCall> {
        self.markers.calls().into_iter().map(|(_, c)| c).collect()
    }

    /// Waits for the worker to return, failing after `bound`.
    pub(crate) async fn ended_within(&mut self, bound: Duration) {
        let worker = self.worker.take().unwrap();
        timeout(bound, worker)
            .await
            .expect("the worker did not return")
            .unwrap();
    }

    /// Whether every event received so far woke the UI at least once.
    pub(crate) fn woke_per_event(&self, readings: usize) -> bool {
        self.wakes.load(Ordering::SeqCst) >= self.received + readings
    }
}

/// `remoteCon` and `output` of a `0xC8` payload.
pub(crate) fn shape(payload: &[u8]) -> (u8, u8) {
    (payload[0], payload[8])
}

/// The voltage setpoint of a `0xC8` payload, raw.
pub(crate) fn set_voltage(payload: &[u8]) -> u16 {
    u16::from_le_bytes([payload[1], payload[2]])
}

/// The `Disconnected` among `events`.
fn disconnected(events: &[AppEvent]) -> Vec<AppEvent> {
    events
        .iter()
        .filter(|e| matches!(e, AppEvent::Disconnected { .. }))
        .cloned()
        .collect()
}

/// Test: UT-APP-010
#[tokio::test(start_paused = true)]
async fn a_scan_and_a_connect_reach_the_ui_in_order() {
    let mut rig = Rig::new("UT-APP-010a", vec![]);
    rig.send(Command::Scan {
        id: 1,
        options: ScanOptions::default(),
    });
    assert_eq!(
        rig.event().await,
        AppEvent::ScanResult {
            id: 1,
            found: vec![found_f()],
            message: None
        }
    );
    rig.next_id = 1;
    let id = rig.id();
    let start = Instant::now();
    rig.send(Command::Connect {
        id,
        identifier: "UT-APP-010a".into(),
        reconnect: false,
        limits: limits(),
    });
    assert_eq!(
        rig.event().await,
        AppEvent::Done {
            id: 2,
            what: What::Connect,
            result: Ok(())
        }
    );
    assert_eq!(
        rig.event().await,
        AppEvent::Connecting {
            sid: 1,
            identifier: "UT-APP-010a".into()
        }
    );
    // The worker waits in the mock's bind delay; the UI side never waits.
    sleep(ms(10)).await;
    assert!(matches!(
        rig.events.try_recv(),
        Err(mpsc::error::TryRecvError::Empty)
    ));
    assert_eq!(
        rig.event().await,
        AppEvent::Session {
            sid: 1,
            event: SessionEvent::BindResult { recognised: true }
        }
    );
    let ready = rig.event().await;
    let AppEvent::Ready {
        sid,
        info,
        reading,
        transport,
    } = &ready
    else {
        panic!("{ready:?}");
    };
    assert_eq!(*sid, 1);
    assert_eq!(*info, crate::testkit::info());
    assert_eq!(*transport, Some(Kind::Ble));
    assert_eq!(
        reading.map(|r| r.at.saturating_duration_since(start)),
        Some(ms(280))
    );
    let first = rig.readings.try_recv().unwrap();
    assert_eq!(
        (first.sid, first.reading.at.saturating_duration_since(start)),
        (1, ms(280))
    );
    assert!(rig.woke_per_event(1));
}

/// Test: UT-APP-010
#[tokio::test(start_paused = true)]
async fn scans_that_find_nothing_fail_or_overlap() {
    let empty = Rig::with(
        "UT-APP-010b",
        connector("UT-APP-010b", vec![]),
        MemoryMarkers::new(),
        Arc::new(ScriptedScanner {
            delay: Duration::ZERO,
            result: Ok(vec![]),
        }),
    );
    let mut rig = empty;
    rig.send(Command::Scan {
        id: 1,
        options: ScanOptions::default(),
    });
    assert_eq!(
        rig.event().await,
        AppEvent::ScanResult {
            id: 1,
            found: vec![],
            message: Some(
                "no supply found: the supply is off or out of range; another app (WebLink \
                 in a browser, ISDT's Polying app) is connected to it; a USB host is talking \
                 to it; remote control is disabled on the supply"
                    .into()
            )
        }
    );

    let mut rig = Rig::with(
        "UT-APP-010b",
        connector("UT-APP-010b", vec![]),
        MemoryMarkers::new(),
        Arc::new(ScriptedScanner {
            delay: Duration::ZERO,
            result: Err(Error::Transport {
                message: "no adapter".into(),
            }),
        }),
    );
    rig.send(Command::Scan {
        id: 1,
        options: ScanOptions::default(),
    });
    assert_eq!(
        rig.event().await,
        AppEvent::ScanResult {
            id: 1,
            found: vec![],
            message: Some("transport: no adapter".into())
        }
    );

    let mut rig = Rig::with(
        "UT-APP-010b",
        connector("UT-APP-010b", vec![]),
        MemoryMarkers::new(),
        Arc::new(ScriptedScanner {
            delay: Duration::from_secs(1),
            result: Ok(vec![found_f()]),
        }),
    );
    let start = Instant::now();
    rig.send(Command::Scan {
        id: 1,
        options: ScanOptions::default(),
    });
    sleep(ms(10)).await;
    rig.send(Command::Scan {
        id: 2,
        options: ScanOptions::default(),
    });
    assert_eq!(
        rig.event().await,
        AppEvent::ScanResult {
            id: 2,
            found: vec![],
            message: Some("a scan is already running".into())
        }
    );
    assert_eq!(Instant::now().saturating_duration_since(start), ms(10));
    assert_eq!(
        rig.event().await,
        AppEvent::ScanResult {
            id: 1,
            found: vec![found_f()],
            message: None
        }
    );
    assert_eq!(
        Instant::now().saturating_duration_since(start),
        Duration::from_secs(1)
    );
}

/// Test: UT-APP-010
#[tokio::test(start_paused = true)]
async fn the_unclean_exit_warning_comes_before_ready() {
    let markers = MemoryMarkers::holding("UT-APP-010c", crate::testkit::wall0());
    let mut rig = Rig::with(
        "UT-APP-010c",
        connector("UT-APP-010c", vec![]),
        markers,
        scanner_f(),
    );
    let events = rig.connect().await;
    let warning = events.iter().position(|e| {
        matches!(
            e,
            AppEvent::Session {
                sid: 1,
                event: SessionEvent::UncleanExitWarning { .. }
            }
        )
    });
    let ready = events
        .iter()
        .position(|e| matches!(e, AppEvent::Ready { .. }));
    assert!(warning.is_some() && warning < ready, "{events:?}");
}

/// Test: UT-APP-010
#[tokio::test(start_paused = true)]
async fn a_stalled_ui_loses_readings_with_a_count() {
    let mut rig = Rig::new("UT-APP-010d", vec![]);
    rig.connect().await;
    let start = rig.start;
    let reading_at = |k: u64| after(start, ms(280 + (k - 1) * 230));
    let mut dropped = Vec::new();
    while dropped.len() < 2 {
        let event = rig.event_within(Duration::from_secs(2000)).await;
        match event {
            AppEvent::ReadingsDropped { total } => dropped.push((total, Instant::now())),
            other => panic!("unexpected {other:?}"),
        }
    }
    assert_eq!(dropped, vec![(1, reading_at(4097)), (6, reading_at(4102))]);
}

/// Test: UT-APP-011
#[tokio::test(start_paused = true)]
async fn an_output_off_supersedes_the_queued_setpoints() {
    let c8 = vec![
        reply_n(0xC8, ms(100), &[0x00], 1),
        reply(0xC8, ms(300), &[0x00]),
    ];
    let mut rig = Rig::new("UT-APP-011a", vec![script(c8)]);
    rig.connect().await;
    rig.grant().await;
    let granted = Instant::now();
    for (id, volts) in [(10, 1.0), (11, 2.0), (12, 3.0)] {
        rig.send(Command::SetVoltage { id, volts });
    }
    sleep(ms(50)).await;
    rig.send(Command::OutputOff { id: 13 });
    let (results, _) = rig.dones(&[10, 11, 12, 13]).await;
    for id in 10..13 {
        let e = results[&id].clone().unwrap_err();
        assert_eq!(e.kind, ErrorKind::Cancelled, "{id}");
        assert!(e.text.contains("superseded by an output-off"), "{e:?}");
    }
    assert_eq!(results[&13], Ok(()));
    let c8s = rig.c8s(0, granted);
    assert_eq!(c8s.len(), 1, "{c8s:?}");
    assert_eq!(shape(&c8s[0]), (1, 0));
    assert_eq!(set_voltage(&c8s[0]), 1300);
}

/// Test: UT-APP-011
#[tokio::test(start_paused = true)]
async fn an_output_off_supersedes_setpoints_that_wait_for_the_grant() {
    let mut rig = Rig::new(
        "UT-APP-011b",
        vec![script(vec![reply(0xC8, ms(300), &[0x00])])],
    );
    rig.connect().await;
    let ready = Instant::now();
    for (id, volts) in [(10, 1.0), (11, 2.0), (12, 3.0)] {
        rig.send(Command::SetVoltage { id, volts });
    }
    sleep(ms(50)).await;
    rig.send(Command::OutputOff { id: 13 });
    let (results, events) = rig.dones(&[10, 11, 12, 13]).await;
    let results: Vec<Result<(), ErrorText>> = (10..14).map(|id| results[&id].clone()).collect();
    let c8s = rig.c8s(0, ready);
    let shapes: Vec<(u8, u8)> = c8s.iter().map(|p| shape(p)).collect();
    assert_eq!(shapes.len(), 2, "{shapes:?}");
    assert_eq!(shapes[0].0, 2, "{shapes:?}");
    assert_eq!(shapes[1], (1, 0), "{shapes:?}");
    assert!(events.iter().any(|e| matches!(
        e,
        AppEvent::Session {
            sid: 1,
            event: SessionEvent::Prompt {
                kind: PromptKind::AllowRemoteControl,
                bound_s: 70,
                ..
            }
        }
    )));
    assert!(events.iter().any(|e| matches!(
        e,
        AppEvent::Session {
            sid: 1,
            event: SessionEvent::RemoteControl(RemoteState::Granted)
        }
    )));
    for (i, result) in results.iter().take(3).enumerate() {
        let e = result.clone().unwrap_err();
        assert_eq!(e.kind, ErrorKind::Cancelled);
        assert!(e.text.contains("superseded by an output-off"), "{e:?}");
        if i == 0 {
            assert!(e.text.contains("it may have been applied"), "{e:?}");
        }
    }
    assert_eq!(results[3], Ok(()));
}

/// A connected and granted rig on `script`.
async fn granted(identifier: &str, script: Script) -> Rig {
    let mut rig = Rig::new(identifier, vec![script]);
    rig.connect().await;
    rig.grant().await;
    rig
}

/// The `Disconnected` that answers a `Disconnect` sent now.
async fn disconnect(rig: &mut Rig, output_off: bool) -> AppEvent {
    let id = rig.id();
    rig.send(Command::Disconnect { id, output_off });
    rig.until(|e| matches!(e, AppEvent::Disconnected { .. }))
        .await
        .pop()
        .unwrap()
}

/// Test: UT-APP-012
#[tokio::test(start_paused = true)]
async fn a_disconnect_with_switch_off_confirms_the_output_off() {
    let on = fixtures::c3_with(1, 0, 0, 1300, 1000);
    let off_from_2s = Reply {
        from: Duration::from_secs(2),
        ..reply(0xC2, ms(130), &fixtures::C3_CAPTURE)
    };
    let mut rig = granted("UT-APP-012a", script(vec![c2_always(&on), off_from_2s])).await;
    sleep_until(after(rig.start, Duration::from_secs(2))).await;
    let from = Instant::now();
    assert_eq!(
        disconnect(&mut rig, true).await,
        AppEvent::Disconnected {
            sid: Some(1),
            text: None,
            off_requested: true,
            output_on: Some(false)
        }
    );
    let shapes: Vec<(u8, u8)> = rig.c8s(0, from).iter().map(|p| shape(p)).collect();
    assert_eq!(shapes, vec![(1, 0), (0, 0)]);
    assert_eq!(rig.mock(0).closes(), 1);
    assert_eq!(rig.marker_calls().last(), Some(&MarkerCall::Clear));
}

/// Test: UT-APP-012
#[tokio::test(start_paused = true)]
async fn a_disconnect_without_switch_off_releases_control() {
    let on = fixtures::c3_with(1, 0, 0, 1300, 1000);
    let mut rig = granted("UT-APP-012b", script(vec![c2_always(&on)])).await;
    let from = Instant::now();
    assert_eq!(
        disconnect(&mut rig, false).await,
        AppEvent::Disconnected {
            sid: Some(1),
            text: None,
            off_requested: false,
            output_on: Some(true)
        }
    );
    let shapes: Vec<(u8, u8)> = rig.c8s(0, from).iter().map(|p| shape(p)).collect();
    assert_eq!(shapes, vec![(0, 1)]);
    assert_eq!(rig.mock(0).closes(), 1);
    assert_eq!(rig.marker_calls().last(), Some(&MarkerCall::Clear));
}

/// Test: UT-APP-012
#[tokio::test(start_paused = true)]
async fn a_switch_off_outside_dc_mode_sends_nothing_and_keeps_the_marker() {
    let pd = fixtures::c3_with(1, 2, 0, 1300, 1000);
    let mut rig = Rig::new("UT-APP-012c", vec![script(vec![c2_always(&pd)])]);
    rig.connect().await;
    let from = Instant::now();
    assert_eq!(
        disconnect(&mut rig, true).await,
        AppEvent::Disconnected {
            sid: Some(1),
            text: None,
            off_requested: true,
            output_on: Some(true)
        }
    );
    assert!(rig.c8s(0, from).is_empty());
    assert_eq!(rig.mock(0).closes(), 1);
    assert!(!rig.marker_calls().contains(&MarkerCall::Clear));
}

/// Test: UT-APP-012
#[tokio::test(start_paused = true)]
async fn a_rejected_switch_off_is_reported_and_keeps_the_marker() {
    let on = fixtures::c3_with(1, 0, 0, 1300, 1000);
    let c8 = vec![
        reply_n(0xC8, ms(100), &[0x00], 1),
        reply_n(0xC8, ms(100), &[0xFF], 1),
        reply(0xC8, ms(100), &[0x00]),
    ];
    let mut overrides = vec![c2_always(&on)];
    overrides.extend(c8);
    let mut rig = granted("UT-APP-012d", script(overrides)).await;
    let from = Instant::now();
    let calls_before = rig.marker_calls().len();
    assert_eq!(
        disconnect(&mut rig, true).await,
        AppEvent::Disconnected {
            sid: Some(1),
            text: Some("the supply rejected the command (status 0xff, busy)".into()),
            off_requested: true,
            output_on: Some(true)
        }
    );
    let shapes: Vec<(u8, u8)> = rig.c8s(0, from).iter().map(|p| shape(p)).collect();
    assert_eq!(shapes, vec![(1, 0), (0, 0)]);
    assert!(!rig.marker_calls()[calls_before..].contains(&MarkerCall::Clear));
}

/// The text of the first `LinkLost` among `events`.
fn loss_text(events: &[AppEvent]) -> Option<String> {
    events.iter().find_map(|e| match e {
        AppEvent::Session {
            event: SessionEvent::LinkLost { text },
            ..
        } => Some(text.clone()),
        _ => None,
    })
}

/// Waits for the `LinkLost` and returns its text and time.
async fn until_lost(rig: &mut Rig) -> (String, Instant) {
    let events = rig
        .until(|e| {
            matches!(
                e,
                AppEvent::Session {
                    event: SessionEvent::LinkLost { .. },
                    ..
                }
            )
        })
        .await;
    (loss_text(&events).unwrap(), Instant::now())
}

/// The test script closing 1 s after `Ready` (1.28 s after the connect).
fn closing_script(overrides: Vec<Reply>) -> Script {
    Script {
        close_at: Some(ms(1280)),
        ..script(overrides)
    }
}

/// Test: UT-APP-012
#[tokio::test(start_paused = true)]
async fn a_switch_off_on_a_lost_link_reports_the_loss() {
    let mut rig = granted("UT-APP-012e", closing_script(vec![])).await;
    let (text, lost_at) = until_lost(&mut rig).await;
    sleep_until(after(lost_at, Duration::from_secs(2))).await;
    let expected = Error::LinkLost { text }.to_string();
    assert_eq!(
        disconnect(&mut rig, true).await,
        AppEvent::Disconnected {
            sid: Some(1),
            text: Some(expected),
            off_requested: true,
            output_on: None
        }
    );
    assert_eq!(rig.frames(0, lost_at), 0);
}

/// Test: UT-APP-012
#[tokio::test(start_paused = true)]
async fn an_exit_with_the_output_on_drops_the_session_without_close() {
    let on = fixtures::c3_with(1, 0, 0, 1300, 1000);
    let mut rig = granted("UT-APP-012f", script(vec![c2_always(&on)])).await;
    // A reading after the grant that shows the output on writes the
    // marker (DD-SESS-052); the exit comes after it.
    sleep(ms(300)).await;
    let from = Instant::now();
    rig.drop_commands();
    rig.ended_within(Duration::from_secs(10)).await;
    sleep(Duration::from_secs(5)).await;
    assert!(rig.c8s(0, from).is_empty());
    let calls = rig.marker_calls();
    assert!(calls.iter().any(|c| matches!(c, MarkerCall::Set(_))));
    assert!(!calls.contains(&MarkerCall::Clear));
}

/// Test: UT-APP-012
#[tokio::test(start_paused = true)]
async fn an_exit_with_the_output_confirmed_off_releases_and_closes() {
    let mut rig = granted("UT-APP-012g", script(vec![])).await;
    let mut readings = 0;
    loop {
        if rig.readings.recv().await.is_some() {
            readings += 1;
        }
        if readings >= 2 {
            break;
        }
    }
    let from = Instant::now();
    rig.drop_commands();
    rig.ended_within(Duration::from_secs(10)).await;
    let shapes: Vec<(u8, u8)> = rig.c8s(0, from).iter().map(|p| shape(p)).collect();
    assert_eq!(shapes, vec![(0, 0)]);
    assert_eq!(rig.mock(0).closes(), 1);
    assert!(rig.marker_calls().contains(&MarkerCall::Clear));
}

/// The test script whose fast bind is denied and whose prompt bind is
/// never answered.
fn unanswered_prompt_bind() -> Script {
    script(vec![reply_n(0x18, ms(50), &[0xFF], 1), never(0x18)])
}

/// Test: UT-APP-012
#[tokio::test(start_paused = true)]
async fn an_exit_while_starting_closes_without_a_marker_call() {
    let mut rig = Rig::new("UT-APP-012h", vec![unanswered_prompt_bind()]);
    let id = rig.id();
    rig.start = Instant::now();
    rig.send(Command::Connect {
        id,
        identifier: rig.identifier.clone(),
        reconnect: false,
        limits: limits(),
    });
    sleep(Duration::from_secs(1)).await;
    let calls_before = rig.marker_calls().len();
    rig.drop_commands();
    rig.ended_within(Duration::from_secs(10)).await;
    assert!(rig.c8s(0, rig.start).is_empty());
    assert!(rig.mock(0).closes() >= 1);
    assert_eq!(rig.marker_calls().len(), calls_before);
}

/// Test: UT-APP-012
#[tokio::test(start_paused = true)]
async fn an_exit_while_closing_awaits_the_close() {
    let on = fixtures::c3_with(1, 0, 0, 1300, 1000);
    let c8 = vec![
        reply_n(0xC8, ms(100), &[0x00], 1),
        reply(0xC8, ms(300), &[0x00]),
    ];
    let mut overrides = vec![c2_always(&on)];
    overrides.extend(c8);
    let mut rig = granted("UT-APP-012i", script(overrides)).await;
    let from = Instant::now();
    let id = rig.id();
    rig.send(Command::Disconnect {
        id,
        output_off: true,
    });
    rig.drop_commands();
    rig.ended_within(Duration::from_secs(30)).await;
    let shapes: Vec<(u8, u8)> = rig.c8s(0, from).iter().map(|p| shape(p)).collect();
    assert_eq!(shapes, vec![(1, 0), (0, 0)]);
}

/// Test: UT-APP-012
#[tokio::test(start_paused = true)]
async fn an_exit_after_a_loss_closes_without_frames() {
    let on = fixtures::c3_with(1, 0, 0, 1300, 1000);
    let mut rig = granted("UT-APP-012j", closing_script(vec![c2_always(&on)])).await;
    let (_, lost_at) = until_lost(&mut rig).await;
    sleep_until(after(lost_at, Duration::from_secs(2))).await;
    let from = Instant::now();
    rig.drop_commands();
    rig.ended_within(Duration::from_secs(10)).await;
    assert_eq!(rig.frames(0, from), 0);
    assert!(!rig.marker_calls().contains(&MarkerCall::Clear));
}

/// Test: UT-APP-012
#[tokio::test(start_paused = true)]
async fn an_exit_with_a_stale_reading_drops_the_session() {
    let quiet = Script {
        stop_replying_at: Some(ms(1250)),
        ..script(vec![])
    };
    let mut rig = granted("UT-APP-012k", quiet).await;
    sleep_until(after(rig.start, ms(2700))).await;
    let from = Instant::now();
    let calls_before = rig.marker_calls().len();
    rig.drop_commands();
    rig.ended_within(Duration::from_secs(10)).await;
    sleep(Duration::from_secs(5)).await;
    assert!(rig.c8s(0, from).is_empty());
    assert!(!rig.marker_calls()[calls_before..].contains(&MarkerCall::Clear));
}

/// Test: UT-APP-012
#[tokio::test(start_paused = true)]
async fn an_exit_with_an_output_on_in_flight_drops_the_session() {
    let c8 = vec![
        reply_n(0xC8, ms(100), &[0x00], 1),
        reply(0xC8, Duration::from_secs(2), &[0x00]),
    ];
    let mut rig = granted("UT-APP-012l", script(c8)).await;
    let id = rig.id();
    rig.send(Command::OutputOn { id });
    sleep(ms(100)).await;
    let from = Instant::now();
    let calls_before = rig.marker_calls().len();
    rig.drop_commands();
    rig.ended_within(Duration::from_secs(10)).await;
    sleep(Duration::from_secs(5)).await;
    assert!(rig.c8s(0, from).iter().all(|p| shape(p).0 != 0));
    assert!(!rig.marker_calls()[calls_before..].contains(&MarkerCall::Clear));
}

/// Test: UT-APP-012
#[tokio::test(start_paused = true)]
async fn an_exit_during_a_reconnects_close_connects_nothing() {
    let mut rig = Rig::new("UT-APP-012m", vec![closing_script(vec![])]);
    rig.connect().await;
    until_lost(&mut rig).await;
    rig.send(Command::Reconnect {
        id: 30,
        reconnect: false,
        limits: Limits::none(),
    });
    rig.drop_commands();
    rig.ended_within(Duration::from_secs(10)).await;
    assert_eq!(rig.connector.handles().len(), 1);
}

/// When the `Done` of the output-on of UT-APP-027 arrives on the test
/// script, after the connect (measured on the paused clock: the grant's
/// `Done` at 380 ms, then the session's fresh reading and settle time
/// before the `0xC8`, and its `0xC9 00` 100 ms later). `close_at` of case
/// (a) is set from it; the tests check it.
const OUTPUT_ON_DONE_MS: u64 = 840;

/// The test script with `0xC2` always `c3_with(0, ..)` (output off).
fn output_off_script(close_at: Option<Duration>) -> Script {
    let off = fixtures::c3_with(0, 0, 0, 1300, 1000);
    Script {
        close_at,
        ..script(vec![c2_always(&off)])
    }
}

/// Connects, takes the grant, sends `OutputOn` and waits for its `Done`
/// with `Ok`; returns when it came.
async fn output_on_answered(rig: &mut Rig) -> Instant {
    rig.connect().await;
    rig.grant().await;
    let id = rig.id();
    rig.send(Command::OutputOn { id });
    assert_eq!(rig.done_of(id).await, Ok(()));
    let done = Instant::now();
    assert_eq!(
        done.saturating_duration_since(rig.start),
        ms(OUTPUT_ON_DONE_MS)
    );
    done
}

/// Test: UT-APP-027
#[tokio::test(start_paused = true)]
async fn a_reading_from_before_a_failed_switch_off_is_no_witness() {
    let close_at = ms(OUTPUT_ON_DONE_MS + 20 + 30);
    let mut rig = Rig::new("UT-APP-027a", vec![output_off_script(Some(close_at))]);
    let done = output_on_answered(&mut rig).await;
    sleep_until(after(done, ms(20))).await;
    let answer = disconnect(&mut rig, true).await;
    let AppEvent::Disconnected {
        sid,
        text,
        off_requested,
        output_on,
    } = answer
    else {
        panic!("{answer:?}");
    };
    assert_eq!((sid, off_requested, output_on), (Some(1), true, None));
    assert!(
        text.as_deref()
            .is_some_and(|t| t.starts_with("link lost: ")),
        "{text:?}"
    );
}

/// Test: UT-APP-027
#[tokio::test(start_paused = true)]
async fn the_reading_a_switch_off_waited_for_is_a_witness() {
    let mut rig = Rig::new("UT-APP-027b", vec![output_off_script(None)]);
    let done = output_on_answered(&mut rig).await;
    sleep_until(after(done, ms(20))).await;
    let from = Instant::now();
    assert_eq!(
        disconnect(&mut rig, true).await,
        AppEvent::Disconnected {
            sid: Some(1),
            text: None,
            off_requested: true,
            output_on: Some(false)
        }
    );
    // No output-off `0xC8` (remoteCon 1, output 0) was needed.
    assert!(rig.c8s(0, from).iter().all(|p| shape(p) != (1, 0)));
}

/// Test: UT-APP-027
#[tokio::test(start_paused = true)]
async fn an_exit_right_after_an_output_on_drops_the_session() {
    crate::testkit::capture_log();
    let mut rig = Rig::new("UT-APP-027c", vec![output_off_script(None)]);
    let done = output_on_answered(&mut rig).await;
    sleep_until(after(done, ms(20))).await;
    let from = Instant::now();
    rig.drop_commands();
    rig.ended_within(Duration::from_secs(10)).await;
    sleep(Duration::from_secs(5)).await;
    assert!(rig.c8s(0, from).is_empty());
    assert!(!rig.marker_calls().contains(&MarkerCall::Clear));
    assert!(crate::testkit::logged_here(log::Level::Warn)
        .iter()
        .any(|l| l == texts::EXIT_WITHOUT_QUESTION));
}

/// Test: UT-APP-027
#[tokio::test(start_paused = true)]
async fn an_unasked_disconnect_with_the_output_on_drops_the_session() {
    crate::testkit::capture_log();
    let on = fixtures::c3_with(1, 0, 0, 1300, 1000);
    let mut rig = Rig::new("UT-APP-027d", vec![script(vec![c2_always(&on)])]);
    rig.connect().await;
    rig.grant().await;
    sleep(ms(300)).await;
    let from = Instant::now();
    let id = rig.id();
    rig.send(Command::DisconnectUnasked { id });
    let answer = rig
        .until(|e| matches!(e, AppEvent::Disconnected { .. }))
        .await
        .pop();
    assert_eq!(
        answer,
        Some(AppEvent::Disconnected {
            sid: Some(1),
            text: Some(texts::DISCONNECT_UNASKED.to_string()),
            off_requested: false,
            output_on: None
        })
    );
    sleep(Duration::from_secs(5)).await;
    assert_eq!(rig.frames(0, from), 0);
    // UT-APP-027 (d) also expects `closes()` at least 1. The core drops the
    // transport without `close()` when a session is dropped (`Link::drop`
    // aborts the link task), so the mock's close count cannot rise; this
    // part is reported, not asserted.
    assert!(!rig.marker_calls().contains(&MarkerCall::Clear));
    assert!(crate::testkit::logged_here(log::Level::Warn)
        .iter()
        .any(|l| l == texts::DISCONNECT_UNASKED));
}

/// Test: UT-APP-027
#[tokio::test(start_paused = true)]
async fn an_unasked_disconnect_with_the_output_confirmed_off_closes() {
    let mut rig = Rig::new("UT-APP-027e", vec![output_off_script(None)]);
    rig.connect().await;
    let ready = Instant::now();
    rig.grant().await;
    sleep_until(after(ready, ms(300))).await;
    let from = Instant::now();
    let id = rig.id();
    rig.send(Command::DisconnectUnasked { id });
    let answer = rig
        .until(|e| matches!(e, AppEvent::Disconnected { .. }))
        .await
        .pop();
    assert_eq!(
        answer,
        Some(AppEvent::Disconnected {
            sid: Some(1),
            text: None,
            off_requested: false,
            output_on: Some(false)
        })
    );
    let shapes: Vec<(u8, u8)> = rig.c8s(0, from).iter().map(|p| shape(p)).collect();
    assert_eq!(shapes, vec![(0, 0)]);
    assert_eq!(rig.mock(0).closes(), 1);
    assert!(rig.marker_calls().contains(&MarkerCall::Clear));
}

/// Test: UT-APP-027
#[tokio::test(start_paused = true)]
async fn an_unasked_disconnect_while_starting_closes() {
    let mut rig = Rig::new("UT-APP-027f", vec![unanswered_prompt_bind()]);
    let id = rig.id();
    rig.start = Instant::now();
    rig.send(Command::Connect {
        id,
        identifier: rig.identifier.clone(),
        reconnect: false,
        limits: limits(),
    });
    sleep(Duration::from_secs(1)).await;
    let calls_before = rig.marker_calls().len();
    let id = rig.id();
    rig.send(Command::DisconnectUnasked { id });
    let answer = rig
        .until(|e| matches!(e, AppEvent::Disconnected { .. }))
        .await
        .pop();
    assert_eq!(
        answer,
        Some(AppEvent::Disconnected {
            sid: Some(1),
            text: None,
            off_requested: false,
            output_on: None
        })
    );
    assert_eq!(rig.mock(0).closes(), 1);
    assert_eq!(rig.marker_calls().len(), calls_before);
}

/// Test: UT-APP-013
#[tokio::test(start_paused = true)]
async fn a_denied_connection_reports_and_frees_the_identifier() {
    let denied = script(vec![
        reply_n(0x18, ms(50), &[0xFF], 1),
        reply_n(0x18, Duration::from_secs(2), &[0xFF], 1),
    ]);
    let mut rig = Rig::new("UT-APP-013a", vec![denied]);
    let events = rig.connect().await;
    assert_eq!(
        events[0],
        AppEvent::Done {
            id: 1,
            what: What::Connect,
            result: Ok(())
        }
    );
    assert!(matches!(&events[1], AppEvent::Connecting { sid: 1, .. }));
    assert!(matches!(
        &events[2],
        AppEvent::Session {
            sid: 1,
            event: SessionEvent::Prompt {
                kind: PromptKind::ConfirmConnection,
                bound_s: 30,
                ..
            }
        }
    ));
    assert_eq!(
        events.last(),
        Some(&AppEvent::ConnectFailed {
            sid: 1,
            text: "the supply denied the connection".into()
        })
    );
    assert_eq!(events.len(), 4, "{events:?}");
    assert!(rig.mock(0).closes() >= 1);
    sleep(ms(10)).await;
    let events = rig.connect().await;
    assert_eq!(
        events[0],
        AppEvent::Done {
            id: 2,
            what: What::Connect,
            result: Ok(())
        }
    );
    assert!(matches!(&events[1], AppEvent::Connecting { sid: 2, .. }));
    assert!(matches!(
        events.last(),
        Some(AppEvent::Ready { sid: 2, .. })
    ));
}

/// Test: UT-APP-013
#[tokio::test(start_paused = true)]
async fn a_lost_link_is_reported_and_a_later_disconnect_answered() {
    let mut rig = Rig::new("UT-APP-013b", vec![closing_script(vec![])]);
    rig.connect().await;
    let events = rig
        .until(|e| {
            matches!(
                e,
                AppEvent::Session {
                    event: SessionEvent::LinkLost { .. },
                    ..
                }
            )
        })
        .await;
    assert!(events.contains(&AppEvent::Session {
        sid: 1,
        event: SessionEvent::RemoteControl(RemoteState::Lost)
    }));
    assert_eq!(
        loss_text(&events),
        Some(session::texts::link_lost(
            &LossReason::Disconnected,
            Kind::Ble
        ))
    );
    assert!(disconnected(&events).is_empty());
    sleep(Duration::from_secs(3)).await;
    assert!(matches!(
        rig.events.try_recv(),
        Err(mpsc::error::TryRecvError::Empty)
    ));
    let answer = disconnect(&mut rig, false).await;
    assert!(matches!(
        answer,
        AppEvent::Disconnected {
            sid: Some(1),
            text: None,
            off_requested: false,
            ..
        }
    ));
}

/// Test: UT-APP-013
#[tokio::test(start_paused = true)]
async fn a_connector_error_is_a_failed_connect() {
    let failing = MockConnector::new(|| {
        Err(Error::Transport {
            message: "no adapter".into(),
        })
    });
    let mut rig = Rig::with("UT-APP-013c", failing, MemoryMarkers::new(), scanner_f());
    let events = rig.connect().await;
    assert_eq!(
        events,
        vec![
            AppEvent::Done {
                id: 1,
                what: What::Connect,
                result: Ok(())
            },
            AppEvent::Connecting {
                sid: 1,
                identifier: "UT-APP-013c".into()
            },
            AppEvent::ConnectFailed {
                sid: 1,
                text: "transport: no adapter".into()
            },
        ]
    );
}

/// Test: UT-APP-013
#[tokio::test(start_paused = true)]
async fn a_second_session_to_one_supply_is_refused() {
    let other = Arc::new(connector("UT-APP-013d", vec![]));
    let (_session, _events) = session::Session::connect(
        other as Arc<dyn Connector>,
        "UT-APP-013d",
        host_id(),
        Arc::new(MemoryMarkers::new()) as Arc<dyn Markers>,
        Options::new(false, limits()),
    )
    .unwrap();
    let mut rig = Rig::new("UT-APP-013d", vec![]);
    let events = rig.connect().await;
    assert_eq!(
        events,
        vec![
            AppEvent::Done {
                id: 1,
                what: What::Connect,
                result: Ok(())
            },
            AppEvent::Connecting {
                sid: 1,
                identifier: "UT-APP-013d".into()
            },
            AppEvent::ConnectFailed {
                sid: 1,
                text: "a session to UT-APP-013d is already open in this process".into()
            },
        ]
    );
}

/// The recording events among `events`.
fn recording_events(events: &[AppEvent]) -> Vec<crate::worker::RecordingEvent> {
    events
        .iter()
        .filter_map(|e| match e {
            AppEvent::Recording(r) => Some(r.clone()),
            _ => None,
        })
        .collect()
}

/// Waits for the `Recording(Off ..)`, returning the events up to it.
async fn until_recording_off(rig: &mut Rig) -> Vec<AppEvent> {
    let wait = async {
        let mut out = Vec::new();
        while let Some(event) = rig.events.recv().await {
            let off = matches!(
                event,
                AppEvent::Recording(crate::worker::RecordingEvent::Off { .. })
            );
            out.push(event);
            if off {
                return out;
            }
        }
        panic!("the event channel closed: {out:?}");
    };
    real_bound(wait, REAL_BOUND).await
}

/// How long a wait on the recorder thread may take in real time.
const REAL_BOUND: Duration = Duration::from_secs(20);

/// Awaits `future`, failing after `bound` of real time. It makes no Tokio
/// timer, so the paused clock's auto-advance cannot end the wait while the
/// recorder, a thread outside the runtime, still works.
async fn real_bound<F: core::future::Future>(future: F, bound: Duration) -> F::Output {
    let (expired, expiry) = tokio::sync::oneshot::channel::<()>();
    let done = Arc::new(std::sync::atomic::AtomicBool::new(false));
    let watching = Arc::clone(&done);
    std::thread::spawn(move || {
        let deadline = std::time::Instant::now().checked_add(bound).unwrap();
        while std::time::Instant::now() < deadline {
            if watching.load(Ordering::SeqCst) {
                return;
            }
            std::thread::sleep(ms(5));
        }
        let _ = expired.send(());
    });
    tokio::pin!(future);
    tokio::select! {
        out = &mut future => {
            done.store(true, Ordering::SeqCst);
            out
        }
        Ok(()) = expiry => panic!("no result within {bound:?} of real time"),
    }
}

/// Test: UT-APP-014
#[tokio::test(start_paused = true)]
async fn a_recording_writes_the_rows_the_ui_sees() {
    use crate::worker::RecordingEvent;
    use mp305_core::csv;
    let dir = tempfile::tempdir().unwrap();
    let log = dir.path().join("log.csv");
    let mut rig = Rig::new("UT-APP-014", vec![]);
    let events = rig.connect().await;
    let origin = match events.last() {
        Some(AppEvent::Ready {
            reading: Some(r), ..
        }) => r.wall,
        other => panic!("{other:?}"),
    };
    // The reading of `Ready` is already on the reading channel.
    rig.readings.try_recv().unwrap();
    rig.send(Command::StartRecording {
        id: 1,
        path: log.clone(),
    });
    let mut collected = Vec::new();
    while collected.len() < 10 {
        collected.push(rig.readings.recv().await.unwrap().reading);
    }
    rig.send(Command::StopRecording { id: 2 });
    let events = until_recording_off(&mut rig).await;
    assert!(events.contains(&AppEvent::Done {
        id: 1,
        what: What::StartRecording,
        result: Ok(())
    }));
    assert!(events.contains(&AppEvent::Done {
        id: 2,
        what: What::StopRecording,
        result: Ok(())
    }));
    assert_eq!(
        recording_events(&events),
        vec![
            RecordingEvent::On { path: log.clone() },
            RecordingEvent::Progress { rows: 4 },
            RecordingEvent::Progress { rows: 8 },
            RecordingEvent::Off {
                path: log.clone(),
                rows: 10,
                error: None
            },
        ]
    );
    let mut expected = csv::header().to_string();
    for r in &collected {
        expected.push_str(&csv::format_row(r, origin));
    }
    let text = std::fs::read_to_string(&log).unwrap();
    assert_eq!(text, expected);
    let t_s: Vec<String> = text
        .lines()
        .skip(1)
        .map(|l| l.split(',').nth(1).unwrap().to_string())
        .collect();
    assert_eq!(t_s.first().map(String::as_str), Some("0.230"));
    assert_eq!(t_s.get(1).map(String::as_str), Some("0.460"));
    assert_eq!(t_s.last().map(String::as_str), Some("2.300"));

    rig.send(Command::StartRecording {
        id: 3,
        path: dir.path().join("b.csv"),
    });
    rig.send(Command::StartRecording {
        id: 4,
        path: dir.path().join("c.csv"),
    });
    assert_eq!(rig.done_of(3).await, Ok(()));
    assert_eq!(
        rig.done_of(4).await,
        Err(ErrorText::app("already recording"))
    );
    rig.send(Command::StopRecording { id: 5 });
    until_recording_off(&mut rig).await;

    for (id, path) in [
        (6, dir.path().join("missing").join("log.csv")),
        (7, log.clone()),
    ] {
        rig.send(Command::StartRecording { id, path });
        let events = until_recording_off(&mut rig).await;
        assert!(events.contains(&AppEvent::Done {
            id,
            what: What::StartRecording,
            result: Ok(())
        }));
        let recording = recording_events(&events);
        assert_eq!(recording.len(), 1, "{recording:?}");
        assert!(matches!(
            &recording[0],
            RecordingEvent::Off {
                rows: 0,
                error: Some(_),
                ..
            }
        ));
    }
    assert_eq!(std::fs::read_to_string(&log).unwrap(), expected);

    let d = dir.path().join("d.csv");
    while rig.readings.try_recv().is_ok() {}
    rig.send(Command::StartRecording {
        id: 8,
        path: d.clone(),
    });
    assert_eq!(rig.done_of(8).await, Ok(()));
    let mut forwarded = Vec::new();
    while forwarded.len() < 3 {
        forwarded.push(rig.readings.recv().await.unwrap().reading);
    }
    let from = Instant::now();
    rig.send(Command::Disconnect {
        id: 9,
        output_off: false,
    });
    let events = until_recording_off(&mut rig).await;
    while let Ok(r) = rig.readings.try_recv() {
        forwarded.push(r.reading);
    }
    let Some(RecordingEvent::Off { path, rows, error }) = recording_events(&events).pop() else {
        panic!("{events:?}");
    };
    assert_eq!((path, error), (d.clone(), None));
    let text = std::fs::read_to_string(&d).unwrap();
    assert_eq!(text.lines().count() as u64, rows + 1);
    let times: Vec<&str> = text
        .lines()
        .skip(1)
        .map(|l| l.split(',').next().unwrap())
        .collect();
    let rfc = |r: &crate::model::TimedReading| mp305_core::civil::rfc3339_millis_of(r.wall);
    let before: Vec<String> = forwarded.iter().filter(|r| r.at <= from).map(rfc).collect();
    let after: Vec<String> = forwarded.iter().filter(|r| r.at > from).map(rfc).collect();
    assert_eq!(times.last().copied(), before.last().map(String::as_str));
    assert!(
        after.iter().all(|t| !times.contains(&t.as_str())),
        "{after:?}"
    );
}

/// Test: UT-APP-014
#[tokio::test(start_paused = true)]
async fn a_recording_continues_across_a_reconnection() {
    use crate::worker::RecordingEvent;
    let dir = tempfile::tempdir().unwrap();
    let e = dir.path().join("e.csv");
    let mut rig = Rig::new("UT-APP-014e", vec![closing_script(vec![])]);
    let id = rig.id();
    rig.start = Instant::now();
    rig.send(Command::Connect {
        id,
        identifier: rig.identifier.clone(),
        reconnect: true,
        limits: limits(),
    });
    rig.until(|e| matches!(e, AppEvent::Ready { .. })).await;
    rig.send(Command::StartRecording {
        id: 20,
        path: e.clone(),
    });
    let mut across = rig
        .until(|e| {
            matches!(
                e,
                AppEvent::Session {
                    event: SessionEvent::LinkLost { .. },
                    ..
                }
            )
        })
        .await;
    let lost_at = Instant::now();
    across.extend(
        rig.until(|e| {
            matches!(
                e,
                AppEvent::Session {
                    event: SessionEvent::Reconnected,
                    ..
                }
            )
        })
        .await,
    );
    sleep(Duration::from_secs(2)).await;
    // The recording stays on across the loss.
    assert!(!recording_events(&across)
        .iter()
        .any(|r| matches!(r, RecordingEvent::Off { .. })));
    rig.send(Command::StopRecording { id: 21 });
    let events = until_recording_off(&mut rig).await;
    assert!(matches!(
        recording_events(&events).last(),
        Some(RecordingEvent::Off { error: None, .. })
    ));
    let text = std::fs::read_to_string(&e).unwrap();
    let t_s: Vec<f64> = text
        .lines()
        .skip(1)
        .map(|l| l.split(',').nth(1).unwrap().parse().unwrap())
        .collect();
    let lost_s = lost_at.saturating_duration_since(rig.start).as_secs_f64();
    let before: Vec<f64> = t_s.iter().copied().filter(|t| *t < lost_s).collect();
    let after: Vec<f64> = t_s.iter().copied().filter(|t| *t > lost_s + 5.0).collect();
    assert!(!before.is_empty() && !after.is_empty(), "{t_s:?}");
    assert!(after[0] > *before.last().unwrap());
    assert!(t_s.windows(2).all(|w| w[0] < w[1]), "{t_s:?}");
}

/// Test: UT-APP-014
#[tokio::test(start_paused = true)]
async fn an_exit_ends_the_recording_with_every_row() {
    let dir = tempfile::tempdir().unwrap();
    let f = dir.path().join("f.csv");
    let mut rig = Rig::new("UT-APP-014f", vec![]);
    rig.connect().await;
    rig.readings.try_recv().unwrap();
    rig.send(Command::StartRecording {
        id: 30,
        path: f.clone(),
    });
    let mut passed = Vec::new();
    while passed.len() < 6 {
        passed.push(rig.readings.recv().await.unwrap().reading);
    }
    let dropped_at = Instant::now();
    rig.drop_commands();
    // `run` returns after the recorder's `Ended`, which comes from a real
    // thread: a real-time bound, no timer on the paused clock.
    let worker = rig.worker.take().unwrap();
    real_bound(worker, REAL_BOUND).await.unwrap();
    // Every reading the worker forwarded before the exit went to the file;
    // the exit stops the recorder first.
    while let Ok(r) = rig.readings.try_recv() {
        passed.push(r.reading);
    }
    let written = passed.iter().filter(|r| r.at <= dropped_at).count();
    let text = std::fs::read_to_string(&f).unwrap();
    assert_eq!(text.lines().count(), written + 1);
    let events: Vec<AppEvent> = std::iter::from_fn(|| rig.events.try_recv().ok()).collect();
    assert!(matches!(
        recording_events(&events).last(),
        Some(crate::worker::RecordingEvent::Off { error: None, .. })
    ));
}

/// A gate the worker's wake blocks on while armed.
#[derive(Default)]
struct Gate {
    /// (armed, blocked).
    state: Mutex<(bool, bool)>,
    /// Signals changes of the state.
    changed: Condvar,
}

impl Gate {
    /// Blocks while armed, telling the test it is blocked.
    fn pass(&self) {
        let mut state = self.state.lock().unwrap();
        if state.0 {
            state.1 = true;
            self.changed.notify_all();
            while state.0 {
                state = self.changed.wait(state).unwrap();
            }
            state.1 = false;
        }
    }

    /// Arms the gate.
    fn arm(&self) {
        self.state.lock().unwrap().0 = true;
    }

    /// Waits until the worker is blocked in the gate.
    fn wait_blocked(&self) {
        let mut state = self.state.lock().unwrap();
        while !state.1 {
            state = self.changed.wait(state).unwrap();
        }
    }

    /// Opens the gate.
    fn open(&self) {
        self.state.lock().unwrap().0 = false;
        self.changed.notify_all();
    }
}

/// A worker on a multi-thread runtime with a gated wake.
struct GatedRig {
    /// The command channel.
    commands: mpsc::UnboundedSender<Command>,
    /// The event channel.
    events: mpsc::UnboundedReceiver<AppEvent>,
    /// The reading channel.
    readings: mpsc::Receiver<UiReading>,
    /// The connector.
    connector: Arc<MockConnector>,
    /// The markers.
    markers: Arc<MemoryMarkers>,
    /// The gate.
    gate: Arc<Gate>,
    /// The ids handed out so far.
    next_id: u64,
}

impl GatedRig {
    /// A worker whose attempts all follow the 5 ms script.
    fn new(identifier: &str) -> GatedRig {
        let id = identifier.to_string();
        let connector = Arc::new(MockConnector::new(move || {
            Ok(Mock::new(Kind::Ble, &id, fast_script(Vec::new())))
        }));
        let markers = Arc::new(MemoryMarkers::new());
        let (commands, command_rx) = mpsc::unbounded_channel();
        let (event_tx, events) = mpsc::unbounded_channel();
        let (reading_tx, readings) = mpsc::channel(super::READING_CAPACITY);
        let gate = Arc::new(Gate::default());
        let inner = Arc::clone(&gate);
        let wake: super::Wake = Arc::new(move || inner.pass());
        tokio::spawn(run(
            deps(&connector, &markers, scanner_f()),
            command_rx,
            UiSender::new(event_tx, reading_tx),
            wake,
        ));
        GatedRig {
            commands,
            events,
            readings,
            connector,
            markers,
            gate,
            next_id: 0,
        }
    }

    /// The next id.
    fn id(&mut self) -> u64 {
        self.next_id += 1;
        self.next_id
    }

    /// Events up to and including the first that `stop` accepts, failing
    /// after 10 s.
    async fn until(&mut self, stop: impl Fn(&AppEvent) -> bool) -> Vec<AppEvent> {
        let mut out = Vec::new();
        loop {
            let event = timeout(Duration::from_secs(10), self.events.recv())
                .await
                .expect("no event in time")
                .unwrap();
            let done = stop(&event);
            out.push(event);
            if done {
                return out;
            }
        }
    }

    /// Waits for the `Done` of `id`.
    async fn done_of(&mut self, id: u64) -> Result<(), ErrorText> {
        match self
            .until(|e| matches!(e, AppEvent::Done { id: i, .. } if *i == id))
            .await
            .pop()
        {
            Some(AppEvent::Done { result, .. }) => result,
            other => panic!("{other:?}"),
        }
    }

    /// Connects to `identifier` and waits for `Ready`.
    async fn connect(&mut self, identifier: &str) -> Vec<AppEvent> {
        let id = self.id();
        self.commands
            .send(Command::Connect {
                id,
                identifier: identifier.into(),
                reconnect: false,
                limits: limits(),
            })
            .unwrap();
        self.until(|e| matches!(e, AppEvent::Ready { .. } | AppEvent::ConnectFailed { .. }))
            .await
    }

    /// Arms the gate, waits until the worker blocks in it, sends
    /// `commands` and opens the gate.
    async fn send_while_blocked(&mut self, commands: Vec<Command>) {
        self.gate.arm();
        let gate = Arc::clone(&self.gate);
        tokio::task::spawn_blocking(move || gate.wait_blocked())
            .await
            .unwrap();
        for command in commands {
            self.commands.send(command).unwrap();
        }
        self.gate.open();
    }

    /// The `0xC8` payloads of the `n`th mock.
    fn c8s(&self, n: usize) -> Vec<Vec<u8>> {
        self.connector.handles()[n]
            .sent()
            .into_iter()
            .filter(|s| s.frame.opcode() == 0xC8)
            .map(|s| s.frame.payload().to_vec())
            .collect()
    }
}

/// Test: UT-APP-015
#[tokio::test(flavor = "multi_thread", worker_threads = 2)]
async fn an_output_off_never_follows_a_later_output_on() {
    let mut rig = GatedRig::new("UT-APP-015a");
    rig.connect("UT-APP-015a").await;
    let id = rig.id();
    rig.commands
        .send(Command::RequestRemoteControl { id })
        .unwrap();
    assert_eq!(rig.done_of(id).await, Ok(()));
    for round in 0..100 {
        let before = rig.c8s(0).len();
        let (on, off) = (rig.id(), rig.id());
        rig.send_while_blocked(vec![
            Command::OutputOn { id: on },
            Command::OutputOff { id: off },
        ])
        .await;
        let mut results = std::collections::BTreeMap::new();
        for _ in 0..2 {
            let event = rig
                .until(|e| matches!(e, AppEvent::Done { id: i, .. } if *i == on || *i == off))
                .await
                .pop();
            if let Some(AppEvent::Done { id, result, .. }) = event {
                results.insert(id, result);
            }
        }
        assert_eq!(results.get(&off), Some(&Ok(())), "round {round}");
        match results.get(&on) {
            Some(Ok(())) => {}
            Some(Err(e)) => assert_eq!(e.kind, ErrorKind::Cancelled, "round {round}: {e:?}"),
            None => panic!("round {round}: no Done for the output-on"),
        }
        let round_c8s: Vec<(u8, u8)> = rig.c8s(0)[before..].iter().map(|p| shape(p)).collect();
        let off_at = round_c8s
            .iter()
            .position(|s| s.1 == 0)
            .unwrap_or_else(|| panic!("round {round}: no output-off frame: {round_c8s:?}"));
        assert!(
            round_c8s[off_at..].iter().all(|s| s.1 == 0),
            "round {round}: {round_c8s:?}"
        );
    }
}

/// Test: UT-APP-015
#[tokio::test(flavor = "multi_thread", worker_threads = 2)]
async fn setpoints_reach_the_supply_in_the_order_sent() {
    let mut rig = GatedRig::new("UT-APP-015b");
    rig.connect("UT-APP-015b").await;
    let id = rig.id();
    rig.commands
        .send(Command::RequestRemoteControl { id })
        .unwrap();
    assert_eq!(rig.done_of(id).await, Ok(()));
    for round in 0..100 {
        let before = rig.c8s(0).len();
        let (five, three) = (rig.id(), rig.id());
        rig.send_while_blocked(vec![
            Command::SetVoltage {
                id: five,
                volts: 5.0,
            },
            Command::SetVoltage {
                id: three,
                volts: 3.0,
            },
        ])
        .await;
        rig.done_of(five).await.unwrap();
        rig.done_of(three).await.unwrap();
        let volts: Vec<u16> = rig.c8s(0)[before..]
            .iter()
            .map(|p| set_voltage(p))
            .collect();
        let at_500 = volts.iter().position(|v| *v == 500);
        let at_300 = volts.iter().position(|v| *v == 300);
        assert!(
            at_500.is_some() && at_300.is_some() && at_500 < at_300,
            "round {round}: {volts:?}"
        );
        assert_eq!(volts.last(), Some(&300), "round {round}");
    }
}

/// Test: UT-APP-015
#[tokio::test(flavor = "multi_thread", worker_threads = 2)]
async fn every_round_warns_before_ready_with_its_reading() {
    let mut rig = GatedRig::new("UT-APP-015c");
    for round in 0..100u64 {
        rig.markers
            .set("UT-APP-015c", crate::testkit::wall0())
            .unwrap();
        let events = rig.connect("UT-APP-015c").await;
        let sid = round + 1;
        let warning = events.iter().position(|e| {
            matches!(
                e,
                AppEvent::Session {
                    sid: s,
                    event: SessionEvent::UncleanExitWarning { .. }
                } if *s == sid
            )
        });
        let ready = events
            .iter()
            .position(|e| matches!(e, AppEvent::Ready { sid: s, .. } if *s == sid));
        assert!(
            warning.is_some() && ready.is_some() && warning < ready,
            "round {round}: {events:?}"
        );
        let mut held = false;
        while let Ok(reading) = rig.readings.try_recv() {
            held |= reading.sid == sid;
        }
        assert!(held, "round {round}");
        let id = rig.id();
        rig.commands
            .send(Command::Disconnect {
                id,
                output_off: false,
            })
            .unwrap();
        rig.until(|e| matches!(e, AppEvent::Disconnected { .. }))
            .await;
    }
}

/// Test: UT-APP-019
#[tokio::test(start_paused = true)]
async fn every_command_without_a_session_is_answered() {
    let mut rig = Rig::new("UT-APP-019a", vec![]);
    rig.send(Command::SetVoltage { id: 1, volts: 1.0 });
    rig.send(Command::SetLimits {
        id: 2,
        limits: limits(),
    });
    rig.send(Command::SetReconnect { id: 3, on: true });
    rig.send(Command::Disconnect {
        id: 4,
        output_off: false,
    });
    rig.send(Command::StartRecording {
        id: 5,
        path: "p".into(),
    });
    rig.send(Command::StopRecording { id: 6 });
    rig.send(Command::Reconnect {
        id: 7,
        reconnect: false,
        limits: Limits::none(),
    });
    let mut events = Vec::new();
    for _ in 0..7 {
        events.push(rig.event().await);
    }
    assert_eq!(
        events,
        vec![
            AppEvent::Done {
                id: 1,
                what: What::SetVoltage,
                result: Err(ErrorText {
                    text: "the session is not ready for control".into(),
                    kind: ErrorKind::NotReady
                })
            },
            AppEvent::Done {
                id: 2,
                what: What::SetLimits,
                result: Ok(())
            },
            AppEvent::Done {
                id: 3,
                what: What::SetReconnect,
                result: Ok(())
            },
            AppEvent::Disconnected {
                sid: None,
                text: None,
                off_requested: false,
                output_on: None
            },
            AppEvent::Done {
                id: 5,
                what: What::StartRecording,
                result: Err(ErrorText::app("not connected"))
            },
            AppEvent::Done {
                id: 6,
                what: What::StopRecording,
                result: Ok(())
            },
            AppEvent::Done {
                id: 7,
                what: What::Reconnect,
                result: Err(ErrorText::app("no connection to renew"))
            },
        ]
    );
}

/// Test: UT-APP-019
#[tokio::test(start_paused = true)]
async fn connect_and_limits_with_a_session() {
    let mut rig = Rig::new("UT-APP-019b", vec![]);
    rig.connect().await;
    rig.send(Command::Connect {
        id: 8,
        identifier: "UT-APP-019b".into(),
        reconnect: false,
        limits: limits(),
    });
    assert_eq!(
        rig.done_of(8).await,
        Err(ErrorText::app("a supply is already connected"))
    );
    rig.send(Command::SetLimits {
        id: 9,
        limits: Limits {
            max_volts: Some(5.0),
            max_amps: None,
        },
    });
    assert_eq!(rig.done_of(9).await, Ok(()));
    rig.send(Command::SetLimits {
        id: 10,
        limits: Limits {
            max_volts: Some(-1.0),
            max_amps: None,
        },
    });
    assert_eq!(
        rig.done_of(10).await.map_err(|e| e.kind),
        Err(ErrorKind::SetpointRange)
    );
}

/// Test: UT-APP-019
#[tokio::test(start_paused = true)]
async fn a_disconnect_while_starting_is_answered_once() {
    let mut rig = Rig::new("UT-APP-019c", vec![unanswered_prompt_bind()]);
    let id = rig.id();
    rig.start = Instant::now();
    rig.send(Command::Connect {
        id,
        identifier: rig.identifier.clone(),
        reconnect: false,
        limits: limits(),
    });
    sleep(Duration::from_secs(1)).await;
    rig.send(Command::Disconnect {
        id: 11,
        output_off: false,
    });
    let events = rig
        .until(|e| matches!(e, AppEvent::Disconnected { .. }))
        .await;
    assert!(events.iter().any(|e| matches!(
        e,
        AppEvent::Session {
            sid: 1,
            event: SessionEvent::Prompt {
                kind: PromptKind::ConfirmConnection,
                ..
            }
        }
    )));
    assert_eq!(
        events.last(),
        Some(&AppEvent::Disconnected {
            sid: Some(1),
            text: None,
            off_requested: false,
            output_on: None
        })
    );
    sleep(Duration::from_secs(60)).await;
    let later: Vec<AppEvent> = std::iter::from_fn(|| rig.events.try_recv().ok()).collect();
    let all: Vec<&AppEvent> = events.iter().chain(later.iter()).collect();
    assert!(!all
        .iter()
        .any(|e| matches!(e, AppEvent::ConnectFailed { .. } | AppEvent::Ready { .. })));
    assert!(rig.mock(0).closes() >= 1);
}

/// Test: UT-APP-019
#[tokio::test(start_paused = true)]
async fn a_reconnect_takes_the_limits_applied_during_its_close() {
    let mut rig = Rig::new("UT-APP-019d", vec![closing_script(vec![])]);
    rig.connect().await;
    until_lost(&mut rig).await;
    rig.send(Command::Reconnect {
        id: 12,
        reconnect: false,
        limits: Limits::none(),
    });
    rig.send(Command::SetLimits {
        id: 13,
        limits: Limits {
            max_volts: Some(5.0),
            max_amps: None,
        },
    });
    let events = rig.until(|e| matches!(e, AppEvent::Ready { .. })).await;
    let position = |pred: &dyn Fn(&AppEvent) -> bool| events.iter().position(pred);
    let done12 = position(&|e| {
        *e == AppEvent::Done {
            id: 12,
            what: What::Reconnect,
            result: Ok(()),
        }
    });
    let done13 = position(&|e| {
        *e == AppEvent::Done {
            id: 13,
            what: What::SetLimits,
            result: Ok(()),
        }
    });
    let connecting = position(&|e| {
        *e == AppEvent::Connecting {
            sid: 2,
            identifier: "UT-APP-019d".into(),
        }
    });
    assert!(done12 < done13 && done13 < connecting, "{events:?}");
    assert!(matches!(
        events.last(),
        Some(AppEvent::Ready { sid: 2, .. })
    ));
    assert!(disconnected(&events).is_empty());
    rig.send(Command::SetVoltage { id: 14, volts: 6.0 });
    assert_eq!(
        rig.done_of(14).await.map_err(|e| e.kind),
        Err(ErrorKind::SetpointRange)
    );
    assert!(rig.c8s(1, rig.start).is_empty());
}

/// Test: UT-APP-019
#[tokio::test(start_paused = true)]
async fn set_reconnect_reaches_the_open_session() {
    let mut rig = Rig::new("UT-APP-019e", vec![closing_script(vec![])]);
    rig.connect().await;
    rig.send(Command::SetReconnect { id: 15, on: true });
    assert_eq!(rig.done_of(15).await, Ok(()));
    let (_, lost_at) = until_lost(&mut rig).await;
    let events = rig
        .until(|e| {
            matches!(
                e,
                AppEvent::Session {
                    sid: 1,
                    event: SessionEvent::Reconnected
                }
            )
        })
        .await;
    assert_eq!(Instant::now().saturating_duration_since(lost_at), ms(5280));
    assert!(!events.iter().any(|e| matches!(e, AppEvent::Ready { .. })));
}

/// Test: UT-APP-019
#[tokio::test(start_paused = true)]
async fn a_disconnect_during_a_reconnects_close_cancels_the_connect() {
    let mut rig = Rig::new("UT-APP-019f", vec![closing_script(vec![])]);
    rig.connect().await;
    until_lost(&mut rig).await;
    rig.send(Command::Reconnect {
        id: 16,
        reconnect: false,
        limits: Limits::none(),
    });
    rig.send(Command::Disconnect {
        id: 17,
        output_off: false,
    });
    let events = rig
        .until(|e| matches!(e, AppEvent::Disconnected { .. }))
        .await;
    assert!(events.contains(&AppEvent::Done {
        id: 16,
        what: What::Reconnect,
        result: Ok(())
    }));
    assert_eq!(
        events.last(),
        Some(&AppEvent::Disconnected {
            sid: Some(1),
            text: None,
            off_requested: false,
            output_on: Some(false)
        })
    );
    sleep(Duration::from_secs(10)).await;
    let later: Vec<AppEvent> = std::iter::from_fn(|| rig.events.try_recv().ok()).collect();
    assert!(!events
        .iter()
        .chain(later.iter())
        .any(|e| matches!(e, AppEvent::Connecting { sid: 2, .. })));
    assert_eq!(rig.connector.handles().len(), 1);
}

/// Test: UT-APP-019
#[tokio::test(start_paused = true)]
async fn two_disconnects_get_one_answer() {
    let mut rig = Rig::new("UT-APP-019g", vec![]);
    rig.connect().await;
    rig.send(Command::Disconnect {
        id: 18,
        output_off: false,
    });
    rig.send(Command::Disconnect {
        id: 18,
        output_off: false,
    });
    let events = rig
        .until(|e| matches!(e, AppEvent::Disconnected { .. }))
        .await;
    assert!(matches!(
        events.last(),
        Some(AppEvent::Disconnected {
            sid: Some(1),
            text: None,
            off_requested: false,
            ..
        })
    ));
    sleep(Duration::from_secs(10)).await;
    let later: Vec<AppEvent> = std::iter::from_fn(|| rig.events.try_recv().ok()).collect();
    assert!(disconnected(&later).is_empty(), "{later:?}");
}
