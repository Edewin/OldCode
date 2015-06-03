/* 
 * File:   CL_SPI.c
 * Author: Eduard
 *
 *  Program pentru realizarea comenzii
 * catre PWM prin intermediul SPI-ului
 *
 *  Sens si frana Verificate
 *
 * Created on March 26, 2014, 6:33 PM
 */

/*
 * File:   C_L_v2.c
 * Author: Eduard
 *
 * Created on February 9, 2014, 9:28 PM
 */

//---------------------------------------------------------------------
//
//							 Software License Agreement
//
// The software supplied herewith by Microchip Technology Incorporated
// (the ?Company?) for its PICmicro® Microcontroller is intended and
// supplied to you, the Company?s customer, for use solely and
// exclusively on Microchip PICmicro Microcontroller products. The
// software is owned by the Company and/or its supplier, and is
// protected under applicable copyright laws. All rights are reserved.
//  Any use in violation of the foregoing restrictions may subject the
// user to criminal sanctions under applicable laws, as well as to
// civil liability for the breach of the terms and conditions of this
// license.
//
// THIS SOFTWARE IS PROVIDED IN AN ?AS IS? CONDITION. NO WARRANTIES,
// WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
// TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
// IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
// CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
//
//---------------------------------------------------------------------
//	File:		ClosedLoopSenBLDC.c
//
// This program runs a sensored BLDC motor in a closed PI loop
// The basic circuit is as depicted in AN957. The hardware is as
// depicted in the Masters2004 SNS845 class.  The board is expected
// to be productized in 2005.  Please check the web for details
//
//	Written By:		Stan D'Souza, Microchip Technology
//
//
// The following files should be included in the MPLAB project:
//
//		ClosedLoopSenBLDC.c		-- Main source code file
//		p30f2010.gld	-- Linker script file
//
//
//---------------------------------------------------------------------
//
// Revision History
//
// 10/01/04 -- first version
// 2/11/05 -- updated with improved PI and serial connection
//----------------------------------------------------------------------

// DSPIC30F2010 Configuration Bit Settings

#include <xc.h>


// FOSC
#pragma config FPR = XT_PLL4            // Primary Oscillator Mode (XT w/PLL 4x)
#pragma config FOS = PRI                // Oscillator Source (Primary Oscillator)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_OFF         // POR Timer Value (Timer Disabled)
#pragma config BODENV = NONE            // Brown Out Voltage (Reserved)
#pragma config BOREN = PBOR_OFF         // PBOR Enable (Disabled)
#pragma config LPOL = PWMxL_ACT_HI      // Low-side PWM Output Polarity (Active High)
#pragma config HPOL = PWMxH_ACT_HI      // High-side PWM Output Polarity (Active High)
#pragma config PWMPIN = RST_IOPIN       // PWM Output Pin Reset (Control with PORT/TRIS regs)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = PGD                // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)


#define FCY  10000000			// xtal = 5.0Mhz; PLLx8
#define MILLISEC FCY/10000			// 1 mSec delay constant
#define FPWM 29000
#define POLEPAIRS	2		// number of pole pairs of the motor
#define INDEX	5			// Hall sensor position index

#define S2	!PORTCbits.RC14
#define S3	!PORTCbits.RC13
#define SS      !PORTBbits.RB2
#define CR	0x0D
#define LF 	0x0A
#define BAUD 19200          //valoarea maxima pentru Long variable 2,147,483,647
#define SPEEDMULT	2343750		// factor used to calculate speed
#define OFFSET 8				// offset in InData to load speed values
#define POTMULT 16				// pot to speed ratio

#define Kps	0.02					// Kp and Ks terms need to be adjusted as per
#define Kis	0.00234//1.8//0.00022					// the motor and load


void InitADC10(void);
void AverageADC(void);
void DelayNmSec(unsigned int N);
void InitMCPWM(void);
void InitUART(void);
void init_SPI(void);
void SendSpeed(void);
void InitTMR3(void);
void SendMsg(void);
void transmit(unsigned char viteza);
void CalculateDC(void);
void init_INT(void);



