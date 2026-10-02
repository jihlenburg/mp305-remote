//! Implements: DD-APP-020, DD-APP-021.
//!
//! What the UI can ask for, its translation into commands, and the close
//! step that decides, once per frame, what a window close request does.
//! Both are pure functions over the model and the same predicates the
//! screens use for their enabled states, so every rule about what a click
//! may send and when the window may close is tested here; the drawing code
//! only reports clicks (SR-030, SR-041).

use core::time::Duration;
use std::path::PathBuf;
use std::time::SystemTime;

use mp305_core::discovery::ScanOptions;
use tokio::time::Instant;

use crate::fields::{FieldKind, FieldState};
use crate::model::{
    BannerKind, CloseOrigin, Limits, Model, Pending, Phase, RecordingState, SCAN_S_RANGE,
};
use crate::paths;
use crate::worker::Command;

/// How long a close without switch-off may take before the window closes
/// anyway, and a close with switch-off before `Close anyway` is offered,
/// counted only while no prompt is open (DD-APP-021).
pub const CLOSE_BOUND: Duration = Duration::from_secs(5);

/// The shortest and longest chart window in seconds (UR-013).
const WINDOW_S: (u32, u32) = (10, 600);

/// The two clocks, read once per call by [`Clock::now`].
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct Clock {
    /// The Tokio clock (the session's stamps are on it).
    pub now: Instant,
    /// The wall clock.
    pub wall: SystemTime,
}

impl Clock {
    /// Both clocks now.
    #[must_use]
    pub fn now() -> Clock {
        Clock {
            now: Instant::now(),
            wall: SystemTime::now(),
        }
    }
}

/// Hands out command ids from 1.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct IdSource {
    /// The id handed out last.
    last: u64,
}

impl Default for IdSource {
    fn default() -> Self {
        Self::new()
    }
}

impl IdSource {
    /// A source whose first id is 1.
    #[must_use]
    pub fn new() -> IdSource {
        IdSource { last: 0 }
    }

    /// The next id.
    pub fn next_id(&mut self) -> u64 {
        self.last = self.last.saturating_add(1);
        self.last
    }
}

/// The user's answer to the close question.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum CloseChoice {
    /// Switch the output off, then disconnect.
    SwitchOff,
    /// Disconnect and leave the output as it is.
    LeaveOn,
    /// Do not disconnect.
    Cancel,
}

/// What the UI can ask for (DD-APP-020).
#[derive(Clone, Debug, PartialEq)]
pub enum UiAction {
    /// Start a scan.
    Scan,
    /// Set the scan time in seconds.
    SetScanTime(u32),
    /// Select the found row with this identifier.
    Select(String),
    /// Connect to the selected row.
    Connect,
    /// The user typed into a field.
    EditField(FieldKind, String),
    /// Apply the voltage field.
    ApplyVoltage,
    /// Apply the current field.
    ApplyCurrent,
    /// Apply the limit fields.
    ApplyLimits,
    /// Switch the output on.
    OutputOn,
    /// Switch the output off.
    OutputOff,
    /// Request remote control.
    RequestRemoteControl,
    /// Release remote control.
    ReleaseRemoteControl,
    /// Switch reconnection on or off.
    SetReconnect(bool),
    /// Set the chart window in seconds.
    SetWindow(u32),
    /// Disconnect.
    Disconnect,
    /// The answer to the close question.
    CloseAnswer(CloseChoice),
    /// Close the window although the switch-off has not ended.
    CloseAnyway,
    /// Connect to the same supply again after a loss.
    Reconnect,
    /// The user typed into the recording path field.
    EditRecordingPath(String),
    /// Start a recording.
    StartRecording,
    /// Stop the recording.
    StopRecording,
    /// Dismiss a banner.
    Dismiss(BannerKind),
}

/// What the close step tells the glue.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum CloseStep {
    /// Nothing to do.
    Nothing,
    /// Cancel the window's close request.
    CancelClose,
    /// Close the window.
    CloseNow,
}

/// Turns `action` into commands; an action whose condition fails changes
/// nothing and yields nothing (DD-APP-020). Every command but `Scan` and
/// `Disconnect` is recorded in `pending` under its id until its `Done`.
pub fn handle(
    model: &mut Model,
    action: UiAction,
    clock: Clock,
    ids: &mut IdSource,
) -> Vec<Command> {
    match action {
        UiAction::Scan => scan(model, ids),
        UiAction::SetScanTime(seconds) => {
            model.scan_s = seconds.clamp(*SCAN_S_RANGE.start(), *SCAN_S_RANGE.end());
            Vec::new()
        }
        UiAction::Select(identifier) => {
            if model.phase == Phase::Idle && model.found.iter().any(|f| f.identifier == identifier)
            {
                model.selected = Some(identifier);
            }
            Vec::new()
        }
        UiAction::Connect => connect(model, clock, ids),
        UiAction::EditField(kind, text) => {
            let limits = model.limits;
            model.field_mut(kind).edit(text, kind, &limits);
            Vec::new()
        }
        UiAction::ApplyVoltage => match valid_value(model, FieldKind::Voltage) {
            Some(volts) => issue(model, clock, ids, None, |id| Command::SetVoltage {
                id,
                volts,
            }),
            None => Vec::new(),
        },
        UiAction::ApplyCurrent => match valid_value(model, FieldKind::Current) {
            Some(amps) => issue(model, clock, ids, None, |id| Command::SetCurrentLimit {
                id,
                amps,
            }),
            None => Vec::new(),
        },
        UiAction::ApplyLimits => apply_limits(model, clock, ids),
        UiAction::OutputOn => {
            if !model.output_on_enabled() {
                return Vec::new();
            }
            issue(model, clock, ids, None, |id| Command::OutputOn { id })
        }
        UiAction::OutputOff => {
            // Also outside DC mode: the session refuses with `Error::Mode`
            // before sending anything, and the `Done` tells the user what
            // to do (DD-APP-014).
            if !model.output_off_enabled() {
                return Vec::new();
            }
            issue(model, clock, ids, None, |id| Command::OutputOff { id })
        }
        UiAction::RequestRemoteControl => {
            if !model.request_remote_enabled() {
                return Vec::new();
            }
            issue(model, clock, ids, None, |id| {
                Command::RequestRemoteControl { id }
            })
        }
        UiAction::ReleaseRemoteControl => {
            if !model.release_remote_enabled() {
                return Vec::new();
            }
            issue(model, clock, ids, None, |id| {
                Command::ReleaseRemoteControl { id }
            })
        }
        UiAction::SetReconnect(on) => {
            model.reconnect = on;
            if has_session(model) {
                issue(model, clock, ids, None, |id| Command::SetReconnect {
                    id,
                    on,
                })
            } else {
                Vec::new()
            }
        }
        UiAction::SetWindow(seconds) => {
            model.window_s = seconds.clamp(WINDOW_S.0, WINDOW_S.1);
            Vec::new()
        }
        UiAction::Disconnect => disconnect(model, clock, ids),
        UiAction::CloseAnswer(CloseChoice::Cancel) => {
            model.close_dialog = None;
            model.close_pending = false;
            model.closing_since = None;
            Vec::new()
        }
        UiAction::CloseAnswer(choice) => {
            if model.close_dialog.is_none() || model.phase != Phase::Connected {
                return Vec::new();
            }
            model.close_dialog = None;
            let commands = begin_disconnect(model, ids, choice == CloseChoice::SwitchOff);
            if model.close_pending {
                model.closing_since = Some(clock.now);
            }
            commands
        }
        UiAction::CloseAnyway => {
            if model.close_anyway_enabled() {
                model.close_forced = true;
            }
            Vec::new()
        }
        UiAction::Reconnect => {
            if !model.reconnect_enabled() {
                return Vec::new();
            }
            // `sid` keeps the old session's number until the `Connecting`
            // of the new attempt, so a `Disconnect` during the reconnect's
            // close is answered for it.
            model.phase = Phase::Connecting;
            let (reconnect, limits) = (model.reconnect, model.limits);
            issue(model, clock, ids, None, |id| Command::Reconnect {
                id,
                reconnect,
                limits,
            })
        }
        UiAction::EditRecordingPath(text) => {
            model.recording_path = text;
            Vec::new()
        }
        UiAction::StartRecording => {
            if !model.recording_start_enabled() {
                return Vec::new();
            }
            let typed = model.recording_path.trim();
            let path = if typed.is_empty() {
                paths::default_recording_path(&model.recording_dir, clock.wall)
            } else {
                PathBuf::from(typed)
            };
            model.recording = RecordingState::Starting { path: path.clone() };
            issue(model, clock, ids, None, |id| Command::StartRecording {
                id,
                path,
            })
        }
        UiAction::StopRecording => {
            if !model.recording_stop_enabled() {
                return Vec::new();
            }
            issue(model, clock, ids, None, |id| Command::StopRecording { id })
        }
        UiAction::Dismiss(kind) => {
            model.dismiss(kind);
            Vec::new()
        }
    }
}

