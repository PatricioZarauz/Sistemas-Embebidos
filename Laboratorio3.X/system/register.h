#ifndef _REGISTER_H    /* Guard against multiple inclusion */
#define _REGISTER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t led;
    uint8_t color;
    uint32_t time;
} app_register_t;

void setLatestLED(uint8_t latestLed);

void setLatestColor(uint8_t latestColor);

void setRGBLEDAndTime(void);

uint8_t* getLatestUpdateTime(void);

#endif /* __REGISTER_H */

/* *****************************************************************************
 End of File
 */
