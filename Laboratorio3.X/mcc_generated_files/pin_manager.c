/**
  PIN MANAGER Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.c

  @Summary:
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for PIN MANAGER.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.169.0
        Device            :  PIC32MM0256GPM064
    The generated drivers are tested against the following:
        Compiler          :  XC32 v2.40
        MPLAB 	          :  MPLAB X v5.40
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/


/**
    Section: Includes
*/

#include <xc.h>
#include "pin_manager.h"
#include "system.h"

/**
 Section: File specific functions
*/
void (*BTN2_InterruptHandler)(void) = NULL;
void (*BTN1_InterruptHandler)(void) = NULL;

/**
 Section: Driver Interface Function Definitions
*/
void PIN_MANAGER_Initialize (void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000;
    LATB = 0x0000;
    LATC = 0x0000;
    LATD = 0x0000;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0xFF77;
    TRISB = 0xAFFF;
    TRISC = 0xFFFF;
    TRISD = 0x001F;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPDA = 0x2000;
    CNPDB = 0x8000;
    CNPDC = 0x0000;
    CNPDD = 0x0000;
    CNPUA = 0x0000;
    CNPUB = 0x0000;
    CNPUC = 0x0000;
    CNPUD = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;
    ODCC = 0x0000;
    ODCD = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSELA = 0x1843;
    ANSELB = 0x201C;
    ANSELC = 0x0123;


    /****************************************************************************
     * Interrupt On Change: positive
     ***************************************************************************/
    CNEN0Abits.CNIE0A13 = 1;    //Pin : RA13
    CNEN0Bbits.CNIE0B15 = 1;    //Pin : RB15
    /****************************************************************************
     * Interrupt On Change: flag
     ***************************************************************************/
    CNFAbits.CNFA13 = 0;    //Pin : RA13
    CNFBbits.CNFB15 = 0;    //Pin : RB15
    /****************************************************************************
     * Interrupt On Change: config
     ***************************************************************************/
    CNCONAbits.CNSTYLE = 1;    //Config for PORTA
    CNCONAbits.ON = 1;    //Config for PORTA
    CNCONBbits.CNSTYLE = 1;    //Config for PORTB
    CNCONBbits.ON = 1;    //Config for PORTB
    
    /* Initialize IOC Interrupt Handler*/
    BTN2_SetInterruptHandler(&BTN2_CallBack);
    BTN1_SetInterruptHandler(&BTN1_CallBack);
    
    /****************************************************************************
     * Interrupt On Change: Interrupt Enable
     ***************************************************************************/
    IFS0CLR= 1 << _IFS0_CNAIF_POSITION; //Clear CNAI interrupt flag
    IEC0bits.CNAIE = 1; //Enable CNAI interrupt
    IFS0CLR= 1 << _IFS0_CNBIF_POSITION; //Clear CNBI interrupt flag
    IEC0bits.CNBIE = 1; //Enable CNBI interrupt
}

void __attribute__ ((weak)) BTN2_CallBack(void)
{

}

void __attribute__ ((weak)) BTN1_CallBack(void)
{

}

void BTN2_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC0bits.CNAIE = 0; //Disable CNAI interrupt
    BTN2_InterruptHandler = InterruptHandler; 
    IEC0bits.CNAIE = 1; //Enable CNAI interrupt
}

void BTN2_SetIOCInterruptHandler(void *handler)
{ 
    BTN2_SetInterruptHandler(handler);
}

void BTN1_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC0bits.CNBIE = 0; //Disable CNBI interrupt
    BTN1_InterruptHandler = InterruptHandler; 
    IEC0bits.CNBIE = 1; //Enable CNBI interrupt
}

void BTN1_SetIOCInterruptHandler(void *handler)
{ 
    BTN1_SetInterruptHandler(handler);
}

/* Interrupt service routine for the CNAI interrupt. */
void __attribute__ ((vector(_CHANGE_NOTICE_A_VECTOR), interrupt(IPL2SOFT))) _CHANGE_NOTICE_A( void )
{
    if(IFS0bits.CNAIF == 1)
    {
        if(CNFAbits.CNFA13 == 1)
        {
            if(BTN2_InterruptHandler) 
            { 
                BTN2_InterruptHandler(); 
            }
            
            CNFACLR = 0x2000;  //Clear CNFAbits.CNFA13
        }
        
        // Clear the flag
        IFS0CLR= 1 << _IFS0_CNAIF_POSITION; // Clear IFS0bits.CNAIF
    }
}

/* Interrupt service routine for the CNBI interrupt. */
void __attribute__ ((vector(_CHANGE_NOTICE_B_VECTOR), interrupt(IPL2SOFT))) _CHANGE_NOTICE_B( void )
{
    if(IFS0bits.CNBIF == 1)
    {
        if(CNFBbits.CNFB15 == 1)
        {
            if(BTN1_InterruptHandler) 
            { 
                BTN1_InterruptHandler(); 
            }
            
            CNFBCLR = 0x8000;  //Clear CNFBbits.CNFB15
        }
        
        // Clear the flag
        IFS0CLR= 1 << _IFS0_CNBIF_POSITION; // Clear IFS0bits.CNBIF
    }
}

