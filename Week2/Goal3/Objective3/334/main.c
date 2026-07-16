#include "sos.h"
#include "button.h"
#include "intrinsics.h"

// ONBOARD
#define ONBOARD_LED0_DDR        (&DDRC)
#define ONBOARD_LED0_PORT       (&PORTC)
#define ONBOARD_LED0_PIN        7

#define ONBOARD_SW0_DDR         (&DDRC)
#define ONBOARD_SW0_PORT        (&PORTC)
#define ONBOARD_SW0_PINR        (&PINC)
#define ONBOARD_SW0_PIN         6

// OLED
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
#define PCINT22_SW0             6
#define PCINT17_SW1             1   
#define PCINT0_SW2              0   
#define PCINT1_SW3              1   

#define PCIE0_PORT_A            0   
#define PCIE2_PORT_C            2   

volatile unsigned char bmw_panel_blocked = 0;

void fast_blink_led0();

#pragma vector = PCINT2_vect
__interrupt void port_c_isr(void)
{
    if (button_is_pressed(ONBOARD_SW0_PINR, ONBOARD_SW0_PIN))
    {
        bmw_panel_blocked = !bmw_panel_blocked;
        
        if (bmw_panel_blocked)
        {
            led_power_off(OLED_LED_1_2_PORT, OLED_LED_1_PIN);
            led_power_off(OLED_LED_1_2_PORT, OLED_LED_2_PIN);
            led_power_off(OLED_LED_3_PORT, OLED_LED_3_PIN);
            
            led_power_on(ONBOARD_LED0_PORT, ONBOARD_LED0_PIN);
        }
        else
        {
            led_power_off(ONBOARD_LED0_PORT, ONBOARD_LED0_PIN);
        }
        return;
    }
    
    if (button_is_pressed(OLED_BUTTON_1_PINR, OLED_BUTTON_1_PIN))
    {
        if (bmw_panel_blocked)
        {
            fast_blink_led0();
            
            led_power_on(ONBOARD_LED0_PORT, ONBOARD_LED0_PIN);
        }
        else
        {
            led_toggle(OLED_LED_1_2_PORT, OLED_LED_1_PIN);
        }
    }
}

#pragma vector = PCINT0_vect
__interrupt void oled_port_a_isr(void)
{
    if (button_is_pressed(OLED_BUTTON_2_3_PINR, OLED_BUTTON_2_PIN))
    {
        if (bmw_panel_blocked)
        {
            fast_blink_led0();
            
            led_power_on(ONBOARD_LED0_PORT, ONBOARD_LED0_PIN); 
        }
        else
        {
            led_toggle(OLED_LED_1_2_PORT, OLED_LED_2_PIN);
        }
    }

    if (button_is_pressed(OLED_BUTTON_2_3_PINR, OLED_BUTTON_3_PIN))
    {
        if (bmw_panel_blocked)
        {
            fast_blink_led0();
            
            led_power_on(ONBOARD_LED0_PORT, ONBOARD_LED0_PIN); 
        }
        else
        {
            led_toggle(OLED_LED_3_PORT, OLED_LED_3_PIN);
        }
    }
}

void init_system(void)
{
    led_init(ONBOARD_LED0_DDR, ONBOARD_LED0_PIN);
    led_init(OLED_LED_1_2_DDR, OLED_LED_1_PIN);
    led_init(OLED_LED_1_2_DDR, OLED_LED_2_PIN);
    led_init(OLED_LED_3_DDR, OLED_LED_3_PIN);
    
    led_power_off(ONBOARD_LED0_PORT, ONBOARD_LED0_PIN);
    led_power_off(OLED_LED_1_2_PORT, OLED_LED_1_PIN);
    led_power_off(OLED_LED_1_2_PORT, OLED_LED_2_PIN);
    led_power_off(OLED_LED_3_PORT, OLED_LED_3_PIN);

    button_init(ONBOARD_SW0_DDR, ONBOARD_SW0_PORT, ONBOARD_SW0_PIN);
    button_init(OLED_BUTTON_1_DDR, OLED_BUTTON_1_PORT, OLED_BUTTON_1_PIN);
    button_init(OLED_BUTTON_2_3_DDR, OLED_BUTTON_2_3_PORT, OLED_BUTTON_2_PIN);
    button_init(OLED_BUTTON_2_3_DDR, OLED_BUTTON_2_3_PORT, OLED_BUTTON_3_PIN);
    
    PCMSK2 |= (1 << PCINT22_SW0) | (1 << PCINT17_SW1);
    PCMSK0 |= (1 << PCINT0_SW2) | (1 << PCINT1_SW3); 
    
    PCICR |= (1 << PCIE0_PORT_A) | (1 << PCIE2_PORT_C);
    
    __enable_interrupt();
}

void fast_blink_led0()
{
  led_blink_fast(ONBOARD_LED0_PORT, ONBOARD_LED0_PIN);
  led_blink_fast(ONBOARD_LED0_PORT, ONBOARD_LED0_PIN);
  led_blink_fast(ONBOARD_LED0_PORT, ONBOARD_LED0_PIN);
}

void main()
{
  init_system();
    
    while (1)
    {
        
    }
}
