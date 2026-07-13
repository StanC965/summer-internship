#include "sos.h"
#include "button.h"
#include "intrinsics.h"

#define PCINT22             6  
#define PCIE2               2
#define TIME_LETTER_GAP     700000UL

volatile unsigned char sos_active = 0;

#pragma vector = PCINT2_vect
__interrupt void switch0_isr(void)
{
    if (gpio_read_pin(BUTTON_SW0_PINR, BUTTON_SW0_PIN) == 0)
    {
        sos_active = !sos_active;
        
        if (sos_active == 0)
        {
            led_power_off(LED_LED0_PORT, LED_LED0_PIN);
        }
    }
}

void init_button_interrupt(void)
{
    button_init(BUTTON_SW0_DDR, BUTTON_SW0_PORT, BUTTON_SW0_PIN);
    
    PCMSK2 |= (1 << PCINT22);
    
    PCICR |= (1 << PCIE2);
    
    __enable_interrupt();
}

void main()
{
  led_init(LED_LED0_DDR, LED_LED0_PIN);
  led_power_off(LED_LED0_PORT, LED_LED0_PIN); 
  init_button_interrupt();
  
  while (1)
  {
    if (sos_active == 1)
        {
            sos_play_letter_s();            
            for (unsigned long i = 0; i < TIME_LETTER_GAP; i++) {
                if (sos_active == 0) break;
            }
            if (sos_active == 0) continue;

            sos_play_letter_o();            
            for (unsigned long i = 0; i < TIME_LETTER_GAP; i++) {
                if (sos_active == 0) break;
            }
            if (sos_active == 0) continue;

            sos_play_letter_s();
            if (sos_active == 0) continue;
            for (unsigned long i = 0; i < TIME_LETTER_GAP; i++) {
                if (sos_active == 0) break;
            }
        }
  }
}