#include "sos.h"
#include "iom324pb.h"
#include "intrinsics.h"

#pragma vector = PCINT2_vect
__interrupt void Switch0_ISR(void)
/* the amazing routine for serving the interrupt caused by my button press */
{
    PowerOn_LED(LED0_PORT, LED0_PIN);
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
    
  }
}