#!/usr/bin/env python3
"""Preserve Ghidra access records and index candidate peripheral addresses.

Usage: index_memory_accesses.py EXPORT_ROOT VENDOR_REFERENCE_DIR OUTPUT_DIR
EXPORT_ROOT contains access-main, access-ble and access-pd exports. This
research index does not interpret unresolved pointers as RAM or prove that
vendor register names describe the installed chips.
"""
import collections
import csv
import hashlib
import json
import re
import shutil
import sys
import xml.etree.ElementTree as ET
from pathlib import Path


def read_rows(path):
    """Read an exporter TSV, including bounded address expressions."""
    with path.open() as stream:
        return list(csv.DictReader(stream, delimiter="\t"))


def write_rows(path, rows, fields):
    """Write deterministic tabular evidence with an explicit header."""
    with path.open("w") as stream:
        writer = csv.DictWriter(stream, fieldnames=fields, delimiter="\t")
        writer.writeheader()
        writer.writerows(rows)


def candidate(row, image):
    """Keep known MMIO ranges and unresolved-purpose 8051 address spaces."""
    if not row["resolved_address"]:
        return False
    address = int(row["resolved_address"], 16)
    if image == "pd":
        return row["space"] == "SFR" or (
            row["space"] == "BITS" and address >= 0x80
        ) or (row["space"] == "EXTMEM" and address >= 0x1000)
    return 0x40000000 <= address < 0x60000000 or 0xE0000000 <= address < 0xE0100000


def main():
    """Build indexes and audit counts without changing the source exports."""
    source, reference, out = map(Path, sys.argv[1:])
    out.mkdir(parents=True, exist_ok=True)
    names = collections.defaultdict(set)
    for path in sorted(reference.glob("*.svd")):
        root = ET.parse(path).getroot()
        peripherals = {p.findtext("name"): p for p in root.findall("./peripherals/peripheral")}
        for peripheral in peripherals.values():
            base = int(peripheral.findtext("baseAddress"), 0)
            registers = peripheral.findall("./registers/register")
            if not registers and peripheral.get("derivedFrom") in peripherals:
                registers = peripherals[peripheral.get("derivedFrom")].findall("./registers/register")
            for register in registers:
                offset = register.findtext("addressOffset")
                if offset is not None:
                    names[base + int(offset, 0)].add(
                        f'{path.stem}:{peripheral.findtext("name")}.{register.findtext("name")}'
                    )
    wch = reference / "CH583SFR.h"
    for name, address in re.findall(
        r"#define\s+(\w+)\s+\(\*\(\(\w+\)(0x[0-9a-fA-F]+)\)\)", wch.read_text(encoding="latin-1")
    ):
        names[int(address, 16)].add("CH583:" + name)
    summary = {
        "scope": "Decoded static instructions, not execution counts or full semantic coverage. High-pcode records are address-resolution candidates. Parameter-dependent accesses remain unresolved. PD XDATA >=0x1000 may include RAM and hardware; SFR includes CPU registers.",
        "images": {},
        "source_hashes": {},
    }
    for image in ["main", "ble", "pd"]:
        target = out / image
        target.mkdir(exist_ok=True)
        groups = collections.defaultdict(list)
        counts = {}
        for phase in ["raw", "high"]:
            path = source / f"access-{image}/memory-accesses-{phase}.tsv"
            rows = read_rows(path)
            fields = list(rows[0])
            shutil.copy2(path, target / path.name)
            summary["source_hashes"][f"{image}/{path.name}"] = hashlib.sha256(path.read_bytes()).hexdigest()
            unresolved = [row for row in rows if not row["resolved_address"]]
            candidates = [row for row in rows if candidate(row, image)]
            write_rows(target / f"unresolved-{phase}.tsv", unresolved, fields)
            write_rows(target / f"peripheral-candidates-{phase}.tsv", candidates, fields)
            for row in candidates:
                groups[(row["space"], int(row["resolved_address"], 16))].append(row)
            counts[phase] = dict(records=len(rows), unresolved=len(unresolved), candidate_records=len(candidates), instructions=len({row["instruction"] for row in rows}))
        statuses = read_rows(source / f"access-{image}/memory-accesses-status.tsv")
        shutil.copy2(source / f"access-{image}/memory-accesses-status.tsv", target)
        counts["decompiler_functions"] = len(statuses)
        counts["decompiler_incomplete"] = sum(row["decompiled"] != "true" for row in statuses)
        registers = []
        for (space, address), accesses in sorted(groups.items()):
            registers.append(dict(space=space, address=hex(address), directions=",".join(sorted({row["direction"] for row in accesses})), widths=",".join(sorted({row["bytes"] for row in accesses})), instructions=",".join(sorted({row["instruction"] for row in accesses})), functions=",".join(sorted({row["function"] for row in accesses})), vendor_candidates=";".join(sorted(n for n in names[address] if n.startswith("CH583:") == (image == "ble"))) if image != "pd" else "unidentified; generic 8051 names do not identify this chip"))
        write_rows(target / "registers.tsv", registers, ["space", "address", "directions", "widths", "instructions", "functions", "vendor_candidates"])
        counts["distinct_candidate_addresses"] = len(registers)
        summary["images"][image] = counts
    (out / "summary.json").write_text(json.dumps(summary, indent=2) + "\n")
    print(json.dumps(summary["images"], indent=2))


if __name__ == "__main__":
    main()
