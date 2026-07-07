#include "sos.h"
#include <intrinsics.h>
#define PCINT22 6

#define PCIE2 2
#define PC7 7
#define OUTPUT 1
#define INPUT 0
#define PC6 6

int pressed = 0;
#pragma vector = PCINT2_vect
__interrupt void my_interrupt(void){
  if(!getPin(&PINC,PC6))
      pressed ^= 1;

}

int main( void )
{
  //am setat ledul 0 ca iesire
  setDirection(&DDRC,PC7,OUTPUT);
  setDirection(&DDRC,PC6,INPUT);
  setPin(&PORTC,PC6);
  //am setat sw ca intrare

  PCMSK2 |= (1 << PCINT22);

    // Activeaza grupul de întreruperi al portului C
   PCICR |= (1 << PCIE2);
   
     __enable_interrupt(); 
  while(1){
    if(!get_pin(&PINC,PC6)){
      confidence_pressed++;
      if(confidence_pressed >200)
      {
        if(pressed == 0){
          pressed = 1;
          
          while(pressed){
           
          ledSos(0);
          for(long i = 0 ;i<100000;i++);
          
          }
         
        }
        confidence_pressed = 0;
      }
    }
    
  }
}
