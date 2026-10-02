//! Implements: DD-APP-031 (the chart).
//!
//! Coverage: excluded from the measurement as GUI drawing code (ADR-0008;
//! app DD, section 8, decision 9); UT-APP-020 inspects this file instead.
//!
//! Three plots for V, A and W from `chart.series(window_s)`, linked on the
//! x axis, x from minus `window_s` to 0 s, and the window choices.

use eframe::egui;
use egui_plot::{Line, Plot};

use crate::actions::UiAction;
use crate::model::{Instant, Model};
use crate::texts::{self, label};

/// The height of one plot in points.
const PLOT_HEIGHT: f32 = 140.0;

/// Draws the chart and its window choices.
pub fn show(ui: &mut egui::Ui, model: &Model, _now: Instant) -> Vec<UiAction> {
    let mut actions = Vec::new();
    ui.strong(label::CHART);
    ui.horizontal(|ui| {
        ui.label(label::WINDOW);
        for (seconds, text) in texts::WINDOW_CHOICES {
            if ui
                .selectable_label(model.window_s == seconds, text)
                .clicked()
            {
                actions.push(UiAction::SetWindow(seconds));
            }
        }
    });
    let series = model.chart.series(model.window_s);
    let window = f64::from(model.window_s);
    let group = egui::Id::new("mp305-chart");
    for (name, points) in [("V", series.volts), ("A", series.amps), ("W", series.watts)] {
        Plot::new(name)
            .height(PLOT_HEIGHT)
            .link_axis(group, [true, false])
            .allow_drag(false)
            .allow_zoom(false)
            .allow_scroll(false)
            .allow_boxed_zoom(false)
            .y_axis_label(name)
            .show(ui, |plot| {
                plot.set_plot_bounds_x(-window..=0.0);
                plot.line(Line::new(name, points));
            });
    }
    actions
}
