"""Read-only Bluetooth LE spike for the ISDT MP305B.

Throwaway experiment (see docs/v-model/README.md, "spikes"). Never imported by
production code. It answers these questions from docs/research:

- Which GATT characteristics exist, with which properties, and what MTU macOS
  negotiates.
- Whether the bind frame is accepted and what the device answers.
- The real byte layout of the E1 (module info), C5 (settings) and C3 (live
  data) replies, including the reply address byte and optional tail fields.
- Whether AF01 commands work (and whether E0 over AF01 returns main MCU info).

Safety: the script can only send the frames in ALLOWED. It never sends C8
(set voltage/current/output/mode), C6 (settings) or any other state-changing
command. The bind frame is the one non-read frame; ISDT's WebLink page sends the
identical bytes on every connection.

Run: uv run --with bleak python spikes/ble_readonly/spike.py
Output: a JSONL capture under docs/research/captures/ and a decoded summary.
"""

from __future__ import annotations

import asyncio
import datetime as dt
import json
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

# Frames copied from ISDT WebLink (otaResp class d / class h, mp305Component _J).
BIND = bytes([0x18, 0x00] + [0x08] * 14 + [0x00, 0x00, 0x00])  # class d, uuid fixed, fastBinding 0, status 0
MODULE_INFO = bytes([0xE0])  # class h with bleBool: [224], written to AF02
SETTINGS_READ = bytes([0x12, 0xC4])  # SEARCH_DATA, BLE branch
LIVE_READ = bytes([0x12, 0xC2])  # INFO_DATA, BLE branch
MAIN_INFO_PROBE = bytes([0x12, 0xE0])  # not used by WebLink over BLE; read-only probe

ALLOWED = {
    (AF02, BIND),
    (AF02, MODULE_INFO),
    (AF01, SETTINGS_READ),
    (AF01, LIVE_READ),
    (AF01, MAIN_INFO_PROBE),
}

REPO = Path(__file__).resolve().parents[2]
CAPTURE_DIR = REPO / "docs" / "research" / "captures"


class Capture:
    """Collects every TX/RX event with a monotonic timestamp."""

    def __init__(self) -> None:
        self.t0 = time.monotonic()
        self.events: list[dict] = []
        self.queue: asyncio.Queue[tuple[str, bytes]] = asyncio.Queue()

    def log(self, direction: str, char: str, data: bytes, note: str = "") -> None:
        ev = {"t": round(time.monotonic() - self.t0, 4), "dir": direction,
              "char": char[4:8], "hex": data.hex(" "), "len": len(data)}
        if note:
            ev["note"] = note
        self.events.append(ev)
        print(f"{ev['t']:8.3f} {direction} {ev['char']} [{len(data):3}] {ev['hex']}" + (f"  ({note})" if note else ""))

    def notify_handler(self, char_uuid: str):
        def handler(_sender, data: bytearray) -> None:
            b = bytes(data)
            self.log("RX", char_uuid, b)
            self.queue.put_nowait((char_uuid, b))
        return handler

    async def wait_for(self, char_uuid: str, pred, timeout: float) -> bytes | None:
        """Wait for a notification on char_uuid matching pred; drop others (they stay in the capture)."""
        deadline = time.monotonic() + timeout
        while (remaining := deadline - time.monotonic()) > 0:
            try:
                ch, data = await asyncio.wait_for(self.queue.get(), remaining)
            except asyncio.TimeoutError:
                break
            if ch == char_uuid and pred(data):
                return data
        return None


async def send(client: BleakClient, cap: Capture, char_uuid: str, frame: bytes, with_response: bool, note: str = "") -> None:
    if (char_uuid, frame) not in ALLOWED:
        raise RuntimeError(f"refusing to send non-allowlisted frame {frame.hex(' ')} to {char_uuid}")
    cap.log("TX", char_uuid, frame, note)
    await client.write_gatt_char(char_uuid, frame, response=with_response)


