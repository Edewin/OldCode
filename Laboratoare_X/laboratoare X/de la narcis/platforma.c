//Soltuzu Narcis Iosif (1403A)  --  Licenta 2009 - PLATFORMA MOBILA + The Hand

#include <pic.h>

//rutinele definite mai jos functioneaza corect numai la frecventa de 20 MHz

#define WaitFor1Us asm("nop"); asm("nop")
#define Jumpback asm("goto $ - 3")

#define stanga RC3
#define dreapta RC2
#define rotatie RC1
#define articulatie RE1
#define dg1 RA3
#define dg2 RA1
#define dg3 RA5
#define dg4 RE0
#define dg5 RA2


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


void left(int n)
	{
	int i;
    stanga=1;
		DelayUs(250); //pozitionare la zero
		DelayUs(250);

 	for(i=0;i<n;i++)
    DelayUs(1); // avans unghi

	 stanga=0;
//		DelayMs(10); // repetare dupa 20 ms
	}

void right(int n)
	{
	int i;
    dreapta=1;
		DelayUs(250); //pozitionare la zero
		DelayUs(250);

 	for(i=0;i<n;i++)
    DelayUs(1); // avans unghi

	 dreapta=0;
//		DelayMs(10); // repetare dupa 20 ms
	}

void rotation(int n)
	{
	int i;
    rotatie=1;
		DelayUs(250); //pozitionare la zero
		DelayUs(250);

 	for(i=0;i<n;i++)
    DelayUs(1); // avans unghi

	 rotatie=0;
//		DelayMs(10); // repetare dupa 20 ms
	}

void articulation(int n)
	{
	int i;
    articulatie=1;
		DelayUs(250); //pozitionare la zero
		DelayUs(250);

 	for(i=0;i<n;i++)
    DelayUs(1); // avans unghi

	 articulatie=0;
//		DelayMs(10); // repetare dupa 20 ms
	}

void deget1(int n)
	{
	int i;
    dg1=1;
		DelayUs(250); //pozitionare la zero
		DelayUs(250);

 	for(i=0;i<n;i++)
    DelayUs(1); // avans unghi

	 dg1=0;
//		DelayMs(10); // repetare dupa 20 ms
	}

void deget2(int n)
	{
	int i;
    dg2=1;
		DelayUs(250); //pozitionare la zero
		DelayUs(250);

 	for(i=0;i<n;i++)
    DelayUs(1); // avans unghi

	 dg2=0;
//		DelayMs(10); // repetare dupa 20 ms
	}

void deget3(int n)
	{
	int i;
    dg3=1;
		DelayUs(250); //pozitionare la zero
		DelayUs(250);

 	for(i=0;i<n;i++)
    DelayUs(1); // avans unghi

	 dg3=0;
//		DelayMs(10); // repetare dupa 20 ms
	}

void deget4(int n)
	{
	int i;
    dg4=1;
		DelayUs(250); //pozitionare la zero
		DelayUs(250);

 	for(i=0;i<n;i++)
    DelayUs(1); // avans unghi

	 dg4=0;
//		DelayMs(10); // repetare dupa 20 ms
	}

void deget5(int n)
	{
	int i;
    dg5=1;
		DelayUs(250); //pozitionare la zero
		DelayUs(250);

 	for(i=0;i<n;i++)
    DelayUs(1); // avans unghi

	 dg5=0;
//		DelayMs(10); // repetare dupa 20 ms
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
	TX9=0;		//transmisei pe 8 biti
	TXEN=1; 	//activare transmisie 

	RCIE=0;		//dezactivare intrerupere USART la receptie
	RX9=0;		//receptie pe 8 biti
	CREN=1; 	//activare receptie
}

unsigned char ReceiveUSART()	//Rutina pt receptia unui octet de la portul serial
{
	unsigned char c;							

	while(!RCIF);	//asteapta pana se incheie receptia
	c=RCREG;	//octetul receptionat este preluat din RCREG	
	return c;	
}

