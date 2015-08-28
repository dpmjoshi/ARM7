#include "includes.h"    

#define RESP_ON_UART0 1

void ZIGB_cmd_mode();
void ZIGB_wr_cmd();
void ZIGB_exit_cmd();
void ZIGB_dl_wrt(U8*);
void ZIGB_pan_wrt(U8*);
void ZIGB_my_wrt(U8*);
void ZIGB_ch_wrt(U8*);
void ZIGB_setting();
void ZIGB_my_read();
void ZIGB_pan_read();
void ZIGB_ch_read();
void ZIGB_dl_read();
void ZIGB_node_disc();
void ZIGB_write();
void ZIGB_read();
void ZIGB_wr_page();
void ZIGB_menu_page();


U8 Uc_zigb_pan[10]  = {"0000"};
U8 Uc_zigb_ch[10]   = {"0C"};
U8 Uc_zigb_my[10]   = {"0000"};
U8 Uc_zigb_dl[10]   = {"0000"};
U8 Uc_zigb_node[50]	= {"0"};

U8 ZIGB_responce(U8, U8*);	



/**********************************************************************************/
/* Function Name: ZIGB_cmd_mode()												  */
/* Arguments	: NONE	  														  */
/* Return Types	: NONE															  */
/* Description	: The function enters into the command mode.					  */
/**********************************************************************************/

void ZIGB_cmd_mode()
{
 uart1_send_string("+++");
 clrscr();
 lcd_line1_disp("CMD Mode",0);

 if(ZIGB_responce(3,"OK\r"))
  {
   #if RESP_ON_UART0 == 1
   uart0_send_string("\n\n\rCMD: OK ");
   #endif
   ms_delay(10000);
  }
 else
  {
   #if RESP_ON_UART0 == 1
   uart0_send_string("\n\n\rCMD: ERROR ");
   #endif
   ms_delay(10000);
  }
}

/**********************************************************************************/
/* Function Name: ZIGB_wr_cmd()												      */
/* Arguments	: NONE	  														  */
/* Return Types	: NONE															  */
/* Description	: The function sends wr cmd to ZigBee module.					  */
/**********************************************************************************/

void ZIGB_wr_cmd()
{
 uart1_send_string("ATWR\r");
 if(ZIGB_responce(3,"OK\r"))
  {
   #if RESP_ON_UART0 == 1
 	uart0_send_string("\n\n\rWR CMD: OK ");
   #endif
   ms_delay(10000);
  }
 else
  {
   #if RESP_ON_UART0 == 1
    uart0_send_string("\n\n\rWR CMD: ERROR ");
   #endif
   ms_delay(10000);
  }
}
 
/**********************************************************************************/
/* Function Name: ZIGB_exit_cmd()												  */
/* Arguments	: NONE	  														  */
/* Return Types	: NONE															  */
/* Description	: The function exits from the command mode.						  */
/**********************************************************************************/

void ZIGB_exit_cmd()
{
 uart1_send_string("ATCN\r");
 if(ZIGB_responce(3,"OK\r"))
  {
   #if RESP_ON_UART0 == 1
   uart0_send_string("\n\n\rExit CMD: OK ");
   #endif
   ms_delay(10000);
  }
 else
  {
   #if RESP_ON_UART0 == 1
   uart0_send_string("\n\n\rExit CMD: ERROR ");
   #endif
   ms_delay(10000);
  }
}


/**********************************************************************************/
/* Function Name: ZIGB_dl_wrt()												  	  */
/* Arguments	: U8 *dest_add(pointer to the array which will hold the 		  */
/*				  destination add ) 											  */
/* Return Types	: NONE															  */
/* Description	: The function writes destination add. to ZigBee.				  */
/**********************************************************************************/

void ZIGB_dl_wrt(U8 *dest_add)
{
  uart1_send_string("ATDL");
  uart1_send_string(dest_add);
  uart1_send_byte('\r');
  if(ZIGB_responce(3,"OK\r"))
  {
   #if RESP_ON_UART0 == 1
   uart0_send_string("\n\n\rDL: OK ");
   #endif
   ms_delay(10000);
  }
 else
  {
   #if RESP_ON_UART0 == 1
   uart0_send_string("\n\n\rDL: ERROR ");
   #endif
   ms_delay(10000);
  }

}


/**********************************************************************************/
/* Function Name: ZIGB_pan_wrt()												  */
/* Arguments	: U8 *pan_add(pointer to the array which will hold the PAN add )  */													  
/* Return Types	: NONE															  */
/* Description	: The function writes PAN add. to ZigBee.						  */
/**********************************************************************************/

