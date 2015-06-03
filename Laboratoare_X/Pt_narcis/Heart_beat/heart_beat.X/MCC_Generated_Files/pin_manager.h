/*******************************************************************************
  Generated Pin Manager Header File 

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.h

  Summary:
    This is the Pin Manager file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI. 
    Generation Information : 
        Product Revision  :  MPLAB® Code Configurator - v1.1
        Device            :  PIC12F1840
        Version           :  1.1
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.30
        MPLAB             :  MPLAB X 2.0
*******************************************************************************/

/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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
*******************************************************************************/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA0 procedures
#define RA0_SetHigh()    do { LATA0 = 1; } while(0)
#define RA0_SetLow()   do { LATA0 = 0; } while(0)
#define RA0_Toggle()   do { LATA0 = ~LATA0; } while(0)
#define RA0_GetValue()         RA0
#define RA0_SetDigitalInput()    do { TRISA0 = 1; } while(0)
#define RA0_SetDigitalOutput()   do { TRISA0 = 0; } while(0)
#define RA0_SetPullup()    do { WPUA0 = 1; } while(0)
#define RA0_ResetPullup()   do { WPUA0 = 0; } while(0)
#define RA0_SetAnalogMode()   do { ANSA0 = 1; } while(0)
#define RA0_SetDigitalMode()   do { ANSA0 = 0; } while(0)
// get/set RA1 procedures
#define RA1_SetHigh()    do { LATA1 = 1; } while(0)
#define RA1_SetLow()   do { LATA1 = 0; } while(0)
#define RA1_Toggle()   do { LATA1 = ~LATA1; } while(0)
#define RA1_GetValue()         RA1
#define RA1_SetDigitalInput()    do { TRISA1 = 1; } while(0)
#define RA1_SetDigitalOutput()   do { TRISA1 = 0; } while(0)
#define RA1_SetPullup()    do { WPUA1 = 1; } while(0)
#define RA1_ResetPullup()   do { WPUA1 = 0; } while(0)
#define RA1_SetAnalogMode()   do { ANSA1 = 1; } while(0)
#define RA1_SetDigitalMode()   do { ANSA1 = 0; } while(0)
// get/set RA2 procedures
#define RA2_SetHigh()    do { LATA2 = 1; } while(0)
#define RA2_SetLow()   do { LATA2 = 0; } while(0)
#define RA2_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define RA2_GetValue()         RA2
#define RA2_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define RA2_SetDigitalOutput()   do { TRISA2 = 0; } while(0)
#define RA2_SetPullup()    do { WPUA2 = 1; } while(0)
#define RA2_ResetPullup()   do { WPUA2 = 0; } while(0)
#define RA2_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define RA2_SetDigitalMode()   do { ANSA2 = 0; } while(0)
// get/set MCLR aliases
#define MCLR_TRIS               TRISA3
#define MCLR_WPU                WPUA3
#define MCLR_GetValue()         RA3
#define MCLR_SetDigitalInput()    do { TRISA3 = 1; } while(0)
#define MCLR_SetDigitalOutput()   do { TRISA3 = 0; } while(0)


#define MCLR_SetPullup()    do { WPUA3 = 1; } while(0)
#define MCLR_ResetPullup()   do { WPUA3 = 0; } while(0)
// get/set RA4 procedures
#define RA4_SetHigh()    do { LATA4 = 1; } while(0)
#define RA4_SetLow()   do { LATA4 = 0; } while(0)
#define RA4_Toggle()   do { LATA4 = ~LATA4; } while(0)
#define RA4_GetValue()         RA4
#define RA4_SetDigitalInput()    do { TRISA4 = 1; } while(0)
#define RA4_SetDigitalOutput()   do { TRISA4 = 0; } while(0)
#define RA4_SetPullup()    do { WPUA4 = 1; } while(0)
#define RA4_ResetPullup()   do { WPUA4 = 0; } while(0)
#define RA4_SetAnalogMode()   do { ANSA4 = 1; } while(0)
#define RA4_SetDigitalMode()   do { ANSA4 = 0; } while(0)
// get/set RA5 procedures
#define RA5_SetHigh()    do { LATA5 = 1; } while(0)
#define RA5_SetLow()   do { LATA5 = 0; } while(0)
#define RA5_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define RA5_GetValue()         RA5
#define RA5_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define RA5_SetDigitalOutput()   do { TRISA5 = 0; } while(0)
#define RA5_SetPullup()    do { WPUA5 = 1; } while(0)
#define RA5_ResetPullup()   do { WPUA5 = 0; } while(0)

/**
 * @protoype        void PIN_MANAGER_initializer (void)
 * @param           none
 * @output          none
 * @description     GPIO and peripheral I/O initialization
 * @usage           PIN_MANAGER_initializer();
 *
 */
void PIN_MANAGER_Initializer (void);
void PIN_MANAGER_IOC(void);
#endif // PIN_MANAGER_H