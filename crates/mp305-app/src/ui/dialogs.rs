//! Implements: DD-APP-031 (the close question).
//!
//! Coverage: excluded from the measurement as GUI drawing code (ADR-0008;
//! app DD, section 8, decision 9); UT-APP-020 inspects this file instead.
//!
//! The close question as a non-modal window, so that Output OFF stays
//! clickable while it is open (SR-041).

use eframe::egui;

use crate::actions::{CloseChoice, UiAction};
use crate::model::{Instant, Model};
use crate::texts::label;

/// Draws the close question while it is open.
pub fn show(ui: &mut egui::Ui, model: &Model, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    let (Some(title), Some(question)) = (model.close_dialog_title(), model.close_question(now))
    else {
        return actions;
    };
    egui::Window::new(title)
        .collapsible(false)
        .resizable(false)
        .show(ui.ctx(), |ui| {
            ui.label(&question.text);
            ui.horizontal(|ui| {
                if question.switch_off {
                    if ui.button(label::SWITCH_OFF).clicked() {
                        actions.push(UiAction::CloseAnswer(CloseChoice::SwitchOff));
                    }
                    if ui.button(label::LEAVE_ON).clicked() {
                        actions.push(UiAction::CloseAnswer(CloseChoice::LeaveOn));
                    }
                } else if ui.button(label::DISCONNECT).clicked() {
                    actions.push(UiAction::CloseAnswer(CloseChoice::LeaveOn));
                }
                if ui.button(label::CANCEL).clicked() {
                    actions.push(UiAction::CloseAnswer(CloseChoice::Cancel));
                }
            });
        });
    actions
}
