//uart0 -9600,8bit,Fosc=10MHz,CCLK=60MHz,Pclk=15MHz
//== PLLCFG *6, VPBDIV /4
void Init_UART0(void)
{
PINSEL0&=0xFFFFFFF0;
PINSEL0|=0x00000005;
U0LCR=0x83;
U0DLL=0x51;	//97
U0DLM=0x00;
U0LCR=0x03;
U0FCR=0x01;
}

void Init_UART1(void)
{
PINSEL0&=0xFFF0FFFF;
PINSEL0|=0x00050000;
U1LCR=0x83;
U1DLL=0x51;	//97
U1DLM=0x00;
U1LCR=0x03;
U1FCR=0x01;
} 

char read_byte_u1(void)
{
char rec;
while((U1LSR&0x01)==0x00);
rec=U1RBR;
return(rec);
}

char read_byte_u0(void)
{
char rec;
while((U0LSR&0x01)==0x00);
rec=U0RBR;
return(rec);
}

// only send a byte
void send_byte_u0(char snd)
{
U0THR=snd;
while((U0LSR&0x40)==0);
}

//sends and wait for 1 sec, if not received the desired repeats
char send_wait_u0(char snd,char rec1,char rec2)
{
unsigned int i;
char tst;

while(1)
{

U0THR=snd;
while((U0LSR&0x40)==0);
i=0;

do
{

if((U0LSR&0x01)==0x01)
{
tst=U0RBR;
}
delay_10us(50);
i++;

}
while( ((tst!=rec1)&&(tst!=rec2)&&(i<2000)) );

if( ( (tst==rec1)||(tst==rec2) ) )
break;
}

return(tst);
}

void send_string_u0(char *ptr)
{
int i;
for(i=0;ptr[i]!='\0';i++)
{
 U0THR=ptr[i];
while((U0LSR&0x40)==0);
}
}

void clear_buffer_u1(void)
{
U1FCR|=0x02; //reset rx fifo. this bit becomes zero after cleareing the buffer
while( ( (U1FCR&0x02)==0x02) );
delay_ms(5);
}

void clear_buffer_u0(void)
{
U0FCR|=0x02; //reset rx fifo. this bit becomes zero after cleareing the buffer
delay_ms(5);
}