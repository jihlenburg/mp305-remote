use eframe::egui::{
    self, Align2, Color32, CornerRadius, FontData, FontFamily, FontId, Pos2, Rect, RichText,
    Stroke, Vec2,
};
use egui_kittest::{kittest::Queryable, Harness};
use std::{path::PathBuf, sync::Arc};

const BLACK: Color32 = Color32::BLACK;
const PEACH: Color32 = Color32::from_rgb(255, 204, 153);
const ORANGE: Color32 = Color32::from_rgb(255, 153, 102);
const LILAC: Color32 = Color32::from_rgb(204, 170, 221);
const BLUE: Color32 = Color32::from_rgb(153, 170, 238);
const CORAL: Color32 = Color32::from_rgb(238, 153, 136);
const WHITE: Color32 = Color32::from_rgb(244, 232, 224);
const DIM: Color32 = Color32::from_rgb(162, 158, 181);
const GRID: Color32 = Color32::from_rgb(39, 35, 46);

fn rect(x: f32, y: f32, w: f32, h: f32) -> Rect {
    Rect::from_min_size(Pos2::new(x, y), Vec2::new(w, h))
}
fn label_font(size: f32) -> FontId {
    FontId::new(size, FontFamily::Name("Antonio".into()))
}
fn number_font(size: f32) -> FontId {
    FontId::new(size, FontFamily::Monospace)
}
fn dot_font(size: f32) -> FontId {
    FontId::new(size, FontFamily::Name("B612 Bold".into()))
}

fn install(ctx: &egui::Context) {
    let mut fonts = egui::FontDefinitions::default();
    for (name, bytes) in [
        ("Antonio", &include_bytes!("../assets/Antonio.ttf")[..]),
        (
            "B612 Mono",
            &include_bytes!("../../../crates/mp305-app/assets/fonts/B612Mono-Bold.ttf")[..],
        ),
        (
            "B612 Bold",
            &include_bytes!("../../../crates/mp305-app/assets/fonts/B612-Bold.ttf")[..],
        ),
    ] {
        fonts
            .font_data
            .insert(name.into(), Arc::new(FontData::from_static(bytes)));
        fonts
            .families
            .insert(FontFamily::Name(name.into()), vec![name.into()]);
    }
    fonts
        .families
        .insert(FontFamily::Monospace, vec!["B612 Mono".into()]);
    ctx.set_fonts(fonts);
    ctx.set_theme(egui::ThemePreference::Dark);
    let mut style = (*ctx.style_of(egui::Theme::Dark)).clone();
    style
        .text_styles
        .insert(egui::TextStyle::Body, label_font(18.0));
    style
        .text_styles
        .insert(egui::TextStyle::Button, label_font(18.0));
    style
        .text_styles
        .insert(egui::TextStyle::Heading, label_font(26.0));
    style.spacing.window_margin = egui::Margin::same(16);
    style.visuals.panel_fill = BLACK;
    style.visuals.window_fill = BLACK;
    style.visuals.widgets.noninteractive.bg_fill = BLACK;
    style.visuals.window_stroke = Stroke::new(2.0, LILAC);
    style.visuals.window_corner_radius = CornerRadius::same(16);
    style.visuals.override_text_color = Some(WHITE);
    style.visuals.extreme_bg_color = BLACK;
    style.visuals.text_edit_bg_color = Some(BLACK);
    style.visuals.selection.bg_fill = Color32::from_rgb(80, 55, 70);
    style.visuals.widgets.inactive.bg_stroke = Stroke::new(1.0, DIM);
    style.visuals.widgets.active.bg_stroke = Stroke::new(2.0, PEACH);
    style.visuals.widgets.hovered.bg_stroke = Stroke::new(2.0, PEACH);
    ctx.set_style_of(egui::Theme::Dark, style.clone());
    ctx.set_style_of(egui::Theme::Light, style);
}

struct Preview {
    voltage: f64,
    current: f64,
    voltage_text: String,
    current_text: String,
    output: bool,
    recording: bool,
    details: bool,
    window: u32,
    error: String,
}
impl Default for Preview {
    fn default() -> Self {
        Self {
            voltage: 12.0,
            current: 0.2,
            voltage_text: "12.00".into(),
            current_text: "0.200".into(),
            output: true,
            recording: false,
            details: false,
            window: 60,
            error: String::new(),
        }
    }
}

