/*******************************************************************************
  ECCP Generated Driver API Header File 

  Company:
    Microchip Technology Inc.

  File Name:
    eccp.h

  Summary:
    This is the generated header file for the ECCP driver using MPLAB® Code Configurator

  Description:
    This header file provides APIs for driver for ECCP. 
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


#ifndef EPWM1_H
#define EPWM1_H

#include <xc.h> 
#include <stdint.h>
            
/****************** THIS IS THE USER GENERATED PWM HEADER *********************/

/*******************************************************************************
  This API initilize CCP in PWM mode.Timer Configuration should be done in TMR <br>module </br>
  @Prototype        void EPWM1_InitializerDefault (void)
  @Param            none
  @Return           none
  @Comment          
  @Usage            EPWM1_InitializerDefault ();
  ****************************************************************************/
void EPWM1_InitializerDefault(void);

/*******************************************************************************
  This function will write the duty cycle value into PWM registers
  @Prototype        void EPWM1_LoadDutyValue(uint16_t dutyValue);
  @Param            value -10 bit digital, duty cycle value to PWM.
  @Return           none
  @Usage            EPWM1_LoadDutyValue(dutyValue);
  ****************************************************************************/
void EPWM1_LoadDutyValue(uint16_t dutyValue);

#endif

