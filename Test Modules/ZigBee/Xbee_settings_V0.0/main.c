#include"includes.h"
//************************************************************//
#define no_recv_byte      14
#define COOLER_ON         1<<19
#define HEATER_ON         1<<20
#define	SSR_ON			  1<<21
#define	BUZZER			  1<<22


U8 uart1_set[30]         = {"\n\rUART1 connected at 9600-8-N"};
U8 uart0_set[30]         = {"\n\rUART0 connected at 9600-8-N"};
U8 welcome_note1[25]     = {"Reaction  Controller"};
U8 welcome_note2[20]     = {"NCL-Pune"};
U8 lcd_data_sys_chk[20]  = {"Initializing"};
U8 Uc_zigb_para[20]		 = {"000000"};

U32 Ui_sample1 = 0;
U32 Ui_sample2 = 0;
U32 Ui_sample3 = 0;
U32 Ui_sample4 = 0;
U32 Ui_sample5 = 0;
U32 Ui_sample6 = 0;
U32 Ui_sample7 = 0;
U32 Ui_sample8 = 0;
U32 Ui_sample9 = 0;

//*************************Flags*******************************//
U8 Uc_user_mode_flag = 4;



void main()
{   
  PINSEL0 |= 0X00050005;	 // selecting UART0 and UART1
  PINSEL1 |= 0X00080000;
  IO1DIR  |= 0X0FFF0000;	 //pins 1.16 to 1.23 output pins
  IO0DIR  |= 0X003E0C00;	 //port 0 rs and en as output
  IO0CLR   = 0X00FF0000;	
  
  IO0SET   = 0X0FF00400;
  IO0CLR   = BUZZER;

  //*************************************//
  //         Initialisations             //
  //*************************************//
  lcd_init();
 // irq_init();
  uart_init();
  adc_init();
  //wdt_init();
  pwm5_init();
  timer1_init_interrupt();
  rtc_init_interrupt();
  
  //*************************************//
  //          Welcome Note               //
  //*************************************//
 
  //*************************************//
  //  Displaying Static Messages		 //
  //*************************************//
  clrscr();
  default_page();
  U0IER = 0;
  wdt_init();
  while(1)
  {	
  	wdt_feed(0x03ffffff);

	Uc_key_temp = get_key(0);

	if(Uc_key_temp == '1')
	{
		Uc_key_temp = 0;
		clrscr();
		ms_delay(8000);

		ZIGB_setting();
		
		default_page();
		
   	}
  }
}







