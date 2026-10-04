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

## Second session, with a person at the supply

2026-10-04, 01:40 to 01:56 local time, commit `fcb1131` (the library's
code is that of `615d949`). `MP305_HIL_PERSON=1` was set, the user was at
the supply. ST-013 is still not verified. What the runs showed:

| Adapter of halobox | Attempts | Outcome |
|---|---|---|
| Built in (MediaTek, USB `13d3:3604`) | 9 | never connected: 4 times "connect did not complete within 10 s", 3 times the scan of the HIL gate did not find the supply (each time right after such a connect), 2 times the find before the connect did not see it within 10 s |
| ASUS USB-BT600 dongle, plugged into halobox, as the only adapter | 3 | connected each time; the pre-flight's close then failed: "the close did not complete within 1.0 s" |

Through the dongle the pre-flight read the supply: model `MP305B`,
application version 1.6.0.51, hardware revision 2.0.2.0, output off,
setpoints 12.0 V and 0.5 A, live mode DC. The user pressed ALLOW in the
first of the three attempts. The second and third needed no prompt, so
the supply remembers the host. Sent to the supply in these three
sessions: the bind request, the information request, readings, and the
release frame of the close. The output stayed off.

Measurements on the same machine, without frames of the protocol:

- A plain connect with BlueZ's own tool takes 15.6 s through the built-in
  adapter and 0.8 to 2.1 s through the dongle. The library's bound is
  10 s.
- A plain disconnect takes 2.3 to 2.8 s. The library bounds the close of
  the transport with 1 s.
- Within one discovery of 10 s the controller scans for Bluetooth LE for
  about 5.3 s only. The built-in adapter then reports the supply after
  0.7 to 4.3 s, and in one of eight scans not at all.
- The dongle, listening without pause for 40 s, received 41
  advertisements of the supply, 0.40 to 2.57 s apart (median 0.84 s).

Findings (TODO.md): on Linux the close bound of 1 s is shorter than what
BlueZ needs to disconnect, so every close reports a failure; after the
library gives up a connect, BlueZ goes on with it in the background and
takes the supply's advertising away from the next scan; with two
adapters the library uses whichever comes first, which need not be the
one the identifier names.

## Third session, with the bounds of ADR-0017

2026-10-04, 18:06 to 18:20 local time, commit `459c394` (connect bound
20 s, close bound 5 s, the cancel of a failed connect awaited). Within
the user's go-ahead of this session to repeat ST-013 from Linux. Only
`MP305_HIL` was set. Adapter: the built-in one alone (the dongle was not
in the machine). ST-013 is still not verified.

| Attempt | Outcome |
|---|---|
| 1 | the scan of the HIL gate did not find the supply |
| 2 | "connect did not complete within 20 s"; log: "connect to hci0/dev_... expired; disconnect issued" |
| 3 | the same, 36 s later |
| 4 | the find before the connect did not see the supply within 10 s |

Nothing was sent to the supply; no connection came up. The Mac saw the
supply in three of three scans of 10 s during this time.

What the session shows:

- The awaited cancel works. After each expired connect the next attempt
  found the supply advertising again, where on 2026-10-04 at night the
  scan after a given-up connect never found it.
- The built-in adapter is the limit, not the bounds. Plain connects with
  BlueZ's own tool through it took 0.96, 15.87 and 4.31 s and once gave
  no result within 40 s, with and without a scan running. In the trace
  of attempt 4 the controller reported the supply once in the first scan
  window of 5.5 s, after 5.1 s, and not at all in the second of 5.2 s.
- The machine's Wi-Fi and Bluetooth are one module (MediaTek MT7925,
  kernel driver `mt7925e`), and the Wi-Fi link uses the 2.4 GHz band
  among others (2412 MHz, which overlaps the advertising channel at
  2402 MHz). The wired network ports have no link. That the Wi-Fi is the
  cause of the poor reception is inferred, not shown.

Tests without hardware on this machine at the same commit:
`cargo test --workspace --exclude mp305-app` passes with 392 tests, and
`pytest` has 201 passed and 1 skipped.

## Open

ST-013 from Linux needs an adapter that hears the supply: the ASUS
dongle in halobox, through which the connect took 0.8 to 2.1 s, or the
built-in adapter with the machine's Wi-Fi off the 2.4 GHz band or on a
wired network.
