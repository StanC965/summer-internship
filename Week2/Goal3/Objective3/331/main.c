#include "sos.h"
#include "button.h"
#include "intrinsics.h"

// LEDs
#define OLED_LED_1_2_DDR        (&DDRD)
#define OLED_LED_1_2_PORT       (&PORTD)
#define OLED_LED_1_PIN          5 
#define OLED_LED_2_PIN          4

#define OLED_LED_3_DDR          (&DDRA)
#define OLED_LED_3_PORT         (&PORTA)
#define OLED_LED_3_PIN          3

// Buttons
#define OLED_BUTTON_1_DDR       (&DDRC)
#define OLED_BUTTON_1_PORT      (&PORTC)
#define OLED_BUTTON_1_PINR      (&PINC)
#define OLED_BUTTON_1_PIN       1    

#define OLED_BUTTON_2_3_DDR     (&DDRA)
#define OLED_BUTTON_2_3_PORT    (&PORTA)
#define OLED_BUTTON_2_3_PINR    (&PINA)
#define OLED_BUTTON_2_PIN       0       
#define OLED_BUTTON_3_PIN       1 

// Interrupts
#define PCINT17                 1   
#define PCINT0                  0   
#define PCINT1                  1   

#define PCIE0                   0   
#define PCIE2                   2   

volatile unsigned char sos_active = 0;

#pragma vector = PCINT2_vect
__interrupt void oled_port_c_isr(void)
{
    if (button_is_pressed(OLED_BUTTON_1_PINR, OLED_BUTTON_1_PIN))
    {
        led_power_on(OLED_LED_1_2_PORT, OLED_LED_1_PIN);
    }
    else
    {
        led_power_off(OLED_LED_1_2_PORT, OLED_LED_1_PIN);
    }
}

#pragma vector = PCINT0_vect
__interrupt void oled_port_a_isr(void)
{
    if (button_is_pressed(OLED_BUTTON_2_3_PINR, OLED_BUTTON_2_PIN))
    {
        led_power_on(OLED_LED_1_2_PORT, OLED_LED_2_PIN);
    }
    else
    {
        led_power_off(OLED_LED_1_2_PORT, OLED_LED_2_PIN);
    }

    if (button_is_pressed(OLED_BUTTON_2_3_PINR, OLED_BUTTON_3_PIN))
    {
        led_power_on(OLED_LED_3_PORT, OLED_LED_3_PIN);
    }
    else
    {
        led_power_off(OLED_LED_3_PORT, OLED_LED_3_PIN);
    }
}

void oled_init_interrupt(void)
{
    led_init(OLED_LED_1_2_DDR, OLED_LED_1_PIN);
    led_init(OLED_LED_1_2_DDR, OLED_LED_2_PIN);
    led_init(OLED_LED_3_DDR, OLED_LED_3_PIN);
    
    led_power_off(OLED_LED_1_2_PORT, OLED_LED_1_PIN);
    led_power_off(OLED_LED_1_2_PORT, OLED_LED_2_PIN);
    led_power_off(OLED_LED_3_PORT, OLED_LED_3_PIN);

    button_init(OLED_BUTTON_1_DDR, OLED_BUTTON_1_PORT, OLED_BUTTON_1_PIN);
    button_init(OLED_BUTTON_2_3_DDR, OLED_BUTTON_2_3_PORT, OLED_BUTTON_2_PIN);
    button_init(OLED_BUTTON_2_3_DDR, OLED_BUTTON_2_3_PORT, OLED_BUTTON_3_PIN);
    
    PCMSK2 |= (1 << PCINT17); 
    PCMSK0 |= (1 << PCINT0) | (1 << PCINT1); 
    
    PCICR |= (1 << PCIE0) | (1 << PCIE2);
    
    __enable_interrupt();
}

void main()
{
  oled_init_interrupt();
    
    while (1)
    {
        
    }
}
