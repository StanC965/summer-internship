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
extern volatile bool flag_10ms   ;
extern volatile bool flag_50ms   ;
extern volatile bool flag_100ms  ;
extern volatile bool flag_500ms  ;
extern volatile bool flag_1000ms ;
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  
/** \fn     void scheduler_flags_management(void);

    \brief      [ This function determine the ]  
*/
extern void scheduler_flags_management (void);

#endif

