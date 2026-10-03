"""Spike: the Mac's built-in Bluetooth advertises a small GATT service for a
while, as a second peer for host_hci.py. It prints every read request that
reaches its characteristic, and answers it.

    uv run --no-project --with pyobjc-framework-CoreBluetooth python mac_peripheral.py 45

The argument is the time to advertise, in seconds.
"""
import sys, time
import CoreBluetooth as CB
from Foundation import NSData, NSDate, NSObject, NSRunLoop

SERVICE = CB.CBUUID.UUIDWithString_("5A3D0001-6D70-3330-3562-646961670001")
CHAR = CB.CBUUID.UUIDWithString_("5A3D0002-6D70-3330-3562-646961670001")

class Delegate(NSObject):
    def peripheralManagerDidUpdateState_(self, pm):
        print("state", pm.state(), flush=True)
        if pm.state() == 5:
            # No stored value: every read is passed to didReceiveReadRequest,
            # so this script sees whether a request arrived.
            ch = CB.CBMutableCharacteristic.alloc().initWithType_properties_value_permissions_(
                CHAR, CB.CBCharacteristicPropertyRead, None, CB.CBAttributePermissionsReadable)
            svc = CB.CBMutableService.alloc().initWithType_primary_(SERVICE, True)
            svc.setCharacteristics_([ch])
            pm.addService_(svc)

    def peripheralManager_didAddService_error_(self, pm, svc, err):
        print("service added, error:", err, flush=True)
        pm.startAdvertising_({CB.CBAdvertisementDataLocalNameKey: "mp305diag",
                              CB.CBAdvertisementDataServiceUUIDsKey: [SERVICE]})

    def peripheralManagerDidStartAdvertising_error_(self, pm, err):
        print("advertising, error:", err, flush=True)

    def peripheralManager_didReceiveReadRequest_(self, pm, request):
        print(time.strftime("%H:%M:%S"), "read request received, answering with 'hello'", flush=True)
        request.setValue_(NSData.dataWithBytes_length_(b"hello", 5))
        pm.respondToRequest_withResult_(request, 0)

d = Delegate.alloc().init()
pm = CB.CBPeripheralManager.alloc().initWithDelegate_queue_options_(d, None, None)
end = time.time() + float(sys.argv[1]) if len(sys.argv) > 1 else time.time() + 40
while time.time() < end:
    NSRunLoop.currentRunLoop().runUntilDate_(NSDate.dateWithTimeIntervalSinceNow_(0.2))
pm.stopAdvertising()
print("stopped", flush=True)