fn text(ui: &egui::Ui, x: f32, y: f32, size: f32, color: Color32, value: &str) {
    ui.painter().text(
        Pos2::new(x, y),
        Align2::LEFT_TOP,
        value,
        label_font(size),
        color,
    );
}

fn button(ui: &mut egui::Ui, bounds: Rect, value: &str, color: Color32, selected: bool) -> bool {
    ui.put(
        bounds,
        egui::Button::new(RichText::new(value).font(label_font(18.0)).color(BLACK))
            .fill(color)
            .stroke(Stroke::new(if selected { 2.0 } else { 0.0 }, WHITE))
            .corner_radius(CornerRadius::same(20))
            .min_size(bounds.size()),
    )
    .clicked()
}

fn band(ui: &egui::Ui, bounds: Rect, color: Color32, value: &str) {
    ui.painter().rect_filled(bounds, 0, color);
    ui.painter().text(
        Pos2::new(bounds.right() - 9.0, bounds.bottom() - 8.0),
        Align2::RIGHT_BOTTOM,
        value,
        label_font(18.0),
        BLACK,
    );
}

fn frame(ui: &egui::Ui, width: f32, height: f32) {
    let painter = ui.painter();
    painter.rect_filled(
        rect(16.0, 16.0, width - 32.0, 98.0),
        CornerRadius {
            nw: 48,
            ne: 14,
            sw: 0,
            se: 0,
        },
        ORANGE,
    );
    painter.rect_filled(
        rect(88.0, 44.0, width - 103.0, 72.0),
        CornerRadius {
            nw: 24,
            ne: 0,
            sw: 0,
            se: 0,
        },
        BLACK,
    );
    // A gap separates the long header band from its rounded terminal.
    painter.rect_filled(rect(width - 120.0, 16.0, 5.0, 28.0), 0, BLACK);
    painter.text(
        Pos2::new(width - 28.0, 17.0),
        Align2::RIGHT_TOP,
        "MP305 / Retro",
        label_font(15.0),
        BLACK,
    );
    text(
        ui,
        121.0,
        17.0,
        17.0,
        BLACK,
        "ENGINEERING  /  AUXILIARY POWER",
    );
    let segment = (height - 226.0) / 3.0;
    band(ui, rect(16.0, 119.0, 72.0, segment - 5.0), LILAC, "01 / DC");
    band(
        ui,
        rect(16.0, 119.0 + segment, 72.0, segment - 5.0),
        BLUE,
        "02 / USB",
    );
    band(
        ui,
        rect(16.0, 119.0 + 2.0 * segment, 72.0, segment - 5.0),
        PEACH,
        "03 / LOG",
    );
    painter.rect_filled(
        rect(16.0, height - 100.0, width - 32.0, 84.0),
        CornerRadius {
            nw: 0,
            ne: 0,
            sw: 44,
            se: 14,
        },
        ORANGE,
    );
    painter.rect_filled(
        rect(88.0, height - 102.0, width - 103.0, 58.0),
        CornerRadius {
            nw: 0,
            ne: 0,
            sw: 24,
            se: 0,
        },
        BLACK,
    );
    painter.rect_filled(rect(width - 120.0, height - 43.0, 5.0, 27.0), 0, BLACK);
    text(
        ui,
        121.0,
        height - 42.0,
        16.0,
        BLACK,
        "SIMULATED DEVICE  /  NO HARDWARE CONNECTION",
    );
    painter.text(
        Pos2::new(width - 28.0, height - 41.0),
        Align2::RIGHT_TOP,
        "LOCAL PREVIEW",
        label_font(14.0),
        BLACK,
    );
}

