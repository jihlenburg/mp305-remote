"""Spike: a nameplate in a program slot (see README.md).

Reads the supply's program list (`D4`) and the selected program (`DC`) over
Bluetooth LE. With `--write NAME` it adds a program header with that name,
no steps, saved to flash (`D6, id, name[16], 0, 1, 0`), where `id` is the
next contiguous id, and reads the list again. With `--delete ID` it deletes
that program (`D6, id, zeros, 0, 1, 1`) and reads the list again. Every
frame goes through an allow-list; the capture is written to
docs/research/captures/.

    uv run --with bleak python spikes/program_nameplate/spike.py
    uv run --with bleak python spikes/program_nameplate/spike.py --write "mp305 7F3A"
    uv run --with bleak python spikes/program_nameplate/spike.py --delete 3

The supply must be on with remote control enabled and nothing else
connected to it. A program write switches the output request off.
"""

from __future__ import annotations

import argparse
import asyncio
import datetime as dt
import json
import platform
import sys
import time
from pathlib import Path

import bleak
from bleak import BleakClient, BleakScanner

AF00 = "0000af00-0000-1000-8000-00805f9b34fb"
AF01 = "0000af01-0000-1000-8000-00805f9b34fb"
NAME_PREFIX = "0000MP30"
PLACEHOLDER = 0x12  # the first byte of an AF01 write, discarded by the CH58x
ROUTE = 0x31  # the first byte of an AF01 notification

REPO = Path(__file__).resolve().parents[2]
CAPTURE_DIR = REPO / "docs" / "research" / "captures"

LIST = bytes([PLACEHOLDER, 0xD4])
SELECTED = bytes([PLACEHOLDER, 0xDC])


def header_write(program_id: int, name: bytes, steps: int, save: int, op: int) -> bytes:
    assert 1 <= program_id <= 10 and len(name) == 16 and steps == 0
    return bytes([PLACEHOLDER, 0xD6, program_id]) + name + bytes([steps, save, op])


class Capture:
    def __init__(self) -> None:
        self.t0 = time.monotonic()
        self.events: list[dict] = []
        self.queue: asyncio.Queue[tuple[str, bytes]] = asyncio.Queue()

    def log(self, direction: str, char: str, data: bytes, note: str = "") -> None:
        ev = {"t": round(time.monotonic() - self.t0, 4), "dir": direction, "char": char[4:8],
              "hex": data.hex(" "), "len": len(data)}
        if note:
            ev["note"] = note
        self.events.append(ev)
        print(f"{ev['t']:8.3f} {direction} {ev['char']} [{len(data):3}] {ev['hex']}" + (f"  ({note})" if note else ""), flush=True)

    def handler(self, char_uuid: str):
        def on_notify(_sender, data: bytearray) -> None:
            b = bytes(data)
            self.log("RX", char_uuid, b)
            self.queue.put_nowait((char_uuid, b))
        return on_notify

    async def wait_for(self, opcode: int, timeout: float) -> bytes | None:
        deadline = time.monotonic() + timeout
        while (remaining := deadline - time.monotonic()) > 0:
            try:
                ch, data = await asyncio.wait_for(self.queue.get(), remaining)
            except asyncio.TimeoutError:
                break
            if ch == AF01 and len(data) >= 2 and data[0] == ROUTE and data[1] == opcode:
                return data
        return None


async def send(client: BleakClient, cap: Capture, allowed: set[bytes], frame: bytes, note: str) -> None:
    if frame not in allowed:
        raise RuntimeError(f"refusing to send a frame that is not on the allow-list: {frame.hex(' ')}")
    cap.log("TX", AF01, frame, note)
    await client.write_gatt_char(AF01, frame, response=True)


def decode_list(reply: bytes) -> list[tuple[int, str, int]]:
    """`31 D5 count (name[16] steps)*count`: (id, name, steps)."""
    count = reply[2]
    out = []
    for k in range(count):
        o = 3 + k * 17
        rec = reply[o:o + 17]
        if len(rec) < 17:
            break
        name = rec[:16].split(b"\0", 1)[0].decode("ascii", "replace")
        out.append((k + 1, name, rec[16]))
    return out


