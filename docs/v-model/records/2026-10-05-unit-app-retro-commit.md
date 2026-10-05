# Retro app commit verification

Date: 2026-10-05. Source: staged, uncommitted over
`a395da7f54481394ffa1ce398009ca9f9d3e739d`. The resulting approved app DD
revision 6 commit is identified by `g4-app-rev6-approved`.
Platform: macOS 27.0.1, arm64. Transport: mock or none. Firmware: not applicable.

Scope: the integrated Retro presentation, compact frame and controls,
typography and button spacing, Retro startup default, both themes' UI
checks, reviewed baselines, prototype history and current documentation.
The user approved the Retro startup default and commit/push on 2026-10-05.
ADR-0020 records the replacement of the earlier Standard startup choice.
The separate HID owner-thread source changes and spike are excluded.

## Isolated source verification

Exported the staged source with `git checkout-index --all` to
`/var/folders/0z/2bt3mdt16rv35drymm52hl_m0000gn/T/mp305-retro-commit-j7v4w3tp/`.
The commands below ran there. Cargo used
`CARGO_TARGET_DIR=/Users/jihlenburg/mp305b/target` to reuse dependency builds.
The generated traceability matrix was staged from this export so it
describes the committed source set, without the unrelated local HID defect.

| Command or inspection | Result |
|---|---|
| `cargo test --workspace` | Pass, 541 tests including 145 app unit tests, three app integration tests and 52 matching screenshots. |
| `cargo clippy --workspace --all-targets -- -D warnings` | Pass. |
| `cargo clippy -p mp305-core --all-targets -- -D warnings` | Pass without the workspace's unified mock feature. |
| `cargo fmt --all --check` | Pass. |
| `cargo fmt --manifest-path spikes/retro_ui/Cargo.toml --check` | Pass. |
| `python3 scripts/check_traceability.py` | Pass, zero defects. |
| `python3 scripts/check_traceability.py --check` | Pass. |
| `cargo build --release -p mp305-app` | Pass, the app built separately from the workspace. |
| `git diff --cached --check` in the source repository | Pass. |
| Relative Markdown links in staged documents | All file targets exist. |

UT-APP-034 now starts with `View::default()`, verifies Retro, switches to
Standard and back, finishes in Standard and checks that a fresh window
starts in Retro. It exercises disconnected, connected, edited, recording,
warning and close-question states. Theme switching preserves fields,
history, phase, recording, names and selection, sends no device command,
and keeps Output OFF usable. This extended test passes.

UT-APP-029, 030, 031, 033 and 035 also pass in both themes. The 52 reviewed
baselines remain unchanged by the startup-default change. IT-041 passes
through the three app integration tests. The wider workspace run checks
the committed core and binding source without including the local HID work.
No system matrix, acceptance or hardware test was run for this commit.
GUI drawing remains excluded from coverage under ADR-0008; coverage was
not remeasured for this presentation change.

## Local bundle

After `cargo clean --release -p mp305-core -p mp305-app`,
`sh scripts/bundle_macos.sh` also passes in the original working directory,
including the plist and ad hoc signature checks. This refreshes the local
app with the Retro startup default while retaining the separate local HID
work used by the earlier native checks. It is a working-tree artifact,
not a claim that the HID work is part of this commit. The running app was
not restarted and no hardware command was sent in this task.

Native inspection at the new 320 by 320 minimum remains open as documented
in the [compact frame record](2026-10-05-unit-app-compact-frame.md).
