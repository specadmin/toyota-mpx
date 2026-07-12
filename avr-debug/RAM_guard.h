#ifndef RAM_GUARD_H
#define RAM_GUARD_H
//-----------------------------------------------------------------------------
void heap_info();
//-----------------------------------------------------------------------------
#ifdef RAM_GUARD_ENABLED
void init() __attribute__ ((section(".init0"), naked));
void memory_usage();
#else
#define memory_usage()
#endif
//-----------------------------------------------------------------------------
#endif
