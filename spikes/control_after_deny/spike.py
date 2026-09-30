"""Control-after-deny spike for the ISDT MP305B (TBD-002).

Throwaway experiment (docs/v-model/README.md, "spikes"). Never imported by
production code. See README.md for the question and the safety reasoning.
The result tells the client how much to rely on a deny.

What it does, in order:
  1. Scan, connect, enable notifications, bind, and ask the user to press DENY.
     Abort if the reply is allowed (0x19 0x00): the experiment needs a deny.
  2. Read one 0xC3 snapshot (reads work after a deny, that is the known gap).
  3. Send exactly one 0xC8 with remoteCon=2 (request remote), built from the
     snapshot so every setpoint is unchanged, with the output field forced 0.
  4. Read the 0xC9 reply: 0 means the supply granted control despite the deny.
  5. finally: if control was granted, release it (remoteCon=0) and confirm the
     output is still off.

This spike never sets the output on and never changes a setpoint. guard_c8
refuses any 0xC8 whose output field is not 0, plus the same voltage, current
and mode caps as the other spikes. The output starts and stays off. The script
refuses to run unless MP305_HIL=1 and MP305_HIL_DEVICE name the unit and the
user types a confirmation.
"""

from __future__ import annotations

import asyncio
import datetime as dt
import json
import os
import platform
import struct
import sys
import time
from pathlib import Path

import bleak
from bleak import BleakClient, BleakScanner

AF00 = "0000af00-0000-1000-8000-00805f9b34fb"
AF01 = "0000af01-0000-1000-8000-00805f9b34fb"
AF02 = "0000af02-0000-1000-8000-00805f9b34fb"
NAME_PREFIX = "0000MP30"

# This spike never energizes the output, so the output field must be 0 on
# every command. The setpoint is copied from the supply's own reading (which
# can be up to 30 V) and left unchanged, so it is capped only at the device
# maximum, a backstop against a garbage snapshot. Nothing here is energized.
DEV_V_RAW = 3050   # 30.50 V, the device maximum
DEV_A_RAW = 5100   # 5.10 A, the device maximum

BIND = bytes([0x18, 0x00] + [0x08] * 14 + [0x00, 0x00, 0x00])
LIVE_READ = bytes([0x12, 0xC2])

REPO = Path(__file__).resolve().parents[2]
CAPTURE_DIR = REPO / "docs" / "research" / "captures"


def u16(b: bytes, o: int) -> int:
    """Read a little-endian u16 at offset o."""
    return struct.unpack_from("<H", b, o)[0]


def decode_c3(frame: bytes) -> dict:
    """Decode the fields of a BLE 0xC3 frame this spike reports (payload at index 2)."""
    p = frame[2:]
    return {"addr": f"0x{frame[0]:02X}", "setV": u16(p, 5) / 100, "setA": u16(p, 9) / 1000,
            "output": p[24], "model": p[25]}


def build_c8_request_remote(snapshot: bytes) -> bytes:
    """Build the single 0xC8 remoteCon=2 probe from a 0xC3 snapshot, output forced 0."""
    p = snapshot[2:]
    payload = bytes([
        2,          # remoteCon: request remote control
        p[5], p[6],  # setVoltage, copied unchanged
        p[9], p[10],  # setCurrent, copied unchanged
        p[22],      # realChange, copied
        p[23],      # voltageSlow, copied
        p[21],      # currentOver, copied
        0,          # output: forced OFF
        0,          # model: DC, forced
        0,          # refresh: none
    ])
    return bytes([0x12, 0xC8]) + payload


def build_c8_release(snapshot: bytes) -> bytes:
    """Build a 0xC8 remoteCon=0 release, output forced 0."""
    p = snapshot[2:]
    payload = bytes([0, p[5], p[6], p[9], p[10], p[22], p[23], p[21], 0, 0, 0])
    return bytes([0x12, 0xC8]) + payload


