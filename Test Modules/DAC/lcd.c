#include "includes.h"
#include <stdio.h>

#define radd 0x40005000

void lcd_init();
void delay();
void datar();
void comdr();
void cursur_on();
void cursur_off();
void display();
void clrscr();


unsigned char k,data_ptr;
int *p,*s;

void lcd_init()
{
   //comdr(0x30);

   comdr(0x38);	 //2 line,5*7 matrix
   ms_delay(25);
   comdr(0x01); //clear display
   ms_delay(25);
   comdr(0x06);	//automatic rt shift cursor
   ms_delay(25);
   comdr(0x0C);	//display on cursor on
   ms_delay(25);
}


void datar(unsigned char data)
 {
   IO1CLR=0X00FF0000;
   IO1SET=data<<16;
   IO0SET=0X00000800;		//RS=1
   IO0SET=0X00000400;		//EN=1
   ms_delay(5);
   IO0CLR=0X00000400;		//EN=0

 }
     
 void comdr(unsigned char comd)
 {	
   IO1CLR=0X00FF0000;		
   IO1SET=comd<<16;
   IO0CLR=0X00000800;		//RS=0
   IO0SET=0X00000400;		//EN=1
   ms_delay(5);
   IO0CLR=0X00000400;		 //EN=0
   
 }

void cursur_on()
{
	comdr(0x0F);	//display on cursor on
  	ms_delay(25);
}

void cursur_off()
{
	comdr(0x0C);	//display on cursor on
  	ms_delay(25);
}



void lcd_line1_disp(unsigned char *line1_data, unsigned char position)
{
 unsigned char l;
 position += 0x80;
 comdr(position);
 ms_delay(15);
 for(l=0; *line1_data!='\0'; l++)
 {		
  datar(*line1_data);
  ms_delay(10);
  line1_data++;
 } 
}



 void lcd_line2_disp(unsigned char *line2_data, unsigned char position)
{
 unsigned char l;
 position += 0xc0;
 comdr(position);
 ms_delay(5);
 for(l=0; *line2_data!='\0'; l++)
 {		
  datar(*line2_data);
  ms_delay(1);
  line2_data++;
 } 
}
void lcd_line3_disp(unsigned char *line3_data, unsigned char position)
{
 unsigned char l;
 position += 0x94;
 comdr(position);
 ms_delay(5);
 for(l=0; *line3_data!='\0'; l++)
 {		
  datar(*line3_data);
  ms_delay(1);
  line3_data++;
 } 
}

void lcd_line4_disp(unsigned char *line4_data, unsigned char position)
{
 unsigned char l;
 position += 0xd4;
 comdr(position);
 ms_delay(5);
 for(l=0; *line4_data!='\0'; l++)
 {		
  datar(*line4_data);
  ms_delay(1);
  line4_data++;
 } 
}

 void lcd_line1_ch_disp(unsigned char line1_data, unsigned char position)
{
 position += 0x80;
 comdr(position);
 ms_delay(5);
 datar(line1_data);
 ms_delay(1);
}


 void lcd_line2_ch_disp(unsigned char line2_data, unsigned char position)
{
 position += 0xc0;
 comdr(position);
 ms_delay(5);
 datar(line2_data);
 ms_delay(1);
}

 void lcd_line3_ch_disp(unsigned char line3_data, unsigned char position)
{
 position += 0x94;
 comdr(position);
 ms_delay(5);
 datar(line3_data);
 ms_delay(1);
}

void lcd_line4_ch_disp(unsigned char line4_data, unsigned char position)
{
 position += 0xd4;
 comdr(position);
 ms_delay(5);
 datar(line4_data);
 ms_delay(1);
}




void lcd_scroll_disp(unsigned char *scroll_data,  unsigned char position)
{
 unsigned char i, j, *d;
 

 position += 0x80;
 d = scroll_data;		
 comdr(position);
 for(j = 15; j>0 ; j--)
 {
  position = j + 0x80;
  comdr(position);
  ms_delay(5);
  for(i=0; *d!='\0'; i++)
  {
   datar(*d);
   ms_delay(1);
   d++;
  }
  d = scroll_data++;
  ms_delay(9000);
  clrscr();
 }
}




   
void clrscr()
{
  comdr(0x01); //clear display
  ms_delay(20);
}  


void display_dots()
{
 U8 b,m;
  for(b=0;b<5;b++)
  	{
	for(m=0;m<3;m++)
		{
		 	comdr(0x8c+m);
			datar('.');
			ms_delay(1000);
		}
	for(m=0;m<3;m++)
		{
			comdr(0x8e-m);
		 	datar(' ');
			ms_delay(9);
		}
	ms_delay(50);
	}
}


