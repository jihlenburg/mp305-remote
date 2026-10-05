use eframe::egui::{self, accesskit::Role};
use egui_kittest::{kittest::Queryable, Harness};
use futures::future::BoxFuture;
use mp305_app::{
    app::AppCore,
    model::{Limits, LiveMode, Model, Reading},
    shell::{Port, Shell},
    ui::App,
    worker::{self, AppEvent, Command, RecordingEvent, Scanner, UiReading},
};
use mp305_core::{
    discovery::{Found, ScanOptions},
    error::Error,
};
use std::{
    path::PathBuf,
    sync::Arc,
    time::{Duration, Instant, SystemTime, UNIX_EPOCH},
};
use tokio::sync::mpsc;

fn note(kind: &str, value: impl std::fmt::Debug) {
    println!(
        "{}",
        serde_json::json!({"time":SystemTime::now().duration_since(UNIX_EPOCH).unwrap().as_secs_f64(), "kind":kind, "value":format!("{value:?}")})
    );
}

struct OnlyUsb {
    inner: Arc<dyn Scanner>,
    id: String,
}
impl Scanner for OnlyUsb {
    fn scan(&self, mut options: ScanOptions) -> BoxFuture<'_, Result<Vec<Found>, Error>> {
        Box::pin(async move {
            options.bluetooth = false;
            options.usb = true;
            Ok(self
                .inner
                .scan(options)
                .await?
                .into_iter()
                .filter(|f| f.identifier == self.id)
                .collect())
        })
    }
}

struct Bench {
    app: App,
    events: mpsc::UnboundedReceiver<AppEvent>,
    readings: mpsc::Receiver<UiReading>,
    event_tx: mpsc::UnboundedSender<AppEvent>,
    reading_tx: mpsc::Sender<UiReading>,
    commands: Option<mpsc::UnboundedSender<Command>>,
    latest: Option<Reading>,
    disconnected: bool,
    recording: bool,
    csv: Option<PathBuf>,
}
impl eframe::App for Bench {
    fn logic(&mut self, ctx: &egui::Context, frame: &mut eframe::Frame) {
        while let Ok(event) = self.events.try_recv() {
            note("event", &event);
            match &event {
                AppEvent::Ready {
                    reading: Some(r), ..
                } => self.latest = Some(r.reading),
                AppEvent::Disconnected { .. } => self.disconnected = true,
                AppEvent::Recording(RecordingEvent::On { path }) => {
                    self.recording = true;
                    self.csv = Some(path.clone());
                }
                AppEvent::Recording(RecordingEvent::Off { .. }) => self.recording = false,
                _ => {}
            }
            self.event_tx.send(event).unwrap();
        }
        while let Ok(r) = self.readings.try_recv() {
            note("reading", r);
            self.latest = Some(r.reading.reading);
            self.reading_tx.try_send(r).unwrap();
        }
        self.app.logic(ctx, frame);
    }
    fn ui(&mut self, ui: &mut egui::Ui, frame: &mut eframe::Frame) {
        self.app.ui(ui, frame);
    }
}

fn advance(h: &mut Harness<'_, Bench>, seconds: f64) {
    let end = Instant::now() + Duration::from_secs_f64(seconds);
    while Instant::now() < end {
        h.step();
        std::thread::sleep(Duration::from_millis(20));
    }
}
fn until(h: &mut Harness<'_, Bench>, what: &str, check: impl Fn(&Bench) -> bool) {
    let end = Instant::now() + Duration::from_secs(12);
    while !check(h.state()) {
        assert!(Instant::now() < end, "timed out: {what}");
        advance(h, 0.05);
    }
    note("pass", what);
}
fn click(h: &mut Harness<'_, Bench>, label: &str) {
    note("click", label);
    h.get_by_role_and_label(Role::Button, label).click();
    advance(h, 0.15);
}
fn edit(h: &mut Harness<'_, Bench>, label: &str, value: &str) {
    note("edit", (label, value));
    h.get_by_role_and_label(Role::TextInput, label).click();
    h.step();
    h.key_press_modifiers(egui::Modifiers::COMMAND, egui::Key::A);
    h.step();
    h.input_mut().events.push(egui::Event::Text(value.into()));
    h.step();
    h.key_press(egui::Key::Enter);
    advance(h, 0.15);
}

