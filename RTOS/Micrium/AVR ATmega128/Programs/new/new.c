#include"includes.h"
#include<string.h>
OS_STK s1[128];
OS_STK s2[128];

char d[20];
int result;

void adc();
void uart();

int main()
{


ADMUX=0x40;
ADCSRA=0x87;

UBRR0L=103;
UCSR0A=0X00;
UCSR0B=0X18;//Tx Rx enabled
UCSR0C=0X06;//8bit async

OSInit();
OSTaskCreate(adc,0xFF,&s1[127],4);
OSTaskCreate(uart,0xFF,&s2[127],5);
OSStart();
}

void adc()
{
	while(1)
	{
	ADCSRA|=(1<<6);
	while((ADCSRA)&(1<<6));
	result=ADCL|(ADCH<<8);
	sprintf(d,"adc=%d\r",result);
	OSTimeDly(61);
		
	}
}
void uart()
{
	while(1)
	{
	int i;
	for(i=0;d[i]!='\0';i++)
	{
		UDR0=d[i];
		while((UCSR0A&(1<<5))==0);
		OSTimeDly(61);
		
	}
}
}

