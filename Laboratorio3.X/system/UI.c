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
#include <ctype.h>
#include <time.h>

#include "UI.h"
#include "../mcc_generated_files/usb/usb.h"
#include "../utils/USB.h"
#include "../utils/appTime.h"
#include "register.h"


const uint8_t textoBienvenida[] = "Laboratorio 3 - Equipo 10\n\t- Patricio Zarauz\n\t- Gastón Salustio\n\t- Sebastián Reynosa";
const uint8_t textoOpciones[] = "Seleccione una opcion:\n\n\t1. Fijar Fecha y Hora\n\t2. Encender o apagar LED especifico\n\t3. Consultar modificacion del ultimo LED:\n";
const uint8_t textoSegundo[] = "Segundo:\n";
const uint8_t textoMinuto[] = "Minuto:\n";
const uint8_t textoHora[] = "Hora:\n";
const uint8_t textoDia[] = "Dia:\n";
const uint8_t textoMes[] = "Mes:\n";
const uint8_t textoAno[] = "Año:\n";
const uint8_t textoLed[] = "LED: (1-8)\n";
const uint8_t textoColor[] = "Color: (0-4)\n";

static bool isValidYear(int yr) {
    return (yr >= 1900);
}

void UI_showMenu(void) {
    static ui_menu_states_t menuState = UI_MENU_STATE_INIT_SHOW;
    static uint8_t rxData[24];

    if (IsUSBConected()) {
        switch (menuState) {
            case( UI_MENU_STATE_INIT_SHOW):
                if (USBSend((uint8_t*) textoBienvenida)) {
                    memset(rxData, 0, sizeof (rxData));
                    menuState = UI_MENU_STATE_INIT_WAIT;
                }
                break;
            case( UI_MENU_STATE_INIT_WAIT):
                if (UI_waitForInput(rxData)) {
                    menuState = UI_MENU_STATE_OPTIONS_SHOW;
                }
                break;
            case( UI_MENU_STATE_OPTIONS_SHOW):
                if (USBSend((uint8_t*) textoOpciones)) {
                    memset(rxData, 0, sizeof (rxData));
                    menuState = UI_MENU_STATE_OPTIONS_WAIT;
                }
                break;
            case( UI_MENU_STATE_OPTIONS_WAIT):
                if (UI_waitForInput(rxData)) {
                    menuState = UI_MENU_STATE_OPTIONS_CHECK;
                }
                break;
            case( UI_MENU_STATE_OPTIONS_CHECK):
                if ((UI_checkValidOption(rxData, UI_OPTION_NUM, 1, 3))) {
                    menuState = UI_MENU_STATE_OPTIONS_CHECK + atoi(rxData);
                } else {
                    menuState = UI_MENU_STATE_OPTIONS_SHOW;
                }
                break;
            case( UI_MENU_STATE_SET_TIMEDATE):
                if (UI_setTimedate(rxData)) {
                    menuState = UI_MENU_STATE_OPTIONS_SHOW;
                }
                break;
            case( UI_MENU_STATE_SET_RGBLED):
                if (UI_setRGBLED(rxData)) {
                    menuState = UI_MENU_STATE_OPTIONS_SHOW;
                }
                break;
            case( UI_MENU_STATE_GET_LAST_UPDATE):
                if (USBSend((uint8_t*)getLatestUpdateTime())){
                    memset(rxData, 0, sizeof (rxData));
                    menuState = UI_MENU_STATE_OPTIONS_SHOW;
                }
                break;
        }
    } else {
        menuState = UI_MENU_STATE_INIT_SHOW;
    }
}

bool UI_waitForInput(uint8_t *dest) {
    uint8_t bytesReceived;

    bytesReceived = USBReceive(dest);
    if (bytesReceived > 0) {
        dest[bytesReceived] = '\0'; // End of String
        return true;
    }
    return false;
}

