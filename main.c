
#include "week1\Goal 2\adc.h"
#include "week1\Goal 2\timer.h"
#include "CarCrashDetection.h"


void main (void)
{
    led_init();
   btn_init();
   ADC_init();
   resolution(Rez8bit);
   InterruptADC();
   timer_init();
    while(1)
    {  
     unsigned char status =GetCarCrashDetectionStatus();
      airbag_dus(status);  
  }
}