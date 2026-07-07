#include "gpio.h"

int main( void )
{
  set_direction(&DDRC,6,0);
  set_pin(&PORTC,6);
  set_direction(&DDRC,7,1);
  set_pin(&PORTC,7);
  int presed = 0;
  int presed_confidence_level = 0;
  int released_confidence_level = 0;
  while(1){
  
  
  if(!get_pin(&PINC,6)){
      presed_confidence_level++;
      if(presed_confidence_level > 500){
        if(presed == 0){
          reset_pin(&PORTC,7);
          presed = 1;
        }
        presed_confidence_level = 0;
      }
      
  }
  else{
    released_confidence_level++;
    if(released_confidence_level > 500){
      set_pin(&PORTC,7);
      presed = 0;
      released_confidence_level = 0;
    }
    
  }
}
}