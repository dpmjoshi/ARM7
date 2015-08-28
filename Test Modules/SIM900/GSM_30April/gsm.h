typedef struct 
{
 U8 detail[200];
 U8 data[300];
 U8 ph_no[20];
}SMS_INFO;
extern SMS_INFO SMS_cur;  
extern void gsm_init(void);
extern void gsm_sms_send(U8*, U8*);
extern void gsm_sms_del(U8);
extern void gsm_sms_del_all(U8 );
extern void gsm_check_status(void);
extern void gsm_voice_call(U8 *phone_no);
extern void gsm_end_voice_call();