fn readout(ui: &egui::Ui, x: f32, y: f32, value: &str, unit: &str, color: Color32, size: f32) {
    let (whole, fraction) = value.split_once('.').unwrap_or((value, ""));
    let painter = ui.painter();
    let whole = painter.layout_no_wrap(whole.into(), number_font(size), color);
    let decimal = painter.layout_no_wrap(".".into(), dot_font(size), color);
    let fraction = painter.layout_no_wrap(fraction.into(), number_font(size), color);
    let decimal_x = x + 55.0;
    painter.galley(Pos2::new(decimal_x - whole.size().x, y), whole, color);
    let fraction_x = decimal_x + decimal.size().x;
    painter.galley(Pos2::new(decimal_x, y), decimal, color);
    painter.galley(Pos2::new(fraction_x, y), fraction, color);
    let fraction_width = painter
        .layout_no_wrap("000".into(), number_font(size), color)
        .size()
        .x;
    text(
        ui,
        fraction_x + fraction_width + 8.0,
        y + size - 20.0,
        18.0,
        color,
        unit,
    );
}

fn field(ui: &mut egui::Ui, x: f32, y: f32, name: &str, value: &mut String) -> bool {
    text(ui, x, y + 2.0, 17.0, DIM, "SET");
    let response = ui.put(
        rect(x + 36.0, y, 93.0, 29.0),
        egui::TextEdit::singleline(value)
            .id_salt(name)
            .font(number_font(15.0))
            .margin(Vec2::new(9.0, 5.0))
            .desired_width(93.0),
    );
    response.widget_info(|| egui::WidgetInfo {
        label: Some(name.into()),
        ..egui::WidgetInfo::text_edit(true, value.as_str(), value.as_str(), "")
    });
    let enter = response.lost_focus() && ui.input(|i| i.key_pressed(egui::Key::Enter));
    let clicked = button(ui, rect(x + 137.0, y, 59.0, 29.0), "SET", BLUE, false);
    enter || clicked
}

fn mini_field(ui: &mut egui::Ui, x: f32, reading_y: f32, name: &str, value: &mut String) -> bool {
    // Align controls to the visible numeral row, not the font's line box.
    // A fixed digit sample keeps this centre stable as the reading changes.
    let digits = ui
        .painter()
        .layout_no_wrap("0123456789".into(), number_font(34.0), WHITE);
    let row_center = reading_y + digits.mesh_bounds.center().y;
    let y = row_center - 14.0;
    let mut layouter = |ui: &egui::Ui, buffer: &dyn egui::TextBuffer, _: f32| {
        let value = buffer.as_str();
        let (whole, fraction) = value.split_once('.').unwrap_or((value, ""));
        let digit_width = ui
            .painter()
            .layout_no_wrap("0".into(), number_font(16.0), WHITE)
            .size()
            .x;
        let padding = 2_usize.saturating_sub(whole.chars().count()) as f32 * digit_width;
        let format = egui::TextFormat {
            font_id: number_font(16.0),
            color: WHITE,
            ..Default::default()
        };
        let mut job = egui::text::LayoutJob::default();
        job.append(whole, padding, format.clone());
        if value.contains('.') {
            job.append(
                ".",
                0.0,
                egui::TextFormat {
                    font_id: dot_font(16.0),
                    ..format.clone()
                },
            );
            job.append(fraction, 0.0, format);
        }
        ui.fonts_mut(|fonts| fonts.layout_job(job))
    };
    let response = ui.put(
        rect(x, y, 76.0, 28.0),
        egui::TextEdit::singleline(value)
            .id_salt(name)
            .font(number_font(16.0))
            .layouter(&mut layouter)
            .vertical_align(egui::Align::Center)
            .margin(Vec2::new(6.0, 2.0)),
    );
    response.widget_info(|| egui::WidgetInfo {
        label: Some(name.into()),
        ..egui::WidgetInfo::text_edit(true, value.as_str(), value.as_str(), "")
    });
    let enter = response.lost_focus() && ui.input(|i| i.key_pressed(egui::Key::Enter));
    button(ui, rect(x + 82.0, y, 38.0, 28.0), "SET", BLUE, false) || enter
}

