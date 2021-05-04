#include <stdbool.h>
#include "buttons.h"

static bool btn1;
static bool btn2;

static void SetButton(enum buttons btn) {
    switch (btn) {
        case BTN1:
            btn1 = true;
        break;
        case BTN2:
            btn2= true;
        break;
    }
}

void SetBTN1(void) {
    SetButton(BTN1);
}

void SetBTN2(void) {
    SetButton(BTN2);
}

bool ReadButton(enum buttons btn) {
    switch (btn) {
        case BTN1:
            return btn1;
        break;
        case BTN2:
            return btn2;
        break;
    }
}

void ResetButton(enum buttons btn) {
    switch (btn) {
        case BTN1:
            btn1 = false;
        break;
        case BTN2:
            btn2= false;
        break;
    }
}


/* *****************************************************************************
 End of File
 */