void main(void)
{
	unsigned char ch,s,d1,d2,d3,d4,d5,x,y; 

		TRISA=0x00;		//PORTA iesire
		TRISE=0x00;
		TRISC=0b10000000;
		TRISD=0x00;

		PORTA=0x00;
		PORTE=0x00;
		PORTC=0x00;
		PORTD=0xFF;
   
	InitUSART();

for(;;)
{ 
ch=ReceiveUSART();	//receptionez caracterul

if (ch=='>')
{
	s=ReceiveUSART();
	x=ReceiveUSART();
	y=ReceiveUSART();
	d1=ReceiveUSART();
	d2=ReceiveUSART();
	d3=ReceiveUSART();
	d4=ReceiveUSART();
	d5=ReceiveUSART();

			DelayMs(2);	
//*******


		if (s=='S')
		{	left(194);
			right(186);	
			PORTD=0xFF;}
		
		else
		if (s=='R')
		{	left(214);
			right(206);	
			PORTD=~7;}

		else
		if (s=='L')
		{	left(174);
			right(166); 
			PORTD=~224;}

		else
		if (s=='B')
		{	left(174);
			right(206);	
			PORTD=~195;}

		else
		if (s=='F')
		{	left(214);
			right(166);	
			PORTD=~60;}

		else
		{	left(194);
			right(186);	
			PORTD=0xFF;}

//*******


		if (x>=96)
			rotation(10);
		else
		if (x<96 && x>=94)
			rotation(30);
		else
		if (x<94 && x>=92)
			rotation(50);
		else
		if (x<92 && x>=90)
			rotation(70);
		else
		if (x<90 && x>=89)
			rotation(90);
		else
		if (x<89 && x>=88)
			rotation(110);
		else
		if (x<88 && x>=87)
			rotation(130);
		else
		if (x<87 && x>=85)
			rotation(150);
		else
		if (x<85 && x>=83)
			rotation(170);
		else
		if (x<83 && x>=81)
			rotation(190);
		else
		if (x<81)
			rotation(210);
		else
			rotation(210);

//*******


		if (y>=112)
			articulation(80);
		else
		if (y<112 && y>=108)
			articulation(112);
		else
		if (y<108 && y>=104)
			articulation(144);
		else
		if (y<104 && y>=100)
			articulation(176);
		else
		if (y<100 && y>=98)
			articulation(208);
		else
		if (y<98 && y>=96)
			articulation(240);
		else
		if (y<96 && y>=92)
			articulation(272);
		else
		if (y<92 && y>=88)
			articulation(304);
		else
		if (y<88 && y>=84)
			articulation(336);
		else
		if (y<84 && y>=81)
			articulation(368);
		else
		if (y<81)
			articulation(400);
		else
			articulation(240);

//*******

		if (d1>=58)
			deget1(200);
		else
		if (d1<58 && d1>=55)
			deget1(185);
		else
		if (d1<55 && d1>=52)
			deget1(170);
		else
		if (d1<52 && d1>=49)
			deget1(155);
		else
		if (d1<49 && d1>=46)
			deget1(140);
		else
		if (d1<46 && d1>=43)
			deget1(125);
		else
		if (d1<43 && d1>=40)
			deget1(110);
		else
		if (d1<40 && d1>=37)
			deget1(95);
		else
		if (d1<37 && d1>=34)
			deget1(80);
		else
		if (d1<34 && d1>=31)
			deget1(65);
		else
		if (d1<31)
			deget1(50);
		else
			deget1(80);

//*******

		if (d2>=32)
			deget2(170);
		else
		if (d2<32 && d2>=30)
			deget2(158);
		else
		if (d2<30 && d2>=29)
			deget2(146);
		else
		if (d2<29 && d2>=27)
			deget2(134);
		else
		if (d2<27 && d2>=25)
			deget2(122);
		else
		if (d2<25 && d2>=23)
			deget2(110);
		else
		if (d2<23 && d2>=21)
			deget2(98);
		else
		if (d2<21 && d2>=19)
			deget2(86);
		else
		if (d2<19 && d2>=18)
			deget2(74);
		else
		if (d2<18 && d2>=17)
			deget2(62);
		else
		if (d2<17)
			deget2(50);
		else
			deget2(74);


//*******

		if (d3>=32)
			deget3(210);
		else
		if (d3<32 && d3>=30)
			deget3(190);
		else
		if (d3<30 && d3>=28)
			deget3(170);
		else
		if (d3<28 && d3>=26)
			deget3(150);
		else
		if (d3<26 && d3>=24)
			deget3(130);
		else
		if (d3<24 && d3>=22)
			deget3(110);
		else
		if (d3<22 && d3>=20)
			deget3(90);
		else
		if (d3<20 && d3>=18)
			deget3(70);
		else
		if (d3<18 && d3>=16)
			deget3(50);
		else
		if (d3<16 && d3>=14)
			deget3(35);
		else
		if (d3<14)
			deget3(20);
		else
			deget3(50);

//*******

		if (d4>=64)
			deget4(190);
		else
		if (d4<64 && d4>=60)
			deget4(170);
		else
		if (d4<60 && d4>=56)
			deget4(152);
		else
		if (d4<56 && d4>=52)
			deget4(134);
		else
		if (d4<52 && d4>=48)
			deget4(116);
		else
		if (d4<48 && d4>=44)
			deget4(98);
		else
		if (d4<44 && d4>=40)
			deget4(80);
		else
		if (d4<40 && d4>=36)
			deget4(62);
		else
		if (d4<36 && d4>=32)
			deget4(44);
		else
		if (d4<32 && d4>=30)
			deget4(26);
		else
		if (d4<30)
			deget4(8);
		else
			deget4(44);


//*******

		if (d5>=48)
			deget5(40);
		else
		if (d5<48 && d5>=44)
			deget5(70);
		else
		if (d5<44 && d5>=40)
			deget5(100);
		else
		if (d5<40 && d5>=36)
			deget5(130);
		else
		if (d5<36 && d5>=34)
			deget5(160);
		else
		if (d5<34 && d5>=31)
			deget5(190);
		else
		if (d5<31 && d5>=28)
			deget5(210);
		else
		if (d5<28 && d5>=25)
			deget5(240);
		else
		if (d5<25 && d5>=22)
			deget5(280);
		else
		if (d5<22 && d5>=18)
			deget5(320);
		else
		if (d5<18)
			deget5(350);
		else
			deget5(280);


		
}

}
}

