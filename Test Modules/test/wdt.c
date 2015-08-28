#include"includes.h"

void wdt_init(void);
void wdt_ISR(void)__irq;

U8 wdt_timeout = 0; 


void wdt_init(void)
{
	VICVectAddr0 = (U32)&wdt_ISR;
  	VICVectCntl0 = 0x20 | 0;
  	VICIntEnable = 1 << 0;
	
	WDTC   = 0x01ffffff;
	WDMOD  = 0x03;
	WDFEED = 0xAA;
	WDFEED = 0x55;
}

void wdt_ISR(void)__irq
{
   	
    wdt_timeout = 1; 
	WDMOD &= ~0x04;
	VICVectAddr   = 0x00;
   	
}

void wdt_feed(U32 feed_val)
{
	WDTC   = feed_val;
	WDFEED = 0xAA;
	WDFEED = 0x55;
}


