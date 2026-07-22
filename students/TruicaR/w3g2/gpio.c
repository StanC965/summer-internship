#include "iom324pb.h"
#include "gpio.h"

void gpio_set_pin(volatile unsigned char *port, unsigned char pin)
{
    *port |= (1 << pin);
}

void gpio_reset_pin(volatile unsigned char *port, unsigned char pin)
{
    *port &= ~(1 << pin);
}

void gpio_set_direction(volatile unsigned char *ddr, unsigned char pin, unsigned char direction)
{
    if (direction)
        *ddr |= (1 << pin);
    else
        *ddr &= ~(1 << pin);
}

unsigned char gpio_read_pin(volatile unsigned char *pin_reg, unsigned char pin)
{
    return (*pin_reg & (1 << pin)) ? 1 : 0;
}

unsigned char gpio_debounce(volatile unsigned char *pin_reg, unsigned char pin)
{
    if (gpio_read_pin(pin_reg, pin) == 0)
    {
        for (volatile int i = 0; i < 2000; i++);
        if (gpio_read_pin(pin_reg, pin) == 0)
            return 1;
    }
    return 0;
}

#define DEBOUNCE_MASK       0x1F 
#define DEBOUNCE_ALL_LOW    0x00
#define DEBOUNCE_ALL_HIGH   0x1F

unsigned char gpio_debounce_5sample(unsigned char *buffer, volatile unsigned char *pin_reg, unsigned char pin, unsigned char previous_stable)
{
    unsigned char sample = gpio_read_pin(pin_reg, pin);

    *buffer = ((*buffer << 1) | sample) & DEBOUNCE_MASK;

    if (*buffer == DEBOUNCE_ALL_LOW)  return 1;   
    if (*buffer == DEBOUNCE_ALL_HIGH) return 0;  
    return previous_stable;                       
}