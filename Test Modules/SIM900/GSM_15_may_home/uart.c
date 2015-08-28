/*
* functions :-
* 1) void uart0_init(void)
*    Baud rate :- 9600
*	 
*/

#include "includes.h"

//#include "includes.h"




void uart_init(void);
void uart_init_interrupt(void);
U8 uart0_rx_byte(void);
U8 uart1_rx_byte(void);
void uart0_tx_byte(U8 );
void uart1_tx_byte(U8 );
void uart0_rx_string(U8*);
void uart1_rx_string(U8*);
void uart0_tx_string(U8*);
void uart1_tx_string(U8*);
void uart0_isr(void) __irq ;
void uart1_isr(void) __irq ;

U8 rx_data;
U8 Uc_user_option;
U8 uc_u1rbr = 0;

U8 Uc_eof_zb = 0;
U8 Uc_uart0_str_zb[100];
U8 Uc_byte_cnt_zb = 0;

U8 Uc_eof_gsm = 0;
U8 Uc_uart1_str_gsm[200];
U8 Uc_byte_cnt_gsm = 0;
U8 Uc_stat_code_gsm = 0;



void uart_init(void)				//Baud Rate: 9600 bps without interrupt
{
	PINSEL0 |=  0x00050005;
	U0LCR    =  DLAB_EN;
	U0DLL 	 =  BR9600_LSB;
	U0DLM    =  BR9600_MSB;
	U0LCR    =  DLAB_DISABLE_8BIT_WRDLEN;
	

	U1LCR    =  DLAB_EN;
	U1DLL 	 =  BR9600_LSB;
	U1DLM    =  BR9600_MSB;
	U1LCR    =  DLAB_DISABLE_8BIT_WRDLEN;

}

void uart_init_interrupt(void)		//Baud Rate: 9600 bps with interrupt
{
	PINSEL0 |=  0x00050005;
	U0LCR    =  DLAB_EN;
	U0DLL 	 =  BR9600_LSB;
	U0DLM    =  BR9600_MSB;
	U0LCR    =  DLAB_DISABLE_8BIT_WRDLEN;
	
	 
	U1LCR    =  DLAB_EN;
	U1DLL 	 =  BR9600_LSB;
	U1DLM    =  BR9600_MSB;
	U1LCR    =  DLAB_DISABLE_8BIT_WRDLEN;
	
  
	VICIntSelect  =  0x00;    
	VICVectAddr0  =  (unsigned) uart0_isr ; 
	VICVectCntl0  =  ENABLE_SLOT | UART0_CHANNEL_NO;
	VICIntEnable  |= (1 << UART0_CHANNEL_NO);
	U0IER	      =  0x01;
	 
	VICIntSelect  =  0x00;    
	VICVectAddr1  =  (unsigned) uart1_isr ; 
	VICVectCntl1  =  ENABLE_SLOT | UART1_CHANNEL_NO;
	VICIntEnable  |= (1 << UART1_CHANNEL_NO);
	U1IER	      =  0x01;	

	uart0_tx_string("\n\rUART0 connnected @9600");

}

U8 uart0_rx_byte(void)							   // Receive single byte
{
	U8 rx_data;
	while(!(U0LSR&0X01));
	rx_data = U0RBR;
	return(rx_data);
}

U8 uart1_rx_byte(void)							   // Receive single byte
{
	U8 rx_data;
	while(!(U1LSR&0X01));
	rx_data = U1RBR;
	return(rx_data);
}

void uart0_tx_byte(U8 tx_data)					   // Transmit single byte
{
	U0THR = tx_data;
	while(!(U0LSR&0X20));
}

void uart1_tx_byte(U8 tx_data)					   // Transmit single byte
{
	U1THR = tx_data;
	while(!(U1LSR&0X20));
}

void uart0_rx_string(U8* pdata)					 // Receive string
{

	U8 len=0;
	do
	{
		pdata[len]=uart0_rx_byte();	
	}
	while (pdata[len++]!=0x0d);
	pdata[len]='\0';

}

void uart1_rx_string(U8* pdata)					 // Receive string
{

	U8 len=0;
	do
	{
		pdata[len]=uart1_rx_byte();	
	}
	while (pdata[len++]!=0x0d);
	pdata[len]='\0';

}


