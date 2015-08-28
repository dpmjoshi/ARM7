#include"includes.h"

U8  Uc_time1_arr[20];
U8  Uc_fre = 1;
U32 Uc_pulse_width = 0;

void timer0_ISR(void)__irq
{
	if((T0IR & 0x10))
	{
		Uc_pulse_width = T0CR0;
		T0TC = 0x00;
		uart0_send_string("A");
		T0IR = 0x10;
 	}
	if((T0IR & 0x20))
	{
		Uc_pulse_width = T0CR1;
		T0TC = 0x00;
		uart0_send_string("B");
		T0IR = 0x20;
 	}

 VICVectAddr   = 0x00;
}


void timer0_init_interrupt()
{		
	VICVectAddr4 = (U32)&timer0_ISR;
  	VICVectCntl4 = 0x20 | 4;
	VICIntEnable = 1 << 4;

	T0PR		 = 15000;
	T0TCR        = T0_RESET;
	T0CTCR       = 0x00;
	T0CCR		 = (CAP1_RISE | CAP1_I );
	T0TCR        = T0_START;
}

void timer1_init()
{
	T1PR = 15000;
}

void timer1_on()
{
	T1PC = 0;
	T1TCR = 0x01;
}

void timer1_off()
{
	T1TCR = 0x00;
}

void time1_measure(U32 timer_val)
{
 	U32 uc_time_t1pc;
	U8  uc_index = 0;
	
	uc_time_t1pc = timer_val;

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
   T1TCR  = 0X01;
   T1PR   = 1000;
   while(T1TC<w)
      {
	  }			                                                    
   T1TC   = 0;
   T1TCR  = 0;
}

void key_delay(unsigned int w)
{
   T1TCR = 0X01;
   T1PR  = 15000;
   while(T1TC<w)
      {
	  }			                                                    
   T1TC  = 0;
   T1TCR = 0;
}
