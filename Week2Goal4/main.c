#include "iom324pb.h"
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"
#include "button.h"
#include "timer.h"

#define TIMER_PRESCALER_COUNT   (5U)

static const unsigned char timer_prescalers[TIMER_PRESCALER_COUNT] =
{
    TIMER_PRESCALER_1,
    TIMER_PRESCALER_8,
    TIMER_PRESCALER_64,
    TIMER_PRESCALER_256,
    TIMER_PRESCALER_1024
};

#pragma vector=TIMER0_OVF_vect
__interrupt void timer0_ovf_isr(void)
{
    led_toggle(LED0_PORT, LED0_PIN);
}

void main( void )
{
    unsigned char prescaler_index = 0;
    unsigned char sw0_previous = BUTTON_RELEASED;
    unsigned char sw0_current;

    gpio_init();
    led_init(LED0_DDR, LED0_PIN);
    led_power_off(LED0_PORT, LED0_PIN);
    button_init(SW0_DDR, SW0_PORT, SW0_PIN);

    timer_init();
    __enable_interrupt();
    timer_start(timer_prescalers[prescaler_index]);

    while(1)
    {
        sw0_current = button_is_pressed(SW0_PIN_REG, SW0_PIN);

        if ((sw0_current == BUTTON_PRESSED) && (sw0_previous == BUTTON_RELEASED))
        {
            prescaler_index++;
            if (prescaler_index >= TIMER_PRESCALER_COUNT)
                prescaler_index = 0;

            timer_start(timer_prescalers[prescaler_index]);
        }

        sw0_previous = sw0_current;
    }
}
