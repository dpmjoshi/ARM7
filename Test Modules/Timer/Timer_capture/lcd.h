extern void lcd_init();
extern void clrscr();
extern void datar(U8);
extern void comdr(U8);
extern void cursur_on();
extern void cursur_off();
extern void ms_delay(unsigned int);
//********************************************************
extern void lcd_line1_disp(unsigned char*, unsigned char);
extern void lcd_line2_disp(unsigned char*, unsigned char);
extern void lcd_line3_disp(unsigned char*, unsigned char);
extern void lcd_line4_disp(unsigned char*, unsigned char);
//********************************************************
extern void lcd_line1_ch_disp(unsigned char, unsigned char);
extern void lcd_line2_ch_disp(unsigned char, unsigned char);
extern void lcd_line3_ch_disp(unsigned char, unsigned char);
extern void lcd_line4_ch_disp(unsigned char, unsigned char);
//********************************************************
extern void display_dots();


