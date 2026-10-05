//! Implements: nothing; the tests name their UT IDs.
//!
//! The task tests of `session` (session DD section 10), compiled under
//! `cfg(test)` as submodules of `session`. Every test runs on a paused Tokio
//! clock with `MockConnector` over scripts that answer by opcode; unless a
//! test says otherwise the script answers `0xE0` with `E1_BLE` after
//! 100 ms, `0xC2` with `C3_CAPTURE` after 130 ms, `0x18` with `19 00` after
//! 50 ms and `0xC8` with `0xC9 00` after 100 ms. Times are offsets from the
//! `connect` call, which is also the creation time of the first mock; "t0"
//! is 280 ms, when `ready()` resolves on the default script. Every test uses
//! its own identifier, since the registry is process-wide.

mod close;
mod connect;
mod control;
mod events;
mod loss;
mod robust;

use std::sync::atomic::{AtomicBool, AtomicU64, Ordering};
use std::sync::Arc;
use std::time::{SystemTime, UNIX_EPOCH};

use core::time::Duration;

use tokio::sync::{mpsc, oneshot, watch};
use tokio::task::JoinHandle;
use tokio::time::{sleep_until, Instant};

use crate::error::Error;
use crate::protocol::ble::{BleRoute, Route};
use crate::protocol::fixtures::{self, on_air, reply_route};
use crate::protocol::ops::bind::HostId;
use crate::protocol::units::Limits;
use crate::session::doubles::{MemoryMarkers, MockConnector};
use crate::session::task::{Setup, Task};
use crate::session::{
    Command, CommandKind, LinkState, Options, Priority, ReadyState, Registration, RemoteState,
    Session, SessionEvent, SessionEvents, Shared, Snapshot,
};
use crate::transport::description::Kind;
use crate::transport::mock::{Injection, Mock, MockHandle, Reply, Script};

/// When `ready()` resolves on the default script: fast bind 50 ms, info
/// 100 ms, first reading 130 ms.
const T0: Duration = Duration::from_millis(280);

/// The test wall origin, 2026-10-01T10:00:00Z.
fn wall0() -> SystemTime {
    UNIX_EPOCH + Duration::from_secs(1_790_848_800)
}

/// Milliseconds as a duration.
fn ms(n: u64) -> Duration {
    Duration::from_millis(n)
}

/// A reply to `request` with `payload` under the reply opcode, `after`
/// the request, forever, from the mock's creation.
fn reply(kind: Kind, request: u8, after: Duration, payload: &[u8]) -> Reply {
    let opcode = request.wrapping_add(1);
    Reply {
        request,
        after,
        route: reply_route(kind, opcode),
        deliveries: vec![on_air(kind, opcode, payload)],
        repeat: None,
        from: Duration::ZERO,
    }
}

/// An injection of a frame from the supply at `at` after the mock's
/// creation.
fn inject(kind: Kind, at: Duration, opcode: u8, payload: &[u8]) -> Injection {
    Injection {
        at,
        route: reply_route(kind, opcode),
        delivery: on_air(kind, opcode, payload),
    }
}

/// The default replies of section 10, with every opcode that `overrides`
/// answers taken out and `overrides` appended.
fn replies(kind: Kind, overrides: Vec<Reply>) -> Vec<Reply> {
    let e1: &[u8] = match kind {
        Kind::Ble => &fixtures::E1_BLE,
        Kind::Hid => &fixtures::E1_USB,
    };
    let defaults = vec![
        reply(kind, 0xE0, ms(100), e1),
        reply(kind, 0xC2, ms(130), &fixtures::C3_CAPTURE),
        reply(kind, 0x18, ms(50), &[0x00]),
        reply(kind, 0xC8, ms(100), &[0x00]),
    ];
    let mut out: Vec<Reply> = defaults
        .into_iter()
        .filter(|d| overrides.iter().all(|o| o.request != d.request))
        .collect();
    out.extend(overrides);
    out
}

/// A script with the default replies and `overrides`.
fn script(kind: Kind, overrides: Vec<Reply>) -> Script {
    Script {
        replies: replies(kind, overrides),
        ..Script::default()
    }
}

