//441
#include "iom324.h"
#include "led.h"
#include "gpio.h"
#include <intrinsics.h>

#define SW0_PIN 6 //pc6
#define LED1_PIN 5      //pd5
#define LED2_PIN 4      //pd4
#define LED3_PIN 3      //pa3
#define OUTPUT 1
#define INPUT 0

void timer1_init(void){
  TCCR1A=0x00; //normal mode
  TCCR1B=0x00; //timer oprit
  TCNT1=0; //contor=0
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

void main( void ){
  leds_and_button_init();
  timer1_init();
  while(1){
    if(read_pin(&PINC, SW0_PIN)==0){
      set_pin(&PORTC,LED1_PIN);
      set_pin(&PORTC,LED2_PIN);
      set_pin(&PORTA,LED3_PIN);
      TCNT1=0;
      TCCR1B=0b00000101; //prescale 1024
      
      while(read_pin(&PINC, SW0_PIN)==0); //cat timp e apasat
      TCCR1B=0x00;//oprim timer ul
      unsigned int timp=TCNT1; //citim cat timp a fost apasat butonul
      
      if(timp<977){
        reset_pin(&PORTD,LED1_PIN);
        set_pin(&PORTD,LED2_PIN);
        set_pin(&PORTA,LED3_PIN);
      }
      else if(timp>=977 && timp<4885){
        reset_pin(&PORTD,LED2_PIN);
        set_pin(&PORTA,LED3_PIN);
        set_pin(&PORTD,LED1_PIN);
      }
      else{
        reset_pin(&PORTA,LED3_PIN);
        set_pin(&PORTD,LED2_PIN);
        set_pin(&PORTD,LED1_PIN);
      }
      
    }
  }
}
