#include"includes.h"

#define OUT_PORT     1<<6


#define flash_ptr    0X0000013E





U8 *ram_ptr;
U8 *rom_ptr;
//*************************Flags*******************************//
U8  Uc_user_mode_flag = 4;
const U8  test_variable = 'A' ;

U8  Uc_cnt = 0;
U8  test_data[256] = {"  Testing of In Application Progrmming(IAP)\n\rROM Sector No: 21\n\rSize of Sector: 32Kb"};



void prog_rom();



void main()
{   
  PINSEL0 |= 0X00050005;	 // selecting UART0 and UART1
  PINSEL1 |= 0X00080000;
  IO1DIR  |= 0X0FFF0000;	 //pins 1.16 to 1.23 output pins
  IO0DIR  |= 0X003E0C00;	 //port 0 rs and en as output
  IO0CLR   = 0X00FF0000;	
  //*************************************//
  //         Initialisations             //
  //*************************************//
  ram_ptr = ram_add;
  rom_ptr = rom_add;
  
  uart_init();
  lcd_init();
  ms_delay(1000);
  lcd_line2_disp("IAP testing !",0);
  uart0_send_string("\n\rIAP testing");
  ms_delay(1000);
  
 
  
  for(Uc_cnt = 0; Uc_cnt < 255; Uc_cnt++)
  {
    *ram_ptr = test_data[Uc_cnt];
    ram_ptr++;
  }
   *ram_ptr = '\0';


  //uart0_send_string(0x00070000);
  
  while(1)
  {	
	 Uc_key_temp = get_key(0);
	 if(Uc_key_temp == '1')
	 {
	  Uc_key_temp = 0;
	  ms_delay(10000);
	  prog_rom();
	 }
	 if(Uc_key_temp == '2')
	 {
	  Uc_key_temp = 0;
	  IAP_read_boot_code();
	  ms_delay(10000);
	 }
	 ms_delay(1000);
  }
}










