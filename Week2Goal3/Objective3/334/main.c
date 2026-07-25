/* 334 - BMW central control panel prototype */

#include "iom324pb.h"
#include <intrinsics.h>
#include "gpio.h"
#include "led.h"
#include "button.h"
#include "panel.h"

#define PCINT22_BIT     (6U)    
#define PCIE2_BIT       (2U)   

#pragma vector=PCINT2_vect
__interrupt void sw0_isr(void)
/* master control routine: SW0 blocks or unblocks the control panel */
{
    if (gpio_read_pin(SW0_PIN_REG, SW0_PIN) == GPIO_LOW)
    {
        panel_toggle_blocked();    
    }
}

static void sw0_interrupt_init(void)
{
    button_init(SW0_DDR, SW0_PORT, SW0_PIN);

    PCMSK2 |= (1 << PCINT22_BIT);   
    PCICR  |= (1 << PCIE2_BIT);    

    __enable_interrupt();
}

void main( void )
{
    panel_init();
    sw0_interrupt_init();

    while(1)
    {
        panel_update();
    }
}
