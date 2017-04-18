#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/IOCFPlugIn.h>
#include <IOKit/usb/IOUSBLib.h>
#include <IOKit/usb/USBSpec.h>

using namespace std;

SInt32 usbVendor = 0x1c11;
SInt32 usbProduct = 0xb04d;

int main(int argc, const char * argv[]) {
    
    CFMutableDictionaryRef matchingDict = NULL;
    io_iterator_t iterator = 0;
    io_service_t usbRef;
    io_name_t deviceName;
    
    
    /* set up a matching dictionary for the class */
    matchingDict = IOServiceMatching("IOUSBHostDevice");
    CFDictionarySetValue(matchingDict, CFSTR(kUSBVendorName),
                         CFNumberCreate(kCFAllocatorDefault,
                                        kCFNumberSInt32Type, &usbVendor));
    CFDictionarySetValue(matchingDict, CFSTR(kUSBProductName),
                         CFNumberCreate(kCFAllocatorDefault,
                                        kCFNumberSInt32Type, &usbProduct));
    
    IOServiceGetMatchingServices(kIOMasterPortDefault,
                                 matchingDict, &iterator);

    
    
    while ((usbRef = IOIteratorNext(iterator))) {
        /* do something with device, eg. check properties */
        /* ... */
        IORegistryEntryGetName(usbRef, deviceName);
        cout << deviceName;
        cout << "\n";
        
        /* And free the reference taken before continuing to the next item */
        IOObjectRelease(usbRef);
    }
    
    
    IOObjectRelease(iterator);
    
    return 0;
}
