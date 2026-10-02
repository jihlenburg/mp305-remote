//! Implements: DD-APP-032.
//!
//! The frame-time and reading-delay notes, pure, so that the tests need no
//! log collector. `AppCore::logic` logs them under [`LOG_TARGET`]. The
//! frame time is eframe's time for the previous frame (its logic, drawing,
//! tessellation and painting, without the wait for vsync), so a frame's
//! line appears one frame later.

use core::time::Duration;

use tokio::time::Instant;

/// The log target of the notes.
pub const LOG_TARGET: &str = "mp305_app::frames";

/// A frame slower than this is logged at WARN.
const SLOW_FRAME: Duration = Duration::from_millis(100);

/// A line to log.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Note {
    /// The level.
    pub level: log::Level,
    /// The text.
    pub text: String,
}

/// The frame time from eframe's `cpu_usage` in seconds; `None` for a
/// missing, negative or non-finite value.
#[must_use]
pub fn frame_time_from(cpu_usage: Option<f32>) -> Option<Duration> {
    cpu_usage.and_then(|seconds| Duration::try_from_secs_f32(seconds).ok())
}

/// `frame <ms> ms`: WARN above 100 ms, TRACE otherwise.
#[must_use]
pub fn frame_note(took: Duration) -> Note {
    let level = if took > SLOW_FRAME {
        log::Level::Warn
    } else {
        log::Level::Trace
    };
    Note {
        level,
        text: format!("frame {} ms", took.as_millis()),
    }
}

/// `reading shown +<ms> ms` at DEBUG: the time from the reading's arrival
/// to the start of the frame that shows it.
#[must_use]
pub fn reading_note(arrived: Instant, shown: Instant) -> Note {
    Note {
        level: log::Level::Debug,
        text: format!(
            "reading shown +{} ms",
            shown.saturating_duration_since(arrived).as_millis()
        ),
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::testkit::after;

    /// A note at `level` with `text`.
    fn note(level: log::Level, text: &str) -> Note {
        Note {
            level,
            text: text.to_string(),
        }
    }

    /// Test: UT-APP-008
    #[test]
    fn frame_times_and_notes() {
        assert_eq!(frame_time_from(None), None);
        assert_eq!(
            frame_time_from(Some(0.118)).map(|d| d.as_millis()),
            Some(118)
        );
        assert_eq!(frame_time_from(Some(-1.0)), None);
        assert_eq!(frame_time_from(Some(f32::NAN)), None);
        let ms = Duration::from_millis;
        assert_eq!(frame_note(ms(16)), note(log::Level::Trace, "frame 16 ms"));
        assert_eq!(frame_note(ms(100)), note(log::Level::Trace, "frame 100 ms"));
        assert_eq!(frame_note(ms(118)), note(log::Level::Warn, "frame 118 ms"));
        let base = Instant::now();
        assert_eq!(
            reading_note(after(base, ms(100)), after(base, ms(130))),
            note(log::Level::Debug, "reading shown +30 ms")
        );
        assert_eq!(
            reading_note(after(base, ms(130)), after(base, ms(100))),
            note(log::Level::Debug, "reading shown +0 ms")
        );
    }
}
