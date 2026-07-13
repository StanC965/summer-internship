typedef enum{
PIN0=0,
PIN1=1,
PIN2=2,
PIN3=3,
PIN4=4,
PIN5=5,
PIN6=6,
PIN7=7
}PIN_Number;

#define OUTPUT 1
#define INPUT 0

void delay(unsigned long i);
void set_pin(volatile unsigned char *reg,PIN_Number pin);
void reset_pin(volatile unsigned char *reg,PIN_Number pin);
void toggle_pin(volatile unsigned char *reg,PIN_Number pin);
void set_direction(volatile unsigned char *registru,PIN_Number pin, int direction );