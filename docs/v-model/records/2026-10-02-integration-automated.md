# Verification record: integration tests, automated entries

Date: 2026-10-02. Level: integration (IT-003, IT-010 to IT-013, IT-015,
IT-018, IT-020 to IT-022, IT-025 to IT-030, IT-032 to IT-034, IT-040,
IT-041, IT-050, IT-052). The inspection entries have their own records of
the same date (`integration-layout`, `-lints`, `-timing`, `-ble`, `-hid`,
`-app`, `-packaging`).

Commit: `6e8ed18` (the run was made on the tree that this commit holds). Diff summary: new `crates/mp305-core/tests/it_*.rs`
(20 files) with `tests/common/mod.rs`; new
`crates/mp305-app/tests/it_worker.rs` and `it_model.rs`; new
`tests/integration/` (`conftest.py`, `core_errors.py`, `test_runtime.py`,
`test_python_api.py`, `test_exceptions.py`). Fixes from the inspections:
the lint attributes in the crate roots (IT-004); the prompt bounds in
`session/task.rs`, the scan bounds in the app's `model.rs` and the Python
wait slice (`_native.WAIT_SLICE_S`, `wait.rs`, `_native.pyi`,
`_checks.py`, `device.py`) derived from `protocol::timing` (IT-014).
Documents: 3-architecture.md revision 11 and 6-integration-tests.md
revision 10 drafted, approval pending; `traceability.md`; the records;
TODO.md; LOGBOOK.md. The tests were written by three delegated agents in
isolated worktrees, which were not allowed to change production code; the
fixes were made in the main session, where all gates were then run on the
main tree.

OS: macOS 27.0 (Darwin 27.0.0), Apple arm64. Rust 1.98.1 (Homebrew),
clippy 0.1.98, cargo-llvm-cov 0.9.1 with the Homebrew LLVM 22 tools;
CPython 3.10.19 through uv 0.9.9, maturin 1.15.0, pytest 9.1.1, ruff
0.16.10, mypy 2.4.0. Transport: the mock on a paused Tokio clock (Rust),
the mock in real time (Python). No scan was started and no device was
opened. Firmware: not applicable.

## Commands

```sh
cargo fmt --all --check
cargo clippy --workspace --all-targets -- -D warnings
cargo clippy -p mp305-core --all-targets -- -D warnings
cargo test --workspace
RUSTDOCFLAGS="-D warnings" cargo doc --workspace --no-deps
LLVM_COV=/opt/homebrew/opt/llvm@22/bin/llvm-cov \
LLVM_PROFDATA=/opt/homebrew/opt/llvm@22/bin/llvm-profdata \
  cargo llvm-cov --workspace --exclude mp305-py --summary-only \
  --ignore-filename-regex '(transport|discovery)/(ble|hid)\.rs|mp305-app/src/(ui/|main\.rs)'
env -u CONDA_PREFIX uv run maturin develop -m crates/mp305-py/Cargo.toml
uv run --no-sync pytest
uv run --no-sync pytest --cov
uv run --no-sync ruff check
uv run --no-sync mypy python/mp305
# the binding coverage block of AGENTS.md
python3 scripts/check_traceability.py --check
```

## Results

| Gate | Result |
|---|---|
| `cargo fmt --all --check` | pass |
| both clippy runs | pass |
| `cargo test --workspace` | pass, three runs: 522 tests (core 269 in-crate, 6 earlier external and 67 integration, 14 doctests; app 129 and 3 integration; `mp305-py` 34) |
| `cargo doc` with `-D warnings` | pass |
| `pytest` | pass, three runs: 182 tests (128 unit, 54 integration) |
| `ruff check`, `mypy` | pass |
| `check_traceability.py --check` (IT-052) | no defects, matrix current |

Line coverage after this commit: workspace without `mp305-py` 95.70 %,
binding crate 91.59 % (target 80 %), pure Python 96.15 % (target 90 %).

