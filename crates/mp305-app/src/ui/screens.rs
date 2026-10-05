//! Implements: DD-APP-031 (the layout of the screens), DD-APP-030 (the
//! form of the drawing functions).
//!
//! Coverage: excluded from the measurement as GUI drawing code (ADR-0008;
//! app DD, section 8, decision 9); UT-APP-020 inspects this file instead.
//!
//! The frame of both screens: a left column of fixed width, slightly
//! lighter than the window, and the right side. Connected, the column is
//! the front panel (`panel`) and the right side the chart (`chart`);
//! before a connection, the column lists the found supplies (`connect`)
//! and the right side says what to do. Then the details panel and the
//! close question. Every drawing function reads the model and reports
//! clicks as actions.

use eframe::egui;

use crate::actions::UiAction;
use crate::model::{Instant, Model, Screen};
use crate::ui::{chart, connect, details, dialogs, panel, theme, View};

/// The width of the left column in points.
pub(super) const COLUMN_WIDTH: f32 = 280.0;

/// Draws everything of a frame and returns the clicks.
pub fn show(ui: &mut egui::Ui, model: &Model, view: &mut View, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    let screen = model.screen();
    egui::Panel::left("column")
        .exact_size(COLUMN_WIDTH)
        .resizable(false)
        .frame(
            egui::Frame::new()
                .fill(theme::COLUMN)
                .inner_margin(egui::Margin::same(theme::PAD_MARGIN)),
        )
        .show(ui, |ui| match screen {
            Screen::Connection => actions.extend(connect::show(ui, model, view, now)),
            Screen::Main => actions.extend(panel::show(ui, model, view, now)),
        });
    egui::CentralPanel::default()
        .frame(
            egui::Frame::new()
                .fill(theme::WINDOW)
                .inner_margin(egui::Margin::same(theme::PAD_MARGIN)),
        )
        .show(ui, |ui| match screen {
            Screen::Connection => connect::hint(ui),
            Screen::Main => actions.extend(chart::show(ui, model, now)),
        });
    if view.details {
        actions.extend(details::show(ui, model, view, now));
    }
    actions.extend(dialogs::show(ui, model, now));
    actions
}
