"""Generate command test vectors by executing the real V51 handlers.

Run: ~/mp305b-fw-re/.venv/bin/python ~/mp305b-fw-re/scripts/commands_vectors.py [group ...]
Prints markdown tables. Every vector runs in a fresh emulator instance
(flash image + RW init, ZI zeroed, peripherals as RAM), through the real
dispatcher 0x12F34 unless the group says "direct".
"""
import os
import sys
import struct

sys.path.insert(0, os.path.expanduser("~/mp305b-fw-re/scripts"))
from commands_emu import HT, S, K, GATE  # noqa: E402
from unicorn.arm_const import UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2  # noqa: E402

TRACE = {
    0x1AF64: "setV", 0x1AEA4: "setI", 0x1AEBC: "outReq", 0x1CB8C: "beep",
    0x1A5FC: "resetCounters", 0x1D6FC: "chargeStart", 0x1D858: "chargeStop",
    0x1D958: "saveCfg", 0x1AE70: "set_aa4e", 0x1DBE8: "factoryDefaults",
    0x1CA60: "rebootReq", 0x1D868: "defaultsInit",
}


class Flash:
    """Model of the 8 MB SPI NOR flash behind 0x1BEF8/0x1BF3A/0x1BDC6/0x1BDF6."""

    def __init__(self):
        self.m = bytearray(b"\xff" * 0x800000)
        self.log = []

    def install(self, h):
        def rd(app):
            a, buf, n = app.reg(UC_ARM_REG_R0), app.reg(UC_ARM_REG_R1), app.reg(UC_ARM_REG_R2)
            app.mu.mem_write(buf, bytes(self.m[a:a + n]))
            self.log.append(("read", a, n))
            return 0

        def wr(app):
            a, buf, n = app.reg(UC_ARM_REG_R0), app.reg(UC_ARM_REG_R1), app.reg(UC_ARM_REG_R2)
            if a + n > 0x800000:
                self.log.append(("write-refused", a, n))
                return 0
            d = app.read(buf, n)
            for i, b in enumerate(d):
                self.m[a + i] &= b
            self.log.append(("write", a, n))
            return 1

        def e64(app):
            a = app.reg(UC_ARM_REG_R0) & ~0xFFFF
            self.m[a:a + 0x10000] = b"\xff" * 0x10000
            self.log.append(("erase64k", a))
            return app.reg(UC_ARM_REG_R0)

        def e4(app):
            a = app.reg(UC_ARM_REG_R0) & ~0xFFF
            self.m[a:a + 0x1000] = b"\xff" * 0x1000
            self.log.append(("erase4k", a))
            return app.reg(UC_ARM_REG_R0)

        h.hook_func(0x1BEF8, rd)
        h.hook_func(0x1BF3A, wr)
        h.hook_func(0x1BDC6, e64)
        h.hook_func(0x1BDF6, e4)


def new(setup=None):
    h = HT()
    for a, n in TRACE.items():
        h.traceon(a, n)
    fl = Flash()
    fl.install(h)
    h.flash = fl
    for k, v in (setup or {}).items():
        if isinstance(k, str):
            # "S+0x30" or "S+0x30:u16"
            off, _, width = k.partition(":")
            base, _, o = off.partition("+")
            addr = {"S": S, "K": K, "GATE": GATE}[base] + int(o, 16)
        else:
            addr, width = k, ""
            if isinstance(k, tuple):
                addr, width = k
        if width == "u16":
            h.w16(addr, v)
        elif width == "u32":
            h.w32(addr, v)
        elif isinstance(v, (bytes, bytearray)):
            h.mu.mem_write(addr, bytes(v))
        else:
            h.w8(addr, v)
    return h


def run(req, typ=6, setup=None, direct=None, shape="rlrt"):
    h = new(setup)
    before = h.snap_all()
    if direct:
        n, rep = h.handler(direct, req, typ=typ, shape=shape)
        out = rep if n else None
    else:
        rec, wire = h.dispatch(req, typ=typ)
        out = rec[4:] if rec else None
    d = h.diff_all(before)
    return h, out, d, list(h.calls)


def fmt_bytes(b):
    return " ".join("%02X" % x for x in b) if b is not None else "none"


def fmt_diff(d, skip=("GATE+0x",)):
    # collapse multi-byte runs into one entry per address
    items = []
    for name, o, n in d:
        if name.startswith("GATE+0x"):
            off = int(name[7:], 16)
            if off < 0x108:
                continue  # tx buffer, pending flag and length: shown as the reply instead
        if name.startswith("K+0x2") or name.startswith("K+0x3") or name == "K+0x0":
            pass
        items.append("%s:%02X>%02X" % (name, o, n))
    return ", ".join(items) if items else "-"


def fmt_calls(c):
    return ", ".join("%s(%d)" % (n, a) if n in ("outReq", "beep", "setV", "setI", "chargeStart", "rebootReq")
                     else n for n, a in c) or "-"