/// Builds the command of the next id with `make` and records it in
/// `pending` (with `limits` for a `SetLimits`).
fn issue(
    model: &mut Model,
    clock: Clock,
    ids: &mut IdSource,
    limits: Option<Limits>,
    make: impl FnOnce(u64) -> Command,
) -> Vec<Command> {
    let id = ids.next_id();
    let command = make(id);
    model.pending.insert(
        id,
        Pending {
            what: command.what(),
            sent: clock.now,
            limits,
        },
    );
    vec![command]
}

/// Whether a session is open or being opened, so that a command can reach
/// it.
fn has_session(model: &Model) -> bool {
    matches!(
        model.phase,
        Phase::Connecting | Phase::Connected | Phase::Lost { .. }
    )
}

/// The value of the setpoint field of `kind`, when it can be applied.
fn valid_value(model: &Model, kind: FieldKind) -> Option<f64> {
    if !model.apply_enabled(kind) {
        return None;
    }
    match model.field(kind).state {
        FieldState::Valid { value, .. } => Some(value),
        FieldState::Empty | FieldState::Invalid(_) => None,
    }
}

/// `Scan`: phase `Scanning` and the command; a scan has no `pending` entry
/// (its answer is the `ScanResult`).
fn scan(model: &mut Model, ids: &mut IdSource) -> Vec<Command> {
    if !model.scan_enabled() {
        return Vec::new();
    }
    let id = ids.next_id();
    model.phase = Phase::Scanning;
    model.scan_id = Some(id);
    model.scan_message = None;
    // `scan_s` is held within 1 to 60 s, so the duration is always in range.
    let options = ScanOptions::default()
        .with_duration(Duration::from_secs(u64::from(model.scan_s)))
        .unwrap_or_default();
    vec![Command::Scan { id, options }]
}

/// `Connect`: the limit fields are committed into the limits in force, and
/// the selected row is connected.
fn connect(model: &mut Model, clock: Clock, ids: &mut IdSource) -> Vec<Command> {
    if !model.connect_enabled() {
        return Vec::new();
    }
    let (Some(limits), Some(found)) = (model.limits_from_fields(), model.selected_found().cloned())
    else {
        return Vec::new();
    };
    model.limits = limits;
    model.reparse_setpoints();
    let identifier = found.identifier.clone();
    model.connected = Some(found);
    model.phase = Phase::Connecting;
    model.sid = None;
    let reconnect = model.reconnect;
    issue(model, clock, ids, None, |id| Command::Connect {
        id,
        identifier,
        reconnect,
        limits,
    })
}

/// `ApplyLimits`: without a session the limits take effect at once; with
/// one they take effect when the session accepted them (`Done` with `Ok`).
fn apply_limits(model: &mut Model, clock: Clock, ids: &mut IdSource) -> Vec<Command> {
    if !model.apply_limits_enabled() {
        return Vec::new();
    }
    let Some(new) = model.limits_from_fields() else {
        return Vec::new();
    };
    if has_session(model) {
        issue(model, clock, ids, Some(new), |id| Command::SetLimits {
            id,
            limits: new,
        })
    } else {
        model.limits = new;
        model.reparse_setpoints();
        Vec::new()
    }
}

/// `Disconnect`: in `Connected` with the output maybe on the question opens
/// and nothing is sent.
fn disconnect(model: &mut Model, clock: Clock, ids: &mut IdSource) -> Vec<Command> {
    match model.phase {
        Phase::Connecting | Phase::Lost { .. } => begin_unasked_disconnect(model, ids),
        Phase::Connected => {
            if model.output_maybe_on(clock.now) {
                if model.close_dialog.is_none() {
                    model.close_dialog = Some(CloseOrigin::Disconnect);
                }
                Vec::new()
            } else {
                begin_disconnect(model, ids, false)
            }
        }
        Phase::Idle | Phase::Scanning | Phase::Closing => Vec::new(),
    }
}

/// Sends `Disconnect { output_off }` and enters `Closing`; a disconnect
/// has no `pending` entry (its answer is the `Disconnected`).
fn begin_disconnect(model: &mut Model, ids: &mut IdSource, output_off: bool) -> Vec<Command> {
    let id = ids.next_id();
    model.phase = Phase::Closing;
    model.off_requested = output_off;
    vec![Command::Disconnect { id, output_off }]
}

