#include "adc.h"
#include "iom324pb.h"
#include <intrinsics.h>

static volatile unsigned char lumina_ambientala=0;

void adc_init(){
  ADMUX=0b01100100; //REFS[1:0]-AVcc with external capacitor at AREF pin, ADLAR=1 - left adjust, MUX[4:0] - ADC4=00100
  ADCSRA=0b10001000;  //ADEN=1 -enables the ADC, ADSC=0 - not starting the conversion, ADATE- no internal trigger signals, 
                  //ADIF=0 -no interrupt flag, ADIE=1 -use interrupts ,ADPS[2:0]=000 - no prescale
  __enable_interrupt();
}

void adc_start_conversion(void){
  ADCSRA=0b11001000;
}

unsigned char adc_get_data(void){
  return lumina_ambientala;
}

#pragma vector=ADC_vect
__interrupt void ADC_interrupt(void){
  lumina_ambientala=ADCH;
}