#include<LPC21xx.h>
#include<stdio.h>
#include "tnmadelay.h"
#include "tnma4bitlcd2129.h"
#include "can_func.h"
#include "tnmaUART2129.h"
#include "tnmaADC.h"

int fire(void)
{
	 int input;
	 IODIR0=0xF0;
	 input=IOPIN0;
	 if((input&0x04)==0x04)
	 	return 1;
	 else 
	 	return 0;
}

int obstacle(void)
{
	 int input;
	 IODIR0=0xF0;
	 input=IOPIN0;
	 if((input&0x08)==0x08)
	 	return 1;
	 else 
	 	return 0;
}

int main(void)
{

int data=0,data1=0,data2=0,data3=0,f,o;
unsigned int val;
char dt[15];
IODIR1 = 0X00FF0000;
IOCLR1 = 0x00FF0000;
Can_Init();
Init_UART0();
init_4bit_lcd();
send_string_u0("Slave..\n\r");
disp_string(1,0x80,"slave.");
while(1) {
 	
	 	 init_ADC();
		 temp(&data);
		 val=(((float)data/1024)*330);
		 sprintf(dt," Temp: %2d dC",val);
		 disp_string(0,0x80,dt);
		 send_string_u0(dt);
		 send_string_u0("\n\r");

		 init_ADC1();
		 temp(&data1);
		 sprintf(dt," CO: %3d ",data1);
		 disp_string(0,0xc0,dt);
		 send_string_u0(dt);
		 send_string_u0("\n\r");
		 		 		 
	//	 delay_ms(1000);

		 init_ADC2();
		 temp(&data2);
		 sprintf(dt," Battery: %2d %",100);
		 disp_string(0,0x80,dt);
		 send_string_u0(dt);
		 send_string_u0("\n\r");


		 init_ADC3();
		 temp(&data3);
		 sprintf(dt," Fuel %2d L ",50);
		 disp_string(0,0xc0,dt);
		 send_string_u0(dt);
		 send_string_u0("\n\r");



		 SendMessage1(0x000000AB,val,data1,data2,data3);
		 
		 f=fire();
		 
		 o=obstacle();

		 SendMessage2(0x000000AB,f,o);


		 if(f==1){
		 	send_string_u0(" Fire Detected\n\r");
			send_string_u0(" Vehicle OFF!!!\n\r");
			while(f==1){
				 	  f=fire();
					}
			}
		 else
		 	send_string_u0(" No Fire\n\r");


		 if(o==1){
		 	send_string_u0(" Obstacle Detected\n\r");
			send_string_u0(" Vehicle OFF!!!\n\r");
			while(o==1){
				 		 o=obstacle();
					}
			}
		 else
		 	send_string_u0(" No Obstacle\n\r");	 	
		
		 
		 	  
	 	  if(data1>390){
		 	disp_string(0,0x80," High CO Level ");
			disp_string(0,0xc0," Vehicle OFF!!!");
			send_string_u0("\n\r High CO Level \n\r");	 
			send_string_u0(" Vehicle OFF!!!\n\r");	 
				
			while(data1>390){
				 	init_ADC1();
		 			temp(&data1);
					}
			}
		if(val>60){
		 	disp_string(0,0x80,"High Temp Level");
			disp_string(0,0xc0," Vehicle OFF!!!");
			send_string_u0("\n\r High Temp Level \n\r");	 
			send_string_u0(" Vehicle OFF!!!\n\r");	
			while(val>60){
				 	init_ADC();
		 			temp(&data);
					val=(((float)data/1024)*330);
					}
			}
			 delay_ms(1000);	
}
return 0;
}
