
# Understand
This is a C++ library for sending any debug information from your **AVR** device to your host machine. It uses an UART interface, that could be assigned to **any** port pin of your controller. So it helps to debug the firmware in AVR devices that have no JTAG and Debugwire interfaces.


### Limits
* The library supports only 16 MHz CPU frequency.
* UART baudrate could be set to 115200 or 1152000 only.
* The library assumes that you are using GNU AVR compiller in your project.


# Connect
Use USB UART adapter or RS232 adapter to connect your controller to the host machine. Connect adapter's RX pin to the assigned pin (see Configure) and don't forget about GND.

# Add to your project
```
git submodule add https://github.com/specadmin/avr-debug lib/avr-debug
```

# Configure

Add or edit config.sh in your include directory

### Required parameters
```
#define DEBUG_PORT         PORTD       // debug port register address
#define DEBUG_DDR          DDRD        // debug port direction register address
#define DEBUG_BIT          2           // bit number in debug port
#define DEBUG_BAUD_RATE    1152000     // 115200 or 1152000 only
```

### Optional parameters
```
#define DEBUG_BUF_SIZE     64          // memory buffer size (default: 96 bytes)
#define DEBUG_EXTENDED_DUMP            // appends ASCII dump to the HEX dump
```

### Special parameters
Use it wih care. You should exactly know what you're doing.
```
#define DEBUG_SECTION      .text       // code section for bootloader (if needed)
```
# Include
Add the following line in the firmware modules, where debug is needed
```
#include "lib/debug.h"
```
Also, please ensure that you have a -DF_CPU parameter set in your command line compiller's options.


# Enable
Add -DDEBUG parameter to your compiller command line options. If this parameter is not set, all debug calls will be ommited by the compiller. So, you don't need to remove all of them in release builds.


# Use

## DEBUG_INIT()

DEBUG_INIT() initializes the library code. This call should be executed before any other library calls.

### Code
```
DEBUG_INIT()
```

### Output
```
==========
DEBUG INIT
==========
```

## DSTR()

DSTR() prints constant string with carrier return (\n). The string is printed from FLASH memory directly, saving your RAM.

### Code
```
DSTR("Hello world!");
DSTR("It works!");
```

### Output
```
Hello world!
It works!
```


## DSTRN()

DSTRN() prints constant string without carrier return. The string is printed from FLASH memory directly, saving your RAM.

### Code
```
DSTRN("Hello world!");
DSTRN("It works!");
```

### Output
```
Hello world!It works!
```

## DVAR()

DVAR() prints an integer variable name and its value in decimal view.

### Code
```
char a = 10;
DVAR(a);
unsigned char b = 200;
DVAR(b);
int c = -15000;
DVAR(c);
long int d = 1000000;
DVAR(d);
DVAR(a + b);
```

### Output
```
a = 10
b = 200
c = -15000
d = 1000000
a + b = 210
```

## DREG()

DREG() prints register name and it's value in hexadecimal  format.

### Code
```
DREG(PORTD);
```

### Output
```
PORTD = 0x16
```

## DHEX()

DHEX() prints an integer variable value in hexadecimal format

### Code
```
char a = 0x1A;
DHEX(a);
int b = 0x1A2B;
DHEX(b);
long int c = 0x1A2B3C4D;
DHEX(c);
```

### Output
```
1A
1A2B
1A2B3C4D
```

## DHEX8()

DHEX8() prints several byte values in hexadecimal format one by one in the line

### Code
```
char a = 0x1A;
char b = 0xFB;
unsigned char c = 0x3C;
DHEX8(3, a, b, c);
```

### Output
```
1A FB 3C
```

## DUMP_MEM()

DUMP_MEM() prints RAM dump from the specified location

### Code
```
char a[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit";
DUMP_MEM(a, sizeof(a));
```

### Output
If DEBUG_EXTENDED_DUMP is defined
```
 04C4:  4C 6F 72 65 6D 20 69 70 73 75 6D 20 64 6F 6C 6F   Lorem ipsum dolo
 04D4:  72 20 73 69 74 20 61 6D 65 74 2C 20 63 6F 6E 73   r sit amet, cons
 04E4:  65 63 74 65 74 75 72 20 61 64 69 70 69 73 63 69   ectetur adipisci
 04F4:  6E 67 20 65 6C 69 74 00                           ng elit.
```

If DEBUG_EXTENDED_DUMP is **not** defined
```
4C 6F 72 65 6D 20 69 70 73 75 6D 20 64 6F 6C 6F
72 20 73 69 74 20 61 6D 65 74 2C 20 63 6F 6E 73
65 63 74 65 74 75 72 20 61 64 69 70 69 73 63 69
6E 67 20 65 6C 69 74 00
```

## memory_usage()

memory_usage() prints RAM usage at the moment, when it is called. See [AVR Libc docs](https://www.nongnu.org/avr-libc/user-manual/malloc.html) for details.
![AVR RAM](https://github.com/specadmin/avr-debug/blob/master/AVR_memory.png)

Please note, that the following macro should be defined to enable this function, the function will do nothing otherwise.
```
#define RAM_GUARD_ENABLED
```

### Code
```
memory_usage();
```

### Output
```
===================
     RAM USAGE
===================
.data   0100      6
.bss    0106    101
heap    016B   1065
stack   07D2     45
-------------------
total          1217
free            831
```


## heap_info()

heap_info() prints heap table at the moment, when it is called.

### Code
```
heap_info();
```

### Output
```
=======================
       HEAP INFO
=======================
PTR      SIZE    STATUS
016D      124     freed
01EB      235     alloc
02D8       16     freed
02EA      100     alloc
0350       78     alloc
03A0      500     alloc
```
