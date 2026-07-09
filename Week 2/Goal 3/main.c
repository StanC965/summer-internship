//323
#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include <intrinsics.h>


#define PCIE2   2
#define PCIE0   0
#define BTN1_PIN 1      //pc1
#define BTN2_PIN 0      //pa0
#define BTN3_PIN 1      //pa1
#define LED1_PIN 5      //pd5
#define LED2_PIN 4      //pd4
#define LED3_PIN 3      //pa3
#define OUTPUT 1
#define INPUT 0

#pragma vector=PCINT2_vect
__interrupt void PortC_ISR(void) 
{
  if(read_pin(&PINC, BTN1_PIN)==0){
    reset_pin(&PORTD,LED1_PIN);
  }
  else{
    set_pin(&PORTD,LED1_PIN);
  }
}

#pragma vector=PCINT0_vect
__interrupt void PortA_ISR(void) 
{
  if(read_pin(&PINA, BTN2_PIN)==0){
    reset_pin(&PORTD,LED2_PIN);
  }
  else{
    set_pin(&PORTD,LED2_PIN);
  }
        
  if(read_pin(&PINA, BTN3_PIN)==0){
    reset_pin(&PORTA,LED3_PIN);
  }
  else{
    set_pin(&PORTA,LED3_PIN);
  }
   
}

void setup(void) {
    Init_LED(&DDRD, LED1_PIN, OUTPUT);
    Init_LED(&DDRD, LED2_PIN, OUTPUT);
    Init_LED(&DDRA, LED3_PIN, OUTPUT);
    set_pin(&PORTD, LED1_PIN); 
    set_pin(&PORTD, LED2_PIN); 
    set_pin(&PORTA, LED3_PIN); 
    set_direction(&DDRC, BTN1_PIN, INPUT); 
    set_direction(&DDRA, BTN2_PIN, INPUT);
    set_direction(&DDRA, BTN3_PIN, INPUT);
    set_pin(&PORTC, BTN1_PIN);
    set_pin(&PORTA, BTN2_PIN);
    set_pin(&PORTA, BTN3_PIN);

    // activam intreruperile pentru tot portul C
    PCICR |= (1 << PCIE2) | (1 << PCIE0);   
    // pin 6
    PCMSK2 |=(1<<BTN1_PIN ); //PORT C
    PCMSK0 |=(1 << BTN2_PIN) | (1 << BTN3_PIN); //PORT A
    __enable_interrupt(); 
}

void main(void) {
    setup(); 

    while(1);
}