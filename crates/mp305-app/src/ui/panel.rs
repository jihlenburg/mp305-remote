//! Implements: DD-APP-034, DD-APP-035, DD-APP-031 (the main screen).
//!
//! Coverage: excluded from the measurement as GUI drawing code (ADR-0008;
//! app DD, section 8, decision 9); UT-APP-020 inspects this file instead.
//!
//! The left column of the main screen, the remote front panel: the model
//! and transport with Disconnect, the measured voltage with its setpoint
//! field, the measured current with its limit field, the power with the
//! regulation, the output key, the status lines, and Record and Details
//! at the bottom. The chart fills the right side (`chart`), everything
//! else is in the details panel (`details`).

use eframe::egui::{self, Align, Layout, RichText};

use crate::actions::UiAction;
use crate::fields::{self, FieldKind};
use crate::model::{Instant, Model, RegulationMode};
use crate::texts::{self, label};
use crate::ui::{status, theme, widgets, View};

/// Shared whole and fractional digit columns for volts and amps.
const NUMERAL_PLACES: [usize; 2] = [2, 3];
/// Whole and fractional digit columns for power (`150.00`).
const POWER_PLACES: [usize; 2] = [3, 2];
/// The size of the recording dot in points.
const DOT: f32 = 8.0;

/// Draws the left column of the main screen.
pub fn show(ui: &mut egui::Ui, model: &Model, view: &mut View, now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    let footer_height = if model.recording_stop_enabled() {
        64.0
    } else if theme::is_retro(ui) {
        32.0
    } else {
        28.0
    };
    let footer_frame = theme::footer_frame();
    egui::Panel::bottom("front-footer")
        .exact_size(footer_height + f32::from(footer_frame.inner_margin.top))
        .frame(footer_frame)
        .show(ui, |ui| {
            if model.recording_stop_enabled() {
                ui.add(egui::Label::new(widgets::dim(model.recording_line())).truncate())
                    .on_hover_text(model.recording_line());
            }
            actions.extend(bottom_row(ui, model, view));
        });
    actions.extend(top_line(ui, model));
    ui.add_space(gap(ui));
    if theme::is_retro(ui) {
        actions.extend(crate::ui::compact::readings(ui, model));
    } else {
        actions.extend(readouts(ui, model));
    }
    ui.add_space(gap(ui));
    actions.extend(widgets::output_key(ui, model));
    ui.add_space(gap(ui));
    actions.extend(status::show(ui, model, now));
    actions
}

/// Retro reserves some window space for its frame; reduce internal gaps.
fn gap(ui: &egui::Ui) -> f32 {
    if theme::is_retro(ui) {
        8.0
    } else {
        theme::PAD
    }
}

/// The model name, the transport dim, and Disconnect at the right.
fn top_line(ui: &mut egui::Ui, model: &Model) -> Vec<UiAction> {
    let mut actions = Vec::new();
    let name = model.connected.as_ref().map_or_else(
        || texts::THE_SUPPLY.to_string(),
        |found| model.device_name(found),
    );
    ui.add(
        egui::Label::new(RichText::new(name).font(theme::caption(
            ui,
            if theme::is_retro(ui) { 24.0 } else { 18.0 },
        )))
        .truncate(),
    )
    .on_hover_text(model.supply_line());
    ui.horizontal(|ui| {
        if let Some(kind) = model.transport {
            ui.label(widgets::dim(format!(
                "MP305B / {}",
                texts::transport_name(kind)
            )));
        }
        ui.with_layout(Layout::right_to_left(Align::Center), |ui| {
            actions.extend(widgets::quiet(
                ui,
                model.disconnect_enabled(),
                label::DISCONNECT,
                UiAction::Disconnect,
            ));
        });
    });
    actions
}

