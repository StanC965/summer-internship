//333
#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include <intrinsics.h>


#define PCIE2   2
#define PCIE0   0
#define BTNSW0_PIN 6    //pc6
#define BTN1_PIN 1      //pc1
#define BTN2_PIN 0      //pa0
#define BTN3_PIN 1      //pa1
#define LED0_PIN 7      //pc7
#define LED1_PIN 5      //pd5
#define LED2_PIN 4      //pd4
#define LED3_PIN 3      //pa3
#define OUTPUT 1
#define INPUT 0

volatile int panel_blocat=0;
//volatile int stare_led0 = 0;
volatile int stare_led1 = 0;
volatile int stare_led2 = 0;
volatile int stare_led3 = 0;

#pragma vector=PCINT2_vect
__interrupt void PortC_ISR(void) 
{ 
  if(read_pin(&PINC, BTNSW0_PIN)==0){
    if(panel_blocat==0){
      panel_blocat=1;
    reset_pin(&PORTC,LED0_PIN);
    set_pin(&PORTD,LED1_PIN);
    set_pin(&PORTD,LED2_PIN);
    set_pin(&PORTA,LED3_PIN);
    stare_led1=0;
    stare_led2=0;
    stare_led3=0;   
    }
    else{
      set_pin(&PORTC,LED0_PIN);
      panel_blocat=0;
    }
    //while(read_pin(&PINC, BTNSW0_PIN) == 0);
  }

  if(read_pin(&PINC, BTN1_PIN)==0){
    if(panel_blocat==1){
      BlinkFast_LED(&PORTC, LED0_PIN);
      reset_pin(&PORTC,LED0_PIN);
    }
    else{
      if(stare_led1==0){
      reset_pin(&PORTD,LED1_PIN);
      stare_led1=1;
    }
  
    else{
      set_pin(&PORTD,LED1_PIN);
      stare_led1=0;
    }
    }
    while(read_pin(&PINC, BTN1_PIN)==0);
  }
}

#pragma vector=PCINT0_vect
__interrupt void PortA_ISR(void) 
{
  if(read_pin(&PINA, BTN2_PIN)==0){
    if(panel_blocat==1){
      BlinkFast_LED(&PORTC, LED0_PIN);
      reset_pin(&PORTC,LED0_PIN);
    }
    else{
    if(stare_led2==0){
      reset_pin(&PORTD,LED2_PIN);
      stare_led2=1;
    }
  
    else{
      set_pin(&PORTD,LED2_PIN);
      stare_led2=0;
    }
    }
    while(read_pin(&PINA, BTN2_PIN)==0);
  }
  
   if(read_pin(&PINA, BTN3_PIN)==0){
     if(panel_blocat==1){
       BlinkFast_LED(&PORTC, LED0_PIN);
       reset_pin(&PORTC,LED0_PIN);}
     else{
    if(stare_led3==0){
      reset_pin(&PORTA,LED3_PIN);
      stare_led3=1;
    }
  
    else{
      set_pin(&PORTA,LED3_PIN);
      stare_led3=0;
    }
     }
    while(read_pin(&PINA, BTN3_PIN)==0);
  }
   
}

void setup(void) {
    Init_LED(&DDRD, LED1_PIN, OUTPUT);
    Init_LED(&DDRD, LED2_PIN, OUTPUT);
    Init_LED(&DDRA, LED3_PIN, OUTPUT);
    Init_LED(&DDRC, LED0_PIN, OUTPUT);
    set_pin(&PORTD, LED1_PIN); 
    set_pin(&PORTD, LED2_PIN); 
    set_pin(&PORTA, LED3_PIN); 
    set_pin(&PORTC, LED0_PIN);
    set_direction(&DDRC, BTN1_PIN, INPUT); 
    set_direction(&DDRA, BTN2_PIN, INPUT);
    set_direction(&DDRA, BTN3_PIN, INPUT);
    set_direction(&DDRC, BTNSW0_PIN, INPUT);
    set_pin(&PORTC, BTN1_PIN);
    set_pin(&PORTA, BTN2_PIN);
    set_pin(&PORTA, BTN3_PIN);
    set_pin(&PORTC, BTNSW0_PIN);

    // activam intreruperile pentru tot portul C
    PCICR |= (1 << PCIE2) | (1 << PCIE0);   
    // pin 6
    PCMSK2 |=(1<<BTN1_PIN ) | (1<<BTNSW0_PIN); //PORT C
    PCMSK0 |=(1 << BTN2_PIN) | (1 << BTN3_PIN); //PORT A
    __enable_interrupt(); 
}

void main(void) {
    setup(); 

    while(1);
}