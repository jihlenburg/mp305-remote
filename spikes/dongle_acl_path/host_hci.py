"""Spike: speak HCI to the USB Bluetooth dongle directly, without the
operating system's Bluetooth stack.

On the Mac the script goes through libusb: commands go out on the control
endpoint, events come in on interrupt IN 0x81, ACL data goes out on bulk
OUT 0x02 and comes in on bulk IN 0x82. No virtual machine may hold the
dongle:

    uv run --no-project --with pyusb python host_hci.py loopback
    uv run --no-project --with pyusb python host_hci.py connect --peer supply --capture FILE
    uv run --no-project --with pyusb python host_hci.py connect --peer mac --capture FILE

On Linux `--hci N` takes the adapter hciN through the kernel's HCI user
channel instead, which hands the script every packet and keeps BlueZ out.
The kernel's `btusb` then does the USB transfers. As root, with the
adapter down:

    hciconfig hci1 down
    python3 host_hci.py connect --hci 1 --peer mac --capture FILE

`connect` scans, connects to the peer, reads the peer's link-layer features
and version, sends an ATT Exchange MTU Request and an ATT Read By Group
Type Request, waits for data, and disconnects. It sends no frame of the
supply's own protocol. `--peer mac` needs mac_peripheral.py running and
first sends a Read By Type Request for that script's characteristic, which
the script reports when it arrives.
"""

import argparse
import ctypes
import datetime
import json
import platform
import select
import socket
import struct
import sys
import threading
import time

LIBUSB = "/opt/homebrew/lib/libusb-1.0.dylib"
VID, PID = 0x0B05, 0x1D70
# The supply: its address prefix and the start of its manufacturer data
# (company 0xABBA, then AF FA; docs/research/device-model.md, section 1).
SUPPLY_OUI = bytes.fromhex("0c3d5e")
SUPPLY_MARK = bytes.fromhex("baabaffa")
# The service UUID of mac_peripheral.py, as it appears in advertising data.
MAC_MARK = bytes.fromhex("01006761696462353033706d01003d5a")
# The characteristic UUID of mac_peripheral.py, in the byte order of ATT.
MAC_CHAR = bytes.fromhex("01006761696462353033706d02003d5a")


class Dongle:
    """An HCI transport to the dongle, with a log of what crossed it."""

    stack = ""

    def __init__(self):
        self.t0 = time.time()
        self.log = []
        self.secret = None
        self.acl_in = []

    def note(self, kind, data):
        text = data.hex()
        if self.secret is not None:
            text = text.replace(self.secret.hex(), "xxxxxx" + self.secret[3:].hex())
        self.log.append({"t": round(time.time() - self.t0, 3), "hci": kind, "hex": text})

    def cmd(self, opcode, params=b""):
        packet = struct.pack("<HB", opcode, len(params)) + params
        self.send_command(packet)
        self.note("command", packet)

    def acl_out(self, handle, cid, payload):
        l2cap = struct.pack("<HH", len(payload), cid) + payload
        packet = struct.pack("<HH", handle, len(l2cap)) + l2cap
        self.send_acl(packet)
        self.note("acl out", packet)

    def close(self):
        self.cmd(0x0C03)
        self.events(0.5)


class UsbDongle(Dongle):
    """The dongle through libusb (the Mac)."""

    stack = "none: HCI through libusb (pyusb), one pending read on bulk IN"

    def __init__(self):
        super().__init__()
        import usb.backend.libusb1
        import usb.core
        import usb.util

        self.usb = usb
        backend = usb.backend.libusb1.get_backend(find_library=lambda _: LIBUSB)
        self.dev = usb.core.find(idVendor=VID, idProduct=PID, backend=backend)
        if self.dev is None:
            sys.exit("the dongle is not on the host")
        self.dev.set_configuration()
        usb.util.claim_interface(self.dev, 0)
        self.running = True
        # One read stays pending on bulk IN and is never aborted: libusb on
        # macOS clears the pipe after an aborted read.
        threading.Thread(target=self._bulk_reader, daemon=True).start()

    def _bulk_reader(self):
        while self.running:
            try:
                data = bytes(self.dev.read(0x82, 1028, timeout=4000))
            except self.usb.core.USBTimeoutError:
                continue
            except self.usb.core.USBError:
                return
            self.acl_in.append(data)
            self.note("acl in", data)

    def send_command(self, packet):
        self.dev.ctrl_transfer(0x20, 0, 0, 0, packet)

    def send_acl(self, packet):
        self.dev.write(0x02, packet, timeout=1000)

    def events(self, seconds, stop=None, record=True):
        out, end = [], time.time() + seconds
        while time.time() < end:
            try:
                event = bytes(self.dev.read(0x81, 255, timeout=60))
            except self.usb.core.USBTimeoutError:
                continue
            out.append(event)
            if record:
                self.note("event", event)
            if stop and stop(event):
                break
        return out

    def close(self):
        super().close()
        self.running = False