bool UI_checkValidOption(uint8_t *src, ui_options_t type, uint32_t min, uint32_t max) {
    uint32_t intValue;
    uint32_t i;

    switch (type) {
        case UI_OPTION_NUM:
            for (i = 0; i < strlen(src); i++) {
                if (isdigit(src[i]) == 0) {
                    return false;
                }
            }
            intValue = atoi(src);
            if ((intValue < min) || (intValue > max)) {
                return false;
            }
            break;

        case UI_OPTION_ALPHANUM:
            for (i = 0; i < strlen(src); i++) {
                if (isalnum(src[i]) == 0) {
                    return false;
                }
            }
            if (strlen(src) > max) {
                return false;
            }
            break;

        case UI_OPTION_ALPHA:
            for (i = 0; i < strlen(src); i++) {
                if (isalpha(src[i]) == 0) {
                    return false;
                }
            }
            if (strlen(src) > max) {
                return false;
            }
            break;
    }
    return true;
}

bool UI_setTimedate(uint8_t *src) {
    static ui_date_states_t dateState = UI_DATE_STATE_PROMT_SEC;
    static struct tm date;

    switch (dateState) {
        case UI_DATE_STATE_PROMT_SEC:
            if (USBSend((uint8_t*) textoSegundo)) {
                memset(src, 0, sizeof (src));
                dateState = UI_DATE_STATE_SEC_WAIT;
            }
            break;
        case UI_DATE_STATE_SEC_WAIT:
            if (UI_waitForInput(src)) {
                dateState = UI_DATE_STATE_SEC_CHECK;
            }
            break;
        case UI_DATE_STATE_SEC_CHECK:
            if (UI_checkValidOption(src, UI_OPTION_NUM, 0, 59)) {
                date.tm_sec = atoi(src);
                dateState = UI_DATE_STATE_PROMT_MIN;
            } else {
                dateState = UI_DATE_STATE_PROMT_SEC;
            }
            break;
        case UI_DATE_STATE_PROMT_MIN:
            if (USBSend((uint8_t*) textoMinuto)) {
                memset(src, 0, sizeof (src));
                dateState = UI_DATE_STATE_MIN_WAIT;
            }
            break;
        case UI_DATE_STATE_MIN_WAIT:
            if (UI_waitForInput(src)) {
                dateState = UI_DATE_STATE_MIN_CHECK;
            }
            break;
        case UI_DATE_STATE_MIN_CHECK:
            if (UI_checkValidOption(src, UI_OPTION_NUM, 0, 59)) {
                date.tm_min = atoi(src);
                dateState = UI_DATE_STATE_PROMT_HR;
            } else {
                dateState = UI_DATE_STATE_PROMT_MIN;
            }
            break;
        case UI_DATE_STATE_PROMT_HR:
            if (USBSend((uint8_t*) textoHora)) {
                memset(src, 0, sizeof (src));
                dateState = UI_DATE_STATE_HR_WAIT;
            }
            break;
        case UI_DATE_STATE_HR_WAIT:
            if (UI_waitForInput(src)) {
                dateState = UI_DATE_STATE_HR_CHECK;
            }
            break;
        case UI_DATE_STATE_HR_CHECK:
            if (UI_checkValidOption(src, UI_OPTION_NUM, 0, 23)) {
                date.tm_hour = atoi(src);
                dateState = UI_DATE_STATE_PROMT_DAY;
            } else {
                dateState = UI_DATE_STATE_PROMT_HR;
            }
            break;
        case UI_DATE_STATE_PROMT_DAY:
            if (USBSend((uint8_t*) textoHora)) {
                memset(src, 0, sizeof (src));
                dateState = UI_DATE_STATE_DAY_WAIT;
            }
            break;
        case UI_DATE_STATE_DAY_WAIT:
            if (UI_waitForInput(src)) {
                dateState = UI_DATE_STATE_DAY_CHECK;
            }
            break;
        case UI_DATE_STATE_DAY_CHECK:
            if (UI_checkValidOption(src, UI_OPTION_NUM, 1, 31)) {
                date.tm_mday = atoi(src);
                dateState = UI_DATE_STATE_PROMT_MON;
            } else {
                dateState = UI_DATE_STATE_PROMT_DAY;
            }
            break;
        case UI_DATE_STATE_PROMT_MON:
            if (USBSend((uint8_t*) textoHora)) {
                memset(src, 0, sizeof (src));
                dateState = UI_DATE_STATE_MON_WAIT;
            }
            break;
        case UI_DATE_STATE_MON_WAIT:
            if (UI_waitForInput(src)) {
                dateState = UI_DATE_STATE_MON_CHECK;
            }
            break;
        case UI_DATE_STATE_MON_CHECK:
            if (UI_checkValidOption(src, UI_OPTION_NUM, 1, 12)) {
                date.tm_mon = atoi(src) - 1;
                dateState = UI_DATE_STATE_PROMT_YR;
            } else {
                dateState = UI_DATE_STATE_PROMT_MON;
            }
            break;
        case UI_DATE_STATE_PROMT_YR:
            if (USBSend((uint8_t*) textoHora)) {
                memset(src, 0, sizeof (src));
                dateState = UI_DATE_STATE_YR_WAIT;
            }
            break;
        case UI_DATE_STATE_YR_WAIT:
            if (UI_waitForInput(src)) {
                dateState = UI_DATE_STATE_YR_CHECK;
            }
            break;
        case UI_DATE_STATE_YR_CHECK:
            if (isValidYear(atoi(src))) {
                date.tm_year = atoi(src) - 1900;
                dateState = UI_DATE_STATE_PROMT_SEC;
                setTime(date);
                return true;
            } else {
                dateState = UI_DATE_STATE_PROMT_YR;
            }
            break;
    }
    return false;
}

