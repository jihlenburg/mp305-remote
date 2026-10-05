//! Implements: DD-APP-031 (the widgets the screens share).
//!
//! Coverage: excluded from the measurement as GUI drawing code (ADR-0008;
//! app DD, section 8, decision 9); UT-APP-020 inspects this file instead.
//!
//! The quiet text buttons, the big readouts, the value fields and the
//! output key. Every widget reads the model and reports clicks as actions;
//! none decides what a click may do.

use eframe::egui::{self, Align, CursorIcon, Layout, RichText, Stroke, WidgetInfo, WidgetType};

use crate::actions::UiAction;
use crate::fields::FieldKind;
use crate::model::Model;
use crate::texts::label;
use crate::ui::theme;

/// The width of a setpoint field in points.
const SETPOINT_WIDTH: f32 = 80.0;
/// The width of the label in front of a setpoint field in points.
const SETPOINT_LABEL_WIDTH: f32 = 36.0;
/// The width of a field in the details panel in points.
const FORM_FIELD_WIDTH: f32 = 96.0;
/// The height of the output key in points.
const OUTPUT_KEY_HEIGHT: f32 = 44.0;
/// The text size of the output key in points.
const OUTPUT_KEY_TEXT: f32 = 14.0;

/// A frameless text button of `size` points: dim, bright under the
/// pointer, faded while not `enabled`.
pub fn quiet_response(ui: &mut egui::Ui, enabled: bool, text: &str, size: f32) -> egui::Response {
    ui.scope(|ui| {
        let widgets = &mut ui.visuals_mut().widgets;
        widgets.inactive.fg_stroke.color = theme::DIM;
        widgets.hovered.fg_stroke.color = theme::TEXT;
        widgets.active.fg_stroke.color = theme::TEXT;
        let button = egui::Button::new(RichText::new(text).size(size)).frame(false);
        let response = ui.add_enabled(enabled, button);
        focus_outline(ui, &response);
        if enabled {
            response.on_hover_cursor(CursorIcon::PointingHand)
        } else {
            response
        }
    })
    .inner
}

/// A [`quiet_response`] button; returns whether it was clicked.
pub fn quiet_button(ui: &mut egui::Ui, enabled: bool, text: &str, size: f32) -> bool {
    quiet_response(ui, enabled, text, size).clicked()
}

/// A quiet button at body size that reports `action` when clicked.
pub fn quiet(ui: &mut egui::Ui, enabled: bool, text: &str, action: UiAction) -> Vec<UiAction> {
    if quiet_button(ui, enabled, text, theme::BODY) {
        vec![action]
    } else {
        Vec::new()
    }
}

/// A button with a thin outline and no fill, for the answers of a
/// dialog and the buttons of the details panel; reports `action`.
pub fn outlined(ui: &mut egui::Ui, enabled: bool, text: &str, action: UiAction) -> Vec<UiAction> {
    let button = egui::Button::new(RichText::new(text).color(theme::TEXT))
        .fill(egui::Color32::TRANSPARENT)
        .stroke(Stroke::new(1.0, theme::RULE))
        .min_size(egui::vec2(0.0, 28.0));
    let response = ui.add_enabled(enabled, button);
    focus_outline(ui, &response);
    if response.clicked() {
        vec![action]
    } else {
        Vec::new()
    }
}

/// A visible keyboard focus indicator for buttons with custom fills.
fn focus_outline(ui: &egui::Ui, response: &egui::Response) {
    if response.has_focus() {
        ui.painter().rect_stroke(
            response.rect,
            theme::RADIUS,
            Stroke::new(1.0, theme::TEXT),
            egui::StrokeKind::Inside,
        );
    }
}

/// Small dim text.
#[must_use]
pub fn dim(text: impl Into<String>) -> RichText {
    RichText::new(text).size(theme::SMALL).color(theme::DIM)
}

