//! Implements: DD-APP-010, DD-APP-011, DD-APP-014 (the model's methods for
//! the screens).
//!
//! The non-drawing state of the app: what the screens show, the
//! enabled-state methods every control takes its state from, and
//! [`Model::apply`], the only function that changes the model from the
//! worker's events. The module re-exports the core data types the screens
//! show, so `ui/` names no core path.

use core::time::Duration;
use std::collections::{BTreeMap, VecDeque};
use std::path::PathBuf;

pub use mp305_core::discovery::Found;
pub use mp305_core::protocol::ops::info::Info;
pub use mp305_core::protocol::ops::settings::Settings;
pub use mp305_core::protocol::ops::telemetry::{Faults, LiveMode, Reading, RegulationMode};
pub use mp305_core::protocol::units::Limits;
pub use mp305_core::session::{PromptKind, RemoteState, TimedReading};
pub use mp305_core::transport::description::Kind;
/// The clock of the session's stamps, which the screens' functions take.
pub use tokio::time::Instant;

use mp305_core::protocol::timing;
use mp305_core::protocol::units::{RawCurrent, RawVoltage};
use mp305_core::session::SessionEvent;

use crate::actions::CLOSE_BOUND;
use crate::chart;
use crate::fields::{self, Field, FieldKind, FieldState};
use crate::texts::{self, label};
use crate::worker::{AppEvent, ErrorKind, ErrorText, RecordingEvent, UiReading, What};

/// One second, the repaint interval of the open close question.
const SECOND: Duration = Duration::from_secs(1);

/// The log target of the model's DEBUG lines (events it ignores).
pub const LOG_TARGET: &str = "mp305_app::model";

/// The log target of the command outcomes.
pub const COMMANDS_TARGET: &str = "mp305_app::commands";

/// The number of lines the event log keeps.
pub const LOG_LINES: usize = 200;

/// The whole seconds of a bound of the core's `protocol::timing`, so that
/// the number is written only there (AR-014).
const fn whole_seconds(bound: Duration) -> u32 {
    let seconds = bound.as_secs();
    if seconds > u32::MAX as u64 {
        u32::MAX
    } else {
        seconds as u32
    }
}

/// The default scan time in seconds (the core's `timing::SCAN_DEFAULT`).
pub const SCAN_S_DEFAULT: u32 = whole_seconds(timing::SCAN_DEFAULT);

/// The scan time range in seconds, 1 to 60 (SR-002; the core's
/// `timing::SCAN_MIN` and `timing::SCAN_MAX`): `SetScanTime` clamps to it
/// and the scan time slider offers it, so the range exists once.
pub const SCAN_S_RANGE: core::ops::RangeInclusive<u32> =
    whole_seconds(timing::SCAN_MIN)..=whole_seconds(timing::SCAN_MAX);

/// The default chart window in seconds.
pub const WINDOW_S_DEFAULT: u32 = 60;

/// How old a reading may be and still count as current.
const FRESH: Duration = Duration::from_secs(1);

/// Where the app is with the supply (DD-APP-010).
#[derive(Clone, Debug, PartialEq)]
pub enum Phase {
    /// No supply; scanning and connecting are possible.
    Idle,
    /// A scan runs.
    Scanning,
    /// A connection attempt runs.
    Connecting,
    /// A supply is connected.
    Connected,
    /// The link was lost.
    Lost {
        /// The session's loss text.
        text: String,
        /// Whether the session reconnects.
        reconnecting: bool,
        /// The session's give-up text, once it gave up.
        gave_up: Option<String>,
    },
    /// The session closes.
    Closing,
}

/// Which screen the phase shows.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Screen {
    /// The connection screen.
    Connection,
    /// The main screen.
    Main,
}

/// A prompt the supply shows.
#[derive(Clone, Debug, PartialEq)]
pub struct Prompt {
    /// Which prompt.
    pub kind: PromptKind,
    /// The session's text.
    pub text: &'static str,
    /// How long it waits, in seconds.
    pub bound_s: u32,
    /// When it appeared.
    pub since: Instant,
}

/// The kind of a stored banner.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum BannerKind {
    /// A previous session may have left the output on.
    UncleanExit,
    /// The setpoints differ from the expected ones.
    SetpointsChanged,
    /// A command or a step failed.
    Error,
    /// The output could not be switched off.
    OffFailed,
}

/// A stored banner; at most one per kind.
#[derive(Clone, Debug, PartialEq)]
pub struct Banner {
    /// Its kind.
    pub kind: BannerKind,
    /// Its text.
    pub text: String,
}

/// A command waiting for its `Done`.
#[derive(Clone, Debug, PartialEq)]
pub struct Pending {
    /// Its kind.
    pub what: What,
    /// When it was sent.
    pub sent: Instant,
    /// The new limits of a `SetLimits`.
    pub limits: Option<Limits>,
}

/// The recording as the model shows it.
#[derive(Clone, Debug, PartialEq)]
pub enum RecordingState {
    /// No recording.
    Off,
    /// Asked for, not yet open.
    Starting {
        /// The file.
        path: PathBuf,
    },
    /// Writing.
    On {
        /// The file.
        path: PathBuf,
        /// The rows written.
        rows: u64,
    },
}

/// What opened the close question.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum CloseOrigin {
    /// The window's close request.
    Window,
    /// The Disconnect button.
    Disconnect,
}

/// The close question's text and whether it offers a switch-off.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct CloseQuestion {
    /// The text.
    pub text: String,
    /// Whether `Switch off` is offered.
    pub switch_off: bool,
}

/// What a shown banner is.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum ShownKind {
    /// The fatal text.
    Fatal,
    /// The loss text.
    Loss,
    /// The reconnection line under the loss text.
    Reconnect,
    /// A stored banner.
    Banner(BannerKind),
    /// The notice outside DC mode.
    ModeNotice,
    /// The notice of setpoints above the user's limits.
    LimitNotice,
    /// The notice of a denied or lost grant.
    RemoteNotice,
}

/// A banner as the status area shows it.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Shown {
    /// What it is.
    pub kind: ShownKind,
    /// Its text.
    pub text: String,
    /// Whether it has a dismiss button.
    pub dismissible: bool,
}

/// What `apply` takes: an event or a reading.
#[derive(Clone, Debug, PartialEq)]
pub enum Incoming {
    /// An event of the event channel.
    Event(AppEvent),
    /// A reading of the reading channel.
    Reading(UiReading),
}

impl From<AppEvent> for Incoming {
    fn from(event: AppEvent) -> Self {
        Incoming::Event(event)
    }
}

impl From<UiReading> for Incoming {
    fn from(reading: UiReading) -> Self {
        Incoming::Reading(reading)
    }
}

/// The non-drawing state of the app (DD-APP-010).
#[derive(Clone, Debug, PartialEq)]
pub struct Model {
    /// Where the app is with the supply.
    pub phase: Phase,
    /// The current connection attempt's number.
    pub sid: Option<u64>,
    /// The row the user connected to.
    pub connected: Option<Found>,
    /// Why the worker cannot work.
    pub fatal: Option<String>,
    /// The supplies the last scan found.
    pub found: Vec<Found>,
    /// The id of the scan in flight.
    pub scan_id: Option<u64>,
    /// Why the last scan found nothing.
    pub scan_message: Option<String>,
    /// The scan time in seconds, 1 to 60.
    pub scan_s: u32,
    /// The identifier of the selected row.
    pub selected: Option<String>,
    /// The supply's info.
    pub info: Option<Info>,
    /// The transport kind.
    pub transport: Option<Kind>,
    /// The latest reading.
    pub reading: Option<TimedReading>,
    /// The remote-control state.
    pub remote: RemoteState,
    /// The supply settings last reported.
    pub settings: Option<Settings>,
    /// The prompt the supply shows.
    pub prompt: Option<Prompt>,
    /// The stored banners.
    pub banners: Vec<Banner>,
    /// Whether the user acknowledged the unclean-exit warning.
    pub unclean_exit_acknowledged: bool,
    /// The commands waiting for their `Done`, by id.
    pub pending: BTreeMap<u64, Pending>,
    /// The recording.
    pub recording: RecordingState,
    /// The recording path field; empty means an automatic name.
    pub recording_path: String,
    /// Where automatic recordings go.
    pub recording_dir: PathBuf,
    /// The limits in force.
    pub limits: Limits,
    /// Whether a lost link is reconnected.
    pub reconnect: bool,
    /// The chart window in seconds, 10 to 600.
    pub window_s: u32,
    /// The chart buffer.
    pub chart: chart::Buffer,
    /// The event log, the last 200 lines.
    pub log: VecDeque<String>,
    /// The voltage setpoint field.
    pub voltage: Field,
    /// The current limit field.
    pub current: Field,
    /// The maximum voltage field.
    pub max_voltage: Field,
    /// The maximum current field.
    pub max_current: Field,
    /// The open close question.
    pub close_dialog: Option<CloseOrigin>,
    /// Whether the window waits to close.
    pub close_pending: bool,
    /// Whether the close was to switch the output off.
    pub off_requested: bool,
    /// Whether the switch-off took longer than the close bound.
    pub close_overdue: bool,
    /// Whether the user chose `Close anyway`.
    pub close_forced: bool,
    /// Whether the window's close is decided.
    pub close_committed: bool,
    /// When the close bound started.
    pub closing_since: Option<Instant>,
    /// When the `Done` of the last `OutputOn` was applied, until a reading
    /// shows its effect (DD-APP-011): an answered output-on may have put
    /// the output on although no reading shows it yet.
    pub output_on_done: Option<Instant>,
    /// When the app started.
    pub started: Instant,
}

impl Model {
    /// A model in `Idle` with nothing found.
    #[must_use]
    pub fn new(recording_dir: PathBuf, started: Instant) -> Model {
        Model {
            phase: Phase::Idle,
            sid: None,
            connected: None,
            fatal: None,
            found: Vec::new(),
            scan_id: None,
            scan_message: None,
            scan_s: SCAN_S_DEFAULT,
            selected: None,
            info: None,
            transport: None,
            reading: None,
            remote: RemoteState::None,
            settings: None,
            prompt: None,
            banners: Vec::new(),
            unclean_exit_acknowledged: false,
            pending: BTreeMap::new(),
            recording: RecordingState::Off,
            recording_path: String::new(),
            recording_dir,
            limits: Limits::none(),
            reconnect: false,
            window_s: WINDOW_S_DEFAULT,
            chart: chart::Buffer::new(),
            log: VecDeque::with_capacity(LOG_LINES),
            voltage: Field::default(),
            current: Field::default(),
            max_voltage: Field::default(),
            max_current: Field::default(),
            close_dialog: None,
            close_pending: false,
            off_requested: false,
            close_overdue: false,
            close_forced: false,
            close_committed: false,
            closing_since: None,
            output_on_done: None,
            started,
        }
    }

    /// Changes the model from an event or a reading (DD-APP-011); every
    /// change is also written to the event log. An event of another
    /// attempt, or one that arrives in `Idle` or `Scanning`, is logged at
    /// DEBUG and ignored.
    pub fn apply(&mut self, input: impl Into<Incoming>, now: Instant) {
        match input.into() {
            Incoming::Reading(UiReading { sid, reading }) => {
                if !self.ignored(sid, "a reading") {
                    self.take_reading(reading);
                }
            }
            Incoming::Event(event) => self.apply_event(event, now),
        }
    }

