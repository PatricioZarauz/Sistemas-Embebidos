#ifndef _LED_RGB_H    /* Guard against multiple inclusion */
#define _LED_RGB_H

#include <stdint.h>

#define AMOUNT_RGB_LED    8 

enum rgb_colors {
    RGB_WHITE,
    RGB_RED,
    RGB_BLUE,
    RGB_GREEN,
    RGB_BLACK
};


void RGB_setLedColor(uint8_t index, enum rgb_colors color);

void RGB_showLeds(uint8_t quantity);


#endif /* _LED_RGB_H */

/* *****************************************************************************
 End of File
 */
