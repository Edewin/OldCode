//experiment 7 - Com. seriala - transmisie catre com1 caracter, mod continuu

//Programul tramsmite in mod continuu un text catre portul serial COM1

#include <htc.h>

//rutinele definite mai jos functioneaza corect numai la frecventa de 20 MHz

#define WaitFor1Us asm("nop"); asm("nop")
#define Jumpback asm("goto $ - 3")

unsigned char delayus_variable;

//maxim 255 us
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

void InitUSART() //rutina de setare si initializare a modulului USART
{
	SPBRG=64;	//19200 baud
	BRGH=1;		//high speed
	SYNC=0;		//modul asincron
	SPEN=1;		//activare port serial

	TXIE=0;		//dezactivare intrerupere USART la transmisie
	TX9=0;		//transmisie pe 8 biti
	TXEN=1; 	//activare transmisie

	RCIE=0;		//dezactivare intrerupere USART la receptie
	RX9=0;		//receptie pe 8 biti
	CREN=1; 	//activare receptie
}

void TransmitUSART(unsigned char c)	//Rutina de transmitere a unui octet la portul serial
{
	while(!TXIF);	//asteapta sa se termine transmisia precedenta
	TXREG=c;	//incarca si transmite noua valoare
}
unsigned char RecieveUsart()
{
    while(!RCIF);
    return RCREG;
}

void main(void)
{
	unsigned char text[20]={'0','1','2','3','4','5','6','7','8','9',13,10};
	unsigned int s,u,z,s1,u1,z1,nr;
        unsigned int i,i1;
	TRISC=0b10000000;	//RC7/RX intrare , RC6/TX iesire
    TRISB=0b00000110;	//RB2 - intrare
  //  i=100;
	InitUSART();
           
	for(;;)
	{

           
                
		if(!RB2)
		
		{
                    i1=RecieveUsart();
DelayMs(150); 
       /*        // s1=i1%10;
                s1=s1*100;
                //z1=i1%10;
                z1=z1*10;
                u1=i1%10;
                nr=s1+z1+u1;
           DelayMs(150); 
                    i=nr;
                    s=i/100;
                    s=s%10;
                    z=i/10;
                    z=z%10;
                    u=i%10;
*/
		//	TransmitUSART(text[s]);
                  //      TransmitUSART(text[z]);
                        TransmitUSART(text[i1]);
                        TransmitUSART(59);
                        TransmitUSART(10);
			DelayMs(150);
                     //   i+=1;
		}
	}
}
