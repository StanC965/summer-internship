#ifndef ADC_H
#define ADC_H
#include "gpio.h"
#define Adc8Bit

#define Adc10Bit
extern void initAdc(volatile unsigned char* DDR,volatile unsigned char* port,unsigned char pin,unsigned char ADMUXn,unsigned char REF0,unsigned char REF1,unsigned char ADIE,unsigned char ADPS0,unsigned char ADPS1,unsigned char ADPS2);

extern void startConversionAdc();
extern void enableAdc();

extern void disableAdc();
#endif