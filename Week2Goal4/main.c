#include "iom324pb.h"
#include <intrinsics.h>
#include "gpio.h"
#include "button.h"
#include "timer.h"
#include "panel.h"

#define PCINT22_BIT     (6U)   /* SW0 = PC6 = PCINT22 */
#define PCIE2_BIT       (2U)

static volatile unsigned char panel_tick = 0;

#pragma vector=PCINT2_vect
__interrupt void sw0_isr(void)
{
    if (gpio_read_pin(SW0_PIN_REG, SW0_PIN) == GPIO_LOW)
        panel_toggle_blocked();
}

#pragma vector=TIMER0_OVF_vect
__interrupt void timer0_ovf_isr(void)
{
    panel_tick = 1;
}

void main( void )
{
    gpio_init();
    panel_init();

    button_init(SW0_DDR, SW0_PORT, SW0_PIN);
    PCMSK2 |= (1 << PCINT22_BIT);
    PCICR  |= (1 << PCIE2_BIT);

    timer_init();
    timer_start(TIMER_PRESCALER_256);   
    __enable_interrupt();

    while(1)
    {
        if (panel_tick)
        {
            panel_tick = 0;
            panel_update();
        }
    }
}
