#include "pwm.h"
#include "gpio.h"

void pwm_init(void)
{
    gpio_set_direction(&DDRB, 3, GPIO_OUTPUT);
    
    TCCR0A = 0x00;
    TCCR0B = 0x00;
    
    // Setup WGM bits for Fast PWM Mode 3 (TOP = 0xFF)
    TCCR0A |= (1 << 1) | (1 << 0);
    
    // Configure Non-Inverting Output Mode on OC0A
    TCCR0A |= (1 << 7);
    
    // duty cycle 0% initially
    OCR0A = 0x00;
    TCNT0 = 0x00;
}

void pwm_set_duty_cycle(unsigned char duty_percentage)
{
    unsigned char compare_value = 0;
    
    if (duty_percentage > 100)
    {
        duty_percentage = 100;
    }
    
    // Calculate register value: (Duty % * 255) / 100
    compare_value = (duty_percentage * 255) / 100;
    
    // Atomic Write to the 8-bit Compare Register
    OCR0A = compare_value;
    
    // Start Timer0 with Prescaler 1
    TCCR0B |= (1 << 0);
}

void pwm_dc(unsigned char param)
{
    unsigned char compare_value = 0;
    
    if (param > 100)
    {
        param = 100;
    }
    
    compare_value = (param * 255U) / 100;
    
    OCR0A = compare_value;
    
    TCCR0B |= (1 << 0);
}