fn mini_frame(ui: &egui::Ui, width: f32, height: f32) {
    let painter = ui.painter();
    painter.rect_filled(rect(8.0, 8.0, width - 16.0, height - 16.0), 16, ORANGE);
    painter.rect_filled(rect(20.0, 30.0, width - 28.0, height - 42.0), 8, BLACK);
    for (y, h, color) in [
        (39.0, 52.0, PEACH),
        (95.0, 52.0, LILAC),
        (151.0, height - 187.0, BLUE),
    ] {
        painter.rect_filled(rect(8.0, y - 4.0, 13.0, h + 8.0), 0, BLACK);
        painter.rect_filled(rect(8.0, y, 12.0, h), 0, color);
    }
    text(ui, 32.0, 8.0, 14.0, BLACK, "MP305B / LAMP BENCH");
    painter.text(
        Pos2::new(width - 18.0, 9.0),
        Align2::RIGHT_TOP,
        "SIMULATION",
        label_font(13.0),
        BLACK,
    );
}

fn secondary_button(
    ui: &mut egui::Ui,
    bounds: Rect,
    value: &str,
    color: Color32,
    selected: bool,
) -> bool {
    ui.put(
        bounds,
        egui::Button::new(
            RichText::new(value)
                .font(label_font(15.0))
                .color(if selected { BLACK } else { color }),
        )
        .fill(if selected { color } else { BLACK })
        .stroke(Stroke::new(1.0, color))
        .corner_radius(12)
        .min_size(bounds.size()),
    )
    .clicked()
}

fn plot(
    ui: &egui::Ui,
    bounds: Rect,
    label: &str,
    unit: &str,
    color: Color32,
    maximum: f64,
    value: f64,
    output: bool,
    seconds: u32,
    last: bool,
) {
    let painter = ui.painter();
    painter.rect_filled(
        rect(bounds.left(), bounds.top(), 5.0, bounds.height() - 10.0),
        2,
        color,
    );
    text(
        ui,
        bounds.left() + 12.0,
        bounds.top() - 2.0,
        17.0,
        color,
        label,
    );
    let chart = Rect::from_min_max(
        Pos2::new(bounds.left() + 49.0, bounds.top() + 31.0),
        Pos2::new(bounds.right(), bounds.bottom() - 16.0),
    );
    for fraction in [0.0, 0.5, 1.0] {
        let y = chart.bottom() - chart.height() * fraction;
        painter.line_segment(
            [Pos2::new(chart.left(), y), Pos2::new(chart.right(), y)],
            Stroke::new(0.7, GRID),
        );
    }
    text(
        ui,
        bounds.left() + 12.0,
        chart.top() - 8.0,
        13.0,
        DIM,
        format!("{maximum:.2}")
            .trim_end_matches('0')
            .trim_end_matches('.'),
    );
    text(
        ui,
        bounds.left() + 12.0,
        chart.bottom() - 12.0,
        13.0,
        DIM,
        "0",
    );
    let points = (0..=180)
        .map(|n| {
            let t = n as f32 / 180.0;
            let live = t > 0.2 && (output || t < 0.82);
            let noise = if label == "CURRENT" && live {
                ((n % 4) as f64 - 1.5) * 0.0008
            } else {
                0.0
            };
            let reading = if live { value + noise } else { 0.0 };
            Pos2::new(
                chart.left() + t * chart.width(),
                chart.bottom() - ((reading / maximum) as f32).clamp(0.0, 1.0) * chart.height(),
            )
        })
        .collect::<Vec<_>>();
    painter.add(egui::Shape::line(points, Stroke::new(1.5, color)));
    let display = if output { value } else { 0.0 };
    painter.text(
        Pos2::new(bounds.right(), bounds.top()),
        Align2::RIGHT_TOP,
        if unit == "A" {
            format!("{display:.3} {unit}")
        } else {
            format!("{display:.2} {unit}")
        },
        number_font(12.0),
        color,
    );
    if last {
        for n in 1..=4 {
            let x = chart.left() + chart.width() * n as f32 / 5.0;
            painter.text(
                Pos2::new(x, chart.bottom() + 5.0),
                Align2::CENTER_TOP,
                format!("-{}s", seconds * (5 - n) / 5),
                label_font(12.0),
                DIM,
            );
        }
    }
}

