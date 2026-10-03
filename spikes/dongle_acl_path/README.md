# Spike: where does data from a peer get lost behind the USB Bluetooth dongle?

Throwaway experiment (see [docs/v-model/README.md](../../docs/v-model/README.md)).
Production code never imports this code and never copies it. The
documentation, lint and coverage rules do not apply here.

## Question

On 2026-10-03 the Linux and the Windows VM could scan through the dongle
(ASUS USB-BT600, USB `0b05:1d70`, Realtek RTL8761CU) but not connect: the
link came up and no data packet ever arrived
(docs/v-model/records/2026-10-03-system-vm-ble.md). Which part loses the
data: the guest's driver or missing firmware, the USB passthrough of
Parallels, the supply, the dongle, or the Mac?

## Method

HCI over USB uses four pipes: commands on the control endpoint, events on
interrupt IN `0x81`, data to the controller on bulk OUT `0x02`, data from
the controller on bulk IN `0x82`. The scripts watch each of them.

- `vm_loopback.py`, in the Linux VM as root: HCI local loopback through a
  raw HCI socket. One data packet goes out and should come back. No radio
  traffic.
- `host_hci.py loopback`, on the Mac: the same test through libusb, with
  no VM and no Bluetooth stack between the script and the dongle.
- `host_hci.py connect --peer supply`, on the Mac: scan, connect to the
  supply, read its link-layer features and version, send an ATT Exchange
  MTU Request and an ATT Read By Group Type Request, wait, disconnect. No
  frame of the supply's own protocol is sent.
- `host_hci.py connect --peer mac` with `mac_peripheral.py` running: the
  same against the Mac's built-in Bluetooth, which advertises a test
  service. The first request is a read of the test characteristic, and
  `mac_peripheral.py` prints every read request that reaches it.

On the Mac `host_hci.py` needs the dongle on the host: no VM may hold it
(suspend a VM that does). It needs libusb from Homebrew. On Linux
`--hci N` runs the same test through the kernel's HCI user channel of
hciN, as root with the adapter down. The commands are in the scripts'
headers. In the capture files the advertising reports are written when the
scan ends, so they all carry that time.

In the Linux VM the stock `btusb` binds the dongle as a generic adapter and
loads no firmware. For the runs with firmware, `btusb` was built from the
kernel's source with the entry of the upstream patch of July 2026
(`{ USB_DEVICE(0x0b05, 0x1d70), .driver_info = BTUSB_REALTEK |
BTUSB_WIDEBAND_SPEECH }`) and loaded in place of the stock module. It then
loads `rtl_bt/rtl8761cu_fw.bin` from the `linux-firmware-realtek` package
and reports `RTL: fw version 0x7bf15762`. The dongle keeps the loaded
firmware until it loses power, so the runs on the Mac afterwards had it
too (HCI revision `0x7bf1`, LMP subversion `0x5762`).

## Answer

The dongle on this Mac's USB. The same dongle works on a PC, so the unit
is sound; on the Mac its received data never reaches the USB host, with
and without a VM (2026-10-04; LOGBOOK, "The dongle delivers no received
data, also without a VM" and "The dongle works on halobox: the fault is
on the Mac's side").

1. With the firmware loaded in the Linux VM the connection to the supply
   fails as before. A USB trace (`usbmon`) shows the driver's two reads on
   bulk IN being submitted when the adapter opens and never completing,
   while bulk OUT, the control endpoint and interrupt IN work.
2. On the Mac, without a VM, the same happens with the supply as the peer
   (`2026-10-03T224341-dongle-acl-supply.jsonl`): the connection is
   created, the feature and version queries are answered, the link stays
   up for 10 s with a supervision timeout of 2 s, the controller reports
   both requests as sent, and nothing arrives on bulk IN.
3. With the Mac's built-in Bluetooth as the peer
   (`2026-10-03T224614-dongle-acl-mac.jsonl`) the Mac printed the read
   request and answered it. The answer never arrived on bulk IN. So the
   direction from the host to the peer works, and the direction from the
   peer to the host is lost.
4. That clears the guests' drivers, the supply and the library. On the
   Mac it makes no difference whether the dongle sits on a USB hub or on
   a port of the Mac, whether its firmware is loaded, or whether a VM is
   in the path.
5. In the Linux machine halobox (x86_64, kernel 7.0, the stock `btusb`
   without the firmware) the same script, through the kernel's HCI user
   channel, receives four data packets from the Mac, among them the
   answer to the read request
   (`2026-10-03T233607-dongle-acl-mac-linux.jsonl`). The loopback test
   returns its packet there too.
6. So the loopback test is a valid test on this controller, and its
   failure on the Mac, in the VM and through libusb, shows the same loss
   as the connection tests: nothing sent by the dongle on bulk IN arrives
   at a host on this Mac.
7. On the Mac the controller answers "Set Controller To Host Flow
   Control" with "unknown command", and setting the host buffer size
   changes nothing.

Not answered: why macOS loses the bulk IN data of this device (a
full-speed device on an Apple silicon Mac, macOS 27.0.1). Parallels and
libusb both go through the same USB host layer of macOS, and both fail.

A second side result: the `scan` action of `host_hci.py` listens without
duplicate filtering and prints when the peer's advertisements arrive. In
halobox the dongle received 41 advertisements of the supply in 40 s, 0.40
to 2.57 s apart (LOGBOOK 2026-10-04, "ST-013 on halobox with the user at
the supply").

A side result is in docs/research/device-model.md, section 2.1: the
supply's Bluetooth chip reports link-layer version 5.3 and the company
identifier of the CH58x's maker.
