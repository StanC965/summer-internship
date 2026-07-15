#ifndef SOS_H
#define SOS_H
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*  Public functions            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Signal one Morse point on LED0 (short light) */
extern void sos_point(void);

/** \brief  Signal one Morse line on LED0 (long light, 3x a point) */
extern void sos_line(void);

/** \brief  Signal the complete SOS sequence: 3 points, 3 lines, 3 points */
extern void sos_signal(void);

#endif
