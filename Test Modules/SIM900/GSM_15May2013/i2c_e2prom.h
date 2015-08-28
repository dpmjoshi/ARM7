
extern void i2c_init(void);
extern void i2c_isr(void) __irq;
extern void i2c_trans(U8* , U8 , U8  , U32 );
extern void i2c_read(U8* , U8 , U8  , U32 );

extern U8 *rec_data;
extern U8 *trans_data;
extern U8 Uc_i2c_read_flag;


void App_e2prom_log_trans(void);
