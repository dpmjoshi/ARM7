#include "includes.h"
#define GSM_INIT_ERR 1<<5

void gsm_init(void);
void gsm_sms_send(U8*, U8*);
void gsm_sms_del(U8);
void gsm_sms_del_all(U8 );
void gsm_sms_frmt(U8 frmt);
void gsm_responce(void);
void gsm_check_status(void);

//*******************************************************//
U8 uc_gsm_flw_ctrl[20]  = {"AT+IFC=1,1\r\n"};
U8 uc_gsm_uart_baud[20] = {"AT+UART=2,9600\r\n"};
U8 uc_gsm_regi[20]      = {"AT+CREG=1\r\n"};
U8 Uc_send_sms1[20]     = {"AT+CMGS="};
U8 Uc_send_sms2[20]     = {",128\r"};
//*******************************************************//

SMS_INFO SMS_cur;

	
void gsm_init(void)
{  
	Uc_stat_code_gsm = 0;
	ms_delay(10000);
	uart1_tx_string(&uc_gsm_flw_ctrl[0]);
	LIB_frmt_arr(Uc_uart1_str_gsm, 50);		  
	ms_delay(10000);
	uart1_tx_string(&uc_gsm_regi[0]);
	ms_delay(10000);
	ms_delay(10000);
	ms_delay(10000);
	ms_delay(10000);
	ms_delay(10000);
	//gsm_sms_frmt('1');
	//gsm_sms_del_all(8);
	ms_delay(10000);
	ms_delay(10000);
	ms_delay(10000);	
}


// There are Two formats 0= PDU(Packet Data unit), 1= Text 
// Select text mode
void gsm_sms_frmt(U8 frmt)
{
 uart1_tx_string("AT+CMGf=");
 uart1_tx_byte(frmt);
 ms_delay(10000);
}

void gsm_sms_send(U8 *ph_no, U8 *sms_content)
{
	uart1_tx_string("AT+CMGS=");	
	uart1_tx_byte('"');	
	uart1_tx_string(ph_no);
	uart1_tx_byte('"');
	uart1_tx_string(",128\r");
	ms_delay(10000);
	uart1_tx_string(&sms_content[0]);
	ms_delay(500);	
	uart1_tx_byte(0x1a);
	ms_delay(50000);
	ms_delay(50000);
	/////////////////////////////////////////
}

/**********************************************************************************/
/* Function Name: gsm_sms_del_all												  */
/* Arguments	: NONE 												  			  */
/* Return Types	: uc_sms_count(Total SMS to be deleted)							  */
/* Description	: Function is to delete number of SIM messeges given by user      */
/**********************************************************************************/
void gsm_sms_del(U8 mem_location)
{

	U8 uc_gsm_sms_del[20] = {"AT+CMGD=1\r\n"};
	
	ms_delay(10000);
	ms_delay(10000);
	uc_gsm_sms_del[8] = mem_location;
	uart1_tx_string(&uc_gsm_sms_del[0]);
}

/**********************************************************************************/
/* Function Name: gsm_sms_del_all												  */
/* Arguments	: NONE 												  			  */
/* Return Types	: uc_sms_count(Total SMS to be deleted)							  */
/* Description	: Function is to delete number of SIM messeges given by user      */
/**********************************************************************************/
void gsm_sms_del_all(U8 uc_sms_count)
{
	while(uc_sms_count)
	{
	 	gsm_sms_del(uc_sms_count+0x30);
		uc_sms_count--;
		//gsm_responce();
	}
	
}

void gsm_check_status(void)
{
 
}

U8 gsm_phno_validate(U8 *phone_no)
{
  while(*phone_no)
  {


  }
  return 1;
}



void gsm_responce(void)
{
  U8 uc_temp_byte = 0;
  U8 uc_count = 0;
  U8 uc_recv_resp[10];
  VICIntEnClr |= (1 << UART0_CHANNEL_NO);
  while(uc_temp_byte != '\r')
  {
  	uc_temp_byte = uart1_rx_byte();
	uart0_tx_byte(uc_temp_byte + 0x26);
  }
  while(uc_temp_byte != '\n')
  {
	uc_temp_byte = uart1_rx_byte();
	uart0_tx_byte(uc_temp_byte + 0x26);
	uc_recv_resp[uc_count] = uc_temp_byte;
	uc_count++;
  }
    VICIntEnable |= (1 << UART0_CHANNEL_NO);
}

/**********************************************************************************/
/* Function Name: gsm_voice_call												  */
/* Arguments	: NONE 												  			  */
/* Return Types	: uc_sms_count(Total SMS to be deleted)							  */
/* Description	: 															      */
/**********************************************************************************/

void gsm_voice_call(U8 *phone_no)
{
 uart1_tx_string("ATD");
 uart1_tx_string(phone_no);
 uart1_tx_string(";\r\n");
} 
 
/**********************************************************************************/
/* Function Name: gsm_end_voice_call											  */
/* Arguments	: NONE 												  			  */
/* Return Types	: uc_sms_count(Total SMS to be deleted)							  */
/* Description	: 															      */
/**********************************************************************************/

void gsm_end_voice_call()
{
 uart1_tx_string("ATH\r\n");
} 

