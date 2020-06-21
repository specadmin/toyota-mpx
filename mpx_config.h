#ifndef MPX_CONFIG_H
#define MPX_CONFIG_H
//-----------------------------------------------------------------------------

#define MPX_BAUD_RATE           10000
#define MPX_MAX_PACKET_SIZE     15      // PRI + ML + DST-ID + MSG-ID + DATA

#ifndef MPX_TIMER_ID
#error Please define MPX_TIMER_ID (0 or 2 for ATmega devices)
#endif

// MPX timer
#define MPX_TIMER_VECT          CONCAT(CONCAT(TIMER, MPX_TIMER_ID), _COMPA_vect)
#define MPX_TIMER_TCCRA         CONCAT(CONCAT(TCCR, MPX_TIMER_ID), A)
#define MPX_TIMER_TCCRB         CONCAT(CONCAT(TCCR, MPX_TIMER_ID), B)
#define MPX_TIMER_TIMSK         CONCAT(TIMSK, MPX_TIMER_ID)
#define MPX_TIMER_OCRA          CONCAT(CONCAT(OCR, MPX_TIMER_ID), A)
#define MPX_TIMER_TCNT          CONCAT(TCNT, MPX_TIMER_ID)
#define MPX_TIMER_TIFR          CONCAT(TIFR, MPX_TIMER_ID)
#define MPX_TIMER_WGM_CTC       CONCAT(CONCAT(WGM, MPX_TIMER_ID), 1)
#define MPX_TIMER_CS0           CONCAT(CONCAT(CS, MPX_TIMER_ID), 0)
#define MPX_TIMER_CS1           CONCAT(CONCAT(CS, MPX_TIMER_ID), 1)
#define MPX_TIMER_OCIEA         CONCAT(CONCAT(OCIE, MPX_TIMER_ID), A)

/*===========================================================================
  Hardware debugger configuration
  ===========================================================================*/

//#define HW_DEBUG_PORT           PORTD
//#define HW_DEBUG_DIR            DDRD
//#define HW_DEBUG_BIT            6
//
//#define HW_DEBUG_SYNC_PORT      PORTC
//#define HW_DEBUG_SYNC_DIR       DDRC
//#define HW_DEBUG_SYNC_BIT       5

#ifdef HW_DEBUG_PORT
    #define MPX_HW_DEBUG_ON()       { set_bit(HW_DEBUG_PORT, HW_DEBUG_BIT); }
    #define MPX_HW_DEBUG_OFF()      { clr_bit(HW_DEBUG_PORT, HW_DEBUG_BIT);}
    #define MPX_HW_DEBUG(us)        { MPX_HW_DEBUG_ON(); udelay(us); MPX_HW_DEBUG_OFF(); }
    #define MPX_HW_DEBUG_SYNC()     { set_bit(HW_DEBUG_SYNC_PORT, HW_DEBUG_SYNC_BIT); udelay(2); clr_bit(HW_DEBUG_SYNC_PORT, HW_DEBUG_SYNC_BIT); }
#else
    #define MPX_HW_DEBUG_ON()
    #define MPX_HW_DEBUG_OFF()
    #define MPX_HW_DEBUG(us)
    #define MPX_HW_DEBUG_SYNC()
