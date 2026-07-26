#ifndef SCHEDULER_CFG_C
#define SCHEDULER_CFG_C

#include "iom324pb.h"

#include "button.h"
#include "gpio.h"
#include "led.h"
#include "scheduler_cfg.h"

/*
BMW Central Control Panel

BUTTON1 / LED1 -> left vent
BUTTON2 / LED2 -> central vent
BUTTON3 / LED3 -> right vent

SW0 -> master block/unblock
LED0 -> blocked-state indicator
*/

/* ========================================================= */
/* CONSTANTS                                                 */
/* ========================================================= */

#define SCHEDULER_CFG_FALSE                  (0U)
#define SCHEDULER_CFG_TRUE                   (1U)

#define SCHEDULER_CFG_PANEL_UNBLOCKED        \
    (SCHEDULER_CFG_FALSE)

#define SCHEDULER_CFG_PANEL_BLOCKED          \
    (SCHEDULER_CFG_TRUE)

#define SCHEDULER_CFG_VENT_DISABLED          \
    (SCHEDULER_CFG_FALSE)

#define SCHEDULER_CFG_VENT_ENABLED           \
    (SCHEDULER_CFG_TRUE)

#define SCHEDULER_CFG_BLINK_INACTIVE         \
    (SCHEDULER_CFG_FALSE)

#define SCHEDULER_CFG_BLINK_ACTIVE           \
    (SCHEDULER_CFG_TRUE)

/*
6 toggles la interval de 100 ms:
OFF-ON-OFF-ON-OFF-ON.

La final LED0 ramane ON.
*/

#define SCHEDULER_CFG_BLOCK_BLINK_TOGGLES    (6U)
#define SCHEDULER_CFG_BLINK_COUNTER_ZERO     (0U)

/* ========================================================= */
/* MAIN BOARD LED0                                           */
/* ========================================================= */

#define SCHEDULER_CFG_LED0_DDR_REGISTER      (&DDRC)
#define SCHEDULER_CFG_LED0_PORT_REGISTER     (&PORTC)
#define SCHEDULER_CFG_LED0_PIN_NUMBER        (7U)

/* ========================================================= */
/* MAIN BOARD SW0                                            */
/* ========================================================= */

#define SCHEDULER_CFG_SW0_DDR_REGISTER       (&DDRC)
#define SCHEDULER_CFG_SW0_PORT_REGISTER      (&PORTC)
#define SCHEDULER_CFG_SW0_PIN_REGISTER       (&PINC)
#define SCHEDULER_CFG_SW0_PIN_NUMBER         (6U)

/* ========================================================= */
/* OLED1 LED CONNECTIONS                                     */
/* ========================================================= */

/* LED1 -> EXT1.7 -> PD5 */

#define SCHEDULER_CFG_LED1_DDR_REGISTER      (&DDRD)
#define SCHEDULER_CFG_LED1_PORT_REGISTER     (&PORTD)
#define SCHEDULER_CFG_LED1_PIN_NUMBER        (5U)

/* LED2 -> EXT1.8 -> PD4 */

#define SCHEDULER_CFG_LED2_DDR_REGISTER      (&DDRD)
#define SCHEDULER_CFG_LED2_PORT_REGISTER     (&PORTD)
#define SCHEDULER_CFG_LED2_PIN_NUMBER        (4U)

/* LED3 -> EXT1.6 -> PA3 */

#define SCHEDULER_CFG_LED3_DDR_REGISTER      (&DDRA)
#define SCHEDULER_CFG_LED3_PORT_REGISTER     (&PORTA)
#define SCHEDULER_CFG_LED3_PIN_NUMBER        (3U)

/* ========================================================= */
/* OLED1 BUTTON CONNECTIONS                                  */
/* ========================================================= */

/* BUTTON1 -> EXT1.9 -> PC1 */

#define SCHEDULER_CFG_BUTTON1_DDR_REGISTER   (&DDRC)
#define SCHEDULER_CFG_BUTTON1_PORT_REGISTER  (&PORTC)
#define SCHEDULER_CFG_BUTTON1_PIN_REGISTER   (&PINC)
#define SCHEDULER_CFG_BUTTON1_PIN_NUMBER     (1U)

