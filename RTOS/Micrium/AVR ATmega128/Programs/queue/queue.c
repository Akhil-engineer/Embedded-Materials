#include"includes.h"
#include<stdio.h>
#include<string.h>
OS_STK s1[128];
OS_STK s2[128];
OS_STK s3[128];
OS_EVENT *maildata1;
int *err;
void *q[10];
int result;

void adc1();
void adc2();
void uart();

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
OSTaskCreate(uart,0xFF,&s3[127],6);
maildata1=OSQCreate(q,10);
OSStart();
}

void adc1()
{
	char d[20];
	while(1)
	{
	ADMUX=0x00;
	ADCSRA|=(1<<6);
	while((ADCSRA)&(1<<6));
	result=ADCL|(ADCH<<8);
	sprintf(d,"adc1=%d\r",result);
	OSQPost(maildata1,d);
	OSTimeDly(61);	
	}
}
void adc2()
{
	char b[20];
	while(1)
	{
	ADMUX=0x01;
	ADCSRA|=(1<<6);
	while((ADCSRA)&(1<<6));
	result=ADCL|(ADCH<<8);
	sprintf(b,"adc2=%d\r",result);
	OSQPost(maildata1,b);
	OSTimeDly(61);
	}
}
void uart()
{
	char *out1,*out2;
	int i;
	while(1)
	{	
	  out1=OSQPend(maildata1,0,err);
	for(i=0;out1[i]!='\0';i++)
	{
		UDR0=out1[i];
		while((UCSR0A&(1<<5))==0);
	}

	out2=OSQPend(maildata1,0,err);
	for(i=0;out2[i]!='\0';i++)
	{
		UDR0=out2[i];
		while((UCSR0A&(1<<5))==0);
	}
	}
}
