#include "includes.h"

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


U32 LIB_ascii_hex(U8 *ascii_arr)
{
 U8  uc_cnt = 0;
 U8  uc_str_cnt;
 U32 ui_mul_fctr = 0;
 U32 ui_hex_val  = 0;

 for(uc_str_cnt = 0; *ascii_arr != '\0'; uc_str_cnt++);

 for(uc_cnt = 0; uc_cnt <= uc_str_cnt; uc_cnt++)
 {
  ui_mul_fctr *= 10;
 }
 
 for(uc_cnt = 0; *ascii_arr != '\0'; uc_cnt++)
 {
  ui_hex_val += (*ascii_arr * ui_mul_fctr);
  ascii_arr++;
  ui_mul_fctr /= 10; 
 }
 return ui_hex_val;

}


void str_copy(U8 *str_input, U8 *str_output)
{
 U8 uc_cnt = 0;

 for(uc_cnt = 0; *str_input != '\0'; uc_cnt++)
 {
  *str_output = *str_input;
  str_output++;
  str_input++; 
 }
}
