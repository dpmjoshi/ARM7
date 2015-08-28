#include"includes.h"

void pwm5_init(void);
void pwm5_pulse_width(unsigned int, unsigned int);
void pwm_ISR(void)__irq;

void pwm5_init(void)
{
	VICVectAddr4 = (unsigned int)&pwm_ISR;
    VICVectCntl4 = 0x20 | 8;
    VICIntEnable = 1 << 8;	
	PWMPR 	 = 7500;	//Load prescaler

	PWMPCR   =  PWM5_OUT_EN;                    //0x00002000;//PWM channel 5 single edge control, output enabled
	PWMMCR   = (MR5_INT | MR0_INT | MR0_RST);   //0x00008003;//On match with timer reset the counter
	
	PWMMR0   = 40;				                //sets cycle rate of PWM
	PWMMR5   = 1;								//sets ON time of PWM
	PWMLER   = (MR5_LATCH_EN | MR0_LATCH_EN);   //0x00000021;//enable shadow latch for match 0 - 2 
	
	PWMTCR   = PWM_TC_RST;                      //0x00000002;//Reset counter and prescaler 
	PWMTCR   = (PWM_EN | PWM_TC_EN);	        //0x09  enable counter and PWM, release counter from reset
}


void pwm5_pulse_width(unsigned int mr0,unsigned int mr5)
{
	PWMTCR   = PWM_TC_RST;
	PWMMR0   = mr0;								//sets cycle rate of PWM
	PWMMR5   = mr5;								//sets ON time of PWM
	PWMLER   = (MR5_LATCH_EN | MR0_LATCH_EN);     
	PWMTCR   = (PWM_EN | PWM_TC_EN);
}

void pwm_ISR(void)__irq
{
 if(PWMIR & 0x01)
  {
   IO0SET |= PWM_OUT7;
   IO0SET |= PWM_OUT9;
   IO0SET |= PWM_OUT10;

   PWMIR = 0x01;
  }
 if(PWMIR & 0x200)
  {
   IO0CLR |= PWM_OUT7;
   IO0CLR |= PWM_OUT9;
   IO0CLR |= PWM_OUT10;
   PWMIR = 0x200;
  }
 VICVectAddr   = 0x00;

}

void pwm_enable(void)
{
	PWMTCR   = 9;
}

void pwm_disable(void)
{
	PWMTCR   = PWM_TC_RST;
  
}

void ms_delay(unsigned int w)
{
   T0TCR=0X01;
   T0PR=1000;
   while(T0TC<w)
      {
	  }			                                                    
   T0TC=0;
   T0TCR=0;
}


