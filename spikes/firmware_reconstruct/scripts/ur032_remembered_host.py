"""UR-032 check: does the CH58x recognise an allowed host again?

Runs the original CH58x code in Unicorn. Session 1: bind with a host-specific
ID and fast flag 0 (prompt path), main MCU answers 19 00. Session 2: a fresh
emulator that only inherits the DataFlash (as after a disconnect or a CH58x
reboot), then fast binds with the same ID, with another ID, and with the same
ID but flag 0. Also fills five IDs and checks that the oldest is dropped.
"""
import os, struct, sys
sys.path.insert(0, os.path.expanduser("~/mp305b-fw-re/scripts"))
from ch58x_emu import Emu, frame

def hx(b): return bytes(b).hex(' ')
def gatt_write(e, ev, data):
    e.w(0x2000E000, data); e.w(0x2000E100, struct.pack("<BBHI", ev, 0, len(data), 0x2000E000)); e.call(0x72a6, 0x2000E100)
def uart_in(e, raw):
    e.w(0x20004670, raw); e.w(0x20004770, bytes([len(raw)])); e.call(0x4cee)
def loop(e, n=4):
    for _ in range(n): e.call(0x4628); e.call(0x42ac)
def take(e):
    n=[hx(b) for h,b in e.notifies]; u=hx(e.uart1_tx); e.notifies.clear(); e.uart1_tx.clear(); return n,u
def ids(e):
    raw=bytes(e.flash.get(0x6f00+i,0xff) for i in range(80))
    return [raw[i*16:(i+1)*16].hex() for i in range(5)]
def bind(host_id, flag): return bytes([0x18])+host_id+bytes([0,0,flag])

HOST=bytes(range(0xA0,0xB0))   # a host-specific 16-byte ID
OTHER=bytes(range(0x10,0x20))

e=Emu()
gatt_write(e,4,bind(HOST,0)); loop(e); n,u=take(e)
print("S1 bind flag0        notify:",n,"| UART:",u)
uart_in(e, frame(0x26, bytes.fromhex("19 00 00"))); loop(e); n,u=take(e)
print("S1 MCU 19 00         notify:",n,"| UART:",u, "| bind state:",e.r(0x20002ff4,1).hex())
print("S1 stored IDs:",ids(e))
flash=dict(e.flash)

e2=Emu(); e2.flash=dict(flash)   # new session, only DataFlash survives
print("S2 bind state at start:",e2.r(0x20002ff4,1).hex())
gatt_write(e2,4,bind(HOST,1)); loop(e2); n,u=take(e2)
print("S2 fast, same ID     notify:",n,"| UART:",u,"| bind state:",e2.r(0x20002ff4,1).hex())
gatt_write(e2,4,bind(OTHER,1)); loop(e2); n,u=take(e2)
print("S2 fast, other ID    notify:",n,"| UART:",u,"| bind state:",e2.r(0x20002ff4,1).hex())
gatt_write(e2,4,bind(HOST,0)); loop(e2); n,u=take(e2)
print("S2 flag0, same ID    notify:",n,"| UART:",u,"(forwarded = prompt)")
uart_in(e2, frame(0x26, bytes.fromhex("19 ff 00"))); loop(e2); n,u=take(e2)
print("S2 MCU 19 FF         notify:",n,"| stored IDs:",ids(e2))

# capacity: allow six different hosts, expect the first one dropped
e3=Emu()
for k in range(6):
    hid=bytes([k]*16)
    gatt_write(e3,4,bind(hid,0)); loop(e3); take(e3)
    uart_in(e3, frame(0x26, bytes.fromhex("19 00 00"))); loop(e3); take(e3)
print("S3 after six allows, stored IDs:",ids(e3))
e4=Emu(); e4.flash=dict(e3.flash)
gatt_write(e4,4,bind(bytes([0]*16),1)); loop(e4); n,u=take(e4); print("S4 fast, dropped ID  notify:",n)
gatt_write(e4,4,bind(bytes([5]*16),1)); loop(e4); n,u=take(e4); print("S4 fast, newest ID   notify:",n)
