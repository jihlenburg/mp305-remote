"""Read-only spike: read the standard Device Information Service and the unknown DB01 value.

Throwaway experiment. Performs GATT reads only: no writes, no notifications, no bind.
Run: uv run --with bleak python spikes/ble_readonly/dis_read.py
"""

from __future__ import annotations

import asyncio
import json
import sys

from bleak import BleakClient, BleakScanner

NAME_PREFIX = "0000MP30"
DIS = {
    "00002a23-0000-1000-8000-00805f9b34fb": "system_id",
    "00002a24-0000-1000-8000-00805f9b34fb": "model_number",
    "00002a25-0000-1000-8000-00805f9b34fb": "serial_number",
    "00002a26-0000-1000-8000-00805f9b34fb": "firmware_revision",
    "00002a27-0000-1000-8000-00805f9b34fb": "hardware_revision",
    "00002a28-0000-1000-8000-00805f9b34fb": "software_revision",
    "00002a29-0000-1000-8000-00805f9b34fb": "manufacturer_name",
    "00002a2a-0000-1000-8000-00805f9b34fb": "regulatory_cert",
    "00002a50-0000-1000-8000-00805f9b34fb": "pnp_id",
    "0000db01-0000-1000-8000-00805f9b34fb": "db01_value",
    "0000af01-0000-1000-8000-00805f9b34fb": "af01_value",
    "0000af02-0000-1000-8000-00805f9b34fb": "af02_value",
}


async def main() -> int:
    dev = await BleakScanner.find_device_by_filter(
        lambda d, adv: (adv.local_name or d.name or "").startswith(NAME_PREFIX), timeout=20.0)
    if dev is None:
        print("MP305 not found")
        return 2
    out = {}
    async with BleakClient(dev, timeout=20.0) as client:
        for uuid, label in DIS.items():
            try:
                raw = bytes(await client.read_gatt_char(uuid))
                out[label] = {"hex": raw.hex(" "), "ascii": raw.decode("ascii", "replace")}
            except Exception as exc:  # spike: record and continue
                out[label] = {"error": str(exc)}
    print(json.dumps(out, indent=2, ensure_ascii=False))
    return 0


if __name__ == "__main__":
    sys.exit(asyncio.run(main()))
