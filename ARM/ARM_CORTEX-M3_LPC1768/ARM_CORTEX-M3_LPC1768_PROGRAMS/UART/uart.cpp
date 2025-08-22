#include <LPC17xx.H>

/*********************************************************************/
void U0_Init()  {
	  LPC_SC->PCONP|=(1<<3);// power up uart0 
	  LPC_SC->PCLKSEL0&=~(1<<6) & ~(1<<7); // clock selection
	  LPC_PINCON->PINSEL0|=(1<<4)|(1<<6);
	  LPC_PINCON->PINSEL0&=~(1<<5) & ~(1<<7);
	  LPC_UART0->LCR=0X83;
	  LPC_UART0->DLL=78;
	  LPC_UART0->LCR=0X03;
}
/*********************************************************************/
void U0_Tx(char data)  {
 	LPC_UART0->THR=data;
	while(!((LPC_UART0->LSR>>6)&1));
}
/*********************************************************************/
char U0_Rx()   {
 	static char data;
	while(!((LPC_UART0->LSR>>0)&1));
	data=LPC_UART0->RBR;
	return(data);	
}
/*********************************************************************/
void U0_StringTx(char *data) {
	for( ;*data;data++)
		U0_Tx(*data);
}
/********************************************************************/
char * U0_StringRx() {
	int i=0;
	char a[50];	
	while(1) {
		a[i]=U0_Rx();
		if(a[i]=='\r')
			break;
		i++;
	}
	a[i]='\0';
	return(a);
}
/********************************************************************/
int main()  {

	U0_Init();
	while(1)  {
		U0_Tx(U0_Rx());
		U0_StringTx(U0_StringRx());
	}
}
/*********************************************************************/
