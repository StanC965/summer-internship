
#include "led.h"

#include "led.h"
//daca nu am avea acei guardians ni s-ar defini de 2 ori  led.h asa este doar o data
int main( void )
{
  set_direction(&DDRD,5,1);
  PowerOn_LED(1);
  PowerOff_LED(1);  
  while(1){
    LED_Blink_slow(1);
    LED_Blink_fast(1);
  }
}