/// Volts with the setpoint, amps with the limit, and the power with the
/// regulation.
fn readouts(ui: &mut egui::Ui, model: &Model) -> Vec<UiAction> {
    let mut actions = Vec::new();
    let raw = model.reading.map(|r| r.reading.raw);
    let volts = raw.map_or_else(
        || texts::NO_VOLTS.to_string(),
        |r| fields::display(FieldKind::Voltage, r.voltage),
    );
    let amps = raw.map_or_else(
        || texts::NO_AMPS.to_string(),
        |r| fields::display(FieldKind::Current, r.current),
    );
    let watts = raw.map_or_else(
        || texts::NO_WATTS.to_string(),
        |r| texts::watts_number(r.power),
    );

    quantity_label(ui, model, FieldKind::Voltage, "Voltage");
    widgets::readout(
        ui,
        &volts,
        NUMERAL_PLACES,
        label::VOLTS,
        theme::colors(ui).volts,
        if theme::is_retro(ui) {
            34.0
        } else {
            theme::NUMERAL
        },
    );
    actions.extend(widgets::setpoint(
        ui,
        model,
        FieldKind::Voltage,
        label::SET,
        UiAction::ApplyVoltage,
    ));
    ui.add_space(gap(ui));
    quantity_label(ui, model, FieldKind::Current, "Current");
    widgets::readout(
        ui,
        &amps,
        NUMERAL_PLACES,
        label::AMPS,
        theme::colors(ui).amps,
        if theme::is_retro(ui) {
            34.0
        } else {
            theme::NUMERAL
        },
    );
    actions.extend(widgets::setpoint(
        ui,
        model,
        FieldKind::Current,
        label::SET,
        UiAction::ApplyCurrent,
    ));
    ui.add_space(gap(ui));
    ui.horizontal(|ui| {
        ui.label(widgets::dim("Power"));
        widgets::readout(
            ui,
            &watts,
            POWER_PLACES,
            label::WATTS,
            theme::colors(ui).watts,
            theme::POWER,
        );
        if let Some(reading) = model.reading {
            let regulation = reading.reading.regulation;
            let color = match regulation {
                RegulationMode::Cv => theme::colors(ui).volts,
                RegulationMode::Cc => theme::colors(ui).amps,
                RegulationMode::Off
                | RegulationMode::HeldAboveSetpoint
                | RegulationMode::Unknown(_) => theme::DIM,
            };
            ui.with_layout(Layout::right_to_left(Align::Center), |ui| {
                ui.add(
                    egui::Label::new(
                        RichText::new(if theme::is_retro(ui) {
                            format!(
                                "{} · {regulation}",
                                if reading.reading.output_on {
                                    "ON"
                                } else {
                                    "OFF"
                                }
                            )
                        } else {
                            regulation.to_string()
                        })
                        .font(egui::FontId::new(theme::BODY, theme::bold()))
                        .color(color),
                    )
                    .truncate(),
                );
            });
        }
    });
    actions
}

/// A stable quantity heading; edited status uses the same row.
fn quantity_label(ui: &mut egui::Ui, model: &Model, kind: FieldKind, name: &str) {
    ui.scope(|ui| {
        ui.spacing_mut().interact_size.y = theme::SMALL;
        ui.horizontal(|ui| {
            ui.label(widgets::dim(name).font(theme::caption(
                ui,
                if theme::is_retro(ui) {
                    16.0
                } else {
                    theme::SMALL
                },
            )));
            ui.with_layout(Layout::right_to_left(Align::Center), |ui| {
                if model.field(kind).edited {
                    ui.label(widgets::dim(label::NOT_APPLIED));
                }
            });
        });
    });
}

/// Record (Stop with a dot while recording) at the left, Details at the
/// right.
fn bottom_row(ui: &mut egui::Ui, model: &Model, view: &mut View) -> Vec<UiAction> {
    let mut actions = Vec::new();
    ui.horizontal(|ui| {
        if model.recording_stop_enabled() {
            let (dot, _) = ui.allocate_exact_size(egui::vec2(DOT, DOT), egui::Sense::hover());
            ui.painter()
                .circle_filled(dot.center(), DOT / 2.0, theme::colors(ui).live);
            if widgets::quiet_response(ui, true, label::STOP, theme::BODY)
                .on_hover_text(model.recording_line())
                .clicked()
            {
                actions.push(UiAction::StopRecording);
            }
        } else if widgets::quiet_button(
            ui,
            model.recording_start_enabled(),
            label::RECORD,
            theme::BODY,
        ) {
            actions.push(UiAction::StartRecording);
        }
        ui.with_layout(Layout::right_to_left(Align::Center), |ui| {
            if widgets::quiet_button(ui, true, label::DETAILS, theme::BODY) {
                view.details = !view.details;
            }
        });
    });
    actions
}
