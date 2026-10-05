# App button spacing

Date: 2026-10-05. Source: uncommitted over
`a395da7f54481394ffa1ce398009ca9f9d3e739d`, building on the integrated
Retro presentation. Platform: macOS 27.0.1, arm64.

The user requested clearance around every button after identifying Set and
Details against the divider. This update adds a 24-point inset on each side
of the Retro divider while retaining the control content width, 8-point
padding above full footer actions, and 4-point padding above compact
connection actions. Scrolling status content is clipped above the footer.
Retro dialog buttons allocate directly into the wrapped row so Cancel wraps
instead of extending through the compact right gutter. No model, action,
protocol or setpoint behavior changed. Separate existing HID discovery work
remains in the working tree and was not changed for this correction.

## Automated procedure

- `cargo test -p mp305-app`: 144 unit tests and three integration tests pass.
- `cargo clippy -p mp305-app --all-targets -- -D warnings`: pass.
- `cargo fmt --all --check` and `git diff --check`: pass.
- `python3 scripts/check_traceability.py`: matrix regenerated; the existing
  unrelated UT-DISC-012 specification defect remains.
- `sh scripts/bundle_macos.sh`: release build, plist and signing succeed.

The nine UI test functions exercise the production screens and action
handler with deterministic fixtures, without device I/O. Geometry assertions
measure the rendered divider and footer rules, check button clearances and
separation, and check compact side gutters. Scrolled-out accessibility nodes
are excluded from visible button-pair comparisons. The check exposed the
compact Cancel overflow and the lack of space above full footer actions.

Reviewed 33 changed images before adopting their baselines: seven full
states at two sizes in both themes, two Retina images, both compact
connection screens, and the compact Retro close question. All 50 snapshots
then matched. Opaque JPEG contact sheets under `target/ui-review/` were used
for visual inspection of the saved PNG pixels.

| Specification | Result |
|---|---|
| UT-APP-029 | Pass, shared connection, setpoint, recording and chart actions in both themes. |
| UT-APP-030 | Pass, output eligibility and Output OFF reachability with secondary windows. |
| UT-APP-031 | Pass, full-size geometry, typography and 30 reviewed snapshots, including divider and footer clearance. |
| UT-APP-033 | Pass, naming selection and save behavior remain unchanged. |
| UT-APP-034 | Pass, theme switches preserve state and send no device command. |
| UT-APP-035 | Pass, compact geometry, 20 snapshots, state retention and fixed output controls. |

GUI drawing remains excluded from coverage under ADR-0008. Coverage was
not remeasured for this presentation-only correction.

## Native inspection and remaining check

Inspected the old running window before editing. Its Set, Disconnect,
Output ON and Details right edges touched the divider. It displayed a USB
write timeout and last readings of zero, output off, with setpoints 12.00 V
and 0.200 A. No output or setpoint command was issued in this check.

After building, closed the old window with Command-Q. Its process, started
at 14:19, remained running without a window. Native automation then returned
`cgWindowNotFound` when selecting the app or other native windows, preventing
the stale process from being cleared through the UI and the updated bundle
from being inspected. Native verification of the new build is pending in
TODO.md; the automated results above are complete. The signed artifact is
`target/release/bundle/MP305 Remote.app`.

This is a unit-level layout verification, not an acceptance or system matrix
run. The earlier native inspection record did not detect the button-margin
defects; its visual result should be read with this correction.

## Later native retry

On 2026-10-05, a later user-requested retry restored native access. Opened
the rebuilt bundle, raised its window, selected Retro in Details, closed
Details and started discovery. The native discovery view showed the new
24-point clearance from Scan and Connect to the divider and the 8-point
gap above the Details footer action. Discovery found the USB endpoint
`DevSrvsID:4295529386`. During inspection, the user interacted with the app;
the selected endpoint appeared as GW300 and Details reopened. Further input
stopped to leave the user's interaction undisturbed. No connection, output
or setpoint command was sent during this retry.

Reopening is complete. The connected and compact portions of the native
spacing check remain pending; the automated results are unchanged.
