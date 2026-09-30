"""Hostlink emulation checks on app.bin (original instructions, synthetic RAM).

Run: ~/mp305b-fw-re/.venv/bin/python ~/mp305b-fw-re/scripts/hostlink_emu_tests.py
"""
import sys, os
sys.path.insert(0, os.path.expanduser('~/mp305b-fw-re/scripts'))
from emu_app import App

DEC = 0x146B8        # decoder byte step (channel, byte) -> record ptr or 0
ENC = 0x15430        # encoder (channel, slot, out) -> length
RXCB = 0x1EF5C       # USART3 RX callback
DISP = 0x12F34       # dispatcher (elapsed)
TXSVC = 0x133BC      # transmit service (elapsed)
USART3 = 0x4001D400

def feed(a, ch, data):
    res = []
    for b in data:
        r = a.call(DEC, ch, b)
        res.append(r)
    return res

def encode(src, dst, body):
    """Reference model of the wire format (what the firmware emits)."""
    addr = ((src & 15) << 4) | (dst & 15)
    raw = [addr, len(body)] + list(body)
    ck = sum(raw) & 0xFF
    out = [0xAA]
    for x in raw + [ck]:
        out.append(x)
        if x == 0xAA:
            out.append(0xAA)
    return bytes(out)

def fw_encode(a, src, dst, body):
    a.heap = 0x30000000
    slot = a.alloc(bytes([src, dst, len(body), 0]) + bytes(body) + bytes(8))
    out = a.alloc(600)
    n = a.call(ENC, 1, slot, out)
    return a.read(out, n)

def test_encoder():
    a = App()
    import random
    rnd = random.Random(1)
    cases = [(2, 1, bytes([0xC3, 0xAA, 0x00])), (2, 6, bytes([0xAA] * 5)), (2, 3, b'\x55'),
             (0xA, 0xA, b'\x10'), (2, 1, bytes([0xAA - 2 - 3 + 256 & 0xFF, 1, 2]))]
    for _ in range(300):
        n = rnd.randint(1, 255)
        cases.append((rnd.randint(0, 15), rnd.randint(0, 15), bytes(rnd.randint(0, 255) for _ in range(n))))
    bad = 0
    for s, d, body in cases:
        if fw_encode(a, s, d, body) != encode(s, d, body):
            bad += 1
            print('ENC MISMATCH', s, d, body.hex())
    print('encoder: %d cases, %d mismatches' % (len(cases), bad))

def rec(a, ch):
    base = 0x1FFF9BE4 + ch * 0x214
    src, dst, ln = a.r8(base), a.r8(base + 1), a.r8(base + 2)
    return src, dst, a.read(base + 4, ln)

def test_decoder():
    a = App()
    import random
    rnd = random.Random(2)
    bad = 0; n = 0
    for _ in range(300):
        s = rnd.randint(0, 15); d = rnd.randint(0, 15)
        body = bytes(rnd.randint(0, 255) for _ in range(rnd.randint(1, 255)))
        if (s << 4 | d) == 0xAA:
            continue
        w = encode(s, d, body)
        r = feed(a, 1, w)
        n += 1
        ok = r[-1] != 0 and all(x == 0 for x in r[:-1]) and rec(a, 1) == (s, d, body)
        if not ok:
            bad += 1; print('DEC FAIL', s, d, body.hex(), [hex(x) for x in r[-3:]])
    print('decoder round trip: %d frames, %d failures' % (n, bad))
    # edge cases
    a = App()
    print('edge: address 0xAA frame ->', hex(feed(a, 1, encode(0xA, 0xA, b'\x10'))[-1]))
    a = App()
    w = bytearray(encode(6, 2, b'\xc4\x31')); w[-1] ^= 1
    print('edge: bad checksum ->', hex(feed(a, 1, bytes(w))[-1]), 'state', a.r8(0x1FFF9BE4 + 0x214 + 0x208))
    a = App()
    print('edge: zero length frame AA 62 00 62 ->', [hex(x) for x in feed(a, 1, bytes([0xAA, 0x62, 0x00, 0x62]))])
    a = App()
    # garbage before frame, then a frame
    r = feed(a, 1, bytes([0x12, 0x34, 0x56]) + encode(6, 2, b'\xc2\x31'))
    print('edge: leading garbage then frame ->', hex(r[-1]), rec(a, 1))
    a = App()
    # frame restart in the middle: AA <non-AA> restarts
    r = feed(a, 1, bytes([0xAA, 0x62, 0x05, 0xC2]) + encode(6, 2, b'\xc2\x31'))
    print('edge: truncated frame then new frame ->', hex(r[-1]), rec(a, 1))
    a = App()
    # length byte 0xAA must be doubled
    body = bytes(range(0xAA))
    r = feed(a, 1, encode(6, 2, body))
    print('edge: len 0xAA ->', hex(r[-1]), rec(a, 1)[2] == body)
    a = App()
    # undoubled 0xAA inside body: AA followed by non-AA restarts parse with that byte as address
    w = bytes([0xAA, 0x62, 0x03, 0xC2, 0xAA, 0x31, 0x00])
    r = feed(a, 1, w)
    print('edge: single AA inside body ->', [hex(x) for x in r], 'state', a.r8(0x1FFF9BE4 + 0x214 + 0x208))

