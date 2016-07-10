/**! \file md380.h
   \brief MD380 callback functions.
*/

#include <stdio.h>
#include <stdint.h>

#include "os.h"
#include "peripherals/stm32f4xx_rtc.h"


//Move these to their own module.
void strhex(char *, long);
void wstrhex(wchar_t *, long);



// md380 gfx
void gfx_drawtext(wchar_t *str,          //16-bit, little endian.
		  short sx, short sy, //Source coords, maybe?
		  short x, short y,   //X and Y position
		  int maxlen);
void gfx_drawbmp(char *bmp,
		 int x,
		 int y);

void gfx_drawtext2(wchar_t *str,    //16-bit, little endian.
                   int x, int y,   //X and Y position
                   int maxlen);

extern void gfx_chars_to_display(wchar_t *str, int x, int y, int unknown);


extern void gfx_select_font(void *p);

void gfx_set_bg_color(int color);
void gfx_set_fg_color(int color);

void gfx_blockfill(int xmin, int ymin, int xmax, int ymax);

// md380 dmr

//! Function that handles checking a DMR contact.
void* dmr_call_end(void *pkt);
//! Function that handles a DMR call.
void* dmr_call_start(void *pkt);
//! Function that handles a data packet.  (Also used in SMS.)
void* dmr_handle_data(void *pkt, int len);
//! Function that handles an incoming SMS.
void* dmr_sms_arrive(void *pkt);

//! Called before unsquelching.
int dmr_before_squelch();


//! Determines the squelching of an incoming call.
extern char* const  dmr_squelch_mode;
//! Unknown function involved in squelching.
extern char** const dmr_squelch_firstthing;


//Pointer to the buffer that stores the bottom line of screen text.
char * const botlinetext;

//ROM copy of the welcome bitmap.
extern char * const welcomebmp;

// md380 usb

//! Handle to the original (unhooked) upload handler.
int usb_upld_handle(void*, char*, int, int);
//! This returns a USB packet to the host from the upload handler.
int usb_send_packet(void*, char*, uint16_t);

int usb_dnld_handle();
extern int * const dnld_tohook;


// md380_spiflash
int     md380_spiflash_read(void *dst, long adr, long len);
void    md380_spiflash_write(void *dst, long adr, long len);
int     md380_spiflash_security_registers_read(void *dst, long adr, long len);
void    md380_spiflash_block_erase64k(uint32_t);
void    md380_spiflash_sektor_erase4k(uint32_t);
void    md380_spiflash_enable();
void    md380_spiflash_disable();
void    md380_spiflash_wait();
uint8_t md380_spi_sendrecv(INT8U data); // SPI1


//! Function that handles uC/OS-II settings
//Task
INT8U       OSTaskCreateExt(void (*task)(void *pd), void *pdata, OS_STK *ptos, INT8U prio, INT16U id, OS_STK *pbos, INT32U stk_size, void *pext, INT16U opt);
void*       OSTaskNameSet(INT8U prio, INT8U *pname, INT8U *perr);

//Semaphore
OS_EVENT *  OSSemCreate(uint16_t);
void        OSSemPend(OS_EVENT *pevent, uint32_t timeout,  uint8_t *perr);
uint8_t     OSSemPost(OS_EVENT *pevent);

//Mbox
uint8_t     md380_OSMboxPost(OS_EVENT *pevent, void *pmsg);

//! Halts all threads.
int         OS_ENTER_CRITICAL();
//! Resumes threads.
void        OS_EXIT_CRITICAL(int);



//! Functions and Variabes regarding the menu
void*   main_menu(void *);     // menu exec

void*   md380_menu_entry_back(void);
void*   md380_create_main_meny_entry(void);

// create one new menu entry
// menu_id (count from mainmenu 0), wt_menu_text, *()green key, *() red key, ?, ?, enabled
void*  md380_create_menu_entry(int, const wchar_t *, void *, void  *,
                               int , int, int);

// for the hook funktion (hook used the space from this entry)
void*  md380_menu_entry_programradio(void);
void*  md380_menu_numerical_input(void);

uint8_t   md380_menu_0x200011e4;
uint8_t   md380_menu_0x2001d3c1;
uint8_t   md380_menu_0x2001d3ed;
uint8_t   md380_menu_0x2001d3ee;
uint8_t   md380_menu_0x2001d3ef;
uint8_t   md380_menu_0x2001d3f0;
uint8_t   md380_menu_0x2001d3f1;
uint8_t   md380_menu_0x2001d3f4;
uint8_t   md380_menu_depth;
uint8_t   md380_menu_entry_selected;
uint8_t   md380_menu_id;

wchar_t	  md380_wt_programradio[1];  // menutext <- menu_entry_programradio

extern void     	* const md380_menu_mem_base;
extern void     	* const md380_menu_memory;
extern wchar_t  	* const md380_menu_edit_buf;

uint32_t  md380_menu_0x20001114;

//! program_radio_unprohibited (menu entry) ... bulding site is an struct
uint8_t md380_program_radio_unprohibited;

//! This points to the byte of the current channel.
extern char* const  channelnum;

//! Reads the current channel number from the rotary switch.
int read_channel_switch();

//! Reads a register from the C5000.
void c5000_spi0_readreg(int reg, char *buf);

//! Writes a register in the C5000.
void c5000_spi0_writereg(int reg, int val);


// md380 aes

//! Unknown AES function.
char* aes_cipher(char *pkt);

// md380 ambe2+
//! Unknown AMBE2+ thing.
int ambe_encode_thing(char *a1, int a2, int *a3, int a4,
		      short a5, short a6, short a7, int a8);
//! Decodes an AMBE2+ frame into bits.
int ambe_unpack(int a1, int a2, char length, int a4);

//! Populates the audio buffer.
int ambe_decode_wav(int *a1, signed int eighty, char *bitbuffer,
		    int a4, short a5, short a6, int a7);


//! Functions and Variabes regarding the beep_
// not yet known ;)
extern uint32_t * const beep_process_unkown;

//! useful firmware functions
wchar_t * md380_itow(wchar_t *, int value);
void      md380_RTC_GetDate(uint32_t RTC_Format, RTC_DateTypeDef *RTC_DateStruct);
void      md380_RTC_GetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct);

uint32_t md380_dmr_id;

// debug and training stuff

void md380_f_4137();
void md380_f_4520();
void md380_f_4098();
void md380_f_4102();
void md380_f_4225();

extern uint8_t * const md380_f_4225_operatingmode;
extern const uint8_t md380_f_4225_operatingmode_menu;
extern const uint8_t md380_f_4225_operatingmode_menu_exit;
