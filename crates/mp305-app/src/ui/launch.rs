//! Implements: DD-APP-030 (`launch`), DD-APP-023 (the macOS menu hook).
//!
//! Coverage: excluded from the measurement as eframe glue that decides
//! nothing (ADR-0008; app DD, section 8, decision 9); UT-APP-020 inspects
//! this file instead.
//!
//! Starts the logger and the window. On macOS winit's default menu is
//! switched off, so that no Quit item (key equivalent Cmd+Q) ends the app
//! through `terminate:` without a close request; Cmd+Q then arrives through
//! egui's default quit shortcut as a close request, which DD-APP-021
//! handles like the close button.

use std::process::ExitCode;
use std::sync::Arc;

use eframe::egui;

use crate::app::AppCore;
use crate::logging;
use crate::paths;
use crate::texts::label;
use crate::ui::App;
use crate::worker::{self, Wake};

/// The window's inner size in points.
const INNER_SIZE: [f32; 2] = [1100.0, 760.0];

/// The window's minimum inner size in points.
const MIN_INNER_SIZE: [f32; 2] = [800.0, 560.0];

/// Runs the app until its window closes.
#[must_use]
pub fn launch() -> ExitCode {
    logging::init();
    #[cfg_attr(not(target_os = "macos"), allow(unused_mut))]
    let mut options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default()
            .with_title(label::APP_TITLE)
            .with_inner_size(INNER_SIZE)
            .with_min_inner_size(MIN_INNER_SIZE),
        ..Default::default()
    };
    #[cfg(target_os = "macos")]
    {
        options.event_loop_builder = Some(Box::new(|builder| {
            use winit::platform::macos::EventLoopBuilderExtMacOS;
            builder.with_default_menu(false);
        }));
    }
    let result = eframe::run_native(
        label::APP_TITLE,
        options,
        Box::new(|cc| {
            let ctx = cc.egui_ctx.clone();
            let wake: Wake = Arc::new(move || ctx.request_repaint());
            let core = AppCore::start(worker::real_deps(), wake, paths::recording_dir())?;
            Ok(Box::new(App::new(core)))
        }),
    );
    match result {
        Ok(()) => ExitCode::SUCCESS,
        Err(e) => {
            logging::launch_failed(&e);
            ExitCode::FAILURE
        }
    }
}