def table(title, rows):
    print("\n#### %s\n" % title)
    print("| # | Setup | Type | Request | Reply | State changes | Calls |")
    print("|---|---|---|---|---|---|---|")
    for i, (setup, typ, req, out, d, calls) in enumerate(rows, 1):
        st = ", ".join("%s=%s" % (k if isinstance(k, str) else hex(k if not isinstance(k, tuple) else k[0]),
                                  (v.hex() if isinstance(v, (bytes, bytearray)) else v))
                       for k, v in (setup or {}).items()) or "reset state"
        print("| %d | %s | %d | `%s` | `%s` | %s | %s |" % (
            i, st, typ, fmt_bytes(req), fmt_bytes(out), fmt_diff(d), fmt_calls(calls)))


def case(rows, req, typ=6, setup=None, **kw):
    h, out, d, calls = run(req, typ, setup, **kw)
    rows.append((setup, typ, req, out, d, calls))
    return h, out


OUT = 0x1FFFAA2E      # output request flag (0x1AEBC writes, 0x1A128 reads)
FAULT = 0x1FFFAA1E    # u16 fault word (0x1A134 reads)
FLAGS = 0x1FFF9550    # tx/event flag word (bit 2 = deferred remote-control reply)


def c8(rc=1, v=1200, i=1000, rt=3, vs=0, co=0, out=0, model=0, refresh=0, suffix=True):
    r = [0xC8, rc, v & 0xFF, v >> 8, i & 0xFF, i >> 8, rt, vs, co, out, model, refresh]
    return r + ([0x31] if suffix else [])


def g_c8():
    rows = []
    G = {"S+0x42": 1, "S+0x45": 1, "S+0x3": 1}
    case(rows, c8(rc=2))
    case(rows, c8(rc=2), setup={"S+0x3": 1})
    case(rows, c8(rc=2, suffix=False), typ=1)
    case(rows, c8(rc=1), setup={"S+0x3": 1})
    case(rows, c8(), setup=G)
    case(rows, c8(v=3050, i=5100), setup=G)
    case(rows, c8(v=3051), setup=G)
    case(rows, c8(v=3050, i=5101), setup=G)
    case(rows, c8(rt=4), setup=G)
    case(rows, c8(vs=2), setup=G)
    case(rows, c8(co=2), setup=G)
    case(rows, c8(out=1), setup=G)
    case(rows, c8(out=1), setup={**G, **{(FAULT, "u16"): 0x20}})
    case(rows, c8(out=1), setup={**G, **{"S+0x4b": 1}})
    case(rows, c8(out=0), setup={**G, **{OUT: 1}})
    case(rows, c8(out=1), setup={**G, **{OUT: 1}})
    case(rows, c8(out=2), setup=G)
    case(rows, c8(refresh=1), setup=G)
    case(rows, c8(refresh=2), setup=G)
    case(rows, c8(model=1, v=0xFFFF, i=0xFFFF), setup=G)
    case(rows, c8(model=1), setup={**G, **{OUT: 1}})
    case(rows, c8(model=4), setup=G)
    case(rows, c8(model=1), setup={**G, **{"S+0x4b": 1}})
    case(rows, c8(), setup={**G, **{"S+0x30": 1}})
    case(rows, c8(), setup={**G, **{"S+0x30": 2}})
    case(rows, c8(), setup={**G, **{"S+0x30": 3}})
    case(rows, c8(rc=0), setup={**G, **{"S+0x30": 2}})
    case(rows, c8(rc=2), setup={"S+0x3": 1, "S+0x30": 3})
    case(rows, c8(rc=3), setup=G)
    case(rows, c8(rc=0), setup=G)
    case(rows, c8(rc=0), setup={"S+0x3": 1})
    case(rows, c8(), setup={"S+0x3": 1, "S+0x45": 2, "S+0x30": 1})
    case(rows, c8(suffix=False), typ=1, setup={"S+0x42": 1, "S+0x45": 1})
    case(rows, [0xC8, 0x31], setup={"S+0x3": 1, "S+0x42": 1, "S+0x45": 1, (FLAGS, "u32"): 4}, direct=0x1B7F4)
    case(rows, [0xC8, 0x31], setup={"S+0x3": 1, "S+0x42": 0, "S+0x45": 0, (FLAGS, "u32"): 4}, direct=0x1B7F4)
    table("0xC8 DC control", rows)



def tx_service(h, elapsed=0):
    """Run the transmit service 0x133BC once; return the frames it sends."""
    sent = []

    def send(app):
        buf, n = app.reg(UC_ARM_REG_R2), app.reg(3 + UC_ARM_REG_R0 - 0) if False else None
        return 0
    from unicorn.arm_const import UC_ARM_REG_R3

    def cap(app):
        buf, n = app.reg(UC_ARM_REG_R2), app.reg(UC_ARM_REG_R3)
        sent.append(app.read(buf, n))
        return 0
    h.hook_func(0x1E24C, cap)
    h.w8(K + 0, 1)          # previous transmission done
    h.w8(0x1FFF9449, 1)     # companion link up
    h.call(0x133BC, elapsed)
    return sent


