#include"includes.h"

#define SPI_CS       1<<7
#define SD_CMD_SIZE	  6

#define IDLE_STATE_TIMEOUT 1


U8 sd_cmd0[7]  = {0x40,0x00,0x00,0x00,0x00,0x95};
U8 sd_cmd1[7]  = {0x40,0x00,0x00,0x00,0x00,0x95};
U8 sd_cmd16[7] = {0x40,0x00,0x00,0x00,0x00,0x95};
U8 sd_cmd17[7] = {0x40,0x00,0x00,0x00,0x00,0x95};
U8 sd_cmd58[7] = {0x40,0x00,0x00,0x00,0x00,0x95};

void sd_init(void);

void sd_init()
{
	IO0DIR = SPI_CS;
	IO0SET = SPI_CS; // set SPI SSEL 
	
	for(temp_cnt = 0; temp_cnt < 10; temp_cnt++)
	{	
		spi_send_byte(0xff);	// sending 80 clks to SD card to get initialise in SPI mode
	}

	IO0CLR = SPI_CS; // low SPI SSEL 
	spi_send_data(sd_cmd0, SD_CMD_SIZE);  // sending CMD0 to SD card 
	if(sd_response(0x01) == 1)
	{
	 SD_status = IDLE_STATE_TIMEOUT;
	 IOSET0 = SPI_SEL; /* set SPI SSEL */
	 return SD_status;
	}
	IOSET0 = SPI_SEL; /* set SPI SSEL */
	SPI_ReceiveByte();
	IOCLR0 = SPI_SEL; /* clear SPI SSEL */



}


int sd_response(U8 response)
{
	U16 count = 0xFFF;
	U8 result;
	while( count > 0 )
	{
		result = spi_recv_byte();
		if ( result == response )
		{
			break;
		}
	count--;
	}
	if ( count == 0 )
		return 1; /* Failure, loop was exited due to timeout */
	else
		return 0; /* Normal, loop was exited before timeout */
}