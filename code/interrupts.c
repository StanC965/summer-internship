#include <iom324pb.h>
#include "button.h"
#include "led.h"
#include "delay.h"

volatile uint8_t button_event_detected = 0;

#pragma vector = PCINT2_vect
__interrupt void button_press_routine(void)
{
    button_event_detected = 1;
}
