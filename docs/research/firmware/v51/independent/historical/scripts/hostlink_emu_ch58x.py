"""Minimal Unicorn harness for the CH58x image (hostlink analysis).

Maps flash at 0x0 (image at 0x1000), RAM 0x20000000-0x20010000 with the
startup copies done, and a fake WCH library table at 0x40000 whose entries
point to trap stubs implemented in Python (memcpy, memset, memcmp, and a
generic logger for the rest).
"""
import struct
from unicorn import Uc, UC_ARCH_RISCV, UC_MODE_RISCV32, UC_HOOK_CODE, UC_HOOK_MEM_UNMAPPED
from unicorn.riscv_const import *

RE = '/Users/jihlenburg/mp305b-fw-re/'
TRAP = 0x7FF00
LIBSTUB = 0x7E000   # stub i at LIBSTUB + 4*i


class CH:
    def __init__(self):
        mu = Uc(UC_ARCH_RISCV, UC_MODE_RISCV32)
        self.mu = mu
        img = open(RE + 'bin/ch58x.bin', 'rb').read()
        mu.mem_map(0, 0x80000)
        mu.mem_write(0x1000, img)
        mu.mem_map(0x20000000, 0x10000)
        mu.mem_write(0x20002000, img[0x1008 - 0x1000:0x1c48 - 0x1000])
        mu.mem_write(0x20002c40, img[0x9318 - 0x1000:0x9318 - 0x1000 + 0x310])
        mu.mem_map(0x40000000, 0x100000)   # peripherals as RAM
        mu.mem_map(0xE0000000, 0x100000)
        # library jump table: word at 0x40000+off holds a function pointer
        self.libnames = {}
        for off in range(0, 0x400, 4):
            mu.mem_write(0x40000 + off, struct.pack('<I', LIBSTUB + off))
        # stubs: 'ret' (c.jr ra = 0x8082)
        mu.mem_write(LIBSTUB, b'\x82\x80\x00\x00' * 0x100)
        mu.mem_write(TRAP, b'\x82\x80')
        self.hooks = {}
        self.log = []
        self.lib = {}
        mu.hook_add(UC_HOOK_CODE, self._code)
        mu.hook_add(UC_HOOK_MEM_UNMAPPED, self._unm)
        self.heap = 0x2000C000

    def _unm(self, mu, acc, addr, size, val, u):
        print('unmapped', hex(addr), 'pc', hex(mu.reg_read(UC_RISCV_REG_PC)))
        return False

    def a(self, i): return self.mu.reg_read(UC_RISCV_REG_A0 + i)

    def _code(self, mu, addr, size, u):
        if LIBSTUB <= addr < LIBSTUB + 0x400:
            off = addr - LIBSTUB
            a0, a1, a2 = self.a(0), self.a(1), self.a(2)
            r = 0
            if off == 0x4c:      # memcpy(dst, src, n)
                mu.mem_write(a0, bytes(mu.mem_read(a1, a2)))
                r = a0
            elif off == 0x48:    # memset(dst, c, n)
                mu.mem_write(a0, bytes([a1 & 0xff]) * a2)
                r = a0
            elif off == 0x3c:    # memcmp -> 0 equal? (tmos_memcmp returns TRUE when equal)
                r = 1 if bytes(mu.mem_read(a0, a2)) == bytes(mu.mem_read(a1, a2)) else 0
            elif off in self.lib:
                r = self.lib[off](self)
            self.log.append(('lib', hex(0x40000 + off), hex(a0), hex(a1), hex(a2), hex(r if r is not None else 0)))
            if r is not None:
                mu.reg_write(UC_RISCV_REG_A0, r & 0xffffffff)
            return
        h = self.hooks.get(addr)
        if h:
            r = h(self)
            if r is not None:
                mu.reg_write(UC_RISCV_REG_A0, r & 0xffffffff)
            mu.reg_write(UC_RISCV_REG_PC, mu.reg_read(UC_RISCV_REG_RA))

    def alloc(self, data):
        data = bytes(data) if not isinstance(data, int) else bytes(data)
        p = self.heap
        self.mu.mem_write(p, data)
        self.heap += (len(data) + 15) & ~15
        return p

    def read(self, a, n): return bytes(self.mu.mem_read(a, n))
    def w8(self, a, v): self.mu.mem_write(a, bytes([v & 0xff]))
    def w16(self, a, v): self.mu.mem_write(a, struct.pack('<H', v & 0xffff))
    def w32(self, a, v): self.mu.mem_write(a, struct.pack('<I', v & 0xffffffff))
    def r8(self, a): return self.read(a, 1)[0]
    def r16(self, a): return struct.unpack('<H', self.read(a, 2))[0]
    def r32(self, a): return struct.unpack('<I', self.read(a, 4))[0]

    def call(self, addr, *args, count=2_000_000):
        mu = self.mu
        for i, v in enumerate(args):
            mu.reg_write(UC_RISCV_REG_A0 + i, v & 0xffffffff)
        mu.reg_write(UC_RISCV_REG_GP, 0x20002000)
        mu.reg_write(UC_RISCV_REG_SP, 0x2000BFF0)
        mu.reg_write(UC_RISCV_REG_RA, TRAP)
        mu.emu_start(addr, TRAP, count=count)
        return mu.reg_read(UC_RISCV_REG_A0)
