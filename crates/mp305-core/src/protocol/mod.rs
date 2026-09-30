//! The device protocol without I/O: frames, the two wire forms, the v1
//! opcodes, the opcode policy, units and the device's timing bounds.
//!
//! Implements: DD-PROTO-001 (module tree).

pub mod ble;
pub mod error;
pub mod frame;
pub mod hid;
pub mod ops;
pub mod policy;
#[cfg(test)]
mod props;
pub mod timing;
pub mod units;
