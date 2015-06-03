/* 
 * File:   main.c
 * Author: Andreea & Eduard
 *  Master mode
 * Created on December 30, 2013, 2:44 PM
 */


// PIC12F1840 Configuration Bit Settings

#include <xc.h>
#include <stdlib.h>

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)


void init(void);
void init_adc(void);
void init_spi(void);

void delay(void)
{
    short temp;
    for(temp=0;temp<255;temp++)
        ;
}
unsigned char Read_ad(void)
{
    unsigned char buf;
    while(ADCON0bits.ADGO)
        continue;
    buf=ADRESH;
    return buf;

}

/*void transmit_spi(unsigned char command)
{
  

    short temp;
    PORTAbits.RA5=0;    // activate Slave
    temp=SSP1BUF;
    SSP1BUF=command;
    if(SSPSTATbits.BF)
      //  continue;
    PORTAbits.RA5=1;    // bye bye Slave
}*/

void transmit_spi1 (unsigned char p)
{ //while (SSPSTATbits.BF) { }
PORTAbits.RA5=0;
short temp;
SSP1BUF = p;
while (!SSPSTATbits.BF);
temp=SSP1BUF;
PORTAbits.RA5=1;

}

void main(void)
{
    init();
    init_adc();
    init_spi();

    unsigned char val;
    val=0;
    for(;;)
    {
        
        for(val=0;val<250;val++)
        {   transmit_spi1(val);
        delay();}
        //_delay(12470);
        
    }
}

void init(void)
{
    OSCCON = 0b01110000;    // 32 MHz
    APFCON=0;
    GIE=0;
    TRISAbits.TRISA0 = 0;   // SDO
    TRISAbits.TRISA1 = 0;   // SCK
    TRISAbits.TRISA2 = 0;   // SDI
    TRISAbits.TRISA5 = 0;   // SS
    INTCON=0;
}

void init_adc(void)
{
    TRISAbits.TRISA4 = 1;   // AN3
    ANSELAbits.ANSA4 = 1;   // Analog

    ADCON1bits.ADCS = 0b011;   // FRC clock
    ADCON1bits.ADPREF = 0;  // Vref connected to Vdd
    ADCON1bits.ADFM = 0;    // Left justified

    ADCON0bits.CHS = 0b00011; // AN3 Input Channel
    ADCON0bits.ADON = 1;    // ADC is enabled
    _delay(15);
    ADCON0bits.ADGO = 1;    // Go go Power Ranger
}

void init_spi(void)
{
    SSP1CON1bits.SSPEN=0;            // disable SPI module
    /*SSPSTATbits.CKE = 1;    // transmit occurs on transition from idle to active
    SSPSTATbits.SMP = 1;    // Input data sample at middle of data output time
    SSP1CON1bits.SSPM = 0b0010; // SPI master mode clock FOSC/64
    SSP1CON1bits.CKP = 1;   // idle state for clock is low level
     */
    SSPSTAT=0b01000000;
    SSP1CON1=0b00010000;
    SSP1CON3=0;
    SSP1CON1bits.SSPEN=1;   // SPI Enabled

}