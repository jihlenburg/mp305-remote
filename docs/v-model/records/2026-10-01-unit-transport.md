# Verification record: unit tests of the transport module

Date: 2026-10-01. Level: unit (UT-TRANS). Scope: `mp305-core`, module
`transport`, implemented from docs/v-model/4-detailed-design/transport.md
revision 2 (tag `g4-transport-approved`).

Commit: `47f6996` (the run was made on the tree that this commit holds). Diff summary: new files under
`crates/mp305-core/src/transport/` (`mod.rs`, `description.rs`,
`guarded.rs`, `ble.rs`, `ble_route.rs`, `hid.rs`, `hid_report.rs`,
`mock.rs`, `stub.rs`, `test_log.rs`), `crates/mp305-core/tests/
ut_transport_mock.rs` and `ut_transport_trait.rs`, the `mock` feature and
the dependencies in `crates/mp305-core/Cargo.toml`, `Error::Transport` in
`error.rs`, this record, TODO.md, LOGBOOK.md.

OS: macOS 27.0 (Darwin 27.0.0), Apple arm64. Rust 1.98.1 (Homebrew), clippy
0.1.98, cargo-llvm-cov 0.9.1 with the Homebrew LLVM 22 tools; btleplug
0.13.3, hidapi 2.6.7, tokio 1.53. Transport: none (no device). Firmware:
not applicable.

## Commands

```sh
cargo fmt --all --check
cargo clippy --workspace --all-targets -- -D warnings
cargo test --workspace
cargo doc --workspace --no-deps
LLVM_COV=/opt/homebrew/opt/llvm@22/bin/llvm-cov \
LLVM_PROFDATA=/opt/homebrew/opt/llvm@22/bin/llvm-profdata \
  cargo llvm-cov -p mp305-core --summary-only --ignore-filename-regex 'transport/(ble|hid)\.rs'
python3 scripts/check_traceability.py --check
```

All passed: fmt clean, clippy clean with `-D warnings`, 58 in-crate tests,
3 mock tests, 1 trait test and 3 doctests passed (0 failed, 0 ignored),
docs built without warnings, traceability without defects.

## Coverage (line, `cargo llvm-cov`, glue excluded under ADR-0013)

| File | Lines |
|---|---|
| transport/ble_route.rs | 100.00% |
| transport/description.rs | 100.00% |
| transport/guarded.rs | 90.78% |
| transport/hid_report.rs | 100.00% |
| transport/mock.rs | 98.73% |
| transport/mod.rs | 69.23% |
| transport/stub.rs | 100.00% |
| transport/test_log.rs | 87.50% |
| TOTAL | 96.44% |

The module's target is 85 % (ADR-0008); `mp305-core` as a whole is at the
TOTAL above. `transport/mod.rs` sits below the target on its own because the
`AnyTransport` arms for `Ble` and `Hid` delegate to the excluded glue and
cannot run without a device; each is one line.

## Results per test specification entry

| UT | Result | Test |
|---|---|---|
| UT-TRANS-001 | pass | `description.rs`; the mock's identifier in `ut_transport_trait.rs` |
| UT-TRANS-002 | pass | `guarded.rs` |
| UT-TRANS-003 | pass | `guarded.rs` (serialised and cancelled sends) |
| UT-TRANS-004 | pass | `guarded.rs` (timestamps, count, log lines) |
| UT-TRANS-005 | pass | `guarded.rs` |
| UT-TRANS-006 | pass | `tests/ut_transport_trait.rs` |
| UT-TRANS-010 | pass | `ble_route.rs` |
| UT-TRANS-011 | pass (inspection, below) | `ble.rs` |
| UT-TRANS-020 | pass | `hid_report.rs` (3 tests) |
| UT-TRANS-021 | pass (inspection, below) | `hid.rs` |
| UT-TRANS-030 | pass | `tests/ut_transport_mock.rs` |
| UT-TRANS-031 | pass | `tests/ut_transport_mock.rs` |
| UT-TRANS-032 | pass | `tests/ut_transport_mock.rs` |
| UT-TRANS-040 | pass | `error.rs` |
| UT-TRANS-041 | pass | `guarded.rs` |

## Inspection of `ble.rs` (UT-TRANS-011)

| Check | Where | Result |
|---|---|---|
| Event stream taken first | `connect`, first statement | present |
| Notification stream taken before `connect` | `connect`, before `peripheral.connect()` | present |
| Connect, then discover | `connect` | present |
| `mtu()` read, logged, threshold 74 | `connect`, `MIN_MTU` | present; disconnects on failure |
| Both characteristics found and subscribed in order (AF01, AF02) | `connect` | present |
| `select!` on notifications and events | reader task | present |
| `DeviceDisconnected` for this peripheral ends the task | reader task | present; the end of either stream too |
| Write with response | `write_frame` | present |
| Route refusal (`Route::Hid`) | `characteristic`, `write_frame` | present |
| Constructor crate-private; only `Guarded::connect_ble` builds a `Ble` | `connect` is `pub(crate)` | present (see deviations; run 2 adds the module visibility) |
| `Drop` aborts the reader and disconnects best effort | `impl Drop` | present |
| Wire logging | `write_frame`, reader task | present |
| No MTU request | whole file | present |
| Exclusion comments naming ADR-0013 and the covering tests | module doc and every function | present |