/// A readout with fixed whole and fractional digit columns in `places`.
/// Digits use the bold fixed-width cut; the decimal uses the proportional
/// cut's narrower punctuation. Padding reserves space without adding false
/// precision. The decimal and unit stay fixed when values or precision differ.
pub fn readout(
    ui: &mut egui::Ui,
    value: &str,
    places: [usize; 2],
    unit: &str,
    color: egui::Color32,
    size: f32,
) {
    let painter = ui.painter();
    let [whole_places, fraction_places] = places;
    let (whole, fraction) = value.split_once('.').unwrap_or((value, ""));
    let digit_font = egui::FontId::new(size, theme::mono_bold());
    let whole =
        painter.layout_no_wrap(format!("{whole:>whole_places$}"), digit_font.clone(), color);
    let decimal = painter.layout_no_wrap(".".into(), egui::FontId::new(size, theme::bold()), color);
    let fraction =
        painter.layout_no_wrap(format!("{fraction:<fraction_places$}"), digit_font, color);
    let suffix = painter.layout_no_wrap(unit.into(), theme::text(theme::BODY), theme::DIM);
    let common_baseline = baseline(&whole);
    let parts = [
        (whole, color),
        (decimal, color),
        (fraction, color),
        (suffix, theme::DIM),
    ];
    let width = parts.iter().map(|(part, _)| part.size().x).sum::<f32>() + 8.0;
    let height = parts
        .iter()
        .map(|(part, _)| common_baseline - baseline(part) + part.size().y)
        .fold(0.0_f32, f32::max);
    let (rect, response) = ui.allocate_exact_size(egui::vec2(width, height), egui::Sense::hover());
    response.widget_info(|| {
        WidgetInfo::labeled(WidgetType::Label, true, format!("{} {unit}", value.trim()))
    });
    let mut x = rect.left();
    for (index, (part, color)) in parts.into_iter().enumerate() {
        if index == 3 {
            x += 8.0;
        }
        let position = egui::pos2(x, rect.top() + common_baseline - baseline(&part));
        x += part.size().x;
        ui.painter().galley(position, part, color);
    }
}

/// Font metrics place both text runs on the same baseline, independent of size.
fn baseline(galley: &egui::Galley) -> f32 {
    galley.rows.first().map_or(0.0, |row| {
        row.pos.y + row.glyphs.first().map_or(0.0, |glyph| glyph.pos.y)
    })
}

/// The text edit of the field of `kind`: fixed-width type, the range hint
/// on hover (not as a placeholder, which would wrap and grow the field);
/// typing reports `EditField` and Enter reports `apply`.
fn value_edit(
    ui: &mut egui::Ui,
    model: &Model,
    kind: FieldKind,
    width: f32,
    apply: UiAction,
) -> Vec<UiAction> {
    let mut actions = Vec::new();
    let mut text = model.field(kind).text.clone();
    let response = ui
        .add(
            egui::TextEdit::singleline(&mut text)
                .id_salt(("field", format!("{kind:?}")))
                .font(egui::TextStyle::Monospace)
                .desired_width(width)
                .margin(egui::vec2(6.0, 3.0)),
        )
        .on_hover_text(model.hint(kind));
    let name = match kind {
        FieldKind::Voltage => label::VOLTAGE,
        FieldKind::Current => label::CURRENT,
        FieldKind::MaxVoltage => label::MAX_VOLTAGE,
        FieldKind::MaxCurrent => label::MAX_CURRENT,
    };
    response.widget_info(|| WidgetInfo {
        label: Some(name.into()),
        ..WidgetInfo::text_edit(
            ui.is_enabled(),
            &model.field(kind).text,
            &text,
            model.hint(kind),
        )
    });
    if response.changed() {
        actions.push(UiAction::EditField(kind, text));
    }
    if response.lost_focus() && ui.input(|i| i.key_pressed(egui::Key::Enter)) {
        actions.push(apply);
    }
    actions
}