if __name__ == '__main__':
    test_encoder()
    test_decoder()

def rx_frame(a, wire):
    for b in wire:
        a.w16(USART3 + 6, b)
        a.call(RXCB)

def tx_frame(a):
    n = a.r8(0x1FFF954A)
    return a.read(0x1FFF944A, n)

def decode_wire(w):
    """Inverse of encode for checking replies."""
    assert w[0] == 0xAA
    out = []; i = 1
    while i < len(w):
        out.append(w[i])
        i += 2 if w[i] == 0xAA else 1
    addr, ln = out[0], out[1]
    body = bytes(out[2:2 + ln]); ck = out[2 + ln]
    assert ck == sum(out[:2 + ln]) & 0xFF, 'bad ck'
    return addr, body

def test_dispatch():
    for src, body in ((6, b'\xc4\x31'), (6, b'\xc4\x00'), (1, b'\xc4'), (5, b'\xc4'), (3, b'\xc4'),
                      (6, b'\xe0\x00'), (1, b'\xe0'), (6, b'\x00\x31'), (1, b'\xa0'), (6, b'\x18' + bytes([8]*16) + b'\x00\x00\x00')):
        a = App()
        a.hook_func(0x1AEBC, lambda s: 0)
        rx_frame(a, encode(src, 2, body))
        flags = [a.r8(0x1FFE01AC + i) for i in range(4)]
        a.w8(0x1FFF9448, 0)
        a.call(DISP, 10)
        pend = a.r8(0x1FFF9448)
        rep = decode_wire(tx_frame(a)) if pend else None
        print('src %d req %s flags %s -> pending %d reply %s S+3=%d' % (
            src, body.hex(' '), flags, pend,
            ('addr %02x body %s' % (rep[0], rep[1].hex(' '))) if rep else '-', a.r8(0x1FFFAACF)))

if __name__ == '__main__':
    test_dispatch()

def svc(a, elapsed=10):
    sent = []
    def dma(s):
        sent.append(s.read(s.reg(__import__('unicorn').arm_const.UC_ARM_REG_R2), s.reg(__import__('unicorn').arm_const.UC_ARM_REG_R3)))
        return 0
    a.hook_func(0x1E24C, dma)
    a.call(TXSVC, elapsed)
    return [decode_wire(w) for w in sent]

def ready(a):
    a.w8(0x1FFE0184, 1)   # K+0: CH58x acknowledged, may send
    a.w8(0x1FFF9449, 1)   # companion initialised (FD 03 seen)
    a.w8(0x1FFF9434, 1)   # first E1 seen

def test_bind():
    for choice, name in ((0x2478C, 'allow'), (0x2483C, 'deny')):
        a = App()
        for f in (0x375F8, 0x37604, 0x58430):
            a.hook_func(f, lambda s: 0)
        ready(a)
        rx_frame(a, encode(6, 2, b'\x18' + bytes([8] * 16) + b'\x00\x00\x00'))
        a.call(DISP, 10)
        print('bind: after 0x18 S+0x47=%d K+6=%d bits=%#x' % (a.r8(0x1FFFAB13), a.r8(0x1FFE018A), a.r32(0x1FFF9550)))
        a.call(choice)
        print('  %s: S+0x46=%d S+0x47=%d bits=%#x' % (name, a.r8(0x1FFFAB12), a.r8(0x1FFFAB13), a.r32(0x1FFF9550)))
        out = svc(a)
        print('  tx:', [('%02x' % ad, b.hex(' ')) for ad, b in out], 'bits=%#x S+0x46=%d K+0=%d' % (a.r32(0x1FFF9550), a.r8(0x1FFFAB12), a.r8(0x1FFE0184)))
    # USB bind: type 1 record
    a = App()
    for f in (0x375F8, 0x37604, 0x58430):
        a.hook_func(f, lambda s: 0)
    ready(a)
    rx_frame(a, encode(1, 2, b'\x18' + bytes([8] * 16) + b'\x00\x00'))
    a.call(DISP, 10)
    a.call(0x2478C)
    out = svc(a)
    print('USB bind allow tx:', [('%02x' % ad, b.hex(' ')) for ad, b in out], 'K+6=%d' % a.r8(0x1FFE018A))

