//-----------------------------------------------------------------------------
#ifndef DEBUG_DEF_H
#define DEBUG_DEF_H
//-----------------------------------------------------------------------------

// DEPENDENCIES
//-----------------------------------------------------------------------------
#include "../avr-misc/avr-misc.h"
//-----------------------------------------------------------------------------

#ifndef LIB_AVR_MISC
#error No avr-misc library found. Please clone it from github.com/specadmin/avr-misc into lib/avr-misc
#endif

#ifndef DEBUG_PORT
#error Please define DEBUG_PORT in configuration file (config.h)
#endif

#ifndef DEBUG_DDR
#error Please define DEBUG_DDR in configuration file (config.h)
#endif

#ifndef DEBUG_BIT
#error Please define DEBUG_BIT in configuration file (config.h)
#endif

#ifndef DEBUG_BAUD_RATE
#error Please define DEBUG_BAUD_RATE in configuration file (config.h)
#endif

#if (DEBUG_BAUD_RATE!=115200) && (DEBUG_BAUD_RATE!=1152000)
#error DEBUG_BAUD_RATE should be equal to 115200 or 1152000
#endif

#ifndef F_CPU
#error Please define F_CPU in configuration file (config.h)
#endif

#if F_CPU!=16000000
#error Sorry, only 16 MHz CPU frequency is supported
#endif

#ifndef DEBUG_BUF_SIZE
#define DEBUG_BUF_SIZE  96
#endif

#ifndef DEBUG_SECTION
#define DEBUG_SECTION   __attribute__ ((section (".debugger.text")))
#endif

//-----------------------------------------------------------------------------
#define DEBUG_STRING __attribute__ ((section (QUOTE(CONCAT(.debugger.strtab.,__COUNTER__)))))
#define VAR_NAME CONCAT(dstr_,__LINE__)
#define PSTRD(str) (__extension__({static const char DEBUG_STRING VAR_NAME[]=str;&VAR_NAME[0];}))
//-----------------------------------------------------------------------------

// DEBUG_INIT initialises the transmitter
#define DEBUG_INIT() { set_bit(DEBUG_DDR, DEBUG_BIT); set_bit(DEBUG_PORT, DEBUG_BIT); mdelay(100); DSTR("=========="); DSTR("DEBUG INIT"); DSTR("=========="); }

// DSTRN prints const string stored in .debugger.strtab section without carrier return
#define DSTRN(str)  { debug_print_pm(PSTRD(str),false); }

// DSTR prints const string stored in .debugger.strtab section
#define DSTR(str)  { debug_print_pm(PSTRD(str),true); }

// DUMP_MEM prints RAM dump starting at ptr
#define DUMP_MEM(ptr,size) debug_print_dump((WORD)ptr,size,RAM);

// DREG prints register value
#define DREG(reg)  { debug_print_pm(PSTRD(#reg" = 0x")); debug_print_hex1(reg,true); }

// DVAR prints integer decimal value
#define DVAR(var)  { debug_print_pm(PSTRD(#var" = ")); debug_print_dec(var); }

// DHEX prints variable value in compact and fast mode
#define DHEX(var)  { debug_print_pm(PSTRD(#var" = 0x")); debug_print_hex(var); }

// DHEX8 prints a set of one-byte variables one by one in a line
#define DHEX8(count, ...)  { debug_print_hex8(count, ##__VA_ARGS__); }

//-----------------------------------------------------------------------------
enum mem_area { RAM = 1, PGM, EE };
void debug_print_pm(const char *str, bool new_line = false);
void debug_print_dump(WORD from, const unsigned int sz, enum mem_area area);
void debug_print_hex1(char data, bool new_line = false);
void debug_print_dec(void* data, bool new_line = true);
void debug_print_dec(char data, bool new_line = true);
void debug_print_dec(int data, bool new_line = true);
void debug_print_dec(long data, bool new_line = true);
void debug_print_dec(unsigned char data, bool new_line = true);
void debug_print_dec(unsigned int data, bool new_line = true);
void debug_print_dec(unsigned long data, bool new_line = true);
void debug_print_hex(void* data, bool new_line = true);
void debug_print_hex(char data);
void debug_print_hex(int data);
void debug_print_hex(long data);
void debug_print_hex(unsigned char data);
void debug_print_hex(unsigned int data, bool new_line = true);
void debug_print_hex(unsigned long data);
void debug_print_hex8(BYTE count, ...);
//-----------------------------------------------------------------------------
#endif
