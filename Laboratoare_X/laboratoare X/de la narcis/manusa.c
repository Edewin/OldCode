//Soltuzu Narcis Iosif (1403A)  --  LICENTA 2009 - MANUSA

#include <pic.h>

//rutinele definite mai jos functioneaza corect numai la frecventa de 20 MHz

#define WaitFor1Us asm("nop"); asm("nop")
#define Jumpback asm("goto $ - 3")

#define UP RC2
#define LEFT RC0
#define RIGHT RC1
#define DOWN RC3


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
//	SPBRG=15;	//19200 baud
//	BRGH=0;		//low speed

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
	TXREG=c;		//incarca si transmite noua valoare
}

char ad[]={0b00000001,0b00001001,0b00010001,0b00011001,0b00100001,0b00101001,0b00110001,0b00111001};


char readSENSOR(char c)	
	{			
		char sense=0b00000000;
		ADCON1=0b00000000;   	// Stabilire configurare intrari
		ADCON0=ad[c];			// Adresa canal  
		DelayMs(1);
		ADGO=1;		     		// Start conversie	
		while(ADGO==1);	     	// Sfarsit conversiei
	        sense=ADRESH;	    // Lectura date semnificative
		return sense;
	}

void main(void)
{
	char deget1, deget2, deget3, deget4, deget5, ay, ax, az;

	TRISA=0xFF;
	TRISE=0xFF;
	TRISC=0b10001111;	//RC7/RX intrare , RC6/TX iesire
    TRISB=0x00;

	InitUSART();
 
	for(;;)
	{	
		deget1=readSENSOR(0);  	// Achizitie date  deget1
			DelayMs(1);
		deget2=readSENSOR(1);  	// Achizitie date  deget2
			DelayMs(1);
		deget3=readSENSOR(2);  	// Achizitie date  deget3
			DelayMs(1);
		deget4=readSENSOR(3);  	// Achizitie date  deget4
			DelayMs(1);
		deget5=readSENSOR(4);  	// Achizitie date  deget5
			DelayMs(1);
		ay=readSENSOR(5);  	// Achizitie date  Y
			DelayMs(1);
		ax=readSENSOR(6);  	// Achizitie date  X
			DelayMs(1);
		az=readSENSOR(7);  	// Achizitie date  Z
			DelayMs(1);

	TransmitUSART('>');

		if(UP==0)
			TransmitUSART('F');
		else
		if(DOWN==0)
			TransmitUSART('B');
		else
		if(LEFT==0)
			TransmitUSART('L');
		else
		if(RIGHT==0)
			TransmitUSART('R');
		else
			TransmitUSART('S');

		TransmitUSART(ax);
		TransmitUSART(ay);
		TransmitUSART(deget1);
		TransmitUSART(deget2);
		TransmitUSART(deget3);
		TransmitUSART(deget4);
		TransmitUSART(deget5);


	}
}
