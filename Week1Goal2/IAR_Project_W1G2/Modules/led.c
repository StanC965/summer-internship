#ifndef LED_C
#define LED_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Module Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
 *  \file       led.c
 *  \brief      LED module implementation.
 *  \author     Chirila Viorel
 *  \date       12.07.2026
 */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "led.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

typedef struct {
  
  volatile gpio_uint8_t *port;
  gpio_uint8_t pin;
  
} led_config_t;

static const led_config_t led_table[] =
{
    { &PORTC, 7 },
    { &PORTD, 5 },
    { &PORTD, 4 },
    { &PORTA, 3 }
};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private function declarations
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* None */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public function implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void LED_Init(void){
  gpio_set_direction(&DDRC, 7, GPIO_OUTPUT);
  gpio_set_direction(&DDRD, 5, GPIO_OUTPUT);
  gpio_set_direction(&DDRD, 4, GPIO_OUTPUT);
  gpio_set_direction(&DDRA, 3, GPIO_OUTPUT);

  /* Turn all LEDs OFF (active LOW) */
  PowerOff_LED(LED0);
  PowerOff_LED(LED1);
  PowerOff_LED(LED2);
  PowerOff_LED(LED3);
}

void PowerOn_LED(led_uint8_t led){
  if(led < NUMBER_OF_LEDS){
    gpio_reset_pin(led_table[led].port, led_table[led].pin);
  }
}

void PowerOff_LED(led_uint8_t led){
  if(led < NUMBER_OF_LEDS){
    gpio_set_pin(led_table[led].port, led_table[led].pin);
  }
}

void Toggle_LED(gpio_uint8_t led){
  if(led < NUMBER_OF_LEDS){
    gpio_toggle_pin(led_table[led].port, led_table[led].pin);
  }
}

void BlinkFast_LED(led_uint8_t led){
  if(led < NUMBER_OF_LEDS){
    PowerOn_LED(led);
    delay(FAST_BLINK_DELAY);

    PowerOff_LED(led);
    delay(FAST_BLINK_DELAY);
  }
}

void BlinkSlow_LED(led_uint8_t led){
  if(led < NUMBER_OF_LEDS){
    PowerOn_LED(led);
    delay(SLOW_BLINK_DELAY);

    PowerOff_LED(led);
    delay(SLOW_BLINK_DELAY);
  }
}
#endif