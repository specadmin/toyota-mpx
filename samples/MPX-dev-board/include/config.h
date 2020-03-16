#ifndef CONFIG_H
#define CONFIG_H
//----------------------------------------------------------------------------
#include <avr/io.h>
//----------------------------------------------------------------------------

#define DEBUG_PORT          PORTC
#define DEBUG_DDR           DDRC
#define DEBUG_BIT           1
#define DEBUG_BAUD_RATE     1152000

// #define DEBUG_EXTENDED_DUMP
// #define RAM_GUARD_ENABLED


#define MPX_RX_PORT         PORTD
#define MPX_RX_DIR          DDRD
#define MPX_RX_PIN          PIND
#define MPX_RX_BIT          2

#define MPX_RX_INT          INT0
#define MPX_RX_INT_VECT     INT0_vect
#define MPX_RX_ISC0         ISC00
#define MPX_RX_ISC1         ISC01

#define MPX_TX_PORT         PORTB
#define MPX_TX_DIR          DDRB
#define MPX_TX_BIT          1

#define MPX_RX_LED_PORT     PORTD
#define MPX_RX_LED_DIR      DDRD
#define MPX_RX_LED_BIT      5

//#define MPX_TX_LED_PORT     PORTB
//#define MPX_TX_LED_DIR      DDRB
//#define MPX_TX_LED_BIT      2

//----------------------------------------------------------------------------
#endif

