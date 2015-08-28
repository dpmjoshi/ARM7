#include"includes.h"

U8 Uc_time1_arr[20];
U8 Uc_T1MR0 = 0;
U8 Uc_zb_tout = 0;

void timer1_ISR(void)__irq
{
	if((T1IR & 0x01) == 1)
	{
		Uc_T1MR0 = 1;
		Uc_zb_tout = 1;
		T1TCR = 0;
		uart0_send_string("\n\n\rTimeout Error!");
		T1IR = 0x01;
		
 	}
 	
	VICVectAddr   = 0x00;
}

void timer1_init_interrupt()
{
	VICVectAddr3 = (U32)&timer1_ISR;
  	VICVectCntl3 = 0x20 | 5;
	VICIntEnable = 1 << 5;
	T1MCR        = 0x01;
	T1MR0		 = 5000;
	T1PR		 = 15000;
	T1TCR        = 0x01;
}


void timer1_init()
{
	T1PR = 15000;
}

void timer1_on()
{
	T1TCR = 0x02;
	T1TCR = 0x01;
}

void timer1_off()
{
	T1TCR = 0x00;
}

void time1_measure()
{
 	U32 uc_time_t1pc;
	//U32 uc_time_t1tc;
	U8  uc_index = 0;

	uc_time_t1pc = T1PC;
	

	Uc_time1_arr[uc_index]  = uc_time_t1pc/10000;	
	Uc_time1_arr[uc_index] += 0x30;
	uc_time_t1pc            = uc_time_t1pc%10000;
	uc_index++;
	//--------------------------------------
	Uc_time1_arr[uc_index]  = uc_time_t1pc/1000;	
	Uc_time1_arr[uc_index] += 0x30;
	uc_time_t1pc            = uc_time_t1pc%1000;
	uc_index++;
	//--------------------------------------
	Uc_time1_arr[uc_index]  = uc_time_t1pc/100;
	Uc_time1_arr[uc_index] += 0x30;
	uc_time_t1pc    = uc_time_t1pc%100;
	uc_index++;
	//--------------------------------------
	Uc_time1_arr[uc_index]  = uc_time_t1pc/10;
	Uc_time1_arr[uc_index] += 0x30;
 	uc_time_t1pc            = uc_time_t1pc%10;
	uc_index++;
	//--------------------------------------
	//--------------------------------------
 	Uc_time1_arr[uc_index]  = uc_time_t1pc;
	Uc_time1_arr[uc_index] += 0x30;
 	uc_index++;
   
	Uc_time1_arr[uc_index]  = '\0' ;
	lcd_line4_disp(&Uc_time1_arr[0],0);


}

void ms_delay(unsigned int w)
{
   T0TCR  = 0X01;
   T0PR   = 1000;
   while(T0TC<w)
      {
	  }			                                                    
   T0TC   = 0;
   T0TCR  = 0;
}

void key_delay(unsigned int w)
{
   T0TCR = 0X01;
   T0PR  = 15000;
   while(T0TC<w)
      {
	  }			                                                    
   T0TC  = 0;
   T0TCR = 0;
}
