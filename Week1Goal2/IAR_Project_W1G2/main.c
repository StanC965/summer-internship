// 242 - CORE
#include "main.h"
#include "gpio.h"
#include "led.h"


void delay(unsigned long count){
  volatile unsigned long i;

  for (i = 0; i < count; i++){
      // Software delay
  }
}

void main( void )
{
  LED_Init();
  
  while(1){
    
    Toggle_LED(LED0);
    
    PowerOff_LED(LED1);
    PowerOff_LED(LED2);
    PowerOff_LED(LED3);
    delay(250000UL);
    
    PowerOn_LED(LED1);
    PowerOn_LED(LED2);
    PowerOff_LED(LED3);
    delay(250000UL);

    PowerOff_LED(LED1);
    PowerOn_LED(LED2);
    PowerOn_LED(LED3);
    delay(250000UL);
    
    PowerOn_LED(LED1);
    PowerOff_LED(LED2);
    PowerOn_LED(LED3);
    delay(250000UL);

  }
}
