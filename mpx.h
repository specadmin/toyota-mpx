#ifndef MPX_H
#define MPX_H
//-----------------------------------------------------------------------------
#include "../lib/avr-misc/avr-misc.h"
//-----------------------------------------------------------------------------
enum mpx_result
{
    MPX_ERR_QUEUED = 0,     // message was queued for delivery
    MPX_ERR_NACK = 1,       // message was sent, but no acknowledgement received
    MPX_ERR_ACK = 3,        // message was sent and acknowledgement received
    MPX_ERR_CRC = 7,        // message was sent, but recepient reported a checksum error
    MPX_ERR_BUSY,           // the interface is busy by processing a previous call
    MPX_ERR_BAD_PARAMETER,  // a bad parameter was specified in a function call
};
//-----------------------------------------------------------------------------
void mpx_init(void (*rx_callback)(BYTE size, const BYTE* buf));
BYTE mpx_send(BYTE priority, BYTE address, BYTE size, const BYTE* data, void (*callback)(BYTE result) = NULL);
//-----------------------------------------------------------------------------
#endif
