#include"includes.h"
//************************************************************//


//*************************Flags*******************************//
U8 Uc_new_key = 0;
U8 Uc_prev_key = 0;
U8 Uc_actual_key = 0;
U8 key_cnt = 0;
U8 msg_cnt = 0, first_key = 1;
U8 msg_arr[128] = {"                  "};

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
  clrscr();
  ms_delay(10000);
  lcd_line1_disp("Lib function", 0);
  while(1)
  {	
  hex_ascii(0x10000000);
  lcd_line2_disp(&Uc_ascii_arr[0], 0);
  while(1);
	 
  }


}