class SocketDongle(Dongle):
    """An adapter of Linux through the HCI user channel (root, adapter down)."""

    def __init__(self, index):
        super().__init__()
        self.stack = f"none: the kernel's HCI user channel of hci{index} (btusb does the USB transfers)"
        self.sock = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_RAW, socket.BTPROTO_HCI)

        class SockaddrHci(ctypes.Structure):
            _fields_ = [("family", ctypes.c_ushort), ("dev", ctypes.c_ushort), ("channel", ctypes.c_ushort)]

        libc = ctypes.CDLL("libc.so.6", use_errno=True)
        addr = SockaddrHci(socket.AF_BLUETOOTH, index, 1)  # 1 is HCI_CHANNEL_USER
        if libc.bind(self.sock.fileno(), ctypes.byref(addr), ctypes.sizeof(addr)) != 0:
            sys.exit(f"cannot take hci{index}: errno {ctypes.get_errno()} (root? adapter down?)")

    def send_command(self, packet):
        self.sock.send(b"\x01" + packet)

    def send_acl(self, packet):
        self.sock.send(b"\x02" + packet)

    def events(self, seconds, stop=None, record=True):
        out, end = [], time.time() + seconds
        while time.time() < end:
            ready, _, _ = select.select([self.sock], [], [], 0.06)
            if not ready:
                continue
            packet = self.sock.recv(2048)
            if packet[0] == 0x02:
                self.acl_in.append(packet[1:])
                self.note("acl in", packet[1:])
                continue
            if packet[0] != 0x04:
                continue
            event = packet[1:]
            out.append(event)
            if record:
                self.note("event", event)
            if stop and stop(event):
                break
        return out


def local_version(dongle):
    """HCI revision and LMP subversion; they change when a patch is loaded."""
    dongle.cmd(0x1001)
    for event in dongle.events(0.5):
        if event[0] == 0x0E and event[3:5] == b"\x01\x10" and len(event) >= 14:
            hci_ver, hci_rev, lmp_ver, company, subver = struct.unpack("<BHBHH", event[6:14])
            return {"hci_version": hci_ver, "hci_revision": f"0x{hci_rev:04x}",
                    "lmp_version": lmp_ver, "company": f"0x{company:04x}",
                    "lmp_subversion": f"0x{subver:04x}"}
    return None


def loopback(dongle):
    """HCI local loopback: one ACL packet out, wait for it to come back."""
    dongle.cmd(0x0C03)
    dongle.events(1.0)
    print("dongle:", local_version(dongle))
    dongle.cmd(0x1802, b"\x01")
    handle = None
    for event in dongle.events(2.0):
        if event[0] == 0x03 and event[2] == 0 and event[11] == 1:
            handle = struct.unpack("<H", event[3:5])[0]
    print("acl loopback handle:", handle)
    if handle is not None:
        payload = bytes(range(16))
        packet = struct.pack("<HH", handle | 0x2000, len(payload)) + payload
        dongle.send_acl(packet)
        done = [e for e in dongle.events(2.0) if e[0] == 0x13]
        print("completed-packets events:", len(done), "packets back:", len(dongle.acl_in))
    dongle.cmd(0x1802, b"\x00")
    dongle.events(0.5)


