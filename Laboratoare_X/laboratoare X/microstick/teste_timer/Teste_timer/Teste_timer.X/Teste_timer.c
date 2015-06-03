/* 
 * File:   Teste_timer.c
 * Author: Eduard
 *
 * Created on January 30, 2014, 8:48 PM
 */


// DSPIC33FJ09GS302 Configuration Bit Settings

#include <xc.h>

// FICD
#pragma config ICS = PGD1               // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler bits (1:32,768)
#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
#pragma config PLLKEN = ON              // PLL Lock Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (Watchdog timer enabled/disabled by user software)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
#pragma config IOL1WAY = ON             // Peripheral pin select configuration (Allow only one reconfiguration)
#pragma config FCKSM = CSECME           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are enabled)

// FOSCSEL
#pragma config FNOSC = FRCPLL           // Oscillator Source Selection (Fast RC Oscillator with divide-by-N with PLL module (FRCPLL))
#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FGS
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GCP = OFF                // General Segment Code-Protect bit (General Segment Code protect is Disabled)

void init(void);
void init_TMR1(void);

//void delay(void);
unsigned int n=0,k=0;




void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt (void)
{
    IFS0bits.T1IF=0;
    TMR1=0;
    PR1=0x2000;
    LATAbits.LATA0^=1;
    //LATAbits.LATA0=~LATAbits.LATA0;
    /* n++;
    k++;
    n=n%2;
    PR1=0xffff;
    TMR1=0;
    if(n)
                LATAbits.LATA0=1;
            else
                LATAbits.LATA0=0;
  */

}

void main(void)
{
        init();
        init_TMR1();
        TRISAbits.TRISA0=0;
        while(1)
        {
          
            
        }
        
}



void init(void)
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

	while(ACLKCONbits.APLLCK != 1);	        /* Wait for Auxiliary PLL to Lock */
}
void init_TMR1(void)
{
    INTCON2bits.ALTIVT=1;
    T1CON=0x8030;
    PR1=0x6200;
    TMR1=0;
    INTCON1bits.NSTDIS=1;
    IPC0bits.T1IP=4;
    IFS0bits.T1IF=0;
    IEC0bits.T1IE=1;
}
void delay(unsigned int d)
{
    short z;
    while(d--)
        for(z=0;z<1000;z++);

}