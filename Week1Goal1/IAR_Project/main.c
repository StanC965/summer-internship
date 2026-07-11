//164 - 165 - CORE

#include <iom324pb.h>

/*SFR_B_N(0x08,PORTC,PORTC7,PORTC6,PORTC5,PORTC4,PORTC3,PORTC2,PORTC1,PORTC0)

Expands to:
__io union {
              unsigned char PORTC;
              struct {
                      unsigned char PORTC_Bit0:1,
                                    PORTC_Bit1:1,
                                    PORTC_Bit2:1,
                                    PORTC_Bit3:1,
                                    PORTC_Bit4:1,
                                    PORTC_Bit5:1,
                                    PORTC_Bit6:1,
                                    PORTC_Bit7:1,
                      };

              struct {
                      unsigned char PORTC_PORTC0:1
                                    PORTC_PORTC1:1,
                                    PORTC_PORTC2:1,
                                    PORTC_PORTC3:1,
                                    PORTC_PORTC4:1,
                                    PORTC_PORTC5:1,
                                    PORTC_PORTC6:1,
                                    PORTC_PORTC7:1,
                      };
}  @ 0x08;

SFR_B_N(0x07, DDRC, DDRC7, DDRC6, DDRC5, DDRC4, DDRC3, DDRC2, DDRC1, DDRC0)

Expands to:

__io union {
              unsigned char DDRC;

              struct {
                  unsigned char DDRC_Bit0:1,
                                DDRC_Bit1:1,
                                DDRC_Bit2:1,
                                DDRC_Bit3:1,
                                DDRC_Bit4:1,
                                DDRC_Bit5:1,
                                DDRC_Bit6:1,
                                DDRC_Bit7:1;
              };

              struct {
                  unsigned char DDRC_DDRC0:1,
                                DDRC_DDRC1:1,
                                DDRC_DDRC2:1,
                                DDRC_DDRC3:1,
                                DDRC_DDRC4:1,
                                DDRC_DDRC5:1,
                                DDRC_DDRC6:1,
                                DDRC_DDRC7:1;
              };
} @ 0x07;

SFR_B_N(0x06, PINC, PINC7, PINC6, PINC5, PINC4, PINC3, PINC2, PINC1, PINC0)

Expands to:

__io union {
              unsigned char PINC;

              struct {
                  unsigned char PINC_Bit0:1,
                                PINC_Bit1:1,
                                PINC_Bit2:1,
                                PINC_Bit3:1,
                                PINC_Bit4:1,
                                PINC_Bit5:1,
                                PINC_Bit6:1,
                                PINC_Bit7:1;
              };

              struct {
                  unsigned char PINC_PINC0:1,
                                PINC_PINC1:1,
                                PINC_PINC2:1,
                                PINC_PINC3:1,
                                PINC_PINC4:1,
                                PINC_PINC5:1,
                                PINC_PINC6:1,
                                PINC_PINC7:1;
              };
} @ 0x06;
*/

int main( void )
{
  

  return 0;
}


/*
The preprocessed file confirms that the preprocessor
    expands all #include directives by inserting the contents of the included files,
    eplaces all macros (#define) with their corresponding definitions,
    removes all comments before the compilation.
*/