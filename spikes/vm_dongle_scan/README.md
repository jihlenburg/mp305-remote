# Spike: does a Parallels VM see the supply through a USB Bluetooth dongle?

Throwaway experiment (see [docs/v-model/README.md](../../docs/v-model/README.md)).
Production code never imports this code and never copies it. The
documentation, lint and coverage rules do not apply here.

## Question

TBD-009: the Linux and Windows machines for hardware runs are Parallels
VMs on the Mac, which have no Bluetooth of their own. With a USB Bluetooth
dongle handed to a VM, does Linux (BlueZ) and does Windows see the
MP305B's advertising, with the name and the manufacturer data that
discovery matches on?

## Method

Scan only. No connection is made and no protocol frame is sent; the OS
scans actively, so it sends link-layer scan requests and receives the
scan response that carries the name. Nothing was installed in the guests.

- The dongle (ASUS, USB `0b05:1d70`, a Realtek controller) is assigned to
  one VM at a time: `prlsrvctl usb set '<device id>' '<vm>'`, then the VM
  is suspended and resumed so that Parallels hands the device over;
  `prlsrvctl usb del '<device id>'` puts it back to "ask".
- Linux: `scan_linux.sh` (`bluetoothctl` of BlueZ, 15 s).
- Windows: `scan_windows.ps1` (the Windows advertisement watcher in active
  mode, 15 s). Windows PowerShell 5.1 cannot subscribe to Windows Runtime
  events, so the script builds a small C# listener with the compiler that
  ships with the .NET Framework and runs it from the temp folder.
- A Windows VM with "pause when idle" must have that setting off for the
  run (`prlctl set '<vm>' --pause-idle off`), or it pauses mid-scan.

## Answer

Yes on both, 2026-10-02 (LOGBOOK, "USB Bluetooth dongle in the VMs").
Both systems report the name `0000MP305B  S             E!K`, the service
UUID `AF00` and the manufacturer data `AF FA 01 35 02 00` plus 14 zero
bytes under company `0xABBA`, as macOS does. On Windows the data and the
UUID arrive in the advertisement and the name in the scan response, as
two events. The captures are
`docs/research/captures/2026-10-02T103456-vm-dongle-scan-linux.jsonl` and
`2026-10-02T104520-vm-dongle-scan-windows.jsonl`; the findings are in
docs/research/device-model.md, section 1.
