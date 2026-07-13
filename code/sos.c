#ifndef SOS_C
#define SOS_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "led.h"
#include "delay.h"

#define TIME_UNIT (SECOND / 2U)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
static void sos_point(led_id_t led_id){
    led_blink_custom(led_id, 1, TIME_UNIT, TIME_UNIT);
}

static void sos_line(led_id_t led_id){
    led_blink_custom(led_id, 1, 3 * TIME_UNIT, TIME_UNIT);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void sos_play(led_id_t led_id){
    sos_point(led_id);
    sos_point(led_id);
    sos_point(led_id);

    delay(2 * TIME_UNIT);

    sos_line(led_id);
    sos_line(led_id);
    sos_line(led_id);

    delay(2 * TIME_UNIT);
    
    sos_point(led_id);
    sos_point(led_id);
    sos_point(led_id);
   
}

#endif /* SOS_C */
