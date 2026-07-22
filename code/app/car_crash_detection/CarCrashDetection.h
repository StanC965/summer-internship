#ifndef CAR_CRASH_DETECTION_H
#define CAR_CRASH_DETECTION_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdlib.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define CRASH           (1u)
#define NO_CRASH        (0u)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     unsigned char GetCarCrashDetectionStatus(void)

    \brief      [ Returns the car crash event status. ]
    \param[in]  [ None ]
    \param[out] [ None ]
    \return     [ The car crash event status: CRASH (1) or NO CRASH (0). ]
*/

extern unsigned char GetCarCrashDetectionStatus(void);

#endif /* CAR_CRASH_DETECTION_H */