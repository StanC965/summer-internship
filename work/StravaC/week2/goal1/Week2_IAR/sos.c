#ifndef SOS_C
#define SOS_C

// Includes

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier contine implementarea modulului sos.

Modulul sos este un nivel de abstractizare mai inalt.

El nu lucreaza direct cu registrele microcontroller-ului pentru LED,
ci foloseste functiile din modulul led.

POINT si LINE sunt comportamente construite peste LED on/off.
SOS este construit peste POINT si LINE.

Pentru versiunea bazata pe intreruperi,
secventa SOS poate fi oprita printr-un flag setat de ISR.

Modulul SOS nu trebuie sa cunoasca pinul butonului,
registrele intreruperii sau numele vectorului.
*/

/* SOS structure */

#define SOS_SYMBOLS_PER_LETTER             (3U)
#define SOS_SYMBOL_INDEX_INITIAL_VALUE     (0U)

/* SOS timing */

#define SOS_POINT_DELAY_COUNT              (30000UL)
#define SOS_LINE_DELAY_COUNT               (120000UL)
#define SOS_SYMBOL_PAUSE_DELAY_COUNT       (30000UL)
#define SOS_DELAY_COUNTER_INITIAL_VALUE    (0UL)

#include "sos.h"
#include "led.h"

/* Static private functions declaration */

static void sos_point(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
);

static void sos_line(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
);

static gpio_uint8_t sos_point_interruptible(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin,
    volatile gpio_uint8_t *interrupt_request
);

static gpio_uint8_t sos_line_interruptible(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin,
    volatile gpio_uint8_t *interrupt_request
);

static gpio_uint8_t sos_interrupt_is_requested(
    volatile gpio_uint8_t *interrupt_request
);

static gpio_uint8_t sos_delay_interruptible(
    unsigned long delay_count,
    volatile gpio_uint8_t *interrupt_request
);

static void sos_delay_point(void);

static void sos_delay_line(void);

static void sos_delay_pause(void);

static void sos_delay(
    unsigned long delay_count
);

/* Public functions */

void sos_play(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    gpio_uint8_t symbol_index;

    /*
    Prima litera S:
    trei puncte.
    */
    for (
        symbol_index = SOS_SYMBOL_INDEX_INITIAL_VALUE;
        symbol_index < SOS_SYMBOLS_PER_LETTER;
        symbol_index++
    )
    {
        sos_point(
            port,
            pin
        );
    }

    /*
    Litera O:
    trei linii.
    */
    for (
        symbol_index = SOS_SYMBOL_INDEX_INITIAL_VALUE;
        symbol_index < SOS_SYMBOLS_PER_LETTER;
        symbol_index++
    )
    {
        sos_line(
            port,
            pin
        );
    }

    /*
    A doua litera S:
    trei puncte.
    */
    for (
        symbol_index = SOS_SYMBOL_INDEX_INITIAL_VALUE;
        symbol_index < SOS_SYMBOLS_PER_LETTER;
        symbol_index++
    )
    {
        sos_point(
            port,
            pin
        );
    }
}

gpio_uint8_t sos_play_interruptible(
    volatile gpio_uint8_t *led_port,
    gpio_uint8_t led_pin,
    volatile gpio_uint8_t *interrupt_request
)
{
    gpio_uint8_t symbol_index;

    /*
    Verifica daca exista deja o cerere de oprire
    inainte de pornirea mesajului.
    */
    if (sos_interrupt_is_requested(interrupt_request) == GPIO_TRUE)
    {
        led_power_off(
            led_port,
            led_pin
        );

        return GPIO_FALSE;
    }

    /*
    Prima litera S:
    trei puncte.
    */
    for (
        symbol_index = SOS_SYMBOL_INDEX_INITIAL_VALUE;
        symbol_index < SOS_SYMBOLS_PER_LETTER;
        symbol_index++
    )
    {
        if (
            sos_point_interruptible(
                led_port,
                led_pin,
                interrupt_request
            ) == GPIO_FALSE
        )
        {
            led_power_off(
                led_port,
                led_pin
            );

            return GPIO_FALSE;
        }
    }

    /*
    Litera O:
    trei linii.
    */
    for (
        symbol_index = SOS_SYMBOL_INDEX_INITIAL_VALUE;
        symbol_index < SOS_SYMBOLS_PER_LETTER;
        symbol_index++
    )
    {
        if (
            sos_line_interruptible(
                led_port,
                led_pin,
                interrupt_request
            ) == GPIO_FALSE
        )
        {
            led_power_off(
                led_port,
                led_pin
            );

            return GPIO_FALSE;
        }
    }

    /*
    A doua litera S:
    trei puncte.
    */
    for (
        symbol_index = SOS_SYMBOL_INDEX_INITIAL_VALUE;
        symbol_index < SOS_SYMBOLS_PER_LETTER;
        symbol_index++
    )
    {
        if (
            sos_point_interruptible(
                led_port,
                led_pin,
                interrupt_request
            ) == GPIO_FALSE
        )
        {
            led_power_off(
                led_port,
                led_pin
            );

            return GPIO_FALSE;
        }
    }

    return GPIO_TRUE;
}

