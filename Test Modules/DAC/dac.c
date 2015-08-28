#include "includes.h"

void DAC_init()
{
 PINSEL1 |= 0x00080000;
}


void DAC_write_val(U32 value)
{
 value &= 0x3ff;
 value <<= 6;

 DACR = value; 
}

























