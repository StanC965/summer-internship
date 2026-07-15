#include <iom324pb.h>
#include "week1\Goal 2\button.h"

#pragma vector=ADC_vect
__interrupt void Conversie(void){
 unsigned int var = ADCH;
}

void main (void)
{
  // DDRD|=Led1/2;
   DDRD=Led1+Led2;
  //Led3
   DDRA=0x08;
   DDRC=0x80;
   PORTC=0x80;
   PCMSK0=0x03;
   PCMSK2=0x42;
   PCICR =0x05;
   SREG_I=1;
   PORTA=0xff;
   PORTD=0xff;
   ADMUX=0xa4;
   ADCSRA=0x88;
 
    while(1)
    {
      ADCSRA_ADSC=1;
    }
    
  
  }
