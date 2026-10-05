# App visual layout and naming verification

Date: 2026-10-05. Level: unit, with integration regression checks.
Design: app DD revision 5, approved 2026-10-05.
Commit: uncommitted on `2528dabe26ca43a08994e11ed2367fa2647b401f`.
Diff: compact B612 layout, accessible controls, local device names and their
file worker, egui interaction tests and 15 rendered baselines. The working
tree also contains a separate pre-existing HID owner-thread change.
OS: macOS 27.0.1 (26A434), arm64. eframe and egui_kittest 0.36.2,
egui_plot 0.37.0. Transport: mock or none. Firmware: not applicable.

## Commands and results

| Command | Result |
|---|---|
| `cargo fmt --all --check` | pass |
| `cargo clippy --workspace --all-targets -- -D warnings` | pass |
| `cargo clippy -p mp305-core --all-targets -- -D warnings` | pass |
| `cargo test --workspace` | pass, 539 tests including doctests; 140 app unit tests |
| `RUSTDOCFLAGS='-D warnings' cargo doc -p mp305-app --no-deps` | pass |
| `scripts/bundle_macos.sh` | pass, release binary, plist and ad hoc signature verified |
| `python3 scripts/check_traceability.py --check` | one existing defect outside the app: UT-DISC-012 has no specification entry in the uncommitted HID owner code; matrix regenerated |

Coverage command:

```sh
LLVM_COV=/opt/homebrew/opt/llvm@22/bin/llvm-cov \
LLVM_PROFDATA=/opt/homebrew/opt/llvm@22/bin/llvm-profdata \
cargo llvm-cov --workspace --exclude mp305-py \
  --ignore-filename-regex '(transport|discovery)/(ble|hid)\.rs|mp305-app/src/(ui/|main\.rs)'
```

Pass. App non-rendering line coverage: 96.46% (5,670 of 5,878 lines), above
the 80% target and the earlier 96.21%. New `names.rs`: 97.95%.
Workspace excluding the binding and the documented GUI/vendor exclusions:
95.88%. The exclusions are those of ADR-0008 and app DD decision 9, with
vendor glue exclusions under ADR-0013 and ADR-0014.

## Test results

| Test specification | Result and evidence |
|---|---|
| UT-APP-001 to UT-APP-019, UT-APP-021 to UT-APP-028 | pass, existing automated app tests in the workspace run |
| UT-APP-020 | pass by inspection, notes below |
| UT-APP-029 | pass, accessible selection, separate Connect, typed fields, Enter/Set, invalid value, Details, chart windows and recording actions |
| UT-APP-030 | pass, model eligibility in warning/lost/non-DC states; Output OFF clickable at minimum size with Details and the question open |
| UT-APP-031 | pass, geometry checks and 15 reviewed PNG baselines, default/minimum sizes and 2x display scale |
| UT-APP-032 | pass, distinct identities and boot scopes, save/reopen/remove, validation, corrupt file and failed write handling, file service |
| UT-APP-033 | pass, UI draft/save and selection behavior, connected AppCore file-service integration, errors retain the old alias and send no device command |
| IT-041 | pass, existing worker/model/chart integration test in workspace run |

UT-APP-020 inspection: `ui/mod.rs` forwards frame logic, actions and exit;
`ui/launch.rs` retains the macOS menu hook and default egui quit shortcut.
Drawing uses the model's eligibility and device state; no device or disk I/O
runs in drawing or frame logic. The name service owns its own file thread.
All three plots, setpoints, controls, status, Details and recording remain
present. Details and the close question are non-modal and clear of Output
OFF. Dependency boundaries, crate safety lints, worker event-end handling
and exclusion comments remain in place. Coordinate arithmetic uses scalar
components rather than unchecked operators on egui geometry types.

Baselines: `crates/mp305-app/tests/snapshots/`. Every image was inspected
before adoption. Review found and corrected misaligned fields and unit
baselines, weak muted text contrast, clipped footer/status content, expanding
Details width for long identifiers, missing discovery accessibility labels
and a chart corner-label overlap. Deterministic snapshots are not hardware
evidence. Other GPUs and operating systems may need rasterization review.

The final native-window check was unavailable because the Mac was locked.
The separate [USB UI check](2026-10-05-app-ui-usb.md) exercises the real app
and hardware through the headless egui harness. No acceptance test is claimed.