/// Sends `DisconnectUnasked` and enters `Closing` with `off_requested`
/// false: in `Connecting` and `Lost` the app cannot ask, and the session
/// may have become ready an instant before, so the worker decides
/// (DD-APP-020, DD-APP-021, DD-APP-005). No `pending` entry.
fn begin_unasked_disconnect(model: &mut Model, ids: &mut IdSource) -> Vec<Command> {
    let id = ids.next_id();
    model.phase = Phase::Closing;
    model.off_requested = false;
    vec![Command::DisconnectUnasked { id }]
}

/// Decides what a window close request does, and runs the close bound
/// (DD-APP-021). Returns the step, the commands to send and whether to
/// bring the window forward.
///
/// In this order: (1) a committed close does nothing more; (2) a request
/// closes at once in `Idle` and `Scanning`, closes the session first in
/// `Connecting` and `Lost`, asks first in `Connected` when the output may
/// be on, and waits in `Closing`; (3) without a request, a forced close or
/// an ended session closes the window, and in `Closing` the bound of 5 s,
/// counted only while no prompt is open, closes a close without
/// switch-off or offers `Close anyway` for one with switch-off.
pub fn close_step(
    model: &mut Model,
    requested: bool,
    now: Instant,
    ids: &mut IdSource,
) -> (CloseStep, Vec<Command>, bool) {
    if model.close_committed {
        return (CloseStep::Nothing, Vec::new(), false);
    }
    if requested {
        return close_requested(model, now, ids);
    }
    if model.close_forced {
        model.close_committed = true;
        return (CloseStep::CloseNow, Vec::new(), false);
    }
    let waiting = model.close_pending && model.closing_since.is_some();
    if model.phase == Phase::Idle && waiting {
        // The `Disconnected`, `ConnectFailed` or `Fatal` came, and it was
        // not a failed switch-off, which clears both (DD-APP-011).
        model.close_committed = true;
        return (CloseStep::CloseNow, Vec::new(), false);
    }
    if model.phase == Phase::Closing && waiting && model.prompt.is_none() {
        let passed = model
            .closing_since
            .is_some_and(|since| now.saturating_duration_since(since) >= CLOSE_BOUND);
        if passed {
            if model.off_requested {
                // A switch-off is never cut silently: the screen offers
                // `Close anyway` (DD-APP-031).
                model.close_overdue = true;
                return (CloseStep::Nothing, Vec::new(), false);
            }
            model.close_committed = true;
            return (CloseStep::CloseNow, Vec::new(), false);
        }
    }
    (CloseStep::Nothing, Vec::new(), false)
}

