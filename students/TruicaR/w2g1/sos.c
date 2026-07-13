#include "gpio.h"
#include "led.h"
#include "sos.h"
#define DELAY 200000
#define LED0_PIN 7

void delay(long units)
{
    for (volatile long i = 0; i < units; i++);
}

void point(void)
{
    PowerOn_LED(LED0_PIN);
    delay(DELAY);
    PowerOff_LED(LED0_PIN);
    delay(DELAY);
}

void line(void)
{
    PowerOn_LED(LED0_PIN);
    delay(600000);
    PowerOff_LED(LED0_PIN);
    delay(DELAY);
}

void sos(void)
{
    for (int i = 0; i < 3; i++) point();
    for (int i = 0; i < 3; i++) line();
    for (int i = 0; i < 3; i++) point();
}