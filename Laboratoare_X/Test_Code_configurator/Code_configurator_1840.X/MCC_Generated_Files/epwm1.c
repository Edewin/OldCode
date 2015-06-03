/*******************************************************************************
  ECCP Generated Driver File 

  Company:
    Microchip Technology Inc.

  File Name:
    eccp.c

  Summary:
    This is the generated driver implementation file for the ECCP driver using MPLAB® Code Configurator

  Description:
    This header file provides implementations for driver APIs for ECCP. 
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


#include <xc.h> 
#include "epwm1.h"

/************* THIS IS THE USER GENERATED PWM SOURCE FILE *********************/

/**
  Prototype:        void EPWM1_InitializerDefault (void);
  Input:            none
  Output:           none
  Description:      custom init function for ECCP
  Comment:          
  Usage:            EPWM1_InitializerDefault ();
*/
void EPWM1_InitializerDefault (void)
{
   //set the PWM to the options selected in MPLAB® Code Configurator
   //Writing to CCPCON,CCPTMRS0,CCPTMRS1 registers
   //STR1A P1A_to_port; STR1C P1C_to_port; STR1B P1B_to_port; STR1D P1D_to_port; STR1SYNC start_at_begin; 
    PSTR1CON = 0x00;

   //P1RSEN automatic_restart; P1DC 0; 
    PWM1CON = 0x80;

   //PSS1BD P1BP1D_0; CCP1AS disabled; CCP1ASE operating; PSS1AC P1AP1C_0; 
    CCP1AS = 0x00;

   //P1M single; CCP1M P1AP1Chi_P1BP1Dhi; DC1B 48; 
    CCP1CON = 0x3C;

   //CCPR1L 50; 
    CCPR1L = 0x32;

   //CCPR1H 0x0; 
    CCPR1H = 0x00;

}

/**
  Prototype:        void EPWM1_LoadDutyValue(uint16_t dutyValue);
  Input:            value-10 bit digital duty cycle value to PWM.
  Output:           none
  Description:      This API loads duty cycle value into PWM registers.
  Usage:            EPWM1_LoadDutyValue(uint16_t dutyValue)
*/
void EPWM1_LoadDutyValue(uint16_t dutyValue)
{
   //Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR1L = ((dutyValue & 0x03FC)>>2);
   //Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP1CON = (CCP1CON & 0xCF) | ((dutyValue & 0x0003)<<4);
}

