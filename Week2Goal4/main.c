#include "iom324pb.h"
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"
#include "timer.h"

#define WAVE_TOP        (195U)   /
#define WAVE_SEGMENTS   (4U)

typedef struct
{
    unsigned char level;     
    unsigned char matches;   
} wave_segment_t;

static const wave_segment_t wave[WAVE_SEGMENTS] =
{
    { 1, 4  },   /* 200ms HIGH */
    { 0, 6  },   /* 300ms LOW  */
    { 1, 10 },   /* 500ms HIGH */
    { 0, 4  }    /* 200ms LOW  */
};

static volatile unsigned char seg_index = 0;
static volatile unsigned char match_count = 0;

static void wave_apply_level(unsigned char level)
{
    if (level)
        led_power_on(LED0_PORT, LED0_PIN);
    else
        led_power_off(LED0_PORT, LED0_PIN);
}

#pragma vector=TIMER0_COMPA_vect
__interrupt void timer0_compa_isr(void)
{
    match_count++;
    if (match_count >= wave[seg_index].matches)
    {
        match_count = 0;
        seg_index++;
        if (seg_index >= WAVE_SEGMENTS)
            seg_index = 0;

        wave_apply_level(wave[seg_index].level);
    }
}

void main( void )
{
    gpio_init();
    led_init(LED0_DDR, LED0_PIN);

    seg_index = 0;
    match_count = 0;
    wave_apply_level(wave[seg_index].level);  

    timer_init_ctc(WAVE_TOP);
    __enable_interrupt();
    timer_start(TIMER_PRESCALER_256);

    while(1)
    {
    }
}