struct {
			unsigned RunMotor : 	1;
			unsigned CalSpeed :		1;
			unsigned CheckRX :		1;
			unsigned SendTX :		1;
			unsigned unused 	:	12;
		}	Flags;

unsigned int HallValue;
unsigned int timer3value;
unsigned int timer3avg;
unsigned char polecount;
//unsigned char *TXPtr;
//unsigned char *RXPtr;
unsigned char sens=0;
unsigned char frana=0;
int DesiredSpeed;
int ActualSpeed;
int SpeedError;
int DutyCycle;
int SpeedIntegral;
unsigned char InData[] = {"000000"};
unsigned char OutData[] = {"Speed = 00000 rpm\r\n"};

unsigned int StateTable[] = {0x0000, 0x0210, 0x2004, 0x0204,
									0x0801, 0x0810, 0x2001, 0x0000};

/*************************************************************
	Low side driver table is as below.  In the StateLoTableClk,
	the Low side driver is a PWM while the high side driver is
	either on or off.
*************************************************************/

unsigned int StateLoTableClk[] = {0x0000, 0x0210, 0x2004, 0x0204,
									0x0801, 0x0810, 0x2001, 0x0000};
unsigned int StateLoTableAntiClk[] = {0x0000, 0x2001, 0x0810, 0x0801,
									0x0204, 0x2004, 0x0210, 0x0000};

void __attribute__((interrupt,no_auto_psv))_INT1Interrupt (void)
{
    frana=~frana;
    IFS1bits.INT1IF=0;  // clear the INT1 flag
}
void __attribute__((interrupt,no_auto_psv))_INT2Interrupt(void)
{
    sens=~sens;     
    IFS1bits.INT2IF=0;
}
/****************************************************************
Interrupt vector for Change Notification CN5, 6 and 7 is as below.
When a Hall sensor changes states, an interrupt will be
caused which will vector to the routine below
The program then reads PORTB, mask bits 3, 4 and 5,
shift and adjust the value to read as 1, 2 ... 6.  This
value is then used as an offset in the lookup table StateLoTableClk
or StateLoTableAntiClk to determine the value loaded in the OCDCON
register.  This routine also reads the Hall sensors and counts
up to the POLEPAIRS to determine the time for one mechanical
revolution using the fact that 1 mech rev = POLEPAIR*(1 elect. rev)
*****************************************************************/
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt (void)
{
	IFS0bits.CNIF = 0;				// clear flag
	HallValue = PORTB & 0x0038;	// mask RB3,4 & 5
	HallValue = HallValue >> 3;	// shift right 3 times
        if(sens)
	OVDCON = StateLoTableAntiClk[HallValue];
        else
            OVDCON=StateLoTableClk[HallValue];
// The code below is uses TMR3 to calculate the speed of the rotor
	if (HallValue == INDEX)  // has the same position been sensed?
		if (polecount++ == POLEPAIRS)  //has one mech rev elasped?
		{								// yes then read timer 3
		timer3value = TMR3;
		TMR3 = 0;
		timer3avg = ((timer3avg + timer3value) >> 1);
             //   timer3avg+=timer3value;
		polecount = 1;
		}
}
//---------------------------------------------------------------------
// Below are the interrupt vectors for the serial receive and transmit
//---------------------------------------------------------------------
void __attribute__((interrupt,no_auto_psv))_SPI1Interrupt(void)
{
    
    IFS0bits.SPI1IF=0;
}



/*********************************************************************
The ADC interrupt reads the demand pot value.

*********************************************************************/

void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt (void)
{
	IFS0bits.ADIF = 0;
//	DesiredSpeed = ADCBUF0;
        DesiredSpeed=0;
        Flags.CalSpeed = 1;		// after every adc read,  do a PI calculation
}

