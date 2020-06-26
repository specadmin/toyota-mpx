//-----------------------------------------------------------------------------
// MPX.cpp
//-----------------------------------------------------------------------------
#include "avr-misc/avr-misc.h"
#include "mpx.h"
#include "config.h"
#include "mpx_config.h"
#include "../avr-debug/debug.h"
//-----------------------------------------------------------------------------
static BYTE queue_head = 0;     // queue write index
static BYTE queue_tail = 0;     // queue read index
static BYTE queue[MPX_QUEUE_SIZE][MPX_MAX_PACKET_SIZE];
//-----------------------------------------------------------------------------
static struct
{
    bool idle;
} bus;
//-----------------------------------------------------------------------------
static struct
{
    BYTE buf[MPX_MAX_FRAME_SIZE];
    BYTE size;
    BYTE crc;
    volatile BYTE byte;
    BYTE bit;
    bool busy;
    BYTE same_bit_counter;
    void (*callback)(BYTE size, const BYTE* buf);
} rx;
//-----------------------------------------------------------------------------
static struct
{
    BYTE buf[MPX_MAX_FRAME_SIZE];
    BYTE size;
    BYTE pos;
    BYTE shift;
    volatile BYTE state;
    BYTE result;
    void (*callback)(BYTE result);
} tx;
//-----------------------------------------------------------------------------
static struct
{
    BYTE counter;
    BYTE prev;
} stuffing;
//-----------------------------------------------------------------------------
__inline void start_timer()
{
    MPX_TIMER_TCNT = 0;
    MPX_TIMER_TCCRB |= _bit(MPX_TIMER_CS1);
    set_bit(TIFR0, OCF0A);
}
//-----------------------------------------------------------------------------
__inline void stop_timer()
{
    MPX_TIMER_TCCRB &= ~_bit(MPX_TIMER_CS1);
}
//-----------------------------------------------------------------------------
__inline void half_bit_timer()
{
    MPX_TIMER_OCRA = F_CPU / 8 / MPX_BAUD_RATE / 2 - 1;
}
//-----------------------------------------------------------------------------
__inline void full_bit_timer()
{
    MPX_TIMER_OCRA = F_CPU / 8 / MPX_BAUD_RATE - 1;
}
//-----------------------------------------------------------------------------
__inline void resync_timer()
{
    MPX_TIMER_TCNT = 0;
    half_bit_timer();
    MPX_TIMER_TCCRB |= _bit(MPX_TIMER_CS1);
    set_bit(TIFR0, OCF0A);
}
//-----------------------------------------------------------------------------
__inline void stuffing_reset()
{
    stuffing.counter = 0;
};
//-----------------------------------------------------------------------------
/**
 * @brief Registers the bit and determines whether it is a stuffing bit
 * @param value - bit value
 * @return 1 - the bit is a stuffing bit and should be skipped in receiption
 */
__inline BYTE stuffing_push(BYTE value)
{
    value = (value > 0) ? 1 : 0;
    if(value == stuffing.prev)
    {
        stuffing.counter++;
        return 0;
    }
    volatile register BYTE res = 0;
    if(stuffing.counter == 5)
    {
        // stuffing bit detected
        res = 1;
    }
    stuffing.counter = 1;
    stuffing.prev = value;
    return res;
}
//-----------------------------------------------------------------------------
/**
 * @brief Checks whether the stuffing bit is needed after the previous push for
 * transmission
 * @return 1 - stuffing bit should be the next
 */
__inline BYTE stuffing_check()
{
    return (stuffing.counter >= 5);
}
//-----------------------------------------------------------------------------
/**
 * @brief Returns the value (polarity) of the following stuffing bit
 */
__inline BYTE stuffing_bit()
{
    stuffing.counter = 1;
    stuffing.prev = (stuffing.prev > 0) ? 0 : 1;  // stuffing bit is an inverted bit
    return stuffing.prev;
}
//-----------------------------------------------------------------------------
/**
 * @brief Checks whether the driver controls the MPX bus during transmission
 * @return true - The driver has lost the control of the bus, another device is
 * transmitting a message with a greater priority or higher message-id
 */
