
#include "gpio.h"

int main( void )
{
  PORTC = 0x00;
  DDRC = 0x00;
  set_direction(&DDRC,7,1);
  while(1){
  }
}
