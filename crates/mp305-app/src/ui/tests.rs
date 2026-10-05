//! Implements: nothing; UI regression tests for the app DD, revision 6.
//!
//! The real screens run over fixed model fixtures. Input travels through
//! egui and the production action handler; no device or file worker starts.
//! UT-APP-020 inspects the production drawing files separately.
//! Coverage: included in the GUI path exclusion as test-only harness code;
//! UT-APP-029 to UT-APP-035 verify the production behavior it exercises.

use std::path::PathBuf;

use eframe::egui::{self, accesskit::Role};
use egui_kittest::{
    kittest::{By, NodeT as _, Queryable as _},
    Harness, SnapshotOptions,
};

use super::{screens, theme, widgets, Theme, View};
use crate::actions::{self, Clock, IdSource};
use crate::fields::FieldKind;
use crate::model::{Banner, BannerKind, CloseOrigin, Model, Phase, Reading, RecordingState};
use crate::names::{Map, Report};
use crate::testkit::{at_s, clock_s, connected_model, found_a, found_b, r, t0};
use crate::worker::Command;

/// An app containing only production drawing and action handling.
struct Scene {
    /// Model fixed at a deterministic reading time.
    model: Model,
    /// Window presentation state.
    view: View,
    /// Collected device commands, never executed.
    sent: Vec<Command>,
    /// IDs assigned by the real action handler.
    ids: IdSource,
    /// Frozen host time.
    clock: Clock,
}

impl eframe::App for Scene {
    fn ui(&mut self, ui: &mut egui::Ui, _frame: &mut eframe::Frame) {
        let actions = screens::show(ui, &self.model, &mut self.view, self.clock.now);
        for action in actions {
            self.sent.extend(actions::handle(
                &mut self.model,
                action,
                self.clock,
                &mut self.ids,
            ));
            self.model.sync_name_target();
        }
    }
}

/// Constructs the real layout at an exact window size and display scale.
fn harness(model: Model, size: [f32; 2], scale: f32) -> Harness<'static, Scene> {
    themed(model, size, scale, Theme::Standard)
}

/// Constructs the same production screens in a selected presentation.
fn themed(
    mut model: Model,
    size: [f32; 2],
    scale: f32,
    presentation: Theme,
) -> Harness<'static, Scene> {
    model
        .names
        .apply(Report::Loaded(Ok(Map::new()), Some("test-boot".into())));
    model.sync_name_target();
    let mut harness = Harness::builder()
        .with_size(size)
        .with_pixels_per_point(scale)
        .with_options(
            SnapshotOptions::new()
                .output_path(PathBuf::from(env!("CARGO_MANIFEST_DIR")).join("tests/snapshots")),
        )
        .build_eframe(|cc| {
            theme::install(&cc.egui_ctx);
            Scene {
                model,
                view: View {
                    theme: presentation,
                    ..View::default()
                },
                sent: Vec::new(),
                ids: IdSource::new(),
                clock: clock_s(60.0),
            }
        });
    harness.run();
    harness
}

/// Connected lamp fixture, including a step and small measurement variation.
fn lamp() -> Model {
    let mut model = connected_model();
    model.connected = Some(found_b());
    model.transport = Some(crate::model::Kind::Hid);
    model.info.as_mut().unwrap().hardware = None;
    model.info.as_mut().unwrap().version.0 = [1, 6, 0, 51];
    model.chart.clear();
    for n in 0..=240_u32 {
        let mut reading = r(1, 0, 0, 1200, 200, at_s(f64::from(n) / 4.0));
        let on = n >= 40;
        reading.reading.raw.voltage = if on { 1200 } else { 0 };
        reading.reading.raw.current = if on {
            94 + u16::try_from(n % 3).unwrap()
        } else {
            0
        };
        reading.reading.raw.power = if on { 113 } else { 0 };
        reading.reading = Reading::from_raw(&reading.reading.raw);
        reading.reading.regulation = crate::model::RegulationMode::Cv;
        model.chart.push(&reading);
        model.reading = Some(reading);
    }
    model
        .voltage
        .follow(FieldKind::Voltage, 1200, &model.limits);
    model.current.follow(FieldKind::Current, 200, &model.limits);
    model
}

/// The same connected supply with confirmed zero output and unchanged setpoints.
fn lamp_off() -> Model {
    let mut model = lamp();
    let mut reading = r(0, 0, 0, 1200, 200, at_s(60.0));
    reading.reading.raw.voltage = 0;
    reading.reading.raw.current = 0;
    reading.reading.raw.power = 0;
    reading.reading = Reading::from_raw(&reading.reading.raw);
    reading.reading.regulation = crate::model::RegulationMode::Off;
    model.reading = Some(reading);
    model
}

