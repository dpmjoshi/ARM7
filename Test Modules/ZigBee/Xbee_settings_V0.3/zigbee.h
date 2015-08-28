extern void ZIGB_cmd_mode();
extern void ZIGB_exit_cmd();
extern void ZIGB_dl_wrt(U8*);
extern void ZIGB_setting();

typedef struct zb_node
{
 U8 my[6];
 U8 serial_high[20];
 U8 serial_low[20];
 U8 db[5];
 struct ZB_NODE *next;
 struct ZB_NODE *prev;
}ZB_NODE;

typedef struct zb_sett
{
 U8 my[7];
 U8 dl[7];
 U8 dh[7];
 U8 pan[7];
 U8 ch[7];
}ZB_SETT;