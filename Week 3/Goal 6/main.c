//672
#include "iom324pb.h"
#include <intrinsics.h>
#include "pwm.h"
#include "scheduler.h"
#include "gpio.h"
#include "adc.h"
#include "led.h"

//TEMT6000 PA4
#define BTNSW0_PIN 6    //pc6
#define LED0_PIN 7      //pc7
#define LED1_PIN 5      //pd5
#define LED2_PIN 4      //pd4
#define OUTPUT 1
#define INPUT 0


void timer1_init(void){
  TCCR1A=0X00;
  TCCR1B=0b00001001;
  OCR1A=9999;
  TIMSK1=0b00000010;
  __enable_interrupt();
}

void leds_button_init(void){
  Init_LED(&DDRC, LED0_PIN, OUTPUT);
  set_pin(&PORTC, LED0_PIN); 
}

#pragma vector=TIMER1_COMPA_vect
__interrupt void timer1_ISR(void){
  scheduler_flags_management();
}

void setup_init(void){
  //adc_init();
  leds_button_init();
  //pwm_init();
  timer1_init();
}


void main( void )
{
  setup_init();
  while(1){
  schedule_tasks_dispatcher();
  }
}
