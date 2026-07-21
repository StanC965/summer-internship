# Week: 3 - Goal : 6


## Objective 5: Measuring the code size

---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[651]** | `CORE`     | [x] Completed
| **[652]** | `CORE`     | [x] Completed

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