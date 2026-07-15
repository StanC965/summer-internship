#ifndef SOS_C
#define SOS_C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "led.h"
#include "sos.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* Morse timing: a point is 1 unit, a line is 3 units */
#define SOS_TIME_UNIT       (6000UL)
#define SOS_POINT_TIME      (SOS_TIME_UNIT)
#define SOS_LINE_TIME       (SOS_TIME_UNIT * 3U)
#define SOS_SYMBOL_PAUSE    (SOS_TIME_UNIT)        /* pause between symbols */
#define SOS_LETTER_PAUSE    (SOS_TIME_UNIT * 3U)   /* pause between letters */

static void sos_delay(unsigned long count)
{
    volatile unsigned long i;
    for (i = 0; i < count; i++) { }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void sos_point(void)
{
    led_power_on();
    sos_delay(SOS_POINT_TIME);
    led_power_off();
    sos_delay(SOS_SYMBOL_PAUSE);
}

void sos_line(void)
{
    led_power_on();
    sos_delay(SOS_LINE_TIME);
    led_power_off();
    sos_delay(SOS_SYMBOL_PAUSE);
}

void sos_signal(void)
{

    sos_point();  sos_point();  sos_point();    /* letter S */
    sos_delay(SOS_LETTER_PAUSE);

    sos_line();   sos_line();   sos_line();     /* letter O */
    sos_delay(SOS_LETTER_PAUSE);

    sos_point();  sos_point();  sos_point();    /* letter S */
}

#endif
