# Week: 2 - Goal : 4


## Objective 1: Getting to know TC0 timer

---

### Task Checklist & Results

| Task ID   | Type   | Status
| :---      | :---   | :--- |
| **[411]** | `CORE` | [x] Completed
| **[412]** | `CORE` | [x] Completed

---

#### Task 411
> **Question/Prompt:** Go at the top menu bar: Atmel-ICE -> Fuse Handler -> Low Fuse -> check the box: Divide clock by 8 internally, check the box: Clock output on PORTB1. Select from the drop-down list the Internal RC oscillator 8MHz as shown (the New Value for Low Fuse is 0x22) -> Program Fuses -> Close.
> 
> What you have set here is the source for system clock signal. The heartbeat of the system. Internal RC oscillator @ 8MHz frequency, but divided by 8, so resulting in 1MHz system clock frequency which will be distributed to all peripherals including CPU. Lowering the system clock frequency is a great way to reduce power consumption in embedded systems. TC0 is an 8bit timer/counter which also receives clock signal from this source. This TC0 we will study further.

> **Answer/Explanation:**
> 

---

#### Task 412
> **Question/Prompt:** TC0 is on chapter 17 in datasheet. REMEMBER — every time you need to work with a peripheral module:

> a. you will encounter a lot of information noise, so prepare your mind to filter
> 
> b. you will not understand all the information at once, therefore be patient reading 2x, 3x times
>
> c. start with the block diagram; it shows in a simplified manner the overall dynamics of that peripheral; follow the signals from outside of the capsule via pins to the inside (and/or viceversa) and further to databus along sketched lines; look also for what clock source has and if interrupt request lines are present there to send interrupt signals to CPU
>
> d. read the overview (with observation 1&2&3 in mind :)
> 
> e. check how many registers that peripheral has (to limit your anxiety over the problem)
>
> f. hover the registers description once scanning with your eyes about how can you implement the objective you have in mind (e.g. for ADC you will want to obtain a digital converted value and use it further, for TIMERS you will want to obtain periodic interrupts, etc.)
>
> g. read the registers description second time looking for how to enable the peripheral, how are you making use of its functionality and its final result*, how you will work with interrupt requests (if you decide to work with interrupts)

> h. read the registers description third time looking to take THE EASIEST decisions over the settings of each bit** (!!!) even if that means not to modify their default (after reset) value at all (this is a valid decision also, right? :); this is the point where you should go also to chapters describing the functionalities (e.g. normal mode, etc.) to get more clarifications.

> **Answer/Explanation:**
> ### block diagram
> - Timer/Count0 (TC0) is an 8 bit peripheral designed around a programmable bi directional counter unit (TCNT0) that continously compares its value against two independent output compare registers (OCR0A and OCR0B)
>   - inputs: external clock signals can pass from the outside environmnet into the peripheral via the dedicated T0 pin in the internal edge detector and clock select logic block
>   - outputs: internal waveform generation modules can drive signals out to physical microcontroller pins via the output compare lines OC0A and OC0B
> - The peripheral can be driven by either the internal system clock via a configurable prescaler divider block, or by an external clock source applied to the T0 pin. The resulting active timing line is designated as clk_T0.
> - There are three independent interrupt request lines linked directly to the CPU:
>   - TOV0 (Timer/Counter0 Overflow Interrupt)
>   - OCF0A (Output Compare A Match Interrupt)
>   - OCF0B (Output Compare B Match Interrupt)
>
> ### peripheral register count
> - Timer/Counter0 contains exactly 8 distinct configuration and data registers described in the module documentation:
>   - TCCR0A (TC0 Control Register A)
>   - TCCR0B (TC0 Control Register B)
>   - TIMSK0 (TC0 Interrupt Mask Register)[cite: 1]
>   - GTCCR  (General Timer/Counter Control Register - shared prescaler sync)
>   - TCNT0  (TC0 Counter Value Register)
>   - OCR0A  (TC0 Output Compare Register A)
>   - OCR0B  (TC0 Output Compare Register B)
>   - TIFR0  (TC0 Interrupt Flag Register) 
>
> ### objective
> - To achieve the objective of generating periodic interrupts, two basic operational configurations are visible during the initial scan:
>   - Normal Mode: The counter increments continuously up to 0xFF (MAX), rolls over to 0x00, and natively triggers a periodic Timer Overflow flag (TOV0) on every single rollover cycle.
>   - CTC Mode: The counter increments up to a custom value defined in OCR0A (TOP), automatically clears itself back to zero, and flags a periodic Compare Match interrupt (OCF0A). This provides exact control over the interrupt period.
>
> ### enabling, functionality, and interrupt configurations
> - To route a clock to TC0 and activate it, you must first clear the Power Reduction Timer0 bit (PRTIM0) by writing a logic 0 into the Power Reduction Register 0 (PRR0).
> - The real-time running value can be extracted directly at any time by reading the 8-bit TCNT0 register.
> - Individual local flags are enabled by writing a logic 1 to their respective enable bits (TOIE0, OCIE0A, or OCIE0B) inside the TIMSK0 register. This must be combined with the execution of the global interrupt enable function (__enable_interrupt()) which toggles the I-bit in the status register (SREG).
>
> ### 
> - Following the guide's rule to make the simplest architectural choices—leaving as many bits at their default 0x00 power-on reset values as possible—here is the ultimate baseline configuration for generic periodic interrupts using Normal Mode.

---

## References & Resources
* AVR Microcontroller with Core Independent Peripherals and PicoPower technology (ATmega324PB)
