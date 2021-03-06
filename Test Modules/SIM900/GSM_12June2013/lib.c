#include"includes.h"

/*******  MATH  Functions   **********/
U32 LIB_hex_dec(U8*, U32);
void LIB_hex_ascii(U8*, U8*);

void LIB_str_copy(U8*, U8*, U8);
U8   LIB_str_cmp(U8*, U8*);
void LIB_str_conc(U8*, U8*, U8*);
void LIB_str_conc1(U8*, U8*, U8*);
void LIB_frmt_arr(U8*, U32);
U8   LIB_frag_arr(U8*, U32*, U8);
	
/**********************************************************************************/
/*****************************  MATH  Functions   *********************************/
/**********************************************************************************/
/* Function Name: LIB_hex_dec(U8*, U32)											  */
/* Arguments	: U8* Pointer to the array, which is used to store final result	  */
/*                U32 hex_val is the HEX input to be converted into dec.		  */ 
/* Return Types	: 															      */
/* Description	: Converts the Hex value to dec and ultimate to corresponding 	  */
/* 				  ASCII. It can convert any no from 0- 0xffff ffff				  */
/**********************************************************************************/

U32 LIB_hex_dec(U8 *dec_arr, U32 hex_val)
{
	U8  uc_cnt = 0;
	U32 ui_div_fctr = 1;		  // very important to initiate it at 1.
	U32 ui_hex_val  = 0;
 
	ui_hex_val = hex_val;
 	while(ui_hex_val > 0)
 	{
  		ui_hex_val /= 10;
  		++uc_cnt;
  		if(ui_hex_val == 0)
  		continue; 
  		ui_div_fctr *= 10;
 	}  
 	while(ui_div_fctr)
	{
  		*dec_arr  = hex_val / ui_div_fctr;
  		*dec_arr += 0x30; 
  		dec_arr++;
  		hex_val  %= ui_div_fctr;
  		ui_div_fctr /= 10;
 	}
 	*dec_arr = '\0';
 	return uc_cnt;   // returning no of bytes in the dec array, this will be usefull in refreshing LCD or any display module.
}
	 
/**********************************************************************************/
/* Function Name: LIB_hex_ascii()												  */
/* Arguments	: U8  *hex_val 													  */
/*				  U8  *ascii_arr 												  */
/* Return Types	: NONE															  */
/* Description	: 																  */
/**********************************************************************************/

void LIB_hex_ascii(U8 *hex_val, U8 *ascii_arr)
{
	U32 uc_temp = 0;
	while(*hex_val)									// hex_val is the hex value array terminated by 0. 
	{
		uc_temp = *hex_val;
		*ascii_arr = ((uc_temp >> 4) + 0x30);				// Higer nibble of the hex val 
  		if(*ascii_arr > 0x39)
  		{
   			*ascii_arr += 7;
  		}
		ascii_arr++;
		*ascii_arr = ((*hex_val & 0x0f) + 0x30);			// Lower nibble of the hex val
  		if(*ascii_arr > 0x39)
  		{
   			*ascii_arr += 7;
  		}
  		ascii_arr++;
   		hex_val++;
 	}
}
/**********************************************************************************/
/* Function Name: LIB_dec_hex()													  */
/* Arguments	: U8 *dec_arr													  */
/*				  																  */
/* Return Types	: U32 ui_hex_val												  */
/* Description	: 																  */
/**********************************************************************************/

U32 LIB_dec_hex(U8 *dec_arr)
{
	U32 ui_mul_fctr = 1;
	U32 ui_hex_val = 0;
	U8  uc_strlen = 0;
	
	uc_strlen   = LIB_strlen(dec_arr);	  // Finding string length in order to get end pointer of string 
	dec_arr += (uc_strlen - 1);		      // adding strlen - 1 in the starting pointer 
	while(uc_strlen)
	{
		ui_hex_val += (( *dec_arr - 0x30 )	* ui_mul_fctr);
		ui_mul_fctr *= 10; 
		dec_arr--;
		uc_strlen--;
	}
	return ui_hex_val;
}

/**********************************************************************************/
/***************************  STRING  Functions   *********************************/
/**********************************************************************************/
/* Function name:  LIB_str_copy(U8* source_str, U8* dest_str, U8 no_bytes)		  */
/* Description  :  returns 1 if i/p src string matches with the cmp string 		  */
/* 																				  */
/* Input 	    :  U8* source_str, U8* dest_str, U8 no_bytes			 		  */	 			
/* Output 	    :  NONE															  */
/* Return Value :  NONE 														  */
/**********************************************************************************/

