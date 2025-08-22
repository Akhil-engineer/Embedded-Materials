#include <LPC17xx.H>

int main()
{
 int i;
 LPC_GPIO0->FIODIR=0XFFFFFFFF;
 LPC_GPIO0->FIOMASK=0XFFFF;
 while(1)
 {
   LPC_GPIO0->FIOSET=0XFFFFFFFF;
   for(i=0;i<1000000;i++);
   LPC_GPIO0->FIOCLR=0XFFFFFFFF;
   for(i=0;i<1000000;i++);
}

}