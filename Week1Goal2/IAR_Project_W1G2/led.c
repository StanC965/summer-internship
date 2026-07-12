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

/* None */

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
  switch (led){
    case LED0:
      gpio_reset_pin(&PORTC, 7);
      break;

    case LED1:
      gpio_reset_pin(&PORTD, 5);
      break;

    case LED2:
      gpio_reset_pin(&PORTD, 4);
      break;

    case LED3:
      gpio_reset_pin(&PORTA, 3);
      break;
  }
}

void PowerOff_LED(led_uint8_t led){
  switch (led){
    case LED0:
      gpio_set_pin(&PORTC, 7);
      break;

    case LED1:
      gpio_set_pin(&PORTD, 5);
      break;

    case LED2:
      gpio_set_pin(&PORTD, 4);
      break;

    case LED3:
      gpio_set_pin(&PORTA, 3);
      break;
  }
}

void Toggle_LED(gpio_uint8_t led){
  switch (led){
    case LED0:
      gpio_toggle_pin(&PORTC, 7);
      break;

    case LED1:
      gpio_toggle_pin(&PORTD, 5);
      break;

    case LED2:
      gpio_toggle_pin(&PORTD, 4);
      break;

    case LED3:
      gpio_toggle_pin(&PORTA, 3);
      break;

    default:
      break;
  }
}
#endif