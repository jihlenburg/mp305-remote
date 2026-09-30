"""Link-drop spike for the ISDT MP305B (TBD-005).

Throwaway experiment (docs/v-model/README.md, "spikes"). Never imported by
production code. See README.md for the question and the safety reasoning.

What it does, in order:
  1. Scan, connect, enable notifications, bind, wait for the user to press
     allow. Abort if denied (this spike needs remote control).
  2. Read one 0xC3 snapshot and remember the original setpoint to restore.
  3. Request remote control (0xC8 remoteCon=2, output forced 0); expect 0xC9=0.
  4. Set 5.00 V, 0.100 A, output ON, with NOTHING connected.
  5. Read 0xC3 a few times to record whether the output came on.
  6. Drop the link abruptly (disconnect without releasing), the way a crash
     would, and wait.
  7. Reconnect, read 0xC3 to observe whether the output stayed on and whether
     remote control survived, then switch the output off and restore the
     setpoint.
  8. A finally block guarantees the teardown runs whenever an energize command
     was sent, retrying, and warns the user to use the front panel if it
     cannot confirm the output is off.

Safety: guard_c8 refuses any command above 5.00 V or 100 mA while the output
is on, any non-DC mode, and any malformed reading. Teardown is keyed on
"an energize command was sent", never on a read-back that might be lost. The
script refuses to run unless MP305_HIL=1 and MP305_HIL_DEVICE name the unit
and the user types a confirmation.
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

# Safety caps. The bench limit applies to any command that ENERGIZES the
# output (output = 1). A command that leaves the output off only has to be
# sane, so it may carry the supply's real setpoint (which can be up to 30 V)
# unchanged, including the teardown that switches the output off.
BENCH_V_RAW = 600    # 6.00 V, the most this spike may energize to
BENCH_A_RAW = 150    # 150 mA, the most this spike may energize to
DEV_V_RAW = 3050     # 30.50 V, the device maximum, a backstop against a garbage snapshot
DEV_A_RAW = 5100     # 5.10 A, the device maximum
SET_V_RAW = 500      # 5.00 V, the spike's working voltage
SET_A_RAW = 100      # 0.100 A, the spike's working current limit

BIND = bytes([0x18, 0x00] + [0x08] * 14 + [0x00, 0x00, 0x00])
LIVE_READ = bytes([0x12, 0xC2])

REPO = Path(__file__).resolve().parents[2]
CAPTURE_DIR = REPO / "docs" / "research" / "captures"


def u16(b: bytes, o: int) -> int:
    """Read a little-endian u16 at offset o."""
    return struct.unpack_from("<H", b, o)[0]


def decode_c3(frame: bytes) -> dict:
    """Decode a BLE 0xC3 live-data frame (payload starts at index 2)."""
    p = frame[2:]
    d = {
        "addr": f"0x{frame[0]:02X}", "outState": p[0], "battery_pct": p[2],
        "V": u16(p, 3) / 100, "setV": u16(p, 5) / 100,
        "A": u16(p, 7) / 1000, "setA": u16(p, 9) / 1000,
        "power_W": u16(p, 19) / 100, "currentOver": p[21], "realChange": p[22],
        "voltageSlow": p[23], "output": p[24], "model": p[25], "temp_C": p[28],
    }
    if len(frame) > 32:  # need payload bytes 29 and 30 for the u16 at offset 29
        d["chargeError"] = u16(p, 29)
    return d


def build_c8(snapshot: bytes, remote_con: int, output: int,
             set_v_raw: int | None = None, set_a_raw: int | None = None) -> bytes:
    """Build a BLE 0xC8 frame from a 0xC3 snapshot, changing only named fields.

    Every field not named is copied from the snapshot, so the command matches
    the device's current state. The mode is forced to DC (0). guard_c8 checks
    the result before it can be sent.
    """
    p = snapshot[2:]
    set_v = p[5] | (p[6] << 8) if set_v_raw is None else set_v_raw
    set_a = p[9] | (p[10] << 8) if set_a_raw is None else set_a_raw
    payload = bytes([
        remote_con,
        set_v & 0xFF, (set_v >> 8) & 0xFF,
        set_a & 0xFF, (set_a >> 8) & 0xFF,
        p[22],   # realChange, copied
        p[23],   # voltageSlow, copied
        p[21],   # currentOver, copied
        output,
        0,       # model: DC, forced
        0,       # refresh: no counter reset
    ])
    return bytes([0x12, 0xC8]) + payload


def guard_c8(frame: bytes) -> None:
    """Raise unless the 0xC8 frame is within this spike's safe envelope.

    The bench limit (BENCH_V_RAW, BENCH_A_RAW) applies only when the command
    energizes the output. A command with the output off may carry the supply's
    real setpoint unchanged, capped only at the device maximum.
    """
    if frame[:2] != bytes([0x12, 0xC8]) or len(frame) != 13:
        raise RuntimeError(f"refusing malformed 0xC8: {frame.hex(' ')}")
    p = frame[2:]
    remote_con, set_v, set_a, output, model = p[0], u16(p, 1), u16(p, 3), p[8], p[9]
    if remote_con not in (0, 1, 2):
        raise RuntimeError(f"refusing 0xC8 remoteCon={remote_con}")
    if output not in (0, 1):
        raise RuntimeError(f"refusing 0xC8 output={output}")
    if model != 0:
        raise RuntimeError(f"refusing 0xC8 model={model} (not DC)")
    v_cap, a_cap = (BENCH_V_RAW, BENCH_A_RAW) if output == 1 else (DEV_V_RAW, DEV_A_RAW)
    if set_v > v_cap:
        raise RuntimeError(f"refusing 0xC8 setV={set_v} (> {v_cap}, output={output})")
    if set_a > a_cap:
        raise RuntimeError(f"refusing 0xC8 setA={set_a} (> {a_cap}, output={output})")


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
    """Send one live read and return the 0xC3 reply, or None on timeout."""
    cap.log("TX", AF01, LIVE_READ, note)
    await client.write_gatt_char(AF01, LIVE_READ, response=True)
    return await cap.wait_for(AF01, lambda d: len(d) > 1 and d[1] == 0xC3, 2.0)


async def acquire_remote(client: BleakClient, cap: Capture, snapshot: bytes) -> bool:
    """Request remote control (output forced 0). Return True on 0xC9 == 0."""
    await send_c8(client, cap, build_c8(snapshot, remote_con=2, output=0), "request remote")
    c9 = await cap.wait_for(AF01, lambda d: len(d) > 1 and d[1] == 0xC9, 2.0)
    return bool(c9 and len(c9) > 2 and c9[2] == 0)


async def switch_off_here(client: BleakClient, cap: Capture,
                          orig_v_raw: int | None, orig_a_raw: int | None) -> bool:
    """On an already-connected, allowed link, force the output off and restore
    the original setpoint. Return True only if a reading confirms output == 0.
    """
    snap = await read_c3(client, cap, "pre-off read")
    if not snap:
        return False
    await acquire_remote(client, cap, snap)  # best effort; the off command follows regardless
    await send_c8(client, cap, build_c8(snap, remote_con=1, output=0, set_v_raw=orig_v_raw, set_a_raw=orig_a_raw), "restore setpoint, output off")
    await send_c8(client, cap, build_c8(snap, remote_con=0, output=0, set_v_raw=orig_v_raw, set_a_raw=orig_a_raw), "release remote")
    confirm = await read_c3(client, cap, "confirm off")
    return bool(confirm and decode_c3(confirm)["output"] == 0)


async def ensure_output_off(device_addr: str, orig_v_raw: int | None, orig_a_raw: int | None,
                            cap: Capture, attempts: int = 3) -> bool:
    """Reconnect and force the output off, retrying. Never raises.

    Turning the output off over Bluetooth needs a fresh bind, so the user has
    to press allow again. Returns True only when a reading confirms the output
    is off.
    """
    for attempt in range(1, attempts + 1):
        try:
            dev = await BleakScanner.find_device_by_filter(
                lambda d, adv: d.address == device_addr, timeout=20.0)
            if dev is None:
                print(f"teardown attempt {attempt}: unit not found, retrying")
                continue
            async with BleakClient(dev, timeout=20.0) as client:
                await client.start_notify(AF01, cap.handler(AF01))
                await client.start_notify(AF02, cap.handler(AF02))
                await asyncio.sleep(1.0)
                print(f"teardown attempt {attempt}/{attempts}: press ALLOW on the supply to let the spike switch the output off")
                cap.log("TX", AF02, BIND, f"bind (teardown {attempt})")
                await client.write_gatt_char(AF02, BIND, response=True)
                bind = await cap.wait_for(AF02, lambda d: d[:1] == b"\x19", 60.0)
                if not (bind and len(bind) > 1 and bind[1] == 0x00):
                    print(f"teardown attempt {attempt}: not allowed, retrying")
                    continue
                if await switch_off_here(client, cap, orig_v_raw, orig_a_raw):
                    return True
                print(f"teardown attempt {attempt}: could not confirm off, retrying")
        except Exception as exc:  # teardown must keep trying, never raise
            print(f"teardown attempt {attempt} error: {exc}")
    return False


def preconditions() -> str:
    """Enforce the HIL guards. Return the device id or exit."""
    if os.environ.get("MP305_HIL") != "1":
        sys.exit("refusing to run: set MP305_HIL=1 only when you are at the bench")
    device = os.environ.get("MP305_HIL_DEVICE")
    if not device:
        sys.exit("refusing to run: set MP305_HIL_DEVICE to the unit's CoreBluetooth UUID")
    print(__doc__)
    print("This spike will switch the OUTPUT ON at 5.00 V, 0.100 A, then drop the link.")
    print("Confirm: NOTHING is connected to the output terminals.")
    if input('Type "yes" to continue: ').strip() != "yes":
        sys.exit("aborted by user")
    return device


async def main() -> int:
    device = preconditions()
    cap = Capture()
    meta = {"kind": "meta", "date": dt.datetime.now().astimezone().isoformat(timespec="seconds"),
            "platform": platform.platform(), "python": platform.python_version(),
            "bleak": getattr(bleak, "__version__", "unknown"), "script": "spikes/link_drop/spike.py",
            "hil_device": device}
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

    commanded_on = False
    orig_v_raw: int | None = None
    orig_a_raw: int | None = None
    off_confirmed = False
    try:
        # Phase 1: connect, energize, then drop the link the way a crash would.
        async with BleakClient(dev, timeout=20.0) as client:
            meta["mtu"] = client.mtu_size
            await client.start_notify(AF01, cap.handler(AF01))
            await client.start_notify(AF02, cap.handler(AF02))
            await asyncio.sleep(1.0)
            cap.log("TX", AF02, BIND, "bind")
            await client.write_gatt_char(AF02, BIND, response=True)
            bind = await cap.wait_for(AF02, lambda d: d[:1] == b"\x19", 60.0)
            results["bind_reply"] = bind.hex(" ") if bind else None
            if not (bind and len(bind) > 1 and bind[1] == 0x00):
                print("not allowed; this spike needs remote control, aborting (nothing energized)")
                return 3
            snap = await read_c3(client, cap, "snapshot before control")
            if not snap:
                print("no 0xC3 snapshot, aborting (nothing energized)")
                return 4
            ps = snap[2:]
            orig_v_raw = ps[5] | (ps[6] << 8)
            orig_a_raw = ps[9] | (ps[10] << 8)
            results["original_setpoint"] = {"setV": orig_v_raw / 100, "setA": orig_a_raw / 1000}
            results["remote_granted"] = await acquire_remote(client, cap, snap)
            if not results["remote_granted"]:
                print("remote control not granted, aborting (nothing energized)")
                return 5
            # ENERGIZE. From here on, commanded_on drives the guaranteed teardown.
            await send_c8(client, cap, build_c8(snap, remote_con=1, output=1, set_v_raw=SET_V_RAW, set_a_raw=SET_A_RAW), "set 5V/0.1A, output on")
            commanded_on = True
            await cap.wait_for(AF01, lambda d: len(d) > 1 and d[1] == 0xC9, 2.0)
            on = []
            for i in range(5):
                c3 = await read_c3(client, cap, f"confirm on {i + 1}")
                if c3:
                    on.append(decode_c3(c3))
                await asyncio.sleep(0.2)
            results["output_confirmed_on"] = bool(on and on[-1]["output"] == 1)
            results["state_before_drop"] = on[-1] if on else None
            print(f"output on confirmed by read-back: {results['output_confirmed_on']} (teardown runs regardless)")
            print("dropping the link WITHOUT releasing (simulated crash) ...")
            cap.log("TX", AF01, b"", "abrupt disconnect, no release sent")
        # leaving the context manager disconnects; the output is likely still on

        # Phase 2: wait with the link down, then reconnect to observe and switch off.
        if commanded_on:
            wait_s = 12.0
            print(f"link down, waiting {wait_s:.0f} s ...")
            await asyncio.sleep(wait_s)
            print("reconnecting to observe ...")
            dev2 = await BleakScanner.find_device_by_filter(
                lambda d, adv: d.address == device, timeout=20.0)
            if dev2 is not None:
                async with BleakClient(dev2, timeout=20.0) as client:
                    await client.start_notify(AF01, cap.handler(AF01))
                    await client.start_notify(AF02, cap.handler(AF02))
                    await asyncio.sleep(1.0)
                    print("press ALLOW on the supply to observe and switch off")
                    cap.log("TX", AF02, BIND, "bind (reconnect)")
                    await client.write_gatt_char(AF02, BIND, response=True)
                    bind2 = await cap.wait_for(AF02, lambda d: d[:1] == b"\x19", 60.0)
                    results["reconnect_bind"] = bind2.hex(" ") if bind2 else None
                    if bind2 and len(bind2) > 1 and bind2[1] == 0x00:
                        after = await read_c3(client, cap, "state after drop")
                        if after:
                            dec = decode_c3(after)
                            results["state_after_drop"] = dec
                            results["output_still_on_after_drop"] = dec["output"] == 1
                            print(f"output still on after the drop: {dec['output'] == 1}")
                        off_confirmed = await switch_off_here(client, cap, orig_v_raw, orig_a_raw)
    finally:
        # Guaranteed teardown: if we ever energized and have not confirmed off,
        # reconnect and force the output off, retrying.
        if commanded_on and not off_confirmed:
            off_confirmed = await ensure_output_off(device, orig_v_raw, orig_a_raw, cap)
        results["output_off_confirmed"] = off_confirmed
        _write_capture(meta, cap, results)
        if commanded_on and not off_confirmed:
            print("\n*** WARNING: could not confirm the output is OFF. ***")
            print("*** SWITCH THE OUTPUT OFF ON THE FRONT PANEL NOW. ***")

    return 0 if (not commanded_on or off_confirmed) else 6


def _write_capture(meta: dict, cap: Capture, results: dict) -> None:
    """Write the JSONL capture and print the decoded results."""
    CAPTURE_DIR.mkdir(parents=True, exist_ok=True)
    stamp = dt.datetime.now().strftime("%Y-%m-%dT%H%M%S")
    out = CAPTURE_DIR / f"{stamp}-ble-link-drop.jsonl"
    with out.open("w") as f:
        f.write(json.dumps(meta) + "\n")
        for ev in cap.events:
            f.write(json.dumps(ev) + "\n")
        f.write(json.dumps({"kind": "results", **results}) + "\n")
    print("\n=== results ===")
    print(json.dumps(results, indent=2, ensure_ascii=False))
    print(f"\ncapture written to {out.relative_to(REPO)}")


if __name__ == "__main__":
    sys.exit(asyncio.run(main()))
