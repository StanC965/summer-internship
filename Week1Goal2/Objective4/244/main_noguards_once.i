#line 1 "C:\\Users\\Bibi\\Desktop\\summer-internship\\Week1Goal2\\main.c"
 

#line 1 "C:\\Users\\Bibi\\Desktop\\summer-internship\\Week1Goal2\\gpio.h"





 
 


 


 
 
 







 
extern void gpio_set_pin(unsigned char pin);







 
extern void gpio_reset_pin(unsigned char pin);







 
extern void gpio_toggle_pin(unsigned char pin);








 
extern void gpio_set_direction(unsigned char pin, unsigned char direction);

#line 4 "C:\\Users\\Bibi\\Desktop\\summer-internship\\Week1Goal2\\main.c"
#line 1 "C:\\Users\\Bibi\\Desktop\\summer-internship\\Week1Goal2\\led.h"





 
 


 
 
 

 
extern void led_init(void);

 
extern void led_power_on(void);

 
extern void led_power_off(void);

 
extern void led_blink_fast(void);

 
extern void led_blink_slow(void);

#line 5 "C:\\Users\\Bibi\\Desktop\\summer-internship\\Week1Goal2\\main.c"

void main( void )
{
    led_init();

    while(1)
    {
        led_blink_slow();   
    }
}
