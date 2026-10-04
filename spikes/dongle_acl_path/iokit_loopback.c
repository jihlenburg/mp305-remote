/* Direct IOUSBLib local loopback on ASUS 0b05:1d70. No libusb or radio.
 * Build: clang -Wno-deprecated-declarations -framework IOKit
 *   -framework CoreFoundation iokit_loopback.c -o /tmp/mp305-iokit-loopback
 * Standard output is a JSONL capture; use exclusive creation in the runner.
 */
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOCFPlugIn.h>
#include <IOKit/usb/IOUSBLib.h>
#include <mach/mach_error.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <time.h>

static IOUSBDeviceInterface320 **dev;
static IOUSBInterfaceInterface300 **intf;
static UInt8 event_pipe, in_pipe, out_pipe;
static int dev_open, intf_open;
static CFRunLoopSourceRef source;
static struct { int done; IOReturn status; UInt32 size; } completion;

static void report(const char *operation, IOReturn status) {
    printf("{\"kind\":\"status\",\"operation\":\"%s\",\"status\":\"0x%08x\",\"description\":\"%s\"}\n",
           operation, status, mach_error_string(status));
    fflush(stdout);
}

static void bytes(const char *kind, const uint8_t *data, unsigned size) {
    printf("{\"kind\":\"%s\",\"size\":%u,\"hex\":\"", kind, size);
    for (unsigned i = 0; i < size; ++i) printf("%02x", data[i]);
    puts("\"}"); fflush(stdout);
}

static void callback(void *refcon, IOReturn result, void *argument) {
    (void)refcon;
    completion.done = 1;
    completion.status = result;
    completion.size = (UInt32)(uintptr_t)argument;
}

static int event(uint8_t *buffer) {
    memset(&completion, 0, sizeof(completion));
    IOReturn r = (*intf)->ReadPipeAsync(intf, event_pipe, buffer, 256, callback, NULL);
    if (r) { report("event_submit", r); return -1; }
    CFAbsoluteTime end = CFAbsoluteTimeGetCurrent() + 1.0;
    while (!completion.done && CFAbsoluteTimeGetCurrent() < end)
        CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.05, true);
    if (!completion.done) {
        report("event_abort", (*intf)->AbortPipe(intf, event_pipe));
        CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.1, false);
    }
    if (!completion.done || completion.status) {
        report("event_completion", completion.done ? completion.status : kIOReturnTimeout);
        return -1;
    }
    bytes("event", buffer, completion.size);
    return (int)completion.size;
}

static int command(uint16_t opcode, int parameter) {
    uint8_t packet[4] = {opcode & 255, opcode >> 8, parameter < 0 ? 0 : 1, parameter & 255};
    IOUSBDevRequestTO request = {0};
    request.bmRequestType = 0x20;
    request.wLength = parameter < 0 ? 3 : 4;
    request.pData = packet;
    request.noDataTimeout = request.completionTimeout = 1000;
    IOReturn r = (*dev)->DeviceRequestTO(dev, &request);
    bytes("command", packet, request.wLength);
    report("command_write", r);
    return r ? -1 : 0;
}

