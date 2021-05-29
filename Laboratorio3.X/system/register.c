#include "../utils/appTime.h"
#include "register.h"
#include "../platform/LED_RGB.h"

static app_register_t registro;

void setLatestLED(uint8_t latestLed) {
    registro.led = latestLed;
}

void setLatestColor(uint8_t latestColor) {
    registro.color = latestColor;
}

void setRGBLEDAndTime(void) {
    RGB_setLedColor(registro.led, registro.color);
    RGB_showLeds(AMOUNT_RGB_LED);
    registro.time = getCurrentTime();
}

uint8_t getLatestUpdateTime(void) {

    uint8_t latestUpdateTime[] = "No se ha actualizado ningun LED aun\n";
    struct tm *data;
    time(&registro.time);
    data = gmtime(&registro.time);
    if (data != NULL) {
        strftime((uint8_t*) latestUpdateTime, 24, "%c", &data);
    }

    return latestUpdateTime;

}

/* *****************************************************************************
 End of File
 */