if __name__ == '__main__':
    test_bind()

def test_boot_sequence():
    """Transmit service from reset state, with a simulated CH58x that answers."""
    a = App()
    a.hook_func(0x1AE70, lambda s: 0)
    log = []
    t = 0
    def step(ms):
        nonlocal t
        out = svc(a, ms); t += ms
        for ad, b in out:
            log.append((t, '%02x' % ad, b.hex(' ')))
        return out
    def ch_reply(body):
        rx_frame(a, encode(3, 2, body))
        a.call(DISP, 0)
    # phase 1: nothing answers for 1.2 s
    for _ in range(1200):
        step(1)
    # CH58x answers E1 (31 bytes as emulated from the CH58x image)
    e1 = bytes.fromhex('e14d503330354200000100660001000000010000' '0f4d503330354200000000')
    ch_reply(e1)
    print('after E1: 0x9434..37 =', a.read(0x1FFF9434, 4).hex(' '), 'K+0 =', a.r8(0x1FFE0184))
    for _ in range(1200):
        step(1)
        if a.r8(0x1FFE0184) == 0:
            ch_reply(bytes([0x55, 0, 0]))
    ch_reply(bytes([0xFD, 0x03]))
    print('after FD 03: 9449=%d bits=%#x' % (a.r8(0x1FFF9449), a.r32(0x1FFF9550)))
    ch_reply(bytes([0x55, 0, 0]))
    step(10)
    ch_reply(e1)
    ch_reply(bytes([0x55, 0, 0]))
    print('after 2nd E1: 0x942c..33 =', a.read(0x1FFF942C, 8).hex(' '))
    a.w8(0x1FFFAB1C, 1)   # powered on
    a.w8(0x1FFFAACF, 1)   # BLE host link (as after BD 01)
    step(10)
    ch_reply(bytes([0x55, 0, 0]))
    a.w32(0x1FFF9550, a.r32(0x1FFF9550) | 1)
    step(10)
    ch_reply(bytes([0x55, 0, 0]))
    for _ in range(11000):
        step(1)
        if a.r8(0x1FFE0184) == 0:
            ch_reply(bytes([0x55, 0, 0]))
    seen = {}
    for e in log:
        k = e[2][:5]
        seen.setdefault(k, []).append(e[0])
    for e in log[:12]:
        print('  t=%5d ms  addr %s  %s' % e)
    for k, v in seen.items():
        print('  %-6s count %3d first %5d last %5d' % (k, len(v), v[0], v[-1]))

if __name__ == '__main__':
    test_boot_sequence()

def booted():
    a = App()
    for f in (0x1AE70, 0x1AF64, 0x1AEA4, 0x1AEBC, 0x1CB8C, 0x1A5FC, 0x1A128, 0x1A134):
        a.hook_func(f, lambda s: 0)
    ready(a)
    a.w8(0x1FFFAB1C, 1)
    return a

