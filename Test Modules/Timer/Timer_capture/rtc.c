#include"includes.h"

void rtc_init();
void rtc_init_interrupt();
void rtc_ISR()__irq;
void rtc_get_time();


U8 	Uc_real_time[9]  = {"00:00:00"};
U8 	Uc_date[11]      = {"00/00/0000"};
U16	Uc_time_sec;
U8	Uc_alrm = 0;

void rtc_init()
{
	SEC     = 0;
	MIN     = 02;
	HOUR    = 11;

	DOM		= 28;
	MONTH	= 02;
	YEAR	= 2012;

	CCR     = 0x11;
}


void rtc_init_interrupt()
{
   	VICVectAddr0 = (U32)&rtc_ISR;
  	VICVectCntl0 = 0x20 | 13;
  	VICIntEnable = 1 << 13;

/*	
	SEC     = 0;
	MIN     = 53;
	HOUR    = 15;

	DOM		= 2;
	MONTH	= 03;
	YEAR	= 2012;
*/	
	AMR		= 0xF8;
	CIIR    = 0x01;
	CCR     = 0x11;
}

//*******************************************************//
//*******************************************************//

void rtc_ISR()__irq
{
	if(ILR & 0x01)
	 {
	 	//Uc_time_sec++;
	    Uc_fre = 1;
		//T0TC   = 0;
		ILR = 1;
	
	 }
	if(ILR & 0x02)
	 {
	 	Uc_alrm = 1;
		ILR = 2;
	
	 }

	VICVectAddr   = 0x00;
}
//*******************************************************//
//*******************************************************//
void set_alarm(U8 alarm_hr, U8 alarm_min, U8 alarm_sec)
{
	alarm_sec = alarm_sec + SEC;
	if(alarm_sec > 59)
	{
		ALSEC      = alarm_sec - 59;
		alarm_min += 1;
	}
	else
	{
		ALSEC = alarm_sec;
	}

	alarm_min = alarm_min + MIN;
	if(alarm_min > 59)
	{
		ALMIN      = alarm_min - 59;
		alarm_hr  += 1;
	}
	else
	{
		ALMIN      = alarm_min;
	}

	alarm_hr = alarm_hr + HOUR;
	if(alarm_hr > 23)
	{
		ALHOUR      = alarm_hr - 23;
	}
	else
	{
		ALHOUR      = alarm_hr;
	}
}


//**********************************************************//

void rtc_get_time()
{
	U16 us_temp_y, us_temp_yr;
	U8 uc_temp;

  	us_temp_y  = YEAR;
	us_temp_y  = us_temp_y / 1000;
	Uc_date[6] = us_temp_y + 0x30;
	us_temp_y  = YEAR;
	
	us_temp_y  = us_temp_y % 1000;
	us_temp_yr = us_temp_y;

	us_temp_y  = us_temp_y / 100;
	Uc_date[7] = us_temp_y + 0x30;

	us_temp_y  = us_temp_yr;
	us_temp_y  = us_temp_y % 100;
	us_temp_yr = us_temp_y;
			
	us_temp_y  = us_temp_y / 10;
	Uc_date[8] = us_temp_y + 0x30;

	us_temp_y  = us_temp_yr;
	us_temp_y  = us_temp_y % 10;
	Uc_date[9] = us_temp_y + 0x30;


  	uc_temp    = MONTH;
	uc_temp    = uc_temp / 10;
	Uc_date[3] = uc_temp + 0x30;

	uc_temp    = MONTH;
	uc_temp    = uc_temp % 10;		
	Uc_date[4] = uc_temp + 0x30;


 	uc_temp    = DOM;
	uc_temp    = uc_temp / 10;
	Uc_date[0] = uc_temp + 0x30;

	uc_temp    = DOM;
	uc_temp    = uc_temp % 10;		
	Uc_date[1] = uc_temp + 0x30;
//********************************************************************************************
	
	uc_temp    = SEC;
	uc_temp    = uc_temp / 10;
	Uc_real_time[6] = uc_temp + 0x30;

	uc_temp    = SEC;
	uc_temp    = uc_temp % 10;		
	Uc_real_time[7] = uc_temp + 0x30;


	uc_temp    = MIN;
	uc_temp    = uc_temp / 10;
	Uc_real_time[3] = uc_temp + 0x30;

	uc_temp    = MIN;
	uc_temp    = uc_temp % 10;		
	Uc_real_time[4] = uc_temp +0x30;


	uc_temp    = HOUR;
	uc_temp    = uc_temp / 10;
	Uc_real_time[0] = uc_temp +0x30;

	uc_temp    = HOUR;
	uc_temp    = uc_temp % 10;		
	Uc_real_time[1] = uc_temp +0x30;


}
