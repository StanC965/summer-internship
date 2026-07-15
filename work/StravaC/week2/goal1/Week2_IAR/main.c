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
*/

/* Board connections */

#define SW0_PIN_NUMBER                     (6U)
#define LED0_PIN_NUMBER                    (7U)

/* Button logic */

#define SW0_PRESSED_LEVEL                  (GPIO_LOW)

/* Pin Change Interrupt configuration */

#define SW0_PCINT_ENABLE_VALUE             (GPIO_ONE)
#define SW0_INTERRUPT_GROUP_ENABLE_VALUE   (GPIO_ONE)
#define SW0_INTERRUPT_FLAG_CLEAR_VALUE     (GPIO_ONE)

/* Application states */

#define SOS_STATE_DISABLED                 (GPIO_FALSE)
#define SOS_STATE_ENABLED                  (GPIO_TRUE)

/* Delay configuration */

#define SOS_MESSAGE_PAUSE_DELAY_COUNT      (250000UL)
#define DELAY_COUNTER_INITIAL_VALUE        (0UL)

/*
Flagul este declarat volatile deoarece este modificat
de rutina de intrerupere si citit de programul principal.
*/
static volatile gpio_uint8_t sw0_interrupt_request;

/* Static private functions declaration */

static void application_initialize_hardware(void);

static void application_initialize_sw0_interrupt(void);

static gpio_uint8_t application_get_and_clear_sw0_request(void);

static void application_clear_sw0_request(void);

static void application_delay_between_sos_messages(void);

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
__interrupt void sw0_interrupt_service_routine(void)
{
    if (gpio_read_pin(&PINC, SW0_PIN_NUMBER) == SW0_PRESSED_LEVEL)
    {
        sw0_interrupt_request = GPIO_TRUE;
    }
}

/* Main function */

void main(void)
{
    gpio_uint8_t sos_state;

    sos_state = SOS_STATE_DISABLED;
    sw0_interrupt_request = GPIO_FALSE;

    application_initialize_hardware();
    application_initialize_sw0_interrupt();

    while (GPIO_TRUE)
    {
        /*
        Cand SOS-ul este oprit, o cerere produsa de SW0
        porneste secventa.
        */
        if (sos_state == SOS_STATE_DISABLED)
        {
            if (application_get_and_clear_sw0_request() == GPIO_TRUE)
            {
                sos_state = SOS_STATE_ENABLED;
            }
        }

        /*
        Cand SOS-ul este pornit, secventa este executata
        pana cand este apasat din nou SW0.
        */
        if (sos_state == SOS_STATE_ENABLED)
        {
            sos_state = sos_play_interruptible(
                &PORTC,
                LED0_PIN_NUMBER,
                &sw0_interrupt_request
            );

            if (sos_state == SOS_STATE_DISABLED)
            {
                /*
                Cererea care a oprit secventa este consumata aici,
                pentru a nu porni imediat o noua secventa SOS.
                */
                application_clear_sw0_request();

                led_power_off(&PORTC, LED0_PIN_NUMBER);
            }
            else
            {
                application_delay_between_sos_messages();
            }
        }
    }
}

/* Static private functions implementation */

static void application_initialize_hardware(void)
{
    /*
    SW0 este conectat la PC6.
    PC6 este configurat ca intrare.
    */
    gpio_set_direction(
        &DDRC,
        SW0_PIN_NUMBER,
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
        SW0_PIN_NUMBER
    );

    /*
    LED0 este conectat la PC7.
    PC7 este configurat ca iesire.
    */
    gpio_set_direction(
        &DDRC,
        LED0_PIN_NUMBER,
        GPIO_OUTPUT
    );

    /*
    LED0 este active-low.
    Scrierea valorii HIGH mentine LED-ul stins.
    */
    led_power_off(
        &PORTC,
        LED0_PIN_NUMBER
    );
}

static void application_initialize_sw0_interrupt(void)
{
    /*
    PC6 corespunde pinului PCINT22.

    PCINT22 face parte din grupa PCINT[23:16],
    controlata prin PCMSK2 si PCIE2.
    */

    /* Permite pinului PCINT22 sa genereze intreruperi. */
    PCMSK2_PCINT22 = SW0_PCINT_ENABLE_VALUE;

    /*
    Sterge un eventual flag ramas setat.

    Flagurile hardware se sterg prin scrierea valorii 1.
    */
    PCIFR_PCIF2 = SW0_INTERRUPT_FLAG_CLEAR_VALUE;

    /* Activeaza grupa Pin Change Interrupt Request 2. */
    PCICR_PCIE2 = SW0_INTERRUPT_GROUP_ENABLE_VALUE;

    /* Activeaza global sistemul de intreruperi. */
    __enable_interrupt();
}

static gpio_uint8_t application_get_and_clear_sw0_request(void)
{
    gpio_uint8_t request;

    /*
    Intreruperile sunt dezactivate pentru o perioada foarte scurta,
    astfel incat citirea si resetarea flagului sa reprezinte
    o singura operatie logica.
    */
    __disable_interrupt();

    request = sw0_interrupt_request;
    sw0_interrupt_request = GPIO_FALSE;

    __enable_interrupt();

    return request;
}

static void application_clear_sw0_request(void)
{
    /*
    Flagul este resetat intr-o sectiune critica scurta,
    pentru a evita modificarea sa simultana de catre ISR.
    */
    __disable_interrupt();

    sw0_interrupt_request = GPIO_FALSE;

    __enable_interrupt();
}

static void application_delay_between_sos_messages(void)
{
    volatile unsigned long delay_counter;

    for (
        delay_counter = DELAY_COUNTER_INITIAL_VALUE;
        delay_counter < SOS_MESSAGE_PAUSE_DELAY_COUNT;
        delay_counter++
    )
    {
        /*
        Daca SW0 este apasat in timpul pauzei dintre doua mesaje,
        bucla de asteptare este oprita.

        Cererea va fi procesata la urmatoarea iteratie
        a programului principal.
        */
        if (sw0_interrupt_request == GPIO_TRUE)
        {
            break;
        }
    }
}