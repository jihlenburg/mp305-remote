//! Implements: nothing; holds the tests of UT-SESS-066 to UT-SESS-069.
//!
//! Task tests: the wait for the marker store at a close, the re-anchoring
//! of the reading times after a system sleep, reconnection through
//! `Connector::reconnect`, and the fixed marker key over USB.

use std::sync::atomic::AtomicU64;
use std::sync::Mutex;

use futures::future::BoxFuture;
use log::Level;

use super::*;
use crate::session::doubles::MarkerCall;
use crate::session::{texts, Connector, Markers, USB_MARKER_KEY};
use crate::store::names;
use crate::transport::guarded::Guarded;
use crate::transport::test_log;
use crate::transport::AnyTransport;

/// A marker store that records every call, `flush` included, and answers
/// `flush` with a fixed result.
struct FlushMarkers {
    /// The calls in order: `present`, `set`, `clear`, `flush <bound>`.
    calls: Mutex<Vec<String>>,
    /// What `flush` returns.
    result: bool,
}

impl FlushMarkers {
    /// A store whose `flush` returns `result`.
    fn new(result: bool) -> Self {
        Self {
            calls: Mutex::new(Vec::new()),
            result,
        }
    }

    /// The calls so far.
    fn calls(&self) -> Vec<String> {
        self.calls.lock().unwrap().clone()
    }
}

impl Markers for FlushMarkers {
    fn present(&self, _: &str) -> Result<Option<SystemTime>, Error> {
        self.calls.lock().unwrap().push("present".to_string());
        Ok(None)
    }

    fn set(&self, _: &str, _: SystemTime) -> Result<(), Error> {
        self.calls.lock().unwrap().push("set".to_string());
        Ok(())
    }

    fn clear(&self, _: &str) -> Result<(), Error> {
        self.calls.lock().unwrap().push("clear".to_string());
        Ok(())
    }

    fn flush(&self, bound: Duration) -> bool {
        self.calls
            .lock()
            .unwrap()
            .push(format!("flush {}", bound.as_secs()));
        self.result
    }
}

/// A ready Bluetooth session to `id` over the default script with
/// `markers`, and its mock connector.
async fn ready_with(
    id: &'static str,
    markers: Arc<dyn Markers>,
) -> (Session, SessionEvents, Arc<MockConnector>) {
    let connector = Arc::new(MockConnector::new(move || {
        Ok(Mock::new(Kind::Ble, id, script(Kind::Ble, vec![])))
    }));
    let (session, events) = Session::connect(
        Arc::clone(&connector) as Arc<dyn Connector>,
        id,
        host_id(),
        markers,
        options(),
    )
    .unwrap();
    session.ready().await.unwrap();
    (session, events, connector)
}

/// Test: UT-SESS-066
///
/// An orderly close waits for the marker store after its final clear,
/// with the bound `timing::CLOSE` (5 s), and returns its result.
#[tokio::test(start_paused = true)]
async fn the_close_waits_for_the_marker_store_after_the_final_clear() {
    let log = test_log::install();
    let markers = Arc::new(FlushMarkers::new(true));
    let (session, _events, connector) =
        ready_with("UT-SESS-066", Arc::clone(&markers) as Arc<dyn Markers>).await;
    assert_eq!(session.close(false).await, Ok(()));
    assert_eq!(markers.calls(), vec!["present", "clear", "flush 5"]);
    assert_eq!(connector.handles()[0].closes(), 1);
    assert_eq!(session.link_state(), LinkState::Closed);
    assert!(!logged(&log, Level::Warn, "close: the marker store"));
}

