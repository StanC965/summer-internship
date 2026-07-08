#ifndef GPIO_H
#define GPIO_H
#include "iom324pb.h"




extern void setPin(volatile unsigned char* port,unsigned char pin);

extern void resetPin(volatile unsigned char* port,unsigned char pin);

extern void setDirection(volatile unsigned char* ddr, unsigned char pin,_Bool dir);

extern void togglePin(volatile unsigned char* reg, unsigned char pin);
extern unsigned char getPin(volatile unsigned char* reg, unsigned char pin);


#endif