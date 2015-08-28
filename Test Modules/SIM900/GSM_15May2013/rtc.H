extern void rtc_init(void);
extern void set_alarm(U8 , U8 , U8 );
extern void rtc_get_time(U8*);
extern void rtc_get_date(U8*);
extern void disp_time(void);


extern U8 Uc_time_sec;
extern U8 Uc_alarm ;
extern U8 time [10];
extern U8 date[12];
