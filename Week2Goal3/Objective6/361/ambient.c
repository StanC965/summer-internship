#ifndef AMBIENT_C
#define AMBIENT_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "iom324pb.h"
#include "led.h"
#include "ambient.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* Midpoint of the 0..255 reading range.
   My observed range is ~0x03 (bright) .. ~0xF5 (dark), so 128 sits nicely in
   the middle; tune it if you want it exactly on your board's range. */
#define AMBIENT_MIDPOINT    (128U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void ambient_init(void)
{
    /* all application LEDs as outputs, initial state OFF */
    led_init(LED0_DDR, LED0_PIN);
    led_init(LED1_DDR, LED1_PIN);
    led_init(LED2_DDR, LED2_PIN);
    led_init(LED3_DDR, LED3_PIN);

    led_power_off(LED0_PORT, LED0_PIN);
    led_power_off(LED1_PORT, LED1_PIN);
    led_power_off(LED2_PORT, LED2_PIN);
    led_power_off(LED3_PORT, LED3_PIN);
}

void ambient_indicate_threshold(unsigned char light)
{
    /* high value = dark on this board, so LED0 lights up in the dark */
    if (light > AMBIENT_MIDPOINT)
        led_power_on(LED0_PORT, LED0_PIN);
    else
        led_power_off(LED0_PORT, LED0_PIN);
}

#endif
