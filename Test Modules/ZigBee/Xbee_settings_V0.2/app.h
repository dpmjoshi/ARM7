//*************Variables**************//
extern  U8 set_time_count;
extern  U8 ch_lcd_data[20]; 
extern  U8 ch_lcd_data2[20];
extern  U8 Uc_dec_arr[11];
extern  U8 Uc_set_user_time[10];
extern  U8 space[400];
extern  U8 Uc_recv_data[110];
extern  U8 Uc_user_dwn_hr;
extern  U8 Uc_user_dwn_min;
extern  U8 Uc_user_dwn_sec;

extern  U8 Uc_byte_count;

//*************Functions**************//
extern  void frame_disp(void);
extern  void irq_init(void);
void    hex_ascii_conv(unsigned char*,unsigned char*,unsigned char);
extern  void default_page(void);
extern  void get_user_time(void);
extern  void user_temp_conv(void);
extern  void temp_ctrl(void);
extern  void adc_val_conv(U32, U32, U32, U32, U32, U8);

//************flags******************//
extern  U8 Uc_adc_time_out_flag;