void ZIGB_pan_wrt(U8 *pan_add)
{
  uart1_send_string("ATID");
  uart1_send_string(pan_add);
  uart1_send_byte('\r');

   if(ZIGB_responce(3,"OK\r"))
  {
   #if RESP_ON_UART0 == 1
   uart0_send_string("\n\n\rPAN: OK ");
   #endif
   ms_delay(10000);
  }
 else
  {
   #if RESP_ON_UART0 == 1
   uart0_send_string("\n\n\rPAN: ERROR ");
   #endif
   ms_delay(10000);
  }
}

/**********************************************************************************/
/* Function Name: ZIGB_my_wrt()												      */
/* Arguments	: U8 *my_add(pointer to the array which will hold the MY add )	  */													  
/* Return Types	: NONE															  */
/* Description	: The function writes MY add. to ZigBee.						  */
/**********************************************************************************/

void ZIGB_my_wrt(U8 *my_add)
{
  uart1_send_string("ATMY");
  uart1_send_string(my_add);
  uart1_send_byte('\r');

   if(ZIGB_responce(3,"OK\r"))
  {
   #if RESP_ON_UART0 == 1
   uart0_send_string("\n\n\rMY: OK ");
   #endif
   ms_delay(10000);
  }
 else
  {
   #if RESP_ON_UART0 == 1
   uart0_send_string("\n\n\rMY: ERROR ");
   #endif
   ms_delay(10000);					  
  }
}


/**********************************************************************************/
/* Function Name: ZIGB_ch_wrt()												      */
/* Arguments	: U8 *ch_no(pointer to the array which will hold the MY add )	  */													  
/* Return Types	: NONE															  */
/* Description	: The function writes MY add. to ZigBee.						  */
/**********************************************************************************/

void ZIGB_ch_wrt(U8 *ch_no)
{
  uart1_send_string("ATCH");
  uart1_send_string(ch_no);
  uart1_send_byte('\r');

   if(ZIGB_responce(3,"OK\r"))
  {
   #if RESP_ON_UART0 == 1
   uart0_send_string("\n\n\rCH: OK ");
   #endif
   ms_delay(10000);
  }
 else
  {
   #if RESP_ON_UART0 == 1
   uart0_send_string("\n\n\rCH: ERROR ");
   #endif
   ms_delay(10000);
  }
}

/**********************************************************************************/
/* Function Name: ZIGB_responce()												  */
/* Arguments	: U8 resp_cnt(defines the responce count)						  */
/*				  U8 *resp (pointer to array containning expected responce)		  */
/* Return Types	: NONE															  */
/* Description	: This function waits for ZigBee to respond on the entered		  */
/*				  AT commands. 													  */
/**********************************************************************************/

U8 ZIGB_responce(U8 resp_cnt, U8 *resp)
{
  U8 temp_arr[20]= "000";
  U8 temp_cnt ;
  for(temp_cnt = 0; temp_cnt < resp_cnt; temp_cnt++)
   {
   	while((U1LSR & 0x01) == 0);
   	temp_arr[temp_cnt] = U1RBR;
   }	
  if(str_cmp(&temp_arr[0],resp))
   {
	 return 1;
   }
  else
   {
	return 0;
   }
}

/**********************************************************************************/
/* Function Name: ZIGB_setting()												  */
/* Arguments	: NONE															  */
/* Return Types	: NONE															  */
/* Description	: This function provides an interface for ZigBee settings through */
/*				  AT Commands. This fn is divided into two parts: 				  */
/*				  a) Read	b) Write											  */
/**********************************************************************************/

void ZIGB_setting()
{
 ZIGB_menu_page();
 
 while((Uc_key_temp = get_key(1)) != 'A')
 {
  if(Uc_key_temp == '1')
  {
  	Uc_key_temp = 0;

	#if RESP_ON_UART0 == 1
	uart0_send_string("\n\n\rReading ZigBee Parameters...");
	#endif
	ZIGB_read();
	ZIGB_menu_page();
  }
  else if(Uc_key_temp == '2')
  {
   	Uc_key_temp = 0;
	ms_delay(1000);
	#if RESP_ON_UART0 == 1
	uart0_send_string("\n\n\rWritting ZigBee Parameters...");
	#endif
	ZIGB_write();
	ZIGB_menu_page();
  }
 }
}

/**********************************************************************************/
/* Function Name: ZIGB_my_read()												  */
/* Arguments	: NONE															  */
/* Return Types	: NONE (Stores MY add. in a Global array Uc_zigb_my[])			  */
/* Description	: AT command function to read MY address of ZigBee				  */
/*				  																  */
/**********************************************************************************/

