//! Implements: DD-APP-031.
//!
//! Discovery presents distinct, accessible endpoints before an explicit
//! connection. Friendly names never replace the connection identifier.
//! Coverage: excluded as GUI drawing code (ADR-0008; app DD, section 8,
//! decision 9); UT-APP-020 inspects it, UT-APP-029 exercises its controls.

use eframe::egui::{self, Align, Layout, RichText, WidgetInfo, WidgetType};

use crate::actions::UiAction;
use crate::model::{Instant, Model};
use crate::texts::{self, label};
use crate::ui::{status, theme, widgets, View};

/// Draws the discovery column and its explicit connect action.
pub fn show(ui: &mut egui::Ui, model: &Model, view: &mut View, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    egui::Panel::bottom("connect-footer")
        .exact_size(28.0)
        .frame(egui::Frame::NONE)
        .show(ui, |ui| {
            if widgets::quiet_button(ui, true, label::DETAILS, theme::BODY) {
                view.details = !view.details;
            }
        });
    ui.heading(label::APP_TITLE);
    ui.label(widgets::dim("Bench power supply"));
    ui.add_space(theme::PAD);
    ui.horizontal(|ui| {
        ui.label(label::SUPPLIES);
        ui.with_layout(Layout::right_to_left(Align::Center), |ui| {
            actions.extend(widgets::outlined(
                ui,
                model.scan_enabled(),
                if model.found.is_empty() {
                    label::SCAN
                } else {
                    label::SCAN_AGAIN
                },
                UiAction::Scan,
            ));
        });
    });
    if model.is_scanning() {
        ui.horizontal(|ui| {
            ui.spinner();
            ui.label(widgets::dim(label::SCANNING));
        });
    }
    ui.add_space(theme::UNIT);
    egui::ScrollArea::vertical()
        .id_salt("found")
        .auto_shrink([false, true])
        .max_height(ui.available_height() * 0.5)
        .show(ui, |ui| {
            for found in &model.found {
                let name = model.device_name(found);
                let identity = format!(
                    "{} / {}",
                    texts::transport_name(found.transport),
                    found.identifier
                );
                let mut job = egui::text::LayoutJob::default();
                job.wrap.max_rows = 3;
                job.append(
                    &name,
                    0.0,
                    egui::TextFormat {
                        font_id: egui::FontId::new(theme::BODY, theme::bold()),
                        color: theme::TEXT,
                        ..Default::default()
                    },
                );
                job.append(
                    &format!("\n{identity}"),
                    0.0,
                    egui::TextFormat {
                        font_id: theme::mono(theme::SMALL),
                        color: theme::DIM,
                        ..Default::default()
                    },
                );
                let selected = model.selected.as_deref() == Some(&found.identifier);
                let response = ui.add_enabled(
                    model.scan_enabled(),
                    egui::Button::new(job)
                        .frame(true)
                        .wrap()
                        .selected(selected)
                        .min_size(egui::vec2(ui.available_width(), 68.0)),
                );
                response.widget_info(|| {
                    WidgetInfo::selected(
                        WidgetType::SelectableLabel,
                        model.scan_enabled(),
                        selected,
                        format!("{name}, {identity}"),
                    )
                });
                let hint = format!(
                    "{}\n{}",
                    found,
                    texts::found_hint(
                        &found.unit_id,
                        &found
                            .remote_flag
                            .map_or_else(|| "not reported".into(), |v| v.to_string())
                    )
                );
                if response.on_hover_text(hint).clicked() {
                    actions.push(UiAction::Select(found.identifier.clone()));
                }
            }
        });
    if let Some(message) = &model.scan_message {
        ui.add(egui::Label::new(widgets::dim(message)).wrap());
    }
    ui.add_space(theme::UNIT);
    actions.extend(widgets::outlined(
        ui,
        model.connect_enabled(),
        label::CONNECT,
        UiAction::Connect,
    ));
    ui.add_space(theme::PAD);
    actions.extend(status::show(ui, model, now));
    actions
}

/// Connection guidance and the offline bench note, directly visible.
pub fn hint(ui: &mut egui::Ui) {
    ui.add_space(48.0);
    ui.heading("Connect your supply");
    ui.add_space(8.0);
    ui.add(egui::Label::new(RichText::new(texts::CONNECT_HINT).color(theme::DIM)).wrap());
    ui.add_space(8.0);
    ui.add(egui::Label::new("Select a device on the left, then connect. You can give each connection a friendly name in Details.").wrap());
    ui.with_layout(Layout::bottom_up(Align::Min), |ui| {
        ui.hyperlink_to(label::BENCH_SAFETY_LINK, texts::BENCH_SAFETY_URL);
        ui.add(egui::Label::new(widgets::dim(texts::BENCH_SAFETY)).wrap());
        ui.label(RichText::new(label::BENCH_SAFETY).strong());
    });
}
