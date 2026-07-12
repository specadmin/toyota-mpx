#ifndef DEBUG_H
#define DEBUG_H
//-----------------------------------------------------------------------------
#include "config.h"
//-----------------------------------------------------------------------------


// DESCRIPTION
/******************************************************************************

  Single-wire UART console library for sending debug info from AVR device

  See Readme.md for instructions

  https://github.com/specadmin/avr-debug

******************************************************************************/


// CONFIGURATION FILE OPTIONS
/******************************************************************************



******************************************************************************/


//-----------------------------------------------------------------------------
#include "RAM_guard.h"
#ifdef DEBUG
    #include "debug_def.h"
#else
    #define DEBUG_INIT()
    #define DSTR(str)
    #define DSTRN(str)
    #define DUMP_MEM(ptr,size)
    #define DREG(reg)
    #define DNUM(var)
    #define DHEX(var)
    #define DHEX8(count, ...)
#endif
//-----------------------------------------------------------------------------
#endif
