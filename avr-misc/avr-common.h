#ifndef AVR_MISC_COMMON_H
#define AVR_MISC_COMMON_H
//-----------------------------------------------------------------------------
#define __inline inline __attribute__ ((always_inline))
#define __unused __attribute__ ((unused))
#define nop() __asm__ volatile ("nop")
#define halt() while(1);
//-----------------------------------------------------------------------------
#define _0      0
#define FALSE   0
#define TRUE    1
#define KB      1024
#define MB      1048576ULL
#define KHZ     1000
#define MHZ     1000000ULL
//-----------------------------------------------------------------------------
typedef unsigned char BYTE;
typedef unsigned int WORD;
typedef unsigned long DWORD;
//-----------------------------------------------------------------------------
union WORD_UNION
{
    WORD data;
    BYTE byte[2];
};
//-----------------------------------------------------------------------------
union DWORD_UNION
{
    DWORD data;
    WORD word[2];
    BYTE byte[4];
};
//-----------------------------------------------------------------------------
#endif
