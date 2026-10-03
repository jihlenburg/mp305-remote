# Verification record: system tests from the VMs over the USB Bluetooth dongle

Date: 2026-10-03 evening and 2026-10-04 just after midnight (local time).
Level: system (ST-002, and an attempt at ST-013). Scope: the Python
library on Linux and on Windows in the Parallels VMs with the USB
Bluetooth dongle, within the user's go-ahead of the session for scans and
for one read-only connection from each VM.

Commit: `37b60cd` (a clone in the Ubuntu VM, the source archive of that
commit in the Windows VM).

Machines: Ubuntu 24.04.5, Linux 7.0.0-38, aarch64, BlueZ 5.72, CPython
3.10.22, Rust 1.99.0. Windows 11 Pro (10.0.26200), ARM64, with the x86_64
toolchain and CPython 3.10.22 x86_64 under emulation; the tests ran as
the logged-in user. Adapter in both: the USB dongle `0b05:1d70` (a
Realtek RTL8761, HCI and LMP version 0x0e), driven by the generic
drivers of both systems. Transport: Bluetooth LE. Firmware of the supply:
System Version 1.6.0.51, Firmware Version 2.0.2.0 (record
`2026-10-03-system-macos-ble-st013.md`); not read in these runs, since no
connection got that far. Nothing was connected to the supply's output.

## Results

| ST | OS | Result | Observation |
|---|---|---|---|
| ST-002 | Windows | pass (`test_st002_scan_times`) | default scan 10.016 s; 1 s scan 1.047 s; 60 s scan 60.031 s |
| ST-002 | Linux | pass on 2026-10-02 (record `2026-10-02-system-linux-ble-discovery.md`) | |
| ST-013 | Windows | not verified: the connect failed | `transport: connect did not complete within 10 s`; no prompt on the supply |
| ST-013 | Linux | not verified: the connect failed | `transport: Service discovery timed out`; no prompt on the supply |

Scans through the library: on Windows the supply is found with name,
unit `E!K`, remote flag and RSSI -34 dBm; on Linux with RSSI -29 dBm,
which verifies discovery DD revision 5 on BlueZ (the open point of the
record `2026-10-02-unit-discovery-rev5.md`).

## Why the connections failed

The failures are in the test setup, below the library, and the supply
was never asked anything (no bind frame was sent).

1. Linux, from a capture of the HCI traffic (`btmon`): the connection is
   created, the remote features are read, BlueZ sends the ATT Exchange
   MTU Request, the controller reports the packet as sent, and no data
   packet is ever received. The same with the request's MTU set to 247
   instead of 517.
2. The same dongle receives no data packet from a second peer either:
   asked for its service list over classic Bluetooth, the user's own Mac
   got two requests (sent according to the controller) and the VM
   received nothing back, while HCI events (the remote name) arrived.
3. Neither system loaded a vendor firmware for the dongle: Linux's
   `btusb` binds it as a generic adapter (no Realtek firmware line in the
   kernel log), Windows uses Microsoft's "Generic Bluetooth Adapter"
   driver. Windows' own stack fails the same way (its services request
   ends "unreachable" after 38 s).
4. So this dongle, as it is driven in the two VMs, can scan but receives
   no data. Whether the cause is the missing vendor firmware or the USB
   passthrough of its data endpoint is not decided.

A handling note: passing the dongle between the VMs by suspend and
resume left it unresponsive in Linux (HCI resets timed out); a reboot of
the VM brought it back.

## Open

Connecting from Linux and Windows is not verified on hardware. It needs
a Bluetooth adapter that works in the VMs (the dongle's vendor driver in
Windows; on Linux a kernel that loads its firmware, or another dongle),
or native machines.

## Follow-up, 2026-10-04

The question left open in point 4 is settled (LOGBOOK 2026-10-04, "The
dongle delivers no received data, also without a VM";
spikes/dongle_acl_path). The dongle is an ASUS USB-BT600 (Realtek
RTL8761CU). With its firmware loaded by a `btusb` that knows it, the
connection from the Linux VM fails in the same way. Driven from the Mac
through libusb, without a VM, it also receives no data packet, from the
supply and from the Mac's built-in Bluetooth, although that peer got the
dongle's request and answered it. So neither the missing firmware nor the
USB passthrough is the cause: the dongle delivers no received data to its
host. A Linux kernel that loads the firmware, named under "Open" above,
does not help. The vendor driver in Windows was not tried. Another
adapter or native machines are needed.

Second follow-up, 2026-10-04: in a native Linux PC the same dongle
receives data, also without its firmware (LOGBOOK 2026-10-04, "The dongle
works on halobox: the fault is on the Mac's side"). The loss is tied to
this Mac's USB host side, which Parallels and libusb share. A VM on this
Mac will therefore not connect through this dongle, whatever the guest
loads.
