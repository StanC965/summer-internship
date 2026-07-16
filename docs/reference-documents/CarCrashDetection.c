#include "CarCrashDetection.h"

static unsigned char __CarCrashEventStatus;

unsigned char GetCarCrashDetectionStatus(void)
{
  __CarCrashEventStatus=NO_CRASH;
  __CarCrashEventStatus=rand()%2;/*reports 1 or 0 as car crash is detected or not*/
  return __CarCrashEventStatus;
}
