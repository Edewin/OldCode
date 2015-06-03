/* 
 * File:   main.c
 * Author: Andreea & Eduard
 *  UART_pic16f876a
 * Created on December 25, 2013, 11:26 AM
 */
// PIC16F876A Configuration Bit Settings

#include <xc.h>
#include<stdlib.h>
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
//char * itoa (char *buf, int val, int base);
void init_UART(void);
/*void transmit(char i)
{
    while(!TXIF)
        continue;
        TXREG=i;
}
*/




void delay(void)
{
    short i,j,k;
   // for(k=0;k<4;k++)
  //  {
    for(j=0;j<32;j++)
        {
        for(i=0;i<255;i++)
            ;
        }
    //}
}
void main()
{
   unsigned char text[20]={'E','D','U','A','R','D','1','9','9','0',10,13};
	 int i, j;
        char buf[8];
    init_UART();
    TRISB=0xff;
//    TRISC=0xff;

    while(1)
    {
      //  if(!RB2)
      //  {
        i=rand();
           itoa(buf,i,16);
           while(!TXIF)
               continue;
           for(j=0;j<4;j++)
           { TXREG=buf[j];
            delay();
           }
          
           delay();
           TXREG=10;
           TXREG=13;
        
   // }
    }
}

void init_UART(void)
{

    SPBRG=129;  // pentru 20 MHz baud rate 9600
    TXSTAbits.BRGH=1;   //High speed mode ON
    TXSTAbits.SYNC=0;   // Asynchronous mode ON
    RCSTAbits.SPEN=1;   // Serial port enable
    TXIE=0;             // no interrupts
    TXSTAbits.TX9=0;    // 8 bit transmission
    TXSTAbits.TXEN=1;   // Transmision Enabled
    TRISCbits.TRISC6=1; // pin de iesire TX
    TRISCbits.TRISC7=0; // pin de intrare RX

}
