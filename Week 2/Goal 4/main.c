//441
#include "iom324.h"
#include "led.h"
#include "gpio.h"
#include "CarCrashDetection.h"
#include <intrinsics.h>

#define SW0_PIN  6      //pc6
#define LED0_PIN 5      //pd5 oled
#define LED1_PIN 4      //pd4 oled
#define LED2_PIN 3      //pa3 oled
#define LED3_PIN 7      //pc7 atmega
#define LED4_PIN 3      //pb3 io1
#define OUTPUT 1
#define INPUT 0

volatile unsigned char secunda = 5;
volatile unsigned char counting = 0;
volatile unsigned char contor_overflow = 0;

void timer0_init(void){
  TCCR0A=0b00000000; //Normal mode
  TIMSK0=0b00000001; //Overflow Interrupt Enable
  TCCR0B=0b00000000; //timer oprit
  __enable_interrupt();
}

void leds_button_init(void){
  Init_LED(&DDRD,LED0_PIN,OUTPUT);
  Init_LED(&DDRD,LED1_PIN,OUTPUT);
  Init_LED(&DDRA,LED2_PIN,OUTPUT);
  Init_LED(&DDRC,LED3_PIN,OUTPUT);
  Init_LED(&DDRB,LED4_PIN,OUTPUT);
  reset_pin(&PORTD,LED0_PIN);
  reset_pin(&PORTD,LED1_PIN);
  reset_pin(&PORTA,LED2_PIN);
  reset_pin(&PORTC,LED3_PIN);
  reset_pin(&PORTB,LED4_PIN);
  
  set_direction(&DDRC, SW0_PIN, INPUT);
  set_pin(&PORTC, SW0_PIN);
}

void substract_leds(void){
  if(secunda==4){
    set_pin(&PORTD,LED0_PIN);
  }
  if(secunda==3){
    set_pin(&PORTD,LED0_PIN);
    set_pin(&PORTD,LED1_PIN);
  }
  if(secunda==2){
    set_pin(&PORTD,LED0_PIN);
    set_pin(&PORTD,LED1_PIN);
    set_pin(&PORTA,LED2_PIN);
  }
  if(secunda==1){
    set_pin(&PORTD,LED0_PIN);
    set_pin(&PORTD,LED1_PIN);
    set_pin(&PORTA,LED2_PIN);
    set_pin(&PORTC,LED3_PIN);
  }
  if(secunda==0){
    set_pin(&PORTD,LED0_PIN);
    set_pin(&PORTD,LED1_PIN);
    set_pin(&PORTA,LED2_PIN);
    set_pin(&PORTC,LED3_PIN);
    set_pin(&PORTB,LED4_PIN);
  }
}

#pragma vector=TIMER0_OVF_vect
__interrupt void timer0_compa_interrupt(void){
  if(counting==1){
    contor_overflow++;
    if(contor_overflow>=61){ //cu prescale 64 avem 15625 pasi, 15625/256=61 o secunda
      contor_overflow=0;
      secunda--;
      substract_leds();
      
      if(secunda==0){
        TCCR0B=0b00000000;
        counting=0;
      }
    }
  }
  
}
void main( void )
{
  leds_button_init();
  timer0_init();
  while(1){
    if(read_pin(&PINC, SW0_PIN)==0 && counting==0){
      counting=1;
      secunda=5;
      contor_overflow=0;
      
      substract_leds();
      
      TCNT0=0;
      TCCR0B=0b00000011;//pornim timer cu prescaler 64
    }
  }
}