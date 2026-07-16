#ifndef SOS_C
#define SOS_C

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Includes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "sos.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Implementation                                                            */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void Play_Point(void)
{
    PowerOn_LED(LED0_PORT, LED0_PIN);
    for (unsigned long i = 0; i < 150000; i++);
    
    PowerOff_LED(LED0_PORT, LED0_PIN);
    for (unsigned long i = 0; i < 150000; i++);
}

void Play_Line(void)
{
    PowerOn_LED(LED0_PORT, LED0_PIN);
    for (unsigned long i = 0; i < 450000; i++);
    
    PowerOff_LED(LED0_PORT, LED0_PIN);
    for (unsigned long i = 0; i < 150000; i++); 
}

void Play_Letter_S(void)
{
    Play_Point();
    Play_Point();
    Play_Point();
}

void Play_Letter_O(void)
{
    Play_Line();
    Play_Line();
    Play_Line();
}

void Play_SOS(void)
{
    Play_Letter_S();
    
    for (unsigned long i = 0; i < 700000; i++);

    Play_Letter_O();
    
    for (unsigned long i = 0; i < 700000; i++);

    Play_Letter_S();
    
    for (unsigned long i = 0; i < 000000; i++);
}

#endif