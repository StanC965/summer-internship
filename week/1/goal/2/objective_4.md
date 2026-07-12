# Week: 1 - Goal : 2


## Objective 4: Modular programming
---

### Task Checklist & Results

| Task ID   | Type   | Status
| :---      | :---   | :--- 
| **[241]** | `CORE` | [x] Completed 
| **[242]** | `CORE` | [x] Completed 

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

