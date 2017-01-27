/*
 * File:   main.c
 * Author: eduard
 *
 * Created on January 27, 2017, 6:18 PM
 */


// PIC16F1503 Configuration Bit Settings


// PIC16F1503 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)


// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 8000000 // needed for use the delay functions

#define MY_LED_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)

void init_clock();
void init_led();
void toggle_led();

//void WDT_Initialize(void)
//{
//    // WDTPS 1:65536; SWDTEN OFF; 
//    WDTCON = 0x16;
//}


void main(void) 
{
    init_led();
    init_clock();
    
//    WDT_Initialize();
    
    while(1)
    {        
        toggle_led();
        __delay_ms(200);
    }
}

void init_clock()
{
    OSCCONbits.SCS = 0x00;      // FOSC
    OSCCONbits.IRCF = 0b1110; // 8MHz
//    OSCCON = 0x70;
}

void init_led()
{
    TRISAbits.TRISA2 = 0; // pin direction -> output
    LATA = 0x00;
    ANSELA = 0x00;
    APFCON = 0x00;

}

void toggle_led()
{
    LATAbits.LATA2 ^= 1;
}