def unframe(w):
    """Decode one main-UART frame: returns (addr, payload bytes)."""
    body = []
    i = 1
    while i < len(w):
        b = w[i]
        if b == 0xAA:
            i += 1  # doubled
        body.append(b)
        i += 1
    addr, ln = body[0], body[1]
    return addr, bytes(body[2:2 + ln])


def seq(steps, setup=None):
    """Run several steps on one emulator. Steps: (req, typ) | "worker" | "tx"."""
    h = new(setup)
    outs = []
    for st in steps:
        if st == "worker":
            h.call(0x1D380)
            outs.append(("worker", h.flash.log[:]))
            h.flash.log.clear()
        elif st == "tx":
            fr = tx_service(h)
            outs.append(("tx", [unframe(f) for f in fr]))
        else:
            req, typ = st
            rec, wire = h.dispatch(req, typ=typ)
            outs.append(("req", bytes(req), rec[4:] if rec else None))
    return h, outs


def settings(pl=90, vol=3, so=0, sd=30, sdir=1, slope=500, ocp=50, chk=0, rec=0, usb=0, suffix=True):
    r = [0xC6, pl, vol, so, sd, sdir, slope & 0xFF, slope >> 8, ocp & 0xFF, ocp >> 8, chk, rec,
         usb & 0xFF, usb >> 8]
    return r + ([0x31] if suffix else [])


def g_c6():
    rows = []
    case(rows, settings())
    case(rows, settings(pl=80, vol=0, so=0, sd=0, sdir=0, slope=0, ocp=0, chk=0, rec=0, usb=0))
    case(rows, settings(pl=100, vol=3, so=1, sd=30, sdir=1, slope=1000, ocp=1000, chk=1, rec=1, usb=1000))
    case(rows, settings(pl=79))
    case(rows, settings(pl=101))
    case(rows, settings(vol=4))
    case(rows, settings(so=2))
    case(rows, settings(sd=31))
    case(rows, settings(sdir=2))
    case(rows, settings(slope=1001))
    case(rows, settings(ocp=1001))
    case(rows, settings(chk=2))
    case(rows, settings(rec=2))
    case(rows, settings(usb=1001))
    case(rows, settings(pl=81, sd=1, slope=0, ocp=1, usb=150, suffix=False), typ=1)
    table("0xC6 settings write", rows)


def g_reads():
    rows = []
    real = {
        "S+0x2": 1, "S+0xe": 0, "S+0x3a": 90, "S+0xac:u16": 1199, "S+0xa8:u16": 1200,
        "S+0xae:u16": 523, "S+0xaa:u16": 1000, "S+0xd0:u32": 3725, "S+0xd4:u32": 12,
        "S+0xb0:u16": 627, "S+0x12": 0, "S+0x18": 3, "S+0x10": 0, "S+0x5": 1, "S+0x30": 0,
        "S+0x37": 1, "S+0x38": 1, "S+0x39": 27, "S+0x9e:u16": 0, "S+0x11": 0,
        (0x1FFFA980, "u32"): 3725123,
    }
    case(rows, [0xC2, 0x31], setup=real)
    case(rows, [0xC2], typ=1, setup={**real, (0x1FFE02A0, "u32"): 0x20001000, "S+0x11": 0})
    case(rows, [0xC2, 0x31], setup={"S+0x9e:u16": 0x0120, "S+0x2": 2, "S+0x39": 0xFB})
    sett = {"S+0x2d": 90, "S+0x32": 3, "S+0x2e": 0, "S+0x33": 30, "S+0x2f": 1,
            "S+0x96:u16": 500, "S+0x98:u16": 50, "S+0xa4:u16": 0}
    case(rows, [0xC4, 0x31], setup=sett)
    case(rows, [0xC4], typ=1, setup=sett)
    case(rows, [0xE0, 0x31])
    case(rows, [0xE0, 0x00])
    case(rows, [0xE0], typ=1)
    case(rows, [0xE0, 0x31], typ=5)
    case(rows, [0x00, 0x31])
    case(rows, [0x00], typ=1)
    case(rows, [0xA0, 0x31], setup={(0x1FFFA0CE): 1})
    case(rows, [0xA0], typ=1)
    table("Read commands (C2, C4, E0, 00, A0)", rows)


