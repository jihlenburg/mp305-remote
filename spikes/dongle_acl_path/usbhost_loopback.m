/* Local loopback using the modern IOUSBHost framework, without libusb or
 * IOUSBLib. Only ASUS 0b05:1d70 is opened. No radio or supply commands.
 * clang -fobjc-arc -framework Foundation -framework IOKit -framework IOUSBHost
 *   usbhost_loopback.m -o /tmp/mp305-usbhost-loopback
 * Optional argument: --idle60 (restore the original idle timeout on exit).
 */
#import <Foundation/Foundation.h>
#import <IOUSBHost/IOUSBHost.h>
#import <IOKit/IOKitLib.h>
#include <sys/utsname.h>

static IOUSBHostDevice *device;
static IOUSBHostInterface *interface;
static IOUSBHostPipe *events, *input, *output;
static BOOL changedIdle;
static NSTimeInterval oldIdle;

static void record(NSDictionary *row) {
    NSData *json = [NSJSONSerialization dataWithJSONObject:row options:0 error:nil];
    fwrite(json.bytes, 1, json.length, stdout); putchar('\n'); fflush(stdout);
}

static NSString *hex(NSData *data) {
    NSMutableString *text = [NSMutableString string];
    const uint8_t *bytes = data.bytes;
    for (NSUInteger i = 0; i < data.length; ++i) [text appendFormat:@"%02x", bytes[i]];
    return text;
}

static BOOL outcome(NSString *operation, BOOL ok, NSError *error) {
    record(@{@"kind":@"status",@"operation":operation,@"ok":@(ok),
             @"code":[NSString stringWithFormat:@"0x%08x",(unsigned)error.code],
             @"error":error ? error.description : @""});
    return ok;
}

static NSData *event(void) {
    NSMutableData *data = [NSMutableData dataWithLength:256];
    dispatch_semaphore_t sem = dispatch_semaphore_create(0);
    __block IOReturn status = kIOReturnTimeout;
    __block NSUInteger size = 0;
    NSError *error = nil;
    BOOL ok = [events enqueueIORequestWithData:data completionTimeout:0 error:&error
                            completionHandler:^(IOReturn value, NSUInteger bytes) {
        status = value; size = bytes; dispatch_semaphore_signal(sem);
    }];
    if (!outcome(@"event_submit",ok,error)) return nil;
    if (dispatch_semaphore_wait(sem,dispatch_time(DISPATCH_TIME_NOW,NSEC_PER_SEC))) {
        [events abortWithError:&error];
        dispatch_semaphore_wait(sem,dispatch_time(DISPATCH_TIME_NOW,NSEC_PER_SEC));
    }
    if (size > data.length) return nil;
    NSData *received = [data subdataWithRange:NSMakeRange(0,size)];
    record(@{@"kind":@"event",@"status":[NSString stringWithFormat:@"0x%08x",status],
             @"bytes":@(size),@"hex":hex(received)});
    return status ? nil : received;
}

static BOOL command(uint16_t opcode, int parameter) {
    uint8_t packet[] = {opcode & 255,opcode >> 8,parameter < 0 ? 0 : 1,parameter & 255};
    NSMutableData *data = [NSMutableData dataWithBytes:packet length:parameter < 0 ? 3 : 4];
    IOUSBDeviceRequest request = {0};
    request.bmRequestType = 0x20; request.wLength = data.length;
    NSUInteger bytes = 0;
    NSError *error = nil;
    BOOL ok = [device sendDeviceRequest:request data:data bytesTransferred:&bytes completionTimeout:1 error:&error];
    record(@{@"kind":@"command",@"hex":hex(data),@"bytes":@(bytes)});
    return outcome(@"command",ok,error);
}