/// The setpoint row under a readout: `name` dim, the field, and a small
/// `Set` button enabled only while the field holds a value the supply does
/// not have (the field is edited). Its reserved space keeps the fields aligned. An invalid value's text goes to the
/// status lines.
pub fn setpoint(
    ui: &mut egui::Ui,
    model: &Model,
    kind: FieldKind,
    name: &str,
    apply: UiAction,
) -> Vec<UiAction> {
    let mut actions = Vec::new();
    ui.horizontal(|ui| {
        ui.add_sized([SETPOINT_LABEL_WIDTH, 28.0], egui::Label::new(dim(name)));
        actions.extend(value_edit(ui, model, kind, SETPOINT_WIDTH, apply.clone()));
        let enabled = model.apply_enabled(kind) && model.field(kind).edited;
        let response = ui.add_enabled(
            enabled,
            egui::Button::new(label::SET_BUTTON)
                .frame(true)
                .min_size(egui::vec2(44.0, 28.0)),
        );
        let name = match kind {
            FieldKind::Voltage => "Set voltage",
            _ => "Set current",
        };
        response.widget_info(|| WidgetInfo::labeled(WidgetType::Button, enabled, name));
        if response.clicked() {
            actions.push(apply);
        }
    });
    actions
}

/// A field of the details panel: `name`, the field, and the range hint
/// dim under it; the error, if any, in the live colour.
pub fn form_field(
    ui: &mut egui::Ui,
    model: &Model,
    kind: FieldKind,
    name: &str,
    apply: UiAction,
) -> Vec<UiAction> {
    let mut actions = Vec::new();
    ui.horizontal(|ui| {
        ui.label(name);
        ui.with_layout(Layout::right_to_left(Align::Center), |ui| {
            actions.extend(value_edit(ui, model, kind, FORM_FIELD_WIDTH, apply));
        });
    });
    ui.label(dim(model.hint(kind)));
    if let Some(error) = model.field_error(kind) {
        ui.label(RichText::new(error).size(theme::SMALL).color(theme::LIVE));
    }
    actions
}

/// The output key across the column: `Off` and `On` side by side, each
/// sending its own action (never a toggle), enabled as the model says.
/// The half that matches the reading is lit, `On` in the live colour and
/// `Off` neutral; without a reading neither is.
pub fn output_key(ui: &mut egui::Ui, model: &Model) -> Vec<UiAction> {
    let mut actions = Vec::new();
    let lit = model.reading.map(|r| r.reading.output_on);
    let width = (ui.available_width() - ui.spacing().item_spacing.x) / 2.0;
    ui.horizontal(|ui| {
        for (text, enabled, active, fill, action) in [
            (
                label::OUTPUT_OFF,
                model.output_off_enabled(),
                lit == Some(false),
                theme::RULE,
                UiAction::OutputOff,
            ),
            (
                label::OUTPUT_ON,
                model.output_on_enabled(),
                lit == Some(true),
                theme::OUTPUT_ACTIVE,
                UiAction::OutputOn,
            ),
        ] {
            let button = egui::Button::new(
                RichText::new(text).font(egui::FontId::new(OUTPUT_KEY_TEXT, theme::bold())),
            )
            .fill(if active { fill } else { theme::WINDOW })
            .stroke(Stroke::new(
                1.0,
                if active { theme::DIM } else { theme::RULE },
            ));
            let response = ui
                .add_enabled_ui(enabled, |ui| {
                    ui.add_sized([width, OUTPUT_KEY_HEIGHT], button)
                })
                .inner;
            focus_outline(ui, &response);
            if response.clicked() {
                actions.push(action);
            }
        }
    });
    actions
}

/// Rows of a dim label and a value in a grid.
pub fn rows(ui: &mut egui::Ui, id: &str, rows: &[(&'static str, String)]) {
    let value_width = (ui.available_width() - 100.0).max(80.0);
    egui::Grid::new(id)
        .num_columns(2)
        .max_col_width(value_width)
        .spacing(egui::vec2(16.0, theme::UNIT))
        .show(ui, |ui| {
            for (name, value) in rows {
                ui.label(dim(*name));
                ui.add(egui::Label::new(value).wrap());
                ui.end_row();
            }
        });
}
