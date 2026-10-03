"""Spike, as root in the Linux VM: HCI local loopback through BlueZ's raw
HCI socket.

Puts the controller into HCI local loopback mode, sends one ACL data packet
and waits for it to come back. No radio traffic is involved. Stop
bluetoothd first (systemctl stop bluetooth) and bring hci0 up.
"""
import select, socket, struct, time

s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_RAW, socket.BTPROTO_HCI)
s.bind((0,))
s.setsockopt(socket.SOL_HCI, socket.HCI_FILTER, struct.pack("<IIIH2x", 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0))

def read_all(seconds):
    out, end = [], time.time() + seconds
    while time.time() < end:
        r, _, _ = select.select([s], [], [], 0.1)
        if r:
            out.append(s.recv(1024))
    return out

def cmd(opcode, params=b""):
    s.send(struct.pack("<BHB", 0x01, opcode, len(params)) + params)

cmd(0x0C03); read_all(1.0)                      # HCI Reset
cmd(0x1802, b"\x01")                            # Write Loopback Mode: local
handles = []
for p in read_all(2.0):
    if p[0] == 0x04 and p[1] == 0x03:           # Connection Complete
        status, handle, link = p[3], struct.unpack("<H", p[4:6])[0], p[12]
        handles.append((handle, link, status))
    if p[0] == 0x04 and p[1] == 0x0E and p[4:6] == b"\x02\x18":
        print("loopback mode command status:", p[6])
print("loopback connections (handle, link type, status):", handles)
acl = [h for h, link, st in handles if link == 1 and st == 0]
if acl:
    payload = bytes(range(16))
    s.send(struct.pack("<BHH", 0x02, acl[0] | 0x2000, len(payload)) + payload)
    got = read_all(3.0)
    back = [p for p in got if p[0] == 0x02]
    done = [p for p in got if p[0] == 0x04 and p[1] == 0x13]
    print("acl packets received back:", len(back), "matching:", sum(p[5:] == payload for p in back))
    print("number-of-completed-packets events:", len(done))
else:
    print("the controller offered no ACL loopback connection")
cmd(0x1802, b"\x00"); read_all(0.5)
cmd(0x0C03); read_all(1.0)