/// The options of section 10: no reconnection, limits 30 V and 5 A, the
/// test wall origin.
fn options() -> Options {
    Options::new(false, limits()).with_wall_origin(wall0())
}

/// The host ID of every test.
fn host_id() -> HostId {
    HostId::new([7; 16]).unwrap()
}

/// A started session with what a test needs to drive and observe it.
struct Rig {
    /// The handle, shared with the tasks that make calls.
    session: Arc<Session>,
    /// The events.
    events: SessionEvents,
    /// The connector, for the mock handles.
    connector: Arc<MockConnector>,
    /// The marker store.
    markers: Arc<MemoryMarkers>,
    /// The time of the `connect` call.
    start: Instant,
}

/// A session to `id` over one mock of `kind` following `script`.
fn start(id: &str, kind: Kind, script: Script) -> Rig {
    let id_owned = id.to_string();
    let mut script = Some(script);
    let connector = MockConnector::new(move || {
        Ok(Mock::new(
            kind,
            &id_owned,
            script.take().unwrap_or_default(),
        ))
    });
    start_with(id, connector, MemoryMarkers::new(), options())
}

/// A session to `id` over `connector` with `markers` and `options`.
fn start_with(id: &str, connector: MockConnector, markers: MemoryMarkers, options: Options) -> Rig {
    let connector = Arc::new(connector);
    let markers = Arc::new(markers);
    let start = Instant::now();
    let (session, events) = Session::connect(
        Arc::clone(&connector) as Arc<dyn crate::session::Connector>,
        id,
        host_id(),
        Arc::clone(&markers) as Arc<dyn crate::session::Markers>,
        options,
    )
    .unwrap();
    Rig {
        session: Arc::new(session),
        events,
        connector,
        markers,
        start,
    }
}

impl Rig {
    /// Sleeps until `d` after the `connect` call.
    async fn until(&self, d: Duration) {
        sleep_until(self.start + d).await;
    }

    /// The time since the `connect` call.
    fn now(&self) -> Duration {
        Instant::now() - self.start
    }

    /// The handle of the `n`th mock handed out.
    fn mock(&self, n: usize) -> MockHandle {
        self.connector.handles()[n].clone()
    }

    /// The sends of the first mock as (time since connect, opcode, payload).
    fn sent(&self) -> Vec<(Duration, u8, Vec<u8>)> {
        self.sent_of(0)
    }

    /// The sends of the `n`th mock as (time since connect, opcode, payload).
    fn sent_of(&self, n: usize) -> Vec<(Duration, u8, Vec<u8>)> {
        self.mock(n)
            .sent()
            .iter()
            .map(|s| {
                (
                    s.at - self.start,
                    s.frame.opcode(),
                    s.frame.payload().to_vec(),
                )
            })
            .collect()
    }

    /// The opcodes the first mock was sent, in order.
    fn opcodes(&self) -> Vec<u8> {
        self.sent().iter().map(|(_, op, _)| *op).collect()
    }

    /// The `0xC8` payloads the first mock was sent after `from`, with their
    /// times.
    fn c8s_after(&self, from: Duration) -> Vec<(Duration, Vec<u8>)> {
        self.sent()
            .into_iter()
            .filter(|(t, op, _)| *op == 0xC8 && *t >= from)
            .map(|(t, _, p)| (t, p))
            .collect()
    }

    /// Every event delivered so far, without waiting.
    fn drain(&mut self) -> Vec<SessionEvent> {
        std::iter::from_fn(|| self.events.try_next()).collect()
    }

    /// Every event delivered so far that is not a reading.
    fn drain_non_readings(&mut self) -> Vec<SessionEvent> {
        self.drain()
            .into_iter()
            .filter(|e| !matches!(e, SessionEvent::Reading(_)))
            .collect()
    }
}

/// The events a [`Recorder`] collected, with their delivery times since
/// the `connect` call.
type Recorded = Arc<std::sync::Mutex<Vec<(Duration, SessionEvent)>>>;

/// Collects every event as it is delivered, in a task.
struct Recorder {
    /// What arrived so far.
    seen: Recorded,
    /// The recording task; it ends when the events end.
    task: JoinHandle<()>,
}