impl Preview {
    fn mini(&mut self, ui: &mut egui::Ui, width: f32, height: f32) {
        mini_frame(ui, width, height);
        let left = 32.0;
        // Keep the essential panel compact when only one dimension is small.
        let right = (width - 12.0).min(480.0);
        let controls_y = height - 82.0;
        if self.details {
            ui.scope_builder(
                egui::UiBuilder::new().max_rect(rect(left, 36.0, right - left, controls_y - 44.0)),
                |ui| {
                    egui::ScrollArea::vertical()
                        .max_height(controls_y - 44.0)
                        .id_salt("mini-details")
                        .show(ui, |ui| {
                            ui.heading(RichText::new("DEVICE STATUS").color(PEACH));
                            ui.label("MP305B / SIMULATED LAMP");
                            ui.label("No hardware connection");
                            ui.label("Output and recording affect this preview only.");
                            ui.label("Enlarge the window to restore all three graphs.");
                            ui.label("Setpoint range: 0 to 30 V / 0 to 5 A");
                        });
                },
            );
        } else {
            let current = (self.voltage / 126.3).min(self.current);
            let volts = (current * 126.3).min(self.voltage);
            let live = if self.output { 1.0 } else { 0.0 };
            let edit_x = right - 120.0;
            let voltage_edited = self.voltage_text != format!("{:.2}", self.voltage);
            let current_edited = self.current_text != format!("{:.3}", self.current);
            text(ui, left, 35.0, 13.0, PEACH, "VOLTAGE");
            text(
                ui,
                edit_x,
                35.0,
                13.0,
                if voltage_edited { PEACH } else { DIM },
                if voltage_edited {
                    "V / NOT APPLIED"
                } else {
                    "SET VOLTAGE"
                },
            );
            readout(
                ui,
                left,
                50.0,
                &format!("{:.2}", volts * live),
                "V",
                PEACH,
                34.0,
            );
            if mini_field(ui, edit_x, 50.0, "Voltage (V)", &mut self.voltage_text) {
                self.apply_voltage();
            }
            text(ui, left, 92.0, 13.0, LILAC, "CURRENT");
            text(
                ui,
                edit_x,
                92.0,
                13.0,
                if current_edited { PEACH } else { DIM },
                if current_edited {
                    "A / NOT APPLIED"
                } else {
                    "CURRENT LIMIT"
                },
            );
            readout(
                ui,
                left,
                107.0,
                &format!("{:.3}", current * live),
                "A",
                LILAC,
                34.0,
            );
            if mini_field(
                ui,
                edit_x,
                107.0,
                "Current limit (A)",
                &mut self.current_text,
            ) {
                self.apply_current();
            }
            ui.painter().line_segment(
                [Pos2::new(left, 148.0), Pos2::new(right, 148.0)],
                Stroke::new(1.0, GRID),
            );
            text(ui, left, 154.0, 13.0, BLUE, "POWER");
            ui.painter().text(
                Pos2::new(left + 45.0, 150.0),
                Align2::LEFT_TOP,
                format!("{:.2} W", volts * current * live),
                number_font(18.0),
                BLUE,
            );
            let mode = if !self.output {
                "OFF"
            } else if current + 0.00001 < self.voltage / 126.3 {
                "ON / CC"
            } else {
                "ON / CV"
            };
            ui.painter().text(
                Pos2::new(right, 154.0),
                Align2::RIGHT_TOP,
                mode,
                label_font(13.0),
                PEACH,
            );
            if !self.error.is_empty() {
                text(ui, left, 174.0, 12.0, CORAL, &self.error);
            }
        }
        let half = (right - left - 8.0) / 2.0;
        if button(
            ui,
            rect(left, controls_y, half, 36.0),
            "OUTPUT OFF",
            CORAL,
            !self.output,
        ) {
            self.output = false;
        }
        if button(
            ui,
            rect(left + half + 8.0, controls_y, half, 36.0),
            "OUTPUT ON",
            PEACH,
            self.output,
        ) {
            self.output = true;
        }
        if secondary_button(
            ui,
            rect(left, height - 38.0, half, 24.0),
            if self.recording { "STOP LOG" } else { "RECORD" },
            LILAC,
            self.recording,
        ) {
            self.recording = !self.recording;
        }
        if secondary_button(
            ui,
            rect(left + half + 8.0, height - 38.0, half, 24.0),
            "DETAILS",
            BLUE,
            self.details,
        ) {
            self.details = !self.details;
        }
    }

