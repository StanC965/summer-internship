# Week: 1 - Goal : 2


## Objective 3: GPIO and Generalization Principle
---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[231]** | `CORE`     | [x] Completed 
| **[232]** | `CORE`     | [x] Completed 
| **[233]** | `CORE`     | [x] Completed 
| **[234]** | `OPTIONAL` | [x] Completed 
| **[235]** | `OPTIONAL` | [x] Completed 
| **[236]** | `OPTIONAL` | [x] Completed 

---

#### Task 231
> **Question/Prompt:** Build a single function e.g. set_pin( … ) to set (set = means writing value "1" to bit) any pin from register PORTC, without affecting the state of the remaining pins from the PORTC. What parameters do you need to build the function? Test this function with LEDs connected to PORTC pins.

> **Answer/Explanation:**
> I used a parameter `pin`, of type `uint8_t`, because a pin number can only be between 0 and 7, and using a parameter of type `int` would've taken up memory space, since it uses 2 bytes. 

```c
void portc_set_pin(uint8_t pin){
  PORTC |= (1 << pin);
}
```

> I then tested the function in the program created in objective 2, task 228. I swapped every line of code that set pins from register port C. I added a snippet from the program:

```c
void main (void){
  
  // set PINs direction to OUTPUT
  
  while(1){
    // INITIAL STATE
    PORTD |= 1 << 5;
    PORTD |= 1 << 4;
    PORTA |= 1 << 3;
    portc_set_pin(7);
    PORTB |= 1 << 3;

    delay(50000);

    // STATE 1

    delay(50000);

    // STATE 2

    delay(50000);

    // STATE 3

    delay(50000);

    // STATE 4
    portc_reset_pin(7);

    delay(50000);

    // STATE 5
    portc_set_pin(7);

    delay(50000);

  }
}
```

---

#### Task 232
> **Question/Prompt:** Build another function e.g. reset_pin( … ) to reset (reset = means writing value "0" to bit) any pin from the same register without changing the other pins value from the register. Test with LEDs connected to PORTC.

> **Answer/Explanation:**

```c
void portc_reset_pin(uint8_t pin){
  PORTC &= ~(1 << pin);
}
```

> I then tested the function in the program:

```c
void main (void){
  
  // set PINs direction to OUTPUT
  
  while(1){
    // INITIAL STATE
    PORTD |= 1 << 5;
    PORTD |= 1 << 4;
    PORTA |= 1 << 3;
    portc_set_pin(7);
    PORTB |= 1 << 3;

    delay(50000);

    // STATE 1

    delay(50000);

    // STATE 2

    delay(50000);

    // STATE 3

    delay(50000);

    // STATE 4
    portc_reset_pin(7);

    delay(50000);

    // STATE 5
    portc_set_pin(7);

    delay(50000);

  }
}
```

---

#### Task 233
> **Question/Prompt:** Finally, build a function only for managing the direction (input/output) of any pin. It can be named e.g. set_direction( ... ). What parameters should it receive and what values should it return?

> **Answer/Explanation:**
> The function needs 2 parameters of type `uint8_t`, one for the pin number and one for the direction of the data.
> It should return nothing, because its purpose is to configure a hardware register.

> I also defined two constants for distinguishing between the direction of the data, because each direction has a different bitwise operation.

```c
#define INPUT 0
#define OUTPUT 1

void ddrc_set_direction(uint8_t direction, uint8_t pin){
  if(direction == OUTPUT){
    DDRC |= (1 << pin);
  } else {
    DDRC &= ~(1 << pin);
  }
}
```

> I then tested the function in the program:

```c
void main (void){
  
  // set PINs direction to OUTPUT
  ddrc_set_direction(OUTPUT, 7);
  
  while(1){
    // INITIAL STATE
    PORTD |= 1 << 5;
    PORTD |= 1 << 4;
    PORTA |= 1 << 3;
    portc_set_pin(7);
    PORTB |= 1 << 3;

    delay(50000);

    // STATE 1

    delay(50000);

    // STATE 2

    delay(50000);

    // STATE 3

    delay(50000);

    // STATE 4
    portc_reset_pin(7);

    delay(50000);

    // STATE 5
    portc_set_pin(7);

    delay(50000);

  }
}
```

---

#### Task 234
> **Question/Prompt:** Build yet another function e.g. toggle_pin( … ) to toggle any pin from the same register, without affecting any other pin from the register.

> **Answer/Explanation:**

```c
void portc_toggle_pin(uint8_t pin){
  PORTC ^= (1 << pin);
}
```

> I then tested the function in the program:

```c
void main (void){
  
  // set PINs direction to OUTPUT
  ddrc_set_direction(OUTPUT, 7);
  
  while(1){
    // INITIAL STATE
    PORTD |= 1 << 5;
    PORTD |= 1 << 4;
    PORTA |= 1 << 3;
    portc_set_pin(7);
    PORTB |= 1 << 3;

    delay(50000);

    // STATE 1

    delay(50000);

    // STATE 2

    delay(50000);

    // STATE 3

    delay(50000);

    // STATE 4
    portc_reset_pin(7);

    delay(50000);

    // STATE 5
    portc_set_pin(7);

    delay(50000);

    // STATE 6
    portc_toggle_pin(7);
    
    delay(50000);

  }
}
```

---

#### Task 235
> **Question/Prompt:** A real challenge is to reduce the complexity of the code for each function above, by writing the functionality of each function in a single line of code! How can you realize this?

> **Answer/Explanation:**
> I did use a single line of code for most functions, and for the function that sets the direction I used a ternary operator.

```c
void portc_set_pin(uint8_t pin){
  PORTC |= (1 << pin);
}

void portc_reset_pin(uint8_t pin){
  PORTC &= ~(1 << pin);
}

void ddrc_set_direction(uint8_t direction, uint8_t pin){
  DDRC = (direction == OUTPUT) ? (DDRC | (1 << pin)) : (DDRC & ~(1 << pin)); 
}

void portc_toggle_pin(uint8_t pin){
  PORTC ^= (1 << pin);
}
```

---

#### Task 236
> **Question/Prompt:** Yet another challenge is to generalize the functions above to cover all existing ports and pins on this ATmega324PB microcontroller! In this way you will cover any connection LED <=> pin! What parameters you could design your function to have in order to cover the existing variability?

> **Answer/Explanation:**
> In order to be able to use the previous functions not only for port C, but for the rest of the ports and registers, I used pointers.
> 
> The hardware registers are not variables, but instead they are macros that point directly to specific memory addresses in the microcontroller's RAM map. Because they are just memory addresses, they can be passed into a function using a pointer.
>
> I went with parameters of type volatile to practice some critical code adaptions in embedded systems, even tough the compiler optimizations are turned off for this project.

```c
void gpio_set_pin(volatile uint8_t *port, uint8_t pin){
  *port |= (1 << pin);
}

void gpio_reset_pin(volatile uint8_t *port, uint8_t pin){
  *port &= ~(1 << pin);
}

void gpio_set_direction(volatile uint8_t *ddr_register, uint8_t direction, uint8_t pin){
  *ddr_register = (direction == OUTPUT) ? (*ddr_register | (1 << pin)) : (*ddr_register & ~(1 << pin)); 
}

void gpio_toggle_pin(volatile uint8_t *port, uint8_t pin){
  *port ^= (1 << pin);
}
```

---

