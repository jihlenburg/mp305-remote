//! Implements: DD-APP-022, DD-APP-021 (the close step's place in the
//! frame), DD-APP-032 (where the notes are logged).
//!
//! `AppCore`: the frame logic and the action dispatch, outside `ui/`, so
//! that what a frame runs (the drain, the close decision, the viewport
//! commands, the repaint deadline, the dispatch of clicks) is tested here
//! and the glue in `ui/` has no branch of its own. The UI thread only
//! sends and calls `try_recv`, and blocks only in [`AppCore::on_exit`]
//! (DD-APP-007).

use core::time::Duration;
use std::path::PathBuf;

use eframe::egui::ViewportCommand;
use futures::future::BoxFuture;
use tokio::sync::mpsc;
use tokio::time::Instant;

use crate::actions::{self, Clock, CloseStep, IdSource, UiAction};
use crate::frametime;
use crate::model::Model;
use crate::shell::{Port, Shell, ShutdownReport};
use crate::texts;
use crate::worker::{AppEvent, Command, Deps, UiReading, Wake};

/// The log target of the frame logic.
pub const LOG_TARGET: &str = "mp305_app::app";

/// How long the exit waits for the worker (DD-APP-007).
pub const SHUTDOWN_BOUND: Duration = Duration::from_secs(3);

/// What the glue passes to [`AppCore::logic`].
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct LogicInput {
    /// Whether the root viewport reports a close request.
    pub close_requested: bool,
    /// eframe's time for the previous frame.
    pub frame_time: Option<Duration>,
}

/// What the glue does after [`AppCore::logic`].
#[derive(Clone, Debug, PartialEq)]
pub struct LogicOutput {
    /// The viewport commands to send, in order.
    pub commands: Vec<ViewportCommand>,
    /// When to repaint without an event.
    pub repaint_after: Option<Duration>,
}

/// The frame logic and the action dispatch of the app.
#[derive(Debug)]
pub struct AppCore {
    /// The model.
    model: Model,
    /// Commands to the worker; `None` after `on_exit`.
    commands: Option<mpsc::UnboundedSender<Command>>,
    /// Events from the worker.
    events: mpsc::UnboundedReceiver<AppEvent>,
    /// Readings from the worker.
    readings: mpsc::Receiver<UiReading>,
    /// The runtime and the worker, when the core started them.
    shell: Option<Shell>,
    /// The command ids.
    ids: IdSource,
}

impl AppCore {
    /// Starts the shell over `build` and a model with `recording_dir`.
    ///
    /// # Errors
    ///
    /// The runtime build error's text.
    pub fn start(
        build: BoxFuture<'static, Result<Deps, String>>,
        wake: Wake,
        recording_dir: PathBuf,
    ) -> Result<AppCore, String> {
        let (shell, port) = Shell::start(build, wake)?;
        let model = Model::new(recording_dir, Instant::now());
        Ok(AppCore::with_port(port, Some(shell), model))
    }

    /// A core around `port`, for the tests without a worker.
    #[must_use]
    pub fn with_port(port: Port, shell: Option<Shell>, model: Model) -> AppCore {
        AppCore {
            model,
            commands: Some(port.commands),
            events: port.events,
            readings: port.readings,
            shell,
            ids: IdSource::new(),
        }
    }

    /// One frame's logic (DD-APP-022), in this order: the frame-time note;
    /// the drain of the event channel, then of the reading channel, into
    /// the model; the close step, whose commands are sent; the viewport
    /// commands (`CancelClose` or `Close`, then `Minimized(false)` and
    /// `Focus` to bring the window forward) and the repaint deadline.
    pub fn logic(&mut self, input: LogicInput, clock: Clock) -> LogicOutput {
        if let Some(took) = input.frame_time {
            note(&frametime::frame_note(took));
        }
        loop {
            match self.events.try_recv() {
                Ok(event) => self.model.apply(event, clock.now),
                Err(mpsc::error::TryRecvError::Empty) => break,
                Err(mpsc::error::TryRecvError::Disconnected) => {
                    // The worker is gone (DD-APP-022): noticed once, and not
                    // after `on_exit`, which ends the worker on purpose.
                    let noticed = self.model.fatal.as_deref() == Some(texts::WORKER_STOPPED);
                    if self.commands.is_some() && !noticed {
                        log::error!(target: LOG_TARGET, "{}", texts::WORKER_STOPPED);
                        self.model.worker_stopped();
                    }
                    break;
                }
            }
        }
        while let Ok(reading) = self.readings.try_recv() {
            note(&frametime::reading_note(reading.reading.at, clock.now));
            self.model.apply(reading, clock.now);
        }
        let (step, commands, bring_forward) = actions::close_step(
            &mut self.model,
            input.close_requested,
            clock.now,
            &mut self.ids,
        );
        self.send(commands, clock.now);
        let mut viewport = match step {
            CloseStep::Nothing => Vec::new(),
            CloseStep::CancelClose => vec![ViewportCommand::CancelClose],
            CloseStep::CloseNow => vec![ViewportCommand::Close],
        };
        if bring_forward {
            viewport.push(ViewportCommand::Minimized(false));
            viewport.push(ViewportCommand::Focus);
        }
        LogicOutput {
            commands: viewport,
            repaint_after: self.model.repaint_after(clock.now),
        }
    }

