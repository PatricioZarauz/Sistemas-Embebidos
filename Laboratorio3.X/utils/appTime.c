#include <time.h>
#include "utils.h"
#include "../mcc_generated_files/rtcc.h"

static ut_tmrDelay_t updateTMR;
static struct tm timeDate;
static time_t timeStamp;

void updateTime(void) {
    if (UT_delayms(&updateTMR, 1000) && RTCC_TimeGet(&timeDate)) {
        timeStamp = mktime(&timeDate);
    }
}

time_t getCurrentTime(void) {
    return timeStamp;
}

void setTime(struct tm newTimeDate){
    timeDate = newTimeDate;
}

/* *****************************************************************************
 End of File
 */