impl Recorder {
    /// Every event so far.
    fn all(&self) -> Vec<(Duration, SessionEvent)> {
        self.seen.lock().unwrap().clone()
    }

    /// Every event so far that is not a reading.
    fn non_readings(&self) -> Vec<(Duration, SessionEvent)> {
        self.all()
            .into_iter()
            .filter(|(_, e)| !matches!(e, SessionEvent::Reading(_)))
            .collect()
    }

    /// Whether the events ended (`next()` yielded `None`).
    fn ended(&self) -> bool {
        self.task.is_finished()
    }

    /// The times of the readings so far.
    fn reading_times(&self) -> Vec<Duration> {
        self.all()
            .into_iter()
            .filter(|(_, e)| matches!(e, SessionEvent::Reading(_)))
            .map(|(t, _)| t)
            .collect()
    }
}

impl Rig {
    /// Moves the events into a task that records them as they arrive.
    fn record(&mut self) -> Recorder {
        let (_tx, events) = tokio::sync::mpsc::unbounded_channel();
        let (_rtx, readings) = tokio::sync::mpsc::channel(1);
        let mut taken = core::mem::replace(&mut self.events, SessionEvents { events, readings });
        let seen: Recorded = Arc::default();
        let (sink, start) = (Arc::clone(&seen), self.start);
        let task = tokio::spawn(async move {
            while let Some(event) = taken.next().await {
                sink.lock().unwrap().push((Instant::now() - start, event));
            }
        });
        Recorder { seen, task }
    }
}

impl Rig {
    /// Makes the call `f` at `at` after the `connect` call, in a task, and
    /// records when it returned (as time since the `connect` call).
    fn call_at<F, Fut>(&self, at: Duration, f: F) -> JoinHandle<(Duration, Result<(), Error>)>
    where
        F: FnOnce(Arc<Session>) -> Fut + Send + 'static,
        Fut: core::future::Future<Output = Result<(), Error>> + Send,
    {
        let (session, start) = (Arc::clone(&self.session), self.start);
        tokio::spawn(async move {
            sleep_until(start + at).await;
            let result = f(session).await;
            (Instant::now() - start, result)
        })
    }

    /// Waits until a reading that arrived after `t` (since the `connect`
    /// call) is the latest, and returns its arrival time.
    async fn reading_after(&self, t: Duration) -> Duration {
        loop {
            if let Some(r) = self.session.latest_reading() {
                if r.at - self.start > t {
                    return r.at - self.start;
                }
            }
            tokio::time::sleep(ms(1)).await;
        }
    }
}

/// The `n`th `0xC8` reply: `0xC9 status` after `after`, for one request,
/// eligible from `from` after the mock's creation.
fn c9_once(kind: Kind, status: u8, after: Duration, from: Duration) -> Reply {
    Reply {
        repeat: Some(1),
        from,
        ..reply(kind, 0xC8, after, &[status])
    }
}

/// The `0xC9 00` after 100 ms that answers every `0xC8` by default.
fn c9_ok(kind: Kind) -> Reply {
    reply(kind, 0xC8, ms(100), &[0x00])
}

/// A reply that answers one `0xC8` with nothing, from `from`.
fn c8_unanswered(from: Duration) -> Reply {
    Reply {
        request: 0xC8,
        deliveries: Vec::new(),
        repeat: Some(1),
        from,
        ..Reply::default()
    }
}

/// A reply to every `0xC2` with `payload` from `from` after the mock's
/// creation.
fn c3_from(kind: Kind, payload: &[u8], from: Duration) -> Reply {
    Reply {
        from,
        ..reply(kind, 0xC2, ms(130), payload)
    }
}

/// Whether the session logged a line at `level` starting with `prefix`
/// on this thread.
fn logged(log: &crate::transport::test_log::Log, level: log::Level, prefix: &str) -> bool {
    log.lines_here(crate::session::LOG_TARGET)
        .iter()
        .any(|(l, m)| *l == level && m.starts_with(prefix))
}

