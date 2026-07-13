#ifndef SOS_C
#define SOS_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Module Information
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
 *  \file       sos.c
 *  \brief      sos app implementation.
 *  \author     Chirila Viorel
 *  \date       13.07.2026
 */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "sos.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private objects
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* None */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private function declarations
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

static void point(led_uint8_t led){
  PowerOn_LED(led);
  delay(ONE_SECOND_DELAY);
  PowerOff_LED(led);
}

static void line(led_uint8_t led){
  PowerOn_LED(led);
  delay(ONE_SECOND_DELAY*3);
  PowerOff_LED(led);
}

/* None */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Public function implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void SOS_play(led_uint8_t led){
  LED_Init();
  
  point(led);
  delay(ONE_SECOND_DELAY);
  point(led);
  delay(ONE_SECOND_DELAY);
  point(led);
  delay(ONE_SECOND_DELAY);
  
  line(led);
  delay(ONE_SECOND_DELAY);
  
  point(led);
  delay(ONE_SECOND_DELAY);
  point(led);
  delay(ONE_SECOND_DELAY);
  point(led);
  
  delay(ONE_SECOND_DELAY*2);
}

#endif