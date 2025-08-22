#include"includes.h"
#include<stdio.h>
#include<string.h>
OS_STK s1[128];
OS_STK s2[128];

char d[20];
int result;

void adc1();
void adc2();

main()
{


ADMUX=0x00;
ADCSRA=0x87;
UBRR0L=103;
UCSR0A=0X00;
UCSR0B=0X18;
UCSR0C=0X06;
TCCR0=0x07;
TIMSK=0x01;

OSInit();
OSTaskCreate(adc1,0xFF,&s1[127],4);
OSTaskCreate(adc2,0xFF,&s2[127],5);
OSStart();
}

void adc1()
{

	int i;
	while(1)
	{
	ADMUX=0x00;
	ADCSRA|=(1<<6);
	while((ADCSRA)&(1<<6));
	result=ADCL|(ADCH<<8);
	sprintf(d,"adc1=%d\r",result);
	OSTimeDly(61);
	for(i=0;d[i]!='\0';i++)
	{
		UDR0=d[i];
		while((UCSR0A&(1<<5))==0);
	}
		
	}
}
void adc2()
{
	int i;
	while(1)
	{
	ADMUX=0x01;
	ADCSRA|=(1<<6);
	while((ADCSRA)&(1<<6));
	result=ADCL|(ADCH<<8);
	sprintf(d,"adc2=%d\r",result);
	OSTimeDly(61);
	for(i=0;d[i]!='\0';i++)
	{
		UDR0=d[i];
		while((UCSR0A&(1<<5))==0);
	}
		
	}
}