/// Test: UT-SESS-066
///
/// When the store has not finished within the bound, the close logs a
/// WARN and goes on to its end; its result is unchanged.
#[tokio::test(start_paused = true)]
async fn the_close_goes_on_when_the_marker_store_is_late() {
    let log = test_log::install();
    let markers = Arc::new(FlushMarkers::new(false));
    let (session, _events, connector) =
        ready_with("UT-SESS-066-late", Arc::clone(&markers) as Arc<dyn Markers>).await;
    assert_eq!(session.close(true).await, Ok(()));
    assert_eq!(markers.calls().last().map(String::as_str), Some("flush 5"));
    assert_eq!(connector.handles()[0].closes(), 1);
    assert_eq!(session.link_state(), LinkState::Closed);
    assert!(logged(
        &log,
        Level::Warn,
        "close: the marker store did not finish writing within 5.0 s"
    ));
}

/// Test: UT-SESS-066
///
/// A close before the session was ever ready clears nothing but still
/// waits for the store, so that earlier writes are on disk.
#[tokio::test(start_paused = true)]
async fn a_close_before_ready_still_waits_for_the_marker_store() {
    let markers = Arc::new(FlushMarkers::new(true));
    let connector = Arc::new(MockConnector::new(|| {
        Err(Error::Transport {
            message: "no adapter".to_string(),
        })
    }));
    let (session, _events) = Session::connect(
        connector as Arc<dyn Connector>,
        "UT-SESS-066-early",
        host_id(),
        Arc::clone(&markers) as Arc<dyn Markers>,
        options(),
    )
    .unwrap();
    assert!(session.ready().await.is_err());
    assert_eq!(session.close(true).await, Ok(()));
    assert_eq!(markers.calls(), vec!["flush 5"]);
}

/// The test system clock of UT-SESS-067: [`wall0`] plus this many seconds.
static AHEAD_S: AtomicU64 = AtomicU64::new(0);

/// The injected system clock of UT-SESS-067. It stands still apart from
/// the jumps the test makes, so it is never ahead of the computed time
/// unless the test moved it.
fn sleepy_clock() -> SystemTime {
    wall0() + Duration::from_secs(AHEAD_S.load(Ordering::SeqCst))
}

/// Test: UT-SESS-067
///
/// With an injected clock: no re-anchoring while the system clock is not
/// ahead; after the system clock jumped an hour ahead (a system sleep the
/// Tokio clock did not see) the next reading carries the system time,
/// later ones follow on from it, and an INFO line says how far it moved;
/// a system clock set back again moves nothing back.
#[tokio::test(start_paused = true)]
async fn reading_times_follow_the_system_clock_after_a_sleep() {
    let log = test_log::install();
    let connector = MockConnector::new(|| {
        Ok(Mock::new(
            Kind::Ble,
            "UT-SESS-067",
            script(Kind::Ble, vec![]),
        ))
    });
    let mut rig = start_with(
        "UT-SESS-067",
        connector,
        MemoryMarkers::new(),
        options().with_clock(sleepy_clock),
    );
    rig.session.ready().await.unwrap();
    rig.until(T0 + ms(1_000)).await;
    let before = rig.session.latest_reading().unwrap();
    assert_eq!(before.wall, wall0() + (before.at - rig.start));
    assert!(!logged(&log, Level::Info, "reading times re-anchored"));

    AHEAD_S.store(3_600, Ordering::SeqCst);
    // The next reading is the first one after the jump; `reading_after`
    // returns as soon as it is the latest.
    rig.reading_after(rig.now()).await;
    let first = rig.session.latest_reading().unwrap();
    assert_eq!(first.wall, wall0() + Duration::from_secs(3_600));
    assert_eq!(count_logged(&log, "reading times re-anchored"), 1);
    assert!(logged(
        &log,
        Level::Info,
        "reading times re-anchored: the system clock ran "
    ));

    AHEAD_S.store(0, Ordering::SeqCst);
    rig.until(rig.now() + ms(1_000)).await;
    let later = rig.session.latest_reading().unwrap();
    assert!(later.at > first.at);
    assert_eq!(later.wall, first.wall + (later.at - first.at));
    assert_eq!(count_logged(&log, "reading times re-anchored"), 1);
    let _ = rig.drain();
}

