"""Record ASUS USB-BT600 local loopback through Linux btusb.

Run as root with the named adapter down and bluetoothd stopped. Only the
0b05:1d70 adapter is accepted. No radio connection or supply command is made.
The controller is reset and the HCI user-channel socket closed at exit.
"""

import argparse
import datetime
import json
from pathlib import Path
import platform
import struct
import sys
import time

from host_hci import SocketDongle


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--hci', type=int, required=True)
    parser.add_argument('--capture', required=True)
    args = parser.parse_args()
    device = Path(f'/sys/class/bluetooth/hci{args.hci}').resolve()
    usb = next((p for p in device.parents if (p / 'idVendor').exists()), None)
    if usb is None or (usb / 'idVendor').read_text().strip() != '0b05' or (
            usb / 'idProduct').read_text().strip() != '1d70':
        parser.error('the selected adapter is not ASUS USB-BT600 0b05:1d70')
    started = time.monotonic()
    with open(args.capture, 'x', encoding='utf-8') as out:
        def note(kind, **data):
            out.write(json.dumps({'t': round(time.monotonic() - started, 6),
                                  'kind': kind, **data}) + '\n')
            out.flush()

        note('meta', spike='dongle_acl_path', script='linux_loopback.py',
             started=datetime.datetime.now(datetime.timezone.utc).isoformat(),
             host=platform.platform(), adapter='ASUS USB-BT600 0b05:1d70',
             usb_path=str(usb), os_release=Path('/etc/os-release').read_text(),
             command=' '.join(sys.argv), transport='HCI user channel through btusb',
             firmware='Read Local Version reply retained; no power supply')
        dongle = None
        try:
            dongle = SocketDongle(args.hci)
            # Write events as they occur, including cleanup, without modifying
            # the reusable transport's existing capture behavior.
            dongle.note = lambda kind, data: note('hci', hci=kind, hex=data.hex())
            dongle.cmd(0x0c03)
            dongle.events(0.3)
            dongle.cmd(0x1001)
            dongle.events(0.3)
            dongle.cmd(0x1802, b'\x01')
            setup = dongle.events(0.5)
            handles = [struct.unpack('<H', e[3:5])[0] for e in setup
                       if len(e) >= 13 and e[0] == 3 and e[2] == 0 and e[11] == 1]
            if not handles:
                raise RuntimeError('no successful ACL loopback connection')
            payload = bytes(range(16))
            packet = struct.pack('<HH', handles[0] | 0x2000, len(payload)) + payload
            dongle.send_acl(packet)
            dongle.note('acl out', packet)
            events = dongle.events(3.0)
            result = {'payload_matches': any(p[4:] == payload for p in dongle.acl_in),
                      'received_packets': len(dongle.acl_in), 'handles': handles,
                      'completion_events': [e.hex() for e in events if e[0] == 0x13]}
            note('result', **result)
            print(json.dumps(result))
        except BaseException as error:
            note('failure', error=repr(error))
            raise
        finally:
            if dongle is not None:
                try:
                    dongle.close()
                    note('cleanup', operation='HCI Reset', result='sent; replies retained')
                finally:
                    dongle.sock.close()
                    note('cleanup', operation='close HCI user channel', result='closed')


if __name__ == '__main__':
    main()