    /// Whether an event of attempt `sid` is ignored: it belongs to another
    /// attempt, or the phase is `Idle` or `Scanning`.
    fn ignored(&self, sid: u64, what: &str) -> bool {
        let ignore = self.sid != Some(sid) || matches!(self.phase, Phase::Idle | Phase::Scanning);
        if ignore {
            log::debug!(
                target: LOG_TARGET,
                "{what} of attempt {sid} ignored (attempt {:?}, phase {:?})",
                self.sid,
                self.phase
            );
        }
        ignore
    }

    /// Applies one event of the event channel.
    fn apply_event(&mut self, event: AppEvent, now: Instant) {
        match event {
            AppEvent::ScanResult { id, found, message } => {
                self.on_scan_result(id, found, message, now);
            }
            AppEvent::Connecting { sid, .. } => self.on_connecting(sid, now),
            AppEvent::Session { sid, event } => {
                if !self.ignored(sid, "a session event") {
                    self.on_session(event, now);
                }
            }
            AppEvent::Ready {
                sid,
                info,
                reading,
                transport,
            } => {
                if !self.ignored(sid, "ready") {
                    self.on_ready(info, reading, transport, now);
                }
            }
            AppEvent::ConnectFailed { sid, text } => {
                if !self.ignored(sid, "a failed connect") {
                    self.on_connect_failed(&text, now);
                }
            }
            AppEvent::Done { id, what, result } => self.on_done(id, what, result, now),
            AppEvent::Disconnected {
                sid,
                text,
                off_requested,
                output_on,
            } => self.on_disconnected(sid, text, off_requested, output_on, now),
            AppEvent::Recording(event) => self.on_recording(event, now),
            AppEvent::ReadingsDropped { total } => {
                self.log_line(now, &texts::readings_dropped(total));
            }
            AppEvent::Fatal(text) => {
                self.log_line(now, &texts::fatal(&text));
                self.fatal = Some(text);
                self.phase = Phase::Idle;
            }
        }
    }

    /// `ScanResult`: only the answer to the scan in flight counts.
    fn on_scan_result(
        &mut self,
        id: u64,
        found: Vec<Found>,
        message: Option<String>,
        now: Instant,
    ) {
        if self.scan_id != Some(id) {
            log::debug!(target: LOG_TARGET, "the result of scan {id} ignored");
            return;
        }
        self.log_line(now, &texts::scan_line(found.len(), message.as_deref()));
        self.found = found;
        self.scan_message = message;
        self.scan_id = None;
        let still_found = self
            .selected
            .as_ref()
            .is_some_and(|s| self.found.iter().any(|f| &f.identifier == s));
        if !still_found {
            self.selected = None;
        }
        if self.phase == Phase::Scanning {
            self.phase = Phase::Idle;
        }
    }

    /// `Connecting`: the attempt's number and the per-connection reset.
    fn on_connecting(&mut self, sid: u64, now: Instant) {
        if !matches!(self.phase, Phase::Connecting | Phase::Closing) {
            log::debug!(target: LOG_TARGET, "connecting {sid} ignored in {:?}", self.phase);
            return;
        }
        self.sid = Some(sid);
        self.reset_connection(
            &[
                BannerKind::UncleanExit,
                BannerKind::SetpointsChanged,
                BannerKind::Error,
            ],
            true,
        );
        self.log_line(now, &texts::connecting(&self.supply_line()));
    }

    /// The per-connection reset: the connection's data cleared, `remote`
    /// `None`, the banners of `banners` removed, the close flags of the
    /// connection cleared, the chart cleared when `chart`, the setpoint
    /// fields empty. `pending` entries stay until their `Done`.
    fn reset_connection(&mut self, banners: &[BannerKind], chart: bool) {
        self.info = None;
        self.transport = None;
        self.reading = None;
        self.settings = None;
        self.prompt = None;
        self.remote = RemoteState::None;
        self.banners.retain(|b| !banners.contains(&b.kind));
        self.unclean_exit_acknowledged = false;
        self.off_requested = false;
        self.close_overdue = false;
        self.close_forced = false;
        self.close_dialog = None;
        self.output_on_done = None;
        if chart {
            self.chart.clear();
        }
        self.voltage.reset();
        self.current.reset();
    }

    /// A session event of the current attempt.
    fn on_session(&mut self, event: SessionEvent, now: Instant) {
        match event {
            SessionEvent::Reading(reading) => self.take_reading(reading),
            SessionEvent::FaultsChanged { faults, reading } => {
                self.take_reading(reading);
                self.log_line(now, &texts::faults_line(faults));
            }
            SessionEvent::SettingsChanged(settings) => {
                self.settings = Some(settings);
                self.log_line(now, texts::settings_line());
            }
            SessionEvent::BindResult { recognised } => {
                self.clear_prompt_of(PromptKind::ConfirmConnection, now);
                let line = if recognised {
                    texts::BIND_RECOGNISED
                } else {
                    texts::BIND_CONFIRMED
                };
                self.log_line(now, line);
            }
            SessionEvent::RemoteControl(state) => {
                self.remote = state;
                if state != RemoteState::Requested {
                    self.clear_prompt_of(PromptKind::AllowRemoteControl, now);
                }
                self.log_line(now, &texts::remote_line(state));
            }
            SessionEvent::Prompt {
                kind,
                bound_s,
                text,
            } => {
                self.prompt = Some(Prompt {
                    kind,
                    text,
                    bound_s,
                    since: now,
                });
                self.log_line(now, text);
            }
            SessionEvent::SetpointsChanged {
                set_volts,
                set_amps,
                expected_volts,
                expected_amps,
            } => {
                let text =
                    texts::setpoints_changed(set_volts, set_amps, expected_volts, expected_amps);
                self.log_line(now, &text);
                self.set_banner(BannerKind::SetpointsChanged, text);
            }
            SessionEvent::UncleanExitWarning { text, .. } => {
                let text = texts::unclean_exit(&self.supply_line(), &text);
                self.log_line(now, &text);
                self.set_banner(BannerKind::UncleanExit, text);
                self.unclean_exit_acknowledged = false;
            }
            SessionEvent::LinkLost { text } => self.on_link_lost(text, now),
            SessionEvent::Reconnected => {
                if matches!(self.phase, Phase::Lost { .. }) {
                    self.phase = Phase::Connected;
                    self.remote = RemoteState::None;
                    self.log_line(now, texts::RECONNECTED);
                } else {
                    log::debug!(target: LOG_TARGET, "reconnected ignored in {:?}", self.phase);
                }
            }
            SessionEvent::ReconnectGaveUp { text } => {
                if let Phase::Lost {
                    reconnecting,
                    gave_up,
                    ..
                } = &mut self.phase
                {
                    *gave_up = Some(text.clone());
                    *reconnecting = false;
                    self.log_line(now, &text);
                } else {
                    log::debug!(target: LOG_TARGET, "give-up ignored in {:?}", self.phase);
                }
            }
        }
    }

    /// `LinkLost`: in `Connected` the phase becomes `Lost` and the controls
    /// go off; elsewhere only a log line (the outcome follows).
    fn on_link_lost(&mut self, text: String, now: Instant) {
        self.log_line(now, &text);
        if self.phase != Phase::Connected {
            return;
        }
        self.phase = Phase::Lost {
            text,
            reconnecting: self.reconnect,
            gave_up: None,
        };
        self.prompt = None;
        self.remote = RemoteState::Lost;
        self.close_dialog = None;
        if self.close_pending {
            self.close_pending = false;
            self.closing_since = None;
        }
    }

    /// `Ready`: in `Connecting` the session is connected; in `Closing` the
    /// user cancelled while the connection completed, and the
    /// `Disconnected` follows.
    fn on_ready(
        &mut self,
        info: Info,
        reading: Option<TimedReading>,
        transport: Option<Kind>,
        now: Instant,
    ) {
        match self.phase {
            Phase::Connecting => {
                self.phase = Phase::Connected;
                self.info = Some(info);
                self.transport = transport;
                if let Some(reading) = reading {
                    self.take_reading(reading);
                }
                self.clear_prompt_of(PromptKind::ConfirmConnection, now);
                self.log_line(now, &texts::ready_line(&self.supply_line()));
            }
            Phase::Closing => self.log_line(now, texts::READY_WHILE_CLOSING),
            _ => log::debug!(target: LOG_TARGET, "ready ignored in {:?}", self.phase),
        }
    }

    /// `ConnectFailed`: back to `Idle` with the `Error` banner naming the
    /// supply.
    fn on_connect_failed(&mut self, text: &str, now: Instant) {
        if !matches!(self.phase, Phase::Connecting | Phase::Closing) {
            log::debug!(target: LOG_TARGET, "a failed connect ignored in {:?}", self.phase);
            return;
        }
        let banner = texts::connect_failed(&self.supply_line(), text);
        self.back_to_idle(&[], true);
        self.log_line(now, &banner);
        self.set_banner(BannerKind::Error, banner);
    }

    /// Phase `Idle` with the per-connection reset (removing `banners`,
    /// clearing the chart when `chart`), the attempt and the connected row
    /// cleared.
    fn back_to_idle(&mut self, banners: &[BannerKind], chart: bool) {
        self.phase = Phase::Idle;
        self.reset_connection(banners, chart);
        self.sid = None;
        self.connected = None;
    }

    /// `Done`: the entry leaves `pending`, the outcome is logged, and an
    /// error that the loss banner does not explain becomes the `Error`
    /// banner.
    fn on_done(&mut self, id: u64, what: What, result: Result<(), ErrorText>, now: Instant) {
        let Some(entry) = self.pending.remove(&id) else {
            self.log_line(now, &texts::stray_done(what, id));
            return;
        };
        if what == What::OutputOn {
            // Answered is not the same as shown by a reading, and a
            // timed-out command may still be applied (DD-APP-011).
            self.output_on_done = Some(now);
        }
        let ms = now.saturating_duration_since(entry.sent).as_millis();
        let line = texts::done_line(what, ms, &result);
        log::info!(target: COMMANDS_TARGET, "{line}");
        self.log_line(now, &line);
        match result {
            Ok(()) => {
                if what == What::SetLimits {
                    if let Some(limits) = entry.limits {
                        self.limits = limits;
                        self.reparse_setpoints();
                    }
                }
            }
            Err(e) if matches!(e.kind, ErrorKind::Cancelled | ErrorKind::LinkLost) => {}
            Err(e) => {
                let banner = texts::command_failed(what, e.kind, &e.text);
                if matches!(what, What::Connect | What::Reconnect)
                    && self.phase == Phase::Connecting
                {
                    // The per-connection reset, applied before the banner
                    // is set, so the banner stays (DD-APP-011, rev 3).
                    self.back_to_idle(
                        &[
                            BannerKind::UncleanExit,
                            BannerKind::SetpointsChanged,
                            BannerKind::Error,
                        ],
                        true,
                    );
                }
                if what == What::StartRecording {
                    self.recording = RecordingState::Off;
                }
                self.set_banner(BannerKind::Error, banner);
            }
        }
    }

