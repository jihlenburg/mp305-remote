# Retro theme preview

Question: can a compact Retro-inspired interface preserve the instrument's
readable decimal columns and clear power controls?

This is an isolated, interactive design preview with simulated readings.
It has no device transport, no recording file writes and no control of a
real supply. Buttons and setpoint fields
operate only the simulation. The preview starts at 12 V and 0.2 A with its
simulated output on so the readout and chart styles are visible.

The prototype is retained as design history. Its reviewed ideas are now
implemented independently in the production app, which starts in Retro
and has a 320 by 320 minimum. See the
[app guide](../../crates/mp305-app/README.md) for current behavior and tests.
The prototype's earlier dimensions and styles below describe this experiment.

The design uses curved panel bands, segmented controls, a black background
and peach, lilac and blue accents. Measurement digits keep B612 Mono with
compact decimal punctuation; labels use the condensed Antonio family.
Both fonts are OFL-licensed. This is an original layout inspired by the
Retro visual vocabulary, without copied panel artwork.

Reference: [Enterprise-D OPS panel](https://www.juliensauctions.com/en/items/111121/star-trek-picard-uss-enterprise-d-ops-lcars-control-panel).
Antonio source: [Google Fonts](https://github.com/google/fonts/tree/main/ofl/antonio),
with its license in `assets/OFL-Antonio.txt`. B612 and its license are taken
from the app's existing `assets/fonts/` directory.

```sh
CARGO_TARGET_DIR=target cargo run --manifest-path spikes/retro_ui/Cargo.toml -- --render
CARGO_TARGET_DIR=target cargo run --manifest-path spikes/retro_ui/Cargo.toml
sh spikes/retro_ui/bundle_macos.sh
```

`--render` writes 15 PNGs under `target/retro-preview/`, from 1000 by 640 down
to 320 by 272, including wide/short and narrow/tall cases. It checks simulated
Output OFF with Details open, Output ON, setpoint editing, recording and a
round trip through both layouts. An additional image checks recording
with an invalid setpoint and a visible unapplied-edit label. An unapplied edit, recording, output state
and the selected chart window survive resizing.

Below 760 points wide or 520 points high, graphs disappear automatically and
the window becomes a small instrument panel. Readings retain decimal and unit
alignment. Setpoints, Output OFF/ON, recording and Details remain accessible.
Details uses a scrollable upper panel, leaving the output controls visible.
Enlarging the window restores the graphs and their previous time range.

Native mode opens a separate preview window. The bundle script writes
`target/retro-preview/MP305 Retro Preview.app` for macOS. Neither mode can
connect to hardware. This prototype is not verification of the implemented
production app design in app DD revision 6.

The revised compact panel has 12-point rails, 34-point measurements, 36-point
output buttons and quieter outlined secondary controls. Its 320 by 272
minimum uses about 24% less area than the first 360 by 320 proposal.
