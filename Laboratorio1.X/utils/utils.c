#include "utils.h"
#include "../mcc_generated_files/tmr2.h"

void UT_delayms(int n) {
    TMR2_SoftwareCounterClear();
    TMR2_SetInterruptHandler(TMR2_Start);
    TMR2_Start();
    while (TMR2_SoftwareCounterGet() < n){
        ;
    }
    TMR2_Stop();
}
