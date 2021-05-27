/*
    (c) 2017 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

/*
    MCC USB CDC Demo Usage:
 
    Call the MCC_USB_CDC_DemoTasks() function from your main loop.
    It will read data sent from the host and echo it back +1.  If you open
    up a terminal window and type 'a' then 'b' will be echoed back.
 */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "../mcc_generated_files/usb/usb.h"

static uint8_t readBuffer[64];
static uint8_t writeBuffer[64];

void writeToBuffer(char* text) {
    if (USBGetDeviceState() < CONFIGURED_STATE) {
        return;
    }

    if (USBIsDeviceSuspended() == true) {
        return;
    }

    if (USBUSARTIsTxTrfReady() == true) {
        putUSBUSART(text, strlen(text));
    }
    CDCTxService();
}

int8_t readInput() {
    if (USBGetDeviceState() < CONFIGURED_STATE) {
        return;
    }

    if (USBIsDeviceSuspended() == true) {
        return;
    }

    if (USBUSARTIsTxTrfReady() == true) {
        uint8_t i;
        uint8_t numBytesRead;

        numBytesRead = getsUSBUSART(readBuffer, 1);
        switch (readBuffer[0]) {
            case 0x30:
            case 0x31:
            case 0x32:
            case 0x33:
            case 0x34:
            case 0x35:
            case 0x36:
            case 0x37:
            case 0x38:
            case 0x39:
                return readBuffer[0];
                break;

            default:
                return -1;
                break;
        }
    }

    CDCTxService();
}

void app(void) {
    writeToBuffer("Seleccione una opcion:\n\n");
    writeToBuffer("\t1. Fijar Fecha y Hora\n");
    writeToBuffer("\t2. Encender o apagar LED especifico\n");
    writeToBuffer("\t3. Consultar modificacion del ultimo LED:\n");

    while (1) {
        switch (readInput()) {
            case 1:
                writeToBuffer("Seleccionaste la opcion 1 \n");
                break;
            case 2:
                writeToBuffer("Seleccionaste la opcion 2 \n");
                break;
            case 3:
                writeToBuffer("Seleccionaste la opcion 3 \n");
                break;
            case -1:
                writeToBuffer("Ingrese un valor valido \n");
                break;
            default:
                writeToBuffer("Ingrese una opcion valida \n");
        }
    }

}
