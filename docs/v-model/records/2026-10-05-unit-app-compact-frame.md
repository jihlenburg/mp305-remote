# Compact frame and typography

Date: 2026-10-05. Source: uncommitted over
`a395da7f54481394ffa1ce398009ca9f9d3e739d`, building on the Retro integration
and button spacing changes. Platform: macOS 27.0.1, arm64.

The user requested a more complete compact frame and explicitly accepted
additional window area. The minimum content size is now 320 by 320 points,
48 points taller than before. The compact Retro frame has a 24-point upper
band, 16-point lower band, 16-point side rail and both curved corners, with
space between the controls and the frame. Action captions use consistent
condensed uppercase lettering, retaining the original accessible names.
Power uses the same compact decimal punctuation as voltage and current.
The status shows one OFF when both output and regulation are off. A floating
scrollbar occupies the right gutter without shifting the setpoint column.
No model, action, protocol, setpoint or device eligibility behavior changed.
Separate pre-existing HID discovery work remains untouched.

## Automated procedure

- `cargo test -p mp305-app`: 145 unit tests and three integration tests pass.
- `cargo clippy -p mp305-app --all-targets -- -D warnings`: pass.
- `cargo fmt --all --check` and `git diff --check`: pass.
- `python3 scripts/check_traceability.py`: matrix regenerated; the existing
  unrelated UT-DISC-012 specification defect remains.
- `sh scripts/bundle_macos.sh`: release build, plist and signing pass.

Ten UI test functions exercise the production drawing and action handler.
The added regression check measures punctuation width, the single OFF
label, frame clearance and stable columns when a warning requires scrolling.
Reviewed 33 replacement images and two new output-off images before adopting
their baselines. All 52 snapshots pass: 30 full and Retina images and 22
compact images covering both themes, minimum size and different aspect
ratios. Review contact sheets and command output are in `target/ui-review/`.

| Specification | Result |
|---|---|
| UT-APP-029 | Pass, shared selection, setpoint, recording and chart actions. |
| UT-APP-030 | Pass, model eligibility and Output OFF reachability with secondary windows. |
| UT-APP-031 | Pass, full-size alignment, button clearance and 30 reviewed snapshots. |
| UT-APP-033 | Pass, naming selection and saving retain their behavior. |
| UT-APP-034 | Pass, theme changes preserve state and dispatch no device commands. |
| UT-APP-035 | Pass, compact frame, 22 snapshots, punctuation, off-state label, stable columns, resizing and fixed output controls. |

GUI drawing remains excluded from coverage under ADR-0008. Coverage was
not remeasured for this presentation-only change.

## Native inspection

1. Closed the disconnected old app, built the bundle and reopened it.
2. Selected Retro in Details, closed Details and scanned. Both transports
   appeared, including the saved USB name GW300.
3. Selected GW300, USB endpoint `DevSrvsID:4295529386`, and connected.
   The firmware reference remains LOGBOOK 2026-10-05, "Lamp operated through
   the real egui controls": system version 1.6.0.51 and firmware version
   2.0.2.0. No firmware update was performed.
4. Inspected the 900 by 580 content window at Retina scale. Set, Disconnect,
   Output ON and Details have visible space before the divider; Record and
   Details have space above the footer. Power punctuation is compact and
   the status displays a single OFF. Readings are 0.00 V, 0.000 A and 0.00 W.
5. Tried edge and corner drags to inspect the native compact view. The
   automation actions returned without resizing the window. Native compact
   verification remains open in TODO.md; the automated compact results
   above are complete. Left the updated app open, connected, at full size.

No output or setpoint command was sent. The output remained off and the
original 12.00 V and 0.200 A setpoints remained unchanged. This is unit-level
layout verification with supplemental native observations, not an acceptance
test or system matrix run. No commit or push was made.
