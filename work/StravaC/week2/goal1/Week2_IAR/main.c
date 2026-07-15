#include "iom324pb.h"

#include "gpio.h"
#include "led.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

BMW Central HVAC Control Panel Prototype

OLED1 Xplained Pro este conectat la EXT1.

BUTTON1 controleaza ventul din stanga si LED1.
BUTTON2 controleaza ventul central si LED2.
BUTTON3 controleaza ventul din dreapta si LED3.

Fiecare apasare comuta starea ventului corespunzator:
OFF -> ON
ON  -> OFF

SW0 este butonul master control.

La apasarea SW0:
- panoul intra in starea BLOCKED;
- toate venturile sunt dezactivate;
- toate LED-urile OLED1 sunt stinse;
- LED0 de pe placa principala este aprins.

In starea BLOCKED:
- butoanele OLED1 nu modifica venturile;
- o apasare pe orice buton OLED1 face LED0 sa clipeasca rapid;
- dupa clipire, LED0 ramane aprins.

O noua apasare SW0 deblocheaza panoul.
*/

/* ========================================================= */
/* OLED1 BUTTON CONNECTIONS - EXT1                           */
/* ========================================================= */

/* BUTTON1: EXT1 pin 9 -> PC1 */

#define APP_BUTTON1_PIN_REGISTER        (&PINC)
#define APP_BUTTON1_PORT_REGISTER       (&PORTC)
#define APP_BUTTON1_DDR_REGISTER        (&DDRC)
#define APP_BUTTON1_PIN_NUMBER          (1U)

/* BUTTON2: EXT1 pin 3 -> PA0 */

#define APP_BUTTON2_PIN_REGISTER        (&PINA)
#define APP_BUTTON2_PORT_REGISTER       (&PORTA)
#define APP_BUTTON2_DDR_REGISTER        (&DDRA)
#define APP_BUTTON2_PIN_NUMBER          (0U)

/* BUTTON3: EXT1 pin 4 -> PA1 */

#define APP_BUTTON3_PIN_REGISTER        (&PINA)
#define APP_BUTTON3_PORT_REGISTER       (&PORTA)
#define APP_BUTTON3_DDR_REGISTER        (&DDRA)
#define APP_BUTTON3_PIN_NUMBER          (1U)

/* ========================================================= */
/* OLED1 LED CONNECTIONS - EXT1                              */
/* ========================================================= */

/* LED1: EXT1 pin 7 -> PD5 */

#define APP_LED1_PORT_REGISTER          (&PORTD)
#define APP_LED1_DDR_REGISTER           (&DDRD)
#define APP_LED1_PIN_NUMBER             (5U)

/* LED2: EXT1 pin 8 -> PD4 */

#define APP_LED2_PORT_REGISTER          (&PORTD)
#define APP_LED2_DDR_REGISTER           (&DDRD)
#define APP_LED2_PIN_NUMBER             (4U)

/* LED3: EXT1 pin 6 -> PA3 */

#define APP_LED3_PORT_REGISTER          (&PORTA)
#define APP_LED3_DDR_REGISTER           (&DDRA)
#define APP_LED3_PIN_NUMBER             (3U)

/* ========================================================= */
/* MASTER CONTROL CONNECTIONS                                */
/* ========================================================= */

/* SW0: PC6 */

#define APP_SW0_PIN_REGISTER            (&PINC)
#define APP_SW0_PORT_REGISTER           (&PORTC)
#define APP_SW0_DDR_REGISTER            (&DDRC)
#define APP_SW0_PIN_NUMBER              (6U)

/* LED0: PC7 */

#define APP_LED0_PORT_REGISTER          (&PORTC)
#define APP_LED0_DDR_REGISTER           (&DDRC)
#define APP_LED0_PIN_NUMBER             (7U)

/* ========================================================= */
/* LOGIC LEVELS                                              */
/* ========================================================= */

#define APP_BUTTON_PRESSED_LEVEL        (GPIO_LOW)
#define APP_BUTTON_RELEASED_LEVEL       (GPIO_HIGH)

/* ========================================================= */
/* PANEL STATES                                              */
/* ========================================================= */

#define APP_PANEL_UNBLOCKED             (GPIO_FALSE)
#define APP_PANEL_BLOCKED               (GPIO_TRUE)

#define APP_VENT_DISABLED               (GPIO_FALSE)
#define APP_VENT_ENABLED                (GPIO_TRUE)

/* ========================================================= */
/* BLINK CONFIGURATION                                       */
/* ========================================================= */

#define APP_BLOCKED_BLINK_COUNT         (3U)
#define APP_BLINK_COUNTER_INITIAL_VALUE (0U)

/* ========================================================= */
/* APPLICATION VARIABLES                                     */
/* ========================================================= */

/*
Starea logica a celor trei venturi.
Fiecare variabila apartine modulului application si foloseste
prefixul app_.
*/