/// Selects the full content of an accessible field and types replacement text.
fn replace(h: &mut Harness<'_, Scene>, label: &str, text: &str) {
    h.get_by_role_and_label(Role::TextInput, label).click();
    h.run();
    h.key_press_modifiers(egui::Modifiers::COMMAND, egui::Key::A);
    h.event(egui::Event::Text(text.into()));
    h.run();
}

/// Test: UT-APP-029
#[test]
fn ui_selection_fields_recording_and_chart_use_real_actions() {
    for presentation in [Theme::Standard, Theme::Retro] {
        let harness = |model, size, scale| themed(model, size, scale, presentation);
        let mut idle = Model::new(PathBuf::from("/recordings"), t0());
        idle.found = vec![found_a(), found_b()];
        let mut picker = harness(idle, [900.0, 580.0], 1.0);
        picker.get_by_label("MP305B, USB / B").click();
        picker.run();
        assert!(picker.state().sent.is_empty());
        picker
            .get_by_role_and_label(Role::Button, "Connect")
            .click();
        picker.run_steps(2);
        assert!(
            matches!(picker.state().sent.as_slice(), [Command::Connect { identifier, .. }] if identifier == "B")
        );

        let mut h = harness(lamp(), [900.0, 580.0], 1.0);
        replace(&mut h, "Voltage (V)", "5.00");
        h.key_press(egui::Key::Enter);
        h.run();
        assert!(
            matches!(h.state().sent.as_slice(), [Command::SetVoltage { volts, .. }] if *volts == 5.0)
        );
        h.state_mut().sent.clear();
        replace(&mut h, "Current limit (A)", "0.100");
        h.get_by_role_and_label(Role::Button, "Set current").click();
        h.run();
        assert!(
            matches!(h.state().sent.as_slice(), [Command::SetCurrentLimit { amps, .. }] if *amps == 0.1)
        );
        h.state_mut().sent.clear();
        replace(&mut h, "Voltage (V)", "bad");
        h.key_press(egui::Key::Enter);
        h.run();
        assert!(h.state().sent.is_empty());
        assert!(h.state().model.field_error(FieldKind::Voltage).is_some());
        assert!(h.get_by_label("Set voltage").accesskit_node().is_disabled());
        h.get_by_label("5 min").click();
        h.run();
        assert_eq!(h.state().model.window_s, 300);
        h.get_by_label("Record").click();
        h.run();
        assert!(matches!(
            h.state().sent.last(),
            Some(Command::StartRecording { .. })
        ));
        h.get_by_label("Stop").click();
        h.run();
        assert!(matches!(
            h.state().sent.last(),
            Some(Command::StopRecording { .. })
        ));
    }
}

/// Test: UT-APP-030
#[test]
fn ui_output_off_remains_reachable_and_other_controls_obey_the_model() {
    for presentation in [Theme::Standard, Theme::Retro] {
        let harness = |model, size, scale| themed(model, size, scale, presentation);
        let mut model = lamp();
        model.banners.push(Banner {
            kind: BannerKind::UncleanExit,
            text: "Previous session ended unexpectedly. The output may still be on.".into(),
        });
        let mut h = harness(model, [760.0, 520.0], 1.0);
        assert!(h.get_by_label("Output ON").accesskit_node().is_disabled());
        assert!(!h.get_by_label("Output OFF").accesskit_node().is_disabled());
        h.get_by_label("Details").click();
        h.run();
        h.state_mut().model.close_dialog = Some(CloseOrigin::Disconnect);
        h.run();
        let off = h.get_by_label("Output OFF").rect();
        let question = h.get_by_role_and_label(Role::Window, "Disconnect").rect();
        assert!(!off.intersects(question));
        let details = h.get_by_role_and_label(Role::Window, "Details").rect();
        assert!(!off.intersects(details));
        assert!(off.bottom() <= 520.0);
        h.get_by_label("Output OFF").click();
        h.run();
        assert!(matches!(
            h.state().sent.as_slice(),
            [Command::OutputOff { .. }]
        ));
        h.state_mut().model.close_dialog = None;
        h.state_mut().view.details = false;
        h.state_mut().model.phase = Phase::Lost {
            text: "USB disconnected; output remains in its last state.".into(),
            reconnecting: false,
            gave_up: None,
        };
        h.run();
        assert!(h.get_by_label("Output OFF").accesskit_node().is_disabled());
        assert!(h.get_by_label("Output ON").accesskit_node().is_disabled());
        let mut non_dc = lamp();
        non_dc.reading.as_mut().unwrap().reading.live_mode = crate::model::LiveMode::Pd;
        let mut h = harness(non_dc, [760.0, 520.0], 1.0);
        assert!(h.get_by_label("Output ON").accesskit_node().is_disabled());
        h.get_by_label("Output OFF").click();
        h.run();
        assert!(matches!(
            h.state().sent.as_slice(),
            [Command::OutputOff { .. }]
        ));
    }
}

