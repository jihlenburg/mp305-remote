#!/usr/bin/env python3
"""Restore a firmware container into a fresh external analysis workspace.

This discovery tool accepts the documented container format rather than a
V51 hash. It verifies the checksum and main reset vector. Companion slicing
requires an explicit size; candidate offsets are reported for inspection.
"""

import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import struct


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--firmware", type=Path, required=True)
    p.add_argument("--scratch", type=Path, required=True)
    p.add_argument("--release", required=True)
    p.add_argument("--pd-size", type=lambda x: int(x, 0))
    p.add_argument("--companion-base", type=lambda x: int(x, 0), default=0x1000)
    a = p.parse_args()
    out = a.scratch.resolve()
    repo = Path(__file__).resolve().parents[3]
    if not re.fullmatch(r"[A-Za-z0-9._-]+", a.release):
        p.error("Use a simple release label")
    if out.exists() or out.is_relative_to(repo):
        p.error("Choose a fresh scratch directory outside the repository")
    raw = a.firmware.read_bytes()
    if len(raw) < 32:
        p.error("Container is shorter than its header")
    words = struct.unpack_from("<8I", raw)
    key, checksum, base, data_base, appsize, datasize, baud, rapid = words
    if len(raw) != 32 + appsize + datasize or (appsize + datasize) % 4:
        p.error("Header sizes do not match the container")
    if appsize < 32 or appsize % 4:
        p.error("Invalid main image size")
    decoded = bytearray()
    state = checksum
    for (value,) in struct.iter_unpack("<I", raw[32:]):
        decoded += struct.pack("<I", value ^ state)
        state = ((state + key) ^ key) & 0xFFFFFFFF
    if sum(v[0] for v in struct.iter_unpack("<I", decoded)) & 0xFFFFFFFF != checksum:
        p.error("Restored checksum mismatch")
    app, data = bytes(decoded[:appsize]), bytes(decoded[appsize:])
    sp, reset = struct.unpack_from("<2I", app)
    if not reset & 1 or not base <= reset - 1 < base + appsize:
        p.error("Main reset vector is inconsistent with the header base")
    if a.pd_size is not None and not 128 <= a.pd_size < len(data) - 32:
        p.error("PD slice is outside companion data")
    candidates = []
    marker = bytes.fromhex("a9 bd f9 f5")
    pos = data.find(marker)
    while pos >= 0:
        start = pos - 0x18
        if start >= 0 and data[start] & 0x7F == 0x6F:
            candidates.append(hex(start))
        pos = data.find(marker, pos + 1)
    out.mkdir(parents=True)
    for name in ["inputs", "exports", "logs", "projects"]:
        (out / name).mkdir()
    shutil.copy2(a.firmware, out / "inputs/original.fwd")
    images = {}

    def image(name, content, processor=None, load=None, confidence=None):
        (out / "inputs" / name).write_bytes(content)
        row = dict(
            file="inputs/" + name,
            bytes=len(content),
            sha256=hashlib.sha256(content).hexdigest(),
        )
        if processor:
            row.update(
                processor=processor, load_address=hex(load), mapping_evidence=confidence
            )
        images[name] = row
        strings = [
            dict(offset=hex(m.start()), text=m[0].decode())
            for m in re.finditer(rb"[\x20-\x7e]{5,}", content)
        ]
        (out / "exports" / f"{name}.strings.json").write_text(
            json.dumps(strings, indent=2) + "\n"
        )

    image(
        "main-arm.bin",
        app,
        "ARM:LE:32:Cortex",
        base,
        "container base and in-range Thumb reset vector",
    )
    image("companion-data.bin", data)
    if a.pd_size is not None:
        pd, ble = data[: a.pd_size], data[a.pd_size :]
        if pd[0] != 2:
            p.error(
                "Configured PD slice does not begin with LJMP; workspace retained for inspection"
            )
        image(
            "pd-8051.bin",
            pd,
            "8051:BE:16:default",
            a.companion_base,
            "explicit configured candidate; verify interrupt prologues",
        )
        image(
            "ble-riscv.bin",
            ble,
            "RISCV:LE:32:default",
            a.companion_base,
            "explicit configured candidate; verify startup and RAM copies",
        )
    record = dict(
        schema=1,
        release=a.release,
        container_sha256=hashlib.sha256(raw).hexdigest(),
        header=dict(
            zip(
                [
                    "key",
                    "checksum",
                    "app_base",
                    "data_base",
                    "app_size",
                    "data_size",
                    "baud",
                    "rapid_baud",
                ],
                words,
            )
        ),
        main_stack_pointer=hex(sp),
        main_reset=hex(reset),
        companion_split_candidates=candidates,
        selected_pd_size=a.pd_size,
        images=images,
        next_steps=[
            "Inspect identity and companion candidates",
            "Import fresh programs with import_release.py",
            "Discover RAM copies and scatter loading",
            "Export analysis and compare fingerprints",
            "Port address-specific probes only after review",
        ],
    )
    (out / "release.json").write_text(json.dumps(record, indent=2) + "\n")
    print(json.dumps(record, indent=2))


if __name__ == "__main__":
    main()
