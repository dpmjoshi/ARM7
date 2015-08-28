#include "includes.h"
 
U8 Uc_ascii_arr[10];
U8 Uc_dec_arr[20];

U8 hex_dec(U32 hex_val)
{
 U32 uc_hex_temp;
 U8  temp_cnt = 0;
 uc_hex_temp = hex_val;
 //--------------------------------------
 Uc_dec_arr[temp_cnt]  = uc_hex_temp/10000;	
 Uc_dec_arr[temp_cnt] += 0x30;
 uc_hex_temp           = uc_hex_temp%10000;
 temp_cnt++;
//--------------------------------------
 Uc_dec_arr[temp_cnt]  = uc_hex_temp/1000;	
 Uc_dec_arr[temp_cnt] += 0x30;
 uc_hex_temp           = uc_hex_temp%1000;
 temp_cnt++;
//--------------------------------------
 Uc_dec_arr[temp_cnt]  = uc_hex_temp/100;
 Uc_dec_arr[temp_cnt] += 0x30;
 uc_hex_temp           = uc_hex_temp%100;
 temp_cnt++;
//--------------------------------------
 Uc_dec_arr[temp_cnt]  = uc_hex_temp/10;
 Uc_dec_arr[temp_cnt] += 0x30;
 temp_cnt++;
//--------------------------------------
 uc_hex_temp           = uc_hex_temp%10;
 Uc_dec_arr[temp_cnt]  = uc_hex_temp + 0x30;
 temp_cnt++;
 Uc_dec_arr[temp_cnt]  = '\0';
//--------------------------------------
 return &Uc_dec_arr[0];
}

void hex_ascii(U32 hex_val)
{
 U32 uc_hex_temp = 0;
 U8  temp_cnt    = 0;
 U32 uc_hex_mask = 0xf0000000;
 for(temp_cnt = 0; temp_cnt < 8; temp_cnt++)
 {
  uc_hex_temp = hex_val;
  uc_hex_temp = (uc_hex_temp & uc_hex_mask);
  uc_hex_temp = uc_hex_temp >> (28-(4*temp_cnt));
   
  if(uc_hex_temp <= 9)
  {
   uc_hex_temp += 0x30; 
  }
  else
  {
   uc_hex_temp += 0x37;
  }
  Uc_ascii_arr[temp_cnt] = uc_hex_temp;
  uc_hex_mask >>= (4*temp_cnt);
 }
 Uc_ascii_arr[temp_cnt] = '\0';
 //return &Uc_ascii_arr[0];
}






