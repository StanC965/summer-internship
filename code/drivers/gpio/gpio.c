#ifndef GPIO_C
#define GPIO_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "gpio.h"
#include <iom324pb.h>
#include "bits.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void gpio_init()
{
  volatile uint8_t *const ddr_registers[] = {&DDRA, &DDRB, &DDRC, &DDRD, &DDRE};
  volatile uint8_t *const port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

  const uint8_t num_ports = sizeof(ddr_registers) / sizeof(ddr_registers[0]);

  for (uint8_t i = 0; i < num_ports; i++)
  {
    *(ddr_registers[i]) = 0x00;
    *(port_registers[i]) = 0x00;
  }
}

void gpio_set_pin(volatile uint8_t *port_register, uint8_t pin)
{
  *port_register |= BIT_MASK(pin);
}

void gpio_switch_set_pin(volatile uint8_t *port_register, uint8_t pin)
{
  switch (pin)
  {
  case 1:
    *port_register |= BIT_MASK(pin);
    break;
  default:
    break;
  }
}

void gpio_reset_pin(volatile uint8_t *port_register, uint8_t pin)
{
  *port_register &= ~BIT_MASK(pin);
}

void gpio_switch_reset_pin(volatile uint8_t *port_register, uint8_t pin)
{
  switch (pin)
  {
  case 1:
    *port_register &= ~BIT_MASK(pin);
    break;
  default:
    break;
  }
}

void gpio_set_direction(volatile uint8_t *ddr_register, uint8_t direction, uint8_t pin)
{
  *ddr_register = (direction == GPIO_OUTPUT) ? (*ddr_register | (BIT_MASK(pin))) : (*ddr_register & ~(BIT_MASK(pin)));
}

void gpio_toggle_pin(volatile uint8_t *port_register, uint8_t pin)
{
  *port_register ^= BIT_MASK(pin);
}

uint8_t gpio_read_pin(volatile uint8_t *pin_register, uint8_t pin)
{
  return ((*pin_register & BIT_MASK(pin)) != 0U);
}

#endif /* GPIO_C */