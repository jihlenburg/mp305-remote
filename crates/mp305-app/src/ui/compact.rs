//! Implements: DD-APP-035, DD-APP-031 (compact instrument presentation).
//!
//! Live measurements and model-controlled actions share a small viewport.
//! Secondary content scrolls above the fixed output controls. Chart data
//! collection remains in the model, independent of whether plots are drawn.
//! Coverage: excluded as GUI drawing code (ADR-0008); UT-APP-020 inspects
//! this file and UT-APP-035 exercises the real controls and resize behavior.

use crate::actions::UiAction;
use crate::fields::{self, FieldKind};
use crate::model::{Instant, Model, RegulationMode, Screen};
use crate::texts::{self, label};
use crate::ui::{connect, details, dialogs, status, theme, widgets, View};
use eframe::egui::{self, Align, Layout, RichText, WidgetInfo, WidgetType};

/// Viewport threshold for displaying the three plots.
pub const FULL_WIDTH: f32 = 760.0;
/// Viewport height threshold for displaying the three plots.
pub const FULL_HEIGHT: f32 = 520.0;

/// Draws the compact content into the bounds reserved by the frame.
pub fn show(ui: &mut egui::Ui, model: &Model, view: &mut View, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    if model.screen() == Screen::Connection && !view.details && model.close_question(now).is_none()
    {
        return connect::compact(ui, model, view, now);
    }
    let main = model.screen() == Screen::Main;
    let bounds = ui.available_rect_before_wrap();
    let footer_bounds = egui::Rect::from_min_max(
        egui::pos2(
            bounds.left(),
            bounds.bottom() - if main { 68.0 } else { 24.0 },
        ),
        bounds.max,
    );
    ui.scope_builder(egui::UiBuilder::new().max_rect(footer_bounds), |ui| {
        ui.set_clip_rect(footer_bounds);
        if main {
            actions.extend(widgets::output_key_sized(ui, model, 36.0));
        }
        actions.extend(footer(ui, model, view));
    });
    let body = egui::Rect::from_min_max(
        bounds.min,
        egui::pos2(bounds.right(), footer_bounds.top() - 4.0),
    );
    let retro = theme::is_retro(ui);
    let scroll_bounds = if retro {
        body.with_max_x(body.right() + 8.0)
    } else {
        body
    };
    ui.scope_builder(egui::UiBuilder::new().max_rect(scroll_bounds), |ui| {
        // The compact frame reserves this outer gutter for the scrollbar.
        // Showing a warning must not squeeze the fixed numeral/field columns.
        ui.set_clip_rect(scroll_bounds);
        if retro {
            ui.spacing_mut().scroll = egui::style::ScrollStyle::floating();
            ui.spacing_mut().scroll.bar_width = 4.0;
            ui.spacing_mut().scroll.bar_outer_margin = 0.0;
        }
        egui::ScrollArea::vertical()
            .id_salt("compact-content")
            .min_scrolled_height(0.0)
            .auto_shrink([false, false])
            .max_height(ui.available_height().max(0.0))
            .show(ui, |ui| {
                if retro {
                    ui.set_width(body.width());
                } else {
                    ui.set_min_width(ui.available_width());
                }
                if let Some(title) = model.close_dialog_title() {
                    ui.strong(title);
                    actions.extend(dialogs::content(ui, model, now));
                } else {
                    actions.extend(status::lines(ui, model, now));
                    if view.details {
                        actions.extend(details::content(ui, model, view, now));
                    } else {
                        actions.extend(readings(ui, model));
                    }
                }
            });
    });
    actions
}

/// Measurements use identical column geometry at every compact width.
pub fn readings(ui: &mut egui::Ui, model: &Model) -> Vec<UiAction> {
    let mut actions = Vec::new();
    for kind in [FieldKind::Voltage, FieldKind::Current] {
        actions.extend(quantity(ui, model, kind));
    }
    let colors = theme::colors(ui);
    ui.separator();
    ui.horizontal(|ui| {
        if theme::is_retro(ui) {
            ui.label(widgets::dim("POWER").font(theme::caption(ui, 13.0)));
        } else {
            ui.label(widgets::dim("Power"));
        }
        let watts = model.reading.map_or_else(
            || texts::NO_WATTS.into(),
            |reading| texts::watts_number(reading.reading.raw.power),
        );
        widgets::readout(ui, &watts, [3, 2], label::WATTS, colors.watts, 18.0);
        ui.with_layout(Layout::right_to_left(Align::Center), |ui| {
            if let Some(reading) = model.reading {
                // Collapse only a redundant confirmed off regulation state.
                let state = if !reading.reading.output_on
                    && reading.reading.regulation == RegulationMode::Off
                {
                    "OFF".to_owned()
                } else {
                    format!(
                        "{} · {}",
                        if reading.reading.output_on {
                            "ON"
                        } else {
                            "OFF"
                        },
                        reading.reading.regulation
                    )
                };
                ui.add(egui::Label::new(RichText::new(state).color(colors.volts)).truncate());
            }
        });
    });
    actions
}

