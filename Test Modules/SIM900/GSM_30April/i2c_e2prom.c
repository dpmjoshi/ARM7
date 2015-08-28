/*
			   -------------  
			   |        	|      			  
  			   |	MSG		| 0028 - 0127
			   |			|
 			   -------------  
			   |    DLC   	|    0027  			  
  			   -------------  
			   |  Duration	| 0024 - 0026 
			   -------------  
			   | Reserved   | 0018 - 0023
			   -------------  
			   |status time | 0012 - 0017
			   -------------
			   | phone no 	| 0002 - 0011 
			   --------------
			   |	ID		| 0000 - 0001
			   ------------- 
	
	MEMORY MAP OF PAGES IN THE EXTERNAL MEMORY

*/

 
#include <LPC21XX.H>
#include "type.h"
#include "uart.h"

#define I2C_CH_NO 9

void init_I2C(void);
void I2C_isr(void) __irq;
void i2c_trans(U8* , U8 , U8  , U32 );
void i2c_read(U8* , U8 , U8  , U32 );

U8 Uc_i2c_read_flag,addr_flag=0;
U8 *trans_data,*rec_data;
U8 tx_count,rx_count,Uc_i2c_count;
U8 Uc_dev_address;
U32 Ui_mem_address;

void i2c_init(void)
{
	PINSEL0|=0x50;
	VICIntSelect=0;
	VICIntEnable |= 1<<I2C_CH_NO;
	VICVectAddr6  = (unsigned)I2C_isr;
	VICVectCntl6  = 0x20|I2C_CH_NO;
	I2SCLH=75;
	I2SCLL=75;
	I2CONSET=0x40;	
}

void I2C_isr(void) __irq
{
	if(Uc_i2c_read_flag==0)
	{		  		
		switch(I2STAT)
		{
			case 0x08:
				I2DAT=Uc_dev_address;
				I2CONCLR=0x20;				
				break;

			case 0x10:
				break;

			case 0x18:
				I2DAT=((Ui_mem_address>>8) & 0xff);				
				break;
			case 0x20:
				break;
			case 0x28:
				if(addr_flag==0)
				{
					I2DAT=((Ui_mem_address) & 0xff);
					addr_flag=1;
					
				}
				else
				{
					if(tx_count<Uc_i2c_count)
					{
						I2DAT= *trans_data;
						trans_data++;
						tx_count++;
						
					}
					else
					{							
						I2CONSET=0x10;
						tx_count = 0;
						addr_flag=0;
						Uc_i2c_read_flag=1;
					}
				}
				break;

			case 0x30:
				break;
		}
	 }
	 else
	 {
		switch(I2STAT)
		{
			case 0x08:
				I2DAT= 0xA0 ;//Uc_dev_address;
				I2CONCLR=0x20;
				break;

			case 0x10:
				I2DAT=Uc_dev_address+1;
				I2CONSET=0x04;
				I2CONCLR=0x20;
				break;

			case 0x18:
				I2DAT=((Ui_mem_address>>8) & 0xff);
				break;

			case 0x20:
				break;

			case 0x28:
				if(addr_flag==0)
				{
					I2DAT=((Ui_mem_address) & 0xff);
					addr_flag=1;
				}
				else
				{
					I2CONSET=0x20;
				}
				break;

			case 0x38:
				break;
			case 0x40:
				if(Uc_i2c_count==1)
				{
					I2CONCLR=0x04;
				}				
				break;
			case 0x48:
				break;
			case 0x50:
				if(rx_count<(Uc_i2c_count)-2)
				{
					*rec_data=I2DAT;
					rec_data++;
					rx_count++;
				}
				else
				{
					*rec_data = I2DAT;
					rx_count++;
					rec_data++;
					I2CONCLR = 0x04;
				}
				break;
			case 0x58:
				*rec_data=I2DAT;
				I2CONSET=0x10;
				addr_flag = 0;
				Uc_i2c_read_flag=0;
				rx_count = 0;
				break;
				
		}
	}
	I2CONCLR=0x08;
	VICVectAddr=0;
}

void i2c_trans(U8* data_write, U8 no_bytes, U8 dev_addr , U32 mem_addr)
{	
	U32 ui_delay_count = 0;
	trans_data		   = data_write;
	Uc_i2c_count   = no_bytes;
	Uc_dev_address = dev_addr;
	Ui_mem_address = mem_addr;
	Uc_i2c_read_flag = 0;
	I2CONSET |= 0x20 ;
	tx_count = 0;
	while(Uc_i2c_read_flag == 0 );
	for(ui_delay_count = 0; ui_delay_count<50000 ; ui_delay_count++);


}

void i2c_read(U8* data_read, U8 no_bytes, U8 dev_addr , U32 mem_addr)
{	
	U32 ui_delay_count = 0;
	rec_data 		   = data_read;
	Uc_i2c_count   = no_bytes;
	Uc_dev_address = dev_addr;
	Ui_mem_address = mem_addr;
	Uc_i2c_read_flag = 1;
	I2CONSET |= 0x20;
	rx_count = 0;
	while(Uc_i2c_read_flag == 1 );
	for(ui_delay_count = 0; ui_delay_count<50000 ; ui_delay_count++);

}
