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
    
    switch (LEDA_GetValue()) {
        case 1:
            if (UT_delayms(&timer, 400)) {
                UT_delayms(&timer, 800);
                LEDA_SetLow();
            }
            break;
        case 0:
            if (UT_delayms(&timer, 800)) {
                UT_delayms(&timer, 400);
                LEDA_SetHigh();
            }
            break;
        default:
            ;
    }

}


/* *****************************************************************************
 End of File
 */
