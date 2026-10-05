//! Implements: DD-APP-031 (the status area).
//!
//! Coverage: excluded from the measurement as GUI drawing code (ADR-0008;
//! app DD, section 8, decision 9); UT-APP-020 inspects this file instead.
//!
//! The status lines in the left column, on every screen: what the user
//! must know now. In order: the banners (with a dismiss button on the
//! dismissible ones, Reconnect under the loss, Request remote control
//! under a denied or lost grant), the prompt with its countdown, the
//! closing line with Close anyway, the connecting line with Cancel, the
//! active faults, the invalid fields, and commands the supply has not
//! answered for a second. Errors, faults and losses are in the live
//! colour; the rest in the text colour. The lines wrap inside the column
//! and scroll only when more of them are shown than fit.

use core::time::Duration;

use eframe::egui::{self, RichText};

use crate::actions::UiAction;
use crate::fields::FieldKind;
use crate::model::{Instant, Model, ShownKind};
use crate::texts::{self, label};
use crate::ui::{theme, widgets};

/// How long a command waits for its answer before the status lines name
/// it, so that quick answers do not flicker.
const PENDING_SHOWN_AFTER: Duration = Duration::from_secs(1);

/// The fields and the names their errors carry.
const FIELDS: [(FieldKind, &str); 4] = [
    (FieldKind::Voltage, label::VOLTAGE),
    (FieldKind::Current, label::CURRENT),
    (FieldKind::MaxVoltage, label::MAX_VOLTAGE),
    (FieldKind::MaxCurrent, label::MAX_CURRENT),
];

/// Draws the status lines into the space `ui` offers.
pub fn show(ui: &mut egui::Ui, model: &Model, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    let mut bounds = ui.available_rect_before_wrap();
    bounds.max.y = (bounds.bottom() - 4.0).max(bounds.top());
    ui.scope_builder(egui::UiBuilder::new().max_rect(bounds), |ui| {
        // Scroll content and focus outlines cannot paint into the fixed footer.
        ui.set_clip_rect(ui.clip_rect().intersect(bounds));
        egui::ScrollArea::vertical()
            .id_salt("status")
            .min_scrolled_height(0.0)
            .auto_shrink([false, true])
            .max_height(ui.available_height().max(0.0))
            .show(ui, |ui| {
                ui.spacing_mut().item_spacing.y = 8.0;
                actions.extend(lines(ui, model, now));
            });
    });
    actions
}

/// A wrapped status line in `color`.
fn line(ui: &mut egui::Ui, text: &str, color: egui::Color32) {
    ui.add(egui::Label::new(RichText::new(text).color(color)).wrap());
}

/// The status lines.
pub fn lines(ui: &mut egui::Ui, model: &Model, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    for shown in model.banners_to_show(now) {
        let color = match shown.kind {
            ShownKind::Fatal | ShownKind::Loss | ShownKind::Banner(_) => theme::colors(ui).live,
            ShownKind::Reconnect
            | ShownKind::ModeNotice
            | ShownKind::LimitNotice
            | ShownKind::RemoteNotice => theme::colors(ui).text,
        };
        line(ui, &shown.text, color);
        let reconnect = shown.kind == ShownKind::Reconnect && model.reconnect_enabled();
        let remote = shown.kind == ShownKind::RemoteNotice;
        if shown.dismiss().is_none() && !reconnect && !remote {
            continue;
        }
        ui.horizontal(|ui| {
            if let Some(kind) = shown.dismiss() {
                if widgets::quiet_button(ui, true, label::DISMISS, theme::SMALL) {
                    actions.push(UiAction::Dismiss(kind));
                }
            }
            if reconnect && widgets::quiet_button(ui, true, label::RECONNECT, theme::SMALL) {
                actions.push(UiAction::Reconnect);
            }
            if remote
                && widgets::quiet_button(
                    ui,
                    model.request_remote_enabled(),
                    label::REQUEST_REMOTE,
                    theme::SMALL,
                )
            {
                actions.push(UiAction::RequestRemoteControl);
            }
        });
    }
    if let Some(prompt) = model.prompt_line(now) {
        ui.add(
            egui::Label::new(RichText::new(prompt).color(theme::colors(ui).text).strong()).wrap(),
        );
    }
    if let Some(closing) = model.closing_line() {
        line(ui, closing, theme::colors(ui).text);
    }
    if model.close_anyway_enabled()
        && widgets::quiet_button(ui, true, label::CLOSE_ANYWAY, theme::SMALL)
    {
        actions.push(UiAction::CloseAnyway);
    }
    if let Some(connecting) = model.connecting_line() {
        ui.horizontal_wrapped(|ui| {
            ui.spinner();
            ui.label(connecting);
        });
        if widgets::quiet_button(ui, model.disconnect_enabled(), label::CANCEL, theme::SMALL) {
            actions.push(UiAction::Disconnect);
        }
    }
    if let Some(reading) = model.reading {
        let faults = reading.reading.faults;
        if !faults.is_empty() {
            line(ui, &texts::faults_line(faults), theme::colors(ui).live);
        }
    }
    for (kind, name) in FIELDS {
        if let Some(error) = model.field_error(kind) {
            line(
                ui,
                &texts::field_error_line(name, &error),
                theme::colors(ui).live,
            );
        }
    }
    for pending in model.pending.values() {
        if now.saturating_duration_since(pending.sent) >= PENDING_SHOWN_AFTER {
            line(ui, &texts::pending_line(pending.what), theme::DIM);
        }
    }
    actions
}
