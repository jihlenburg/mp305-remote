# Verification record: unit tests and inspection of the discovery module

Date: 2026-10-01. Level: unit (UT-DISC). Scope: `mp305-core`, module
`discovery`, implemented from docs/v-model/4-detailed-design/discovery.md
revision 2 (tag `g4-discovery-approved`), with the test entry UT-DISC-009
of revision 3.

Commit: uncommitted. Diff summary: new `crates/mp305-core/src/discovery/`
(`mod.rs`, `classify.rs`, `ble.rs`, `hid.rs`); `error.rs`
(`Error::NotFound { causes }`); `lib.rs` (`pub mod discovery`);
discovery.md (revision 3: UT-DISC-009); `traceability.md`; this record;
TODO.md; LOGBOOK.md. Written test first by a delegated agent in an
isolated worktree; the gates below were run again in the main session
after the change was applied to the main tree. The two inspections were
made by a second delegated agent that read the files without changing
them, and its tables were checked in the main session against the code.

OS: macOS 27.0 (Darwin 27.0.0), Apple arm64. Rust 1.98.1 (Homebrew),
clippy 0.1.98, cargo-llvm-cov 0.9.1 with the Homebrew LLVM 22 tools;
btleplug 0.13.3. Transport: none (no scan was started and no device was
opened). Firmware: not applicable.

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
| `cargo test --workspace` | pass: 254 in-crate, 5 + 1 external, 13 doctests (273) |
| `cargo doc` with `-D warnings` | pass |
| `check_traceability.py --check` | no defects, matrix current |

Line coverage: `discovery/classify.rs` 99.64 %, `discovery/mod.rs`
84.62 %, `mp305-core` TOTAL 95.46 % (target 85 %). `ble.rs` and `hid.rs`
are excluded under ADR-0014. The uncovered lines of `mod.rs` are
`Discovery::new` and the parts of `scan` and `reach` that call a backend;
UT-DISC-010 covers them by inspection, IT-032 and ST-001 to ST-003 on
hardware.

| UT | Result | Tests |
|---|---|---|
| UT-DISC-001 | pass | 1 |
| UT-DISC-002 | pass | 1 |
| UT-DISC-003 | pass | 1 |
| UT-DISC-004 | pass | 1 |
| UT-DISC-005 | pass | 1 test, 2 `compile_fail` doctests, 1 doctest |
| UT-DISC-006 | pass | 1 |
| UT-DISC-007 | pass | 1 |
| UT-DISC-008 | pass | 1 |
| UT-DISC-009 | pass | 3 |
| UT-DISC-010 | pass by inspection, with the notes below | table below |
| UT-DISC-011 | pass by inspection | table below |

## UT-DISC-010: inspection of `mod.rs` and `ble.rs`

Line numbers are those of the inspected tree (M is `mod.rs`, B is
`ble.rs`, C is `classify.rs`); B shifted by three lines after line 226
when the log line of note 1 was added.

| Point | Result | Where |
|---|---|---|
| No vendor call in `mod.rs` | present | M names only `ble::`, `hid::` and the alias `ble::Adapter` |
| The adapter probe with its three "no adapter" cases | present | B:68 to 89 |
| The USB probe; both missing is `Error::Transport` | present | `hid::available`, M:205 to 210 |
| The scan lock from before `start_scan` to after `stop_scan`, and the drop guard | present | B:204, `ScanStop` B:141 to 182 |
| The snapshot into `Sightings` before the event stream, the stream before `start_scan` | present | B:206 to 213 |
| The four event kinds mapped and every other event `Other` | present, note 1 | `sighting`, B:111 to 126 |
| `stop_scan` with its error only logged | present | `stop`, B:130 to 134 |
| `properties()` per counted id in `seen()` order, `advertised_name` applied | present | `scan` in B |
| `find` ends at the first counted sighting of the identifier and stops the scan | present | `watch` and `find` in B |
| `connect`'s plan | present | M:281 |
| The USB enumeration only for a non-Bluetooth shape | present | M:275 to 279 |
| The `find` before every Bluetooth connect | present | M:284 to 291 |
| `timeout(CONNECT)` with the best-effort `disconnect` after an expiry | present | `PendingConnect` and `connect` in B |
| The whole bounded by `FIND + CONNECT`, the wait for the lock included | present | M:320 to 331 |
| Ids written with `fmt::Write`, a failing `Display` skipped | present | `id_text`, B:54 to 63 |
| One backend's failure logged and the other's result returned | present | `merge` in M, also UT-DISC-009 |
| The log lines of DD-DISC-020 | present, note 1 | M, B and C |
| The exclusion comments | present | every function and `Drop` impl of B |

## UT-DISC-011: inspection of `hid.rs`

| Point | Result | Where |
|---|---|---|
| A fresh `HidApi::new()` inside `spawn_blocking` per enumeration | present | H:77 and 78 |
| De-duplication by path | present | H:79 and 91 (first entry kept) |
| `to_string_lossy` for the identifier, the enumerated `CString` kept for `open_hid` | present | H:84 and 85, M:302 and 303 |
| `HidApi::new()` for the open, never `new_without_enumerate` | present | H:126 |
| No `MutexGuard` across an await | present | no `std::sync` lock in `discovery/` |
| The classifier fed with vendor, product, product string and path | present | H:109 to 111 |
| The exclusion comments | present | the file header and every function |

## Notes and open points

1. An adapter state change (`CentralEvent::StateUpdate`) names no
   peripheral, so it cannot be fed to `Sightings::note`. The inspection
   found that it was dropped without a log line; the glue now logs it at
   DEBUG as an event that was not counted (DD-DISC-020). DD-DISC-012 says
   "every other event `Other`"; a wording that excepts the adapter state
   change is to be put to the user.
2. `Discovery` holds no flag for the USB side (DD-DISC-010: the optional
   adapter, the scan lock "and nothing else"). After a failed USB probe a
   USB scan still runs and its failure is logged at WARN as a failed
   backend, so "skipped with a WARN log" applies to Bluetooth only. This
   follows the design item as written.
3. When Bluetooth is the only enabled transport and there is no adapter,
   `scan` returns an empty list with the WARN line, and a product then
   shows the "no supply found" text with its four causes although the
   cause is the missing adapter. The design item says so ("skipped");
   whether this case should be an error is to be put to the user.
4. A `properties()` error on one counted id fails the whole Bluetooth
   scan (the other backend's result is still returned). An id the adapter
   no longer holds is skipped at DEBUG.
5. Dropped outside a Tokio runtime, the scan guard and the pending connect
   log a WARN and issue no `stop_scan` or `disconnect`; the session always
   runs them inside a runtime.
6. `ble::find` takes the scan lock as DD-DISC-012 says; DD-DISC-011's
   text omits the argument. The texts are to be aligned editorially.