def test_timeouts():
    # (a) no 0x55 ack: resend after 5000 loop iterations
    a = booted(); a.w8(0x1FFFAACF, 1); a.w8(0x1FFE018C, 1)
    a.w32(0x1FFF9550, 1 << 12)            # C4 push pending
    sent = []
    for i in range(12000):
        for ad, b in svc(a, 1):
            sent.append((i, '%02x' % ad, b.hex(' ')))
    print('(a) no-ack resend:', sent[:4], '... total', len(sent))
    # (b) USB host inactivity
    a = booted()
    rx_frame(a, encode(1, 2, b'\xc2')); a.call(DISP, 1)
    n = 0
    while a.r8(0x1FFFAACF) == 2 and n < 20000:
        a.call(DISP, 1); n += 1
    print('(b) USB link S+3=2 cleared after %d dispatcher iterations' % n)
    # (c) CH58x reports notify failure (55 00 FF): resend every 100 iterations, give up after 50
    a = booted(); a.w8(0x1FFFAACF, 1)
    w = encode(2, 6, b'\xc3\x00\x31'); a.w8(0x1FFF9448, 1); a.mu.mem_write(0x1FFF944A, w); a.w8(0x1FFF954A, len(w))
    svc(a, 1)                              # sends and saves frame
    rx_frame(a, encode(3, 2, bytes([0x55, 0x00, 0xFF])))
    print('(c) after 55 00 FF: K+0=%d K+1=%d K+2=%d' % (a.r8(0x1FFE0184), a.r8(0x1FFE0185), a.r8(0x1FFE0186)))
    cnt = 0; n = 0
    while a.r8(0x1FFFAACF) != 0 and n < 20000:
        cnt += len(svc(a, 1)); n += 1
    print('    resends=%d, S+3 cleared after %d iterations, K+2=%d' % (cnt, n, a.r8(0x1FFE0186)))
    # (d) USB queue full (55 FF 00) -> 0x55 polls to CH58x every 100, give up after 50
    a = booted(); a.w8(0x1FFFAACF, 2)
    rx_frame(a, encode(3, 2, bytes([0x55, 0xFF, 0x00])))
    polls = []; n = 0
    while a.r8(0x1FFFAACF) != 0 and n < 20000:
        for ad, b in svc(a, 1):
            polls.append((n, '%02x' % ad, b.hex()))
        if a.r8(0x1FFE0184) == 0:
            rx_frame(a, encode(3, 2, bytes([0x55, 0xFF, 0x00])))
        n += 1
    print('(d) queue-full polls:', polls[:3], 'count', len(polls), 'S+3 cleared after', n)
    # (e) 0x50 without 0x51 ack: resend after 1000
    a = booted(); a.w8(0x1FFFAACF, 1)
    sent = []
    for i in range(3500):
        for ad, b in svc(a, 1):
            sent.append((i, b.hex(' ')))
        a.call(DISP, 1)
        if a.r8(0x1FFE0184) == 0:
            rx_frame(a, encode(3, 2, bytes([0x55, 0, 0])))
    print('(e) 50 without 51:', sent)
    a = booted(); a.w8(0x1FFFAACF, 1)
    svc(a, 1); rx_frame(a, encode(3, 2, bytes([0x51, 0x00]))); a.call(DISP, 1)
    print('    after 51 00: 954b=%d K+8=%d' % (a.r8(0x1FFF954B), a.r8(0x1FFE018C)))

def test_remote():
    for link, src, sfx in ((2, 1, b''), (1, 6, b'\x31')):
        a = booted()
        a.w8(0x1FFFAACF, link); a.w8(0x1FFE018C, link)
        body = bytes([0xC8, 2, 0x14, 0x05, 0xE8, 0x03, 0, 0, 0, 0, 0, 0]) + sfx
        rx_frame(a, encode(src, 2, body)); a.w8(0x1FFF9448, 0)
        a.call(DISP, 1)
        rep = decode_wire(tx_frame(a)) if a.r8(0x1FFF9448) else None
        print('link %d remoteCon 2 -> reply %s S+0x42=%d S+0x45=%d' % (link, rep and rep[1].hex(' '), a.r8(0x1FFFAB0E), a.r8(0x1FFFAB11)))
        if link == 1:
            for f in (0x375F8, 0x37604, 0x58430):
                a.hook_func(f, lambda s: 0)
            a.call(0x5AF88)
            out = svc(a, 1)
            print('   allow dialog -> deferred', [('%02x' % x, y.hex(' ')) for x, y in out], 'S+0x42=%d' % a.r8(0x1FFFAB0E))
    a = booted(); a.w8(0x1FFFAACF, 1); a.w8(0x1FFE018C, 1)
    for f in (0x375F8, 0x37604, 0x58430):
        a.hook_func(f, lambda s: 0)
    rx_frame(a, encode(6, 2, bytes([0xC8, 2]) + bytes(10) + b'\x31')); a.call(DISP, 1)
    a.call(0x5B034)
    print('   deny dialog -> deferred', [('%02x' % x, y.hex(' ')) for x, y in svc(a, 1)])
    # link drop: BD 00 from CH58x (type 6), then UI snapshot 0x1e284
    a = booted(); a.w8(0x1FFFAACF, 1); a.w8(0x1FFFAB0E, 1); a.w8(0x1FFFAB11, 1)
    rx_frame(a, encode(6, 2, b'\xbd\x00')); a.call(DISP, 1)
    print('BD 00: S+3=%d, S+0x42=%d (before UI snapshot)' % (a.r8(0x1FFFAACF), a.r8(0x1FFFAB0E)))

