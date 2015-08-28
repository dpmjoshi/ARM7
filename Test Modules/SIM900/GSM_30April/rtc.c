/*
 *File name: <rtc.c>
 *Description:
 *It contains a function for RTC initialization.
 *This RTC value is used as a time stamp in the system.
 */
#include "includes.h"

#define		CLK_EN						0x11

void rtc_init(void);
void rtc_isr(void) __irq;
void set_alarm(U8 , U8 , U8 );
void disp_time(void);

U8 Uc_time_sec = 0;
U8 Uc_alarm = 0;
U8 time[10] = "00:00:00";
U8 date[12];

/*
 *Function name:RTC_init
 *Description: 
 *This function is used to initialize the RTC module. 
 *The PREINT and PREFRAC registers are fed with the calculated value of the prescaler, that depends on the pclk (15 Mhz in our case).
 *The CCR  register is used to enable the clock. HOUR, MIN and SEC are the timer registers which a re all initialized to zero.                           
 */
void rtc_init(void)
{
	YEAR  = 2013;
	DOM   = 25;
	MONTH = 4;		
}


void rtc_isr(void) __irq
{
	if(ILR & 0x01)
	{
		Uc_time_sec = 1;
		ILR = 1;
	
	}
	if(ILR & 0x02)
	{
	 	Uc_alarm = 1;
		ILR = 2;
	
	}
	VICVectAddr   = 0x00;
}


/**********************************************************************************/
/* Function Name: rtc_get_date()												  */
/* Arguments	: U8 *date_arr													  */
/*				  																  */
/* Return Types	: NONE															  */
/* Description	: 																  */
/**********************************************************************************/						  
void rtc_get_date(U8 *date_arr)
{ 
	U8 uc_year[6];
	U8 uc_day[4];
	U8 uc_month[4];
	U8 seprator[2] = "/";
	U8 uc_temp;
	
	uc_temp = LIB_hex_dec(uc_day, DOM);			// this fuction copies the day, month and year into the date_arr
	LIB_str_copy(uc_day, date_arr, uc_temp);	// if month & date are single digits then only those digits will be copied 
	date_arr += uc_temp;						// there will be no trailling Zeros. like if date is 4th Nov then date will be displayed as:
												// 4/11/2013. for 23rd may : 23/5/2013	
	LIB_str_copy(seprator, date_arr, 1); 		// adding date seperator 
	date_arr++;


	uc_temp = LIB_hex_dec(uc_month, MONTH);
	LIB_str_copy(uc_month, date_arr, uc_temp);
	date_arr += uc_temp;

	LIB_str_copy(seprator, date_arr, 1); 	
	date_arr++;

	
	uc_temp = LIB_hex_dec(uc_year, YEAR);
	LIB_str_copy(uc_year, date_arr, uc_temp);
	date_arr += (uc_temp + 1);

	*date_arr = '\0';
}

/**********************************************************************************/
/* Function Name: rtc_get_time()												  */
/* Arguments	: U8 *date_arr													  */
/*				  																  */
/* Return Types	: NONE															  */
/* Description	: 																  */
/**********************************************************************************/						  


void rtc_get_time(U8 *time_arr)
{
	U8 uc_temp = 0;
	
	uc_temp  = SEC;
	uc_temp  = uc_temp / 10;
	time[6]  = uc_temp + 0x30;

	uc_temp  = SEC;
	uc_temp  = uc_temp % 10;		
	time[7]  = uc_temp + 0x30;


	uc_temp  = MIN;
	uc_temp  = uc_temp / 10;
	time[3]  = uc_temp + 0x30;

	uc_temp  = MIN;
	uc_temp  = uc_temp % 10;		
	time[4]  = uc_temp + 0x30;


	uc_temp  = HOUR;
	uc_temp  = uc_temp / 10;
	time[0]  = uc_temp + 0x30;

	uc_temp  = HOUR;
	uc_temp  = uc_temp % 10;		
	time[1]  = uc_temp + 0x30;

}


void set_alarm(U8 al_hr, U8 al_min, U8 al_sec)
{
	U8 temp;
	AMR = 0XF8;
	temp = SEC + al_sec;
	if(temp <60)
	{
		ALSEC = temp;
		temp = 0;
	}
	else
	{
		ALSEC = temp - 60;
		temp = 1;
	}
	
	temp = temp + MIN + al_min;
	if(temp <60)
	{
		ALMIN = temp;
		temp = 0;
	}
	else
	{
		ALMIN = temp - 60;
		temp = 1;
	}
	
	temp = temp + HOUR + al_hr;
	if(temp <24)
	{
		ALHOUR = temp;
	}
	else
	{
		ALHOUR = temp - 24;
	}
}