/* BUTTON2 -> EXT1.3 -> PA0 */

#define SCHEDULER_CFG_BUTTON2_DDR_REGISTER   (&DDRA)
#define SCHEDULER_CFG_BUTTON2_PORT_REGISTER  (&PORTA)
#define SCHEDULER_CFG_BUTTON2_PIN_REGISTER   (&PINA)
#define SCHEDULER_CFG_BUTTON2_PIN_NUMBER     (0U)

/* BUTTON3 -> EXT1.4 -> PA1 */

#define SCHEDULER_CFG_BUTTON3_DDR_REGISTER   (&DDRA)
#define SCHEDULER_CFG_BUTTON3_PORT_REGISTER  (&PORTA)
#define SCHEDULER_CFG_BUTTON3_PIN_REGISTER   (&PINA)
#define SCHEDULER_CFG_BUTTON3_PIN_NUMBER     (1U)

/* ========================================================= */
/* PRIVATE BUTTON INSTANCES                                  */
/* ========================================================= */

static button_t scheduler_cfg_sw0_button;
static button_t scheduler_cfg_button1;
static button_t scheduler_cfg_button2;
static button_t scheduler_cfg_button3;

/* ========================================================= */
/* APPLICATION STATES                                        */
/* ========================================================= */

static unsigned char scheduler_cfg_panel_state;

static unsigned char scheduler_cfg_left_vent_state;
static unsigned char scheduler_cfg_central_vent_state;
static unsigned char scheduler_cfg_right_vent_state;

static unsigned char scheduler_cfg_block_blink_active;
static unsigned char scheduler_cfg_block_blink_counter;

/* ========================================================= */
/* PRIVATE FUNCTIONS                                         */
/* ========================================================= */

static void scheduler_cfg_process_buttons(void);

static void scheduler_cfg_toggle_panel_state(void);

static void scheduler_cfg_enter_blocked_state(void);

static void scheduler_cfg_enter_unblocked_state(void);

static void scheduler_cfg_process_vent_buttons(void);

static void scheduler_cfg_toggle_left_vent(void);

static void scheduler_cfg_toggle_central_vent(void);

static void scheduler_cfg_toggle_right_vent(void);

static void scheduler_cfg_turn_off_all_vent_leds(void);

static void scheduler_cfg_start_blocked_feedback(void);

static void scheduler_cfg_process_blocked_feedback(void);

/* ========================================================= */
/* INITIALIZATION                                            */
/* ========================================================= */

void scheduler_cfg_init(void)
{
    gpio_init();

    led_init(
        SCHEDULER_CFG_LED0_DDR_REGISTER,
        SCHEDULER_CFG_LED0_PORT_REGISTER,
        SCHEDULER_CFG_LED0_PIN_NUMBER
    );

    led_init(
        SCHEDULER_CFG_LED1_DDR_REGISTER,
        SCHEDULER_CFG_LED1_PORT_REGISTER,
        SCHEDULER_CFG_LED1_PIN_NUMBER
    );

    led_init(
        SCHEDULER_CFG_LED2_DDR_REGISTER,
        SCHEDULER_CFG_LED2_PORT_REGISTER,
        SCHEDULER_CFG_LED2_PIN_NUMBER
    );

    led_init(
        SCHEDULER_CFG_LED3_DDR_REGISTER,
        SCHEDULER_CFG_LED3_PORT_REGISTER,
        SCHEDULER_CFG_LED3_PIN_NUMBER
    );

    button_init(
        &scheduler_cfg_sw0_button,
        SCHEDULER_CFG_SW0_DDR_REGISTER,
        SCHEDULER_CFG_SW0_PORT_REGISTER,
        SCHEDULER_CFG_SW0_PIN_REGISTER,
        SCHEDULER_CFG_SW0_PIN_NUMBER
    );

    button_init(
        &scheduler_cfg_button1,
        SCHEDULER_CFG_BUTTON1_DDR_REGISTER,
        SCHEDULER_CFG_BUTTON1_PORT_REGISTER,
        SCHEDULER_CFG_BUTTON1_PIN_REGISTER,
        SCHEDULER_CFG_BUTTON1_PIN_NUMBER
    );

    button_init(
        &scheduler_cfg_button2,
        SCHEDULER_CFG_BUTTON2_DDR_REGISTER,
        SCHEDULER_CFG_BUTTON2_PORT_REGISTER,
        SCHEDULER_CFG_BUTTON2_PIN_REGISTER,
        SCHEDULER_CFG_BUTTON2_PIN_NUMBER
    );

    button_init(
        &scheduler_cfg_button3,
        SCHEDULER_CFG_BUTTON3_DDR_REGISTER,
        SCHEDULER_CFG_BUTTON3_PORT_REGISTER,
        SCHEDULER_CFG_BUTTON3_PIN_REGISTER,
        SCHEDULER_CFG_BUTTON3_PIN_NUMBER
    );

    scheduler_cfg_panel_state =
        SCHEDULER_CFG_PANEL_UNBLOCKED;

    scheduler_cfg_left_vent_state =
        SCHEDULER_CFG_VENT_DISABLED;

    scheduler_cfg_central_vent_state =
        SCHEDULER_CFG_VENT_DISABLED;

    scheduler_cfg_right_vent_state =
        SCHEDULER_CFG_VENT_DISABLED;

    scheduler_cfg_block_blink_active =
        SCHEDULER_CFG_BLINK_INACTIVE;

    scheduler_cfg_block_blink_counter =
        SCHEDULER_CFG_BLINK_COUNTER_ZERO;
}

