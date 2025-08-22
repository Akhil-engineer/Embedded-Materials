void init_ADC(void)
{
PINSEL1|=0x00400000;
ADCR=0x00200201;	//adc clock=PCLK/(2+1),  no burst mode, ADC enabled
}

void init_ADC1(void)
{
PINSEL1|=0x01000000;
ADCR=0x00200202;	//adc clock=PCLK/(2+1),  no burst mode, ADC enabled
}
void init_ADC2(void)
{
PINSEL1|=0x04000000;
ADCR=0x00200204;	//adc clock=PCLK/(2+1),  no burst mode, ADC enabled
}

void init_ADC3(void)
{
PINSEL1|=0x10000000;
ADCR=0x00200208;	//adc clock=PCLK/(2+1),  no burst mode, ADC enabled
}


unsigned int read_adc(void)
{
 unsigned int g;

 ADCR|=0x01000000;	//// start & chaannel ADC0 = P0.27
 delay_10us(2);
 while((ADDR&0x80000000)==0);	  //done==1
 g=ADDR;
 g=((g>>6)&0x3ff);	//10bit result
 //need CALCULATION============

 ADCR&=0xF8FFFFFF;	//ADC stop
 return(g);
}


void temp(int *temp)
{
 int g=0;

 ADCR|=0x01000000;	//// start & chaannel ADC0 = P0.27
 delay_10us(3);
 while((ADDR&0x80000000)==0);	  //done==1
 g=ADDR;
 g=((g>>6)&0x3ff);	//10bit result
 *temp=g;
 ADCR&=0xF8FFFFFF;

}