#include"includes.h"
//************************************************************//


//*************************Flags*******************************//

void main()
{   
  PINSEL0 |= 0X00050005;	 // selecting UART0 and UART1
  PINSEL1 |= 0X00080000;
  IO1DIR  |= 0X0FFF0000;	 //pins 1.16 to 1.23 output pins
  IO0DIR  |= 0X003E0C00;	 //port 0 rs and en as output
  IO0CLR   = 0X00FF0000;	
  
  IO0SET   = 0X0FF00400;
 

  //*************************************//
  //         Initialisations             //
  //*************************************//
  lcd_init();
  spi_init();
  irq_init();
  uart_init();
  adc_init();
  pwm5_init();
  timer1_init_interrupt();
  rtc_init_interrupt();
 

  while(1)
  {	
  
  }
}







