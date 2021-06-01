#include "LED_A_intermitente.h"
#include "../utils/utils.h"
#include "../mcc_generated_files/pin_manager.h"

ut_tmrDelay_t timer;


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

void Timer_state_Initialize(void) {
    timer.state = UT_TMR_DELAY_INIT;
}


void LED_A_intermitente() {
    static leds_blink_state_t leds_blinkState=LEDS_BLINK_A_ON;

    switch(leds_blinkState){
        case LEDS_BLINK_A_ON:
            LEDA_SetHigh( );
            if(UT_delayms( &timer, LEDS_TIME_ON_ms )){
                leds_blinkState=LEDS_BLINK_A_OFF;
            }
            break;

        case LEDS_BLINK_A_OFF:
            LEDA_SetLow( );
            if(UT_delayms( &timer, LEDS_TIME_OFF_ms )){
                leds_blinkState=LEDS_BLINK_A_ON;
            }
            break;
    }
}


/* *****************************************************************************
 End of File
 */
