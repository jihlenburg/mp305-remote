//! Implements: DD-APP-050 (the crate root and its lints), DD-APP-030 (the
//! split between the tested modules and `ui/`).
//!
//! The logic of the desktop app `mp305-app`; the binary in `main.rs` only
//! calls [`ui::launch()`]. A worker task on a Tokio runtime owns the session
//! and does all device I/O (`worker`, `shell`), a recorder thread does all
//! file writes (`recording`), and the UI thread holds a [`model::Model`] of
//! what to show, drains the worker's events once per frame, draws, and
//! turns clicks into commands (`app`, `actions`). Every rule about what a
//! click may send, when the window may close and what the user is told
//! lives in the tested modules; `ui/` holds the drawing functions and the
//! eframe glue, which decide nothing. Every module is public, so that the
//! integration test IT-041 reaches `worker`, `model` and `chart`.

#![forbid(unsafe_code)]
#![cfg_attr(
    test,
    allow(
        clippy::unwrap_used,
        clippy::expect_used,
        clippy::panic,
        clippy::indexing_slicing,
        clippy::arithmetic_side_effects
    )
)]

pub mod actions;
pub mod app;
pub mod chart;
pub mod fields;
pub mod frametime;
pub mod logging;
pub mod model;
pub mod paths;
pub mod recording;
pub mod shell;
#[cfg(test)]
mod testkit;
pub mod texts;
pub mod ui;
pub mod worker;
