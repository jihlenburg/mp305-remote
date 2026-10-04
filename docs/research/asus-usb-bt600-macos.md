# ASUS USB-BT600 receive failure on macOS

Updated 2026-10-04. This concerns the USB Bluetooth adapter, not the
MP305B's USB interface or firmware. The user requested diagnosis after
reconnecting the adapter to the Mac. No power-supply command or radio
connection is needed for the local-loopback experiments below.

## Evidence and current limit

**Confirmed on hardware:** ASUS USB-BT600, USB `0b05:1d70`, reports
USB 1.1, full speed (12 Mbit/s), with 64-byte bulk endpoints `0x02`
(OUT) and `0x82` (IN), plus interrupt IN `0x81`. Interface 0 has one
alternate setting, 0. The separate audio interface has alternate settings
0 to 6. The controller reports HCI revision `0x000e` and LMP subversion
`0x8761`, matching the factory-firmware state of the earlier experiments.

The Mac runs macOS 27.0.1, build 26A434, Darwin 27.0.0, arm64. The
initial connection is directly below `AppleT6000USBXHCI@01000000`, at
USB location `0x01100000`. During cases 01 to 14, all VMs were stopped
or suspended and the dongle was assigned to the host. libusb is Homebrew
1.0.30. Successful serial
probes claim interface 0 exclusively; libusb reports no active kernel
driver on that interface once configured.

**Confirmed on hardware:** both libusb's C API and Apple's IOUSBLib API
can reset the controller, read its version, enter local loopback and send
an ACL packet. The controller emits a Number Of Completed Packets event
for that packet. Neither path delivers its returned ACL data to the host.
The direct IOUSBLib call returns `0xe0004051`,
`kIOUSBTransactionTimeout`. `GetPipeStatus` then returns `0xe000404f`,
`kIOUSBPipeStalled`, after all three pipes initially reported success.
This is the host API's status; it does not establish that an electrical
STALL handshake was observed on the USB wire.

**Inference:** the failure reproduces below Python, libusb, the Bluetooth
host stack and the virtual machine. It also requires neither radio nor
the supply. The earlier success on halobox shows the unit can return
data and execute local loopback. A compatibility problem in the Mac USB
host/device interaction is therefore the leading explanation. These
results do not yet distinguish a host-controller/driver defect from a
device USB behavior that this host exposes. They do not prove defective
Mac hardware or identify a particular kernel bug.

## Experiment record

Code baseline: `f93c71b` plus the uncommitted probes in
`spikes/dongle_acl_path/`. The older probe's background reader discarded
non-timeout USB errors and used PyUSB. The replacement calls the libusb
C API directly and records return status and partial byte counts. A
second probe uses IOUSBLib directly, with pipe addresses obtained from
Apple's own API. Captures are created exclusively and remain unedited.

Every loopback test sends HCI Reset, Read Local Version and Write
Loopback Mode (local), then one ACL packet. HCI Reset is sent again at
exit and the interface is released. The controller version reply is
preserved in every completed capture. The power supply's version is not
applicable because no connection to it is made.

The capture prefix is `2026-10-04-dongle-usb-loopback-`, under
`docs/research/captures/`; the suffixes below include the file extension.

| Capture suffix | Method or changed variable | Result |
|---|---|---|
| `01-default.jsonl` | libusb, 1028-byte receive buffer, 16-byte payload, 1.5 s timeout | Receive timeout, zero bytes; outbound completion event |
| `02-size64.jsonl` | 64-byte receive buffer | Same |
| `03-size1024.jsonl` | 1024-byte receive buffer | Same |
| `04-before.jsonl` | Start the receive before sending, buffer 64 | Same |
| `05-clearhalt.jsonl` | Clear bulk-IN halt before the test | Same |
| `06-alt0.jsonl` | Explicitly select interface 0 alternate setting 0 | Same |
| `07-config.jsonl` | Explicitly reapply configuration 1 | Same |
| `08-fullpacket.jsonl` | 60-byte payload plus 4-byte ACL header, buffer 64 | Same |
| `09-twopackets.jsonl` | 124-byte payload plus header, buffer 128 | Same |
| `10-longwait.jsonl` | Ten-second receive timeout | Same; returned after about 10.16 s |
| `11-no-idle-polls.jsonl` | Stop reading events at Command Complete, avoiding interrupt-read timeouts before the ACL transfer | Same |
| `12-debug.jsonl` | A debug invocation started before case 11 had released the interface | Inconclusive: exclusive claim refused with `LIBUSB_ERROR_ACCESS`; no loopback command sent |
| `13-debug-serial.jsonl` | Debug invocation repeated after case 11 finished | Receive timeout, zero bytes; libusb maps endpoint `0x82` to pipe 3 and receives kernel timeout status |
| `14-iokit.jsonl` | IOUSBLib directly, without libusb; synchronous bulk read | `kIOUSBTransactionTimeout`; receive pipe reports stalled afterwards |

