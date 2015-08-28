#include "includes.h"

#define AD_CR_SEL0          (0x00000001)                  // Select channel 0
#define AD_CR_SEL1          (0x00000002)                  // Select channel 1
#define AD_CR_SEL2          (0x00000004)                  // Select channel 2
#define AD_CR_SEL3          (0x00000008)                  // Select channel 3
#define AD_CR_SEL4          (0x00000010)                  // Select channel 4
#define AD_CR_SEL5          (0x00000020)                  // Select channel 5
#define AD_CR_SEL6          (0x00000040)                  // Select channel 6
#define AD_CR_SEL7          (0x00000080)                  // Select channel 7
#define AD_CR_SELMASK       (0x000000ff)
#define AD_CR_BURST         (0x00010000)
#define AD_CR_CLKS10        (0x00000000)                  // Use 10-bit conversions
#define AD_CR_PDN           (0x00200000)                  // Whether AD is operational (1) or powered-down (0)
#define AD_CR_START_NONE    (0x00000000)                  // No start (used when clearing PDN to 0)
#define AD_CR_START_NOW     (0x01000000)                  // Start conversion now
#define AD_CR_START_MASK    (0x07000000) 

//***********************************
//	adc_init
//***********************************
void adc_init()
{
	PINSEL1 |= 0X15000000;		//AD0.1
	AD0CR    = 0X00210A0e;
	
}
//***********************************
//	adc0.1_getval
//***********************************
U32 adc1_getval()
{
  U32 ui_adc1_value; 
  AD0CR &= ~(AD_CR_START_MASK | AD_CR_SELMASK);// Deselects all channels and stops all conversions
  AD0CR |=  (AD_CR_START_NONE | AD_CR_SEL1);   // Select channel 3    
  AD0CR |=   AD_CR_START_NOW;// Manually start conversions (rather than waiting on an external input)
  do
  {
    ui_adc1_value = AD0DR1;
  } 
 while((ui_adc1_value & 0x80000000) );//wait for the conversion done bit to be 1
 ui_adc1_value = ((ui_adc1_value >>6)& 0x3ff );//
 return ui_adc1_value;
}
//***********************************
//	adc0.2_getval
//***********************************
U32 adc2_getval()
{
  U32 ui_adc2_value; 
  AD0CR &= ~(AD_CR_START_MASK | AD_CR_SELMASK);// Deselects all channels and stops all conversions
  AD0CR |=  (AD_CR_START_NONE | AD_CR_SEL2);   // Select channel 3    
  AD0CR |=   AD_CR_START_NOW;// Manually start conversions (rather than waiting on an external input)
  do
  {
    ui_adc2_value = AD0DR2;
  } 
 while((ui_adc2_value & 0x80000000) );//wait for the conversion done bit to be 1
 ui_adc2_value = ((ui_adc2_value >>6)& 0x3ff );//
 return ui_adc2_value;
}
//***********************************
//	adc0.3_getval
//***********************************
U32 adc3_getval()
{
  U32 ui_adc3_value; 
  AD0CR &= ~(AD_CR_START_MASK | AD_CR_SELMASK);// Deselects all channels and stops all conversions
  AD0CR |=  (AD_CR_START_NONE | AD_CR_SEL3);   // Select channel 3    
  AD0CR |=   AD_CR_START_NOW;// Manually start conversions (rather than waiting on an external input)
  do
  {
    ui_adc3_value = AD0DR3;
  } 
 while((ui_adc3_value & 0x80000000) );//wait for the conversion done bit to be 1
 ui_adc3_value = ((ui_adc3_value >>6)& 0x3ff );//
 return ui_adc3_value;
}

void adc0_1_soc()
{
	AD0CR    = 0X01210A02;
}

void adc0_1_eoc()
{
	AD0CR    = 0X00210A02;
}

void adc0_3_soc()
{
	AD0CR    = 0X01210A08;
}

void adc0_3_eoc()
{
	AD0CR    = 0X00210A08;
}