    /// `Disconnected`: a switch-off that no reading confirmed keeps the
    /// window open with the `OffFailed` banner; then phase `Idle`.
    fn on_disconnected(
        &mut self,
        sid: Option<u64>,
        text: Option<String>,
        off_requested: bool,
        output_on: Option<bool>,
        now: Instant,
    ) {
        if sid.is_some() && sid != self.sid {
            log::debug!(target: LOG_TARGET, "disconnected of {sid:?} ignored");
            return;
        }
        let supply = self.supply_line();
        if off_requested && output_on != Some(false) {
            let not_dc = self
                .reading
                .is_some_and(|r| r.reading.live_mode != LiveMode::Dc);
            let reason = match &text {
                Some(text) => text.as_str(),
                None if not_dc => texts::OFF_NOT_DC,
                None if output_on == Some(true) => texts::OFF_STILL_ON,
                None => texts::OFF_UNCONFIRMED,
            };
            let banner = texts::off_failed(reason);
            self.log_line(now, &banner);
            self.set_banner(BannerKind::OffFailed, banner);
            self.close_pending = false;
            self.closing_since = None;
            self.close_overdue = false;
        } else if let Some(text) = &text {
            let banner = texts::disconnect_error(text);
            self.log_line(now, &banner);
            self.set_banner(BannerKind::Error, banner);
        }
        self.back_to_idle(
            &[BannerKind::UncleanExit, BannerKind::SetpointsChanged],
            false,
        );
        self.log_line(now, &texts::disconnected_line(&supply));
    }

    /// A recording event.
    fn on_recording(&mut self, event: RecordingEvent, now: Instant) {
        match event {
            RecordingEvent::On { path } => {
                self.log_line(now, &texts::recording_on(&path));
                self.recording = RecordingState::On { path, rows: 0 };
            }
            RecordingEvent::Progress { rows } => {
                if let RecordingState::On { rows: held, .. } = &mut self.recording {
                    *held = rows;
                }
            }
            RecordingEvent::Off { path, rows, error } => {
                self.recording = RecordingState::Off;
                match error {
                    None => self.log_line(now, &texts::recording_saved(rows, &path)),
                    Some(error) => {
                        let banner = texts::recording_stopped(&error, rows, &path);
                        self.log_line(now, &banner);
                        self.set_banner(BannerKind::Error, banner);
                    }
                }
            }
        }
    }

    /// A reading that is newer than the stored one replaces it, goes to
    /// the chart, and the setpoint fields follow it; an older or equal one
    /// is dropped.
    fn take_reading(&mut self, reading: TimedReading) {
        if self.reading.is_some_and(|held| reading.at <= held.at) {
            return;
        }
        self.reading = Some(reading);
        self.chart.push(&reading);
        let raw = reading.reading.raw;
        self.voltage
            .follow(FieldKind::Voltage, raw.set_voltage, &self.limits);
        self.current
            .follow(FieldKind::Current, raw.set_current, &self.limits);
        // A reading at or after `output_on_done` plus `SETTLE` shows what
        // the answered output-on did (DD-APP-011).
        let shows_it = self.output_on_done.is_some_and(|done| {
            reading
                .at
                .checked_duration_since(done)
                .is_some_and(|since| since >= timing::SETTLE)
        });
        if shows_it {
            self.output_on_done = None;
        }
    }

    /// Clears a prompt of `kind`, if one is open.
    fn clear_prompt_of(&mut self, kind: PromptKind, now: Instant) {
        if self.prompt.as_ref().is_some_and(|p| p.kind == kind) {
            self.clear_prompt(now);
        }
    }

    /// Clears the prompt; in `Closing` with the close bound started, the
    /// bound starts again now (DD-APP-021).
    fn clear_prompt(&mut self, now: Instant) {
        if self.prompt.take().is_some()
            && self.phase == Phase::Closing
            && self.closing_since.is_some()
        {
            self.closing_since = Some(now);
        }
    }

    /// Stores `text` as the banner of `kind`, replacing an older one.
    fn set_banner(&mut self, kind: BannerKind, text: String) {
        self.banners.retain(|b| b.kind != kind);
        self.banners.push(Banner { kind, text });
    }

    /// The stored banner of `kind`.
    fn banner(&self, kind: BannerKind) -> Option<&Banner> {
        self.banners.iter().find(|b| b.kind == kind)
    }

    /// A command could not reach the worker: the `Error` banner
    /// [`texts::WORKER_STOPPED`] (DD-APP-022, the dispatch).
    pub fn command_not_sent(&mut self, now: Instant) {
        self.log_line(now, texts::WORKER_STOPPED);
        self.set_banner(BannerKind::Error, texts::WORKER_STOPPED.to_string());
    }

    /// The worker is gone (its event channel closed, DD-APP-022,
    /// DD-APP-011): the fatal text [`texts::WORKER_STOPPED`], phase `Idle`,
    /// the prompt, the question and the pending commands gone, and the
    /// waiting window close cancelled, so that it does not complete and the
    /// user sees the text; the next close request finds `Idle` and closes.
    pub fn worker_stopped(&mut self) {
        self.fatal = Some(texts::WORKER_STOPPED.to_string());
        self.phase = Phase::Idle;
        self.prompt = None;
        self.close_dialog = None;
        self.pending.clear();
        self.close_pending = false;
        self.closing_since = None;
        self.close_overdue = false;
    }

    /// Removes the banner of `kind`; for `UncleanExit` also records the
    /// acknowledgement.
    pub fn dismiss(&mut self, kind: BannerKind) {
        self.banners.retain(|b| b.kind != kind);
        if kind == BannerKind::UncleanExit {
            self.unclean_exit_acknowledged = true;
        }
    }

    /// The field of `kind`.
    #[must_use]
    pub fn field(&self, kind: FieldKind) -> &Field {
        match kind {
            FieldKind::Voltage => &self.voltage,
            FieldKind::Current => &self.current,
            FieldKind::MaxVoltage => &self.max_voltage,
            FieldKind::MaxCurrent => &self.max_current,
        }
    }

    /// The field of `kind`, mutably.
    pub fn field_mut(&mut self, kind: FieldKind) -> &mut Field {
        match kind {
            FieldKind::Voltage => &mut self.voltage,
            FieldKind::Current => &mut self.current,
            FieldKind::MaxVoltage => &mut self.max_voltage,
            FieldKind::MaxCurrent => &mut self.max_current,
        }
    }

    /// The limits the limit fields hold, when none is invalid: `Empty` is
    /// no limit, `Valid` its value.
    #[must_use]
    pub fn limits_from_fields(&self) -> Option<Limits> {
        Some(Limits {
            max_volts: limit_of(&self.max_voltage)?,
            max_amps: limit_of(&self.max_current)?,
        })
    }

    /// Re-parses the setpoint fields under the limits in force.
    pub fn reparse_setpoints(&mut self) {
        self.voltage.reparse(FieldKind::Voltage, &self.limits);
        self.current.reparse(FieldKind::Current, &self.limits);
    }

    // ----- Enabled states (DD-APP-010) -----

    /// Whether the stored reading is in DC mode.
    fn dc(&self) -> bool {
        self.reading
            .is_some_and(|r| r.reading.live_mode == LiveMode::Dc)
    }

    /// Whether no limit field is invalid.
    fn limit_fields_valid(&self) -> bool {
        self.limits_from_fields().is_some()
    }

    /// Phase `Connected`, a reading and the info, DC mode, and the
    /// unclean-exit warning absent or acknowledged.
    #[must_use]
    pub fn base_ready(&self) -> bool {
        self.phase == Phase::Connected
            && self.reading.is_some()
            && self.info.is_some()
            && self.dc()
            && (self.banner(BannerKind::UncleanExit).is_none() || self.unclean_exit_acknowledged)
    }

    /// Whether the setpoints can be applied: `base_ready()` and remote
    /// control not denied or lost.
    #[must_use]
    pub fn setpoint_enabled(&self) -> bool {
        self.base_ready()
            && matches!(
                self.remote,
                RemoteState::None | RemoteState::Requested | RemoteState::Granted
            )
    }

    /// Whether Output ON is enabled: the setpoints can be applied, no
    /// fault, and no setpoint above a user limit.
    #[must_use]
    pub fn output_on_enabled(&self) -> bool {
        self.setpoint_enabled()
            && self.reading.is_some_and(|r| r.reading.faults.is_empty())
            && self.limit_notice().is_none()
    }

    /// Whether Output OFF is enabled: whenever a supply is connected, in
    /// every remote state and mode.
    #[must_use]
    pub fn output_off_enabled(&self) -> bool {
        self.phase == Phase::Connected
    }

    /// Whether remote control can be requested.
    #[must_use]
    pub fn request_remote_enabled(&self) -> bool {
        self.base_ready()
            && matches!(
                self.remote,
                RemoteState::None | RemoteState::Denied | RemoteState::Lost
            )
    }

    /// Whether remote control can be released.
    #[must_use]
    pub fn release_remote_enabled(&self) -> bool {
        self.phase == Phase::Connected && self.dc() && self.remote == RemoteState::Granted
    }

    /// Whether the field of `kind` can be applied.
    #[must_use]
    pub fn apply_enabled(&self, kind: FieldKind) -> bool {
        self.setpoint_enabled() && matches!(self.field(kind).state, FieldState::Valid { .. })
    }

    /// Whether the limit fields can be applied.
    #[must_use]
    pub fn apply_limits_enabled(&self) -> bool {
        self.limit_fields_valid() && self.phase != Phase::Closing
    }

    /// Whether a scan can start.
    #[must_use]
    pub fn scan_enabled(&self) -> bool {
        self.phase == Phase::Idle && self.fatal.is_none()
    }

    /// Whether Connect is enabled.
    #[must_use]
    pub fn connect_enabled(&self) -> bool {
        self.scan_enabled() && self.selected_found().is_some() && self.limit_fields_valid()
    }

    /// The found entry the selection names.
    #[must_use]
    pub fn selected_found(&self) -> Option<&Found> {
        let selected = self.selected.as_ref()?;
        self.found.iter().find(|f| &f.identifier == selected)
    }

    /// Whether Disconnect is enabled.
    #[must_use]
    pub fn disconnect_enabled(&self) -> bool {
        matches!(
            self.phase,
            Phase::Connecting | Phase::Connected | Phase::Lost { .. }
        )
    }

    /// Whether Reconnect is enabled.
    #[must_use]
    pub fn reconnect_enabled(&self) -> bool {
        matches!(self.phase, Phase::Lost { .. })
    }

    /// Whether a recording can start.
    #[must_use]
    pub fn recording_start_enabled(&self) -> bool {
        self.phase == Phase::Connected
            && self.reading.is_some()
            && self.recording == RecordingState::Off
    }

    /// Whether the recording can stop.
    #[must_use]
    pub fn recording_stop_enabled(&self) -> bool {
        matches!(
            self.recording,
            RecordingState::Starting { .. } | RecordingState::On { .. }
        )
    }

    /// The screen of the phase.
    #[must_use]
    pub fn screen(&self) -> Screen {
        match self.phase {
            Phase::Idle | Phase::Scanning | Phase::Connecting => Screen::Connection,
            Phase::Connected | Phase::Lost { .. } | Phase::Closing => Screen::Main,
        }
    }

    // ----- Display methods (DD-APP-014) -----

    /// The `Display` of the connected row, else `the supply`.
    #[must_use]
    pub fn supply_line(&self) -> String {
        self.connected
            .as_ref()
            .map_or_else(|| texts::THE_SUPPLY.to_string(), ToString::to_string)
    }

