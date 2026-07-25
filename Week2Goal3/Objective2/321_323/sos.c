#ifndef SOS_C
#define SOS_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "gpio.h"
#include "led.h"
#include "sos.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* Morse timing: a point is 1 unit, a line is 3 units */
#define SOS_TIME_UNIT       (6000UL)
#define SOS_POINT_TIME      (SOS_TIME_UNIT)
#define SOS_LINE_TIME       (SOS_TIME_UNIT * 3U)
#define SOS_SYMBOL_PAUSE    (SOS_TIME_UNIT)
#define SOS_LETTER_PAUSE    (SOS_TIME_UNIT * 3U)
#define SOS_ONE_SECOND      (30000UL)

static void sos_delay(unsigned long count)
{
    volatile unsigned long i;
    for (i = 0; i < count; i++) { }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void sos_point(gpio_reg_t port, unsigned char pin)
{
    led_power_on(port, pin);
    sos_delay(SOS_POINT_TIME);
    led_power_off(port, pin);
    sos_delay(SOS_SYMBOL_PAUSE);
}

void sos_line(gpio_reg_t port, unsigned char pin)
{
    led_power_on(port, pin);
    sos_delay(SOS_LINE_TIME);
    led_power_off(port, pin);
    sos_delay(SOS_SYMBOL_PAUSE);
}

void sos_signal(gpio_reg_t port, unsigned char pin)
{
    sos_point(port, pin);  sos_point(port, pin);  sos_point(port, pin);   /* letter S */
    sos_delay(SOS_LETTER_PAUSE);

    sos_line(port, pin);   sos_line(port, pin);   sos_line(port, pin);    /* letter O */
    sos_delay(SOS_LETTER_PAUSE);

    sos_point(port, pin);  sos_point(port, pin);  sos_point(port, pin);   /* letter S */
}

void sos_pause(void)
{
    sos_delay(SOS_ONE_SECOND);
}

#endif
