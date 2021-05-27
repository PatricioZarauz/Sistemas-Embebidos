/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _USB_H    /* Guard against multiple inclusion */
#define _USB_H

#include <stdint.h>
#include <stdbool.h>


#define EXAMPLE_CONSTANT 0

void USBStatusUpdater(void);

bool IsUSBConected(void);

void setUSBConected(bool state);

uint8_t USBReceive( uint8_t *p_dest );
bool USBSend( uint8_t *p_src );


#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
