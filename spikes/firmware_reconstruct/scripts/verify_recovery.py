#!/usr/bin/env python3
"""Assert selected recovery findings against original instructions, offline.

Use PYTHONPATH pointing at the repaired workspace scripts. These research
cases do not represent hardware tests or V-model verification. External
hardware, the WCH library and selected UI callees are modeled explicitly.
"""
import hashlib
import json
import os
from pathlib import Path
import sys

# A directly executed script otherwise puts the repository's older helpers
# before PYTHONPATH. Require the repaired directory explicitly.
sys.path.insert(0, os.environ["MP305_RE_SCRIPTS"])

from unicorn import UC_HOOK_MEM_WRITE
from unicorn.arm_const import UC_ARM_REG_LR, UC_ARM_REG_PC, UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_SP
from unicorn.riscv_const import UC_RISCV_REG_GP, UC_RISCV_REG_PC
from emu_app import App
from ch58x_emu import Emu, frame
from ch58x_bridge_checks import gatt_write, uart_in, loop, usb_out, usb_in_all
from hostlink_emu_tests import feed, booted, rx_frame, encode
from commands_vectors import new, c8, e2, e8, ee

RESULTS = []


def check(name, actual, expected):
    ok = actual == expected
    RESULTS.append(dict(case=name, passed=ok, actual=repr(actual), expected=repr(expected)))
    if not ok:
        print(f"FAIL {name}: {actual!r} != {expected!r}")


def inputs():
    root = Path(os.environ["MP305_RE_WORKSPACE"]) / "bin"
    expected = {
        "app.bin": "58bb8c3a1d0d37c1996306598d32591098e9fd38ded275831be9453120cd891f",
        "data.bin": "6ba172918737c3073fa166c876a42819dc7ee9a83c1273549c65a0e13b99fdfd",
        "ch58x.bin": "f0e052057de8cb3ff0b2f7182692b755dc3ef89046d8d2aa3ea33fee8df4865a",
        "pd8051.bin": "6ea3a7640e44c2aedf4cb054c5ee4d185203ce913a32ee1bb6829c0c39a3a10e",
        "ram_rw_init.bin": "e831601923ebee907f50d4d739ce2f0fd32be9045d36f0d0f3b5ea40085546eb",
    }
    for name, sha in expected.items():
        check(f"input-{name}", hashlib.sha256((root/name).read_bytes()).hexdigest(), sha)
    data = (root/"data.bin").read_bytes()
    check("companion-split", ((root/"pd8051.bin").read_bytes() + (root/"ch58x.bin").read_bytes()) == data, True)
    a = App()
    a.mu.mem_write(0x1FFE0000, bytes(0xB5C))
    a.mu.reg_write(UC_ARM_REG_R0, 0x83FC8)
    a.mu.reg_write(UC_ARM_REG_R1, 0x1FFE0000)
    a.mu.reg_write(UC_ARM_REG_R2, 0xB5C)
    a.mu.reg_write(UC_ARM_REG_SP, 0x2003F600)
    a.mu.reg_write(UC_ARM_REG_LR, 0x1F0001)
    a.mu.emu_start(0x11653, 0x1F0000, count=10_000_000)
    check("scatter-return", a.mu.reg_read(UC_ARM_REG_PC), 0x1F0000)
    check("scatter-image", a.read(0x1FFE0000, 0xB5C) == (root/"ram_rw_init.bin").read_bytes(), True)


def startup_and_parser():
    a = App()
    a.hook_func(0x1DAE8, lambda _: 0)  # clock calculation is outside this VTOR check
    a.call(0x1DB74)
    check("SystemInit-VTOR", a.r32(0xE000ED08), 0x10000)
    e = Emu()
    # Deliberately execute exactly the two startup instructions that set GP.
    e.u.emu_start(0x1C48, 0x1C50, count=2)
    check("CH58x-startup-GP", e.u.reg_read(UC_RISCV_REG_GP), 0x20002000)
    check("CH58x-startup-step-end", e.u.reg_read(UC_RISCV_REG_PC), 0x1C50)
    a = App(); base = 0x1FFF9BE4 + 0x214
    feed(a, 1, bytes.fromhex("aa 62"))
    check("decoder-state-offset", a.r8(base+0x208), 2)
    feed(a, 1, bytes.fromhex("02 c2"))
    check("decoder-state-after-one-of-two-bytes", a.r8(base+0x208), 3)
    check("decoder-fill-offset", a.r32(base+0x20C), 1)
    for name, obj, address, kwargs in [("ARM", App(), 0x1DB74, {"count": 1}),
                                        ("RV32", Emu(), 0x35A8, {"limit": 1})]:
        try:
            obj.call(address, **kwargs)
        except RuntimeError as error:
            check(f"{name}-budget-exhaustion-rejected", "exhausted" in str(error), True)
        else:
            check(f"{name}-budget-exhaustion-rejected", False, True)


