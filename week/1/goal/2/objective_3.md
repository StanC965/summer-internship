# Week: 1 - Goal : 2


## Objective 3: GPIO and Generalization Principle
---

### Task Checklist & Results

| Task ID   | Type   | Status
| :---      | :---   | :--- 
| **[231]** | `CORE` | [x] Completed 
| **[232]** | `CORE` | [x] Completed 

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

> I then tested the function on the program created in objective 2, task 228. I swapped every line of code that set pins from register port C. I added a snippet from the program:

```c
void main (void){
  
  // set PINs direction to OUTPUT
  
  while(1){
    // INITIAL STATE:
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

    delay(50000);

    // STATE 5
    portc_set_pin(7);
    PORTB &= ~(1 << 3);

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

---
