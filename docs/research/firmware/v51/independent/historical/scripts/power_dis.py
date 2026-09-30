#!/usr/bin/env python3
"""Recursive-descent Thumb disassembler for app.bin (power analysis helper).

Usage: power_dis.py ADDR [ADDR ...]
Follows branches inside the function starting at ADDR, stops at returns and
tail calls (b to an address before start or far away is printed as tail).
Annotates PC-relative literals with HC32F4A0 register names.
"""
import os
import sys
import capstone
import re

RE = os.path.expanduser("~/mp305b-fw-re/")
BASE = 0x10000
D = open(RE + "bin/app.bin", "rb").read()
REGS = {}
for line in open(RE + "out/hc32f4a0_regs.txt"):
    f = line.split()
    if len(f) >= 3:
        REGS[int(f[0], 16)] = f[2]
for line in open(RE + "out/hc32f4a0_periph.txt"):
    f = line.split()
    REGS.setdefault(int(f[0], 16), f[2])

md = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB | capstone.CS_MODE_MCLASS)
md.detail = True


def word(a):
    return int.from_bytes(D[a - BASE:a - BASE + 4], "little")


def one(a):
    for i in md.disasm(D[a - BASE:a - BASE + 4], a, 1):
        return i
    return None


def lit(i):
    if i.mnemonic.startswith("ldr") and "[pc" in i.op_str:
        try:
            off = int(i.op_str.split("#")[1].rstrip("]"), 0)
        except Exception:
            off = 0
        la = ((i.address + 4) & ~3) + off
        v = word(la)
        n = REGS.get(v, "")
        return la, "  ; =0x%08x %s" % (v, n)
    if i.mnemonic == "adr":
        off = int(i.op_str.split("#")[1], 0)
        return None, "  ; =&0x%x" % (((i.address + 4) & ~3) + off)
    return None, ""


def func(start, limit=4000):
    seen = {}
    work = [start]
    lits = set()
    while work:
        a = work.pop()
        while a not in seen and len(seen) < limit:
            i = one(a)
            if i is None:
                break
            seen[a] = i
            la, _ = lit(i)
            if la:
                lits.add(la)
            m = i.mnemonic
            ops = i.op_str
            if m in ("tbb", "tbh"):
                # table branch: read table following the instruction
                base = a + 4
                n = 0
                tgt = []
                sz = 1 if m == "tbb" else 2
                # guess table length from preceding cmp
                j = 0
                while n < 64:
                    e = int.from_bytes(D[base - BASE + j:base - BASE + j + sz], "little")
                    t = base + 2 * e
                    tgt.append(t)
                    j += sz
                    n += 1
                    if base + j >= min(tgt):
                        break
                for t in tgt:
                    work.append(t)
                break
            if re.match(r"^b(eq|ne|cs|hs|cc|lo|mi|pl|vs|vc|hi|ls|ge|lt|gt|le|al)?(\.w|\.n)?$", m):
                try:
                    t = int(ops.split("#")[-1], 0)
                except Exception:
                    t = None
                cond = m not in ("b", "b.w")
                if t is not None:
                    if cond:
                        work.append(t)
                    else:
                        if t < start or t > start + 0x2000:
                            break  # tail call
                        work.append(t)
                        break
            elif m in ("cbz", "cbnz"):
                t = int(ops.split("#")[-1], 0)
                work.append(t)
            if m == "bx" or (m.startswith("pop") and "pc" in ops) or (m.startswith("ldr") and ops.startswith("pc")):
                break
            a += i.size
    return seen, lits


def show(start):
    seen, lits = func(start)
    print("==== %08x" % start)
    for a in sorted(seen):
        i = seen[a]
        _, c = lit(i)
        extra = ""
        if i.mnemonic in ("b", "b.w") or i.mnemonic.startswith("bl"):
            pass
        print("%08x: %-8s %s%s" % (a, i.mnemonic, i.op_str, c))


if __name__ == "__main__":
    for s in sys.argv[1:]:
        show(int(s, 16))
