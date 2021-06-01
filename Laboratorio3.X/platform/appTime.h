#ifndef _APP_TIME_H    /* Guard against multiple inclusion */
#define _APP_TIME_H


#include <time.h>


void APP_updateTime(void);

time_t APP_getTimestamp(void);

void setTime(struct tm *newTimeDate);

#endif /* _APP_TIME_H */

/* *****************************************************************************
 End of File
 */