## Inspection of `hid.rs` (UT-TRANS-021)

| Check | Where | Result |
|---|---|---|
| `open_path` on the given `HidApi` context | `open` | present |
| One owning I/O thread; `HidDevice` moved into it | `open`, `io_loop` | present |
| Jobs written in order, one job per frame, acknowledged by `oneshot` | `io_loop`, `write_frame` | present |
| `read_timeout` with `Ok(0)` as a timeout | `io_loop` | present |
| One `Decoder` across reports | `io_loop` | present |
| Stop flag checked every iteration; set on `close` and `Drop` | `io_loop`, `shut_down`, `impl Drop` | present |
| Join inside `spawn_blocking` | `shut_down` | present |
| Route refusal (`Route::Ble`) | `write_frame` | present |
| Constructor crate-private; only `Guarded::open_hid` builds a `Hid` | `open` is `pub(crate)` | present (see deviations; run 2 adds the module visibility) |
| Wire logging per report | `io_loop` | present |
| Timestamps through the runtime handle | `io_loop` (`runtime.enter()`) | present |
| Exclusion comments | module doc and every function | present |

## Deviations from the design

- DD-TRANS-012 and DD-TRANS-022 say the concrete `send` and `close` are
  `pub(crate)`. A trait method is as visible as its trait, so that cannot be
  written in Rust. The intent (nothing reaches a transport except through
  `Guarded`) is met the way the review offered as the alternative: the
  constructors `Ble::connect` and `Hid::open` are `pub(crate)`, and
  `Guarded::connect_ble` and `Guarded::open_hid` are the only public ways
  to obtain them. The DD carried an editorial revision 3 for this wording;
  the user then chose a structural fix, DD revision 4, verified in run 2
  below.
- The mock stamps deliveries with their scheduled time (request time plus
  `after`, or creation plus the injection offset) instead of reading the
  clock when its task wakes, because a coarse clock advance in a test wakes
  several timers at once and would stamp them late. The script times are
  offsets by design, so the stamps are what the DD describes.
- `AnyTransport` has its `Mock` variant under the `mock` feature only.

## Run 2: DD revision 4 (the visibility rule)

Date: 2026-10-01. Scope: the change approved as DD revision 4 (DD-TRANS-001,
DD-TRANS-012, DD-TRANS-022; UT-TRANS-006 reworded, UT-TRANS-007 added,
UT-TRANS-011 and UT-TRANS-021 checklists reworded). Commit: `4659c57` (the run was made on the tree that this commit holds).
Diff summary: `crates/mp305-core/src/transport/mod.rs` (`ble` and `hid`
crate-private, `AnyTransport` an opaque struct around a private enum with
`pub(crate)` constructors and `From<Mock>`, three `compile_fail,E0603`
doctests), `guarded.rs` (the two constructors), `ble.rs` and `hid.rs` (one
doc sentence each), `tests/ut_transport_trait.rs` (`AnyTransport::from`),
the DD, `traceability.md`, this record, TODO.md, LOGBOOK.md. Same OS and
toolchain as run 1. The commands are those of run 1.

Red step: with the `ble` module made public again, the first doctest of
UT-TRANS-007 fails (`compile fail ... FAILED`); restored, all pass.

| Gate | Result |
|---|---|
| `cargo fmt --all --check` | pass |
| `cargo clippy --workspace --all-targets -- -D warnings` | pass |
| `cargo test --workspace` | pass: 58 in-crate, 3 + 1 external, 6 doctests |
| `cargo doc --workspace --no-deps` with `-D warnings` | pass |
| `check_traceability.py --check` | no defects, matrix current |

Line coverage of `mp305-core` with the ADR-0013 exclusion:

| File | Lines |
|---|---|
| transport/guarded.rs | 90.43% |
| transport/mod.rs | 60.00% |
| all other files | as in run 1 |
| TOTAL | 96.09% |

TOTAL fell from 96.44 % to 96.09 %: the two crate-private constructors
`AnyTransport::ble` and `AnyTransport::hid` are reachable only from
`Guarded::connect_ble` and `Guarded::open_hid`, which need a device, and
join the delegation arms for the excluded glue as uncovered lines. The
component stays above its 85 % target.

| UT | Result | Test |
|---|---|---|
| UT-TRANS-006 | pass | `tests/ut_transport_trait.rs` (`AnyTransport::from(Mock)`) |
| UT-TRANS-007 | pass | three `compile_fail,E0603` doctests on `AnyTransport` in `transport/mod.rs` |
| UT-TRANS-011 | pass (inspection) | `ble.rs`: module `pub(crate)` in `mod.rs`, `connect` `pub(crate)`, no public function returns a `Ble` (`rg` over `crates/mp305-core/src` for `-> .*Ble` finds only `connect`) |
| UT-TRANS-021 | pass (inspection) | `hid.rs`: module `pub(crate)` in `mod.rs`, `open` `pub(crate)`, no public function returns a `Hid` (same search for `Hid`) |
| all others | pass, unchanged | as in run 1 |

Deviations from the design in this run: none. The deviation of run 1 on
`pub(crate)` trait methods is closed by revision 4.
