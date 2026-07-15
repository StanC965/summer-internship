/* 252 - read the SW0 button and turn ON LED0 while it is pressed
   SW0  -> PC6 
   LED0 -> PC7  
*/

#include "iom324pb.h"

#define SW0_PIN  6
#define LED0_PIN 7

void main( void )
{
    DDRC &= ~(1 << SW0_PIN);     /* PC6 as input */
    PORTC |= (1 << SW0_PIN);     /* enable internal pull-up on PC6 */

    DDRC |= (1 << LED0_PIN);     /* PC7 as output */
    PORTC |= (1 << LED0_PIN);    /* LED0 OFF at start */

    while(1)
    {
        /* button pressed means bit 6 of PINC is 0 */
        if ((PINC & (1 << SW0_PIN)) == 0)
        {
            PORTC &= ~(1 << LED0_PIN);   /* LED0 ON  */
        }
        else
        {
            PORTC |= (1 << LED0_PIN);    /* LED0 OFF */
        }
    }
}
