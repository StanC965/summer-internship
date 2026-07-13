// 242 - CORE
#include "main.h"


void main( void )
{
  LED_Init();
  
  while(1){
    
    Toggle_LED(LED0);
    
    PowerOff_LED(LED1);
    PowerOff_LED(LED2);
    PowerOff_LED(LED3);
    delay(SECOND);
    
    PowerOn_LED(LED1);
    PowerOn_LED(LED2);
    PowerOff_LED(LED3);
    delay(SECOND);

    PowerOff_LED(LED1);
    PowerOn_LED(LED2);
    PowerOn_LED(LED3);
    delay(SECOND);
    
    PowerOn_LED(LED1);
    PowerOff_LED(LED2);
    PowerOn_LED(LED3);
    delay(SECOND);

  }
}
