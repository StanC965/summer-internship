# Week 2 · Goal 3

> **GOAL: Interrupts and Analog-to-Digital conversions**

By the end of this week you should be able to handle the interrupts and an AD conversion.

Personal programming style/performance should be acknowledged and improved further (coding rules and naming conventions).

On short what you will do this week:

- get to control buttons by interrupts
- redesign your code respecting some basic naming conventions/rules
- build a main application: CONTROL PANEL
- control the ADC and light sensor

---

## Objective 1: "Hello" interrupts!

- **311** — **CORE** —  With this objective we introduce the interrupts, THE big idea in embedded systems :) A microcontroller can implement many sources/triggers of interrupts for its processor (CPU). One simple interrupt can be the one triggered by the push of an external button. So you push the button and a signal is sent through the registers way up until it reaches the CPU. That signal is the interrupt request. Keep in mind this short idea:

    > button pressed > pin voltage level changed > interrupt request to CPU

    when studying from the microcontroller's datasheet the interrupts for your personal understanding. Be aware you will encounter a lot of information noise, but you have to filter it out... so keep focus on what you have to find to program the interrupts triggered by your button press.

    Study:

    - [ ] chapter 8.1 on how interrupts are implemented
    - [ ] chapter 8.3.1 on the Global Interrupt Enable bit effect
    - [ ] chapter 8.5 on the link between Stack Pointer and interrupts
    - [ ] chapter 8.8 and down the page chapter 8.8.1 on the behavior of interrupts
    - [ ] chapter 14.1 on the Interrupt Vector Table (just the table!!!)
    - [ ] chapter 15 on the external interrupts mechanism and registers description
    - [ ] chapter 6 table for pin identification

- **312** — **CORE** —  Identify and double check within `iom324pb.h` that the interrupt vector table is implemented correctly. Go to Compiler Guide (from IAR Embedded Workbench HELP) and read for:

    - [ ] INTERRUPT FUNCTIONS (pag.64)
    - [ ] RESTRICTIONS FOR SPECIAL FUNCTION TYPES => Interrupt functions (pag.163)
    - [ ] `__interrupt` keyword (pag. 307)

- **313** — **CORE** —  As your understanding over interrupts grows it is time to introduce the routine executed by the CPU when it will be interrupted by the external request. So remember the sequence:

    > button pressed > pin voltage level changed > interrupt request to CPU > jump to vector > executes routine written by you

    Our IAR compiler (like any other compiler) uses a special construct to mark the function written by you in C language as being the routine executed by the CPU in case of interrupt request. Remember that saying it is a FUNCTION is improper/wrong, the correct saying is INTERRUPT SERVICE ROUTINE, on short ISR. It is a routine and not a function for some simple reasons: it does not have input parameters, does not return anything and it is not called (!!!) like a normal function is called within the program. The amount of code you write inside ISR should be kept small. Below is an example of what you should write (between `#pragma` and the ISR name you MUST NOT introduce any other line of code!!! as the compiler after the `#pragma` is strictly expecting to encounter the routine name!):

    ```c
    #pragma vector=INT2_vect
    __interrupt void my_routine(void)
    /* the amazing routine for serving the interrupt caused by my button press */
    {
        /* some code here… e.g. you can turn ON the LED0 here  */
    }
    ```

- **314** — **CORE** —  Establish what kind of settings you should do for the registers supporting external interrupts, knowing the connection between SW0 and microcontroller's pin. Adapt also the interrupt vector name (above it was just an example).
- **315** — **CORE** —  One small step before running the program is to put a breakpoint somewhere in the code of your ISR. Run the program, press the SW0 button and your CPU should hit the breakpoint. Congrats!
- **316** — **STRETCH** —  Revisit the exercise with SOS message behavior and refactor it now with the help of external interrupts.

