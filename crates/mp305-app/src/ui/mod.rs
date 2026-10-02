//! Implements: DD-APP-030 (the eframe glue), DD-APP-031 (the screens'
//! module tree).
//!
//! Coverage: excluded from the measurement as GUI drawing code and eframe
//! glue that decides nothing (ADR-0008; app DD, section 8, decision 9);
//! UT-APP-020 inspects this directory instead.
//!
//! [`App`] implements `eframe::App` over [`AppCore`]: `logic` hands the
//! close request and the frame time to the core and carries out what it
//! returns, `ui` draws the model and passes the clicks back, `on_exit`
//! runs the core's exit. Every rule lives in the tested modules.

mod chart;
mod connect;
mod dialogs;
pub mod launch;
mod panel;
mod screens;
mod status;

pub use launch::launch;

use eframe::egui;

use crate::actions::Clock;
use crate::app::{AppCore, LogicInput};
use crate::frametime;

/// The eframe app: the glue between eframe and [`AppCore`].
pub struct App {
    /// The frame logic and the dispatch.
    core: AppCore,
}

impl App {
    /// The app over `core`.
    #[must_use]
    pub fn new(core: AppCore) -> App {
        App { core }
    }
}

impl eframe::App for App {
    fn logic(&mut self, ctx: &egui::Context, frame: &mut eframe::Frame) {
        let input = LogicInput {
            close_requested: ctx.input(|i| i.viewport().close_requested()),
            frame_time: frametime::frame_time_from(frame.info().cpu_usage),
        };
        let output = self.core.logic(input, Clock::now());
        for command in output.commands {
            ctx.send_viewport_cmd(command);
        }
        if let Some(after) = output.repaint_after {
            ctx.request_repaint_after(after);
        }
    }

    fn ui(&mut self, ui: &mut egui::Ui, _frame: &mut eframe::Frame) {
        let actions = screens::show(ui, self.core.model(), Clock::now().now);
        self.core.dispatch(actions, Clock::now());
    }

    fn on_exit(&mut self) {
        let _ = self.core.on_exit();
    }
}
