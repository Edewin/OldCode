/* 
 * File:   v_3.c
 * Author: Eduard
 *
 * Created on May 14, 2014, 7:25 PM
 */

#include <xc.h>

#define inainte_s 250
#define inapoi_s 10
#define stop_s 195
#define stop_d 198
#define inapoi_d 240
#define inainte_d 1
#define start PORTBbits.RB4
#define stanga PORTBbits.RB2
#define dreapta PORTBbits.RB3

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define WaitFor1Us asm("nop"); asm("nop")
#define Jumpback asm("goto $ - 3")

unsigned char delayus_variable;

//maxim 255 microsecunde
#define DelayUs(x) { \
			delayus_variable=(unsigned char)x; \
			WaitFor1Us; } \
			asm("decfsz _delayus_variable,f"); \
			Jumpback;

//maxim 255 ms
void DelayMs(unsigned char cnt)
{
	unsigned char	i;
	do {
		i = 4;
		do {
			DelayUs(250);
		} while(--i);
	} while(--cnt);
}
void motor_dreapta(char t)
	{
		PORTBbits.RB0=1;
                DelayUs(250);
                DelayUs(250);
               // DelayUs(200);
               
		//DelayMs(1); //pozitionare la zero

        DelayUs(t); // avans unghi
        DelayUs(t);
        DelayUs(t);
        DelayUs(t);
        DelayUs(t); 
	    PORTBbits.RB0=0;
		DelayMs(20); // repetare dupa 20 ms
	}

void motor_stanga(char t)
	{
		PORTBbits.RB1=1;
                DelayUs(250);
                DelayUs(250);
               // DelayUs(200);

		//DelayMs(1); //pozitionare la zero

        DelayUs(t); // avans unghi
        DelayUs(t);
        DelayUs(t);
        DelayUs(t);
        DelayUs(t);
	    PORTBbits.RB1=0;
		DelayMs(20); // repetare dupa 20 ms
	}


void main(void)
{
int i;
	TRISB=0b11111100;	//RB0 si RB1 iesiri, restul intrari
     PORTBbits.RB0=0;
     PORTBbits.RB1=0;
     PORTB=0;


	for(;;)		//executia programului se repeta in continuu
	{
            while(!start)
            {
                
            motor_dreapta(stop_d);
            motor_stanga(stop_s);
            while(start)
            {
                motor_dreapta(inainte_d);
                motor_stanga(inainte_s);
        
                if(stanga && !dreapta)
                {
                    motor_dreapta(inainte_d);
                    motor_stanga(inapoi_s);
                }
                if(dreapta && !stanga)
                {
                    motor_dreapta(inapoi_d);
                    motor_stanga(inainte_s);
                }
                if(!stanga && !dreapta)
                {
                motor_dreapta(stop_d);     // 197 e frana pentru m1
                motor_stanga(stop_s);
                }
            }
			}
	}
}
     

