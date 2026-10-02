//! Implements: DD-APP-031 (the main screen).
//!
//! Coverage: excluded from the measurement as GUI drawing code (ADR-0008;
//! app DD, section 8, decision 9); UT-APP-020 inspects this file instead.
//!
//! The main screen: the supply and its readings, the setpoint fields,
//! Output ON and Output OFF, remote control, the limits, the connection
//! buttons, the recording controls, the chart, and the closing line.

use eframe::egui;

use crate::actions::UiAction;
use crate::fields::FieldKind;
use crate::model::{Instant, Model};
use crate::texts::label;
use crate::ui::{chart, connect, screens};

/// The width of the recording path field in points.
const PATH_WIDTH: f32 = 360.0;

/// Draws the main screen.
pub fn show(ui: &mut egui::Ui, model: &Model, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    ui.heading(model.supply_line());
    if let Some(line) = model.closing_line() {
        ui.strong(line);
    }
    if model.close_anyway_enabled() {
        actions.extend(screens::button(
            ui,
            true,
            label::CLOSE_ANYWAY,
            UiAction::CloseAnyway,
        ));
    }
    ui.columns(3, |columns| {
        if let [left, middle, right] = columns {
            left.strong(label::SUPPLY);
            screens::rows(left, "info", &model.info_rows());
            middle.strong(label::READINGS);
            screens::rows(middle, "reading", &model.reading_rows());
            right.strong(label::SETTINGS);
            screens::rows(right, "settings", &model.settings_rows());
        }
    });
    ui.separator();
    actions.extend(setpoints(ui, model, now));
    ui.horizontal(|ui| {
        actions.extend(screens::button(
            ui,
            model.output_on_enabled(),
            label::OUTPUT_ON,
            UiAction::OutputOn,
        ));
        actions.extend(screens::button(
            ui,
            model.output_off_enabled(),
            label::OUTPUT_OFF,
            UiAction::OutputOff,
        ));
    });
    ui.horizontal(|ui| {
        ui.label(model.remote_line());
        actions.extend(screens::button(
            ui,
            model.request_remote_enabled(),
            label::REQUEST_REMOTE,
            UiAction::RequestRemoteControl,
        ));
        actions.extend(screens::button(
            ui,
            model.release_remote_enabled(),
            label::RELEASE_REMOTE,
            UiAction::ReleaseRemoteControl,
        ));
    });
    ui.separator();
    actions.extend(connect::limit_fields(ui, model, now));
    actions.extend(connect::reconnect_checkbox(ui, model, now));
    ui.horizontal(|ui| {
        actions.extend(screens::button(
            ui,
            model.disconnect_enabled(),
            label::DISCONNECT,
            UiAction::Disconnect,
        ));
        if model.reconnect_enabled() {
            actions.extend(screens::button(
                ui,
                true,
                label::RECONNECT,
                UiAction::Reconnect,
            ));
        }
    });
    ui.separator();
    actions.extend(recording(ui, model, now));
    ui.separator();
    actions.extend(chart::show(ui, model, now));
    actions
}

/// The two setpoint fields with their hints, apply buttons and the `not
/// applied` mark while edited.
fn setpoints(ui: &mut egui::Ui, model: &Model, _now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    ui.strong(label::SETPOINTS);
    for (kind, name, apply) in [
        (FieldKind::Voltage, label::VOLTAGE, UiAction::ApplyVoltage),
        (FieldKind::Current, label::CURRENT, UiAction::ApplyCurrent),
    ] {
        actions.extend(screens::field(ui, model, kind, name, apply.clone()));
        ui.horizontal(|ui| {
            actions.extend(screens::button(
                ui,
                model.apply_enabled(kind),
                label::APPLY,
                apply,
            ));
            if model.field(kind).edited {
                ui.weak(label::NOT_APPLIED);
            }
        });
    }
    actions
}

/// The recording controls: the path field with the automatic name as its
/// placeholder, start, stop, the state and the row count.
fn recording(ui: &mut egui::Ui, model: &Model, _now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    ui.strong(label::RECORDING);
    ui.horizontal(|ui| {
        let mut path = model.recording_path.clone();
        let response = ui.add(
            egui::TextEdit::singleline(&mut path)
                .desired_width(PATH_WIDTH)
                .hint_text(model.recording_placeholder()),
        );
        if response.changed() {
            actions.push(UiAction::EditRecordingPath(path));
        }
        actions.extend(screens::button(
            ui,
            model.recording_start_enabled(),
            label::START_RECORDING,
            UiAction::StartRecording,
        ));
        actions.extend(screens::button(
            ui,
            model.recording_stop_enabled(),
            label::STOP_RECORDING,
            UiAction::StopRecording,
        ));
    });
    ui.label(model.recording_line());
    actions
}