void LIB_str_copy(U8 *source_str, U8 *dest_str, U8 no_bytes)
{
	U8 uc_count = 0;
	for(uc_count = 0; uc_count < no_bytes; uc_count++)
	{
		*dest_str = *source_str;
		dest_str++;
		source_str++;
	}		
}
/**********************************************************************************
 *Function name: LIB_str_cmp(U8 *src, U8 *cmp)
 *Description  : returns 1 if i/p src string matches with the cmp string 
 
 *Input 	   :   U8 *src, U8 *cmp				 						
 *Output 	   :   None
 *Return Value :   0/1 
***********************************************************************************/

U8 LIB_str_cmp(U8 *src,U8 *cmp)
{
  U8 str_temp;
  for(str_temp = 0; *cmp!='\0'; str_temp++)
    {
     if(*src == *cmp)
	  {
	   src++;
	   cmp++;
	   if(*cmp == '\0')
	   return 1;
	  }
     else
	   return 0;
	} 
}
/**********************************************************************************/
/* Function Name: LIB_str_conc()												  */
/* Arguments	: U32   hex_val 												  */
/*				  U8  *ascii_arr (addresses are of fragmented arr are saved)	  */
/* Return Types	: NONE															  */
/* Description	: Concatinates two strings & saves it in third string 			  */
/**********************************************************************************/

void LIB_str_conc(U8 *str1, U8 *str2, U8 *str_conc)
{
 U8 *temp;
 temp = str_conc;
 while(*str1)
 {
  *str_conc = *str1;
  str1++;
  str_conc++;
 }
 while(*str2)
 {
  *str_conc = *str2;
  str2++;
  str_conc++;
 }
 *str_conc = '\0';
}

/**********************************************************************************/
/* Function Name: LIB_str_conc1()												  */
/* Arguments	:  												 				  */
/*				  																  */
/* Return Types	: NONE															  */
/* Description	: Concatinates two strings & saves it in third string 			  */
/**********************************************************************************/

void LIB_str_conc1(U8 *str1, U8 *str2, U8 *str_conc)
{
 U8 *temp;
 temp = str_conc;
 while(*str1 != '$')
 {
  *str_conc = *str1;
  str1++;
  str_conc++;
 }
 while(*str2)
 {
  *str_conc = *str2;
  str2++;
  str_conc++;
 }
 *str_conc = '\0';
}
 

/**********************************************************************************/
/* Function Name: LIB_strlen()												  */
/* Arguments	: NONE															  */
/* Return Types	: NONE															  */
/* Description	: calculates the byte 											  */
/**********************************************************************************/

U16 LIB_strlen(U8 *str)
{
 U16 uc_str_cnt = 0;
 while(*str)
 {
  uc_str_cnt++;
  str++;
 }
 return uc_str_cnt;
}

/**********************************************************************************/
/* Function Name: LIB_frmt_arr()												  */
/* Arguments	: U8 *input_arr													  */
/*				  U32 frmt_bytes												  */
/* Return Types	: NONE															  */
/* Description	: 																  */
/**********************************************************************************/

void LIB_frmt_arr(U8 *input_arr, U32 frmt_bytes)
{
 while(frmt_bytes)
 {
  *input_arr = '\0';
  input_arr++;
  frmt_bytes--;
 }
}

/**********************************************************************************/
/* Function Name: LIB_frag_arr()												  */
/* Arguments	: U8   *input_arr 												  */
/*				  U32  *add_arr	(addresses are of fragmented arr are saved)		  */
/*				  U8   delim (delimeter used for fragmenting array)			      */
/* Return Types	: NONE															  */
/* Description	: 																  */
/**********************************************************************************/

U8 LIB_frag_arr(U8 *input_arr, U32 *add_arr, U8 delim)
{
  U8  uc_delim_cnt = 0;
  
  *add_arr = (U32)input_arr;
  add_arr++;

  while(*input_arr != '\0')
  {
   if(*input_arr == delim)
   {
	uc_delim_cnt++;
	*add_arr = (U32)(input_arr + 2); 
	add_arr++;
   }
   input_arr++;
  }
  
 return uc_delim_cnt;
}

