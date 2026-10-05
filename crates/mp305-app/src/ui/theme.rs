//! Implements: DD-APP-031 (the look of the screens).
//!
//! Coverage: excluded from the measurement as GUI drawing code (ADR-0008;
//! app DD, section 8, decision 9); UT-APP-020 inspects this file instead.
//!
//! The design tokens (colours, type sizes, spacing) and their installation
//! at start-up: the B612 fonts, embedded in the binary, and one dark style
//! for both OS themes. Colour means quantity: amber is volts and teal is
//! amps everywhere; the live colour marks the output on, a recording and
//! faults. Nothing else is coloured.

use std::sync::Arc;

use eframe::egui::{
    self, Color32, CornerRadius, FontData, FontDefinitions, FontFamily, FontId, Margin, Stroke,
    TextStyle,
};

/// The window background.
pub const WINDOW: Color32 = Color32::from_rgb(0x15, 0x17, 0x1B);
/// The left column, slightly lighter than the window.
pub const COLUMN: Color32 = Color32::from_rgb(0x1B, 0x1E, 0x24);
/// Rules, outlines and grid lines.
pub const RULE: Color32 = Color32::from_rgb(0x2A, 0x2E, 0x36);
/// The text.
pub const TEXT: Color32 = Color32::from_rgb(0xE8, 0xE4, 0xDA);
/// Dim text: labels, units and quiet buttons.
pub const DIM: Color32 = Color32::from_rgb(0xA0, 0xA6, 0xB1);
/// Volts, in readouts and in the chart.
pub const VOLTS: Color32 = Color32::from_rgb(0xF0, 0xB2, 0x3E);
/// Amps, in readouts and in the chart.
pub const AMPS: Color32 = Color32::from_rgb(0x4C, 0xC7, 0xB4);
/// The output on, a recording, faults and errors.
pub const LIVE: Color32 = Color32::from_rgb(0xE5, 0x53, 0x3D);

/// The selected output-on background, with readable light text.
pub const OUTPUT_ACTIVE: Color32 = Color32::from_rgb(0x86, 0x32, 0x29);
/// Power in the readout and plot.
pub const WATTS: Color32 = Color32::from_rgb(0xAB, 0xAE, 0xF2);

/// The body text size in points.
pub const BODY: f32 = 14.0;
/// The small text size in points.
pub const SMALL: f32 = 12.0;
/// The size of the volts and amps numerals in points.
pub const NUMERAL: f32 = 40.0;
/// The size of the power numerals in points.
pub const POWER: f32 = 22.0;

/// The unit of spacing in points; every gap is a multiple of it.
pub const UNIT: f32 = 4.0;
/// The padding inside the left column and around the chart.
pub const PAD: f32 = 16.0;
/// The padding inside the left column, as a frame margin.
pub const PAD_MARGIN: i8 = 16;
/// The corner radius of keys, fields and windows.
pub const RADIUS: u8 = 6;

/// The font data name of B612 Regular.
const B612: &str = "B612-Regular";
/// The font data name of B612 Bold.
const B612_BOLD: &str = "B612-Bold";
/// The font data name of B612 Mono Regular.
const B612_MONO: &str = "B612Mono-Regular";
/// The font data name of B612 Mono Bold.
const B612_MONO_BOLD: &str = "B612Mono-Bold";
/// The named family of the bold proportional cut.
const BOLD_FAMILY: &str = "B612 Bold";
/// The named family of the bold fixed-width cut, for the big numerals.
const MONO_BOLD_FAMILY: &str = "B612 Mono Bold";

/// The bold proportional family.
#[must_use]
pub fn bold() -> FontFamily {
    FontFamily::Name(BOLD_FAMILY.into())
}

/// The bold fixed-width family of the big numerals.
#[must_use]
pub fn mono_bold() -> FontFamily {
    FontFamily::Name(MONO_BOLD_FAMILY.into())
}

/// The fixed-width font at `size`.
#[must_use]
pub fn mono(size: f32) -> FontId {
    FontId::new(size, FontFamily::Monospace)
}

/// The proportional font at `size`.
#[must_use]
pub fn text(size: f32) -> FontId {
    FontId::new(size, FontFamily::Proportional)
}

/// Installs the fonts and the style on `ctx`; called once at start-up.
pub fn install(ctx: &egui::Context) {
    ctx.set_fonts(fonts());
    ctx.set_theme(egui::ThemePreference::Dark);
    let style = style();
    ctx.set_style_of(egui::Theme::Dark, style.clone());
    ctx.set_style_of(egui::Theme::Light, style);
}