static gpio_uint8_t app_left_vent_state;
static gpio_uint8_t app_center_vent_state;
static gpio_uint8_t app_right_vent_state;

static gpio_uint8_t app_panel_blocked;

/*
Starile anterioare ale butoanelor sunt necesare pentru detectarea
unei apasari noi.

Un toggle trebuie executat o singura data la trecerea:
RELEASED -> PRESSED.
*/

static gpio_uint8_t app_button1_previous_state;
static gpio_uint8_t app_button2_previous_state;
static gpio_uint8_t app_button3_previous_state;
static gpio_uint8_t app_sw0_previous_state;

/* ========================================================= */
/* STATIC PRIVATE FUNCTIONS DECLARATION                      */
/* ========================================================= */

static void app_initialize_hardware(void);

static void app_initialize_states(void);

static void app_process_master_button(void);

static void app_process_oled_buttons(void);

static gpio_uint8_t app_button_has_new_press(
    gpio_uint8_t app_current_state,
    gpio_uint8_t app_previous_state
);

static void app_toggle_left_vent(void);

static void app_toggle_center_vent(void);

static void app_toggle_right_vent(void);

static void app_update_left_vent_led(void);

static void app_update_center_vent_led(void);

static void app_update_right_vent_led(void);

static void app_enter_blocked_state(void);

static void app_exit_blocked_state(void);

static void app_disable_all_vents(void);

static void app_turn_off_all_oled_leds(void);

static void app_signal_blocked_button_press(void);

/* ========================================================= */
/* MAIN                                                      */
/* ========================================================= */

void main(void)
{
    app_initialize_hardware();
    app_initialize_states();

    while (GPIO_TRUE)
    {
        /*
        SW0 este verificat primul deoarece este master control
        si are prioritate asupra celor trei butoane OLED1.
        */
        app_process_master_button();

        /*
        Apoi sunt procesate independent cele trei butoane OLED1.
        */
        app_process_oled_buttons();
    }
}

/* ========================================================= */
/* INITIALIZATION                                            */
/* ========================================================= */

static void app_initialize_hardware(void)
{
    /* ---------------- BUTTON1 ---------------- */

    gpio_set_direction(
        APP_BUTTON1_DDR_REGISTER,
        APP_BUTTON1_PIN_NUMBER,
        GPIO_INPUT
    );

    gpio_activate_pullup(
        APP_BUTTON1_PORT_REGISTER,
        APP_BUTTON1_PIN_NUMBER
    );

    /* ---------------- BUTTON2 ---------------- */

    gpio_set_direction(
        APP_BUTTON2_DDR_REGISTER,
        APP_BUTTON2_PIN_NUMBER,
        GPIO_INPUT
    );

    gpio_activate_pullup(
        APP_BUTTON2_PORT_REGISTER,
        APP_BUTTON2_PIN_NUMBER
    );

    /* ---------------- BUTTON3 ---------------- */

    gpio_set_direction(
        APP_BUTTON3_DDR_REGISTER,
        APP_BUTTON3_PIN_NUMBER,
        GPIO_INPUT
    );

    gpio_activate_pullup(
        APP_BUTTON3_PORT_REGISTER,
        APP_BUTTON3_PIN_NUMBER
    );

    /* ---------------- SW0 ---------------- */

    gpio_set_direction(
        APP_SW0_DDR_REGISTER,
        APP_SW0_PIN_NUMBER,
        GPIO_INPUT
    );

    gpio_activate_pullup(
        APP_SW0_PORT_REGISTER,
        APP_SW0_PIN_NUMBER
    );

    /* ---------------- LED1 ---------------- */

    gpio_set_direction(
        APP_LED1_DDR_REGISTER,
        APP_LED1_PIN_NUMBER,
        GPIO_OUTPUT
    );

    /* ---------------- LED2 ---------------- */

    gpio_set_direction(
        APP_LED2_DDR_REGISTER,
        APP_LED2_PIN_NUMBER,
        GPIO_OUTPUT
    );

    /* ---------------- LED3 ---------------- */

    gpio_set_direction(
        APP_LED3_DDR_REGISTER,
        APP_LED3_PIN_NUMBER,
        GPIO_OUTPUT
    );

    /* ---------------- LED0 ---------------- */

    gpio_set_direction(
        APP_LED0_DDR_REGISTER,
        APP_LED0_PIN_NUMBER,
        GPIO_OUTPUT
    );

    /*
    Toate LED-urile sunt active-low.
    Initial sunt stinse.
    */

    app_turn_off_all_oled_leds();

    led_power_off(
        APP_LED0_PORT_REGISTER,
        APP_LED0_PIN_NUMBER
    );
}

