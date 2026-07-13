/* 226 
    1: LED1 ON,  LED2 ON,  LED3 OFF
    2: LED1 OFF, LED2 ON,  LED3 ON
    3: LED1 ON,  LED2 OFF, LED3 ON
    1 2 3 repeat in a loop
*/

#include "iom324pb.h"

#define LED1_PIN 5   /* LED1 on PD5 */
#define LED2_PIN 4   /* LED2 on PD4 */
#define LED3_PIN 3   /* LED3 on PA3 */

#define DELAY_HALF_SECOND 15000UL

#define LED_ON  0    
#define LED_OFF 1    

void delay(void)
{
    volatile unsigned long i;
    for (i = 0; i < DELAY_HALF_SECOND; i++) { }
}

/* set all 3 LEDs at once */
void set_leds(unsigned char led1, unsigned char led2, unsigned char led3)
{
    if (led1 == LED_ON) PORTD &= ~(1 << LED1_PIN); else PORTD |= (1 << LED1_PIN);
    if (led2 == LED_ON) PORTD &= ~(1 << LED2_PIN); else PORTD |= (1 << LED2_PIN);
    if (led3 == LED_ON) PORTA &= ~(1 << LED3_PIN); else PORTA |= (1 << LED3_PIN);
}

void main( void )
{
    /* configure the LED pins as outputs */
    DDRD |= (1 << LED1_PIN);
    DDRD |= (1 << LED2_PIN);
    DDRA |= (1 << LED3_PIN);

    /* initial state: all LEDs OFF */
    set_leds(LED_OFF, LED_OFF, LED_OFF);

    while(1)
    {
        set_leds(LED_ON,  LED_ON,  LED_OFF);   delay();   /* 1 */
        set_leds(LED_OFF, LED_ON,  LED_ON );   delay();   /* 2 */
        set_leds(LED_ON,  LED_OFF, LED_ON );   delay();   /* 3 */
    }
}