/// Step (2) of [`close_step`]: the window's close request.
fn close_requested(
    model: &mut Model,
    now: Instant,
    ids: &mut IdSource,
) -> (CloseStep, Vec<Command>, bool) {
    match model.phase {
        Phase::Idle | Phase::Scanning => {
            model.close_committed = true;
            (CloseStep::Nothing, Vec::new(), false)
        }
        Phase::Connecting | Phase::Lost { .. } => {
            model.close_pending = true;
            let commands = begin_unasked_disconnect(model, ids);
            model.closing_since = Some(now);
            (CloseStep::CancelClose, commands, false)
        }
        Phase::Connected => {
            model.close_pending = true;
            if model.close_dialog.is_some() {
                (CloseStep::CancelClose, Vec::new(), true)
            } else if model.output_maybe_on(now) {
                // The bound does not run while the question is open.
                model.close_dialog = Some(CloseOrigin::Window);
                (CloseStep::CancelClose, Vec::new(), true)
            } else {
                let commands = begin_disconnect(model, ids, false);
                model.closing_since = Some(now);
                (CloseStep::CancelClose, commands, false)
            }
        }
        Phase::Closing => {
            model.close_pending = true;
            if model.closing_since.is_none() {
                model.closing_since = Some(now);
            }
            (CloseStep::CancelClose, Vec::new(), false)
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::fields::FieldState;
    use crate::model::{CloseOrigin, Limits, Pending, Phase, RecordingState, RemoteState};
    use crate::testkit::{at_s, clock_s, connected_model, found_a, found_b, r, t0, wall0};
    use crate::worker::{AppEvent, ErrorKind, ErrorText, UiReading, What};
    use mp305_core::discovery::ScanOptions;
    use mp305_core::session::{PromptKind, SessionEvent};
    use std::path::PathBuf;

    /// Applies `action` at `s` seconds with a fresh id source.
    fn one(m: &mut Model, action: UiAction, s: f64) -> Vec<Command> {
        handle(m, action, clock_s(s), &mut IdSource::new())
    }

    /// A model in `Idle` with `A` and `B` found.
    fn idle_found() -> Model {
        let mut m = Model::new(PathBuf::from("/rec"), t0());
        m.found = vec![found_a(), found_b()];
        m
    }

    /// The connected model with three pending commands.
    fn with_three_pending() -> Model {
        let mut m = connected_model();
        for id in 100..103 {
            m.pending.insert(
                id,
                Pending {
                    what: What::SetVoltage,
                    sent: at_s(0.5),
                    limits: None,
                },
            );
        }
        m
    }

    /// A lost connected model.
    fn lost() -> Model {
        let mut m = connected_model();
        m.phase = Phase::Lost {
            text: "L".into(),
            reconnecting: false,
            gave_up: None,
        };
        m
    }

    /// Test: UT-APP-005
    #[test]
    fn a_setpoint_is_sent_only_on_apply_and_the_field_follows_the_supply() {
        let mut m = connected_model();
        let mut ids = IdSource::new();
        let c = clock_s(1.0);
        for text in ["4", "4.", "4.5"] {
            let sent = handle(
                &mut m,
                UiAction::EditField(FieldKind::Voltage, text.into()),
                c,
                &mut ids,
            );
            assert!(sent.is_empty());
        }
        assert!(m.voltage.edited);
        assert!(matches!(
            m.voltage.state,
            FieldState::Valid { raw: 450, .. }
        ));
        let sent = handle(&mut m, UiAction::ApplyVoltage, c, &mut ids);
        assert_eq!(sent, vec![Command::SetVoltage { id: 1, volts: 4.5 }]);
        assert_eq!(
            m.pending.get(&1),
            Some(&Pending {
                what: What::SetVoltage,
                sent: at_s(1.0),
                limits: None
            })
        );
        let apply_reading = |m: &mut Model, set_v: u16, s: f64| {
            m.apply(
                UiReading {
                    sid: 1,
                    reading: r(0, 0, 0, set_v, 1000, at_s(s)),
                },
                at_s(s),
            );
        };
        apply_reading(&mut m, 1300, 1.2);
        assert_eq!(m.voltage.text, "4.5");
        assert!(m.voltage.edited);
        apply_reading(&mut m, 450, 1.5);
        assert!(!m.voltage.edited);
        assert_eq!(m.voltage.text, "4.50");
        apply_reading(&mut m, 460, 1.8);
        assert_eq!(m.voltage.text, "4.60");

        handle(
            &mut m,
            UiAction::EditField(FieldKind::Voltage, "31".into()),
            c,
            &mut ids,
        );
        assert_eq!(
            m.voltage.state,
            FieldState::Invalid("voltage 31 is outside 0 to 30".into())
        );
        assert!(handle(&mut m, UiAction::ApplyVoltage, c, &mut ids).is_empty());

        handle(
            &mut m,
            UiAction::EditField(FieldKind::Current, "0.1".into()),
            c,
            &mut ids,
        );
        let sent = handle(&mut m, UiAction::ApplyCurrent, c, &mut ids);
        assert_eq!(sent, vec![Command::SetCurrentLimit { id: 2, amps: 0.1 }]);

        handle(
            &mut m,
            UiAction::EditField(FieldKind::MaxVoltage, "5".into()),
            c,
            &mut ids,
        );
        let five = Limits {
            max_volts: Some(5.0),
            max_amps: None,
        };
        let sent = handle(&mut m, UiAction::ApplyLimits, c, &mut ids);
        assert_eq!(
            sent,
            vec![Command::SetLimits {
                id: 3,
                limits: five
            }]
        );
        assert_eq!(m.pending.get(&3).and_then(|p| p.limits), Some(five));
        assert_eq!(m.limits, Limits::none());
        assert_eq!(m.hint(FieldKind::Voltage), "0 to 30 V");
        m.apply(
            AppEvent::Done {
                id: 3,
                what: What::SetLimits,
                result: Ok(()),
            },
            at_s(1.9),
        );
        assert_eq!(m.limits.max_volts, Some(5.0));
        assert_eq!(m.hint(FieldKind::Voltage), "0 to 30 V, your limit 5 V");
        assert_eq!(m.limits_text(), "in force: 5 V, none");

        handle(
            &mut m,
            UiAction::EditField(FieldKind::Voltage, "6".into()),
            c,
            &mut ids,
        );
        assert_eq!(
            m.voltage.state,
            FieldState::Invalid("voltage 6 is outside 0 to 5".into())
        );
        assert!(handle(&mut m, UiAction::ApplyVoltage, c, &mut ids).is_empty());

        handle(
            &mut m,
            UiAction::EditField(FieldKind::MaxCurrent, "abc".into()),
            c,
            &mut ids,
        );
        assert!(handle(&mut m, UiAction::ApplyLimits, c, &mut ids).is_empty());
        assert_eq!(m.limits.max_volts, Some(5.0));
        assert!(!m.apply_limits_enabled());

        let mut idle = Model::new(PathBuf::from("/rec"), t0());
        handle(
            &mut idle,
            UiAction::EditField(FieldKind::MaxVoltage, "12".into()),
            c,
            &mut ids,
        );
        assert!(handle(&mut idle, UiAction::ApplyLimits, c, &mut ids).is_empty());
        assert_eq!(idle.limits.max_volts, Some(12.0));
    }

    /// Test: UT-APP-006
    #[test]
    fn scan_and_its_settings() {
        let mut m = Model::new(PathBuf::from("/rec"), t0());
        let mut ids = IdSource::new();
        let sent = handle(&mut m, UiAction::Scan, clock_s(0.0), &mut ids);
        assert_eq!(m.phase, Phase::Scanning);
        assert_eq!(m.scan_id, Some(1));
        let options = ScanOptions::default()
            .with_duration(Duration::from_secs(10))
            .unwrap();
        assert_eq!(sent, vec![Command::Scan { id: 1, options }]);
        assert!(options.bluetooth && options.usb);
        assert!(m.pending.is_empty());
        assert!(handle(&mut m, UiAction::Scan, clock_s(0.0), &mut ids).is_empty());
        for (s, expected) in [(0, 1), (90, 60), (20, 20)] {
            assert!(one(&mut m, UiAction::SetScanTime(s), 0.0).is_empty());
            assert_eq!(m.scan_s, expected);
        }
        // The one range the clamp and the slider use is the core's bound.
        let seconds = |d: Duration| u32::try_from(d.as_secs()).unwrap();
        assert_eq!(
            SCAN_S_RANGE,
            seconds(mp305_core::protocol::timing::SCAN_MIN)
                ..=seconds(mp305_core::protocol::timing::SCAN_MAX)
        );
    }

    /// Test: UT-APP-006
    #[test]
    fn select_and_connect() {
        let mut m = idle_found();
        let before = m.clone();
        assert!(one(&mut m, UiAction::Select("x".into()), 0.0).is_empty());
        assert_eq!(m, before);
        one(&mut m, UiAction::Select("A".into()), 0.0);
        assert_eq!(m.selected.as_deref(), Some("A"));
        let mut ids = IdSource::new();
        let c = clock_s(0.0);
        handle(
            &mut m,
            UiAction::EditField(FieldKind::MaxVoltage, "12".into()),
            c,
            &mut ids,
        );
        handle(
            &mut m,
            UiAction::EditField(FieldKind::MaxCurrent, String::new()),
            c,
            &mut ids,
        );
        let twelve = Limits {
            max_volts: Some(12.0),
            max_amps: None,
        };
        let sent = handle(&mut m, UiAction::Connect, c, &mut ids);
        assert_eq!(m.phase, Phase::Connecting);
        assert_eq!(m.limits, twelve);
        assert_eq!(m.connected, Some(found_a()));
        assert_eq!(
            sent,
            vec![Command::Connect {
                id: 1,
                identifier: "A".into(),
                reconnect: false,
                limits: twelve
            }]
        );
        assert!(m.pending.contains_key(&1));
        assert!(handle(&mut m, UiAction::Connect, c, &mut ids).is_empty());
    }

    /// Test: UT-APP-006
    #[test]
    fn output_on_and_off() {
        let mut m = connected_model();
        assert_eq!(
            one(&mut m, UiAction::OutputOn, 1.0),
            vec![Command::OutputOn { id: 1 }]
        );
        assert!(m.pending.contains_key(&1));
        let mut m = connected_model();
        m.apply(
            UiReading {
                sid: 1,
                reading: r(0, 0, 32, 1300, 1000, at_s(1.0)),
            },
            at_s(1.0),
        );
        assert!(one(&mut m, UiAction::OutputOn, 1.0).is_empty());
        let mut idle = Model::new(PathBuf::from("/rec"), t0());
        assert!(one(&mut idle, UiAction::OutputOn, 1.0).is_empty());

        let mut m = with_three_pending();
        assert_eq!(
            one(&mut m, UiAction::OutputOff, 2.0),
            vec![Command::OutputOff { id: 1 }]
        );
        assert_eq!(
            m.pending.get(&1),
            Some(&Pending {
                what: What::OutputOff,
                sent: at_s(2.0),
                limits: None
            })
        );
        let mut m = lost();
        assert!(one(&mut m, UiAction::OutputOff, 2.0).is_empty());
        let mut m = with_three_pending();
        m.apply(
            UiReading {
                sid: 1,
                reading: r(1, 2, 0, 1300, 1000, at_s(1.0)),
            },
            at_s(1.0),
        );
        assert_eq!(
            one(&mut m, UiAction::OutputOff, 2.0),
            vec![Command::OutputOff { id: 1 }]
        );
    }

    /// Test: UT-APP-006
    #[test]
    fn remote_control_reconnect_flag_and_window() {
        let mut m = connected_model();
        m.remote = RemoteState::Denied;
        assert_eq!(
            one(&mut m, UiAction::RequestRemoteControl, 1.0),
            vec![Command::RequestRemoteControl { id: 1 }]
        );
        m.remote = RemoteState::Granted;
        assert!(one(&mut m, UiAction::RequestRemoteControl, 1.0).is_empty());
        assert_eq!(
            one(&mut m, UiAction::ReleaseRemoteControl, 1.0),
            vec![Command::ReleaseRemoteControl { id: 1 }]
        );
        m.remote = RemoteState::None;
        assert!(one(&mut m, UiAction::ReleaseRemoteControl, 1.0).is_empty());

        let mut idle = Model::new(PathBuf::from("/rec"), t0());
        assert!(one(&mut idle, UiAction::SetReconnect(true), 1.0).is_empty());
        assert!(idle.reconnect);
        let mut m = connected_model();
        assert_eq!(
            one(&mut m, UiAction::SetReconnect(true), 1.0),
            vec![Command::SetReconnect { id: 1, on: true }]
        );
        assert!(m.pending.contains_key(&1));

        for (s, expected) in [(5, 10), (700, 600), (120, 120)] {
            assert!(one(&mut m, UiAction::SetWindow(s), 1.0).is_empty());
            assert_eq!(m.window_s, expected);
        }
    }

    /// Test: UT-APP-006
    #[test]
    fn recording_start_and_stop() {
        let mut m = connected_model();
        let c = Clock {
            now: at_s(1.0),
            wall: wall0(),
        };
        let sent = handle(&mut m, UiAction::StartRecording, c, &mut IdSource::new());
        let auto = PathBuf::from("/rec/mp305-20261001-100000.csv");
        assert_eq!(
            sent,
            vec![Command::StartRecording {
                id: 1,
                path: auto.clone()
            }]
        );
        assert_eq!(m.recording, RecordingState::Starting { path: auto });
        assert!(m.pending.contains_key(&1));
        m.recording = RecordingState::Off;
        one(
            &mut m,
            UiAction::EditRecordingPath(" /x/a.csv ".into()),
            1.0,
        );
        assert_eq!(
            handle(&mut m, UiAction::StartRecording, c, &mut IdSource::new()),
            vec![Command::StartRecording {
                id: 1,
                path: PathBuf::from("/x/a.csv")
            }]
        );
        m.recording = RecordingState::On {
            path: PathBuf::from("/x/a.csv"),
            rows: 3,
        };
        assert!(one(&mut m, UiAction::StartRecording, 1.0).is_empty());
        assert_eq!(
            one(&mut m, UiAction::StopRecording, 1.0),
            vec![Command::StopRecording { id: 1 }]
        );
        m.recording = RecordingState::Off;
        assert!(one(&mut m, UiAction::StopRecording, 1.0).is_empty());
    }

    /// Test: UT-APP-006
    #[test]
    fn dismiss_reconnect_and_disconnect() {
        let mut m = connected_model();
        m.banners.push(crate::model::Banner {
            kind: BannerKind::Error,
            text: "e".into(),
        });
        one(&mut m, UiAction::Dismiss(BannerKind::Error), 1.0);
        assert!(m.banners.is_empty());
        one(&mut m, UiAction::Dismiss(BannerKind::UncleanExit), 1.0);
        assert!(m.unclean_exit_acknowledged);

        let mut m = lost();
        m.connected = Some(found_a());
        let sent = one(&mut m, UiAction::Reconnect, 1.0);
        assert_eq!(m.phase, Phase::Connecting);
        assert_eq!(m.sid, Some(1));
        assert_eq!(
            sent,
            vec![Command::Reconnect {
                id: 1,
                reconnect: false,
                limits: Limits::none()
            }]
        );
        assert!(m.pending.contains_key(&1));
        let mut m = connected_model();
        assert!(one(&mut m, UiAction::Reconnect, 1.0).is_empty());

        let mut connecting = connected_model();
        connecting.phase = Phase::Connecting;
        for mut m in [connecting, lost()] {
            // UT-APP-006 (k) of revision 3 still names `Disconnect { 1, false }`;
            // DD-APP-020 (rev 3) and UT-APP-025 (e) give `DisconnectUnasked`
            // in `Connecting` and `Lost`. The design, the safer reading, is
            // tested; the entry is reported as inconsistent.
            assert_eq!(
                one(&mut m, UiAction::Disconnect, 1.0),
                vec![Command::DisconnectUnasked { id: 1 }]
            );
            assert!(m.pending.is_empty());
            assert_eq!(m.phase, Phase::Closing);
            assert!(!m.off_requested);
        }
    }

    /// Test: UT-APP-006
    #[test]
    fn apply_limits_while_connected_waits_for_the_session() {
        let five = Limits {
            max_volts: Some(5.0),
            max_amps: None,
        };
        let mut connecting = connected_model();
        connecting.phase = Phase::Connecting;
        for mut m in [connecting, lost(), connected_model()] {
            one(
                &mut m,
                UiAction::EditField(FieldKind::MaxVoltage, "5".into()),
                1.0,
            );
            let sent = one(&mut m, UiAction::ApplyLimits, 1.0);
            assert_eq!(
                sent,
                vec![Command::SetLimits {
                    id: 1,
                    limits: five
                }]
            );
            assert_eq!(m.pending.get(&1).and_then(|p| p.limits), Some(five));
            assert_eq!(m.limits, Limits::none());
            m.apply(
                AppEvent::Done {
                    id: 1,
                    what: What::SetLimits,
                    result: Err(ErrorText {
                        text: "x".into(),
                        kind: ErrorKind::SetpointRange,
                    }),
                },
                at_s(1.1),
            );
            assert_eq!(m.limits, Limits::none());
            assert_eq!(
                m.banners.last().map(|b| b.text.as_str()),
                Some("set limits failed: x")
            );
        }
    }

    /// The connected model with the reading `r(1, 0, 0, 1300, 1000, 9.8 s)`.
    fn on_at_9_8() -> Model {
        let mut m = connected_model();
        m.apply(
            UiReading {
                sid: 1,
                reading: r(1, 0, 0, 1300, 1000, at_s(9.8)),
            },
            at_s(9.8),
        );
        m
    }

    /// `t` is 10 s.
    const T: f64 = 10.0;

    /// The close step at `T + dt`.
    fn step(m: &mut Model, requested: bool, dt: f64) -> (CloseStep, Vec<Command>, bool) {
        close_step(m, requested, at_s(T + dt), &mut IdSource::new())
    }

    /// The `Disconnect` command with id 1.
    fn disconnect(output_off: bool) -> Vec<Command> {
        vec![Command::Disconnect { id: 1, output_off }]
    }

    /// The `DisconnectUnasked` command with id 1.
    fn unasked_disconnect() -> Vec<Command> {
        vec![Command::DisconnectUnasked { id: 1 }]
    }

    /// Runs case (b): a close request with the output on, then the bound.
    fn case_b() -> Model {
        let mut m = on_at_9_8();
        assert_eq!(
            step(&mut m, true, 0.0),
            (CloseStep::CancelClose, vec![], true)
        );
        assert_eq!(m.close_dialog, Some(CloseOrigin::Window));
        assert!(m.close_pending);
        assert_eq!(m.closing_since, None);
        assert_eq!(
            step(&mut m, false, 6.0),
            (CloseStep::Nothing, vec![], false)
        );
        assert_eq!(
            step(&mut m, true, 7.0),
            (CloseStep::CancelClose, vec![], true)
        );
        m
    }

    /// Applies the answer `choice` at `T + dt`.
    fn answer(m: &mut Model, choice: CloseChoice, dt: f64) -> Vec<Command> {
        one(m, UiAction::CloseAnswer(choice), T + dt)
    }

    /// A `Disconnected` of attempt 1.
    fn disconnected(text: Option<&str>, off_requested: bool, output_on: Option<bool>) -> AppEvent {
        AppEvent::Disconnected {
            sid: Some(1),
            text: text.map(str::to_string),
            off_requested,
            output_on,
        }
    }

    /// Test: UT-APP-007
    #[test]
    fn a_close_request_in_idle_closes_at_once() {
        let mut m = Model::new(PathBuf::from("/rec"), t0());
        for _ in 0..2 {
            assert_eq!(step(&mut m, true, 0.0), (CloseStep::Nothing, vec![], false));
            assert!(m.close_committed);
        }
    }

    /// Test: UT-APP-007
    #[test]
    fn a_close_with_switch_off_is_never_cut_silently() {
        let mut m = case_b();
        assert_eq!(
            answer(&mut m, CloseChoice::SwitchOff, 10.0),
            disconnect(true)
        );
        assert_eq!(m.phase, Phase::Closing);
        assert!(m.off_requested);
        assert_eq!(m.closing_since, Some(at_s(T + 10.0)));
        assert_eq!(
            step(&mut m, false, 12.0),
            (CloseStep::Nothing, vec![], false)
        );
        assert_eq!(
            m.repaint_after(at_s(T + 12.0)),
            Some(Duration::from_secs(3))
        );
        assert_eq!(
            step(&mut m, false, 15.1),
            (CloseStep::Nothing, vec![], false)
        );
        assert!(m.close_overdue);
        assert!(one(&mut m, UiAction::CloseAnyway, T + 15.1).is_empty());
        assert!(m.close_forced);
        assert_eq!(
            step(&mut m, false, 15.2),
            (CloseStep::CloseNow, vec![], false)
        );
        assert!(m.close_committed);
        assert_eq!(
            step(&mut m, true, 15.3),
            (CloseStep::Nothing, vec![], false)
        );
    }

    /// Test: UT-APP-007
    #[test]
    fn a_confirmed_switch_off_closes_the_window() {
        let mut m = case_b();
        answer(&mut m, CloseChoice::SwitchOff, 10.0);
        m.apply(disconnected(None, true, Some(false)), at_s(T + 11.0));
        assert_eq!(
            step(&mut m, false, 11.0),
            (CloseStep::CloseNow, vec![], false)
        );
    }

    /// Test: UT-APP-007
    #[test]
    fn leave_on_is_cut_after_the_bound() {
        let mut m = case_b();
        assert_eq!(
            answer(&mut m, CloseChoice::LeaveOn, 10.0),
            disconnect(false)
        );
        assert_eq!(
            step(&mut m, false, 15.1),
            (CloseStep::CloseNow, vec![], false)
        );
    }

    /// Test: UT-APP-007
    #[test]
    fn the_bound_does_not_run_while_a_prompt_is_open() {
        let mut m = case_b();
        answer(&mut m, CloseChoice::SwitchOff, 10.0);
        m.apply(
            AppEvent::Session {
                sid: 1,
                event: SessionEvent::Prompt {
                    kind: PromptKind::AllowRemoteControl,
                    bound_s: 70,
                    text: "allow",
                },
            },
            at_s(T + 11.0),
        );
        assert_eq!(
            step(&mut m, false, 20.0),
            (CloseStep::Nothing, vec![], false)
        );
        assert!(!m.close_overdue);
        m.apply(
            AppEvent::Session {
                sid: 1,
                event: SessionEvent::RemoteControl(RemoteState::Granted),
            },
            at_s(T + 21.0),
        );
        assert_eq!(m.closing_since, Some(at_s(T + 21.0)));
        assert_eq!(
            step(&mut m, false, 25.9),
            (CloseStep::Nothing, vec![], false)
        );
        assert!(!m.close_overdue);
        assert_eq!(
            step(&mut m, false, 26.1),
            (CloseStep::Nothing, vec![], false)
        );
        assert!(m.close_overdue);
    }

    /// Test: UT-APP-007
    #[test]
    fn a_failed_switch_off_keeps_the_window_open() {
        let mut m = case_b();
        answer(&mut m, CloseChoice::SwitchOff, 10.0);
        let e = "the supply rejected the command (status 0xff, busy)";
        m.apply(disconnected(Some(e), true, Some(true)), at_s(T + 11.0));
        assert_eq!(m.phase, Phase::Idle);
        assert_eq!(
            m.banners.last().map(|b| b.text.as_str()),
            Some(
                "The output could not be switched off (the supply rejected the command \
                 (status 0xff, busy)). It may still be on: switch it off on the supply."
            )
        );
        assert!(!m.close_pending);
        assert_eq!(
            step(&mut m, false, 12.0),
            (CloseStep::Nothing, vec![], false)
        );
        assert!(!m.close_committed);
        assert_eq!(
            step(&mut m, true, 13.0),
            (CloseStep::Nothing, vec![], false)
        );
        assert!(m.close_committed);
    }

    /// The `OffFailed` text of `reason`.
    fn off_failed(reason: &str) -> String {
        crate::texts::off_failed(reason)
    }

    /// The `OffFailed` banner of `m`.
    fn off_banner(m: &Model) -> Option<String> {
        m.banners
            .iter()
            .find(|b| b.kind == BannerKind::OffFailed)
            .map(|b| b.text.clone())
    }

    /// The connected model after `Disconnect` and `SwitchOff`.
    fn switching_off(m: &mut Model) {
        one(m, UiAction::Disconnect, T);
        answer(m, CloseChoice::SwitchOff, 0.5);
        assert_eq!(m.phase, Phase::Closing);
    }

    /// Test: UT-APP-007
    #[test]
    fn the_reasons_of_a_failed_switch_off() {
        let mut m = on_at_9_8();
        switching_off(&mut m);
        m.apply(disconnected(None, true, None), at_s(T + 1.0));
        assert_eq!(off_banner(&m), Some(off_failed("no reading confirmed it")));

        let mut m = on_at_9_8();
        switching_off(&mut m);
        m.apply(disconnected(None, true, Some(true)), at_s(T + 1.0));
        assert_eq!(
            off_banner(&m),
            Some(off_failed("the supply still reports the output on"))
        );

        let mut m = on_at_9_8();
        switching_off(&mut m);
        m.apply(
            UiReading {
                sid: 1,
                reading: r(1, 2, 0, 1300, 1000, at_s(T + 0.6)),
            },
            at_s(T + 0.6),
        );
        m.apply(disconnected(None, true, Some(true)), at_s(T + 1.0));
        assert_eq!(
            off_banner(&m),
            Some(off_failed("the supply is not in DC mode"))
        );

        let mut m = case_b();
        answer(&mut m, CloseChoice::SwitchOff, 10.0);
        m.apply(
            disconnected(Some("store: x"), true, Some(false)),
            at_s(T + 11.0),
        );
        assert_eq!(off_banner(&m), None);
        assert_eq!(
            m.banners.last().map(|b| b.text.as_str()),
            Some("Disconnect: store: x")
        );
        assert_eq!(
            step(&mut m, false, 11.0),
            (CloseStep::CloseNow, vec![], false)
        );
    }

    /// Test: UT-APP-007
    #[test]
    fn a_loss_during_the_question_closes_after_the_session() {
        let mut m = case_b();
        m.apply(
            AppEvent::Session {
                sid: 1,
                event: SessionEvent::LinkLost { text: "L".into() },
            },
            at_s(T + 1.0),
        );
        assert_eq!(m.close_dialog, None);
        assert!(!m.close_pending);
        assert!(matches!(m.phase, Phase::Lost { .. }));
        assert_eq!(
            step(&mut m, true, 2.0),
            (CloseStep::CancelClose, unasked_disconnect(), false)
        );
        assert_eq!(m.phase, Phase::Closing);
        assert_eq!(m.closing_since, Some(at_s(T + 2.0)));
        m.apply(disconnected(None, false, None), at_s(T + 2.1));
        assert_eq!(
            step(&mut m, false, 2.1),
            (CloseStep::CloseNow, vec![], false)
        );
    }

    /// Test: UT-APP-007
    #[test]
    fn cancel_keeps_the_window_and_the_connection() {
        let mut m = case_b();
        assert!(answer(&mut m, CloseChoice::Cancel, 8.0).is_empty());
        assert_eq!(m.close_dialog, None);
        assert!(!m.close_pending);
        assert_eq!(m.phase, Phase::Connected);
    }

    /// Test: UT-APP-007
    #[test]
    fn when_the_close_asks() {
        let mut m = connected_model();
        m.apply(
            UiReading {
                sid: 1,
                reading: r(0, 0, 0, 1300, 1000, at_s(9.8)),
            },
            at_s(9.8),
        );
        assert_eq!(
            step(&mut m, true, 0.0),
            (CloseStep::CancelClose, disconnect(false), false)
        );

        let mut m = connected_model();
        m.apply(
            UiReading {
                sid: 1,
                reading: r(0, 0, 0, 1300, 1000, at_s(9.8)),
            },
            at_s(9.8),
        );
        m.pending.insert(
            7,
            Pending {
                what: What::OutputOn,
                sent: at_s(9.0),
                limits: None,
            },
        );
        assert_eq!(
            step(&mut m, true, 0.0),
            (CloseStep::CancelClose, vec![], true)
        );
        let q = m.close_question(at_s(T)).unwrap();
        assert!(q.switch_off);
        assert_eq!(
            q.text,
            "An output-on command is still pending, so the output may be on. Switch it off \
             before disconnecting?"
        );

        let mut m = connected_model();
        m.apply(
            UiReading {
                sid: 1,
                reading: r(0, 0, 0, 1300, 1000, at_s(7.5)),
            },
            at_s(7.5),
        );
        assert_eq!(
            step(&mut m, true, 0.0),
            (CloseStep::CancelClose, vec![], true)
        );
        assert_eq!(
            m.close_question(at_s(T)).unwrap().text,
            "The last reading is 2 s old, so the output may be on. Switch it off before \
             disconnecting?"
        );

        let mut m = connected_model();
        m.apply(
            UiReading {
                sid: 1,
                reading: r(1, 2, 0, 1300, 1000, at_s(9.8)),
            },
            at_s(9.8),
        );
        assert_eq!(
            step(&mut m, true, 0.0),
            (CloseStep::CancelClose, vec![], true)
        );
        assert!(!m.close_question(at_s(T)).unwrap().switch_off);
    }

    /// Test: UT-APP-007
    #[test]
    fn a_window_close_during_a_disconnect_with_switch_off() {
        let mut m = on_at_9_8();
        assert!(one(&mut m, UiAction::Disconnect, T).is_empty());
        assert_eq!(m.close_dialog, Some(CloseOrigin::Disconnect));
        assert!(!m.close_pending);
        assert_eq!(
            answer(&mut m, CloseChoice::SwitchOff, 1.0),
            disconnect(true)
        );
        assert_eq!(m.closing_since, None);
        assert_eq!(
            step(&mut m, false, 60.0),
            (CloseStep::Nothing, vec![], false)
        );
        assert_eq!(
            step(&mut m, true, 61.0),
            (CloseStep::CancelClose, vec![], false)
        );
        assert!(m.close_pending);
        assert_eq!(m.closing_since, Some(at_s(T + 61.0)));
        assert_eq!(
            step(&mut m, false, 66.1),
            (CloseStep::Nothing, vec![], false)
        );
        assert!(m.close_overdue);
    }

    /// Test: UT-APP-007
    #[test]
    fn scanning_closes_at_once_and_connecting_after_the_session() {
        let mut m = Model::new(PathBuf::from("/rec"), t0());
        m.phase = Phase::Scanning;
        assert_eq!(step(&mut m, true, 0.0), (CloseStep::Nothing, vec![], false));
        assert!(m.close_committed);

        let mut m = Model::new(PathBuf::from("/rec"), t0());
        m.phase = Phase::Connecting;
        m.sid = Some(1);
        assert_eq!(
            step(&mut m, true, 0.0),
            (CloseStep::CancelClose, unasked_disconnect(), false)
        );
        m.apply(disconnected(None, false, None), at_s(T + 0.5));
        assert_eq!(
            step(&mut m, false, 0.5),
            (CloseStep::CloseNow, vec![], false)
        );
    }

    /// Test: UT-APP-025
    #[test]
    fn a_disconnect_during_a_reconnect() {
        let mut m = lost();
        let sent = one(&mut m, UiAction::Reconnect, 1.0);
        assert!(matches!(sent.as_slice(), [Command::Reconnect { .. }]));
        assert_eq!(m.phase, Phase::Connecting);
        assert_eq!(m.sid, Some(1));
        assert_eq!(one(&mut m, UiAction::Disconnect, 1.1), unasked_disconnect());
        assert_eq!(m.phase, Phase::Closing);
        m.apply(disconnected(None, false, None), at_s(1.2));
        assert_eq!(m.phase, Phase::Idle);
    }

    /// The connected, granted model with the reading
    /// `r(0, 0, 0, 1300, 1000, 9.8 s)` (output off).
    fn granted_off_at_9_8() -> Model {
        let mut m = connected_model();
        m.remote = RemoteState::Granted;
        m.apply(
            UiReading {
                sid: 1,
                reading: r(0, 0, 0, 1300, 1000, at_s(9.8)),
            },
            at_s(9.8),
        );
        m
    }

    /// The `OutputOn` action at `t` and its `Done` with `result` at
    /// `t + 0.05 s`.
    fn output_on_answered(m: &mut Model, result: Result<(), ErrorText>) {
        let sent = one(m, UiAction::OutputOn, T);
        assert_eq!(sent, vec![Command::OutputOn { id: 1 }]);
        m.apply(
            AppEvent::Done {
                id: 1,
                what: What::OutputOn,
                result,
            },
            at_s(T + 0.05),
        );
    }

    /// A reading with the output off at `t + dt`.
    fn off_reading(m: &mut Model, dt: f64) {
        m.apply(
            UiReading {
                sid: 1,
                reading: r(0, 0, 0, 1300, 1000, at_s(T + dt)),
            },
            at_s(T + dt),
        );
    }

    /// Test: UT-APP-026
    #[test]
    fn an_answered_output_on_may_have_put_the_output_on() {
        let err = |kind, text: &str| {
            Err(ErrorText {
                text: text.to_string(),
                kind,
            })
        };
        for result in [
            Ok(()),
            err(ErrorKind::Timeout, "no reply to 0xc8 within 1.0 s"),
            err(ErrorKind::NotReady, "the session is not ready for control"),
        ] {
            let mut m = granted_off_at_9_8();
            output_on_answered(&mut m, result.clone());
            assert!(m.output_maybe_on(at_s(T + 0.06)), "{result:?}");

            let mut asked = m.clone();
            assert!(one(&mut asked, UiAction::Disconnect, T + 0.06).is_empty());
            assert_eq!(asked.close_dialog, Some(CloseOrigin::Disconnect));
            assert_eq!(
                asked.close_question(at_s(T + 0.06)),
                Some(crate::model::CloseQuestion {
                    text: "An output-on command was just sent and no reading shows its effect \
                           yet, so the output may be on. Switch it off before disconnecting?"
                        .to_string(),
                    switch_off: true
                }),
                "{result:?}"
            );

            let mut closing = m.clone();
            assert_eq!(
                step(&mut closing, true, 0.06),
                (CloseStep::CancelClose, vec![], true),
                "{result:?}"
            );
            assert_eq!(closing.close_dialog, Some(CloseOrigin::Window));
        }
    }

    /// Test: UT-APP-026
    #[test]
    fn a_reading_after_the_settle_time_shows_the_output_on_effect() {
        let mut m = granted_off_at_9_8();
        output_on_answered(&mut m, Ok(()));
        // Arrived before `output_on_done` plus `SETTLE` (t + 0.15 s).
        off_reading(&mut m, 0.1);
        assert!(m.output_maybe_on(at_s(T + 0.1)));
        assert!(m.output_on_done.is_some());
        off_reading(&mut m, 0.15);
        assert!(!m.output_maybe_on(at_s(T + 0.15)));
        assert_eq!(m.output_on_done, None);
        assert_eq!(
            one(&mut m, UiAction::Disconnect, T + 0.15),
            disconnect(false)
        );
        assert_eq!(m.close_dialog, None);
    }

    /// Test: UT-APP-026
    #[test]
    fn a_new_connection_forgets_an_answered_output_on() {
        let mut m = granted_off_at_9_8();
        output_on_answered(&mut m, Ok(()));
        assert!(m.output_on_done.is_some());
        // `Connecting` applies in `Connecting` and `Closing` (DD-APP-011).
        m.phase = Phase::Connecting;
        m.apply(
            AppEvent::Connecting {
                sid: 2,
                identifier: "A".into(),
            },
            at_s(T + 0.2),
        );
        assert_eq!(m.output_on_done, None);
    }
}
