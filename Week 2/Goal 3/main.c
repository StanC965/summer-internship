//355
#include "iom324pb.h"
#include "led.h"
#include "gpio.h"
#include <intrinsics.h>

#define LED0_PIN 7      //pc7
#define OUTPUT 1
#define MIDDLE_POINT 127 //255/2

volatile unsigned char lumina_ambientala=0;

#pragma vector=ADC_vect
__interrupt void ADC_interrupt(void){
  lumina_ambientala=ADCH;
}

void adc_init(){
  ADMUX=0b01100100; //REFS[1:0]-AVcc with external capacitor at AREF pin, ADLAR=1 - left adjust, MUX[4:0] - ADC4=00100
  ADCSRA=0b10001000;  //ADEN=1 -enables the ADC, ADSC=0 - not starting the conversion, ADATE- no internal trigger signals, 
                  //ADIF=0 -no interrupt flag, ADIE=1 -use interrupts ,ADPS[2:0]=000 - no prescale
  __enable_interrupt();
}

void led0_init(){
  Init_LED(&DDRC, LED0_PIN,OUTPUT);
  set_pin(&PORTC, LED0_PIN);
}

void adc_start_conversion(void){
  ADCSRA=0b11001000;
}

unsigned char adc_get_result(void){
  return lumina_ambientala;
}

void main(void){
  adc_init();
  led0_init();
  
  while(1){
    adc_start_conversion();
    unsigned char lumina=adc_get_result();
    
    if(lumina<MIDDLE_POINT){
      reset_pin(&PORTC, LED0_PIN);
    }
    else{
      set_pin(&PORTC, LED0_PIN);
    }
  }
}


