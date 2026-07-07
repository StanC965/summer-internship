#include <iom324pb.h>

/*
1. SFR_B_N(0x08,PORTC,PORTC7,PORTC6,PORTC5,PORTC4,PORTC3,PORTC2,PORTC1,PORTC0)
--------------------------------------------------------------------------------
- variable 'PORTC' is bound to memory address 0x08.
- bit-field expansion maps bits 0 to 7 to software structures:
  Bit 0 -> PORTC0
  Bit 1 -> PORTC1
  Bit 2 -> PORTC2
  Bit 3 -> PORTC3
  Bit 4 -> PORTC4
  Bit 5 -> PORTC5
  Bit 6 -> PORTC6
  Bit 7 -> PORTC7

2. SFR_B_N(0x07, DDRC, DDRC7, DDRC6, DDRC5, DDRC4, DDRC3, DDRC2, DDRC1, DDRC0)
--------------------------------------------------------------------------------
The preprocessor binds the software variable DDRC to memory address 0x07 and automatically
generates identical bit-field mappings for bits 0 through 7 (DDRC0 to DDRC7).

3. SFR_B_N(0x06, PINC, PINC7, PINC6, PINC5, PINC4, PINC3, PINC2, PINC1, PINC0)
--------------------------------------------------------------------------------
The macro maps the variable PINC directly to hardware address 0x06,
expanding bits 0 through 7 into individual pin structures (PINC0 to PINC7).
*/