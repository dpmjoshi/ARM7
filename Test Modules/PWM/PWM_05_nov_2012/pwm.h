

/**** Macros -> PWM OUT PUT pin ****/
#define PWM_OUT7  1<<7
#define PWM_OUT9  1<<9
#define PWM_OUT10 1<<10
/**** Macros -> PWMPCR ****/
#define PWM5_OUT_EN 1<<13
/**** Macros -> PWMLER ****/
#define MR0_LATCH_EN 1<<0
#define MR1_LATCH_EN 1<<1
#define MR2_LATCH_EN 1<<2
#define MR3_LATCH_EN 1<<3
#define MR4_LATCH_EN 1<<4
#define MR5_LATCH_EN 1<<5
#define MR6_LATCH_EN 1<<6
/**** Macros -> PWM MR0 ****/
#define MR0_INT 1<<0
#define MR0_RST 1<<1
/**** Macros -> PWM MR5 ****/
#define MR5_INT 1<<15
#define MR5_RST 1<<16
/**** Macros -> PWMTC****/
#define PWM_TC_RST 0x02
#define PWM_TC_EN  0x01
#define PWM_EN     0x08

extern void pwm5_init(void);
extern void pwm5_pulse_width(unsigned int, unsigned int); 
extern void pwm_enable(void);
extern void pwm_disable(void);
extern void ms_delay(unsigned int w);
