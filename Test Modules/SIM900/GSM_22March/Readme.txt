/****************************************************************************************/
/ This file contains the documentation of vital & basic functions used in this project.  /
/ The document is categorized according to the C files developed.				     /
/														     /
/****************************************************************************************/
 
/****************************************************************************************/
/						LIB.c								     /
/****************************************************************************************/

Function Name:

****** MATH Functions *******
1) LIB_hex_dec()
2) LIB_hex_ascii()

****** String Functions *******
3) LIB_str_copy()
4) LIB_str_cmp()
5) LIB_str_conc()
6) LIB_frmt_arr()
7) LIB_frag_arr()

/****************************************************************************************/

1) U32 LIB_hex_dec(U8 *dec_arr, U32 hex_val)

   Arguments: 
		U8  *dec_arr - a pointer to the array of type unsigned char, which will hold the converted decimal(ASCII) values.
		U32 hex_val  - a hex value that is to be converted into decimal. 
   
   Return value: 
		ui_hex_val - this variable contains the no of characters that are utilized for conversion. The use of this return value is optional 
		it will be more useful in the case where decimal array is displayed on LCD. In that case if first value is of 4 digits and the 
		second one is of lesser digits then it is necessary to clear LCD first & then print new value.

   Local Variables:
		U8  uc_cnt = 0
		U32 ui_div_fctr = 1  -> very important to initiate it at 1.
		U32 ui_hex_val  = 0

   Description:
		It first evaluates the division factor by dividing the hex no by 10 recurssively.
		It also increments the uc_cnt which is the return value of function.
		The second loop actually converts the hex no into dec and adds 0x30 in it. It places these numbers in the provided dec_arr. 
		Lastly it terminates the array by adding '\0'.

/****************************************************************************************/

2) void LIB_hex_ascii(U8 *hex_val, U8 *ascii_arr)

   Arguments: 
		U8 *hex_val   - a pointer to the array of type unsigned char, which contains the hex values.for example: hex_val[10] = {34,23,22,56};
		U8 *ascii_arr - a pointer to the array of type unsigned char, which contains ASCII equivalent characters of hex numbers. Thus for each 
		number ascii_arr consumes two bytes. 

   Return Value: 
		NONE

   Local Variables: 
		U8 uc_temp = 0 - a temporary variable used for conversion 

   Description: 
		This function converts the array of Hex values into ASCII characters.
		It is done by shifting the byte by 4 in order to get higer nibble, and then masking the lower nibble with 0x0f

/****************************************************************************************/


3) void LIB_str_copy(U8 *source_str, U8 *dest_str, U8 no_bytes)


    Arguments: 
		U8 *source_str - a pointer to the source string 
		U8 *des_str    - a pointer to the destination string 
		U8 no_bytes    - Number of bytes that need to be copied from source to destination

    Return Value: 
		NONE

    Local Variables:
		U8 uc_count  - a temp count variable used in internal loop.

    Description:
		The function copies X number of bytes from source array to destination array. The X number is specified by the "no_bytes" argument.
		The important point is it does not terminate destination array with 0. 