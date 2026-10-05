//! Implements: DD-APP-014, DD-APP-041 (the bench safety text).
//!
//! The texts the app shows on screen and the texts the worker, the paths
//! and the model put into events, banners and log lines. The session's and
//! the core's texts appear unchanged inside them. The screens take every
//! label from here too (the `label` module), so that `ui/` makes up no
//! text of its own (DD-APP-030).

use std::path::Path;

use crate::model::{Faults, Kind, Limits, LiveMode, RemoteState};
use crate::worker::{ErrorKind, ErrorText, What};

/// The answer to a second `Scan` while one runs.
pub const SCAN_RUNNING: &str = "a scan is already running";
/// The answer to a `StartRecording` while a recorder exists.
pub const ALREADY_RECORDING: &str = "already recording";
/// The answer to a `StartRecording` without an open session and a reading.
pub const NOT_CONNECTED: &str = "not connected";
/// The answer to a `Connect` while a session exists.
pub const ALREADY_CONNECTED: &str = "a supply is already connected";
/// The answer to a `Reconnect` without an open session.
pub const NO_CONNECTION_TO_RENEW: &str = "no connection to renew";
/// The report of a session whose events ended without `close`.
pub const SESSION_ENDED: &str =
    "the session ended unexpectedly; the output is left in its last state";
/// The error of a recording whose queue overflowed.
pub const ROWS_DROPPED: &str = "rows were dropped: the file is not keeping up";
/// The error of a missing home directory.
pub const NO_HOME: &str = "the OS reports no home directory";
/// The warning of an exit that drops the session without `close`.
pub const EXIT_WITHOUT_QUESTION: &str =
    "exit without a question: the output may be on; it is left as it is and the unclean-exit marker stays";
/// A field with a `,`.
pub const DECIMAL_POINT: &str = "use . as the decimal point";
/// A field that is not a number.
pub const NOT_A_NUMBER: &str = "not a number";
/// The log line of a fast bind.
pub const BIND_RECOGNISED: &str = "the supply recognised this host";
/// The log line of a confirmed prompt bind.
pub const BIND_CONFIRMED: &str = "confirmed on the supply";
/// The banner when a command cannot reach the worker.
pub const WORKER_STOPPED: &str = "The app's worker has stopped and the supply is no longer controlled. The output is left in its last state: switch it off on the supply if needed, then restart the app.";
/// The error of a recorder that ended without its report.
pub const RECORDER_ENDED: &str = "the recorder ended without a report";
/// The bench safety note (DD-APP-041); the README's `Bench safety`
/// section holds it word for word.
pub const BENCH_SAFETY: &str = "Set a hardware current limit and the OCP mode on the supply's front panel. Keep only a load on the output that is safe at the supply's settings. The supply keeps the output on when the link drops, and the app cannot switch it off then. Prefer USB over Bluetooth for unattended runs.";
/// Where the bench safety note is online.
pub const BENCH_SAFETY_URL: &str =
    "https://github.com/jihlenburg/mp305-remote/blob/main/crates/mp305-app/README.md#bench-safety";

/// The reason of [`off_failed`] when the stored reading is not in DC mode.
pub const OFF_NOT_DC: &str = "the supply is not in DC mode";
/// The reason of [`off_failed`] when the close's reading shows the output
/// on.
pub const OFF_STILL_ON: &str = "the supply still reports the output on";
/// The reason of [`off_failed`] when no reading was taken.
pub const OFF_UNCONFIRMED: &str = "no reading confirmed it";

/// The close question without a reading.
pub const CLOSE_NO_READING: &str =
    "There is no reading, so the output may be on. Switch it off before disconnecting?";
/// The close question with the output on.
pub const CLOSE_OUTPUT_ON: &str = "The output is on. Switch it off before disconnecting?";
/// The close question with an output-on in flight.
pub const CLOSE_ON_PENDING: &str =
    "An output-on command is still pending, so the output may be on. Switch it off before disconnecting?";
