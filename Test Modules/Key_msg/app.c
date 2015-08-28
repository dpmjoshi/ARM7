#include "includes.h"
#define NO_RECV_BYTE     22
#define	NO_OF_SAMPLE     05
#define COOLER_ON        1<<19
#define HEATER_ON        1<<20
#define	SSR_ON			 1<<21
#define	BUZZER			 1<<22
//**********************************************//
void irq_init(void);
void uart0_ISR(void)__irq;
void uart1_ISR(void)__irq;
void default_page(void);
void get_user_time(void);
void temp_ctrl(void);
void adc_val_conv(U32, U32, U32, U32, U32, U8);

void user_time_conv(void);
void user_temp_conv(void);


//**********************************************//
U8  space[400]             = {"                                                                                                                                                                                                                     "};
U8  Uc_cr_lf[3]            = {"\n\r"};
U8  Uc_temp_low_lcd[5]	  = {"Low "};
U8  Uc_temp_high_lcd[5]	  = {"High"};

U8  Uc_dec_arr[11]         = {"00000"};
U8  Uc_set_user_time[10]   = {"00:00:00"};
U8  Uc_set_temp[7]         = {"000"};

U8  ascii_arr[100];
U8  node_addr_arr[2];
U8  node_ascii_arr[5];
U8  Uc_recv_data[100];

U8  Uc_byte_count = 0;
U8  frame_chk_cnt = 0;
U8  Uc_temp_high  = 0; 
U8  Uc_adc_time_out_flag = 0;
U32	Ui_temp_set_val = 0;
U8  Uc_user_dwn_hr  = 0;
U8  Uc_user_dwn_min = 0;
U8  Uc_user_dwn_sec = 0;


struct frame_data
{
 unsigned char  api_identifier;
 unsigned char  node_addr[5];
 unsigned char  rssi_val;
 unsigned short no_of_samples;
 unsigned char  ch_indicator;
 unsigned int   ch0_s1; 
 unsigned int   ch0_s2;
 unsigned int   ch0_s3;
 unsigned int   ch0_s4;
 unsigned int   ch0_s5;
 unsigned int   ch1_s1;
}node_01;
					   
//***************************************************
//Initialisation of ISR
//***************************************************

void irq_init(void)
{
  
  VICVectAddr0 = (U32)&uart0_ISR;
  VICVectCntl0 = 0x20 | 6;
  VICIntEnable = 1 << 6;	
  U0IER=0x1; 

  VICVectAddr1 = (U32)&uart1_ISR;
  VICVectCntl1 = 0x20 | 7;
  VICIntEnable = 1 << 7;	
  U1IER=0x1;

}
//***************************************************
// ISR for UART0
//***************************************************
void uart0_ISR(void)__irq
{
    
   VICVectAddr   = 0x00;
}  
//***************************************************
// ISR for UART1
//***************************************************

