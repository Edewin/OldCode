


/*******************************************************************************
  TMR2 Generated Driver File 

  Company:
    Microchip Technology Inc.

  File Name:
    tmr2.c

  Summary:
    This is the generated driver implementation file for the TMR2 driver using MPLAB® Code Configurator

  @Description
    This header file provides implementations for driver APIs for TMR2. 
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
#include "tmr2.h"

/**
  @Prototype        void TMR2_InitializerDefault(void)
  @Input            none
  @Output           none
  @Description      custom initializer function for TMR2
  @Comment          
  @Usage            TMR2_InitializerDefault ();
*/
void TMR2_InitializerDefault(void)
{
    // set TMR2 to the options selected in the User Interface

    //TMR2ON off; T2CKPS 1:64; T2OUTPS 1:10; 
    T2CON = 0x4B; 

    //PR2 255; 
    PR2 = 0xFF; 

    //TMR2 0; 
    TMR2 = 0x00; 

    
    // Clearing IF flag before enabling the interrupt.
    PIR1bits.TMR2IF = 0;

    // Enabling TMR2 interrupt.
    PIE1bits.TMR2IE = 1;
}

/**
  @Prototype        void TMR2_StartTimer(void)
  @Input            none
  @Output           none
  @Description      TMR2_StartTimer function.
  @Usage            TMR2_StartTimer();
*/
void TMR2_StartTimer(void)
{
    //Start the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 1;
}

/**
  @Prototype        void TMR2_StopTimer(void)
  @Input            none
  @Output           none
  @Description      TMR2 Stop function.
  @Usage            TMR2_StopTimer();
*/
void TMR2_StopTimer(void)
{
    //Stop the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 0;
}

/**
  @Prototype        uint8_t TMR2_ReadTimer(void)
  @Input            none
  @Output           Timer value at the time of the function call
                    read as a 8-bit value
  @Description      TMR2 Read function
  @Usage            TMR2_ReadTimer();
*/
uint8_t TMR2_ReadTimer(void)
{
    uint8_t readVal;
    readVal = TMR2;
    return readVal;
}

/**
  @Prototype        void TMR2_WriteTimer(uint8_t timerVal)
  @Input            TimerVal : Timer value to be loaded
  @Output           none
  @Description      TMR2_WriteTimer function
  @Usage            TMR2_WriteTimer(timerVal);
*/
void TMR2_WriteTimer(uint8_t timerVal)
{   
    //Write to the Timer2 register
    TMR2 = timerVal;
    
}

/**
  @Prototype        void TMR2_LoadPeriodRegister(uint8_t PeriodVal)
  @Input            PeriodVal : Value to be loaded into period register
  @Output           none
  @Description      TMR2_LoadPeriodRegister function.
  @Usage            TMR2_LoadPeriodRegister(PeriodVal);
*/
void TMR2_LoadPeriodRegister(uint8_t PeriodVal)
{
   PR2 = PeriodVal;
}

/**
  @Prototype        void TMR2_ISR(void)
  @Input            none
  @Output           none
  @Description      TMR2 Interrupt Service Routine.Called by the
                    Interrupt Manager.Place your TMR2 Interrupt code here.
  @Usage            TMR2_ISR();
*/
void TMR2_ISR(void)
{

    static volatile unsigned int CountCallBack = 0;

    // clear the TMR2 interrupt flag
    PIR1bits.TMR2IF = 0;
   
    if (++CountCallBack >= TMR2_INTERRUPT_TICKER_FACTOR)
    {
        // ticker function call
        TMR2_CallBack();

        // reset ticker counter
        CountCallBack = 0;
    }
    // add your TMR2 interrupt custom code
}

/**
  @Prototype        void TMR2_CallBack(void)
  @Input            none
  @Output           none
  @Description      TMR2 CallBack function.
                    Called by the TMR2 interrupt handler.
                    Place your TMR2 CallBack code here. 
  @Usage            TMR2_CallBack();
*/
void TMR2_CallBack(void)
{
    // Add your custom callback code here
    // this code executes every TMR2_INTERRUPT_TICKER_FACTOR periods of TMR2
}