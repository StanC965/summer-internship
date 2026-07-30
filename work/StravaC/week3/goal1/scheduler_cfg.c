#include "iom324pb.h"

#include "blink_state_machine.h"
#include "gpio.h"
#include "led.h"
#include "scheduler_cfg.h"

/*
Exercise 672

LED0 blinking behavior:

LED0 ON  for 1 second
LED0 OFF for 1 second
sequence repeated continuously

The Task Scheduler generates one event every 1000 ms.
The State Machine processes the event and performs the
corresponding transition and LED action.

LED0 on ATmega324PB Xplained Pro:
- pin PC7
- active-low
*/

#define APP_LED0_DDR_REGISTER        (&DDRC)
#define APP_LED0_PORT_REGISTER       (&PORTC)
#define APP_LED0_PIN_NUMBER          (7U)

static blink_sm_t app_led0_state_machine;

void scheduler_cfg_init(void)
{
    gpio_init();

    led_init(
        APP_LED0_DDR_REGISTER,
        APP_LED0_PORT_REGISTER,
        APP_LED0_PIN_NUMBER
    );

    blink_sm_init(
        &app_led0_state_machine,
        APP_LED0_PORT_REGISTER,
        APP_LED0_PIN_NUMBER
    );
}

void scheduler_task_10ms(void)
{
    /*
    Not used by this application.
    */
}

void scheduler_task_50ms(void)
{
    /*
    Not used by this application.
    */
}

void scheduler_task_100ms(void)
{
    /*
    Not used by this application.
    */
}

void scheduler_task_500ms(void)
{
    /*
    Not used by this application.
    */
}

void scheduler_task_1000ms(void)
{
    /*
    The scheduler generates the TIMEOUT_1S event.

    This event is processed by the State Machine,
    which changes the LED state.
    */

    blink_sm_process(
        &app_led0_state_machine,
        BLINK_SM_EVENT_TIMEOUT_1S
    );
}