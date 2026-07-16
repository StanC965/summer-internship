#include "adc.h"

volatile unsigned char conver = 0;
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
__interrupt void Conversie(void){
 conver = ADCH;
}
void Led_on_sensor(){
  if(conver>(SensorH-SensorL)/2){
      led0_set_state(ON);}
   else
     led0_set_state(OFF);
}
