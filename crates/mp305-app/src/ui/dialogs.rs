//! Implements: DD-APP-031 (the close question).
//!
//! Coverage: excluded from the measurement as GUI drawing code (ADR-0008;
//! app DD, section 8, decision 9); UT-APP-020 inspects this file instead.
//!
//! The close question as a non-modal window in the middle of the screen,
//! so that the output key's Off stays clickable while it is open
//! (SR-041). Its texts and buttons are the model's; only the look follows
//! the tokens.

use eframe::egui::{self, Align2, RichText};

use crate::actions::{CloseChoice, UiAction};
use crate::model::{Instant, Model};
use crate::texts::label;
use crate::ui::{theme, widgets};

/// The width of the close question in points.
const WIDTH: f32 = 340.0;

/// Draws the close question while it is open.
pub fn show(ui: &mut egui::Ui, model: &Model, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    let (Some(title), Some(_)) = (model.close_dialog_title(), model.close_question(now)) else {
        return actions;
    };
    egui::Window::new(RichText::new(title).strong())
        .id(egui::Id::new("close-question"))
        .anchor(Align2::RIGHT_CENTER, egui::vec2(-theme::PAD, 0.0))
        .collapsible(false)
        .resizable(false)
        .default_width(WIDTH)
        .show(ui.ctx(), |ui| {
            actions.extend(content(ui, model, now));
        });
    actions
}

/// Shared question content; compact mode keeps it above the fixed output row.
pub fn content(ui: &mut egui::Ui, model: &Model, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    if let Some(question) = model.close_question(now) {
        ui.add(egui::Label::new(&question.text).wrap());
        ui.add_space(8.0);
        ui.horizontal_wrapped(|ui| {
            if question.switch_off {
                actions.extend(widgets::outlined(
                    ui,
                    true,
                    label::SWITCH_OFF,
                    UiAction::CloseAnswer(CloseChoice::SwitchOff),
                ));
                actions.extend(widgets::outlined(
                    ui,
                    true,
                    label::LEAVE_ON,
                    UiAction::CloseAnswer(CloseChoice::LeaveOn),
                ));
            } else {
                actions.extend(widgets::outlined(
                    ui,
                    true,
                    label::DISCONNECT,
                    UiAction::CloseAnswer(CloseChoice::LeaveOn),
                ));
            }
            actions.extend(widgets::outlined(
                ui,
                true,
                label::CANCEL,
                UiAction::CloseAnswer(CloseChoice::Cancel),
            ));
        });
    }
    actions
}
