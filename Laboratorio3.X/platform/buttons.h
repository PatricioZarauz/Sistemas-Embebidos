#ifndef _BUTTONS_H    /* Guard against multiple inclusion */
#define _BUTTONS_H

enum buttons {
    BTN1,
    BTN2
};

static void SetButton(enum buttons btn);

void SetBTN1(void);
void SetBTN2(void);
bool ReadButton(enum buttons btn);
void ResetButton(enum buttons btn);

#endif /* _BUTTONS_H */

/* *****************************************************************************
 End of File
 */
