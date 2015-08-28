#include"includes.h"
//************************************************************//
#define no_recv_byte      14
#define COOLER_ON         1<<19
#define HEATER_ON         1<<20
#define	SSR_ON			  1<<21
#define	BUZZER			  1<<22

U8 Uc_data_sent[30];
U8 uart1_set[30]         = {"\n\rUART1 connected at 9600-8-N"};
U8 uart0_set[30]         = {"\n\rUART0 connected at 9600-8-N"};
U8 welcome_note1[25]     = {"Reaction  Controller"};
U8 welcome_note2[20]     = {"NCL-Pune"};
U8 lcd_data_sys_chk[20]  = {"Initializing"};

U8 Uc_data = 0;
//*************************Flags*******************************//
U8 Uc_user_mode_flag = 4;
U8 Uc_labview_stop = 1;
U8 Uc_labview_hdsk = 0;


void main()
{   
  PINSEL0 |= 0X00050005;	 // selecting UART0 and UART1
  PINSEL1 |= 0X00080000;
  IO1DIR  |= 0X0FFF0000;	 //pins 1.16 to 1.23 output pins
  IO0DIR  |= 0X003E0C00;	 //port 0 rs and en as output
  IO0CLR   = 0X00FF0000;	
  
  IO0SET   = 0X0FF00400;
  IO0CLR   = BUZZER;

  PCONP   |= 0x00000218;
  INTWAKE |= 0x8000; 
  //*************************************//
  //         Initialisations             //
  //*************************************//
  lcd_init();
  irq_init();
  uart_init();
  adc_init();
  //wdt_init();
  pwm5_init();
  timer1_init_interrupt();
  rtc_init_interrupt();
  
  //*************************************//
  //          Welcome Note               //
  //*************************************//
  lcd_line1_disp("Power-Down Testing",0);
  ms_delay(50000);
  
  //*************************************//
  //  Displaying Static Messages		 //
  //*************************************//

  U0IER = 0;
  
  
    
  wdt_init();
  while(1)
  {	
  	
	wdt_feed(0x03ffffff);
	if(wdt_timeout == 1)
	{
		wdt_timeout = 0;
		lcd_line3_disp("WDEnable",12);
	}
	
	rtc_get_time();
	lcd_line2_disp(Uc_real_time,8);
	 
  	
	//*********************************************//
	//   displaying Real Time & user Set Time      //
	//*********************************************//
	if(Uc_alrm == 1)
	{
		Uc_alrm = 2;
		lcd_line3_disp("Alarm",9);
	}
   
   	//*********************************************//
	//			key press on background  		   //
	//*********************************************//
	Uc_key_temp = get_key(0);
	if(Uc_key_temp == '1')
	{
		Uc_key_temp = 0;
		get_user_time();
		PCON = 0x02;								 // forcing ARM in power-down mode
	
	}
  }
}







