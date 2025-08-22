#include<includes.h>
#include<stdio.h>
#include<string.h>
OS_STK s1[128];
OS_STK s2[128];
OS_STK s3[128];
char temp;
char hr,min,sec,a[30];
int len,i;
void read();
void write();
void uart();
void start(void)
{
	TWCR=((1<<TWINT)|(1<<TWSTA)|(1<<TWEN));
	while(!(TWCR&(1<<TWINT)));
}
void stop(void)
{
	TWCR=((1<<TWEN)|(1<<TWSTO)|(1<<TWINT));
}
void ack(void)
{
	TWCR=((1<<TWINT)|(1<<TWEN)|(1<<TWEA));
	while(!(TWCR&(1<<TWINT)));
	temp=TWDR;
}
void nack(void)
{
	TWCR=((1<<TWINT)|(1<<TWEN));
	while(!(TWCR&(1<<TWINT)));
	temp=TWDR;
}
void send (char a)
{
	TWDR=a;
	TWCR=((1<<TWINT)|(1<<TWEN));
	while(!(TWCR&(1<<TWINT)));
}
void restart (void)
{
	TWCR=((1<<TWINT)|(1<<TWSTA)|(1<<TWEN));
	while(!(TWCR&(1<<TWINT)));
}
int main()
{
	UCSR0A=0x02;
	UCSR0B=0X18;
	UCSR0C=0X06;
	UBRR0L=207;
	TWBR=18;
	TCCR0=0x07;
	TIMSK=0x01;
	OSInit();
	OSTaskCreate(write,0xFF,&s1[127],4);
	OSTaskCreate(read,0xFF,&s2[127],5);
	OSTaskCreate(uart,0xFF,&s3[127],6);
	OSStart();
}
void write()
{
	while(1)
	{
		start();
		send(0xd0);
		send(0x00);
		send(0x29);
		send(0x06);
		send(0x04);
		stop();
		OSTaskResume(5);
		OSTaskSuspend(4);
		
	}
}
void read()
{
	while(1)
	{
		start();
		send(0xd0);
		send(0x00);
		restart();
		send(0xd1);
		ack();
		sec=temp;
		ack();
		min=temp;
		nack();
		hr=temp;
		stop();
		sprintf(a,"%x:%x:%x     \r",hr,min,sec);
		len=strlen(a);
		OSTimeDly(61);
	}
}
void uart()
{
	while(1)
	{
		int i;
		for(i=0;a[i];i++)
		{
			UDR0=a[i];
			while((UCSR0A&(1<<5))==0);
		}
		OSTimeDly(61);
	}
}