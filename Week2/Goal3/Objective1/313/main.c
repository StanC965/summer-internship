#include "sos.h"
#include "iom324pb.h"

#pragma vector=INT2_vect
__interrupt void my_routine(void)
/* the amazing routine for serving the interrupt caused by my button press */
{
    PowerOn_LED(LED0_PORT, LED0_PIN);
}

void main()
{
  while (1)
  {
    
  }
}