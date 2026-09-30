"""Trace denial and command permissions in original instructions, offline only."""
from emulate import *
from unicorn import UC_HOOK_CODE
from ble_cases import BLE, REQ

results = []


def check(name, condition, **details):
    assert condition, (name, details)
    results.append(dict(case=name, pass_result=True, **details))


def denied_machine(grant=0):
    machine = Machine()
    machine.uc.mem_map(0xe0000000, 0x100000)
    machine.uc.mem_write(0x1ffe0000, (ROOT / 'inputs/main-initialized-ram.bin').read_bytes())
    machine.uc.mem_write(STATE + 0x42, bytes([grant]))
    machine.uc.mem_write(STATE + 0x46, b'\x01\x01')

    def ui_stub(u, address, size, data):
        if address in [0x375f8, 0x37604, 0x58430]:
            u.reg_write(UC_ARM_REG_R0, 0)
            u.reg_write(UC_ARM_REG_PC, u.reg_read(UC_ARM_REG_LR))

    machine.uc.hook_add(UC_HOOK_CODE, ui_stub)
    machine.call(0x2483c)
    check(f'deny callback with prior grant {grant}',
          machine.uc.mem_read(STATE + 0x46, 2) == b'\0\0'
          and machine.uc.mem_read(STATE + 0x42, 1) == bytes([grant])
          and int.from_bytes(machine.uc.mem_read(0x1fff9550, 4), 'little') & 2 != 0)
    count = machine.call(0x12690, RESPONSE, 6)
    check(f'deny reply with prior grant {grant}', count == 3 and machine.uc.mem_read(RESPONSE, 3) == b'\x19\xff\0')
    return machine


for opcode in [0xc2, 0xc4, 0xe0, 0xc6, 0xc8]:
    m = denied_machine()
    request = bytes([opcode, 0x31])
    if opcode == 0xc6:
        request = settings_frame() + b'\x31'
    if opcode == 0xc8:
        request = bytes([0xc8, 1]) + struct.pack('<HH', 500, 100) + bytes([0, 0, 0, 0, 0, 0, 0x31])
    m.uc.mem_write(0x1fff9660, bytes([6, 2, len(request), 0]) + request)
    m.uc.mem_write(0x1ffe01ac, b'\x01')
    m.call(0x12f34, 1)
    slot = bytes(m.uc.mem_read(0x1fff9efc, 128))
    reply = slot[4:4 + slot[2]]
    check(f'dispatch after denial {opcode:02x}', bool(reply) and reply[0] == opcode + 1, reply=reply.hex())
    if opcode == 0xc6:
        check('C6 changes settings without binding or remote grant', reply == b'\xc7\0\x31' and m.uc.mem_read(STATE + 0x2d, 1) == b'\x5a' and m.uc.mem_read(STATE + 0x48, 1) == b'\x01')
    if opcode == 0xc8:
        check('C8 remote-active request fails without remote grant', reply == b'\xc9\x01\x31')

denied_machine(grant=1)

# BLE connection/binding state does not gate AF01 forwarding. SDK copy/fill
# functions are explicit substitutes in BLE; queue construction is original code.
for connection_state in [0, 1, 2]:
    for opcode in [0xc2, 0xc4, 0xe0, 0xc6, 0xc8]:
        m = BLE()
        m.u.mem_write(0x20002ff4, bytes([connection_state]))
        m.u.mem_write(REQ, bytes([opcode, 0]))
        m.call(0x4224, REQ, 2, 0)
        check(f'AF01 forwards opcode {opcode:02x} state {connection_state}', m.u.mem_read(0x20003a54, 3) == bytes([opcode, 0, 0x31]) and m.u.mem_read(0x20003c58, 1) == b'\x01')

(ROOT / 'exports/permission-emulation.json').write_text(json.dumps(dict(
    scope='Original main UI denial callback, reply builder, dispatcher and handlers with UI functions substituted; original RV32 AF01 and queue code with SDK memory substitutes. Synthetic RAM only; no device I/O. Does not establish vendor intent or all command permissions.',
    passed=len(results), failed=0, cases=results), indent=2) + '\n')
print(len(results), 'permission cases passed')