The completed libusb cases return `LIBUSB_ERROR_TIMEOUT` (`-7`) with
zero transferred bytes. There is no hidden non-timeout receive error in
these replacements. The accidental overlap in case 12 is kept as its own
attempt and is not evidence of an ordinary ownership problem.

Commands are recorded in the Python captures. The IOUSBLib probe was
built and run as follows, with stdout written to a newly created capture:

```sh
clang -Wall -Wextra -Wno-deprecated-declarations -framework IOKit \
  -framework CoreFoundation spikes/dongle_acl_path/iokit_loopback.c \
  -o /tmp/mp305-iokit-loopback
/tmp/mp305-iokit-loopback
```

The SDK's `IOKit/usb/USB.h` defines the two return codes, and
`IOKit/usb/IOUSBLib.h` documents that a failed `ReadPipeTO` does not
provide a valid byte count or buffer. The capture therefore reports no
valid bytes for that failure, rather than interpreting the unchanged
requested length as received data.

## Ubuntu VM comparison

**Confirmed on hardware, 2026-10-04:** the user installed OpenSSH Server
in the Ubuntu 26.04.1 ARM64 VM. The dongle was attached by Parallels
27.0.1 (58670), with USB 3 support enabled and automatic Bluetooth sharing
disabled. The guest runs kernel `7.0.0-38-generic`, BlueZ
`5.85-4ubuntu0.2` and libusb package `2:1.0.29-2build1`. It sees the
dongle at `1-2.1`, bus 1 address 3, full speed, as `hci0` using the stock
`btusb` module. No replacement driver or firmware was loaded for these
runs. Read Local Version again reports revision `0x000e`, subversion
`0x8761`.

Captures use the same prefix as above. Each row also has a USB trace
capture formed by inserting `-usbmon` before `.jsonl`.

| Capture suffix | Method | Result |
|---|---|---|
| `15-ubuntu-btusb.jsonl` | Initial HCI user-channel attempt after stopping Bluetooth and bringing hci0 down | Inconclusive: bind returned errno 16, busy; no probe command sent. The trace reader also failed. |
| `16-ubuntu-libusb.jsonl` | Direct libusb with temporary kernel-driver detachment, 64-byte receive buffer | Receive timeout after 1.507 s, zero bytes; outbound completion event. HCI capture valid, USB trace reader failed. |
| `17-ubuntu-btusb.jsonl` | HCI user channel after temporarily masking Bluetooth activation and verifying hci0 down | No ACL packet received in 3 s; outbound completion event. USB trace valid. |
| `18-ubuntu-libusb.jsonl` | Direct libusb repeated with repaired trace reader | Receive timeout after 1.508 s, zero bytes; outbound completion event. USB trace valid. |

The initial trace reader did not handle a nonblocking read returning
`EAGAIN` after readiness. Both empty trace attempts are retained, but
their `probe_exit_code` fields are not evidence of successful tracing.
The wrapper now retries that condition, records reader errors and fails
when either the reader or probe fails. Cases 17 and 18 used that repair.

In case 17, `btusb` submitted two 1028-byte bulk-IN requests before the
loopback packet was sent. The 20-byte bulk-OUT transfer completed with
status 0. Both reads stayed pending until socket teardown, then completed
with status `-2` and length 0. In case 18, the 20-byte write completed
with status 0; the subsequent 64-byte bulk-IN request completed with
status `-2` and length 0 after the libusb timeout. The controller's
Number Of Completed Packets event arrived on interrupt IN in both cases.
Driver reattachment submitted new receive requests, also visible at the
end of case 18's trace.

