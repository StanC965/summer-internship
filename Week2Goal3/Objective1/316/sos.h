#ifndef SOS_H
#define SOS_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  Return values used to signal that the sequence was stopped */
#define SOS_RUNNING         (0x00U)
#define SOS_STOPPED         (0x01U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Signal one Morse point on LED0 (short light) */
extern void sos_point(void);

/** \brief  Signal one Morse line on LED0 (long light, 3x a point) */
extern void sos_line(void);

/** \brief  Signal the complete SOS sequence: 3 points, 3 lines, 3 points */
extern void sos_signal(void);

/** \brief  Pause of 1 second between two SOS sequences */
extern void sos_pause(void);

/** \brief  Signal SOS, checking the button between symbols
    \return SOS_STOPPED if a new button press was detected during the sequence,
            SOS_RUNNING otherwise
    \details The button is polled after each symbol, so a new press can interrupt
             the sequence. This is the polling "resolution": the button must be held
             long enough to be seen between two symbols.
*/
extern unsigned char sos_signal_interruptible(void);

#endif
