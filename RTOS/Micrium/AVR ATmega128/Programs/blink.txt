#include"includes.h"
OS_STK s1[128];
char a=0;
void blink();

int main()
{
DDRA=0xFF;
PORTA=0x00;
TCCR0=0x07;
TIMSK=0x01;
OSInit();
OSTaskCreate(blink,0xFF,&s1[127],4);
OSStart();
}

void blink()
{
	while(1)
	{
		a=~a;
		PORTA=a;
		OSTimeDlyHMSM(0,0,1,0);
	}
}