/// The report and WARN line of a disconnect that dropped the session
/// without `close` (DD-APP-005).
pub const DISCONNECT_UNASKED: &str = "the supply had just connected and its output may be on; the output is left as it is and the next connection will warn";
/// The close question while an answered output-on is not yet shown by a
/// reading (DD-APP-014).
pub const CLOSE_ON_DONE: &str = "An output-on command was just sent and no reading shows its effect yet, so the output may be on. Switch it off before disconnecting?";
/// The close question with the output confirmed off.
pub const CLOSE_NOW_OFF: &str = "The output is now off.";
/// The log line of a reconnection.
pub const RECONNECTED: &str = "reconnected";
/// The log line of a `Ready` that came while disconnecting.
pub const READY_WHILE_CLOSING: &str =
    "the connection completed while disconnecting; the disconnect goes on";
/// The supply line without a connected row.
pub const THE_SUPPLY: &str = "the supply";
/// A found supply without a name.
pub const NO_NAME: &str = "(no name)";
/// A value the supply or the OS did not report.
pub const UNKNOWN: &str = "unknown";
/// A hardware version the supply did not report.
pub const NOT_REPORTED: &str = "not reported";
/// The recording state without a recording.
pub const RECORDING_OFF: &str = "Recording: off";
/// The recording state before the file is open.
pub const RECORDING_STARTING: &str = "Recording: starting";
/// The recording state while writing.
pub const RECORDING_ON: &str = "Recording";
/// The automatic recording name, as the path field's placeholder shows it.
pub const AUTOMATIC_NAME: &str = "mp305-YYYYMMDD-HHMMSS.csv";

/// The chart window choices: seconds and label (DD-APP-031).
pub const WINDOW_CHOICES: [(u32, &str); 6] = [
    (10, "10 s"),
    (30, "30 s"),
    (60, "1 min"),
    (120, "2 min"),
    (300, "5 min"),
    (600, "10 min"),
];

/// The line on the empty right side of the connection screen.
pub const CONNECT_HINT: &str = "Switch the supply on and enable remote control, then scan";
/// A measured voltage before the first reading, as wide as `30.00`.
pub const NO_VOLTS: &str = "--.--";
/// A measured current before the first reading, as wide as `5.000`.
pub const NO_AMPS: &str = "-.---";
/// A power before the first reading.
pub const NO_WATTS: &str = "--.--";