void ZIGB_my_read()
{
  U8 temp_cnt;
  
  uart1_send_string("ATMY");
  uart1_send_byte('\r');

  for(temp_cnt = 0; Uc_zigb_my[temp_cnt - 1] != '\r'; temp_cnt++)
  {
   	while((U1LSR & 0x01) == 0);
   	Uc_zigb_my[temp_cnt] = U1RBR;
  }

  Uc_zigb_my[temp_cnt - 1] = '\0';

  uart0_send_string("\n\n\rMY : ");
  uart0_send_string(&Uc_zigb_my[0]);
}


/**********************************************************************************/
/* Function Name: ZIGB_pan_read()												  */
/* Arguments	: NONE															  */
/* Return Types	: NONE (Stores PAN add. in a Global array Uc_zigb_pan[])		  */
/* Description	: AT command function to read PAN address of ZigBee				  */
/*				  																  */
/**********************************************************************************/

void ZIGB_pan_read()
{
  U8 temp_cnt;
  
  uart1_send_string("ATID");
  uart1_send_byte('\r');

  for(temp_cnt = 0; Uc_zigb_pan[temp_cnt - 1] != '\r'; temp_cnt++)
  {
   	while((U1LSR & 0x01) == 0);
   	Uc_zigb_pan[temp_cnt] = U1RBR;
  }

  Uc_zigb_pan[temp_cnt - 1] = '\0';

  uart0_send_string("\n\n\rPAN: ");
  uart0_send_string(&Uc_zigb_pan[0]);
}

/**********************************************************************************/
/* Function Name: ZIGB_ch_read()												  */
/* Arguments	: NONE															  */
/* Return Types	: NONE (Stores CH no. in a Global array Uc_zigb_ch[])			  */
/* Description	: AT command function to read CH no. of ZigBee					  */
/*				  																  */
/**********************************************************************************/

void ZIGB_ch_read()
{
  U8 temp_cnt;
  
  uart1_send_string("ATCH");
  uart1_send_byte('\r');

  for(temp_cnt = 0; Uc_zigb_ch[temp_cnt - 1] != '\r'; temp_cnt++)
  {
   	while((U1LSR & 0x01) == 0);
   	Uc_zigb_ch[temp_cnt] = U1RBR;
  }

  Uc_zigb_ch[temp_cnt - 1] = '\0';

  uart0_send_string("\n\n\rCH : ");
  uart0_send_string(&Uc_zigb_ch[0]);
}

/**********************************************************************************/
/* Function Name: ZIGB_dl_read()												  */
/* Arguments	: NONE															  */
/* Return Types	: NONE (Stores DL add. in a Global array Uc_zigb_dl[])			  */
/* Description	: AT command function to read DL add. of ZigBee					  */
/*				  																  */
/**********************************************************************************/

void ZIGB_dl_read()
{
  U8 temp_cnt;
  
  uart1_send_string("ATDL");
  uart1_send_byte('\r');

  for(temp_cnt = 0; Uc_zigb_dl[temp_cnt - 1] != '\r'; temp_cnt++)
  {
   	while((U1LSR & 0x01) == 0);
   	Uc_zigb_dl[temp_cnt] = U1RBR;
  }

  Uc_zigb_dl[temp_cnt - 1] = '\0';

  uart0_send_string("\n\n\rDL : ");
  uart0_send_string(&Uc_zigb_dl[0]);
}

/**********************************************************************************/
/* Function Name: ZIGB_node_disc()												  */
/* Arguments	: NONE															  */
/* Return Types	: NONE (Discovers Nodes in near range and stores in a Global	  */
/*				  array Uc_zigb_node[])			  								  */
/* Description	: AT command function to read DL add. of ZigBee					  */
/*				  																  */
/**********************************************************************************/

void ZIGB_node_disc()
{
  U32      temp_arr[50]; 
  ZB_NODE  zb_node1;
  U8       *temp_ptr;
  U8       uc_cnt = 0;

  uart0_send_string("\n\n\rNode Search");
  LIB_frmt_arr(Uc_recv_data, 100);
  
  U1IER = 0x01;
  
  uart1_send_string("ATND");
  uart1_send_byte('\r');
     
  ms_delay(100000);

  U1IER = 0x00;
  
  uart0_send_string("\n\n\rND :\n");
  uart0_send_string(Uc_recv_data);
 
  LIB_frag_arr(Uc_recv_data, temp_arr,'\r');

  
  str_copy(temp_arr[0], zb_node1.my, '\r');
  uart0_send_string("\n\n\rRemote MY: ");
  uart0_send_string(zb_node1.my);
  
 
  str_copy(temp_arr[1], zb_node1.serial_high, '\r');
  uart0_send_string("\n\n\rRemote Serial High: ");
  uart0_send_string(zb_node1.serial_high);
  

  str_copy(temp_arr[2], zb_node1.serial_low, '\r');
  uart0_send_string("\n\n\rRemote Serial Low: ");
  uart0_send_string(zb_node1.serial_low);
 
  str_copy(temp_arr[3], zb_node1.db, '\r');
  uart0_send_string("\n\n\rDB: ");
  uart0_send_string(zb_node1.db);

  
  Uc_byte_count = 0; 
}
 
