#include "iom324pb.h"
#include "gpio.h"
#include "led.h"
#include "sos.h"
#include <intrinsics.h>

#define GPIO_INPUT   0
#define GPIO_OUTPUT  1
#define PULLUP_ON    1
#define INTERRUPT_ENABLED  1

#define BUTTON1_PIN  1   /* PC1 */
#define BUTTON2_PIN  0   /* PA0 */
#define BUTTON3_PIN  1   /* PA1 */
#define LED1_PIN     5   /* PD5 */
#define LED2_PIN     4   /* PD4 */
#define LED3_PIN     3   /* PA3 */
#define LED0_PIN     7   /* PC7 */

#pragma vector = PCINT2_vect
__interrupt void pcint2_isr(void)
{

}

void main(void)
{

    DDRC_DDRC6 = GPIO_INPUT;
    PORTC_PORTC6 = PULLUP_ON;
    PCMSK2_PCINT22 = INTERRUPT_ENABLED;
    PCICR_PCIE2 = INTERRUPT_ENABLED;


    gpio_set_direction(&DDRC, BUTTON1_PIN, GPIO_INPUT);
    gpio_set_pin(&PORTC, BUTTON1_PIN);

    gpio_set_direction(&DDRA, BUTTON2_PIN, GPIO_INPUT);
    gpio_set_pin(&PORTA, BUTTON2_PIN);

    gpio_set_direction(&DDRA, BUTTON3_PIN, GPIO_INPUT);
    gpio_set_pin(&PORTA, BUTTON3_PIN);

    gpio_set_direction(&DDRD, LED1_PIN, GPIO_OUTPUT);
    gpio_set_direction(&DDRD, LED2_PIN, GPIO_OUTPUT);
    gpio_set_direction(&DDRA, LED3_PIN, GPIO_OUTPUT);
    gpio_set_direction(&DDRC, LED0_PIN, GPIO_OUTPUT);

    led_off(&PORTD, LED1_PIN);
    led_off(&PORTD, LED2_PIN);
    led_off(&PORTA, LED3_PIN);
    led_off(&PORTC, LED0_PIN);

    __enable_interrupt();

    while (1)
    {
        if (gpio_debounce(&PINC, BUTTON1_PIN))
            led_on(&PORTD, LED1_PIN);
        else
            led_off(&PORTD, LED1_PIN);

        if (gpio_debounce(&PINA, BUTTON2_PIN))
            led_on(&PORTD, LED2_PIN);
        else
            led_off(&PORTD, LED2_PIN);

        if (gpio_debounce(&PINA, BUTTON3_PIN))
            led_on(&PORTA, LED3_PIN);
        else
            led_off(&PORTA, LED3_PIN);
    }
}