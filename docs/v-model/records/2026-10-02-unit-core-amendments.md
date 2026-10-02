# Verification record: unit tests after the amendments of 2026-10-02 (discovery revision 4, session revision 6, store revision 4)

Date: 2026-10-02. Level: unit (UT-DISC, UT-SESS, UT-STORE). Scope:
`mp305-core` after the design revisions the user approved on 2026-10-02:
discovery.md revision 4 (a scan whose enabled transports all lack a
backend fails, DD-DISC-010, UT-DISC-009 (2); the adapter state change,
DD-DISC-012), session.md revision 6 and store.md revision 4, which state
what the code already did (DD-SESS-035, DD-SESS-053, UT-SESS-044 (5),
UT-STORE-011).

Commit: `9acf5d4` (the run was made on the tree that this commit holds). Diff summary: `crates/mp305-core/src/discovery/mod.rs`
(`scan` returns `Error::Transport` when Bluetooth is the only enabled
transport and there is no adapter; the UT-DISC-009 test for it, changed
first and seen to fail); `traceability.md`; this record; TODO.md;
LOGBOOK.md. No change in `session/` or `store/`. Written and run in the
main session.

OS: macOS 27.0 (Darwin 27.0.0), Apple arm64. Rust 1.98.1 (Homebrew),
clippy 0.1.98, cargo-llvm-cov 0.9.1 with the Homebrew LLVM 22 tools.
Transport: none and the mock. Firmware: not applicable.

## Commands

```sh
cargo fmt --all --check
cargo clippy --workspace --all-targets -- -D warnings
cargo clippy -p mp305-core --all-targets -- -D warnings
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
| `cargo test --workspace` | pass: 269 in-crate, 5 + 1 external, 14 doctests (289) |
| `cargo doc` with `-D warnings` | pass |
| `check_traceability.py --check` | no defects, matrix current |

Line coverage: `discovery/mod.rs` 85.11 %, `discovery/classify.rs`
99.64 %, `mp305-core` TOTAL 95.31 % (target 85 %).

| UT | Result | Note |
|---|---|---|
| UT-DISC-009 | pass (3 tests) | case (2) now expects the error for a Bluetooth-only scan without an adapter, and an empty list with no transport enabled |
| UT-DISC-010 | pass by inspection, unchanged | DD-DISC-012 now states what the glue does with an adapter state change (note 1 of the record of 2026-10-01 is closed) |
| UT-SESS-044 | pass (16 tests) | the entry's case (5) now says "never `Ready`", which is what its test does |
| UT-STORE-011 | pass (2 tests, 1 doctest) | the entry now lists the planted-marker step its test makes |
| every other entry of `mp305-core` | pass (rerun, unchanged) | |

With these revisions the open points 1 and 3 of the discovery record, 1,
3 and 4 of the session revision 5 record and the UT-STORE-011 point of
the core additions record are closed.
