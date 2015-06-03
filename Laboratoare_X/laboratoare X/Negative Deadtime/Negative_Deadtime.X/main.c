/* 
 * File:   main.c
 * Author: Eduard
 *
 * Created on May 22, 2013, 1:49 PM
 */

/**************************************************************************************
*  © 2008 Microchip Technology Inc.
*
*  FileName:              Negative Deadtime.c
*  Dependencies:          Header (.h) files if applicable, see below
*  Processor:             dsPIC33FJ06GS202
*  Compiler:              MPLAB® C30 v3.02 or higher
*  IDE:                   MPLAB® IDE v8.02 or later
*  Hardware Dependencies: 16-Bit 28-Pin Starter Board
*
*  SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all ownership and
* intellectual property rights in the code accompanying this message and in all
* derivatives hereto.  You may use this code, and any derivatives created by
* any person or entity by or on your behalf, exclusively with Microchip's
* proprietary products.  Your acceptance and/or use of this code constitutes
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
* TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP'S
* PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE, WHETHER
* IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY),
* STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL,
* PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF
* ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN
* ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
* ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO
* THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO
* HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and
* determining its suitability.  Microchip has no obligation to modify, test,
* certify, or support the code.
*
* Description:
*     This program illustrates the use of Negative Dead-time in the PWM
* module in the dsPIC33F SMPS family with ADC triggers. The
* PWM is configured with negative deadtime and configured to
* generate an ADC trigger. PWM1 generates a trigger on ADC channel 5.
* The converted ADC value is used to update the duty cycle of PWM1.
* The voltage at AN5 (POT) decides the duty cycle of PWM1.
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "p33FJ09GS302.h"

/* Configuration Bit Settings */
_FOSCSEL(FNOSC_FRC)
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON)
_FWDT(FWDTEN_OFF)
_FICD(ICS_PGD2 & JTAGEN_OFF)
        


void init_PWM();
void init_ADC();

int main()
{
/* Configure Oscillator to operate the device at 40Mhz
	   Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
 	   Fosc= 7.37*(43)/(2*2)=80Mhz for Fosc, Fcy = 40Mhz */

	/* Configure PLL prescaler, PLL postscaler, PLL divisor */
	PLLFBD=41; 				/* M = PLLFBD + 2 */
	CLKDIVbits.PLLPOST=0;   /* N1 = 2 */
	CLKDIVbits.PLLPRE=0;    /* N2 = 2 */

    __builtin_write_OSCCONH(0x01);			/* New Oscillator FRC w/ PLL */
    __builtin_write_OSCCONL(0x01);  		/* Enable Switch */

	while(OSCCONbits.COSC != 0b001);		/* Wait for new Oscillator to become FRC w/ PLL */
    while(OSCCONbits.LOCK != 1);			/* Wait for Pll to Lock */

	/* Now setup the ADC and PWM clock for 120MHz
	   ((FRC * 16) / APSTSCLR ) = (7.37 * 16) / 1 = ~ 120MHz*/

	ACLKCONbits.FRCSEL = 1;					/* FRC provides input for Auxiliary PLL (x16) */
	ACLKCONbits.SELACLK = 1;				/* Auxiliary Oscillator provides clock source for PWM & ADC */
	ACLKCONbits.APSTSCLR = 7;				/* Divide Auxiliary clock by 1 */
	ACLKCONbits.ENAPLL = 1;					/* Enable Auxiliary PLL */

	while(ACLKCONbits.APLLCK != 1);			/* Wait for Auxiliary PLL to Lock */

	
	init_ADC();
        init_PWM();

	IPC3bits.ADIP = 4;      				/* ADC Interrupt Priority */
	IFS0bits.ADIF = 0;     					/* Clear ADC Interrupt Flag */
	IEC0bits.ADIE = 1;     					/* ADC Interrupt Enable */

    PTCONbits.PTEN = 1;                 /* Turn ON PWM module */
    ADCONbits.ADON = 1;     	            /* ADC is turned ON */
 	
       // LATAbits.LATA0=0;
       // TRISAbits.TRISA0=0;
    while(1)
    {
        Nop();
       // LATAbits.LATA0=1;
    }
}

void init_PWM()
{
    PTCON2bits.PCLKDIV= 2 ;                     /* PWM input clock prescaler = 4 */
    PTPER = 23960;							/* PTPER = ((10us) / 1.04ns) = 9615, where 10us
    											is the PWM period and 1.04ns is PWM resolution. */

    PDC1 = 5990;                            /* PWM1 duty cycle (2.5us / 1.04ns) 2404 */

    IOCON1bits.PENH = 1;                    /* PWM1 outputs controlled by PWM */
    IOCON1bits.PENL = 1;
    IOCON1bits.PMOD = 0;                    /* Choose Complementary PWM mode */
    IOCON1bits.POLH = 0;
    IOCON1bits.POLL = 0;

    PWMCON1bits.DTC = 1;                    /* Negative Dead time enabled */

        			                        /* Negative deadtime = 130nsec */
    DTR1 = 63;                              /* Deadtime = (65ns / 1.04ns) where 65ns is desired deadtime */
    ALTDTR1 = 63;                           /* ALTDeadtime = (65ns / 1.04ns) where 65ns is desired deadtime */

    TRGCON1bits.TRGDIV = 1;                 /* Trigger output every 2nd trigger event */
    TRIG1 = 11980;                           /* Trigger generated in the middle of the PWM period */

}

void init_ADC()
{
      ADPCFGbits.PCFG5 = 0;                           /* Choose AN5 as analog input */
   //   ADPCFG2=0;
      TRISBbits.TRISB10=1;
      ADCPC1bits.IRQEN2 = 1;                /* Enable interrupt request */
      ADCPC1bits.TRGSRC2 = 4;               /* Trigger ADC pair 2 conversion on PWM1 generator */
      ADCPC1bits.PEND2 = 1;
      ADCPC1bits.SWTRG2 = 1;

      
      ADSTATbits.P2RDY = 0;                 /* Clear pair 2 data ready bit */

      ADCONbits.FORM = 0;                   /* Choose integer data format */
      ADCONbits.ORDER = 0;                  /* Even numbered input is converted first */
      ADCONbits.SEQSAMP = 1;                /* Sequential sampling enabled */
      ADCONbits.ADCS = 4;                   /* 7 ADC clock = FADC/14 */
      ADCONbits.SLOWCLK = 1;


}

void __attribute__ ((__interrupt__, no_auto_psv)) _ADCInterrupt(void)
{
    unsigned int tmp=0;
    IFS0bits.ADIF = 0;                      /* Clear ADC interrupt flag */
    ADSTATbits.P2RDY = 0;                   /* Clear pair 2 data ready bit */

    tmp = ADCBUF5*8000;                        /* Scaling of AN5 voltage */
                                            /* This ensures a significant
                                               change in duty cycle based
                                               on ADC conversion value */

    if (tmp < 500) tmp = 500;               /* Applying boundary conditions */
                                            /* The boundary conditions ensure
                                               that the duty cycle does not
                                               become less than deadtime
                                               setting 500/8 >= Deadtime */

    PDC1 = tmp;                             /* Update PWM1 duty cycle */
}