def guard_c8(frame: bytes) -> None:
    """Raise unless the 0xC8 frame is within this spike's safe envelope (output must be 0)."""
    if frame[:2] != bytes([0x12, 0xC8]) or len(frame) != 13:
        raise RuntimeError(f"refusing malformed 0xC8: {frame.hex(' ')}")
    p = frame[2:]
    remote_con, set_v, set_a, output, model = p[0], u16(p, 1), u16(p, 3), p[8], p[9]
    if remote_con not in (0, 2):
        raise RuntimeError(f"refusing 0xC8 remoteCon={remote_con} (this spike sends only 0 or 2)")
    if output != 0:
        raise RuntimeError(f"refusing 0xC8 output={output} (this spike never enables the output)")
    if set_v > DEV_V_RAW:
        raise RuntimeError(f"refusing 0xC8 setV={set_v} (> {DEV_V_RAW})")
    if set_a > DEV_A_RAW:
        raise RuntimeError(f"refusing 0xC8 setA={set_a} (> {DEV_A_RAW})")
    if model != 0:
        raise RuntimeError(f"refusing 0xC8 model={model} (not DC)")


class Capture:
    """Collects every TX and RX event with a monotonic timestamp."""

    def __init__(self) -> None:
        self.t0 = time.monotonic()
        self.events: list[dict] = []
        self.queue: asyncio.Queue[tuple[str, bytes]] = asyncio.Queue()

    def log(self, direction: str, char: str, data: bytes, note: str = "") -> None:
        """Record and print one event."""
        ev = {"t": round(time.monotonic() - self.t0, 4), "dir": direction,
              "char": char[4:8], "hex": data.hex(" "), "len": len(data)}
        if note:
            ev["note"] = note
        self.events.append(ev)
        print(f"{ev['t']:8.3f} {direction} {ev['char']} [{len(data):3}] {ev['hex']}" + (f"  ({note})" if note else ""))

    def handler(self, char_uuid: str):
        """Return a notification handler bound to char_uuid."""
        def h(_sender, data: bytearray) -> None:
            b = bytes(data)
            self.log("RX", char_uuid, b)
            self.queue.put_nowait((char_uuid, b))
        return h

    async def wait_for(self, char_uuid: str, pred, timeout: float) -> bytes | None:
        """Wait for a matching notification on char_uuid, else None."""
        deadline = time.monotonic() + timeout
        while (remaining := deadline - time.monotonic()) > 0:
            try:
                ch, data = await asyncio.wait_for(self.queue.get(), remaining)
            except asyncio.TimeoutError:
                return None
            if ch == char_uuid and pred(data):
                return data
        return None


async def send_c8(client: BleakClient, cap: Capture, frame: bytes, note: str) -> None:
    """Guard, log and send a 0xC8 frame on AF01."""
    guard_c8(frame)
    cap.log("TX", AF01, frame, note)
    await client.write_gatt_char(AF01, frame, response=True)


async def read_c3(client: BleakClient, cap: Capture, note: str) -> bytes | None:
    """Send one live read and return the 0xC3 reply."""
    cap.log("TX", AF01, LIVE_READ, note)
    await client.write_gatt_char(AF01, LIVE_READ, response=True)
    return await cap.wait_for(AF01, lambda d: len(d) > 1 and d[1] == 0xC3, 2.0)


def preconditions() -> str:
    """Enforce the HIL guards. Return the device id or exit."""
    if os.environ.get("MP305_HIL") != "1":
        sys.exit("refusing to run: set MP305_HIL=1 only when you are at the bench")
    device = os.environ.get("MP305_HIL_DEVICE")
    if not device:
        sys.exit("refusing to run: set MP305_HIL_DEVICE to the unit's CoreBluetooth UUID")
    print(__doc__)
    print("This spike never switches the output on. It sends one request-remote command after a deny.")
    print("Confirm: NOTHING is connected to the output terminals.")
    if input('Type "yes" to continue: ').strip() != "yes":
        sys.exit("aborted by user")
    return device