/// Test: UT-APP-033
#[test]
fn ui_names_follow_selection_and_only_success_changes_the_display() {
    for presentation in [Theme::Standard, Theme::Retro] {
        let harness = |model, size, scale| themed(model, size, scale, presentation);
        let mut model = Model::new(PathBuf::from("/recordings"), t0());
        model.found = vec![found_a(), found_b()];
        let mut h = harness(model, [900.0, 580.0], 1.0);
        h.get_by_label("MP305B, USB / B").click();
        h.run();
        h.get_by_label("Details").click();
        h.run();
        replace(&mut h, "Device name", "Lamp bench");
        h.get_by_label("Save name").click();
        h.run();
        let save = h.state_mut().model.names.queued.take().unwrap();
        assert!(save.key.ends_with(":B"));
        assert!(h.state().sent.is_empty());
        h.state_mut().model.names.apply(Report::Saved(save, Ok(())));
        h.run();
        assert!(h.query_by_label("Lamp bench, USB / B").is_some());
        replace(&mut h, "Device name", "Unsaved");
        h.get_by_label("Save name").click();
        h.run();
        let save = h.state_mut().model.names.queued.take().unwrap();
        h.state_mut()
            .model
            .names
            .apply(Report::Saved(save, Err("disk full".into())));
        h.run();
        assert!(h.query_by_label("Lamp bench, USB / B").is_some());
        h.get_by_label("MP305B, Bluetooth / A").click();
        h.run();
        assert!(h.state().model.names.draft.is_empty());
        assert!(h.state().sent.is_empty());
    }
}

/// Test: UT-APP-031
#[test]
fn ui_snapshots_cover_window_sizes_states_and_retina() {
    let mut failures = Vec::new();
    for presentation in [Theme::Standard, Theme::Retro] {
        let harness = |model, size, scale| themed(model, size, scale, presentation);
        let theme_suffix = if presentation == Theme::Standard {
            ""
        } else {
            "-retro"
        };
        for (size, suffix) in [([900.0, 580.0], "default"), ([760.0, 520.0], "minimum")] {
            for state in [
                "connection",
                "connected",
                "edited",
                "recording",
                "lost",
                "details",
                "close",
            ] {
                let mut model = lamp();
                if state == "connection" {
                    model = Model::new(PathBuf::from("/recordings"), t0());
                    model.found = vec![found_a(), found_b()];
                }
                if state == "edited" {
                    model
                        .voltage
                        .edit("5.00".into(), FieldKind::Voltage, &model.limits);
                }
                if state == "recording" {
                    model.recording = RecordingState::On {
                        path: PathBuf::from("/recordings/lamp.csv"),
                        rows: 240,
                    };
                }
                if state == "lost" {
                    model.phase = Phase::Lost {
                        text:
                            "The USB link was lost. The output may still be on. Check the supply."
                                .into(),
                        reconnecting: false,
                        gave_up: None,
                    };
                }
                if state == "close" {
                    model.close_dialog = Some(CloseOrigin::Disconnect);
                }
                if state == "details" {
                    model.connected.as_mut().unwrap().identifier =
                        "DevSrvsID:4295529386-with-a-deliberately-long-endpoint-identifier".into();
                }
                let mut h = harness(model, size, 1.0);
                h.state_mut().view.details = state == "details";
                h.run();
                assert_full_button_clearance(&h, presentation);
                if let Err(error) = h.try_snapshot(format!("{state}-{suffix}{theme_suffix}")) {
                    failures.push(error.to_string());
                }
            }
        }
        let mut h = harness(lamp(), [900.0, 580.0], 2.0);
        assert_full_button_clearance(&h, presentation);
        if let Err(error) = h.try_snapshot(format!("connected-retina{theme_suffix}")) {
            failures.push(error.to_string());
        }
    }
    assert!(failures.is_empty(), "{}", failures.join("\n"));
}

