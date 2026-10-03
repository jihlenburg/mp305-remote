# Verification record: system tests on macOS over Bluetooth, first batches

Date: 2026-10-03, 02:26 to 02:37 local time. Level: system. Scope: the
entries of 7-system-tests.md that need neither a load nor front-panel
actions, run on the user's MP305B from the Mac over Bluetooth with the
user at the supply, within the go-ahead given in the session (batch A:
read-only entries; batch B: control commands at 5 V and 0.1 A with the
output switched on and off, nothing connected).

Commit: `80e42f8` (the tree of that commit; the library built from it).

OS: macOS 27.0.1, Apple arm64, the Mac's own Bluetooth adapter. CPython
3.10.19, pytest 9.1.1. Transport: Bluetooth LE. Firmware: System Version
1.6.0.51, Firmware Version 2.0.2.0 (the record
`2026-10-03-system-macos-ble-st013.md` and this run's `0xE1` replies).
The supply started each batch in DC mode with the output off, its own
setpoints 12.0 V and 0.5 A, nothing connected to the output; the
pre-flight of each batch confirmed the output off.

## Commands

```sh
MP305_HIL=1 MP305_HIL_DEVICE=72de66a3-7c9b-58a3-a45b-cf098194d568 \
  MP305_HIL_PERSON=1 MP305_HIL_RECORD=<file> \
  uv run --no-sync pytest tests/system -m hil -k "<the tests of the batch>" -s -rs -v
```

The user pressed ALLOW on the supply whenever its screen asked (the
remote-control prompt, once per test of batch B and at some teardowns).

## Results

| ST | Result | Note |
|---|---|---|
| ST-004 | pass (step 1 on the supply; step 2 on the mock elsewhere) | |
| ST-006 | pass (step 1; step 2 is IT-012) | the log holds only `0x18`, `0xE0`, `0xC2` and `0xC8` requests |
| ST-012 | pass (the early control call; the comparison with the screen is a person entry, not run) | the call before the first reading is refused: "the session is not ready for control" |
| ST-013 | pass (run again for the log checks) | 268 readings in 60 s, shortest gap 101 ms |
| ST-017 | pass (step 1, on the log of ST-013; step 2 on the mock elsewhere) | no overlapping requests |
| ST-018 | pass | the first command requests remote control; the user's ALLOW came after 24 s and the reply was `0xC9` 00 (TBD-012 evidence) |
| ST-020 | pass | the output stays off through 20 setpoint changes |
| ST-023 | pass (step 1; step 2 is a person entry, step 3 on the mock) | |
| ST-024 | pass | invalid setpoints send nothing, valid ones are rounded |
| ST-029 | pass (both cases) | a `with` block ends with the output off, then the release |
| ST-031 | pass (step 2; step 1 is a person entry) | |
| ST-033 | pass | |
| ST-034 | pass (steps 1 to 3; step 4 on the mock elsewhere) | 3, 60 and 120 readings at 0.1, 2 and 4 per second; the CSV file written |
| ST-035 | pass | the ramp, and a ramp above the user limit refused |
| ST-039 | pass (on the log of ST-013) | |
| ST-041 | pass | after a killed process the next connection reports "A previous session may have left the output on (marker written 2026-10-03T00:36:33Z)" |
| ST-043 | step 2 pass; step 1 skipped (needs the same unit over USB, `MP305_HIL_DEVICE_HID`) | step 2 failed once, finding 1 |
| ST-047 | pass (on the logs of ST-006 and ST-018) | |

Batch A: 8 passed, 1 failed (ST-043 step 2, finding 1), 2 skipped. Batch
B: 11 passed, including the repeat of ST-043 step 2. No teardown reported
a problem; the supply was advertising with the output off after each
batch.

## Findings

1. In batch A the connect of ST-043 step 2, started right after the
   pre-flight's disconnect, did not see the supply advertising within the
   10 s find bound ("no supply found"), while every later connect of the
   session succeeded, and the repeat in batch B passed. Right after a
   disconnect the supply, or CoreBluetooth, can take longer than 10 s to
   show the next advertisement. A user who connects again right after a
   disconnect may therefore see "no supply found" once. To be put to the
   user: a second scan window inside `connect` before giving up, or a
   note in the library's documentation (TODO.md).
2. TBD-012 (remote control on hardware): the request `0xC8` with
   `remoteCon` 2 put the prompt on the supply's screen, the reply after
   the user's ALLOW was `0xC9` 00, commands with `remoteCon` 1 were then
   accepted, and the release at close was answered. The research note is
   to be updated.
3. The supply's firmware applied every setpoint and output change these
   tests sent and reported them back in the readings as the design
   expects; no deviation from device-model.md was seen.

## Not covered

The person entries (batch C), the entries with a load (batch D), USB, and
Linux and Windows.
