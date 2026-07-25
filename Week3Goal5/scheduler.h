#ifndef SCHEDULER_H
#define SCHEDULER_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Clears the tick counter and all period flags */
extern void scheduler_init(void);

/** \brief  Builds periodic flags from the 10ms tick. Called from the system tick ISR. */
extern void scheduler_flags_management(void);

#endif
