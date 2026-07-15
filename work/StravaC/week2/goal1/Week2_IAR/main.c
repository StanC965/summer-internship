#include "iom324pb.h"
#include "intrinsics.h"

#include "gpio.h"
#include "led.h"
#include "sos.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier contine punctul principal al aplicatiei.

SW0 este conectat la PC6, care are functia alternativa PCINT22.
LED0 este conectat la PC7 si este active-low.

Pentru detectarea apasarii butonului este folosita o intrerupere
Pin Change Interrupt.

Rutina de intrerupere nu executa direct secventa SOS.
Ea doar seteaza un flag, iar programul principal decide
ce comportament trebuie executat.

Conventie de numire:
Toate functiile si variabilele acestui modul folosesc prefixul app_.
*/

/* Board connections */

#define APP_SW0_PIN_NUMBER                    (6U)
#define APP_LED0_PIN_NUMBER                   (7U)

/* Button logic */

#define APP_SW0_PRESSED_LEVEL                 (GPIO_LOW)

/* Pin Change Interrupt configuration */

#define APP_SW0_PCINT_ENABLE_VALUE            (GPIO_ONE)
#define APP_SW0_INTERRUPT_GROUP_ENABLE_VALUE  (GPIO_ONE)
#define APP_SW0_INTERRUPT_FLAG_CLEAR_VALUE    (GPIO_ONE)

/* Application states */

#define APP_SOS_STATE_DISABLED                (GPIO_FALSE)
#define APP_SOS_STATE_ENABLED                 (GPIO_TRUE)

/* Delay configuration */

#define APP_SOS_MESSAGE_PAUSE_DELAY_COUNT     (250000UL)
#define APP_DELAY_COUNTER_INITIAL_VALUE       (0UL)

/*
Flagul este declarat volatile deoarece este modificat
de rutina de intrerupere si citit de programul principal.
*/
static volatile gpio_uint8_t app_sw0_interrupt_request;

/* Static private functions declaration */

static void app_initialize_hardware(void);

static void app_initialize_sw0_interrupt(void);

static gpio_uint8_t app_get_and_clear_sw0_request(void);

static void app_clear_sw0_request(void);

static void app_delay_between_sos_messages(void);

/* Interrupt Service Routine */

/*
Rutina asociata grupei PCINT[23:16].

PC6 corespunde pinului PCINT22, iar PCINT22 face parte
din grupa Pin Change Interrupt Request 2.

Pin Change Interrupt se declanseaza la orice schimbare a pinului:
HIGH -> LOW la apasare;
LOW  -> HIGH la eliberare.

Pentru a reactiona doar la apasare, starea pinului este verificata
in interiorul rutinei.
*/
#pragma vector=PCINT2_vect
__interrupt void app_sw0_interrupt_service_routine(void)
{
    if (
        gpio_read_pin(
            &PINC,
            APP_SW0_PIN_NUMBER
        ) == APP_SW0_PRESSED_LEVEL
    )
    {
        app_sw0_interrupt_request = GPIO_TRUE;
    }
}

/* Main function */

void main(void)
{
    gpio_uint8_t app_sos_state;

    app_sos_state = APP_SOS_STATE_DISABLED;
    app_sw0_interrupt_request = GPIO_FALSE;

    app_initialize_hardware();
    app_initialize_sw0_interrupt();

    while (GPIO_TRUE)
    {
        /*
        Cand SOS-ul este oprit, o cerere produsa de SW0
        porneste secventa.
        */
        if (app_sos_state == APP_SOS_STATE_DISABLED)
        {
            if (app_get_and_clear_sw0_request() == GPIO_TRUE)
            {
                app_sos_state = APP_SOS_STATE_ENABLED;
            }
        }

        /*
        Cand SOS-ul este pornit, secventa este executata
        pana cand este apasat din nou SW0.
        */
        if (app_sos_state == APP_SOS_STATE_ENABLED)
        {
            app_sos_state = sos_play_interruptible(
                &PORTC,
                APP_LED0_PIN_NUMBER,
                &app_sw0_interrupt_request
            );

            if (app_sos_state == APP_SOS_STATE_DISABLED)
            {
                /*
                Cererea care a oprit secventa este consumata aici,
                pentru a nu porni imediat o noua secventa SOS.
                */
                app_clear_sw0_request();

                led_power_off(
                    &PORTC,
                    APP_LED0_PIN_NUMBER
                );
            }
            else
            {
                app_delay_between_sos_messages();
            }
        }
    }
}