int main(void)
{
	LATE = 0x0000;
	TRISE = 0xFFC0;		// PWMs are outputs
	CNEN1 = 0x00E0;		// CN5,6 and 7 enabled
	CNPU1 = 0x00E0;		// enable internal pullups
	IFS0bits.CNIF = 0;	// clear CNIF
	IEC0bits.CNIE = 1;	// enable CN interrupt
	InitMCPWM();
	InitADC10();
        Flags.CheckRX = 0;			// clear rx and tx flags
        Flags.SendTX = 0;
	
        init_SPI();
	InitTMR3();
        init_INT();
	timer3avg = 0;
        unsigned int viteza_motor=0;
	while(1)
	{
           
		
		// read hall position sensors on PORTB
		HallValue = PORTB & 0x0038;			// mask RB3,4 & 5
		HallValue = HallValue >> 3;			// shift right to get value = 1, 2 ... 6
                if(sens)
		OVDCON = StateLoTableAntiClk[HallValue];	// Load the overide control register
                else
                    OVDCON=StateLoTableClk[HallValue];
		PWMCON1 = 0x0777;					// enable PWM outputs
		Flags.RunMotor = 1;					// set running flag
		T3CONbits.TON = 1;					// start tmr3
		polecount = 1;
		DelayNmSec(100);
		while (Flags.RunMotor)				// while motor is running
			{
                        viteza_motor = SPEEDMULT/timer3avg;
                         
                       // if(SS)
                        //transmit(viteza_motor);
			while (frana)							// if S2 is pressed, stop
				{
                            unsigned char auux=0;
                            auux=HallValue+1;
                            if(sens)
                            OVDCON=StateLoTableClk[auux];
                            else
                                OVDCON=StateLoTableAntiClk[auux];
                            DelayNmSec(100);
				PWMCON1 = 0x0700;			// disable PWM outputs
  				OVDCON = 0x0000;			// overide PWM low.
				Flags.RunMotor = 0;			// reset run flag
			//	while (frana);					// wait for key release
			//		DelayNmSec(10);
				}
			if (Flags.CalSpeed)		// if calculate flag set then
				{
				//SendSpeed();		// send present speed serially
				CalculateDC();		// calculate new dutycycle using PI
				Flags.CalSpeed = 0;		// clear flag
				}
			}
	}	// end of while (1)


}	// end of main

/*******************************************************************
		Below is the code required to setup the ADC registers for :
		1. 1 channel conversion (in this case RB2/AN2)
		2. PWM trigger starts conversion
		3. Pot is connected to CH0 and RB2
		4. AD interrupt is set and buffer is read in the interrupt

*********************************************************************/
void InitADC10(void)
{

 ADPCFG = 0xFFF8;				// all PORTB = Digital;RB0 to RB2 = analog
 ADCON1 = 0x0064;				// PWM starts conversion
 ADCON2 =  0x0200;				// simulataneous sample 4 channels
 ADCHS = 0x0002;				// Connect RB2/AN2 as CH0 = pot
 ADCON3 = 0x0080;				// Tad = internal RC (4uS)
 IFS0bits.ADIF = 0;
 IEC0bits.ADIE = 1;

 ADCON1bits.ADON = 1;			// turn ADC ON
}


void transmit(unsigned char viteza)
{
    SPI1BUF=viteza;
    while(SPI1STATbits.SPITBF);
}

/********************************************************************
InitMCPWM, intializes the Motor PWM as follows:
1. FPWM = 39000 hz at 10Mips
2. Independant PWMs
3. Control outputs using OVDCON
4. Init Duty Cycle with a value = 100
5. Set ADC to be triggered by PWM special trigger
*********************************************************************/

void InitMCPWM(void)
{
	PTPER = FCY/FPWM - 1;		// set the pwm period register

	PWMCON1 = 0x0700;			// disable PWMs
	OVDCON = 0x0000;			// allow control using OVD register
	PDC1 = 100;					// init PWM DC 1, 2 and 3 to 100
	PDC2 = 100;
	PDC3 = 100;
	SEVTCMP = PTPER;		// set ADC to trigeer at ...
	PWMCON2 = 0x0F00;		// 16 PWM values
	PTCON = 0x8000;			// start PWM however output ...
							// is enabled by OVDCON which is OFF

}
void init_INT(void)
{
    TRISDbits.TRISD0=1;
    TRISDbits.TRISD1=1;
    INTCON2bits.INT1EP=1; // interrupt on negative edge
    INTCON2bits.INT2EP=1; // same
    IFS1bits.INT1IF=0;  // clear the INT1 flag
    IFS1bits.INT2IF=0;  // clear the INT2 flag
    IPC4bits.INT1IP=6;  // interrupt priority
    IPC5bits.INT2IP=2;  // interrupt priority
    IEC1bits.INT1IE=1;  // interrupt request enable
    IEC1bits.INT2IE=1;  // same

}
/************************************************************************
Tmr3 is used to determine the rotor speed so it is set to count using Tcy/256

*************************************************************************/

