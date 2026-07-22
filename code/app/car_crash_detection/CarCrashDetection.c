#ifndef CAR_CRASH_DETECTION_C
#define CAR_CRASH_DETECTION_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "CarCrashDetection.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects & functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

static unsigned char __CarCrashEventStatus;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

unsigned char GetCarCrashDetectionStatus(void)
{
  __CarCrashEventStatus = NO_CRASH;
  rand();
  __CarCrashEventStatus = rand() % 2;
  return __CarCrashEventStatus;
}

#endif /* CAR_CRASH_DETECTION_C */