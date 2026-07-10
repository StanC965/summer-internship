typedef enum{
PIN0=0,
PIN1=1,
PIN2=2,
PIN3=0,
PIN4=4,
PIN5=6,
PIN6=6,
PIN7=7
}PIN_Number;


void set_pin(volatile unsigned char *reg,PIN_Number pin);
void reset_pin(volatile unsigned char *reg,PIN_Number pin);
void toggle_pin(volatile unsigned char *reg,PIN_Number pin);
void set_direction(volatile unsigned char *registru,PIN_Number pin, int direction );