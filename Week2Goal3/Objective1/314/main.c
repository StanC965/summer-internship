/* 314 - external interrupt settings for SW0
   SW0 is on PC6 = PCINT22 -> group PCINT[23:16] -> vector PCINT2_vect */

#include "iom324pb.h"
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"
#include "button.h"

#define PCINT22_BIT     (6U)    /* PC6 is bit 6 in PCMSK2 */
#define PCIE2_BIT       (2U)    /* PCINT[23:16] group is bit 2 in PCICR */

#pragma vector=PCINT2_vect
__interrupt void sw0_isr(void)
/* the routine serving the interrupt caused by my button press */
{
    led_power_on();
}

static void button_interrupt_init(void)
{
    gpio_set_direction(SW0_PIN, GPIO_INPUT);
    gpio_enable_pullup(SW0_PIN);

    PCMSK2 |= (1 << PCINT22_BIT);   
    PCICR  |= (1 << PCIE2_BIT);     

    __enable_interrupt();           
}

void main( void )
{
    led_init();
    led_power_off();

    button_interrupt_init();

    while(1)
    {
        
    }
}
