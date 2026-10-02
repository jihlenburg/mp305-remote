//! Implements: DD-APP-030 (the thin binary), DD-APP-040 (no console window
//! on Windows), DD-APP-050 (the crate root's lints).
//!
//! Coverage: excluded from the measurement; it only calls
//! `mp305_app::ui::launch` (ADR-0008; app DD, section 8, decision 9).
//! UT-APP-020 and UT-APP-021 inspect it instead.
//!
//! Entry point of the desktop app. All logic lives in the library crate.
//! Release builds on Windows open no console window; the log then goes to
//! `MP305_LOG_FILE` (DD-APP-033).

#![forbid(unsafe_code)]
#![deny(missing_docs)]
#![warn(clippy::missing_docs_in_private_items)]
#![deny(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::panic,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects
)]
#![cfg_attr(all(windows, not(debug_assertions)), windows_subsystem = "windows")]

use std::process::ExitCode;

/// Starts the app.
fn main() -> ExitCode {
    mp305_app::ui::launch()
}
