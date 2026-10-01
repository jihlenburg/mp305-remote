# Verification record: unit tests of the store module

Date: 2026-10-01. Level: unit (UT-STORE). Scope: `mp305-core`, module
`store`, implemented from docs/v-model/4-detailed-design/store.md revision
2 (tag `g4-store-approved`).

Commit: `uncommitted`. Diff summary: new `crates/mp305-core/src/store/`
(`mod.rs`, `names.rs`, `files.rs`); `lib.rs` (`pub mod store`);
`crates/mp305-core/Cargo.toml` (`getrandom` 0.4, dev dependency `tempfile`
3; both were already in `Cargo.lock`, which gains two dependency lines);
`traceability.md`; this record; TODO.md; LOGBOOK.md. Written test first by
a delegated agent in an isolated worktree; the gates below were run again
in the main session after the change was applied to the main tree.

OS: macOS 27.0 (Darwin 27.0.0), Apple arm64 (APFS). Rust 1.98.1
(Homebrew), clippy 0.1.98, cargo-llvm-cov 0.9.1 with the Homebrew LLVM 22
tools; getrandom 0.4.3, tempfile 3.27.0. Transport: none. Firmware: not
applicable.

## Commands

```sh
cargo fmt --all --check
cargo clippy --workspace --all-targets -- -D warnings
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
| `cargo test --workspace` | pass: 243 in-crate, 5 + 1 external, 10 doctests (259) |
| `cargo doc` with `-D warnings` | pass |
| `check_traceability.py --check` | no defects, matrix current |

Line coverage: `store/names.rs` 100.00 %, `store/files.rs` 95.87 %,
`store/mod.rs` 94.79 %, `mp305-core` TOTAL 95.74 % (target 85 %). The
uncovered production lines are error paths no test entry produces (a
random-source failure inside `host_id`, a corrupt file found by
`create_or_adopt`, the log line of a failed marker removal, the I/O error
of `clear`).

| UT | Result | Tests |
|---|---|---|
| UT-STORE-001 | pass | 1 |
| UT-STORE-002 | pass (cases a to f) | 1 |
| UT-STORE-003 | pass (the permission case ran; it was not skipped) | 2 |
| UT-STORE-004 | pass | 1 |
| UT-STORE-005 | pass (plus an unreadable-marker case, see deviations) | 2 |
| UT-STORE-006 | pass | 1 |
| UT-STORE-007 | pass | 2 |
| UT-STORE-008 | pass | 1 |
| UT-STORE-009 | pass | 1 |
| UT-STORE-010 | pass (plus the `create_new` fallback, see deviations) | 4 |

Run on APFS only; the hard-link path on ext4 and NTFS and the `create_new`
fallback on file systems without hard links are covered by the unit test
of the fallback seam, not by a run on those file systems.

## Deviations and open points

- Two tests go beyond the listed inputs: the `create_new` fallback of
  DD-STORE-003 (tagged UT-STORE-010) and `present` on an unreadable marker
  (tagged UT-STORE-005). The entries are to be amended with the user's
  approval.
- Identifiers that cannot round-trip: one with leading or trailing ASCII
  whitespace is reported as `identifier mismatch`, and an empty one or one
  containing a line break as `malformed`. Bluetooth identifiers and HID
  paths are not affected. The DD is to say what the store does with such
  an identifier.
- Texts the DD does not give: WARN `marker not removed <path>: <os error>`
  when a removal fails; `random source: <text>` and `random source: 3
  values rejected`, prefixed with the `host_id` path.
- A marker line may end in `\r` (a file edited on Windows still parses).
- A failed write after the fallback created the file leaves a partial
  `host_id`; the next read treats it as corrupt and replaces it.
