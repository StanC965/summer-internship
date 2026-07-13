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
#define FULL_DARK 255
#define SEMI_DARK 225
#define SEMI_LIGHT 120
#define FULL_LIGHT 60

volatile unsigned char lumina_ambientala=0;

#pragma vector=ADC_vect
__interrupt void ADC_interrupt(void){
  lumina_ambientala=ADCH;
  ADCSRA = 0b00001000; //disable the ADC
}

void adc_init(){
  ADMUX=0b01100100; //REFS[1:0]-AVcc with external capacitor at AREF pin, ADLAR=1 - left adjust, MUX[4:0] - ADC4=00100
  ADCSRA=0b00001000;  //ADEN=0 -disables the ADC, ADSC=0 - not starting the conversion, ADATE- no internal trigger signals, 
                  //ADIF=0 -no interrupt flag, ADIE=1 -use interrupts ,ADPS[2:0]=000 - no prescale
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

void turn_on_leds(unsigned char lumina){
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
  ADCSRA=0b10001000; //enable the ADC
  for(long i=0;i<30000;i++);
  ADCSRA=0b11001000; //incepem conversia
  
}

unsigned char adc_get_result(void){
  return lumina_ambientala;
}

void main(void){
  adc_init();
  oled1_leds_init();
  
  while(1){
    adc_start_conversion();
    for(long i=0;i<30000;i++); //delay
    unsigned char lumina=adc_get_result();
    
    turn_on_leds(lumina);
  }
}


