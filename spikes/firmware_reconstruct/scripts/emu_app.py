"""Unicorn harness for app.bin (HC32F4A0, linked at 0x10000).

Usage from Python:
    from emu_app import App
    a = App()                      # flash + RAM init image, peripherals as zeroed RAM
    a.w8(0x1FFFAACC + 0x30, 0)     # poke state
    req = a.alloc(bytes([0xC8, 1, 0x10, 0x04, 0xE8, 0x03, 0, 0, 0, 1, 0, 0]))
    rep = a.alloc(64)
    ret = a.call(0x1B7F4, req, 12, rep, 6)   # returns r0
    print(a.read(rep, 4).hex())

Calls return when the function returns to the trap address. Functions that
reach FreeRTOS or hardware wait loops may need hooks; use a.hook_func(addr, py)
to replace a callee (py receives the App and returns r0).
"""
import os
import struct
from unicorn import Uc, UC_ARCH_ARM, UC_MODE_THUMB, UC_MODE_MCLASS, UC_HOOK_CODE, UC_HOOK_MEM_UNMAPPED
from unicorn.arm_const import *

RE = os.path.expanduser("~/mp305b-fw-re/")
TRAP = 0x1FFF00


class App:
    def __init__(self):
        mu = Uc(UC_ARCH_ARM, UC_MODE_THUMB | UC_MODE_MCLASS)
        self.mu = mu
        d = open(RE + "bin/app.bin", "rb").read()
        mu.mem_map(0, 0x200000)
        mu.mem_write(0x10000, d)
        mu.mem_map(0x1FFE0000, 0x80000)
        rw = open(RE + "bin/ram_rw_init.bin", "rb").read()
        mu.mem_write(0x1FFE0000, rw)
        mu.mem_map(0x200F0000, 0x1000)
        mu.mem_map(0x40000000, 0x100000)  # peripherals as plain RAM
        mu.mem_map(0x88000000, 0x200000)
        mu.mem_map(0xE0000000, 0x100000)
        mu.mem_map(0x30000000, 0x10000)   # scratch heap for test buffers
        self.heap = 0x30000000
        self.hooks = {}
        self.trace = False
        mu.hook_add(UC_HOOK_CODE, self._code)
        mu.hook_add(UC_HOOK_MEM_UNMAPPED, self._unmapped)

    def _unmapped(self, mu, access, addr, size, value, user):
        print("unmapped access", hex(addr), "pc", hex(mu.reg_read(UC_ARM_REG_PC)))
        return False

    def _code(self, mu, addr, size, user):
        if self.trace:
            print("pc", hex(addr))
        h = self.hooks.get(addr)
        if h:
            r0 = h(self)
            if r0 is not None:
                mu.reg_write(UC_ARM_REG_R0, r0 & 0xFFFFFFFF)
            mu.reg_write(UC_ARM_REG_PC, mu.reg_read(UC_ARM_REG_LR))

    def hook_func(self, addr, fn):
        self.hooks[addr & ~1] = fn

    def alloc(self, data_or_len):
        data = bytes(data_or_len) if not isinstance(data_or_len, int) else bytes(data_or_len)
        a = self.heap
        self.mu.mem_write(a, data)
        self.heap += (len(data) + 15) & ~15
        return a

    def read(self, a, n):
        return bytes(self.mu.mem_read(a, n))

    def w8(self, a, v): self.mu.mem_write(a, bytes([v & 0xFF]))
    def w16(self, a, v): self.mu.mem_write(a, struct.pack("<H", v & 0xFFFF))
    def w32(self, a, v): self.mu.mem_write(a, struct.pack("<I", v & 0xFFFFFFFF))
    def r8(self, a): return self.read(a, 1)[0]
    def r16(self, a): return struct.unpack("<H", self.read(a, 2))[0]
    def r32(self, a): return struct.unpack("<I", self.read(a, 4))[0]
    def reg(self, r): return self.mu.reg_read(r)

    def call(self, addr, *args, count=5_000_000):
        mu = self.mu
        regs = [UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3]
        sp = 0x2003F000
        stack_args = list(args[4:])
        for i, v in enumerate(args[:4]):
            mu.reg_write(regs[i], v & 0xFFFFFFFF)
        for i, v in enumerate(stack_args):
            mu.mem_write(sp + 4 * i, struct.pack("<I", v & 0xFFFFFFFF))
        mu.reg_write(UC_ARM_REG_SP, sp)
        mu.reg_write(UC_ARM_REG_LR, TRAP | 1)
        mu.emu_start(addr | 1, TRAP, count=count)
        return mu.reg_read(UC_ARM_REG_R0)


if __name__ == "__main__":
    a = App()
    rep = a.alloc(64)
    req = a.alloc(bytes([0x00, 0x00, 0x00, 0x00]))
    n = a.call(0x1DFFC, req, rep, 6, 4)
    print("0x00 handler ->", n, a.read(rep, n).hex())
