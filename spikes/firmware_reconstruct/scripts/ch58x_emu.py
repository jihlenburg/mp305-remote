#!/usr/bin/env python3
"""Unicorn harness for bin/ch58x.bin (WCH CH58x, RV32IMAC, linked at 0x1000).

Maps flash, the RAM copies made by handle_reset (highcode, .data), zeroed BSS,
peripherals as plain RAM, and a fake WCH BLE library jump table at 0x40000
whose slots point at stub addresses. Stubs are implemented in Python.

Captures:
  uart1_tx   bytes written to UART1 THR (0x40003408), i.e. CH58x -> main MCU
  notifies   (which, bytes) passed to GATT_Notification (AF01/AF02 notify)
  lib_calls  list of (name, args) for every library call
Usage: from ch58x_emu import Emu; e = Emu(); e.call(0x35a8, ...)
"""
import os, struct
from unicorn import Uc, UC_ARCH_RISCV, UC_MODE_RISCV32, UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.riscv_const import *

RE = os.path.expanduser("~/mp305b-fw-re/")
IMG = open(RE + "bin/ch58x.bin", "rb").read()
LIB = {}
for line in open(os.path.expanduser("~/mp305b/docs/research/firmware/v51/canonical/wch-sdk-api.tsv")).read().splitlines()[1:]:
    slot, _, name = line.split("\t")
    LIB[int(slot, 16)] = name
STUB = 0x50000
RET = 0x60000  # return trap
A = [UC_RISCV_REG_A0 + i for i in range(8)]


class Emu:
    def __init__(self):
        u = self.u = Uc(UC_ARCH_RISCV, UC_MODE_RISCV32)
        u.mem_map(0x0, 0x20000)
        u.mem_write(0x1000, IMG)
        u.mem_map(0x40000, 0x1000)
        u.mem_map(STUB, 0x2000)
        u.mem_map(RET, 0x1000)
        u.mem_map(0x20000000, 0x10000)
        u.mem_map(0x40001000, 0x10000)
        u.mem_map(0xE000E000, 0x2000)
        u.mem_write(0x20002000, IMG[0x8:0xC48])
        u.mem_write(0x20002C40, IMG[0x8318:0x8628])
        self.slot_of = {}
        for slot, name in LIB.items():
            stub = STUB + (slot - 0x40000) * 2
            u.mem_write(slot, struct.pack("<I", stub))
            u.mem_write(stub, b"\x82\x80")  # c.jr ra
            self.slot_of[stub] = name
        u.mem_write(RET, b"\x01\x00" * 8)  # c.nop
        self.uart1_tx = bytearray()
        self.notifies = []
        self.lib_calls = []
        self.flash = {}          # DataFlash emulation: offset -> byte
        self.cccd = 1
        self.bm = 0x2000F000
        u.hook_add(UC_HOOK_CODE, self._stub, begin=STUB, end=STUB + 0x2000)
        u.hook_add(UC_HOOK_MEM_WRITE, self._uw, begin=0x40003408, end=0x40003408)
        # flash op dispatcher lives in RAM at 0x200028d6: emulate it
        u.hook_add(UC_HOOK_CODE, self._flashop, begin=0x200028D6, end=0x200028D6)
        u.reg_write(UC_RISCV_REG_GP, 0x200023B8)

    # --- helpers
    def r(self, a, n): return bytes(self.u.mem_read(a, n))
    def w(self, a, b): self.u.mem_write(a, bytes(b))
    def arg(self, i): return self.u.reg_read(A[i])

    def _uw(self, uc, access, addr, size, value, user):
        self.uart1_tx.append(value & 0xFF)

    def _ret(self, v=None):
        u = self.u
        if v is not None:
            u.reg_write(A[0], v & 0xFFFFFFFF)
        u.reg_write(UC_RISCV_REG_PC, u.reg_read(UC_RISCV_REG_RA))

    def _flashop(self, uc, addr, size, user):
        cmd, off, buf, n = (self.arg(i) for i in range(4))
        if cmd == 0x0B:      # EEPROM read
            self.w(buf, bytes(self.flash.get(off + i, 0xFF) for i in range(n)))
        elif cmd == 0x09:    # EEPROM erase
            for i in range(n):
                self.flash[off + i] = 0xFF
        elif cmd == 0x0A:    # EEPROM write
            for i, b in enumerate(self.r(buf, n)):
                self.flash[off + i] = b
        elif cmd == 0x06:    # ROM info (MAC)
            self.w(buf, bytes([0x11, 0x22, 0x33, 0x44, 0x55, 0x66]))
        self.lib_calls.append(("FLASH_EEPROM_CMD", (cmd, off, buf, n)))
        self._ret(0)

    def _stub(self, uc, addr, size, user):
        name = self.slot_of.get(addr)
        if name is None:
            return
        a = [self.arg(i) for i in range(6)]
        self.lib_calls.append((name, a))
        if name == "tmos_memcpy":
            self.w(a[0], self.r(a[1], a[2])); return self._ret(a[0])
        if name == "tmos_memset":
            self.w(a[0], bytes([a[1] & 0xFF]) * a[2]); return self._ret(a[0])
        if name == "tmos_memcmp":   # WCH: TRUE when equal
            return self._ret(1 if self.r(a[0], a[2]) == self.r(a[1], a[2]) else 0)
        if name == "GATT_bm_alloc":
            p = self.bm; self.bm += 0x200; return self._ret(p)
        if name == "GATTServApp_ReadCharCfg":
            return self._ret(self.cccd)
        if name == "GATT_Notification":
            hdl, n, p = struct.unpack("<HHI", self.r(a[1], 8))
            self.notifies.append((hdl, self.r(p, n)))
            return self._ret(0)
        if name == "GAPRole_GetParameter" and a[0] == 0x304:
            self.w(a[1], bytes([0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6])); return self._ret(0)
        return self._ret(0)

    def call(self, fn, *args, sp=0x20007700, limit=5_000_000):
        u = self.u
        for i, v in enumerate(args):
            u.reg_write(A[i], v & 0xFFFFFFFF)
        u.reg_write(UC_RISCV_REG_SP, sp)
        u.reg_write(UC_RISCV_REG_RA, RET)
        u.emu_start(fn, RET, count=limit)
        return u.reg_read(A[0])


def frame(addr, data):
    """Reference encoder: AA addr len data cksum, every AA in the body doubled."""
    body = bytes([addr, len(data)]) + bytes(data)
    body += bytes([sum(body) & 0xFF])
    out = bytearray([0xAA])
    for b in body:
        out.append(b)
        if b == 0xAA:
            out.append(0xAA)
    return bytes(out)