static void app_initialize_states(void)
{
    app_left_vent_state = APP_VENT_DISABLED;
    app_center_vent_state = APP_VENT_DISABLED;
    app_right_vent_state = APP_VENT_DISABLED;

    app_panel_blocked = APP_PANEL_UNBLOCKED;

    /*
    Se citesc starile initiale ale butoanelor pentru a evita
    detectarea falsa a unei apasari la pornirea programului.
    */

    app_button1_previous_state = gpio_read_pin(
        APP_BUTTON1_PIN_REGISTER,
        APP_BUTTON1_PIN_NUMBER
    );

    app_button2_previous_state = gpio_read_pin(
        APP_BUTTON2_PIN_REGISTER,
        APP_BUTTON2_PIN_NUMBER
    );

    app_button3_previous_state = gpio_read_pin(
        APP_BUTTON3_PIN_REGISTER,
        APP_BUTTON3_PIN_NUMBER
    );

    app_sw0_previous_state = gpio_read_pin(
        APP_SW0_PIN_REGISTER,
        APP_SW0_PIN_NUMBER
    );
}

/* ========================================================= */
/* MASTER CONTROL                                            */
/* ========================================================= */

static void app_process_master_button(void)
{
    gpio_uint8_t app_sw0_current_state;

    app_sw0_current_state = gpio_read_pin_debounced(
        APP_SW0_PIN_REGISTER,
        APP_SW0_PIN_NUMBER
    );

    if (
        app_button_has_new_press(
            app_sw0_current_state,
            app_sw0_previous_state
        ) == GPIO_TRUE
    )
    {
        if (app_panel_blocked == APP_PANEL_UNBLOCKED)
        {
            app_enter_blocked_state();
        }
        else
        {
            app_exit_blocked_state();
        }
    }

    app_sw0_previous_state = app_sw0_current_state;
}

static void app_enter_blocked_state(void)
{
    app_panel_blocked = APP_PANEL_BLOCKED;

    /*
    BMW solicita dezactivarea intregului panou.
    Toate venturile si LED-urile OLED1 sunt oprite.
    */

    app_disable_all_vents();
    app_turn_off_all_oled_leds();

    /*
    LED0 aprins indica starea BLOCKED.
    */

    led_power_on(
        APP_LED0_PORT_REGISTER,
        APP_LED0_PIN_NUMBER
    );
}

static void app_exit_blocked_state(void)
{
    app_panel_blocked = APP_PANEL_UNBLOCKED;

    /*
    La deblocare, LED0 este stins.
    Venturile raman initial dezactivate.
    */

    led_power_off(
        APP_LED0_PORT_REGISTER,
        APP_LED0_PIN_NUMBER
    );
}

/* ========================================================= */
/* OLED1 BUTTON PROCESSING                                    */
/* ========================================================= */

static void app_process_oled_buttons(void)
{
    gpio_uint8_t app_button1_current_state;
    gpio_uint8_t app_button2_current_state;
    gpio_uint8_t app_button3_current_state;

    gpio_uint8_t app_button1_new_press;
    gpio_uint8_t app_button2_new_press;
    gpio_uint8_t app_button3_new_press;

    app_button1_current_state = gpio_read_pin_debounced(
        APP_BUTTON1_PIN_REGISTER,
        APP_BUTTON1_PIN_NUMBER
    );

    app_button2_current_state = gpio_read_pin_debounced(
        APP_BUTTON2_PIN_REGISTER,
        APP_BUTTON2_PIN_NUMBER
    );

    app_button3_current_state = gpio_read_pin_debounced(
        APP_BUTTON3_PIN_REGISTER,
        APP_BUTTON3_PIN_NUMBER
    );

    app_button1_new_press = app_button_has_new_press(
        app_button1_current_state,
        app_button1_previous_state
    );

    app_button2_new_press = app_button_has_new_press(
        app_button2_current_state,
        app_button2_previous_state
    );

    app_button3_new_press = app_button_has_new_press(
        app_button3_current_state,
        app_button3_previous_state
    );

    if (app_panel_blocked == APP_PANEL_BLOCKED)
    {
        /*
        In stare BLOCKED, niciun buton OLED1 nu poate modifica
        vreun vent sau vreun LED OLED1.
        */

        if (
            (app_button1_new_press == GPIO_TRUE) ||
            (app_button2_new_press == GPIO_TRUE) ||
            (app_button3_new_press == GPIO_TRUE)
        )
        {
            app_signal_blocked_button_press();
        }
    }
    else
    {
        /*
        Fiecare buton controleaza exclusiv ventul sau.
        Aceasta separare elimina crosstalk-ul.
        */

        if (app_button1_new_press == GPIO_TRUE)
        {
            app_toggle_left_vent();
        }

        if (app_button2_new_press == GPIO_TRUE)
        {
            app_toggle_center_vent();
        }

        if (app_button3_new_press == GPIO_TRUE)
        {
            app_toggle_right_vent();
        }
    }

    /*
    Actualizeaza starile anterioare dupa procesare.
    */

    app_button1_previous_state = app_button1_current_state;
    app_button2_previous_state = app_button2_current_state;
    app_button3_previous_state = app_button3_current_state;
}

