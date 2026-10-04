# Verification record: ST-013 on Linux over Bluetooth

Date: 2026-10-05, 00:08 to 00:10 local time (2026-10-04T22:08 to 22:10
UTC). Level: system (ST-013). Scope: the Python library on the user's
machine "halobox", within the user's go-ahead of this session to repeat
ST-013 from Linux; the user had switched the supply on with remote
control enabled and plugged the dongle into halobox.

Commit: `dda48f8` (a clone of the public repository on the machine; the
library's code is that of `1cbcb09`, the implementation of ADR-0017).

Machine: Ubuntu 26.04.1 LTS, Linux 7.0.0-31-generic, x86_64, no virtual
machine. BlueZ 5.85. CPython 3.10.20, pytest 9.1.1, Rust 1.93.1.
Adapter: the ASUS USB-BT600 dongle (USB `0b05:1d70`, Realtek RTL8761CU,
under the stock `btusb`), as the machine's only Bluetooth adapter: the
built-in adapter was unbound from `btusb` for the run and bound again
afterwards (record `2026-10-04-system-linux-ble-halobox.md` on why).
Transport: Bluetooth LE. Firmware of the supply, read in this run:
System Version 1.6.0.51, Firmware Version 2.0.2.0.

## Command

```sh
MP305_HIL=1 MP305_HIL_DEVICE=<the BlueZ identifier> MP305_HIL_RECORD=<file> \
  uv run --no-sync pytest tests/system/test_readings.py -m hil -k st013 -s -rs -v
```

No opt-in besides `MP305_HIL`. The identifier came from a scan through
the library on the same machine (`hci1/dev_...`, RSSI -76 dBm).

## Result

| ST | Result | Observation |
|---|---|---|
| ST-013 | pass (`test_st013_readings_for_60_s_with_the_output_off`), first attempt | 195 readings in 60 s; the shortest time from a reply to the next request 101 ms |

Pre-flight: connected, output off, setpoints 12.0 V and 0.5 A, live mode
DC. The supply recognised the host (allowed on 2026-10-04), so no prompt
appeared and nobody was at the supply. The output stayed off. Sent to the
supply in the test's own session: the bind request, the information
request, 202 reading requests and the release frame of the close, which
the supply answered with `C9 00`. The pre-flight's session sent the same
kinds of frame.

From the log of the test's session: the connect took 2.4 s, the bind was
answered 0.15 s later, and the close of the transport took 1.9 s after
the release was accepted. With the reply bound of 1 s that the close had
before ADR-0017, this close would have been reported as failed.

## Run record

`2026-10-05T000844-system-linux-ble-st013.json` is the run's record file,
reduced for the repository: the last three octets of the supply's
address are masked, and of the retained log only the lines of the
library's own loggers are kept. Removed were 6705 TRACE lines of the
Bluetooth dependencies and 19 lines that name other devices in range.

Two findings about the test harness on Linux, both in TODO.md. The log
kept for the frame checks takes in the TRACE lines of the Bluetooth
dependencies, which name every device in range; and during the connect
the library's log bridge reported "5383 log records were dropped". ST-013
does not depend on the dropped lines: its frames are in the log from the
first reading on.

## Open

ST-013 is verified on Linux through this dongle. Through halobox's
built-in adapter it is not; that adapter hears the supply too rarely as
the machine is set up.
