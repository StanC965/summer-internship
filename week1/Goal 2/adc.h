#include <iom324pb.h>
#include "gpio.h"

void ADC_init();
void set_Pin_ADC(PIN_Number pin);
void reset_Pin_ADC(PIN_Number pin);
void Adjust_Left();
void Adjust_right();
void Enable_ADC();
void Disable_ADC();
void Start_Conversion();
void InterruptADC();