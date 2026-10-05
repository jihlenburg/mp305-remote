//! Implements: DD-APP-034, DD-APP-035, DD-APP-030 (`launch`), DD-APP-023 (the macOS menu hook),
//! DD-APP-040 (the window icon).
//!
//! Coverage: excluded from the measurement as eframe glue that decides
//! nothing (ADR-0008; app DD, section 8, decision 9); UT-APP-020 inspects
//! this file instead.
//!
//! Starts the logger and the window, and installs the fonts and the
//! style (`theme`). On macOS winit's default menu is
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
const INNER_SIZE: [f32; 2] = [900.0, 580.0];

/// The window's minimum inner size in points.
const MIN_INNER_SIZE: [f32; 2] = [320.0, 320.0];

/// Runs the app until its window closes.
#[must_use]
pub fn launch() -> ExitCode {
    logging::init();
    let icon =
        match eframe::icon_data::from_png_bytes(include_bytes!("../../assets/icons/icon.png")) {
            Ok(icon) => icon,
            Err(error) => {
                logging::launch_failed(&error);
                return ExitCode::FAILURE;
            }
        };
    #[cfg_attr(not(target_os = "linux"), allow(unused_mut))]
    let mut viewport = egui::ViewportBuilder::default()
        .with_title(label::APP_TITLE)
        .with_icon(icon)
        .with_inner_size(INNER_SIZE)
        .with_min_inner_size(MIN_INNER_SIZE);
    #[cfg(target_os = "linux")]
    {
        viewport = viewport.with_app_id("de.ihlems.mp305-remote");
    }
    #[cfg_attr(not(target_os = "macos"), allow(unused_mut))]
    let mut options = eframe::NativeOptions {
        viewport,
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
            Ok(Box::new(App::new(core, &cc.egui_ctx)))
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
