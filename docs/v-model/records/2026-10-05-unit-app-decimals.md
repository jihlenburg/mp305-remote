# Readout decimal alignment correction

Date: 2026-10-05. Level: unit, drawing inspection and UI regression.
Commit: uncommitted on `2528dabe26ca43a08994e11ed2367fa2647b401f`.
OS: macOS 27.0.1, arm64. Transport: none. Firmware: not applicable.
Diff for this correction: `ui/widgets.rs`, `ui/panel.rs`, `ui/tests.rs`,
13 existing screenshot baselines, TODO and LOGBOOK. No device logic changed.

The user's visual review found that equal total string widths put the
decimal in different positions for volts and amps, and a full monospace
cell around the period left too much space. Corrected the rendering within
DD-APP-031's fixed digit layout: separate whole/fractional columns, B612 Mono
Bold digits and compact B612 Bold punctuation. Voltage retains two decimal
places and current three; blank reserved space adds no displayed precision.
The units retain a common column and baseline.

| Check | Result |
|---|---|
| `cargo test -p mp305-app ui::tests` | pass, all five tests; UT-APP-029, 030, 031 and 033 |
| UT-APP-031 geometry | pass, rendered decimal and unit positions stay fixed across narrow/wide digits, both precisions, zero and missing-reading placeholders; separator narrower than a digit cell |
| UT-APP-031 images | pass, all 15 baselines; reviewed and replaced the 13 readout images at default/minimum/Retina sizes; two connection images unchanged |
| UT-APP-020 inspection | pass, drawing-only change, no device I/O or control eligibility changes |
| `cargo clippy -p mp305-app --all-targets -- -D warnings` | pass |
| `cargo fmt --all --check`, `git diff --check` | pass |
| `scripts/bundle_macos.sh` | pass, release build and bundle signature |
| `python3 scripts/check_traceability.py --check` | existing UT-DISC-012 defect remains outside this correction; no new defect |

Coverage was not repeated for this change to the documented GUI exclusion.
The prior non-rendering coverage result remains applicable. No hardware
cycling was needed for the typography correction.

Native follow-up: reopened the rebuilt app, clicked Scan, selected
`DevSrvsID:4295529386` over USB and clicked Connect. The native screenshot
confirmed aligned decimal positions at 0.00 V and 0.000 A, output off,
and unchanged 12.00 V / 0.200 A setpoints. The app was left connected for
the user's review. No setpoint or output command was sent. Firmware context
is the [USB UI record](2026-10-05-app-ui-usb.md) from the same day.
