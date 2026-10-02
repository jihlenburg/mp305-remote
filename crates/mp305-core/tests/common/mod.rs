//! Shared support of the integration tests of `mp305-core`: the byte
//! fixtures with their capture citations, the scripted replies of the mock
//! transport, and a session rig over `MockConnector` and `MemoryMarkers`
//! whose events are recorded with their times on the paused Tokio clock.
//!
//! Implements: nothing; the tests that use it name their IT IDs.

// Every test binary uses its own part of this module.
#![allow(dead_code)]

use std::sync::{Arc, Mutex};
use std::time::{SystemTime, UNIX_EPOCH};

use core::future::Future;
use core::time::Duration;

use tokio::task::JoinHandle;
use tokio::time::{sleep, sleep_until, Instant};

use mp305_core::error::Error;
use mp305_core::link::{DeviceEvent, Link, Outcome, Requested};
use mp305_core::protocol::fixtures::{on_air, reply_route};
use mp305_core::protocol::frame::Frame;
use mp305_core::protocol::ops::bind::HostId;
use mp305_core::protocol::ops::control::{Command, RemoteCon};
use mp305_core::protocol::ops::telemetry::{self, RawReading};
use mp305_core::protocol::units::{Limits, RawVoltage};
use mp305_core::session::doubles::{MemoryMarkers, MockConnector};
use mp305_core::session::{Connector, Markers, Options, Session, SessionEvent, SessionEvents};
use mp305_core::transport::description::Kind;
use mp305_core::transport::guarded::Guarded;
use mp305_core::transport::mock::{Injection, Mock, MockHandle, Reply, Script};

/// The payload of the first `0xC3` of
/// `docs/research/captures/2026-09-29T193614-ble-readonly.jsonl`, event
/// t = 12.8857 (RX on AF01, `31 c3` and these 36 bytes): DC mode, output
/// off, no fault, setpoints 1300 (13.00 V) and 1000 (1.000 A), battery 90 %.
pub const C3_CAPTURE: [u8; 36] = [
    0x00, 0x00, 0x5A, 0x00, 0x00, 0x14, 0x05, 0x00, 0x00, 0xE8, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1A, 0x00, 0x00, 0x01,
    0x40, 0x06, 0x00, 0x00,
];

/// The payload of the `0xE1` of
/// `docs/research/captures/2026-09-29T193614-ble-readonly.jsonl`, event
/// t = 12.6162 (RX on AF02, `e1` and these 16 bytes): version 1.6.0.40,
/// model `MP305B`, hardware 2.0.2.0.
pub const E1_BLE: [u8; 16] = [
    0x01, 0x06, 0x00, 0x28, 0x4D, 0x50, 0x33, 0x30, 0x35, 0x42, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00,
];

/// A constructed fixture, never captured (TBD-010): the 30-byte USB layout
/// of `0xE1` from protocol.md 4.4 (31 bytes with the opcode), model
/// `MP305B`, eight placeholder bootloader bytes, version `01 06 00 33`
/// (1.6.0.51), name `MP305B`.
pub const E1_USB: [u8; 30] = [
    0x4D, 0x50, 0x33, 0x30, 0x35, 0x42, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x01, 0x06, 0x00, 0x33, 0x4D, 0x50, 0x33, 0x30, 0x35, 0x42, 0x00, 0x00, 0x00, 0x00,
];

/// The payload of the `0xC5` of
/// `docs/research/captures/2026-09-29T193614-ble-readonly.jsonl`, event
/// t = 12.7497 (RX on AF01, `31 c5` and these 11 bytes): charge limit 90 %,
/// volume 2, ramp step 500, OCP delay 50.
pub const C5_SETTINGS: [u8; 11] = [
    0x5A, 0x02, 0x00, 0x00, 0x01, 0xF4, 0x01, 0x32, 0x00, 0x00, 0x00,
];

/// When `ready()` resolves on the default script: fast bind 50 ms, info
/// 100 ms, first reading 130 ms.
pub const T0: Duration = Duration::from_millis(280);