static int initialize(void) {
    CFMutableDictionaryRef match = IOServiceMatching(kIOUSBDeviceClassName);
    int vid = 0x0b05, pid = 0x1d70;
    CFNumberRef v = CFNumberCreate(NULL, kCFNumberIntType, &vid);
    CFNumberRef p = CFNumberCreate(NULL, kCFNumberIntType, &pid);
    CFDictionarySetValue(match, CFSTR(kUSBVendorID), v);
    CFDictionarySetValue(match, CFSTR(kUSBProductID), p);
    CFRelease(v); CFRelease(p);
    io_service_t service = IOServiceGetMatchingService(kIOMainPortDefault, match);
    if (!service) { puts("{\"kind\":\"failure\",\"reason\":\"device absent\"}"); return -1; }
    IOCFPlugInInterface **plugin = NULL;
    SInt32 score;
    IOReturn r = IOCreatePlugInInterfaceForService(service, kIOUSBDeviceUserClientTypeID,
                                                  kIOCFPlugInInterfaceID, &plugin, &score);
    IOObjectRelease(service);
    report("device_plugin", r);
    if (r || !plugin) return -1;
    HRESULT h = (*plugin)->QueryInterface(plugin, CFUUIDGetUUIDBytes(kIOUSBDeviceInterfaceID320), (LPVOID *)&dev);
    (*plugin)->Release(plugin);
    if (h || !dev) return -1;
    r = (*dev)->USBDeviceOpen(dev); report("device_open", r);
    if (r) return -1;
    dev_open = 1;
    UInt8 config;
    r = (*dev)->GetConfiguration(dev, &config); report("get_configuration", r);
    if (r) return -1;
    if (!config) { r = (*dev)->SetConfiguration(dev, 1); report("configure", r); if (r) return -1; }
    IOUSBFindInterfaceRequest request = {kIOUSBFindInterfaceDontCare,kIOUSBFindInterfaceDontCare,
                                        kIOUSBFindInterfaceDontCare,kIOUSBFindInterfaceDontCare};
    io_iterator_t iterator;
    r = (*dev)->CreateInterfaceIterator(dev, &request, &iterator);
    if (r) return -1;
    while ((service = IOIteratorNext(iterator))) {
        r = IOCreatePlugInInterfaceForService(service, kIOUSBInterfaceUserClientTypeID,
                                             kIOCFPlugInInterfaceID, &plugin, &score);
        IOObjectRelease(service);
        if (r || !plugin) continue;
        h = (*plugin)->QueryInterface(plugin, CFUUIDGetUUIDBytes(kIOUSBInterfaceInterfaceID300), (LPVOID *)&intf);
        (*plugin)->Release(plugin);
        if (h || !intf) continue;
        UInt8 number;
        if (!(*intf)->GetInterfaceNumber(intf, &number) && number == 0) break;
        (*intf)->Release(intf); intf = NULL;
    }
    IOObjectRelease(iterator);
    if (!intf) return -1;
    r = (*intf)->USBInterfaceOpen(intf); report("interface_open", r);
    if (r) return -1;
    intf_open = 1;
    UInt8 count;
    if ((*intf)->GetNumEndpoints(intf, &count)) return -1;
    for (UInt8 pipe = 1; pipe <= count; ++pipe) {
        UInt8 direction, number, type, interval;
        UInt16 max_packet;
        r = (*intf)->GetPipeProperties(intf, pipe, &direction, &number, &type, &max_packet, &interval);
        if (r) return -1;
        printf("{\"kind\":\"pipe\",\"pipe\":%u,\"direction\":%u,\"endpoint\":%u,\"type\":%u,\"max_packet\":%u,\"interval\":%u}\n",
               pipe,direction,number,type,max_packet,interval);
        if (direction == kUSBIn && type == kUSBInterrupt) event_pipe = pipe;
        if (direction == kUSBIn && type == kUSBBulk) in_pipe = pipe;
        if (direction == kUSBOut && type == kUSBBulk) out_pipe = pipe;
        report("pipe_status", (*intf)->GetPipeStatus(intf, pipe));
    }
    if (!event_pipe || !in_pipe || !out_pipe) return -1;
    r = (*intf)->CreateInterfaceAsyncEventSource(intf, &source);
    report("event_source", r);
    if (r) return -1;
    CFRunLoopAddSource(CFRunLoopGetCurrent(), source, kCFRunLoopDefaultMode);
    return 0;
}

int main(void) {
    struct utsname host;
    uname(&host);
    printf("{\"kind\":\"meta\",\"script\":\"iokit_loopback.c\",\"epoch\":%ld,\"kernel\":\"%s\",\"architecture\":\"%s\",\"adapter\":\"ASUS 0b05:1d70\",\"transport\":\"IOUSBLib directly, no libusb\",\"sent\":\"HCI reset/version/local loopback and one 20-byte ACL packet; no radio or supply commands\"}\n",time(NULL),host.release,host.machine);
    int exit_code = 1;
    uint8_t buffer[256] = {0};
    if (initialize()) goto done;
    if (command(0x0c03, -1) || event(buffer) < 0) goto done;
    if (command(0x1001, -1) || event(buffer) < 0) goto done;
    if (command(0x1802, 1)) goto done;
    uint16_t handle = 0;
    for (int i = 0; i < 8; ++i) {
        int size = event(buffer);
        if (size < 0) goto done;
        if (size >= 13 && buffer[0] == 3 && buffer[2] == 0 && buffer[11] == 1)
            handle = buffer[3] | (buffer[4] << 8);
        if (size >= 6 && buffer[0] == 0x0e) break;
    }
    if (!handle) goto done;
    uint8_t packet[20] = {handle & 255,(handle >> 8) | 0x20,16,0};
    for (int i = 0; i < 16; ++i) packet[i + 4] = i;
    IOReturn r = (*intf)->WritePipeTO(intf,out_pipe,packet,sizeof(packet),1000,1000);
    report("bulk_out", r); bytes("bulk_out", packet, sizeof(packet));
    if (r) goto done;
    UInt32 size = 64;
    memset(buffer, 0, sizeof(buffer));
    r = (*intf)->ReadPipeTO(intf,in_pipe,buffer,&size,2000,2000);
    report("bulk_in",r);
    /* IOUSBLib does not define size or buffer contents when ReadPipeTO fails. */
    if (!r) bytes("bulk_in",buffer,size);
    printf("{\"kind\":\"result\",\"bulk_status\":\"0x%08x\",\"valid_bytes\":%u,\"payload_matches\":%s}\n",
           r,r ? 0 : size,(!r && size == sizeof(packet) && !memcmp(buffer+4,packet+4,16)) ? "true" : "false");
    report("bulk_in_pipe_status_after", (*intf)->GetPipeStatus(intf,in_pipe));
    event(buffer);
    exit_code = 0;
done:
    if (intf_open) {
        command(0x0c03,-1);
        if (source) event(buffer);
        report("interface_close", (*intf)->USBInterfaceClose(intf));
    }
    if (source) { CFRunLoopRemoveSource(CFRunLoopGetCurrent(),source,kCFRunLoopDefaultMode); CFRelease(source); }
    if (intf) (*intf)->Release(intf);
    if (dev_open) report("device_close", (*dev)->USBDeviceClose(dev));
    if (dev) (*dev)->Release(dev);
    return exit_code;
}
