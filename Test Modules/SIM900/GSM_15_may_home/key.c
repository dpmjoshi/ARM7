#include"includes.h"
// P1.16 - P1.18 and P1.20  COLOMNS
// P0.28 - P0.31  ROWS//

#define ROWS 0xF0000000

U8 scancode(U32 temp1,U32 temp2);
U8 get_key(U8 pass_key);

U8 keyboard[4][4] = 		  
 { '1','2','3','A',
   '4','5','6','B',
   '7','8','9','C',
   'E','0','.','D'};
 

U8 get_key(U8 pass_key)
{
 U32 i=0,temp1,temp2; 
 U32 val1 =0;
 U8 key =0;
 
 IO0DIR |= ROWS;
 IO0CLR = ROWS;

 temp1 = IO1PIN ;
 temp1 >>= 16;
 val1   = temp1;
 
 if(pass_key == 1)
 {
	while((val1 & 0x0000000F) == 0x0000000F)
	{
		temp1  = IO1PIN;
		temp1 >>= 16;
		val1   = temp1;
	}
 }
 if((val1 & 0x0000000F) != 0x0000000F)					//temp2 == 	Row
 { 
 	key_delay(20);		//wait 20msec debounce time

	temp1  = IO1PIN;
	temp1 >>= 16;
	val1   = temp1;

 	if((val1 & 0x0000000F) != 0x0000000F)
  	{   
   		for(i=0;i<4;i++)
  		{
			IO0CLR = 0xF0000000;
  			switch(i)
			{
				case 0 : IO0SET = 0x70000000;				 	 
					     break;
				case 1 : IO0SET = 0xB0000000;	 
						 break;
				case 2 : IO0SET = 0xD0000000;	  
						 break;
				case 3 : IO0SET = 0xE0000000;	  
						 break;
	        }
			temp2 = i;	 ////------>  temp2 ====  row .... temp1 = column
			temp1 = IO1PIN;
			temp1 >>= 16;

			if((temp1 & 0x0000000F) != 0x0000000F)
  			{	                      
   				key = scancode(temp1,temp2);		//temp2 ------> row number
   	   			break;
  			}
			
  		}
	}
 } 
key_delay(250);
return key;
}


 
U8 scancode(U32 temp1,U32 temp2)	//temp1 = column......temp2 = row......
{
 U8 ch;				
 U16  code1 = 0,code2 = 0, j=0;

 for(j=0;j<4;j++)
 {
	code1 = temp1; 					//ADDED
	code1 = code1 & (1<<j);
	if(code1 == 0)
	{
		code1 = j;
		break;
	}
	else
		continue;
 }
 code2 = temp2;
 ch = keyboard[code2][code1];
 return ch;

}
