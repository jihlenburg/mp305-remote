//! `mp305-core`: the device protocol, the transports and the device API of
//! the ISDT MP305B remote control, shared by the desktop app and the Python
//! library. The crate performs no device I/O of its own; every byte to or
//! from a supply goes through the `transport` layer.
//!
//! Implements: AR-001, AR-002, AR-004.

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

pub mod error;
pub mod protocol;
pub mod transport;
