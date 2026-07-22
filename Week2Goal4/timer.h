#ifndef TIMER_H
#define TIMER_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define TIMER_STOP              (0x00U)
#define TIMER_PRESCALER_1       (0x01U)
#define TIMER_PRESCALER_8       (0x02U)
#define TIMER_PRESCALER_64      (0x03U)
#define TIMER_PRESCALER_256     (0x04U)
#define TIMER_PRESCALER_1024    (0x05U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Normal mode, overflow interrupt (TOP = 0xFF) */
extern void timer_init_normal(void);

/** \brief  CTC mode, compare match A interrupt (TOP = OCR0A)
    \param[in]  top  value loaded in OCR0A
*/
extern void timer_init_ctc(unsigned char top);

/** \brief  Start TC0 with the given prescaler */
extern void timer_start(unsigned char prescaler);

extern void timer_stop(void);

#endif
