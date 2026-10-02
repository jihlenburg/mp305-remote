//! Integration test IT-015 (AR-015): `Guarded` over the scripted mock: two
//! frames sent back to back are written one after the other, an injected
//! frame carries the paused clock time of its injection, and the
//! description names the kind and the identifier.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    missing_docs
)]

mod common;

use std::sync::{Arc, Mutex};

use core::time::Duration;

use tokio::sync::mpsc;
use tokio::time::{sleep, sleep_until, Instant};

use mp305_core::error::Error;
use mp305_core::protocol::ble::{BleRoute, Route};
use mp305_core::protocol::frame::Frame;
use mp305_core::protocol::ops::{info, telemetry};
use mp305_core::transport::description::{Description, Kind};
use mp305_core::transport::guarded::{Guarded, Item};
use mp305_core::transport::mock::{Mock, Script};
use mp305_core::transport::{RawIncoming, Transport};

use common::{inject, ms, C5_SETTINGS};

/// The command characteristic.
const AF01: Route = Route::Ble(BleRoute::Af01);

/// The start and end of every write a [`Slow`] carried out.
type Writes = Arc<Mutex<Vec<(Instant, Instant)>>>;

/// The scripted mock with a write that takes `delay` on the Tokio clock.
/// The mock's own writes complete at once, so two overlapping writes could
/// not be told from two consecutive ones; the delay makes the order of the
/// writes observable. Everything else is the mock's.
struct Slow {
    /// The mock every write ends in.
    mock: Mock,
    /// How long each write takes before it reaches the mock.
    delay: Duration,
    /// The start and end of each write.
    writes: Writes,
}

impl Transport for Slow {
    async fn send(&self, frame: &Frame, route: Route) -> Result<(), Error> {
        let started = Instant::now();
        sleep(self.delay).await;
        let result = self.mock.send(frame, route).await;
        self.writes.lock().unwrap().push((started, Instant::now()));
        result
    }

    fn incoming(&mut self) -> &mut mpsc::UnboundedReceiver<RawIncoming> {
        self.mock.incoming()
    }

    async fn close(&self) -> Result<(), Error> {
        self.mock.close().await
    }

    fn description(&self) -> &Description {
        self.mock.description()
    }
}

/// Test: IT-015
#[tokio::test(start_paused = true)]
async fn two_frames_sent_back_to_back_are_written_one_after_the_other() {
    let (c2, e0) = (telemetry::request(), info::request());
    // Through `Guarded<Mock>` the two frames reach the mock in the order
    // they were sent.
    let mock = Mock::new(Kind::Ble, "IT-015-a", Script::default());
    let handle = mock.handle();
    let guard: Guarded<Mock> = Guarded::new(mock);
    let (a, b) = tokio::join!(guard.send(&c2, AF01), guard.send(&e0, AF01));
    assert_eq!((a, b), (Ok(()), Ok(())));
    let opcodes: Vec<u8> = handle.sent().iter().map(|s| s.frame.opcode()).collect();
    assert_eq!(opcodes, vec![0xC2, 0xE0]);

    // With a write that takes 100 ms, the second write starts only when the
    // first has completed.
    let writes: Writes = Arc::default();
    let mock = Mock::new(Kind::Ble, "IT-015-b", Script::default());
    let handle = mock.handle();
    let guard = Guarded::new(Slow {
        mock,
        delay: ms(100),
        writes: Arc::clone(&writes),
    });
    let t = Instant::now();
    let (a, b) = tokio::join!(guard.send(&c2, AF01), guard.send(&e0, AF01));
    assert_eq!((a, b), (Ok(()), Ok(())));
    let spans: Vec<(Duration, Duration)> = writes
        .lock()
        .unwrap()
        .iter()
        .map(|(s, e)| (*s - t, *e - t))
        .collect();
    assert_eq!(spans, vec![(ms(0), ms(100)), (ms(100), ms(200))]);
    assert!(spans[1].0 >= spans[0].1);
    let reached: Vec<(Duration, u8)> = handle
        .sent()
        .iter()
        .map(|s| (s.at - t, s.frame.opcode()))
        .collect();
    assert_eq!(reached, vec![(ms(100), 0xC2), (ms(200), 0xE0)]);

    // The same two writes without the guard overlap, so the check above
    // would see a missing serialisation.
    let writes: Writes = Arc::default();
    let unguarded = Slow {
        mock: Mock::new(Kind::Ble, "IT-015-c", Script::default()),
        delay: ms(100),
        writes: Arc::clone(&writes),
    };
    let t = Instant::now();
    let _ = tokio::join!(unguarded.send(&c2, AF01), unguarded.send(&e0, AF01));
    let starts: Vec<Duration> = writes.lock().unwrap().iter().map(|(s, _)| *s - t).collect();
    assert_eq!(starts, vec![ms(0), ms(0)]);
}

/// Test: IT-015
#[tokio::test(start_paused = true)]
async fn an_injected_frame_carries_the_clock_time_of_its_injection() {
    let script = Script {
        injections: vec![inject(Kind::Ble, ms(1_234), 0xC5, &C5_SETTINGS)],
        ..Script::default()
    };
    let start = Instant::now();
    let mut guard: Guarded<Mock> = Guarded::new(Mock::new(Kind::Ble, "IT-015-d", script));
    // Read well after the injection: the stamp is the injection's time,
    // not the time it was read.
    sleep_until(start + ms(5_000)).await;
    let incoming = guard.recv().await.unwrap();
    assert_eq!(incoming.at - start, ms(1_234));
    assert_eq!(incoming.route, AF01);
    match incoming.item {
        Item::Frame(frame) => {
            assert_eq!(frame.opcode(), 0xC5);
            assert_eq!(frame.payload(), &C5_SETTINGS);
        }
        other => panic!("expected a frame, got {other:?}"),
    }
}

/// Test: IT-015
#[tokio::test(start_paused = true)]
async fn the_description_names_the_kind_and_the_identifier() {
    for (kind, identifier, text) in [
        (
            Kind::Ble,
            "72de66a3-1b2c-4d5e-8f90-abcdef123456",
            "ble 72de66a3-1b2c-4d5e-8f90-abcdef123456",
        ),
        (Kind::Hid, "/dev/hidraw3", "hid /dev/hidraw3"),
    ] {
        let guard: Guarded<Mock> = Guarded::new(Mock::new(kind, identifier, Script::default()));
        assert_eq!(
            guard.description(),
            &Description {
                kind,
                identifier: identifier.to_string()
            }
        );
        assert_eq!(guard.description().to_string(), text);
    }
}
