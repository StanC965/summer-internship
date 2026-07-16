//522
#include "iom324pb.h"
#include "scheduler.h"
#include <intrinsics.h>
#include "led.h"
#include "gpio.h"
#include "adc.h"

#define LED0_PIN 7
#define LED1_PIN 5      //pd5
#define LED2_PIN 4      //pd4
#define LED3_PIN 3      //pa3
#define OUTPUT 1
#define INPUT 0

void leds_init(void){
  Init_LED(&DDRD,LED1_PIN,OUTPUT);
  Init_LED(&DDRD,LED2_PIN,OUTPUT);
  Init_LED(&DDRA,LED3_PIN,OUTPUT);
  
  set_pin(&PORTD,LED1_PIN);
  set_pin(&PORTD,LED2_PIN);
  set_pin(&PORTA,LED3_PIN);
}

void timer1_init(void){
  TCCR1A=0x00;
  TCCR1B=0b00001001; //CS1[2:0]=001 prescale 1
  OCR1A=9999;
  TIMSK1=0b00000010;  //compare match A
  __enable_interrupt();
}

#pragma vector=TIMER1_COMPA_vect
__interrupt void timer1_interrupt(void){
  scheduler_flags_management();
}

void main( void ){
  adc_init();
  leds_init();
  timer1_init();
  adc_start_conversion();
  schedule_tasks_dispatcher();
}