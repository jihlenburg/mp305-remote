# Verification record: unit and integration tests on Linux

Date: 2026-10-02. Level: unit and integration (every UT and IT entry
with an automated test, and the system tests that need no supply). Scope:
the whole workspace and the Python library, built and run on Linux for
the first time; before, only macOS arm64 had been built.

Commit: `700e1cf`. The run was made on a clone of the public repository
at that commit in the VM. Two findings of the first two attempts were
fixed in the commits `ff63181` and `700e1cf` (below).

OS: Ubuntu 24.04.5 LTS, Linux 6.17.0-22-generic, aarch64, a Parallels VM
on the user's Mac (4 cores, 7 GB). Rust 1.99.0 (rustup), clippy 0.1.99;
CPython 3.10.22 through uv 0.12.22 (the system's 3.12.3 for the binding
crate's Rust tests), pytest 9.1.1. Packages installed for the build:
`pkg-config`, `libdbus-1-dev`, `libudev-dev`, `python3-dev` and the
libraries the GUI stack links against (`libxkbcommon-dev`,
`libwayland-dev`, `libx11-dev`, the `libxcb` development packages,
`libgl1-mesa-dev`, `libssl-dev`, `libfontconfig1-dev`). Transport: the
mock. No Bluetooth adapter was attached to the VM, no scan was started
and no device was opened. Firmware: not applicable.

## Commands

```sh
cargo fmt --all --check
cargo clippy --workspace --all-targets -- -D warnings
cargo clippy -p mp305-core --all-targets -- -D warnings
cargo test --workspace
RUSTDOCFLAGS="-D warnings" cargo doc --workspace --no-deps
cargo build --release -p mp305-app
uv run maturin develop -m crates/mp305-py/Cargo.toml
uv run --no-sync pytest
uv run --no-sync ruff check
uv run --no-sync mypy python/mp305
python3 scripts/check_traceability.py --check
```

## Results

| Gate | Result |
|---|---|
| `cargo fmt --all --check` | pass |
| `cargo clippy --workspace --all-targets -- -D warnings` | pass (after the two fixes) |
| `cargo clippy -p mp305-core --all-targets -- -D warnings` | pass (after the first fix) |
| `cargo test --workspace` | pass: 522 tests, the same counts as on macOS |
| `cargo doc` with `-D warnings` | pass |
| `cargo build --release -p mp305-app` | pass (the binary was not run) |
| `maturin develop` | pass |
| `pytest` | pass: 201 tests (128 unit, 54 integration, 19 system without a supply); ST-037 skipped as on macOS; the 52 HIL tests deselected |
| `ruff check`, `mypy` | pass |
| `check_traceability.py --check` | no defects, matrix current |

Every UT, IT and supply-free ST test that passes on macOS passes on
Linux aarch64. Coverage was not measured in the VM.

## Findings

1. Rust 1.99 deprecates `Atomic*::fetch_update` in favour of
   `try_update`, so both clippy gates failed there, and with them the
   Python test of UT-PY-020 that runs clippy on the binding crate. The
   crate's minimum Rust version (1.85) has no `try_update`, so the three
   saturating counters (link, session, mock) keep `fetch_update` under a
   commented `allow(deprecated)` (commit `ff63181`). No behaviour changed.
2. clippy 1.99 rejects a bare `#[must_use]` on `worker::real_deps`, which
   returns a boxed future that is must-use itself; the attribute was
   removed (commit `700e1cf`).

Both findings come from the compiler version (the Mac has 1.98.1), not
from Linux.

## Not covered

- Nothing on the supply: the discovery and the transports on BlueZ and
  hidraw are untested apart from the scan of the spike `vm_dongle_scan`.
- The app was built, not run. No x86_64 build, no wheel build, no
  Windows.
- The VM had a kernel and libc upgrade pending a reboot when the run was
  made; it ran on the kernel named above.
