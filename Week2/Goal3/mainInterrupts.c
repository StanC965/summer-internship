#include "iom324pb.h"
#include "led.h"
#include <intrinsics.h>

#define PCINT22 6

#define PCIE2 2

/*rutina mea de intreruperi*/
#pragma vector = PCINT2_vect
__interrupt void my_routine(void){
    PowerOn_LED(1);
}

int main( void )
{
  //setam ledul ca output
  set_direction(&DDRD,5,1);
  set_pin(&PORTD,5);
  //setez pinul ca intrere
  set_direction(&DDRC,6,0);
  set_pin(&PORTC,6);
  
  
  PCMSK2 |= (1 << PCINT22);

    // Activeaza grupul de întreruperi al portului C
   PCICR |= (1 << PCIE2);

  __enable_interrupt();
  
  while(1){
 
  }
}
