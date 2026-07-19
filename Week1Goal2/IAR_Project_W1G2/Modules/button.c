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

static const button_config_t button_table[] =
{
    { &PORTC, SW0_PIN, &PINC, &DDRC},
    { &PORTC, BUTTON1_PIN, &PINC, &DDRC},
    { &PORTA, BUTTON2_PIN, &PINA, &DDRA},
    { &PORTA, BUTTON3_PIN, &PINA, &DDRA}
};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private function declarations
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* None */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public function implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void BUTTON_Init(void){
  gpio_set_direction(&DDRC, SW0_PIN, GPIO_INPUT);
  gpio_set_direction(&DDRC, BUTTON1_PIN, GPIO_INPUT);
  gpio_set_direction(&DDRA, BUTTON2_PIN, GPIO_INPUT);
  gpio_set_direction(&DDRA, BUTTON3_PIN, GPIO_INPUT);
  
  button_enable_pullup(SW0);
  button_enable_pullup(BUTTON1);
  button_enable_pullup(BUTTON2);
  button_enable_pullup(BUTTON3);
}

void button_init(button_uint8_t button){
  if(button < NUMBER_OF_BUTTONS){
    gpio_set_direction(button_table[button].ddr, button_table[button].pin, GPIO_INPUT); 
    button_enable_pullup(button);
  }
}

void button_interrupt_init(button_uint8_t button) {
    
  if (button >= NUMBER_OF_BUTTONS) {
    return;
  }
  
  volatile gpio_uint8_t *port_curent = button_table[button].port;
  gpio_uint8_t pin_curent = button_table[button].pin;
  
  if (port_curent == &PORTA) {
    gpio_set_pin(&PCMSK0, pin_curent);
    gpio_set_pin(&PCICR, PCIE0);
  } 
  else if (port_curent == &PORTB) {
    gpio_set_pin(&PCMSK1, pin_curent);
    gpio_set_pin(&PCICR, PCIE1);
  } 
  else if (port_curent == &PORTC) {
    gpio_set_pin(&PCMSK2, pin_curent);
    gpio_set_pin(&PCICR, PCIE2);
  } 
  else if (port_curent == &PORTD) {
    gpio_set_pin(&PCMSK3, pin_curent);
    gpio_set_pin(&PCICR, PCIE3);
  }
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