__inline bool arbitration_lost()
{
    return (!test_bit(MPX_TX_PORT, MPX_TX_BIT) && RX_PIN);
}
//-----------------------------------------------------------------------------
__inline void rx_reset()
{
    rx.size = 0;
    rx.crc = 0;
    rx.byte = 0;
    rx.bit = 0;
    stuffing_reset();
}
//-----------------------------------------------------------------------------
__inline BYTE CRC8(const BYTE* buf, BYTE size)
{
    BYTE crc = 0;
    while(size--)
    {
        crc = CRC8_table[crc ^ *buf++];
    }
    return crc;
}
//-----------------------------------------------------------------------------
__inline void suspend_transmission()
{
    // suspend the transmission
    clr_bit(MPX_TX_PORT, MPX_TX_BIT);
    tx.state = TX_QUEUED;
    MPX_TX_LED_OFF();

    // and continue receiption
    MPX_RX_LED_ON();
    rx.busy = true;

    // restore skipped data
    volatile register BYTE size = tx.pos;
    memcpy(rx.buf, tx.buf, size);
    rx.crc = CRC8(rx.buf, size);
    rx.bit = tx.shift - 1;
    rx.byte = tx.buf[size] >> (9 - tx.shift);
    rx.size = size;
}
//-----------------------------------------------------------------------------
__inline void start_transmission()
{
    if(!RX_PIN)
    {
        // start of frame (a start bit)
        MPX_HW_DEBUG_ON();
        tx.pos = 0;
        tx.shift = 0;
        stuffing_reset();
        stuffing_push(1);
        tx.state = TX_IN_PROGRESS;
        set_bit(MPX_TX_PORT, MPX_TX_BIT);
        full_bit_timer();
        start_timer();
        MPX_HW_DEBUG_OFF();
    }
}
//-----------------------------------------------------------------------------
__inline void get_bit()
{
    static BYTE EOM = 0;
    EOM = EOM << 1 | RX_PIN;
    if(EOM == 0x7E)
    {
        // end-of-message detected
        rx.buf[rx.size++] = 0x7E;
        if(!rx.crc)
        {
            // if received CRC and calculated CRC are equal, then
            // the result CRC should be zero
            if(rx.callback)
            {
                rx.callback(rx.size, rx.buf);
            }
        }
        rx_reset();
        return;
    }

    if(!rx.busy && RX_PIN)
    {
        // start bit detected
        MPX_RX_LED_ON();
        rx_reset();
        rx.busy = true;
        return;
    }

    if(stuffing_push(RX_PIN))
    {
        // skip stuffing-bit
        return;
    }

    rx.byte = rx.byte << 1 | RX_PIN;
    if(++rx.bit >= 8)
    {
        // byte reception completed
        rx.bit = 0;
        rx.buf[rx.size++] = rx.byte;
        rx.crc = CRC8_table[rx.crc ^ rx.byte];
    }
}
//-----------------------------------------------------------------------------
__inline void send_bit()
{
    volatile register BYTE value = 0;

    if(tx.pos < tx.size && stuffing_check())
    {
        if(stuffing_bit())
            set_bit(MPX_TX_PORT, MPX_TX_BIT);
        else
            clr_bit(MPX_TX_PORT, MPX_TX_BIT);
        return;
    }

    if(tx.pos <= tx.size)
    {
        // various data (from priority to CRC)
        value = (tx.buf[tx.pos] << tx.shift) & 0x80;
        // set bit value as soon as possible
        if(value)
        {
            set_bit(MPX_TX_PORT, MPX_TX_BIT);
        }
        else
        {
            clr_bit(MPX_TX_PORT, MPX_TX_BIT);
        }
        if(++tx.shift >= 8)
        {
            tx.pos++;
            tx.shift = 0;
        }
        if(value)
        {
            set_bit(MPX_TX_PORT, MPX_TX_BIT);
            stuffing_push(1);
        }
        else
        {
            clr_bit(MPX_TX_PORT, MPX_TX_BIT);
            // prepare arbitration check
            half_bit_timer();
            tx.state = TX_ARBITRATION;
        }
    }
    else
    {
        switch(tx.shift++)
        {
        case 0:
            // prepare to receive checksum and acknowlegement reply
            resync_timer();
            tx.state = TX_ACKNOWLEGEMENT;
            // prevent detecting acknowlegement as a start bit
            rx.busy = true;
            break;
        case 1:
            // checksum reply
            tx.result = RX_PIN << 1;
            break;
        case 2:
            // acknowlegement reply
            tx.result = (tx.result | RX_PIN);
            break;
        case 3:
            // resync back into transmission mode
            resync_timer();
            if(!RX_PIN)
            {
                tx.result = tx.result << 1 | 1;
                //** tx.result values
                // "001" = 1 -- NACK
                // "011" = 3 -- ACK
                // "111" = 7 -- BAD CRC
            }
            else
            {
                // unexpected bus level
                tx.result = MPX_ERR_UNKNOWN;
            }

            // transmission completed
            MPX_TX_LED_OFF();
            tx.state = TX_IDLE;
            if(tx.callback)
            {
                tx.callback(tx.result);
            }
            rx.busy = false;
            break;
        }
    }
}
//-----------------------------------------------------------------------------
ISR(MPX_RX_INT_VECT)
{
    MPX_HW_DEBUG_ON();

    // resync the timer
    if(tx.state == TX_IN_PROGRESS)      // do not resync while transmission is in progress
    {
        full_bit_timer();
        start_timer();
    }
    else
    {
        resync_timer();
    }
    bus.idle = false;
    if(tx.state == TX_IN_PROGRESS && arbitration_lost())
    {
        //MPX_HW_DEBUG_SYNC();
        resync_timer();
        suspend_transmission();
    }
    // continue further receiption
    rx.same_bit_counter = 0;

    MPX_HW_DEBUG_OFF();
}
//-----------------------------------------------------------------------------
ISR(MPX_TIMER_VECT)
{
    MPX_HW_DEBUG_ON();
    // change the timer interval to full-bit value
    full_bit_timer();
    switch(tx.state)
    {
    case TX_ARBITRATION:
        if(arbitration_lost())
        {
            suspend_transmission();
            get_bit();
        }
        else
        {
            // arbitration is OK, continue the transmission
            stuffing_push(0);
            tx.state = TX_IN_PROGRESS;
            half_bit_timer();
        }
        break;
    case TX_IN_PROGRESS:
    case TX_ACKNOWLEGEMENT:
        // transmission mode
        send_bit();
        break;
    default:
        // receiption mode
        if(++rx.same_bit_counter > 6)
        {
            // idle state detected
            bus.idle = true;
            rx.busy = false;
            MPX_RX_LED_OFF();
            rx.same_bit_counter = 0;
            if(tx.state == TX_QUEUED)
            {
                // a packet is waiting for transmission
                start_transmission();
            }
            else
            {
                // go to idle mode
                stop_timer();
            }
        }
        else
        {
            get_bit();
        }
    }
    MPX_HW_DEBUG_OFF();
}
//-----------------------------------------------------------------------------
void mpx_init(void (*rx_callback)(BYTE size, const BYTE* buf))
{
    rx.callback = rx_callback;
    set_bit(MPX_TX_DIR, MPX_TX_BIT);

    bus.idle = true;
    rx.busy = false;
    tx.state = TX_IDLE;
    stuffing.counter = 0;
    stuffing.prev = 0;

    #ifdef MPX_RX_LED_PORT
    set_bit(MPX_RX_LED_DIR, MPX_RX_LED_BIT);
    #endif

    #ifdef HW_DEBUG_PORT
    set_bit(HW_DEBUG_DIR, HW_DEBUG_BIT);
    #endif

    #ifdef HW_DEBUG_SYNC_PORT
    set_bit(HW_DEBUG_SYNC_DIR, HW_DEBUG_SYNC_BIT);
    #endif

    MPX_TIMER_TCCRA = _bit(MPX_TIMER_WGM_CTC);    // CTC (clear timer on compare) mode
    set_bit(MPX_TIMER_TIMSK, MPX_TIMER_OCIEA);       // enable timer compare match interrupt

    // keep in sync, correcting the timer on every level change
    set_bit(EICRA, MPX_RX_ISC0);
    clr_bit(EICRA, MPX_RX_ISC1);

    // enable receiption interrupt
    set_bit(EIFR, INTF0);   // reset pending interrupt call
    set_bit(EIMSK, INT0);
}
//-----------------------------------------------------------------------------
BYTE mpx_send(BYTE priority, BYTE address, BYTE size, const BYTE* data, void (*callback)(BYTE result))
{
    if(tx.state != TX_IDLE)
    {
        return MPX_ERR_BUSY;
    }
    if((priority > 15) || (size < 2) || (size > MPX_MAX_DATA_SIZE + 1))
    {
        // valid priority range: 0...15
        // valid size range: 2...12 (includes message id)
        return MPX_ERR_BAD_PARAMETER;
    }
    // priority and size
    tx.buf[0] = (priority << 4) | (size + 1);

    // destination address
    tx.buf[1] = address;

    // data
    memcpy(tx.buf + 2, data, size);

    // CRC
    tx.buf[size + 2] = CRC8(tx.buf, size + 2);

    // EOM
    tx.buf[size + 3] = 0x7E;

    tx.size = size + 3;
    tx.callback = callback;
    tx.state = TX_QUEUED;

    if(bus.idle)
    {
        start_transmission();
    }
    return MPX_ERR_QUEUED;
}
//-----------------------------------------------------------------------------
#define mpx_queue_is_empty()        (queue_head == queue_tail)
#define mpx_queue_is_not_empty()    (queue_head != queue_tail)
//-----------------------------------------------------------------------------
void mpx_queue_check(__unused BYTE result)
{
    if(mpx_queue_is_not_empty())
    {
        BYTE index = queue_tail;
        queue_tail = (queue_tail + 1) % MPX_QUEUE_SIZE;
        mpx_send(queue[index][0], queue[index][1], queue[index][2], queue[index] + 3, mpx_queue_check);
    }
}
//-----------------------------------------------------------------------------
BYTE mpx_queue(BYTE priority, BYTE address, BYTE size, const BYTE* data)
{
    BYTE result = 0;
    if(mpx_queue_is_empty() && tx.state == TX_IDLE)
    {
        result = mpx_send(priority, address, size, data, mpx_queue_check);
    }
    else
    {
        disable_interrupts();
        BYTE next_index = (queue_head + 1) % MPX_QUEUE_SIZE;
        if(next_index == queue_tail)
        {
            // step on self tail
            result = MPX_ERR_QUEUE_OVERFLOW;
        }
        else
        {
            queue[queue_head][0] = priority;
            queue[queue_head][1] = address;
            queue[queue_head][2] = size;
            memcpy(queue[queue_head] + 3, data, size);
            queue_head = next_index;
        }
        resume_interrupts();
    }
    return result;
}
//-----------------------------------------------------------------------------
BYTE mpx_CRC8(const BYTE* buf, BYTE size)
{
    return CRC8(buf, size);
}
//-----------------------------------------------------------------------------