bool UI_setRGBLED(uint8_t *src) {
    static ui_rgb_led_states_t rgbLedState = UI_RGB_LED_STATE_PROMT_LED;

    switch (rgbLedState) {
        case UI_RGB_LED_STATE_PROMT_LED:
            if (USBSend((uint8_t*) textoLed)) {
                memset(src, 0, sizeof (src));
                rgbLedState = UI_RGB_LED_STATE_LED_WAIT;
            }
            break;
        case UI_RGB_LED_STATE_LED_WAIT:
            if (UI_waitForInput(src)) {
                rgbLedState = UI_RGB_LED_STATE_LED_CHECK;
            }
            break;
        case UI_RGB_LED_STATE_LED_CHECK:
            if (UI_checkValidOption(src, UI_OPTION_NUM, 1, 8)) {
                setLatestLED(src);
                rgbLedState = UI_RGB_LED_STATE_PROMT_COLOR;
            } else {
                rgbLedState = UI_RGB_LED_STATE_PROMT_LED;
            }
            break;
        case UI_RGB_LED_STATE_PROMT_COLOR:
            if (USBSend((uint8_t*) textoColor)) {
                memset(src, 0, sizeof (src));
                rgbLedState = UI_RGB_LED_STATE_COLOR_WAIT;
            }
            break;
        case UI_RGB_LED_STATE_COLOR_WAIT:
            if (UI_waitForInput(src)) {
                rgbLedState = UI_RGB_LED_STATE_COLOR_CHECK;
            }
            break;
        case UI_RGB_LED_STATE_COLOR_CHECK:
            if (UI_checkValidOption(src, UI_OPTION_NUM, 0, 4)) {
                setLatestColor(src);
                setRGBLEDAndTime();
                rgbLedState = UI_RGB_LED_STATE_PROMT_LED;
                return true;
            } else {
                rgbLedState = UI_RGB_LED_STATE_PROMT_COLOR;
            }
            break;
    }
    return false;
}
