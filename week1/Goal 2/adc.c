#include "adc.h"

void ADC_init(){
  ADMUX=0x40;
  Enable_ADC();
  set_Pin_ADC(PIN4);
  Adjust_Left();
  
}
void set_Pin_ADC(PIN_Number pin){
ADMUX|=pin;
}
void reset_Pin_ADC(PIN_Number pin){
ADMUX &=~pin;
}
void Adjust_Left(){
ADMUX |=0x20;
}
void Adjust_right(){
ADMUX &=~0x20;
}
void Enable_ADC(){
ADCSRA|=0x88;
}
void Disable_ADC(){
ADCSRA&=~0x80;
}
void Start_Conversion(){
ADCSRA|=0x40;
}
void InterruptADC(){
 ADCSRA_ADIE=1;
  SREG_I=1;
}