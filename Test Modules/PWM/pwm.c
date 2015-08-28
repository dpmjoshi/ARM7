#include"includes.h"

void pwm5_init(void);
void pwm5_pulse_width(U8, U8);
void pwm_enable(void);
void pwm_disable(void);
//**********************************************************************************//
// Function Name: pwm5_init					   										//
// Arguments	: NONE																//
// Return Types	: NONE																//
// Description	: PWM channel 5, Single edge control,On match reset PWMTC .			//
//                																	//
//**********************************************************************************//
void pwm5_sngl_init(void)
{
	PINSEL1 |= 0x00000400;			//Enable pin 0.7   as PWM2 
	PWMPR 	 = 15000;	//Load prescaler

	PWMPCR   = 0x00002000;				//PWM channel 5 single edge control, output enabled
	PWMMCR   = 0x00000002;				//On match with timer reset the counter
	
	PWMMR0   = 1000;				//set cycle rate to sixteen ticks
	PWMMR5   = 100;				//set rising edge of PWM2 to 2 ticks
	PWMLER   = 0x00000021;				//enable shadow latch for match 0 - 2 
	
	PWMTCR   = 0x00000002;				//Reset counter and prescaler 
	PWMTCR   = 0x00000008;	//0x09  enable counter and PWM, release counter from reset
}
//**********************************************************************************//
// Function Name: pwm5_init					   										//
// Arguments	: NONE																//
// Return Types	: NONE																//
// Description	: PWM channel 5, Single edge control,On match reset PWMTC .			//
//                																	//
//**********************************************************************************//
void pwm5_dbl_init(void)
{
	PINSEL1 |= 0x00000400;			//Enable pin 0.7   as PWM2 
	PWMPR 	 = 15000;	//Load prescaler

	PWMPCR   = 0x00002020;				//PWM channel 5 single edge control, output enabled
	PWMMCR   = 0x00000002;				//On match with timer reset the counter
	
	PWMMR0   = 1000;				//set cycle rate to sixteen ticks
	PWMMR5   = 100;				//set rising edge of PWM2 to 2 ticks
	PWMLER   = 0x00000021;				//enable shadow latch for match 0 - 2 
	
	PWMTCR   = 0x00000002;				//Reset counter and prescaler 
	PWMTCR   = 0x00000008;	//0x09  enable counter and PWM, release counter from reset
}


//**********************************************************************************//
// Function Name: pwm5_pulse_width			   										//
// Arguments	: mr0, mr5															//
// Return Types	: NONE																//
// Description	: mr0 signifies to cycle length and mr5 corresponds to ON time		//
//				  pulse width														//
//**********************************************************************************//
void pwm5_sngl_pulse_width(U8 mr0, U8 mr5)
{
	
	PWMMR0   = mr0;				//set cycle rate to sixteen ticks
	PWMMR5   = mr5;				//set rising edge of PWM2 to 2 ticks
	PWMLER   = 0x00000021;
	PWMTCR   = 2;
	PWMTCR   = 9;
	
}
//**********************************************************************************//
// Function Name: pwm5_pulse_width			   										//
// Arguments	: mr0, mr5															//
// Return Types	: NONE																//
// Description	: mr0 signifies to cycle length and mr5 corresponds to ON time		//
//				  pulse width														//
//**********************************************************************************//
void pwm5_dbl_pulse_width(U8 mr0, U8 mr5, U8 mr4)
{
	
	PWMMR0   = mr0;				//set cycle rate to sixteen ticks
	PWMMR4   = mr4;
	PWMMR5   = mr5;				//set rising edge of PWM2 to 2 ticks
	PWMLER   = 0x00000021;
	PWMTCR   = 2;
	PWMTCR   = 9;
	
}
//**********************************************************************************//
// Function Name: pwm_enable				   										//
// Arguments	: NONE																//
// Return Types	: NONE																//
// Description	: Enables PWMTCR													//
//**********************************************************************************//
void pwm_enable(void)
{
	PWMTCR   = 9;
}
//**********************************************************************************//
// Function Name: pwm_disable				   										//
// Arguments	: NONE																//
// Return Types	: NONE																//
// Description	: Disable PWMTCR													//
//**********************************************************************************//
void pwm_disable(void)
{
	while(PWMTC < PWMMR5 );
	PWMTCR   = 2;
}