def g_misc():
    rows = []
    case(rows, [0xA2, 0x01, 0x31])
    case(rows, [0xA2, 0x00, 0x31], setup={0x1FFFA0CE: 1})
    case(rows, [0xA2, 0x05, 0x31], setup={0x1FFFA0CE: 1})
    case(rows, [0xA2, 0x01, 0x31], setup={0x1FFFA0CE: 1})
    case(rows, [0xA2, 0x01, 0x31], setup={"S+0x30": 3})
    case(rows, [0x18, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
                0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00])
    for op in (0x01, 0x19, 0xC3, 0xC9, 0xDD, 0xDF, 0xE3, 0xE5, 0xE6, 0xE7, 0xE9, 0xEB, 0xED, 0xEF,
               0xF3, 0xF5, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFF, 0x50, 0x52, 0x55, 0xAA, 0x10, 0x11):
        case(rows, [op, 0x00, 0x31])
    case(rows, [0x51, 0x00], typ=3, setup={GATE + 0x103: 1})
    case(rows, [0x51, 0x01], typ=3, setup={GATE + 0x103: 1})
    case(rows, [0x51, 0x00, 0x31], typ=6, setup={GATE + 0x103: 1})
    case(rows, [0x53, 0x00], typ=3, setup={GATE + 0x104: 1})
    case(rows, [0xF1, 0x00], typ=3, setup={0x1FFFA00E: 1})
    case(rows, [0xF1, 0x00], typ=3)
    case(rows, [0xFD, 0x03], typ=3)
    case(rows, [0xFD, 0xFF], typ=3)
    case(rows, [0xFD, 0x03, 0x31], typ=6)
    case(rows, [0xBD, 0x01, 0x31], typ=6)
    case(rows, [0xBD, 0x00, 0x31], typ=6, setup={"S+0x3": 1})
    case(rows, [0xBD, 0x01, 0x41, 0x42, 0x43], typ=5)
    case(rows, [0xBD, 0x00], typ=5, setup={"S+0x4": 1})
    case(rows, [0xBE, 0x01, 0x31], typ=5)
    case(rows, [0xBE, 0x00, 0x01, 0x31], typ=5, setup={K + 0xE: 1})
    case(rows, [0xBB, 0x01, 1, 2, 3, 4, 5, 6, 3, 0x41, 0x42, 0x43, 0x31], typ=5)
    e1 = [0xE1] + list(range(1, 0x11)) + [0x0A, 0x0B, 0x0C, 0x0D]
    case(rows, e1, typ=3)
    case(rows, e1, typ=3, setup={0x1FFF9434: 1})
    case(rows, e1 + [0x31], typ=6)
    table("Language, bind, ignored opcodes and companion messages", rows)


def e2(rc=1, act=0, out=0, model=1, suffix=True):
    return [0xE2, rc, act, out, model] + ([0x31] if suffix else [])


def g_e2():
    rows = []
    P = {"S+0x30": 1, "S+0x42": 1, "S+0x45": 1, "S+0x3": 1, 0x1FFFA408: 0, 0x1FFFA3F4: 5}
    case(rows, e2(), setup=P)
    for a in (1, 2, 3, 4):
        case(rows, e2(act=a), setup=P)
    case(rows, e2(out=1), setup=P)
    case(rows, e2(out=1), setup={**P, 0x1FFFA3F4: 0})
    case(rows, e2(out=1), setup={**P, (FAULT, "u16"): 1})
    case(rows, e2(out=1), setup={**P, OUT: 1})
    case(rows, e2(out=0), setup={**P, OUT: 1})
    case(rows, e2(out=2), setup=P)
    case(rows, e2(out=1), setup={**P, "S+0x4b": 1})
    case(rows, e2(act=4, out=1), setup=P)
    case(rows, e2(model=0), setup=P)
    case(rows, e2(model=0), setup={**P, OUT: 1})
    case(rows, e2(model=4), setup=P)
    case(rows, e2(rc=1), setup={**P, "S+0x42": 0})
    case(rows, e2(rc=2), setup={"S+0x30": 1, "S+0x3": 1})
    case(rows, e2(rc=2, suffix=False), typ=1, setup={"S+0x30": 1})
    case(rows, e2(rc=0), setup=P)
    case(rows, e2(), setup={**P, "S+0x30": 0})
    case(rows, e2(rc=3), setup=P)
    table("0xE2 program run control", rows)


def e8(rc=1, mask=0, sel=0, out=0, model=2, suffix=True):
    return [0xE8, rc, mask & 0xFF, mask >> 8, sel, out, model] + ([0x31] if suffix else [])


def g_e8():
    rows = []
    P = {"S+0x30": 2, "S+0x42": 1, "S+0x45": 1, "S+0x3": 1}
    case(rows, e8(), setup=P)
    case(rows, e8(mask=0x01FF, sel=1), setup=P)
    case(rows, e8(out=1), setup=P)
    case(rows, e8(out=1, sel=1), setup=P)
    case(rows, e8(out=1), setup={**P, (FAULT, "u16"): 1})
    case(rows, e8(out=1), setup={**P, OUT: 1})
    case(rows, e8(out=0), setup={**P, OUT: 1})
    case(rows, e8(out=2, mask=0x1234, sel=7), setup=P)
    case(rows, e8(out=1), setup={**P, "S+0x4b": 1})
    case(rows, e8(model=0), setup=P)
    case(rows, e8(model=3), setup={**P, OUT: 1})
    case(rows, e8(), setup={**P, "S+0x30": 0})
    case(rows, e8(rc=1), setup={**P, "S+0x42": 0})
    case(rows, e8(rc=2), setup={"S+0x30": 2, "S+0x3": 1})
    table("0xE8 PD control", rows)


def ee(rc=1, typ_=1, v=4200, cells=3, cur=1000, out=0, model=3, suffix=True):
    return [0xEE, rc, typ_, v & 0xFF, v >> 8, cells, cur & 0xFF, cur >> 8, out, model] + ([0x31] if suffix else [])


