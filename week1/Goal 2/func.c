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

void set_pin_PORTC(PIN_Number pin){
  PORTC |=(0x01<<pin);
}
void reset_pin_PORTC(PIN_Number pin){
  PORTC &=(0xfe<<pin);
}
void set_pin(volatile unsigned char *reg,PIN_Number pin){
  *reg |=(0x01<<pin);
}
void reset_pin(volatile unsigned char *reg,PIN_Number pin){
  *reg &=(0xfe<<pin);
}
void toggle_pin(volatile unsigned char *reg,PIN_Number pin){
  *reg ^=(0x01<<pin);
}
void set_direction(volatile unsigned char *registru,PIN_Number pin, int direction ){
  (direction==1)? (*registru |=(0x01<<pin)) : (*registru =(0xfe<<pin));     
}

void main(void){

}