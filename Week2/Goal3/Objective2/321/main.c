#include "sos.h"
#include "button.h"
#include "intrinsics.h"

#define PCINT22       6  
#define PCIE2         2

volatile unsigned char sos_active = 0;

#pragma vector = PCINT2_vect
__interrupt void Switch0_ISR(void)
{
    if (read_pin(SW0_PINR, SW0_PIN) == 0)
    {
        sos_active = !sos_active;
        
        if (sos_active == 0)
        {
            PowerOff_LED(LED0_PORT, LED0_PIN);
        }
    }
}

void Init_Button_Interrupt(void)
{
    Init_Button(SW0_DDR, SW0_PORT, SW0_PIN);
    
    PCMSK2 |= (1 << PCINT22);
    
    PCICR |= (1 << PCIE2);
    
    __enable_interrupt();
}

void main()
{
  Init_LED(LED0_DDR, LED0_PIN);
  PowerOff_LED(LED0_PORT, LED0_PIN);
  
  Init_Button_Interrupt();
  
  while (1)
  {
    if (sos_active == 1)
        {
            Play_Letter_S();            
            for (unsigned long i = 0; i < 300000; i++) {
                if (sos_active == 0) break;
            }
            if (sos_active == 0) continue;

            Play_Letter_O();            
            for (unsigned long i = 0; i < 300000; i++) {
                if (sos_active == 0) break;
            }
            if (sos_active == 0) continue;

            Play_Letter_S();
            if (sos_active == 0) continue;
            for (unsigned long i = 0; i < 300000; i++) {
                if (sos_active == 0) break;
            }
        }
  }
}