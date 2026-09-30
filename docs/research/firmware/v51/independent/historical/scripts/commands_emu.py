"""Helpers for executing command handlers of app.bin (area: commands).

Usage:
    from commands_emu import H
    h = H()
    h.s8(0x30, 0)                        # poke S+0x30
    rep = h.handler(0x1B7F4, [0xC8, 1, ...], typ=6, shape="rlrt")
    wire = h.dispatch([0xC8, ...], typ=1)   # runs the real dispatcher 0x12F34

shape "rlrt": handler(request, length, reply, type)   (most handlers)
shape "rrtl": handler(request, reply, type, length)   (0x00, 0x20, 0xE0, 0xF0..0xFE)
"""
import os
import sys
import struct

sys.path.insert(0, os.path.expanduser("~/mp305b-fw-re/scripts"))
from emu_app import App  # noqa: E402
from unicorn.arm_const import UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3, UC_ARM_REG_LR, UC_ARM_REG_PC  # noqa: E402

S = 0x1FFFAACC
K = 0x1FFE0184
CHAN = 0x1FFF9660
GATE = 0x1FFF9448


class H(App):
    def __init__(self, stub_ui=True):
        super().__init__()
        self.calls = []
        if stub_ui:
            pass

    # state helpers
    def s8(self, off, v): self.w8(S + off, v)
    def s16(self, off, v): self.w16(S + off, v)
    def s32(self, off, v): self.w32(S + off, v)
    def g8(self, off): return self.r8(S + off)
    def g16(self, off): return self.r16(S + off)
    def g32(self, off): return self.r32(S + off)

    def snap(self, base=S, n=0x200):
        return self.read(base, n)

    def diff(self, before, base=S, n=0x200):
        after = self.read(base, n)
        return [(i, before[i], after[i]) for i in range(n) if before[i] != after[i]]

    def record(self, name, addr, ret=0, args=4):
        """Replace callee with a recorder that logs its arguments."""
        def fn(app, name=name, ret=ret, args=args):
            regs = [app.reg(r) for r in (UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3)][:args]
            app.calls.append((name, tuple(regs)))
            return ret
        self.hook_func(addr, fn)

    def handler(self, addr, req, typ=6, shape="rlrt", replen=300):
        req = bytes(req)
        r = self.alloc(req)
        rep = self.alloc(replen)
        self.mu.mem_write(rep, b"\xEE" * replen)
        if shape == "rlrt":
            n = self.call(addr, r, len(req), rep, typ)
        elif shape == "rrtl":
            n = self.call(addr, r, rep, typ, len(req))
        elif shape == "rl":
            n = self.call(addr, r, len(req), typ)
            return n, b""
        else:
            raise ValueError(shape)
        return n, self.read(rep, n) if 0 < n < 0x1000 else b""

    def dispatch(self, req, typ=6, dst=2, chan=0, elapsed=0):
        """Run the real dispatcher on one request. Returns (reply_record, wire)."""
        req = bytes(req)
        rec = CHAN + chan * 260
        self.mu.mem_write(rec, bytes([typ, dst, len(req) & 0xFF, 0]) + req)
        for i in range(4):
            self.w8(0x1FFE01AC + i, 1 if i == chan else 0)
        self.w8(GATE, 0)  # tx pending flag
        self.w8(GATE + 0x102, 0)
        self.call(0x12F34, elapsed)
        if self.r8(GATE) == 1:
            n = self.r8(GATE + 0x102)
            wire = self.read(GATE + 2, n)
            txrec = self.read(0x1FFF9EFC, 4 + self.r8(0x1FFF9EFC + 2))
            return txrec, wire
        return None, None


REGIONS = [
    ("S", S, 0x200),
    ("PWR", 0x1FFFA934, 0x198),      # power-stage block (setpoints, output flags, faults)
    ("GATE", GATE, 0x10C),           # tx record / flags word at +0x108 (0x1FFF9550)
    ("K", K, 0x48),
    ("PROG", 0x1FFFA354, 0xC0),
    ("PD", 0x1FFFA138, 0x21C),
    ("XFER", 0x1FFFA8C4, 0x10),
    ("UPD", 0x1FFFA00C, 0x98),
    ("CFG", 0x1FFFA0B8, 0x80),
    ("PDC", 0x1FFF9B34, 0x90),
    ("CAP", 0x1FFF942C, 0x1C),
]


def region_name(addr):
    for n, b, l in REGIONS:
        if b <= addr < b + l:
            return "%s+0x%X" % (n, addr - b)
    return hex(addr)


class HT(H):
    """H with call tracing (callee still executes) and multi-region diffs."""

    def __init__(self):
        super().__init__()
        self.watch = {}
        from unicorn import UC_HOOK_CODE
        self.mu.hook_add(UC_HOOK_CODE, self._watch_hook)

    def _watch_hook(self, mu, addr, size, user):
        n = self.watch.get(addr)
        if n:
            regs = [mu.reg_read(r) for r in (UC_ARM_REG_R0, UC_ARM_REG_R1)]
            self.calls.append((n, regs[0]))

    def traceon(self, addr, name):
        self.watch[addr & ~1] = name

    def snap_all(self):
        return {n: self.read(b, l) for n, b, l in REGIONS}

    def diff_all(self, before):
        out = []
        for n, b, l in REGIONS:
            a = self.read(b, l)
            o = before[n]
            for i in range(l):
                if a[i] != o[i]:
                    out.append(("%s+0x%X" % (n, i), o[i], a[i]))
        return out
