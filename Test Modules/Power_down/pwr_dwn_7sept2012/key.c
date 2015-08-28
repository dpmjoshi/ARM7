#include"includes.h"

void scancode(long temp1,long temp2);
U8 get_key(U8 pass_key);

U8 keyboard[4][4] = 		  
 { 'E','7','4','1',
   '0','8','5','2',
   '.','9','6','3',
   'D','C','B','A'};

 
U8 ch ;
U8 Uc_key_temp;
//*************************************
// Get key
//*************************************
U8 get_key(U8 pass_key)
{
		
U32 i=0,temp1,temp2; 
U32 val1 =0, val2 = 0;
U32 col1=0,col2=0; 


ch = 0;
IO1CLR = 0xFFFFFFFF;
temp1  = IO1PIN;							
val1   = temp1;
if(pass_key == 1)
{
	while((val1 & 0xF0000000) == 0xF0000000)
	{
		temp1  = IO1PIN;							
		val1   = temp1;
	}
}
if((col1 = (val1 & 0xF0000000)) != 0xF0000000)					//temp2 == 	Row
{

 val1 = temp1;
 key_delay(20);		//wait 20msec debounce time
 if((col2 = (val1 & 0xF0000000)) != 0xF0000000)
  	{   
   for(i=0;i<4;i++)
  		{
  			switch(i)
			{
			case 0 : IO1SET = 0x0D000000;	 //0x00580000
					 break;
			case 1 : IO1SET = 0x07000000;	 //0x00380000
					 break;
			case 2 : IO1SET = 0x0E000000;	  //0x00700000	  0x0E000000
					 break;
			case 3 : IO1SET = 0x0B000000;	  //0x00680000
					 break;
	        }
			temp2 = IO1PIN;	 ////------>  temp2 ====  row .... temp1 = column
			val2 = temp2;
			if((val2 & 0xF0000000) != 0xF0000000)
  				{	                      
   					scancode(temp1,temp2);		//temp2 ------> row number
   	    			break;
  				}
			IO1SET = 0xFFFFFFFF;
			IO1CLR = 0xFFFFFFFF; 
  		}
	}
	//else
	//continue;
 } 
key_delay(100);
return ch;
}


 
void scancode(long temp1,long temp2)	//temp1 = column......temp2 = row......
{
				
U16  code1 = 0,code2 = 0, j=0;
U16  val1=0,val2=0;					//ADDED VARIABLES



temp1=temp1>>28;                  //col
temp2=temp2 & 0x0F000000 ;	 //row
temp2=temp2>>24;


for(j=0;j<4;j++)
{
val1 = temp1; 					//ADDED
code1 = val1 & (1<<j);
	if(code1 == 0)
		{
			code1 = j;
			break;
		}
	else
			continue;
}

for(j=0;j<4;j++)
{
val2=temp2;						//ADDED
code2 = val2 & (1<<j);
	if(code2 == 0)
		{
			code2 = j;
			break;
		}
	else
	continue;
}


ch = keyboard[code2][code1];

temp1 = temp2 = 0;
IO1SET=0xFFFFFFFF;
IO1CLR = 0xFFFFFFFF;

}