#ifndef _LED_A_INTERMITENTE_H    /* Guard against multiple inclusion */
#define _LED_A_INTERMITENTE_H

#include "../mcc_generated_files/pin_manager.h"
#include "../utils/utils.h"
#include "../mcc_generated_files/tmr2.h"
#include <xc.h>

#define LEDS_TIME_ON_ms     400
#define LEDS_TIME_OFF_ms    800

typedef enum {
    LEDS_BLINK_A_ON,
    LEDS_BLINK_A_OFF
} leds_blink_state_t;

void Timer_state_Initialize(void);

void LED_A_intermitente(void);


#endif /* _LED_A_INTERMITENTE_H */

/* *****************************************************************************
 End of File
 */