void InitTMR3(void)
{
	T3CON = 0x0030;			// internal Tcy/256 clock
	TMR3 = 0;
	PR3 = 0xFFFF;
}

void init_SPI(void)
{
    SPI1BUF=0;
    IFS0bits.SPI1IF=0;
    IEC0bits.SPI1IE=1;
    IPC2bits.SPI1IP=5;      // interrupt priority
    SPI1CON=0x0180;
    SPI1STATbits.SPIROV=0;
    SPI1STATbits.SPIEN=1;   // enable SPI

}

/*void InitUART(void)
{
//---------------------------------------------------------------------
// Initialize the UART1 for BAUD = 19,200
 U1MODE = 0x8000;
 U1STA = 0x0000;
 U1BRG = ((FCY/16)/BAUD) - 1;	// set baud to 19200
 IEC0bits.U1RXIE = 1;			// enable RX interrupt
 RXPtr = &InData[0];		// point to first char in receive buffer
 Flags.CheckRX = 0;			// clear rx and tx flags
 Flags.SendTX = 0;

 U1STAbits.UTXEN = 1;           // Initiate transmission
}
*/
//------------------------------------------------------------------------
// SendSpeed sends the speed information on the uart at 19200 baud
void SendSpeed()
{
unsigned int k;
unsigned char c;

	k = SPEEDMULT/timer3avg;
	c = k/10000;
	if (c > 0)
		k = k - c*10000;
	OutData[OFFSET] = (c + 0x30);
	c = k/1000;
	if (c > 0)
		k = k - c*1000;
	OutData[OFFSET+1] = (c + 0x30);
	c = k/100;
	if (c > 0)
		k = k - c*100;
	OutData[OFFSET+2] = (c + 0x30);
	c = k/10;
	if (c > 0)
		k = k - c*10;
	OutData[OFFSET+3] = (c + 0x30);
	OutData[OFFSET+4] = (char)(k + 0x30);
//	TXPtr = &OutData[0];
	//SendMsg();
	Flags.CalSpeed = 0;
}

void SendMsg(void)
{
//while (*TXPtr)
	{
	while (U1STAbits.UTXBF);
//	U1TXREG = *TXPtr++;
	}
}


/*****************************************************************************
CalculateDC, uses the PI algorithm to calculate the new DutyCycle value which
will get loaded into the PDCx registers.

****************************************************************************/

void CalculateDC(void)
{
	ActualSpeed = SPEEDMULT/timer3avg;
	DesiredSpeed = DesiredSpeed*POTMULT;
	SpeedError = DesiredSpeed - ActualSpeed;
			SpeedIntegral += SpeedError;
	DutyCycle = (((long)Kps*(long)SpeedError + (long)Kis*(long)SpeedIntegral) >> 16);
        //	DutyCycle = (Kps*SpeedError +Kis*SpeedIntegral)>>8;

	PDC1 = PDC1 + DutyCycle;
	if (PDC1 < 5)
		{PDC1 = 5;SpeedIntegral = 0;}
	if (PDC1 > 1024)
		{PDC1 = 1024;SpeedIntegral = 0;}
	PDC2 = PDC1;
	PDC3 = PDC1;
        Flags.CalSpeed = 0;
}


//---------------------------------------------------------------------
// This is a generic 1ms delay routine to give a 1mS to 65.5 Seconds delay
// For N = 1 the delay is 1 mS, for N = 65535 the delay is 65,535 mS.
// Note that FCY is used in the computation.  Please make the necessary
// Changes(PLLx4 or PLLx8 etc) to compute the right FCY as in the define
// statement above.

void DelayNmSec(unsigned int N)
{
unsigned int j;
while(N--)
 	for(j=0;j < MILLISEC;j++);
}
