# App theme and responsive layout verification

Date: 2026-10-05. Source: uncommitted over
`a395da7f54481394ffa1ce398009ca9f9d3e739d`. Platform: macOS 27.0.1,
arm64. Transport: fixtures only for automated checks. No device control
commands were sent during the supplemental native UI check.

## Scope and approval

The user requested integration of the reviewed prototype, approving app DD
revision 6. Subsequent instructions requested a shared grid, cleaner device
identification and the name Retro. The changed production files are in
`crates/mp305-app/src/ui/`, with Antonio font assets and bundled licenses.
Standard remains the initial theme. The model, action handler, protocol and
transport behavior are unchanged by this work. The separate pre-existing HID
owner-thread changes were present in the workspace and remain uncommitted.

## Commands and results

| Command | Result |
|---|---|
| `cargo test -p mp305-app ui::tests:: -- --skip snapshots` | Pass, seven interaction and geometry tests |
| `cargo test --workspace` | Pass, 543 tests including doctests; app has 144 unit tests and three integration tests |
| `cargo clippy --workspace --all-targets -- -D warnings` | Pass |
| `cargo clippy -p mp305-core --all-targets -- -D warnings` | Pass without the mock feature |
| `cargo fmt --all --check` | Pass |
| `git diff --check` | Pass |
| `python3 scripts/check_traceability.py` | Matrix regenerated; one separate pre-existing defect: UT-DISC-012 lacks a specification entry |
| `sh scripts/bundle_macos.sh` | Release build, bundle and ad hoc signature verification pass |

The 50 PNG baselines were reviewed before adoption. They cover both themes
at 900 by 580 and 760 by 520, the connected view at twice the pixel density,
and compact fixtures at 320 by 272, 900 by 272 and 320 by 580. Review contact
sheets are generated artifacts under `target/ui-review/`; committed evidence
is the baseline set in `crates/mp305-app/tests/snapshots/`.

Individual image previews sometimes appeared to omit or displace content.
The original pixel values and opaque contact sheets show the correct saved
images. No GPU or tessellation workaround was retained. The fresh workspace
test run matches all 50 adopted baselines.

## Results by specification

| Test | Result and evidence |
|---|---|
| UT-APP-020 | Pass by inspection: new frame and compact modules only draw the model and return existing actions; presentation state stays in View. No runtime, channel or hardware command handling was added to drawing code. |
| UT-APP-029 | Pass in both themes: discovery selection, connection, field edits, apply, invalid values, chart selection and recording use the real action handler. |
| UT-APP-030 | Pass in both themes: model eligibility is retained and Output OFF remains available with Details and the close question. |
| UT-APP-031 | Pass: full-size and Retina baselines, fixed numeral geometry, aligned fields and visible chart choices. |
| UT-APP-033 | Pass in both themes: naming follows selection and successful saves; failed saves retain the previous display name. |
| UT-APP-034 | Pass: Standard is initial; theme selection sends no device command and preserves field text, selected endpoint, name draft, phase, recording and chart data. |
| UT-APP-035 | Pass: threshold transitions, compact screenshots, field and button columns, setpoint decimals and numeral centres, invalid input, lost-link eligibility, recording/name/session preservation, compact connection actions and new readings while plots are hidden. Output OFF dispatches with Details and the close question open. |

Drawing code remains excluded from coverage under ADR-0008. No covered
production logic changed, so coverage was not remeasured for this UI change.
No system or acceptance matrix run was started, and no acceptance result is
claimed.

## Supplemental native check

Opened the release bundle, selected Retro through Details, closed Details and
reviewed the native typography and layout. The earlier discovery completed
with USB and Bluetooth endpoints, also visible in the user's screenshot.
The final rebuilt app's discovery request remained pending during observation.
Native edge-drag attempts did not change the window size through the available
automation. Compact resizing is verified by the production-screen harness;
a fresh native device connection and compact hardware interaction remain a
follow-up item in TODO.md. No setpoints or output state were changed.
