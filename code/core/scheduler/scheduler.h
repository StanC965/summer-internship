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

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn      void scheduler_flags_management(void)
    \brief   [  ]
    \param   [ None ] 
    \return  [ None ]
    \details [  ]
*/
extern void scheduler_flags_management(void);

/** \fn      void scheduler_tasks_dispatcher(void)
    \brief   [  ]
    \param   [ None ] 
    \return  [ None ]
    \details [  ]
*/
extern void scheduler_tasks_dispatcher(void);

#endif /* SCHEDULER_H */
