#ifndef _HARDWARE_PROFILE_H    /* Guard against multiple inclusion */
#define _HARDWARE_PROFILE_H


#define LEDA_SetDigitalOutput() (TRISAbits.TRISA7 = 0)
#define LEDB_SetDigitalOutput() (TRISBbits.TRISB14 = 0)

#define LEDA_SetHigh() (LATAbits.LATA7 = 1)// Pone en nivel alto del LED A
#define LEDB_SetHigh() (LATBbits.LATB14 = 1)// Pone en nivel alto del LED B

#define LEDA_SetLow() (LATAbits.LATA7 = 0)// Pone en nivel bajo del LED A
#define LEDB_SetLow() (LATBbits.LATB14 = 0)// Pone en nivel bajo del LED B

#define LEDA_Toggle() (LATAbits.LATA7 = !LATAbits.LATA7)// Invierte de nivel del LED A
#define LEDB_Toggle() (LATBbits.LATB14 = !LATBbits.LATB14)// Invierte de nivel del LED B

#endif