extern U32  LIB_hex_dec(U8 *dec_arr, U32 hex_val);
extern U32  LIB_dec_hex(U8 *dec_arr);
extern void LIB_hex_ascii(U8 *hex_val, U8 *ascii_arr);
													  
extern void LIB_str_copy(U8* source_str, U8* dest_str, U8 no_bytes);
extern U8   LIB_str_cmp(U8 *src,U8 *cmp);
extern void LIB_str_conc(U8 *str1, U8 *str2, U8 *str_conc);
extern void LIB_str_conc1(U8 *str1, U8 *str2,U8 *str_conc);
extern void LIB_frmt_arr(U8 *input_arr, U32 frmt_bytes);
extern U16  LIB_strlen(U8 *str);


