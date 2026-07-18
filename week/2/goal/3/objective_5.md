# Week: 2 - Goal : 3


## Objective 5: Mastering the ADC

---

### Task Checklist & Results

| Task ID   | Type      | Status 
| :---      | :---      | :---                    
| **[351]** | `CORE`    | [x] Completed 
| **[352]** | `CORE`    | [x] Completed 
| **[353]** | `CORE`    | [x] Completed 

--- 

#### Task 351
> **Question/Prompt:** Now you have a minimum experience with microcontroller's datasheet reading. Next big task is to understand how ADC is working and how to make the correct register settings. Every time you need to work with a peripheral module remember:

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
>
> h. read the registers description third time looking to take THE EASIEST decisions over the settings of each bit** (!!!) even if that means not to modify their default (after reset) value at all (this is a valid decision also, right? :); this is the point where you should go also to chapters describing the functionalities (e.g. start a convertion, etc.) to get more clarifications.

> **Answer/Explanation:**
> ### block diagram:
> - the analog signal enters the chip viar port A (pins PA[7:0]) which serve as the 8 ADC input channels
> -  the ADC has a dedicated clock domain, which allows the CPU and digital I/O clocks to be halted to minimize digital switching noise and maximize precision
> - the ADC possesses a dedicated interrupt request line 
> ### peripheral overview:
> - the board featues a 10 bit successive approximation ADC
> - it supports 8 independent single ended channels mapped to port A, along with differential input stages
> - the raw analog voltage value is converted into a digital number between 0 and 1023 (2^10 - 1)
> - it requires an analog supply voltage pin AVCCC which must be connected to VCC
> ### peripheral's registers:
> the core registers:
> - ADMUX 
> - ADCSRA (control and status register A) 
> - ADCSRB (control and status register B)
> - ADCL and ADCH (the data register holding the 10-bit result)
> - DIDR0 (digital input disable register 0)
> ### objective:
> to read a light sensor (which outputs a variable analog voltage based on ambient light intensity):
> - select pin PA4
> - trigger a conversion, wait for completion, extract the 10 bit value from the ADC data registers
> ### enabling, processing functionality, and results:
> - enabling: the ADC is turned on by writing a logic one to the ADEN in the ADCSRA
> - converting: write a logic one to the ADCSC in ADCSRA
> - results: polling (monitor ADSC) or via interrupts (set ADIE in ADCSRA, enable global interrupts and use the ADC_vect routine)
> - thre result spans on 2 bit registers ADCL and ADCH
> ### easiest decisions:
> - set REFS[1:0] in ADMUX to 01 to use AVCC as reference voltage. This maps the input range directly to the board's operating voltage
> - leave MUX[4:0] in ADMUX at default reset values
> - leave the ADLAR bit in ADMUX at 0 for standard right adjusted reading
> - clock prescaler (see more about this)
> - write 1 in DIDR. This shuts down the digital input buffer on the PA4 pin, preventing floating analog voltages from consuming unnecessary leakage current

--- 

#### Task 352
> **Question/Prompt:** After reading the ADC datasheet information (registers & functionalities) you should have these questions.

> **Answer/Explanation:**
> 

--- 

#### Task 353
> **Question/Prompt:** Introduce the interrupt service routine for ADC. Inside you need to read the ADCH to get the result of conversion. What kind of data type you will use for this? (<<< your decision). Put a breakpoint to ISR and your program should hit it! Wonderful!

> **Answer/Explanation:**
> I used a volatile uint8_t to store ADCH.

---

## References & Resources
* I/O1 Xplained Pro user guide