# Verification record: the bounds of ADR-0017, unit and integration level

Date: 2026-10-04. Level: unit (UT-PROTO-060, UT-LINK-025, UT-DISC-010)
and integration (IT-014). Scope: the implementation of ADR-0017 (AR-014
revision 13, protocol DD revision 8, link DD revision 4, discovery DD
revision 7).

Commit: `1cbcb09` (the run was made on the tree that this commit holds). Diff summary: `timing::CONNECT` 20 s and the new
`timing::CLOSE` 5 s; the link closes the transport under `CLOSE`; the
discovery glue awaits the cancel of a connect that expired or failed and
bounds a connect as a whole with `FIND + CONNECT + CLOSE`; the transport
stub gets a close delay; two tests for UT-LINK-025; the one-adapter note
in the two READMEs.

OS: macOS 27.0.1, arm64. Rust 1.98.1 (Homebrew), CPython 3.10.19.
Transport: none (stub and mock). No supply was involved.

## Commands

```sh
cargo fmt --all --check
cargo clippy --workspace --all-targets -- -D warnings
cargo clippy -p mp305-core --all-targets -- -D warnings
cargo test --workspace
RUSTDOCFLAGS="-D warnings" cargo doc --workspace --no-deps
env -u CONDA_PREFIX uv run maturin develop -m crates/mp305-py/Cargo.toml
uv run --no-sync pytest
uv run --no-sync ruff check
uv run --no-sync mypy python/mp305
python3 scripts/check_traceability.py --check
cargo llvm-cov --workspace --exclude mp305-py --ignore-filename-regex '(transport|discovery)/(ble|hid)\.rs|mp305-app/src/(ui/|main\.rs)' --summary-only
```

All of them pass. `cargo test --workspace`: 524 tests, none failed.
`pytest`: 201 passed, 1 skipped, 52 deselected (the tests that need a
supply). Line coverage: 95.75 % of the workspace without the binding
crate; `protocol/timing.rs` 100 %, `link/task.rs` 96.73 %,
`transport/stub.rs` 96.10 %, `discovery/mod.rs` 85.21 %.

## Results

| ID | Result | Evidence |
|---|---|---|
| UT-PROTO-060 | pass | `the_first_bounds_have_their_values`, `the_later_bounds_have_their_values` in `protocol/timing.rs`: every constant of DD-PROTO-060 asserted once, `CONNECT` 20 s and `CLOSE` 5 s among them |
| UT-LINK-025 | pass | `close_resolves_everything_and_closes_the_transport`, `dropping_the_link_ends_it`, and the two new cases `a_slow_close_within_the_bound_succeeds` (3 s, `Ok` at 3 s, `closes() == 1`) and `a_close_beyond_the_bound_is_reported` (6 s, `Error::Transport` "the close did not complete within 5.0 s" at 5 s, `closes() == 1`) in `link/tests/loss.rs` |
| UT-DISC-010 | pass for the points of revision 7, by inspection | below |
| IT-014 | pass, by inspection | below |

## UT-DISC-010: the points of revision 7

Inspected in the main session on the final tree, `discovery/ble.rs` and
`discovery/mod.rs`. The other points of UT-DISC-010 are unchanged since
the record `2026-10-02-unit-discovery-rev5.md`.

| Point | Result |
|---|---|
| `Guarded::connect_ble` under `timeout(timing::CONNECT)` | present (`ble.rs`, `connect`) |
| After an expiry and after an error of the connect: the fetch of the peripheral and the `disconnect` awaited under one `timeout(timing::CLOSE)` | present (`cancel`, called once from `connect`) |
| The three outcomes logged, at WARN after an expiry and at DEBUG after an error | present ("disconnect issued", "disconnect failed: ...", "disconnect did not complete within 5 s") |
| The error returned only after the cancel: the expiry text "connect did not complete within 20 s", the connect's own error otherwise | present |
| The guard armed from before the connect until `Ok` or until the awaited `disconnect` returned | present (`pending.adapter = None` in the `Ok` arm and in `cancel` after `disconnect()` returned) |
| Dropped while armed, the guard issues the `disconnect` once on a spawned task | present, unchanged `Drop` of `PendingConnect` |
| The whole bounded by `FIND + CONNECT + CLOSE`, the wait for the lock included | present (`mod.rs`, saturating additions; the text names 35 s) |

Two observations, both inside the design text. When the fetch of the
peripheral fails, or the close bound cuts the awaited cancel, the guard
is still armed when `connect` returns, so its `Drop` issues one more
disconnect in the background and logs it at WARN. And a connect that
fails on a too small MTU has disconnected already (DD-TRANS-010), so the
cancel then finds no link and logs a failed disconnect at DEBUG.

## IT-014: the new literals

The search covered the `Duration` constructors with 5, 20 and 35 seconds
and with 5000, 20000 and 35000 milliseconds in `crates/` and the
float-second literals in `python/mp305/`, as in the record
`2026-10-02-integration-timing.md`.

| Point | Result |
|---|---|
| `CONNECT` (20 s) and `CLOSE` (5 s) are named constants in `protocol::timing` with a source comment | present |
| The bound of a connect as a whole is built from the three constants, no literal 35 | present |
| No other module carries one of these bounds as a duration literal | present |

Remaining hits, none of them a bound of AR-014: the app's own
`CLOSE_BOUND` of 5 s (`actions.rs`, DD-APP-021), which AR-014 does not
list, and test code (scripted delays and guard timeouts in
`worker_tests.rs`, `shell.rs` and `recording.rs`).

## Open

The change is not yet verified on hardware. ST-013 from Linux, which
failed at the close on 2026-10-04, is to be repeated on halobox.
