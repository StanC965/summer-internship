//164
#include <iom324pb.h>

SFR_B_N(0x08,PORTC,PORTC7,PORTC6,PORTC5,PORTC4,PORTC3,PORTC2,PORTC1,PORTC0)
// 0x08 este adresa fizica a registrului, PORTC este numele folosit in C, restul sunt bitii registrului de la msb la lsb
SFR_B_N(0x07, DDRC, DDRC7, DDRC6, DDRC5, DDRC4, DDRC3, DDRC2, DDRC1, DDRC0)
// 0x07 este adresa fizica a registrului, DDRC este numele folosit in C, restul sunt bitii registrului de la msb la lsb
SFR_B_N(0x06, PINC, PINC7, PINC6, PINC5, PINC4, PINC3, PINC2, PINC1, PINC0)
// 0x06 este adresa fizica a registrului, PINC este numele folosit in C, restul sunt bitii registrului de la msb la lsb