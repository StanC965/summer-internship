# Week: 2 - Goal : 4


## Objective 3: CTC MODE of operation for TC0

---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[431]** | `CORE`     | [x] Completed
| **[432]** | `CORE`     | [x] Completed
| **[433]** | `CORE`     | [x] Completed
| **[434]** | `CORE`     | [x] Completed
| **[435]** | `STRETCH`  | [] Completed
| **[436]** | `CORE`     | [x] Completed

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

---

#### Task 433
> **Question/Prompt:** Build code to output a waveform (you are free to choose on which pin) with a period of 100ms. Is this observable with the human eye? 

> **Answer/Explanation:**
> I picked OC1A, which is connected to PD5 (LED_1) on the OLED1 board.
>
> For a full period of 100ms, each half period (one toggle) needs to be 50ms.
> With prescaler = 8, we get 6249 ticks needed.
>
> The flicker is observable with the human eye.

---

#### Task 434
> **Question/Prompt:** Do the math calculations for minimum and maximum of real time you can natively measure with CTC MODE, all prescalers considered. It is a combination of:
>
> - HOW FAST timer can count: system clock frequency (1MHz) with prescaler (1, 8, ..., 1024) results in the counting frequency
> - HOW MUCH timer can count: TC0 minimum (0x00) and maximum value for overflow (0xFF)
> - MIN => _ MAX => _
> 
> How can you extend the maximum real time measured in CTC MODE? 

> **Answer/Explanation:**
> - t = (OCR0A + 1) × prescaler / F_CPU
>   - F_CPU = 1 MHz
>   - prescalers available: 1, 8, 64, 256, 1024
>   - OCR0A range: 0x00 (0) to 0xFF (255)
>
> smallest prescaler (1) × smallest count (OCR0A = 0 → 1 tick):
> - t_min = 1 × 1 / 1,000,000 = 1 µs
> - MIN => 1 µs (0.001 ms)
>
> largest prescaler (1024) × largest count (OCR0A = 255 → 256 ticks):
> - t_max = 256 × 1024 / 1,000,000 = 262,144 µs
> - MAX => 262.144 ms
> 
> since Timer0 is only 8 bit (max 256 ticks) and 1024 is the largest prescaler, the hardware alone tops out at 262.144 ms. To measure longer intervals:
>   - We can count multiple compare matches in software (increment a counter in the ISR, act after N matches).
>   - Use a 16-bit timer instead. Same formula but OCR range goes up to 0xFFFF (65536 ticks), giving 65536 × 1024 / 1,000,000 ≈ 67.1 s natively, no software counting needed.

---

#### Task 435
> **Question/Prompt:** Considering that at min, max above (exercise 434) you toggle an LED, what min, max frequency will that signal have? FREQ MIN => _ FREQ MAX => _

> **Answer/Explanation:**
>

---

#### Task 436
> **Question/Prompt:** Take the basetime of 100ms you developed on the previous exercise. Without changing the prescaler and OCR0A settings, develop a 400ms periodic signal, with 50% of the period on HIGH (1 logic) and 50% of the period on LOW (0 logic). Apply it to an LED.

> **Answer/Explanation:**
> Timer 1 already ticks every 50ms (that's what makes the OC1A blink at 100 ms).
> Because we cannot change that timing, we count the tick in the ISR, every 4th tick (200 ms), the pin is toggled. 
> Toggling on a fixed count keeps HIGH and LOW time equal, which results in 400ms period at 50% duty.

---






