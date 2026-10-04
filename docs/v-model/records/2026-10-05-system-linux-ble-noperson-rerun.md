# Verification record: system tests on Linux over Bluetooth without a person, rerun

Date: 2026-10-05, 00:55 to 01:01 local time (2026-10-04T22:55 to 23:01
UTC). Level: system. Scope: the rerun of the entries that need neither a
person, a load nor USB, after the reworded ST-034 (system tests revision
13) and the log bridge's cap for dependencies (py DD revision 7), within
the user's go-ahead of this session for the Linux entries without a
person.

Commit: `fc542ab` (a clone of the public repository on the machine).

Machine: the user's "halobox", Ubuntu 26.04.1 LTS, Linux 7.0.0-31-generic,
x86_64, no virtual machine. BlueZ 5.85. CPython 3.10.20, pytest 9.1.1,
Rust 1.93.1. Adapter: the ASUS USB-BT600 dongle as the machine's only
Bluetooth adapter (the built-in one unbound from `btusb` for the run,
bound again afterwards). Transport: Bluetooth LE. Firmware of the supply,
read in the run: System Version 1.6.0.51, Firmware Version 2.0.2.0.
Nobody was at the supply.

## Command

```sh
MP305_HIL=1 MP305_HIL_DEVICE=<the BlueZ identifier> MP305_HIL_RECORD=<file> \
  uv run --no-sync pytest tests/system -m hil -s -rs -v
```

No opt-in besides `MP305_HIL`. 10 tests passed, none failed, 42 skipped
(a person, a load or USB needed).

## Results

| ST | Result | Observation |
|---|---|---|
| ST-002 | pass | default scan 10.045 s; 1 s scan 1.040 s; 60 s scan 60.039 s |
| ST-004 | pass | connect by identifier; a simulated second supply is refused |
| ST-012 | pass for the automated part | a control call before the first reading is refused; the comparison with the screens is a reuse cell on Linux (ADR-0018) and open |
| ST-013 | pass | 154 readings in 60 s; the shortest time from a reply to the next request 100 ms |
| ST-017 | pass for step 1 | no overlapping requests in the frame log of ST-013 |
| ST-031 | pass for step 2 | step 1 needs a person |
| ST-033 | pass | |
| ST-034 | pass (revision 13) | counts in 30 s: 3 at 0.1 per second, 60 at 2 per second, both without a warning; 75 at 4 per second with exactly one warning, above the floor of 54 (90 % of the 2 per second of SR-013). The CSV follows SR-037; 4.1 per second raises `ValueError`. |
| ST-039 | pass for the log of ST-013 | the log of ST-008 needs a person |
| ST-043 | pass for step 2 | step 1 needs the unit over USB too |

Pre-flight: connected, output off, setpoints 12.0 V and 0.5 A, live mode
DC. No control command was sent; the output stayed off. Sent: bind,
information requests, reading requests, and the release frame of each
close.

## The log bridge on Linux

No "log records were dropped" warning in the whole run, where the run
before it (record `2026-10-05-system-linux-ble-noperson.md`) had two,
with 1073 and 1633 records. The record file of this run,
`2026-10-05T005518-system-linux-ble-noperson.json`, was written by the
run itself with the record writer of `44b2463`: it holds no address of
another device, the supply's address with its maker's prefix only, and
no dependency lines. It was stored as written.

## Open

ST-034 and the other entries of this run are verified on Linux over
Bluetooth through this dongle, in their parts without a person. The
entries that need a person, a load or USB have not run on Linux.