The kernel documents `-ENOENT` in a completion status as cancellation by
unlinking, not an endpoint stall. Also, usbmon records driver requests
and callbacks at the host-controller boundary, not physical USB packets.
These traces show that no data was delivered to either guest receive
path, but cannot distinguish the dongle NAKing physical IN transactions
from data lost by the host. Sources:
[USB error codes](https://docs.kernel.org/driver-api/usb/error-codes.html),
[usbmon](https://docs.kernel.org/usb/usbmon.html).

The successful capture procedure, run as root from
`/tmp/mp305-usb-diag-20261004` after copying the spike scripts there, was:

```sh
systemctl mask --runtime --now bluetooth
hciconfig hci0 down
sleep 1
hciconfig hci0
modprobe usbmon
python3 usbmon_probe.py --capture 2026-10-04-dongle-usb-loopback-17-ubuntu-btusb-usbmon.jsonl -- python3 linux_loopback.py --hci 0 --capture 2026-10-04-dongle-usb-loopback-17-ubuntu-btusb.jsonl
python3 usbmon_probe.py --capture 2026-10-04-dongle-usb-loopback-18-ubuntu-libusb-usbmon.jsonl -- python3 usb_loopback.py --detach-kernel-driver --stop-at-command-complete --read-size 64 --capture 2026-10-04-dongle-usb-loopback-18-ubuntu-libusb.jsonl
```

An EXIT trap ran `hciconfig hci0 up`, `systemctl unmask --runtime
bluetooth`, `systemctl start bluetooth` and `modprobe -r usbmon`.
Completed probes reset the controller; libusb released the interface
and reattached its kernel driver successfully. Final inspection confirmed
Bluetooth active and enabled, hci0 UP RUNNING, usbmon unloaded and the
device's original power control `auto` unchanged. Guest and local capture
SHA-256 hashes match. The VM remains running with the dongle attached.
No supply connection was made and no ST or AT result is credited.

**Inference:** changing from native macOS to Linux in this VM does not
remove the failure. It reproduces with and without the guest Bluetooth
driver, matching the earlier native IOUSBLib result. The common Mac USB
host/device interaction remains implicated; the guest alone is not a
workaround. This does not identify the exact controller, driver or device
implementation defect.

## Further discrimination

### NINA-B506 alternative controller candidate

On 2026-10-04 the user asked whether their attached u-blox NINA-B506
evaluation board could be used. **Confirmed on hardware by USB/serial
enumeration:** the Mac reports an FTDI `0403:6015` device named
`U-BLOX EVB-NINA-B506`, at `/dev/cu.usbserial-DP051L4K`, and a SEGGER
J-Link `1366:0105` with serial port `/dev/cu.usbmodem0004831547401`.
No serial command, debugger connection or firmware write was made.
The installed application firmware remains unidentified.

**Confirmed in vendor documentation and example code:** the NINA-B50
uses an MCX W71. NXP provides an HCI Black Box application for that chip's
FRDM board. Its source parses HCI ACL packets as well as commands and
forwards controller packets back over UART. The u-blox EVK guide requires
board-file adaptation for NXP SDK examples and matching radio-core NBU
firmware and keys. It identifies the FTDI port as the module UART; the
J-Link serial port is an extra UART not normally connected to the module.
The documented factory application is a beacon demo, not this HCI bridge.

**Inferred feasibility, not hardware confirmation or a design decision:**
adapt the HCI firmware to the EVK, pass its FTDI USB interface into Ubuntu,
and attach the UART controller to BlueZ using H4. If initialization and
GATT traffic work, the project's existing Linux Bluetooth backend should
be usable without a new application transport. This changes both the
radio and USB bridge, so success would provide a workaround, not isolate
the ASUS defect. The first implementation prerequisite is identifying
the installed firmware and a recovery procedure before replacing it.
No firmware replacement or production change was approved in this
feasibility discussion.

Sources: [NINA-B50 product](https://www.u-blox.com/en/product/nina-b50-series-open-cpu),
[EVK guide, sections 2.1.3, 2.1.4, 2.2 and 4.4.2](https://content.u-blox.com/sites/default/files/documents/EVK-NINA-B50_UserGuide_UBX-23007761.pdf),
[NXP HCI Black Box](https://mcuxpresso.nxp.com/mcuxsdk/latest/html/examples/wireless_examples/ble_controller/hci_bb/readme.html),
[HCI bridge source](https://github.com/nxp-mcuxpresso/mcuxsdk-examples/blob/main/wireless_examples/ble_controller/hci_bb/hci_bb.c),
[UART controllers with BlueZ](https://docs.zephyrproject.org/latest/samples/bluetooth/hci_uart/README.html#using-the-controller-with-bluez).

### Remaining ASUS comparisons

The user was asked to move the idle dongle to another USB-C port using
the same adapter, then requested the Ubuntu comparison above instead.
The port/controller comparison remains pending.

A second native probe, `usbhost_loopback.m`, has been
built against the modern IOUSBHost framework. It permits comparison
with the older IOUSBLib path and, separately, an idle-timeout experiment
that restores the original timeout afterwards. No result is claimed for
these pending comparisons.

If both native APIs and different host-controller paths fail, a USB
transaction trace or a controlled comparison on another OS/host is
needed to locate the remaining failure inside the host/device boundary.
Ordinary HCI logs cannot show whether the host sent IN tokens, the device
NAKed them, or data was lost after reaching the host controller.

Earlier experiments and the successful Linux control are recorded in
[the spike](../../spikes/dongle_acl_path/README.md) and LOGBOOK.md,
2026-10-04, "The dongle works on halobox: the fault is on the Mac's side".
