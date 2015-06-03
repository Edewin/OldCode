/* 
 * File:   EUSART.c
 * Author: Eduard
 * PROGRAMUL nu functioneaza !!!!!!!!!!!!
 * Created on January 30, 2014, 12:00 PM
 */

// PIC12F1840 Configuration Bit Settings

#include <xc.h>

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)
void init_EUSART(void);
void delay(unsigned int d)
{short b;
    while(d--)
    {for(b=0;b<1000;b++)
        ;
    }
}

unsigned char v[]={"0000000000\r\n"};

void main(void)
{
    OSCCON=0b01110000;
    init_EUSART();
    unsigned char *Ptr,i;
   
    while(1)
    {
        for(i=0;i<16;i++)
        {
            v[i]=i;
            Ptr=&v[i];

        while(!TXIF)continue;
        TXREG=*Ptr;
        //  delay(2);
        }
    }
}

void init_EUSART(void)
{
    SPBRGH=0;
    SPBRGL=25;
    BRGH=1;
    BRG16=0;
    TXSTAbits.SYNC=0;
    TXIE=0;
    RCSTAbits.SPEN=1;
    TXSTAbits.TX9=0;
    TXSTAbits.TXEN=1;
    TRISAbits.TRISA0=0;

}