def u16(b: bytes, o: int) -> int:
    return struct.unpack_from("<H", b, o)[0]


def u32(b: bytes, o: int) -> int:
    return struct.unpack_from("<I", b, o)[0]


def decode_c3(frame: bytes) -> dict:
    """Decode a BLE C3 frame per protocol-findings 4.1 (payload starts at index 2)."""
    p = frame[2:]
    d = {
        "frame_len": len(frame), "addr": f"0x{frame[0]:02X}",
        "outState(1=CV,2=CC)": p[0], "batteryState": p[1], "battery_pct": p[2],
        "V": u16(p, 3) / 100, "setV": u16(p, 5) / 100,
        "A": u16(p, 7) / 1000, "setA": u16(p, 9) / 1000,
        "time_s": u32(p, 11), "energy_raw": u32(p, 15), "W": u16(p, 19) / 100,
        "currentOver(0=CC,1=OCP)": p[21], "realChange": p[22], "voltageSlow": p[23],
        "output": p[24], "model": p[25], "voltageBoard": p[26], "currentBoard": p[27],
        "temp_C": p[28],
    }
    if len(frame) > 31:
        d["chargeError"] = u16(p, 29)
    if len(frame) > 33:
        d["wavePause"] = p[31]
        if len(p) >= 36:
            d["waveTime_ms"] = u32(p, 32)
    return d


def decode_c5(frame: bytes) -> dict:
    p = frame[2:]
    d = {"frame_len": len(frame), "addr": f"0x{frame[0]:02X}", "chargeLimit_pct": p[0], "volume": p[1],
         "screenOff": p[2], "autoOff_min": p[3], "screenDirection": p[4],
         "rampStep_mV_per_100ms": u16(p, 5), "ocpDelay_ms": u16(p, 7)}
    if len(frame) > 11:
        d["usbLineComp_mV"] = u16(p, 9)
    return d


def decode_module_e1(frame: bytes) -> dict:
    p = frame[1:]
    d = {"frame_len": len(frame), "ble_hw": f"{p[0]}.{p[1]}", "ble_sw": f"{p[2]}.{p[3]}",
         "deviceId_hex": p[4:12].hex(), "deviceId_ascii": p[4:12].decode("ascii", "replace")}
    if len(frame) > 16:
        d["hw_version"] = ".".join(str(x) for x in p[12:16])
    return d


