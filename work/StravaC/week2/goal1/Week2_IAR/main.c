#include "iom324pb.h"
#include "intrinsics.h"

#include "gpio.h"
#include "led.h"
#include "sos.h"

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier contine punctul principal al aplicatiei.

Pentru task-ul 316, butonul SW0 nu mai este verificat continuu
prin polling. Apasarea butonului este detectata cu ajutorul
intreruperii PCINT22.

SW0 este conectat la PC6 / PCINT22.
LED0 este conectat la PC7 si este active-low.

Rutina de intrerupere nu executa direct secventa SOS.
Ea doar semnalizeaza aparitia apasarii printr-un flag.
*/

#define SW0_PIN                 (6U)
#define LED0_PIN                (7U)

static volatile gpio_uint8_t sw0_interrupt_request;

/* Static private functions declaration */

static void application_delay_between_sos(void);
static void application_external_interrupt_init(void);
static gpio_uint8_t application_get_sw0_request(void);

/* Interrupt Service Routine */

/*
Rutina pentru grupa PCINT[23:16].

SW0 este conectat la PC6, care are functia alternativa PCINT22.
Intreruperea Pin Change apare atat la apasare, cat si la eliberare,
de aceea starea pinului este verificata in interiorul ISR-ului.
*/
#pragma vector=PCINT2_vect
__interrupt void sw0_interrupt_routine(void)
{
    if (gpio_read_pin(&PINC, SW0_PIN) == GPIO_LOW)
    {
        sw0_interrupt_request = GPIO_TRUE;
    }
}

/* Main function */

void main(void)
{
    gpio_uint8_t sos_enabled;

    sos_enabled = GPIO_FALSE;
    sw0_interrupt_request = GPIO_FALSE;

    /* SW0 - PC6 input */
    gpio_set_direction(&DDRC, SW0_PIN, GPIO_INPUT);

    /* LED0 - PC7 output */
    gpio_set_direction(&DDRC, LED0_PIN, GPIO_OUTPUT);

    /*
    Placa nu are rezistenta pull-up externa pentru SW0.
    Pull-up-ul intern mentine PC6 pe HIGH atunci cand butonul
    nu este apasat.
    */
    gpio_activate_pullup(&PORTC, SW0_PIN);

    /* LED0 este active-low, deci este stins initial. */
    led_power_off(&PORTC, LED0_PIN);

    application_external_interrupt_init();

    while (1)
    {
        if (application_get_sw0_request() == GPIO_TRUE)
        {
            /*
            Prima apasare porneste SOS.
            Urmatoarea apasare il opreste.
            */
            sos_enabled = !sos_enabled;

            if (sos_enabled == GPIO_FALSE)
            {
                led_power_off(&PORTC, LED0_PIN);
            }
        }

        if (sos_enabled == GPIO_TRUE)
        {
            sos_enabled = sos_play_interruptible(&PORTC,
                                                 LED0_PIN,
                                                 &sw0_interrupt_request);

            if (sos_enabled == GPIO_TRUE)
            {
                application_delay_between_sos();
            }
        }
    }
}

/* Static private functions implementation */

static void application_external_interrupt_init(void)
{
    /*
    PC6 corespunde pinului PCINT22.
    PCINT22 face parte din grupa PCINT[23:16], controlata
    de registrul PCMSK2 si de bitul PCIE2.
    */

    /* Permite pinului PCINT22 sa genereze cereri. */
    PCMSK2_PCINT22 = GPIO_ONE;

    /*
    Sterge un eventual flag ramas setat.
    Flagurile de intrerupere se sterg prin scrierea valorii 1.
    */
    PCIFR_PCIF2 = GPIO_ONE;

    /* Activeaza grupa Pin Change Interrupt 2. */
    PCICR_PCIE2 = GPIO_ONE;

    /* Activeaza global intreruperile. */
    __enable_interrupt();
}

static gpio_uint8_t application_get_sw0_request(void)
{
    gpio_uint8_t request;

    request = GPIO_FALSE;

    /*
    Sectiune critica scurta:
    flagul este citit si resetat fara ca ISR-ul sa poata modifica
    valoarea intre cele doua operatii.
    */
    __disable_interrupt();

    if (sw0_interrupt_request == GPIO_TRUE)
    {
        sw0_interrupt_request = GPIO_FALSE;
        request = GPIO_TRUE;
    }

    __enable_interrupt();

    return request;
}

static void application_delay_between_sos(void)
{
    volatile unsigned long i;

    for (i = 0; i < 250000UL; i++)
    {
        /*
        Daca butonul este apasat in timpul pauzei dintre doua
        mesaje SOS, pauza este intrerupta mai devreme.
        */
        if (sw0_interrupt_request == GPIO_TRUE)
        {
            break;
        }
    }
}