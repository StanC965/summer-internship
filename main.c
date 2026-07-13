#include <iom324pb.h>
#include <intrinsics.h>
#include "week1\Goal 2\button.h"

#pragma vector=PCINT2_vect
__interrupt void buton_apasat(void)

{
  if(PINC_PINC6==0){
  PORTC_PORTC7^=1;
  }
}

void main (void)
{
   DDRC=0x80;
   PORTC=0xc0;
   PCMSK2_Bit6=1; 
   PCICR_PCIE2=1; 
   SREG_I=1;
    while(1)
    {
     
      
    }
    
  
  }