def connect(dongle, peer, capture):
    started = datetime.datetime.now(datetime.timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")
    result = {"peer_seen": False, "connected": False}
    dongle.cmd(0x0C03)
    dongle.events(1.0)
    version = local_version(dongle)
    dongle.cmd(0x0C01, bytes.fromhex("ffffffffffffff3f"))  # event mask with LE Meta
    dongle.events(0.2)
    dongle.cmd(0x2001, bytes.fromhex("1f00000000000000"))  # LE event mask
    dongle.events(0.2)
    dongle.cmd(0x200B, struct.pack("<BHHBB", 1, 0x0010, 0x0010, 0, 0))
    dongle.events(0.2)
    dongle.cmd(0x200C, b"\x01\x00")
    reports = dongle.events(6.0, record=False)  # other devices are not recorded
    dongle.cmd(0x200C, b"\x00\x00")
    dongle.events(0.3)

    target, seen = None, set()
    for event in reports:
        if event[0] != 0x3E or event[2] != 0x02:
            continue
        atype, addr, data, rssi = event[5], event[6:12], event[13:-1], event[-1] - 256
        seen.add(addr)
        if peer == "supply":
            hit = addr[:2:-1] == SUPPLY_OUI and SUPPLY_MARK in data
        else:
            hit = MAC_MARK in data
        if hit and (target is None or rssi > target[2]):
            target = (atype, addr, rssi)
    result["advertisers_seen"] = len(seen)
    if target is not None:
        atype, addr, rssi = target
        dongle.secret = addr
        result.update(peer_seen=True, peer_address_type=atype, rssi_dbm=rssi)
        for event in reports:
            if event[0] == 0x3E and event[2] == 0x02 and event[6:12] == addr:
                dongle.note("event", event)
        # Supervision timeout 2 s: a link that stays up shows that the
        # dongle keeps hearing the peer.
        dongle.cmd(0x200D, struct.pack("<HHBB6sBHHHHHH", 0x0060, 0x0030, 0, atype, addr,
                                       0, 0x0018, 0x0028, 0, 0x00C8, 0, 0))
        handle = None
        for event in dongle.events(10.0, lambda e: e[0] == 0x3E and e[2] == 0x01):
            if event[0] == 0x3E and event[2] == 0x01 and event[3] == 0:
                handle = struct.unpack("<H", event[4:6])[0]
        if handle is None:
            dongle.cmd(0x200E)
            dongle.events(0.5)
        else:
            result["connected"] = True
            completed, dropped = 0, None

            def step(seconds):
                nonlocal completed, dropped
                for event in dongle.events(seconds):
                    if event[0] == 0x13:
                        completed += struct.unpack("<H", event[5:7])[0]
                    if event[0] == 0x05:
                        dropped = event[5]
                    if event[0] == 0x3E and event[2] == 0x04 and event[3] == 0:
                        result["remote_features"] = event[6:14].hex()
                    if event[0] == 0x0C and event[2] == 0:
                        ver, company, subver = struct.unpack("<BHH", event[5:10])
                        result["remote_version"] = {"ll_version": ver, "company": f"0x{company:04x}",
                                                    "subversion": f"0x{subver:04x}"}

            dongle.cmd(0x2016, struct.pack("<H", handle))
            step(2.0)
            dongle.cmd(0x041D, struct.pack("<H", handle))
            step(2.0)
            sent = 0
            if dropped is None and peer == "mac":
                # Read By Type for the test characteristic: the Mac reports
                # the read request when it arrives.
                dongle.acl_out(handle, 0x0004, bytes([0x08]) + struct.pack("<HH", 1, 0xFFFF) + MAC_CHAR)
                sent += 1
                step(3.0)
            if dropped is None:
                dongle.acl_out(handle, 0x0004, bytes([0x02]) + struct.pack("<H", 247))
                sent += 1
                step(3.0)
            if dropped is None:
                dongle.acl_out(handle, 0x0004, bytes([0x10]) + struct.pack("<HHH", 1, 0xFFFF, 0x2800))
                sent += 1
                step(3.0)
            result.update(acl_out=sent, acl_out_completed=completed, acl_in=len(dongle.acl_in),
                          link_dropped_reason=dropped)
            if dropped is None:
                dongle.cmd(0x0406, struct.pack("<HB", handle, 0x13))
                dongle.events(3.0, lambda e: e[0] == 0x05)

    meta = {
        "spike": "dongle_acl_path", "script": "host_hci.py connect --peer " + peer,
        "started": started,
        "host": (f"macOS {platform.mac_ver()[0]}" if platform.system() == "Darwin"
                 else f"{platform.system()} {platform.release()}")
                + f" ({platform.machine()}), no virtual machine",
        "stack": dongle.stack,
        "adapter": "ASUS USB-BT600, USB 0b05:1d70 (Realtek RTL8761CU), on a USB port of the machine",
        "adapter_version": version,
        "peer": "the MP305B" if peer == "supply" else "the Mac's built-in Bluetooth (mac_peripheral.py)",
        "sent": "active scan, connection, link-layer feature and version queries, "
                + ("ATT Read By Type Request for the test characteristic, " if peer == "mac" else "")
                + "ATT Exchange MTU Request, ATT Read By Group Type Request, disconnect; no frame of "
                "the supply's protocol",
        "firmware": "the supply's versions were not read in this run",
        "note": "The last three octets of the peer's address are masked (xxxxxx). Advertisements of "
                "other devices are not recorded, only their count.",
    }
    print(json.dumps(result, indent=1))
    if capture:
        with open(capture, "w", encoding="utf-8") as out:
            out.write(json.dumps({"meta": meta}) + "\n")
            for line in dongle.log:
                out.write(json.dumps(line) + "\n")
            out.write(json.dumps({"result": result}) + "\n")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("action", choices=["loopback", "connect"])
    parser.add_argument("--peer", choices=["supply", "mac"], default="supply")
    parser.add_argument("--capture")
    parser.add_argument("--hci", type=int, help="Linux: use hciN through the HCI user channel")
    args = parser.parse_args()
    dongle = UsbDongle() if args.hci is None else SocketDongle(args.hci)
    try:
        if args.action == "loopback":
            loopback(dongle)
        else:
            connect(dongle, args.peer, args.capture)
    finally:
        dongle.close()


if __name__ == "__main__":
    main()
