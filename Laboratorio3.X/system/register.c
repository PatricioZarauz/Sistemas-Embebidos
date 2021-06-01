#include <time.h>
#include "register.h"
#include "../platform/LED_RGB.h"
#include "../utils/USB.h"

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
    registro.time = getTimestamp();
}

uint8_t* getLatestUpdateTime(void) {
    static uint8_t latestUpdateTime[24];

    struct tm *data;
    time_t time = registro.time;
    data = localtime(&time);
    
    uint8_t bytes = strftime(latestUpdateTime, 24, "%c", data);
    
    latestUpdateTime[bytes] = '\n';
    latestUpdateTime[bytes+1] = '\0';

    return latestUpdateTime;
}

/* *****************************************************************************
 End of File
 */
