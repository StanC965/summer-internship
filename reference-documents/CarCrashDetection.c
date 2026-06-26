#include "CarCrashDetection.h"

static unsigned char __CarCrashEventStatus;

unsigned char GetCarCrashDetectionStatus(void)
{
  __CarCrashEventStatus=NO_CRASH;
  srand(31);/*initializes with 31 the random generator*/
  __CarCrashEventStatus=rand()%2;/*reports 1 or 0 as car crash is detected or not*/
  return __CarCrashEventStatus;
}
