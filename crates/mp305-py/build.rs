//! Implements: DD-PY-063
//!
//! The build script of `mp305-py`. It adds the run-time search path of
//! `libpython` to the link of the crate's own Rust test binary, so that plain
//! `cargo test`, `cargo clippy` and `cargo llvm-cov` find the interpreter
//! PyO3 picked. PyO3 emits nothing when maturin sets
//! `PYO3_BUILD_EXTENSION_MODULE`, so a wheel does not link `libpython`.

fn main() {
    pyo3_build_config::add_libpython_rpath_link_args();
}