/// One labelled live quantity, its centred setpoint field and its Set button.
fn quantity(ui: &mut egui::Ui, model: &Model, kind: FieldKind) -> Vec<UiAction> {
    let colors = theme::colors(ui);
    let voltage = kind == FieldKind::Voltage;
    let (name, unit, color, apply) = if voltage {
        (
            "Voltage",
            label::VOLTS,
            colors.volts,
            UiAction::ApplyVoltage,
        )
    } else {
        ("Current", label::AMPS, colors.amps, UiAction::ApplyCurrent)
    };
    let value = model.reading.map_or_else(
        || {
            if voltage {
                texts::NO_VOLTS
            } else {
                texts::NO_AMPS
            }
            .to_owned()
        },
        |reading| {
            fields::display(
                kind,
                if voltage {
                    reading.reading.raw.voltage
                } else {
                    reading.reading.raw.current
                },
            )
        },
    );
    let (row, _) =
        ui.allocate_exact_size(egui::vec2(ui.available_width(), 54.0), egui::Sense::hover());
    let edit_x = row.right() - 120.0;
    let label_font = theme::caption(ui, 13.0);
    ui.painter().text(
        row.min,
        egui::Align2::LEFT_TOP,
        if theme::is_retro(ui) {
            name.to_uppercase()
        } else {
            name.to_owned()
        },
        label_font.clone(),
        color,
    );
    let caption = if model.field(kind).edited {
        label::NOT_APPLIED
    } else if voltage {
        "Set voltage"
    } else {
        "Current limit"
    };
    ui.painter().text(
        egui::pos2(edit_x, row.top()),
        egui::Align2::LEFT_TOP,
        if theme::is_retro(ui) {
            caption.to_uppercase()
        } else {
            caption.to_owned()
        },
        label_font,
        colors.dim,
    );
    let reading_y = row.top() + 14.0;
    let number = egui::Rect::from_min_max(
        egui::pos2(row.left(), reading_y),
        egui::pos2(edit_x - 4.0, row.bottom()),
    );
    ui.scope_builder(egui::UiBuilder::new().max_rect(number), |ui| {
        widgets::readout(ui, &value, [2, 3], unit, color, 34.0);
    });
    let digits = ui.painter().layout_no_wrap(
        "0123456789".into(),
        egui::FontId::new(34.0, theme::mono_bold()),
        color,
    );
    let center = reading_y + digits.mesh_bounds.center().y;
    let controls =
        egui::Rect::from_min_size(egui::pos2(edit_x, center - 14.0), egui::vec2(120.0, 28.0));
    ui.scope_builder(egui::UiBuilder::new().max_rect(controls), |ui| {
        widgets::inline_setpoint(ui, model, kind, apply)
    })
    .inner
}

/// Recording and Details, with full recording state available by hover and in Details.
fn footer(ui: &mut egui::Ui, model: &Model, view: &mut View) -> Vec<UiAction> {
    let mut actions = Vec::new();
    let width = (ui.available_width() - 8.0) / 2.0;
    ui.horizontal(|ui| {
        ui.spacing_mut().interact_size.y = 24.0;
        let font = theme::caption(ui, if theme::is_retro(ui) { 14.0 } else { 12.0 });
        let recording = model.recording_stop_enabled();
        let caption = if recording {
            label::STOP
        } else {
            label::RECORD
        };
        let enabled = recording || model.recording_start_enabled();
        let text = if recording {
            format!("Stop: {}", model.recording_line())
        } else {
            caption.to_owned()
        };
        let text = if theme::is_retro(ui) {
            text.to_uppercase()
        } else {
            text
        };
        let response = ui
            .add_enabled_ui(enabled, |ui| {
                ui.add_sized(
                    [width, 24.0],
                    egui::Button::new(RichText::new(text).font(font.clone()))
                        .truncate()
                        .fill(if theme::is_retro(ui) {
                            egui::Color32::from_rgb(21, 23, 35)
                        } else {
                            theme::colors(ui).window
                        })
                        .stroke(egui::Stroke::NONE)
                        .corner_radius(6),
                )
            })
            .inner;
        response.widget_info(|| WidgetInfo::labeled(WidgetType::Button, enabled, caption));
        if response.on_hover_text(model.recording_line()).clicked() {
            actions.push(if recording {
                UiAction::StopRecording
            } else {
                UiAction::StartRecording
            });
        }
        let details_text = if theme::is_retro(ui) {
            label::DETAILS.to_uppercase()
        } else {
            label::DETAILS.to_owned()
        };
        let response = ui.add_sized(
            [width, 24.0],
            egui::Button::new(RichText::new(details_text).font(font))
                .fill(if view.details {
                    theme::colors(ui).rule
                } else if theme::is_retro(ui) {
                    egui::Color32::from_rgb(21, 23, 35)
                } else {
                    theme::colors(ui).window
                })
                .stroke(egui::Stroke::NONE)
                .corner_radius(6),
        );
        response.widget_info(|| WidgetInfo::labeled(WidgetType::Button, true, label::DETAILS));
        if response.clicked() {
            view.details = !view.details;
        }
    });
    actions
}
