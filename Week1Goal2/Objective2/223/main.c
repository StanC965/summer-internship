/* 223 - turn on all 3 LEDs of the OLED1 board 
   LED1 -> PD5, LED2 -> PD4, LED3 -> PA3 */

#include "iom324pb.h"

#define LED1_PIN 5   /* LED1 on PD5 */
#define LED2_PIN 4   /* LED2 on PD4 */
#define LED3_PIN 3   /* LED3 on PA3 */

void main( void )
{
    /* configure the LED pins as outputs */
    DDRD |= (1 << LED1_PIN);   /* PD5 output */
    DDRD |= (1 << LED2_PIN);   /* PD4 output */
    DDRA |= (1 << LED3_PIN);   /* PA3 output */

    /* turn all LEDs ON*/
    PORTD &= ~(1 << LED1_PIN);   /* LED1 ON */
    PORTD &= ~(1 << LED2_PIN);   /* LED2 ON */
    PORTA &= ~(1 << LED3_PIN);   /* LED3 ON */

    while(1)
    {
    }
}
