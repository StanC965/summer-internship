
#include "led.h"
int main( void )
{
  set_direction(&DDRD,5,1);
  PowerOn_LED(1);
  PowerOff_LED(1);  
  while(1){
  }
}