async def read_list(client: BleakClient, cap: Capture, allowed: set[bytes], note: str) -> list[tuple[int, str, int]] | None:
    await send(client, cap, allowed, LIST, note)
    reply = await cap.wait_for(0xD5, 3.0)
    if reply is None:
        print("no D5 reply within 3 s", flush=True)
        return None
    programs = decode_list(reply)
    print(f"programs: {len(programs)} (count byte {reply[2]})", flush=True)
    for pid, name, steps in programs:
        print(f"  id {pid:2}: {name!r:20} {steps} steps", flush=True)
    return programs


VID, PID = 0x28E9, 0x028A
START, REQUEST, REPLY = 0xAA, 0x12, 0x21


def usb_stream(opcode: int, payload: bytes = b"") -> bytes:
    """The framed request as the USB stream: `AA`, address, length, body, sum, every later `AA` doubled."""
    body = bytes([opcode]) + payload
    length = len(body)
    total = (REQUEST + length + sum(body)) & 0xFF
    out = bytearray([START])
    for b in bytes([REQUEST, length]) + body + bytes([total]):
        out.append(b)
        if b == START:
            out.append(START)
    return bytes(out)


def usb_frames(stream: bytes) -> list[bytes]:
    """The reply frames in a reassembled input stream: `opcode + payload` each (no checksum)."""
    frames, i = [], 0
    while (i := stream.find(bytes([START, REPLY]), i)) >= 0:
        rest = bytearray()
        k = i + 1
        while k < len(stream):
            if stream[k] == START and k + 1 < len(stream) and stream[k + 1] == START:
                rest.append(START); k += 2
            elif stream[k] == START:
                break
            else:
                rest.append(stream[k]); k += 1
        if len(rest) >= 3 and len(rest) >= 2 + rest[1] + 1:
            frames.append(bytes(rest[2:2 + rest[1]]))
        i = k if k > i + 1 else i + 2
    return frames


def usb_read_list(cap: Capture) -> list[tuple[int, str, int]] | None:
    """Reads `DC` and `D4` over USB HID; nothing is written to the supply."""
    import hid  # the PyPI package `hidapi`
    device = hid.device()
    device.open(VID, PID)
    try:
        device.set_nonblocking(True)
        for opcode, note in ((0xDC, "DC selected program"), (0xD4, "D4 list")):
            stream = usb_stream(opcode)
            report = bytes([0x01, len(stream)]) + stream + bytes(65 - 2 - len(stream))
            cap.log("TX", "0000hid0", report[:2 + len(stream)], note)
            device.write(report)
            got = bytearray()
            deadline = time.monotonic() + 2.0
            while time.monotonic() < deadline:
                data = bytes(device.read(65))
                if data and data[0] == 0x02:
                    cap.log("RX", "0000hid0", data[:2 + data[1]])
                    got += data[2:2 + data[1]]
                    wanted = 0xDD if opcode == 0xDC else 0xD5
                    if any(f[0] == wanted for f in usb_frames(bytes(got))):
                        break
                time.sleep(0.01)
            for f in usb_frames(bytes(got)):
                if f[0] == 0xDD:
                    print(f"USB selected program: id {f[1]}, {f[2]} steps", flush=True)
                if f[0] == 0xD5:
                    programs = decode_list(bytes([ROUTE]) + f)
                    print(f"USB programs: {len(programs)} (count byte {f[1]})", flush=True)
                    for pid, name, steps in programs:
                        print(f"  id {pid:2}: {name!r:20} {steps} steps", flush=True)
                    return programs
    finally:
        device.close()
    return None


