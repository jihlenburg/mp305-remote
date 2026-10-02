//! Implements: DD-APP-031 (the connection screen).
//!
//! Coverage: excluded from the measurement as GUI drawing code (ADR-0008;
//! app DD, section 8, decision 9); UT-APP-020 inspects this file instead.
//!
//! The connection screen: the scan, the list of found supplies, connect
//! and cancel, the reconnect checkbox, the limit fields and the bench
//! safety note, which is readable without a network.

use eframe::egui;

use crate::actions::UiAction;
use crate::fields::FieldKind;
use crate::model::{Instant, Model, SCAN_S_RANGE};
use crate::texts::{self, label};
use crate::ui::screens;

/// Draws the connection screen.
pub fn show(ui: &mut egui::Ui, model: &Model, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    ui.horizontal(|ui| {
        actions.extend(screens::button(
            ui,
            model.scan_enabled(),
            label::SCAN,
            UiAction::Scan,
        ));
        let mut seconds = model.scan_s;
        let slider = egui::Slider::new(&mut seconds, SCAN_S_RANGE)
            .suffix(" s")
            .text(label::SCAN_TIME);
        if ui.add_enabled(model.scan_enabled(), slider).changed() {
            actions.push(UiAction::SetScanTime(seconds));
        }
        if model.is_scanning() {
            ui.spinner();
            ui.label(label::SCANNING);
        }
    });
    ui.heading(label::SUPPLIES);
    egui::Grid::new("found")
        .num_columns(label::COLUMNS.len())
        .striped(true)
        .show(ui, |ui| {
            for column in label::COLUMNS {
                ui.strong(column);
            }
            ui.end_row();
            for row in model.found_rows() {
                if ui.selectable_label(row.selected, &row.name).clicked() {
                    actions.push(UiAction::Select(row.identifier.clone()));
                }
                ui.label(&row.unit);
                ui.label(&row.transport);
                ui.label(&row.signal);
                ui.label(&row.remote);
                ui.end_row();
            }
        });
    if let Some(message) = &model.scan_message {
        ui.label(message);
    }
    ui.horizontal(|ui| {
        actions.extend(screens::button(
            ui,
            model.connect_enabled(),
            label::CONNECT,
            UiAction::Connect,
        ));
        if let Some(line) = model.connecting_line() {
            ui.spinner();
            ui.label(line);
            actions.extend(screens::button(
                ui,
                model.disconnect_enabled(),
                label::CANCEL,
                UiAction::Disconnect,
            ));
        }
    });
    actions.extend(reconnect_checkbox(ui, model, now));
    ui.separator();
    actions.extend(limit_fields(ui, model, now));
    ui.separator();
    egui::CollapsingHeader::new(label::BENCH_SAFETY)
        .default_open(true)
        .show(ui, |ui| {
            ui.label(texts::BENCH_SAFETY);
            ui.hyperlink_to(label::BENCH_SAFETY_LINK, texts::BENCH_SAFETY_URL);
        });
    actions
}

/// The reconnect checkbox.
pub fn reconnect_checkbox(ui: &mut egui::Ui, model: &Model, _now: Instant) -> Vec<UiAction> {
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

/// The two limit fields with their hints, the limits in force and the
/// apply button.
pub fn limit_fields(ui: &mut egui::Ui, model: &Model, _now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    ui.strong(label::LIMITS);
    actions.extend(screens::field(
        ui,
        model,
        FieldKind::MaxVoltage,
        label::MAX_VOLTAGE,
        UiAction::ApplyLimits,
    ));
    actions.extend(screens::field(
        ui,
        model,
        FieldKind::MaxCurrent,
        label::MAX_CURRENT,
        UiAction::ApplyLimits,
    ));
    ui.horizontal(|ui| {
        actions.extend(screens::button(
            ui,
            model.apply_limits_enabled(),
            label::APPLY_LIMITS,
            UiAction::ApplyLimits,
        ));
        ui.label(model.limits_text());
    });
    actions
}
