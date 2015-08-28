//*************************************************************//
// Project: Timer0 in Capture Mode 							   //
// Hardware Pins: channel0	(CAP 0.0 => P0.2)				   //
//															   //
//															   //
//															   //
//*************************************************************//
#include"includes.h"

#define OUT_PORT     1<<6
//*************************Flags*******************************//
U8 Uc_user_mode_flag = 4;
U8 Uc_temp_arr[10] = {"00000"};


void main()
{   
  PINSEL0 |= 0X00050205;	 // selecting UART0 and UART1
  PINSEL1 |= 0X00080000;
  IO1DIR  |= 0X0FFF0000;	 //pins 1.16 to 1.23 output pins
  IO0DIR  |= 0X003E0C40;	 //port 0 rs and en as output
  IO0CLR   = 0X00FF0000;	
  
  //*************************************//
  //         Initialisations             //
  //*************************************//
  lcd_init();
  timer0_init_interrupt();
  UART_init();
  ms_delay(1000);
  lcd_line2_disp("TIMER0 testing",0);
  uart0_send_string("\r\nUART1 Connected @ 9600 ");
  ms_delay(1000);
  while(1)
  {	
  	hex_dec1(Uc_temp_arr, T0TC);
	lcd_line3_disp(Uc_temp_arr, 0);

	hex_dec1(Uc_temp_arr, Uc_pulse_width);
	lcd_line4_disp(Uc_temp_arr, 0);
  }
}
