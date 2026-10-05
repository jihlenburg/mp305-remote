//! Implements: DD-APP-034, DD-APP-035, DD-APP-031.
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
    let footer_frame = theme::footer_frame();
    egui::Panel::bottom("connect-footer")
        .exact_size(
            if theme::is_retro(ui) { 32.0 } else { 28.0 }
                + f32::from(footer_frame.inner_margin.top),
        )
        .frame(footer_frame)
        .show(ui, |ui| {
            if widgets::quiet_button(ui, true, label::DETAILS, theme::BODY) {
                view.details = !view.details;
            }
        });
    if !theme::is_retro(ui) {
        ui.heading(label::APP_TITLE);
        ui.label(widgets::dim("Bench power supply"));
        ui.add_space(theme::PAD);
    }
    ui.horizontal(|ui| {
        if theme::is_retro(ui) {
            ui.label(RichText::new("SUPPLIES").font(theme::caption(ui, 24.0)));
        } else {
            ui.label(label::SUPPLIES);
        }
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
            actions.extend(endpoints(
                ui,
                model,
                if theme::is_retro(ui) { 72.0 } else { 68.0 },
            ));
        });
    if let Some(message) = &model.scan_message {
        ui.add(egui::Label::new(widgets::dim(message)).wrap());
    }
    ui.add_space(theme::UNIT);
    ui.with_layout(Layout::top_down_justified(Align::Min), |ui| {
        actions.extend(widgets::outlined(
            ui,
            model.connect_enabled(),
            label::CONNECT,
            UiAction::Connect,
        ));
    });
    ui.add_space(theme::PAD);
    actions.extend(status::show(ui, model, now));
    actions
}

/// Connection guidance and the offline bench note, directly visible.
pub fn hint(ui: &mut egui::Ui) {
    if theme::is_retro(ui) {
        ui.heading("CONNECT YOUR SUPPLY");
    } else {
        ui.add_space(48.0);
        ui.heading("Connect your supply");
    }
    ui.add_space(8.0);
    ui.add(egui::Label::new(RichText::new(texts::CONNECT_HINT).color(theme::DIM)).wrap());
    ui.add_space(16.0);
    ui.add(egui::Label::new("Select a supply, then press Connect.").wrap());
    ui.add_space(8.0);
    ui.add(
        egui::Label::new(widgets::dim(
            "Give each connection a friendly name in Details.",
        ))
        .wrap(),
    );
    ui.with_layout(Layout::bottom_up(Align::Min), |ui| {
        ui.hyperlink_to(label::BENCH_SAFETY_LINK, texts::BENCH_SAFETY_URL);
        ui.add(egui::Label::new(widgets::dim(texts::BENCH_SAFETY)).wrap());
        ui.label(RichText::new(label::BENCH_SAFETY).strong());
    });
}

/// Endpoint rows shared by the full and compact connection screens.
fn endpoints(ui: &mut egui::Ui, model: &Model, height: f32) -> Vec<UiAction> {
    let mut actions = Vec::new();
    for found in &model.found {
        let name = model.device_name(found);
        let identity = format!(
            "{} / {}",
            texts::transport_name(found.transport),
            found.identifier
        );
        let retro = theme::is_retro(ui);
        let transport = texts::transport_name(found.transport);
        let duplicates = model
            .found
            .iter()
            .filter(|item| item.transport == found.transport && model.device_name(item) == name)
            .count()
            > 1;
        let subtitle = if duplicates {
            let tail: String = found
                .identifier
                .chars()
                .rev()
                .take(6)
                .collect::<String>()
                .chars()
                .rev()
                .collect();
            format!("{transport} connection · …{tail}")
        } else {
            format!("{transport} connection")
        };
        let mut job = egui::text::LayoutJob::default();
        job.wrap.max_rows = 3;
        job.append(
            &name,
            0.0,
            egui::TextFormat {
                font_id: if retro {
                    theme::caption(ui, 20.0)
                } else {
                    egui::FontId::new(theme::BODY, theme::bold())
                },
                color: theme::colors(ui).text,
                ..Default::default()
            },
        );
        job.append(
            &format!("\n{}", if retro { &subtitle } else { &identity }),
            0.0,
            egui::TextFormat {
                font_id: if retro {
                    theme::text(theme::SMALL)
                } else {
                    theme::mono(theme::SMALL)
                },
                color: theme::DIM,
                ..Default::default()
            },
        );
        let selected = model.selected.as_deref() == Some(&found.identifier);
        let response = ui
            .scope(|ui| {
                if retro {
                    ui.spacing_mut().button_padding = egui::vec2(16.0, 8.0);
                    ui.spacing_mut().item_spacing.y = 8.0;
                }
                let mut button = egui::Button::new(job)
                    .frame(true)
                    .wrap()
                    .selected(selected)
                    .min_size(egui::vec2(ui.available_width(), height));
                if retro {
                    button = button
                        .corner_radius(8)
                        .fill(if selected {
                            egui::Color32::from_rgb(45, 37, 52)
                        } else {
                            egui::Color32::from_rgb(18, 18, 24)
                        })
                        .stroke(egui::Stroke::new(
                            1.0,
                            if selected {
                                theme::colors(ui).amps
                            } else {
                                theme::colors(ui).rule
                            },
                        ));
                }
                ui.add_enabled(model.scan_enabled(), button)
            })
            .inner;
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
    actions
}

/// A short discovery screen with connection actions fixed below the list.
pub fn compact(ui: &mut egui::Ui, model: &Model, view: &mut View, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    egui::Panel::bottom("compact-connect-footer")
        .exact_size(if theme::is_retro(ui) { 36.0 } else { 32.0 })
        .frame(egui::Frame::NONE.inner_margin(egui::Margin {
            top: 4,
            ..egui::Margin::ZERO
        }))
        .show(ui, |ui| {
            ui.columns(2, |columns| {
                if let Some(left) = columns.get_mut(0) {
                    left.with_layout(Layout::top_down_justified(Align::Min), |ui| {
                        actions.extend(widgets::outlined(
                            ui,
                            model.connect_enabled(),
                            label::CONNECT,
                            UiAction::Connect,
                        ));
                    });
                }
                if let Some(right) = columns.get_mut(1) {
                    right.with_layout(Layout::top_down_justified(Align::Min), |ui| {
                        if widgets::quiet_button(ui, true, label::DETAILS, theme::SMALL) {
                            view.details = true;
                        }
                    });
                }
            });
        });
    ui.horizontal(|ui| {
        if theme::is_retro(ui) {
            ui.label(RichText::new("SUPPLIES").font(theme::caption(ui, 24.0)));
        } else {
            ui.label(label::SUPPLIES);
        }
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
    egui::ScrollArea::vertical()
        .id_salt("compact-found")
        .min_scrolled_height(0.0)
        .auto_shrink([false, false])
        .show(ui, |ui| {
            actions.extend(status::lines(ui, model, now));
            if model.is_scanning() {
                ui.label(widgets::dim(label::SCANNING));
            }
            actions.extend(endpoints(ui, model, 56.0));
            if let Some(message) = &model.scan_message {
                ui.add(egui::Label::new(widgets::dim(message)).wrap());
            }
        });
    actions
}
