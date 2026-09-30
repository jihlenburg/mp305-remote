"""Extract CH58x register addresses from WCH's CH583SFR.h into out/ch58x_regs.txt.

Input: svd/CH583SFR.h (download with fetch_references.sh).
Output lines: address (hex), width in bytes, register name.
"""
import os
import re

RE = os.path.expanduser("~/mp305b-fw-re/")
seen = set()
n = 0
with open(RE + "out/ch58x_regs.txt", "w") as out:
    for line in open(RE + "svd/CH583SFR.h", errors="ignore"):
        m = re.match(r"#define\s+R(8|16|32)_(\w+)\s+\(\*\(\(PUINT(?:8|16|32)V?\)(0x[0-9A-Fa-f]+)\)\)", line)
        if not m:
            continue
        a = int(m.group(3), 16)
        if a in seen:
            continue
        seen.add(a)
        out.write(f"{a:08x} {int(m.group(1)) // 8} {m.group(2)}\n")
        n += 1
print(n, "registers")
