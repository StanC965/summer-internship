#ifndef GPIO_H
#define GPIO_H

// Exported types and values

/*
Autor: Strava Cosmin-Paul
Data: 2026

Acest fisier reprezinta interfata modulului gpio.
Aici sunt declarate tipurile, constantele si functiile publice
care pot fi folosite de alte module.
*/

#define GPIO_NULL              ((void*)0x00U)

#define GPIO_ZERO              (0x00U)
#define GPIO_ONE               (0x01U)

#define GPIO_FALSE             (GPIO_ZERO)
#define GPIO_TRUE              (GPIO_ONE)

#define GPIO_NOTOK             (GPIO_FALSE)
#define GPIO_OK                (GPIO_TRUE)

#define GPIO_INPUT             (GPIO_ZERO)
#define GPIO_OUTPUT            (GPIO_ONE)

typedef unsigned char gpio_uint8_t;
typedef unsigned int  gpio_uint16_t;

// Public functions  

/** \fn         void gpio_set_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin)

    \brief      Seteaza un pin dintr-un registru PORTx.
    \param[in]  port - adresa registrului PORTx
    \param[in]  pin  - numarul pinului care trebuie setat
    \param[out] Nu exista.
    \return     Nu returneaza nimic.
    \details    Scrie 1 logic pe pinul ales, fara sa afecteze ceilalti pini.
*/
extern void gpio_set_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);

/** \fn         void gpio_reset_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin)

    \brief      Reseteaza un pin dintr-un registru PORTx.
    \param[in]  port - adresa registrului PORTx
    \param[in]  pin  - numarul pinului care trebuie resetat
    \param[out] Nu exista.
    \return     Nu returneaza nimic.
    \details    Scrie 0 logic pe pinul ales, fara sa afecteze ceilalti pini.
*/
extern void gpio_reset_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);

/** \fn         void gpio_toggle_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin)

    \brief      Schimba starea unui pin dintr-un registru PORTx.
    \param[in]  port - adresa registrului PORTx
    \param[in]  pin  - numarul pinului care trebuie inversat
    \param[out] Nu exista.
    \return     Nu returneaza nimic.
    \details    Daca pinul este 0 devine 1, iar daca este 1 devine 0.
*/
extern void gpio_toggle_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);

/** \fn         void gpio_set_direction(volatile gpio_uint8_t *ddr, gpio_uint8_t pin, gpio_uint8_t direction)

    \brief      Configureaza directia unui pin.
    \param[in]  ddr       - adresa registrului DDRx
    \param[in]  pin       - numarul pinului care trebuie configurat
    \param[in]  direction - GPIO_OUTPUT pentru output sau GPIO_INPUT pentru input
    \param[out] Nu exista.
    \return     Nu returneaza nimic.
    \details    Scrie in registrul DDRx pentru a configura pinul ca input sau output.
*/
extern void gpio_set_direction(volatile gpio_uint8_t *ddr, gpio_uint8_t pin, gpio_uint8_t direction);

#endif