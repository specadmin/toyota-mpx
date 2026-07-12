#ifndef AVR_MISC_DELAY_H
#define AVR_MISC_DELAY_H
//-----------------------------------------------------------------------------
#include <util/delay.h>
//-----------------------------------------------------------------------------
#define delay_cycles(a) __builtin_avr_delay_cycles(a)
#define delay(sec)      _delay_ms(1000*sec)
#define mdelay(ms)      _delay_ms(ms)
#define udelay(us)      _delay_us(us)
//-----------------------------------------------------------------------------
#endif
