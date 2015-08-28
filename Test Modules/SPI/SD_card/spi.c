//********************************************************************************************************//


//*******************************************************************************************************//
#include "includes.h"

void spi_init(void);
void spi_clk_sel(U8);
void spi_send_byte(U8 data);
U8   spi_recv_byte(void);
void spi_send_data(U8*, U16);
void spi_recv_data(U8*, U16);


//**********************************************************************************//
// Function Name: spi_init					   										//
// Arguments	: NONE	     														//
// Return Types	: NONE																//
// Description	: Function to initialise SPI interface in to master mode,clk-400kHz //
//**********************************************************************************//
void spi_init(void)
{
  PINSEL0 |= SPI0_SEL;
  S0SPCR  |= MASTER;
  spi_clk_sel(37); 
}
//**********************************************************************************//
// Function Name: spi_clk_sel				   										//
// Arguments	: U8 clk     														//
// Return Types	: NONE																//
// Description	: Function which writes "U8 clk" to S0SPCCR, the value in S0SPCCR   //
//                is used to derive SPI clk from PCLK								//
//**********************************************************************************//
void spi_clk_sel(U8 clk)
{
 S0SPCCR  =	clk;
}
//**********************************************************************************//
// Function Name: spi_send_byte				   										//
// Arguments	: U8 data	     													//
// Return Types	: NONE																//
// Description	: Function to transmit a single byte as specified by "U8 data"      //
//**********************************************************************************//
void spi_send_byte(U8 data)
{
  U8 temp;	
  S0SPDR = data;
  while(!(S0SPSR & 0x80));
  temp = S0SPDR;
}
//**********************************************************************************//
// Function Name: spi_recv_byte				   										//
// Arguments	: NONE	        													//
// Return Types	: U8																//
// Description	: Function to receive a single byte                                 //
//**********************************************************************************//
U8 spi_recv_byte(void)
{
  U8 data;
  S0SPDR = 0xff;		    // dummy write in S0SPDR which causes SPI controller to 
  while(!(S0SPSR & 0x80));	// genrate CLK which in turn recv the data from MISO PIN
  data = S0SPDR;
  return data;
}
//**********************************************************************************//
// Function Name: spi_send_data				   										//
// Arguments	: NONE	     														//
// Return Types	: NONE																//
// Description	: Function to transmit no of bytes to slave specified by	        //
//                "U16 no_byte" argument & "U8 *data" is the source of bytes 		//
//**********************************************************************************//
void spi_send_data(U8 *data, U16 no_byte)
{
  U8 temp_count;
  if(no_byte > 0)
  {
   for(temp_count = 0; temp_count < no_byte; temp_count++)
   {
	spi_send_byte(*data);
	data++;
   }
  }
}
//**********************************************************************************//
// Function Name: spi_recv_data					 									//
// Arguments	: U8 *data, U16 no_bytes	     									//
// Return Types	: NONE																//
// Description	: Function to receive no of bytes from slave specified by	        //
//                "U16 no_byte" the argument & are stored in "U8 *data"             //
//**********************************************************************************//
void spi_recv_data(U8 *data, U16 no_byte)
{
  U16 temp_count;
  for(temp_count = 0; temp_count < no_byte; temp_count++)
  {
  	*data = spi_recv_byte();
	data++;
  }
}






























