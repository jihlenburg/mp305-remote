#!/usr/bin/env python3
"""Offline checks of the CH58x bridge (see notes/ch58x.md). Runs original code in Unicorn via ch58x_emu."""
import sys, os, struct
sys.path.insert(0, os.path.expanduser("~/mp305b-fw-re/scripts"))
from ch58x_emu import Emu, frame
import ch58x_emu


def hx(b): return bytes(b).hex(' ')
def gatt_write(e, ev, data):
    e.w(0x2000E000, data); e.w(0x2000E100, struct.pack("<BBHI", ev, 0, len(data), 0x2000E000)); e.call(0x72a6, 0x2000E100)
def uart_in(e, raw):
    e.w(0x20004670, raw); e.w(0x20004770, bytes([len(raw)])); e.call(0x4cee)
def loop(e, n=4):
    for _ in range(n): e.call(0x4628); e.call(0x42ac)
def show(tag, e):
    print(tag, "notify:", [hx(b) for h, b in e.notifies], "| UART:", hx(e.uart1_tx)); e.notifies.clear(); e.uart1_tx.clear()
def usb_out(e, chunk):
    ep1 = struct.unpack("<I", e.r(0x20002f54, 4))[0]
    e.w(ep1, bytes([1, len(chunk)]) + chunk + bytes(62 - len(chunk))); e.call(0x4e86)
def usb_in_all(e):
    out = []; ep1 = struct.unpack("<I", e.r(0x20002f54, 4))[0]
    for _ in range(20):
        if e.r(0x20003a4a, 1)[0] == 0: break
        e.w(0x20003a49, b"\x01"); e.call(0x3e1a); out.append(e.r(ep1 + 0x40, 64))
    return out

# ==== check t1
def check_t1():
    import sys, os, struct; sys.path.insert(0, os.path.expanduser("~/mp305b-fw-re/scripts"))
    from ch58x_emu import Emu, frame
    def hx(b): return bytes(b).hex(' ')
    def gatt_write(e, ev, data):
        e.w(0x2000E000, data)
        e.w(0x2000E100, struct.pack("<BBHI", ev, 0, len(data), 0x2000E000))
        e.call(0x72a6, 0x2000E100)
    def loop(e, n=3):
        for _ in range(n): e.call(0x4628)
    e = Emu()
    # 1. AF01 write "12 c4"
    gatt_write(e, 3, bytes([0x12, 0xc4])); loop(e)
    print("AF01 12 c4 -> UART:", hx(e.uart1_tx)); e.uart1_tx.clear()
    # 2. AF02 write "e0"
    gatt_write(e, 4, bytes([0xe0])); loop(e)
    print("AF02 e0 -> UART:", hx(e.uart1_tx)); e.uart1_tx.clear()
    # 3. AF02 bind (WebLink frame)
    bind = bytes.fromhex("18 00 08 08 08 08 08 08 08 08 08 08 08 08 08 08 00 00 00")
    gatt_write(e, 4, bind); loop(e)
    print("AF02 bind -> UART:", hx(e.uart1_tx)); e.uart1_tx.clear()
    print("pending host id @0x20005130:", hx(e.r(0x20005130, 16)))
    # 4. AF02 opcode 00
    gatt_write(e, 4, bytes([0x00])); loop(e)
    print("AF02 00 -> notify:", [(h, hx(b)) for h, b in e.notifies], "UART:", hx(e.uart1_tx)); e.notifies.clear(); e.uart1_tx.clear()
    # 5. AF01 0x10 + 14 bytes
    gatt_write(e, 3, bytes([0x12, 0x10]) + bytes(range(1, 15))); loop(e)
    print("AF01 10 -> notify:", [(h, hx(b)) for h, b in e.notifies], "UART:", hx(e.uart1_tx)); e.notifies.clear(); e.uart1_tx.clear()
    print("adv data:", hx(e.r(0x20002e78, 31)))
    print("flash 0x6e00:", hx(bytes(e.flash.get(0x6e00+i, 0xff) for i in range(22))))

