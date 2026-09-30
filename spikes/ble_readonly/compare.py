"""Compare two read-only spike captures reply by reply (firmware regression check).

Throwaway spike tool. Reads two JSONL captures written by spike.py, takes the
first reply of each kind (characteristic plus opcode), and prints whether the
bytes are identical, with a byte-level diff where they are not.

Run: python3 spikes/ble_readonly/compare.py OLD.jsonl NEW.jsonl
"""

from __future__ import annotations

import json
import sys


def replies(path: str) -> dict[str, bytes]:
    """Return the first RX frame per (characteristic, opcode) key."""
    out: dict[str, bytes] = {}
    for line in open(path):
        ev = json.loads(line)
        if ev.get("dir") != "RX":
            continue
        data = bytes.fromhex(ev["hex"].replace(" ", ""))
        # AF02 module replies carry the opcode at index 0, AF01 replies at index 1.
        op = data[0] if ev["char"] == "af02" else data[1]
        out.setdefault(f"{ev['char']}:{op:02x}", data)
    return out


def main() -> int:
    old, new = replies(sys.argv[1]), replies(sys.argv[2])
    for key in sorted(set(old) | set(new)):
        a, b = old.get(key), new.get(key)
        if a is None or b is None:
            print(f"{key}: only in {'new' if a is None else 'old'} capture")
            continue
        if a == b:
            print(f"{key}: identical ({len(a)} bytes)")
            continue
        print(f"{key}: DIFFERENT (old {len(a)} bytes, new {len(b)} bytes)")
        for i in range(max(len(a), len(b))):
            x = f"{a[i]:02x}" if i < len(a) else "--"
            y = f"{b[i]:02x}" if i < len(b) else "--"
            if x != y:
                print(f"    byte {i:2}: {x} -> {y}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
