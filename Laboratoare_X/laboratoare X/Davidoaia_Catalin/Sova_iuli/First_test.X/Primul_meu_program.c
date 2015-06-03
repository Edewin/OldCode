/* 
 * File:   Primul_meu_program.c
 * Author: Eduard
 * program de semnalizare versiunea 1
 * 2 butoane pe ...
 * 2 leduri pe ...
 * Created on June 1, 2014, 4:47 PM
 */

// PIC16F684 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

#define _XTAL_FREQ 8000000
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Detect (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)


#define stanga PORTCbits.RC0
#define dreapta PORTCbits.RC1
#define buton_stanga PORTCbits.RC2
#define buton_dreapta PORTCbits.RC3

void main()
{
    /*
     * configurare oscilator
     */
    OSCCON=0b01110100;      // am ales frecventa de 8 MHz
    /*
     * configurare pini
     */
    TRISCbits.TRISC0=0;
    TRISCbits.TRISC1=0;
    TRISCbits.TRISC2=1;
    TRISCbits.TRISC3=1;
    /*initializare*/
    PORTC=0;
    /*bucla infinita*/
    for(;;)
    {
        stanga=0;
        dreapta=0;
        if(buton_dreapta)
        {
            dreapta=1;
            stanga=0;
            __delay_ms(1000);
            dreapta=0;
            stanga=0;
            __delay_ms(1000);
        }
        if(buton_stanga)
        {
            dreapta=0;
            stanga=1;
            __delay_ms(1000);
            dreapta=0;
            stanga=0;
            __delay_ms(1000);
        }
    }

}

