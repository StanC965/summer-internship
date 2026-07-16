//363
#include "iom324pb.h"
#include "led.h"
#include "gpio.h"
#include <intrinsics.h>

#define LED0_PIN 7 
#define LED1_PIN 5      //pd5
#define LED2_PIN 4      //pd4
#define LED3_PIN 3      //pa3//pc7
#define OUTPUT 1
#define FULL_DARK 1023
#define SEMI_DARK 800
#define SEMI_LIGHT 440
#define FULL_LIGHT 150

volatile unsigned int lumina_ambientala=0;

#pragma vector=ADC_vect
__interrupt void ADC_interrupt(void){
  unsigned char lumina_low=ADCL;
  unsigned char lumina_high=ADCH;
  lumina_ambientala=(lumina_high<<8) | lumina_low;
  ADCSRA = 0b00001111; //disable the ADC
}

void adc_init(){
  ADMUX=0b01000100; //REFS[1:0]-AVcc with external capacitor at AREF pin, ADLAR=0 - RIGHT adjust, MUX[4:0] - ADC4=00100
  ADCSRA=0b00001111;  //ADEN=0 -disables the ADC, ADSC=0 - not starting the conversion, ADATE- no internal trigger signals, 
                  //ADIF=0 -no interrupt flag, ADIE=1 -use interrupts ,ADPS[2:0]=111 - prescale cu 128
  DIDR0=0b00010000; // disable ADC4D
  __enable_interrupt();
}


void oled1_leds_init(){
  Init_LED(&DDRD, LED1_PIN, OUTPUT);
  Init_LED(&DDRD, LED2_PIN, OUTPUT);
  Init_LED(&DDRA, LED3_PIN, OUTPUT);
  set_pin(&PORTD, LED1_PIN); 
  set_pin(&PORTD, LED2_PIN); 
  set_pin(&PORTA, LED3_PIN);
}

void turn_on_leds(unsigned int lumina){
  if(lumina>=SEMI_DARK && lumina <=FULL_DARK){
    set_pin(&PORTD, LED1_PIN); 
    set_pin(&PORTD, LED2_PIN); 
    set_pin(&PORTA, LED3_PIN);
  }
  if(lumina>=SEMI_LIGHT && lumina <SEMI_DARK){
    reset_pin(&PORTD, LED1_PIN); 
    set_pin(&PORTD, LED2_PIN); 
    set_pin(&PORTA, LED3_PIN);
  }
  if(lumina>=FULL_LIGHT && lumina <SEMI_LIGHT){
    reset_pin(&PORTD, LED1_PIN); 
    reset_pin(&PORTD, LED2_PIN); 
    set_pin(&PORTA, LED3_PIN);
  }
  if(lumina<FULL_LIGHT){
    reset_pin(&PORTD, LED1_PIN); 
    reset_pin(&PORTD, LED2_PIN); 
    reset_pin(&PORTA, LED3_PIN);
  }
}

void adc_start_conversion(void){
  ADCSRA=0b10001111; //enable the ADC
  for(long i=0;i<30000;i++);
  ADCSRA=0b11001111; //incepem conversia
  
}

unsigned int adc_get_result(void){
  return lumina_ambientala;
}

void main(void){
  adc_init();
  oled1_leds_init();
  
  while(1){
    adc_start_conversion();
    for(long i=0;i<30000;i++); //delay
    unsigned int lumina=adc_get_result();
    
    turn_on_leds(lumina);
  }
}