/* ========================================================= */
/* 10 MS TASK                                                */
/* ========================================================= */

void scheduler_task_10ms(void)
{
    /*
    Fiecare buton primeste un esantion la 10 ms.

    5 esantioane egale:
    debounce time = 50 ms.
    */

    button_debounce_task(
        &scheduler_cfg_sw0_button
    );

    button_debounce_task(
        &scheduler_cfg_button1
    );

    button_debounce_task(
        &scheduler_cfg_button2
    );

    button_debounce_task(
        &scheduler_cfg_button3
    );

    scheduler_cfg_process_buttons();
}

/* ========================================================= */
/* 50 MS TASK                                                */
/* ========================================================= */

void scheduler_task_50ms(void)
{
    /*
    Disponibil pentru functionalitati ulterioare.
    */
}

/* ========================================================= */
/* 100 MS TASK                                               */
/* ========================================================= */

void scheduler_task_100ms(void)
{
    /*
    Fast blink pentru LED0 cand panoul este blocat.
    */

    scheduler_cfg_process_blocked_feedback();
}

/* ========================================================= */
/* 500 MS TASK                                               */
/* ========================================================= */

void scheduler_task_500ms(void)
{
    /*
    Disponibil pentru functionalitati ulterioare.
    */
}

/* ========================================================= */
/* 1000 MS TASK                                              */
/* ========================================================= */

void scheduler_task_1000ms(void)
{
    /*
    Disponibil pentru functionalitati ulterioare.
    */
}

/* ========================================================= */
/* BUTTON PROCESSING                                         */
/* ========================================================= */

static void scheduler_cfg_process_buttons(void)
{
    /*
    SW0 are prioritate functionala in acest ciclu.
    Daca este detectat, starea panoului este schimbata
    si butoanele OLED sunt procesate abia la urmatorul tick.
    */

    if (
        button_was_pressed(
            &scheduler_cfg_sw0_button
        ) ==
        BUTTON_EVENT_DETECTED
    )
    {
        scheduler_cfg_toggle_panel_state();

        return;
    }

    scheduler_cfg_process_vent_buttons();
}

