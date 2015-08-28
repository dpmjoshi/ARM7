
extern void lcd_init(void);
extern void clrscr(void);
extern void datar(unsigned char);
extern void comdr(unsigned char);
extern void cursur_on(void);
extern void cursur_off(void);
extern void ms_delay(unsigned int);

//********************************************************
extern void lcd_line1_disp(unsigned char*, unsigned char);
extern void lcd_line2_disp(unsigned char*, unsigned char);
extern void lcd_line3_disp(unsigned char*, unsigned char);
extern void lcd_line4_disp(unsigned char*, unsigned char);
extern void lcd_line_disp(unsigned char*, unsigned char, unsigned char);
//********************************************************
extern void lcd_line1_ch_disp(unsigned char, unsigned char);
extern void lcd_line2_ch_disp(unsigned char, unsigned char);
extern void lcd_line3_ch_disp(unsigned char, unsigned char);
extern void lcd_line4_ch_disp(unsigned char, unsigned char);
//********************************************************
extern void display_dots(void);


