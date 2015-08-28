#define    DLAB_EN         					0X80
#define    DLAB_DISABLE_8BIT_WRDLEN         0X03
#define    BR9600_LSB         				0X61
#define    BR9600_MSB         				0X00
#define    BR4800_LSB         				0X86
#define    BR4800_MSB         				0X01
#define    UART0_PINSEL         			0X05
#define    MAX_CHAR        					0X20
#define    UART0_CHANNEL_NO       			0X06
#define    UART1_CHANNEL_NO       			0X07
#define    ENABLE_SLOT       				0X20


extern U8 Uc_uart1_string[200];
extern U8 Uc_eof;
extern U8 Uc_user_option;

extern U8 Uc_uart0_str_zb[100];
extern U8 Uc_eof_zb;

extern U8 Uc_eof_gsm;
extern U8 Uc_uart1_str_gsm[200];
extern U8 Uc_stat_code_gsm;
extern U8 Uc_byte_cnt_gsm;


extern void ms_delay(unsigned int);
extern void uart_init(void);
extern U8 uart0_rx_byte(void);
extern U8 uart1_rx_byte(void);
extern void uart0_tx_byte(U8 );
extern void uart1_tx_byte(U8 );
extern void uart0_rx_string(U8*);
extern void uart1_rx_string(U8*);
extern void uart0_tx_string(U8*);
extern void uart1_tx_string(U8*);
extern void uart_init_interrupt(void);