void uart1_ISR(void)__irq
{
   Uc_recv_data[Uc_byte_count] = U1RBR;
   if(Uc_recv_data[Uc_byte_count] == 0x7E)
   {
	Uc_byte_count = 0;
   }
   Uc_byte_count++;
   
   VICVectAddr = 0x00;
}
//***************************************************
// default page to be displayed in SYSTEM mode
//***************************************************
void default_page(void)
{
  U8 lcd_data_temp[10]     = {"TEMP:"};
  U8 lcd_data_pres[10]     = {"PRES:"};
  U8 lcd_data_rpm[10]      = {"RPM :"};
  U8 lcd_data_temp_unit[5] = {" C"};
  U8 lcd_data_pres_unit[5] = {"PSI"};

  clrscr();

  lcd_data_temp_unit[0] = 0xdf;		  // hex value for degree
  
  lcd_line1_disp(&lcd_data_temp[0],0);
  lcd_line1_disp(&lcd_data_temp_unit[0],17);
  lcd_line1_disp(&Uc_set_temp[0],12);
  lcd_line2_disp(&lcd_data_pres[0],0);
  lcd_line2_disp(&lcd_data_pres_unit[0],17);
  lcd_line3_disp(&lcd_data_rpm[0],0);
}
//***************************************************
// function to get time duration from user
//***************************************************
void get_user_time(void)
{
  U8 uc_lcd_data_user_time[30] = {"Enter Time: "};
  U8 uc_lcd_data_user_temp[30] = {"Enter Temp: "};
  U8 sc_set_time_count = 0;
  U8 uc_set_temp_count = 0;

  clrscr();
  lcd_line1_disp(&uc_lcd_data_user_time[0],0);
  lcd_line1_disp(&Uc_set_user_time[0],12);
 
  while(sc_set_time_count < 8)					 //uc_set_time_count < 9
  {
  	wdt_feed(0x03ffffff);
	Uc_key_temp = get_key(1);
	pwm5_pulse_width(5000, 100);
	//pwm_enable();

	if((Uc_key_temp <= '9')&(Uc_key_temp >= '0'))
	{
		if(sc_set_time_count == 0)
		{
			
			if(Uc_key_temp < '3')
			{
				Uc_set_user_time[sc_set_time_count] = Uc_key_temp;
				sc_set_time_count += 1;
			}
		}
		else if(sc_set_time_count == 1)
		{
		   if((Uc_set_user_time[0] - 0x30) == 2)
		   {
			if(Uc_key_temp < '4')
			{
				Uc_set_user_time[sc_set_time_count] = Uc_key_temp;
				sc_set_time_count += 2;
			}
		   }
		   else
		   {
		   		Uc_set_user_time[sc_set_time_count] = Uc_key_temp;
				sc_set_time_count += 2;
		   }
		}
		else if(sc_set_time_count == 3)
		{
			
		  	if(Uc_key_temp < '6')
			{
				Uc_set_user_time[sc_set_time_count] = Uc_key_temp;
				sc_set_time_count += 1;
			}
		}
		else if(sc_set_time_count == 4)
		{
		 	
			Uc_set_user_time[sc_set_time_count] = Uc_key_temp;
			sc_set_time_count += 2;
			
		}
		else if(sc_set_time_count == 6)
		{
		  	
			if(Uc_key_temp < '6')
			{
				Uc_set_user_time[sc_set_time_count] = Uc_key_temp;
				sc_set_time_count += 1;
			}
		}
		else if(sc_set_time_count == 7)
		{
		  	
			if(Uc_key_temp < 'A')
			{
				Uc_set_user_time[sc_set_time_count] = Uc_key_temp;
				sc_set_time_count += 1;
			}
		}

	}

	if(Uc_key_temp == 'A')
	{	  	
		  lcd_line2_disp(&uc_lcd_data_user_temp[0],0);
		  lcd_line2_disp(&Uc_set_temp[0],12);
		  sc_set_time_count = 8;
		  uc_set_temp_count	= 3;
	}
	//*********************************************//
  
  	if(sc_set_time_count == 0)
	{
		lcd_line4_disp("Range 0-2",11);
	}
	if(sc_set_time_count == 1)
	{
		lcd_line4_disp("Range 0-3",11);
	}
	if(sc_set_time_count == 3)
	{
		lcd_line4_disp("Range 0-5",11);
	}
	if(sc_set_time_count == 4)
	{
		lcd_line4_disp("Range 0-9",11);
	}
	if(sc_set_time_count == 6)
	{
		lcd_line4_disp("Range 0-5",11);
	}
	if(sc_set_time_count == 7)
	{
		lcd_line4_disp("Range 0-9",11);
	}
	//*********************************************//
	lcd_line1_ch_disp(' ',((sc_set_time_count+12)-1));
	//Uc_set_user_time[sc_set_time_count + 1] = '\0';
	key_delay(250);		// do not remove it
	lcd_line1_disp(&Uc_set_user_time[0],12);
	pwm_disable();
  }
  

//---------------------------------------------------------------------------------
//------------------------------get temp from User---------------------------------
//---------------------------------------------------------------------------------
  lcd_line2_disp(&uc_lcd_data_user_temp[0],0);
  while(uc_set_temp_count < 3)
  {
  	wdt_feed(0x03ffffff);
	Uc_key_temp = get_key(1);
	
	pwm5_pulse_width(5000, 100);

	if((Uc_key_temp <= '9')&(Uc_key_temp >= '0'))
	{
		 if(uc_set_temp_count == 0)
		 {
		 	if(Uc_key_temp <= '3')
			{
				Uc_set_temp[uc_set_temp_count] =  Uc_key_temp;
		 		uc_set_temp_count++; 

			}
		 }
		 else 
		 {
		 		Uc_set_temp[uc_set_temp_count] =  Uc_key_temp;
		 		uc_set_temp_count++; 

		 }

	}
	if(Uc_key_temp == 'A')
	{
		 uc_set_temp_count = 3;
	}
	lcd_line2_disp(&Uc_set_temp[0],12);
	key_delay(250);		// do not remove it
	//*************range of no*****************//
	if(uc_set_temp_count == 0)
	{
		lcd_line4_disp("Range 0-3",11);
	}
	if(uc_set_temp_count == 1)
	{
		lcd_line4_disp("Range 0-9",11);
	}
	if(uc_set_temp_count == 2)
	{
		lcd_line4_disp("Range 0-9",11);
	}
	//****************************************//
	pwm_disable();
  }	
  
  lcd_line4_disp("Press Start",9);															 
  while((Uc_key_temp = get_key(1)) != 'D');
  Uc_alrm = 3;
  user_time_conv();	  // to convert the time entered by USER
  user_temp_conv();	  // to convert the temp entered by USER

  clrscr();
  default_page();    // Displaying default PAGE while leaving from USER MODE.
}
//***************************************************
// function to convert user time in to hex
//***************************************************