def g_ee():
    rows = []
    P = {"S+0x30": 3, "S+0x42": 1, "S+0x45": 1, "S+0x3": 1}
    case(rows, ee(), setup=P)
    for t, lo, hi, maxc in ((0, 4250, 4450, 6), (1, 4150, 4250, 6), (2, 4050, 4150, 6), (3, 3600, 3700, 8),
                            (4, 2350, 2450, 12), (5, 3, 13, 255)):
        case(rows, ee(typ_=t, v=lo, cells=min(maxc, 255)), setup=P)
        case(rows, ee(typ_=t, v=hi, cells=0), setup=P)
        case(rows, ee(typ_=t, v=lo - 1), setup=P)
        case(rows, ee(typ_=t, v=hi + 1), setup=P)
        if maxc < 255:
            case(rows, ee(typ_=t, v=lo, cells=maxc + 1), setup=P)
    case(rows, ee(typ_=6), setup=P)
    case(rows, ee(cur=5000), setup=P)
    case(rows, ee(cur=5001), setup=P)
    case(rows, ee(cur=0), setup=P)
    case(rows, ee(out=1), setup=P)
    case(rows, ee(out=1), setup={**P, "S+0x7b": 1})
    case(rows, ee(out=1), setup={**P, "S+0x9e:u16": 4})
    case(rows, ee(out=1), setup={**P, (FAULT, "u16"): 4})
    case(rows, ee(out=0), setup={**P, "S+0x7b": 1})
    case(rows, ee(out=2), setup=P)
    case(rows, ee(out=1), setup={**P, "S+0x4b": 1})
    case(rows, ee(model=0), setup=P)
    case(rows, ee(model=0), setup={**P, OUT: 1})
    case(rows, ee(), setup={**P, "S+0x30": 0})
    case(rows, ee(rc=2), setup={"S+0x30": 3, "S+0x3": 1})
    table("0xEE charge control", rows)



def name16(t):
    b = t.encode()[:16]
    return list(b + b"\0" * (16 - len(b)))


def d6(pid, name, steps, save=1, op=0, suffix=True):
    return [0xD6, pid] + name16(name) + [steps, save, op] + ([0x31] if suffix else [])


def step(v, i, t):
    return list(struct.pack("<III", v, i, t))


def da(pid, recs, suffix=True):
    r = [0xDA, pid]
    for rec in recs:
        r += step(*rec)
    return r + ([0x31] if suffix else [])


def print_seq(title, steps, setup=None, show=("S+0x4B", "XFER")):
    h, outs = seq(steps, setup)
    print("\n#### %s\n" % title)
    print("| Step | Input | Output |")
    print("|---|---|---|")
    for i, o in enumerate(outs, 1):
        if o[0] == "req":
            print("| %d | `%s` | `%s` |" % (i, fmt_bytes(o[1]), fmt_bytes(o[2])))
        elif o[0] == "worker":
            print("| %d | worker 0x1D380 | flash ops: %s |" % (i, ", ".join(
                "%s 0x%X%s" % (x[0], x[1], (" len 0x%X" % x[2]) if len(x) > 2 else "") for x in o[1]) or "none"))
        else:
            print("| %d | tx service 0x133BC | %s |" % (i, "; ".join(
                "addr %02X `%s`" % (a, fmt_bytes(p)) for a, p in o[1]) or "nothing sent"))
    return h


def g_prog():
    S1 = {"S+0x3": 1}
    recs3 = [(5000, 1000, 10), (12000, 2000, 20), (3300, 500, 99990)]
    h = print_seq("Program upload, read back and delete (BLE host, S+3 = 1)", [
        ([0xD4, 0x31], 6),
        (d6(1, "TEST", 3, save=1, op=2), 6),
        ([0xD4, 0x31], 6),
        (da(1, recs3 + [(0, 0, 0)] * 7), 6),
        "worker", "tx",
        ([0xDC, 0x31], 6),
        ([0xD8, 0x01, 0x31], 6), "worker", "tx", "tx",
        ([0xD8, 0x05, 0x31], 6), "worker", "tx",
        (d6(1, "TEST", 3, save=1, op=1), 6), "worker",
        ([0xD4, 0x31], 6),
    ], setup=S1)
    print("\nFlash 0x161000 after sequence:", h.flash.m[0x161000:0x1610C0].hex())
    print("Flash 0x162000:", h.flash.m[0x162000:0x162000 + 48].hex())
    print("S+0x4B =", h.g8(0x4B))

    recs12 = [(1000 + 100 * k, 100 * k, k + 1) for k in range(12)]
    print_seq("Program with 12 steps: two DA chunks", [
        (d6(2, "TWELVE", 12, save=1, op=2), 6),
        (da(2, recs12[:10]), 6),
        (da(2, recs12[10:] + [(0, 0, 0)] * 8), 6),
        "worker", "tx",
        ([0xD8, 0x02, 0x31], 6), "worker", "tx", "tx", "tx",
    ], setup=S1)

    print_seq("DA validation", [
        (d6(3, "V", 1, save=1, op=2), 6),
        (da(3, [(30501, 1000, 1)] + [(0, 0, 0)] * 9), 6),
        (d6(3, "V", 1, save=1, op=2), 6),
        (da(3, [(30500, 5101, 1)] + [(0, 0, 0)] * 9), 6),
        (d6(3, "V", 1, save=1, op=2), 6),
        (da(3, [(30500, 5100, 99991)] + [(0, 0, 0)] * 9), 6),
        (d6(3, "V", 1, save=1, op=2), 6),
        (da(3, [(30500, 0x02000003, 0)] + [(0, 0, 0)] * 9), 6),
        (da(10, [(1, 1, 1)] * 10), 6),
        (da(0, [(1, 1, 1)] * 10), 6),
        (da(4, [(1, 1, 1)] * 10), 6),
    ], setup=S1)

    print_seq("D6 edge cases", [
        (d6(0, "ZERO", 1), 6),
        (d6(11, "ELEVEN", 1), 6),
        (d6(10, "TEN", 0, save=0), 6),
        ([0xD4, 0x31], 6),
        (d6(10, "TEN", 0, save=0, op=1), 6),
        ([0xD4, 0x31], 6),
        (d6(1, "USB", 0, suffix=False), 1),
    ], setup=S1)

    print_seq("Deferred replies go to the host link in S+3 (USB, S+3 = 2)", [
        (d6(1, "U", 1, save=1, op=2, suffix=False), 1),
        (da(1, [(100, 100, 1)] + [(0, 0, 0)] * 9, suffix=False), 1),
        "worker", "tx",
        ([0xD8, 0x01], 1), "worker", "tx",
    ])


