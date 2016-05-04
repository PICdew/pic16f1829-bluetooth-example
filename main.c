/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - v3.00
        Device            :  PIC16F1829
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20
*/

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */
//#include "stdio.h"
#include <stdio.h>  // used for printf
#include <xc.h>     // regsiter mappings

void putch(char d); // the 'printf' function uses this for its printing. 
                    // we are going to override it so it prints to the UART
static void uartWrite(char d); // function for printing one character at a time
void timer4ISR(); // function callback from TMR4 interrupt routine
static uint32_t tmp; // global temp variable that will be sent to 
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    // Create a call-back to our own implementation of a timer4 interrupt
    TMR4_SetInterruptHandler(timer4ISR); 
    
    // pin configuration for the two LEDs
    ANSELCbits.ANSC0 = 0; // digital pin
    ANSELCbits.ANSC3 = 0; // digital pin
    TRISCbits.TRISC0 = 0; // output
    TRISCbits.TRISC3 = 0; // output
    WPUCbits.WPUC0 = 0; // disable weak pull-up
    WPUCbits.WPUC3 = 0; // disable weak pull-up
    
    
    
    __delay_ms(2000); // delay for HC-06 initialization
    printf("AT+NAMEmcuhq.com");
    __delay_ms(4000); // wait for setting to take effect
    
    while (1)
    {
        if(eusartRxCount != 0){
            char rxChar = EUSART_Read(); // check to see if received anything on the UART
            printf("\nRX: %c\n", rxChar); // if yes, echo it back
            if(rxChar == 'c') // if we got a `c` character, toggle an LED
                LATCbits.LATC3 ^= 1; // toggle this
        }
    }
}

void putch(char d){
    uartWrite(d);
}

static void uartWrite(char txData){
    while(0 == PIR1bits.TXIF); // wait for current byte to finish sending
    TXREG = txData;    // Write the data byte to the USART.
}

// Enter here on a Timer4 rollover interrupt
void timer4ISR(){
    printf("%d",tmp++); // constantly write this to connected device
    LATCbits.LATC0 ^= 1;
}

/**
 End of File
*/