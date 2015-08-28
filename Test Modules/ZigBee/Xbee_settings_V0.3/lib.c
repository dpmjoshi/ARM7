#include"includes.h"

/**********************************
 *Function name: str_copy(U8* source_str, U8* dest_str, U8 no_bytes)
 *Description  : returns 1 if i/p src string matches with the cmp string 
 
 *Input 	   :   U8* source_str, U8* dest_str, U8 no_bytes			 						
 *Output 	   :   NONE
 *Return Value :   NONE 
***********************************/
void str_copy(U8* source_str, U8* dest_str, U8 delim)
{
	U8 uc_count = 0;
	for(uc_count = 0; *source_str != delim; uc_count++)
	{
		*dest_str = *source_str;
		dest_str++;
		source_str++;
	}
	*dest_str = '\0';		
}
/**********************************
 *Function name: str_cmp(U8 *src, U8 *cmp)
 *Description  : returns 1 if i/p src string matches with the cmp string 
 
 *Input 	   :   U8 *src, U8 *cmp				 						
 *Output 	   :   None
 *Return Value :   0/1 
***********************************/
U8 str_cmp(U8 *src,U8 *cmp)
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

void hex_dec(U8 *dec_arr, U8 hex_val)
{
 *dec_arr  = hex_val/10;
 *dec_arr += 0x30;
 hex_val     = hex_val%10;
 dec_arr++;
 *dec_arr  = hex_val + 0x30;
}


void hex_dec1(U8 *dec_arr, U32 hex_val)
{
 *dec_arr  = hex_val/1000;
 *dec_arr += 0x30;
 hex_val     = hex_val%1000;
 dec_arr++;
 *dec_arr  = hex_val/100;
 *dec_arr += 0x30;
 hex_val     = hex_val%100;
 dec_arr++;
 *dec_arr  = hex_val/10;
 *dec_arr += 0x30;
 hex_val     = hex_val%10;
 dec_arr++;
 *dec_arr  = hex_val + 0x30;
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










