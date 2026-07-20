#ifndef SCHEDULER_H
#define SCHEDULER_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdint.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define SCHEDULER_TICK_MS             (10U)
#define SCHEDULER_TICK_FOR_50MS       (50U / SCHEDULER_TICK_MS)
#define SCHEDULER_TICK_FOR_100MS      (100U / SCHEDULER_TICK_MS)
#define SCHEDULER_TICK_FOR_500MS      (500U / SCHEDULER_TICK_MS)
#define SCHEDULER_TICK_FOR_1000MS     (1000U / SCHEDULER_TICK_MS)

extern volatile uint8_t scheduler_flag_10ms = 0;
extern volatile uint8_t scheduler_flag_50ms = 0;
extern volatile uint8_t scheduler_flag_100ms = 0;
extern volatile uint8_t scheduler_flag_500ms = 0;
extern volatile uint8_t scheduler_flag_1000ms = 0;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn      scheduler_flags_management(void)
    \brief   [  ]
    \param   [ None ] 
    \return  [ None ]
    \details [  ]
*/
extern void scheduler_flags_management(void);

#endif /* SCHEDULER_H */
