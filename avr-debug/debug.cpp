//-----------------------------------------------------------------------------
// debug.cpp
//-----------------------------------------------------------------------------
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include "debug.h"
//-----------------------------------------------------------------------------
#ifdef DEBUG
//char dbg_fmt[DEBUG_BUF_SIZE];
char dbg_buf[DEBUG_BUF_SIZE];
//-----------------------------------------------------------------------------
#pragma GCC diagnostic ignored "-Wunused-function"
//-----------------------------------------------------------------------------
static void DEBUG_SECTION _write_byte(char data)
{
    disable_interrupts();
    #if DEBUG_BAUD_RATE==1152000
    register BYTE cbit;
    asm volatile
    (
        "cbi %[port],%[pin]\n"  // start bit
        "rjmp .+0\n"
        "rjmp .+0\n"
        "rjmp .+0\n"
        "rjmp .+0\n"
        "ldi %[cbit],8 \n"
  "loop: sbrc %[data],0 \n"
        "rjmp one\n"
        "cbi %[port],%[pin]\n"
        "rjmp .+6 \n"
   "one: sbi %[port],%[pin]\n"
        "rjmp .+0\n"
        "nop \n"
        "nop \n"
        "rjmp .+0\n"
        "lsr %[data] \n"
        "dec %[cbit] \n"
        "brne loop \n"
        "rjmp .+0\n"
        "rjmp .+0\n"
        "sbi %[port],%[pin]\n"  // stop bit
        "rjmp .+0\n"
        : [cbit] "=&r" (cbit)
        : [port] "I" (_SFR_IO_ADDR(DEBUG_PORT)),
          [pin]  "I" (DEBUG_BIT),
          [data] "r" (data)
    );
    #else
        #if DEBUG_BAUD_RATE==115200
            #define D_DELAY 139
        #else
            #error Unsupported baud rate defined
        #endif
        #define D_DELAY2 D_DELAY-2
        #define D_DELAY7 D_DELAY-7
        #define D_DELAY8 D_DELAY-8
    clr_bit(DEBUG_PORT, DEBUG_BIT); // start bit
    delay_cycles(D_DELAY2);    // ceil(F_CPU)/115200-2 (-2 clocks for 'for' initialisation)
    for(int i = 0; i < 8; i++) // data bits
    {
        if(data & 0x01)
        {
            set_bit(DEBUG_PORT, DEBUG_BIT);
            delay_cycles(D_DELAY8);  // -8 clocks
        }
        else
         {
            clr_bit(DEBUG_PORT, DEBUG_BIT);
            delay_cycles(D_DELAY7); // -7 clocks
         }
         data>>=1;
    }
    set_bit(DEBUG_PORT, DEBUG_BIT); // stop bit
    delay_cycles(D_DELAY2);    // -2 clocks
    #endif
    resume_interrupts();
}
//-----------------------------------------------------------------------------
static void DEBUG_SECTION _write(const char *data,int num)
{
    for(int i = 0; i < num; i++)
        _write_byte(data[i]);
}
//-----------------------------------------------------------------------------
__inline void _endl()
{
   _write_byte('\n');
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_hex1(char data,bool new_line)
{
    char buf[2];
    char c = data & 0x0F;
    buf[1] = c < 10 ? c + '0' : c - 10 + 'A';
    c= (data >> 4) & 0x0F;
    buf[0] = c < 10 ? c + '0' : c - 10 + 'A';
    _write(buf, 2);
    if(new_line)
    {
        _endl();
    }
}
//-----------------------------------------------------------------------------
__inline void DEBUG_SECTION _print_hexN(long int data, BYTE bytes)
{
    char buf[8];
    char *p = buf + 7;
    bytes *= 2;
    for(int i = 0; i < bytes; i++)
    {
        char c = data & 0x0F;
        *p-- = (c < 10) ? c + '0' : c - 10 + 'A';
        data >>= 4;
    }
    _write(buf+sizeof(buf)-bytes,bytes);
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_pm(const char *str,bool new_line)
{
    char val = 0;
    while((val = pgm_read_byte(str++)))
        _write_byte(val);
    if(new_line)
        _endl();
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_dump(WORD from, const unsigned int sz, enum mem_area area)
{
    WORD index;
    for(WORD k = 0; k <= (sz - 1) / 16; k++)
    {
        #ifdef DEBUG_EXTENDED_DUMP
        _write_byte(' ');
        debug_print_hex(from + k * 16, false);
        _write_byte(':');
        _write_byte(' ');
        _write_byte(' ');
        #endif
        for(WORD i = 0; i < 16; i++)
        {
            index = k * 16 + i;
            if(index < sz)
            {
                BYTE val = 0;
                switch(area)
                {
                case EE:
                    #ifdef DEBUG_EEPROM
                    val = EEPROM_read(from + index);
                    #endif
                    break;
                case PGM:
                    val = pgm_read_byte((BYTE*)from + index);
                    break;
                case RAM:
                    val = *(BYTE*)((BYTE*)from + index);
                }
                debug_print_hex1(val);
            }
            else
            {
                _write_byte(' ');
                _write_byte(' ');
            }
            _write_byte(' ');
        }
        #ifdef DEBUG_EXTENDED_DUMP
        _write_byte(' ');
        _write_byte(' ');
        for(WORD i = 0; i < 16; i++)
        {
            index = k * 16 + i;
            if(index >= sz) break;
            BYTE c = 0;
            switch(area)
            {
            case EE:
                #ifdef DEBUG_EEPROM
                c = EEPROM_read(from + index);
                #endif
                break;
            case PGM:
                c = pgm_read_byte((BYTE*)from + index);
                break;
            case RAM:
                c = *(BYTE*)((BYTE*)from + index);
            }
            switch(c)
            {
            // непечатаемые символы
            case '\r':
            case '\n':
            case '\v':
            case '\f':
            case '\t':
            case '\b':
            case '\0':
            case 0x05:
            case 0x07:
            case 0x0E:
            case 0x0F:
            case 0x8E:
            case 0x8F:
            case 0xCF:
            case 0xDF:
            case 0xEF:
                c = '.';
            }
            _write_byte(c);
        }
        #endif
        if((k + 1) * 16 < sz)
            _endl();
    }
    _endl();
}
//-----------------------------------------------------------------------------
__inline void _print_dec(unsigned long data, bool new_line)
{
    char buf[10];
    BYTE i = 0;
    if(data < 10)
    {
        _write_byte(data+'0');
    }
    else
    {
        while(data)
        {
            buf[i++] = data % 10;
            data /= 10;
        }
        while(i)
        {
            _write_byte(buf[--i] + '0');
        }
    }
    if(new_line) _endl();
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_dec(char data, bool new_line)
{
    if(data<0)
    {
        _write_byte('-');
        _print_dec(~data + 1, new_line);
    }
    else
    {
        _print_dec(data, new_line);
    }
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_dec(void* data, bool new_line)
{
    _print_dec((unsigned int)data, new_line);
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_dec(int data, bool new_line)
{
    if(data<0)
    {
        _write_byte('-');
        _print_dec(~data + 1, new_line);
    }
    else
    {
        _print_dec(data, new_line);
    }
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_dec(long data, bool new_line)
{
    if(data<0)
    {
        _write_byte('-');
        _print_dec(~data + 1, new_line);
    }
    else
    {
        _print_dec(data, new_line);
    }
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_dec(unsigned char data, bool new_line)
{
    _print_dec(data, new_line);
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_dec(unsigned int data, bool new_line)
{
    _print_dec(data, new_line);
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_dec(unsigned long data, bool new_line)
{
    _print_dec(data, new_line);
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_hex(char data)
{
    debug_print_hex1(data);
    _endl();
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_hex(int data)
{
    _print_hexN(data, 2);
    _endl();
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_hex(long int data)
{
    _print_hexN(data, 4);
    _endl();
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_hex(unsigned char data)
{
    debug_print_hex1(data);
    _endl();
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_hex(void* data, bool new_line)
{
    _print_hexN((unsigned int)data, 2);
    if(new_line) _endl();
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_hex(unsigned int data, bool new_line)
{
    _print_hexN(data, 2);
    if(new_line) _endl();
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_hex(unsigned long int data)
{
    _print_hexN(data, 4);
    _endl();
}
//-----------------------------------------------------------------------------
void DEBUG_SECTION debug_print_hex8(BYTE count, ...)
{
    va_list list;
    va_start(list, count);
    while(count-- > 0)
    {
        debug_print_hex1((char)va_arg(list, int));
        _write_byte(' ');
    }
    _endl();
}
//-----------------------------------------------------------------------------
#endif