void user_time_conv(void)
{	
	U8 uc_user_hr  = 0;
	U8 uc_user_min = 0;
	U8 uc_user_sec = 0;

	uc_user_hr   = ((Uc_set_user_time[0] - 0x30) * 10); 	
	uc_user_hr	+= (Uc_set_user_time[1] - 0x30);	
	uc_user_min  = ((Uc_set_user_time[3] - 0x30) * 10); 
	uc_user_min	+= (Uc_set_user_time[4] - 0x30);
	uc_user_sec  = ((Uc_set_user_time[6] - 0x30) * 10); 
	uc_user_sec	+= (Uc_set_user_time[7] - 0x30);

	Uc_user_dwn_hr  = uc_user_hr;
	Uc_user_dwn_min = uc_user_min;
	Uc_user_dwn_sec = uc_user_sec;
	
	set_alarm(uc_user_hr,uc_user_min,uc_user_sec);
}
//**********************************************************************************//
// Function Name: function to convert User Temp in to hex							//
// Arguments	: NONE																//
// Return Types	: NONE																//
// Description	: Converts Ui_temp_set_val to HEX and the conversion is placed into	//
//				  Uc_set_temp[] array												//
//**********************************************************************************//
void user_temp_conv(void)
{	
	Ui_temp_set_val	  =  0;
	Ui_temp_set_val   = ((Uc_set_temp[0] - 0x30) * 1000); 	
	Ui_temp_set_val  += ((Uc_set_temp[1] - 0x30) *  100);	
	Ui_temp_set_val  += ((Uc_set_temp[2] - 0x30) *   10); 
	
}
//**********************************************************************************//
// Function Name: function to control SSR and SOLENOID								//
// Arguments	: NONE																//
// Return Types	: NONE																//
// Description	: Depending on Uc_temp_high	 HEATER and COOLER are controlled		//
//**********************************************************************************//
void temp_ctrl(void)
{
	if(Uc_temp_high == 1)
	 {
		IO0SET = COOLER_ON;	
		IO0CLR = HEATER_ON; 
		IO0CLR = SSR_ON;
	 }
	else
	 {
		IO0SET = HEATER_ON;	
		IO0CLR = COOLER_ON;
		IO0SET = SSR_ON;
	 }
}
//**********************************************************************************//
// Description : function to convert ADC hex value into DEC						    //
// Argument    : U32 (5 samples)												    //
// Return Type : NONE															    //
//**********************************************************************************//
void adc_val_conv(U32 sample1, U32 sample2, U32 sample3, U32 sample4, U32 sample5, U8 condition)
{
 U8 a = 0;
 U32 adc_temp;
 U32 adc_val;
//*****************************************
// Taking AVG of 3 samples
//*****************************************
 adc_val = (sample1 + sample2 + sample3 + sample4 + sample5)/5;
 if(condition == 1)
 {
 	if(adc_val < 4)
 	{
 		lcd_line3_disp("Sensor Open", 9);
	 }
 	else
 	{
	 	lcd_line3_disp("           ", 9);
	}
 }
//*****************************************
// calibrating ADC hex data
//*****************************************
 adc_val *= 3300;	
 adc_val >>= 10;


 if(condition == 0)
 {
  	adc_val *= 2;
//	adc_val /= 700;
 }

 if(condition == 1)
 {
 	if(adc_val > 10)
 	{
 		adc_val -= 10;
 	}
 }
 
 adc_temp = adc_val;
//*****************************************
// Temp Control
//*****************************************
if(condition == 1)
{
 if( adc_val  > Ui_temp_set_val)
   {
   		Uc_temp_high = 1;
   }
 else
   {
   		Uc_temp_high = 0;
   }

}
//*****************************************
// HEX to DEC conversion 
//*****************************************
 Uc_dec_arr[a]  = adc_temp/10000;	
 Uc_dec_arr[a] += 0x30;
 adc_temp       = adc_temp%10000;
 a++;
//--------------------------------------
 Uc_dec_arr[a]  = adc_temp/1000;	
 Uc_dec_arr[a] += 0x30;
 adc_temp       = adc_temp%1000;
 a++;
//--------------------------------------
 Uc_dec_arr[a]  = adc_temp/100;
 Uc_dec_arr[a] += 0x30;
 adc_temp       = adc_temp%100;
 a++;
//--------------------------------------
 Uc_dec_arr[a]  = adc_temp/10;
 Uc_dec_arr[a] += 0x30;
 adc_temp       = adc_temp%10;
 a++;
 Uc_dec_arr[a]  = adc_temp + 0x30;

}
 
  
