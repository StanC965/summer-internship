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

static const led_config_t led_table[] =
{
    { &PORTC, LED0_PIN, &DDRC },
    { &PORTD, LED1_PIN, &DDRD },
    { &PORTD, LED2_PIN, &DDRD },
    { &PORTA, LED3_PIN, &DDRA },
    { &PORTB, LED4_PIN, &DDRB }
};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private function declarations
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* None */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public function implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void LED_Init(void){
  gpio_set_direction(&DDRC, LED0_PIN, GPIO_OUTPUT);
  gpio_set_direction(&DDRD, LED1_PIN, GPIO_OUTPUT);
  gpio_set_direction(&DDRD, LED2_PIN, GPIO_OUTPUT);
  gpio_set_direction(&DDRA, LED3_PIN, GPIO_OUTPUT);
  gpio_set_direction(&DDRB, LED4_PIN, GPIO_OUTPUT);

  /* Turn all LEDs OFF (active LOW) */
  PowerOff_LED(LED0);
  PowerOff_LED(LED1);
  PowerOff_LED(LED2);
  PowerOff_LED(LED3);
  PowerOff_LED(LED4);
}

void led_init(led_uint8_t led){
  if(led < NUMBER_OF_LEDS){
    gpio_set_direction(led_table[led].ddr, led_table[led].pin, GPIO_OUTPUT);
    PowerOff_LED(led);
  }
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