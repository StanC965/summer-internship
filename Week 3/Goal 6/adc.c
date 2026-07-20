#include "adc.h"
#include "iom324pb.h"
#include <intrinsics.h>

static volatile unsigned int lumina_ambientala=0;

void adc_init(){
  ADMUX=0b01000100; //REFS[1:0]-AVcc with external capacitor at AREF pin, ADLAR=0 - RIGHT adjust, MUX[4:0] - ADC4=00100
  ADCSRA=0b10001111;  //ADEN=1 -enables the ADC, ADSC=0 - not starting the conversion, ADATE- no internal trigger signals, 
                  //ADIF=0 -no interrupt flag, ADIE=1 -use interrupts ,ADPS[2:0]=111 - prescale cu 128
  DIDR0=0b00010000; // disable ADC4D
  __enable_interrupt();
}

void adc_start_conversion(void){
  ADCSRA=0b11001111; //incepem conversia
}

unsigned int adc_get_data(void){
  return lumina_ambientala;
}

unsigned char adc_scale(void){
  unsigned int value=adc_get_data();
  return 100-((value*100UL)/1023);
}


#pragma vector=ADC_vect
__interrupt void ADC_interrupt(void){
  unsigned char lumina_low=ADCL;
  unsigned char lumina_high=ADCH;
  lumina_ambientala=((unsigned int)lumina_high<<8) | lumina_low;
}