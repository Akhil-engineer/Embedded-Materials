#include <LPC17xx.H>

int main()
{
 int i;
 LPC_GPIO0->FIODIR=0XFFFFFFFF;
 LPC_GPIO1->FIODIR=0X00000000;
 while(1)
 {
   if(LPC_GPIO1->FIOPIN&(1<<17))
   LPC_GPIO0->FIOPIN=0XFFFFFFFF;
   else
   LPC_GPIO0->FIOPIN=0X00000000;
 }

}