//! Implements: nothing; UI regression tests for the app DD, revision 5.
//!
//! The real screens run over fixed model fixtures. Input travels through
//! egui and the production action handler; no device or file worker starts.
//! UT-APP-020 inspects the production drawing files separately.
//! Coverage: included in the GUI path exclusion as test-only harness code;
//! UT-APP-029 to UT-APP-033 verify the production behavior it exercises.

use std::path::PathBuf;

use eframe::egui::{self, accesskit::Role};
use egui_kittest::{
    kittest::{By, NodeT as _, Queryable as _},
    Harness, SnapshotOptions,
};

use super::{screens, theme, widgets, View};
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
fn harness(mut model: Model, size: [f32; 2], scale: f32) -> Harness<'static, Scene> {
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
                view: View::default(),
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

/// Test: UT-APP-030
#[test]
fn ui_output_off_remains_reachable_and_other_controls_obey_the_model() {
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

/// Test: UT-APP-033
#[test]
fn ui_names_follow_selection_and_only_success_changes_the_display() {
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

/// Test: UT-APP-031
#[test]
fn ui_snapshots_cover_window_sizes_states_and_retina() {
    let mut failures = Vec::new();
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
                    text: "The USB link was lost. The output may still be on. Check the supply."
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
            if let Err(error) = h.try_snapshot(format!("{state}-{suffix}")) {
                failures.push(error.to_string());
            }
        }
    }
    let mut h = harness(lamp(), [900.0, 580.0], 2.0);
    if let Err(error) = h.try_snapshot("connected-retina") {
        failures.push(error.to_string());
    }
    assert!(failures.is_empty(), "{}", failures.join("\n"));
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
