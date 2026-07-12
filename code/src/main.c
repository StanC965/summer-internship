#include "main.h" 
#include "led.h"

void delay(long count){
  for(long i = 0; i < count; i++);
}

void main (void){

  led_init();
  
  while(1){
    // INITIAL STATE:
    led_power_off(LED_ONBOARD);
    led_power_off(LED_OLED1_1);
    led_power_off(LED_OLED1_2);
    led_power_off(LED_OLED1_3);
    led_power_off(LED_IO1);

    delay(50000);

    // STATE 1
    led_power_on(LED_OLED1_1);

    delay(50000);

    // STATE 2
    led_power_off(LED_OLED1_1);
    led_power_on(LED_OLED1_2);

    delay(50000);

    // STATE 3
    led_power_off(LED_OLED1_2);
    led_power_on(LED_OLED1_3);

    delay(50000);

    // STATE 4
    led_power_off(LED_OLED1_3);
    led_power_on(LED_ONBOARD);

    delay(50000);

    // STATE 5
    led_power_off(LED_ONBOARD);
    led_power_on(LED_IO1);

    delay(50000);
    
    // STATE 6
    led_power_off(LED_IO1);
    led_toggle(LED_ONBOARD);

    delay(50000);
  }
  
}