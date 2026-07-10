#ifndef ADC_H
#define ADC_H
#include "gpio.h"
extern void initAdc(volatile unsigned char* DDR,volatile unsigned char* port,unsigned char pin,unsigned char ADMUXn,unsigned char REF0,unsigned char REF1,unsigned char ADLAR,unsigned char ADIE,unsigned char ADPS0,unsigned char ADPS1,unsigned char ADPS2);

extern void startConversionAdc();

#endif