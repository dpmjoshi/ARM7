#include"includes.h"
//************************************************************//


//*************************Flags*******************************//

void main()
{   
  PINSEL0 |= 0X00051505;	 // selecting UART0 and UART1
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
  
  lcd_line1_disp("SPI Test", 0);

  while(1)
  {	
   Uc_key_temp = get_key(0);
   if(Uc_key_temp == '1')
   {

	Uc_key_temp = 0;
	lcd_line2_disp("Enter data", 0);
	ms_delay(10000);
	Uc_key_temp = get_key(1);

	uart0_send_byte(spi_send_byte(Uc_key_temp));
	ms_delay(10000);
	lcd_line2_disp("          ", 0);

   }
  }
}