/// Measures rendered divider and footer rules, independently of layout constants.
fn assert_full_button_clearance(h: &Harness<'_, Scene>, presentation: Theme) {
    let lines = h
        .output()
        .shapes
        .iter()
        .filter_map(|shape| {
            if let egui::Shape::LineSegment { points, .. } = &shape.shape {
                Some(*points)
            } else {
                None
            }
        })
        .collect::<Vec<_>>();
    let divider = lines
        .iter()
        .find(|[a, b]| (a.x - b.x).abs() < 0.1 && (a.y - b.y).abs() > 300.0)
        .expect("full panel divider")[0]
        .x;
    let retro = presentation == Theme::Retro;
    let minimum = if retro { 23.0 } else { 15.0 };
    let buttons = h
        .get_all_by_role(Role::Button)
        .filter(|button| button.rect().left() < divider)
        .collect::<Vec<_>>();
    for button in &buttons {
        let rect = button.rect();
        assert!(
            divider - rect.right() >= minimum,
            "divider clearance: {button:?}, {rect:?}, {divider}"
        );
        assert!(
            rect.left() >= if retro { 80.0 } else { 16.0 },
            "left clearance: {button:?}"
        );
    }
    let details = h.get_by_role_and_label(Role::Button, "Details").rect();
    let footer_top = lines
        .iter()
        .filter(|[a, b]| (a.y - b.y).abs() < 0.1 && b.x < divider && a.y <= details.top())
        .map(|[a, _]| a.y)
        .max_by(f32::total_cmp)
        .unwrap();
    // AccessKit also exposes rows outside a scroll viewport. Only compare
    // fully visible status buttons with the fixed controls; status drawing
    // is clipped above the footer rule.
    let buttons = buttons
        .into_iter()
        .filter(|button| {
            let rect = button.rect();
            rect.top() >= footer_top || rect.bottom() <= footer_top - 4.0
        })
        .collect::<Vec<_>>();
    for (index, button) in buttons.iter().enumerate() {
        for other in buttons.iter().skip(index + 1) {
            assert!(
                !button
                    .rect()
                    .expand(1.5)
                    .intersects(other.rect().expand(1.5)),
                "button gap: {button:?}, {other:?}"
            );
        }
    }
    for name in [
        "Record", "Stop", "Details", "10 s", "30 s", "1 min", "2 min", "5 min", "10 min",
    ] {
        for button in h.query_all_by_role_and_label(Role::Button, name) {
            let rect = button.rect();
            let rule = lines
                .iter()
                .filter(|[a, b]| {
                    (a.y - b.y).abs() < 0.1
                        && a.x <= rect.center().x
                        && b.x >= rect.center().x
                        && a.y <= rect.top()
                })
                .map(|[a, _]| a.y)
                .max_by(f32::total_cmp)
                .expect("footer rule");
            assert!(
                rect.top() - rule >= 7.5,
                "footer clearance for {name}: {rect:?}, rule {rule}"
            );
        }
    }
}

/// Test: UT-APP-031
#[test]
fn ui_numerals_have_fixed_width_and_setpoint_fields_align() {
    let mut rects = Vec::new();
    let mut decimals = Vec::new();
    let mut units = Vec::new();
    for (value, unit) in [
        ("11.11", "V"),
        ("88.88", "V"),
        ("0.00", "V"),
        ("0.095", "A"),
        ("5.000", "A"),
        ("--.--", "V"),
        ("-.---", "A"),
    ] {
        let mut h = Harness::new_ui_state(
            |ui, ready| {
                if *ready {
                    widgets::readout(ui, value, [2, 3], unit, theme::VOLTS, theme::NUMERAL);
                }
            },
            false,
        );
        theme::install(&h.ctx);
        *h.state_mut() = true;
        h.run();
        rects.push(h.get(By::new().role(Role::Label)).rect());
        let text = h
            .output()
            .shapes
            .iter()
            .filter_map(|shape| match &shape.shape {
                egui::Shape::Text(text) => Some(text),
                _ => None,
            })
            .collect::<Vec<_>>();
        let decimal = text.iter().find(|text| text.galley.text() == ".").unwrap();
        let suffix = text.iter().find(|text| text.galley.text() == unit).unwrap();
        let whole = text.first().unwrap();
        assert!(decimal.galley.size().x < whole.galley.size().x / 4.0);
        decimals.push(decimal.pos.x);
        units.push(suffix.pos.x);
    }
    // Unit glyph widths differ, but the decimal and the unit column do not.
    for x in &decimals {
        assert!((x - decimals[0]).abs() < 0.1);
    }
    for x in &units {
        assert!((x - units[0]).abs() < 0.1);
    }
    for rect in &rects {
        assert!((rect.left() - rects[0].left()).abs() < 0.1);
    }
    assert!((rects[0].width() - rects[1].width()).abs() < 0.1);
    assert!((rects[0].width() - rects[2].width()).abs() < 0.1);
    let h = harness(lamp(), [760.0, 520.0], 1.0);
    let v = h
        .get_by_role_and_label(Role::TextInput, "Voltage (V)")
        .rect();
    let a = h
        .get_by_role_and_label(Role::TextInput, "Current limit (A)")
        .rect();
    assert_eq!(v.left(), a.left());
    assert_eq!(v.width(), a.width());
    for name in [
        "10 s",
        "30 s",
        "1 min",
        "2 min",
        "5 min",
        "10 min",
        "Output OFF",
        "Record",
        "Details",
    ] {
        let rect = h.get_by_role_and_label(Role::Button, name).rect();
        assert!(
            rect.left() >= 0.0 && rect.right() <= 760.0 && rect.bottom() <= 520.0,
            "{name}: {rect:?}"
        );
    }
}

