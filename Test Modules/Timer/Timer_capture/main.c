#include"includes.h"

#define OUT_PORT     1<<6
//*************************Flags*******************************//
U8 Uc_user_mode_flag = 4;

void main()
{   
  PINSEL0 |= 0X00050025;	 // selecting UART0 and UART1
  PINSEL1 |= 0X00080000;
  IO1DIR  |= 0X0FFF0000;	 //pins 1.16 to 1.23 output pins
  IO0DIR  |= 0X003E0C40;	 //port 0 rs and en as output
  IO0CLR   = 0X00FF0000;	
  
  //IO0SET   = 0X0FF00400;


  //*************************************//
  //         Initialisations             //
  //*************************************//
  lcd_init();
  timer0_init_interrupt();
  //rtc_init_interrupt();
  ms_delay(1000);
  lcd_line2_disp("TIMER0 testing",0);
  ms_delay(1000);
  while(1)
  {	
	Uc_pulse_width = T0TC;
	time1_measure(Uc_pulse_width);
	IO0SET = OUT_PORT;
   	ms_delay(10000);
   	IO0CLR = OUT_PORT;
   	ms_delay(10000);
  }
}







