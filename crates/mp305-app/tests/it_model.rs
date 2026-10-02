//! Implements: nothing; the model part of the integration test IT-041
//! (docs/v-model/6-integration-tests.md).
//!
//! One hour of readings at 4 per second goes into a connected
//! `mp305_app::model::Model` through `Model::apply`, the one function the UI
//! changes the model with, and the chart buffer is checked after every
//! reading. The model is connected the way the UI connects it: the actions
//! `Select` and `Connect` through `actions::handle`, then the worker's
//! events `Connecting`, `Done` and `Ready`. Only public items of the crate
//! are used. The readings are the core's fixture `C3_CAPTURE` (the payload
//! of the first `0xC3` of `2026-09-29T193614-ble-readonly.jsonl`,
//! t = 12.8857, AF01) through `telemetry::parse_payload`; the info is its
//! `E1_BLE` (the `0xE1` of the same capture, t = 12.6162, AF02).

#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::panic,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects
)]

use core::time::Duration;
use std::path::PathBuf;
use std::time::{SystemTime, UNIX_EPOCH};

use mp305_app::actions::{handle, Clock, IdSource, UiAction};
use mp305_app::chart;
use mp305_app::model::{Found, Info, Instant, Kind, Model, Phase, Reading, TimedReading};
use mp305_app::worker::{AppEvent, Command, UiReading, What};
use mp305_core::protocol::ble::{self, BleRoute};
use mp305_core::protocol::fixtures;
use mp305_core::protocol::ops::{info as info_op, telemetry};

/// Readings per second.
const PER_SECOND: u64 = 4;

/// One hour in seconds.
const HOUR_S: u64 = 3600;

/// `at` plus `d`, through `checked_add` (no operator on `Instant`, as in
/// the crate, DD-APP-050).
fn after(at: Instant, d: Duration) -> Instant {
    at.checked_add(d).unwrap()
}

/// 2026-10-01T10:00:00Z, the wall time of `t0`.
fn wall0() -> SystemTime {
    UNIX_EPOCH
        .checked_add(Duration::from_secs(1_790_848_800))
        .unwrap()
}

/// The capture reading at `at`, its wall time `at - t0` after [`wall0`].
fn reading_at(t0: Instant, at: Instant) -> TimedReading {
    let raw = telemetry::parse_payload(&fixtures::C3_CAPTURE).unwrap();
    TimedReading {
        at,
        wall: wall0()
            .checked_add(at.saturating_duration_since(t0))
            .unwrap(),
        reading: Reading::from_raw(&raw),
    }
}

/// `E1_BLE` parsed.
fn info() -> Info {
    let wire = fixtures::on_air(Kind::Ble, info_op::REPLY, &fixtures::E1_BLE);
    info_op::parse(&ble::decode(&wire, BleRoute::Af01).unwrap()).unwrap()
}

/// A model connected at `t0` to the supply `IT-041` (attempt 1), with no
/// reading yet.
fn connected_model(t0: Instant) -> Model {
    let mut model = Model::new(PathBuf::from("/rec"), t0);
    model.found = vec![Found {
        transport: Kind::Ble,
        identifier: "IT-041".into(),
        unit_id: "IT-041".into(),
        name: "MP305B".into(),
        rssi: Some(-60),
        remote_flag: Some(true),
    }];
    let clock = Clock {
        now: t0,
        wall: wall0(),
    };
    let mut ids = IdSource::new();
    assert!(handle(
        &mut model,
        UiAction::Select("IT-041".into()),
        clock,
        &mut ids
    )
    .is_empty());
    let sent = handle(&mut model, UiAction::Connect, clock, &mut ids);
    let [Command::Connect { id, .. }] = sent.as_slice() else {
        panic!("{sent:?}");
    };
    model.apply(
        AppEvent::Connecting {
            sid: 1,
            identifier: "IT-041".into(),
        },
        t0,
    );
    model.apply(
        AppEvent::Done {
            id: *id,
            what: What::Connect,
            result: Ok(()),
        },
        t0,
    );
    model.apply(
        AppEvent::Ready {
            sid: 1,
            info: info(),
            reading: None,
            transport: Some(Kind::Ble),
        },
        t0,
    );
    assert_eq!(model.phase, Phase::Connected);
    model
}

/// Test: IT-041
#[test]
fn an_hour_of_readings_at_4_per_second_keeps_the_chart_within_its_10_min_capacity() {
    let t0 = Instant::now();
    let mut model = connected_model(t0);
    let capacity = model.chart.capacity();
    assert!(model.chart.is_empty());
    let period = Duration::from_millis(1000 / PER_SECOND);
    let count = HOUR_S * PER_SECOND;
    for k in 0..count {
        let at = after(t0, period * u32::try_from(k).unwrap());
        model.apply(
            UiReading {
                sid: 1,
                reading: reading_at(t0, at),
            },
            at,
        );
        assert!(
            model.chart.len() <= chart::CAPACITY,
            "{} points after reading {k}",
            model.chart.len()
        );
        assert_eq!(model.chart.capacity(), capacity, "the ring grew at {k}");
    }
    assert_eq!(
        model.reading.map(|r| r.at),
        Some(after(t0, period * u32::try_from(count - 1).unwrap()))
    );
    assert_eq!(model.chart.len(), chart::CAPACITY);
    // The 2401 points span the last 10 minutes, one per 250 ms slot.
    let oldest = model.chart.points().next().unwrap().t;
    let newest = model.chart.points().last().unwrap().t;
    assert_eq!(newest, Duration::from_millis(3_599_750));
    assert_eq!(newest.checked_sub(oldest), Some(Duration::from_secs(600)));
}
