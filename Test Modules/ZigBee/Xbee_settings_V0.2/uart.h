extern void uart_init(void);
extern void uart0_send_byte(unsigned char );
extern void uart1_send_byte(unsigned char );
extern void uart0_send_string(unsigned char*);
extern void uart1_send_string(unsigned char*);
extern void uart0_ISR(void)__irq;
extern void uart1_ISR(void)__irq;