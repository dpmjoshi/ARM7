#include"includes.h"




U32 IAP_cmd[5] = {0,0,0,0,0};
U32 IAP_result[3] = {0,0,0};

U8  Uc_resp;


void IAP_call(U32*, U32*, U32);
U8   IAP_prep_sec(U8, U8);
U8   IAP_erase_sec(U8, U8);
U8   IAP_program_sec(U32, U32, U16, U32);
//void IAP_prog_ROM(U8, U32);
void IAP_read_boot_code();
void IAP_status_code(U8);

U8 uc_result;





void IAP_call(U32 *iap_cmd, U32 *result, U32 iap_add)
{
  
 __asm{mov r15,r2}

}

//**************************************************//

//**************************************************//

U8 IAP_prep_sec(U8 start_sec, U8 end_sec)
{

 U8 dec_arr1[5] = {"00"};


 IAP_cmd[0] = 50;
 IAP_cmd[1] = start_sec;
 IAP_cmd[2] = end_sec;
 IAP_call(&IAP_cmd[0], &IAP_result[0], 0x7FFFFFF0);

 uc_result = IAP_result[0];
 uart0_send_string("\n\rPreparing Sectors ");
 IAP_status_code(uc_result);
 return uc_result;
}
//**************************************************//
//													//
//**************************************************//

U8 IAP_erase_sec(U8 start_sec, U8 end_sec)
{
 IAP_cmd[0] = 52;
 IAP_cmd[1] = start_sec;
 IAP_cmd[2] = end_sec;
 IAP_cmd[3] = IAP_CCLK;
 IAP_call(&IAP_cmd[0], &IAP_result[0], 0x7FFFFFF0);

 uc_result = IAP_result[0];
 uart0_send_string("\n\rErase_sector      ");
 clrscr();
 lcd_line1_disp("Erasing Sectors...",0);
  
 IAP_status_code(uc_result);
 
 if(uc_result == 0)
 {
  ms_delay(10000);
  clrscr();
  lcd_line2_disp("Sectors Erased !",0);
 }
 return uc_result;
}
//**************************************************//

//**************************************************//

U8 IAP_program_sec(U32 dest_add, U32 ram_add, U16 no_bytes, U32 IAP_clk)
{
  IAP_cmd[0] = 51;
  IAP_cmd[1] = dest_add;
  IAP_cmd[2] = (U32)ram_add;
  IAP_cmd[3] = no_bytes;
  IAP_cmd[4] = IAP_clk;

  IAP_call(&IAP_cmd[0], &IAP_result[0], 0x7FFFFFF0);
  
  uc_result = IAP_result[0];

  clrscr();
  lcd_line1_disp("Programming_sector...",0);
  uart0_send_string("\n\rProgram_sector    ");
  IAP_status_code(uc_result);

  if(uc_result == 0)
  {
   ms_delay(10000);
   clrscr();
   lcd_line1_disp("Sectors programed !",0);
  }

  return uc_result;
}
//**************************************************//

//**************************************************//
void IAP_read_boot_code()
{
 U32 boot_ver;
 U8  arr[5]= "00";

 IAP_cmd[0] = 55;
 
 IAP_call(&IAP_cmd[0], &IAP_result[0], 0x7FFFFFF0);

 uart0_send_string("\n\r Boot Version: ");



 boot_ver = IAP_result[0];
 uc_result = (boot_ver & 0xff); 
 uart1_send_byte(uc_result + 0x30); 
 

 boot_ver = IAP_result[1];
 uc_result = (boot_ver & 0xff); 


 hex_dec(arr, uc_result);
 uart1_send_string(arr);

}



void IAP_status_code(U8 status_code)
{
  switch(status_code)
 {
  case 0:  uart0_send_string("   |    CMD_SUCCESS         |\n\r");
  		   break;
 
  case 1:  uart0_send_string("   |    INVALID_CMD         |\n\r");
		   break;

  case 2:  uart0_send_string("   |    SRC_ADD_ERROR       |\n\r");
		   break;
 
  case 3:  uart0_send_string("   |    DST_ADD_ERROR       |\n\r");
		   break;
 
  case 4:  uart0_send_string("   |    SRC_ADD_NOT_MAPPED  |\n\r");
		   break;

  case 5:  uart0_send_string("   |    DST_ADD_NOT_MAPPED  |\n\r");
		   break;	  		  
  
  case 6:  uart0_send_string("   |    COUNT_ERROR         |\n\r");
		   break; 
  
  case 7:  uart0_send_string("   |    INVALID_SECTOR      |\n\r");
		   break;
  
  case 8:  uart0_send_string("   |    SECTOR_NOT_BLANK    |\n\r");
		   break;
  
  case 9:  uart0_send_string("   |    SECTOR_NOT_PREPARED |\n\r");
		   break;	    
  
  case 10: uart0_send_string("   |    COMPARE_ERROR       |\n\r");
		   break;
  
  case 11: uart0_send_string("   |    BUSY                |\n\r");
 		   break; 
 }

}



//**************************************************//
//													//
//**************************************************//

void prog_rom()
{
 Uc_resp = IAP_prep_sec(21, 21);         // cmmand success
 if(Uc_resp == 0)
 {
  ms_delay(10000);
 
  Uc_resp = IAP_erase_sec(21, 21);	   // Erasing Sectors 
  if(Uc_resp == 0)
  {
   ms_delay(10000);
   Uc_resp = IAP_prep_sec(21, 21);    // Preparing Sectors
   if(Uc_resp == 0)
   {
    Uc_resp = IAP_program_sec(0x00070000, (U32)ram_add, 256, IAP_CCLK); // Programming Sectors
		 
    uart0_send_string("\n\n\n\r RAM Array:---->  ");
    uart0_send_string(ram_add);
		   
    uart0_send_string("\n\n\n\r ROM Array:---->  ");
    uart0_send_string(0x00070000);
   } 
  }
 }
}






/*
void IAP_prog_ROM(U8 sec_no, U32 src_add)
{
 
}

*/









