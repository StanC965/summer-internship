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

void Play_SOS(void)
{
    Play_Point();
    Play_Point();
    Play_Point();
    
    for (unsigned long i = 0; i < 200000; i++);

    // 3 Lines (---)
    Play_Line();
    Play_Line();
    Play_Line();
    
    for (unsigned long i = 0; i < 200000; i++);

    // 3 Points (...)
    Play_Point();
    Play_Point();
    Play_Point();
    
    for (unsigned long i = 0; i < 1000000; i++);
}

#endif