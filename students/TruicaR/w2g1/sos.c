#include "gpio.h"
#include "led.h"
#include "sos.h"

#define SOS_DOT_DELAY   200000
#define SOS_DASH_DELAY  600000
#define LED0_PIN        7

static void sos_delay(long units)
{
    for (volatile long i = 0; i < units; i++);
}

static void sos_dot(void)
{
    led_on(LED0_PIN);
    sos_delay(SOS_DOT_DELAY);
    led_off(LED0_PIN);
    sos_delay(SOS_DOT_DELAY);
}

static void sos_dash(void)
{
    led_on(LED0_PIN);
    sos_delay(SOS_DASH_DELAY);
    led_off(LED0_PIN);
    sos_delay(SOS_DOT_DELAY);
}

void sos_play(void)
{
    for (int i = 0; i < 3; i++) sos_dot();
    for (int i = 0; i < 3; i++) sos_dash();
    for (int i = 0; i < 3; i++) sos_dot();
}