async def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--write", metavar="NAME", help="add a program header with this name (ASCII, up to 16 bytes)")
    parser.add_argument("--delete", metavar="ID", type=int, help="delete the program with this id")
    parser.add_argument("--usb", action="store_true", help="read the list over USB HID instead of Bluetooth (no writes)")
    args = parser.parse_args()
    if args.usb:
        cap = Capture()
        meta = {"kind": "meta", "date": dt.datetime.now().astimezone().isoformat(timespec="seconds"),
                "platform": platform.platform(), "python": platform.python_version(),
                "script": "spikes/program_nameplate/spike.py", "args": vars(args)}
        programs = usb_read_list(cap)
        CAPTURE_DIR.mkdir(parents=True, exist_ok=True)
        path = CAPTURE_DIR / f"{dt.datetime.now().strftime('%Y-%m-%dT%H%M%S')}-program-nameplate-usb.jsonl"
        with path.open("w") as f:
            f.write(json.dumps(meta) + "\n")
            for ev in cap.events:
                f.write(json.dumps({"kind": "event", **ev}) + "\n")
            f.write(json.dumps({"kind": "result", "usb": programs}) + "\n")
        print(f"capture: {path.relative_to(REPO)}", flush=True)
        return 0 if programs is not None else 1
    if args.write is not None and args.delete is not None:
        parser.error("one of --write and --delete")

    cap = Capture()
    meta: dict = {"kind": "meta", "date": dt.datetime.now().astimezone().isoformat(timespec="seconds"),
                  "platform": platform.platform(), "python": platform.python_version(),
                  "bleak": getattr(bleak, "__version__", "unknown"), "script": "spikes/program_nameplate/spike.py",
                  "args": vars(args)}
    allowed: set[bytes] = {LIST, SELECTED}

    print("scanning up to 20 s ...", flush=True)
    dev = await BleakScanner.find_device_by_filter(
        lambda d, adv: (adv.local_name or d.name or "").startswith(NAME_PREFIX) or AF00 in [u.lower() for u in adv.service_uuids],
        timeout=20.0)
    if dev is None:
        print("MP305 not found: is it on, with remote control enabled, and nothing else connected?")
        return 2
    meta.update(name=dev.name)
    print(f"found {dev.name!r}", flush=True)

    results: dict = {}
    async with BleakClient(dev, timeout=20.0) as client:
        await client.start_notify(AF01, cap.handler(AF01))
        await asyncio.sleep(0.3)

        await send(client, cap, allowed, SELECTED, "DC selected program")
        sel = await cap.wait_for(0xDD, 3.0)
        if sel is not None and len(sel) >= 4:
            print(f"selected program: id {sel[2]}, {sel[3]} steps", flush=True)
            results["selected"] = {"id": sel[2], "steps": sel[3]}

        before = await read_list(client, cap, allowed, "D4 list before")
        results["before"] = before

        if args.write is not None and before is not None:
            name = args.write.encode("ascii")
            if len(name) > 16:
                print("the name must be at most 16 bytes")
                return 2
            program_id = len(before) + 1
            if program_id > 10:
                print("all ten slots are in use; delete one first")
                return 2
            frame = header_write(program_id, name.ljust(16, b"\0"), 0, 1, 0)
            allowed.add(frame)
            await send(client, cap, allowed, frame, f"D6 header write: id {program_id}, name {args.write!r}, 0 steps, save 1, op 0")
            reply = await cap.wait_for(0xD7, 5.0)
            status = None if reply is None else reply[2] if len(reply) > 2 else -1
            print(f"D7 status: {status!r} (0 is accepted, 255 rejected, None no reply)", flush=True)
            results["write"] = {"id": program_id, "name": args.write, "status": status}
            await asyncio.sleep(1.0)
            results["after"] = await read_list(client, cap, allowed, "D4 list after the write")

        if args.delete is not None and before is not None:
            frame = header_write(args.delete, bytes(16), 0, 1, 1)
            allowed.add(frame)
            await send(client, cap, allowed, frame, f"D6 delete: id {args.delete}, save 1, op 1")
            reply = await cap.wait_for(0xD7, 5.0)
            status = None if reply is None else reply[2] if len(reply) > 2 else -1
            print(f"D7 status: {status!r}", flush=True)
            results["delete"] = {"id": args.delete, "status": status}
            await asyncio.sleep(1.0)
            results["after"] = await read_list(client, cap, allowed, "D4 list after the delete")

        await asyncio.sleep(0.5)

    CAPTURE_DIR.mkdir(parents=True, exist_ok=True)
    path = CAPTURE_DIR / f"{dt.datetime.now().strftime('%Y-%m-%dT%H%M%S')}-program-nameplate.jsonl"
    with path.open("w") as f:
        f.write(json.dumps(meta) + "\n")
        for ev in cap.events:
            f.write(json.dumps({"kind": "event", **ev}) + "\n")
        f.write(json.dumps({"kind": "result", **results}) + "\n")
    print(f"capture: {path.relative_to(REPO)}", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(asyncio.run(main()))
