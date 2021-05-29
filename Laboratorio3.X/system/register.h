#ifndef _REGISTER_H    /* Guard against multiple inclusion */
#define _REGISTER_H

#include <stdint.h>
#include <stdbool.h>

//NO VA DESDE ACA
#define EVENT_MAX               8
#define EVENT_PARAM_ON          1
#define EVENT_PARAM_OFF         0
#define EVENT_PARAM_NOT_CONFIG  0xFF
//HASTA ACA

typedef struct {
    uint8_t led;
    uint8_t color;
    uint32_t time;
} app_register_t;

void setLatestLED(uint8_t latestLed);

void setLatestColor(uint8_t latestColor);

void setRGBLEDAndTime(void);

uint8_t getLatestUpdateTime(void);

#endif /* __REGISTER_H */

/* *****************************************************************************
 End of File
 */