if __name__ == '__main__':
    test_timeouts()
    test_remote()

def test_link_drop_snapshot():
    for s3 in (0, 1, 2):
        a = booted()
        for f in (0x1814C, 0x528AC, 0x49A70, 0x4B288, 0x2E158, 0x4EF90, 0x5689C, 0x21A50, 0x4FEA8,
                  0x18114, 0x17CF8, 0x58BA4, 0x52A82, 0x4AA6E, 0x4CD1E, 0x58268, 0x569B8, 0x52ABE):
            a.hook_func(f, lambda s: 0)
        a.w8(0x1FFFAACF, s3); a.w8(0x1FFFAB0E, 1); a.w8(0x1FFFAB11, 1); a.w8(0x1FFE0220, 1)
        a.w8(0x1FFFAA2E, 1)  # output on
        a.call(0x1E284)
        print('UI snapshot with S+3=%d: S+0x42=%d S+0x45=%d output(0x1fffaa2e)=%d aa4f=%d' % (
            s3, a.r8(0x1FFFAB0E), a.r8(0x1FFFAB11), a.r8(0x1FFFAA2E), a.r8(0x1FFFAA4F)))
        if s3 == 0:
            a.call(0x1E284)
            print('   second pass: S+0x42=%d S+0x45=%d 0x220=%d' % (a.r8(0x1FFFAB0E), a.r8(0x1FFFAB11), a.r8(0x1FFE0220)))

if __name__ == '__main__':
    test_link_drop_snapshot()

def test_pipelining():
    a = booted(); a.w8(0x1FFFAACF, 1); a.w8(0x1FFE018C, 1)
    a.w8(0x1FFE0184, 0)   # previous frame not yet acknowledged by the CH58x
    rx_frame(a, encode(6, 2, b'\xc4\x31')); a.call(DISP, 1); svc(a, 1)
    rx_frame(a, encode(6, 2, b'\xe0\x31')); a.call(DISP, 1); svc(a, 1)
    rx_frame(a, encode(3, 2, bytes([0x55, 0, 0])))
    out = svc(a, 1)
    print('pipelined C4 then E0 while unacked ->', [('%02x' % x, y[:1].hex()) for x, y in out])
    # two sources pending in the same loop: only one record per dispatcher call
    a = booted(); a.w8(0x1FFFAACF, 1); a.w8(0x1FFE018C, 1)
    rx_frame(a, encode(6, 2, b'\xc4\x31')); rx_frame(a, encode(1, 2, b'\xc2'))
    a.call(DISP, 1); o1 = svc(a, 1); rx_frame(a, encode(3, 2, bytes([0x55, 0, 0])))
    a.call(DISP, 1); o2 = svc(a, 1)
    print('BLE+USB pending ->', [('%02x' % x, y[:1].hex()) for x, y in o1 + o2])

if __name__ == '__main__':
    test_pipelining()

