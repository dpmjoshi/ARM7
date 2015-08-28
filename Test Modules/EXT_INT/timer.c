#include"includes.h"

#define CAP0_RISE_EDGE 0x00000001 
#define CAP0_INT	   0x00000004

U8 Uc_time1_arr[20];
U8 Uc_fre = 0;
U32 Uc_pulse_width = 0;


void timer0_ISR(void)__irq
{
	if((T0IR & 0x10) == 1)
	{
		if(Uc_fre == 1)
		{	
			Uc_fre += 1;
			Uc_pulse_width = T1CR0;
			T0PC = 0;
			T0TC = 0;
			
		}
		else
		{
			Uc_fre += 1;
		}
		T0IR = 0x10;
 	}
 	
	VICVectAddr   = 0x00;
}


void timer0_init_interrupt()
{
	
	
	VICVectAddr3 = (U32)&timer0_ISR;
  	VICVectCntl3 = 0x20 | 4;
	VICIntEnable = 1 << 4;
	//T1MCR      = 0x01;
	//T1MR0		 = 1000;
	T0CCR		 = 0x00;
	
	T0CTCR       = 0x02;
	T0PR		 = 15000;
	T0TCR        = 0x01;
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
	//U32 uc_time_t1tc;
	U8  uc_index = 0;

	//uc_time_t1pc = T1PC;
	 	
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
