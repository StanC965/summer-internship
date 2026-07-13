#ifndef SOS_C
#define SOS_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "led.h"
#include "delay.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Static private functions
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
static void sos_point(led_id_t led_id){
    led_blink_custom(led_id, 1, SECOND / 2, SECOND / 2);
}

static void sos_line(led_id_t led_id){
    led_blink_custom(led_id, 1, SECOND * 2, SECOND / 2);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Implementation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void sos_play(led_id_t led_id){
    sos_point(led_id);
    sos_point(led_id);
    sos_point(led_id);

    delay(SECOND);

    sos_line(led_id);
    sos_line(led_id);
    sos_line(led_id);

    delay(SECOND);
    
    sos_point(led_id);
    sos_point(led_id);
    sos_point(led_id);
}

#endif /* SOS_C */
