//! Implements: DD-CSV-003
//!
//! Calendar conversion and RFC 3339 formatting in UTC. The standard library
//! has no calendar, so the conversion from seconds since the Unix epoch to
//! a date and time of day lives here, once, for its three users: the CSV
//! time column (DD-CSV-002), the unclean-exit marker text (DD-SESS-061) and
//! the ISO text of a reading in the Python library.
//!
//! The arithmetic is unsigned throughout. Every `+`, `-` and `*` is a
//! `saturating_*` method whose operands are bounded so that it never
//! saturates (each step states its bound); `/` and `%` appear only with a
//! non-zero literal divisor. A time before the epoch formats as the epoch.
//!
//! ```
//! use mp305_core::civil;
//!
//! assert_eq!(civil::rfc3339_millis(1_790_848_800_250), "2026-10-01T10:00:00.250Z");
//! ```

use std::time::{SystemTime, UNIX_EPOCH};

/// A UTC calendar date and time of day in the proleptic Gregorian calendar.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct Civil {
    /// The year.
    pub year: i64,
    /// The month, 1 to 12.
    pub month: u8,
    /// The day of the month, 1 to 31.
    pub day: u8,
    /// The hour, 0 to 23.
    pub hour: u8,
    /// The minute, 0 to 59.
    pub minute: u8,
    /// The second, 0 to 59.
    pub second: u8,
}

/// `value` as a `u8`; every caller passes a value already bounded to fit,
/// so the saturating fallback is never taken.
fn narrow(value: u64) -> u8 {
    u8::try_from(value).unwrap_or(u8::MAX)
}

/// The UTC date and time of `seconds` after the Unix epoch, in the
/// proleptic Gregorian calendar (Howard Hinnant's days-to-civil algorithm).
///
/// Every `u64` converts: the largest gives a year near 5.8e11, far inside
/// `i64`.
#[must_use]
pub fn from_unix(seconds: u64) -> Civil {
    // At most u64::MAX / 86 400, about 2.1e14 days.
    let days = seconds / 86_400;
    let rest = seconds % 86_400;
    // Days since 0000-03-01; the year starts in March so that the leap day
    // is the last day of the year. The sum stays far below u64::MAX.
    let z = days.saturating_add(719_468);
    // Eras of 400 years, 146 097 days each; `era` is at most about 1.5e9.
    let era = z / 146_097;
    // Day of the era, 0 to 146 096.
    let doe = z % 146_097;
    // Year of the era, 0 to 399. Each subtraction removes a quotient of
    // `doe` (or of the running value) that is no larger than its minuend.
    let yoe = doe
        .saturating_sub(doe / 1_460)
        .saturating_add(doe / 36_524)
        .saturating_sub(doe / 146_096)
        / 365;
    // Day of the year starting 1 March, 0 to 365; the subtrahend is the
    // count of days before year `yoe` of the era, never above `doe`.
    let doy = doe.saturating_sub(
        yoe.saturating_mul(365)
            .saturating_add(yoe / 4)
            .saturating_sub(yoe / 100),
    );
    // Month counted from March, 0 to 11.
    let mp = doy.saturating_mul(5).saturating_add(2) / 153;
    // Day of the month, 1 to 31.
    let day = doy
        .saturating_sub(mp.saturating_mul(153).saturating_add(2) / 5)
        .saturating_add(1);
    // Calendar month, 1 to 12.
    let month = if mp < 10 {
        mp.saturating_add(3)
    } else {
        mp.saturating_sub(9)
    };
    // January and February belong to the next calendar year.
    let year = yoe
        .saturating_add(era.saturating_mul(400))
        .saturating_add(u64::from(month <= 2));
    Civil {
        year: i64::try_from(year).unwrap_or(i64::MAX),
        month: narrow(month),
        day: narrow(day),
        hour: narrow(rest / 3_600),
        minute: narrow(rest % 3_600 / 60),
        second: narrow(rest % 60),
    }
}

/// Whole seconds from the Unix epoch to `at`, 0 for a time before it.
fn unix_seconds(at: SystemTime) -> u64 {
    at.duration_since(UNIX_EPOCH).map_or(0, |d| d.as_secs())
}

/// Milliseconds from the Unix epoch to `at`, truncated: 0 for a time before
/// the epoch, `u64::MAX` for one too far ahead to count in a `u64`. The CSV
/// time columns take both of their values from this one number
/// (DD-CSV-002).
pub(crate) fn unix_millis(at: SystemTime) -> u64 {
    at.duration_since(UNIX_EPOCH)
        .map_or(0, |d| u64::try_from(d.as_millis()).unwrap_or(u64::MAX))
}

/// `civil` as `YYYY-MM-DDTHH:MM:SS`, without a fraction or a zone.
fn date_time(civil: &Civil) -> String {
    format!(
        "{:04}-{:02}-{:02}T{:02}:{:02}:{:02}",
        civil.year, civil.month, civil.day, civil.hour, civil.minute, civil.second
    )
}

/// `at` in RFC 3339 at second precision, UTC, with a `Z` suffix
/// (`2026-10-01T10:00:00Z`). The fraction is truncated; a time before the
/// epoch formats as the epoch.
#[must_use]
pub fn rfc3339(at: SystemTime) -> String {
    format!("{}Z", date_time(&from_unix(unix_seconds(at))))
}

/// `ms` milliseconds after the Unix epoch in RFC 3339 with three fraction
/// digits, UTC, with a `Z` suffix (`2026-10-01T10:00:00.250Z`).
#[must_use]
pub fn rfc3339_millis(ms: u64) -> String {
    format!("{}.{:03}Z", date_time(&from_unix(ms / 1_000)), ms % 1_000)
}

/// `at` as [`rfc3339_millis`] does, the sub-millisecond part truncated; a
/// time before the epoch formats as the epoch.
#[must_use]
pub fn rfc3339_millis_of(at: SystemTime) -> String {
    rfc3339_millis(unix_millis(at))
}

#[cfg(test)]
mod tests {
    use super::*;
    use core::time::Duration;
    use std::time::UNIX_EPOCH;

    /// A `Civil` from its six fields.
    fn civil(year: i64, month: u8, day: u8, hour: u8, minute: u8, second: u8) -> Civil {
        Civil {
            year,
            month,
            day,
            hour,
            minute,
            second,
        }
    }

    /// Test: UT-CSV-005
    #[test]
    fn from_unix_and_the_rfc3339_formatters() {
        assert_eq!(from_unix(0), civil(1970, 1, 1, 0, 0, 0));
        assert_eq!(from_unix(951_782_400), civil(2000, 2, 29, 0, 0, 0));
        assert_eq!(from_unix(1_790_848_800), civil(2026, 10, 1, 10, 0, 0));

        assert_eq!(rfc3339_millis(0), "1970-01-01T00:00:00.000Z");
        assert_eq!(
            rfc3339_millis(1_709_251_199_999),
            "2024-02-29T23:59:59.999Z"
        );
        assert_eq!(
            rfc3339_millis(1_790_848_800_000),
            "2026-10-01T10:00:00.000Z"
        );

        assert_eq!(
            rfc3339(UNIX_EPOCH - Duration::from_secs(1)),
            "1970-01-01T00:00:00Z"
        );

        let just_after = UNIX_EPOCH + Duration::new(1_790_848_800, 400_000);
        assert_eq!(rfc3339_millis_of(just_after), "2026-10-01T10:00:00.000Z");
    }
}