# ==== check t2
def check_t2():
    import sys, os, struct; sys.path.insert(0, os.path.expanduser("~/mp305b-fw-re/scripts"))
    from ch58x_emu import Emu, frame
    def hx(b): return bytes(b).hex(' ')
    def gatt_write(e, ev, data):
        e.w(0x2000E000, data); e.w(0x2000E100, struct.pack("<BBHI", ev, 0, len(data), 0x2000E000)); e.call(0x72a6, 0x2000E100)
    def uart_in(e, raw):
        e.w(0x20004670, raw); e.w(0x20004770, bytes([len(raw)])); e.call(0x4cee)
    def loop(e, n=4):
        for _ in range(n): e.call(0x4628); e.call(0x42ac)
    def show(tag, e):
        print(tag, "notify:", [hx(b) for h, b in e.notifies], "| UART:", hx(e.uart1_tx)); e.notifies.clear(); e.uart1_tx.clear()
    e = Emu()
    uart_in(e, frame(0x26, bytes.fromhex("c5 5a 02 00 00 01 f4 01 32 00 00 00 31"))); loop(e); show("MCU->AF01 c5:", e)
    uart_in(e, frame(0x26, bytes.fromhex("e1 01 06 00 28 4d 50 33 30 35 42 00 00 02 00 02 00 00"))); loop(e); show("MCU->AF02 e1:", e)
    # bind flow: host sends bind on AF02, MCU answers 19 00 00
    gatt_write(e, 4, bytes.fromhex("18 00 08 08 08 08 08 08 08 08 08 08 08 08 08 08 00 00 00")); loop(e); e.uart1_tx.clear()
    uart_in(e, frame(0x26, bytes.fromhex("19 00 00"))); loop(e); show("MCU->AF02 19 00:", e)
    print("bind state ff4 =", e.r(0x20002ff4,1).hex(), " flash 6f00:", hx(bytes(e.flash.get(0x6f00+i,0xff) for i in range(32))))
    # fast bind lookup with last byte 1
    gatt_write(e, 4, bytes.fromhex("18 00 08 08 08 08 08 08 08 08 08 08 08 08 08 08 00 00 01")); loop(e); show("fast bind known:", e)
    gatt_write(e, 4, bytes.fromhex("18 11 08 08 08 08 08 08 08 08 08 08 08 08 08 08 00 00 01")); loop(e); show("fast bind unknown:", e)
    # notify failure -> 55 status
    e.cccd = 0
    uart_in(e, frame(0x26, bytes.fromhex("c3 00 31"))); loop(e); show("MCU->AF01 with CCCD off:", e)
    e.cccd = 1
    # control frames to CH58x (dst 3)
    for d in ("e0", "10", "52 53", "52 20", "50 02", "50 00", "50 01", "f0 ac", "ef 2a", "fc 2a 4d 50 33 30 35 42 20 20 01 35 02 00", "00", "55", "c2"):
        uart_in(e, frame(0x23, bytes.fromhex(d))); loop(e); show(f"MCU->CH58x {d}:", e)
    print("adv:", hx(e.r(0x20002e78, 31)))
    print("scanrsp:", hx(e.r(0x20002e98, 31)))
    print("flash 6e00:", hx(bytes(e.flash.get(0x6e00+i,0xff) for i in range(22))))
    print("usb product string:", hx(e.r(0x20002e44, 18)))
    print("2f89/2f8a/3a48:", e.r(0x20002f89,2).hex(), e.r(0x20003a48,1).hex())
    print([c for c in e.lib_calls if c[0].startswith("GAPRole_SetParameter")][-6:])