/// The labels of the screens (DD-APP-031).
pub mod label {
    /// The button that opens the details panel, and the panel's title.
    pub const DETAILS: &str = "Details";
    /// The button that starts a recording.
    pub const RECORD: &str = "Record";
    /// The button that stops the recording.
    pub const STOP: &str = "Stop";
    /// The label of the voltage setpoint field.
    pub const SET: &str = "set";
    /// The label of the current limit field.
    pub const LIMIT: &str = "limit";
    /// The button that applies an edited setpoint field.
    pub const SET_BUTTON: &str = "Set";
    /// The off half of the output key.
    pub const OFF: &str = "Off";
    /// The on half of the output key.
    pub const ON: &str = "On";
    /// The unit of a voltage.
    pub const VOLTS: &str = "V";
    /// The unit of a current.
    pub const AMPS: &str = "A";
    /// The unit of a power.
    pub const WATTS: &str = "W";
    /// The scan button once a scan ran.
    pub const SCAN_AGAIN: &str = "Scan again";
    /// The details row of the connection.
    pub const CONNECTION: &str = "Connection";
    /// The USB transport.
    pub const USB: &str = "USB";
    /// The Bluetooth transport.
    pub const BLUETOOTH: &str = "Bluetooth";
    /// The window title and the app's name.
    pub const APP_TITLE: &str = "MP305 Remote";
    /// The dismiss button of a banner.
    pub const DISMISS: &str = "Dismiss";
    /// The event log's header.
    pub const EVENT_LOG: &str = "Event log";
    /// The scan button.
    pub const SCAN: &str = "Scan";
    /// The scan time slider.
    pub const SCAN_TIME: &str = "Scan time";
    /// The scanning indicator.
    pub const SCANNING: &str = "Scanning";
    /// The list of found supplies.
    pub const SUPPLIES: &str = "Supplies";
    /// The columns of the list of found supplies.
    pub const COLUMNS: [&str; 5] = ["Name", "Unit", "Transport", "Signal", "Remote"];
    /// The connect button.
    pub const CONNECT: &str = "Connect";
    /// The cancel button.
    pub const CANCEL: &str = "Cancel";
    /// The reconnect checkbox.
    pub const RECONNECT_AUTOMATICALLY: &str = "Reconnect automatically after a link loss";
    /// The heading of the limit fields.
    pub const LIMITS: &str = "Your limits";
    /// The maximum voltage field.
    pub const MAX_VOLTAGE: &str = "Maximum voltage (V)";
    /// The maximum current field.
    pub const MAX_CURRENT: &str = "Maximum current (A)";
    /// The apply button of the limit fields.
    pub const APPLY_LIMITS: &str = "Apply limits";
    /// The bench safety note's header.
    pub const BENCH_SAFETY: &str = "Bench safety";
    /// The link to the bench safety note.
    pub const BENCH_SAFETY_LINK: &str = "The bench safety note online";
    /// The heading of the supply's info.
    pub const SUPPLY: &str = "Supply";
    /// The heading of the readings.
    pub const READINGS: &str = "Readings";
    /// The heading of the supply settings.
    pub const SETTINGS: &str = "Supply settings";
    /// The heading of the setpoint fields.
    pub const SETPOINTS: &str = "Setpoints";
    /// The voltage field.
    pub const VOLTAGE: &str = "Voltage (V)";
    /// The current field.
    pub const CURRENT: &str = "Current limit (A)";
    /// The apply button of a setpoint field.
    pub const APPLY: &str = "Apply";
    /// The mark of an edited setpoint field.
    pub const NOT_APPLIED: &str = "not applied";
    /// The output-on button.
    pub const OUTPUT_ON: &str = "Output ON";
    /// The output-off button.
    pub const OUTPUT_OFF: &str = "Output OFF";
    /// The request button.
    pub const REQUEST_REMOTE: &str = "Request remote control";
    /// The release button.
    pub const RELEASE_REMOTE: &str = "Release remote control";
    /// The disconnect button.
    pub const DISCONNECT: &str = "Disconnect";
    /// The reconnect button.
    pub const RECONNECT: &str = "Reconnect";
    /// The heading of the recording controls.
    pub const RECORDING: &str = "Recording";
    /// The start button of the recording.
    pub const START_RECORDING: &str = "Start recording";
    /// The stop button of the recording.
    pub const STOP_RECORDING: &str = "Stop recording";
    /// The button that ends a switch-off the user gave up waiting for.
    pub const CLOSE_ANYWAY: &str = "Close anyway (the output may still be on)";
    /// The heading of the chart.
    pub const CHART: &str = "Chart";
    /// The window choice of the chart.
    pub const WINDOW: &str = "Window";
    /// The close question's title for the window's close.
    pub const CLOSE_TITLE_WINDOW: &str = "Close MP305 Remote";
    /// The close question's title for the Disconnect button.
    pub const CLOSE_TITLE_DISCONNECT: &str = "Disconnect";
    /// The switch-off answer.
    pub const SWITCH_OFF: &str = "Switch off";
    /// The leave-on answer.
    pub const LEAVE_ON: &str = "Leave on";
    /// The info row of the transport.
    pub const TRANSPORT: &str = "Transport";
    /// The info row of the model.
    pub const MODEL: &str = "Model";
    /// The info row of the firmware version.
    pub const VERSION: &str = "Version";
    /// The info row of the hardware version.
    pub const HARDWARE: &str = "Hardware";
    /// The reading row of the measured voltage.
    pub const MEASURED_VOLTAGE: &str = "Voltage";
    /// The reading row of the measured current.
    pub const MEASURED_CURRENT: &str = "Current";
    /// The reading row of the power.
    pub const POWER: &str = "Power";
    /// The reading row of the voltage setpoint.
    pub const SET_VOLTAGE: &str = "Set voltage";
    /// The reading row of the current limit.
    pub const SET_CURRENT: &str = "Set current";
    /// The reading row of the output state.
    pub const OUTPUT: &str = "Output";
    /// The reading row of the regulation mode.
    pub const REGULATION: &str = "Regulation";
    /// The reading row of the live mode.
    pub const MODE: &str = "Mode";
    /// The reading row of the faults.
    pub const FAULTS: &str = "Faults";
    /// The settings row of the charge limit.
    pub const CHARGE_LIMIT: &str = "Charge limit";
    /// The settings row of the volume.
    pub const VOLUME: &str = "Volume";
    /// The settings row of the screen-off setting.
    pub const SCREEN_OFF: &str = "Screen off";
    /// The settings row of the auto shutdown.
    pub const AUTO_SHUTDOWN: &str = "Auto shutdown";
    /// The settings row of the screen direction.
    pub const SCREEN_DIRECTION: &str = "Screen direction";
    /// The settings row of the ramp step.
    pub const RAMP_STEP: &str = "Ramp step";
    /// The settings row of the OCP delay.
    pub const OCP_DELAY: &str = "OCP delay";
    /// The settings row of the USB line drop compensation.
    pub const USB_LINE_DROP: &str = "USB line drop";
}

