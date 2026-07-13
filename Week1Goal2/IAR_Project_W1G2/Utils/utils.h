#ifndef UTILS_H
#define UTILS_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Module Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
 *  \file       utils.h
 *  \brief      utils module interface.
 *  \author     Chirila Viorel
 *  \date       13.07.2026
 */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief Time */
#define SECOND     (100000L)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \fn     void delay(unsigned long count)

    \brief      Sets software delay
    \param[in]  delay
    \param[out] None.
    \return     None.
    \details    Softare delay
*/
extern void delay(unsigned long count);

#endif