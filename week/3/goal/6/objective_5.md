# Week: 3 - Goal : 6


## Objective 5: Measuring the code size

---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[651]** | `CORE`     | [x] Completed
| **[652]** | `CORE`     | [x] Completed
| **[653]** | `CORE`     | [x] Completed
| **[654]** | `STRETCH`  | [] Completed
| **[655]** | `STRETCH`  | [] Completed
| **[656]** | `OPTIONAL` | [] Completed

---

#### Task 651
> **Question/Prompt:** Why bother measuring the code size? In embedded systems we don't have at our disposal too much memory, from ~2KB to ~8MB, therefore it becomes a highly important resource you should take care about. Activate memory map by right-click on Project Name => Options => Linker => List and make sure you mark the following checkboxes.

> **Answer/Explanation:**
> 

---

#### Task 652
> **Question/Prompt:** Then, after compiling, open from Project Browser the .map file. This file is showing you the layout of object files and how the linker processed those object files into the final executable file. There are a lot of things to know about linker, but for the moment retain the following:

> - a function or a variable is usually named ENTRY
> - memory is organized in several zones, most important are CODE (storing your code) and DATA (storing your variables)
> - within those memory zones there will be several types of SEGMENTS
> - addresses are given in hexadecimal as start address and end address (in paranthesis is the ENTRY's total size in hexa)
> 
> Below is the example of main.r90 object file corresponding to main.c file containing the initial code from exercise 143 (yeah! week 1 :)).

> **Answer/Explanation:**
> 

---

#### Task 653
> **Question/Prompt:** Open the .map file of your current project code and check the code size for the following functions:

> **Answer/Explanation:**


| functions proposed for measuring	|implementation with switch — CODE	| implementation with switch — DATA*	|implementation with binary operators — CODE	|implementation with binary operators — DATA*
| :---                              | :---                              | :---                                  | :---                                          | :---    
|set_pin (…)				        | 0x18 (24B)                        | 0                                     | 0x14 (20B)                                    | 0
|reset_pin(…)	                    | 0x1A (26B)                        | 0                                     | 0x16 (22B)                                    | 0

> - The binary operator version is consistently smaller thant the switch version, which was expected, because the bit wise operation is far more simpler than multiple cases in a switch branch (in this case I only used 1 case and default).
> - The DATA zone excludes memory mapped hardware registers, since that address space is reserverd by the SFR itself, not allocated because of this function.

---

#### Task 654
> **Question/Prompt:** Optimize your code in order to occupy less ROM memory. Keep a record or screenshots "before" and "after".

> **Answer/Explanation:**
> 

---

#### Task 655
> **Question/Prompt:** Do you think code size is the only measure of code performance? Can you give examples of other measures of code performance? (<<< answer here)

> **Answer/Explanation:**
> 

---

#### Task 656
> **Question/Prompt:** To modify one or several bits in a register without affecting the others, so just the ones you need, you now have/know two methods: bitfields (see the expansion talk week 1) and bitmasks. But which one is better to use in terms of code size and execution cycles? Compare code performance when applying the two methods, in terms of code size and execution cycles, for the use cases of modifying 1, 2, 3..., 8 bits at once. You should use the assembler code in Disassembly window, and for each instruction you can check the Instruction Set Summary in the microcontroller's datasheet for the amount of cycles/clocks it takes. Table your data observed and draw conclusions.

> **Answer/Explanation:**
> 

---