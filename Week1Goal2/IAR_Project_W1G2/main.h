#ifndef MAIN_H
#define MAIN_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Module Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
 *  \file       main.h
 *  \brief      main module interface.
 *  \author     Chirila Viorel
 *  \date       12.07.2026
 */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <iom324pb.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* None */

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
void delay(unsigned long count);

#endif