/// Test: UT-APP-034
#[test]
fn ui_theme_selection_preserves_session_and_edits_without_commands() {
    for state in [
        "connection",
        "connected",
        "edited",
        "recording",
        "warning",
        "close",
    ] {
        let mut model = lamp();
        if state == "connection" {
            model = Model::new(PathBuf::from("/recordings"), t0());
            model.found = vec![found_b()];
            model.selected = Some(found_b().identifier);
        }
        if state == "edited" {
            model
                .voltage
                .edit("7.25".into(), FieldKind::Voltage, &model.limits);
        }
        if state == "recording" {
            model.recording = RecordingState::On {
                path: PathBuf::from("/recordings/lamp.csv"),
                rows: 240,
            };
        }
        if state == "warning" {
            model.banners.push(Banner {
                kind: BannerKind::UncleanExit,
                text: "Check the supply output.".into(),
            });
        }
        if state == "close" {
            model.close_dialog = Some(CloseOrigin::Disconnect);
        }
        let mut h = themed(model, [900.0, 580.0], 1.0, View::default().theme);
        assert_eq!(h.state().view.theme, Theme::Retro);
        h.state_mut().view.details = true;
        h.run();
        let fields = (
            h.state().model.voltage.text.clone(),
            h.state().model.current.text.clone(),
        );
        let chart = h.state().model.chart.len();
        let phase = h.state().model.phase.clone();
        let recording = h.state().model.recording_line();
        let name = h.state().model.names.draft.clone();
        let selected = h.state().model.selected.clone();
        for (caption, expected) in [
            ("Standard", Theme::Standard),
            ("Retro", Theme::Retro),
            ("Standard", Theme::Standard),
        ] {
            h.get_by_label(caption).click();
            h.run();
            assert_eq!(h.state().view.theme, expected);
            assert!(h.state().sent.is_empty());
            assert_eq!(
                (&h.state().model.voltage.text, &h.state().model.current.text),
                (&fields.0, &fields.1)
            );
            assert_eq!(h.state().model.chart.len(), chart);
            assert_eq!(h.state().model.phase, phase);
            assert_eq!(h.state().model.recording_line(), recording);
            assert_eq!(h.state().model.names.draft, name);
            assert_eq!(h.state().model.selected, selected);
        }
        let fresh = themed(lamp(), [900.0, 580.0], 1.0, View::default().theme);
        assert_eq!(fresh.state().view.theme, Theme::Retro);
        assert!(fresh.state().sent.is_empty());
        if state != "connection" {
            h.get_by_label("Output OFF").click();
            h.run();
            assert!(matches!(
                h.state().sent.as_slice(),
                [Command::OutputOff { .. }]
            ));
        }
    }
}

