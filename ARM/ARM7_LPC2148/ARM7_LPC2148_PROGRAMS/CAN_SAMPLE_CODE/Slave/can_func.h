#define DWORD unsigned int

#define CAN_REG_BASE (0xE0000000)
#define ACCEPTANCE_FILTER_RAM_BASE (CAN_REG_BASE + 0x00038000)

int Can_Init(void)
{

PINSEL1|= 0x15414000; 
PINSEL2|=  0x00000030;


// Init CAN interface 2
C2MOD = 1; // Enter Reset Mode
C2GSR = 0; // Clear status register
C2BTR = 0x001C001D; // Set bit timing

// Disable All Interrupt
C2IER = 0;

// Enter Normal Operating Mode
C2MOD = 0; // Operating Mode 

return 0;
}


void send_remote_frame(unsigned int x)
{
unsigned int DatA,DatB;
while((C2SR & 0x00000004) != 0x00000004);
C2TFI1 = 0x40010000; //RTR bit high
C2TID1 = x;
C2TDA1 = DatA;
C2TDB1 = DatB;
C2CMR = 0x21;

while((C2GSR & 0x00000008) != 0x00000008);
C2CMR = 0x00; 
disp_string(1,0x80,"Remt fram snt");
}




unsigned int Wait_for_data_frame(void)
{
unsigned int CANIDnew=0, DatA,DatB;


while( (C2GSR & 0x10)==0x10) ;  //wait until receiving complete.


CANIDnew=C2RID;
	
if(CANIDnew==(0x000000AB))
{

DatA=C2RDA;
DatB=C2RDB;

C2CMR = 0x00000004;	//release receiver
return(DatA);
}
return 0;		
}





char Wait_for_remote_frame(void)
{
unsigned int CANIDnew=0,DatB,DatA;
disp_string(1,0x80,"in loop");
while(1)
{
while( ( (C2GSR & 0x00000010)==0x00000010) );   //wait until receiving complete.

if((C2RFS & 0x40000000)==0x40000000)	//RTR == 1 remote frame
{
CANIDnew=C2RID;
	
if(CANIDnew==(0x000000CF))
{

DatA=C2RDA;
DatB=C2RDB;
C2CMR = 0x00000004;	//release receiver
return(1);
}
	else {
		C2CMR = 0x00000004;	
		return(0);
		}		
}
		else;
		C2CMR = 0x00000004;	//release receiver
}

}


void SendMessage2(unsigned int x,unsigned int y,unsigned int z)
{
unsigned int status;
//IOSET1 = 0X00800000;
while((C2SR & 0x00000004)!=0x00000004);

C2TFI2 = 0x00080000; 
C2TDA2 = y;
C2TDB2 = z;
C2TID2 = x;

//C1MOD = 0x1;
C2CMR = 0x41;
//C1MOD = 0x04;
status = C2GSR; 
while((status & 0x00000008) != 0x00000008)
status = C2GSR; 
C2CMR=0X00;
// disp_string(1,0x80,"sent!!!");
//	if((CANTxSR & 0x00010000)!=0);

}
void SendMessage1(unsigned int x,unsigned int a,unsigned int b,unsigned int c,unsigned int d)
{
unsigned int status;
//IOSET1 = 0X00800000;
while((C2SR & 0x00000004)!=0x00000004);

C2TFI1 = 0x00080000; 
C2TDA1 = (a<<16)|b;
C2TDB1 = (c<<16)|d;
C2TID1 = x;

//C1MOD = 0x1;
C2CMR = 0x21;
//C1MOD = 0x04;
status = C2GSR; 
while((status & 0x00000008) != 0x00000008)
status = C2GSR; 

C2CMR=0X00;
}


int ReceiveMessage (void)
{
unsigned int len,id;
char data; 

len = C2RFS;
id = C2RID;
data = C2RDA;
if(id == 0x000000CF) {
disp_string(0,0x80,"correct");
disp_string(0,0xc0,&data);
//while(1);
}
else
{
disp_string(1,0x80,"wrong");
}
C2CMR = 0x04;	
return 0;

}
