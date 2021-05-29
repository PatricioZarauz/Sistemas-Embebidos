#ifndef _APP_TIME_H    /* Guard against multiple inclusion */
#define _APP_TIME_H

#include <time.h>

void setTime(struct tm newTimeDate);
void updateTime(void);
time_t getCurrentTime(void);

#endif /* _APP_TIME_H */

/* *****************************************************************************
 End of File
 */