/// The step of [`crate::worker::real_deps`] that failed.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum DepsStep {
    /// The state directory.
    StateDirectory,
    /// The host ID.
    HostId,
    /// Discovery.
    Discovery,
}

/// `state directory: <text>`, `host ID: <text>` or `discovery: <text>`.
#[must_use]
pub fn deps_failed(step: DepsStep, text: &str) -> String {
    let name = match step {
        DepsStep::StateDirectory => "state directory",
        DepsStep::HostId => "host ID",
        DepsStep::Discovery => "discovery",
    };
    format!("{name}: {text}")
}

/// `faults: <names joined by ", ">`, or `faults cleared` for none.
#[must_use]
pub fn faults_line(faults: Faults) -> String {
    if faults.is_empty() {
        return "faults cleared".to_string();
    }
    format!("faults: {}", fault_names(faults))
}

/// The names of `faults` joined by `, `, or `none`.
#[must_use]
pub fn fault_names(faults: Faults) -> String {
    if faults.is_empty() {
        return "none".to_string();
    }
    faults
        .iter()
        .map(|f| f.to_string())
        .collect::<Vec<_>>()
        .join(", ")
}

/// `recording saved: <rows> rows in <path>`.
#[must_use]
pub fn recording_saved(rows: u64, path: &Path) -> String {
    format!("recording saved: {rows} rows in {}", path.display())
}

/// `Disconnect: <text>`.
#[must_use]
pub fn disconnect_error(text: &str) -> String {
    format!("Disconnect: {text}")
}

/// `Could not connect to <supply>: <text>`.
#[must_use]
pub fn connect_failed(supply: &str, text: &str) -> String {
    format!("Could not connect to {supply}: {text}")
}

/// `<what> failed: <text>`, with `. Switch the output off on the supply.`
/// for an output-off refused outside DC mode.
#[must_use]
pub fn command_failed(what: What, kind: ErrorKind, text: &str) -> String {
    if what == What::OutputOff && kind == ErrorKind::Mode {
        format!("{what} failed: {text}. Switch the output off on the supply.")
    } else {
        format!("{what} failed: {text}")
    }
}

/// The log line of a `Done` after `ms` milliseconds: `output off
/// acknowledged after <ms> ms` for an output-off that succeeded, else
/// `<what> done`, `<what> cancelled` or `<what> failed after <ms> ms`.
#[must_use]
pub fn done_line(what: What, ms: u128, result: &Result<(), ErrorText>) -> String {
    match result {
        Ok(()) if what == What::OutputOff => format!("output off acknowledged after {ms} ms"),
        Ok(()) => format!("{what} done after {ms} ms"),
        Err(e) if e.kind == ErrorKind::Cancelled => {
            format!("{what} cancelled after {ms} ms: {}", e.text)
        }
        Err(e) => format!("{what} failed after {ms} ms: {}", e.text),
    }
}

/// The `OffFailed` banner with `reason`.
#[must_use]
pub fn off_failed(reason: &str) -> String {
    format!(
        "The output could not be switched off ({reason}). It may still be on: switch it off \
         on the supply."
    )
}