static void scheduler_cfg_process_vent_buttons(void)
{
    unsigned char scheduler_cfg_button1_event;
    unsigned char scheduler_cfg_button2_event;
    unsigned char scheduler_cfg_button3_event;

    scheduler_cfg_button1_event =
        button_was_pressed(
            &scheduler_cfg_button1
        );

    scheduler_cfg_button2_event =
        button_was_pressed(
            &scheduler_cfg_button2
        );

    scheduler_cfg_button3_event =
        button_was_pressed(
            &scheduler_cfg_button3
        );

    if (
        scheduler_cfg_panel_state ==
        SCHEDULER_CFG_PANEL_BLOCKED
    )
    {
        /*
        In starea BLOCKED, niciun buton OLED nu modifica
        ventilatia sau LED-urile OLED.

        Orice apasare produce doar feedback rapid pe LED0.
        */

        if (
            (scheduler_cfg_button1_event ==
             BUTTON_EVENT_DETECTED) ||
            (scheduler_cfg_button2_event ==
             BUTTON_EVENT_DETECTED) ||
            (scheduler_cfg_button3_event ==
             BUTTON_EVENT_DETECTED)
        )
        {
            scheduler_cfg_start_blocked_feedback();
        }

        return;
    }

    /*
    Panou deblocat:
    fiecare buton modifica numai propriul canal.
    */

    if (
        scheduler_cfg_button1_event ==
        BUTTON_EVENT_DETECTED
    )
    {
        scheduler_cfg_toggle_left_vent();
    }

    if (
        scheduler_cfg_button2_event ==
        BUTTON_EVENT_DETECTED
    )
    {
        scheduler_cfg_toggle_central_vent();
    }

    if (
        scheduler_cfg_button3_event ==
        BUTTON_EVENT_DETECTED
    )
    {
        scheduler_cfg_toggle_right_vent();
    }
}

/* ========================================================= */
/* MASTER CONTROL                                            */
/* ========================================================= */

static void scheduler_cfg_toggle_panel_state(void)
{
    if (
        scheduler_cfg_panel_state ==
        SCHEDULER_CFG_PANEL_UNBLOCKED
    )
    {
        scheduler_cfg_enter_blocked_state();
    }
    else
    {
        scheduler_cfg_enter_unblocked_state();
    }
}

static void scheduler_cfg_enter_blocked_state(void)
{
    scheduler_cfg_panel_state =
        SCHEDULER_CFG_PANEL_BLOCKED;

    /*
    Toate functiile de ventilatie sunt dezactivate.
    */

    scheduler_cfg_left_vent_state =
        SCHEDULER_CFG_VENT_DISABLED;

    scheduler_cfg_central_vent_state =
        SCHEDULER_CFG_VENT_DISABLED;

    scheduler_cfg_right_vent_state =
        SCHEDULER_CFG_VENT_DISABLED;

    scheduler_cfg_turn_off_all_vent_leds();

    /*
    Opreste un eventual blink anterior si mentine LED0 ON.
    */

    scheduler_cfg_block_blink_active =
        SCHEDULER_CFG_BLINK_INACTIVE;

    scheduler_cfg_block_blink_counter =
        SCHEDULER_CFG_BLINK_COUNTER_ZERO;

    led_power_on(
        SCHEDULER_CFG_LED0_PORT_REGISTER,
        SCHEDULER_CFG_LED0_PIN_NUMBER
    );
}

static void scheduler_cfg_enter_unblocked_state(void)
{
    scheduler_cfg_panel_state =
        SCHEDULER_CFG_PANEL_UNBLOCKED;

    scheduler_cfg_block_blink_active =
        SCHEDULER_CFG_BLINK_INACTIVE;

    scheduler_cfg_block_blink_counter =
        SCHEDULER_CFG_BLINK_COUNTER_ZERO;

    led_power_off(
        SCHEDULER_CFG_LED0_PORT_REGISTER,
        SCHEDULER_CFG_LED0_PIN_NUMBER
    );

    /*
    La deblocare, ventilatiile raman initial dezactivate.
    */

    scheduler_cfg_left_vent_state =
        SCHEDULER_CFG_VENT_DISABLED;

    scheduler_cfg_central_vent_state =
        SCHEDULER_CFG_VENT_DISABLED;

    scheduler_cfg_right_vent_state =
        SCHEDULER_CFG_VENT_DISABLED;

    scheduler_cfg_turn_off_all_vent_leds();
}

/* ========================================================= */
/* VENT CONTROL                                              */
/* ========================================================= */

static void scheduler_cfg_toggle_left_vent(void)
{
    if (
        scheduler_cfg_left_vent_state ==
        SCHEDULER_CFG_VENT_DISABLED
    )
    {
        scheduler_cfg_left_vent_state =
            SCHEDULER_CFG_VENT_ENABLED;

        led_power_on(
            SCHEDULER_CFG_LED1_PORT_REGISTER,
            SCHEDULER_CFG_LED1_PIN_NUMBER
        );
    }
    else
    {
        scheduler_cfg_left_vent_state =
            SCHEDULER_CFG_VENT_DISABLED;

        led_power_off(
            SCHEDULER_CFG_LED1_PORT_REGISTER,
            SCHEDULER_CFG_LED1_PIN_NUMBER
        );
    }
}