/// Test: UT-APP-035
#[test]
fn ui_compact_resize_preserves_data_and_keeps_output_reachable() {
    for presentation in [Theme::Standard, Theme::Retro] {
        let mut h = themed(lamp(), [900.0, 580.0], 1.0, presentation);
        replace(&mut h, "Voltage (V)", "7.25");
        h.get_by_label("5 min").click();
        h.run();
        let count = h.state().model.chart.len();
        for (size, full) in [
            ([760.0, 520.0], true),
            ([759.0, 520.0], false),
            ([760.0, 519.0], false),
            ([320.0, 320.0], false),
            ([900.0, 320.0], false),
            ([320.0, 580.0], false),
        ] {
            h.set_size(egui::vec2(size[0], size[1]));
            h.run();
            assert_eq!(h.query_by_label("5 min").is_some(), full);
            assert_eq!(h.state().model.voltage.text, "7.25");
            assert_eq!(h.state().model.chart.len(), count);
            assert_eq!(h.state().model.window_s, 300);
            assert!(h.state().sent.is_empty());
            for caption in [
                "Voltage (V)",
                "Current limit (A)",
                "Set voltage",
                "Set current",
                "Output OFF",
                "Output ON",
                "Record",
                "Details",
            ] {
                let rect = h.get_by_label(caption).rect();
                assert!(
                    rect.left() >= 0.0
                        && rect.top() >= 0.0
                        && rect.right() <= size[0]
                        && rect.bottom() <= size[1],
                    "{presentation:?}: {size:?} {caption}: {rect:?}"
                );
            }
        }
        h.set_size(egui::vec2(320.0, 320.0));
        h.run();
        h.get_by_label("Set voltage").click();
        h.run();
        assert!(
            matches!(h.state().sent.as_slice(), [Command::SetVoltage { volts, .. }] if *volts == 7.25)
        );
        h.state_mut().sent.clear();
        h.get_by_label("Record").click();
        h.run();
        assert!(matches!(
            h.state().sent.last(),
            Some(Command::StartRecording { .. })
        ));
        h.get_by_label("Stop").click();
        h.run();
        assert!(matches!(
            h.state().sent.last(),
            Some(Command::StopRecording { .. })
        ));
        h.state_mut().sent.clear();
        h.get_by_label("Details").click();
        h.run();
        h.get_by_label("Output OFF").click();
        h.run();
        assert!(matches!(
            h.state().sent.as_slice(),
            [Command::OutputOff { .. }]
        ));
        h.state_mut().sent.clear();
        h.state_mut().model.close_dialog = Some(CloseOrigin::Disconnect);
        h.run();
        h.get_by_label("Output OFF").click();
        h.run();
        assert!(matches!(
            h.state().sent.as_slice(),
            [Command::OutputOff { .. }]
        ));
        h.state_mut().model.apply(
            crate::worker::UiReading {
                sid: 1,
                reading: r(0, 0, 0, 1200, 200, at_s(60.25)),
            },
            at_s(60.25),
        );
        assert_eq!(h.state().model.chart.len(), count + 1);
        h.state_mut().model.close_dialog = None;
        h.state_mut().view.details = false;
        h.state_mut().sent.clear();
        h.set_size(egui::vec2(900.0, 580.0));
        h.run();
        assert!(h.query_by_label("5 min").is_some());
        assert_eq!(h.state().model.chart.len(), count + 1);
        assert!(h.state().sent.is_empty());
    }
}

/// Test: UT-APP-035
#[test]
fn ui_compact_snapshots_cover_states_and_aspect_ratios() {
    let mut failures = Vec::new();
    for presentation in [Theme::Standard, Theme::Retro] {
        for state in [
            "connected",
            "off",
            "connection",
            "edited",
            "recording",
            "warning",
            "lost",
            "details",
            "close",
        ] {
            let mut model = lamp();
            if state == "off" {
                model = lamp_off();
            }
            if state == "connection" {
                model = Model::new(PathBuf::from("/recordings"), t0());
                model.found = vec![found_a(), found_b()];
            }
            if state == "edited" {
                model
                    .voltage
                    .edit("31.00".into(), FieldKind::Voltage, &model.limits);
            }
            if state == "recording" {
                model.recording = RecordingState::On {
                    path: PathBuf::from("/recordings/lamp.csv"),
                    rows: 240,
                };
            }
            if state == "warning" {
                model.banners.push(Banner {
                    kind: BannerKind::UncleanExit,
                    text: "Previous session ended unexpectedly. The output may still be on.".into(),
                });
            }
            if state == "lost" {
                model.phase = Phase::Lost {
                    text: "USB disconnected. The output remains in its last state.".into(),
                    reconnecting: false,
                    gave_up: None,
                };
            }
            if state == "close" {
                model.close_dialog = Some(CloseOrigin::Disconnect);
            }
            let mut h = themed(model, [320.0, 320.0], 1.0, presentation);
            h.state_mut().view.details = state == "details";
            h.run();
            assert_compact_button_clearance(&h, 320.0, presentation);
            if let Err(error) = h.try_snapshot(format!("compact-{presentation:?}-{state}")) {
                failures.push(error.to_string());
            }
        }
        for (size, name) in [([900.0, 320.0], "wide"), ([320.0, 580.0], "tall")] {
            let mut h = themed(lamp(), size, 1.0, presentation);
            assert_compact_button_clearance(&h, size[0], presentation);
            if let Err(error) = h.try_snapshot(format!("compact-{presentation:?}-{name}")) {
                failures.push(error.to_string());
            }
        }
    }
    assert!(failures.is_empty(), "{}", failures.join("\n"));
}