/* Static private functions */

static void sos_point(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    led_power_on(
        port,
        pin
    );

    sos_delay_point();

    led_power_off(
        port,
        pin
    );

    sos_delay_pause();
}

static void sos_line(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin
)
{
    led_power_on(
        port,
        pin
    );

    sos_delay_line();

    led_power_off(
        port,
        pin
    );

    sos_delay_pause();
}

static gpio_uint8_t sos_point_interruptible(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin,
    volatile gpio_uint8_t *interrupt_request
)
{
    led_power_on(
        port,
        pin
    );

    if (
        sos_delay_interruptible(
            SOS_POINT_DELAY_COUNT,
            interrupt_request
        ) == GPIO_FALSE
    )
    {
        led_power_off(
            port,
            pin
        );

        return GPIO_FALSE;
    }

    led_power_off(
        port,
        pin
    );

    if (
        sos_delay_interruptible(
            SOS_SYMBOL_PAUSE_DELAY_COUNT,
            interrupt_request
        ) == GPIO_FALSE
    )
    {
        return GPIO_FALSE;
    }

    return GPIO_TRUE;
}

static gpio_uint8_t sos_line_interruptible(
    volatile gpio_uint8_t *port,
    gpio_uint8_t pin,
    volatile gpio_uint8_t *interrupt_request
)
{
    led_power_on(
        port,
        pin
    );

    if (
        sos_delay_interruptible(
            SOS_LINE_DELAY_COUNT,
            interrupt_request
        ) == GPIO_FALSE
    )
    {
        led_power_off(
            port,
            pin
        );

        return GPIO_FALSE;
    }

    led_power_off(
        port,
        pin
    );

    if (
        sos_delay_interruptible(
            SOS_SYMBOL_PAUSE_DELAY_COUNT,
            interrupt_request
        ) == GPIO_FALSE
    )
    {
        return GPIO_FALSE;
    }

    return GPIO_TRUE;
}

static gpio_uint8_t sos_interrupt_is_requested(
    volatile gpio_uint8_t *interrupt_request
)
{
    if (interrupt_request == GPIO_NULL)
    {
        return GPIO_FALSE;
    }

    if (*interrupt_request == GPIO_TRUE)
    {
        return GPIO_TRUE;
    }

    return GPIO_FALSE;
}

static gpio_uint8_t sos_delay_interruptible(
    unsigned long delay_count,
    volatile gpio_uint8_t *interrupt_request
)
{
    volatile unsigned long delay_counter;

    for (
        delay_counter = SOS_DELAY_COUNTER_INITIAL_VALUE;
        delay_counter < delay_count;
        delay_counter++
    )
    {
        if (
            sos_interrupt_is_requested(
                interrupt_request
            ) == GPIO_TRUE
        )
        {
            return GPIO_FALSE;
        }
    }

    return GPIO_TRUE;
}

static void sos_delay_point(void)
{
    sos_delay(
        SOS_POINT_DELAY_COUNT
    );
}

static void sos_delay_line(void)
{
    sos_delay(
        SOS_LINE_DELAY_COUNT
    );
}

static void sos_delay_pause(void)
{
    sos_delay(
        SOS_SYMBOL_PAUSE_DELAY_COUNT
    );
}

static void sos_delay(
    unsigned long delay_count
)
{
    volatile unsigned long delay_counter;

    for (
        delay_counter = SOS_DELAY_COUNTER_INITIAL_VALUE;
        delay_counter < delay_count;
        delay_counter++
    )
    {
        /*
        Bucla este folosita pentru realizarea
        unei intarzieri software.
        */
    }
}

#endif