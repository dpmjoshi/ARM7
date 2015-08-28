#define CAP0_RISE_EDGE 0x00000001 
#define CAP0_INT	   0x00000004

/* Macros for Capture Control Register (CCR)			  
The CCR is used to control functionality provided by      
capture registers. There are four capture regi. (CR0-CR3) */

#define CAP0_RISE	   0x001
#define CAP0_FALL	   0x002
#define CAP0_I  	   0x004

#define CAP1_RISE	   0x008
#define CAP1_FALL	   0x010
#define CAP1_I  	   0x020

#define CAP2_RISE	   0x040
#define CAP2_FALL	   0x080
#define CAP2_I  	   0x100

#define CAP3_RISE	   0x200
#define CAP3_FALL	   0x400
#define CAP3_I  	   0x800


/*  Macros for Timer0 */
#define T0_RESET       0x02 
#define T0_START	   0x01


extern U8   Uc_time1_arr[20];

extern U8   Uc_fre;
extern U32  Uc_pulse_width;

extern void timer0_init_interrupt();
extern void timer1_init_interrupt();
extern void timer1_init();
extern void timer1_on();
extern void timer1_off();
extern void time1_measure(U32);
extern void ms_delay(unsigned int w);
extern void key_delay(unsigned int w);