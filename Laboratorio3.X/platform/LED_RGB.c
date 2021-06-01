#include "LED_RGB.h"
#include "LEDs_RGB/WS2812.h"

static ws2812_t LEDRing[AMOUNT_RGB_LED];

void RGB_setLedColor(uint8_t index, enum rgb_colors color) {
    switch (color) {
        case RGB_WHITE:
            LEDRing[index] = WHITE;
            break;
        case RGB_RED:
            LEDRing[index] = RED;
            break;
        case RGB_BLUE:
            LEDRing[index] = BLUE;
            break;
        case RGB_GREEN:
            LEDRing[index] = GREEN;
            break;
        case RGB_BLACK:
            LEDRing[index] = BLACK;
            break;
    }
}

void RGB_showLeds(uint8_t quantity) {
    if (quantity > AMOUNT_RGB_LED) {
        quantity = AMOUNT_RGB_LED;
    }
    WS2812_send(LEDRing, quantity);
}


/* *****************************************************************************
 End of File
 */
