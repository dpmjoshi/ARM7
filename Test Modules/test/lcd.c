#include "includes.h"
#include <stdio.h>

#define DATA_MASK 0xFF<<16
#define RS        1<<11
#define EN        1<<10

#define EIGHT_BIT_MODE   0x38
#define FOUR_BIT_MODE    0x28
#define CLR_DISP	     0x01
#define AUTO_CUR         0x06
#define DISP_ON_CUR_OFF	 0x0C
#define DISP_ON_CUR_ON	 0x0F


void lcd_init();
void delay();
void lcd_data();
void lcd_cmd();
void cursur_on();
void cursur_off();
void display();
void clrscr();

//**********************************************************************************//
// Function Name: lcd_data					   										//
// Arguments	: U8 data															//
// Return Types	: NONE																//
// Description	: Function to write into DATA Reg. of LCD               			//
//**********************************************************************************//
void lcd_data(U8 data)
{
   IO1CLR |= DATA_MASK;                  
   IO1SET  = data<<16;
   IO0SET |= RS;              	//RS=1
   IO0SET |= EN;           		//EN=1
   ms_delay(5);
   IO0CLR |= EN;                //EN=0

}
//**********************************************************************************//
// Function Name: lcd_cmd					   										//
// Arguments	: U8 cmd															//
// Return Types	: NONE																//
// Description	: Function to write into Command Reg. of LCD               			//
//**********************************************************************************//
void lcd_cmd(U8 cmd)
{	
   IO1CLR |= DATA_MASK;                       		
   IO1SET  = cmd<<16;
   IO0CLR |= RS;               	//RS=0
   IO0SET |= EN;               	//EN=1
   ms_delay(5);
   IO0CLR |= EN;                //EN=0
   
}
//**********************************************************************************//
// Function Name: lcd_init					   										//
// Arguments	: NONE	     														//
// Return Types	: NONE																//
// Description	: Function to initialize LCD in 8-bit mode, 5*7 display, autocursor	//
//                increament with cursor off 										//
//**********************************************************************************//
void lcd_init()
{     
   lcd_cmd(EIGHT_BIT_MODE);	 //2 line,5*7 matrix
   ms_delay(25);
   lcd_cmd(CLR_DISP); //clear display
   ms_delay(25);
   lcd_cmd(AUTO_CUR);	//automatic rt shift cursor
   ms_delay(25);
   lcd_cmd(DISP_ON_CUR_OFF);	//display on cursor off
   ms_delay(25);
}
//**********************************************************************************//
// Function Name: clrscr					   										//
// Arguments	: NONE	     														//
// Return Types	: NONE																//
// Description	: Function to clear the display                                 	//
//**********************************************************************************//
void clrscr()
{
  lcd_cmd(CLR_DISP); //clear display
  ms_delay(5);
}

void cursur_on()
{
	lcd_cmd(DISP_ON_CUR_ON);	//display on cursor on
  	ms_delay(25);
}

void cursur_off()
{
	lcd_cmd(DISP_ON_CUR_OFF);	//display on cursor off
  	ms_delay(25);
}



void lcd_line1_disp(unsigned char *line1_data, unsigned char position)
{
 unsigned char l;
 position += 0x80;
 lcd_cmd(position);
 ms_delay(15);
 for(l=0; *line1_data!='\0'; l++)
 {		
  lcd_data(*line1_data);
  ms_delay(10);
  line1_data++;
 } 
}



 void lcd_line2_disp(unsigned char *line2_data, unsigned char position)
{
 unsigned char l;
 position += 0xc0;
 lcd_cmd(position);
 ms_delay(5);
 for(l=0; *line2_data!='\0'; l++)
 {		
  lcd_data(*line2_data);
  ms_delay(1);
  line2_data++;
 } 
}
void lcd_line3_disp(unsigned char *line3_data, unsigned char position)
{
 unsigned char l;
 position += 0x94;
 lcd_cmd(position);
 ms_delay(5);
 for(l=0; *line3_data!='\0'; l++)
 {		
  lcd_data(*line3_data);
  ms_delay(1);
  line3_data++;
 } 
}

void lcd_line4_disp(unsigned char *line4_data, unsigned char position)
{
 unsigned char l;
 position += 0xd4;
 lcd_cmd(position);
 ms_delay(5);
 for(l=0; *line4_data!='\0'; l++)
 {		
  lcd_data(*line4_data);
  ms_delay(1);
  line4_data++;
 } 
}

void lcd_scroll_disp(unsigned char *scroll_data,  unsigned char position)
{
 unsigned char i, j, *d;
 

 position += 0x80;
 d = scroll_data;		
 lcd_cmd(position);
 for(j = 15; j>0 ; j--)
 {
  position = j + 0x80;
  lcd_cmd(position);
  ms_delay(5);
  for(i=0; *d!='\0'; i++)
  {
   lcd_data(*d);
   ms_delay(1);
   d++;
  }
  d = scroll_data++;
  ms_delay(9000);
  clrscr();
 }
}

void display_dots()
{
 U8 b,m;
  for(b=0;b<5;b++)
  	{
	for(m=0;m<3;m++)
		{
		 	lcd_cmd(0x8c+m);
			lcd_data('.');
			ms_delay(1000);
		}
	for(m=0;m<3;m++)
		{
			lcd_cmd(0x8e-m);
		 	lcd_data(' ');
			ms_delay(9);
		}
	ms_delay(50);
	}
}


