#ifndef INTERRUPTS_H
#define INTERRUPTS_H

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Module Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
 *  \file       interrupts.h
 *  \brief      interrupts interface.
 *  \author     Chirila Viorel
 *  \date       18.07.2026
 */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "Modules/button.h"
#include "Modules/adc.h"
#include "Modules/led.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** \brief  Interrupts flags structure */
typedef struct {
    unsigned char sw0_pressed;
    unsigned char btn1_pressed;
    unsigned char btn2_pressed;
    unsigned char btn3_pressed;
} button_events_t;

/** \brief  Interrupts flags variable */
extern volatile button_events_t button_events;

/** \brief  Overflow count */
extern volatile unsigned long tc0_overflow_count;

extern volatile unsigned char countdown_active; 
extern volatile unsigned char seconds_left;

/** \brief  Compare count */
extern volatile unsigned long tc0_compare_count;
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



#endif