fn main() {
    assert_eq!(std::env::var("MP305_HIL").as_deref(), Ok("1"));
    let id = std::env::var("MP305_HIL_DEVICE").expect("explicit USB identifier required");
    assert!(id.starts_with("DevSrvsID:"), "this spike is for macOS USB");
    let output = std::env::current_dir().unwrap().join(format!(
        "target/hardware-ui-{}",
        SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_secs()
    ));
    std::fs::create_dir(&output).unwrap();
    note(
        "meta",
        (
            &id,
            &output,
            "12 V 1 W LED lamp, USB, user authorised 2026-10-05",
        ),
    );
    let mut h = Harness::builder()
        .with_size([900.0, 580.0])
        .build_eframe(|cc| {
            let ctx = cc.egui_ctx.clone();
            let identifier = id.clone();
            let build = Box::pin(async move {
                let mut deps = worker::real_deps().await?;
                deps.scanner = Arc::new(OnlyUsb {
                    inner: deps.scanner,
                    id: identifier,
                });
                Ok(deps)
            });
            let (shell, port) =
                Shell::start(build, Arc::new(move || ctx.request_repaint())).unwrap();
            let (event_tx, events) = mpsc::unbounded_channel();
            let (reading_tx, readings) = mpsc::channel(worker::READING_CAPACITY);
            let commands = port.commands.clone();
            let mut model = Model::new(output.clone(), tokio::time::Instant::now());
            model.limits = Limits {
                max_volts: Some(12.0),
                max_amps: Some(0.2),
            };
            let core = AppCore::with_port(
                Port {
                    commands: port.commands,
                    events,
                    readings,
                },
                Some(shell),
                model,
            );
            Bench {
                app: App::new(core, &cc.egui_ctx),
                events: port.events,
                readings: port.readings,
                event_tx,
                reading_tx,
                commands: Some(commands),
                latest: None,
                disconnected: false,
                recording: false,
                csv: None,
            }
        });
    let mut original = None;
    let result = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
        click(&mut h, "Scan");
        advance(&mut h, 2.0);
        click(&mut h, &format!("MP305B, USB / {id}"));
        click(&mut h, "Connect");
        until(&mut h, "first real reading", |b| b.latest.is_some());
        let first = h.state().latest.unwrap();
        assert!(!first.output_on, "preflight: output already on");
        assert_eq!(first.live_mode, LiveMode::Dc);
        assert!((first.set_volts - 12.0).abs() < 0.006 && (first.set_amps - 0.2).abs() < 0.0006);
        original = Some((first.set_volts, first.set_amps));
        note("preflight", first);
        edit(&mut h, "Current limit (A)", "0.100");
        until(&mut h, "current edit applied", |b| {
            b.latest.is_some_and(|r| (r.set_amps - 0.1).abs() < 0.0006)
        });
        edit(&mut h, "Current limit (A)", "0.200");
        until(&mut h, "current restored", |b| {
            b.latest.is_some_and(|r| (r.set_amps - 0.2).abs() < 0.0006)
        });
        click(&mut h, "Record");
        until(&mut h, "CSV started", |b| b.recording);
        click(&mut h, "Output ON");
        until(&mut h, "lamp readings", |b| {
            b.latest
                .is_some_and(|r| r.output_on && r.volts > 11.9 && r.amps > 0.05 && r.amps < 0.15)
        });
        advance(&mut h, 3.0);
        h.render()
            .unwrap()
            .save(output.join("lamp-on.png"))
            .unwrap();
        click(&mut h, "Details");
        click(&mut h, "Disconnect");
        assert!(h
            .query_by_role_and_label(Role::Button, "Switch off")
            .is_some());
        h.render()
            .unwrap()
            .save(output.join("lamp-on-with-question.png"))
            .unwrap();
        click(&mut h, "Output OFF");
        until(&mut h, "output off with Details and question open", |b| {
            b.latest
                .is_some_and(|r| !r.output_on && r.volts < 0.1 && r.amps < 0.002)
        });
        click(&mut h, "Cancel");
        click(&mut h, "Stop");
        until(&mut h, "CSV stopped", |b| !b.recording);
        h.render()
            .unwrap()
            .save(output.join("lamp-off.png"))
            .unwrap();
    }));
    // Direct worker commands are reserved for teardown, including an assertion failure.
    let tx = h.state_mut().commands.take().unwrap();
    tx.send(Command::OutputOff { id: 9000 }).unwrap();
    advance(&mut h, 2.0);
    if let Some((volts, amps)) = original {
        tx.send(Command::SetVoltage { id: 9001, volts }).unwrap();
        tx.send(Command::SetCurrentLimit { id: 9002, amps })
            .unwrap();
        advance(&mut h, 1.0);
    }
    note("final_reading", h.state().latest);
    let off = h.state().latest.is_some_and(|r| !r.output_on);
    tx.send(Command::Disconnect {
        id: 9003,
        output_off: true,
    })
    .unwrap();
    advance(&mut h, 4.0);
    note("disconnected", h.state().disconnected);
    note("csv", &h.state().csv);
    drop(tx);
    eframe::App::on_exit(&mut h.state_mut().app);
    assert!(off, "output off not confirmed");
    assert!(h.state().disconnected, "disconnect not confirmed");
    if let Err(error) = result {
        std::panic::resume_unwind(error);
    }
    note("result", "PASS");
}