/// How many lines the session logged starting with `prefix` on this
/// thread.
fn count_logged(log: &crate::transport::test_log::Log, prefix: &str) -> usize {
    log.lines_here(crate::session::LOG_TARGET)
        .iter()
        .filter(|(_, m)| m.starts_with(prefix))
        .count()
}

/// A `0xC8` payload's `remoteCon` byte.
fn remote_con(payload: &[u8]) -> u8 {
    payload[0]
}

/// A `0xC8` payload's voltage and current setpoints, raw.
fn setpoints(payload: &[u8]) -> (u16, u16) {
    (
        u16::from_le_bytes([payload[1], payload[2]]),
        u16::from_le_bytes([payload[3], payload[4]]),
    )
}

/// A `0xC8` payload's `output` byte.
fn output(payload: &[u8]) -> u8 {
    payload[8]
}

/// The reasons of the two cancellations of DD-SESS-035.
fn cancelled(in_progress: bool) -> Error {
    Error::Cancelled {
        reason: if in_progress {
            "superseded by an output-off; it may have been applied".to_string()
        } else {
            "superseded by an output-off".to_string()
        },
    }
}

/// The `remoteCon` and `output` bytes of every `0xC8` in `c8s`.
fn shape(c8s: &[(Duration, Vec<u8>)]) -> Vec<(u8, u8)> {
    c8s.iter()
        .map(|(_, p)| (remote_con(p), output(p)))
        .collect()
}

/// Whether `events` hold a `Prompt`.
fn prompted(events: &[SessionEvent]) -> bool {
    events
        .iter()
        .any(|e| matches!(e, SessionEvent::Prompt { .. }))
}

/// The `SetpointsChanged` events among `events`.
fn setpoint_changes(events: &[SessionEvent]) -> Vec<SessionEvent> {
    events
        .iter()
        .filter(|e| matches!(e, SessionEvent::SetpointsChanged { .. }))
        .cloned()
        .collect()
}

/// The limits of section 10 as a command carries them.
fn limits() -> Limits {
    Limits {
        max_volts: Some(30.0),
        max_amps: Some(5.0),
    }
}

/// A session task the test drives one turn at a time (white-box), with the
/// channels a [`Session`] would hold. Used where a test must order what
/// the task sees, which the biased select of a spawned task fixes.
struct Driven {
    /// The task.
    task: Task,
    /// Control commands to the task.
    commands: mpsc::UnboundedSender<Command>,
    /// Output-off and close to the task.
    priority: mpsc::UnboundedSender<Priority>,
    /// What the queries read.
    shared: Arc<Shared>,
    /// The ready state.
    ready: watch::Receiver<ReadyState>,
    /// The events.
    events: SessionEvents,
    /// The connector, for the mock handles.
    connector: Arc<MockConnector>,
    /// The time the task was started.
    start: Instant,
}

/// A driven task to `id` over one mock of `kind` following `script`, its
/// connect flow started; no turn taken yet.
fn driven(id: &str, kind: Kind, script: Script) -> Driven {
    let id_owned = id.to_string();
    let mut script = Some(script);
    let connector = Arc::new(MockConnector::new(move || {
        Ok(Mock::new(
            kind,
            &id_owned,
            script.take().unwrap_or_default(),
        ))
    }));
    let (commands, command_rx) = mpsc::unbounded_channel();
    let (priority, priority_rx) = mpsc::unbounded_channel();
    let (event_tx, events) = mpsc::unbounded_channel();
    let (reading_tx, readings) = mpsc::channel(1024);
    let (ready_tx, ready) = watch::channel(ReadyState::Pending);
    let shared = Arc::new(Shared {
        snapshot: std::sync::Mutex::new(Snapshot {
            info: None,
            reading: None,
            link_state: LinkState::Connecting,
            remote_state: RemoteState::None,
            kind: None,
            counters: None,
        }),
        reconnect: AtomicBool::new(false),
        limits: std::sync::Mutex::new(limits()),
        generation: AtomicU64::new(1),
        dropped_readings: AtomicU64::new(0),
        close_result: std::sync::Mutex::new(None),
        trace: std::sync::Mutex::new(Vec::new()),
    });
    let start = Instant::now();
    let task = Task::started(Setup {
        connector: Arc::clone(&connector) as Arc<dyn crate::session::Connector>,
        identifier: id.to_string(),
        host_id: host_id(),
        markers: Arc::new(MemoryMarkers::new()),
        wall_origin: Some(wall0()),
        clock: None,
        shared: Arc::clone(&shared),
        ready: ready_tx,
        events: event_tx,
        readings: reading_tx,
        commands: command_rx,
        priority: priority_rx,
        registration: Registration::register(id).unwrap(),
    });
    Driven {
        task,
        commands,
        priority,
        shared,
        ready,
        events: SessionEvents { events, readings },
        connector,
        start,
    }
}