async def main() -> int:
    device = preconditions()
    cap = Capture()
    meta = {"kind": "meta", "date": dt.datetime.now().astimezone().isoformat(timespec="seconds"),
            "platform": platform.platform(), "python": platform.python_version(),
            "bleak": getattr(bleak, "__version__", "unknown"),
            "script": "spikes/control_after_deny/spike.py", "hil_device": device}
    results: dict = {}

    print("scanning up to 20 s ...")
    dev = await BleakScanner.find_device_by_filter(
        lambda d, adv: (adv.local_name or d.name or "").startswith(NAME_PREFIX) or AF00 in [u.lower() for u in adv.service_uuids],
        timeout=20.0)
    if dev is None:
        return 2
    if dev.address != device:
        sys.exit(f"found {dev.address}, not the named MP305_HIL_DEVICE {device}; refusing")
    meta.update(name=dev.name, address=dev.address)
    print(f"found {dev.name!r} at {dev.address}")

    async with BleakClient(dev, timeout=20.0) as client:
        meta["mtu"] = client.mtu_size
        await client.start_notify(AF01, cap.handler(AF01))
        await client.start_notify(AF02, cap.handler(AF02))
        await asyncio.sleep(1.0)
        print(">>> When the supply asks, press DENY on its screen. <<<")
        cap.log("TX", AF02, BIND, "bind")
        await client.write_gatt_char(AF02, BIND, response=True)
        bind = await cap.wait_for(AF02, lambda d: d[:1] == b"\x19", 60.0)
        results["bind_reply"] = bind.hex(" ") if bind else None
        if bind is None:
            print("no bind reply, aborting")
            return 3
        if len(bind) > 1 and bind[1] == 0x00:
            print("the supply was ALLOWED, not denied; this spike needs a deny. Aborting, no command sent.")
            return 4
        print(f"denied as expected (bind reply {results['bind_reply']})")

        snapshot = None
        try:
            snapshot = await read_c3(client, cap, "snapshot after deny (reads work after a deny)")
            results["read_after_deny"] = decode_c3(snapshot) if snapshot else None
            if not snapshot:
                print("no 0xC3 after the deny, cannot build a state-matched probe, aborting")
                return 5
            # The one probe: request remote control, output forced 0, setpoints unchanged.
            await send_c8(client, cap, build_c8_request_remote(snapshot), "probe: request remote after deny")
            c9 = await cap.wait_for(AF01, lambda d: len(d) > 1 and d[1] == 0xC9, 2.0)
            results["c9_reply"] = c9.hex(" ") if c9 else None
            granted = bool(c9 and len(c9) > 2 and c9[2] == 0)
            results["remote_granted_after_deny"] = granted
            if granted:
                print("FINDING: the supply GRANTED remote control after a deny. This is a device-side gap.")
            else:
                print("the supply refused remote control after the deny (as it should).")
        finally:
            # If control was granted, release it. The output was never enabled.
            if snapshot is not None and results.get("remote_granted_after_deny"):
                try:
                    await send_c8(client, cap, build_c8_release(snapshot), "release remote")
                except Exception as exc:
                    print(f"release warning: {exc}")
            confirm = await read_c3(client, cap, "confirm output still off")
            results["output_off_confirmed"] = bool(confirm and decode_c3(confirm)["output"] == 0)

    CAPTURE_DIR.mkdir(parents=True, exist_ok=True)
    stamp = dt.datetime.now().strftime("%Y-%m-%dT%H%M%S")
    out = CAPTURE_DIR / f"{stamp}-ble-control-after-deny.jsonl"
    with out.open("w") as f:
        f.write(json.dumps(meta) + "\n")
        for ev in cap.events:
            f.write(json.dumps(ev) + "\n")
        f.write(json.dumps({"kind": "results", **results}) + "\n")
    print("\n=== results ===")
    print(json.dumps(results, indent=2, ensure_ascii=False))
    print(f"\ncapture written to {out.relative_to(REPO)}")
    return 0


if __name__ == "__main__":
    sys.exit(asyncio.run(main()))
