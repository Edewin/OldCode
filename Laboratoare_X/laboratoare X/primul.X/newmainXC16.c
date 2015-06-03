/*
 * File:   newmainXC16.c
 * Author: Eduard
 *
 * Created on February 11, 2013, 9:28 AM
 */




/*
 * Use of the LED-s and the button
 *
 * Tested on:
 * Microstick + Microstick Plus
 * PIC24HJ64GP502
 *
 * File name: HardwareProfile.h
 * Author: Jozsef KOPJAK
 * Info: info@microstickplus.com
 *
 * Last modification: 17-10-2012
 */
#include <xc.h>
#include <p33fj128mc802.h>



#define FOSC	80000000
#define FCY	(FOSC/2)
#define FPWM    20000
#include <libpic30.h>

//#include "HardwareProfile.h"
#include "typedefs.h"
#include <stdio.h>
#include <stdlib.h>
/* Setting up configuration bits */
_FOSCSEL(FNOSC_FRC);    // Use internal oscillator  (FOSC ~ 8 Mhz)
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_NONE);	// RA3 pin is output
_FWDT(FWDTEN_OFF);	// Watchdog timer is disabled
_FPOR(PWMPIN_ON & HPOL_ON & LPOL_ON );
_FICD(JTAGEN_OFF);      // JTAG Port is disabled


/* Function prototypes */
void vInitPLLIntOsc( void );

//void vInitApp( void );
void PWM(void);

//signed int tabel [10]={0,3212,6393,9512,12539,15446,18204,20787,23170,25329};
//signed int tabel_2 [10]={0,3212,6393,9512,12539,15446,18204,20787,23170,25329};


/*********************************************************************
  Function:        void __attribute__((__interrupt__)) _ADCInterrupt (void)

  PreCondition:    None.

  Input:           None.

  Output:          None.

  Side Effects:    None.

  Overview:        The ADC interrupt loads the reference speed (RefSpeed) with
                   the respective value of the POT. The value will be a signed
                   fractional value, so it doesn't need any scaling.

  Note:            None.
********************************************************************/
unsigned int RefSpeed;

void __attribute__((__interrupt__)) _ADCInterrupt (void)
{
	IFS0bits.AD1IF = 0;	// Clear interrupt flag
	RefSpeed = ADCBUF0; // Read POT value to set Reference Speed
	return;
}


/*---------------------------------------------------------------------
  Function name: main
  Description: Entry point of the program
  Input parameters: -
  Output parameters: -
-----------------------------------------------------------------------*/
int main( void )
{
 int i;
  //  vInitApp(); // Hardware Initialization
    PWM();

    /* set LEDs (D3-D10/RA0-RA7) drive state low */
 //   LATA = 0xFF02;
    /* set LED pins (D3-D10/RA0-RA7) as outputs */
 //   TRISA = 0xFF02;
    //TRISB = 0xFFFF;

    /* Infinite loop */
    while(1)
    {
        for(i=0;i<250;i++)
        {
        
       
     P1TPER=999; //perioada
     P1DC1=i;
     __delay_ms(10);
 
        }

    }
    return 0;
}

/*---------------------------------------------------------------------
  Function name: vInitApp
  Description: Startup initializations
  Input parameters: -
  Output parameters: -
-----------------------------------------------------------------------*/
/*void vInitApp( void )
{
    vInitPLLIntOsc();  // Initialization of PLL
    mTurnOnPower(); // Turn on 3.3V power pin
    mInitLEDs();    // Initializations of LEDs
    mInitButton();  // Initializations of Button
}
*/
/*---------------------------------------------------------------------
  Function name: vInitPLLIntOsc
  Description: Setup internal oscillator with PLL (7.37 MHz -> 80 MHz )
  Input parameters: -
  Output parameters: -
-----------------------------------------------------------------------*/
void vInitPLLIntOsc( void )
{
    PLLFBD = 41;            // M = 26
    CLKDIVbits.PLLPOST=0;   // N1 = 2
    CLKDIVbits.PLLPRE=0;    // N2 = 2
/*
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(0x01);

    while (OSCCONbits.COSC != 0b001);
    while(OSCCONbits.LOCK != 1);
  */  
    // Initiate Clock Switch to Primary Oscillator with PLL (NOSC = 0b011)
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(OSCCON | 0x01);
    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b001);
    // Wait for PLL to lock
    while(OSCCONbits.LOCK!=1) {};

}

/*********************************************************************
  Function:        void InitADC10(void)

  PreCondition:    None.

  Input:           None.

  Output:          None.

  Side Effects:    None.

  Overview:        Below is the code required to setup the ADC registers for:
	               1. 1 channel conversion (in this case RB2/AN2)
                   2. PWM trigger starts conversion
                   3. Pot is connected to CH0 and RB2/AN2
                   4. The data format will be signed fractional

  Note:            None.
********************************************************************/

void InitADC10(void)
{

	ADPCFG = 0x0038;				// RB3, RB4, and RB5 are digital
	AD1CON1 = 0x036E;				// PWM starts conversion
									// Signed fractional conversions
	AD1CON2 = 0x0000;
	ADCHS = 0x0002;					// Pot is connected to AN2
		
	AD1CON3 = 0x0003;
	IFS0bits.AD1IF = 0;				// Clear ISR flag
	IEC0bits.AD1IE = 1;				// Enable interrupts

	AD1CON1bits.ADON = 1;			// turn ADC ON
	return;
}


void PWM( void )
{
    
    P1TCONbits.PTMOD=0b00;
    P1TCONbits.PTCKPS=0b01;
    P1TCONbits.PTOPS=0b00;
    P1TPER=999; //perioada
    PWM1CON1bits.PMOD1=0;
    PWM1CON1bits.PMOD2=0;
    PWM1CON1bits.PEN1H=1;
    PWM1CON1bits.PEN2H=1;
    PWM1CON1bits.PEN1L=1;
    PWM1CON1bits.PEN2L=1;
    PWM1CON2bits.IUE=0;
    PWM1CON2bits.SEVOPS=0000;
    P1DTCON1bits.DTAPS=0b00;
    P1DTCON1bits.DTBPS=0b00;
    P1DTCON1bits.DTA=40; //dead time maxim 3F=63 pentru ca e un nr fara semn pe
                         //pe 6 biti
    P1DTCON1bits.DTB=20; //dead time
    P1DTCON2bits.DTS2A=0;
    P1DTCON2bits.DTS2I=1;
    P1DTCON2bits.DTS1A=0;
    P1DTCON2bits.DTS1I=1;
    P1OVDCONbits.POVD2H=1;
    P1OVDCONbits.POVD1H=1;
    P1OVDCONbits.POVD2L=1;
    P1OVDCONbits.POVD1L=1;
    P1DC1=0;
    P1DC2=0;
    P1TCONbits.PTEN=1;
//    P1OVDCON=0x0000;


}