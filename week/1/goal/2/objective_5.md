# Week: 1 - Goal : 2


## Objective 5: Reading the user button SW0 - debounce
---

### Task Checklist & Results

| Task ID   | Type      | Status
| :---      | :---      | :--- 
| **[251]** | `CORE`    | [x] Completed 
| **[252]** | `CORE`    | [x] Completed 
| **[253]** | `CORE`    | [x] Completed 
| **[254]** | `STRETCH` | [x] Completed 
| **[255]** | `CORE`    | [x] Completed 

---

#### Task 251
> **Question/Prompt:** Search in the User Guide the port and the pin to which the SW0 button is connected. Pin direction must be input (signal will be read). To use SW0 you must activate the pull-up resistor for that pin (write 1 to the pin's corresponding bit of the PORTx data register). By pressing the SW0 button the i/o line of the PINx port is coupled to GND (see User Guide and Electronic Schematic). Define a variable to which you assign the value of the PINx register and test if button is pressed. First code you should do it step by step (debugging the code and check the Registers and Watch Windows) in main.c file.

> **Answer/Explanation:**
> The button is connected to port C, pin 6.
> I added a button module which deals with the initialization of the button (sets the pin direction to input). The logic of this module follows the led module.

**`button.c`** 
```c
void button_init(void){
    for(uint8_t i = 0; i < BUTTON_COUNT; i++){
        gpio_set_direction(button_table[i].ddr_register, GPIO_INPUT, button_table[i].pin);
    }
}
```

> I also added a function in this module that activates the pull-up resistor for button:

**`button.c`** 
```c
void button_enable_pullup(button_id_t button_id){
    if(button_id < BUTTON_COUNT){
        gpio_set_pin(button_table[button_id].port_register, button_table[button_id].pin);
    }
}
```

> The functions in the button module use an array that contains the specific configuration of the buttons on the ATmega324PB and OLED1 boards.

**`button.c`** 
```c
static const button_config_t button_table[BUTTON_COUNT] = {
    // ATmega328P onboard button
    { &DDRC, &PORTC, &PINC, 6 },

    // OLED1 buttons
    { &DDRC, &PORTC, &PINC, 1 },
    { &DDRA, &PORTA, &PINA, 0 },
    { &DDRA, &PORTA, &PINA, 1 },
};
```

> Regarding checking whether or not the button was pressed, I tested that by adding a variable called `button_pressed` in main, which gets the state of the button using a function that reads the button's respective pin.
> - If the button was pressed, the function `button_read` will return a LOW, which is equal to 0.
> In that case we need to check if the `button_pressed` variable is equal to 0. This also proves see whether or not the logic works, making the LED turn on.
> - If the button is not pressed, or to turn off the LED after a button press, I also added the function `led_power_off`.

**`main.c`** 
```c
  while(1){
    button_pressed = button_read(BUTTON_ONBOARD);
    
    if(!button_pressed){
      // button is pressed (0), turn on the onboard LED
      led_power_on(LED_ONBOARD); 
    }
    else{
      // button is not pressed (1), turn off the onboard LED
      led_power_off(LED_ONBOARD); 
    }
  }
```

---

#### Task 252
> **Question/Prompt:** Within main.c file combine the reading of a "pressed" SW0 button with turning ON the LED0. Congrats!

> **Answer/Explanation:**

**`button.c`** 
```c
  uint8_t button_pressed;
  
  while(1){
    button_pressed = button_read(BUTTON_ONBOARD);
    
    if(!button_pressed){
      // button is pressed, turn on the onboard LED
      led_power_on(LED_ONBOARD); 
    }
    else{
      // button is not pressed, turn off the onboard LED
      led_power_off(LED_ONBOARD); 
    }
  }
```

---

#### Task 253
> **Question/Prompt:** The GPIO module should be developed further. So add/modify the GPIO module according to the new button functionality. What variables and/or functions should be changed or added? Remember the point where we started in the modular programming. Observe one of the advantages of modular programming, that the code interventions are punctual in the modules affected by the newly added button functionality (LED module is not affected).

> **Answer/Explanation:**
> I added new functions in the gpio module called `gpio_toggle_pin`, and also `gpio_read_pin` to be able to implement the `button_read` function.

**`gpio.c`** 
```c
void gpio_toggle_pin(volatile uint8_t *port_register, uint8_t pin){
  *port_register ^= (1 << pin);
}
  
uint8_t gpio_read_pin(volatile uint8_t *pin_register, uint8_t pin){
  return ((*pin_register & (1 << pin)) != 0);
}
```

> Additionaly, I hava created the button module, which implements:
> - the `button_init` function
> - the `button_enable_pullup` function
> - the `button_read` function

> I integrated the button functions in the main file, alongside the led functions, to light up a led when the button is pressed.
>
> These additions prove further the advantages of modular programming, because code intervations were easy to follow.

---

#### Task 255
> **Question/Prompt:** Introduce a debounce for the button you read to filter the noise in the signal when pressed or released.

> **Answer/Explanation:**
> When a button is presses or released, the metal contacts don't close perfectly in one motion, and that makes them bounce against each other for a few miliseconds. This makes the microcontroller think the button is being pressed and release a dozens of times in a microsecond.
>
> To filter out this noise, a debounce mechanism is introduced. A simple method of software debouncing uses time delays.

**`main.c`** 
```c
  while(1){
    // perform the initial check of the physical button state
    button_pressed = button_read(BUTTON_ONBOARD);
    
    if(!button_pressed){
      // the button appears to be pressed
      // wait 10 miliseconds to let any physical contact bouncing settle
      delay((SECOND / 1000) * 10);
      // read button state again to confirm it wasn't just electrical noise
      button_pressed = button_read(BUTTON_ONBOARD);
      
      if(!button_pressed){
        // the press was validates
        // turn onboard led on
        led_power_on(LED_ONBOARD);
        // wait another 10 miliseconds before checking again
        delay((SECOND / 1000) * 10));
      }
    }
    else{
      led_power_off(LED_ONBOARD); 
    }
  }
```

---

## References & Resources
* ATmega324PB Xplained Pro user guide