    fn apply_voltage(&mut self) {
        match self.voltage_text.parse::<f64>() {
            Ok(value) if value.is_finite() && (0.0..=30.0).contains(&value) => {
                self.voltage = value;
                self.voltage_text = format!("{value:.2}");
                self.error.clear();
            }
            _ => self.error = "VOLTAGE MUST BE 0 TO 30 V".into(),
        }
    }
    fn apply_current(&mut self) {
        match self.current_text.parse::<f64>() {
            Ok(value) if value.is_finite() && (0.0..=5.0).contains(&value) => {
                self.current = value;
                self.current_text = format!("{value:.3}");
                self.error.clear();
            }
            _ => self.error = "CURRENT MUST BE 0 TO 5 A".into(),
        }
    }
}

impl eframe::App for Preview {
    fn ui(&mut self, ui: &mut egui::Ui, _: &mut eframe::Frame) {
        let width = ui.max_rect().width();
        let height = ui.max_rect().height();
        if width < 760.0 || height < 520.0 {
            self.mini(ui, width, height);
            return;
        }
        frame(ui, width, height);
        let left = 112.0;
        let compact = ((580.0 - height) / 60.0).clamp(0.0, 1.0);
        let y = |normal: f32, small: f32| normal + (small - normal) * compact;
        let numeral_size = 42.0 - 6.0 * compact;
        text(ui, left, 57.0, 25.0, PEACH, "POWER CONTROL");
        text(ui, left, 89.0, 14.0, DIM, "MP305B  /  LAMP BENCH");
        let current = (self.voltage / 126.3).min(self.current);
        let volts = (current * 126.3).min(self.voltage);
        let watts = volts * current;
        let on = self.output;
        text(ui, left, y(123.0, 114.0), 18.0, PEACH, "VOLTAGE");
        readout(
            ui,
            left,
            y(143.0, 132.0),
            &format!("{:.2}", if on { volts } else { 0.0 }),
            "V",
            PEACH,
            numeral_size,
        );
        if field(
            ui,
            left + 8.0,
            y(194.0, 177.0),
            "Voltage (V)",
            &mut self.voltage_text,
        ) {
            self.apply_voltage();
        }
        text(ui, left, y(244.0, 218.0), 18.0, LILAC, "CURRENT");
        readout(
            ui,
            left,
            y(264.0, 236.0),
            &format!("{:.3}", if on { current } else { 0.0 }),
            "A",
            LILAC,
            numeral_size,
        );
        if field(
            ui,
            left + 8.0,
            y(315.0, 281.0),
            "Current limit (A)",
            &mut self.current_text,
        ) {
            self.apply_current();
        }
        text(ui, left, y(370.0, 327.0), 17.0, BLUE, "POWER");
        ui.painter().text(
            Pos2::new(left + 61.0, y(369.0, 326.0)),
            Align2::LEFT_TOP,
            format!("{:.2} W", if on { watts } else { 0.0 }),
            number_font(20.0),
            BLUE,
        );
        let mode = if !on {
            "OFF"
        } else if current + 0.00001 < self.voltage / 126.3 {
            "CC"
        } else {
            "CV"
        };
        text(ui, left + 196.0, y(370.0, 327.0), 18.0, PEACH, mode);
        if button(
            ui,
            rect(left, y(410.0, 365.0), 107.0, 40.0),
            "OUTPUT OFF",
            CORAL,
            !self.output,
        ) {
            self.output = false;
        }
        if button(
            ui,
            rect(left + 116.0, y(410.0, 365.0), 107.0, 40.0),
            "OUTPUT ON",
            PEACH,
            self.output,
        ) {
            self.output = true;
        }
        text(
            ui,
            left,
            y(462.0, 412.0),
            13.0,
            if self.error.is_empty() { DIM } else { CORAL },
            if self.error.is_empty() {
                "SIMULATION / CONTROLS ARE LOCAL"
            } else {
                &self.error
            },
        );
        let footer = height - 86.0;
        if button(
            ui,
            rect(left + 8.0, footer, 104.0, 28.0),
            if self.recording { "STOP LOG" } else { "RECORD" },
            if self.recording { CORAL } else { LILAC },
            self.recording,
        ) {
            self.recording = !self.recording;
        }
        if button(
            ui,
            rect(left + 120.0, footer, 95.0, 28.0),
            "DETAILS",
            BLUE,
            self.details,
        ) {
            self.details = !self.details;
        }

        let chart_x = 374.0;
        text(ui, chart_x + 12.0, 57.0, 25.0, PEACH, "POWER TELEMETRY");
        ui.painter().text(
            Pos2::new(width - 24.0, 65.0),
            Align2::RIGHT_TOP,
            "SIMULATED / DC",
            label_font(16.0),
            DIM,
        );
        ui.painter()
            .rect_filled(rect(chart_x, 100.0, width - chart_x - 24.0, 7.0), 3, LILAC);
        let plot_height = (height - 223.0) / 3.0;
        for (index, label, unit, color, maximum, value) in [
            (
                0,
                "VOLTAGE",
                "V",
                PEACH,
                (self.voltage * 1.25).max(1.0),
                volts,
            ),
            (1, "CURRENT", "A", LILAC, (current * 1.25).max(0.1), current),
            (2, "POWER", "W", BLUE, (watts * 1.25).max(1.0), watts),
        ] {
            plot(
                ui,
                rect(
                    chart_x,
                    122.0 + index as f32 * plot_height,
                    width - chart_x - 24.0,
                    plot_height - 7.0,
                ),
                label,
                unit,
                color,
                maximum,
                value,
                self.output,
                self.window,
                index == 2,
            );
        }
        let options = [
            (10, "10 S"),
            (30, "30 S"),
            (60, "1 MIN"),
            (120, "2 MIN"),
            (300, "5 MIN"),
            (600, "10 MIN"),
        ];
        let option_width = (width - chart_x - 49.0) / 6.0;
        for (i, (seconds, label)) in options.into_iter().enumerate() {
            let chosen = self.window == seconds;
            if button(
                ui,
                rect(
                    chart_x + i as f32 * (option_width + 5.0),
                    footer,
                    option_width,
                    28.0,
                ),
                label,
                if chosen { PEACH } else { BLUE },
                chosen,
            ) {
                self.window = seconds;
            }
        }

        if self.details {
            egui::Window::new("DEVICE STATUS").open(&mut self.details).anchor(Align2::RIGHT_TOP, Vec2::new(-24.0, 122.0))
                .fixed_size(Vec2::new(294.0, 310.0)).collapsible(false).resizable(false).show(ui.ctx(), |ui| {
                    ui.heading(RichText::new("MP305B / SIMULATION").color(PEACH));
                    ui.add_space(18.0);
                    ui.label("No hardware connection");
                    ui.label("Lamp model: 12 V / approximately 1 W");
                    ui.label("Setpoint range: 0 to 30 V / 0 to 5 A");
                    ui.add_space(18.0);
                    ui.label("This is a theme preview. Output and recording controls affect the simulation only.");
                    ui.add_space(18.0);
                    ui.label(RichText::new("OUTPUT OFF STAYS REACHABLE").color(CORAL));
                });
        }
    }
}