def test_internal_inbound():
    a = booted()
    a.w8(0x1FFE0191, 1); a.w8(0x1FFE0192, 1); a.w32(0x1FFE01B0, 5)
    rx_frame(a, encode(5, 2, b'\xbd\x01' + b'ISDT-RC')); a.call(DISP, 1)
    print('BD src5 01 name: S+4=%d S+0x58=%r K+0x0D=%d' % (a.r8(0x1FFFAAD0), a.read(0x1FFFAB24, 10), a.r8(0x1FFE0191)))
    rx_frame(a, encode(5, 2, b'\xbd\x00')); a.call(DISP, 1)
    print('BD src5 00: S+4=%d K+0x0D=%d K+0x0E=%d K+0x2C=%d' % (a.r8(0x1FFFAAD0), a.r8(0x1FFE0191), a.r8(0x1FFE0192), a.r32(0x1FFE01B0)))
    a.w8(0x1FFE0186, 1); a.w8(0x1FFFAACF, 1)
    rx_frame(a, encode(6, 2, b'\xbd\x00')); a.call(DISP, 1)
    print('BD src6 00: S+3=%d K+2=%d' % (a.r8(0x1FFFAACF), a.r8(0x1FFE0186)))
    rx_frame(a, encode(6, 2, b'\xbd\x01')); a.call(DISP, 1)
    print('BD src6 01: S+3=%d' % a.r8(0x1FFFAACF))
    # BE accessory events (9-byte frames)
    for ev in (bytes([0xBE, 4, 0, 0, 0, 0, 0, 0, 0]), bytes([0xBE, 0, 0, 0, 0, 0, 0, 1, 0]),
               bytes([0xBE, 0, 0, 0, 0, 0, 0, 0xFF, 0]), bytes([0xBE, 1, 0, 0, 0, 0, 0, 0, 0]),
               bytes([0xBE, 0, 0, 0, 0, 0, 0, 0, 0])):
        rx_frame(a, encode(5, 2, ev)); a.call(DISP, 1)
        print('  BE %s -> K+0D..0F=%d,%d,%d wheel=%d S+0x1D=%d' % (ev.hex(' '), a.r8(0x1FFE0191), a.r8(0x1FFE0192),
              a.r8(0x1FFE0193), a.r32(0x1FFE01B0) - (1 << 32) * (a.r32(0x1FFE01B0) >> 31), a.r8(0x1FFFAAE9)))
    # BB list
    lst = bytes([0xBB, 2]) + bytes([1, 2, 3, 4, 5, 6, 3]) + b'ABC' + bytes([0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 2]) + b'XY'
    rx_frame(a, encode(5, 2, lst)); a.call(DISP, 1)
    print('BB: count=%d rec0=%s rec1=%s sum=%#x S+0x3D=%d' % (a.r8(0x1FFF9A74), a.read(0x1FFF9A76, 12).hex(' '),
          a.read(0x1FFF9A76 + 0x26, 10).hex(' '), a.r32(0x1FFF9A70), a.r8(0x1FFFAB09)))
    # 0x51 / 0x53 / F1 / FD
    a.w8(0x1FFF954B, 1); a.w8(0x1FFF954C, 1)
    rx_frame(a, encode(3, 2, b'\x51\x00')); a.call(DISP, 1)
    rx_frame(a, encode(6, 2, b'\x53\x00')); a.call(DISP, 1)
    print('51 from src3 clears 954b=%d; 53 from src6 leaves 954c=%d' % (a.r8(0x1FFF954B), a.r8(0x1FFF954C)))
    a.w8(0x1FFFA00E, 1)
    rx_frame(a, encode(3, 2, b'\xf1\x00')); a.call(DISP, 1)
    print('F1 00 from src3: a00e=%d' % a.r8(0x1FFFA00E))
    rx_frame(a, encode(3, 2, b'\xfd\xff')); a.call(DISP, 1)
    print('FD FF: 9449=%d K+0..2=%s 943c=%d' % (a.r8(0x1FFF9449), a.read(0x1FFE0184, 3).hex(' '), a.r32(0x1FFF943C)))
    rx_frame(a, encode(1, 2, b'\xfd\x03')); a.call(DISP, 1)
    print('FD 03 from src1 (USB!): 9449=%d bits=%#x' % (a.r8(0x1FFF9449), a.r32(0x1FFF9550)))
    # time sync 0x11
    a.w32(0x1FFE0168, 1000)
    rx_frame(a, encode(3, 2, b'\x11' + (5000).to_bytes(4, 'little')))
    a.w32(0x1FFE0168, 11000)
    rx_frame(a, encode(3, 2, b'\x11' + (1005000).to_bytes(4, 'little')))
    print('0x11 sync: ratio=%d last=%d flag3=%d' % (a.r32(0x1FFE0160), a.r32(0x1FFF9444), a.r8(0x1FFE01AF)))

if __name__ == '__main__':
    test_internal_inbound()

