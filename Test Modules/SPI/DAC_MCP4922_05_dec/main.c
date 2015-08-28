#include"includes.h"

#define CS_DAC 1<<7
#define LDAC   1<<17
//************************************************************//


//*************************Flags*******************************//

void main()
{   
  PINSEL0 |= 0X00051505;	 // selecting UART0 and UART1
  PINSEL1 |= 0X00080000;
  IO1DIR  |= 0X0FFF0000;	 //pins 1.16 to 1.23 output pins
  IO0DIR  |= 0X003E0C88;	 //port 0 rs and en as output
  IO0CLR   = 0X00FF0000;	
  
  IO0SET   = 0X0FF00400;
 

  //*************************************//
  //         Initialisations             //
  //*************************************//
  lcd_init();
  spi_init();
  irq_init();
  uart_init();
  
  IO0SET |= (CS_DAC | LDAC);
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

	IO0CLR |= CS_DAC; 
	ms_delay(100);
	spi_send_byte(0x3800);
	ms_delay(100);
	IO0SET |= CS_DAC;
	
	ms_delay(10000);
	IO0CLR |= LDAC;
	ms_delay(100);
	IO0SET |= LDAC;
	
	ms_delay(100);
	lcd_line2_disp("          ", 0);

   }
  }
}







