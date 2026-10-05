//! Implements: DD-APP-034, DD-APP-035, DD-APP-031 (the details panel).
//!
//! Coverage: excluded from the measurement as GUI drawing code (ADR-0008;
//! app DD, section 8, decision 9); UT-APP-020 inspects this file instead.
//!
//! Everything the front panel leaves out, in a closable window at the
//! right. Connected: the supply's facts and the connection, the reading
//! in full, remote control with Request and Release, the supply settings,
//! your limits, the reconnect checkbox, the recording file and state, and
//! the event log. Before a connection: the scan time, your limits, the
//! reconnect checkbox, the bench safety note and the event log.

use eframe::egui::{self, Align2, RichText};

use crate::actions::UiAction;
use crate::fields::FieldKind;
use crate::model::{Instant, Model, Screen, SCAN_S_RANGE};
use crate::texts::{self, label};
use crate::ui::{theme, widgets, Theme, View};

/// The width of the panel in points.
const WIDTH: f32 = 340.0;
/// The height of the event log in points.
const LOG_HEIGHT: f32 = 160.0;

/// Draws the details panel while it is open.
pub fn show(ui: &mut egui::Ui, model: &Model, view: &mut View, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    let mut open = view.details;
    let height = ui.ctx().content_rect().height() - 4.0 * theme::PAD - 32.0;
    egui::Window::new(label::DETAILS)
        .open(&mut open)
        .anchor(Align2::RIGHT_TOP, egui::vec2(-theme::PAD, theme::PAD))
        .collapsible(false)
        .resizable(false)
        .default_width(WIDTH)
        .max_width(WIDTH)
        .max_height(height.max(120.0))
        .vscroll(true)
        .show(ui.ctx(), |ui| {
            actions.extend(content(ui, model, view, now));
        });
    view.details = open;
    actions
}

/// Shared content for the full window and compact scrollable upper panel.
pub fn content(ui: &mut egui::Ui, model: &Model, view: &mut View, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    ui.horizontal(|ui| {
        ui.label("Theme");
        ui.selectable_value(&mut view.theme, Theme::Standard, "Standard");
        ui.selectable_value(&mut view.theme, Theme::Retro, "Retro");
    });
    ui.add_space(8.0);
    if model.screen() == Screen::Main {
        actions.extend(widgets::outlined(
            ui,
            model.disconnect_enabled(),
            label::DISCONNECT,
            UiAction::Disconnect,
        ));
    }
    actions.extend(friendly_name(ui, model));
    match model.screen() {
        Screen::Main => actions.extend(connected(ui, model, now)),
        Screen::Connection => actions.extend(unconnected(ui, model, now)),
    }
    actions
}

/// The local name of the selected or connected endpoint.
fn friendly_name(ui: &mut egui::Ui, model: &Model) -> Vec<UiAction> {
    let mut actions = Vec::new();
    ui.label(RichText::new("Device name").strong());
    let mut name = model.names.draft.clone();
    let enabled =
        model.names.loaded && model.names.target.is_some() && model.names.saving.is_none();
    let response = ui.add_enabled(
        enabled,
        egui::TextEdit::singleline(&mut name)
            .id_salt("device-name")
            .desired_width(f32::INFINITY)
            .hint_text("Optional friendly name"),
    );
    response.widget_info(|| egui::WidgetInfo {
        label: Some("Device name".into()),
        ..egui::WidgetInfo::text_edit(enabled, &model.names.draft, &name, "Optional friendly name")
    });
    if response.changed() {
        actions.push(UiAction::EditName(name));
    }
    actions.extend(widgets::outlined(
        ui,
        model.names.can_save(),
        "Save name",
        UiAction::SaveName,
    ));
    if model.names.saving.is_some() {
        ui.label(widgets::dim("Saving name..."));
    }
    if let Some(error) = &model.names.error {
        ui.add(egui::Label::new(RichText::new(error).color(theme::colors(ui).live)).wrap());
    }
    if let Err(error) = crate::names::validate(&model.names.draft) {
        ui.add(egui::Label::new(RichText::new(error).color(theme::colors(ui).live)).wrap());
    }
    ui.add(egui::Label::new(widgets::dim("Names are saved on this computer, separately for USB and Bluetooth. USB names may need reassignment after reconnecting or rebooting. Clear the field to remove a name.")).wrap());
    if model.names.target.is_none() {
        ui.add(
            egui::Label::new(widgets::dim(
                "Select a device to name it. USB naming also requires a valid host identity.",
            ))
            .wrap(),
        );
    }
    ui.add_space(theme::PAD);
    actions
}

/// A small dim heading with space above it.
fn heading(ui: &mut egui::Ui, text: &str) {
    ui.add_space(theme::PAD);
    ui.label(widgets::dim(text));
    ui.add_space(theme::UNIT);
}

