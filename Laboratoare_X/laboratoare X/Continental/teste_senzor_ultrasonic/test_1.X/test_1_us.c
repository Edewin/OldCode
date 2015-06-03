/* 
 * File:   test_1_us.c
 * Author: Eduard
 *
 * Created on May 1, 2014, 8:55 PM
 */

// DSPIC33FJ128MC802 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
#pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure segment may be written)
#pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
#pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = FRCPLL           // Oscillator Mode (Internal Fast RC (FRC) w/ PLL)
#pragma config IESO = ON                // Internal External Switch Over Mode (Start-up device with FRC, then automatically switch to user-selected oscillator source when ready)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Source (Primary Oscillator Disabled)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function (OSC2 pin has digital I/O function)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow Only One Re-configuration)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)
#pragma config LPOL = ON                // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-high output polarity)
#pragma config HPOL = ON                // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config PWMPIN = ON              // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)

// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

void write_SPI(short command)
{
	short temp;

	PORTGbits.RG15 = 0;		// lower the slave select line
	temp = SPI2BUF;			// dummy read of the SPI1BUF register to clear the SPIRBF flag
	SPI2BUF = command;		// write the data out to the SPI peripheral
    while (!SPI2STATbits.SPIRBF)	// wait for the data to be sent out
		;
	PORTGbits.RG15 = 1;		// raise the slave select line
}

void delay(void)
{
	short temp;
	for (temp=0;temp<255;temp++);

}

void Init_SPI(void)
{

	// setup the SPI peripheral
	SPI2STAT = 0x0;  // disable the SPI module (just in case)
	SPI2CON1 = 0x0161;	// FRAMEN = 0, SPIFSD = 0, DISSDO = 0, MODE16 = 0; SMP = 0; CKP = 1; CKE = 1; SSEN = 0; MSTEN = 1; SPRE = 0b000, PPRE = 0b01
	SPI2CON1bits.CKE = 0x01;
	SPI2CON1bits.CKP = 0x00;
	SPI2STAT = 0x8000; // enable the SPI module

}
int main(void)
{

	short i,j;

// Configure Oscillator to operate the device at 40Mhz
// Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
// Fosc= 8M*40/(2*2)=80Mhz for 8M input clock
	PLLFBD=38;					// M=40
	CLKDIVbits.PLLPOST=0;		// N1=2
	CLKDIVbits.PLLPRE=0;		// N2=2
	OSCTUN=0;					// Tune FRC oscillator, if FRC is used


// Disable Watch Dog Timer
	RCONbits.SWDTEN=0;

// Clock switching to incorporate PLL
	__builtin_write_OSCCONH(0x03);		// Initiate Clock Switch to Primary
													// Oscillator with PLL (NOSC=0b011)
	__builtin_write_OSCCONL(0x01);		// Start clock switching
	while (OSCCONbits.COSC != 0b011);	// Wait for Clock switch to occur

// Wait for PLL to lock
	while(OSCCONbits.LOCK!=1) {};

	TRISA = 0x0;				// set to all outputs

	// setup the SPI1 port
	// setup the I/O pins properly (SDI1 as input, SDO1 as output, RG3 as output)
        
	AD1PCFGL =0xffff;		// set the RB0 pin to Digital Mode (all others to analog)
	TRISF = 0x0080;				// set PORTF to output except for SDI1
        RPINR7BITS.IC1R=11; //RB11





	while(OSCCONbits.LOCK!=1) {}; /* Wait for PLL to lock*/


	while(1)
	{
		//demonstrate the SPI peripheral in Master Mode CKE = 0, CKP = 0

			Init_SPI();

		for (i=0;i<255;i++)
			{
				write_SPI(i);
				delay();
			}


	}
}