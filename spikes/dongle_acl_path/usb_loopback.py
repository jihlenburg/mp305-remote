"""Diagnose ASUS USB-BT600 local loopback through the libusb C API.

No radio connection or power-supply command is made. Each run opens only
0b05:1d70, resets it, enters local loopback, sends one ACL packet, reads
bulk IN and resets it again. Results include partial bytes on USB errors.
The capture is created exclusively and is never overwritten.
"""

import argparse
import ctypes as c
import ctypes.util
import datetime
import json
import platform
import struct
import threading
import time


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--capture', required=True)
    parser.add_argument('--read-size', type=int, default=1028)
    parser.add_argument('--payload-size', type=int, default=16)
    parser.add_argument('--timeout-ms', type=int, default=1500)
    parser.add_argument('--read-before-write', action='store_true')
    parser.add_argument('--set-configuration', action='store_true')
    parser.add_argument('--set-alt', action='store_true')
    parser.add_argument('--clear-halt', action='store_true')
    parser.add_argument('--stop-at-command-complete', action='store_true')
    parser.add_argument('--detach-kernel-driver', action='store_true',
                        help='Temporarily detach interface 0 and reattach it at exit (Linux)')
    args = parser.parse_args()
    if not 4 <= args.read_size <= 65536 or not 1 <= args.payload_size <= 252:
        parser.error('read size must be 4..65536; payload size 1..252')
    if not 100 <= args.timeout_ms <= 10000:
        parser.error('timeout must be 100..10000 ms')
    out = open(args.capture, 'x', encoding='utf-8')
    lock = threading.Lock()
    started = time.monotonic()

    def note(kind, **data):
        with lock:
            row = {'t': round(time.monotonic() - started, 6), 'kind': kind, **data}
            out.write(json.dumps(row) + '\n')
            out.flush()

    note('meta', spike='dongle_acl_path', script='usb_loopback.py',
         started=datetime.datetime.now(datetime.timezone.utc).isoformat(),
         host=platform.platform(), adapter='ASUS USB-BT600 0b05:1d70',
         firmware='controller version recorded in HCI Read Local Version reply; no supply',
         parameters=vars(args), command=' '.join(__import__('sys').argv))
    library = (ctypes.util.find_library('usb-1.0') if platform.system() == 'Linux'
               else '/opt/homebrew/lib/libusb-1.0.dylib')
    if not library:
        raise RuntimeError('libusb-1.0 was not found')
    lib = c.CDLL(library)
    note('library', path=library)
    signatures = {
        'libusb_init': (c.c_int, [c.POINTER(c.c_void_p)]),
        'libusb_exit': (None, [c.c_void_p]),
        'libusb_open_device_with_vid_pid': (c.c_void_p, [c.c_void_p, c.c_uint16, c.c_uint16]),
        'libusb_close': (None, [c.c_void_p]),
        'libusb_get_configuration': (c.c_int, [c.c_void_p, c.POINTER(c.c_int)]),
        'libusb_set_configuration': (c.c_int, [c.c_void_p, c.c_int]),
        'libusb_claim_interface': (c.c_int, [c.c_void_p, c.c_int]),
        'libusb_release_interface': (c.c_int, [c.c_void_p, c.c_int]),
        'libusb_set_interface_alt_setting': (c.c_int, [c.c_void_p, c.c_int, c.c_int]),
        'libusb_kernel_driver_active': (c.c_int, [c.c_void_p, c.c_int]),
        'libusb_detach_kernel_driver': (c.c_int, [c.c_void_p, c.c_int]),
        'libusb_attach_kernel_driver': (c.c_int, [c.c_void_p, c.c_int]),
        'libusb_clear_halt': (c.c_int, [c.c_void_p, c.c_ubyte]),
        'libusb_error_name': (c.c_char_p, [c.c_int]),
        'libusb_control_transfer': (c.c_int, [c.c_void_p, c.c_ubyte, c.c_ubyte,
                                             c.c_uint16, c.c_uint16, c.c_void_p,
                                             c.c_uint16, c.c_uint]),
        'libusb_bulk_transfer': (c.c_int, [c.c_void_p, c.c_ubyte, c.c_void_p,
                                          c.c_int, c.POINTER(c.c_int), c.c_uint]),
        'libusb_interrupt_transfer': (c.c_int, [c.c_void_p, c.c_ubyte, c.c_void_p,
                                               c.c_int, c.POINTER(c.c_int), c.c_uint]),
    }
    for name, (restype, argtypes) in signatures.items():
        fn = getattr(lib, name)
        fn.restype, fn.argtypes = restype, argtypes

    def status(operation, result):
        note('usb_status', operation=operation, result=result,
             error=lib.libusb_error_name(result).decode() if result < 0 else None)
        if result < 0:
            raise RuntimeError(f'{operation}: {lib.libusb_error_name(result).decode()}')

    context, handle, claimed, detached = c.c_void_p(), None, False, False
    bulk_thread = None
    try:
        status('init', lib.libusb_init(c.byref(context)))
        handle = lib.libusb_open_device_with_vid_pid(context, 0x0b05, 0x1d70)
        if not handle:
            raise RuntimeError('could not open 0b05:1d70')
        config = c.c_int()
        status('get_configuration', lib.libusb_get_configuration(handle, c.byref(config)))
        note('configuration', value=config.value,
             kernel_driver=lib.libusb_kernel_driver_active(handle, 0))
        if args.detach_kernel_driver and lib.libusb_kernel_driver_active(handle, 0) == 1:
            status('detach_kernel_driver', lib.libusb_detach_kernel_driver(handle, 0))
            detached = True
        if args.set_configuration or config.value != 1:
            status('set_configuration', lib.libusb_set_configuration(handle, 1))
        status('claim_interface', lib.libusb_claim_interface(handle, 0))
        claimed = True
        if args.set_alt:
            status('set_alt_0', lib.libusb_set_interface_alt_setting(handle, 0, 0))
        if args.clear_halt:
            status('clear_halt_IN', lib.libusb_clear_halt(handle, 0x82))

        def command(opcode, payload=b''):
            packet = struct.pack('<HB', opcode, len(payload)) + payload
            buf = c.create_string_buffer(packet)
            result = lib.libusb_control_transfer(handle, 0x20, 0, 0, 0, buf, len(packet), 1000)
            note('hci_command', hex=packet.hex(), result=result)
            if result != len(packet):
                raise RuntimeError(f'command {opcode:04x}: {result}')

        def events(seconds):
            rows = []
            end = time.monotonic() + seconds
            while time.monotonic() < end:
                buf, count = c.create_string_buffer(256), c.c_int()
                result = lib.libusb_interrupt_transfer(handle, 0x81, buf, 256, c.byref(count), 100)
                raw = buf.raw[:count.value]
                if raw or result != -7:
                    note('hci_event', result=result, transferred=count.value, hex=raw.hex())
                if result not in (0, -7):
                    raise RuntimeError(f'event read: {result}')
                if raw:
                    rows.append(raw)
                    if args.stop_at_command_complete and raw[0] == 0x0e:
                        break
            return rows

        command(0x0c03)
        events(0.3)
        command(0x1001)
        version_events = events(0.3)
        command(0x1802, b'\x01')
        setup = events(0.5)
        handles = [struct.unpack('<H', event[3:5])[0] for event in setup
                   if len(event) >= 13 and event[0] == 3 and event[2] == 0 and event[11] == 1]
        if not handles:
            raise RuntimeError('no successful ACL loopback connection event')
        payload = bytes(range(args.payload_size))
        packet = struct.pack('<HH', handles[0] | 0x2000, len(payload)) + payload
        received = []
        ready = threading.Event()

        def receive():
            buf, count = c.create_string_buffer(args.read_size), c.c_int()
            ready.set()
            before = time.monotonic()
            result = lib.libusb_bulk_transfer(handle, 0x82, buf, args.read_size,
                                              c.byref(count), args.timeout_ms)
            raw = buf.raw[:count.value]
            row = {'result': result, 'error': lib.libusb_error_name(result).decode(),
                   'transferred': count.value, 'hex': raw.hex(),
                   'elapsed_s': round(time.monotonic() - before, 6)}
            received.append(row)
            note('bulk_in', **row)

        if args.read_before_write:
            bulk_thread = threading.Thread(target=receive)
            bulk_thread.start()
            ready.wait(1)
            time.sleep(0.03)
        buf, count = c.create_string_buffer(packet), c.c_int()
        result = lib.libusb_bulk_transfer(handle, 2, buf, len(packet), c.byref(count), 1000)
        note('bulk_out', result=result, transferred=count.value, hex=packet.hex())
        if args.read_before_write:
            bulk_thread.join()
        else:
            receive()
        completed = events(0.3)
        result = {'loopback_handles': handles, 'bulk_in': received,
                  'payload_matches': bool(received and received[0]['hex'][8:] == payload.hex()),
                  'completion_events': [e.hex() for e in completed if e[0] == 0x13],
                  'version_events': [e.hex() for e in version_events]}
        note('result', **result)
        print(json.dumps(result))
    except BaseException as error:
        note('failure', error=repr(error))
        raise
    finally:
        if bulk_thread is not None and bulk_thread.is_alive():
            bulk_thread.join()
        if handle and claimed:
            try:
                command(0x0c03)
                events(0.2)
                note('cleanup', operation='HCI Reset', result='sent; replies retained')
            except Exception as error:
                note('cleanup', error=repr(error))
            note('cleanup', operation='release_interface', result=lib.libusb_release_interface(handle, 0))
        if handle and detached:
            note('cleanup', operation='attach_kernel_driver',
                 result=lib.libusb_attach_kernel_driver(handle, 0))
        if handle:
            lib.libusb_close(handle)
        if context:
            lib.libusb_exit(context)
        out.close()


if __name__ == '__main__':
    main()
