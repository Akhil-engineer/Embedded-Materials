#include"includes.h"
OS_STK s1[128];
OS_STK s2[128];
char a=0;
void blink();
void uart();

int main()
{
DDRA=0xFF;
PORTA=0x00;
TCCR0=0x07;
TIMSK=0x01;

char data;
UBRR0L=103;
UCSR0A=0X00;
UCSR0B=0X18;//Tx Rx enabled
UCSR0C=0X06;//8bit async

OSInit();
OSTaskCreate(blink,0xFF,&s1[127],4);
OSTaskCreate(uart,0xFF,&s2[127],5);
OSStart();
}

void blink()
{
	while(1)
	{
		a=~a;
		PORTA=a;
		OSTimeDly(61);
	}
}
void uart()
{
while(1)
{
UDR0='A';
while((UCSR0A&(1<<6))==0);
OSTimeDly(61);
}
}