/* Static private functions implementation */

static void app_initialize_hardware(void)
{
    /*
    SW0 este conectat la PC6.
    PC6 este configurat ca intrare.
    */
    gpio_set_direction(
        &DDRC,
        APP_SW0_PIN_NUMBER,
        GPIO_INPUT
    );

    /*
    Placa nu contine o rezistenta pull-up externa pentru SW0.
    Din acest motiv este activata rezistenta pull-up interna.

    Buton eliberat: PC6 = HIGH
    Buton apasat:   PC6 = LOW
    */
    gpio_activate_pullup(
        &PORTC,
        APP_SW0_PIN_NUMBER
    );

    /*
    LED0 este conectat la PC7.
    PC7 este configurat ca iesire.
    */
    gpio_set_direction(
        &DDRC,
        APP_LED0_PIN_NUMBER,
        GPIO_OUTPUT
    );

    /*
    LED0 este active-low.
    Scrierea valorii HIGH mentine LED-ul stins.
    */
    led_power_off(
        &PORTC,
        APP_LED0_PIN_NUMBER
    );
}

static void app_initialize_sw0_interrupt(void)
{
    /*
    PC6 corespunde pinului PCINT22.

    PCINT22 face parte din grupa PCINT[23:16],
    controlata prin PCMSK2 si PCIE2.
    */

    /* Permite pinului PCINT22 sa genereze intreruperi. */
    PCMSK2_PCINT22 = APP_SW0_PCINT_ENABLE_VALUE;

    /*
    Sterge un eventual flag hardware ramas setat.

    Flagurile hardware se sterg prin scrierea valorii 1.
    */
    PCIFR_PCIF2 = APP_SW0_INTERRUPT_FLAG_CLEAR_VALUE;

    /* Activeaza grupa Pin Change Interrupt Request 2. */
    PCICR_PCIE2 = APP_SW0_INTERRUPT_GROUP_ENABLE_VALUE;

    /* Activeaza global sistemul de intreruperi. */
    __enable_interrupt();
}

static gpio_uint8_t app_get_and_clear_sw0_request(void)
{
    gpio_uint8_t app_request;

    /*
    Intreruperile sunt dezactivate pentru o perioada foarte scurta,
    astfel incat citirea si resetarea flagului sa reprezinte
    o singura operatie logica.
    */
    __disable_interrupt();

    app_request = app_sw0_interrupt_request;
    app_sw0_interrupt_request = GPIO_FALSE;

    __enable_interrupt();

    return app_request;
}

static void app_clear_sw0_request(void)
{
    /*
    Flagul este resetat intr-o sectiune critica scurta,
    pentru a evita modificarea sa simultana de catre ISR.
    */
    __disable_interrupt();

    app_sw0_interrupt_request = GPIO_FALSE;

    __enable_interrupt();
}

static void app_delay_between_sos_messages(void)
{
    volatile unsigned long app_delay_counter;

    for (
        app_delay_counter = APP_DELAY_COUNTER_INITIAL_VALUE;
        app_delay_counter < APP_SOS_MESSAGE_PAUSE_DELAY_COUNT;
        app_delay_counter++
    )
    {
        /*
        Daca SW0 este apasat in timpul pauzei dintre doua mesaje,
        bucla de asteptare este oprita.

        Cererea va fi procesata la urmatoarea iteratie
        a programului principal.
        */
        if (app_sw0_interrupt_request == GPIO_TRUE)
        {
            break;
        }
    }
}