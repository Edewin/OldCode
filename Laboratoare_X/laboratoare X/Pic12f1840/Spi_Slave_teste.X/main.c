/* 
 * File:   main.c
 * Author: Eduard
 *
 * Created on December 5, 2013, 8:45 PM
 */
#include<xc.h>

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)



void init_spi(void);
void main(void)
{
    void init_spi();
    PIE1bits.SSP1IE=1;
    INTCONbits.PEIE=1;
    INTCONbits.GIE=1;
    unsigned char data;
    data=0;
    for(;;)
    {
        if(SSP1IE && SSP1IF)
            {SSP1IF=0;
            data=SSP1BUF;
            
            }

    }
}
void init_spi(void)
{
    TRISAbits.TRISA0=0;     // SDO
    TRISAbits.TRISA1=1;     // SCK
    TRISAbits.TRISA2=1;     // SDI
    TRISAbits.TRISA3=1;     // SS
    TRISAbits.TRISA4=0;     // NC
    TRISAbits.TRISA5=0;     // I/O sau PWM
    SSP1CON1bits.WCOL=0;    // no colision
    SSP1CON1bits.SSPOV=0;   // no overflow
    SSP1CON1bits.CKP=0;     // polarity
    SSP1CON1bits.SSPM=4;    // SPI Slave mode cu SS activ
    SSP1CON1bits.SSPEN=1;   // SPI Enable
    SSPSTATbits.SMP=0;      // Slave mode
    SSPSTATbits.CKE=0;      // Polarity
    SSPSTATbits.BF=0;       // Buffer Full
    SSP1CON3bits.BOEN=0;    // Fara overwrite
}