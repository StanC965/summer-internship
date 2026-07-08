# Week: 1 - Goal : 1


## Objective 6: Refresh your microcontroller know-how

### Task Checklist & Results

| Task ID | Type | Status / Deliverable
| :--- | :--- | :--- |
| **[161]** | `CORE` | [x] Completed
| **[162]** | `CORE` | [x] Completed



#### Task 161
> **Question/Prompt:** Usually a microcontroller (MCU) comes with a datasheet explaining how it works and different other specifications which engineers are looking for understanding them. Go to ATmega324PB datasheet and familiarize yourself with the block diagram showing the internal components as blocks, with external pinout and finally with the CPU core. Try to identify what is interesting for you or makes you curious about.

> **Answer/Explanation:**

---

#### Task 162
> **Question/Prompt:** Check the endian architecture of ATMega324PB microcontroller (is it little endian or big endian?). Re-write the first program code (the one with the sum) and assign to variable b the value 257, then compile again, download and run your program and you should see the sum to be 258 or 0x0102 in hexadecimal. Now open a Watch window and a Memory window and compare the content from variable c address. Is it the same?

> **Answer/Explanation:**
> The sum of a and b is 258 or 0x0102. In the watch window, the result is shown as 0102, but in memory it's stored as 02 01. That means that ATMega324PB is a little endian architecture.