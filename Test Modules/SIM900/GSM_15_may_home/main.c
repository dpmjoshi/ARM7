#include "includes.h"

U8  Uc_new_ip_msg[80];
U8  temp_byte = 0;
U8  Uc_gsm_sms_read[20]  = {"AT+CMGR=1,0\r\n"};
U8  temp_key = 0;
U8  uc_temp[15];
U32 ui_temp = 0;
U8  phone_no[15];
U8  *main_opt[10] = {"CALL", "Save Number", "Message", "Internet Call", "Exit", " "};
U8  msg[50] = {"-----------9"};


void main(void)
{

 lcd_init();
 lcd_line_disp("SIM900 testing",3, 2);
 uart_init_interrupt();
// VICIntEnClr |= (1 << UART1_CHANNEL_NO);
 gsm_init();
 rtc_init();
 GSM_APP_diallist_init(10);
 ms_delay(10000);
 //VICIntEnable |= (1 << UART1_CHANNEL_NO);
 uart0_tx_string("\n\rGSM Init Complete...");
 if(Uc_stat_code_gsm != 0)
 {
	Uc_stat_code_gsm = 0;
	uart0_tx_string("\n\n\rBigg Big reason to Worry...!!!!");
 }

 
 while(1)
 {
  //gsm_check_status();	

	rtc_get_time(time);
	lcd_line_disp(time, 8, 4);

   temp_key = get_key(0);

   	if(temp_key == '1')
	{
		GSM_APP_call(phone_no);		
	}
   	else if(temp_key == '2')
	{
		ms_delay(1000);
		GSM_APP_diallist_show();	             
	}
   	else if(temp_key == 'D')
   	{
		gsm_end_voice_call();
		ms_delay(2000);
		APP_default_page();
	}
	else if(temp_key == 'E')
   	{
		GSM_APP_options(main_opt, 3);
		ms_delay(2000);
		APP_default_page();
	}
	else if(temp_key == '0')
	{
		GSM_APP_write(msg);
	}
  /*
  if(Uc_stat_code_gsm == 11)
  {
	if(strgcmp(&Uc_uart1_str_gsm[0],"\r\n+CMTI:"))
	{
		Uc_stat_code_gsm = 20;
		Uc_gsm_sms_read[8] = Uc_uart1_str_gsm[14];
		uart0_tx_string(Uc_uart1_str_gsm);
		uart0_tx_string("\n\n\rCompared");
		uart1_tx_string(Uc_gsm_sms_read);
	}
	else
	{
		Uc_stat_code_gsm = 0;	// Comparision fails which shows that unwanted event ocurred. Thus making status code 0 &
							   // byte_cnt = 0. So that hence forth we do not miss any notifications.
		uart0_tx_string("\n\n\rCompare fails:");
 	}	
  }
  else if(Uc_stat_code_gsm == 20)
  {
  	 //uart0_tx_string("\n\rcase 20:");
  }
  else if(Uc_stat_code_gsm == 23)
  {
	str_copy(&SMS_cur.detail[33], SMS_cur.ph_no, 13);
	uart0_tx_string("\n\rMSG Details. : ");
	uart0_tx_string(&SMS_cur.detail[10]);

	uart0_tx_string("\n\rPhone No. : ");
	uart0_tx_string(SMS_cur.ph_no);

  }
  else if(Uc_stat_code_gsm == 24)
  {
 	Uc_stat_code_gsm = 0;
	uart0_tx_string("\n\rMessage : ");
	uart0_tx_string(SMS_cur.data);
  }	
  
  */   
 }	
}
