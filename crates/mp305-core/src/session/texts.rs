//! Implements: DD-SESS-061, DD-SESS-050 (the loss text), DD-SESS-010 (the
//! text of a loss while connecting), DD-SESS-051 (the give-up texts).
//!
//! The user-facing texts of the session, defined once so that the app and
//! the library show the same wording, and the RFC 3339 formatter they use.
//! Products render or log these texts and derive none of their own.

use std::time::{SystemTime, UNIX_EPOCH};

use crate::link::LossReason;
use crate::transport::description::Kind;

/// The prompt shown while the supply asks to confirm the connection
/// (SR-008).
pub const CONFIRM_CONNECTION: &str =
    "Confirm the connection on the supply's screen within 30 seconds";

/// The prompt shown while the supply asks to allow remote control
/// (SR-053).
pub const ALLOW_REMOTE_CONTROL: &str = "Allow remote control on the supply's screen";

/// Appended to the loss text over Bluetooth, and logged with every
/// Bluetooth timeout (AR-030).
pub const USB_HOST_HINT: &str = " A USB host talking to the supply is one possible cause.";

/// The give-up text after a `19 FF` during a reconnection attempt.
pub const GAVE_UP_UNRECOGNISED: &str =
    "The supply did not recognise this host; connect again to confirm on its screen.";

/// The give-up text after ten minutes without a reconnection.
pub const GAVE_UP_TIMEOUT: &str = "No reconnection within 10 minutes.";

/// The give-up text after the reconnect flag was switched off.
pub const GAVE_UP_SWITCHED_OFF: &str = "Reconnection switched off.";

/// The loss text when the host closed the session.
pub const CLOSED_BY_HOST: &str = "closed by the host";

/// What the output and the grant are after a loss (SR-028).
const AFTER_LOSS: &str =
    "The output is still in its last state and the supply has released remote control.";

/// `text` with its first letter in upper case.
fn capitalised(text: &str) -> String {
    let mut chars = text.chars();
    match chars.next() {
        Some(first) => first.to_uppercase().chain(chars).collect(),
        None => String::new(),
    }
}

/// The text of a link loss after the session was ready (DD-SESS-050): the
/// reason with its first letter in upper case, what the output and the
/// grant are, and over Bluetooth the USB host hint.
#[must_use]
pub fn link_lost(reason: &LossReason, kind: Kind) -> String {
    let hint = match kind {
        Kind::Ble => USB_HOST_HINT,
        Kind::Hid => "",
    };
    format!("{}. {AFTER_LOSS}{hint}", capitalised(&reason.to_string()))
}

/// The text of a link loss before the session was ready (DD-SESS-010).
#[must_use]
pub fn lost_while_connecting(reason: &LossReason) -> String {
    format!("The link to the supply was lost while connecting: {reason}.")
}

/// The unclean-exit warning (SR-046) with the marker's time in RFC 3339.
#[must_use]
pub fn unclean_exit(since: SystemTime) -> String {
    format!(
        "A previous session may have left the output on (marker written {})",
        rfc3339(since)
    )
}

/// `t` in RFC 3339 at second precision, UTC, with a `Z` suffix. A time
/// before the epoch, or one too far ahead to convert, formats as the epoch.
#[must_use]
pub fn rfc3339(t: SystemTime) -> String {
    let secs = t.duration_since(UNIX_EPOCH).map_or(0, |d| d.as_secs());
    civil(secs).unwrap_or_else(|| "1970-01-01T00:00:00Z".to_string())
}

/// Seconds since the epoch as `YYYY-MM-DDTHH:MM:SSZ`, by the civil-from-days
/// conversion (proleptic Gregorian calendar) in checked `i64` arithmetic;
/// `None` on an overflow.
fn civil(secs: u64) -> Option<String> {
    let secs = i64::try_from(secs).ok()?;
    let days = secs.checked_div(86_400)?;
    let rest = secs.checked_rem(86_400)?;
    let (hour, minute, second) = (
        rest.checked_div(3_600)?,
        rest.checked_rem(3_600)?.checked_div(60)?,
        rest.checked_rem(60)?,
    );
    // Days since 0000-03-01, in eras of 400 years (146 097 days); the
    // day count is never negative here.
    let z = days.checked_add(719_468)?;
    let era = z.checked_div(146_097)?;
    let doe = z.checked_sub(era.checked_mul(146_097)?)?;
    let yoe = doe
        .checked_sub(doe.checked_div(1_460)?)?
        .checked_add(doe.checked_div(36_524)?)?
        .checked_sub(doe.checked_div(146_096)?)?
        .checked_div(365)?;
    let doy = doe.checked_sub(
        yoe.checked_mul(365)?
            .checked_add(yoe.checked_div(4)?)?
            .checked_sub(yoe.checked_div(100)?)?,
    )?;
    let mp = doy.checked_mul(5)?.checked_add(2)?.checked_div(153)?;
    let day = doy
        .checked_sub(mp.checked_mul(153)?.checked_add(2)?.checked_div(5)?)?
        .checked_add(1)?;
    let month = if mp < 10 {
        mp.checked_add(3)?
    } else {
        mp.checked_sub(9)?
    };
    let year = yoe
        .checked_add(era.checked_mul(400)?)?
        .checked_add(i64::from(month <= 2))?;
    Some(format!(
        "{year:04}-{month:02}-{day:02}T{hour:02}:{minute:02}:{second:02}Z"
    ))
}

#[cfg(test)]
mod tests {
    use super::*;
    use core::time::Duration;

    fn at(secs: u64) -> SystemTime {
        UNIX_EPOCH + Duration::from_secs(secs)
    }

    /// Test: UT-SESS-005
    #[test]
    fn texts_and_rfc3339() {
        let base = "Three requests in a row went unanswered. The output is still in \
                    its last state and the supply has released remote control.";
        assert_eq!(
            link_lost(&LossReason::Unanswered, Kind::Ble),
            format!("{base} A USB host talking to the supply is one possible cause.")
        );
        assert_eq!(link_lost(&LossReason::Unanswered, Kind::Hid), base);
        assert_eq!(
            lost_while_connecting(&LossReason::Disconnected),
            "The link to the supply was lost while connecting: the transport reported \
             the link closed."
        );
        assert_eq!(rfc3339(UNIX_EPOCH), "1970-01-01T00:00:00Z");
        assert_eq!(rfc3339(at(1_709_210_096)), "2024-02-29T12:34:56Z");
        assert_eq!(rfc3339(at(1_790_848_800)), "2026-10-01T10:00:00Z");
        assert_eq!(
            rfc3339(UNIX_EPOCH - Duration::from_secs(1)),
            "1970-01-01T00:00:00Z"
        );
        assert_eq!(
            unclean_exit(at(1_790_848_800)),
            "A previous session may have left the output on (marker written \
             2026-10-01T10:00:00Z)"
        );
    }
}
