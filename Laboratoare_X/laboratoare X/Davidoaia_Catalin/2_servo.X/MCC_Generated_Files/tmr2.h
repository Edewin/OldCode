
/*******************************************************************************
  TMR2 Generated Driver API Header File 

  Company:
    Microchip Technology Inc.

  File Name:
    tmr2.h

  Summary:
    This is the generated header file for the TMR2 driver using MPLAB® Code Configurator

  Description:
    This header file provides APIs for driver for TMR2. 
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



#ifndef TMR2_H
#define TMR2_H

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t timer_size_t;

#define TMR2_INTERRUPT_TICKER_FACTOR    1
 
/**
  This initializer configure the Timer control registers.
  @Prototype        void TMR2_InitializerDefault(void)
  @Param            parameters required to initialize comparator are provided by UI
  @Return           none
  @Comment          
  @Usage            TMR2_InitializerDefault();
*/
void TMR2_InitializerDefault(void);

/**
  This routine starts the timer
  @Prototype        void TMR2_StartTimer(void)
  @Param            none
  @Return           none
  @Usage            TMR2_StartTimer();
*/
void TMR2_StartTimer(void);

/**
  This routine stops the timer
  @Prototype        void TMR2_StopTimer(void)
  @Param            none
  @Return           none
  @Usage            TMR2_StopTimer();
*/
void TMR2_StopTimer(void);

/**
  This routine reads the Timer register value 
  @Prototype        uint8_t TMR2_ReadTimer(void)
  @Param            none
  @Return           Timer value at the time of the function call
                    read as a 8-bit value
  @Usage            TMR2_ReadTimer();
*/
uint8_t TMR2_ReadTimer(void);

/**
  This routine writes to Timer register
  @Prototype        void TMR2_WriteTimer(uint8_t TimerVal)
  @Param            TimerVal : Timer value to be loaded
  @Return           none
  @Usage            TMR2_WriteTimer(TimerVal);
*/
void TMR2_WriteTimer(uint8_t TimerVal);

/**
  This routine is used to load value to period register
  @Prototype        void TMR2_LoadPeriodRegister(uint8_t PeriodVal)
  @Param            PeriodVal : Value to be loaded into the period register
  @Return           none
  @Usage            TMR2_LoadPeriodRegister(PeriodVal);
*/
void TMR2_LoadPeriodRegister(uint8_t PeriodVal);

/**
  Timer Interrupt Service Routine. Called by the Interrupt Manager. <br>Place your Timer Interrupt code here. </br>
  @Protoype         void TMR2_ISR(void)
  @Param            none
  @Output           none
  @Return           none
  @Usage            TMR2_ISR();
 */
void TMR2_ISR(void);

/**
  CallBack function.Called by the Interrupt Manager. <br>CallBack code here. </br>
  @Protoype         void TMR2_CallBack(void)
  @Param            none
  @Output           none
  @Return           none
  @Usage            TMR2_CallBack();
 */
 void TMR2_CallBack(void);
 
 #endif // tmr2.h
