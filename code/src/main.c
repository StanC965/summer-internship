#include "main.h" 
#include "led.h"
#include "delay.h"

void main (void){

  led_init();
  
  while(1){
    // INITIAL STATE:
    led_power_off(LED_ONBOARD);
    led_power_off(LED_OLED1_1);
    led_power_off(LED_OLED1_2);
    led_power_off(LED_OLED1_3);
    led_power_off(LED_IO1);
    delay(SECOND / 2);

    // STATE 1
    led_power_on(LED_OLED1_1);
    delay(SECOND / 2);

    // STATE 2
    led_power_off(LED_OLED1_1);
    led_power_on(LED_OLED1_2);
    delay(SECOND / 2);

    // STATE 3
    led_power_off(LED_OLED1_2);
    led_power_on(LED_OLED1_3);
    delay(SECOND / 2);

    // STATE 4
    led_power_off(LED_OLED1_3);
    led_power_on(LED_ONBOARD);
    delay(SECOND / 2);

    // STATE 5
    led_power_off(LED_ONBOARD);
    led_power_on(LED_IO1);
    delay(SECOND / 2);
    
    // STATE 6
    led_power_off(LED_IO1);
    led_toggle(LED_ONBOARD);
    delay(SECOND / 2);
    
    // STATE 7
    led_power_off(LED_ONBOARD);
    led_blink_fast(LED_IO1);
    delay(SECOND / 2);
    
    // STATE 8
    led_blink_slow(LED_OLED1_1);
    delay(SECOND / 2);
    
  }
  
}