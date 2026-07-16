//454
//Nu pot lega pinii de la butonul SW0 si ICP1
#include "iom324.h"
#include "led.h"
#include "gpio.h"
#include <intrinsics.h>

#define ICP1_PIN 6 //pd6
#define SW0_PIN 6 //pc6
#define LED1_PIN 5      //pd5
#define LED2_PIN 4      //pd4
#define LED3_PIN 3      //pa3
#define OUTPUT 1
#define INPUT 0

void timer1_init(void){
  TCCR1A=0x00; //normal mode
  TCCR1B=0b10000101; //ICNC1=1 - input capture noise canceler, 00000,CS1[2:0]=101 prescale 1024
  TIMSK1=0b00100000; //bit 5 =1: Input Capture interrupt is enabled
  __enable_interrupt();
}

void leds_and_button_init(void){
  set_direction(&DDRC, SW0_PIN,INPUT);
  set_pin(&PORTC,SW0_PIN);
  
  Init_LED(&DDRD,LED1_PIN,OUTPUT);
  Init_LED(&DDRD,LED2_PIN,OUTPUT);
  Init_LED(&DDRA,LED3_PIN,OUTPUT);
  set_pin(&PORTD,LED1_PIN);
  set_pin(&PORTD,LED2_PIN);
  set_pin(&PORTA,LED3_PIN);
}

#pragma vector=TIMER1_CAPT_vect
__interrupt void timer1_capture_interrupt(void){
  static unsigned char apasari=0;
  apasari++;
  if(apasari==4){
    reset_pin(&PORTD,LED1_PIN);
  }
  else if(apasari==5){
    reset_pin(&PORTD,LED2_PIN);
  }
  else if(apasari==6){
    reset_pin(&PORTA,LED3_PIN);
  }
  else if(apasari>6){
    apasari=0;
    set_pin(&PORTD,LED1_PIN);
    set_pin(&PORTD,LED2_PIN);
    set_pin(&PORTA,LED3_PIN);
  }
}

void main( void ){
  leds_and_button_init();
  timer1_init();
  while(1);
}