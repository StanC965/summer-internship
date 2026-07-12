# Week: 1 - Goal : 1


## Objective 4: Build a new project with IAR Embedded Workbench IDE

### Task Checklist & Results

| Task ID   | Type      | Status / Deliverable 
| :---      | :---      | :--- 
| **[141]** | `CORE`    | [x] Completed 
| **[142]** | `CORE`    | [x] Completed 
| **[143]** | `CORE`    | [x] Completed 
| **[144]** | `STRETCH` | [x] Completed 
| **[145]** | `STRETCH` | [x] Completed 
| **[146]** | `CORE`    | [x] Completed 

---

#### Task [141]
> **Question/Prompt:**    Install IAR Embedded Workbench on your computer (see Guide on how to do this).

> **Answer/Explanation:**
---

#### Task [142]
> **Question/Prompt:**     First steps to follow when creating a new project in IAR EW are described in the same Guide.

> **Answer/Explanation:**

---

#### Task [143]
> **Question/Prompt:**    Write the following code in main.c file. It will be programmed (flashed/downloaded) on the ATmega 324PB microcontroller by selecting Download and Debug. Once you do this you are in DEBUGGING mode. To exit DEBUGGING mode you select the icon Stop debugging.

> **Answer/Explanation:**
> I added the following code snippet:

```c
int main( void )
{
  int a = 5; 
  int b = 10;
  int sum = 0;
  
  sum = a + b;
  
  while(1){
    
  }
}
```

---

#### Task [144]
> **Question/Prompt:**     Try out the functionality of all buttons used for debugging (the blue buttons) to get familiar with their effects, e.g. RESET, RUN UNTIL CURSOR, STEP OVER, etc.

> **Answer/Explanation:**

---

#### Task [145]
> **Question/Prompt:**     Try out the windows in IDE: observe in Watch window the variables (right-click to change the format in decimal or hexa), check the Memory window for placement of those variables in memory (at what address they are?), observe in the Registers window the changing PC (Program Counter) and SP (Stack Pointer) as you go through the program step wise.

> **Answer/Explanation:**

---

#### Task [146]
> **Question/Prompt:**      Now that you are finishing Objective 4, you must upload your project files to github.com as instructed on your personal branch.

> **Answer/Explanation:**


