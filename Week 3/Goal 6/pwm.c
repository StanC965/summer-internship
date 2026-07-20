#include "iom324pb.h"
#include "pwm.h"
#include "gpio.h"

#define PWM_PIN 3 //pb3
#define OUTPUT 1
#define TOP_VALUE 255

void pwm_init(void){
  set_direction(&DDRB,PWM_PIN,OUTPUT);
  TCCR0A=0b10000011;
  TCCR0B=0b00000011;
  OCR0A=0x00;
}

void pwm_set_duty_cycle(unsigned char value){
  if(value>100){
    value=100;
  }
  OCR0A=(value*TOP_VALUE)/100;
  
}

void pwm_dc(int param){
  if(param>100){
    param=100;
  }
  if(param<0){
    param=0;
  }
  OCR0A=(param*TOP_VALUE)/100;
}