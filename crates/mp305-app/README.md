# MP305 Remote

MP305 Remote is the desktop app of this project. It finds an ISDT MP305B
bench power supply over Bluetooth LE or USB, connects to it, and shows its
readings, setpoints, output state, faults and settings. It sets the voltage
and the current limit, switches the output on and off, requests and
releases remote control, applies your own voltage and current limits,
charts voltage, current and power over a window of 10 s to 10 min, and
records the readings to a CSV file. Closing the window while the output may
be on asks first whether to switch it off.

Read the [bench safety](#bench-safety) note before you connect a load.

## Controls and device names

Select a supply, then press Connect. The left column keeps the measurements,
setpoints and output buttons visible; Details holds settings and recording
options. Editing a setpoint does not send it until you press Enter or Set.
Record starts a CSV; Stop finishes it. Choose a file in Details, or leave the
field empty to use a timestamped file in your Documents directory.

To name a supply, select it and open Details, enter a Device name, then press
Save name. Clear the field and save to remove the name. Names are saved on
this computer, separately for each transport and exact OS identifier. They
survive app restarts. Bluetooth names follow the OS peripheral identity.
USB names follow the attached USB endpoint and can need reassignment after
unplugging. On macOS they are also scoped to the current boot, because the
USB registry identifier is not permanent. USB and Bluetooth entries are not
automatically merged, and the app controls one selected connection at a time.

## Appearance and compact mode

The app opens in Retro, with curved frame bands, condensed labels, consistent
action sizes and fixed-width measurement digits. Choose Standard or Retro at
the top of Details. The selection lasts for the current window; each new
window starts in Retro. Full endpoint identifiers remain in Details and
tooltips.

Shrink the window below 760 points wide or 520 points high to hide the graphs
and use the compact instrument panel, down to 320 by 320 points. The compact
Retro frame keeps both curved bands and space around the controls. Output
controls stay below scrollable warnings and Details. Enlarging the window
restores the graphs, including readings collected while they were hidden.
Edits, the selected supply and recording survive resizing and theme changes.

## UI regression checks

```sh
cargo test -p mp305-app ui::tests
```

These tests click and type into the actual egui screens, checking the commands
they produce without connecting to hardware. They cover duplicate device
names, renaming, invalid setpoints, recording, chart windows and Output OFF
while other windows are open. Fifty-two image baselines cover both themes at
full and compact sizes, connection loss, edited fields, recording, Details,
the close question and a Retina display scale. Interaction tests also check
Retro startup, theme changes, resizing, shared decimal columns, control
alignment, visible frame bands, clean off status and incoming readings while
plots are hidden.

Baselines live in `tests/snapshots/`. A mismatch writes `.new.png` and
`.diff.png` alongside the baseline. Review the images before replacing a
baseline; do not automatically accept snapshot updates. Rendering needs a
wgpu adapter, and other operating systems or GPUs may need a visual review
of rasterization differences. Native window behavior and real hardware
remain separate hands-on checks.

## Build and run

The app is part of the Cargo workspace of this repository and needs Rust
1.95 or later.

### macOS

Build the app bundle with the script at the root of the repository:

```sh
scripts/bundle_macos.sh
```

It builds a release binary and makes `target/release/bundle/MP305 Remote.app`,
signed ad hoc for this machine. Open the bundle from Finder or with
`open "target/release/bundle/MP305 Remote.app"`.

- macOS asks for the Bluetooth permission at the first scan. Allow it, or
  the app finds supplies over USB only.
- A bundle that macOS quarantined (for example one copied from another
  machine) is ad hoc signed only, so macOS refuses to open it with a double
  click. Open it once with Open from its context menu in Finder.
- A rebuilt bundle has a new signature, so macOS may ask for the Bluetooth
  permission again.

### Linux

- Bluetooth needs BlueZ running, and your user must be allowed to use it.
- The app needs the run-time libraries `libudev` and `libdbus-1`.
- Building it needs the packages `pkg-config`, `libudev-dev` and
  `libdbus-1-dev` (Debian and Ubuntu names).
- USB access needs the udev rule `packaging/linux/70-mp305b.rules` of this
  crate. Copy it to `/etc/udev/rules.d/`, load it, and plug the supply in
  again:

  ```sh
  sudo cp crates/mp305-app/packaging/linux/70-mp305b.rules /etc/udev/rules.d/
  sudo udevadm control --reload-rules
  sudo udevadm trigger
  ```

Build and run:

```sh
cargo build --release -p mp305-app
target/release/mp305-app
```

### Windows

Bluetooth LE needs Windows 10 22H2 or later; nothing else is to be
installed. Build the app with the C runtime linked statically, so that no
Visual C++ runtime is needed on the machine that runs it (in PowerShell):

```powershell
$env:RUSTFLAGS = "-C target-feature=+crt-static"
cargo build --release -p mp305-app
```

The result is `target\release\mp305-app.exe`. A release build opens no
console window; the log then goes to the file named by `MP305_LOG_FILE`
(see Logging).

## Logging

The app writes its log with millisecond timestamps.

- `RUST_LOG` sets the filter, for example `RUST_LOG=debug`. Without it the
  app logs at `info`.
- `MP305_LOG_FILE` names a file the log is appended to instead of stderr.
  A file that does not open is reported on stderr, which is then used.

For the frame-time log of system test ST-038, set
`RUST_LOG=mp305_app::frames=trace,mp305_core::frames=trace` and
`MP305_LOG_FILE` to the file the log goes to:

- macOS: start the binary inside the bundle from a terminal, so that it
  sees the variables:

  ```sh
  RUST_LOG=mp305_app::frames=trace,mp305_core::frames=trace \
  MP305_LOG_FILE="$HOME/mp305-st038.log" \
  "target/release/bundle/MP305 Remote.app/Contents/MacOS/mp305-app"
  ```

- Linux: the same with `target/release/mp305-app`.
- Windows (PowerShell), since the release build has no console:

  ```powershell
  $env:RUST_LOG = "mp305_app::frames=trace,mp305_core::frames=trace"
  $env:MP305_LOG_FILE = "$env:USERPROFILE\mp305-st038.log"
  target\release\mp305-app.exe
  ```

## Bench safety

Set a hardware current limit and the OCP mode on the supply's front panel. Keep only a load on the output that is safe at the supply's settings. The supply keeps the output on when the link drops, and the app cannot switch it off then. Prefer USB over Bluetooth for unattended runs.

## Fonts

B612 and Antonio are embedded under the SIL Open Font License. Their license
texts are in `assets/fonts/OFL.txt` and `assets/fonts/OFL-Antonio.txt`.
