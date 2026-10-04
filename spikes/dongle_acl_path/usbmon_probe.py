"""Capture only the ASUS USB-BT600's Linux USB requests around a probe.

Requires root, loaded usbmon and mounted debugfs. The capture retains each
matching usbmon text line verbatim in JSONL. These are driver requests and
callbacks, not a physical USB-wire trace. Probe execution is limited to
30 seconds. Invoke with --capture FILE -- python3 PROBE [arguments].
"""

import argparse
import datetime
import json
import os
from pathlib import Path
import platform
import select
import subprocess
import threading
import time


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--capture', required=True)
    parser.add_argument('command', nargs=argparse.REMAINDER)
    args = parser.parse_args()
    command = args.command[1:] if args.command[:1] == ['--'] else args.command
    if not command:
        parser.error('provide a probe command after --')
    matches = [p for p in Path('/sys/bus/usb/devices').iterdir()
               if (p / 'idVendor').exists() and (p / 'idVendor').read_text().strip() == '0b05'
               and (p / 'idProduct').read_text().strip() == '1d70']
    if len(matches) != 1:
        parser.error('exactly one ASUS USB-BT600 is required')
    device = matches[0]
    bus, address = [int((device / key).read_text()) for key in ('busnum', 'devnum')]
    started = time.monotonic()
    stop = threading.Event()
    reader_errors = []
    lock = threading.Lock()
    with open(args.capture, 'x', encoding='utf-8') as out:
        def note(kind, **data):
            with lock:
                out.write(json.dumps({'t': round(time.monotonic() - started, 6),
                                      'kind': kind, **data}) + '\n')
                out.flush()

        note('meta', spike='dongle_acl_path', script='usbmon_probe.py',
             started=datetime.datetime.now(datetime.timezone.utc).isoformat(),
             host=platform.platform(), adapter='ASUS USB-BT600 0b05:1d70',
             device=str(device.resolve()), bus=bus, address=address, command=command,
             descriptors_hex=(device / 'descriptors').read_bytes().hex(),
             autosuspend={key: (device / 'power' / key).read_text().strip()
                          for key in ('control', 'runtime_status', 'autosuspend_delay_ms')},
             firmware='see accompanying HCI capture; no supply connection')
        fd = os.open(f'/sys/kernel/debug/usb/usbmon/{bus}u', os.O_RDONLY | os.O_NONBLOCK)

        def read_lines():
            pending = b''
            while not stop.is_set():
                if not select.select([fd], [], [], 0.1)[0]:
                    continue
                try:
                    chunk = os.read(fd, 65536)
                except BlockingIOError:
                    # usbmon can report readiness before a full record is
                    # available. Keep the reader alive until the next event.
                    stop.wait(0.01)
                    continue
                if not chunk:
                    break
                pending += chunk
                while b'\n' in pending:
                    raw, pending = pending.split(b'\n', 1)
                    line = raw.decode('ascii')
                    fields = line.split()
                    if len(fields) < 4:
                        continue
                    endpoint = fields[3].split(':')
                    if len(endpoint) == 4 and int(endpoint[1]) == bus and int(endpoint[2]) == address:
                        note('usbmon', line=line)

        def monitor():
            try:
                read_lines()
            except BaseException as error:
                reader_errors.append(repr(error))
                note('failure', operation='usbmon reader', error=repr(error))

        reader = threading.Thread(target=monitor)
        reader.start()
        try:
            result = subprocess.run(command, timeout=30, check=False)
            note('result', probe_exit_code=result.returncode)
        except BaseException as error:
            note('failure', error=repr(error))
            raise
        finally:
            time.sleep(0.2)
            stop.set()
            reader.join()
            os.close(fd)
            note('cleanup', operation='close usbmon reader', result='closed')
        if reader_errors or result.returncode != 0:
            raise SystemExit(1)


if __name__ == '__main__':
    main()