| IT | Result | Tests |
|---|---|---|
| IT-003 | pass (step 1 Python, step 2 app, step 3 core) | `test_runtime.py` 3, `it_worker.rs` 1, `it_clock.rs` 1 |
| IT-010 | pass, note 1 | `it_protocol_frames.rs` 5 (one a property test) |
| IT-011 | pass, note 2 | `it_protocol_payloads.rs` 3 |
| IT-012 | pass | `it_allowlist.rs` 2 |
| IT-013 | pass | `it_units.rs` 2 |
| IT-015 | pass, note 3 | `it_transport_guard.rs` 3 |
| IT-018 | pass, note 4 | `it_frame_log.rs` 2 |
| IT-020 | pass, note 5 | `it_link_dispatch.rs` 5 |
| IT-021 | pass | `it_poll_keepalive.rs` 2 |
| IT-022 | pass, note 5 | `it_link_loss.rs` 3 |
| IT-025 | pass | `it_session_dc.rs` 9 |
| IT-026 | pass | `it_bind.rs` 7 |
| IT-027 | pass | `it_remote_control.rs` 5 |
| IT-028 | pass, note 6 | `it_events.rs` 6 |
| IT-029 | pass | `it_reconnect.rs` 4 |
| IT-030 | pass | `it_single_session.rs` 1 |
| IT-032 | pass | `it_discovery.rs` 3 |
| IT-033 | pass | `it_store.rs` 2 |
| IT-034 | pass | `it_csv.rs` 1 |
| IT-040 | pass | `test_python_api.py` 33 |
| IT-041 | pass (automated part; the inspection is in `integration-app`) | `it_worker.rs` 1, `it_model.rs` 1 |
| IT-050 | pass, note 7 | `it_errors.rs` 1, `test_exceptions.py` 18 |
| IT-052 | pass | the traceability check |

No test fails, and the agents found no defect in production code.

## Deviations and open points

The entries below were written before the detailed designs. Where an
entry and the approved design or the code disagree, the test follows the
design and the code, and the entry's corrected wording is drafted in
6-integration-tests.md revision 10, approval pending.

1. IT-010: a 70-byte frame gives a 74-byte stream and two report payloads
   of 62 and 12 bytes, not "62 and 10". The decoder can report a length
   error only for the length byte 0; any other wrong length shows as a
   checksum error or a restart. The `C8_170` fixture's bytes carry
   `realChange` 0 although its description says "other fields from
   `C3_CAPTURE`" (which would give 3); the test uses the bytes as listed,
   since the entry is about framing.
2. IT-011: the requests' payload lengths are 18, 0, 0 and 11; `0xE0` and
   `0xC2` have empty payloads. The entry's "1, 1" is their HID length
   byte.
3. IT-015: the mock's write takes no time, so two overlapping writes
   cannot be told from consecutive ones. The test puts a transport that
   delays each write by 100 ms on the Tokio clock between the guard and
   the mock, and also shows that the same writes overlap without the
   guard.
4. IT-018: besides the guard's `tx` and `rx` lines, the transports log
   `wire` lines with the on-air bytes under the same target. The test
   counts the guard's lines.
5. IT-020 and IT-022 drive `Link` directly, as `session` does. In IT-022
   case 1 the "request from `session`" is a `Link::request` of `0xE0`
   during the silence; at the session level no immediate request can go
   out while a remote request is pending.
6. IT-028: `Reconnected` and `ReconnectGaveUp` do not occur in the four
   scenarios the entry names; the test takes them from IT-029's.
7. IT-050: the core test triggers all 16 variants through the public API
   (the match has no wildcard) and the Python test maps each to its
   exception class. The app's mapping to its message (`ErrorKind::of`) is
   not reachable from either file; it is a match without a wildcard,
   verified at the unit level (UT-APP-010, UT-APP-013).
8. Python: `NotReady` cannot be raised through `Mp305`, since `connect`
   returns only when the session is ready; the test uses the native
   session of the mock before `ready` (the hook of DD-PY-031 and
   DD-PY-034). On CPython 3.10, adding an unknown attribute to a `Reading`
   raises `TypeError` where later versions raise `AttributeError`; the
   test accepts either.
9. IT-003 step 2: with every reply 2 s late, the fast bind's 1 s bound
   ends the connect attempt, so the worker is inside the delay for the
   first second; the UI-side calls are made at 500 ms.
