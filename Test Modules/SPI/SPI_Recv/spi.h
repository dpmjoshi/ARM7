#define SPI0_SEL   0x15<<8
#define CPHA		  1<<3
#define CLK_POLARITY  1<<4
#define MASTER        1<<5
#define LSB_FIRST     1<<6
#define INT_EN        1<<7
#define	MAX_CLK        8
#define MIN_CLK		  255

extern void spi_init(void);
extern void spi_clk_sel(U8);
extern U8   spi_send_byte(U8 data);
extern U8   spi_recv_byte(void);
extern void spi_send_data(U8*, U16);
extern void spi_recv_data(U8*, U16);