/// The `SetpointsChanged` banner: volts with two decimals, amps with
/// three.
#[must_use]
pub fn setpoints_changed(set_v: f64, set_a: f64, exp_v: f64, exp_a: f64) -> String {
    format!(
        "The supply's setpoints are {set_v:.2} V and {set_a:.3} A, not the expected \
         {exp_v:.2} V and {exp_a:.3} A."
    )
}

/// The `UncleanExit` banner: `<supply>: <text>`.
#[must_use]
pub fn unclean_exit(supply: &str, text: &str) -> String {
    format!("{supply}: {text}")
}

/// The banner of a recording that ended with an error.
#[must_use]
pub fn recording_stopped(error: &str, rows: u64, path: &Path) -> String {
    format!(
        "Recording stopped: {error}. {rows} rows are in {}.",
        path.display()
    )
}

/// The fatal banner.
#[must_use]
pub fn fatal(text: &str) -> String {
    format!("The app cannot work: {text}")
}

/// The notice outside DC mode (UR-006).
#[must_use]
pub fn mode_notice(mode: LiveMode) -> String {
    format!(
        "The supply is in {mode} mode. The app controls it only in DC mode; switch the output \
         off on the supply."
    )
}

/// The notice of setpoints above the user's limits, volts with two
/// decimals and amps with three.
#[must_use]
pub fn limit_notice(volts: f64, amps: f64) -> String {
    format!(
        "The supply's setpoints ({volts:.2} V, {amps:.3} A) exceed your limits; set lower \
         values before switching the output on."
    )
}

/// The notice of a denied or lost grant; `None` for the other states.
#[must_use]
pub fn remote_notice(state: RemoteState) -> Option<&'static str> {
    match state {
        RemoteState::Denied => {
            Some("The supply denied remote control. Press Request remote control to ask again.")
        }
        RemoteState::Lost => {
            Some("Remote control was lost. Press Request remote control to take it again.")
        }
        RemoteState::None | RemoteState::Requested | RemoteState::Granted => None,
    }
}

/// The line under the loss text.
#[must_use]
pub fn reconnect_line(reconnecting: bool, gave_up: Option<&str>) -> String {
    match gave_up {
        Some(text) => text.to_string(),
        None if reconnecting => {
            "Reconnecting automatically every 5 s for up to 10 minutes.".to_string()
        }
        None => "Press Reconnect to connect again.".to_string(),
    }
}

/// The line while the session closes.
#[must_use]
pub fn closing_line(off_requested: bool, overdue: bool) -> &'static str {
    if overdue {
        "Switching the output off is taking longer than expected; the output may still be on."
    } else if off_requested {
        "Disconnecting: switching the output off and releasing remote control."
    } else {
        "Disconnecting: releasing remote control."
    }
}

/// The log line of readings the UI did not take.
#[must_use]
pub fn readings_dropped(total: u64) -> String {
    format!("{total} readings were not shown (the window fell behind)")
}

/// `in force: <voltage>, <current>`, each `<value> V` (or `A`) or `none`.
#[must_use]
pub fn limits_text(limits: &Limits) -> String {
    let volts = limits
        .max_volts
        .map_or_else(|| "none".to_string(), |v| format!("{v} V"));
    let amps = limits
        .max_amps
        .map_or_else(|| "none".to_string(), |a| format!("{a} A"));
    format!("in force: {volts}, {amps}")
}

/// The close question with the output on outside DC mode.
#[must_use]
pub fn close_not_dc(mode: LiveMode) -> String {
    format!(
        "The output is on and the supply is in {mode} mode, where the app cannot switch it off. \
         Switch it off on the supply, or disconnect and leave it on."
    )
}

/// The close question with a reading `seconds` old.
#[must_use]
pub fn close_stale(seconds: u64) -> String {
    format!(
        "The last reading is {seconds} s old, so the output may be on. Switch it off before \
         disconnecting?"
    )
}

/// The prompt's text with the seconds left.
#[must_use]
pub fn prompt_line(text: &str, left: u32) -> String {
    format!("{text} ({left} s left)")
}

