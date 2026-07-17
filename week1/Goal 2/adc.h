#include <iom324pb.h>
#include "gpio.h"
#include "Led.h"

#pragma vector=ADC_vect
__interrupt void Conversie(void);
#define SensorL 0
static unsigned int SensorH;

#define MID (SensorH+SensorL)/2
#pragma once
typedef enum{
Rez10bit=1,
Rez8bit =0
}Rezolution;

extern volatile unsigned int conver;
void ADC_init();
void set_Pin_ADC(PIN_Number pin);
void reset_Pin_ADC(PIN_Number pin);
void Adjust_Left();
void Adjust_right();
void Enable_ADC();
void Disable_ADC();
void Start_Conversion();
void InterruptADC();
void Led_on_sensor();
void light_read();
void resolution(Rezolution i);