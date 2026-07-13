// 243 - CORE
#include "main.h"


void main( void )
{
  LED_Init();
  
  while(1){
    
    //Toggle_LED(LED0);
    BlinkFast_LED(LED0);
    /*
    PowerOff_LED(LED1);
    PowerOff_LED(LED2);
    PowerOff_LED(LED3);
    delay(ONE_SECOND_DELAY);
    
    PowerOn_LED(LED1);
    PowerOn_LED(LED2);
    PowerOff_LED(LED3);
    delay(ONE_SECOND_DELAY);

    PowerOff_LED(LED1);
    PowerOn_LED(LED2);
    PowerOn_LED(LED3);
    delay(ONE_SECOND_DELAY);
    
    PowerOn_LED(LED1);
    PowerOff_LED(LED2);
    PowerOn_LED(LED3);
    delay(ONE_SECOND_DELAY);*/

  }
}
