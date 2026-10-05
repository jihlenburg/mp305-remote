# Hardware UI check

Question: can the real egui controls operate the lamp and record readings
through the production USB worker without a native window?

This exploratory check uses `mp305_app::ui::App`, the production worker,
session and USB transport. egui_kittest clicks accessible controls and types
into the real setpoint fields. The harness forwards worker events unchanged
and observes them for assertions. It is not a system or acceptance matrix run.
The native window, window manager and app-local name service are not tested
here; naming has separate unit and UI tests.

The user authorised this run on 2026-10-05 with a 12 V, 1 W LED lamp attached.
The 12 V and 0.2 A limits exceed the usual defaults because that is the lamp's
operating voltage and the previously verified CV current limit. Only the
exact USB identifier passed in `MP305_HIL_DEVICE` appears in discovery.
The first reading must be DC, output off, and have the expected 12 V / 0.2 A
setpoints. No Bluetooth connection is made. Reconnection stays disabled.

The normal path clicks Output OFF, checks zero readings, stops the CSV and
disconnects. A caught failure always sends Output OFF and disconnects with
switch-off requested before the worker shuts down. Setpoint changes are
restored in teardown. A broken physical link cannot guarantee switch-off.

Run only with the authorised lamp connected:

```sh
MP305_HIL=1 MP305_HIL_DEVICE=DevSrvsID:4295529386 \
CARGO_TARGET_DIR=target cargo run --manifest-path spikes/hardware_ui/Cargo.toml
```

The program writes JSONL observations to stdout and a CSV plus rendered
screens under a new `target/hardware-ui-<timestamp>/` directory. The output
is live hardware evidence, not a deterministic snapshot baseline.
