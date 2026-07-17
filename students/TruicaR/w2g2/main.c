#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "CarCrashDetection.h"
#include <intrinsics.h>

#define AIRBAG_LED_PIN       5   
#define MATCHES_TO_TRIGGER   6   

static volatile unsigned char match_count = 0;

#pragma vector = TIMER0_COMPA_vect
__interrupt void tc0_compa_isr(void)
{
    match_count++;
    if (match_count >= MATCHES_TO_TRIGGER)
    {
        led_on(&PORTD, AIRBAG_LED_PIN);  
        TCCR0B_CS00 = 0;                 
        TIMSK0_OCIE0A = 0;
    }
}

void main(void)
{
    unsigned char status;

    gpio_set_direction(&DDRD, AIRBAG_LED_PIN, 1);
    led_off(&PORTD, AIRBAG_LED_PIN);

    TCCR0A_WGM01 = 1;
    TCCR0A_WGM00 = 0;
    TCCR0B_WGM02 = 0;
    OCR0A = 127;
    TIMSK0_OCIE0A = 1;

    __enable_interrupt();

    status = GetCarCrashDetectionStatus();

    if (status == CRASH)
    {
        match_count = 0;
        TCNT0 = 0;
        TCCR0B_CS00 = 1;  
    }

    while (1) {}
}