# Verification record: system test ST-002 on macOS over Bluetooth

Date: 2026-10-02. Level: system (ST-002). Scope: discovery timing of the
Python library on the user's MP305B, the first run of a system test on
hardware, with the user's go-ahead in the session for discovery only (no
connection).

Commit: uncommitted. Diff summary: `tests/system/conftest.py` (the
pre-flight connection moved out of the HIL gate into its own fixture, so
that the entries that only discover make no connection); this record;
TODO.md; LOGBOOK.md. The library under test is the build of commit
`d2ee627`.

OS: macOS 27.0.1, Apple arm64 (the Mac's own Bluetooth adapter). CPython
3.10.19, pytest 9.1.1, `mp305` 0.1.0. Transport: Bluetooth LE,
advertising only. Sent: nothing above the link layer (the OS scans; no
connection was made and no frame of the protocol was sent). Firmware: not
read in this run; the unit's versions are in LOGBOOK 2026-09-29
("Hardware: read-only spike after the firmware update"). The supply was
on, remote control enabled, nothing connected to its output.

## Commands

```sh
# one scan to learn the identifier macOS gives the unit
uv run --no-sync python -c "import mp305; print(mp305.discover(5.0, bluetooth=True, usb=False))"
MP305_HIL=1 MP305_HIL_DEVICE=72de66a3-7c9b-58a3-a45b-cf098194d568 \
  MP305_HIL_RECORD=<file> \
  uv run --no-sync pytest tests/system/test_discovery.py -m hil -k st002 -rs -v
```

## Results

| ST | Result | Observation |
|---|---|---|
| ST-002 | pass (`test_st002_scan_times`, macOS BLE) | default scan 10.003 s; 1 s scan 1.006 s; 60 s scan 60.006 s; 0.5 s and 61 s raise `ValueError` |

The first scan (5 s) returned one supply:
`Found(transport='ble', identifier='72de66a3-7c9b-58a3-a45b-cf098194d568',
unit_id='E!K', name='0000MP305B  S             E!K', rssi=-22,
remote_flag=True)`. The identifier is the one the read-only spike of
2026-09-29 had on this Mac. The run's JSON record shows no pre-flight
connection and no supply versions, as intended for a discovery-only run.

## Notes and open points

- ST-002 on Linux and Windows (the VMs with the dongle) and every other
  system test are still to be run.
- Step 3 of ST-002 is also covered without a supply by
  `test_st002_step3_out_of_range_scan_times_raise_value_error`.
- The HIL gate as first written connected once at the start of every
  hardware run (a pre-flight that checks the output state), which would
  have put the bind prompt on the supply's screen during a discovery-only
  run. It now connects only before the first test that connects.
