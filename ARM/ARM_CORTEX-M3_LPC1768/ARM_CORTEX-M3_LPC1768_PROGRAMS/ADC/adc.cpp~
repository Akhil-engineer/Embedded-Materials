#include<LPC17xx.H>
#include"uart.h"
#include<stdio.h>
/*****************************************************************************/
void ADC_Init()  {
  LPC_SC->PCONP|=(1<<12); // Set PCADC bit to power ADC
  LPC_SC->PCLKSEL0&=~(1<<24) & ~(1<<25);
  LPC_PINCON->PINSEL1|=(1<<14);
  LPC_PINCON->PINSEL1&=~(1<<15);
  LPC_ADC->ADCR=0X00200101;
  for(int i=0;i<5000;i++);
}
/****************************************************************************/
unsigned int ADC_Read(int channel)  {
   	unsigned int result;
	LPC_ADC->ADCR &=~(0XFF);
	LPC_ADC->ADCR |=(1<<channel);
	for(int i=0;i<5000;i++);
	LPC_ADC->ADCR|=(1<<24);  // Start conversion
	while(!((LPC_ADC->ADGDR)&(1<<31)));
	result=(LPC_ADC->ADGDR>>4)&(0XFFF);
	return(result);	
}
/****************************************************************************/
int main() {
  unsigned int res;
  char a[10];
  ADC_Init();
  U0_Init();
  while(1) {
  	res=ADC_Read(7); 
	sprintf(a,"%d\n",res);
	U0_StringTx(a);
  }
}
/****************************************************************************/
													
