#ifndef AVR_MISC_INTERRUPTS_H
#define AVR_MISC_INTERRUPTS_H
//-----------------------------------------------------------------------------
#include <avr/interrupt.h>
//-----------------------------------------------------------------------------
#define enable_interrupts() __asm__ volatile ("sei")
#define disable_interrupts() { _sreg=SREG; __asm__ volatile ("cli"); }
#define resume_interrupts() { SREG=_sreg; }
//-----------------------------------------------------------------------------
extern unsigned char _sreg;
//-----------------------------------------------------------------------------
#endif