/// Test: UT-SESS-067
///
/// A small lead of the system clock (within the 2 s threshold) is left
/// alone.
#[tokio::test(start_paused = true)]
async fn a_small_lead_of_the_system_clock_is_left_alone() {
    /// Two seconds ahead of the computed time at the first reading.
    fn near_clock() -> SystemTime {
        wall0() + T0 + Duration::from_secs(2)
    }
    let log = test_log::install();
    let connector = MockConnector::new(|| {
        Ok(Mock::new(
            Kind::Ble,
            "UT-SESS-067-small",
            script(Kind::Ble, vec![]),
        ))
    });
    let rig = start_with(
        "UT-SESS-067-small",
        connector,
        MemoryMarkers::new(),
        options().with_clock(near_clock),
    );
    rig.session.ready().await.unwrap();
    rig.until(T0 + ms(500)).await;
    let reading = rig.session.latest_reading().unwrap();
    assert_eq!(reading.wall, wall0() + (reading.at - rig.start));
    assert!(!logged(&log, Level::Info, "reading times re-anchored"));
}

/// A connector that records which trait method the session called, with
/// the identifier, and hands out the mocks of `inner` either way.
struct Recording {
    /// The mocks.
    inner: MockConnector,
    /// `("connect" or "reconnect", identifier)`, in order.
    calls: Mutex<Vec<(&'static str, String)>>,
}

impl Connector for Recording {
    fn connect<'a>(
        &'a self,
        identifier: &'a str,
    ) -> BoxFuture<'a, Result<Guarded<AnyTransport>, Error>> {
        self.calls
            .lock()
            .unwrap()
            .push(("connect", identifier.to_string()));
        self.inner.connect(identifier)
    }

    fn reconnect<'a>(
        &'a self,
        identifier: &'a str,
    ) -> BoxFuture<'a, Result<Guarded<AnyTransport>, Error>> {
        self.calls
            .lock()
            .unwrap()
            .push(("reconnect", identifier.to_string()));
        self.inner.connect(identifier)
    }
}

/// Test: UT-SESS-068
///
/// The first connection calls `connect`; every automatic reconnection
/// attempt calls `reconnect`, with the session's own identifier, which
/// the session keeps.
#[tokio::test(start_paused = true)]
async fn reconnection_attempts_call_reconnect() {
    let id = "UT-SESS-068";
    let ble = Kind::Ble;
    let mut first = script(ble, vec![]);
    first.close_at = Some(T0 + ms(1_000));
    let mut n = 0;
    let inner = MockConnector::new(move || {
        n += 1;
        match n {
            1 => Ok(Mock::new(ble, id, first.clone())),
            2 => Err(Error::Transport {
                message: "no adapter".to_string(),
            }),
            _ => Ok(Mock::new(ble, id, script(ble, vec![]))),
        }
    });
    let connector = Arc::new(Recording {
        inner,
        calls: Mutex::new(Vec::new()),
    });
    let (session, _events) = Session::connect(
        Arc::clone(&connector) as Arc<dyn Connector>,
        id,
        host_id(),
        Arc::new(MemoryMarkers::new()),
        Options {
            reconnect: true,
            ..options()
        },
    )
    .unwrap();
    session.ready().await.unwrap();
    tokio::time::sleep(T0 + ms(2_000)).await;
    assert_eq!(session.link_state(), LinkState::Reconnecting);
    let info = session.ready().await.unwrap();
    assert_eq!(info.model, "MP305B");
    assert_eq!(
        *connector.calls.lock().unwrap(),
        vec![
            ("connect", id.to_string()),
            ("reconnect", id.to_string()),
            ("reconnect", id.to_string()),
        ]
    );
    assert_eq!(session.identifier(), id);
    assert_eq!(session.close(false).await, Ok(()));
}