/// The panel while a supply is connected.
fn connected(ui: &mut egui::Ui, model: &Model, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    let mut info = model.info_rows();
    for (name, value) in &mut info {
        if *name == label::TRANSPORT {
            if let Some(kind) = model.transport {
                *value = texts::transport_name(kind).to_string();
            }
        }
    }
    info.push((label::CONNECTION, model.supply_line()));
    widgets::rows(ui, "info", &info);

    heading(ui, label::READINGS);
    widgets::rows(ui, "reading", &model.reading_rows());

    ui.add_space(theme::PAD);
    ui.label(model.remote_line());
    ui.horizontal_wrapped(|ui| {
        actions.extend(widgets::outlined(
            ui,
            model.request_remote_enabled(),
            label::REQUEST_REMOTE,
            UiAction::RequestRemoteControl,
        ));
        actions.extend(widgets::outlined(
            ui,
            model.release_remote_enabled(),
            label::RELEASE_REMOTE,
            UiAction::ReleaseRemoteControl,
        ));
    });

    heading(ui, label::SETTINGS);
    widgets::rows(ui, "settings", &model.settings_rows());

    actions.extend(limits(ui, model));
    ui.add_space(theme::PAD);
    actions.extend(reconnect(ui, model));

    heading(ui, label::RECORDING);
    let mut path = model.recording_path.clone();
    let response = ui.add(
        egui::TextEdit::singleline(&mut path)
            .id_salt("recording-path")
            .desired_width(f32::INFINITY)
            .hint_text(widgets::dim(model.recording_placeholder())),
    );
    response.widget_info(|| egui::WidgetInfo {
        label: Some("Recording file".into()),
        ..egui::WidgetInfo::text_edit(
            true,
            &model.recording_path,
            &path,
            model.recording_placeholder(),
        )
    });
    if response.changed() {
        actions.push(UiAction::EditRecordingPath(path));
    }
    ui.add(egui::Label::new(widgets::dim(model.recording_line())).wrap());

    actions.extend(log(ui, model, now));
    actions
}

/// The panel before a connection.
fn unconnected(ui: &mut egui::Ui, model: &Model, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    let mut seconds = model.scan_s;
    let slider = egui::Slider::new(&mut seconds, SCAN_S_RANGE)
        .suffix(" s")
        .text(label::SCAN_TIME);
    if ui.add_enabled(model.scan_enabled(), slider).changed() {
        actions.push(UiAction::SetScanTime(seconds));
    }
    actions.extend(limits(ui, model));
    ui.add_space(theme::PAD);
    actions.extend(reconnect(ui, model));

    heading(ui, label::BENCH_SAFETY);
    ui.add(egui::Label::new(RichText::new(texts::BENCH_SAFETY).size(theme::SMALL)).wrap());
    ui.hyperlink_to(
        RichText::new(label::BENCH_SAFETY_LINK).size(theme::SMALL),
        texts::BENCH_SAFETY_URL,
    );

    actions.extend(log(ui, model, now));
    actions
}

/// Your limits: the two fields with their hints, the limits in force and
/// the apply button.
fn limits(ui: &mut egui::Ui, model: &Model) -> Vec<UiAction> {
    let mut actions = Vec::new();
    heading(ui, label::LIMITS);
    actions.extend(widgets::form_field(
        ui,
        model,
        FieldKind::MaxVoltage,
        label::MAX_VOLTAGE,
        UiAction::ApplyLimits,
    ));
    ui.add_space(theme::UNIT);
    actions.extend(widgets::form_field(
        ui,
        model,
        FieldKind::MaxCurrent,
        label::MAX_CURRENT,
        UiAction::ApplyLimits,
    ));
    ui.add_space(theme::UNIT);
    ui.horizontal_wrapped(|ui| {
        actions.extend(widgets::outlined(
            ui,
            model.apply_limits_enabled(),
            label::APPLY_LIMITS,
            UiAction::ApplyLimits,
        ));
        ui.label(widgets::dim(model.limits_text()));
    });
    actions
}

/// The reconnect checkbox.
fn reconnect(ui: &mut egui::Ui, model: &Model) -> Vec<UiAction> {
    let mut on = model.reconnect;
    if ui
        .checkbox(&mut on, label::RECONNECT_AUTOMATICALLY)
        .changed()
    {
        vec![UiAction::SetReconnect(on)]
    } else {
        Vec::new()
    }
}

/// The event log, newest at the bottom.
fn log(ui: &mut egui::Ui, model: &Model, _now: Instant) -> Vec<UiAction> {
    heading(ui, label::EVENT_LOG);
    egui::ScrollArea::vertical()
        .id_salt("log")
        .max_height(LOG_HEIGHT)
        .auto_shrink([false, true])
        .stick_to_bottom(true)
        .show(ui, |ui| {
            for line in &model.log {
                ui.add(
                    egui::Label::new(RichText::new(line).font(theme::mono(theme::SMALL))).wrap(),
                );
            }
        });
    Vec::new()
}
