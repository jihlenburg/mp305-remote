//! Implements: DD-APP-040 (the Windows executable icon).
//!
//! Compiles the native icon resource only for Windows targets. Resource
//! errors fail the build; no device code or runtime dependency is involved.

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

/// Embeds the icon using the target's resource compiler, propagating errors.
fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("cargo:rerun-if-changed=build.rs");
    println!("cargo:rerun-if-changed=Cargo.toml");
    println!("cargo:rerun-if-changed=../../Cargo.toml");
    println!("cargo:rerun-if-changed=assets/icons/mp305.ico");
    if std::env::var("CARGO_CFG_TARGET_OS")? == "windows" {
        winresource::WindowsResource::new()
            .set_icon("assets/icons/mp305.ico")
            .set("ProductName", "MP305 Remote")
            .set("OriginalFilename", "mp305-app.exe")
            .compile()?;
    }
    Ok(())
}