/// Test: UT-SESS-068
///
/// The default `reconnect` of the trait calls `connect`.
#[tokio::test(start_paused = true)]
async fn the_default_reconnect_calls_connect() {
    let calls = Arc::new(AtomicU64::new(0));
    let counted = Arc::clone(&calls);
    let connector = MockConnector::new(move || {
        counted.fetch_add(1, Ordering::SeqCst);
        Ok(Mock::new(Kind::Hid, "x", Script::default()))
    });
    let guard = connector.reconnect("x").await.unwrap();
    assert_eq!(guard.description().kind, Kind::Hid);
    assert_eq!(calls.load(Ordering::SeqCst), 1);
}

/// Test: UT-SESS-069
///
/// Over USB the marker is keyed by the fixed key, not by the HID path:
/// a marker left under the key by an earlier session on another path is
/// found, reported and cleared, and the key is storable.
#[tokio::test(start_paused = true)]
async fn over_usb_the_marker_has_a_fixed_key() {
    assert_eq!(names::storable(USB_MARKER_KEY), Ok(()));
    let id = "DevSrvsID:4294971234";
    let since = UNIX_EPOCH + Duration::from_secs(1_790_845_200);
    let connector =
        MockConnector::new(move || Ok(Mock::new(Kind::Hid, id, script(Kind::Hid, vec![]))));
    let mut rig = start_with(
        id,
        connector,
        MemoryMarkers::holding(USB_MARKER_KEY, since),
        options(),
    );
    let events = rig.record();
    rig.session.ready().await.unwrap();
    tokio::time::sleep(ms(1)).await;
    let warning = SessionEvent::UncleanExitWarning {
        since,
        text: texts::unclean_exit(since),
    };
    assert!(events.non_readings().iter().any(|(_, e)| *e == warning));
    assert_eq!(
        rig.markers.calls(),
        vec![
            (USB_MARKER_KEY.to_string(), MarkerCall::Present),
            (USB_MARKER_KEY.to_string(), MarkerCall::Clear),
        ]
    );
    assert_eq!(rig.session.identifier(), id);
}

/// Test: UT-SESS-069
///
/// Over USB with control held and the output on, the marker is written
/// under the fixed key; over Bluetooth the key stays the identifier, so a
/// marker under the USB key is not reported there.
#[tokio::test(start_paused = true)]
async fn over_usb_the_marker_is_written_under_the_fixed_key() {
    let hid = Kind::Hid;
    let on = fixtures::c3_with(1, 0, 0, 1300, 1000);
    let rig = granted_on(
        "UT-SESS-069-usb",
        hid,
        vec![
            reply(hid, 0xC2, ms(130), &fixtures::C3_CAPTURE),
            c3_from(hid, &on, T0 + ms(500)),
        ],
        vec![],
    )
    .await;
    rig.until(T0 + ms(2_000)).await;
    let calls = rig.markers.calls();
    assert!(
        calls
            .iter()
            .any(|(key, c)| key == USB_MARKER_KEY && matches!(c, MarkerCall::Set(_))),
        "{calls:?}"
    );
    assert!(
        calls.iter().all(|(key, _)| key == USB_MARKER_KEY),
        "{calls:?}"
    );

    let id = "UT-SESS-069-ble";
    let since = UNIX_EPOCH + Duration::from_secs(1_790_845_200);
    let connector =
        MockConnector::new(move || Ok(Mock::new(Kind::Ble, id, script(Kind::Ble, vec![]))));
    let mut rig = start_with(
        id,
        connector,
        MemoryMarkers::holding(USB_MARKER_KEY, since),
        options(),
    );
    rig.session.ready().await.unwrap();
    tokio::time::sleep(ms(1)).await;
    assert!(!rig
        .drain_non_readings()
        .iter()
        .any(|e| matches!(e, SessionEvent::UncleanExitWarning { .. })));
    assert_eq!(
        rig.markers.calls(),
        vec![(id.to_string(), MarkerCall::Present)]
    );
}
