#ifndef _UI_H    /* Guard against multiple inclusion */
#define _UI_H

typedef enum {
    UI_MENU_STATE_INIT_SHOW,
    UI_MENU_STATE_INIT_WAIT,
    UI_MENU_STATE_OPTIONS_SHOW,
    UI_MENU_STATE_OPTIONS_WAIT,
    UI_MENU_STATE_OPTIONS_CHECK,
    UI_MENU_STATE_SET_TIMEDATE,
    UI_MENU_STATE_SET_RGBLED,
    UI_MENU_STATE_GET_LAST_UPDATE,
} ui_menu_states_t;

typedef enum {
    UI_DATE_STATE_PROMT_SEC,
    UI_DATE_STATE_SEC_WAIT,
    UI_DATE_STATE_SEC_CHECK,
    UI_DATE_STATE_PROMT_MIN,
    UI_DATE_STATE_MIN_WAIT,
    UI_DATE_STATE_MIN_CHECK,
    UI_DATE_STATE_PROMT_HR,
    UI_DATE_STATE_HR_WAIT,
    UI_DATE_STATE_HR_CHECK,
    UI_DATE_STATE_PROMT_DAY,
    UI_DATE_STATE_DAY_WAIT,
    UI_DATE_STATE_DAY_CHECK,
    UI_DATE_STATE_PROMT_MON,
    UI_DATE_STATE_MON_WAIT,
    UI_DATE_STATE_MON_CHECK,
    UI_DATE_STATE_PROMT_YR,
    UI_DATE_STATE_YR_WAIT,
    UI_DATE_STATE_YR_CHECK,
} ui_date_states_t;

typedef enum {
    UI_RGB_LED_STATE_PROMT_LED,
    UI_RGB_LED_STATE_LED_WAIT,
    UI_RGB_LED_STATE_LED_CHECK,
    UI_RGB_LED_STATE_PROMT_COLOR,
    UI_RGB_LED_STATE_COLOR_WAIT,
    UI_RGB_LED_STATE_COLOR_CHECK,
} ui_rgb_led_states_t;




void UI_showMenu(void);

bool UI_waitForInput(uint8_t *dest);

bool UI_checkValidOption(uint8_t *src, uint32_t min, uint32_t max);

bool UI_setTimedate(uint8_t *src);

bool UI_setRGBLED(uint8_t *src);

#endif /* _UI_H */

/* *****************************************************************************
 End of File
 */
