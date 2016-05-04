/**
  TMR4 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr4.c

  @Summary
    This is the generated driver implementation file for the TMR4 driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for TMR4.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - v3.00
        Device            :  PIC16F1829
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20
*/

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr4.h"

/**
  Section: TMR4 APIs
*/

void TMR4_Initialize(void)
{
    // Set TMR4 to the options selected in the User Interface

    // T4CKPS 1:64; T4OUTPS 1:1; TMR4ON off; 
    T4CON = 0x03;

    // PR4 5; 
    PR4 = 0x05;

    // TMR4 0; 
    TMR4 = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR3bits.TMR4IF = 0;

    // Enabling TMR4 interrupt.
    PIE3bits.TMR4IE = 1;

    // Set Default Interrupt Handler
    TMR4_SetInterruptHandler(TMR4_DefaultInterruptHandler);

    // Start TMR4
    TMR4_StartTimer();
}

void TMR4_StartTimer(void)
{
    // Start the Timer by writing to TMRxON bit
    T4CONbits.TMR4ON = 1;
}

void TMR4_StopTimer(void)
{
    // Stop the Timer by writing to TMRxON bit
    T4CONbits.TMR4ON = 0;
}

uint8_t TMR4_ReadTimer(void)
{
    uint8_t readVal;

    readVal = TMR4;

    return readVal;
}

void TMR4_WriteTimer(uint8_t timerVal)
{
    // Write to the Timer4 register
    TMR4 = timerVal;
}

void TMR4_LoadPeriodRegister(uint8_t periodVal)
{
   PR4 = periodVal;
}

void TMR4_ISR(void)
{
    static volatile unsigned int CountCallBack = 0;

    // clear the TMR4 interrupt flag
    PIR3bits.TMR4IF = 0;

    // callback function - called every 10500th pass
    if (++CountCallBack >= TMR4_INTERRUPT_TICKER_FACTOR)
    {
        // ticker function call
        TMR4_CallBack();

        // reset ticker counter
        CountCallBack = 0;
    }
}

void TMR4_CallBack(void)
{
    // Add your custom callback code here
    // this code executes every TMR4_INTERRUPT_TICKER_FACTOR periods of TMR4
    if(TMR4_InterruptHandler)
    {
        TMR4_InterruptHandler();
    }
}

void TMR4_SetInterruptHandler(void* InterruptHandler){
    TMR4_InterruptHandler = InterruptHandler;
}

void TMR4_DefaultInterruptHandler(void){
    // add your TMR4 interrupt custom code
    // or set custom function using TMR4_SetInterruptHandler()
}

/**
  End of File
*/