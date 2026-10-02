# Verification record: system test ST-002 on Linux over Bluetooth

Date: 2026-10-02. Level: system (ST-002). Scope: discovery timing of the
Python library on the user's MP305B from Linux, within the user's
go-ahead of this session for scans without a connection in the VMs.

Commit: `44a627f` (a clone of the public repository in the VM).

OS: Ubuntu 24.04.5 LTS, Linux 7.0.0-38-generic, aarch64, a Parallels VM
on the user's Mac, BlueZ 5.72. Adapter: the USB Bluetooth dongle (ASUS,
`0b05:1d70`) assigned to the VM. CPython 3.10.22, pytest 9.1.1, Rust
1.99.0. Transport: Bluetooth LE, advertising only. Sent: nothing above
the link layer; no connection was made and no frame of the protocol was
sent. Firmware: not read in this run (LOGBOOK 2026-09-29, "Hardware:
read-only spike after the firmware update"). The supply was on with
remote control enabled; the user had said earlier in the session that
nothing is connected to its output.

## Commands

```sh
uv run maturin develop -m crates/mp305-py/Cargo.toml
uv run --no-sync python -c "import mp305; print(mp305.discover(5.0, bluetooth=True, usb=False))"
MP305_HIL=1 MP305_HIL_DEVICE=<the BlueZ identifier> MP305_HIL_RECORD=<file> \
  uv run --no-sync pytest tests/system/test_discovery.py -m hil -k st002 -rs -q
```

## Results

| ST | Result | Observation |
|---|---|---|
| ST-002 | pass (`test_st002_scan_times`, Linux BLE) | default scan 10.048 s; 1 s scan 1.052 s; 60 s scan 60.064 s; 0.5 s and 61 s raise `ValueError` |

The first scan (5 s) returned one supply: transport `ble`, identifier
`hci0/dev_0C_3D_5E_xx_xx_xx` (the last three octets masked here), unit
`E!K`, name `0000MP305B  S             E!K`, remote flag set, and no
signal strength (`rssi=None`). The run's JSON record shows no pre-flight
connection.

## Findings

1. The signal strength is missing on Linux. DD-DISC-012 reads
   `properties()` after `stop_scan`, and BlueZ drops a device's RSSI when
   discovery stops. SR-001 asks for the signal strength, and ST-001 checks
   it, so ST-001 would fail on Linux as the code stands. Discovery DD
   revision 5, drafted and pending approval, moves the read to the end of
   the scan window, before `stop_scan`.
2. This is the first run of the discovery glue on BlueZ: the adapter
   probe, the event stream, the accumulator's rule for cached devices and
   the classification by name all worked on the real stack.

## Not covered

- ST-002 on Windows. An attempt in the Windows VM found no Bluetooth
  adapter (`no backend for the enabled transports: Bluetooth`). During
  that attempt the Mac lost all its USB devices, the dongle included, so
  the result says nothing about the library on Windows; it is to be
  repeated when the dongle is back.
- Every system test that connects.
