#!/usr/bin/env python3
"""RISC-V (RV32IMAC) disassembly of bin/ch58x.bin with the RAM copies mapped.
usage: ch58x_dis.py ADDR [NBYTES]   (ADDR in flash 0x1000.. or RAM 0x20002000..)"""
import sys, os, struct
from capstone import Cs, CS_ARCH_RISCV, CS_MODE_RISCV32, CS_MODE_RISCVC
B = open(os.path.expanduser("~/mp305b-fw-re/bin/ch58x.bin"), "rb").read()
BASE = 0x1000
def mem(addr, n):
    if 0x20002000 <= addr < 0x20002C40:
        o = addr - 0x20002000 + 0x1008 - BASE
    elif 0x20002C40 <= addr < 0x20002F50:
        o = addr - 0x20002C40 + 0x9318 - BASE
    else:
        o = addr - BASE
    return B[o:o + n]
def u32(a): return struct.unpack("<I", mem(a, 4))[0]
if __name__ == "__main__":
    a = int(sys.argv[1], 16); n = int(sys.argv[2], 0) if len(sys.argv) > 2 else 0x80
    md = Cs(CS_ARCH_RISCV, CS_MODE_RISCV32 | CS_MODE_RISCVC)
    code = mem(a, n)
    lui = {}
    for i in md.disasm(code, a):
        extra = ""
        ops = i.op_str
        if i.mnemonic in ("lui", "c.lui"):
            r, v = ops.split(", "); lui[r] = int(v, 0) << 12
        elif i.mnemonic in ("addi", "c.addi") and ops.count(",") == 2:
            r, s, v = ops.split(", ")
            if s in lui: extra = f"  ; ={(lui[s] + int(v,0)) & 0xffffffff:#x}"
        elif i.mnemonic == "auipc":
            r, v = ops.split(", "); lui[r] = (i.address + (int(v, 0) << 12)) & 0xffffffff
        elif i.mnemonic in ("jal", "c.jal", "c.j", "j", "c.beqz", "c.bnez") or i.mnemonic.startswith("b"):
            try:
                off = int(ops.split(", ")[-1], 0); extra = f"  ; ->{(i.address + off) & 0xffffffff:#x}"
            except ValueError: pass
        elif i.mnemonic in ("jalr", "c.jalr", "c.jr"):
            pass
        m = i.mnemonic
        if m.lstrip("c.") in ("lw","sw","lb","lbu","sb","sh","lh","lhu") and "(" in ops:
            off, rest = ops.split(", ")[1].split("(")
            r = rest.rstrip(")")
            if r in lui: extra = f"  ; @{(lui[r] + int(off,0)) & 0xffffffff:#x}"
            if r == "gp": extra = f"  ; @{(0x200023b8 + int(off,0)) & 0xffffffff:#x}"
        if m in ("addi",) and ", gp, " in ops:
            extra = f"  ; ={(0x200023b8 + int(ops.split(', ')[2],0)) & 0xffffffff:#x}"
        print(f"{i.address:08x}: {i.bytes.hex():10s} {m:8s} {ops}{extra}")
