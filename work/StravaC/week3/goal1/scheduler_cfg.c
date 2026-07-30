#include "iom324pb.h"

#include "button.h"
#include "gpio.h"
#include "led.h"
#include "scheduler_cfg.h"
#include "state_machine.h"

/*
OLED1 mounted on EXT1.

Buttons:
BUTTON1 -> PC1
BUTTON2 -> PA0
BUTTON3 -> PA1

LEDs:
LED1 -> PD5
LED2 -> PD4
LED3 -> PA3

Each button has its own independent state machine.

BUTTON1 affects only LED1.
BUTTON2 affects only LED2.
BUTTON3 affects only LED3.

No crosstalk is allowed.
*/

/* BUTTON1 */

#define APP_BUTTON1_DDR_REGISTER       (&DDRC)
#define APP_BUTTON1_PORT_REGISTER      (&PORTC)
#define APP_BUTTON1_PIN_REGISTER       (&PINC)
#define APP_BUTTON1_PIN_NUMBER         (1U)

/* BUTTON2 */

#define APP_BUTTON2_DDR_REGISTER       (&DDRA)
#define APP_BUTTON2_PORT_REGISTER      (&PORTA)
#define APP_BUTTON2_PIN_REGISTER       (&PINA)
#define APP_BUTTON2_PIN_NUMBER         (0U)

/* BUTTON3 */

#define APP_BUTTON3_DDR_REGISTER       (&DDRA)
#define APP_BUTTON3_PORT_REGISTER      (&PORTA)
#define APP_BUTTON3_PIN_REGISTER       (&PINA)
#define APP_BUTTON3_PIN_NUMBER         (1U)

/* LED1 */

#define APP_LED1_DDR_REGISTER          (&DDRD)
#define APP_LED1_PORT_REGISTER         (&PORTD)
#define APP_LED1_PIN_NUMBER            (5U)

/* LED2 */

#define APP_LED2_DDR_REGISTER          (&DDRD)
#define APP_LED2_PORT_REGISTER         (&PORTD)
#define APP_LED2_PIN_NUMBER            (4U)

/* LED3 */

#define APP_LED3_DDR_REGISTER          (&DDRA)
#define APP_LED3_PORT_REGISTER         (&PORTA)
#define APP_LED3_PIN_NUMBER            (3U)

static button_t app_button1;
static button_t app_button2;
static button_t app_button3;

static state_machine_led_t
    app_led1_state_machine;

static state_machine_led_t
    app_led2_state_machine;

static state_machine_led_t
    app_led3_state_machine;

static state_machine_event_t
    app_get_button_event(
        button_t *button_instance
    );

void scheduler_cfg_init(void)
{
    gpio_init();

    led_init(
        APP_LED1_DDR_REGISTER,
        APP_LED1_PORT_REGISTER,
        APP_LED1_PIN_NUMBER
    );

    led_init(
        APP_LED2_DDR_REGISTER,
        APP_LED2_PORT_REGISTER,
        APP_LED2_PIN_NUMBER
    );

    led_init(
        APP_LED3_DDR_REGISTER,
        APP_LED3_PORT_REGISTER,
        APP_LED3_PIN_NUMBER
    );

    button_init(
        &app_button1,
        APP_BUTTON1_DDR_REGISTER,
        APP_BUTTON1_PORT_REGISTER,
        APP_BUTTON1_PIN_REGISTER,
        APP_BUTTON1_PIN_NUMBER
    );

    button_init(
        &app_button2,
        APP_BUTTON2_DDR_REGISTER,
        APP_BUTTON2_PORT_REGISTER,
        APP_BUTTON2_PIN_REGISTER,
        APP_BUTTON2_PIN_NUMBER
    );

    button_init(
        &app_button3,
        APP_BUTTON3_DDR_REGISTER,
        APP_BUTTON3_PORT_REGISTER,
        APP_BUTTON3_PIN_REGISTER,
        APP_BUTTON3_PIN_NUMBER
    );

    state_machine_init(
        &app_led1_state_machine,
        APP_LED1_PORT_REGISTER,
        APP_LED1_PIN_NUMBER
    );

    state_machine_init(
        &app_led2_state_machine,
        APP_LED2_PORT_REGISTER,
        APP_LED2_PIN_NUMBER
    );

    state_machine_init(
        &app_led3_state_machine,
        APP_LED3_PORT_REGISTER,
        APP_LED3_PIN_NUMBER
    );
}

void scheduler_task_10ms(void)
{
    state_machine_event_t button1_event;
    state_machine_event_t button2_event;
    state_machine_event_t button3_event;

    /*
    Acquire one sample for every button.

    Five equal samples at 10 ms:
    debounce time = 50 ms.
    */

    button_debounce_task(
        &app_button1
    );

    button_debounce_task(
        &app_button2
    );

    button_debounce_task(
        &app_button3
    );

    /*
    Convert debounced button events into
    state-machine events.
    */

    button1_event =
        app_get_button_event(
            &app_button1
        );

    button2_event =
        app_get_button_event(
            &app_button2
        );

    button3_event =
        app_get_button_event(
            &app_button3
        );

    /*
    Run the three independent state machines.
    */

    state_machine_process(
        &app_led1_state_machine,
        button1_event
    );

    state_machine_process(
        &app_led2_state_machine,
        button2_event
    );

    state_machine_process(
        &app_led3_state_machine,
        button3_event
    );
}

void scheduler_task_50ms(void)
{
}

void scheduler_task_100ms(void)
{
}

void scheduler_task_500ms(void)
{
}

void scheduler_task_1000ms(void)
{
}

static state_machine_event_t
    app_get_button_event(
        button_t *button_instance
    )
{
    if (
        button_was_pressed(
            button_instance
        ) ==
        BUTTON_EVENT_DETECTED
    )
    {
        return STATE_MACHINE_EVENT_BUTTON_PRESSED;
    }

    return STATE_MACHINE_EVENT_NONE;
}