static gpio_uint8_t app_button_has_new_press(
    gpio_uint8_t app_current_state,
    gpio_uint8_t app_previous_state
)
{
    if (
        (app_previous_state == APP_BUTTON_RELEASED_LEVEL) &&
        (app_current_state == APP_BUTTON_PRESSED_LEVEL)
    )
    {
        return GPIO_TRUE;
    }

    return GPIO_FALSE;
}

/* ========================================================= */
/* VENT TOGGLE FUNCTIONS                                     */
/* ========================================================= */

static void app_toggle_left_vent(void)
{
    if (app_left_vent_state == APP_VENT_DISABLED)
    {
        app_left_vent_state = APP_VENT_ENABLED;
    }
    else
    {
        app_left_vent_state = APP_VENT_DISABLED;
    }

    app_update_left_vent_led();
}

static void app_toggle_center_vent(void)
{
    if (app_center_vent_state == APP_VENT_DISABLED)
    {
        app_center_vent_state = APP_VENT_ENABLED;
    }
    else
    {
        app_center_vent_state = APP_VENT_DISABLED;
    }

    app_update_center_vent_led();
}

static void app_toggle_right_vent(void)
{
    if (app_right_vent_state == APP_VENT_DISABLED)
    {
        app_right_vent_state = APP_VENT_ENABLED;
    }
    else
    {
        app_right_vent_state = APP_VENT_DISABLED;
    }

    app_update_right_vent_led();
}

/* ========================================================= */
/* LED UPDATE FUNCTIONS                                      */
/* ========================================================= */

static void app_update_left_vent_led(void)
{
    if (app_left_vent_state == APP_VENT_ENABLED)
    {
        led_power_on(
            APP_LED1_PORT_REGISTER,
            APP_LED1_PIN_NUMBER
        );
    }
    else
    {
        led_power_off(
            APP_LED1_PORT_REGISTER,
            APP_LED1_PIN_NUMBER
        );
    }
}

static void app_update_center_vent_led(void)
{
    if (app_center_vent_state == APP_VENT_ENABLED)
    {
        led_power_on(
            APP_LED2_PORT_REGISTER,
            APP_LED2_PIN_NUMBER
        );
    }
    else
    {
        led_power_off(
            APP_LED2_PORT_REGISTER,
            APP_LED2_PIN_NUMBER
        );
    }
}

static void app_update_right_vent_led(void)
{
    if (app_right_vent_state == APP_VENT_ENABLED)
    {
        led_power_on(
            APP_LED3_PORT_REGISTER,
            APP_LED3_PIN_NUMBER
        );
    }
    else
    {
        led_power_off(
            APP_LED3_PORT_REGISTER,
            APP_LED3_PIN_NUMBER
        );
    }
}

/* ========================================================= */
/* BLOCKED STATE HELPERS                                     */
/* ========================================================= */

static void app_disable_all_vents(void)
{
    app_left_vent_state = APP_VENT_DISABLED;
    app_center_vent_state = APP_VENT_DISABLED;
    app_right_vent_state = APP_VENT_DISABLED;
}

static void app_turn_off_all_oled_leds(void)
{
    led_power_off(
        APP_LED1_PORT_REGISTER,
        APP_LED1_PIN_NUMBER
    );

    led_power_off(
        APP_LED2_PORT_REGISTER,
        APP_LED2_PIN_NUMBER
    );

    led_power_off(
        APP_LED3_PORT_REGISTER,
        APP_LED3_PIN_NUMBER
    );
}

static void app_signal_blocked_button_press(void)
{
    gpio_uint8_t app_blink_counter;

    /*
    LED0 este aprins permanent in starea BLOCKED.
    Pentru semnalizarea unei apasari interzise, acesta clipeste
    rapid, apoi revine in starea ON.
    */

    for (
        app_blink_counter = APP_BLINK_COUNTER_INITIAL_VALUE;
        app_blink_counter < APP_BLOCKED_BLINK_COUNT;
        app_blink_counter++
    )
    {
        led_power_off(
            APP_LED0_PORT_REGISTER,
            APP_LED0_PIN_NUMBER
        );

        led_delay_fast();

        led_power_on(
            APP_LED0_PORT_REGISTER,
            APP_LED0_PIN_NUMBER
        );

        led_delay_fast();
    }

    /*
    Dupa semnalizare, LED0 trebuie sa ramana aprins,
    indicand faptul ca panoul este in continuare blocat.
    */

    led_power_on(
        APP_LED0_PORT_REGISTER,
        APP_LED0_PIN_NUMBER
    );
}