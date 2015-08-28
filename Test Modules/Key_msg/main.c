#include"includes.h"
//************************************************************//


//*************************Flags*******************************//
U8 Uc_new_key = 0;
U8 Uc_prev_key = 0;
U8 Uc_actual_key = 0;
U8 key_cnt = 0;
U8 msg_cnt = 0, first_key = 1;
U8 msg_arr[128] = {"                  "};

void main()
{   
  PINSEL0 |= 0X00050005;	 // selecting UART0 and UART1
  PINSEL1 |= 0X00080000;
  IO1DIR  |= 0X0FFF0000;	 //pins 1.16 to 1.23 output pins
  IO0DIR  |= 0X003E0C00;	 //port 0 rs and en as output
  IO0CLR   = 0X00FF0000;	
  
  IO0SET   = 0X0FF00400;
 

  //*************************************//
  //         Initialisations             //
  //*************************************//
  lcd_init();
  clrscr();
  //irq_init();
  uart_init();
  //adc_init();
 // pwm5_init();
  timer1_init_interrupt();
//  rtc_init_interrupt();
  ms_delay(1000);
  lcd_line4_disp("key test", 0);

  while(1)
  {	
  	 Uc_new_key = get_key(0);
	 lcd_line4_ch_disp(Uc_actual_key, 14);
	 lcd_line4_ch_disp(Uc_prev_key, 12);
	 lcd_line4_ch_disp(Uc_new_key, 10);

	/*
	 if(Uc_new_key != 0)
	 {
	  lcd_line4_ch_disp((key_cnt+0x30), 16);
	 }
	*/ 
	 if(Uc_new_key == '1')
	 {
	  Uc_new_key = 0;
	  if(msg_cnt > 0) 
	  {
	   msg_arr[msg_cnt] = ' ';
	   lcd_line1_disp(&msg_arr[0], 0);
	   msg_cnt -= 1 ;
	  }
	  else if(msg_cnt == 0)
	  {
	   msg_arr[msg_cnt] = ' ';
	   lcd_line1_disp(&msg_arr[0], 0);
	  }
	 }
	 if(Uc_new_key != 0)
	 {
	  if(Uc_time_out == 0)
	  {
	   if(Uc_new_key == Uc_prev_key)
	    {
	     if(key_cnt <= 1)
	      {
		   Uc_new_key = 0;
	       key_cnt++;
		   Uc_actual_key = Uc_prev_key + key_cnt;
		   msg_arr[msg_cnt] = Uc_actual_key;
  		   lcd_line1_disp(&msg_arr[0], 0);
 		   timer1_on();
		   
	      }
	     else
	      {
		   Uc_new_key = 0;
	       key_cnt = 0;
		   Uc_actual_key = Uc_prev_key + key_cnt;
		   msg_arr[msg_cnt] = Uc_actual_key;
		   lcd_line1_disp(&msg_arr[0], 0);
		   timer1_on();
	      }
	    }
	   else if(Uc_new_key != Uc_prev_key)
	    {
	     if(msg_cnt > 1)
	      {
		   timer1_off();
	       msg_arr[msg_cnt] = Uc_actual_key;
	       msg_cnt++;
		   lcd_line1_disp(&msg_arr[0], 0);
		   Uc_prev_key   = Uc_new_key;
		   Uc_actual_key = Uc_new_key;
		   Uc_new_key = 0;
		   timer1_on();
	      }
	     else
	      {
		   timer1_off();
	 	   Uc_prev_key   = Uc_new_key;
		   Uc_actual_key = Uc_new_key;
		   msg_arr[msg_cnt] = Uc_actual_key;
		   if(first_key == 1)
		   {
		    first_key = 0; 
		   }
		   else
		   {
		    msg_cnt++;
		   }

		   lcd_line1_disp(&msg_arr[0], 0);
		   Uc_new_key = 0;
		   timer1_on();
	      }
	    }
       }
     } 
    if(Uc_time_out == 1)
	  {
	   timer1_off();
	   Uc_time_out = 0;
	   lcd_line1_disp("Time out", 11);
	   ms_delay(10000);
	   lcd_line1_disp("        ", 11);
	   msg_arr[msg_cnt] = Uc_actual_key;
	   msg_cnt++;
       lcd_line1_disp(&msg_arr[0], 0);
	  }
	 
   }


}