impl Driven {
    /// The link state.
    fn link_state(&self) -> LinkState {
        crate::session::lock(&self.shared.snapshot).link_state
    }

    /// The ready state.
    fn ready_state(&self) -> ReadyState {
        self.ready.borrow().clone()
    }

    /// Takes turns until the state is `Ready`.
    async fn until_ready(&mut self) {
        while self.link_state() != LinkState::Ready {
            self.task.turn().await;
        }
    }

    /// Sends a control command with the current generation.
    fn command(&self, kind: CommandKind) -> oneshot::Receiver<Result<(), Error>> {
        let (reply, rx) = oneshot::channel();
        let generation = self.shared.generation.load(Ordering::SeqCst);
        self.commands
            .send(Command {
                kind,
                limits: limits(),
                generation,
                reply,
            })
            .unwrap();
        rx
    }

    /// Sends an output-off on the priority channel.
    fn output_off(&self) -> oneshot::Receiver<Result<(), Error>> {
        let (reply, rx) = oneshot::channel();
        let generation = self.shared.generation.load(Ordering::SeqCst);
        self.priority
            .send(Priority::OutputOff { generation, reply })
            .unwrap();
        rx
    }

    /// Sends a close on the priority channel.
    fn close(&self, output_off: bool) -> oneshot::Receiver<Result<(), Error>> {
        let (reply, rx) = oneshot::channel();
        self.priority
            .send(Priority::Close { output_off, reply })
            .unwrap();
        rx
    }

    /// Lets the other tasks run, without a turn of the session task, until
    /// the first mock was sent a frame that `f` accepts.
    async fn until_sent(&self, f: impl Fn(&crate::transport::mock::Sent) -> bool) {
        while !self.connector.handles()[0].sent().iter().any(&f) {
            tokio::task::yield_now().await;
        }
    }

    /// Takes turns until `rx` is answered, and returns the answer and the
    /// time since the start.
    async fn drive(
        &mut self,
        rx: &mut oneshot::Receiver<Result<(), Error>>,
    ) -> (Duration, Result<(), Error>) {
        loop {
            tokio::select! {
                biased;
                answer = &mut *rx => return (Instant::now() - self.start, answer.unwrap()),
                () = self.task.turn() => {}
            }
        }
    }

    /// The `0xC8` payloads the first mock was sent, with their times since
    /// the start.
    fn c8s(&self) -> Vec<(Duration, Vec<u8>)> {
        self.connector.handles()[0]
            .sent()
            .iter()
            .filter(|s| s.frame.opcode() == 0xC8)
            .map(|s| (s.at - self.start, s.frame.payload().to_vec()))
            .collect()
    }
}

/// A ready session to `id` on Bluetooth that holds remote control: the
/// script answers the first `0xC8` (the request) with `0xC9 00` after
/// 100 ms like every other. Returns when the grant arrived.
async fn granted(id: &str, overrides: Vec<Reply>, injections: Vec<Injection>) -> Rig {
    granted_on(id, Kind::Ble, overrides, injections).await
}

/// As [`granted`], on `kind`.
async fn granted_on(
    id: &str,
    kind: Kind,
    overrides: Vec<Reply>,
    injections: Vec<Injection>,
) -> Rig {
    let mut script = script(kind, overrides);
    script.injections = injections;
    let rig = start(id, kind, script);
    rig.session.ready().await.unwrap();
    rig.session.request_remote_control().await.unwrap();
    assert_eq!(
        rig.session.remote_state(),
        crate::session::RemoteState::Granted
    );
    rig
}