??? info "Additional materials — FOR YOUR INFO"
    - [External Interrupts - SPARK FUN on YouTube](https://www.youtube.com/watch?v=J61_PKyWjxU)
    - [Learning AVR-C Episode 9: External Interrupts - YouTube](https://www.youtube.com/watch?v=aT1tU0EnSHw)

---

## Objective 2: Coding rules

- **321** — **CORE** —  You need to avoid using magic numbers in the code. They are numbers which at the moment you write the code they make perfect sense for you and only for you, but the drawback is that it will be non-sense for the colleague that will make a code-review over your code (which frequently happens in real life projects). Even for yourself, they will become non-sense after 3 months of not working with that code, you will ask "what was I thinking here?!". So re-code your program and cover all these magic numbers with `#define`s as in the example:

    ```c
    // change... set_direction(2,7,1);  ...to...
    #define PORT_B   2
    #define PIN_NUMBER_7   7
    #define OUTPUT   1
    /******************some code here*****************************/
    set_direction(PORT_B, PIN_NUMBER_7, OUTPUT);
    /******************************************************************/
    ```

- **322** — **STRETCH** —  [Watch this movie clip on magic numbers](https://www.youtube.com/watch?v=p8RC_i9t0MU)
- **323** — **CORE** —  Re-design your code wrote so far using the following naming convention: name your functions and variables with a prefix which represents the name of the module it belongs to. e.g. if `led` is my module's name, then:
    - `led_set_state( ON )` will be the name of the function setting the state ON for that LED
    - `unsigned char led_state;` will be your variable declaration
- **324** — **STRETCH** —  [Watch this movie clip on naming](https://www.youtube.com/watch?v=zx7euEEZ0H4)

---

## Objective 3: Building a Control Panel - Internship's main application

- **331** — **CORE** —  Construct your software program so that it can handle the 3 buttons from OLED1 extension board. The general behavior should be the following: when pressing button X then LED X is on, where X = 1,2,3, and when releasing button X then LED X is off. You have the freedom to choose what kind of implementation approach you prefer: polling the button state or trigger interrupts.
- **332** — **CORE** —  Modify your program so that when pressing button X on OLED1 a second time (X=1,2,3), only then LED X is off.
- **333** — **CORE** —  Add to the previous program the following behavior: when button SW0 is pressed then all LED X are off (no matter their current state on/off) and LED0 is on.
- **334** — **CORE** —  Your customer, BMW, has requested to implement a prototype for a central control panel in the car.

    **REQUIREMENTS:**

    The HVAC vents are positioned to blow the AC in 3 directions: left, central and right. Each vent has its corresponding control button and LED for visual confirmation to the driver about the enabled function of that particular vent. They are the buttons and LEDs on OLED1 board. Each button push will toggle the function of the corresponding vent and will toggle accordingly also the corresponding LED. No crosstalks are allowed.

    For comfort security BMW has requested that an additional button, SW0, called master control, when it is pushed to block the function of the entire control panel. The BLOCKED state of the control panel will be implemented as follows:

    - LED0 on ATmega324PB main board is activated
    - pushing on OLED1 buttons will have no effect on vent and LED indicators from OLED1 (they stay OFF)
    - pushing on any OLED1 button will fast blink the LED0 indicating that the panel is blocked

    To unblock the panel it is needed to push the SW0 master control again (and the normal functionality is re-established).

---

## Objective 4: Light sensor

- **341** — **CORE** —  Our next big move will be to integrate the light sensor within our project and writing code for handling the analog to digital conversion. On short we want to do: connect light sensor to pin, receiving analog signal based on ambient light, convert this signal to a digital value, light up LED. A preview of how the setup will look like is here: [TEMT6000 Ambient Light Sensor with Arduino - YouTube](https://www.youtube.com/watch?v=pxR6e-3XkIk).
- **342** — **CORE** —  Connect the I/O board with light sensor to EXT4. Read from the User Guide about sensor type, its datasheet and most important: connection to microcontroller's pins. Observe in the electronic schematic also the connections to GND and VCC (without them the sensor would not work, right?). *(<<< microcontroller's pin identified)*

    So, this phototransistor will transform the ambient light (photons hitting the base of this NPN) into electrical current flowing through collector. And because a 100K resistor is placed in collector we can measure the voltage drop that occurs compared to 3.3V (which is the VCC). This voltage\* will act as input analog signal for the microcontroller's pin connected.

    !!! note "Note"
        ADC peripheral is capable of measuring voltages and not currents! so the resistor acts together with the phototransistor as a voltage divider in the circuit.

- **343** — **CORE** —  Double check the connected pin for its second functionality (other than just being a pin for GPIO) at microcontroller's datasheet, table 16-3 from chapter 16.3.1. *(<<< second functionality of the microcontroller's pin identified)*

    Therefore, somehow\* the pin can act both as a GPIO and as an ADC reader. This aspect is called alternate functions. Who decides to switch between the alternatives? You as embedded developer, depending on what you have connected to the pin (LEDs or analog sensors). In our case we connected the ambient light sensor which gives us the analog signal, therefore you need to use the analog function of the pin. How this decision is made? By enabling the ADC peripheral (writing the correct bits in its registers) the GPIO functionality is disabled.

    !!! note "Note for the most curious minds"
        This "somehow" can be explained by the logic gates in the diagram 16-5. Alternate Port Functions where at the bottom you have DIEOExn and DIEOVxn signals that are internal signals coming from ADC registers. These signals are triggered when you enable the ADC functionality by setting its registers. So, these signals will block the digital input capture path and the signal coming from outside (from light sensor) will be redirected towards the AIOxn (analog converter input). Better explanation at chapter 16.3.

??? info "Additional materials — FOR YOUR INFO"
    - [Movie time! :) for understanding what a signal is.](https://www.youtube.com/watch?v=jNebPEW3ZNU)
    - [About the frequency and the period of a signal.](https://www.youtube.com/watch?v=Axx8WfxQDkk)
    - [First movie about (1) ANALOG and DIGITAL signals.](https://www.youtube.com/watch?v=WxJKXGugfh8)
    - [Second movie about (2) ANALOG and DIGITAL signals.](https://www.youtube.com/watch?v=64FSgQdWHrE&ab_channel=MinimalistPhysicist)
    - [Transforming ANALOG to DIGITAL.](https://www.youtube.com/watch?v=oSZNQ1LZjHg)

---

## Objective 5: Mastering the ADC

- **351** — **CORE** —  Now you have a minimum experience with microcontroller's datasheet reading. Next big task is to understand how ADC is working and how to make the correct register settings. Every time you need to work with a peripheral module remember:

    1. you will encounter a lot of information noise, so prepare your mind to filter
    2. you will not understand all the information at once, therefore be patient reading 2x, 3x times
    3. start with the block diagram; it shows in a simplified manner the overall dynamics of that peripheral; follow the signals from outside of the capsule via pins to the inside (and/or viceversa) and further to databus along sketched lines; look also for what clock source has and if interrupt request lines are present there to send interrupt signals to CPU
    4. read the overview (with observation 1&2&3 in mind :)
    5. check how many registers that peripheral has (to limit your anxiety over the problem)
    6. hover the registers description once scanning with your eyes about how can you implement the objective you have in mind (e.g. for ADC you will want to obtain a digital converted value and use it further, for TIMERS you will want to obtain periodic interrupts, etc.)
    7. read the registers description second time looking for how to enable the peripheral, how are you making use of its functionality and its final result\*, how you will work with interrupt requests (if you decide to work with interrupts)
    8. read the registers description third time looking to take THE EASIEST decisions over the settings of each bit\*\* (!!!) even if that means not to modify their default (after reset) value at all (this is a valid decision also, right? :); this is the point where you should go also to chapters describing the functionalities (e.g. start a convertion, etc.) to get more clarifications.

    !!! note "Note"
        These 8 rules to read a peripheral datasheet information are general, and applicable for any peripheral you might study; in ADC case the final result of the ADC peripheral is a digital data stored in ADCL-ADCH register (similar to how PINx was storing the 0 or 1 corresponding to the button state); so your program needs to read that register in a variable to further use it in the program.

- **352** — **CORE** —  After reading the ADC datasheet information (registers & functionalities) you should have these questions.

    !!! note "Good start decisions"
        Here you can find some good start decisions:

    | Register | Questions | Good start decisions |
    | -------- | --------- | -------------------- |
    | ADMUX | What voltage reference should I use? | AVCC = 3.3V, VREF has to be >= sensor analog signal to avoid ADC saturation on high input levels |
    | ADMUX | Should I choose result left aligned or right aligned? | The easiest way: just read ADCH => 8 bit left align |
    | ADMUX | What ADC channel should I use? | The corresponding pin with light sensor connected |
    | ADMUX | Is my channel single ended input or +/- differential? | Single ended as you have one pin connected to sensor |
    | ADCSRA | Should I enable the ADC? | Yes, resulting in digital input path disabled |
    | ADCSRA | When should I start a convertion? | Not right away! the starting of conversion is the last thing you do, after setting all the registers properly |
    | ADCSRA | Should I use auto trigger? | Keep It Simple! don't use internal trigger signals for the moment, rely only on your call to start convertion. ADC will work in Single Convertion Mode. |
    | ADCSRA | What should I do with ADC Interrupt Flag? | Nothing. It is a flag signaling there is an interrupt. Your CPU has already received the interrupt request by this time and is ready to execute the ISR. |
    | ADCSRA | Should I use interrupts? | Yes. It's an easy way to get the result when it's ready |
    | ADCSRA | Should I prescale the clock input to ADC? | Keep it Simple! no |
    | ADCL & ADCH | How should I read the ADCH? | Within ISR just capture it in a variable `var = ADCH;`. Remember ADCH is 8bit left align (decided above) |
    | ADCSRB | Should I use analog comparator? | Keep it Simple! no |
    | ADCSRB | What auto trigger source should I select? | None. Remember you decided above: no auto-trigger. ADC will work in Single Conversion Mode. |
    | DIDR0 | Should I disable the digital input buffer? | Keep it Simple! no (we don't care for now about power consumption) |

- **353** — **CORE** —  Introduce the interrupt service routine for ADC. Inside you need to read the ADCH to get the result of conversion. What kind of data type you will use for this? *(<<< your decision)*. Put a breakpoint to ISR and your program should hit it! Wonderful!
- **354** — **STRETCH** —  You can play with darker ambient (cover the sensor with a book, NOT with your finger!!!) or brighter ambient (you can use your phone flashlight) to observe different ADC results. Change the VREF settings to 1.1V and check if ADC is saturated (meaning that results will be topped with `0xFF` for the same light intensity\*).

    !!! note "Note"
        To have aprox. the same light intensity place your phone on a stack of books nearby main board, flashlight over the light sensor and keep this setup as long as you are doing the measurements for both VREF settings.

- **355** — **CORE** —  More design rules! Re-design your code (all modules so far!) along the additional rules:
    1. each module must have an initialization function (e.g. `led_init( )`, `adc_init( )`, `gpio_init( )`, etc.) which will define the initial state for that particular module (it can be peripheral dependent, e.g. module ADC is initialized with all the default decisions you took or it can be peripheral independent, e.g. module LED is initialized with all LEDs by default turned off)
    2. determine the atomic actions a software driver can do to "drive" the hardware and build dedicated functions for them (e.g. at GPIO module, which is a driver, you determined set, reset, get being the atomic actions and you build functions accordingly; at ADC module which is a driver you can determine the start of conversion and get the result as the atomic actions, building dedicated functions)

??? info "Additional materials — FOR YOUR INFO"
    - [Atmel AVR127: Understanding ADC Parameters (microchip.com)](https://ww1.microchip.com/downloads/en/Appnotes/atmel-8456-8-and-32-bit-avr-microcontrollers-avr127-understanding-adc-parameters_application-note.pdf)

---

## Objective 6: Ambient Light Application

- **361** — **CORE** —  Establish the middle point of the readings range and turn on LED0 if readings are above that point.
- **362** — **CORE** —  Take 4 readings intervals (1 corresponding to complete dark, 2 semi-dark, 3 semi-light, 4 full light) and turn on LED1,2,3 as follows:

    | ADC readings interval | Light intensity correspondence | LEDs state |
    | --------------------- | ------------------------------ | ---------- |
    | 1 | full dark | all off |
    | 2 | semi-dark | LED1 on |
    | 3 | semi-light | LED1,2 on |
    | 4 | full light | LED1,2,3 on |

- **363** — **STRETCH** —  Now it's time to be interested of another key performance indicator in embedded systems: power consumption. On the main board, near the SW0 button, there is a current measurement header. How you can measure the current in a circuit? *(<<< your answer here)*. Since we do not have in our Internship online setup the possibility to measure the current consumption we will rely on datasheet information:
    - disable the digital input buffer (if it is powered then it consumes current) for the analog pin (the pin with connected sensor to it)
    - enable the ADC peripheral only when you are wishing to make a conversion, otherwise shut it down (disable)
- **364** — **OPTIONAL** — Implement the 10bit convertion resolution and check if you observe any sensitivity to ADC. Some of the questions you might have: What changes should I do to register settings to implement 10bit resolution? How can I get the result now? Does data type change? Would be easier to have the result right aligned or left aligned? Should I change the prescaler as chapter 27.4 is telling me?
- **365** — **OPTIONAL** — Imagine that your software driver module will be used by your colleagues into their projects. At the time you write the code you do not know what resolution they will need, 8bit or 10bit. It will depend on their particular application. Therefore your job is to implement a solution offering them the possibility to choose between 8bit or 10bit resolution. Make use of conditional compilation.
- **366** — **OPTIONAL** — Measure the code size for the newly added ADC driver module so that your colleagues are informed. Include a table with the functions available and the two options on resolution (8bit, 10bit).
- **367** — **OPTIONAL** — Prescale the ADC clock down to [ 50KHz - 200KHz ]. Slower the clock better the accuracy of conversion. Do you observe any difference to ADC results?