def telemetry_and_faults():
    for timer, flag, expected in [(0,0,1), (0,1,1), (0x20001000,0,0), (0x20001000,1,1)]:
        h = new(); h.w32(0x1FFE02A0, timer); h.s8(0x11, flag)
        n, reply = h.handler(0x158BC, [0xC2], typ=1)
        check(f"wavePause-{timer:x}-{flag}", (n, reply[32]), (37, expected))
    # Inputs isolate each fault bit. The actual producer works in the power
    # block, and the UI publisher later copies the word to S+0x9E.
    for name, addr, width, values, bit, calls in [
        ("reverse-sensor",0x1FFFA9C8,16,[(500,False),(501,True)],0,1),
        ("battery-cold",0x1FFFAA26,8,[(-19,False),(-20,True)],2,1),
        ("battery-hot",0x1FFFAA26,8,[(57,False),(58,True)],3,1),
        ("system-hot",0x1FFFAA27,8,[(84,False),(85,True)],4,1),
        ("overvoltage",0x1FFFA964,16,[(33000,False),(33001,True)],6,6),
    ]:
        for value, expected in values:
            a = App(); a.w8(0x1FFFAA26,20); a.w8(0x1FFFAA23,50); a.w16(0x1FFFA9D8,500)
            (a.w8 if width==8 else a.w16)(addr, value)
            for _ in range(calls): a.call(0x1978C,100)
            check(f"fault-{name}-{value}", bool(a.r16(0x1FFFAA1E)&(1<<bit)), expected)
    for value, expected in [(4999,False),(5000,True)]:
        a = App(); a.w8(0x1FFFAA26,20); a.w8(0x1FFFAA23,50); a.w16(0x1FFFA9D8,500)
        a.w8(0x1FFFAA40,1); a.w16(0x1FFFA964,12000); a.w16(0x1FFFA9C4,12000-value)
        for _ in range(6):a.call(0x1978C,100)
        check(f"fault-voltage-disagreement-{value}", bool(a.r16(0x1FFFAA1E)&0x100), expected)


def permissions_and_bridge():
    for mode, req, opcode in [(0,c8(rc=1),0xC9),(1,e2(rc=1),0xE3),
                              (2,e8(rc=1),0xE9),(3,ee(rc=1),0xEF)]:
        h = new({"S+0x30":mode,"S+0x3":1,"S+0x42":0,"S+0x45":1})
        rec,_=h.dispatch(req,typ=6)
        check(f"ungranted-mode-{mode}",rec[4:],bytes([opcode,1,0x31]))
    e = Emu(); gatt_write(e,3,bytes.fromhex("12 c4")); loop(e)
    check("unbound-AF01-route",bytes(e.uart1_tx),frame(0x62,bytes.fromhex("c4 31")))
    # The AF01 first byte is discarded, independently of its value.
    e = Emu(); gatt_write(e,3,bytes.fromhex("ff c4")); loop(e)
    check("AF01-prefix-discard",bytes(e.uart1_tx),frame(0x62,bytes.fromhex("c4 31")))
    e = Emu(); e.call(0x55C0)
    first,second=frame(0x12,b"\xc4"),frame(0x12,b"\xc2")
    usb_out(e,first+second);loop(e)
    check("two-USB-frames-overwrite",bytes(e.uart1_tx),second)
    e = Emu(); e.call(0x55C0)
    wire=frame(0x21,b"\xd9"+bytes(range(1,123)));uart_in(e,wire);loop(e)
    reports=usb_in_all(e)
    check("USB-IN-chunk-sizes",[p[1] for p in reports],[62,62,3])
    check("USB-IN-reassembly",b"".join(p[2:2+p[1]] for p in reports),wire)
    # Accessory input reaches the output-key worker from source 6 without a
    # remote grant. Replace the output actuator with an argument recorder.
    a=booted(); actuations=[]
    a.hook_func(0x1AEBC,lambda x: actuations.append(x.reg(UC_ARM_REG_R0)) or 0)
    for fn in (0x1A128,0x1A134,0x186F0,0x1CB8C):a.hook_func(fn,lambda _:0)
    for ad,v in [(0x1FFFAAE5,7),(0x1FFFAAFC,0),(0x1FFFAB0E,0),(0x1FFFAB17,0),(0x1FFFAAD3,0),
                 (0x1FFE0191,0),(0x1FFE0192,0),(0x1FFE0193,0)]:a.w8(ad,v)
    for key in (1,0):
        rx_frame(a,encode(6,2,bytes([0xBE,key,0,0,0,0,0,0,0,0x31])));a.call(0x12F34,1)
    check("host-accessory-output-event",a.r8(0x1FFFAAE9),1)
    a.call(0x18728,10)
    check("host-accessory-output-request",actuations,[1])


def reset_path():
    a=App();writes=[]
    for fn in (0x144BC,0x1C350,0x144A8,0x1F23C,0x15384):a.hook_func(fn,lambda _:0)
    def on_write(mu, access, addr, size, value, user):
        if addr in (0x2005F000,0xE000ED0C):writes.append((addr,value))
        if addr==0xE000ED0C:mu.emu_stop()  # emulate reset boundary, never expect a return
    a.mu.hook_add(UC_HOOK_MEM_WRITE,on_write)
    a.mu.reg_write(UC_ARM_REG_SP,0x2003F000)
    a.mu.emu_start(0x1B71D,0x1FFF00,count=10000)
    check("reset-mailbox-and-AIRCR",writes,[(0x2005F000,0x1234),(0xE000ED0C,0x05FA0004)])


if __name__=="__main__":
    inputs();startup_and_parser();telemetry_and_faults();permissions_and_bridge();reset_path()
    summary=dict(cases=len(RESULTS),passed=sum(r["passed"] for r in RESULTS),results=RESULTS)
    Path(sys.argv[1]).write_text(json.dumps(summary,indent=2)+"\n")
    print(f"Recovery assertions: {summary['passed']}/{summary['cases']} passed")
    sys.exit(0 if summary['passed']==summary['cases'] else 1)