fn check_setpoint_columns(h: &Harness<'_, Preview>) {
    let decimal_x = |value: &str| {
        h.output()
            .shapes
            .iter()
            .find_map(|shape| {
                let egui::Shape::Text(text) = &shape.shape else {
                    return None;
                };
                if text.galley.text() != value {
                    return None;
                }
                text.galley.rows.iter().find_map(|row| {
                    row.glyphs
                        .iter()
                        .find(|glyph| glyph.chr == '.')
                        .map(|glyph| text.pos.x + row.pos.x + glyph.pos.x)
                })
            })
            .unwrap()
    };
    assert!((decimal_x(&h.state().voltage_text) - decimal_x(&h.state().current_text)).abs() < 0.75);
}

fn render() {
    let directory = PathBuf::from("target/retro-preview");
    std::fs::create_dir_all(&directory).unwrap();
    for (size, name) in [
        ([1000.0, 640.0], "retro-default"),
        ([900.0, 580.0], "retro-compact"),
        ([760.0, 520.0], "retro-minimum"),
        ([360.0, 290.0], "retro-mini"),
        ([320.0, 272.0], "retro-mini-minimum"),
        ([900.0, 272.0], "retro-mini-wide"),
        ([320.0, 580.0], "retro-mini-tall"),
    ] {
        let mut h = Harness::builder()
            .with_render_every_step(true)
            .with_size(size)
            .build_eframe(|cc| {
                install(&cc.egui_ctx);
                Preview::default()
            });
        h.run();
        if size[0] < 760.0 || size[1] < 520.0 {
            check_setpoint_columns(&h);
        }
        h.render()
            .unwrap()
            .save(directory.join(format!("{name}.png")))
            .unwrap();
        h.get_by_label("DETAILS").click();
        h.run();
        h.get_by_label("OUTPUT OFF").click();
        h.run();
        assert!(!h.state().output);
        h.render()
            .unwrap()
            .save(directory.join(format!("{name}-off-details.png")))
            .unwrap();
        h.get_by_label("OUTPUT ON").click();
        h.run();
        assert!(h.state().output);
    }
    let mut h = Harness::builder()
        .with_render_every_step(true)
        .with_size([900.0, 580.0])
        .build_eframe(|cc| {
            install(&cc.egui_ctx);
            Preview::default()
        });
    h.run();
    h.get_by_label("5 MIN").click();
    h.get_by_label("RECORD").click();
    h.run();
    h.get_by_label("Voltage (V)").click();
    h.run();
    h.key_press_modifiers(egui::Modifiers::COMMAND, egui::Key::A);
    h.event(egui::Event::Text("7.25".into()));
    h.run();
    h.set_size(Vec2::new(320.0, 272.0));
    h.run();
    assert!(h.query_by_label("5 MIN").is_none());
    assert_eq!(h.state().voltage_text, "7.25");
    assert_eq!(h.state().voltage, 12.0);
    assert!(h.state().recording);
    assert!(h.state().output);
    h.get_by_label("Voltage (V)").click();
    h.key_press(egui::Key::Enter);
    h.run();
    assert_eq!(h.state().voltage, 7.25);
    h.get_by_label("STOP LOG").click();
    h.run();
    h.set_size(Vec2::new(900.0, 580.0));
    h.run();
    assert!(h.query_by_label("5 MIN").is_some());
    assert_eq!(h.state().window, 300);
    assert_eq!(h.state().voltage, 7.25);
    assert!(!h.state().recording);
    assert!(h.state().output);
    h.set_size(Vec2::new(320.0, 272.0));
    h.run();
    h.get_by_label("Voltage (V)").click();
    h.run();
    h.key_press_modifiers(egui::Modifiers::COMMAND, egui::Key::A);
    h.event(egui::Event::Text("31.00".into()));
    h.key_press(egui::Key::Enter);
    h.run();
    assert_eq!(h.state().voltage, 7.25);
    assert!(!h.state().error.is_empty());
    check_setpoint_columns(&h);
    h.get_by_label("RECORD").click();
    h.run();
    h.render()
        .unwrap()
        .save(directory.join("retro-mini-error-recording.png"))
        .unwrap();
    h.get_by_label("OUTPUT OFF").click();
    h.run();
    assert!(!h.state().output);
    assert!(h.state().recording);
    println!("Rendered 15 previews; output, Details, setpoint validation, recording and resize checks passed.");
}

fn main() -> eframe::Result {
    if std::env::args().any(|arg| arg == "--render") {
        render();
        return Ok(());
    }
    eframe::run_native(
        "MP305 Remote / Retro preview (simulation)",
        eframe::NativeOptions {
            viewport: egui::ViewportBuilder::default()
                .with_inner_size([900.0, 580.0])
                .with_min_inner_size([320.0, 272.0]),
            ..Default::default()
        },
        Box::new(|cc| {
            install(&cc.egui_ctx);
            Ok(Box::new(Preview::default()))
        }),
    )
}
