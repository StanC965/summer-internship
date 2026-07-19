# Week: 2 - Goal : 4


## Objective 3: CTC MODE of operation for TC0

---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[431]** | `CORE`     | [x] Completed
| **[432]** | `CORE`     | [x] Completed

---

#### Task 431
> **Question/Prompt:** On short: CTC MODE is an enhancement of NORMAL MODE which gives you the possibility to have an interrupt request before overflow happens. The interrupt request is generated when TCNT0 register value matches OCR0A register value. Additionally, the pin labeled OC0A can be used to toggle its level when matching occurs. Re-make the process described at NORMAL MODE for setting the registers for TC0 to work on CTC MODE obtaining an interrupt at OCR0A = 127.

> **Answer/Explanation:**
> 

---

#### Task 432
> **Question/Prompt:** What pin is OC0A? Which LED is connected to it? Using the Waveform Generator toggle the OC0A pin on match with OCR0A=127. Within the same program, but from inside ISR code, toggle another pin which has LED connected. What do you observe with respect to the two LEDs blinking behavior?  If they are out-of-synch, make them to be turned on/off synchronously (both on, both off). How much real time (use ms/miliseconds) can be measured with OCR0A = 127? What other real timings you can measure having the same OCR0A = 127?

> **Answer/Explanation:**
> - OC0A is pin PB3, and LED IO1 is connected to it. 
>
> - Both LEDs toggle at the same frequency, but they run out of sync. OC0A is toggled instantly by the timer hardware at the moment the match occurs, while the onboard LED is toggled by software inside the ISR, which only executes after interupt latency.
>
> - With F_CPU = 1MHz and no prescaler -> 0.256 ms full period.
> - By switching the hardware prescalers, you can measure:
>   - Prescaler 8: 2.048 ms
>   - Prescaler 64: 16.384 ms
>   - Prescaler 256: 65.536 ms
>   - Prescaler 1024: 262.144 ms





