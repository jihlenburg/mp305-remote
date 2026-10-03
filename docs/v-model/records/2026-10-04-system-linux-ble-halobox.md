# Verification record: system tests on Linux over Bluetooth, on a native machine

Date: 2026-10-04 local time (the run's stamps are 2026-10-03T23:27 to
23:29 UTC). Level: system (ST-002, and an attempt at ST-013). Scope: the
Python library on the user's machine "halobox", within the user's
go-ahead of this session for that machine.

Commit: `615d949` (a clone of the public repository on the machine).

Machine: Ubuntu 26.04.1 LTS, Linux 7.0.0-31-generic, x86_64, no virtual
machine. BlueZ 5.85. Bluetooth adapter: built in, USB `13d3:3604`, a
MediaTek controller (HCI 5.4). CPython 3.10.20, pytest 9.1.1, Rust
1.93.1. Transport: Bluetooth LE. Firmware of the supply: System Version
1.6.0.51, Firmware Version 2.0.2.0 (record
`2026-10-03-system-macos-ble-st013.md`); not read in this run, since no
connection got past the bind.

## Commands

```sh
uv run maturin develop -m crates/mp305-py/Cargo.toml
MP305_HIL=1 MP305_HIL_DEVICE=<the BlueZ identifier> MP305_HIL_RECORD=<file> \
  uv run --no-sync pytest tests/system/test_discovery.py -m hil -k st002 -rs -q
MP305_HIL=1 MP305_HIL_DEVICE=<the BlueZ identifier> MP305_HIL_RECORD=<file> \
  uv run --no-sync pytest tests/system/test_readings.py -m hil -k st013 -s -rs -v
```

No opt-in besides `MP305_HIL` was set. The identifier came from a scan
through the library on the same machine (`hci0/dev_...`).

## Results

| ST | Result | Observation |
|---|---|---|
| ST-002 | pass (`test_st002_scan_times`) | default scan 10.025 s; 1 s scan 1.023 s; 60 s scan 60.025 s |
| ST-013 | not verified: nobody was at the supply to confirm the connection | see below |

Scan through the library before the run: one supply, unit `E!K`, remote
flag set, RSSI -52 dBm.

## The attempt at ST-013

The pre-flight connection reached the supply: the library connected over
BlueZ, sent the bind request, and the supply answered that it does not
know this installation's host ID. The library logged "Confirm the
connection on the supply's screen within 30 seconds". Nobody was at the
supply and `MP305_HIL_PERSON` was not set, so the pre-flight gave up
(record: `connected` false, "the supply does not recognise this
installation's host ID"). No reading was requested and no control frame
was sent.

This is the first exchange of protocol frames with the supply from Linux:
the connection, the service discovery and the bind request and reply work
on native BlueZ with the machine's own adapter.

The test itself then failed instead of skipping: its connect came while
the close of the pre-flight's session was still running in the background
("a session to hci0/dev_... is already open in this process"), and at
the end of the process that close had not completed within 1.0 s. That
is a defect of the test's pre-flight for a host the supply does not know
when no person is there (TODO.md), not a result about the library's
readings.

## Open

ST-013 from Linux needs one run with a person at the supply who presses
ALLOW (`MP305_HIL_PERSON=1`, `pytest -s`). After that the supply knows
the host and the entries without a person can run from this machine.
