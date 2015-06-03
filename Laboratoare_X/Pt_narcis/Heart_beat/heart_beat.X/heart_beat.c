/*
 * File:   main.c
 * Author: Eduard
 *
 * Created on December 9, 2013, 6:57 AM
 * Program care simuleaza bataile inimii pe led-uri
 * Iesirea este pe RA2, iar potentiometrul este pe RA4
 */

// PIC12F1840 Configuration Bit Settings

#include <xc.h>
#define _XTAL_FREQ 32000000

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
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

void init(void);
void init_adc(void);
void init_eccp(void);
void delay_us(unsigned int d);
void delay_nr(unsigned int Da);
unsigned char read_ad(void)
{   unsigned temp=0;
    while(ADCON0bits.ADGO);    // asteapta sfarsitul conversiei

        temp=ADRESH;        // incarca valoarea
        ADCON0bits.ADGO=1;
        temp/=16;
        return temp;
}

void main(void)
{
    unsigned char x,y;
    x=0;
    init();
    init_adc();
    init_eccp();
    for(;;)
    {
     /*   x=read_ad();
        CCPR1L=0;
        delay_nr(x);
        CCPR1L=150;
        delay_nr(x);
*/
            x=read_ad();
            CCPR1L=0;
            delay_nr(x*24);
            for(y=3;y<160;y++)
            {x=read_ad();
            CCPR1L=y;
            delay_us(x*50);
            //  __delay_us(700);
            //delay_nr(x/4);
            }
              for(y=160;y>=3;y--)
            {x=read_ad();
            CCPR1L=y;
            delay_us(x*50);
            //       __delay_us(700);
            // delay_nr(x/4);
            }
            CCPR1L=0;
            delay_nr(x*8);
            for(y=3;y<160;y++)
            {x=read_ad();
            CCPR1L=y;
            delay_us(x*100);
            //   __delay_us(900);
            }
              for(y=160;y>=3;y--)
            {x=read_ad();
            CCPR1L=y;
            delay_nr(x/4);
            }
            CCPR1L=0;
            delay_nr(x*24);
        
    }
}
void init(void)
{
    //Configurarea Oscilatorului
    OSCCONbits.SCS=0;
    OSCCONbits.IRCF=0b1110;
    //Configurarea Pinilor
    APFCONbits.CCP1SEL=0;    // CCP1/P1A se afla pe pinul RA2
    APFCONbits.P1BSEL=0;    // P1B se afla pe pinul RA0
    PORTA=0;
}

void init_adc(void)
{

    ADCON1bits.ADCS=0b011;     // ADC conversion clock is FRC
    ADCON1bits.ADPREF=0;      // VREF este conectat la VDD
    ADCON1bits.ADFM=0;       // Aliniere la stanga numai 2 biti sunt in ADRESL
    TRISAbits.TRISA4=1;
    ANSELAbits.ANSA4=1;         // ADC pin pe RA4
    ADCON0bits.CHS=0b00011; // AN3
    ADCON0bits.ADON=1;     // ADC activat
    __delay_us(10);
    ADCON0bits.ADGO=1;
}
void init_eccp(void)
{
    TRISAbits.TRISA0=1;
    TRISAbits.TRISA2=1;
    PR2=0xff;
    CCP1CONbits.P1M=0;  // single output PWM
    CCP1CONbits.CCP1M=0b1100;   // PWM activ pe 1 logic
    CCP1CONbits.DC1B=0;
    CCPR1L=10;  // init value
    PIR1bits.TMR2IF=0;
    T2CONbits.T2CKPS=2;   // prescaler 16 pentru 2
                            // prescaler 01 pentru 4
    T2CONbits.TMR2ON=1;
  //  PWM1CONbits.P1DC=50;    // delay= 12.5 us
   // if(PIR1bits.TMR2IF==1)


        TRISAbits.TRISA2=0; // PWM-ul este pe pinul RA2


}

void delay_nr(unsigned int Da)
{
   unsigned int att;
while(Da--)
    for(att=0;att<1000;att++);
}
void delay_us(unsigned int d)
{
    unsigned char temp;
    while(d--)
        for(temp=0;temp<=1;temp++);

}