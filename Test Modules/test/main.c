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
  lcd_line2_disp(&welcome_note1[0],0);
  lcd_line3_disp(&welcome_note2[0],6);
  ms_delay(50000);
  clrscr();
  lcd_line1_disp(&lcd_data_sys_chk[0],0);
  display_dots();
  display_dots();
  //*************************************//
  //  Displaying Static Messages		 //
  //*************************************//
  clrscr();
  default_page();
  U0IER = 0;

  rtc_get_time();
  lcd_line4_disp(&Uc_real_time[0],12);
  lcd_line4_disp(&Uc_set_user_time[0],0);

  wdt_init();
  while(1)
  {	
  
  	wdt_feed(0x03ffffff);
	rtc_get_time();
	lcd_line4_disp(&Uc_real_time[0],12);
	if(wdt_timeout == 1)
	{
		wdt_timeout = 0;
		lcd_line3_disp("WDEnable",12);
	}
	//*********************************************//
	//		ADC input value						   //
	//*********************************************//
	if(Uc_adc_time_out_flag == 1)
	{			
		Uc_adc_time_out_flag = 0;
		Ui_sample1 = adc1_getval();
		ms_delay(800);
		Ui_sample2 = adc1_getval();
		ms_delay(800);
		Ui_sample3 = adc1_getval();
		ms_delay(800);
		Ui_sample4 = adc1_getval();
		ms_delay(800);
		Ui_sample5 = adc1_getval();
		adc_val_conv(Ui_sample1, Ui_sample2, Ui_sample3, Ui_sample4, Ui_sample5, 1);
		temp_ctrl();
		lcd_line1_disp(&Uc_dec_arr[1],5);
		
		
					
		//*********Sending DATA to User desk*************//
		//uart0_send_string("\n\r ");
		uart0_send_byte((Ui_sample1 & 0xff));
		uart1_send_byte(0x7E);
		uart1_send_string(&Uc_dec_arr[1]);
		uart1_send_byte('\0');
		//**********************************************//
		
		Ui_sample1 = adc3_getval();
		ms_delay(900);
		Ui_sample2 = adc3_getval();
		ms_delay(900);
		Ui_sample3 = adc3_getval();
		ms_delay(900);
		Ui_sample4 = adc3_getval();
		ms_delay(900);
		Ui_sample5 = adc3_getval();
		ms_delay(750);
		Ui_sample6 = adc3_getval();
		ms_delay(750);
		Ui_sample7 = adc3_getval();
		ms_delay(750);
		Ui_sample8 = adc3_getval();
		ms_delay(750);
		Ui_sample9 = adc3_getval();
		Ui_sample6 = ((Ui_sample6 + Ui_sample7 + Ui_sample8 + Ui_sample9) / 4);
		Ui_sample5 = ((Ui_sample6 + Ui_sample5)/2);
		adc_val_conv(Ui_sample1, Ui_sample2, Ui_sample3, Ui_sample4, Ui_sample5 , 0);
		lcd_line3_disp(&Uc_dec_arr[1],5);
		
		//*********Sending DATA to User desk*************//
		uart1_send_string(&Uc_dec_arr[1]);
		//**********************************************//

	}


	//*********************************************//
	//   displaying Real Time & user Set Time      //
	//*********************************************//
	
	if(Uc_alrm == 1)
	{
		Uc_alrm = 2;
		pwm5_pulse_width(5000, 100);
	}
	/*
	else if(Uc_alrm == 3)
	{
		if(Uc_user_dwn_sec == 0)
		{
		   Uc_user_dwn_sec  = 59;

		   if( (Uc_user_dwn_min +  Uc_user_dwn_hr) != 0)
	   	 	{	
				Uc_user_dwn_min -= 1;
	   	   	}
		   Uc_set_user_time[3] = ((Uc_user_dwn_min / 10) + 0x30);
	   	   Uc_set_user_time[4] = ((Uc_user_dwn_min % 10) + 0x30);
		}
		if(Uc_user_dwn_min == 0)
		{
		   Uc_user_dwn_min  = 59;
	       if(Uc_user_dwn_hr != 0)
		   {
		   		Uc_user_dwn_hr -= 1;
		   }
	   	   Uc_set_user_time[0] = ((Uc_user_dwn_hr / 10) + 0x30);
	   	   Uc_set_user_time[1] = ((Uc_user_dwn_hr % 10) + 0x30);
		}
		Uc_set_user_time[6] = ((Uc_user_dwn_sec / 10) + 0x30);
		Uc_set_user_time[7] = ((Uc_user_dwn_sec % 10) + 0x30);
	 }

	 */
	//*********************************************//
	rtc_get_time();
	lcd_line4_disp(&Uc_real_time[0],12);
	lcd_line4_disp(&Uc_set_user_time[0],0);

	//*********************************************//
	//			key press on background  		   //
	//*********************************************//
	Uc_key_temp = get_key(0);
	if(Uc_key_temp == 'E')
	{
		Uc_key_temp = 0;
		get_user_time();
	}
	else if((Uc_key_temp == '.')&(Uc_alrm == 2))
	{
		Uc_key_temp = 0;
		Uc_alrm = 0;
		pwm_disable();
	}
	else if(Uc_key_temp == 'A')
	{
		clrscr();
		ms_delay(1000);
		lcd_line2_disp("Emergency Stop!",3);
		lcd_line4_disp("Cooling ON",5);
		IO0CLR = SSR_ON;
		IO0CLR = HEATER_ON;
		IO0SET = COOLER_ON;
		while(1);
	}
	else if(Uc_key_temp == 'D')
	{
		Uc_key_temp = 0;
		rtc_change_time();
	}

  }
}