/// Compact scrollable controls retain side gutters; the fixed footer stays separated.
fn assert_compact_button_clearance(h: &Harness<'_, Scene>, width: f32, presentation: Theme) {
    for button in h.get_all_by_role(Role::Button) {
        let rect = button.rect();
        assert!(
            rect.left()
                >= if presentation == Theme::Retro {
                    36.0
                } else {
                    12.0
                },
            "compact left gutter: {button:?}"
        );
        assert!(
            rect.right()
                <= width
                    - if presentation == Theme::Retro {
                        15.5
                    } else {
                        11.5
                    },
            "compact right gutter: {button:?}, {rect:?}"
        );
    }
    if let Some(off) = h.query_by_role_and_label(Role::Button, "Output OFF") {
        let on = h.get_by_role_and_label(Role::Button, "Output ON");
        let details = h.get_by_role_and_label(Role::Button, "Details");
        assert!(on.rect().left() - off.rect().right() >= 7.5);
        assert!(details.rect().top() - on.rect().bottom() >= 3.5);
    }
    if presentation == Theme::Retro {
        let rectangles = h
            .output()
            .shapes
            .iter()
            .filter_map(|shape| {
                if let egui::Shape::Rect(rect) = &shape.shape {
                    Some(rect)
                } else {
                    None
                }
            })
            .collect::<Vec<_>>();
        let outer = rectangles
            .iter()
            .find(|shape| shape.fill == egui::Color32::from_rgb(255, 153, 102))
            .unwrap()
            .rect;
        let inner = rectangles
            .iter()
            .find(|shape| {
                shape.fill == egui::Color32::BLACK
                    && shape.rect.left() > outer.left()
                    && shape.rect.top() > outer.top()
                    && shape.rect.width() > 200.0
                    && shape.rect.height() > 150.0
            })
            .unwrap()
            .rect;
        let details = h.get_by_role_and_label(Role::Button, "Details").rect();
        assert!(
            outer.bottom() - inner.bottom() >= 15.5,
            "lower band must stay visible"
        );
        assert!(
            inner.bottom() - details.bottom() >= 15.0,
            "footer must clear the lower elbow"
        );
        assert!(details.left() >= inner.left() + 11.5);
    }
}

/// Test: UT-APP-035
#[test]
fn ui_compact_off_state_uses_shared_numeric_spacing_and_one_off_label() {
    for presentation in [Theme::Standard, Theme::Retro] {
        let mut h = themed(lamp_off(), [320.0, 320.0], 1.0, presentation);
        assert!(h.query_by_label("OFF").is_some());
        assert!(h.query_by_label("OFF · off").is_none());
        assert!(h.query_by_label("0.00 W").is_some());
        let dots = h
            .output()
            .shapes
            .iter()
            .filter_map(|shape| {
                if let egui::Shape::Text(text) = &shape.shape {
                    (text.galley.text() == ".").then_some(text)
                } else {
                    None
                }
            })
            .collect::<Vec<_>>();
        assert_eq!(dots.len(), 3, "V/A/W use the same compact punctuation");
        assert!(dots.last().unwrap().galley.size().x < 8.0);
        assert!(h.state().sent.is_empty());
        assert_compact_button_clearance(&h, 320.0, presentation);
        let field_left = h.get_by_label("Voltage (V)").rect().left();
        h.state_mut().model.banners.push(Banner {
            kind: BannerKind::UncleanExit,
            text: "Previous session ended unexpectedly. The output may still be on.".into(),
        });
        h.run();
        for (reading, field) in [("0.00 V", "Voltage (V)"), ("0.000 A", "Current limit (A)")] {
            let field = h.get_by_label(field).rect();
            let value = h.get_by_label(reading).rect();
            assert!(
                field.left() - value.right() >= 4.0,
                "scrolling must not overlap readings and setpoints"
            );
            if presentation == Theme::Retro {
                assert_eq!(
                    field.left(),
                    field_left,
                    "scrollbar must not move the setpoint column"
                );
            }
        }
    }
}

