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
#include "Modules/led.h"
#include "Utils/utils.h"
#include "Modules/gpio.h"
#include "Modules/button.h"
#include "sos.h"
#include "ISR/interrupts.h"
#include "HVAC.h"
#include <intrinsics.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Exported types and values
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define MID_LIGHT       127
#define FULL_LIGHT_LIMIT      63
#define SEMI_LIGHT_LIMIT      127
#define SEMI_DARK_LIMIT      191

/* None */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#endif