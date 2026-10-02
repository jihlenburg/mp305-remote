//! Implements: DD-APP-031 (the layout of the screens), DD-APP-030 (the
//! form of the drawing functions).
//!
//! Coverage: excluded from the measurement as GUI drawing code (ADR-0008;
//! app DD, section 8, decision 9); UT-APP-020 inspects this file instead.
//!
//! Draws the status area, then the screen of the phase, then the close
//! question, and the field widget the screens share. Every drawing
//! function reads the model and reports clicks as actions.

use eframe::egui;

use crate::actions::UiAction;
use crate::fields::FieldKind;
use crate::model::{Instant, Model, Screen};
use crate::ui::{connect, dialogs, panel, status};

/// The width of a value field in points.
const FIELD_WIDTH: f32 = 90.0;

/// Draws everything of a frame and returns the clicks.
pub fn show(ui: &mut egui::Ui, model: &Model, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    egui::CentralPanel::default().show(ui, |ui| {
        actions.extend(status::show(ui, model, now));
        ui.separator();
        egui::ScrollArea::vertical()
            .auto_shrink([false, false])
            .show(ui, |ui| match model.screen() {
                Screen::Connection => actions.extend(connect::show(ui, model, now)),
                Screen::Main => actions.extend(panel::show(ui, model, now)),
            });
    });
    actions.extend(dialogs::show(ui, model, now));
    actions
}

/// A value field of `kind` with its label, its hint and its error: the
/// text edits a copy of the field's text and reports `EditField`, and
/// Enter reports `apply`.
pub fn field(
    ui: &mut egui::Ui,
    model: &Model,
    kind: FieldKind,
    label: &str,
    apply: UiAction,
) -> Vec<UiAction> {
    let mut actions = Vec::new();
    ui.horizontal(|ui| {
        ui.label(label);
        let mut text = model.field(kind).text.clone();
        let response = ui.add(
            egui::TextEdit::singleline(&mut text)
                .desired_width(FIELD_WIDTH)
                .hint_text(model.hint(kind)),
        );
        if response.changed() {
            actions.push(UiAction::EditField(kind, text));
        }
        if response.lost_focus() && ui.input(|i| i.key_pressed(egui::Key::Enter)) {
            actions.push(apply);
        }
        ui.weak(model.hint(kind));
    });
    if let Some(error) = model.field_error(kind) {
        ui.colored_label(ui.visuals().error_fg_color, error);
    }
    actions
}

/// A button enabled by `enabled` that reports `action` when clicked.
pub fn button(ui: &mut egui::Ui, enabled: bool, label: &str, action: UiAction) -> Vec<UiAction> {
    if ui.add_enabled(enabled, egui::Button::new(label)).clicked() {
        vec![action]
    } else {
        Vec::new()
    }
}

/// Rows of a label and a value in a grid.
pub fn rows(ui: &mut egui::Ui, id: &str, rows: &[(&'static str, String)]) {
    egui::Grid::new(id).num_columns(2).show(ui, |ui| {
        for (label, value) in rows {
            ui.label(*label);
            ui.label(value);
            ui.end_row();
        }
    });
}
