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

/** \brief  Returns 1 once when the period elapsed, then clears it (consume) */
extern unsigned char scheduler_flag_10ms(void);
extern unsigned char scheduler_flag_50ms(void);
extern unsigned char scheduler_flag_100ms(void);
extern unsigned char scheduler_flag_500ms(void);
extern unsigned char scheduler_flag_1000ms(void);

#endif
