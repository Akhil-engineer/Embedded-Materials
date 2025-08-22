#include <LPC17xx.H>

/*******************************************************************************************/
void T0_Init()
{
  LPC_SC->PCONP|=(1<<1);
  LPC_SC->PCLKSEL0&=~(1<<2) & ~(1<<3);
  LPC_TIM0->PR=11999;
  LPC_TIM0->MCR=2;
  LPC_TIM0->MR0=5;
  LPC_TIM0->TC=0;
  LPC_TIM0->TCR=2;
  LPC_TIM0->TCR=1;
  LPC_GPIO0->FIODIR=0XFFFFFFFF;
 LPC_GPIO0->FIOMASK=0XFFFF;
 LPC_GPIO0->FIOPIN=0XFFFFFFFF;
}

int main()
{
    T0_Init();
	while(1)
	{
	  while(LPC_TIM0->TC!=LPC_TIM0->MR0);
	  LPC_TIM0->TC=0;
	  LPC_GPIO0->FIOPIN=~LPC_GPIO0->FIOPIN;
	}


}

