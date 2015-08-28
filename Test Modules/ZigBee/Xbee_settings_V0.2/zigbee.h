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
}ZB_NODE;

