extern void UART_init(void);
extern void UART_init_irq(void);
extern void uart0_send_byte(unsigned char );
extern void uart1_send_byte(unsigned char );
extern void uart0_send_string(unsigned char*);
extern void uart1_send_string(unsigned char*);
extern void uart0_ISR(void)__irq;
extern void uart1_ISR(void)__irq;

extern U8   Uc_recv_data[100];
extern U8   Uc_byte_count;

extern  U8  Uc_sof;
extern  U8  Uc_eof;



