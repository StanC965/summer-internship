#ifndef MOD_C
#define MOD_C
#include "iom324pb.h"

unsigned char* reg;
unsigned char pin;
_Bool dir;


extern void set_pin(volatile unsigned char* port,unsigned char pin);

extern void reset_pin(volatile unsigned char* port,unsigned char pin);

extern void set_direction(volatile unsigned char* ddr, unsigned char pin,_Bool dir);

extern void toggle_pin(volatile unsigned char* reg, unsigned char pin);



#endif