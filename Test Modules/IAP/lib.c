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