#include "iom324pb.h"
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"
#include "button.h"
#include "timer.h"

#define LED_COUNT               (5U)
#define TIMER_OVF_PER_SECOND    (4U)   /* 4 x 262 ~= 1s at prescaler 1024 */

typedef struct
{
    gpio_reg_t ddr;
    gpio_reg_t port;
    unsigned char pin;
} led_t;

static const led_t leds[LED_COUNT] =
{
    { LED0_DDR, LED0_PORT, LED0_PIN },
    { LED1_DDR, LED1_PORT, LED1_PIN },
    { LED2_DDR, LED2_PORT, LED2_PIN },
    { LED3_DDR, LED3_PORT, LED3_PIN },
    { LED4_DDR, LED4_PORT, LED4_PIN }
};

static volatile unsigned char timer_ovf_count = 0;
static volatile unsigned char second_tick = 0;

#pragma vector=TIMER0_OVF_vect
__interrupt void timer0_ovf_isr(void)
{
    timer_ovf_count++;
    if (timer_ovf_count >= TIMER_OVF_PER_SECOND)
    {
        timer_ovf_count = 0;
        second_tick = 1;
    }
}

void main( void )
{
    unsigned char i;
    unsigned char counting = 0;
    unsigned char leds_off = 0;
    unsigned char sw0_current;
    unsigned char sw0_previous = BUTTON_RELEASED;

    gpio_init();

    for (i = 0; i < LED_COUNT; i++)
    {
        led_init(leds[i].ddr, leds[i].pin);
        led_power_on(leds[i].port, leds[i].pin);   
    }

    button_init(SW0_DDR, SW0_PORT, SW0_PIN);
    timer_init();
    __enable_interrupt();

    while(1)
    {
        sw0_current = button_is_pressed(SW0_PIN_REG, SW0_PIN);

        if (!counting && (sw0_current == BUTTON_PRESSED) && (sw0_previous == BUTTON_RELEASED))
        {
            for (i = 0; i < LED_COUNT; i++)
                led_power_on(leds[i].port, leds[i].pin);

            counting = 1;
            leds_off = 0;
            timer_ovf_count = 0;
            second_tick = 0;
            timer_start(TIMER_PRESCALER_1024);
        }
        sw0_previous = sw0_current;

        if (counting && second_tick)
        {
            second_tick = 0;
            led_power_off(leds[leds_off].port, leds[leds_off].pin);
            leds_off++;

            if (leds_off >= LED_COUNT)
            {
                timer_stop();
                counting = 0;
            }
        }
    }
}
