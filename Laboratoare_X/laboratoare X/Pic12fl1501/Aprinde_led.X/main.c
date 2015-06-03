#include <xc.h>
#define _XTAL_FREQ 8000000

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)
void init_pwm(void);
void init_adc(void);
void main(void)
{
    OSCCON=0b01110011;
    init_pwm();
    init_adc();
    unsigned char i;
    i=0;
    for(;;)
    {
       
        if(ADGO==0)
        {
            i=ADRESH;
            i=i*8;  // scalarea pentru fotorezistenta
            PWM4DCH=i;
            ADGO=1;
            
        }
        //if(TMR2IF==1)
       // {
           /* for(i=0;i<=84;i++)
            {
                   
                    PWM4DCH=i;
                   __delay_ms(10);
                  
                   if(i==84)
                   {
                       for(j=84;j>0;j--)
                       {
                           PWM4DCH=j;
                           __delay_ms(20);
                       }
                   }

          //  }
          //  TMR2IF=0;
        }*/
    }
}
void init_pwm(void)
{
    TRISAbits.TRISA5=1;
    PWM4CON=0;
    TMR2=0;
    PR2=0x65;
    PWM4DCH=0;
    PWM4DCL=0;
    T2CONbits.T2CKPS=0;
    T2CONbits.TMR2ON=1;
    TRISAbits.TRISA5=0;
    PWM4CONbits.PWM4POL=0;
    PWM4CONbits.PWM4OUT=1;
    PWM4CONbits.PWM4OE=1;
    PWM4CONbits.PWM4EN=1;
}
void init_adc(void)
{
    TRISAbits.TRISA4=1;
    ANSELAbits.ANSA4=1;
    ADCON1bits.ADCS=011; // FRC oscilator
    ADCON1bits.ADFM=0; // aliniati la stanga
    ADCON1bits.ADPREF=0; // VREF e conectat la VDD
    ADCON0bits.CHS=3;    // AN3
    ADCON0bits.ADON=1;  // ADC Pornit
    _delay(20);
    ADCON0bits.ADGO=1;

}