def test_be_from_host():
    """BE frames arriving from a BLE host (source 6, route suffix 0x31) drive the accessory input state."""
    a = booted()
    calls = []
    a.hook_func(0x1AEBC, lambda s: calls.append(('set_output', s.reg(__import__('unicorn').arm_const.UC_ARM_REG_R0))) or 0)
    a.hook_func(0x1A128, lambda s: 0)      # output currently off
    a.hook_func(0x1A134, lambda s: 0)      # no output fault
    a.hook_func(0x186F0, lambda s: 0)      # physical output key not pressed
    a.hook_func(0x1CB8C, lambda s: 0)
    a.w8(0x1FFFAAE5, 7); a.w8(0x1FFFAAFC, 0); a.w8(0x1FFFAB0E, 0); a.w8(0x1FFFAB17, 0); a.w8(0x1FFFAAD3, 0)
    a.w8(0x1FFE0191, 0); a.w8(0x1FFE0192, 0); a.w8(0x1FFE0193, 0)
    for body in (bytes([0xBE, 1, 0, 0, 0, 0, 0, 0, 0, 0x31]), bytes([0xBE, 0, 0, 0, 0, 0, 0, 0, 0, 0x31])):
        rx_frame(a, encode(6, 2, body)); a.call(DISP, 1)
    print('host BE 01 / BE 00 (src 6): S+0x1D=%d' % a.r8(0x1FFFAAE9))
    a.call(0x18728, 10)
    print('   output-key worker 0x18728 ->', calls, 'S+0x1D=%d' % a.r8(0x1FFFAAE9))
    # wheel and push via 0x15b54 (keypad read helper)
    a.w32(0x1FFE01B0, 0)
    rx_frame(a, encode(6, 2, bytes([0xBE, 0, 0, 0, 0, 0, 0, 0, 1, 0x31]))); a.call(DISP, 1)
    print('   wheel +1 -> 0x15b54 returns', a.call(0x15B54))
    rx_frame(a, encode(6, 2, bytes([0xBE, 4, 0, 0, 0, 0, 0, 0, 0, 0x31]))); a.call(DISP, 1)
    r = [a.call(0x15B54) for _ in range(3)]
    rx_frame(a, encode(6, 2, bytes([0xBE, 0, 0, 0, 0, 0, 0, 0, 0, 0x31]))); a.call(DISP, 1)
    print('   push (BE 04) then release -> 0x15b54 returns', r, a.call(0x15B54))
    # BD 01 from the host itself
    a.w8(0x1FFFAACF, 0)
    rx_frame(a, encode(6, 2, bytes([0xBD, 1, 0x31]))); a.call(DISP, 1)
    print('host-sent BD 01 on AF01 (src 6, len 3): S+3=%d' % a.r8(0x1FFFAACF))

if __name__ == '__main__':
    test_be_from_host()

def c8(a, src, rc, sfx=b'\x31', out=0):
    body = bytes([0xC8, rc, 0x14, 0x05, 0xE8, 0x03, 0, 0, 0, out, 0, 0]) + (sfx if src == 6 else b'')
    a.w8(0x1FFF9448, 0)
    rx_frame(a, encode(src, 2, body)); a.call(DISP, 1)
    return decode_wire(tx_frame(a))[1].hex(' ') if a.r8(0x1FFF9448) else 'no reply'

def test_c8_sequences():
    a = booted(); a.w8(0x1FFFAACF, 1); a.w8(0x1FFE018C, 1)
    print('BLE: rc2 ->', c8(a, 6, 2), '| rc1 while pending ->', c8(a, 6, 1), '| S+0x45=%d' % a.r8(0x1FFFAB11))
    a.w8(0x1FFFAB0E, 1); a.w8(0x1FFFAB11, 1)   # as after Allow
    print('BLE granted: rc1 ->', c8(a, 6, 1), '| rc2 again ->', c8(a, 6, 2), 'S+0x45=%d S+0x42=%d' % (a.r8(0x1FFFAB11), a.r8(0x1FFFAB0E)))
    print('BLE: rc0 ->', c8(a, 6, 0), 'S+0x42=%d' % a.r8(0x1FFFAB0E))
    a = booted(); a.w8(0x1FFFAACF, 0)
    print('BLE unbound (S+3=0): rc2 ->', c8(a, 6, 2), '| rc1 ->', c8(a, 6, 1))
    a = booted(); a.w8(0x1FFFAACF, 0)
    print('USB first frame rc2 ->', c8(a, 1, 2), 'S+3=%d | rc1 ->' % a.r8(0x1FFFAACF), c8(a, 1, 1), '| rc3 ->', c8(a, 1, 3))

if __name__ == '__main__':
    test_c8_sequences()
