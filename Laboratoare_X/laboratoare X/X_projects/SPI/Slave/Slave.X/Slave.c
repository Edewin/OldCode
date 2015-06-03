/* 
 * File:   Slave.c
 * Author: Andreea & Eduard
 *  Slave Mode
 * Created on January 1, 2014, 7:41 PM
 */


// PIC12F1840 Configuration Bit Settings

#include <xc.h>


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

#define _XTAL_FREQ 8000000
/****************************************/
#define FOSC    8000000
#define FCY     FOSC/4
#define Milisec FCY/2000
#define Volum   CCPR1L
#define Note    PR2
/****************************************/
//Delay de la  1 ms la 65.5 s
/****************************************/
void delay(unsigned int N)
{
    unsigned int i;
    while(N--)
    for(i=0;i<Milisec;i++);
}

/*void delay(void)
{unsigned char j;
    for(j=0;j<255;j++)
    {}
}
*/



void init(void);
void init_ad();
void init_pwm(void);

unsigned char Read_ad1(void)
{
    unsigned char buf;
    while(GO)
        continue;
    GO=1;
    buf=ADRESH;
    return buf;

}

void main(void)
{
    init();
    init_pwm();
    init_ad();
 
 unsigned char i,j,n;
   i=0;
   j=0;
   n=0;
    for(;;)
    {
       CCPR1L=30;
       if(!PORTAbits.RA2)
       {__delay_ms(1);
           if(!PORTAbits.RA2)
           
           n=n+1;

       }
       i=Read_ad1();
       i=i>>3;
                   
       //i=Read_ad;
        switch (n%2){
                case 1:
                    j=i;
                    i=32-i;
                    CCPR1L=j;
                    delay(i);
                    CCPR1L=0;
                    delay(i);
                break;                             
                default:
                    i=i+4;
                    j=35-i;
                    j=j/6;
                    CCPR1L=j;

                    delay(i);
                    CCPR1L=0;
                    delay(i);
                    
                break;}
       
    }
      
   }


void init(void)
{
    OSCCON = 0b01110100;    // 32 MHz fara pll 8 MHz

    TRISAbits.TRISA2 = 1;
   

    ANSELbits.ANS2=0;
     CMCON0bits.CM=0b111;
 
    INTCON=0;
   

}



void init_pwm(void)
{
  TRISCbits.TRISC5=1;   // protect pin

  PR2=0x65;
  CCPR1L=20;
  CCP1CON= 0b00001100;
  PIR1bits.TMR2IF=0;
  T2CONbits.T2CKPS=0b10 ;   // prescaler is 16
  T2CONbits.TMR2ON=1;   // enable TIMER2
 // PWM1CONbits.P1DC = 10;    // dead time
  TRISCbits.TRISC5=0;   // protect pin
//  TRISAbits.TRISA4=0;

}


void init_ad(void)
{
    TRISCbits.TRISC2 = 1;   // AN6
    ANSELbits.ANS6 = 1;   // Analog
  //ANSEL=0;
    ADCON1=0;   // FRC clock
    ADCON0bits.VCFG = 0;  // Vref connected to Vdd
    ADCON0bits.ADFM = 0;    // LEFT justified
  //  ADIF=0;
    //ADIE=1;
    //INTCONbits.PEIE=1;
    //INTCONbits.GIE=1;
    ADCON0bits.CHS = 0b110; // AN6 Input Channel
    ADCON0bits.ADON = 1;    // ADC is enabled
    __delay_us(15);
    ADCON0bits.GO = 1;    // Go go Power Ranger
}
/*void interrupt functia_de_intrerupere(void)
{
    if(ADIF)
    {
        ADIF=0;
        Read_ad=ADRESH;
    }
    if(INTF)
    {
        INTF=0;
        n=n+1;
    }
}
 */