async def main() -> int:
    cap = Capture()
    meta: dict = {"kind": "meta", "date": dt.datetime.now().astimezone().isoformat(timespec="seconds"),
                  "platform": platform.platform(), "python": platform.python_version(),
                  "bleak": getattr(bleak, "__version__", "unknown"), "script": "spikes/ble_readonly/spike.py"}

    print("scanning up to 20 s ...")
    dev = await BleakScanner.find_device_by_filter(
        lambda d, adv: (adv.local_name or d.name or "").startswith(NAME_PREFIX) or AF00 in [u.lower() for u in adv.service_uuids],
        timeout=20.0)
    if dev is None:
        print("MP305 not found. Is Chrome/Polying connected to it? Is it powered?")
        return 2
    meta.update(name=dev.name, address=dev.address)
    print(f"found {dev.name!r} at {dev.address}")

    results: dict = {}
    async with BleakClient(dev, timeout=20.0) as client:
        meta["mtu"] = client.mtu_size
        gatt = []
        for s in client.services:
            chars = []
            for c in s.characteristics:
                chars.append({"uuid": c.uuid, "handle": c.handle, "properties": c.properties,
                              "max_write_without_response": getattr(c, "max_write_without_response_size", None),
                              "descriptors": [x.uuid for x in c.descriptors]})
            gatt.append({"service": s.uuid, "characteristics": chars})
        meta["gatt"] = gatt
        print(f"connected, mtu={client.mtu_size}")
        for s in gatt:
            print(f"  service {s['service']}")
            for c in s["characteristics"]:
                print(f"    {c['uuid']} handle={c['handle']} props={c['properties']} mwwr={c['max_write_without_response']}")

        props = {c["uuid"]: c["properties"] for s in gatt for c in s["characteristics"]}
        if AF01 not in props or AF02 not in props:
            print("AF01/AF02 missing, aborting")
            return 3
        resp = {u: ("write" in props[u]) for u in (AF01, AF02)}
        meta["write_with_response"] = {k[4:8]: v for k, v in resp.items()}

        await client.start_notify(AF01, cap.notify_handler(AF01))
        await client.start_notify(AF02, cap.notify_handler(AF02))
        await asyncio.sleep(1.0)  # WebLink waits 1000 ms before binding

        await send(client, cap, AF02, BIND, resp[AF02], "bind")
        bind = await cap.wait_for(AF02, lambda d: d[:1] == b"\x19", 30.0)  # a person must press allow/deny on the device
        results["bind_reply"] = bind.hex(" ") if bind else None
        print(f"bind reply: {results['bind_reply']}")
        if bind and len(bind) > 1 and bind[1] == 0x00:
            await asyncio.sleep(0.5)  # WebLink waits 500 ms
            await send(client, cap, AF02, MODULE_INFO, resp[AF02], "module info")
            e1 = await cap.wait_for(AF02, lambda d: d[:1] == b"\xE1", 5.0)
            results["module_e1"] = decode_module_e1(e1) if e1 else None
        else:
            print("bind not confirmed; continuing with read-only AF01 requests to learn whether binding is required")

        await send(client, cap, AF01, SETTINGS_READ, resp[AF01], "settings read")
        c5 = await cap.wait_for(AF01, lambda d: len(d) > 1 and d[1] == 0xC5, 3.0)
        results["c5"] = decode_c5(c5) if c5 and len(c5) >= 11 else (c5.hex(" ") if c5 else None)

        c3s = []
        for i in range(20):
            await send(client, cap, AF01, LIVE_READ, resp[AF01], f"live poll {i + 1}")
            c3 = await cap.wait_for(AF01, lambda d: len(d) > 1 and d[1] == 0xC3, 2.0)
            if c3 is None:
                print("no C3 reply")
                continue
            c3s.append(c3)
            await asyncio.sleep(0.1)  # WebLink polls 100 ms after each reply
        results["c3_count"] = len(c3s)
        results["c3_first"] = decode_c3(c3s[0]) if c3s and len(c3s[0]) >= 31 else (c3s[0].hex(" ") if c3s else None)
        results["c3_lengths"] = sorted({len(x) for x in c3s})

        await send(client, cap, AF01, MAIN_INFO_PROBE, resp[AF01], "probe: E0 over AF01")
        probe = await cap.wait_for(AF01, lambda d: len(d) > 1 and d[1] == 0xE1, 3.0)
        results["main_e1_over_af01"] = probe.hex(" ") if probe else None

        await asyncio.sleep(0.5)
        for u in (AF01, AF02):
            try:
                await client.stop_notify(u)
            except Exception as exc:  # spike: log and continue to disconnect
                print(f"stop_notify {u}: {exc}")

    CAPTURE_DIR.mkdir(parents=True, exist_ok=True)
    stamp = dt.datetime.now().strftime("%Y-%m-%dT%H%M%S")
    out = CAPTURE_DIR / f"{stamp}-ble-readonly.jsonl"
    with out.open("w") as f:
        f.write(json.dumps(meta) + "\n")
        for ev in cap.events:
            f.write(json.dumps(ev) + "\n")
        f.write(json.dumps({"kind": "results", **results}) + "\n")
    print("\n=== decoded results ===")
    print(json.dumps(results, indent=2, ensure_ascii=False))
    print(f"\ncapture written to {out.relative_to(REPO)}")
    return 0


if __name__ == "__main__":
    sys.exit(asyncio.run(main()))
