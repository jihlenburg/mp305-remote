# Verification record: unit tests of the protocol module

Date: 2026-09-30. Level: unit (UT-PROTO). Scope: `mp305-core`, module
`protocol`, implemented from docs/v-model/4-detailed-design/protocol.md
revision 2 (tag `g4-protocol-approved`).

Commit: uncommitted at the time of the run. Diff summary: new files
`Cargo.toml`, `crates/mp305-core/**`, `crates/mp305-app/**`,
`crates/mp305-py/**` (workspace skeleton and the protocol module), this
record, TODO.md, LOGBOOK.md, AGENTS.md (commands). The commit hash is added
to the LOGBOOK entry once the user permits the commit.

OS: macOS 27.0 (Darwin 27.0.0), Apple arm64. Rust 1.98.1 (Homebrew), clippy
0.1.98, cargo-llvm-cov 0.9.1 with the Homebrew LLVM 22 tools. Transport:
none (no device). Firmware: not applicable, no hardware run.

## Commands

```sh
cargo fmt --all --check
cargo clippy --workspace --all-targets -- -D warnings
cargo test --workspace
cargo doc --workspace --no-deps
LLVM_COV=/opt/homebrew/opt/llvm@22/bin/llvm-cov \
LLVM_PROFDATA=/opt/homebrew/opt/llvm@22/bin/llvm-profdata \
  cargo llvm-cov -p mp305-core --summary-only
python3 scripts/check_traceability.py --check
```

All commands passed: fmt clean, clippy clean with `-D warnings`, 47 unit
tests and 3 doctests passed (0 failed, 0 ignored), docs built without
warnings, traceability reports no defects.

## Coverage (line, `cargo llvm-cov`)

| File | Lines |
|---|---|
| protocol/ble.rs | 100.00% |
| protocol/error.rs | 100.00% |
| protocol/frame.rs | 100.00% |
| protocol/hid.rs | 97.06% |
| protocol/ops/bind.rs | 94.44% |
| protocol/ops/control.rs | 99.24% |
| protocol/ops/events.rs | 100.00% |
| protocol/ops/info.rs | 100.00% |
| protocol/ops/mod.rs | 100.00% |
| protocol/ops/settings.rs | 100.00% |
| protocol/ops/telemetry.rs | 93.03% |
| protocol/policy.rs | 100.00% |
| protocol/props.rs | 100.00% |
| protocol/timing.rs | 100.00% |
| protocol/units.rs | 100.00% |
| TOTAL | 97.62% |

The protocol module's target is 95 % (ADR-0008); the module is at 97.62 %.
`protocol/props.rs` holds the in-crate property tests.

## Results per test specification entry

| UT | Result | Test |
|---|---|---|
| UT-PROTO-001 | pass | `frame.rs` (3 tests) |
| UT-PROTO-002 | pass | `ble.rs` (3 tests), `ops/mod.rs` (1 test) |
| UT-PROTO-003 | pass | `props.rs`, 512 cases |
| UT-PROTO-004 | pass | `error.rs`, `error.rs` (crate), and the length checks of every parser test |
| UT-PROTO-010 | pass | `hid.rs` |
| UT-PROTO-011 | pass | `hid.rs` |
| UT-PROTO-012 | pass | `hid.rs`, 41 splits |
| UT-PROTO-013 | pass | `hid.rs` (6 tests) |
| UT-PROTO-014 | pass | `props.rs`, 512 cases |
| UT-PROTO-020 | pass | `ops/bind.rs` (3 tests) |
| UT-PROTO-021 | pass | `ops/bind.rs` |
| UT-PROTO-022 | pass | `ops/info.rs` (4 tests) |
| UT-PROTO-024 | pass | `ops/telemetry.rs` (3 tests) |
| UT-PROTO-025 | pass | `ops/telemetry.rs` |
| UT-PROTO-026 | pass | `ops/telemetry.rs` |
| UT-PROTO-027 | pass | `ops/control.rs` (2 tests) |
| UT-PROTO-028 | pass | `ops/control.rs` |
| UT-PROTO-029 | pass | `ops/control.rs`, 3 `compile_fail` doctests |
| UT-PROTO-030 | pass | `ops/settings.rs` |
| UT-PROTO-031 | pass | `ops/events.rs` |
| UT-PROTO-032 | pass | `ops/telemetry.rs` |
| UT-PROTO-033 | pass | `ops/mod.rs` |
| UT-PROTO-040 | pass | `policy.rs` (2 tests) |
| UT-PROTO-050 | pass | `units.rs` |
| UT-PROTO-051 | pass | `units.rs` (2 tests) |
| UT-PROTO-060 | pass | `timing.rs` |
| UT-PROTO-070 | pass (inspection) | `cargo doc` clean under `deny(missing_docs)`; the byte tables are in the rustdoc of `hid::Decoder`, `RawReading`, `Command`, `Info` and `Settings` with links to protocol.md; doctests pass |

## Deviations from the design

- The property tests live in `crates/mp305-core/src/protocol/props.rs`
  instead of `crates/mp305-core/tests/ut_protocol_props.rs`, because
  `Frame::new` is crate-private by design (DD-PROTO-001) and a test in
  `tests/` cannot call it. Only the test path changes (editorial).
- `RawVoltage::for_tests` and `RawCurrent::for_tests` exist under
  `#[cfg(test)]` so that UT-PROTO-027 can build raw setpoints without the
  validation of `units`; they are not compiled into the library.
- `Frame::empty` is a crate-private infallible constructor for the
  payload-less requests; it adds nothing to the public API.
