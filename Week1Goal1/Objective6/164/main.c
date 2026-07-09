/* 164 - how the SFR_B_N macros for PORTC, DDRC and PINC expand */

/*
1. SFR_B_N(0x08, PORTC, PORTC7, PORTC6, PORTC5, PORTC4, PORTC3, PORTC2, PORTC1, PORTC0)
expands to a variable PORTC placed at physical address 0x08 (using the @ operator),
and defines bit names PORTC0..PORTC7 as bit positions 0..7 inside that register
PORTC = output value register for port C

2.SFR_B_N(0x07, DDRC, DDRC7, DDRC6, DDRC5, DDRC4, DDRC3, DDRC2, DDRC1, DDRC0)
expands to a variable DDRC at address 0x07, with bit names DDRC0..DDRC7 (bits 0..7)
DDRC = data direction register: 1 = pin is output, 0 = pin is input

3.SFR_B_N(0x06, PINC, PINC7, PINC6, PINC5, PINC4, PINC3, PINC2, PINC1, PINC0)
expands to a variable PINC at address 0x06, with bit names PINC0..PINC7 (bits 0..7)
PINC = reads the actual state of the port C pins
*/

void main( void )
{
}
