void command4bit(char c)
{
 int cc;
 cc=c;
 cc=cc<<20;	
 
 IOCLR1=0X00F00000;  //clear D7 to D4
 
 IOCLR1=0X00040000;  //rw = 0
 IOCLR1=0X00020000;	 //rs = 0

 IOSET1=(cc&0X00F00000);
 IOSET1=0X00080000;   //en=1
 delay_10us(20);
 IOCLR1=0X00080000;   //en=0 
}

void command(char c)
{
 int cc;
 cc=c;
 cc=cc<<16;  //to send higher nibble first
 IOCLR1=0X00F00000;
 IOCLR1=0X00040000;
 IOCLR1=0X00020000;
 IOSET1=(cc&0X00F00000);
 IOSET1=0X00080000;
 delay_10us(20);
 IOCLR1=0X00080000;;
 cc=c;
 cc=cc<<20;
 IOCLR1=0X00F00000;
 IOCLR1=0X00040000;
 IOCLR1=0X00020000;
 IOSET1=(cc&0X00F00000);
 IOSET1=0X00080000;
 delay_10us(20);
 IOCLR1=0X00080000;
}




void init_4bit_lcd(void)
{
 IODIR1 |= 0X00FE0000; // P1.23 - P1.20 to D7 to D4
                       // P1.17 to RS, p1.18 to rw, p1.19 to EN 
                       // all 7 configured as output
                           
 delay_ms(20);
 command4bit(3);
 delay_ms(10);
 command4bit(3);
 delay_ms(10);
  command4bit(3);
 delay_ms(10);
  command4bit(2);
 delay_ms(10);
 command(0X28);
 delay_ms(10);
 command(0X0E);
  delay_ms(5);
 command(0X01);
  delay_ms(5);
 command(0X06);
  delay_ms(5);
 command(0X80);
  delay_ms(5);
}



void display(char g)
{
 int c;
 
 delay_ms(1);
 c=g;
 c=c<<16;
 IOCLR1=0X00F00000;
 IOCLR1=0X00040000;
 IOSET1=0X00020000;
 IOSET1=(c&0X00F00000);
 IOSET1=0X00080000;
 delay_10us(20);
 IOCLR1=0X00080000;

 c=g;
 c=c<<20;
 IOCLR1=0X00F00000;
 IOCLR1=0X00040000;
 IOSET1=0X00020000;
 IOSET1=(c&0X00F00000);
 IOSET1=0X00080000;
 delay_10us(20);
 IOCLR1=0X00080000;
 }

 void disp_string(char clr,char pos,char *dat)
 {
  int i;
   if(clr==1)
   {
     command(0X01);
	 delay_ms(5);
   }
	 command(pos);
	 for(i=0;dat[i]!='\0';i++)
	 display(dat[i]);
}
