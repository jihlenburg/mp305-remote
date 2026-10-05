//! Implements: DD-APP-034, DD-APP-035 (decorative frame and content bounds).
//!
//! Frames reserve space for working controls and never handle input. The
//! compact header identifies the connected endpoint without changing it.
//! Coverage: excluded as GUI drawing code (ADR-0008); UT-APP-020 inspects
//! this file, UT-APP-031 and UT-APP-035 inspect rendered layouts.

use crate::model::Model;
use crate::texts::label;
use crate::ui::theme;
use eframe::egui::{self, Align2, Color32, CornerRadius, Rect, RichText};

/// The Retro outer bands, independent of quantity and output state.
const BAND: Color32 = Color32::from_rgb(255, 153, 102);

/// A rectangle constructed without operators on GUI coordinate types.
fn area(x: f32, y: f32, width: f32, height: f32) -> Rect {
    Rect::from_min_size(
        egui::pos2(x, y),
        egui::vec2(width.max(0.0), height.max(0.0)),
    )
}

/// Draws the selected frame and returns the space reserved for content.
pub fn content(ui: &mut egui::Ui, model: &Model, compact: bool) -> Rect {
    let bounds = ui.max_rect();
    let x = bounds.left();
    let y = bounds.top();
    let width = bounds.width();
    let height = bounds.height();
    let retro = theme::is_retro(ui);
    if !retro && !compact {
        return bounds;
    }
    let left = if compact {
        if retro {
            36.0
        } else {
            12.0
        }
    } else {
        80.0
    };
    let (top, bottom, right) = if !compact {
        (56.0, 48.0, 24.0)
    } else if retro {
        (48.0, 40.0, 16.0)
    } else {
        (34.0, 12.0, 12.0)
    };
    let content = area(
        x + left,
        y + top,
        width - left - right,
        height - top - bottom,
    );
    if retro {
        let rail = if compact { 16.0 } else { 40.0 };
        let head = if compact { 24.0 } else { 28.0 };
        let colors = theme::colors(ui);
        let painter = ui.painter();
        painter.rect_filled(
            area(x + 8.0, y + 8.0, width - 16.0, height - 16.0),
            CornerRadius {
                nw: 28,
                ne: 12,
                sw: 28,
                se: 12,
            },
            BAND,
        );
        painter.rect_filled(
            area(
                x + 8.0 + rail,
                y + 8.0 + head,
                width - rail - 16.0,
                height - head - if compact { 32.0 } else { bottom },
            ),
            CornerRadius {
                nw: 16,
                ne: 0,
                sw: 16,
                se: 0,
            },
            colors.window,
        );
        let start = y + top + 4.0;
        let available = (height - top - bottom - if compact { 0.0 } else { 16.0 }).max(0.0);
        let segment = available / 3.0;
        for (offset, color) in [
            (0.0, colors.volts),
            (segment, colors.amps),
            (segment * 2.0, colors.watts),
        ] {
            painter.rect_filled(
                area(x + 8.0, start + offset - 4.0, rail + 1.0, segment),
                0,
                colors.window,
            );
            painter.rect_filled(area(x + 8.0, start + offset, rail, segment - 4.0), 0, color);
        }
        if compact {
            painter.text(
                egui::pos2(x + left, bounds.bottom() - 16.0),
                Align2::LEFT_CENTER,
                "MP305 / POWER CONTROL",
                theme::caption(ui, 11.0),
                Color32::BLACK,
            );
        } else {
            painter.text(
                egui::pos2(x + left, y + 10.0),
                Align2::LEFT_TOP,
                "ENGINEERING / AUXILIARY POWER",
                theme::caption(ui, 17.0),
                Color32::BLACK,
            );
            painter.text(
                egui::pos2(bounds.right() - 24.0, y + 10.0),
                Align2::RIGHT_TOP,
                "MP305 / REMOTE",
                theme::caption(ui, 17.0),
                Color32::BLACK,
            );
            painter.text(
                egui::pos2(x + left, bounds.bottom() - 30.0),
                Align2::LEFT_TOP,
                "MP305 REMOTE / POWER CONTROL",
                theme::caption(ui, 15.0),
                Color32::BLACK,
            );
        }
    }
    if compact {
        let title = model.connected.as_ref().map_or_else(
            || label::APP_TITLE.to_owned(),
            |found| model.device_name(found),
        );
        let color = if retro {
            Color32::BLACK
        } else {
            theme::colors(ui).text
        };
        ui.put(
            area(
                x + left,
                y + 8.0,
                width - left - right,
                if retro { 24.0 } else { 22.0 },
            ),
            egui::Label::new(
                RichText::new(title)
                    .font(theme::caption(ui, 14.0))
                    .color(color),
            )
            .truncate(),
        )
        .on_hover_text(model.supply_line());
    }
    content
}