/// `Connecting to <supply>`.
#[must_use]
pub fn connecting(supply: &str) -> String {
    format!("Connecting to {supply}")
}

/// The log line of a scan result.
#[must_use]
pub fn scan_line(found: usize, message: Option<&str>) -> String {
    match message {
        Some(text) => format!("scan: {text}"),
        None => format!("scan: {found} found"),
    }
}

/// The log line of a remote-control state.
#[must_use]
pub fn remote_line(state: RemoteState) -> String {
    format!("remote control: {state}")
}

/// The log line of new supply settings.
#[must_use]
pub fn settings_line() -> &'static str {
    "the supply's settings changed"
}

/// The log line of a ready session.
#[must_use]
pub fn ready_line(supply: &str) -> String {
    format!("connected to {supply}")
}

/// The log line of an ended session.
#[must_use]
pub fn disconnected_line(supply: &str) -> String {
    format!("disconnected from {supply}")
}

/// The log line of a recording that started.
#[must_use]
pub fn recording_on(path: &Path) -> String {
    format!("recording to {}", path.display())
}

/// The log line of a `Done` whose command is not pending.
#[must_use]
pub fn stray_done(what: What, id: u64) -> String {
    format!("{what} answered for command {id}, which was not pending")
}

/// `on` or `off`.
#[must_use]
pub fn on_off(on: bool) -> &'static str {
    if on {
        "on"
    } else {
        "off"
    }
}

/// A remote-control flag: `on`, `off` or `unknown`.
#[must_use]
pub fn flag(flag: Option<bool>) -> &'static str {
    flag.map_or(UNKNOWN, on_off)
}

/// A raw power in 10 mW steps with its unit: `6.17 W`.
#[must_use]
pub fn watts(raw: u16) -> String {
    format!("{}.{:02} W", raw / 100, raw % 100)
}

/// A live mode with the word `mode`: `DC mode`, `PD mode`.
#[must_use]
pub fn mode_name(mode: LiveMode) -> String {
    format!("{mode} mode")
}

/// The remote-control state as the main screen shows it.
#[must_use]
pub fn remote_state_line(state: RemoteState) -> String {
    format!("Remote control: {state}")
}

/// The line of the recording's state.
#[must_use]
pub fn recording_state(state: &str, rows: Option<u64>, path: Option<&Path>) -> String {
    match (rows, path) {
        (Some(rows), Some(path)) => format!("{state}: {rows} rows in {}", path.display()),
        (None, Some(path)) => format!("{state}: {}", path.display()),
        _ => state.to_string(),
    }
}

/// The transport as the screens name it: `USB` or `Bluetooth`.
#[must_use]
pub fn transport_name(kind: Kind) -> &'static str {
    match kind {
        Kind::Hid => label::USB,
        Kind::Ble => label::BLUETOOTH,
    }
}

/// A raw power in 10 mW steps without its unit: `6.17`.
#[must_use]
pub fn watts_number(raw: u16) -> String {
    format!("{}.{:02}", raw / 100, raw % 100)
}

/// `<field name>: <error>`, the status line of an invalid field.
#[must_use]
pub fn field_error_line(name: &str, error: &str) -> String {
    format!("{name}: {error}")
}

/// `Waiting for the supply: <what>`, a command that has no answer yet.
#[must_use]
pub fn pending_line(what: What) -> String {
    format!("Waiting for the supply: {what}")
}

/// The hover text of a found supply: `Unit <unit>, remote control flag
/// <flag>`.
#[must_use]
pub fn found_hint(unit: &str, remote: &str) -> String {
    format!("Unit {unit}, remote control flag {remote}")
}

/// A time axis label in seconds before now: `-30 s`, and `0 s` at now.
#[must_use]
pub fn axis_seconds(seconds: f64) -> String {
    if seconds.abs() < 0.5 {
        "0 s".to_string()
    } else {
        format!("{seconds:.0} s")
    }
}