def g_pd():
    rows = []
    prof = [0xD2, 1] + name16("PD65") + [65, 3, 1] + [0x2C, 0x91, 0x01, 0x0A] * 3
    case(rows, prof + [0x31], setup={"S+0x3": 1})
    case(rows, [0xD2, 0] + name16("X") + [65, 0, 1] + [0x31], setup={"S+0x3": 1})
    case(rows, [0xD2, 11] + name16("X") + [65, 0, 1] + [0x31], setup={"S+0x3": 1})
    case(rows, [0xD2, 10] + name16("X") + [140, 9, 0] + [0x11, 0x22, 0x33, 0x44] * 9 + [0x31])
    pd = {(0x1FFFA138): bytes(name16("PROFILE1")), 0x1FFFA340: 100, (0x1FFFA1D8, "u32"): 0x0A01912C,
          (0x1FFFA1DC, "u32"): 0x0A02D12D}
    case(rows, [0xD0, 0x01, 0x31], setup=pd)
    case(rows, [0xD0, 0x01, 0x31], setup={**pd, 0x1FFFA340: 101})
    case(rows, [0xD0, 0x01], typ=1, setup=pd)
    case(rows, [0xE4, 0x31], setup={0x1FFFA34A: 2})
    case(rows, [0xE4], typ=1)
    table("PD profile commands (D0, D2, E4)", rows)

    h = print_seq("D2 without save flag leaves S+0x4B = 1", [
        ([0xD2, 1] + name16("A") + [65, 0, 0] + [0x31], 6),
        "worker",
    ], setup={"S+0x3": 1})
    print("S+0x4B after:", h.g8(0x4B))
    h = print_seq("D2 with save flag: worker clears S+0x4B", [
        ([0xD2, 1] + name16("A") + [65, 0, 1] + [0x31], 6),
        "worker",
    ], setup={"S+0x3": 1})
    print("S+0x4B after:", h.g8(0x4B))


def g_charge_reads():
    rows = []
    ch = {"S+0x1ca": 1, "S+0x1c8:u16": 4200, "S+0x1c4": 3, "S+0x1c6:u16": 1000, "S+0x1cc": 1, "S+0x1cd": 3,
          "S+0x1d0:u32": 1234, "S+0x1d4:u32": 15230, "S+0x1d8:u32": 3600}
    case(rows, [0xEA, 0x31], setup=ch)
    case(rows, [0xEA], typ=1, setup=ch)
    ec = {"S+0xe": 1, "S+0x3a": 80, "S+0xb4:u16": 1000, "S+0xd8:u32": 250, "S+0x7a": 1, "S+0x79": 3,
          "S+0xb2:u16": 1180, "S+0xdc:u32": 2950, "S+0xe0:u32": 900, "S+0xb6:u16": 1180, "S+0x78": 0,
          "S+0x5": 1, "S+0x30": 3, "S+0x39": 30, "S+0x1dc:u32": 0x00020001, "S+0x9e:u16": 0x0010}
    case(rows, [0xEC, 0x31], setup=ec)
    de = {"S+0x2": 1, "S+0xe": 0, "S+0x3a": 77, "S+0xac:u16": 500, "S+0xae:u16": 1000, "S+0xc8:u32": 0x00012345,
          "S+0xd0:u32": 3725, "S+0xd4:u32": 12, "S+0xb0:u16": 500, "S+0x7c:u16": 2, "S+0x5": 1, "S+0x30": 1,
          "S+0x39": 28, "S+0x20": 0, "S+0xb8:u32": 4, "S+0x1f": 0, "S+0x9e:u16": 0, (0x1FFFA980, "u32"): 5000}
    case(rows, [0xDE, 0x31], setup=de)
    case(rows, [0xDE, 0x31], setup={**de, "S+0x30": 2, "S+0x7c:u16": 0xFFFF, "S+0xb8:u32": 0xFFFFFFFF})
    pat = {(S + 0x1E0 + i): (0xA0 + i) for i in range(0x12)}
    pat.update({(0x1FFF9B34 + 8 + i): (0x10 + i) for i in range(0x18)})
    pat.update({0x1FFF9B8E: 0x5A, "S+0x1f": 1})
    case(rows, [0xDE], typ=1, setup=pat)
    table("Charge and program/PD telemetry reads (EA, EC, DE)", rows)



