/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.0.1
        Device            :  PIC16F1503
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.31
        MPLAB             :  MPLAB X 2.10
*/

/*
Copyright (c) 2013 - 2014 released Microchip Technology Inc.  All rights reserved.

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

#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include <flash.h>

/*
                         Main application
 */

#define AdresaPWM3 400
#define AdresaPWM4 500
#define max 0x001F
//#define _XTAL_FREQ  16000000

void main(void)
{
    /*Memory variables*/
    uint16_t faddrPWM3=AdresaPWM3;
    uint16_t faddrPWM4=AdresaPWM4;
    uint16_t Rbuf[32];
    uint16_t *pRbuf=&Rbuf[0];
    /*PWM duty cycle variables*/
    uint16_t dutyCycleP3=0;
    uint16_t dutyCycleP4=0;

    uint16_t randPWM3,randPWM4;


    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    dutyCycleP3=FLASH_ReadWord(faddrPWM3);
    dutyCycleP4=FLASH_ReadWord(faddrPWM4);
    PWM3_LoadDutyValue(dutyCycleP3);
    PWM4_LoadDutyValue(dutyCycleP4);
    __delay_ms(500);

    while (1)
    {
        dutyCycleP3=rand()%50;
        dutyCycleP4=rand()%50+10;
            PWM3_LoadDutyValue(dutyCycleP3);
            PWM4_LoadDutyValue(dutyCycleP4);
            FLASH_WriteWord(faddrPWM3,pRbuf,dutyCycleP3);
            FLASH_WriteWord(faddrPWM4,&Rbuf[16],dutyCycleP4);
            __delay_ms(100);
     /*   for(dutyCycleP3=0;dutyCycleP3<max;dutyCycleP3+=10)
        {
            dutyCycleP4=max-dutyCycleP3;
            PWM3_LoadDutyValue(dutyCycleP3);
            PWM4_LoadDutyValue(dutyCycleP4);
            FLASH_WriteWord(faddrPWM3,pRbuf,dutyCycleP3);
            FLASH_WriteWord(faddrPWM4,&Rbuf[16],dutyCycleP4);
            __delay_ms(700);

        }
         for(dutyCycleP4=0;dutyCycleP4<max;dutyCycleP4+=10)
        {
            dutyCycleP3=max-dutyCycleP4;
            PWM3_LoadDutyValue(dutyCycleP3);
            PWM4_LoadDutyValue(dutyCycleP4);
            FLASH_WriteWord(faddrPWM3,pRbuf,dutyCycleP3);
            FLASH_WriteWord(faddrPWM4,&Rbuf[16],dutyCycleP4);
            __delay_ms(700);
        }*/
        // Add your application code
    }
}
/**
 End of File
*/