/// A value axis label with as many decimals as the grid `step` needs.
#[must_use]
pub fn axis_value(value: f64, step: f64) -> String {
    let decimals = if step >= 1.0 {
        0
    } else if step >= 0.1 {
        1
    } else if step >= 0.01 {
        2
    } else {
        3
    };
    let shown = if value.abs() < 0.0005 { 0.0 } else { value };
    format!("{shown:.decimals$}")
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::path::PathBuf;

    /// Test: UT-APP-023
    #[test]
    fn the_lines_of_reconnection_and_closing() {
        assert_eq!(
            reconnect_line(true, None),
            "Reconnecting automatically every 5 s for up to 10 minutes."
        );
        assert_eq!(
            reconnect_line(false, None),
            "Press Reconnect to connect again."
        );
        assert_eq!(
            reconnect_line(false, Some("Reconnection switched off.")),
            "Reconnection switched off."
        );
        assert_eq!(
            closing_line(true, false),
            "Disconnecting: switching the output off and releasing remote control."
        );
        assert_eq!(
            closing_line(false, false),
            "Disconnecting: releasing remote control."
        );
        assert_eq!(
            closing_line(true, true),
            "Switching the output off is taking longer than expected; the output may still be on."
        );
    }

    /// Test: UT-APP-023
    #[test]
    fn limits_text_names_each_limit_or_none() {
        assert_eq!(limits_text(&Limits::none()), "in force: none, none");
        assert_eq!(
            limits_text(&Limits {
                max_volts: Some(12.0),
                max_amps: Some(1.5)
            }),
            "in force: 12 V, 1.5 A"
        );
    }

    /// Test: UT-APP-023
    #[test]
    fn the_bench_safety_note_is_word_for_word() {
        assert_eq!(
            BENCH_SAFETY,
            "Set a hardware current limit and the OCP mode on the supply's front panel. \
             Keep only a load on the output that is safe at the supply's settings. \
             The supply keeps the output on when the link drops, and the app cannot \
             switch it off then. Prefer USB over Bluetooth for unattended runs."
        );
    }

    /// Test: UT-APP-021
    #[test]
    fn the_readme_holds_the_bench_safety_note_word_for_word() {
        let readme = include_str!("../README.md");
        let section = readme
            .split("\n## Bench safety\n")
            .nth(1)
            .expect("the README has a Bench safety section");
        let body = section.split("\n## ").next().unwrap().trim();
        assert_eq!(body, BENCH_SAFETY);
    }

    /// Test: UT-APP-023
    #[test]
    fn the_worker_texts_and_the_constants() {
        assert_eq!(
            deps_failed(DepsStep::StateDirectory, "the OS reports no home directory"),
            "state directory: the OS reports no home directory"
        );
        assert_eq!(
            deps_failed(DepsStep::HostId, "store: x"),
            "host ID: store: x"
        );
        assert_eq!(
            deps_failed(DepsStep::Discovery, "transport: y"),
            "discovery: transport: y"
        );
        assert_eq!(faults_line(Faults(0)), "faults cleared");
        assert_eq!(faults_line(Faults(32)), "faults: over current");
        assert_eq!(SCAN_RUNNING, "a scan is already running");
        assert_eq!(ALREADY_RECORDING, "already recording");
        assert_eq!(NOT_CONNECTED, "not connected");
        assert_eq!(ALREADY_CONNECTED, "a supply is already connected");
        assert_eq!(NO_CONNECTION_TO_RENEW, "no connection to renew");
        assert_eq!(
            SESSION_ENDED,
            "the session ended unexpectedly; the output is left in its last state"
        );
        assert_eq!(
            DISCONNECT_UNASKED,
            "the supply had just connected and its output may be on; the output is left as it \
             is and the next connection will warn"
        );
        assert_eq!(
            ROWS_DROPPED,
            "rows were dropped: the file is not keeping up"
        );
        assert_eq!(NO_HOME, "the OS reports no home directory");
    }

    /// Test: UT-APP-023
    #[test]
    fn the_composed_texts_of_banners_and_log_lines() {
        let p = PathBuf::from("p");
        assert_eq!(recording_saved(10, &p), "recording saved: 10 rows in p");
        assert_eq!(disconnect_error("store: x"), "Disconnect: store: x");
        assert_eq!(
            connect_failed("the supply", "x"),
            "Could not connect to the supply: x"
        );
        assert_eq!(
            command_failed(What::SetVoltage, ErrorKind::RemoteControlDenied, "x"),
            "set voltage failed: x"
        );
        assert_eq!(
            command_failed(What::OutputOff, ErrorKind::Mode, "x"),
            "output off failed: x. Switch the output off on the supply."
        );
        assert_eq!(
            command_failed(What::OutputOff, ErrorKind::Timeout, "x"),
            "output off failed: x"
        );
        assert_eq!(
            done_line(What::OutputOff, 143, &Ok(())),
            "output off acknowledged after 143 ms"
        );
        assert_eq!(
            done_line(What::SetVoltage, 7, &Ok(())),
            "set voltage done after 7 ms"
        );
        let cancelled = ErrorText {
            text: "c".to_string(),
            kind: ErrorKind::Cancelled,
        };
        assert_eq!(
            done_line(What::SetVoltage, 7, &Err(cancelled)),
            "set voltage cancelled after 7 ms: c"
        );
        assert_eq!(
            done_line(What::OutputOff, 9, &Err(ErrorText::app("x"))),
            "output off failed after 9 ms: x"
        );
        assert_eq!(
            off_failed(OFF_UNCONFIRMED),
            "The output could not be switched off (no reading confirmed it). It may still \
             be on: switch it off on the supply."
        );
        assert_eq!(
            setpoints_changed(12.0, 1.0, 5.0, 1.0),
            "The supply's setpoints are 12.00 V and 1.000 A, not the expected 5.00 V and \
             1.000 A."
        );
        assert_eq!(unclean_exit("s", "T"), "s: T");
        assert_eq!(
            recording_stopped("disk full", 2, &p),
            "Recording stopped: disk full. 2 rows are in p."
        );
        assert_eq!(fatal("x"), "The app cannot work: x");
        assert_eq!(
            readings_dropped(12),
            "12 readings were not shown (the window fell behind)"
        );
        assert_eq!(
            close_not_dc(LiveMode::Pd),
            "The output is on and the supply is in PD mode, where the app cannot switch it \
             off. Switch it off on the supply, or disconnect and leave it on."
        );
        assert_eq!(
            close_stale(2),
            "The last reading is 2 s old, so the output may be on. Switch it off before \
             disconnecting?"
        );
    }

    /// Test: UT-APP-023
    #[test]
    fn the_notices() {
        assert_eq!(
            mode_notice(LiveMode::Pd),
            "The supply is in PD mode. The app controls it only in DC mode; switch the \
             output off on the supply."
        );
        assert_eq!(
            limit_notice(13.0, 1.0),
            "The supply's setpoints (13.00 V, 1.000 A) exceed your limits; set lower \
             values before switching the output on."
        );
        assert_eq!(
            remote_notice(RemoteState::Denied),
            Some(
                "The supply denied remote control. Press Request remote control to ask \
                 again."
            )
        );
        assert_eq!(
            remote_notice(RemoteState::Lost),
            Some("Remote control was lost. Press Request remote control to take it again.")
        );
        assert_eq!(remote_notice(RemoteState::Granted), None);
    }

    /// Test: UT-APP-023
    #[test]
    fn the_texts_of_the_redesigned_screen() {
        assert_eq!(transport_name(Kind::Hid), "USB");
        assert_eq!(transport_name(Kind::Ble), "Bluetooth");
        assert_eq!(watts_number(617), "6.17");
        assert_eq!(watts_number(15_000), "150.00");
        assert_eq!(
            field_error_line("Voltage (V)", "not a number"),
            "Voltage (V): not a number"
        );
        assert_eq!(
            pending_line(What::SetVoltage),
            "Waiting for the supply: set voltage"
        );
        assert_eq!(found_hint("A1B", "on"), "Unit A1B, remote control flag on");
        assert_eq!(axis_seconds(-30.0), "-30 s");
        assert_eq!(axis_seconds(-0.0), "0 s");
        assert_eq!(axis_value(12.0, 5.0), "12");
        assert_eq!(axis_value(0.25, 0.05), "0.25");
        assert_eq!(axis_value(-0.0, 0.1), "0.0");
    }
}
