#include "includes.h"


void dac_val(U16 val)
{
	DACR = ((val & 0x3ff) >> 6);
}