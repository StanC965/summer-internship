#include "iom324pb.h"
#include "gpio.h" 
#include "led.h" 
#include "sos.h"

extern volatile _Bool sos_stop; 

_Bool current_button_state = 0;
_Bool last_button_state = 0;

void setup(void)
{
    leds_initialize(1, 0, 0, 0, 0); 
    gpio_set_direction(&DDRC, 6, GPIO_INPUT);
    gpio_set_pin(&PORTC, 6); // Pull-up activat asta inseamna ca butonul e active low 
    
    sos_stop = 1; 
}

void ButtonTask(void)
{
    current_button_state = (gpio_read_pin(&PINC,6) == GPIO_FALSE);

    if(current_button_state && !last_button_state)
    {
        sos_stop = !sos_stop;                   // toggle sos la schimbarea starii (cod gray)
    }

    last_button_state = current_button_state;// actualizam starea 
}

void main(void)
{
    setup();
                                                                              //Functionare:am schimbat pe metoda de stari si valori boolene si am renuntat la confidence level
                // astfel acuma acel debounce se face printr-o bucla while la apasarea butonului  ca si schimbari am adaugat bool sos_stop care prin interogare la fiecare instructiune
    while(1)    //continua sau opreste executia astfel avem efectul de toggle la functia SOS .
    {
        ButtonTask();

        if(!sos_stop) // polling simplu                         // rezolutia interogarii este la instructiune pentru fiecare punct . linie  
        {                                       
            SOS();
            
        //    Sincronizam starea butonului dupa terminarea SOS, ca sa nu reinitializeze imediat
            last_button_state = (gpio_read_pin(&PINC,6) == GPIO_FALSE);
        }
        else
        {
            led_Reset(LED_ZERO);
        }
    }
}