# Spike: read-only Bluetooth LE

Throwaway experiment (see [docs/v-model/README.md](../../docs/v-model/README.md)).
Production code never imports this code and never copies it. Production code
is written from the approved detailed design (DD) files. The documentation,
lint and coverage rules do not apply here.

## Questions

`spike.py`:

1. Which GATT services and characteristics does the MP305B offer, with which
   properties, and what MTU does macOS negotiate?
2. Does the device accept WebLink's bind frame on `0xAF02`, and what does it
   answer?
3. What is the byte layout of the module info reply (`0xE1` on `0xAF02`), the
   settings reply (`0xC5`) and the live data reply (`0xC3`), including the
   reply address byte and the optional fields at the end?
4. Do commands on `0xAF01` work, and does `0xE0` sent on `0xAF01` return the
   main firmware version?
5. After a denied bind, does the device still answer read requests on
   `0xAF01`?

`dis_read.py`: what do the standard Device Information service and the
unknown `0xDB01` characteristic contain?

## Answers

All answers are confirmed on hardware and recorded in LOGBOOK.md under
2026-09-29. They go into docs/research/protocol.md when that file is written.

1. Services `0x180A`, `0xAF00` (characteristics `0xAF01` and `0xAF02`) and
   `0xDB00`. No `0xFEE0` in normal operation. MTU 247. See the GATT table in
   "Hardware: read-only Bluetooth LE spike".
2. Yes. With WebLink's bind frame, the device asks on its screen on every
   connection whether to allow it. It answers `19 00` for allow and `19 FF`
   for deny.
3. Replies on `0xAF01` start with address byte `0x31`. The `0xC5` reply is 13
   bytes and the `0xC3` reply is 38 bytes. The module `0xE1` reply on `0xAF02`
   is 17 bytes with no address byte.
4. Yes. `0xE0` on `0xAF01` returns the same 16 bytes as on `0xAF02`. The
   spike labelled them as Bluetooth module info, which was wrong: bytes 1 to
   4 are the main firmware version (WebLink's "System Version", 1.6.0.40)
   and bytes 13 to 16 are WebLink's "Firmware Version" (2.0.2.0). See
   LOGBOOK 2026-09-29, "Corrections, second round".
5. Yes. Settings, live data and info reads all work after a deny.

`dis_read.py`: every text field holds a placeholder string from the Bluetooth
chip vendor's SDK, and `0xDB01` reads back empty. See "Hardware: Device
Information service".

## Safety

A read-only spike was approved before `spike.py` first ran (LOGBOOK
2026-09-29, "Hardware: read-only Bluetooth LE spike").

- `spike.py` sends only the frames in its `ALLOWED` set: the bind frame,
  which WebLink sends in the same form on every connection, and the read
  requests `0xE0`, `0xC4` and `0xC2`. `send()` refuses any other frame.
- `dis_read.py` only reads. It writes nothing and does not bind.
- Neither script sends a command that changes the output, setpoints or
  settings. Nothing was connected to the output during the first recorded
  run.

A spike that talks to the device follows the HIL safety rules: 5 V and
100 mA defaults, output off at the end, and nothing on the output unless
stated. Adding a frame that changes device state needs the user's go-ahead
first.

## Run

`spike.py` needs a person at the supply to press allow or deny within 30 s.

```sh
uv run --with bleak python spikes/ble_readonly/spike.py
uv run --with bleak python spikes/ble_readonly/dis_read.py
```

`spike.py` writes a capture to `docs/research/captures/` (format and rules in
[docs/research/README.md](../../docs/research/README.md)). The file name
holds the local time when the file was written at the end of the run. The
meta line holds the start time. The meta line records the bleak version as
`unknown` because the installed bleak had no `__version__` attribute. The
versions are in the recorded `0xE1` replies, but `spike.py` decodes them
under wrong labels (`ble_hw`, `ble_sw`, `hw_version`); see answer 4.
`dis_read.py` prints its result and writes no file.
