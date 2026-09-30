"""Compare readable worker C and collect display setup from original ARM code."""
from emulate import *
from unicorn import UC_HOOK_CODE
import ctypes

lib = ctypes.CDLL(str(ROOT / 'reconstructed/libprotocol.dylib'))
lib.reconstructed_reference_registers.argtypes = [ctypes.c_uint32, ctypes.c_void_p]
lib.reconstructed_d9.argtypes = [ctypes.c_void_p, ctypes.c_uint8, ctypes.c_uint8,
                               ctypes.c_void_p, ctypes.c_uint8, ctypes.c_uint8,
                               ctypes.c_void_p]
lib.reconstructed_d9.restype = ctypes.c_size_t
results = []


def check(name, condition, **details):
    assert condition, (name, details)
    results.append(dict(case=name, pass_result=True, **details))


for target in [0, 1, 2, 3, 10, 999, 1000, 2045, 2046, 2047, 2048, 3000, 0xffffffff]:
    for selector in [0, 1]:
        m = Machine()
        events = []

        def register_stub(u, address, size, data):
            if address == 0x12cb0:
                events.append([u.reg_read(r) for r in [UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2]])
                u.reg_write(UC_ARM_REG_PC, u.reg_read(UC_ARM_REG_LR))

        m.uc.hook_add(UC_HOOK_CODE, register_stub)
        m.call(0x19116, selector, target)
        packed = ctypes.create_string_buffer(2)
        lib.reconstructed_reference_registers(target, packed)
        check(f'reference registers {selector}/{target}', events == [[selector, 3, packed.raw[0]], [selector, 4, packed.raw[1]]], events=events)

records = bytes(i % 256 for i in range(1200))
for count in [0, 1, 9, 10, 11, 20, 100]:
    for kind in [1, 6]:
        m = Machine()
        m.uc.mem_write(0x1fffa3fe + 3, b'\x07')
        m.uc.mem_write(0x1fffa3f4 + 3, bytes([count]))
        m.uc.mem_write(0x1fff8f7c, records)
        cursor = ctypes.c_uint8(0)
        for start in range(0, max(count, 1), 10):
            original = m.handler(0x15ca0, bytes([0xd8, 3, 0x31]), kind)
            out = ctypes.create_string_buffer(123)
            length = lib.reconstructed_d9(records, count, 7, ctypes.byref(cursor), kind, 0x31, out)
            check(f'D9 C versus ARM {count}/{kind}/{start}', out.raw[:length] == original and cursor.value == m.uc.mem_read(0x1ffe0187, 1)[0])

# Preserve every command/data byte and delay from the original display setup.
m = Machine()
display = []


def display_stub(u, address, size, data):
    if address in [0x3c132, 0x3c150, 0x658d4]:
        display.append(dict(operation={0x3c132: 'command', 0x3c150: 'data', 0x658d4: 'delay_ticks'}[address], value=u.reg_read(UC_ARM_REG_R0)))
        u.reg_write(UC_ARM_REG_PC, u.reg_read(UC_ARM_REG_LR))


m.uc.hook_add(UC_HOOK_CODE, display_stub)
m.call(0x60258)
check('display initialization signature', display[:3] == [dict(operation='command', value=0xdf), dict(operation='data', value=0x98), dict(operation='data', value=0x53)])
check('display initialization final commands', display[-3:] == [dict(operation='delay_ticks', value=120), dict(operation='command', value=0x29), dict(operation='command', value=0x2c)])
(ROOT / 'exports/display-initialization.json').write_text(json.dumps(dict(
    scope='Original ARM 0x60258 with command/data transfer and delay helpers substituted; no panel I/O.', operations=display), indent=2) + '\n')
(ROOT / 'exports/worker-comparison.json').write_text(json.dumps(dict(
    scope='Readable C versus original ARM reference-register packing and D9 replies; original display initialization with bus/delay substitutes. No hardware.',
    passed=len(results), failed=0, cases=results), indent=2) + '\n')
print(len(results), 'worker comparison cases passed')