# ==== check t3
def check_t3():
    import sys, os, struct; sys.path.insert(0, os.path.expanduser("~/mp305b-fw-re/scripts"))
    from ch58x_emu import Emu, frame
    def hx(b): return bytes(b).hex(' ')
    def gatt_write(e, ev, data):
        e.w(0x2000E000, data); e.w(0x2000E100, struct.pack("<BBHI", ev, 0, len(data), 0x2000E000)); e.call(0x72a6, 0x2000E100)
    def uart_in(e, raw):
        e.w(0x20004670, raw); e.w(0x20004770, bytes([len(raw)])); e.call(0x4cee)
    def loop(e, n=4):
        for _ in range(n): e.call(0x4628); e.call(0x42ac)
    e = Emu()
    uart_in(e, frame(0x23, bytes.fromhex("fc 2a 4d 50 33 30 35 42 20 20 01 35 02 00"))); loop(e); e.uart1_tx.clear()
    print("after FC  flash 6e00:", hx(bytes(e.flash.get(0x6e00+i,0xff) for i in range(22))))
    gatt_write(e, 3, bytes([0x12, 0xc0]) + bytes(range(0x41, 0x4f))); loop(e)
    print("after C0  flash 6e00:", hx(bytes(e.flash.get(0x6e00+i,0xff) for i in range(22))))
    uart_in(e, frame(0x23, bytes.fromhex("fc 2a 4d 50 33 30 35 42 20 20 01 35 02 00"))); loop(e); e.uart1_tx.clear()
    print("after FC2 flash 6e00:", hx(bytes(e.flash.get(0x6e00+i,0xff) for i in range(22))))
    print("adv:", hx(e.r(0x20002e78, 31)))
    # periodic event 2 name patch
    e.w(0x20002f8a, b"\x01"); e.w(0x20002f89, b"\x00")
    e.call(0x6cb0, 0, 2)
    print("scanrsp after ev2:", hx(e.r(0x20002e98, 31)), repr(e.r(0x20002e9a, 29)))
    e.w(0x200043b7, b"\xa5"); e.call(0x6cb0, 0, 2); print("with 43b7=A5:", repr(e.r(0x20002e9a, 29)))
    e.w(0x200043b7, b"\x00"); e.w(0x20002f89, b"\x02"); e.call(0x6cb0, 0, 2); print("with 2f89=2:", repr(e.r(0x20002e9a, 29)))
    # state STARTED -> suffix from BD addr a1..a6
    e.w(0x2000E200, bytes(24)); e.call(0x7106, 1, 0x2000E200)
    print("after STARTED:", repr(e.r(0x20002e9a, 29)))
    b = [0xA1,0xA2,0xA3,0xA4,0xA5,0xA6]; v = ((b[0]^b[1])<<24)|((b[2]^b[3])<<16)|(b[4]<<8)|b[5]
    print("predicted suffix:", ''.join(chr(0x21 + (v//d) % 94) for d in (1, 94, 8836)))

# ==== check t4
def check_t4():
    import sys, os, struct; sys.path.insert(0, os.path.expanduser("~/mp305b-fw-re/scripts"))
    from ch58x_emu import Emu, frame
    def hx(b): return bytes(b).hex(' ')
    def uart_in(e, raw):
        e.w(0x20004670, raw); e.w(0x20004770, bytes([len(raw)])); e.call(0x4cee)
    def loop(e, n=4):
        for _ in range(n): e.call(0x4628); e.call(0x42ac)
    def usb_out(e, chunk):
        ep1 = struct.unpack("<I", e.r(0x20002f54, 4))[0]
        e.w(ep1, bytes([1, len(chunk)]) + chunk + bytes(62 - len(chunk)))
        e.call(0x4e86)
    def usb_in_all(e):
        out = []
        ep1 = struct.unpack("<I", e.r(0x20002f54, 4))[0]
        for _ in range(20):
            if e.r(0x20003a4a, 1)[0] == 0: break
            e.w(0x20003a49, b"\x01"); e.call(0x3e1a)
            out.append(e.r(ep1 + 0x40, 64))
        return out
    e = Emu()
    e.call(0x55c0)   # USB enable (as done by MCU 52 'S')
    print("EP pointers:", [hex(struct.unpack('<I', e.r(0x20002f50 + 4*i, 4))[0]) for i in range(4)])
    f = frame(0x12, bytes([0xc4])); print("host frame:", hx(f))
    usb_out(e, f); loop(e); print("USB OUT c4 -> UART:", hx(e.uart1_tx)); e.uart1_tx.clear()
    # frame with AA inside, split over two reports with arbitrary split
    f = frame(0x12, bytes([0xc6, 0xaa, 1, 2, 0xaa, 0xaa] + list(range(60))))
    usb_out(e, f[:30]); loop(e); print("partial -> UART:", hx(e.uart1_tx), " IN queue count:", e.r(0x20003a4a,1).hex())
    usb_out(e, f[30:]); loop(e); print("rest -> UART == frame:", bytes(e.uart1_tx) == f, len(f)); e.uart1_tx.clear()
    # bad checksum dropped
    g = bytearray(frame(0x12, bytes([0xc2]))); g[-1] ^= 1
    usb_out(e, bytes(g)); loop(e); print("bad cksum -> UART:", hx(e.uart1_tx)); e.uart1_tx.clear()
    # address byte preserved (host uses 0x62)
    usb_out(e, frame(0x62, bytes([0xc2]))); loop(e); print("host addr 0x62 -> UART:", hx(e.uart1_tx)); e.uart1_tx.clear()
    # partial frame with opcode 0x20 -> local ack
    f = frame(0x12, bytes([0x20, 5] + [0]*100))
    usb_out(e, f[:40]); loop(e); print("partial 0x20 -> IN reports:", [hx(r[:12]) for r in usb_in_all(e)], "UART:", hx(e.uart1_tx)); e.uart1_tx.clear()
    e.call(0x3876, 1)  # reset decoder
    f = frame(0x12, bytes([0xf4, 0, 1, 2, 3, 4] + [0]*80))
    usb_out(e, f[:40]); loop(e); print("partial 0xF4 -> IN reports:", [hx(r[:12]) for r in usb_in_all(e)])
    e.call(0x3876, 1)
    # MCU -> USB, long frame
    data = bytes([0xd5] + [0xaa if i % 7 == 0 else i for i in range(1, 100)])
    mf = frame(0x21, data); print("MCU frame len", len(mf))
    uart_in(e, mf); loop(e); e.uart1_tx.clear()
    reps = usb_in_all(e)
    for r in reps: print(" IN:", hx(r[:4]), "... n=%d" % r[1])
    stream = b''.join(r[2:2 + r[1]] for r in reps)
    print("reassembled == MCU frame:", stream == mf)
    # queue capacity
    for k in range(6):
        uart_in(e, frame(0x21, bytes([0xc3, k]))); loop(e, 1)
    print("queue count after 6 frames w/o IN:", e.r(0x20003a4a,1).hex(), "last 55 frames:", hx(e.uart1_tx[-14:]))
    print("---- partial ack check")
    e = Emu(); e.call(0x55c0)
    ep1 = struct.unpack("<I", e.r(0x20002f54, 4))[0]
    for op, body in ((0x20, [5] + [0]*100), (0xf4, [0, 1, 2, 3, 4] + [0]*80), (0xc6, [0]*80)):
        e.call(0x3876, 1); e.w(0x20003a49, b"\x01"); e.w(ep1 + 0x40, bytes(64))
        f = frame(0x12, bytes([op] + body))
        usb_out(e, f[:40]); loop(e, 1)
        print("partial op %02x -> EP1 IN:" % op, hx(e.r(ep1 + 0x40, 16)), "UART:", hx(e.uart1_tx)); e.uart1_tx.clear()

# ==== check t5
def check_t5():
    import sys, os, struct; sys.path.insert(0, os.path.expanduser("~/mp305b-fw-re/scripts"))
    e = Emu(); e.call(0x55c0)
    f1 = frame(0x12, bytes([0xc4])); f2 = frame(0x12, bytes([0xc2]))
    usb_out(e, f1 + f2); loop(e); print("two frames in one report -> UART:", hx(e.uart1_tx)); e.uart1_tx.clear()
    f3 = frame(0x12, bytes([0xc8] + list(range(1, 12))))
    usb_out(e, f1 + f3[:6]); loop(e); print("frame + start of next -> UART:", hx(e.uart1_tx)); e.uart1_tx.clear()
    usb_out(e, f3[6:]); loop(e); print("   rest -> UART:", hx(e.uart1_tx)); e.uart1_tx.clear()
    # count byte bigger than 62
    ep1 = struct.unpack("<I", e.r(0x20002f54, 4))[0]
    print("n field used as-is: reads ep1+2 .. ep1+2+n")

# ==== check t6
def check_t6():
    import sys, os, struct; sys.path.insert(0, os.path.expanduser("~/mp305b-fw-re/scripts"))
    e = Emu()
    e.w(0x20004c08, b"\x02")
    e.w(0x20004be5, bytes([1,2,3,4,5,6, 7,8,9,10,11,12]))
    e.w(0x20004c03, bytes([4, 3]))
    e.w(0x20004b4a, b"KNOB"); e.w(0x20004b4a + 0x1f, b"ABC")
    uart_in(e, frame(0x25, bytes([0xba]))); loop(e); print("BA ->", hx(e.uart1_tx)); e.uart1_tx.clear()
    uart_in(e, frame(0x25, bytes([0xbc, 0x11,0x22,0x33,0x44,0x55,0x66]))); loop(e); print("BC -> addr", hx(e.r(0x20002f30, 6)), "UART", hx(e.uart1_tx)); e.uart1_tx.clear()
    uart_in(e, frame(0x25, bytes([0xb8, 0xb0]))); loop(e); print("B8 B0 -> 4c09 =", e.r(0x20004c09,1).hex(), "UART", hx(e.uart1_tx)); e.uart1_tx.clear()
    uart_in(e, frame(0x25, bytes([0xbe]))); loop(e); print("BE -> addr", hx(e.r(0x20002f30, 6)), [c for c in e.lib_calls if 'Terminate' in c[0]][-1:], "UART", hx(e.uart1_tx)); e.uart1_tx.clear()
    # accessory link state -> BD on channel 5
    e.w(0x20002f30, bytes([7,8,9,10,11,12])); e.w(0x20002fdb, b"\x02"); e.w(0x20002fc8, b"\x01"); e.w(0x20002fcf, b"\x01")
    e.w(0x20004c08, b"\x02"); e.w(0x20004be5, bytes([1,2,3,4,5,6, 7,8,9,10,11,12])); e.w(0x20004c03, bytes([4, 3])); e.w(0x20004b4a, b"KNOB"); e.w(0x20004b4a + 0x1f, b"ABC")
    loop(e); print("accessory connected -> UART", hx(e.uart1_tx)); e.uart1_tx.clear()
    e.w(0x20002fdb, b"\x00"); loop(e); print("accessory lost -> UART", hx(e.uart1_tx)); e.uart1_tx.clear()

# ==== check t7
def check_t7():
    import sys, os, struct; sys.path.insert(0, os.path.expanduser("~/mp305b-fw-re/scripts"))
    from ch58x_emu import Emu
    from unicorn import UC_HOOK_MEM_WRITE, UC_HOOK_CODE
    e = Emu()
    w0 = []
    e.u.hook_add(UC_HOOK_MEM_WRITE, lambda uc,a,ad,s,v,u: w0.append((hex(ad), v)), begin=0x40003000, end=0x400030ff)
    stubs = []
    for s in (0x8d0e,0x8d1e,0x8d2e,0x8d3e,0x8d4e,0x8d8e):
        e.u.hook_add(UC_HOOK_CODE, lambda uc,a,sz,u: stubs.append(hex(a)), begin=s, end=s)
    e.call(0x7968, 0x8ec0, 1, 2, 3)   # printf("GRB:(%d,%d,%d)")
    e.call(0x79ac, 10)                # putchar('\n')
    print("UART0 writes:", w0[:10], " stub hits:", stubs[:10])

# ==== check t8
def check_t8():
    import sys, os, struct; sys.path.insert(0, os.path.expanduser("~/mp305b-fw-re/scripts"))
    import ch58x_emu
    e = Emu()
    msg = [0]
    orig = e._stub
    def stub(uc, addr, size, user):
        if e.slot_of.get(addr) == "tmos_msg_receive":
            e.lib_calls.append(("tmos_msg_receive", [])); return e._ret(msg[0])
        return orig(uc, addr, size, user)
    e._stub = stub
    from unicorn import UC_HOOK_CODE
    e.u.hook_add(UC_HOOK_CODE, stub, begin=ch58x_emu.STUB, end=ch58x_emu.STUB + 0x2000)
    e.w(0x20002fdb, b"\x02"); e.w(0x20004c16, struct.pack("<H", 0x10)); e.w(0x20004c2a, struct.pack("<H", 0x30)); e.w(0x20004c0c, struct.pack("<H", 0x100))
    for rep in ("01 00 00 ff 00", "01 00 00 00 00", "00 00 00 01 00", "03 00 00 01"):
        d = bytes.fromhex(rep); e.w(0x2000D100, d)
        e.w(0x2000D000, struct.pack("<BBHBBBBHHI", 0xB0, 0, 0, 0x1b, 0, 0, 0, 0x20, len(d), 0x2000D100))
        msg[0] = 0x2000D000
        e.call(0x5af0, 0, 0x8000); msg[0] = 0
        loop(e); print("HID report", rep, "-> UART:", hx(e.uart1_tx)); e.uart1_tx.clear()

if __name__ == "__main__":
    print('==== t1'); check_t1()
    print('==== t2'); check_t2()
    print('==== t3'); check_t3()
    print('==== t4'); check_t4()
    print('==== t5'); check_t5()
    print('==== t6'); check_t6()
    print('==== t7'); check_t7()
    print('==== t8'); check_t8()
