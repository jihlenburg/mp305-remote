# Retro theme and compact layout preview

Date: 2026-10-05. Scope: desktop presentation experiment, not protocol or
hardware evidence. Source: `spikes/retro_ui`, outside the production workspace.

## Current status

The user approved production integration and the subsequent refinements on
2026-10-05. The app now starts in Retro, offers Standard in Details and has
a 320 by 320 minimum with complete upper and lower frame bands. See the
[app guide](../../crates/mp305-app/README.md),
[app DD](../v-model/4-detailed-design/app.md#8b-retro-default-theme-and-compact-mode-revision-6-approved-2026-10-05)
and [compact verification](../v-model/records/2026-10-05-unit-app-compact-frame.md).
The sections below preserve the prototype's earlier stages and measurements.

## Question and result

Can a Retro-inspired panel preserve readable measurements and useful controls,
and become a small instrument window when the graphs no longer fit?

Confirmed by rendered and interactive simulation: the preview provides curved
orange bands, peach/lilac/blue controls, Antonio labels and aligned B612 Mono
measurement digits with compact decimal punctuation. Below 760 points wide
or 520 points high it replaces the graph area with a compact control panel.
The minimum viewport is 360 by 320 points. Enlarging restores the graphs.

The compact panel keeps V/A readings, power, regulation/output state, editable
setpoints and Set buttons, separate Output OFF/ON, recording and Details.
Details uses a scrollable upper region and leaves output controls reachable.
The simulated load is approximately the user's 12 V, 1 W lamp. The preview
has no transport dependency and cannot send device commands or record files.

## Checks

Platform: macOS 27.0.1 (26A434), arm64. Source: uncommitted preview and app DD
revision 6 draft, based on production app commit
`a395da7f54481394ffa1ce398009ca9f9d3e739d`. No production source was changed.

Commands from the repository root:

```sh
cargo fmt --manifest-path spikes/retro_ui/Cargo.toml --check
CARGO_TARGET_DIR=target cargo run --manifest-path spikes/retro_ui/Cargo.toml -- --render
sh spikes/retro_ui/bundle_macos.sh
```

- Passed rendering at 1000 by 640, 900 by 580, 760 by 520, 420 by 340,
  360 by 320, 900 by 320 and 360 by 580 points. Each size has an on-state
  image and an off-state image with Details open, 14 PNGs in total under
  `target/retro-preview/`. Full, compact, minimum, wide/short and narrow/tall
  layouts were visually inspected.
- Passed simulated Output OFF with Details open, then Output ON, at every
  size. Tests drive the drawn egui controls by their accessible labels.
- Passed resizing from 900 by 580 to 360 by 320 and back. The unapplied
  7.25 V edit, recording and output states survived shrinking. Applying the
  edit by Enter and stopping recording worked while compact. Enlarging
  restored chart choices, preserving the five-minute choice and setpoint.
- Native full layout was opened and reviewed at 900 by 580 and 760 by 520.
  Opening Details and pressing Output OFF at the latter size showed zero
  simulated readings while Details remained open. The user liked the
  appearance and requested the smaller mode during this review.
- The updated compact-mode bundle built and passed ad hoc signature
  verification. Native restart/resize testing of this updated build was not
  completed because the Mac had become locked. The earlier preview process
  may still be running and needs restarting to load the new build.

These are exploratory checks, not production UT, system or acceptance test
results. At this stage, app DD revision 6 proposed production integration and
its tests; approval and implementation followed later, as recorded above.

## Visual sources

The layout is original, informed by the
[Enterprise-D OPS panel](https://www.juliensauctions.com/en/items/111121/star-trek-picard-uss-enterprise-d-ops-lcars-control-panel).
Antonio comes from [Google Fonts](https://github.com/google/fonts/tree/main/ofl/antonio)
under the bundled OFL license. B612 and its OFL license are reused from the
production app's existing font assets. No reference panel artwork is copied.

## Compact layout refinement

Follow-up on 2026-10-05: the user requested a further refinement after opening
the first compact preview. Reduced the minimum to 320 by 272, about 24% less
area than 360 by 320. Measurement text grew from 32 to 34 points, rails shrank
from 24 to 12 points, Output OFF/ON grew from 34 to 36 points high, and the
secondary controls became smaller outlined buttons. The header identifies
the simulation; the large bottom simulation band is removed. Edited fields
show an explicit not-applied label.

Repeated the same render command at 1000 by 640, 900 by 580, 760 by 520,
360 by 290, 320 by 272, 900 by 272 and 320 by 580. Added an invalid-setpoint
and recording image, bringing the total to 15. The interaction checks pass:
31.00 V is rejected, the last applied 7.25 V remains, and Output OFF works
while the error and recording state are present. Resize/state checks now use
320 by 272. Rebuilt and signed the bundle, reopened it and resized the native
window into the refined compact layout. This completes the previously blocked
native launch/resize check above.

One headless rendering run showed transient raster corruption of several
painted items. Inspecting the emitted text shapes showed the expected positions;
a repeat render and the native window displayed the correct layout. No cause
was established. This is a limitation of this exploratory visual check, to
investigate if it recurs during production snapshot work.

The user also asked about a fixed-width Retro readout font. The preview still
uses B612 Mono Bold. Iosevka Fixed Bold was suggested as a narrower monospace
alternative, and Antonio in equal-width digit cells as an option that matches
the labels. No font replacement was made in this follow-up.

### Setpoint row alignment

On 2026-10-05 the user requested vertical alignment of the setpoint fields and
SET buttons with the live voltage/current readings. Compact fields and their
buttons now share a row centre derived from the visible numeral bounds. The
same digit sample fixes the centre independently of the current reading, and
text fields centre their contents vertically. Both rows retain matching field
and button columns. The 15-image render and existing interaction checks pass;
the minimum-size image was reviewed. The updated macOS bundle built and passed
signature verification. No production code or device behavior changed.

### Setpoint readability and decimal alignment

A further review on 2026-10-05 found that the 14-point setpoints were small
and their decimal positions differed. Increased them to 16 points and used
layout-only leading space to reserve two whole-number columns. Decimal
punctuation uses the compact B612 face. The editable and accessible strings
contain no added padding. Both fields remain centred on their live readings,
with the SET buttons in the same rows. Added a subtle separator above power
and output state.

Rendered all 15 cases and repeated the existing input/resize checks. A new
exploratory geometry assertion checks the actual painted setpoint decimal
positions at all compact sizes, including invalid 31.00 V with 0.200 A.
They differ by less than 0.75 points. Minimum-size normal presentation was
visually reviewed and the release preview bundle rebuilt and signed.

The previously reported headless raster anomaly recurred in the invalid-input
image; rendering every egui pass did not eliminate it. The emitted text
geometry and interaction checks pass. This remains an open rendering issue
for the exploratory harness, not a verified production snapshot baseline.

## Production integration, 2026-10-05

The user approved integration and subsequently requested a shared layout grid,
cleaner connection cards and the name Retro. The production implementation is
separate from this prototype, using the app's real model and actions. See the
[production verification record](../v-model/records/2026-10-05-unit-app-retro.md).

The apparent missing or displaced pixels seen in individual image previews
were investigated during integration. Saved pixel values and opaque RGB
contact sheets show the expected header, controls and positions. The final
50 production PNG baselines pass on a fresh workspace test run without GPU
sharing, extra renders or tessellation changes. The image-preview symptom is
not evidence of a fault in the saved production renders.
