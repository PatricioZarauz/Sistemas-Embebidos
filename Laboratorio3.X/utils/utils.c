#include "utils.h"
#include "../mcc_generated_files/tmr2.h"

bool UT_delayms(ut_tmrDelay_t* p_timer, uint32_t p_ms) {
    switch (p_timer->state) {
        case UT_TMR_DELAY_INIT:
            p_timer->startValue = TMR2_SoftwareCounterGet();
            p_timer->state = UT_TMR_DELAY_WAIT;
            break;
        case UT_TMR_DELAY_WAIT:
            if (p_timer->startValue + p_ms <= TMR2_SoftwareCounterGet()) {
                p_timer->state = UT_TMR_DELAY_INIT;
                return true;
            }
            break;
        default:
            p_timer->state = UT_TMR_DELAY_INIT;
    }
    return false;
}
