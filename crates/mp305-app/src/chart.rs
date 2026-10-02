//! Implements: DD-APP-012.
//!
//! The chart's bounded buffer: at most one point per 250 ms slot, at most
//! 2401 points (10 minutes of slots plus one), in a ring that never grows,
//! so that memory stays bounded however long the app runs (SR-038). The
//! window the chart shows is measured from the newest point, so the chart
//! stands still while no readings arrive.

use core::time::Duration;
use std::collections::VecDeque;

use tokio::time::Instant;

use crate::model::TimedReading;

/// The buffer's fixed capacity: 600 s of 250 ms slots, plus one.
pub const CAPACITY: usize = 2401;

/// The width of a slot in milliseconds.
const SLOT_MS: u128 = 250;

/// One point of the chart.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Point {
    /// The reading's `at` minus the buffer's origin.
    pub t: Duration,
    /// The measured voltage in V.
    pub volts: f64,
    /// The measured current in A.
    pub amps: f64,
    /// The output power in W.
    pub watts: f64,
}

/// The three series of the chart, with x in seconds relative to the newest
/// point (0 or negative).
#[derive(Clone, Debug, Default, PartialEq)]
pub struct Series {
    /// Voltage in V.
    pub volts: Vec<[f64; 2]>,
    /// Current in A.
    pub amps: Vec<[f64; 2]>,
    /// Power in W.
    pub watts: Vec<[f64; 2]>,
}

/// The bounded chart buffer.
#[derive(Clone, Debug, PartialEq)]
pub struct Buffer {
    /// The points, oldest first.
    points: VecDeque<Point>,
    /// The `at` of the first reading pushed after `new()` or `clear()`.
    origin: Option<Instant>,
}

impl Default for Buffer {
    fn default() -> Self {
        Self::new()
    }
}

impl Buffer {
    /// An empty buffer with its fixed capacity.
    #[must_use]
    pub fn new() -> Buffer {
        Buffer {
            points: VecDeque::with_capacity(CAPACITY),
            origin: None,
        }
    }

    /// Stores a point for `reading` when its slot is later than the last
    /// stored point's; with the buffer full the oldest point goes first.
    pub fn push(&mut self, reading: &TimedReading) {
        let origin = *self.origin.get_or_insert(reading.at);
        let Some(t) = reading.at.checked_duration_since(origin) else {
            return;
        };
        if let Some(last) = self.points.back() {
            if slot(t) <= slot(last.t) {
                return;
            }
        }
        if self.points.len() >= CAPACITY {
            self.points.pop_front();
        }
        let view = &reading.reading;
        self.points.push_back(Point {
            t,
            volts: view.volts,
            amps: view.amps,
            watts: view.watts,
        });
    }

    /// The points whose `t` is greater than the newest point's `t` minus
    /// `window_s` seconds; all points when the window reaches back past the
    /// origin.
    pub fn visible(&self, window_s: u32) -> impl Iterator<Item = &Point> {
        let start = self.points.back().and_then(|newest| {
            newest
                .t
                .checked_sub(Duration::from_secs(u64::from(window_s)))
        });
        self.points
            .iter()
            .filter(move |p| start.is_none_or(|start| p.t > start))
    }

    /// The visible points as three series, x in seconds relative to the
    /// newest point (0 or negative).
    #[must_use]
    pub fn series(&self, window_s: u32) -> Series {
        let newest = self.points.back().map_or(Duration::ZERO, |p| p.t);
        let mut series = Series::default();
        for p in self.visible(window_s) {
            let x = -newest.saturating_sub(p.t).as_secs_f64();
            series.volts.push([x, p.volts]);
            series.amps.push([x, p.amps]);
            series.watts.push([x, p.watts]);
        }
        series
    }

    /// The number of points stored.
    #[must_use]
    pub fn len(&self) -> usize {
        self.points.len()
    }

    /// Whether no point is stored.
    #[must_use]
    pub fn is_empty(&self) -> bool {
        self.points.is_empty()
    }

    /// The capacity of the ring.
    #[must_use]
    pub fn capacity(&self) -> usize {
        self.points.capacity()
    }

    /// Removes every point and the origin; the capacity stays.
    pub fn clear(&mut self) {
        self.points.clear();
        self.origin = None;
    }

    /// The points, oldest first.
    pub fn points(&self) -> impl Iterator<Item = &Point> {
        self.points.iter()
    }
}

/// The slot of `t`: whole milliseconds divided by 250.
fn slot(t: Duration) -> u128 {
    t.as_millis() / SLOT_MS
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::testkit::{after, r, t0};

    /// Pushes a reading at `ms` after `t0`.
    fn push_at(buffer: &mut Buffer, base: Instant, ms: u64) {
        buffer.push(&r(
            0,
            0,
            0,
            1300,
            1000,
            after(base, Duration::from_millis(ms)),
        ));
    }

    /// The times of `points` in seconds.
    fn times<'a>(points: impl Iterator<Item = &'a Point>) -> Vec<f64> {
        points.map(|p| p.t.as_secs_f64()).collect()
    }

    /// Test: UT-APP-001
    #[test]
    fn three_thousand_quarter_second_readings_keep_the_last_2401() {
        let base = t0();
        let mut buffer = Buffer::new();
        assert_eq!(buffer.capacity(), CAPACITY);
        for k in 0..3000u64 {
            push_at(&mut buffer, base, k * 250);
        }
        assert_eq!(buffer.len(), 2401);
        assert_eq!(buffer.capacity(), CAPACITY);
        assert_eq!(
            buffer.points().next().unwrap().t,
            Duration::from_millis(149_750)
        );
        let v60 = times(buffer.visible(60));
        let v10 = times(buffer.visible(10));
        let v600 = times(buffer.visible(600));
        assert_eq!((v60.len(), v60[0]), (240, 690.0));
        assert_eq!((v10.len(), v10[0]), (40, 740.0));
        assert_eq!((v600.len(), v600[0]), (2400, 150.0));
        let series = buffer.series(10);
        for quantity in [&series.volts, &series.amps, &series.watts] {
            assert_eq!(quantity.len(), 40);
            for (i, point) in quantity.iter().enumerate() {
                let expected = -9.75 + 0.25 * i as f64;
                assert!((point[0] - expected).abs() < 1e-9, "{point:?} at {i}");
            }
        }
        assert_eq!(series.volts.last().unwrap()[0], 0.0);
    }

    /// Test: UT-APP-001
    #[test]
    fn bluetooth_readings_share_a_slot_now_and_then() {
        let base = t0();
        let mut buffer = Buffer::new();
        for k in 0..20u64 {
            push_at(&mut buffer, base, k * 230);
        }
        assert_eq!(buffer.len(), 18);
        let t = times(buffer.points());
        assert!(!t.contains(&0.23));
        assert!(!t.contains(&2.99));
        assert!(t.contains(&2.76));
    }

    /// Test: UT-APP-001
    #[test]
    fn a_reading_not_later_than_the_last_is_dropped_and_clear_resets_the_origin() {
        let base = t0();
        let mut buffer = Buffer::new();
        for k in 0..10u64 {
            push_at(&mut buffer, base, k * 100);
        }
        push_at(&mut buffer, base, 700);
        assert_eq!(times(buffer.points()), vec![0.0, 0.3, 0.5, 0.8]);
        buffer.clear();
        assert!(buffer.is_empty());
        push_at(&mut buffer, base, 5000);
        assert_eq!(times(buffer.points()), vec![0.0]);
    }
}
