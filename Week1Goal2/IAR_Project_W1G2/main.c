// 252 - CORE
#include "main.h"


void main( void )
{
  LED_Init();
  
  unsigned char button_state;
  
  gpio_set_direction(&DDRC,6,GPIO_INPUT);
  gpio_set_pin(&PORTC,6);
  
  while(1){
    
    button_state = PINC_PINC6;
    if(button_state == 0){
      PowerOn_LED(LED0);
    }else{
      PowerOff_LED(LED0);
    }
    //Toggle_LED(LED0);
    //BlinkFast_LED(LED0);
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
