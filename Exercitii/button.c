#ifndef BUTTON_C
#define BUTTON_C

#include "gpio.h"        
#include "iom324pb.h"  
#include "led.h"
#include "button.h"
      

static volatile unsigned char debounce_buffer_sw0   = 0x1F; 
static volatile unsigned char debounce_buffer_bttn1 = 0x1F; 
static volatile unsigned char debounce_buffer_bttn2 = 0x1F;
static volatile unsigned char debounce_buffer_bttn3 = 0x1F; 

static unsigned char stable_state_sw0 = 0, prev_state_sw0 = 0, press_edge_sw0 = 0;
static unsigned char stable_state_bttn1 = 0, prev_state_bttn1 = 0, press_edge_bttn1 = 0;
static unsigned char stable_state_bttn2 = 0, prev_state_bttn2 = 0, press_edge_bttn2 = 0;
static unsigned char stable_state_bttn3 = 0, prev_state_bttn3 = 0, press_edge_bttn3 = 0;

void buttons_initialize(_Bool bttn1, _Bool bttn2, _Bool bttn3, _Bool SW0)
{
    if(bttn1) {
        gpio_set_direction(&DDRC, 1, GPIO_INPUT);
        gpio_set_pin(&PORTC, 1);
    }
    if(bttn2) {
        gpio_set_direction(&DDRA, 0, GPIO_INPUT);
        gpio_set_pin(&PORTA, 0);
    }
    if(bttn3) {
        gpio_set_direction(&DDRA, 1, GPIO_INPUT);
        gpio_set_pin(&PORTA, 1);
    }
    if(SW0) {
        gpio_set_direction(&DDRC, 6, GPIO_INPUT);
        gpio_set_pin(&PORTC, 6);
    }
}


void button_update_all(void)
{
    unsigned char current;

    // SW0 Debounce
    current = ((PINC & 0x40) == 0) ? 1 : 0;
    debounce_buffer_sw0 = ((debounce_buffer_sw0 << 1) | current) & 0x1F; 
    
    if (debounce_buffer_sw0 == 0x1F) 
      stable_state_sw0 = 1;//oprit
    else if (debounce_buffer_sw0 == 0x00) 
      stable_state_sw0 = 0;//pornit
    
    press_edge_sw0 = (stable_state_sw0 == 1 && prev_state_sw0 == 0);
    prev_state_sw0 = stable_state_sw0;

    // BTTN1 Debounce
    current = ((PINC & 0x02) == 0) ? 1 : 0;
    debounce_buffer_bttn1 = ((debounce_buffer_bttn1 << 1) | current) & 0x1F;
    
    if (debounce_buffer_bttn1 == 0x1F) 
      stable_state_bttn1 = 1;
    else if (debounce_buffer_bttn1 == 0x00)
      stable_state_bttn1 = 0;
    press_edge_bttn1 = (stable_state_bttn1 == 1 && prev_state_bttn1 == 0);
    prev_state_bttn1 = stable_state_bttn1;

    // BTTN2 Debounce
    current = ((PINA & 0x01) == 0) ? 1 : 0;
    debounce_buffer_bttn2 = ((debounce_buffer_bttn2 << 1) | current) & 0x1F;
    
    if (debounce_buffer_bttn2 == 0x1F)
      stable_state_bttn2 = 1;
    else if (debounce_buffer_bttn2 == 0x00)
      stable_state_bttn2 = 0;
    press_edge_bttn2 = (stable_state_bttn2 == 1 && prev_state_bttn2 == 0);
    prev_state_bttn2 = stable_state_bttn2;

    // BTTN3 Debounce
    current = ((PINA & 0x02) == 0) ? 1 : 0;
    debounce_buffer_bttn3 = ((debounce_buffer_bttn3 << 1) | current) & 0x1F;
    
    if (debounce_buffer_bttn3 == 0x1F)
      stable_state_bttn3 = 1;
    else if (debounce_buffer_bttn3 == 0x00)
      stable_state_bttn3 = 0;
    press_edge_bttn3 = (stable_state_bttn3 == 1 && prev_state_bttn3 == 0);
    prev_state_bttn3 = stable_state_bttn3;
}


unsigned char button_get_press_sw0(void)  
{ unsigned char ret = press_edge_sw0;   press_edge_sw0 = 0;   return ret; }

unsigned char button_get_press_bttn1(void)
{ unsigned char ret = press_edge_bttn1; press_edge_bttn1 = 0; return ret; }

unsigned char button_get_press_bttn2(void) 
{ unsigned char ret = press_edge_bttn2; press_edge_bttn2 = 0; return ret; }

unsigned char button_get_press_bttn3(void)
{ unsigned char ret = press_edge_bttn3; press_edge_bttn3 = 0; return ret; }

#endif