/* 316 - the SOS refactored */

#include "iom324pb.h"
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"
#include "button.h"
#include "sos.h"

#define PCINT22_BIT     (6U)
#define PCIE2_BIT       (2U)

static volatile unsigned char sos_active = 0;

#pragma vector=PCINT2_vect
__interrupt void sw0_isr(void)
/* the routine serving the interrupt caused by my button press */
{
    if (gpio_read_pin(SW0_PIN) == GPIO_LOW)
    {
        sos_active = !sos_active;   
    }
}

static void button_interrupt_init(void)
{
    gpio_set_direction(SW0_PIN, GPIO_INPUT);
    gpio_enable_pullup(SW0_PIN);

    PCMSK2 |= (1 << PCINT22_BIT);   /* pin change interrupt on PC6 only */
    PCICR  |= (1 << PCIE2_BIT);     /* enable the PCINT[23:16] group */

    __enable_interrupt();
}

void main( void )
{
    led_init();
    led_power_off();

    button_interrupt_init();

    while(1)
    {
        if (sos_active != 0)
        {
            sos_signal();
            sos_pause();
        }
        else
        {
            led_power_off();
        }
    }
}
