# Week: 1 - Goal : 2


## Objective 4: Modular programming
---

### Task Checklist & Results

| Task ID   | Type      | Status
| :---      | :---      | :--- 
| **[241]** | `CORE`    | [x] Completed 
| **[242]** | `CORE`    | [x] Completed 
| **[243]** | `STRETCH` | [x] Completed 
| **[244]** | `CORE`    | [x] Completed 

---

#### Task 241
> **Question/Prompt:** Reorganize your code written until now using the following templates from Reference_Documents folder: mod.c, mod.h.
> Therefore build two files gpio.c and gpio.h. In general, there is a convention that this combination of files (.c and .h) represents a software module. The gpio module must contain only functions and variables used in the very basic management/handling of the pins and ports of the microcontroller (e.g. set, reset pins, etc.). Then include the gpio.h header (the module's interface) in the main.c file to give the program access to the functions contained in the gpio.c. The main.c module will remain as the central module that makes the integration of all the other modules you will create in the future. Why do you think it would be so much needed to organize our software program in a modular way? 

> **Answer/Explanation:**
> Code organization in a modular way has a lot of properties:
> 1. if we want to switch from the ATmega324PB chip to another chip, we do not need to rewrite the entire project, only the internal implemantation
> 2. we can encapsulate variables and function in modules, and make them unreachable from the rest of the other modules
> 3. it provides scalability, other people can work on the project and design other modules, which can then be added without breaking code
> 4. cleaner debugging

---

#### Task 242
> **Question/Prompt:** Further separate the software program, considering the functionality of the LEDs (on, off). Create a new LED module (led.c and led.h) which will contain only the variables and functions that manipulate the on/off state of LEDs (e.g. functions might be referred as PowerOn_LED(...) and PowerOff_LED(...)). These led related functions will call the basic i/o functions of the gpio module!*

> **Answer/Explanation:**

> I created an array which contains the configuration of each LED from the 3 boards: the data register, the port register and the pin number.

**`led.c`** 
```c 
typedef struct {
    volatile uint8_t *ddr_register; 
    volatile uint8_t *port_register; 
    uint8_t pin;                     
} led_config_t;

static const led_config_t led_table[LED_COUNT] = {
    // ATmega328P onboard LED
    { &DDRC, &PORTC, 7 },

    // OLED1 LEDs
    { &DDRD, &PORTD, 5 },
    { &DDRD, &PORTD, 4 },
    { &DDRA, &PORTA, 3 },

    // IO1 LED
    { &DDRB, &PORTB, 3 }
};
```

> The configuration correspond to the following LEDs: 

**`led.h`** 
```c
typedef enum {
    // ATmega328P onboard LED
    LED_ONBOARD = 0,

    // OLED1 LEDs
    LED_OLED1_1,
    LED_OLED1_2,
    LED_OLED1_3,

    // IO1 LED
    LED_IO1,

    LED_COUNT // Total number of LEDs
}led_id_t;

```

> From this array we can extract the port register and the pin number of each LED, in order to turn it on or off.

**`led.c`** 
```c
void led_power_on(led_id_t led_id){
    // check if the led id is correct
    if(led_id < LED_COUNT){
        // drive PORTxn HIGH by setting bit n to 1 (LED OFF)
        gpio_reset_pin(led_table[led_id].port_register, led_table[led_id].pin);
    }
}

void led_power_off(led_id_t led_id){
    // check if the led id is correct
    if(led_id < LED_COUNT){
        // drive PORTxn LOW by clearing bit n to 0 (LED ON)
        gpio_set_pin(led_table[led_id].port_register, led_table[led_id].pin);
    }
}
```

---

#### Task 243
> **Question/Prompt:** The separation of functionalities in logical units allows us to develop new functionalities. For example, add two new LED functionalities to the LED module:
> - LED blink fast = The LED lights on and off repetitively with 6-ons and 6-offs per second;
> - LED blink slow = The LED lights on and off repetitively with 2-ons and 2-offs per second.
>Compile again. It often happens during software development to have to reorganize the written code, process called redesign or refactoring.

> **Answer/Explanation:**

**`led.c`** 
```c
void led_blink_fast(led_id_t led_id){
    if(led_id < LED_COUNT){
        // this loop recreates 12 actions: 6 LED ons and 6 LED offs
        for(uint8_t i = 0; i < 5; i++){
            led_power_on(led_id);
            // because 6 actions needed to be done in 1 second, there is a delay of 
            // 1 second / 4 between the actions
            delay(SECOND / 12);

            led_power_off(led_id);
            delay(SECOND / 12);
        }
    }
}  

void led_blink_slow(led_id_t led_id){
    if(led_id < LED_COUNT){
        // this loop recreates 4 actions: 2 LED ons and 2 LED offs
        for(uint8_t i = 0; i < 2; i++){
            led_power_on(led_id);
            // because 4 actions needed to be done in 1 second, there is a delay of 
            // 1 second / 4 between the actions
            delay(SECOND / 4);

            led_power_off(led_id);
            delay(SECOND / 4);
        }
    }
}  
```

---

#### Task 244
> **Question/Prompt:** In the header file mod.h observe the existence of some constructs at the beginning and at the end of the file (they are called guardians). By analogy, to the gpio module they should look like:

```c
#ifndef GPIO_H
#define GPIO_H
……..
#endif
```

> In your opinion what would be the role of these constructs? To clear the issue of these constructs, compare the output files .i of the preprocessor in these use cases:

> **Answer/Explanation:**

| What you observe to .i files when     | gpio.h is included ONCE in main.c        | gpio.h is included TWICE in main.c
| :---                                  | :---                                     | :--- 
| gpio.h with guardians                 | SAME                                     | SAME
| gpio.h without guardians	            | SAME                                     | DIFFERENCE

> I gathered all of the .i files obtained after the preprocessing stage, for each one of the four cases. After comparing each file what I observed is that the files have the same content for these cases:
> - if we use no guardians but include the header only once in main
> - if we use guardians and include the file as many times as we want
> 
> If we do not use the guardians and include the file twice in main, then the contents of the gpio.h file will appear twice in the .i file.
> 
> The role of these constructs is to prevent duplicate declaration errors during the compilation phase. It ensures that structures, data types, macros and function prototypes are only parsed exactly once by the compiler, no matter how many times or through how many intermediate headers the file is included.

---



