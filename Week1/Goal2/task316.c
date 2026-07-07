#include "sos.h"
#include <intrinsics.h>
#define PCINT22 6

#define PCIE2 2
int pressed = 0;
#pragma vector = PCINT2_vect
__interrupt void my_interrupt(void){
  if(!get_pin(&PINC,6))
      pressed ^= 1;

}

int main( void )
{
  //am setat ledul 0 ca iesire
  set_direction(&DDRC,7,1);
  set_direction(&DDRC,6,0);
  set_pin(&PORTC,6);
  //am setat sw ca intrare

  int confidence_pressed= 0;
  int confidence_release = 0;
  PCMSK2 |= (1 << PCINT22);

    // Activeaza grupul de întreruperi al portului C
   PCICR |= (1 << PCIE2);
   
     __enable_interrupt(); 
  while(1){
    if(!get_pin(&PINC,6)){
      confidence_pressed++;
      if(confidence_pressed >200)
      {
        if(pressed == 0){
          pressed = 1;
          
          while(pressed){
           
          SOS(0);
          for(long i = 0 ;i<100000;i++);
          
          }
         
        }
        confidence_pressed = 0;
      }
    }
    
  }
}
