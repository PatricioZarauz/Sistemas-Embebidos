#include "../utils/utils.h"
#include "../mcc_generated_files/rtcc.h"

static ut_tmrDelay_t updateTimer;
static struct tm timeDate;
static time_t timeStamp;

void updateTime(void) {
    if (UT_delayms(&updateTimer, 1000) && RTCC_TimeGet(&timeDate)) {
        timeStamp = mktime(&timeDate);
    }
}

time_t getTimestamp(void) {
    return timeStamp;
}

void setTime(struct tm *newTimeDate){
    RTCC_TimeSet(newTimeDate);
}

/* *****************************************************************************
 End of File
 */