    /// Runs the actions of a frame in order and sends their commands.
    pub fn dispatch(&mut self, actions: Vec<UiAction>, clock: Clock) {
        for action in actions {
            let commands = actions::handle(&mut self.model, action, clock, &mut self.ids);
            self.send(commands, clock.now);
        }
    }

    /// The model, for drawing.
    #[must_use]
    pub fn model(&self) -> &Model {
        &self.model
    }

    /// Drops the command sender, so that the worker takes the exit of
    /// DD-APP-006, and shuts the shell down within [`SHUTDOWN_BOUND`];
    /// `None` without a shell. The one place where the UI thread waits.
    pub fn on_exit(&mut self) -> Option<ShutdownReport> {
        self.commands = None;
        let report = self
            .shell
            .take()
            .map(|shell| shell.shutdown(SHUTDOWN_BOUND));
        log::info!(target: LOG_TARGET, "exit: {report:?}");
        report
    }

    /// Sends `commands`; a closed channel is logged at ERROR and raises the
    /// `Error` banner [`texts::WORKER_STOPPED`].
    fn send(&mut self, commands: Vec<Command>, now: Instant) {
        for command in commands {
            let sent = self
                .commands
                .as_ref()
                .is_some_and(|tx| tx.send(command.clone()).is_ok());
            if !sent {
                log::error!(
                    target: LOG_TARGET,
                    "{} ({command:?} not sent)",
                    texts::WORKER_STOPPED
                );
                self.model.command_not_sent(now);
            }
        }
    }
}

