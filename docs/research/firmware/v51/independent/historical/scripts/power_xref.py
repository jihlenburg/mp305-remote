#!/usr/bin/env python3
"""Base+offset field cross-reference for app.bin (power analysis helper).

For each function start (from the fixed Ghidra index), disassemble by
recursive descent, track registers that hold a literal address (RAM or
peripheral) and emit every load/store through them as an absolute address.
Also tracks `adds rX, #imm` / `add.w rX, rY, #imm` on tracked bases.
Output TSV: absaddr, R/W, width, insn_addr, func, base, offset, text
"""
import os
import re
import sys

sys.path.insert(0, os.path.expanduser("~/mp305b-fw-re/scripts"))
import power_dis as P  # noqa: E402

FUNCS = sys.argv[1]
OUT = sys.argv[2]
starts = sorted(int(l.split("\t")[0], 16) for l in open(FUNCS) if l.strip())
starts = [s for s in starts if 0x10000 <= s < 0x84400]

MEMRE = re.compile(r"^(ldr|str)(b|h|sb|sh|d|ex|exb|exh)?(\.w)?$")


def interesting(v):
    return 0x1FFE0000 <= v < 0x20060000 or 0x40000000 <= v < 0x40100000 or 0xE0000000 <= v < 0xE0100000


out = open(OUT, "w")
for s in starts:
    try:
        seen, _ = P.func(s)
    except Exception:
        continue
    regs = {}
    for a in sorted(seen):
        i = seen[a]
        m = i.mnemonic
        ops = i.op_str
        if m.startswith("ldr") and "[pc" in ops:
            la, _ = P.lit(i)
            rd = ops.split(",")[0].strip()
            v = P.word(la)
            if m in ("ldr", "ldr.w") and interesting(v):
                regs[rd] = v
            else:
                regs.pop(rd, None)
            continue
        if m in ("bl", "blx"):
            for r in ("r0", "r1", "r2", "r3", "ip"):
                regs.pop(r, None)
            continue
        mm = MEMRE.match(m)
        if mm and "[" in ops:
            inner = ops[ops.index("[") + 1:ops.index("]")]
            parts = [p.strip() for p in inner.split(",")]
            base = parts[0]
            off = 0
            if len(parts) > 1 and parts[1].startswith("#"):
                off = int(parts[1][1:], 0)
            elif len(parts) > 1:
                off = None
            if base in regs and off is not None:
                w = {"b": 1, "sb": 1, "h": 2, "sh": 2, "d": 8, None: 4, "ex": 4, "exb": 1, "exh": 2}[mm.group(2)]
                out.write("%08x\t%s\t%d\t%08x\t%08x\t%08x\t%d\t%s %s\n" % (
                    regs[base] + off, "R" if m.startswith("ldr") else "W", w, a, s, regs[base], off, m, ops))
            # destination register clobbered by loads
            if m.startswith("ldr"):
                dests = [ops.split(",")[0].strip()]
                if mm.group(2) == "d":
                    dests.append(ops.split(",")[1].strip())
                for d in dests:
                    regs.pop(d, None)
            continue
        # add immediate to tracked base
        am = re.match(r"^(adds|add|add\.w|addw|subs|sub|sub\.w|subw)$", m)
        if am:
            f = [x.strip() for x in ops.split(",")]
            if len(f) == 2 and f[1].startswith("#") and f[0] in regs:
                v = int(f[1][1:], 0)
                regs[f[0]] = regs[f[0]] + (v if m.startswith("add") else -v)
                continue
            if len(f) == 3 and f[2].startswith("#") and f[1] in regs:
                v = int(f[2][1:], 0)
                regs[f[0]] = regs[f[1]] + (v if m.startswith("add") else -v)
                continue
        if m in ("mov", "movs") :
            f = [x.strip() for x in ops.split(",")]
            if len(f) == 2 and f[1] in regs:
                regs[f[0]] = regs[f[1]]
                continue
        # any other write to a register clobbers it (first operand)
        f = ops.split(",")
        if f and not m.startswith(("str", "cmp", "cmn", "tst", "teq", "b", "cb", "push", "it", "vstr", "vcmp")):
            regs.pop(f[0].strip(), None)
out.close()
