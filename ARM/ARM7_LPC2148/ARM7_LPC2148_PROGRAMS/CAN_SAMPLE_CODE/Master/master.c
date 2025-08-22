#include<LPC21xx.h>
#include<stdio.h>
#include "tnmadelay.h"
#include "tnma4bitlcd2129.h"
#include "can_func.h"
#include "tnmaUART2129.h"

int main(void)
{
char dt[13];
unsigned int val=0,val1=0;
unsigned int val2=0,val3=0;	
IODIR1 = 0X00FF0000;
IOCLR1 = 0x00FF0000;

Can_Init();
init_4bit_lcd();
Init_UART0();
disp_string(1,0x80,"master");
send_string_u0("Master..");
send_string_u0("\n\r");
while(1) {
		while((C2GSR&0X10)!=0X10);
		val=((C2RDA&0xFFFF0000)>>16);
		val1=(C2RDA&0xFFFF);
		val2=((C2RDB&0xFFFF0000)>>16);
		val3=(C2RDB&0xFFFF);
		//C2CMR = 0x00000004;
		sprintf(dt,"   Temp: %2d dC  ",val);
		disp_string(0,0x80,dt);
		send_string_u0(dt);
		send_string_u0("\n\r");
		

		sprintf(dt,"     CO: %3d     ",val1);
		send_string_u0(dt);
		send_string_u0("\n\r");

	  	if(val>60){
		 	disp_string(0,0x80,"High Temperature");
			disp_string(0,0xc0," Vehicle OFF!!! ");
			send_string_u0("High Temperature!!!\n\rVehicle OFF!!!\n\r");	
			}
		
		if(val1>390){
		 	disp_string(0,0x80,"  High CO Level ");
			disp_string(0,0xc0," Vehicle OFF!!! ");
			send_string_u0("High CO Level\n\rVehicle OFF!!!\n\r");	
			}
		else{
			disp_string(0,0xc0,"  Low CO level  ");
			send_string_u0("Low CO level");
			send_string_u0("\n\r");
			}
			
		// delay_ms(1000);	
					
		
		 sprintf(dt," Battery: %2d %  ",val2);
		 disp_string(0,0x80,dt);
	 	 send_string_u0(dt);
		 send_string_u0("\n\r");
		

		 sprintf(dt,"    Fuel %2d L   ",val3);
		 disp_string(0,0xC0,dt);
		 send_string_u0(dt);
		 send_string_u0("\n\r");

		 while((C2GSR&0X10)!=0X10);
		 val2=C2RDA;
	     val3=C2RDB;
		 C2CMR = 0x00000004;    

		 delay_ms(1000);

		    
		if(val2==1){
		  disp_string(0,0xc0,"Fire Detected...");
		  send_string_u0(" Fire Detected\n\r");
		  send_string_u0(" Vehicle OFF!!!\n\r");
		  }
		else{ 
		  disp_string(0,0xc0,"No Fire");
		  send_string_u0(" No Fire\n\r");
		  }

 
		if(val3==1){
		  disp_string(0,0xc0,"Obstacle Detectd");
		  send_string_u0(" Obstacle Detected\n\r");
		  }
		else 
		  disp_string(0,0xc0,"No Obstacle");
		  send_string_u0(" No Obstacle\n\r");
		}

return 0;
}
