#include"includes.h"


void uart_init(void)
{

U1FCR=0X01;
U1LCR=0X83;		// Enable DLAB bit and selecting word length 8bit.
U1DLM=0X00;
U1DLL=0X62;	   //TO SET BAUD RATE
U1LCR=0X03;	   //disable DLAB bit.

//PINSEL0=0X00005005;
U0FCR=0X01;
U0LCR=0X83;		//
U0DLM=0X00;
U0DLL=0X62;	   //TO SET BAUD RATE
U0LCR=0X03;
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


