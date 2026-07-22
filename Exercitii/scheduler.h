#ifndef SCHEDULER_H
#define SCHEDULER_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  time period of 50 ms */
#define PERIOD_OF_50MS                5U

/** \brief  time period of 100 ms */
#define PERIOD_OF_100MS                10U

/** \brief  time period of 500 ms */
#define PERIOD_OF_500MS                50U

/** \brief  time period of 1000 ms */
#define PERIOD_OF_1000MS                100U
/*
/** \brief pozitia de 10ms in "registrul scheduler" 
#define SH_FLAG_10MS                   (1 << 0)
*/
/*
/** \brief pozitia de 50ms in "registrul scheduler" 
#define SH_FLAG_50MS                   (1 << 1) 
*/
/* \brief pozitia de 100ms in "registrul scheduler" 
#define SH_FLAG_100MS                  (1 << 2)
*/
/* \brief pozitia de 500ms in "registrul scheduler"         =>>>>> daca foloseam bitmask
#define SH_FLAG_500MS                  (1 << 3) 
*/
/* \brief pozitia de 1000ms in "registrul scheduler"
#define SH_FLAG_1000MS                 (1 << 4) 
*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

typedef struct{
  unsigned char flag_10ms : 1;
  unsigned char flag_50ms : 1;
  unsigned char flag_100ms : 1;
  unsigned char flag_500ms : 1;
  unsigned char flag_1000ms : 1;
}scheduler_t;

extern volatile scheduler_t scheduler;

// extern volatile unsigned char scheduler;                    =>>>>>> daca foloseam bitmask
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