/// The B612 family, embedded: B612 first for the proportional family,
/// B612 Mono first for the fixed-width family, egui's own fonts behind
/// them for glyphs B612 lacks, and the bold cuts as named families.
fn fonts() -> FontDefinitions {
    let mut fonts = FontDefinitions::default();
    for (name, bytes) in [
        (
            B612,
            &include_bytes!("../../assets/fonts/B612-Regular.ttf")[..],
        ),
        (
            B612_BOLD,
            &include_bytes!("../../assets/fonts/B612-Bold.ttf")[..],
        ),
        (
            B612_MONO,
            &include_bytes!("../../assets/fonts/B612Mono-Regular.ttf")[..],
        ),
        (
            B612_MONO_BOLD,
            &include_bytes!("../../assets/fonts/B612Mono-Bold.ttf")[..],
        ),
    ] {
        fonts
            .font_data
            .insert(name.to_string(), Arc::new(FontData::from_static(bytes)));
    }
    let fallback = |family: FontFamily, fonts: &FontDefinitions| {
        fonts.families.get(&family).cloned().unwrap_or_default()
    };
    let proportional = fallback(FontFamily::Proportional, &fonts);
    let monospace = fallback(FontFamily::Monospace, &fonts);
    let with = |first: &str, rest: &[String]| {
        let mut list = vec![first.to_string()];
        list.extend(rest.iter().cloned());
        list
    };
    fonts
        .families
        .insert(FontFamily::Proportional, with(B612, &proportional));
    fonts
        .families
        .insert(FontFamily::Monospace, with(B612_MONO, &monospace));
    fonts
        .families
        .insert(bold(), with(B612_BOLD, &proportional));
    fonts
        .families
        .insert(mono_bold(), with(B612_MONO_BOLD, &monospace));
    fonts
}

/// The style: the token colours on egui's dark visuals, quiet frameless
/// buttons, text that cannot be selected (so that rows take the click),
/// and the type sizes.
fn style() -> egui::Style {
    let mut style = egui::Style {
        text_styles: [
            (TextStyle::Heading, text(18.0)),
            (TextStyle::Body, text(BODY)),
            (TextStyle::Button, text(BODY)),
            (TextStyle::Small, text(SMALL)),
            (TextStyle::Monospace, mono(BODY)),
        ]
        .into(),
        ..Default::default()
    };
    style.interaction.selectable_labels = false;
    let spacing = &mut style.spacing;
    spacing.item_spacing = egui::vec2(8.0, UNIT);
    spacing.button_padding = egui::vec2(UNIT, 2.0);
    spacing.interact_size.y = 28.0;
    spacing.scroll = egui::style::ScrollStyle::solid();
    spacing.window_margin = Margin::same(PAD_MARGIN);

    let mut v = egui::Visuals::dark();
    let radius = CornerRadius::same(RADIUS);
    let rule = Stroke::new(1.0, RULE);
    v.panel_fill = WINDOW;
    v.window_fill = COLUMN;
    v.window_stroke = rule;
    v.window_corner_radius = CornerRadius::same(8);
    v.window_shadow = egui::Shadow::NONE;
    v.popup_shadow = egui::Shadow::NONE;
    v.extreme_bg_color = WINDOW;
    v.text_edit_bg_color = Some(WINDOW);
    v.faint_bg_color = COLUMN;
    v.code_bg_color = WINDOW;
    v.weak_text_color = Some(DIM);
    v.hyperlink_color = TEXT;
    v.warn_fg_color = TEXT;
    v.error_fg_color = LIVE;
    v.button_frame = false;
    v.collapsing_header_frame = false;
    v.indent_has_left_vline = false;
    v.striped = false;
    v.selection.bg_fill = RULE;
    v.selection.stroke = Stroke::new(1.0, TEXT);
    v.text_cursor.stroke = Stroke::new(2.0, TEXT);
    let w = &mut v.widgets;
    w.noninteractive.bg_fill = COLUMN;
    w.noninteractive.weak_bg_fill = COLUMN;
    w.noninteractive.bg_stroke = rule;
    w.noninteractive.fg_stroke = Stroke::new(1.0, TEXT);
    for (state, fg) in [
        (&mut w.inactive, TEXT),
        (&mut w.hovered, TEXT),
        (&mut w.active, TEXT),
        (&mut w.open, TEXT),
    ] {
        state.bg_fill = WINDOW;
        state.weak_bg_fill = Color32::TRANSPARENT;
        state.bg_stroke = rule;
        state.fg_stroke = Stroke::new(1.0, fg);
        state.corner_radius = radius;
        state.expansion = 0.0;
    }
    w.hovered.bg_stroke = Stroke::new(1.0, DIM);
    w.active.bg_stroke = Stroke::new(1.0, TEXT);
    style.visuals = v;
    style
}