def g_maint():
    rows = []
    case(rows, [0xF0, 0xAC, 0x31])
    case(rows, [0xF0, 0xAC], typ=1)
    case(rows, [0xF0, 0x00, 0x31])
    case(rows, [0xFE, 0xAA, 0x55, 0x31])
    case(rows, [0xFE, 0x00, 0x00, 0x31])
    case(rows, [0xFE, 0xAA, 0x55], typ=1)
    case(rows, [0xFC, 0x00, 0x31])
    case(rows, [0xFC, 0xCA, 0x31])
    case(rows, [0xF6, 0x00, 0x31])
    case(rows, [0xF2, 0x01, 0x31])
    table("Maintenance commands, single frames", rows)

    img = bytearray(b"\x00" * 0x100)
    struct.pack_into("<I", img, 0x1C, 0x10040)
    img[0x40:0x44] = b"\xff\xff\xff\xff"
    img[0x44:0x4A] = b"MP305B"
    words = struct.unpack("<64I", bytes(img))
    total = sum(words) & 0xFFFFFFFF
    # the magic is not in the sum: F4 sums what was read back, F6 writes magic afterwards
    f2 = [0xF2, 0x00] + list(struct.pack("<II", 0x10000, 0x100)) + [0x31]
    for ln in (0x100, 0xFFFF, 0x10000, 0x18000, 0x20000):
        hh, oo = seq([([0xF2, 0x00] + list(struct.pack("<II", 0x10000, ln)) + [0x31], 6)])
        er = [x[1] for x in hh.flash.log if x[0] == "erase64k"]
        print("F2 len 0x%X: reply %s, %d erase64k calls, first %s, last %s" % (
            ln, fmt_bytes(oo[0][2]), len(er), [hex(e) for e in er[:3]], hex(er[-1])))
    f4a = [0xF4, 0x00] + list(struct.pack("<I", 0x10000)) + list(img[:0x80]) + [0x31]
    f4b = [0xF4, 0x00] + list(struct.pack("<I", 0x10080)) + list(img[0x80:]) + [0x31]
    f6 = [0xF6, 0x35, 0x00] + list(struct.pack("<III", 0x10000, 0x100, total)) + [0x31]
    f6bad = [0xF6, 0x35, 0x00] + list(struct.pack("<III", 0x10000, 0x100, total ^ 1)) + [0x31]
    blk0 = [0x20, 0x05, 0, 0, 0] + list(struct.pack("<II", 0, 0x80)) + [0] * 16 + list(range(0x80)) + [0x31]
    blk1 = [0x20, 0x05, 0, 0, 0] + list(struct.pack("<II", 0x80, 0x80)) + [0] * 16 + list(range(0x80, 0x100)) + [0x31]
    csum = (sum(range(0x100))) & 0xFFFFFFFF
    fin = [0x20, 0x06, 0, 0, 0] + [0] * 8 + list(struct.pack("<I", csum)) + [0x31]
    finbad = [0x20, 0x06, 0, 0, 0] + [0] * 8 + list(struct.pack("<I", csum + 1)) + [0x31]
    blkbad = [0x20, 0x05, 0, 0, 0] + list(struct.pack("<II", 0x43000, 0x80)) + [0] * 16 + [0] * 0x80 + [0x31]
    blklen = [0x20, 0x05, 0, 0, 0] + list(struct.pack("<II", 0x100, 0x40)) + [0] * 16 + [0] * 0x80 + [0x31]
    h = print_seq("In-application update sequence (flash modelled)", [
        ([0xF0, 0xAC, 0x31], 6), (f2, 6), (f4a, 6), (f4b, 6), (f6bad, 6), (f6, 6),
        (blk0, 6), (blk1, 6), (fin, 6), (finbad, 6), (blkbad, 6), (blklen, 6),
        (fin, 6), (blk0, 6), (blk1, 6), (fin, 6),
        ([0xFC, 0xCA, 0x31], 6), ([0xFC, 0xCA, 0x31], 6),
    ])
    print("\nFlash log (erase runs collapsed):")
    last = None
    cnt = 0
    for x in h.flash.log + [("end", 0)]:
        if last and x[0] == last[0] == "erase64k":
            cnt += 1
            continue
        if last:
            print("   ", last[0], hex(last[1]), (hex(last[2]) if len(last) > 2 else ""), ("x%d" % (cnt + 1)) if cnt else "")
        last, cnt = x, 0
    print("SPI 0x0..0x10:", h.flash.m[0:0x10].hex())
    print("SPI 0x10040..:", h.flash.m[0x10040:0x10050].hex())
    print("SPI 0x1F0000..:", h.flash.m[0x1F0000:0x1F0008].hex())
    print("SPI 0x100000..:", h.flash.m[0x100000:0x100010].hex())
    print("UPD block:", h.read(0x1FFFA00C, 0x10).hex(), "sum", hex(h.r32(0x1FFFA01C)), "A0A0", hex(h.r32(0x1FFFA0A0)))
    print("S+0x3F (update-ready)", h.g8(0x3F), " A00D", h.r8(0x1FFFA00D))
    print("total word sum used:", hex(total))