/// Milliseconds as a duration.
#[must_use]
pub fn ms(n: u64) -> Duration {
    Duration::from_millis(n)
}

/// Seconds as a duration.
#[must_use]
pub fn secs(n: u64) -> Duration {
    Duration::from_secs(n)
}

/// A reply to `request` with `payload` under the reply opcode (`request`
/// plus one), on the route the supply answers on, `after` the request,
/// forever, eligible from the mock's creation.
#[must_use]
pub fn reply(kind: Kind, request: u8, after: Duration, payload: &[u8]) -> Reply {
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

/// As [`reply`], serving `repeat` requests (`None` forever) from `from`
/// after the mock's creation.
#[must_use]
pub fn reply_with(
    kind: Kind,
    request: u8,
    after: Duration,
    payload: &[u8],
    repeat: Option<usize>,
    from: Duration,
) -> Reply {
    Reply {
        repeat,
        from,
        ..reply(kind, request, after, payload)
    }
}

/// A reply that answers `repeat` requests for `request` with nothing, from
/// `from` after the mock's creation.
#[must_use]
pub fn silent(request: u8, repeat: Option<usize>, from: Duration) -> Reply {
    Reply {
        request,
        deliveries: Vec::new(),
        repeat,
        from,
        ..Reply::default()
    }
}

/// A frame from the supply with `opcode` and `payload`, delivered at `at`
/// after the mock's creation regardless of requests.
#[must_use]
pub fn inject(kind: Kind, at: Duration, opcode: u8, payload: &[u8]) -> Injection {
    Injection {
        at,
        route: reply_route(kind, opcode),
        delivery: on_air(kind, opcode, payload),
    }
}

/// The default replies: `0xE0` with the `0xE1` of the kind after 100 ms,
/// `0xC2` with [`C3_CAPTURE`] after 130 ms, `0x18` with `19 00` after
/// 50 ms, `0xC8` with `0xC9 00` after 100 ms; every opcode that
/// `overrides` answers is taken out and `overrides` appended.
#[must_use]
pub fn replies(kind: Kind, overrides: Vec<Reply>) -> Vec<Reply> {
    let e1: &[u8] = match kind {
        Kind::Ble => &E1_BLE,
        Kind::Hid => &E1_USB,
    };
    let defaults = vec![
        reply(kind, 0xE0, ms(100), e1),
        reply(kind, 0xC2, ms(130), &C3_CAPTURE),
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
#[must_use]
pub fn script(kind: Kind, overrides: Vec<Reply>) -> Script {
    Script {
        replies: replies(kind, overrides),
        ..Script::default()
    }
}

/// The wall-clock origin of every session, 2026-10-01T10:00:00Z.
#[must_use]
pub fn wall0() -> SystemTime {
    UNIX_EPOCH + Duration::from_secs(1_790_848_800)
}

/// The host ID the sessions present, unless a test takes one from a store.
#[must_use]
pub fn host_id() -> HostId {
    HostId::new([7; 16]).unwrap()
}

/// The options of every session: reconnection as given, no user limits,
/// the fixed wall origin.
#[must_use]
pub fn options(reconnect: bool) -> Options {
    Options::new(reconnect, Limits::none()).with_wall_origin(wall0())
}

/// The events a [`Recorder`] collected, with their delivery times since
/// the `connect` call.
pub type Recorded = Arc<Mutex<Vec<(Duration, SessionEvent)>>>;

/// Collects every session event as it is delivered, in a task.
pub struct Recorder {
    /// What arrived so far.
    seen: Recorded,
    /// The recording task; it ends when the events end.
    task: JoinHandle<()>,
}

impl Recorder {
    /// Moves `events` into a task that records each event with its delivery
    /// time since `start`.
    #[must_use]
    pub fn new(mut events: SessionEvents, start: Instant) -> Self {
        let seen: Recorded = Arc::default();
        let sink = Arc::clone(&seen);
        let task = tokio::spawn(async move {
            while let Some(event) = events.next().await {
                sink.lock().unwrap().push((Instant::now() - start, event));
            }
        });
        Self { seen, task }
    }

    /// Every event so far, with its time.
    #[must_use]
    pub fn all(&self) -> Vec<(Duration, SessionEvent)> {
        self.seen.lock().unwrap().clone()
    }

    /// Every event so far that is not a reading, with its time.
    #[must_use]
    pub fn non_readings(&self) -> Vec<(Duration, SessionEvent)> {
        self.all()
            .into_iter()
            .filter(|(_, e)| !matches!(e, SessionEvent::Reading(_)))
            .collect()
    }

    /// Every event so far that is not a reading, without its time.
    #[must_use]
    pub fn non_reading_events(&self) -> Vec<SessionEvent> {
        self.non_readings().into_iter().map(|(_, e)| e).collect()
    }

    /// The arrival stamps of the readings so far, as times since `start`.
    #[must_use]
    pub fn reading_times(&self, start: Instant) -> Vec<Duration> {
        self.all()
            .into_iter()
            .filter_map(|(_, e)| match e {
                SessionEvent::Reading(r) => Some(r.at - start),
                _ => None,
            })
            .collect()
    }

    /// The delivery time of the first event matching `f`.
    #[must_use]
    pub fn time_of(&self, f: impl Fn(&SessionEvent) -> bool) -> Option<Duration> {
        self.all().into_iter().find(|(_, e)| f(e)).map(|(t, _)| t)
    }

    /// Whether the events ended (`next()` yielded `None`).
    #[must_use]
    pub fn ended(&self) -> bool {
        self.task.is_finished()
    }
}

/// A connector whose attempts come from `attempts` in order, the last one
/// repeating, recording the clock time of every call.
#[must_use]
pub fn scripted_connector(
    attempts: Vec<Box<dyn Fn() -> Result<Mock, Error> + Send>>,
) -> (MockConnector, Arc<Mutex<Vec<Instant>>>) {
    let calls: Arc<Mutex<Vec<Instant>>> = Arc::default();
    let log = Arc::clone(&calls);
    let mut n = 0usize;
    let connector = MockConnector::new(move || {
        log.lock().unwrap().push(Instant::now());
        let attempt = &attempts[n.min(attempts.len() - 1)];
        n += 1;
        attempt()
    });
    (connector, calls)
}

/// A connector that hands out one mock of `kind` named `id` following
/// `script`, and a mock without a script for any later attempt.
#[must_use]
pub fn one_mock(id: &str, kind: Kind, script: Script) -> MockConnector {
    let id = id.to_string();
    let mut script = Some(script);
    MockConnector::new(move || Ok(Mock::new(kind, &id, script.take().unwrap_or_default())))
}

/// A started session with what a test needs to drive and observe it.
pub struct Rig {
    /// The handle, shared with the tasks that make calls.
    pub session: Arc<Session>,
    /// The recorded events.
    pub events: Recorder,
    /// The connector, for the mock handles.
    pub connector: Arc<MockConnector>,
    /// The marker store.
    pub markers: Arc<MemoryMarkers>,
    /// The time of the `connect` call.
    pub start: Instant,
}

/// A session to `id` over one mock of `kind` following `script`, with an
/// empty marker store and reconnection off.
#[must_use]
pub fn start(id: &str, kind: Kind, script: Script) -> Rig {
    start_with(
        id,
        one_mock(id, kind, script),
        MemoryMarkers::new(),
        options(false),
        host_id(),
    )
}

/// A session to `id` over `connector` with `markers`, `options` and
/// `host_id`.
#[must_use]
pub fn start_with(
    id: &str,
    connector: MockConnector,
    markers: MemoryMarkers,
    options: Options,
    host_id: HostId,
) -> Rig {
    let connector = Arc::new(connector);
    let markers = Arc::new(markers);
    let start = Instant::now();
    let (session, events) = Session::connect(
        Arc::clone(&connector) as Arc<dyn Connector>,
        id,
        host_id,
        Arc::clone(&markers) as Arc<dyn Markers>,
        options,
    )
    .unwrap();
    Rig {
        session: Arc::new(session),
        events: Recorder::new(events, start),
        connector,
        markers,
        start,
    }
}

impl Rig {
    /// Sleeps until `d` after the `connect` call.
    pub async fn until(&self, d: Duration) {
        sleep_until(self.start + d).await;
    }

    /// The time since the `connect` call.
    #[must_use]
    pub fn now(&self) -> Duration {
        Instant::now() - self.start
    }

    /// The handle of the `n`th mock handed out.
    #[must_use]
    pub fn mock(&self, n: usize) -> MockHandle {
        self.connector.handles()[n].clone()
    }

    /// The number of mocks handed out so far.
    #[must_use]
    pub fn mocks(&self) -> usize {
        self.connector.handles().len()
    }

    /// The sends of the `n`th mock as (time since connect, opcode, payload).
    #[must_use]
    pub fn sent_of(&self, n: usize) -> Vec<(Duration, u8, Vec<u8>)> {
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

    /// The sends of the first mock as (time since connect, opcode, payload).
    #[must_use]
    pub fn sent(&self) -> Vec<(Duration, u8, Vec<u8>)> {
        self.sent_of(0)
    }

    /// The opcodes the first mock was sent, in order.
    #[must_use]
    pub fn opcodes(&self) -> Vec<u8> {
        self.sent().iter().map(|(_, op, _)| *op).collect()
    }

    /// The `0xC8` payloads the first mock was sent at or after `from`, with
    /// their times.
    #[must_use]
    pub fn c8s_after(&self, from: Duration) -> Vec<(Duration, Vec<u8>)> {
        self.sent()
            .into_iter()
            .filter(|(t, op, _)| *op == 0xC8 && *t >= from)
            .map(|(t, _, p)| (t, p))
            .collect()
    }

    /// The write times of the `0xC2`s the first mock was sent.
    #[must_use]
    pub fn c2_times(&self) -> Vec<Duration> {
        self.sent()
            .into_iter()
            .filter(|(_, op, _)| *op == 0xC2)
            .map(|(t, _, _)| t)
            .collect()
    }

    /// Makes the call `f` at `at` after the `connect` call, in a task, and
    /// records when it returned (as time since the `connect` call).
    pub fn call_at<F, Fut>(&self, at: Duration, f: F) -> JoinHandle<(Duration, Result<(), Error>)>
    where
        F: FnOnce(Arc<Session>) -> Fut + Send + 'static,
        Fut: Future<Output = Result<(), Error>> + Send,
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
    pub async fn reading_after(&self, t: Duration) -> Duration {
        loop {
            if let Some(r) = self.session.latest_reading() {
                if r.at - self.start > t {
                    return r.at - self.start;
                }
            }
            sleep(ms(1)).await;
        }
    }
}

/// A link started on one mock, with the mock's handle and the link's events
/// recorded with their delivery times.
pub struct LinkRig {
    /// The link's handle.
    pub link: Link,
    /// The link's events as (time since `start`, event).
    pub events: Arc<Mutex<Vec<(Duration, DeviceEvent)>>>,
    /// The recording task; it ends after the last event.
    pub recorder: JoinHandle<()>,
    /// What the mock was sent.
    pub mock: MockHandle,
    /// The creation of the mock and the guard, also `connected_at`.
    pub start: Instant,
}

/// A link on a mock of `kind` named `id` following `script`.
#[must_use]
pub fn link_rig(kind: Kind, id: &str, script: Script) -> LinkRig {
    let start = Instant::now();
    let mock = Mock::new(kind, id, script);
    let handle = mock.handle();
    let (link, mut events) = Link::start(Guarded::new(mock), start).unwrap();
    let seen: Arc<Mutex<Vec<(Duration, DeviceEvent)>>> = Arc::default();
    let sink = Arc::clone(&seen);
    let recorder = tokio::spawn(async move {
        while let Some(event) = events.next().await {
            sink.lock().unwrap().push((Instant::now() - start, event));
        }
    });
    LinkRig {
        link,
        events: seen,
        recorder,
        mock: handle,
        start,
    }
}

impl LinkRig {
    /// Sleeps until `d` after the start.
    pub async fn until(&self, d: Duration) {
        sleep_until(self.start + d).await;
    }

    /// The time since the start.
    #[must_use]
    pub fn now(&self) -> Duration {
        Instant::now() - self.start
    }

    /// The events so far.
    #[must_use]
    pub fn events(&self) -> Vec<(Duration, DeviceEvent)> {
        self.events.lock().unwrap().clone()
    }

    /// The arrival stamps of the readings so far, as times since the start.
    #[must_use]
    pub fn reading_times(&self) -> Vec<Duration> {
        self.events()
            .into_iter()
            .filter_map(|(_, e)| match e {
                DeviceEvent::Reading { at, .. } => Some(at - self.start),
                _ => None,
            })
            .collect()
    }

    /// The sends so far as (time since the start, opcode, payload).
    #[must_use]
    pub fn sent(&self) -> Vec<(Duration, u8, Vec<u8>)> {
        self.mock
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

    /// The write times of the sends with `opcode`.
    #[must_use]
    pub fn sent_times(&self, opcode: u8) -> Vec<Duration> {
        self.sent()
            .into_iter()
            .filter(|(_, op, _)| *op == opcode)
            .map(|(t, _, _)| t)
            .collect()
    }
}

/// Awaits `request` in a task and returns when it resolved (as time since
/// `start`) with its result.
pub fn track(request: Requested, start: Instant) -> JoinHandle<(Duration, Result<Outcome, Error>)> {
    tokio::spawn(async move {
        let result = request.await;
        (Instant::now() - start, result)
    })
}

/// The raw reading of [`C3_CAPTURE`].
#[must_use]
pub fn capture_reading() -> RawReading {
    telemetry::parse_payload(&C3_CAPTURE).unwrap()
}

/// A `0xC8` copied from [`C3_CAPTURE`] with `remote_con`, as the session
/// builds it.
#[must_use]
pub fn c8(remote_con: RemoteCon) -> Frame {
    Command::from_reading(&capture_reading())
        .unwrap()
        .remote_con(remote_con)
        .encode()
}

/// A `0xC8` copied from [`C3_CAPTURE`] with `remoteCon` 1 and the voltage
/// setpoint `volts`, as `set_voltage` builds it.
#[must_use]
pub fn c8_volts(volts: f64) -> Frame {
    Command::from_reading(&capture_reading())
        .unwrap()
        .set_voltage(RawVoltage::from_volts(volts, &Limits::none()).unwrap())
        .encode()
}

/// A ready session to `id` over one mock of `kind` following `script` that
/// holds remote control: the script must answer the first `0xC8` (the
/// request) with `0xC9 00`. Returns when the grant arrived.
pub async fn granted(id: &str, kind: Kind, script: Script) -> Rig {
    let rig = start(id, kind, script);
    rig.session.ready().await.unwrap();
    rig.session.request_remote_control().await.unwrap();
    assert_eq!(
        rig.session.remote_state(),
        mp305_core::session::RemoteState::Granted
    );
    rig
}

/// Awaits `f` and returns the time it resolved (since `start`) with its
/// output.
pub async fn timed<F: Future>(start: Instant, f: F) -> (Duration, F::Output) {
    let output = f.await;
    (Instant::now() - start, output)
}

/// A `0xC8` payload's `remoteCon` byte.
#[must_use]
pub fn remote_con(payload: &[u8]) -> u8 {
    payload[0]
}

/// A `0xC8` payload's voltage and current setpoints, raw.
#[must_use]
pub fn setpoints(payload: &[u8]) -> (u16, u16) {
    (
        u16::from_le_bytes([payload[1], payload[2]]),
        u16::from_le_bytes([payload[3], payload[4]]),
    )
}

/// A `0xC8` payload's `output` byte.
#[must_use]
pub fn output(payload: &[u8]) -> u8 {
    payload[8]
}

/// The `remoteCon` and `output` bytes of every `0xC8` in `c8s`.
#[must_use]
pub fn shape(c8s: &[(Duration, Vec<u8>)]) -> Vec<(u8, u8)> {
    c8s.iter()
        .map(|(_, p)| (remote_con(p), output(p)))
        .collect()
}