    /// The notice outside DC mode, in `Connected`.
    #[must_use]
    pub fn mode_notice(&self) -> Option<String> {
        let reading = self.reading?;
        (self.phase == Phase::Connected && reading.reading.live_mode != LiveMode::Dc)
            .then(|| texts::mode_notice(reading.reading.live_mode))
    }

    /// The notice of setpoints above the user's limits: `Some` when the
    /// core refuses the reading's setpoints under the limits in force.
    #[must_use]
    pub fn limit_notice(&self) -> Option<String> {
        let reading = self.reading?.reading;
        let over = RawVoltage::from_volts(reading.set_volts, &self.limits).is_err()
            || RawCurrent::from_amps(reading.set_amps, &self.limits).is_err();
        over.then(|| texts::limit_notice(reading.set_volts, reading.set_amps))
    }

    /// The notice of a denied or lost grant, in `Connected`.
    #[must_use]
    pub fn remote_notice(&self) -> Option<String> {
        if self.phase != Phase::Connected {
            return None;
        }
        texts::remote_notice(self.remote).map(str::to_string)
    }

    /// The banners to show, in order: the fatal text, the loss text and
    /// the reconnection line in `Lost`, the stored banners (`OffFailed`,
    /// `UncleanExit`, `Error`, `SetpointsChanged`, dismissible), then the
    /// mode, limit and remote notices.
    #[must_use]
    pub fn banners_to_show(&self, _now: Instant) -> Vec<Shown> {
        let fixed = |kind, text| Shown {
            kind,
            text,
            dismissible: false,
        };
        let mut shown = Vec::new();
        if let Some(text) = &self.fatal {
            // `WORKER_STOPPED` is shown as it is (DD-APP-014, rev 3).
            let text = if text == texts::WORKER_STOPPED {
                text.clone()
            } else {
                texts::fatal(text)
            };
            shown.push(fixed(ShownKind::Fatal, text));
        }
        if let Phase::Lost {
            text,
            reconnecting,
            gave_up,
        } = &self.phase
        {
            shown.push(fixed(ShownKind::Loss, text.clone()));
            shown.push(fixed(
                ShownKind::Reconnect,
                texts::reconnect_line(*reconnecting, gave_up.as_deref()),
            ));
        }
        for kind in [
            BannerKind::OffFailed,
            BannerKind::UncleanExit,
            BannerKind::Error,
            BannerKind::SetpointsChanged,
        ] {
            if let Some(banner) = self.banner(kind) {
                shown.push(Shown {
                    kind: ShownKind::Banner(kind),
                    text: banner.text.clone(),
                    dismissible: true,
                });
            }
        }
        for (kind, notice) in [
            (ShownKind::ModeNotice, self.mode_notice()),
            (ShownKind::LimitNotice, self.limit_notice()),
            (ShownKind::RemoteNotice, self.remote_notice()),
        ] {
            if let Some(text) = notice {
                shown.push(fixed(kind, text));
            }
        }
        shown
    }

    /// The seconds left of the prompt: `bound_s` minus the whole seconds
    /// since it appeared, saturating at 0.
    #[must_use]
    pub fn prompt_seconds_left(&self, now: Instant) -> Option<u32> {
        let prompt = self.prompt.as_ref()?;
        let elapsed = now.saturating_duration_since(prompt.since).as_secs();
        Some(
            prompt
                .bound_s
                .saturating_sub(u32::try_from(elapsed).unwrap_or(u32::MAX)),
        )
    }

    /// The age of the stored reading.
    fn reading_age(&self, now: Instant) -> Option<Duration> {
        self.reading.map(|r| now.saturating_duration_since(r.at))
    }

    /// Whether an `OutputOn` waits for its `Done`.
    fn output_on_pending(&self) -> bool {
        self.pending.values().any(|p| p.what == What::OutputOn)
    }

    /// Whether the output may be on: no reading, the reading showing the
    /// output on, an `OutputOn` pending, an answered `OutputOn` that no
    /// reading shows yet (`output_on_done`), or a reading older than 1 s.
    #[must_use]
    pub fn output_maybe_on(&self, now: Instant) -> bool {
        let Some(reading) = self.reading else {
            return true;
        };
        reading.reading.output_on
            || self.output_on_pending()
            || self.output_on_done.is_some()
            || self.reading_age(now).is_some_and(|age| age > FRESH)
    }

    /// The close question while the dialog is open: the first case that
    /// applies of no reading, the output on outside DC mode, the output
    /// on, an `OutputOn` pending, an answered `OutputOn` not yet shown, a
    /// stale reading, and the output off.
    #[must_use]
    pub fn close_question(&self, now: Instant) -> Option<CloseQuestion> {
        self.close_dialog?;
        let ask = |text: String, switch_off: bool| Some(CloseQuestion { text, switch_off });
        let Some(reading) = self.reading else {
            return ask(texts::CLOSE_NO_READING.to_string(), true);
        };
        let view = reading.reading;
        if view.output_on && view.live_mode != LiveMode::Dc {
            return ask(texts::close_not_dc(view.live_mode), false);
        }
        if view.output_on {
            return ask(texts::CLOSE_OUTPUT_ON.to_string(), true);
        }
        if self.output_on_pending() {
            return ask(texts::CLOSE_ON_PENDING.to_string(), true);
        }
        if self.output_on_done.is_some() {
            return ask(texts::CLOSE_ON_DONE.to_string(), true);
        }
        match self.reading_age(now) {
            Some(age) if age > FRESH => ask(texts::close_stale(age.as_secs()), true),
            _ => ask(texts::CLOSE_NOW_OFF.to_string(), false),
        }
    }

    /// The limits in force as text.
    #[must_use]
    pub fn limits_text(&self) -> String {
        texts::limits_text(&self.limits)
    }

    /// When the next frame is due without an event: with a prompt, at the
    /// next whole second of its countdown; in `Closing` while the window
    /// waits, at the close bound; with the close question open, in 1 s.
    #[must_use]
    pub fn repaint_after(&self, now: Instant) -> Option<Duration> {
        if let Some(prompt) = &self.prompt {
            let into = now.saturating_duration_since(prompt.since).subsec_nanos();
            return Some(SECOND.saturating_sub(Duration::from_nanos(u64::from(into))));
        }
        if self.phase == Phase::Closing && self.close_pending && !self.close_overdue {
            if let Some(since) = self.closing_since {
                return Some(CLOSE_BOUND.saturating_sub(now.saturating_duration_since(since)));
            }
        }
        self.close_dialog.map(|_| SECOND)
    }

    /// Writes `text` to the event log, prefixed with the seconds since
    /// `started`; the log keeps the last 200 lines.
    pub fn log_line(&mut self, now: Instant, text: &str) {
        let seconds = now.saturating_duration_since(self.started).as_secs_f64();
        while self.log.len() >= LOG_LINES {
            self.log.pop_front();
        }
        self.log.push_back(format!("{seconds:.1} s  {text}"));
    }

    // ----- Rows and lines for the screens -----

    /// The range hint of the field of `kind` under the limits in force.
    #[must_use]
    pub fn hint(&self, kind: FieldKind) -> String {
        Field::hint(kind, &self.limits)
    }

    /// Why the field of `kind` is invalid, if it is.
    #[must_use]
    pub fn field_error(&self, kind: FieldKind) -> Option<String> {
        match &self.field(kind).state {
            FieldState::Invalid(text) => Some(text.clone()),
            FieldState::Empty | FieldState::Valid { .. } => None,
        }
    }

    /// Whether a scan runs.
    #[must_use]
    pub fn is_scanning(&self) -> bool {
        self.phase == Phase::Scanning
    }

    /// `Connecting to <supply>` while connecting.
    #[must_use]
    pub fn connecting_line(&self) -> Option<String> {
        (self.phase == Phase::Connecting).then(|| texts::connecting(&self.supply_line()))
    }

    /// The prompt's text with the seconds left.
    #[must_use]
    pub fn prompt_line(&self, now: Instant) -> Option<String> {
        let prompt = self.prompt.as_ref()?;
        let left = self.prompt_seconds_left(now)?;
        Some(texts::prompt_line(prompt.text, left))
    }

    /// The found supplies as rows.
    #[must_use]
    pub fn found_rows(&self) -> Vec<FoundRow> {
        self.found
            .iter()
            .map(|f| FoundRow {
                identifier: f.identifier.clone(),
                name: if f.name.is_empty() {
                    texts::NO_NAME.to_string()
                } else {
                    f.name.clone()
                },
                unit: if f.unit_id.is_empty() {
                    texts::UNKNOWN.to_string()
                } else {
                    f.unit_id.clone()
                },
                transport: f.transport.to_string(),
                signal: f
                    .rssi
                    .map_or_else(|| texts::UNKNOWN.to_string(), |r| format!("{r} dBm")),
                remote: texts::flag(f.remote_flag).to_string(),
                selected: self.selected.as_ref() == Some(&f.identifier),
            })
            .collect()
    }

    /// The supply's info as rows: transport, model, version and hardware.
    #[must_use]
    pub fn info_rows(&self) -> Vec<(&'static str, String)> {
        let Some(info) = &self.info else {
            return Vec::new();
        };
        vec![
            (
                label::TRANSPORT,
                self.transport
                    .map_or_else(|| texts::UNKNOWN.to_string(), |k| k.to_string()),
            ),
            (label::MODEL, info.model.clone()),
            (label::VERSION, info.version.to_string()),
            (
                label::HARDWARE,
                info.hardware
                    .map_or_else(|| texts::NOT_REPORTED.to_string(), |v| v.to_string()),
            ),
        ]
    }

    /// The reading as rows: measured voltage, current and power, the
    /// setpoints, the output state, the regulation and live modes, and the
    /// active faults by name.
    #[must_use]
    pub fn reading_rows(&self) -> Vec<(&'static str, String)> {
        let Some(reading) = self.reading else {
            return Vec::new();
        };
        let view = reading.reading;
        let raw = view.raw;
        vec![
            (label::MEASURED_VOLTAGE, volts_text(raw.voltage)),
            (label::MEASURED_CURRENT, amps_text(raw.current)),
            (label::POWER, texts::watts(raw.power)),
            (label::SET_VOLTAGE, volts_text(raw.set_voltage)),
            (label::SET_CURRENT, amps_text(raw.set_current)),
            (label::OUTPUT, texts::on_off(view.output_on).to_string()),
            (label::REGULATION, view.regulation.to_string()),
            (label::MODE, texts::mode_name(view.live_mode)),
            (label::FAULTS, texts::fault_names(view.faults)),
        ]
    }

    /// The supply settings last reported, each field with its name.
    #[must_use]
    pub fn settings_rows(&self) -> Vec<(&'static str, String)> {
        let Some(s) = self.settings else {
            return Vec::new();
        };
        vec![
            (label::CHARGE_LIMIT, format!("{} %", s.charge_limit)),
            (label::VOLUME, s.volume.to_string()),
            (label::SCREEN_OFF, s.screen_off.to_string()),
            (label::AUTO_SHUTDOWN, format!("{} min", s.shutdown)),
            (label::SCREEN_DIRECTION, s.screen_direction.to_string()),
            (label::RAMP_STEP, format!("{} mV per 100 ms", s.ramp_step)),
            (label::OCP_DELAY, format!("{} ms", s.ocp_delay)),
            (label::USB_LINE_DROP, s.usb_line_drop.to_string()),
        ]
    }