/// Test: UT-APP-035
#[test]
fn ui_compact_alignment_selection_and_eligibility_follow_the_model() {
    for presentation in [Theme::Standard, Theme::Retro] {
        let mut model = lamp();
        model.recording = RecordingState::On {
            path: PathBuf::from("/recordings/lamp.csv"),
            rows: 240,
        };
        let mut h = themed(model, [320.0, 320.0], 1.0, presentation);
        h.state_mut().model.names.draft = "Lamp bench".into();
        for size in [[900.0, 580.0], [320.0, 320.0]] {
            h.set_size(egui::vec2(size[0], size[1]));
            h.run();
            assert!(matches!(
                h.state().model.recording,
                RecordingState::On { rows: 240, .. }
            ));
            assert_eq!(h.state().model.names.draft, "Lamp bench");
            assert_eq!(h.state().model.connected.as_ref().unwrap().identifier, "B");
            assert!(h.state().sent.is_empty());
        }
        let v = h.get_by_label("Voltage (V)").rect();
        let a = h.get_by_label("Current limit (A)").rect();
        assert_eq!(v.left(), a.left());
        assert_eq!(v.width(), a.width());
        assert_eq!(
            h.get_by_label("Set voltage").rect().left(),
            h.get_by_label("Set current").rect().left()
        );
        let texts = h
            .output()
            .shapes
            .iter()
            .filter_map(|shape| match &shape.shape {
                egui::Shape::Text(text) => Some(text),
                _ => None,
            })
            .collect::<Vec<_>>();
        let mut dots = Vec::new();
        for (value, field) in [("12.00", v), ("0.200", a)] {
            let text = texts
                .iter()
                .find(|text| text.galley.text() == value)
                .unwrap();
            let dot = text
                .galley
                .rows
                .first()
                .unwrap()
                .glyphs
                .iter()
                .find(|glyph| glyph.chr == '.')
                .unwrap();
            dots.push(text.pos.x + dot.pos.x);
            assert!(
                (text.pos.y + text.galley.mesh_bounds.center().y - field.center().y).abs() < 2.0
            );
        }
        assert!((dots[0] - dots[1]).abs() < 0.1);
        for (digits, rect) in [("12", v), ("094", a)] {
            let text = texts
                .iter()
                .find(|text| text.galley.text().trim() == digits)
                .unwrap();
            assert!(
                (text.pos.y + text.galley.mesh_bounds.center().y - rect.center().y).abs() < 2.0
            );
        }
        replace(&mut h, "Voltage (V)", "31.00");
        assert!(h.get_by_label("Set voltage").accesskit_node().is_disabled());
        assert!(!h.get_by_label("Output OFF").accesskit_node().is_disabled());
        h.state_mut().model.phase = Phase::Lost {
            text: "Link lost".into(),
            reconnecting: false,
            gave_up: None,
        };
        h.run();
        assert!(h.get_by_label("Output OFF").accesskit_node().is_disabled());
        assert!(h.get_by_label("Output ON").accesskit_node().is_disabled());
        assert!(h.state().sent.is_empty());
        let mut model = Model::new(PathBuf::from("/recordings"), t0());
        model.found = vec![found_a(), found_b()];
        let mut picker = themed(model, [320.0, 320.0], 1.0, presentation);
        picker.get_by_label("MP305B, USB / B").click();
        picker.run();
        picker.set_size(egui::vec2(900.0, 580.0));
        picker.run();
        assert_eq!(picker.state().model.selected.as_deref(), Some("B"));
        if presentation == Theme::Retro {
            let first = picker.get_by_label("MP305B, Bluetooth / A").rect();
            let second = picker.get_by_label("MP305B, USB / B").rect();
            let connect = picker.get_by_label("Connect").rect();
            let details = picker.get_by_label("Details").rect();
            assert_eq!(first.left(), second.left());
            assert_eq!(first.width(), second.width());
            assert_eq!(first.left(), connect.left());
            assert_eq!(first.width(), connect.width());
            assert_eq!(first.left(), details.left());
            assert_eq!(details.height(), 32.0);
        }

        assert!(picker.state().sent.is_empty());
        picker.set_size(egui::vec2(320.0, 320.0));
        picker.run();
        picker.get_by_label("Connect").click();
        picker.run_steps(2);
        assert!(
            matches!(picker.state().sent.as_slice(), [Command::Connect { identifier, .. }] if identifier == "B")
        );
    }
}
