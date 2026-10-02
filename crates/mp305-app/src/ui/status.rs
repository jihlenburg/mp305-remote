//! Implements: DD-APP-031 (the status area).
//!
//! Coverage: excluded from the measurement as GUI drawing code (ADR-0008;
//! app DD, section 8, decision 9); UT-APP-020 inspects this file instead.
//!
//! The status area, on every screen: the banners with a dismiss button on
//! the dismissible ones, the prompt with its countdown, and the event log.

use eframe::egui;

use crate::actions::UiAction;
use crate::model::{Instant, Model, ShownKind};
use crate::texts::label;

/// The height of the event log in points.
const LOG_HEIGHT: f32 = 140.0;

/// Draws the status area.
pub fn show(ui: &mut egui::Ui, model: &Model, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    for shown in model.banners_to_show(now) {
        ui.horizontal_wrapped(|ui| {
            let color = match shown.kind {
                ShownKind::Fatal | ShownKind::Loss | ShownKind::Banner(_) => {
                    ui.visuals().error_fg_color
                }
                ShownKind::Reconnect
                | ShownKind::ModeNotice
                | ShownKind::LimitNotice
                | ShownKind::RemoteNotice => ui.visuals().warn_fg_color,
            };
            ui.colored_label(color, &shown.text);
            if let Some(kind) = shown.dismiss() {
                if ui.small_button(label::DISMISS).clicked() {
                    actions.push(UiAction::Dismiss(kind));
                }
            }
        });
    }
    if let Some(line) = model.prompt_line(now) {
        ui.strong(line);
    }
    egui::CollapsingHeader::new(label::EVENT_LOG)
        .default_open(false)
        .show(ui, |ui| {
            egui::ScrollArea::vertical()
                .max_height(LOG_HEIGHT)
                .stick_to_bottom(true)
                .show(ui, |ui| {
                    for line in &model.log {
                        ui.monospace(line);
                    }
                });
        });
    actions
}
