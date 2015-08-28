extern U8   APP_phone_dial(U8 *phone_no);
extern void APP_default_page();
extern void APP_mem_read(U8 uc_user_mode, U8 uc_old_msg);
extern void APP_mem_init(void);
extern U8 APP_msgtype_eval(U8 uc_msgtype);

extern U8 Uc_old_msg_disp[100];
extern U8 Uc_latest_msg_disp[100];

extern U8 Uc_old_msg_stu;
extern U8 Uc_old_msg_sta;

extern void APP_msgkey(U8 *text_msg);

extern void APP_msg();



