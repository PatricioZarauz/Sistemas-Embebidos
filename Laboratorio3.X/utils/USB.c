#include "USB.h"
#include "../mcc_generated_files/usb/usb_device.h"
#include "../mcc_generated_files/usb/usb.h"
#include <stdint.h>
#include <stdbool.h>

static uint8_t readBuffer[64];
static uint8_t writeBuffer[64];
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

uint8_t USBReceive(uint8_t *destination) {
    return getsUSBUSART(destination, 64);
}

bool USBSend(uint8_t *source) {
    if (USBUSARTIsTxTrfReady()) {
        putsUSBUSART(source);
        return true;
    } else {
        return false;
    }
}

/* *****************************************************************************
 End of File
 */
