//-----------------------------------------------------------------------------
#include "debug.h"
#include "RAM_guard.h"
#ifdef DEBUG
//-----------------------------------------------------------------------------
struct __free_list
{
	WORD sz;
	__free_list* nx;
};
//-----------------------------------------------------------------------------
extern int __data_start;
extern int __data_end;
extern int __bss_start;
extern int __bss_end;
extern int __heap_start;
extern void* __brkval;
extern __free_list*  __flp;
//-----------------------------------------------------------------------------
__inline void align_dec(WORD value)
{
    for(WORD reg = 10000; reg > 1; reg /= 10)
    {
        if(value < reg)
        {
            DSTRN(" ");
        }
    }
}
//-----------------------------------------------------------------------------
#define debug_print_dec_aligned(value) align_dec(value); debug_print_dec(value);
#define RAM_GUARD_MAGIC_NUM     0xFEFEFEFE
#ifdef RAM_GUARD_ENABLED
//-----------------------------------------------------------------------------
void init()
{
    // prefill whole the RAM with a magic 0xFE
    for(volatile register BYTE* ptr = (BYTE*)RAMSTART; ptr < (BYTE*)RAMEND; ptr++)
    {
        *ptr = RAM_GUARD_MAGIC_NUM >> 24;
    }
}
//-----------------------------------------------------------------------------
void memory_usage()
{
    DSTR("");
    DSTR("===================");
    DSTR("     RAM USAGE");
    DSTR("===================");

    // .data section size
    DSTRN(".data   ");
    debug_print_hex((WORD) &__data_start, false);
    DSTRN("  ");
    WORD data = (WORD) &__data_end - (WORD) &__data_start;
    debug_print_dec_aligned(data);

    // .bss section size
    DSTRN(".bss    ");
    debug_print_hex((WORD) &__bss_start, false);
    DSTRN("  ");
    WORD bss = (WORD) &__bss_end - (WORD) &__bss_start;
    debug_print_dec_aligned(bss);


    // heap size
    WORD heap = 0;
    DSTRN("heap    ");
    debug_print_hex((WORD)&__heap_start, false);
    DSTRN("  ");
    if(__brkval)
    {
        heap = (WORD)__brkval - (WORD)&__heap_start;
    }
    debug_print_dec_aligned(heap);

    // stack depth
    DSTRN("stack   ");
    DWORD tracker = 0;
    BYTE found = false;
    volatile register BYTE* ptr = (BYTE*)RAMEND;
    while(ptr-- > (BYTE*)RAMSTART)
    {
        tracker = (tracker << 8) | *ptr;
        if(tracker == RAM_GUARD_MAGIC_NUM)
        {
            found = true;
            break;
        }
    }
    WORD stack = 0;
    if(found)
    {
        stack = RAMEND - (WORD) ptr - sizeof(tracker);
    }
    debug_print_hex((WORD) ptr + sizeof(tracker), false);
    DSTRN("  ");
    debug_print_dec_aligned(stack);
    DSTR("-------------------");

    // total RAM used
    DSTRN("total         ");
    WORD total = data + bss + heap + stack;
    debug_print_dec_aligned(total);

    // free RAM
    DSTRN("free          ");
    WORD free = RAMEND - RAMSTART - total;
    debug_print_dec_aligned(free);
}
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
void heap_info()
{
    DSTR("");
    DSTR("=======================");
    DSTR("       HEAP INFO");
    DSTR("=======================");

    BYTE* ptr = (BYTE*)&__heap_start;
    struct __free_list* fp = __flp;
    DSTR("PTR      SIZE    STATUS");
    while(ptr < __brkval)
    {
        void* data = ptr + 2;
        WORD size = *(WORD*) ptr;
        debug_print_hex(data, false);
        DSTRN("    ");
        align_dec(size);
        debug_print_dec(size, false);
        if((WORD)ptr == (WORD)fp)
        {
            DSTR("     freed");
            fp = fp->nx;
        }
        else
        {
            DSTR("     alloc");
        }
        ptr += (2 + size);
    }
}
//-----------------------------------------------------------------------------
#endif
