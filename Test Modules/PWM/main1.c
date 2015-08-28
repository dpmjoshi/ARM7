/************************************************************/
/* PROJECT NAME: PWM	                                    */
/* Project:      						                    */
/* Engineer:     			                                */
/* Filename:     main.c                                     */
/* Language:     C                      	                */
/* Compiler:     Keil Carm 2.00b		                    */
/* Assembler:    					                        */
/*                                                          */
/************************************************************/
/* Modification History:                                    */
/*                                                          */
/************************************************************/
/* Function:                                                */
/*                                                          */
/* Example PWM module program for LPC2100         			*/
/*															*/
/* Demonstrates dual edge PWM generation					*/
/*															*/	
/* Oscillator frequency 12.000 Mhz							*/
/* Target board Keil MCB2100								*/
/************************************************************/

#include"includes.h"

void ms_delay(unsigned int w)
{
   T0TCR  = 0X01;
   T0PR   = 1000;
   while(T0TC<w)
      {
	  }			                                                    
   T0TC   = 0;
   T0TCR  = 0;
}


int main(void)
{
	int i = 25, j = 15, k = 40;

	pwm5_dbl_init();
	//pwm5_pulse_width(1000, i);

	while(1)				// main loop
	{
 	 pwm5_dbl_pulse_width(k,i,j);
	 i += 1;
	 j -= 1;
	 if(i == k)
	 { 	 	
		k  += 5; 
		i   = k-15;
	 }

	 if(j == 0)
	 {
	 	j = 15 ;
	 }
	 /*
	 ms_delay(4000);							 //set latch to update PWM registers next cycle
	 ms_delay(4000);
	 ms_delay(4000);
	 */
	}


}