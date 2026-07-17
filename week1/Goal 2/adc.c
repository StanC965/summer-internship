#include "adc.h"

volatile unsigned int conver = 0;
void ADC_init(){
  ADMUX=0x40;
  set_Pin_ADC(PIN4);
  Adjust_right();
  
}
void set_Pin_ADC(PIN_Number pin){
DIDR0|=(0x01<<pin);
ADMUX|=pin;
}
void reset_Pin_ADC(PIN_Number pin){
ADMUX &=~pin;
DIDR0 &=~(0x01<<pin);
}
void Adjust_Left(){
ADMUX |=0x20;
}
void Adjust_right(){
ADMUX &=~0x20;
}
void Enable_ADC(){
ADCSRA|=0x80;
}
void Disable_ADC(){
ADCSRA&=~0x80;
}
void Start_Conversion(){
 Enable_ADC();
ADCSRA|=0x40;

}
void InterruptADC(){
 ADCSRA_ADIE=1;
  SREG_I=1;
}
__interrupt void Conversie(void){
  if((ADCSRA&0x07)==0x07) conver = ADC ;
  else{ 
    conver = ADCH;}
 Disable_ADC();
}
void Led_on_sensor(){
  if(conver>MID){
      led0_set_state(ON);}
   else
     led0_set_state(OFF);
}
void light_read(){
    //semi-light
  if(conver<MID){
    LedOff(&PORTA,PIN3);
    //full-light
    if(conver<MID/2)
    LedOn(&PORTA,PIN3);
    
    LedOn(&PORTD,PIN5);
    LedOn(&PORTD,PIN4);
 }
 //full-dark
  else{
    LedOff(&PORTD,PIN5);
    //semi-dark
    if(conver<MID+MID/2)
    LedOn(&PORTD,PIN5);
    
    LedOff(&PORTA,PIN3);
    LedOff(&PORTD,PIN4);
  }
}
void resolution(Rezolution i){
  if(i){
  Adjust_right();
  ADCSRA|=0x07;
  SensorH=1023;
  }
  else{
  Adjust_Left();
  ADCSRA&=~0x07;
  SensorH=255;
  }
}