    /// The remote-control state as a line.
    #[must_use]
    pub fn remote_line(&self) -> String {
        texts::remote_state_line(self.remote)
    }

    /// The closing line, in `Closing`.
    #[must_use]
    pub fn closing_line(&self) -> Option<&'static str> {
        (self.phase == Phase::Closing)
            .then(|| texts::closing_line(self.off_requested, self.close_overdue))
    }

    /// Whether `Close anyway` is offered: in `Closing` while the window
    /// waits and the switch-off is overdue.
    #[must_use]
    pub fn close_anyway_enabled(&self) -> bool {
        self.phase == Phase::Closing && self.close_pending && self.close_overdue
    }

    /// The recording's state as a line.
    #[must_use]
    pub fn recording_line(&self) -> String {
        match &self.recording {
            RecordingState::Off => texts::recording_state(texts::RECORDING_OFF, None, None),
            RecordingState::Starting { path } => {
                texts::recording_state(texts::RECORDING_STARTING, None, Some(path))
            }
            RecordingState::On { path, rows } => {
                texts::recording_state(texts::RECORDING_ON, Some(*rows), Some(path))
            }
        }
    }

    /// The placeholder of the recording path field: the automatic name.
    #[must_use]
    pub fn recording_placeholder(&self) -> String {
        self.recording_dir
            .join(texts::AUTOMATIC_NAME)
            .display()
            .to_string()
    }

    /// The close question's title, while it is open.
    #[must_use]
    pub fn close_dialog_title(&self) -> Option<&'static str> {
        self.close_dialog.map(|origin| match origin {
            CloseOrigin::Window => label::CLOSE_TITLE_WINDOW,
            CloseOrigin::Disconnect => label::CLOSE_TITLE_DISCONNECT,
        })
    }
}

/// The limit a limit field holds: `None` when empty, `Some(Some(v))` when
/// valid, `None` (invalid) as the outer `None`.
fn limit_of(field: &Field) -> Option<Option<f64>> {
    match field.state {
        FieldState::Empty => Some(None),
        FieldState::Valid { value, .. } => Some(Some(value)),
        FieldState::Invalid(_) => None,
    }
}

/// A raw voltage with its unit: `13.00 V`.
fn volts_text(raw: u16) -> String {
    format!("{} V", fields::display(FieldKind::Voltage, raw))
}

/// A raw current with its unit: `1.000 A`.
fn amps_text(raw: u16) -> String {
    format!("{} A", fields::display(FieldKind::Current, raw))
}

/// A found supply as the connection screen lists it.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct FoundRow {
    /// The identifier, which `Select` takes.
    pub identifier: String,
    /// The name.
    pub name: String,
    /// The unit characters.
    pub unit: String,
    /// The transport.
    pub transport: String,
    /// The signal strength.
    pub signal: String,
    /// The remote-control flag.
    pub remote: String,
    /// Whether this row is selected.
    pub selected: bool,
}

