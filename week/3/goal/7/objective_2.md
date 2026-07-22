# Week: 3 - Goal : 7


## Objective 2: Setting up the USART

---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[721]** | `CORE`     | [x] Completed
| **[722]** | `CORE`     | [x] Completed
| **[723]** | `CORE`     | [x] Completed
| **[724]** | `CORE`     | [x] Completed

---

#### Task 721
> **Question/Prompt:** First, observe that for our microcontroller the naming is not UART (as general accepted) but USART. The letter S comes from a feature enhancement of this peripheral: the engineers have decided to add a clock line, transforming the asynchronous UART into a synchronous one. The synchronous communication is not an UART anymore but an SPI (Serial Peripheral Interface) using the same hardware with UART. You can look at this enhancement as two mutual exclusive modes of operations of the same USART hardware module. We will not use the synchronous mode, therefore we will implement an asynchronous UART communication using the USART peripheral. For the sake of consistency we will keep the datasheet naming only for the peripheral references and the register names, but use UART name every time we refer to the communication protocol.

> **Answer/Explanation:**
> 

---

#### Task 722
> **Question/Prompt:** To implement a simple UART communication we will use the IO1 board. Observe that on the IO1 board there is a black jumper which connects the TX and RX of the same USART peripheral (e.g. USART0). This connection is called loopback. We will use those TX, RX connected together to simulate the communication between two different microcontrollers. Imagine that TX is from MCU1 sending messages and RX is from MCU2 receiving the messages. This is a simplex communication (one way communication, as MCU2 will not be able to respond back to MCU1, because RX pin cannot transmit, it only receives, but that's ok for our purpose here).

> **Answer/Explanation:**
> 

---

#### Task 723
> **Question/Prompt:** Identify (using schematics and User Guides) the exact peripheral name which has the TX, RX exposed on IO1. Is it USART0, USART1 or USART2?

> **Answer/Explanation:**
> IO1 is connected thorugh the EXT4 header, so it's USART2.

---

#### Task 724
> **Question/Prompt:** Use the same approach as you had for ADC and TIMER peripherals to study the datasheet chapter for USART peripheral. Observe there is a chapter also dedicated to the USART in SPI mode which we will NOT use. Therefore ask yourself how many registers there are, what settings to choose (keep it simple!), how does UART communication works (keep it simple in using the features). Today you have become a mature engineer and you can take accountable decisions for yourself. Congrats!

> **Answer/Explanation:**
> 

---
