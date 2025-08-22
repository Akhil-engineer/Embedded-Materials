 void delay_10us(long int dly)
 {
  int j,k;
 	for(k=0;k<dly;k++)
	{
		
		// aprox 10us
	  for(j=0;j<200;j++)   // one iteration step takes 3 machine cycle period
	  {					   // ie. j<200 + ; + j++ .
		;  				   // Cclk=60MHz
	  }					   // 1 M.cycle=(1/60)us. so 3*(1/60)us=(1/20)us
	}					   // 200 * (1/20)us gives ~~ 10us
		
 }


 void delay_ms(long int dly)
 {
 unsigned long int i,j,k;
 	for(k=0;k<dly;k++)
	{
		for(i=0;i<100;i++)
		{
			// aprox 10us
			for(j=0;j<200;j++)	   // one iteration step takes 3 machine cycle period
			{					   // ie. j<200 + ; + j++ .
			;   				   // Cclk=60MHz
			}					   // 1 M.cycle=(1/60)us. so 3*(1/60)us=(1/20)us
		}						   // 200 * (1/20)us gives ~~ 10us
	 }
 
 }
