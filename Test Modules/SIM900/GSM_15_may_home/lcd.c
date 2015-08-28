#include <LPC214X.H>
#include "type.h"
#include "lcd.h"

#define RS 1 << 23
#define EN 1 << 22
#define DATA_MASK 0xff << 10






unsigned char k,data_ptr;
int *p,*s;

void lcd_init()
{
   //comdr(0x30);
   IO0DIR |= DATA_MASK;
   IO1DIR |= (RS | EN);

   comdr(0x30);	 //2 line,5*7 matrix
   ms_delay(40);
   comdr(0x38);	 //2 line,5*7 matrix
   ms_delay(40);
   comdr(0x01); //clear display
   ms_delay(40);
   comdr(0x06);	//automatic rt shift cursor
   ms_delay(40);
   comdr(0x0C);	//display on cursor on
   ms_delay(50);
}


void datar(unsigned char data)
 {
   IO0CLR = DATA_MASK;
   IO0SET = data << 10;
   IO1SET = RS;		//RS=1
   IO1SET = EN;		//EN=1
   ms_delay(5);
   IO1CLR = EN;		//EN=0

 }
     
 void comdr(unsigned char comd)
 {	
   IO0CLR = DATA_MASK;		
   IO0SET = comd << 10;
   IO1CLR = RS;		//RS=0
   IO1SET = EN;		//EN=1
   ms_delay(5);
   IO1CLR = EN;		 //EN=0
}

  
void clrscr()
{
  comdr(0x01); //clear display
  ms_delay(50);
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


void lcd_line_disp(U8 *line4_data, U8 position, U8 line_no)
{
 U8 l;
 switch(line_no)
 {
 	case 1:	position += 0x80;
	break;
	case 2:	position += 0xC0;
	break;
	case 3:	position += 0x90;
	break;
	case 4:	position += 0xd0;
	break;

 }
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
/*
void ms_delay(unsigned int w)
{
   U32 ui_cnt = 15000;
   while(w > 0)
      {
	  	while(ui_cnt > 0)
		{
			ui_cnt--;
		}
		ui_cnt = 15000;
	  }		
}

*/
