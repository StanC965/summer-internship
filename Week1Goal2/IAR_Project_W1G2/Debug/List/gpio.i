


 




 

 
typedef unsigned char gpio_uint8_t;

 



 










 
extern void gpio_set_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);










 
extern void gpio_reset_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);










 
extern void gpio_toggle_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin);











 
extern void gpio_set_direction(volatile gpio_uint8_t *ddr, gpio_uint8_t pin, gpio_uint8_t direction);




 

 



 

void gpio_set_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin){
  *port |= (1 << pin);
}

void gpio_reset_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin){
  *port &= ~(1 << pin);
}

void gpio_toggle_pin(volatile gpio_uint8_t *port, gpio_uint8_t pin){
  *port ^= (1 << pin);
}

void gpio_set_direction(volatile gpio_uint8_t *ddr, gpio_uint8_t pin, gpio_uint8_t direction){
  direction ? (*ddr |= (1 << pin)) : (*ddr &= ~(1 << pin));
}

