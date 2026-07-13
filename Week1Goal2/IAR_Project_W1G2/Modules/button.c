#ifndef BUTTON_C
#define BUTTON_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Module Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
 *  \file       button.c
 *  \brief      BUTTON module implementation.
 *  \author     Chirila Viorel
 *  \date       13.07.2026
 */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "button.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

typedef struct {
  
  volatile gpio_uint8_t *port;
  gpio_uint8_t pin;
  volatile gpio_uint8_t *pin_register;
  
} button_config_t;

static const button_config_t button_table[] =
{
    { &PORTC, 6, &PINC},
};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private function declarations
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* None */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public function implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void BUTTON_Init(void){
  gpio_set_direction(&DDRC, 6, GPIO_INPUT);
  
  button_enable_pullup(SW0);
}

void button_enable_pullup(button_uint8_t button){
  if(button<NUMBER_OF_BUTTONS){
    gpio_set_pin(button_table[button].port,button_table[button].pin);
  }
}

unsigned char button_read_state(button_uint8_t button){
  if(button < NUMBER_OF_BUTTONS){
    return gpio_read_pin(button_table[button].pin_register,button_table[button].pin);
  }
  return -1;
}

#endif