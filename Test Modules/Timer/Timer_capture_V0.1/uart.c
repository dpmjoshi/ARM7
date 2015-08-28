#include"includes.h"

U8  Uc_recv_data[100];
U8  Uc_byte_count = 0;

U8  Uc_eof = 0;
U8  Uc_sof = 0;

void UART_init(void)
{
 PINSEL0 |=0X00005005;
 U1FCR=0X01;
 U1LCR=0X83;		// Enable DLAB bit and selecting word length 8bit.
 U1DLM=0X00;
 U1DLL=0X62;	   //TO SET BAUD RATE
 U1LCR=0X03;	   //disable DLAB bit.

 U0FCR=0X01;
 U0LCR=0X83;		//
 U0DLM=0X00;
 U0DLL=0X62;	   //TO SET BAUD RATE
 U0LCR=0X03;
}

//***************************************************
//Initialisation of ISR
//***************************************************

void UART_init_irq(void)
{
  PINSEL0 |=0X00005005;

  U1FCR=0X01;
  U1LCR=0X83;		// Enable DLAB bit and selecting word length 8bit.
  U1DLM=0X00;
  U1DLL=0X62;	   //TO SET BAUD RATE
  U1LCR=0X03;	   //disable DLAB bit.

  U0FCR=0X01;
  U0LCR=0X83;		//
  U0DLM=0X00;
  U0DLL=0X62;	   //TO SET BAUD RATE
  U0LCR=0X03;
  
  VICVectAddr0 = (U32)&uart0_ISR;
  VICVectCntl0 = 0x20 | 6;
  VICIntEnable = 1 << 6;	
  U0IER=0x1; 

  VICVectAddr1 = (U32)&uart1_ISR;
  VICVectCntl1 = 0x20 | 7;
  VICIntEnable = 1 << 7;	
  U1IER=0x1;

}

//***************************************************
// ISR for UART0
//***************************************************
void uart0_ISR(void)__irq
{
    
   VICVectAddr   = 0x00;
}  
//***************************************************
// ISR for UART1
//***************************************************

void uart1_ISR(void)__irq
{
   Uc_recv_data[Uc_byte_count] = U1RBR;
   
   uart1_send_byte(Uc_recv_data[Uc_byte_count]);

   if(Uc_recv_data[Uc_byte_count] == '$')
   {
	   Uc_sof = 1;
	   Uc_eof = 0;
	   Uc_byte_count = 0;
   }
   else if((Uc_sof == 1) & (Uc_recv_data[Uc_byte_count] == '#'))
   {
	   Uc_eof = 1;
	   Uc_sof = 0;
	   Uc_recv_data[Uc_byte_count] = '\0';
   }
   Uc_byte_count++;
   
   VICVectAddr = 0x00;
}



// function sends a byte on UART0
void uart0_send_byte(unsigned char byte)
{
  U0THR=byte;
  while((U0LSR&0x20)==0);
}


// function sends a byte on UART1
void uart1_send_byte(unsigned char byte)
{
  U1THR=byte;
  while((U1LSR&0x20)==0);
 
}


// function sends a string on UART0
void uart0_send_string(unsigned char *string)
{
  unsigned char cnt;
  
  for (cnt=0; *string!='\0'; cnt++)
  {
  	U0THR =*string;
 	while((U0LSR&0x20) == 0);
  	string++;
  }
}

// function sends a string on UART1
void uart1_send_string(unsigned char *string)
{
  unsigned char cnt;
  
  for (cnt=0; *string != '\0'; cnt++)
  {
  	U1THR=*string;
 	while((U1LSR&0x20) == 0);
  	string++;
  }
}


