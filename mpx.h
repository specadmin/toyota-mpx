#ifndef MPX_H
#define MPX_H
//-----------------------------------------------------------------------------
#include <string.h>
#include "../avr-misc/avr-misc.h"
//-----------------------------------------------------------------------------
enum mpx_result
{
    MPX_ERR_QUEUED  = 0,        // the message was queued for delivery
    MPX_ERR_NACK    = 1,        // the message was sent, but no acknowledgement received
    MPX_ERR_ACK     = 3,        // the message was sent and acknowledgement received
    MPX_ERR_UNKNOWN = 4,        // an unknown error has happened during the transmission
    MPX_ERR_CRC     = 7,        // the message was sent, but recepient reported a checksum error
    MPX_ERR_BUSY,               // the interface is busy by processing a previous call
    MPX_ERR_BAD_PARAMETER,      // a bad parameter was specified in a function call
    MPX_ERR_QUEUE_OVERFLOW      // no free slots left in the queue
};
//-----------------------------------------------------------------------------
/**
 * @brief Initializes the the driver
 * @param rx_callback - a function to be called, when the packet is received.
 * The driver performs checksum calculation and comparison. The function will
 * be called only when the checksum is correct. Packets with incorrect checksum
 * will be omitted and the fuction will not be called for those packets.
 * This function should be as fast as possible, since it is called in the
 * interrupt routing and other interrupts proccessing are hold, while this
 * function is being executed. A slow function could cause data lost in your
 * MPX driver. The function receives two parameters: size - the size of the
 * received packet; buf - a pointer to the buffer, that contains the received
 * packet. Callback function should copy the buffer's content for further
 * processing. After the callback function returns the buffer can be used by the
 * driver for receiving the next packet. You may set this parameter to NULL if
 * you do not need to receive any packets.
 */
void mpx_init(void (*rx_callback)(BYTE size, const BYTE* buf));
//-----------------------------------------------------------------------------
/**
 * @brief Sends a packet into the MPX network
 * @param priority - a packet priority (0...15); a higher value means a higher
 * priority. If two devices start transmiting packets at the same time, then
 * the packet with a greater priority will be transmitted and the packet with a
 * lower priority will be delayed. If both of those packets has the same
 * priority, then the packet with a greater size will be transmitted. If
 * priorities and sizes are the same, then the packet with higher destination
 * address will be transmited, etc.
 * @param address - destination device address.
 * @param data - a pointer to the buffer, that contains data to be sent. The
 * first byte of the buffer must contain message-id and the other bytes
 * must contain message data. You should not matter about the checksum, since
 * the driver will calculate it automatically and will insert it into the packet.
 * @param size - the number of bytes (2...12) to be sent from the data buffer.
 * @param callback - a function to be called, when the packet will be
 * transmitted. The parameter could be set to NULL or ommited, if you don't need
 * it. This function should be as fast as possible, since it is called in the
 * interrupt routing and other interrupts proccessing are hold while this
 * function is being executed. A slow function could cause data lost in your
 * MPX driver. The function receives the only parameter, that indicates the
 * result of the transmission (ACK, NACK or bad CRC).
 * @return Returns MPX_ERR_QUEUED, MPX_ERR_BUSY or MPX_ERR_BAD_PARAMETER (see
 * the codes description above).
 */
BYTE mpx_send(BYTE priority, BYTE address, BYTE size, const BYTE* data, void (*callback)(BYTE result) = NULL);
//-----------------------------------------------------------------------------
/**
 * @brief Queue a packet for sending. This method adds a packet into the queue
 * for further delivery. The queue is beeing processed for sending automatically.
 * If the driver is not busy, then the transmission will be started immediately.
 * @param priority - a packet priority (0...15); a higher value means a higher
 * priority. If two devices start transmiting packets at the same time, then
 * the packet with a greater priority will be transmitted and the packet with a
 * lower priority will be delayed. If both of those packets has the same
 * priority, then the packet with a greater size will be transmitted. If
 * priorities and sizes are the same, then the packet with higher destination
 * address will be transmited, etc.
 * @param address - destination device address.
 * @param data - a pointer to the buffer, that contains data to be sent. The
 * first byte of the buffer must contain message-id and the other bytes
 * must contain message data. You should not matter about the checksum, since
 * the driver will calculate it automatically and will insert it into the packet.
 * @param size - the number of bytes (2...12) to be sent from the data buffer.
 * @return Returns MPX_ERR_QUEUED, MPX_ERR_QUEUE_OVERFLOW or
 * MPX_ERR_BAD_PARAMETER (see the codes description above).
 */
BYTE mpx_queue(BYTE priority, BYTE address, BYTE size, const BYTE* data);
//-----------------------------------------------------------------------------
/**
 * @brief Calculates MPX packet checksum
 * @param buf - a pointer to the buffer, that contains MPX packet
 * @param size - the number of bytes in the buffer, that will be used for
 * calculating checksum
 */
BYTE mpx_CRC8(const BYTE* buf, BYTE size);
//-----------------------------------------------------------------------------
#endif
