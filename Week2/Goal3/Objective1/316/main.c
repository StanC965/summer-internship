#include "sos.h"
#include "intrinsics.h"

volatile unsigned char sos_active = 0;

#pragma vector = PCINT2_vect
__interrupt void Switch0_ISR(void)
{
    if (read_pin(&PINC, 6) == 0)
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
    set_direction(&DDRC, 6, INPUT);    
    set_pin(&PORTC, 6);
    
    // PCINT22 is Bit 6 of PCMSK2
    PCMSK2 |= (1 << 6);
    
    // PCIE2 is Bit 2 of PCICR
    PCICR |= (1 << 2);
    
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