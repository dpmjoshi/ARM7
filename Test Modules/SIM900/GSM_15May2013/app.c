#include"includes.h"
#define     PAGE_SIZE        128
#define     DEVICE_ADDR      0XA0


void APP_default_page()
{
	clrscr();
	lcd_line2_disp("NCL Mobile", 5);
}

/**********************************************************************************/
/* Function Name: APP_phone_dial												  */
/* Arguments	: *phone_no 												  			  */
/* Return Types	: 																  */
/* Description	: 															      */
/**********************************************************************************/


U8 APP_phone_dial(U8 *phone_no)
{
	U8 uc_cnt = 10;
	U8 uc_temp_key = 0;
	U8 *uc_ptr;
	U8 uc_phone_no[20] = {0};
	clrscr();
	lcd_line1_disp("Phone:",0);
	lcd_line4_disp("Call",0);
	lcd_line4_disp("Cancel",14);
	ms_delay(8000);

	uc_ptr = &uc_phone_no[0];
	while(uc_temp_key != 'E')
	{
		uc_temp_key = get_key(0);
		if((uc_temp_key >= '0') && (uc_temp_key <= '9'))
		{
			*uc_ptr = uc_temp_key;
			uc_ptr++;
		}
		else if(uc_temp_key == 'A')
		{
			if(uc_ptr >= &uc_phone_no[0])
	 		{		
	   			if(uc_ptr > &uc_phone_no[0])
	 			{
					uc_ptr--;
				}
			*uc_ptr = ' ';
	 		}
		}
		else if(uc_temp_key == 'D')
		{
	 		return 0;
		}
		lcd_line1_disp(&uc_phone_no[0], 7);
    	ms_delay(1100);
  	}
  	*uc_ptr = '\0';

  	uc_cnt = LIB_strlen(&uc_phone_no[0]);
  	if(uc_cnt > 0)
  	{
  		LIB_str_copy(&uc_phone_no[0], phone_no, uc_cnt+1);
  		return 1;
  	}
  	else
  	{
   		return 2;
  	}
}

/**********************************************************************************/
/* Function Name: APP_keypad												  	  */
/* Arguments	: 			 												  	  */
/* Return Types	: 																  */
/* Description	: 															      */
/**********************************************************************************/

void APP_msgkey(U8 *text_msg)
{
	U8 uc_key = 0;
	U8 *uc_ptr, *temp_msg;
	U8 cur_key = 0;
	U8 prev_key = 0;
	U8 *msg_arr[15]	= {" 0", ".,;1", "abc2", "def3", "ghi4", "jkl5", "mno6", "pqrs7", "tuv8", "wxyz9"}; 
	
	temp_msg = text_msg;
	clrscr();
	
	while(cur_key != 'D')
	{	
 		cur_key = get_key(1);
		uart0_tx_string("\r\nCur key: ");
		uart0_tx_byte(cur_key);
		uart0_tx_string("\r\nPrev key: ");
		uart0_tx_byte(prev_key);
		

		if((cur_key >= '0')&&(cur_key <= '9'))
		{
			if(cur_key == prev_key)
			{
	  			if(*(uc_ptr + 1) == 0)
	  			{
					uart0_tx_string("\r\n *uc_ptr == 0 ");
		   			uc_ptr = msg_arr[cur_key - 0x30];
				}
	  			else
	  			{
					uart0_tx_string("\r\n *uc_ptr != 0 ");
	   				uc_ptr++;
	   			}
				*text_msg = *uc_ptr;  
			}
			else 
			{
			 	uc_ptr = msg_arr[cur_key - 0x30];
		   		text_msg++;
				*text_msg = *uc_ptr;
				*(text_msg + 1) = '\0';
				prev_key = cur_key;
			}
		}
		else if(cur_key == 'A')
		{
		 *text_msg = ' ';
		 if(text_msg != temp_msg)
		 {
		 	text_msg--;
		 }
		}
		lcd_line_disp(temp_msg, 0, 1);
		uart0_tx_string("\n\r----->");
		uart0_tx_string(uc_ptr);
		uart0_tx_string("\n\r----->");
		uart0_tx_string(temp_msg);
		ms_delay(500);
	}
}


