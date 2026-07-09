#include "sos.h"
#include <intrinsics.h>

#define PA1 1
#define INPUT 0
#define ADMUX1 0
#define REF1 7
#define PC7 7
#define OUTPUT 1
#define ADEN 7
#define ADCS 6
#define ADLAR 5
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADIE 3
#pragma vector = ADC_vect
__interrupt void myInterrupt(void){
  unsigned char value = ADCH;
  if(value >100)
      ledPowerOn(0);
  else
      ledPowerOff(0);
 
  setPin(&ADCSRA,ADCS);    
}


void initADCSRA(){
    setDirection(&DDRC,PC7,OUTPUT);
    setPin(&PORTC,PC7);
    setDirection(&DDRA,PA1,INPUT);
    resetPin(&PORTA,PA1);
    
    setPin(&ADMUX,ADMUX1);
    setPin(&ADMUX,REF1);
    setPin(&ADMUX,ADLAR);
    
    setPin(&ADCSRA,ADEN);
    setPin(&ADCSRA,ADIE);
   
}


int main( void )
{
  initADCSRA();
  
  __enable_interrupt();
  
  setPin(&ADCSRA,ADCS);
  
  while(1){
  }
  
  
}
