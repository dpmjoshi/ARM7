#include"includes.h"

#define OUT_PORT     1<<6
#define EINT0_MASK	 0x01
#define EINT1_MASK	 0x02
#define EINT2_MASK	 0x04
#define EINT3_MASK	 0x08
//*************************Flags*******************************//

extern U32 Uc_freq_count = 0;


void ext_int1()__irq
{
  Uc_freq_count += 1;
  time1_measure(Uc_freq_count);
  EXTINT = EINT1_MASK;
  VICVectAddr   = 0x00;
}


void extint_init()
{

  EXTPOLAR  = EINT1_MASK;
  EXTMODE   = EINT1_MASK;

  VICVectAddr6 = (U32)&ext_int1;
  VICVectCntl6 = 0x20 | 15;
  VICIntEnable = 1 << 15;
}


void main()
{   
  //extint_init();
  
  PINSEL0 |= 0X000500c5;	 // selecting UART0 and UART1
  PINSEL1 |= 0X00080000;
  IO1DIR  |= 0X0FFF0000;	 //pins 1.16 to 1.23 output pins
  IO0DIR  |= 0X003E0C40;	 //port 0 rs and en as output
  IO0CLR   = 0X00FF0000;	
  
  IO0SET   = 0X0FF00400;

  
  //*************************************//
  //         Initialisations             //
  //*************************************//
  rtc_init_interrupt();
  lcd_init();
  clrscr();
  extint_init();
  ms_delay(1000);
  lcd_line1_disp("EXT INT2",0);
  ms_delay(1000);
  while(1)
  {	
   rtc_get_time();
   lcd_line3_disp(&Uc_real_time[0],11);
   /*
   
   if(Uc_rtc_flag == 1)
   {
		lcd_line3_disp("RTC int",0);
  		Uc_rtc_flag = 0;
		time1_measure(Uc_freq_count);
		Uc_freq_count = 0;

   }
   */
   IO0SET = OUT_PORT;
   ms_delay(10000);
   IO0CLR = OUT_PORT;
   ms_delay(10000);

  }
}







