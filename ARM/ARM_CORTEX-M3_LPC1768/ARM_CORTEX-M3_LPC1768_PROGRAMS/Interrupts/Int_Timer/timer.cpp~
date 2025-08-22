 #include<LPC17xx.h>
 int x=0;
 
int main (void) 
{
 LPC_SC->PCONP |= 1 << 1;      // Power up Timer 0
 LPC_SC->PCLKSEL0 |= 1 << 2;   // Clock for timer = CCLK
 LPC_TIM0->MR0 = 2;      // Suitable for LED
 LPC_TIM0->PR = 11999999;
 LPC_TIM0->MCR |= 1 << 0;      // Interrupt on Match0 compare
 LPC_TIM0->MCR |= 1 << 1;      // Reset timer on Match 0.
 LPC_TIM0->TCR |= 1 << 1;      // Reset Timer0 
 
 LPC_TIM0->TCR &= ~(1 << 1);   // stop resetting the timer.
 NVIC_EnableIRQ(TIMER0_IRQn);  // Enable timer interrupt
 LPC_TIM0->TCR |= 1 << 0;      // Start timer
 
 LPC_SC->PCONP |= ( 1 << 15 ); // power up GPIO
 LPC_GPIO1->FIODIR |= 1 << 29; // LED is connected to P1.29
 while(1)
 {
 //do nothing
 }
   
}
void TIMER0_IRQHandler (void)
{
    if((LPC_TIM0->IR & 0x01) == 0x01) // if MR0 interrupt
    {
        LPC_TIM0->IR |= 1 << 0; // Clear MR0 interrupt flag
        LPC_GPIO1->FIOPIN ^= 1 << 29; // Toggle the LED
		x++;
    }
}





















