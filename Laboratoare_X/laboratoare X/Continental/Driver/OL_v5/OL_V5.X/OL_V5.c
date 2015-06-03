/* 
 * File:   OL_V5.c
 * Author: Eduard
 *
 * Created on April 10, 2014, 8:20 AM
 * BLDC Driver v_5 (Open_Loop)
 * Program for getting MCPWM`s Duty Cycle through SPI and
 * send wheel speed rotation
 */

//Core Configuration

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
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV_27         // Brown Out Voltage (4.5V)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config LPOL = PWMxL_ACT_HI      // Low-side PWM Output Polarity (Active High)
#pragma config HPOL = PWMxH_ACT_HI      // High-side PWM Output Polarity (Active High)
#pragma config PWMPIN = RST_PWMPIN       // PWM Output Pin Reset (Control with PORT/TRIS regs)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = PGD                // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)


// Definitions

#define FCY  10000000			// xtal = 10.0Mhz; PLLx4
#define MILLISEC FCY/10000			// 1 mSec delay constant
#define FPWM 39000
#define POLEPAIRS	2		// number of pole pairs
#define INDEX	1			// Hall sensor position index
#define S2      PORTDbits.RD1
#define SPEEDMULT	(2343750)     // wheel rot/s
#define SS      PORTBbits.RB2       // chip select


// Functions Prototypes
void InitADC10(void);
void InitMCPWM(void);
void InitTMR3(void);
void InitSPI(void);

// Global Variables

struct {
    unsigned SPI : 1;
    unsigned RunMotor : 1;
    unsigned unused : 14;
        }Flags;
unsigned int HallValue;
unsigned int timer3value;
unsigned int timer3avg;
unsigned char polecount;
unsigned int viteza;
unsigned char dc=0;
const unsigned char *dutycycle;
// State Tables

unsigned int StateLoTableClk[] = {0x0000, 0x0210, 0x2004, 0x0204,
                                        0x0801, 0x0810, 0x2001, 0x0000};
unsigned int StateLoTableAntiClk[] = {0x0000, 0x2001, 0x0810, 0x0801,
                                        0x0204, 0x2004, 0x0210, 0x0000};

// Interrupt Service Routines (ISR)

void __attribute__((interrupt,no_auto_psv)) _ADCInterrupt(void)
{
   // PDC1=dutycycle<<1;
    PDC1=*dutycycle;
    PDC2=PDC1;
    PDC3=PDC1;
    
    IFS0bits.ADIF=0; //Clear flag
}

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt (void)
{

	HallValue = PORTB & 0x0038;	// mask RB3,4 & 5
	HallValue = HallValue >> 3;	// shift right 3 times
	OVDCON = StateLoTableClk[HallValue];
	if (HallValue == INDEX)	// has the same position been sensed?
		if (polecount++ == POLEPAIRS)	//has one mech rev elasped?
		{								// yes then read timer3
		timer3value = TMR3;
		TMR3 = 0;
		timer3avg = ((timer3avg + timer3value) >> 1);
		polecount = 1;

		}
        IFS0bits.CNIF = 0;				// clear flag
}

void __attribute__((interrupt,no_auto_psv)) _SPI1Interrupt(void)
{
    dutycycle=&SPI1BUF;
    
    //Flags.SPI=1;
    IFS0bits.SPI1IF=0;          // Clear SPI interrupt flag
}

// Main
int main(void)
{       TRISD=3;

        //PORTD=3;
	LATE = 0x0000;
	TRISE = 0xFFC0;		// PWMs are outputs
	CNEN1 = 0x00E0;		// CN5,6 and 7 enabled
	CNPU1 = 0x00E0;		// enable internal pullups
        IFS0bits.CNIF = 0;	// clear CNIF
	IEC0bits.CNIE = 1;	// enable CN interrupt
        InitADC10();
	InitMCPWM();
	InitTMR3();
        InitSPI();
/*TRISBbits.TRISB2=1;
TRISEbits.TRISE8=1;
TRISFbits.TRISF3=0;
TRISFbits.TRISF2=1;*/
	timer3avg = 0;
	
		// read hall position sensors on PORTB
		
		polecount = 1;
                T3CONbits.TON = 1;
                while(1)
                    {
                    	// read hall position sensors on PORTB
		HallValue = PORTB & 0x0038;			// mask RB3,4 & 5
		HallValue = HallValue >> 3;			// shift right to get value 1, 2 ... 6
		OVDCON = StateLoTableClk[HallValue];	// Load the overide control register
		PWMCON1 = 0x0777;					// enable PWM outputs
		Flags.RunMotor = 1;					// set flag
		T3CONbits.TON = 1;			// start tmr3
		polecount = 1;
                while(Flags.RunMotor)           // while motor is running
                {
                  //  dc=80;
                    
                        viteza=SPEEDMULT/timer3avg;     // get speed in m/s
                            viteza/=12;
                        //    PDC1=200;
                        //    PDC2=PDC1;
                       //    PDC3=PDC1;
                        if(!SS)
                            {
                            //SPI1BUF=(char)viteza;          // Write the speed
                            SPI1BUF=viteza*2;
                            while(SPI1STATbits.SPITBF); // wait for transmission to complete
                            Nop();
                            Nop();
                            Nop();
                            Nop();
                            Nop();
                            dc=SPI1BUF;
                       //      dutycycle=dc<<1;
                            }
                       

                        }	// end of while (1)
                }

}


// Init functions
void InitADC10(void)
{

 ADPCFG = 0xFFFC;				// all PORTB = Digital;RB0 and RB1 = analog
 ADCON1 = 0x0064;				// PWM starts conversion
 ADCON2 =  0x0200;				// simulataneous sample 4 channels
 ADCHS = 0x0001;				// Connect RB1/AN1 as CH0 = pot
 ADCON3 = 0x0080;				// Tad = internal RC (4uS)
 IFS0bits.ADIF = 0;
 IEC0bits.ADIE = 1;

 ADCON1bits.ADON = 1;			// turn ADC ON
}
void InitMCPWM(void)
{
	PTPER = FCY/FPWM - 1;

	PWMCON1 = 0x0700;			// disable PWMs
	OVDCON = 0x0000;			// allow control using OVD
	PDC1 = 100;					// init PWM 1, 2 and 3 to 100
	PDC2 = PDC1;
	PDC3 = PDC1;
	SEVTCMP = PTPER;
	PWMCON2 = 0x0F00;		// 16 postscale values
  //      PWMCON2bits.IUE=1;
	PTCON = 0x8000;			// start PWM

}

void InitTMR3(void)
{
	T3CON = 0x0030;			// internal Tcy/256 clock
	TMR3 = 0;
	PR3 = 0xFFFF;
}

void InitSPI(void)
{
    SPI1BUF=0;
    IFS0bits.SPI1IF=0;
    IEC0bits.SPI1IE=1;
    IPC2bits.SPI1IP=5;      // interrupt priority
    SPI1CON=0x0080;     // CKE=0; CKP=0;
    SPI1CONbits.CKP=1;  // ckp=1;
    SPI1CONbits.CKE=0;  // cke=0;
    SPI1STATbits.SPIROV=0;
    SPI1STATbits.SPIEN=1;   // enable SPI

}