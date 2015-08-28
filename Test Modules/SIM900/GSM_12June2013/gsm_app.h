#define FREE     0
#define NOT_FREE 1

typedef struct dial
{
	U8 cnt;
	U8 no[15];
	U8 name[25];
	U8 time[8];
	struct dial *next;
	struct dial *prev;
}DIAL;

typedef struct contact
{
	U8 cnt;
	U8 no[15];
	U8 name[25];
	struct contact *next_no;
	struct contact *prev_no;
	struct contact *next_name;
	struct contact *prev_name;
}CONTACT;

extern void GSM_APP_diallist_init(U8 diallist_size);
extern void GSM_APP_diallist_update(U8 *phone_no, U8 *time);
extern U8   GSM_APP_diallist_show();
extern void GSM_APP_diallist_delete(DIAL *del_node);
extern U8   GSM_APP_options(U8 **opt_disp, U8 opt_cnt);
extern void GSM_APP_call(U8 *phone_no);
extern void GSM_APP_deleteall(DIAL *list_head);
extern void GSM_APP_write(U8 *text_msg);

extern U8 GSM_APP_compare_no(U8 *no1, U8 *no2);








