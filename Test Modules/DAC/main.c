#include"includes.h"

#define OUT_PORT     1<<6


//*************************Flags*******************************//
U8  Uc_user_mode_flag = 4;
const U8  test_variable = 'A' ;

U8  Uc_cnt = 0;

void main()
{   
  PINSEL0 |= 0X00050005;	 // selecting UART0 and UART1
  //PINSEL1 |= 0X00080000;
  IO1DIR  |= 0X0FFF0000;	 //pins 1.16 to 1.23 output pins
  IO0DIR  |= 0X003E0C00;	 //port 0 rs and en as output
  IO0CLR   = 0X00FF0000;	
  //*************************************//
  //         Initialisations             //
  //*************************************//

  
  uart_init();
  lcd_init();
  ms_delay(100);
  lcd_line2_disp("DAC testing",0);
  ms_delay(1000);
  DAC_init();

  //uart0_send_string(0x00070000);
  
  while(1)
  {	
	 Uc_key_temp = get_key(0);
	 if(Uc_key_temp == '1')
	 {
	  Uc_key_temp = 0;
	  ms_delay(10000);
	  DAC_write_val(10);
	 }

  }
}










