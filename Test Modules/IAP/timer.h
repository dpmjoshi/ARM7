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