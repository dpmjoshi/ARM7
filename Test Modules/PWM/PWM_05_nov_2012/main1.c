#include"includes.h"


void main(void)
{
	unsigned int i = 25, j = 15, k = 40;
	PINSEL0 |= 0x00000000;
	PINSEL1 |= 0x00000000;
	PINSEL2 |= 0x00000000;

	IO1DIR  |= 0X0FFF0000;	 //pins 1.16 to 1.23 output pins
  	IO0DIR  |= 0X003E0C80;	 //port 0 rs and en as output
  	IO0CLR   = 0X00FF0000;
 	
	pwm5_init();
	
	lcd_init();


	clrscr();
	
	ms_delay(10000);
	pwm5_pulse_width(1000, 500);
    
	while(1)				// main loop
	{
	 for(i = 25; i < 150; i++)
	 {
	  pwm5_pulse_width(20, 10);
	  ms_delay(1000000);	 
	 }
	}
}