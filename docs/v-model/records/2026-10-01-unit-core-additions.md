# Verification record: unit tests of the core additions (store revision 3, csv revision 3, protocol revision 6)

Date: 2026-10-01. Level: unit (UT-STORE, UT-CSV, UT-PROTO). Scope:
`mp305-core`, the changes the user approved on 2026-10-01: the identifier
rule of the store (store.md revision 3, DD-STORE-004, UT-STORE-011), the
two mode cases of UT-CSV-003 (csv.md revision 3), and from protocol.md
revision 6 `telemetry::parse_payload` (DD-PROTO-025, UT-PROTO-024),
`timing::WAIT_SLICE` (DD-PROTO-060, UT-PROTO-060) and the test support
functions `fixtures::reply_route` and `fixtures::on_air`. Also the
workspace release profile `strip = "none"` (ADR-0015).

Commit: `ccdcd2f` (the run was made on the tree that this commit holds). Diff summary: `Cargo.toml` (release profile);
`crates/mp305-core/src/store/names.rs` (`storable`) and `store/mod.rs`
(`set`, `present`, `clear`); `csv.rs` (test only); `protocol/ops/mod.rs`
(`expect_reply` split into `expect_opcode` and `expect_len`),
`protocol/ops/telemetry.rs` (`parse_payload`), `protocol/timing.rs`
(`WAIT_SLICE`), `protocol/fixtures.rs` (`reply_route`, `on_air`),
`protocol/ble.rs` (`AF01_TAG` visible in the crate); `traceability.md`;
this record; TODO.md; LOGBOOK.md. Written test first by a delegated agent
in an isolated worktree; the diff was read and the gates below were run in
the main session on that worktree, whose tree is the one this commit
holds.

OS: macOS 27.0 (Darwin 27.0.0), Apple arm64 (APFS). Rust 1.98.1
(Homebrew), clippy 0.1.98, cargo-llvm-cov 0.9.1 with the Homebrew LLVM 22
tools. Transport: none. Firmware: not applicable.

## Commands

```sh
cargo fmt --all --check
cargo clippy --workspace --all-targets -- -D warnings
cargo clippy -p mp305-core --all-targets -- -D warnings
cargo clippy -p mp305-core --features mock -- -D warnings
cargo test --workspace
RUSTDOCFLAGS="-D warnings" cargo doc --workspace --no-deps
LLVM_COV=/opt/homebrew/opt/llvm@22/bin/llvm-cov \
LLVM_PROFDATA=/opt/homebrew/opt/llvm@22/bin/llvm-profdata \
  cargo llvm-cov -p mp305-core --summary-only --ignore-filename-regex '(transport|discovery)/(ble|hid)\.rs'
python3 scripts/check_traceability.py --check
```

## Results

| Gate | Result |
|---|---|
| `cargo fmt --all --check` | pass |
| `cargo clippy --workspace --all-targets -- -D warnings` | pass |
| `cargo clippy -p mp305-core --all-targets -- -D warnings` | pass |
| `cargo clippy -p mp305-core --features mock -- -D warnings` | pass |
| `cargo test --workspace` | pass: 257 in-crate, 5 + 1 external, 14 doctests (277) |
| `cargo doc` with `-D warnings` | pass |
| `check_traceability.py --check` | no defects, matrix current |

Line coverage: `store/names.rs` 100.00 %, `store/mod.rs` 94.93 %,
`csv.rs` 100.00 %, `protocol/ops/telemetry.rs` 100.00 %,
`protocol/timing.rs` 100.00 %, `protocol/fixtures.rs` 58.97 %,
`mp305-core` TOTAL 95.09 % (target 85 %).

| UT | Result | Tests |
|---|---|---|
| UT-STORE-011 | pass | 2 tests, 1 doctest |
| UT-STORE-001 to UT-STORE-010 | pass (rerun, unchanged) | 16 |
| UT-CSV-003 | pass (now with the `cv` and `held_above` rows) | 1 |
| UT-PROTO-024 | pass (now with the three `parse_payload` cases) | 5 |
| UT-PROTO-060 | pass (now with `WAIT_SLICE`) | 2 |

## Deviations and open points

- `fixtures::reply_route` and `fixtures::on_air` are test support without
  a test entry of their own, and no test calls them yet, which is why
  `protocol/fixtures.rs` stands at 59 % and the total fell from 95.46 %
  to 95.09 %. The session tests hold private copies with the same
  behaviour and switch to these functions with the session revision 5
  implementation (TODO.md), which brings the lines under test.
- The UT-STORE-011 test makes one check beyond the entry's listed steps:
  it plants a marker file for `" a"` that would read back as valid and
  checks that `present` gives `None` and `clear` leaves the file in
  place. This is what shows DD-STORE-004's "without touching a file"; the
  entry is to gain the step with the user's approval.
- `fixtures::on_air` over USB with a payload longer than 254 bytes
  saturates the length byte at 255 and the stream is then not a valid
  frame. No real frame is that long; the function documents it.
- `ops::expect_reply` was split into `expect_opcode` and `expect_len`
  (crate-private) so that `parse` and `parse_payload` share the checks;
  its behaviour is unchanged.