static BOOL run(BOOL idle60) {
    NSError *error = nil;
    CFMutableDictionaryRef match = [IOUSBHostDevice createMatchingDictionaryWithVendorID:@0x0b05
        productID:@0x1d70 bcdDevice:nil deviceClass:nil deviceSubclass:nil deviceProtocol:nil speed:nil productIDArray:nil];
    io_service_t service = IOServiceGetMatchingService(kIOMainPortDefault, match);
    if (!service) return outcome(@"device_absent",NO,nil);
    device = [[IOUSBHostDevice alloc] initWithIOService:service options:0 queue:nil error:&error interestHandler:nil];
    IOObjectRelease(service);
    if (!outcome(@"device_open",device != nil,error)) return NO;
    if (!device.configurationDescriptor) {
        BOOL ok = [device configureWithValue:1 matchInterfaces:YES error:&error];
        if (!outcome(@"configure",ok,error)) return NO;
    }
    for (int attempt = 0; attempt < 20; ++attempt) {
        match = [IOUSBHostInterface createMatchingDictionaryWithVendorID:@0x0b05
            productID:@0x1d70 bcdDevice:nil interfaceNumber:@0 configurationValue:@1
            interfaceClass:nil interfaceSubclass:nil interfaceProtocol:nil speed:nil productIDArray:nil];
        service = IOServiceGetMatchingService(kIOMainPortDefault,match);
        if (service) break;
        [NSThread sleepForTimeInterval:0.05];
    }
    if (!service) return outcome(@"interface_absent",NO,nil);
    error = nil;
    interface = [[IOUSBHostInterface alloc] initWithIOService:service options:0 queue:nil error:&error interestHandler:nil];
    IOObjectRelease(service);
    if (!outcome(@"interface_open",interface != nil,error)) return NO;
    oldIdle = interface.idleTimeout;
    record(@{@"kind":@"idle_timeout",@"seconds":@(oldIdle)});
    if (idle60) {
        BOOL ok = [interface setIdleTimeout:60 error:&error];
        if (!outcome(@"idle_timeout_60",ok,error)) return NO;
        changedIdle = YES;
    }
    events = [interface copyPipeWithAddress:0x81 error:&error];
    input = [interface copyPipeWithAddress:0x82 error:&error];
    output = [interface copyPipeWithAddress:0x02 error:&error];
    if (!outcome(@"pipes",events && input && output,error)) return NO;
    if (!command(0x0c03,-1) || !event()) return NO;
    if (!command(0x1001,-1) || !event()) return NO;
    if (!command(0x1802,1)) return NO;
    uint16_t handle = 0;
    for (int i = 0; i < 8; ++i) {
        NSData *data = event();
        if (!data) return NO;
        const uint8_t *bytes = data.bytes;
        if (data.length >= 13 && bytes[0] == 3 && bytes[2] == 0 && bytes[11] == 1)
            handle = bytes[3] | (bytes[4] << 8);
        if (data.length >= 6 && bytes[0] == 0x0e) break;
    }
    if (!handle) return outcome(@"loopback_handle_absent",NO,nil);
    uint8_t packet[20] = {handle & 255,(handle >> 8) | 0x20,16,0};
    for (int i = 0; i < 16; ++i) packet[i+4] = i;
    NSMutableData *data = [NSMutableData dataWithBytes:packet length:sizeof(packet)];
    NSUInteger size = 0;
    error = nil;
    BOOL ok = [output sendIORequestWithData:data bytesTransferred:&size completionTimeout:1 error:&error];
    record(@{@"kind":@"bulk_out",@"bytes":@(size),@"hex":hex(data)});
    if (!outcome(@"bulk_out",ok,error)) return NO;
    data = [NSMutableData dataWithLength:64]; size = 0; error = nil;
    ok = [input sendIORequestWithData:data bytesTransferred:&size completionTimeout:2 error:&error];
    outcome(@"bulk_in",ok,error);
    if (size > data.length) return NO;
    NSData *received = [data subdataWithRange:NSMakeRange(0,size)];
    record(@{@"kind":@"result",@"bytes":@(size),@"hex":hex(received),
             @"payload_matches":@(ok && size == sizeof(packet) && !memcmp((const uint8_t *)data.bytes+4,packet+4,16))});
    event();
    return YES;
}

int main(int argc, char **argv) {
    @autoreleasepool {
        struct utsname host; uname(&host);
        BOOL idle60 = argc == 2 && !strcmp(argv[1],"--idle60");
        record(@{@"kind":@"meta",@"script":@"usbhost_loopback.m",@"date":[NSDate.date description],
                 @"kernel":@(host.release),@"adapter":@"ASUS 0b05:1d70",
                 @"transport":@"modern IOUSBHost framework",@"idle60":@(idle60),
                 @"sent":@"HCI reset/version/local loopback and 20-byte ACL; no radio or supply commands"});
        BOOL result = run(idle60);
        if (device && events) { command(0x0c03,-1); event(); }
        if (changedIdle) { NSError *error = nil; BOOL ok = [interface setIdleTimeout:oldIdle error:&error]; outcome(@"restore_idle",ok,error); }
        [interface destroy]; [device destroy];
        return result ? 0 : 1;
    }
}
