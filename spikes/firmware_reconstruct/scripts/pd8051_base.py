"""Find the CODE load address of the 8051 slice of data.bin.

The slice starts with LJMP instructions at the standard 8051 interrupt
vector positions. Their targets only land on interrupt service routine
prologues (PUSH ACC followed by another PUSH) if the slice is loaded at the
right base. The most frequent (target - prologue) difference is the base.
"""
import os
import re
from collections import Counter

RE = os.path.expanduser("~/mp305b-fw-re/")
d = open(RE + "bin/pd8051.bin", "rb").read()
vec = [0x00, 0x03, 0x0B, 0x13, 0x1B, 0x23, 0x2B, 0x33, 0x3B, 0x43, 0x4B, 0x53, 0x5B, 0x63, 0x6B, 0x73, 0x7B, 0x83, 0x8B, 0x93]
targets = [(d[v + 1] << 8) | d[v + 2] for v in vec if d[v] == 0x02]
prologues = [m.start() for m in re.finditer(b"\xc0\xe0", d) if d[m.start() + 2] == 0xC0]
c = Counter(t - p for t in targets for p in prologues)
print("vector targets:", [hex(t) for t in targets])
print("most common base candidates:", [(hex(k), v) for k, v in c.most_common(3)])