#endif
//-----------------------------------------------------------------------------
#ifdef MPX_RX_LED_PORT
#define MPX_RX_LED_ON()    set_bit(MPX_RX_LED_PORT, MPX_RX_LED_BIT);
#define MPX_RX_LED_OFF()   clr_bit(MPX_RX_LED_PORT, MPX_RX_LED_BIT);
#else
#define MPX_RX_LED_ON()
#define MPX_RX_LED_OFF()
#endif
//-----------------------------------------------------------------------------
#ifdef MPX_TX_LED_PORT
#define MPX_TX_LED_ON()    set_bit(MPX_TX_LED_PORT, MPX_TX_LED_BIT);
#define MPX_TX_LED_OFF()   clr_bit(MPX_TX_LED_PORT, MPX_TX_LED_BIT);
#else
#define MPX_TX_LED_ON()
#define MPX_TX_LED_OFF()
#endif
//-----------------------------------------------------------------------------
#define MPX_HEADER_SIZE    2
#define MPX_MAX_DATA_SIZE  11
#define MPX_MAX_FRAME_SIZE  (MPX_HEADER_SIZE + MPX_MAX_DATA_SIZE + 1 + 1)
//-----------------------------------------------------------------------------
#define RX_PIN (test_bit(MPX_RX_PIN, MPX_RX_BIT))
//-----------------------------------------------------------------------------
#ifndef MPX_QUEUE_SIZE
#define MPX_QUEUE_SIZE  16
#endif
//-----------------------------------------------------------------------------
enum
{
    TX_IDLE = 0,
    TX_QUEUED,
    TX_START,
    TX_IN_PROGRESS,
    TX_ARBITRATION,
    TX_ACKNOWLEGEMENT
};
//-----------------------------------------------------------------------------
const BYTE CRC8_table[256] = {
  0x00, 0x13, 0x26, 0x35, 0x4C, 0x5F, 0x6A, 0x79,
  0x98, 0x8B, 0xBE, 0xAD, 0xD4, 0xC7, 0xF2, 0xE1,
  0x23, 0x30, 0x05, 0x16, 0x6F, 0x7C, 0x49, 0x5A,
  0xBB, 0xA8, 0x9D, 0x8E, 0xF7, 0xE4, 0xD1, 0xC2,
  0x46, 0x55, 0x60, 0x73, 0x0A, 0x19, 0x2C, 0x3F,
  0xDE, 0xCD, 0xF8, 0xEB, 0x92, 0x81, 0xB4, 0xA7,
  0x65, 0x76, 0x43, 0x50, 0x29, 0x3A, 0x0F, 0x1C,
  0xFD, 0xEE, 0xDB, 0xC8, 0xB1, 0xA2, 0x97, 0x84,
  0x8C, 0x9F, 0xAA, 0xB9, 0xC0, 0xD3, 0xE6, 0xF5,
  0x14, 0x07, 0x32, 0x21, 0x58, 0x4B, 0x7E, 0x6D,
  0xAF, 0xBC, 0x89, 0x9A, 0xE3, 0xF0, 0xC5, 0xD6,
  0x37, 0x24, 0x11, 0x02 ,0x7B, 0x68, 0x5D, 0x4E,
  0xCA, 0xD9, 0xEC, 0xFF, 0x86, 0x95, 0xA0, 0xB3,
  0x52, 0x41, 0x74, 0x67 ,0x1E, 0x0D, 0x38, 0x2B,
  0xE9, 0xFA, 0xCF, 0xDC, 0xA5, 0xB6, 0x83, 0x90,
  0x71 ,0x62, 0x57, 0x44 ,0x3D, 0x2E, 0x1B, 0x08,
  0x0B, 0x18, 0x2D, 0x3E, 0x47, 0x54, 0x61, 0x72,
  0x93, 0x80, 0xB5, 0xA6, 0xDF, 0xCC, 0xF9, 0xEA,
  0x28, 0x3B, 0x0E, 0x1D, 0x64, 0x77, 0x42, 0x51,
  0xB0, 0xA3, 0x96, 0x85, 0xFC, 0xEF, 0xDA, 0xC9,
  0x4D, 0x5E, 0x6B, 0x78, 0x01, 0x12, 0x27, 0x34,
  0xD5, 0xC6, 0xF3, 0xE0, 0x99, 0x8A, 0xBF, 0xAC,
  0x6E, 0x7D, 0x48, 0x5B, 0x22, 0x31, 0x04, 0x17,
  0xF6, 0xE5, 0xD0, 0xC3 ,0xBA, 0xA9, 0x9C, 0x8F,
  0x87, 0x94, 0xA1, 0xB2, 0xCB, 0xD8, 0xED, 0xFE,
  0x1F ,0x0C, 0x39, 0x2A ,0x53, 0x40, 0x75, 0x66,
  0xA4, 0xB7, 0x82, 0x91, 0xE8, 0xFB, 0xCE, 0xDD,
  0x3C ,0x2F, 0x1A, 0x09 ,0x70, 0x63, 0x56, 0x45,
  0xC1, 0xD2, 0xE7, 0xF4, 0x8D, 0x9E, 0xAB, 0xB8,
  0x59, 0x4A, 0x7F, 0x6C, 0x15, 0x06, 0x33, 0x20,
  0xE2, 0xF1, 0xC4, 0xD7, 0xAE, 0xBD, 0x88, 0x9B,
  0x7A, 0x69, 0x5C ,0x4F ,0x36, 0x25, 0x10, 0x03
};
//-----------------------------------------------------------------------------
#endif
