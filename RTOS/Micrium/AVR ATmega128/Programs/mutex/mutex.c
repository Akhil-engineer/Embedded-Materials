#include<includes.h>
#include<avr/io.h>
#include<util/delay.h>
void txt(char *);
char a[]="hello how are you alphabets a b c d e f g h\r";
char b[]="i am fine\r";
char c[]="good morning \r";
OS_STK s1[128],s2[128],s3[128];
OS_EVENT *event;
unsigned int *err;
void txt(char *a)
{
	int i;
	
		for(i=0;a[i];i++)
		{
			UDR0=a[i];
			while((UCSR0A&(1<<5))==0);
			_delay_ms(100);
		}
	
}
void t1()
{
	while(1)
	{
		OSMutexPend(event,0,err);
		txt(a);
		OSMutexPost(event);
		OSTimeDly(1);
	}
}
void t2()
{
	while(1)
	{
		OSMutexPend(event,0,err);
		txt(b);
		OSMutexPost(event);
		OSTimeDly(1);
	}
}
void t3()
{
	while(1)
	{
		OSMutexPend(event,0,err);
		txt(c);
		OSMutexPost(event);
		OSTimeDly(1);
	}
}
void main()
{
	UCSR0A=0;

	UCSR0B=0x18;

	UCSR0C=0x06;

	UBRR0L=103;

	TCCR0=0x07;

	TIMSK=0x01;

	OSInit();

	OSTaskCreate(t1,0xFF,&s1[127],5);

	OSTaskCreate(t2,0xFF,&s2[127],6);
	OSTaskCreate(t3,0xFF,&s3[127],7);
	event=OSMutexCreate(4,err);
	OSStart();

}