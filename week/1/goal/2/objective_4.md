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
> 1. if we want to switch from the ATmega324PB chip, we do not need to rewrite the entire project, only the internal implemantation.
> 2. we can encapsulate variables and function in modules, and make them unreachable from the rest of the modules
> 3. it provides scalability, other people can work on the project and design other modules, which can then be added without breaking other code
> 4. cleaner debugging

---

#### Task 242
> **Question/Prompt:** Further separate the software program, considering the functionality of the LEDs (on, off). Create a new LED module (led.c and led.h) which will contain only the variables and functions that manipulate the on/off state of LEDs (e.g. functions might be referred as PowerOn_LED(...) and PowerOff_LED(...)). These led related functions will call the basic i/o functions of the gpio module!*

> **Answer/Explanation:**

---

#### Task 243
> **Question/Prompt:** The separation of functionalities in logical units allows us to develop new functionalities. For example, add two new LED functionalities to the LED module:
> - LED blink fast = The LED lights on and off repetitively with 6-ons and 6-offs per second;
> - LED blink slow = The LED lights on and off repetitively with 2-ons and 2-offs per second.
>Compile again. It often happens during software development to have to reorganize the written code, process called redesign or refactoring.

> **Answer/Explanation:**

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

> I gathered all of the .i files obtained after preprocessing for the 4 cases, and after comparing each file what I observed is that the files have the same content if we use no guardians but include the header only once in main or if we use guardians and include the file as many times as we want.
> 
> If we do not use the guardians and include the file twice in main, then the contents of the gpio.h file will appear twice.
> 
> The role of this constructs is to prevent duplicate declaration errors during compilation phase. It ensures that structures, data types, macros and function prototypes are only parsed exactly once by the compiler, no matter how many times or through how many intermediate headers the file is included.

---