/// Logs `note` under the frames target (DD-APP-032).
fn note(note: &frametime::Note) {
    log::log!(target: frametime::LOG_TARGET, note.level, "{}", note.text);
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::model::{BannerKind, Kind, Phase, PromptKind};
    use crate::testkit::{
        at_s, capture_log, clock_s, connected_model, found_a, found_b, info, logged_here, r, t0,
    };
    use crate::worker::What;
    use mp305_core::session::texts::{ALLOW_REMOTE_CONTROL, CONFIRM_CONNECTION};
    use mp305_core::session::SessionEvent;

    /// The test's ends of the channels.
    struct Ends {
        /// Commands the core sent.
        commands: mpsc::UnboundedReceiver<Command>,
        /// Events to the core.
        events: mpsc::UnboundedSender<AppEvent>,
        /// Readings to the core.
        readings: mpsc::Sender<UiReading>,
    }

    /// A core around fresh channels with `model`.
    fn core(model: Model) -> (AppCore, Ends) {
        let (commands, command_rx) = mpsc::unbounded_channel();
        let (event_tx, events) = mpsc::unbounded_channel();
        let (reading_tx, readings) = mpsc::channel(16);
        let port = Port {
            commands,
            events,
            readings,
        };
        (
            AppCore::with_port(port, None, model),
            Ends {
                commands: command_rx,
                events: event_tx,
                readings: reading_tx,
            },
        )
    }

    /// The input of a frame.
    fn input(close_requested: bool, frame_time: Option<Duration>) -> LogicInput {
        LogicInput {
            close_requested,
            frame_time,
        }
    }

    /// Every command sent so far.
    fn sent(ends: &mut Ends) -> Vec<Command> {
        std::iter::from_fn(|| ends.commands.try_recv().ok()).collect()
    }

    /// Test: UT-APP-018
    #[test]
    fn a_frame_drains_decides_the_close_and_dispatches() {
        let mut model = Model::new(PathBuf::from("/rec"), t0());
        model.found = vec![found_a(), found_b()];
        let (mut core, mut ends) = core(model);
        core.dispatch(
            vec![UiAction::Select("A".into()), UiAction::Connect],
            clock_s(0.0),
        );
        assert!(matches!(
            sent(&mut ends).as_slice(),
            [Command::Connect { .. }]
        ));
        for event in [
            AppEvent::Connecting {
                sid: 1,
                identifier: "A".into(),
            },
            AppEvent::Session {
                sid: 1,
                event: SessionEvent::Prompt {
                    kind: PromptKind::ConfirmConnection,
                    bound_s: 30,
                    text: CONFIRM_CONNECTION,
                },
            },
            AppEvent::Ready {
                sid: 1,
                info: info(),
                reading: None,
                transport: Some(Kind::Ble),
            },
        ] {
            ends.events.send(event).unwrap();
        }
        let first = r(1, 0, 0, 1300, 1000, crate::testkit::at_s(0.0));
        ends.readings
            .try_send(UiReading {
                sid: 1,
                reading: first,
            })
            .unwrap();
        let out = core.logic(input(false, Some(Duration::from_millis(16))), clock_s(0.05));
        assert_eq!(core.model().phase, Phase::Connected);
        assert_eq!(core.model().reading, Some(first));
        assert_eq!(core.model().prompt, None);
        assert_eq!(
            out,
            LogicOutput {
                commands: vec![],
                repaint_after: None
            }
        );

        // (b) The window's close with the output on.
        let out = core.logic(input(true, None), clock_s(0.1));
        assert_eq!(
            out,
            LogicOutput {
                commands: vec![
                    ViewportCommand::CancelClose,
                    ViewportCommand::Minimized(false),
                    ViewportCommand::Focus
                ],
                repaint_after: Some(Duration::from_secs(1))
            }
        );
        assert!(sent(&mut ends).is_empty());
        core.dispatch(
            vec![UiAction::CloseAnswer(actions::CloseChoice::SwitchOff)],
            clock_s(0.2),
        );
        assert!(matches!(
            sent(&mut ends).as_slice(),
            [Command::Disconnect {
                output_off: true,
                ..
            }]
        ));
        let out = core.logic(input(false, None), clock_s(1.2));
        assert_eq!(
            out,
            LogicOutput {
                commands: vec![],
                repaint_after: Some(Duration::from_secs(4))
            }
        );
        ends.events
            .send(AppEvent::Disconnected {
                sid: Some(1),
                text: None,
                off_requested: true,
                output_on: Some(false),
            })
            .unwrap();
        let out = core.logic(input(false, None), clock_s(1.3));
        assert_eq!(out.commands, vec![ViewportCommand::Close]);
        let out = core.logic(input(true, None), clock_s(1.31));
        assert!(out.commands.is_empty());
    }

    /// Test: UT-APP-018
    #[test]
    fn an_output_off_is_sent_and_its_answer_logged() {
        let (mut core, mut ends) = core(connected_model());
        core.dispatch(vec![UiAction::OutputOff], clock_s(2.0));
        let commands = sent(&mut ends);
        let [Command::OutputOff { id }] = commands.as_slice() else {
            panic!("{commands:?}");
        };
        ends.events
            .send(AppEvent::Done {
                id: *id,
                what: What::OutputOff,
                result: Ok(()),
            })
            .unwrap();
        core.logic(input(false, None), clock_s(2.143));
        assert!(core
            .model()
            .log
            .iter()
            .any(|l| l.ends_with("output off acknowledged after 143 ms")));
    }

    /// Test: UT-APP-018
    #[test]
    fn a_stopped_worker_raises_a_banner() {
        let (mut core, ends) = core(Model::new(PathBuf::from("/rec"), t0()));
        drop(ends.commands);
        core.dispatch(vec![UiAction::Scan], clock_s(0.0));
        assert!(core
            .model()
            .banners
            .iter()
            .any(|b| b.kind == BannerKind::Error
                && b.text
                    == "The app's worker has stopped and the supply is no longer controlled. \
                        The output is left in its last state: switch it off on the supply if \
                        needed, then restart the app."));
    }

    /// Test: UT-APP-018
    #[test]
    fn a_failed_start_is_fatal_and_the_exit_finishes() {
        let build: BoxFuture<'static, Result<Deps, String>> =
            Box::pin(async { Err("the OS reports no home directory".to_string()) });
        let wake: Wake = std::sync::Arc::new(|| {});
        let mut core = AppCore::start(build, wake, PathBuf::from("/rec")).unwrap();
        let started = std::time::Instant::now();
        while core.model().fatal.is_none() {
            assert!(
                started.elapsed() < Duration::from_secs(1),
                "no Fatal in time"
            );
            std::thread::sleep(Duration::from_millis(5));
            core.logic(input(false, None), Clock::now());
        }
        assert_eq!(core.on_exit(), Some(ShutdownReport::Finished));
    }

    /// The ERROR lines of this thread that carry `texts::WORKER_STOPPED`.
    fn worker_stopped_lines() -> usize {
        logged_here(log::Level::Error)
            .iter()
            .filter(|l| l.contains(texts::WORKER_STOPPED))
            .count()
    }

    /// Whether a close request led to the window's close: DD-APP-021 gives
    /// `Nothing` with `close_committed` for a request in `Idle`, so the
    /// request is not cancelled and eframe closes the window. UT-APP-028
    /// writes this outcome as `[Close]`; the design's form is checked.
    fn window_closes(out: &LogicOutput, core: &AppCore) -> bool {
        !out.commands.contains(&ViewportCommand::CancelClose) && core.model().close_committed
    }

    /// Test: UT-APP-028
    #[test]
    fn a_closed_event_channel_stops_the_app_once() {
        capture_log();
        let (mut core, ends) = core(connected_model());
        drop(ends.events);
        core.logic(input(false, None), clock_s(10.0));
        let model = core.model();
        assert_eq!(model.fatal.as_deref(), Some(texts::WORKER_STOPPED));
        assert_eq!(model.phase, Phase::Idle);
        let first = &model.banners_to_show(at_s(10.0))[0];
        assert_eq!(first.text, texts::WORKER_STOPPED);
        assert!(!first.dismissible);
        assert_eq!(worker_stopped_lines(), 1);
        core.logic(input(false, None), clock_s(10.5));
        assert_eq!(worker_stopped_lines(), 1);
        let out = core.logic(input(true, None), clock_s(11.0));
        assert!(window_closes(&out, &core), "{out:?}");
    }

    /// Test: UT-APP-028
    #[test]
    fn a_stopped_worker_keeps_a_waiting_close_from_completing() {
        let (mut core, ends) = core(connected_model());
        // The reading is 10 s old: the close request asks first.
        let out = core.logic(input(true, None), clock_s(10.0));
        assert_eq!(out.commands.first(), Some(&ViewportCommand::CancelClose));
        core.dispatch(
            vec![UiAction::CloseAnswer(actions::CloseChoice::SwitchOff)],
            clock_s(10.1),
        );
        assert_eq!(core.model().phase, Phase::Closing);
        assert!(core.model().close_pending && core.model().off_requested);
        ends.events
            .send(AppEvent::Session {
                sid: 1,
                event: SessionEvent::Prompt {
                    kind: PromptKind::AllowRemoteControl,
                    bound_s: 70,
                    text: ALLOW_REMOTE_CONTROL,
                },
            })
            .unwrap();
        core.logic(input(false, None), clock_s(10.2));
        assert!(core.model().prompt.is_some());
        drop(ends.events);
        let out = core.logic(input(false, None), clock_s(10.3));
        assert_eq!(core.model().phase, Phase::Idle);
        assert_eq!(core.model().prompt, None);
        assert!(!core.model().close_pending);
        assert!(out.commands.is_empty());
        let out = core.logic(input(false, None), clock_s(20.3));
        assert!(out.commands.is_empty());
        let out = core.logic(input(true, None), clock_s(20.4));
        assert!(window_closes(&out, &core), "{out:?}");
    }

    /// Test: UT-APP-028
    #[test]
    fn no_stopped_worker_after_the_exit() {
        let (mut core, ends) = core(connected_model());
        assert_eq!(core.on_exit(), None);
        drop(ends.events);
        core.logic(input(false, None), clock_s(1.0));
        assert_eq!(core.model().fatal, None);
        assert_eq!(core.model().phase, Phase::Connected);
    }
}
