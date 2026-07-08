#include <iom324pb.h>

void main(void)
{
 /* SFR_B_N(0x08,PORTC,PORTC7,PORTC6,PORTC5,PORTC4,PORTC3,PORTC2,PORTC1,PORTC0)
 *  Expands to:
 *  __io union { 
 *              - byte level access
 *              unsigned char PORTC; 
 *
 *              - generic bit level
 *              struct { 
 *                      unsigned char PORTC_Bit0:1, 
 *                                    PORTC_Bit1:1, 
 *                                    PORTC_Bit2:1, 
 *                                    PORTC_Bit3:1, 
 *                                    PORTC_Bit4:1, 
 *                                    PORTC_Bit5:1, 
 *                                    PORTC_Bit6:1, 
 *                                    PORTC_Bit7:1; 
 *                     }; 
 *              - specific bit-name level
 *              struct { 
 *                      unsigned char PORTC_PORTC0:1, 
 *                                    PORTC_PORTC1:1, 
 *                                    PORTC_PORTC2:1, 
 *                                    PORTC_PORTC3:1, 
 *                                    PORTC_PORTC4:1, 
 *                                    PORTC_PORTC5:1, 
 *                                    PORTC_PORTC6:1, 
 *                                    PORTC_PORTC7:1; 
 *                     }; 
 *             } @ 0x08;
 *
 * this same expansion happens to the other two macros
 * we just need to switch:
 *      - PORTC with DDRC and PINC
 *      - PORTC_ Bit/PORTC [0-7] with DDRC_ Bit/DDRC [0-7] and PINC_ Bit/PINC [0-7]
 *      - 0x08 with 0x07 and 0x06
 */
}