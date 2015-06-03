/*
 * File:   main.c
 * Author: Eduard
 *
 * Created on December 9, 2013, 6:57 AM
 * Half bridge pentru a testa driverul IR2101
 */

// PIC12F1840 Configuration Bit Settings

#include <xc.h>
#define _XTAL_FREQ 8000000
// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Detect (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)


void init(void);
void init_adc(void);
void init_eccp(void);
void main()
{
    unsigned char x;
    x=0;
    init();
    init_adc();
    init_eccp();
    for(;;)
    {
        if(ADCON0bits.GO==0)
        {
            ADCON0bits.GO=1;
            x=ADRESH;
          //  x=x>>2;
          //  x=x*8;
            CCPR1L=x;

        }
    }
}
void init(void)
{
    //Configurarea Oscilatorului
    OSCCON=0b01110100;

    //Configurarea Pinilor
   // APFCONbits.CCP1SEL=0;    // CCP1/P1A se afla pe pinul RA2
  //  APFCONbits.P1BSEL=0;    // P1B se afla pe pinul RA0
  //  PORTA=0;
}

void init_adc(void)
{

    ADCON1bits.ADCS=0b011;     // ADC conversion clock is FRC
    ADCON0bits.VCFG=0;      // VREF este conectat la VDD
    ADCON0bits.ADFM=0;       // Aliniere la stanga numai 2 biti sunt in ADRESL
    TRISCbits.TRISC0=1;
    ANSELbits.ANS4=1;         // ADC pin pe RC0
    ADCON0bits.CHS=0b100; // AN4
    ADCON0bits.ADON=1;     // ADC activat
    __delay_us(10);
    ADCON0bits.GO=1;
}
void init_eccp(void)
{
    TRISCbits.TRISC4=1;
    TRISCbits.TRISC5=1;
    PR2=0x65;
    CCP1CONbits.PM=0b10;
    CCP1CONbits.CCP1M=0b1100;
    CCP1CONbits.DCB=0;
    CCPR1L=0;
    PIR1bits.TMR2IF=0;
    T2CONbits.T2CKPS=0;   // prescaler 0 pentru 1
                            // prescaler 01 pentru 4
    T2CONbits.TMR2ON=1;
    PWM1CONbits.PDC=50;    // delay= 12.5 us
   // if(PIR1bits.TMR2IF==1)

        TRISCbits.TRISC4=0;
        TRISCbits.TRISC5=0;


}
