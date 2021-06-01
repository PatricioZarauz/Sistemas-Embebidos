#include "USB.h"
#include "../mcc_generated_files/usb/usb_device.h"
#include "../mcc_generated_files/usb/usb.h"
#include <stdint.h>
#include <stdbool.h>

static bool USBConected;

void USBStatusUpdater(void) {
    if ((USBGetDeviceState() >= CONFIGURED_STATE) && !USBIsDeviceSuspended()) {
        CDCTxService();
        USBConected = true;
    } else {
        USBConected = false;
    }
}

bool IsUSBConected(void) {
    return USBConected;
}

void setUSBConected(bool state) {
    USBConected = state;
}

uint8_t USBReceive(uint8_t *dest) {
    return getsUSBUSART(dest, 64);
}

bool USBSend(uint8_t *src) {
    if (USBUSARTIsTxTrfReady()) {
        putsUSBUSART(src);
        return true;
    } else {
        return false;
    }
}

/* *****************************************************************************
 End of File
 */
