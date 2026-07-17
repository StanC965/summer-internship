#ifndef SCHEDULER_H
#define SCHEDULER_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  time period of 50 ms */
#define PERIOD_OF_50MS                5U

/** \brief  time period of 100 ms */
#define PERIOD_OF_100MS                10U

/** \brief  time period of 500 ms */
#define PERIOD_OF_500MS                50U

/** \brief  time period of 1000 ms */
#define PERIOD_OF_1000MS                100U

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Global variables (flags)
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
extern volatile _Bool flag_10ms   ;
extern volatile _Bool flag_50ms   ;
extern volatile _Bool flag_100ms  ;
extern volatile _Bool flag_500ms  ;
extern volatile _Bool flag_1000ms ;
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  
/** \fn     void scheduler_flags_management(void);

    \brief      [ This function keeps track of all flags declared in this header based on a 10 ms  spaced ISR]  
*/
extern void scheduler_flags_management (void);

/** \fn     void schedule_tasks_dispatcher(void);
schedule_tasks_dispatcher
    \brief      [ This function provides the architecture of a scheduler]  
*/
extern void schedule_tasks_dispatcher (void);

#endif

