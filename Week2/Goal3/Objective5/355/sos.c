#ifndef SOS_C
#define SOS_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "sos.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Implementation                                                            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void sos_init(void)
{
    led_configure_pin(LED_LED0_DDR, LED_LED0_PIN);
    led_power_off(LED_LED0_PORT, LED_LED0_PIN);
}

void sos_play_point(void)
{
    led_power_on(LED_LED0_PORT, LED_LED0_PIN);
    for (unsigned long i = 0; i < SOS_TIME_POINT_DURATION; i++);
    
    led_power_off(LED_LED0_PORT, LED_LED0_PIN);
    for (unsigned long i = 0; i < SOS_TIME_ELEMENT_GAP; i++);
}

void sos_play_line(void)
{
    led_power_on(LED_LED0_PORT, LED_LED0_PIN);
    for (unsigned long i = 0; i < SOS_TIME_LINE_DURATION; i++);
    
    led_power_off(LED_LED0_PORT, LED_LED0_PIN);
    for (unsigned long i = 0; i < SOS_TIME_ELEMENT_GAP; i++); 
}

void sos_play_letter_s(void)
{
    sos_play_point();
    sos_play_point();
    sos_play_point();
}

void sos_play_letter_o(void)
{
    sos_play_line();
    sos_play_line();
    sos_play_line();
}

void sos_play_sos(void)
{
    sos_play_letter_s();
    
    for (unsigned long i = 0; i < SOS_TIME_CHARACTER_GAP; i++);

    sos_play_letter_o();
    
    for (unsigned long i = 0; i < SOS_TIME_CHARACTER_GAP; i++);

    sos_play_letter_s();
    
    for (unsigned long i = 0; i < SOS_TIME_CHARACTER_GAP; i++);
}

#endif