void uart0_tx_string(U8* tx_data)				 // Transmit string
{
	/*
	uart0_tx_byte(0x0d);
	uart0_tx_byte(0x0a);
	*/
	while(*tx_data != '\0')
	{
		uart0_tx_byte(*tx_data);
		tx_data++;
	}	  
}

void uart1_tx_string(U8* tx_data)				 // Transmit string
{
	/*
	uart1_tx_byte(0x0d);
	uart1_tx_byte(0x0a);
	*/
	while(*tx_data != '\0')
	{
		uart1_tx_byte(*tx_data);
		tx_data++;
	}	  
}


void uart0_isr(void) __irq
{
	//Uc_eof_zb = 0;
  	Uc_uart0_str_zb[Uc_byte_cnt_zb] = U0RBR; 
  //	uart0_tx_byte(Uc_uart0_str_zb[Uc_byte_cnt_zb]);
	if((Uc_uart0_str_zb[Uc_byte_cnt_zb] == '\r'))
  	{
		if(Uc_byte_cnt_zb > 76)
		{
		 	uart0_tx_string("\n\n\r Buffer limit exceeded!!!");
			uart0_tx_string("\n\r Please enter messege within limits(max 77 characters)");
		}
		else
		{
  			Uc_uart0_str_zb[Uc_byte_cnt_zb] = '\0';
			Uc_eof_zb = 1;
		}
  			Uc_byte_cnt_zb = 0;
 	}
  	if((Uc_eof_zb == 0) && (Uc_byte_cnt_zb < 77))
  	{
  		Uc_byte_cnt_zb++;
  	}   
  	VICVectAddr = 0;

}


void uart1_isr(void) __irq
{ 	
	uc_u1rbr = U1RBR;
/*	if(uc_u1rbr == '\n')
	{
	uc_u1rbr = '@';
	}
	else if(uc_u1rbr == '\r')
	{
	uc_u1rbr = '#';
	}
*/	
	uart0_tx_byte(uc_u1rbr);			 
	
	switch(Uc_stat_code_gsm)
	{
	  case  0:  if(uc_u1rbr == '\r')
				{
	  				Uc_stat_code_gsm = 10;
	  				Uc_byte_cnt_gsm = 0;
					Uc_uart1_str_gsm[Uc_byte_cnt_gsm] = uc_u1rbr;	
					Uc_byte_cnt_gsm++;
				}
				break;

	  case 10: 	Uc_uart1_str_gsm[Uc_byte_cnt_gsm] = uc_u1rbr;	 // Status code 10 signifies that first '\r' has been received and coming bytes  7
				Uc_byte_cnt_gsm++;							 // will be a part of GSM response. This response is further analyzed in case 11.
				if(uc_u1rbr == '\r')
				{
				 	Uc_stat_code_gsm = 11;
				}
				break;

	  case 11:	Uc_uart1_str_gsm[Uc_byte_cnt_gsm] = uc_u1rbr;
				Uc_uart1_str_gsm[Uc_byte_cnt_gsm + 1] = '\0';
				
	            break;
						  
	  case 20:	if(uc_u1rbr == '+')
				{				
					Uc_byte_cnt_gsm = 0;	
					SMS_cur.detail[Uc_byte_cnt_gsm] = uc_u1rbr;
				    Uc_byte_cnt_gsm++;
				 	Uc_stat_code_gsm = 21;
				}
				break;

	  case 21:	SMS_cur.detail[Uc_byte_cnt_gsm] = uc_u1rbr;
				Uc_byte_cnt_gsm++;							 
				if(uc_u1rbr == '\n')
				{
				 	Uc_stat_code_gsm = 22;
				}
				break;

	  case 22: 	SMS_cur.detail[Uc_byte_cnt_gsm] = uc_u1rbr;
				Uc_byte_cnt_gsm++;							 
				if(uc_u1rbr == '\n')
				{
					SMS_cur.detail[Uc_byte_cnt_gsm] = '\0';
				 	Uc_stat_code_gsm = 23;
					Uc_byte_cnt_gsm = 0;
				}
				break;

	  case 23:  SMS_cur.data[Uc_byte_cnt_gsm] = uc_u1rbr;
				Uc_byte_cnt_gsm++;							 
				if(uc_u1rbr == '\n')
				{
					SMS_cur.data[Uc_byte_cnt_gsm] = '\0';
				 	Uc_stat_code_gsm = 24;
				}
	}
	
  	VICVectAddr = 0;

}
