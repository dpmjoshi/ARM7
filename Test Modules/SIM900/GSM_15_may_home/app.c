#include"includes.h"
#define     PAGE_SIZE        128
#define     DEVICE_ADDR      0XA0


void APP_default_page()
{
	clrscr();
	lcd_line_disp("NCL Mobile", 5, 2);
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
	lcd_line_disp("Phone:",0, 1);
	lcd_line_disp("Call",0, 4);
	lcd_line_disp("Cancel",14, 4);
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
		lcd_line_disp(&uc_phone_no[0], 7, 1);
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


