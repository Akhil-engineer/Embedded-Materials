#include"includes.h"
#include<stdio.h>
#include<string.h>

char a[]="helloo how are you\r\n";
char d[]="hi am fine....\r";

OS_STK s1[128];
OS_STK s2[128];
OS_EVENT *maildata1;

void *err;
void uart1();
void uart2();

main()
{

UBRR0L=103;
UCSR0A=0X00;
UCSR0B=0X18;
UCSR0C=0X06;
TCCR0=0x07;
TIMSK=0x01;

OSInit();
OSTaskCreate(uart1,0xFF,&s1[127],4);
OSTaskCreate(uart2,0xFF,&s2[127],5);
maildata1=OSSemCreate(0);
OSStart();
}

void uart1()
{
	int i;
	while(1)
	{
	OSSemPend(maildata1,0,err);
	for(i=0;a[i]!='\0';i++)
	{
		UDR0=a[i];
		while((UCSR0A&(1<<5))==0);	
	}
	OSTimeDly(1);
}
}
void uart2()
{
	while(1)
	{
	int i;
	for(i=0;d[i]!='\0';i++)
	{
		UDR0=d[i];
		while((UCSR0A&(1<<5))==0);
	}
	OSSemPost(maildata1);
}
}
