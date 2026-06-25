# Week 2 · Part 2

> **GOAL: Tack your app with TIMERS**

By the end of this week you should be able to control the TC0 peripheral to measure time.

On short what you will do this week:

- get to setup and control TC0
- measure timings and output pin signals accordingly

---

## Objective 1: Getting to know TC0 timer

- **411** — Go at the top menu bar: `Atmel-ICE -> Fuse Handler -> Low Fuse` -> check the box: *Divide clock by 8 internally*, check the box: *Clock output on PORTB1*. Select from the drop-down list the Internal RC oscillator 8MHz as shown (the New Value for Low Fuse is `0x22`) -> Program Fuses -> Close.

    What you have set here is the source for system clock signal. The heartbeat of the system. Internal RC oscillator @ 8MHz frequency, but divided by 8, so resulting in 1MHz system clock frequency which will be distributed to all peripherals including CPU. Lowering the system clock frequency is a great way to reduce power consumption in embedded systems. TC0 is an 8bit timer/counter which also receives clock signal from this source. This TC0 we will study further.

- **412** — TC0 is on chapter 17 in datasheet. REMEMBER — every time you need to work with a peripheral module:

    1. you will encounter a lot of information noise, so prepare your mind to filter
    2. you will not understand all the information at once, therefore be patient reading 2x, 3x times
    3. start with the block diagram; it shows in a simplified manner the overall dynamics of that peripheral; follow the signals from outside of the capsule via pins to the inside (and/or viceversa) and further to databus along sketched lines; look also for what clock source has and if interrupt request lines are present there to send interrupt signals to CPU
    4. read the overview (with observation 1&2&3 in mind :)
    5. check how many registers that peripheral has (to limit your anxiety over the problem)
    6. hover the registers description once scanning with your eyes about how can you implement the objective you have in mind (e.g. for ADC you will want to obtain a digital converted value and use it further, for TIMERS you will want to obtain periodic interrupts, etc.)
    7. read the registers description second time looking for how to enable the peripheral, how are you making use of its functionality and its final result\*, how you will work with interrupt requests (if you decide to work with interrupts)
    8. read the registers description third time looking to take THE EASIEST decisions over the settings of each bit\*\* (!!!) even if that means not to modify their default (after reset) value at all (this is a valid decision also, right? :); this is the point where you should go also to chapters describing the functionalities (e.g. normal mode, etc.) to get more clarifications.

    !!! note "Note"
        In TC0 case the final result will depend on the Operating Mode you choose (in Normal mode final result is interrupt request to CPU at overflow, in CTC mode the final result will be an interrupt request to CPU when matching occurs, in PWM mode the final result will be a digital signal output to physical microcontroller's pin). The following exercises will guide you through.

??? info "Additional materials — FOR YOUR INFO"
    - [Introduction to AVR Timers » maxEmbedded](https://maxembedded.com/2011/06/introduction-to-avr-timers/)
    - [AVR Timer programming - Tutorials (exploreembedded.com)](https://exploreembedded.com/wiki/AVR_Timer_programming)
    - [AVR130: Setup and Use of AVR Timers (microchip.com)](https://ww1.microchip.com/downloads/en/Appnotes/Atmel-2505-Setup-and-Use-of-AVR-Timers_ApplicationNote_AVR130.pdf)

---

## Objective 2: Start simple — NORMAL MODE of operation for TC0

- **421** — Your big task now is to make TC0 work in NORMAL MODE (from `0x00` to `0xFF`) obtaining an interrupt at overflow. After reading the TC0 datasheet information (registers & functionalities) you should have these questions.

    !!! note "Good start decisions"
        | Register | Questions | Good start decisions |
        | -------- | --------- | -------------------- |
        | TCCR0A | Should I use Compare Mode for channel A or B? | None. Remember we are in NORMAL MODE not in any of the Compare Modes. |
        | TCCR0A | What values WGM0[1:0] bits should have? | These 2 bits + WGM02 single bit in TCCR0B will determine the NORMAL MODE of operation |
        | TCCR0B | Should I force an output signal to pin OC0A? | No. NORMAL MODE cannot output signals on pin. |
        | TCCR0B | What prescaler should I use? | Start with NO PRESCALING (1MHz from system clock). Feeding in a prescaler will start the timer. Therefore this is the last thing you do after all settings are done. You can make your own Excel calculator to determine the time measured based on system clock frequency, prescaler and timer resolution (8bits) |
        | TIMSK0 | What interrupt should I enable? | Overflow Interrupt Enable (overflow is the only trigger point for interrupts in NORMAL MODE) |
        | GTCCR | Should I use synchro mode and prescalers there? | No. Remember we are using NORMAL MODE. |
        | TCNT0 | Should I write/read any counter value? | No. In NORMAL MODE we are using the interrupt request raised at overflow, not counter value. |
        | OCR0A | Should I use output compare A? | No. We are in NORMAL MODE, not any compare mode. |
        | OCR0B | Should I use output compare B? | No. We are in NORMAL MODE, not any compare mode. |
        | TIFR0 | Should I process these Interrupt Flags? | No. We are relying on interrupt request served by the CPU and NOT relying on polling the Interrupt Flag to check when overflow occurs. |

- **422** — Introduce the corresponding interrupt service routine, breakpoint and hit!!!
- **423** — Do the math calculations for minimum and maximum of real time you can natively measure with NORMAL MODE until overflow, all prescalers considered. It is a combination of:
    - HOW FAST timer can count: system clock frequency (1MHz) with prescaler (1, 8, ..., 1024) results in the counting frequency
    - HOW MUCH timer can count: TC0 maximum value for overflow (`0xFF`)

    MIN => ____  MAX => ____

    How can you extend the maximum real time measured in NORMAL MODE? *(<<< your answer here)*

- **424** — **OPTIONAL** — What can you say about the jitter (deviation in time) introduced when extending the maximum real time measured in NORMAL MODE? *(<<< your answer here)*
- **425** — Time your LED0 on and off at 1 second interval (exercise 216 revisited! but this time without software delays!) managed by TC0 Timer working in NORMAL MODE of operation with the help of interrupt service routine.
- **426** — What min, max frequency would have the signal on LED0 toggled from within ISR in case of min, max prescalers? FREQ MIN => ____  FREQ MAX => ____
- **427** — Use button SW0 to cycle through the possible frequencies (5 prescalers = 5 different frequencies). Use LED0 for your demonstration.
- **428** — Build a 5 seconds countdown timer using the 5 LEDs you have on all the boards: the countdown shall start when SW0 is pressed. The initial system state is that all LEDs are on, then for each substracted second one LED goes off.
- **429** — Re-design your BMW Control Panel Application with the introduction of timer feature. You can e.g. introduce a timer managed delay or a reading of the button from ISR.

---

## Objective 3: CTC MODE of operation for TC0

- **431** — On short: CTC MODE is an enhancement of NORMAL MODE which gives you the possibility to have an interrupt request before overflow happens. The interrupt request is generated when TCNT0 register value matches OCR0A register value. Additionally, the pin labeled OC0A can be used to toggle its level when matching occurs. Re-make the process described at NORMAL MODE for setting the registers for TC0 to work on CTC MODE obtaining an interrupt at OCR0A = 127.
- **432** — What pin is OC0A? *(<<< your answer here)*. Which LED is connected to it? *(<<< your answer here)*. Using the Waveform Generator toggle the OC0A pin on match with OCR0A=127. Within the same program, but from inside ISR code, toggle another pin which has LED connected. What do you observe with respect to the two LEDs blinking behavior? *(<<< your answer here)*. If they are out-of-synch, make them to be turned on/off synchronously (both on, both off). How much real time (use ms/miliseconds) can be measured with OCR0A = 127? *(<<< your answer here)*. What other real timings you can measure having the same OCR0A = 127? *(<<< your answer here)*
- **433** — Build code to output a waveform (you are free to choose on which pin) with a period of 100ms. Is this observable with the human eye? *(<<< your observation here)*
- **434** — Do the math calculations for minimum and maximum of real time you can natively measure with CTC MODE, all prescalers considered. It is a combination of:
    - HOW FAST timer can count: system clock frequency (1MHz) with prescaler (1, 8, ..., 1024) results in the counting frequency
    - HOW MUCH timer can count: TC0 minimum (`0x00`) and maximum value for overflow (`0xFF`)

    MIN => ____  MAX => ____

    How can you extend the maximum real time measured in CTC MODE? *(<<< your answer here)*

- **435** — Considering that at min, max above (exercise 434) you toggle an LED, what min, max frequency will that signal have? FREQ MIN => ____  FREQ MAX => ____
- **436** — Take the basetime of 100ms you developed on the previous exercise. Without changing the prescaler and OCR0A settings, develop a 400ms periodic signal, with 50% of the period on HIGH (1 logic) and 50% of the period on LOW (0 logic). Apply it to an LED.
- **437** — Take the basetime of 100ms you developed on the previous exercise. Without changing the prescaler and OCR0A settings, develop a 1000ms periodic signal, with 70% of the period on HIGH (1 logic) and 30% of the period on LOW (0 logic). Apply it to an LED.
- **438** — Take the basetime of 100ms you developed on the previous exercise. Without changing the prescaler and OCR0A settings, develop a 1200ms periodic signal, with the first 200ms on HIGH (1 logic), then 300ms on LOW (0 logic), then 500ms on HIGH again, and finally 200ms on LOW again. Apply it to an LED.
- **439** — **OPTIONAL** — For each signal above (exercise 436, 437, 438) change the code implementation by updating the value TOP from the ISR code. Which type of implementation is better?

??? info "Additional materials — FOR YOUR INFO"
    - [Learning AVR-C Episode 6: Timers - YouTube](https://www.youtube.com/watch?v=cAui6116XKc)

---

## Objective 4: Integration challenge

- **441** — You are a member of the software development team for application Car Crash Management. The requirement (1) for today is to integrate in your program the module called `CarCrashDetection` (You can find it in the folder Reference Documents). This module was developed by our colleagues in [Pune, India](https://www.google.ro/maps/place/MARQUARDT+INDIA+PVT.+LTD./@18.587949,73.674906,482m), where Marquardt has a subsidiary. The module offers an interface `unsigned char GetCarCrashDetectionStatus(void)` which returns 1 in case of detection of a frontal impact with another car and returns 0 in all other cases. The requirement (2) for today is that after the correct integration of module `CarCrashDetection`, you should command the explosion of the airbag caps for the driver and the passenger. The time window to do this is [ 650µs – 800µs ]. So, no later than 800µs, but also no earlier than 650µs!!! Measurements are started from the moment when your program is notified that has been detected a frontal accident with another car. (For our safety, the airbag caps explosion will be simulated by lighting up an LED :))

    !!! note "Note"
        The measurements should be done with a Logic Analyzer you have. In 101 meetings we will look over the signals.

---

## Objective 5: Advancing TC1

- **451** — [Level Up Your Arduino Code: Timer Interrupts - YouTube](https://www.youtube.com/watch?v=2kr5A350H7E)
- **452** — **OPTIONAL** — On timer TC1, 16 bits counter, implement and document the minimum and the maximum real time you can obtain using this timer. The same for minimum and maximum signal frequencies when applied to a toggling LED. What is the advantage of using a timer on 16 bits instead of a timer on 8 bits?
- **453** — **OPTIONAL** — Turn on LEDs on the OLED1 with the help of TC1 as follows:

    | Press duration of SW0 button | LED on |
    | ---------------------------- | ------ |
    | < 1 second | LED1 |
    | 1 second < 5 seconds | LED2 |
    | > 5 seconds | LED3 |

- **454** — **OPTIONAL** — With the Unit of Input Capture count how many times the external button is pushed. On the 4th push light up LED1, on the 5th push light up LED2, on the 6th push light up LED3.
