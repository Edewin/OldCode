/* 
 * File:   CONTI.c
 * Author: Eduard
 *
 * Created on April 11, 2014, 1:48 PM
 */

// DSPIC30F2010 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// FOSC
#pragma config FPR = XT_PLL4            // Primary Oscillator Mode (XT w/PLL 4x)
#pragma config FOS = PRI                // Oscillator Source (Primary Oscillator)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_8         // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_8       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF             // Watchdog Timer (Enabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV_27         // Brown Out Voltage (2.7V)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config LPOL = PWMxL_ACT_HI      // Low-side PWM Output Polarity (Active High)
#pragma config HPOL = PWMxH_ACT_HI      // High-side PWM Output Polarity (Active High)
#pragma config PWMPIN = RST_IOPIN       // PWM Output Pin Reset (Control with PORT/TRIS regs)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = PGD                // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)


#define FCY  10000000			// xtal = 10.0Mhz; PLLx4
#define MILLISEC FCY/10000			// 1 mSec delay constant
#define FPWM 39000
#define POLEPAIRS	2		// number of pole pairs
#define INDEX	1			// Hall sensor position index

#define Sens	PORTDbits.RD0

#define SPEEDMULT	2343750

void InitCN();
void InitMCPWM(void);
void InitTMR3(void);
void InitSPI(void);



struct {
			unsigned RunMotor : 	1;
			unsigned SndSpeed :		1;
                        unsigned sens   :   1;
			unsigned unused 	:	13;
		}	Flags;

unsigned int HallValue;
unsigned int timer3value;
unsigned int timer3avg;
unsigned char polecount;
unsigned char desired_speed=0;
unsigned int viteza_rotii=0;


/*************************************************************
	High side driver table is as below.  In the StateLoTableClk
	and the StateLoTableAntiClk tables, the High side driver is
	PWM while the Low side driver is either on or off.
*************************************************************/

unsigned int StateLoTableClk[] = {0x0000, 0x0210, 0x2004, 0x0204,
					0x0801, 0x0810, 0x2001, 0x0000};
unsigned int StateLoTableAntiClk[] = {0x0000, 0x2001, 0x0810, 0x0801,
					0x0204, 0x2004, 0x0210, 0x0000};


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
   
	 IFS0bits.CNIF = 0;                // clear flag
	HallValue = PORTB & 0x0038;	// mask RB3,4 & 5
	HallValue = HallValue >> 3;	// shift right 3 times
        Flags.sens=Sens;
        if(Flags.sens)
            OVDCON = StateLoTableClk[HallValue];
        else
            OVDCON = StateLoTableAntiClk[HallValue];
	if (HallValue == INDEX)	// has the same position been sensed?
		if (polecount++ == POLEPAIRS)	//has one mech rev elasped?
		{								// yes then read timer3
		timer3value = TMR3;
		TMR3 = 0;
		timer3avg = ((timer3avg + timer3value) >> 1);
		polecount = 1;

		}
       
}
//---------------------------------------------------------------------

void __attribute__((interrupt,no_auto_psv)) _SPI1Interrupt (void)
{

    desired_speed=SPI1BUF;

    if(SPI1STATbits.SPIROV)
    {
        SPI1STATbits.SPIROV=0;
    }
    Flags.SndSpeed=1;
    IFS0bits.SPI1IF=0;          // Clear flag
}




int main(void)
{

        ADPCFG=0xFF;    // All pins are Digital
        TRISDbits.TRISD0=1;     // Sensul
	LATE = 0x0000;
        InitCN();
        InitMCPWM();
	InitTMR3();
        InitSPI();
	timer3avg = 0;
	while(1)
	{		
		// read hall position sensors on PORTB
		HallValue = PORTB & 0x0038;			// mask RB3,4 & 5
		HallValue = HallValue >> 3;			// shift right to get value 1, 2 ... 6
                Flags.sens=Sens;
                if(Flags.sens)
                    OVDCON = StateLoTableClk[HallValue];	// Load the overide control register
                else
                    OVDCON = StateLoTableAntiClk[HallValue];
                PWMCON1 = 0x0777;					// enable PWM outputs
		Flags.RunMotor = 1;					// set flag
		T3CONbits.TON = 1;			// start tmr3
		polecount = 1;
                
		while (Flags.RunMotor)				// while motor is running
			{
                    Flags.sens=Sens;             
                    PDC1=desired_speed;                 
                    PDC2=PDC1;
                    PDC3=PDC1;
                    if(Flags.SndSpeed)
                    {
                         viteza_rotii=SPEEDMULT/timer3avg;
                         viteza_rotii=(viteza_rotii/3)>>2;
                         SPI1BUF=viteza_rotii;          
                         Flags.SndSpeed=0;
                    }
                    	
			
			}
	}	// end of while (1)


}


void InitCN(void)
{
        IPC3bits.CNIP=7;        // CN interrupt priority
	CNEN1 = 0x00E0;		// CN5,6 and 7 enabled
	CNPU1 = 0x00E0;		// enable internal pullups
	IFS0bits.CNIF = 0;	// clear CNIF
	IEC0bits.CNIE = 1;	// enable CN interrupt
}


/********************************************************************
InitMCPWM, intializes the PWM as follows:
1. FPWM = 16000 hz
2. Independant PWMs
3. Control outputs using OVDCON
4.	Set Duty Cycle with the ADC value read from pot
5. Set ADC to be triggered by PWM special trigger
*********************************************************************/

void InitMCPWM(void)
{
        TRISE = 0xFFC0;		// PWMs are outputs
	PTPER = FCY/FPWM - 1;   // PWM period
	PWMCON1 = 0x0700;	// disable PWMs
	OVDCON = 0x0000;	// allow control using OVD
	PDC1 = 100;		// init duty cycle 1, 2 and 3 to 100
	PDC2 = 100;
	PDC3 = 100;
	SEVTCMP = PTPER;
	PWMCON2 = 0x0F04;	// 16 postscale values
	PTCON = 0x8000;		// start PWM

}


/************************************************************************
Tmr3 is used to determine the rotor speed so it is set to count using Tcy/256

*************************************************************************/


void InitTMR3(void)
{
	T3CON = 0x0030;			// internal Tcy/256 clock
	TMR3 = 0;                       // reset TMR3
	PR3 = 0xFFFF;                   // max period
}

void InitSPI(void)
{
    SPI1BUF=0;              // initializare memorie tampon
    IFS0bits.SPI1IF=0;      // sterge flag-ul pentru intrerupere
    IEC0bits.SPI1IE=1;      // activeaza intreruperi pentru SPI
    IPC2bits.SPI1IP=5;      // interrupt priority
    SPI1CON=0;              // resetare SPI1CON
    SPI1CONbits.MSTEN=0;    // Slave Mode
    SPI1CONbits.SSEN=1;     // Slave Select activ
    SPI1CONbits.MODE16=1;   // comunicare pe 16 biti
    SPI1CONbits.CKP=0;      // CKP=0;
    SPI1CONbits.CKE=1;      // CKE=1;
    SPI1STATbits.SPIROV=0;  // initializare bit de overflow
    SPI1STATbits.SPIEN=1;   // activeaza SPI
}