def tx_only(setup, flags, title):
    h = new(setup)
    h.w32(FLAGS, flags)
    fr = tx_service(h)
    out = [unframe(f) for f in fr]
    print("| %s | 0x%04X | %s | %s |" % (title, flags, ", ".join(
        "%s=%s" % (k if isinstance(k, str) else hex(k), v) for k, v in setup.items()) or "reset",
        "; ".join("addr %02X `%s`" % (a, fmt_bytes(p)) for a, p in out) or "nothing"))


def g_deferred():
    print("\n#### Deferred and unsolicited frames built by the transmit service 0x133BC\n")
    print("| Case | Flag bits (0x1FFF9550) | State | Frames sent |")
    print("|---|---|---|---|")
    tx_only({"S+0x3": 1, "S+0x42": 1, "S+0x45": 1, "S+0x30": 0}, 0x4, "remote grant allowed, DC")
    tx_only({"S+0x3": 1, "S+0x42": 0, "S+0x45": 0, "S+0x30": 0}, 0x4, "remote grant denied, DC")
    tx_only({"S+0x3": 1, "S+0x42": 1, "S+0x45": 1, "S+0x30": 1}, 0x4, "remote grant allowed, Prog")
    tx_only({"S+0x3": 1, "S+0x42": 1, "S+0x45": 1, "S+0x30": 2}, 0x4, "remote grant allowed, PD")
    tx_only({"S+0x3": 1, "S+0x42": 0, "S+0x45": 0, "S+0x30": 3}, 0x4, "remote grant denied, Charge")
    tx_only({"S+0x3": 2, "S+0x42": 1, "S+0x45": 1, "S+0x30": 0}, 0x4, "remote grant, USB link")
    tx_only({"S+0x3": 0, "S+0x42": 1, "S+0x45": 1, "S+0x30": 0}, 0x4, "remote grant, no link")
    tx_only({"S+0x3": 1, "S+0x46": 1, K + 6: 6}, 0x2, "bind allowed, BLE")
    tx_only({"S+0x3": 0, "S+0x46": 0, K + 6: 6}, 0x2, "bind denied, BLE")
    tx_only({"S+0x3": 1, "S+0x2d": 90, "S+0x32": 3}, 0x1000, "settings push")
    tx_only({"S+0x3": 1, 0x1FFFA34A: 1}, 0x400, "active PD profile push")
    tx_only({"S+0x3": 1, "S+0x1ca": 2}, 0x800, "charge settings push")
    tx_only({"S+0x3": 1, 0x1FFFA3FE: 1, 0x1FFFA3F4: 4}, 0x200, "selected program push")
    tx_only({"S+0x3": 1}, 0x100, "program saved")
    tx_only({"S+0x3": 2}, 0x100, "program saved, USB")
    tx_only({"S+0x3": 1}, 0x2000, "ask companion identity")
    tx_only({"S+0x3": 1}, 0x4000, "companion update prepare")
    tx_only({"S+0x3": 1}, 0x8, "bit 3")
    tx_only({"S+0x3": 1}, 0x40, "bit 6")
    tx_only({"S+0x3": 1, K + 8: 1, 0x1FFFAB1C: 1}, 0x1, "bit 0, ab1c=1")
    tx_only({"S+0x3": 1, K + 8: 1, 0x1FFFAB1C: 0}, 0x1, "bit 0, ab1c=0")
    tx_only({"S+0x3": 1, K + 8: 0, 0x1FFFAB1C: 1}, 0x0, "link state change notice")
    tx_only({"S+0x3": 1}, 0x0, "idle heartbeat")

    rows = []
    case(rows, [0x20, 0x07, 0x31])
    case(rows, [0x20, 0x07], typ=1)
    case(rows, [0xD0, 0x00, 0x31])
    case(rows, [0xE0], typ=3)
    table("Further edge cases", rows)


GROUPS = {"c8": g_c8, "c6": g_c6, "reads": g_reads, "misc": g_misc, "e2": g_e2, "e8": g_e8, "ee": g_ee, "prog": g_prog, "pd": g_pd, "chreads": g_charge_reads, "maint": g_maint, "deferred": g_deferred}

if __name__ == "__main__":
    names = sys.argv[1:] or list(GROUPS)
    for n in names:
        GROUPS[n]()
