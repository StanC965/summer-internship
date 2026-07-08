# Week: 1 - Goal : 1


## Objective 6: Refresh your microcontroller know-how

### Task Checklist & Results

| Task ID | Type | Status / Deliverable
| :--- | :--- | :--- |
| **[161]** | `CORE` | [x] Completed
| **[162]** | `CORE` | [x] Completed
| **[163]** | `CORE` | [x] Completed
| **[164]** | `CORE` | [x] Completed
| **[165]** | `CORE` | [x] Completed


#### Task 161
> **Question/Prompt:** Usually a microcontroller (MCU) comes with a datasheet explaining how it works and different other specifications which engineers are looking for understanding them. Go to ATmega324PB datasheet and familiarize yourself with the block diagram showing the internal components as blocks, with external pinout and finally with the CPU core. Try to identify what is interesting for you or makes you curious about.

> **Answer/Explanation:**

---

#### Task 162
> **Question/Prompt:** Check the endian architecture of ATMega324PB microcontroller (is it little endian or big endian?). Re-write the first program code (the one with the sum) and assign to variable b the value 257, then compile again, download and run your program and you should see the sum to be 258 or 0x0102 in hexadecimal. Now open a Watch window and a Memory window and compare the content from variable c address. Is it the same?

> **Answer/Explanation:**
> The sum of a and b is 258 or 0x0102. In the watch window, the result is shown as 0102, but in memory it's stored as 02 01. That means that ATMega324PB is a little endian architecture.

---

#### Task 163
> **Question/Prompt:** Open the datasheet of the ATMega324PB microcontroller and find the register TCCR2B, a real register!!! Compare the information found in the datasheet with the macro of the register TCCR2B. What is your conclusion?

> **Answer/Explanation:**
> The Timer/Counter Control Register B (TCCR2B) consists of 8 bits:

![alt text](../../../../images/w1g1obj6t163.PNG)

> The macro has the following structure:  SFR_B_N(0xB1, TCCR2B, FOC2A, FOC2B, Dummy5, Dummy4, WGM22, CS22, CS21, CS20)

> Based on the structure of the register and the macro the conclusion is that the macro directly maps the software definition to the exact physical structure of the hardware register.

---

#### Task 164
> **Question/Prompt:**  By analogy with the expansion example above, write in the main.c file as comments (!) how you understood the following macro registers will be expanded:

```
SFR_B_N(0x08,PORTC,PORTC7,PORTC6,PORTC5,PORTC4,PORTC3,PORTC2,PORTC1,PORTC0)
SFR_B_N(0x07, DDRC, DDRC7, DDRC6, DDRC5, DDRC4, DDRC3, DDRC2, DDRC1, DDRC0)
SFR_B_N(0x06, PINC, PINC7, PINC6, PINC5, PINC4, PINC3, PINC2, PINC1, PINC0)
```

> **Answer/Explanation:**
> 

---

#### Task 165
> **Question/Prompt:**  Include the header file iom324pb.h in your main.c file. Compile. Check with preprocessed files (main.i) how the macros or #defines are expanded. Is this confirming your knowledge acquired so far? How the comments are preprocessed?

> **Answer/Explanation:**
> After I included the header file and compiled the source code, the macros expanded just as expected after doing the previous task. 
> The comments were stripped from the file by the preprocessor, since there was no option chosen to keep them.

## References & Resources
* AVR Microcontroller with Core Independent Peripherals and PicoPower technology