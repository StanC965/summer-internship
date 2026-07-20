#ifndef DELAY_H
#define DELAY_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \brief  Module specific constant number zero */
#define SECOND     (100000U)
/** \brief  Module specific constant number one */
#define MILISECOND (SECOND / 1000U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void delay(long count)

    \brief      [ Introduces a delay of the specified duration. ]
    \param[in]  count [ the delay duration ]
    \param[out] [ None ]
    \return     [ None ]
    \details    [ The delay function is measured in raw, calibrated software
                 loop iterations. The actual time delay will depend on the 
                 system clock frequency and the compiler optimizations. ]
*/
extern void delay(long count);

#endif /* DELAY_H */