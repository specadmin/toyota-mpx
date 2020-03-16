//-----------------------------------------------------------------------------
#include <stdlib.h>
#include "lib/avr-misc/avr-misc.h"
#include "lib/avr-debug/debug.h"
#include "lib/toyota-mpx/mpx.h"
//-----------------------------------------------------------------------------
void mpx_callback(BYTE size, const BYTE* buf);
//-----------------------------------------------------------------------------
int main()
{
    DEBUG_INIT();

    mpx_init(&mpx_callback);


    mdelay(100);
    enable_interrupts();

    while(1)
    {
        // BYTE buf[] = { 0x2C, 160 }; mpx_send(5, 0xFE, sizeof(buf), buf); // engine temperature
        BYTE buf[] = { 0xd3, 0x20 }; mpx_send(6, 0x46, sizeof(buf), buf); //
        //BYTE buf[] = { 0xd2, 0x30, 0x00, 0x00 }; mpx_send(6, 0xFE, sizeof(buf), buf); //
         //BYTE buf[] = { 0xe6, 0x71, 0xB9, 0x00 }; mpx_send(5, 0xFE, sizeof(buf), buf); //
         //BYTE buf[] = { 0xe4, 0x05, 0xFF }; mpx_send(5, 0xFE, sizeof(buf), buf); //
        //BYTE buf[] = { 0xdf, 0x20, 0x00, 0x00, 0x80, 0x00, 0x00 }; mpx_send(6, 0xFE, sizeof(buf), buf); //
        mdelay(27);
    }


    return 0;
}
//-----------------------------------------------------------------------------
void mpx_callback(__unused BYTE size, __unused const BYTE* buf)
{
    //DUMP_MEM(buf, size);
}
//-----------------------------------------------------------------------------