static void scheduler_cfg_toggle_central_vent(void)
{
    if (
        scheduler_cfg_central_vent_state ==
        SCHEDULER_CFG_VENT_DISABLED
    )
    {
        scheduler_cfg_central_vent_state =
            SCHEDULER_CFG_VENT_ENABLED;

        led_power_on(
            SCHEDULER_CFG_LED2_PORT_REGISTER,
            SCHEDULER_CFG_LED2_PIN_NUMBER
        );
    }
    else
    {
        scheduler_cfg_central_vent_state =
            SCHEDULER_CFG_VENT_DISABLED;

        led_power_off(
            SCHEDULER_CFG_LED2_PORT_REGISTER,
            SCHEDULER_CFG_LED2_PIN_NUMBER
        );
    }
}

static void scheduler_cfg_toggle_right_vent(void)
{
    if (
        scheduler_cfg_right_vent_state ==
        SCHEDULER_CFG_VENT_DISABLED
    )
    {
        scheduler_cfg_right_vent_state =
            SCHEDULER_CFG_VENT_ENABLED;

        led_power_on(
            SCHEDULER_CFG_LED3_PORT_REGISTER,
            SCHEDULER_CFG_LED3_PIN_NUMBER
        );
    }
    else
    {
        scheduler_cfg_right_vent_state =
            SCHEDULER_CFG_VENT_DISABLED;

        led_power_off(
            SCHEDULER_CFG_LED3_PORT_REGISTER,
            SCHEDULER_CFG_LED3_PIN_NUMBER
        );
    }
}

static void scheduler_cfg_turn_off_all_vent_leds(void)
{
    led_power_off(
        SCHEDULER_CFG_LED1_PORT_REGISTER,
        SCHEDULER_CFG_LED1_PIN_NUMBER
    );

    led_power_off(
        SCHEDULER_CFG_LED2_PORT_REGISTER,
        SCHEDULER_CFG_LED2_PIN_NUMBER
    );

    led_power_off(
        SCHEDULER_CFG_LED3_PORT_REGISTER,
        SCHEDULER_CFG_LED3_PIN_NUMBER
    );
}

/* ========================================================= */
/* BLOCKED FEEDBACK                                          */
/* ========================================================= */

static void scheduler_cfg_start_blocked_feedback(void)
{
    /*
    Daca apare o noua apasare in timpul blink-ului,
    secventa este restartata.
    */

    scheduler_cfg_block_blink_active =
        SCHEDULER_CFG_BLINK_ACTIVE;

    scheduler_cfg_block_blink_counter =
        SCHEDULER_CFG_BLOCK_BLINK_TOGGLES;
}

static void scheduler_cfg_process_blocked_feedback(void)
{
    if (
        scheduler_cfg_panel_state !=
        SCHEDULER_CFG_PANEL_BLOCKED
    )
    {
        return;
    }

    if (
        scheduler_cfg_block_blink_active ==
        SCHEDULER_CFG_BLINK_ACTIVE
    )
    {
        led_toggle(
            SCHEDULER_CFG_LED0_PORT_REGISTER,
            SCHEDULER_CFG_LED0_PIN_NUMBER
        );

        if (
            scheduler_cfg_block_blink_counter >
            SCHEDULER_CFG_BLINK_COUNTER_ZERO
        )
        {
            scheduler_cfg_block_blink_counter--;
        }

        if (
            scheduler_cfg_block_blink_counter ==
            SCHEDULER_CFG_BLINK_COUNTER_ZERO
        )
        {
            scheduler_cfg_block_blink_active =
                SCHEDULER_CFG_BLINK_INACTIVE;

            /*
            LED0 trebuie sa ramana ON in BLOCKED state.
            */

            led_power_on(
                SCHEDULER_CFG_LED0_PORT_REGISTER,
                SCHEDULER_CFG_LED0_PIN_NUMBER
            );
        }
    }
}

#endif