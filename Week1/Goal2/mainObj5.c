#include "gpio.h"

int main( void )
{
  set_direction(&DDRC,6,0);
  set_pin(&PORTC,6);
  set_direction(&DDRC,7,1);
  set_pin(&PORTC,7);
  unsigned char sw;
  unsigned char sum=0;
  while(1){
  sw = PINC;
  
  if(!(sw & (1<<6))){
      reset_pin(&PORTC,7);
  }
  else{
    set_pin(&PORTC,7);
  }
}
}