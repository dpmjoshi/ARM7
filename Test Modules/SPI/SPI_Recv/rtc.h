extern void rtc_init();
extern void rtc_init_interrupt();
extern void rtc_get_time();
extern U8 Uc_real_time[9];
extern U8 Uc_date[11];
extern U16	Uc_time_sec;
extern U8 Uc_alrm;
extern void set_alarm(U8, U8, U8);
extern void rtc_change_time();
