
/*******************************************************************************
  TMR0 Generated Driver File 

  Company:
    Microchip Technology Inc.

  File Name:
    tmr0.c

  Summary:
    This is the generated driver implementation file for the TMR0 driver using MPLAB® Code Configurator

  @Description
    This header file provides implementations for driver APIs for TMR0. 
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
#include "tmr0.h"

uint8_t Timer0ReloadVal;

/**
  @Prototype        void TMR0_InitializerDefault(void)
  @Input            none
  @Output           none
  @Description      custom init function for TMR0
  @Comment          
  @Usage            TMR0_InitializerDefault();
*/
void TMR0_InitializerDefault(void)
{
    // set TMR0 to the options selected in the User Interface
    OPTION_REG = 0xF2; 
    // set TMR0 to the options selected in the User Interface
    TMR0 = 0x00; 
		
    // Load the TMR value to reload variable
    Timer0ReloadVal=TMR0;
	
    // Clear Interrupt flag before enabling the interrupt.
    INTCONbits.TMR0IF = 0;

    // Enabling TMR0 interrupt.
    INTCONbits.TMR0IE = 1;
}

/**
  @Prototype        void TMR0_StartTimer(void)
  @Input            none
  @Output           none
  @Description      TMR0 Start function.
  @Usage            TMR0_StartTimer();
*/
void TMR0_StartTimer(void)
{
    //Start the Timer by writing to TMR0CS bit
    OPTION_REGbits.TMR0CS = 0;
}

/**
  @Prototype        void TMR0_StopTimer(void)
  @Input            none
  @Output           none
  @Description      TMR0 Stop function.
  @Usage            TMR0_StopTimer(void)();
*/
void TMR0_StopTimer(void)
{
    //Stop the Timer by writing to TMR0CS bit
    OPTION_REGbits.TMR0CS = 1;
}

/**
  @Prototype        uint8_t TMR0_ReadTimer(void)
  @Input            none
  @Output           Timer value at the time of the function call
                    read as a 8-bit value
  @Description      Function returns the timer value at the time of function call.
  @Usage            TMR0_ReadTimer();
*/
uint8_t TMR0_ReadTimer(void)
{
    uint8_t ReadVal;
    ReadVal = TMR0;
    return ReadVal;
}

/**
  @Prototype        void TMR0_WriteTimer(uint8_t TimerVal)
  @Input            TimerVal : Timer value
  @Output           none
  @Description      TMR0 Write function
  @Usage            TMR0_WriteTimer(TimerVal);
*/
void TMR0_WriteTimer(uint8_t TimerVal)
{   
    //Write to the Timer0 register
    TMR0 = TimerVal;
}

/**
  @Prototype        void TMR0_Reload(void)
  @Input            none
  @Output           none
  @Description      TMR0 Reload function
  @Usage            TMR0_Reload();
*/
void TMR0_Reload(void)
{   
    //Write to the Timer0 register
    TMR0 = Timer0ReloadVal;
}

/**
  @Prototype        void TMR0_ISR(void)
  @Input            none
  @Output           none
  @Description      TMR0 Interrupt Service Routine.Called by the
                    Interrupt Manager.Place your TMR0 Interrupt code here.
  @Usage            TMR0_ISR();
*/
void TMR0_ISR(void)
{
    
    static volatile unsigned int CountCallBack = 0;

    // clear the TMR0 interrupt flag
    INTCONbits.TMR0IF = 0;
    TMR0 += Timer0ReloadVal;
    if (++CountCallBack >= TMR0_INTERRUPT_TICKER_FACTOR)
    {
        // ticker function call
        TMR0_CallBack();

        // reset ticker counter
        CountCallBack = 0;
    }
    // add your TMR0 interrupt custom code
}

/**
  @Prototype        void TMR0_CallBack(void)
  @Input            none
  @Output           none
  @Description      TMR0 CallBack function.Called by the TMR0 interrupt handler.
                    Place your TMR0 CallBack code here.
  @Usage            TMR0_CallBack();
*/
void TMR0_CallBack(void)
{
    // Add your custom callback code here
}