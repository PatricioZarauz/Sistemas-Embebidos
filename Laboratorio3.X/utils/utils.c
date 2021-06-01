#include "utils.h"

static volatile uint32_t ut_tmrCount=0;


void UT_incrementCounter( void ){
    ut_tmrCount++;
}

void UT_delayReset( ut_tmrDelay_t* p_timer ){
    p_timer->state=UT_TMR_DELAY_INIT;
}

bool UT_delayms( ut_tmrDelay_t* p_timer, uint32_t p_ms ){
    switch(p_timer->state){
        case UT_TMR_DELAY_INIT:
            p_timer->startValue=ut_tmrCount;
            p_timer->state=UT_TMR_DELAY_WAIT;
            break;

        case UT_TMR_DELAY_WAIT:
            if(ut_tmrCount>=p_timer->startValue+p_ms){
                p_timer->state=UT_TMR_DELAY_INIT;
                return true;
            }
            break;
    }
    return false;
}