impl Shown {
    /// The banner kind its dismiss button dismisses, when it has one.
    #[must_use]
    pub fn dismiss(&self) -> Option<BannerKind> {
        match self.kind {
            ShownKind::Banner(kind) if self.dismissible => Some(kind),
            _ => None,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::actions::{handle, IdSource, UiAction};
    use crate::testkit::{
        at_ms, at_s, clock_s, connected_model, found_a, found_b, info, r, settings, t0,
    };
    use crate::worker::{Command, ErrorText};
    use mp305_core::session::texts::{ALLOW_REMOTE_CONTROL, CONFIRM_CONNECTION};

    /// Whether the log holds a line ending with `text`.
    fn logged(m: &Model, text: &str) -> bool {
        m.log.iter().any(|line| line.ends_with(text))
    }

    /// The texts of the stored banners of `kind`.
    fn banner(m: &Model, kind: BannerKind) -> Option<String> {
        m.banners
            .iter()
            .find(|b| b.kind == kind)
            .map(|b| b.text.clone())
    }

    /// A `Session` event of attempt 1.
    fn session(event: SessionEvent) -> AppEvent {
        AppEvent::Session { sid: 1, event }
    }

    /// A reading event of attempt `sid`.
    fn reading(sid: u64, reading: TimedReading) -> UiReading {
        UiReading { sid, reading }
    }

    /// The `Done` of `id`.
    fn done(id: u64, what: What, result: Result<(), ErrorText>) -> AppEvent {
        AppEvent::Done { id, what, result }
    }

    /// An error text of `kind`.
    fn err(kind: ErrorKind, text: &str) -> Result<(), ErrorText> {
        Err(ErrorText {
            text: text.to_string(),
            kind,
        })
    }

    /// Test: UT-APP-003
    #[test]
    fn a_session_from_scan_to_disconnect() {
        let mut m = Model::new(PathBuf::from("/rec"), t0());
        let mut ids = IdSource::new();
        let scan = handle(&mut m, UiAction::Scan, clock_s(0.0), &mut ids);
        assert_eq!(m.phase, Phase::Scanning);
        assert!(matches!(scan.as_slice(), [Command::Scan { id: 1, .. }]));
        m.apply(
            AppEvent::ScanResult {
                id: 1,
                found: vec![found_a(), found_b()],
                message: None,
            },
            at_s(0.0),
        );
        assert_eq!(m.phase, Phase::Idle);
        assert_eq!(m.found.len(), 2);
        assert_eq!(m.scan_message, None);
        handle(&mut m, UiAction::Select("A".into()), clock_s(0.0), &mut ids);
        assert_eq!(m.selected.as_deref(), Some("A"));
        let connect = handle(&mut m, UiAction::Connect, clock_s(0.0), &mut ids);
        assert_eq!(m.phase, Phase::Connecting);
        assert_eq!(m.connected, Some(found_a()));
        assert_eq!(m.limits, Limits::none());
        assert_eq!(
            connect,
            vec![Command::Connect {
                id: 2,
                identifier: "A".into(),
                reconnect: false,
                limits: Limits::none()
            }]
        );
        assert!(m.pending.contains_key(&2));

        m.apply(
            AppEvent::Connecting {
                sid: 1,
                identifier: "A".into(),
            },
            at_s(0.0),
        );
        m.apply(done(2, What::Connect, Ok(())), at_s(0.0));
        assert_eq!(m.sid, Some(1));
        assert!(m.pending.is_empty());

        m.apply(
            session(SessionEvent::Prompt {
                kind: PromptKind::ConfirmConnection,
                bound_s: 30,
                text: CONFIRM_CONNECTION,
            }),
            at_s(0.1),
        );
        assert!(m.prompt.is_some());
        assert_eq!(m.prompt_seconds_left(at_s(12.4)), Some(18));
        m.apply(
            session(SessionEvent::BindResult { recognised: false }),
            at_s(12.5),
        );
        assert_eq!(m.prompt, None);
        assert!(logged(&m, "confirmed on the supply"));

        let first = r(0, 0, 0, 1300, 1000, at_s(12.6));
        m.apply(reading(1, first), at_s(12.6));
        assert_eq!(m.reading, Some(first));
        assert_eq!(m.chart.len(), 1);
        assert_eq!(m.voltage.text, "13.00");
        assert_eq!(m.current.text, "1.000");

        m.apply(
            session(SessionEvent::UncleanExitWarning {
                since: crate::testkit::wall0(),
                text: "T".into(),
            }),
            at_s(12.7),
        );
        assert_eq!(
            banner(&m, BannerKind::UncleanExit).as_deref(),
            Some("ble A MP305B (unit ABC): T")
        );
        m.apply(
            AppEvent::Ready {
                sid: 1,
                info: info(),
                reading: Some(first),
                transport: Some(Kind::Ble),
            },
            at_s(12.8),
        );
        assert_eq!(m.phase, Phase::Connected);
        assert_eq!(m.info, Some(info()));
        assert_eq!(m.chart.len(), 1);
        assert!(!m.setpoint_enabled());
        assert!(m.output_off_enabled());
        m.dismiss(BannerKind::UncleanExit);
        assert!(m.setpoint_enabled());

        m.apply(
            session(SessionEvent::SettingsChanged(settings())),
            at_s(13.0),
        );
        assert_eq!(m.settings, Some(settings()));
        m.apply(
            session(SessionEvent::RemoteControl(RemoteState::Requested)),
            at_s(13.1),
        );
        m.apply(
            session(SessionEvent::Prompt {
                kind: PromptKind::AllowRemoteControl,
                bound_s: 70,
                text: ALLOW_REMOTE_CONTROL,
            }),
            at_s(13.1),
        );
        assert_eq!(m.remote, RemoteState::Requested);
        assert!(m.prompt.is_some());
        m.apply(
            session(SessionEvent::RemoteControl(RemoteState::Granted)),
            at_s(20.0),
        );
        assert_eq!(m.prompt, None);
        assert_eq!(m.remote, RemoteState::Granted);

        m.apply(reading(1, r(0, 0, 0, 500, 100, at_s(20.2))), at_s(20.2));
        assert_eq!(m.voltage.text, "5.00");
        assert_eq!(m.current.text, "0.100");
        assert_eq!(m.chart.len(), 2);

        m.reconnect = true;
        m.apply(
            session(SessionEvent::LinkLost { text: "L".into() }),
            at_s(30.0),
        );
        assert_eq!(
            m.phase,
            Phase::Lost {
                text: "L".into(),
                reconnecting: true,
                gave_up: None
            }
        );
        assert_eq!(m.remote, RemoteState::Lost);
        assert!(!m.output_off_enabled());
        assert!(m.reconnect_enabled());
        assert_eq!(m.banners_to_show(at_s(30.0))[0].text, "L");

        m.apply(session(SessionEvent::Reconnected), at_s(35.0));
        assert_eq!(m.phase, Phase::Connected);
        assert_eq!(m.remote, RemoteState::None);
        m.apply(reading(1, r(0, 0, 0, 500, 100, at_s(35.3))), at_s(35.3));
        assert_eq!(m.chart.len(), 3);

        let disconnect = handle(&mut m, UiAction::Disconnect, clock_s(36.0), &mut ids);
        assert_eq!(
            disconnect,
            vec![Command::Disconnect {
                id: 3,
                output_off: false
            }]
        );
        assert!(m.pending.is_empty());
        assert_eq!(m.phase, Phase::Closing);

        m.apply(
            AppEvent::Disconnected {
                sid: Some(1),
                text: None,
                off_requested: false,
                output_on: Some(false),
            },
            at_s(36.2),
        );
        assert_eq!(m.phase, Phase::Idle);
        assert_eq!(m.sid, None);
        assert_eq!(m.connected, None);
        assert_eq!(m.reading, None);
        assert_eq!(m.info, None);
        assert_eq!(banner(&m, BannerKind::UncleanExit), None);
        assert_eq!(m.chart.len(), 3);
    }

    /// The enabled states of `m`, by name.
    fn enabled(m: &Model) -> Vec<&'static str> {
        let all = [
            ("setpoint", m.setpoint_enabled()),
            ("output_on", m.output_on_enabled()),
            ("output_off", m.output_off_enabled()),
            ("request_remote", m.request_remote_enabled()),
            ("release_remote", m.release_remote_enabled()),
            ("scan", m.scan_enabled()),
            ("connect", m.connect_enabled()),
            ("disconnect", m.disconnect_enabled()),
            ("reconnect", m.reconnect_enabled()),
            ("recording_start", m.recording_start_enabled()),
            ("recording_stop", m.recording_stop_enabled()),
        ];
        all.iter().filter(|(_, on)| *on).map(|(n, _)| *n).collect()
    }

    /// A model in `Idle` with `A` found and selected.
    fn idle_with_a() -> Model {
        let mut m = Model::new(PathBuf::from("/rec"), t0());
        m.found = vec![found_a()];
        m.selected = Some("A".into());
        m
    }

    /// Test: UT-APP-004
    #[test]
    fn the_enabled_states_in_every_case() {
        let new = Model::new(PathBuf::from("/rec"), t0());
        assert_eq!(enabled(&new), ["scan"], "(1)");
        assert_eq!(enabled(&idle_with_a()), ["scan", "connect"], "(2)");
        let mut m = idle_with_a();
        m.max_voltage
            .edit("31".into(), FieldKind::MaxVoltage, &Limits::none());
        assert_eq!(enabled(&m), ["scan"], "(3)");
        let mut m = idle_with_a();
        m.fatal = Some("x".into());
        assert!(enabled(&m).is_empty(), "(4)");
        let mut m = idle_with_a();
        m.phase = Phase::Connecting;
        assert_eq!(enabled(&m), ["disconnect"], "(5)");
        let connected = [
            "setpoint",
            "output_on",
            "output_off",
            "request_remote",
            "disconnect",
            "recording_start",
        ];
        assert_eq!(enabled(&connected_model()), connected, "(6)");
        let mut m = connected_model();
        m.apply(
            session(SessionEvent::UncleanExitWarning {
                since: crate::testkit::wall0(),
                text: "T".into(),
            }),
            at_s(1.0),
        );
        assert_eq!(
            enabled(&m),
            ["output_off", "disconnect", "recording_start"],
            "(7)"
        );
        let mut m = connected_model();
        m.remote = RemoteState::Granted;
        assert_eq!(
            enabled(&m),
            [
                "setpoint",
                "output_on",
                "output_off",
                "release_remote",
                "disconnect",
                "recording_start"
            ],
            "(8)"
        );
        let mut m = connected_model();
        m.remote = RemoteState::Requested;
        for id in 10..13 {
            m.pending.insert(
                id,
                Pending {
                    what: What::SetVoltage,
                    sent: at_s(1.0),
                    limits: None,
                },
            );
        }
        m.prompt = Some(Prompt {
            kind: PromptKind::AllowRemoteControl,
            text: ALLOW_REMOTE_CONTROL,
            bound_s: 70,
            since: at_s(1.0),
        });
        assert_eq!(
            enabled(&m),
            [
                "setpoint",
                "output_on",
                "output_off",
                "disconnect",
                "recording_start"
            ],
            "(9)"
        );
        for (case, state) in [("(10)", RemoteState::Denied), ("(11)", RemoteState::Lost)] {
            let mut m = connected_model();
            m.remote = state;
            assert_eq!(
                enabled(&m),
                [
                    "output_off",
                    "request_remote",
                    "disconnect",
                    "recording_start"
                ],
                "{case}"
            );
        }
        let mut m = connected_model();
        m.apply(reading(1, r(0, 0, 32, 1300, 1000, at_s(1.0))), at_s(1.0));
        assert_eq!(
            enabled(&m),
            [
                "setpoint",
                "output_off",
                "request_remote",
                "disconnect",
                "recording_start"
            ],
            "(12)"
        );
        let mut m = connected_model();
        m.apply(reading(1, r(0, 2, 0, 1300, 1000, at_s(1.0))), at_s(1.0));
        assert_eq!(
            enabled(&m),
            ["output_off", "disconnect", "recording_start"],
            "(13)"
        );
        let mut m = connected_model();
        m.limits.max_volts = Some(5.0);
        assert_eq!(
            enabled(&m),
            [
                "setpoint",
                "output_off",
                "request_remote",
                "disconnect",
                "recording_start"
            ],
            "(14)"
        );
        let mut m = connected_model();
        m.reading = None;
        assert_eq!(enabled(&m), ["output_off", "disconnect"], "(15)");
        let mut m = connected_model();
        m.phase = Phase::Lost {
            text: "L".into(),
            reconnecting: false,
            gave_up: None,
        };
        assert_eq!(enabled(&m), ["disconnect", "reconnect"], "(16)");
        let mut m = connected_model();
        m.phase = Phase::Closing;
        assert!(enabled(&m).is_empty(), "(17)");
        let mut m = connected_model();
        m.recording = RecordingState::On {
            path: PathBuf::from("p"),
            rows: 0,
        };
        assert_eq!(
            enabled(&m),
            [
                "setpoint",
                "output_on",
                "output_off",
                "request_remote",
                "disconnect",
                "recording_stop"
            ],
            "(18)"
        );
        assert_eq!(new.screen(), Screen::Connection);
        assert_eq!(connected_model().screen(), Screen::Main);
    }

    /// Test: UT-APP-009
    #[test]
    fn scan_results_of_another_scan_are_ignored() {
        let mut m = idle_with_a();
        m.scan_id = Some(2);
        let before = m.clone();
        m.apply(
            AppEvent::ScanResult {
                id: 1,
                found: vec![found_b()],
                message: None,
            },
            at_s(1.0),
        );
        assert_eq!(m, before);
        m.apply(
            AppEvent::ScanResult {
                id: 2,
                found: vec![],
                message: Some("M".into()),
            },
            at_s(1.0),
        );
        assert!(m.found.is_empty());
        assert_eq!(m.scan_message.as_deref(), Some("M"));
        assert_eq!(m.selected, None);
        assert_eq!(m.scan_id, None);
    }

    /// Test: UT-APP-009
    #[test]
    fn events_of_another_attempt_or_phase_are_ignored() {
        let mut m = connected_model();
        let before = m.clone();
        m.apply(reading(7, r(0, 0, 0, 1, 1, at_s(5.0))), at_s(5.0));
        m.apply(
            AppEvent::Session {
                sid: 7,
                event: SessionEvent::SettingsChanged(settings()),
            },
            at_s(5.0),
        );
        m.apply(session(SessionEvent::Reconnected), at_s(5.0));
        assert_eq!(m, before);

        let mut lost = connected_model();
        lost.phase = Phase::Lost {
            text: "L".into(),
            reconnecting: false,
            gave_up: None,
        };
        let before = lost.clone();
        lost.apply(
            AppEvent::Ready {
                sid: 1,
                info: info(),
                reading: None,
                transport: Some(Kind::Ble),
            },
            at_s(5.0),
        );
        assert_eq!(lost, before);

        let mut closing = connected_model();
        closing.phase = Phase::Closing;
        let before = closing.clone();
        closing.apply(session(SessionEvent::Reconnected), at_s(5.0));
        assert_eq!(closing, before);

        let mut idle = Model::new(PathBuf::from("/rec"), t0());
        idle.sid = Some(1);
        let before = idle.clone();
        idle.apply(reading(1, r(0, 0, 0, 1, 1, at_s(5.0))), at_s(5.0));
        assert_eq!(idle, before);
    }

    /// A model in `Connecting` with `sid` 1, `A` connected and the bind
    /// prompt open.
    fn connecting_with_prompt() -> Model {
        let mut m = idle_with_a();
        m.phase = Phase::Connecting;
        m.connected = Some(found_a());
        m.sid = Some(1);
        m.prompt = Some(Prompt {
            kind: PromptKind::ConfirmConnection,
            text: CONFIRM_CONNECTION,
            bound_s: 30,
            since: at_s(0.0),
        });
        m
    }

    /// Test: UT-APP-009
    #[test]
    fn a_failed_connect_names_the_supply() {
        let mut m = connecting_with_prompt();
        m.apply(
            AppEvent::ConnectFailed {
                sid: 1,
                text: "the supply denied the connection".into(),
            },
            at_s(1.0),
        );
        assert_eq!(m.phase, Phase::Idle);
        assert_eq!(m.prompt, None);
        assert_eq!(m.sid, None);
        assert_eq!(m.connected, None);
        assert_eq!(
            banner(&m, BannerKind::Error).as_deref(),
            Some("Could not connect to ble A MP305B (unit ABC): the supply denied the connection")
        );
    }

    /// Test: UT-APP-009
    #[test]
    fn done_events_log_or_raise_banners() {
        let mut m = connected_model();
        let lines = m.log.len();
        m.apply(done(9, What::SetVoltage, Ok(())), at_s(1.0));
        assert_eq!(m.log.len(), lines + 1);
        assert!(m.banners.is_empty());

        let pend = |m: &mut Model, id: u64, what: What, sent: Instant| {
            m.pending.insert(
                id,
                Pending {
                    what,
                    sent,
                    limits: None,
                },
            );
        };
        pend(&mut m, 4, What::OutputOff, at_ms(1000));
        m.apply(done(4, What::OutputOff, Ok(())), at_ms(1143));
        assert!(logged(&m, "output off acknowledged after 143 ms"));

        pend(&mut m, 5, What::OutputOff, at_s(1.0));
        m.apply(
            done(
                5,
                What::OutputOff,
                err(ErrorKind::Mode, "the supply is not in DC mode (mode 2)"),
            ),
            at_s(1.1),
        );
        assert_eq!(
            banner(&m, BannerKind::Error).as_deref(),
            Some(
                "output off failed: the supply is not in DC mode (mode 2). Switch the output \
                 off on the supply."
            )
        );
        pend(&mut m, 6, What::SetVoltage, at_s(1.0));
        m.apply(
            done(
                6,
                What::SetVoltage,
                err(
                    ErrorKind::RemoteControlDenied,
                    "the supply denied remote control",
                ),
            ),
            at_s(1.1),
        );
        assert_eq!(
            banner(&m, BannerKind::Error).as_deref(),
            Some("set voltage failed: the supply denied remote control")
        );
        m.dismiss(BannerKind::Error);
        pend(&mut m, 8, What::SetVoltage, at_s(1.0));
        let lines = m.log.len();
        m.apply(
            done(
                8,
                What::SetVoltage,
                err(
                    ErrorKind::Cancelled,
                    "the command was cancelled: superseded by an output-off",
                ),
            ),
            at_s(1.1),
        );
        assert_eq!(m.log.len(), lines + 1);
        assert!(m.banners.is_empty());
        assert!(m.pending.is_empty());
    }

    /// Test: UT-APP-009
    #[test]
    fn a_refused_connect_returns_to_idle() {
        let mut m = idle_with_a();
        m.phase = Phase::Connecting;
        m.connected = Some(found_a());
        m.pending.insert(
            1,
            Pending {
                what: What::Connect,
                sent: at_s(0.0),
                limits: None,
            },
        );
        m.apply(
            done(
                1,
                What::Connect,
                err(ErrorKind::App, "a supply is already connected"),
            ),
            at_s(0.1),
        );
        assert_eq!(m.phase, Phase::Idle);
        assert!(m.pending.is_empty());
        assert_eq!(m.connected, None);
        assert_eq!(
            banner(&m, BannerKind::Error).as_deref(),
            Some("connect failed: a supply is already connected")
        );
    }

    /// Test: UT-APP-009
    #[test]
    fn faults_come_from_the_reading() {
        let mut m = connected_model();
        m.apply(
            session(SessionEvent::FaultsChanged {
                faults: Faults(32),
                reading: r(0, 0, 32, 1300, 1000, at_s(1.0)),
            }),
            at_s(1.0),
        );
        assert!(logged(&m, "faults: over current"));
        assert!(!m.output_on_enabled());
        m.apply(
            session(SessionEvent::LinkLost { text: "L".into() }),
            at_s(2.0),
        );
        m.apply(session(SessionEvent::Reconnected), at_s(8.0));
        m.apply(reading(1, r(0, 0, 0, 1300, 1000, at_s(9.0))), at_s(9.0));
        assert!(m.output_on_enabled());
    }

    /// Test: UT-APP-009
    #[test]
    fn a_setpoints_changed_banner_leaves_an_edited_field() {
        let mut m = connected_model();
        m.voltage
            .edit("5".into(), FieldKind::Voltage, &Limits::none());
        m.apply(
            session(SessionEvent::SetpointsChanged {
                set_volts: 12.0,
                set_amps: 1.0,
                expected_volts: 5.0,
                expected_amps: 1.0,
            }),
            at_s(1.0),
        );
        assert_eq!(
            banner(&m, BannerKind::SetpointsChanged).as_deref(),
            Some("The supply's setpoints are 12.00 V and 1.000 A, not the expected 5.00 V and 1.000 A.")
        );
        assert_eq!(m.voltage.text, "5");
    }

    /// Test: UT-APP-009
    #[test]
    fn a_loss_while_connecting_or_closing_is_only_logged() {
        for phase in [Phase::Connecting, Phase::Closing] {
            let mut m = connecting_with_prompt();
            m.phase = phase.clone();
            let lines = m.log.len();
            m.apply(
                session(SessionEvent::LinkLost { text: "L".into() }),
                at_s(1.0),
            );
            assert_eq!(m.phase, phase);
            assert_eq!(m.log.len(), lines + 1);
        }
    }

    /// Test: UT-APP-009
    #[test]
    fn a_reconnection_that_gave_up() {
        let mut m = connected_model();
        m.reconnect = true;
        m.apply(
            session(SessionEvent::LinkLost { text: "L".into() }),
            at_s(1.0),
        );
        m.apply(
            session(SessionEvent::ReconnectGaveUp {
                text: "No reconnection within 10 minutes.".into(),
            }),
            at_s(601.0),
        );
        assert_eq!(
            m.phase,
            Phase::Lost {
                text: "L".into(),
                reconnecting: false,
                gave_up: Some("No reconnection within 10 minutes.".into())
            }
        );
        let texts: Vec<String> = m
            .banners_to_show(at_s(601.0))
            .into_iter()
            .map(|s| s.text)
            .collect();
        assert!(texts.contains(&"L".to_string()));
        assert!(texts.contains(&"No reconnection within 10 minutes.".to_string()));
    }

    /// Test: UT-APP-009
    #[test]
    fn connecting_resets_the_connection_but_keeps_off_failed_and_pending() {
        let mut m = connected_model();
        m.phase = Phase::Connecting;
        for (kind, text) in [
            (BannerKind::SetpointsChanged, "s"),
            (BannerKind::Error, "e"),
            (BannerKind::OffFailed, "o"),
        ] {
            m.banners.push(Banner {
                kind,
                text: text.into(),
            });
        }
        for k in 1..5 {
            m.chart.push(&r(0, 0, 0, 1300, 1000, at_s(f64::from(k))));
        }
        assert_eq!(m.chart.len(), 5);
        m.settings = Some(settings());
        m.prompt = Some(Prompt {
            kind: PromptKind::ConfirmConnection,
            text: CONFIRM_CONNECTION,
            bound_s: 30,
            since: at_s(0.0),
        });
        m.remote = RemoteState::Granted;
        m.pending.insert(
            3,
            Pending {
                what: What::SetVoltage,
                sent: at_s(0.0),
                limits: None,
            },
        );
        m.apply(
            AppEvent::Connecting {
                sid: 2,
                identifier: "A".into(),
            },
            at_s(6.0),
        );
        assert_eq!(m.sid, Some(2));
        assert_eq!(
            m.banners,
            vec![Banner {
                kind: BannerKind::OffFailed,
                text: "o".into()
            }]
        );
        assert!(m.chart.is_empty());
        assert_eq!(m.reading, None);
        assert_eq!(m.info, None);
        assert_eq!(m.settings, None);
        assert_eq!(m.prompt, None);
        assert_eq!(m.remote, RemoteState::None);
        assert!(m.pending.contains_key(&3));
        assert_eq!(m.voltage, Field::default());
    }

    /// Test: UT-APP-009
    #[test]
    fn recording_events() {
        let mut m = connected_model();
        let p = PathBuf::from("p");
        m.apply(
            AppEvent::Recording(RecordingEvent::On { path: p.clone() }),
            at_s(1.0),
        );
        assert_eq!(
            m.recording,
            RecordingState::On {
                path: p.clone(),
                rows: 0
            }
        );
        m.apply(
            AppEvent::Recording(RecordingEvent::Progress { rows: 8 }),
            at_s(1.0),
        );
        assert_eq!(
            m.recording,
            RecordingState::On {
                path: p.clone(),
                rows: 8
            }
        );
        m.apply(
            AppEvent::Recording(RecordingEvent::Off {
                path: p.clone(),
                rows: 10,
                error: None,
            }),
            at_s(1.0),
        );
        assert_eq!(m.recording, RecordingState::Off);
        assert!(logged(&m, "recording saved: 10 rows in p"));
        m.apply(
            AppEvent::Recording(RecordingEvent::Off {
                path: p,
                rows: 2,
                error: Some("disk full".into()),
            }),
            at_s(1.0),
        );
        assert_eq!(
            banner(&m, BannerKind::Error).as_deref(),
            Some("Recording stopped: disk full. 2 rows are in p.")
        );
    }

    /// Test: UT-APP-009
    #[test]
    fn fatal_dropped_readings_and_the_log_bound() {
        let mut m = Model::new(PathBuf::from("/rec"), t0());
        m.apply(
            AppEvent::Fatal("the OS reports no home directory".into()),
            at_s(0.1),
        );
        assert_eq!(m.fatal.as_deref(), Some("the OS reports no home directory"));
        assert_eq!(m.phase, Phase::Idle);
        assert!(!m.scan_enabled());
        let first = &m.banners_to_show(at_s(0.1))[0];
        assert_eq!(
            first.text,
            "The app cannot work: the OS reports no home directory"
        );
        assert!(!first.dismissible);

        m.apply(AppEvent::ReadingsDropped { total: 12 }, at_s(0.2));
        assert!(logged(
            &m,
            "12 readings were not shown (the window fell behind)"
        ));

        let mut m = Model::new(PathBuf::from("/rec"), t0());
        for i in 0..250 {
            m.log_line(at_s(1.0), &format!("line {i}"));
        }
        assert_eq!(m.log.len(), 200);
        assert!(m.log.front().unwrap().ends_with("line 50"));
        assert!(m.log.back().unwrap().ends_with("line 249"));
    }

    /// Test: UT-APP-009
    #[test]
    fn disconnected_in_closing() {
        let mut m = connected_model();
        m.phase = Phase::Closing;
        m.sid = None;
        m.apply(
            AppEvent::Disconnected {
                sid: None,
                text: None,
                off_requested: false,
                output_on: None,
            },
            at_s(1.0),
        );
        assert_eq!(m.phase, Phase::Idle);

        let mut m = connected_model();
        m.phase = Phase::Closing;
        m.apply(
            AppEvent::Disconnected {
                sid: Some(1),
                text: Some("store: x".into()),
                off_requested: false,
                output_on: Some(true),
            },
            at_s(1.0),
        );
        assert_eq!(m.phase, Phase::Idle);
        assert_eq!(
            banner(&m, BannerKind::Error).as_deref(),
            Some("Disconnect: store: x")
        );
        assert_eq!(banner(&m, BannerKind::OffFailed), None);

        let mut m = connected_model();
        m.phase = Phase::Closing;
        let before = m.clone();
        m.apply(
            AppEvent::Disconnected {
                sid: Some(3),
                text: None,
                off_requested: false,
                output_on: None,
            },
            at_s(1.0),
        );
        assert_eq!(m, before);
    }

    /// Test: UT-APP-023
    #[test]
    fn the_supply_line_and_the_notices() {
        assert_eq!(connected_model().supply_line(), "ble A MP305B (unit ABC)");
        assert_eq!(
            Model::new(PathBuf::from("/rec"), t0()).supply_line(),
            "the supply"
        );
        let mut m = connected_model();
        m.apply(reading(1, r(0, 2, 0, 1300, 1000, at_s(1.0))), at_s(1.0));
        assert_eq!(
            m.mode_notice().as_deref(),
            Some(
                "The supply is in PD mode. The app controls it only in DC mode; switch the \
                 output off on the supply."
            )
        );
        let mut m = connected_model();
        assert_eq!(m.limit_notice(), None);
        m.limits.max_volts = Some(5.0);
        assert_eq!(
            m.limit_notice().as_deref(),
            Some(
                "The supply's setpoints (13.00 V, 1.000 A) exceed your limits; set lower \
                 values before switching the output on."
            )
        );
        let mut m = connected_model();
        m.remote = RemoteState::Denied;
        assert_eq!(
            m.remote_notice().as_deref(),
            Some("The supply denied remote control. Press Request remote control to ask again.")
        );
        m.remote = RemoteState::Lost;
        assert_eq!(
            m.remote_notice().as_deref(),
            Some("Remote control was lost. Press Request remote control to take it again.")
        );
    }

    /// Test: UT-APP-023
    #[test]
    fn the_close_question() {
        let mut m = connected_model();
        m.close_dialog = Some(CloseOrigin::Window);
        m.reading = None;
        assert_eq!(
            m.close_question(at_s(1.0)),
            Some(CloseQuestion {
                text: "There is no reading, so the output may be on. Switch it off before \
                       disconnecting?"
                    .into(),
                switch_off: true
            })
        );
        m.apply(reading(1, r(1, 2, 0, 1300, 1000, at_s(1.0))), at_s(1.0));
        assert_eq!(
            m.close_question(at_s(1.0)),
            Some(CloseQuestion {
                text: "The output is on and the supply is in PD mode, where the app cannot \
                       switch it off. Switch it off on the supply, or disconnect and leave it \
                       on."
                .into(),
                switch_off: false
            })
        );
        let mut m = connected_model();
        m.close_dialog = Some(CloseOrigin::Disconnect);
        m.apply(reading(1, r(0, 0, 0, 1300, 1000, at_s(1.0))), at_s(1.0));
        assert_eq!(
            m.close_question(at_s(1.5)),
            Some(CloseQuestion {
                text: "The output is now off.".into(),
                switch_off: false
            })
        );
        m.close_dialog = None;
        assert_eq!(m.close_question(at_s(1.5)), None);
    }

    /// Test: UT-APP-023
    #[test]
    fn the_banners_in_order() {
        let mut m = connected_model();
        for (kind, text) in [
            (BannerKind::SetpointsChanged, "s"),
            (BannerKind::Error, "e"),
            (BannerKind::UncleanExit, "u"),
            (BannerKind::OffFailed, "o"),
        ] {
            m.banners.push(Banner {
                kind,
                text: text.into(),
            });
        }
        m.apply(reading(1, r(0, 2, 0, 1300, 1000, at_s(1.0))), at_s(1.0));
        m.limits.max_volts = Some(5.0);
        m.remote = RemoteState::Denied;
        let shown = m.banners_to_show(at_s(1.0));
        let kinds: Vec<ShownKind> = shown.iter().map(|s| s.kind).collect();
        assert_eq!(
            kinds,
            vec![
                ShownKind::Banner(BannerKind::OffFailed),
                ShownKind::Banner(BannerKind::UncleanExit),
                ShownKind::Banner(BannerKind::Error),
                ShownKind::Banner(BannerKind::SetpointsChanged),
                ShownKind::ModeNotice,
                ShownKind::LimitNotice,
                ShownKind::RemoteNotice,
            ]
        );
        let dismissible: Vec<bool> = shown.iter().map(|s| s.dismissible).collect();
        assert_eq!(
            dismissible,
            vec![true, true, true, true, false, false, false]
        );
    }

    /// Test: UT-APP-023
    #[test]
    fn repaint_deadlines() {
        let mut m = connected_model();
        m.prompt = Some(Prompt {
            kind: PromptKind::AllowRemoteControl,
            text: ALLOW_REMOTE_CONTROL,
            bound_s: 70,
            since: at_s(0.0),
        });
        assert_eq!(
            m.repaint_after(at_s(12.4)),
            Some(Duration::from_millis(600))
        );
        let mut m = connected_model();
        m.phase = Phase::Closing;
        m.close_pending = true;
        m.closing_since = Some(at_s(0.0));
        assert_eq!(m.repaint_after(at_s(2.0)), Some(Duration::from_secs(3)));
        let mut m = connected_model();
        m.close_dialog = Some(CloseOrigin::Window);
        assert_eq!(m.repaint_after(at_s(2.0)), Some(Duration::from_secs(1)));
        assert_eq!(connected_model().repaint_after(at_s(2.0)), None);
    }

    /// Test: UT-APP-025
    #[test]
    fn an_older_reading_never_replaces_a_newer_one() {
        let mut m = connected_model();
        m.apply(reading(1, r(0, 0, 0, 1300, 1000, at_s(2.0))), at_s(2.0));
        m.apply(reading(1, r(0, 0, 0, 500, 100, at_s(1.0))), at_s(2.1));
        assert_eq!(m.reading.map(|r| r.at), Some(at_s(2.0)));
        assert_eq!(m.voltage.text, "13.00");
        assert_eq!(m.current.text, "1.000");
        assert_eq!(m.chart.len(), 2);
    }

    /// Test: UT-APP-025
    #[test]
    fn a_scan_keeps_a_selection_that_is_still_found() {
        let mut m = idle_with_a();
        m.scan_id = Some(3);
        m.apply(
            AppEvent::ScanResult {
                id: 3,
                found: vec![found_a(), found_b()],
                message: None,
            },
            at_s(1.0),
        );
        assert_eq!(m.selected.as_deref(), Some("A"));
        assert_eq!(m.found, vec![found_a(), found_b()]);
    }

    /// Test: UT-APP-025
    #[test]
    fn ready_clears_the_bind_prompt_and_is_ignored_while_closing() {
        let mut m = connecting_with_prompt();
        let ready = AppEvent::Ready {
            sid: 1,
            info: info(),
            reading: None,
            transport: Some(Kind::Ble),
        };
        m.apply(ready.clone(), at_s(1.0));
        assert_eq!(m.phase, Phase::Connected);
        assert_eq!(m.prompt, None);

        let mut m = connecting_with_prompt();
        m.phase = Phase::Closing;
        let before = m.clone();
        m.apply(ready, at_s(1.0));
        assert_eq!(m.phase, Phase::Closing);
        assert_eq!(m.log.len(), before.log.len() + 1);
        m.log = before.log.clone();
        assert_eq!(m, before);
    }

    /// Test: UT-APP-025
    #[test]
    fn a_command_lost_with_the_link_is_only_logged() {
        let mut m = connected_model();
        m.pending.insert(
            6,
            Pending {
                what: What::SetVoltage,
                sent: at_s(0.0),
                limits: None,
            },
        );
        let lines = m.log.len();
        m.apply(
            done(6, What::SetVoltage, err(ErrorKind::LinkLost, "x")),
            at_s(1.0),
        );
        assert_eq!(m.log.len(), lines + 1);
        assert!(m.banners.is_empty());
        assert!(!m.pending.contains_key(&6));
    }

    /// Test: UT-APP-025
    #[test]
    fn a_refused_recording_turns_the_recording_off() {
        let mut m = connected_model();
        m.recording = RecordingState::Starting {
            path: PathBuf::from("p"),
        };
        m.pending.insert(
            7,
            Pending {
                what: What::StartRecording,
                sent: at_s(0.0),
                limits: None,
            },
        );
        m.apply(
            done(
                7,
                What::StartRecording,
                err(ErrorKind::App, "not connected"),
            ),
            at_s(1.0),
        );
        assert_eq!(m.recording, RecordingState::Off);
        assert_eq!(
            banner(&m, BannerKind::Error).as_deref(),
            Some("start recording failed: not connected")
        );
    }

    /// Test: UT-APP-025
    #[test]
    fn a_pending_output_on_survives_a_loss() {
        let mut m = connected_model();
        let mut ids = IdSource::new();
        for _ in 0..8 {
            ids.next_id();
        }
        let sent = handle(&mut m, UiAction::OutputOn, clock_s(1.0), &mut ids);
        assert_eq!(sent, vec![Command::OutputOn { id: 9 }]);
        m.apply(
            session(SessionEvent::LinkLost { text: "L".into() }),
            at_s(1.1),
        );
        assert!(matches!(m.phase, Phase::Lost { .. }));
        assert_eq!(m.pending.get(&9).map(|p| p.what), Some(What::OutputOn));
    }

    /// Test: UT-APP-023
    #[test]
    fn the_rows_and_lines_of_the_screens() {
        let mut m = connected_model();
        m.prompt = Some(Prompt {
            kind: PromptKind::ConfirmConnection,
            text: CONFIRM_CONNECTION,
            bound_s: 30,
            since: at_s(0.1),
        });
        assert_eq!(
            m.prompt_line(at_s(12.4)).as_deref(),
            Some("Confirm the connection on the supply's screen within 30 seconds (18 s left)")
        );
        assert_eq!(
            m.info_rows(),
            vec![
                ("Transport", "ble".to_string()),
                ("Model", "MP305B".to_string()),
                ("Version", "1.6.0.40".to_string()),
                ("Hardware", "2.0.2.0".to_string()),
            ]
        );
        let mut usb = info();
        usb.hardware = None;
        m.info = Some(usb);
        assert_eq!(m.info_rows()[3], ("Hardware", "not reported".to_string()));
        assert_eq!(
            m.reading_rows(),
            vec![
                ("Voltage", "0.00 V".to_string()),
                ("Current", "0.000 A".to_string()),
                ("Power", "0.00 W".to_string()),
                ("Set voltage", "13.00 V".to_string()),
                ("Set current", "1.000 A".to_string()),
                ("Output", "off".to_string()),
                ("Regulation", "off".to_string()),
                ("Mode", "DC mode".to_string()),
                ("Faults", "none".to_string()),
            ]
        );
        m.apply(reading(1, r(1, 2, 33, 1300, 1000, at_s(1.0))), at_s(1.0));
        let rows = m.reading_rows();
        assert_eq!(rows[5], ("Output", "on".to_string()));
        assert_eq!(rows[7], ("Mode", "PD mode".to_string()));
        assert_eq!(
            rows[8],
            ("Faults", "reversed output, over current".to_string())
        );
        assert!(m.settings_rows().is_empty());
        m.settings = Some(settings());
        assert_eq!(
            m.settings_rows(),
            vec![
                ("Charge limit", "90 %".to_string()),
                ("Volume", "2".to_string()),
                ("Screen off", "0".to_string()),
                ("Auto shutdown", "0 min".to_string()),
                ("Screen direction", "1".to_string()),
                ("Ramp step", "500 mV per 100 ms".to_string()),
                ("OCP delay", "50 ms".to_string()),
                ("USB line drop", "0".to_string()),
            ]
        );
        assert_eq!(m.remote_line(), "Remote control: none");
        assert_eq!(m.closing_line(), None);
        m.phase = Phase::Closing;
        m.off_requested = true;
        assert_eq!(
            m.closing_line(),
            Some("Disconnecting: switching the output off and releasing remote control.")
        );
        assert!(!m.close_anyway_enabled());
        m.close_pending = true;
        m.close_overdue = true;
        assert!(m.close_anyway_enabled());
        assert_eq!(m.close_dialog_title(), None);
        m.close_dialog = Some(CloseOrigin::Window);
        assert_eq!(m.close_dialog_title(), Some("Close MP305 Remote"));
        m.close_dialog = Some(CloseOrigin::Disconnect);
        assert_eq!(m.close_dialog_title(), Some("Disconnect"));
    }

    /// Test: UT-APP-023
    #[test]
    fn the_connection_screen_and_recording_lines() {
        let mut m = Model::new(PathBuf::from("/rec"), t0());
        let mut nameless = found_b();
        nameless.name = String::new();
        nameless.unit_id = String::new();
        m.found = vec![found_a(), nameless];
        m.selected = Some("A".into());
        let rows = m.found_rows();
        assert_eq!(
            rows[0],
            FoundRow {
                identifier: "A".into(),
                name: "MP305B".into(),
                unit: "ABC".into(),
                transport: "ble".into(),
                signal: "-60 dBm".into(),
                remote: "on".into(),
                selected: true,
            }
        );
        assert_eq!(
            (
                rows[1].name.as_str(),
                rows[1].unit.as_str(),
                rows[1].signal.as_str()
            ),
            ("(no name)", "unknown", "unknown")
        );
        assert_eq!(
            (rows[1].remote.as_str(), rows[1].selected),
            ("unknown", false)
        );
        assert!(!m.is_scanning());
        assert_eq!(m.connecting_line(), None);
        m.connected = Some(found_a());
        m.phase = Phase::Connecting;
        assert_eq!(
            m.connecting_line().as_deref(),
            Some("Connecting to ble A MP305B (unit ABC)")
        );
        m.max_voltage
            .edit("31".into(), FieldKind::MaxVoltage, &Limits::none());
        assert_eq!(
            m.field_error(FieldKind::MaxVoltage).as_deref(),
            Some("voltage 31 is outside 0 to 30")
        );
        assert_eq!(m.field_error(FieldKind::MaxCurrent), None);
        assert_eq!(m.recording_line(), "Recording: off");
        m.recording = RecordingState::Starting {
            path: PathBuf::from("/x/a.csv"),
        };
        assert_eq!(m.recording_line(), "Recording: starting: /x/a.csv");
        m.recording = RecordingState::On {
            path: PathBuf::from("/x/a.csv"),
            rows: 12,
        };
        assert_eq!(m.recording_line(), "Recording: 12 rows in /x/a.csv");
        assert_eq!(m.recording_placeholder(), "/rec/mp305-YYYYMMDD-HHMMSS.csv");
        let banner = Shown {
            kind: ShownKind::Banner(BannerKind::Error),
            text: "e".into(),
            dismissible: true,
        };
        assert_eq!(banner.dismiss(), Some(BannerKind::Error));
        let notice = Shown {
            kind: ShownKind::ModeNotice,
            text: "n".into(),
            dismissible: false,
        };
        assert_eq!(notice.dismiss(), None);
    }
}
