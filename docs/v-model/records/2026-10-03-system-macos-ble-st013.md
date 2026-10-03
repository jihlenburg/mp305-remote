# Verification record: system test ST-013 on macOS over Bluetooth

Date: 2026-10-03 (02:19 local time). Level: system (ST-013). Scope: the
first connection of the library to the user's MP305B, with the user's
go-ahead in the session for ST-013 including the release frame that
every close sends, and the user at the supply.

Commit: `e0a723d`. The run was made on commit `0ad7503` plus the change
of the find bound to 10 s (AR-014 revision 12, DD-DISC-011 revision 6,
DD-PROTO-060 revision 7, approved by the user on 2026-10-03 before the
run), which is committed together with this record.

OS: macOS 27.0.1, Apple arm64, the Mac's own Bluetooth adapter. CPython
3.10.19, pytest 9.1.1. Transport: Bluetooth LE. Firmware, from the
supply's `0xE1` reply in this run (payload
`e1 01 06 00 33 4d 50 33 30 35 42 00 00 02 00 02 00`): System Version
1.6.0.51 (bytes 1 to 4), model `MP305B`, Firmware Version 2.0.2.0 (bytes
13 to 16). The supply was on in DC mode with its own setpoints 12.0 V
and 0.5 A, the output off, nothing connected to the output.

## Commands

```sh
MP305_HIL=1 MP305_HIL_DEVICE=72de66a3-7c9b-58a3-a45b-cf098194d568 \
  MP305_HIL_PERSON=1 MP305_HIL_RECORD=<file> \
  uv run --no-sync pytest tests/system/test_readings.py -m hil -k st013 -s -rs -v
```

## What was sent

Two connections. The pre-flight connection (the first contact of this
installation's host ID with the supply): the fast bind was refused, the
prompt bind put the question on the supply's screen and the user pressed
ALLOW; then `0xE0`, `0xC2` polls, and at the close one release frame
(`0xC8` with `remoteCon` 0, `output` 0). The test's connection: the fast
bind was accepted at once (`19 00`, the host is remembered), `0xE0`, 273
`0xC2` polls over 61 s, and at the close one release frame. No command
with `remoteCon` 1 or 2 was sent, so no setpoint and no output state was
changed, and the supply's remote-control prompt did not appear.

## Results

| ST | Result | Observation |
|---|---|---|
| ST-013 | pass (`test_st013_readings_for_60_s_with_the_output_off`, macOS BLE) | 268 readings in 60 s, the output off in every one; shortest gap between a reply and the next request 101 ms (the rule is 100 ms) |

The first attempt, before the find bound was changed, failed at the
pre-flight with "no supply found": the 4 s scan before the connect did
not see the supply (finding 1). The second attempt, with 10 s, connected
within 3 s of the scan's start. In the test's connection the link went
`connecting`, `connected`, `binding`, `allowed`, `ready` within 0.3 s,
and every `0xC3` showed `output` 0, mode DC, setpoints 1200 and 500
(12.00 V, 0.500 A), no fault. The run's JSON record holds the supply's
versions and the frame log of the test's connection.

## Findings

1. The find bound of 4 s is too short on macOS: CoreBluetooth delivers
   the supply's advertisements seconds apart (research note of
   2026-09-29). Measured before the change: a 4 s scan saw the supply in 6
   of 8 tries, a 10 s scan in 3 of 3. The bound is now 10 s; a
   reconnection attempt can therefore take up to 20 s.
2. The supply reports System Version 1.6.0.51 now, where the entries of
   2026-09-29 recorded 1.6.0.40 after the update and left the update's
   status open: the update has taken effect.
3. The kept frame log ends before the test's close, because the
   `frame_log` fixture is torn down before the `supply` guard whose
   teardown closes the connection; the release frame's reply is therefore
   not in the record (it is in the firmware's analysis: a release without
   a grant is answered with status 0). The fixture order is to be
   changed so that the log covers the close (TODO.md).
4. The previous unit record of the discovery change
   (`2026-10-02-unit-discovery-rev5.md`) left the signal strength on
   Linux open; this run says nothing about it.

## Not covered

Every other system test, and every transport and OS but macOS over
Bluetooth.
