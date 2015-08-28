/************************************************************/
/* PROJECT NAME: PWM	                                    */
/* Project:      LPC2100 Training course                    */
/* Engineer:     T Martin                                   */
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

#include <LPC21XX.H>


  


int main(void)
{
unsigned int val,delay;

PINSEL0 |= ;			//Enable pin 0.7   as PWM2 
PWMPR 	 = 0x00000001;	//Load prescaler

PWMPCR = ;				//PWM channel 2 double edge control, output enabled
PWMMCR = ;				//On match with timer reset the counter
PWMMR0 = ;				//set cycle rate to sixteen ticks
PWMMR1 = ;				//set rising edge of PWM2 to 2 ticks
PWMMR2 = ;				//set falling edge of PWM2 to 8 ticks
PWMLER = ;				//enable shadow latch for match 0 - 2 
PWMEMR = 0x00000280;	//Match 1 and Match 2 outputs set high
PWMTCR = ;				//Reset counter and prescaler 
PWMTCR = 0x00000009;	//enable counter and PWM, release counter from reset

ADCR   = 0x00250601;    // Setup A/D: 10-bit AIN0 @ 3MHz 
ADCR  |= 0x01000000;    // Start A/D Conversion 

while(1)				// main loop
{
for (delay=0;delay < 0x100;delay++)
{
;
}
do
{
    val = ADDR;                   		// Read A/D Data Register 
}        
while ((val & 0x80000000) == 0);  		//Wait for the conversion to complete
val = ((val >> 8) & 0x00FF);  			//Extract the A/D result 

PWMMR1 = 0x00000000+val;				 //Modulate PWM
PWMMR2 = 0x000000FF-val;
PWMLER = ;								 //set latch to update PWM registers next cycle
}


}



