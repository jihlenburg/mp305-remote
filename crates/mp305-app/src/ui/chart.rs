//! Implements: DD-APP-031 (the chart).
//!
//! Coverage: excluded from the measurement as GUI drawing code (ADR-0008;
//! app DD, section 8, decision 9); UT-APP-020 inspects this file instead.
//!
//! Three plots stacked from `chart.series(window_s)`: volts in the volt
//! colour on top, amps in the amp colour below, x from minus `window_s` to
//! 0 s on all three. Faint horizontal grid lines, small dim axis labels, no
//! frame and no legend. Each quantity has its own labelled scale.
//! Under the plots, at the right, the window choices as small text
//! buttons, the active one in the text colour.

use eframe::egui::{self, Align, Layout, RichText};
use egui_plot::{AxisHints, Line, Plot};

use crate::actions::UiAction;
use crate::model::{Instant, Model};
use crate::texts::{self, label};
use crate::ui::{theme, widgets};

/// The width of the value axis in points, equal in all plots so that
/// their time axes line up.
const AXIS_WIDTH: f32 = 64.0;
/// The height of the row of window choices in points.
const CHOICES_HEIGHT: f32 = 28.0;
/// The smallest height of one plot in points.
const MIN_PLOT_HEIGHT: f32 = 60.0;
/// The width of a plotted line in points.
const LINE_WIDTH: f32 = 1.5;

/// Draws the chart and its window choices into the space `ui` offers.
pub fn show(ui: &mut egui::Ui, model: &Model, _now: Instant) -> Vec<UiAction> {
    let series = model.chart.series(model.window_s);
    let window = f64::from(model.window_s);
    let gap = theme::PAD;
    let mut actions = Vec::new();
    egui::Panel::bottom("chart-window")
        .exact_size(CHOICES_HEIGHT)
        .frame(egui::Frame::NONE)
        .show(ui, |ui| {
            actions.extend(window_choices(ui, model));
        });
    ui.horizontal(|ui| {
        ui.heading(if matches!(model.phase, crate::model::Phase::Lost { .. }) {
            "Last readings"
        } else {
            "Live readings"
        });
        ui.with_layout(Layout::right_to_left(Align::Center), |ui| {
            ui.label(widgets::dim("Time before latest reading"));
        });
    });
    let plots = ui.available_height() - 2.0 * gap - 3.0 * ui.spacing().item_spacing.y;
    let height = (plots / 3.0).max(MIN_PLOT_HEIGHT);
    let group = egui::Id::new("mp305-chart");
    for (name, unit, color, points, floor, last) in [
        (
            "Voltage",
            label::VOLTS,
            theme::VOLTS,
            series.volts,
            1.0_f64,
            false,
        ),
        (
            "Current",
            label::AMPS,
            theme::AMPS,
            series.amps,
            0.1_f64,
            false,
        ),
        (
            "Power",
            label::WATTS,
            theme::WATTS,
            series.watts,
            1.0_f64,
            true,
        ),
    ] {
        let upper = points
            .iter()
            .map(|point| point.get(1).copied().unwrap_or(0.0))
            .fold(floor, f64::max)
            * 1.1;
        let value_axis = AxisHints::new_y()
            .formatter(move |mark, _| {
                format!("{} {unit}", texts::axis_value(mark.value, mark.step_size))
            })
            .tick_label_color(theme::DIM)
            .tick_label_font(theme::mono(theme::SMALL))
            .min_thickness(AXIS_WIDTH);
        let time_axis = AxisHints::new_x()
            .formatter(move |mark, _| {
                // The corner tick would overlap the zero label of the value axis.
                if mark.value <= -window {
                    String::new()
                } else {
                    texts::axis_seconds(mark.value)
                }
            })
            .tick_label_color(theme::DIM)
            .tick_label_font(theme::mono(theme::SMALL));
        Plot::new(name)
            .height(height)
            .link_axis(group, [true, false])
            .allow_drag(false)
            .allow_zoom(false)
            .allow_scroll(false)
            .allow_boxed_zoom(false)
            .allow_double_click_reset(false)
            .show_x(false)
            .show_y(false)
            .show_background(false)
            .show_grid([false, true])
            .grid_color(theme::RULE)
            .grid_spacing(24.0..=80.0)
            .grid_fade(0.4)
            .show_axes([last, true])
            .custom_y_axes(vec![value_axis])
            .custom_x_axes(vec![time_axis])
            .include_y(0.0)
            .show(ui, |plot| {
                plot.set_plot_bounds_x(-window..=0.0);
                plot.set_plot_bounds_y(0.0..=upper);
                plot.line(Line::new(name, points).color(color).width(LINE_WIDTH));
            });
        if !last {
            ui.add_space(gap);
        }
    }
    actions
}

/// The window choices, right-aligned, in reading order.
fn window_choices(ui: &mut egui::Ui, model: &Model) -> Vec<UiAction> {
    let mut actions = Vec::new();
    ui.allocate_ui_with_layout(
        egui::vec2(ui.available_width(), CHOICES_HEIGHT),
        Layout::right_to_left(Align::Center),
        |ui| {
            ui.spacing_mut().item_spacing.x = 4.0;
            for (seconds, text) in texts::WINDOW_CHOICES.iter().rev() {
                let clicked = ui
                    .add(
                        egui::Button::new(RichText::new(*text).size(theme::SMALL))
                            .frame(true)
                            .selected(model.window_s == *seconds),
                    )
                    .clicked();
                if clicked {
                    actions.push(UiAction::SetWindow(*seconds));
                }
            }
        },
    );
    actions
}
