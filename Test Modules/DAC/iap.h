#define IAP_CCLK (60000000 / 1000)
#define ram_add		 0x40002000
#define rom_add      0x00070000

#define FCCLK		 60000000
#define IAP_CLK		 FCCLK

extern void IAP_call(U32*, U32*, U32);
extern U8   IAP_prep_sec(U8, U8);
extern U8   IAP_erase_sec(U8, U8);
extern U8   IAP_program_sec(U32, U32, U16, U32);
extern void IAP_prog_ROM(U8 sec_no, U32 src_add);
extern void IAP_read_boot_code();
extern void IAP_status_code(U8);



