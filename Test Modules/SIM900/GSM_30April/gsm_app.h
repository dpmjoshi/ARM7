#define FREE     0
#define NOT_FREE 1

typedef struct dial
{
	U8 cnt;
	U8 no[15];
	U8 name[25];
	U8 time[8];
	struct DIAL *next;
	struct DIAL *prev;
}DIAL;

extern void GSM_APP_diallist_init(U8 diallist_size);
extern void GSM_APP_diallist_update(U8 *phone_no, U8 *time);
extern U8   GSM_APP_diallist_show();
extern void GSM_APP_diallist_delete(DIAL *del_node);
extern U8   GSM_APP_options(U8 **opt_disp, U8 opt_cnt);
extern void GSM_APP_call();








