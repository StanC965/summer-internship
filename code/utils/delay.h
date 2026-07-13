#ifndef DELAY_H
#define DELAY_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  Module specific constant number zero */
#define SECOND      (100000U)
#define MILISECOND  (SECOND / 1000U)

/** \fn     void delay(long count)

    \brief      [ Introduces a delay of the specified duration. ]
    \param[in]  count [ the delay duration ]
    \param[out] [ None ]
    \return     [ None ]
*/
extern void delay(long count);

#endif /* DELAY_H */