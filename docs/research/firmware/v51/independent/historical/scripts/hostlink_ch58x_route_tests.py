"""CH58x-side emulation used by notes/hostlink.md (original RV32 instructions, synthetic RAM).

1. MCU->CH58x commands handled at 0x388A and the replies the CH58x frames back.
2. USB OUT report -> frame forwarded verbatim on the UART to the MCU.
3. MCU frame -> USB IN reports (report ID 2, count, <=62 bytes) or GATT AF01/AF02.
"""
import sys
sys.path.insert(0, '/Users/jihlenburg/mp305b-fw-re/scripts')
from hostlink_emu_ch58x import CH
from hostlink_emu_tests import encode

CB = 0x7F000

def cmds():
    c = CH(); out = []
    c.mu.mem_write(CB, b'\x82\x80')
    c.hooks[CB] = lambda ch: out.append(ch.read(ch.a(0), ch.a(1)))
    c.hooks[0x200028D6] = lambda ch: 0      # DataFlash access stub
    c.hooks[0x7532] = lambda ch: 0
    for op, pl in ((0xE0, b''), (0x00, b''), (0x10, b''), (0x50, b'\x00'), (0x50, b'\x01'), (0x50, b'\x02'),
                   (0x52, b'S'), (0x52, b' '), (0xF0, b'\xac'), (0xEF, b'*'), (0xFC, b'*MP305B  \x01\x35\x02\x00'), (0x55, b'')):
        body = bytes([op]) + pl
        c.mu.mem_write(0x2000419C, bytes([2, 3]) + len(body).to_bytes(2, 'little') + body)
        c.w32(0x20002FBC, 0x11223344)
        out.clear(); c.log.clear()
        c.call(0x388A, CB)
        libs = [l[1] + '(' + ','.join(l[2:5]) + ')' for l in c.log if l[1] not in ('0x4004c', '0x40048', '0x4003c')]
        print('MCU->CH58x %-40s reply %-50s f89=%d f8a=%d lib=%s' % (body.hex(' '), ' | '.join(o.hex(' ') for o in out),
              c.r8(0x20002F89), c.r8(0x20002F8A), libs))

def usb_out(frame, label):
    c = CH(); uart = []
    c.hooks[0x2914] = lambda ch: uart.append(ch.read(ch.a(0), ch.a(1)))
    c.hooks[0x4DD8] = lambda ch: uart.append(ch.read(ch.a(0), ch.a(1)))
    buf = 0x2000A000; c.w32(0x20002F54, buf)
    pkt = bytes([1, len(frame)]) + frame
    c.mu.mem_write(buf, pkt + bytes(64 - len(pkt)))
    c.w8(0x20003A49, 1)
    c.call(0x4E86)
    for _ in range(3):
        c.call(0x4628)
    print('USB OUT %-16s %-24s -> UART %s' % (label, frame.hex(' '), [u.hex(' ') for u in uart]))

def mcu_frame(body, dst, label):
    c = CH(); usb = []; gatt = []
    c.hooks[0x2A5E] = lambda ch: None
    buf = 0x2000A000; c.w32(0x20002F54, buf); c.w8(0x20003A49, 1)
    c.hooks[0x6F6C] = lambda ch: gatt.append(('AF02', ch.read(ch.a(0), ch.a(1))))
    c.hooks[0x6FF6] = lambda ch: gatt.append(('AF01', ch.read(ch.a(0), ch.a(1))))
    w = encode(2, dst, body)
    c.mu.mem_write(0x20004670, w); c.w8(0x20004770, len(w))
    c.call(0x4CEE)
    for _ in range(8):
        c.call(0x4628)
        if c.r8(0x20003A4A):
            c.w8(0x20003A49, 1); c.call(0x3E1A)
            usb.append(c.read(buf + 0x40, 64))
    print('MCU->%s wire %s' % (label, w.hex(' ')))
    for u in usb: print('    USB IN report: ' + u[:u[1] + 2].hex(' '))
    for g in gatt: print('    GATT %s notify: %s' % (g[0], g[1].hex(' ')))

if __name__ == '__main__':
    cmds()
    usb_out(encode(1, 2, b'\xc2'), 'addr 0x12')
    usb_out(encode(6, 2, b'\xc2\x31'), 'addr 0x62')
    usb_out(encode(3, 2, b'\xfd\x03'), 'addr 0x32')
    usb_out(encode(5, 2, b'\xbe\x01'), 'addr 0x52')
    mcu_frame(b'\xc5' + bytes(11), 1, 'USB (0x21)')
    mcu_frame(bytes([0xD9]) + bytes(range(1, 123)), 1, 'USB 123-byte body')
    mcu_frame(b'\xc5' + bytes(11) + b'\x31', 6, 'BLE suffix 31')
    mcu_frame(b'\x19\x00\x00', 6, 'BLE suffix 00')
