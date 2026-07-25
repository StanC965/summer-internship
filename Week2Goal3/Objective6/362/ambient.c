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

/* Midpoint of the 0..255 reading range.*/
#define AMBIENT_MIDPOINT        (128U)

#define AMBIENT_LEVEL_BRIGHT    (64U)     /* light <= this  -> full light  */
#define AMBIENT_LEVEL_MID       (128U)    /* light <= this  -> semi-light  */
#define AMBIENT_LEVEL_DARK      (192U)    /* light <= this  -> semi-dark   */
                                          /* light  > this  -> full dark   */

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
    /* high value = dark */
    if (light > AMBIENT_MIDPOINT)
        led_power_on(LED0_PORT, LED0_PIN);
    else
        led_power_off(LED0_PORT, LED0_PIN);
}

void ambient_indicate_level(unsigned char light)
{
    /* start with the whole bar off */
    led_power_off(LED1_PORT, LED1_PIN);
    led_power_off(LED2_PORT, LED2_PIN);
    led_power_off(LED3_PORT, LED3_PIN);

    if (light <= AMBIENT_LEVEL_BRIGHT)          /* full light -> 3 LEDs */
    {
        led_power_on(LED1_PORT, LED1_PIN);
        led_power_on(LED2_PORT, LED2_PIN);
        led_power_on(LED3_PORT, LED3_PIN);
    }
    else if (light <= AMBIENT_LEVEL_MID)        /* semi-light -> 2 LEDs */
    {
        led_power_on(LED1_PORT, LED1_PIN);
        led_power_on(LED2_PORT, LED2_PIN);
    }
    else if (light <= AMBIENT_LEVEL_DARK)       /* semi-dark -> 1 LED */
    {
        led_power_on(LED1_PORT, LED1_PIN);
    }
    /* else: full dark -> all stay off */
}

#endif