/**********************************************************************************/
/* Function Name: ZIGB_read()													  */
/* Arguments	: NONE															  */
/* Return Types	: NONE															  */
/* Description	: reads all the basic parameters of Zigbee						  */
/*				  																  */
/**********************************************************************************/

void ZIGB_read()
{
 ZIGB_cmd_mode();
 ZIGB_my_read(); 
 ZIGB_pan_read();
 ZIGB_ch_read();
 ZIGB_dl_read();
 ZIGB_node_disc();
 ZIGB_exit_cmd();
}


/**********************************************************************************/
/* Function Name: ZIGB_write()													  */
/* Arguments	: NONE															  */
/* Return Types	: NONE															  */
/* Description	: writes all the basic parameters of Zigbee						  */
/*				  PAN, DL, CH, MY												  */
/**********************************************************************************/

void ZIGB_write()
{
 ZIGB_read();

 ZIGB_wr_page();
 
 Uc_key_temp = get_key(0);
 while(Uc_key_temp != 'D')
 {
  Uc_key_temp = get_key(0);
  wdt_feed(0x03ffffff);
  lcd_line1_disp(&Uc_zigb_pan[0],10);
  lcd_line2_disp(&Uc_zigb_ch[0],10);
  lcd_line3_disp(&Uc_zigb_my[0],10);
  lcd_line4_disp(&Uc_zigb_dl[0],10);
  

  if(Uc_key_temp == '1')
  { 
 	clrscr();
	lcd_line1_disp("PAN",0);
 	key_usr_ip(4,&Uc_zigb_pan[0],1,10);
	ZIGB_wr_page();
  }
  else if(Uc_key_temp == '2')
   {
	clrscr();
	lcd_line1_disp("CH",0);
    key_usr_ip(2,&Uc_zigb_ch[0],1,10);
	ZIGB_wr_page();
   }
  else if(Uc_key_temp == '3')
   {
 	clrscr();
	lcd_line1_disp("MY",0);
 	key_usr_ip(4,&Uc_zigb_my[0],1,10);
	ZIGB_wr_page();
   }
  else if(Uc_key_temp == '4')
   {
 	clrscr();
	lcd_line1_disp("DL",0);
 	key_usr_ip(4,&Uc_zigb_dl[0],1,10);
	ZIGB_wr_page();
   }
 }

 ms_delay(500);

 // Writing to ZigBee //
 
 ZIGB_cmd_mode();
 
 ZIGB_dl_wrt(&Uc_zigb_dl[0]);
 ZIGB_pan_wrt(&Uc_zigb_pan[0]);
 ZIGB_my_wrt(&Uc_zigb_my[0]);
 ZIGB_ch_wrt(&Uc_zigb_ch[0]);

 ZIGB_wr_cmd();

 ZIGB_exit_cmd();

}

/**********************************************************************************/
/* Function Name: ZIGB_wr_page()												  */
/* Arguments	: NONE															  */
/* Return Types	: NONE															  */
/* Description	: Static content displayed on 3rd page for Zigbee settings		  */
/*				  This page is related  with the Writing to ZigBee				  */
/**********************************************************************************/

void ZIGB_wr_page()
{
 clrscr();
 lcd_line1_disp("PAN",0);
 lcd_line2_disp("CH",0);
 lcd_line3_disp("MY",0);
 lcd_line4_disp("DL",0);
}

/**********************************************************************************/
/* Function Name: ZIGB_menu_page()												  */
/* Arguments	: NONE															  */
/* Return Types	: NONE															  */
/* Description	: Static content displayed on 2nd page for Zigbee settings		  */
/*				  																  */
/**********************************************************************************/

void ZIGB_menu_page()
{
 clrscr();
 lcd_line1_disp("ZigBee Settings",2);
 lcd_line2_disp("Read    [1]",0);
 lcd_line3_disp("Write   [2]",0);
 ms_delay(1000);
}

