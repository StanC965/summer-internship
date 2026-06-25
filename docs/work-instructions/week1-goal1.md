# Week 1 · Goal 1

> **GOAL: set up the stage for software embedded development**

By the end of this week you should be able to recognize and control your system and tools very effectively and efficiently.

Also you must be honest to yourself making an assessment for your knowledge/skill level from where you start to grow.

On short what you will do this week:

- get to know your dev boards, IDE and backend compiler.
- refresh your knowledge on C programming language, microcontrollers and basic electronics

---

## Objective 1: Knowing your main development board

*(you can get help by opening also User Guide for ATMega324PB Xplained PRO)*

- **111** — **CORE** —  Search and identify ATMega324PB microcontroller on the board.
- **112** — **CORE** —  Search and identify LED0, a LED that you will program to lit later.
- **113** — **CORE** —  Search and identify SW0, a switch that you will program later to be interpreted as pressed/not pressed.
- **114** — **CORE** —  Search and identify other components like external oscillator and debugger chip/microcontroller.
- **115** — **CORE** —  How many extension headers there are on the board? *( <<< just fill in the number )*
- **116** — **CORE** —  How are the extension headers labeled? *( <<< one example of label found )*
- **117** — **CORE** —  Search and identify GND and VCC pins on the headers and on the power connector.
- **118** — **CORE** —  Connect the USB cable to the main board and you should see the green LED lit.
- **119** — **OPTIONAL** — Even though you don't have an external power supply connected to VCC and GND the board is still powered up (green LED lit) when pluging in the USB cable. How can you explain that? *(<<< your answer here)*

??? info "Additional materials — FOR YOUR INFO"
    During internship you will develop embedded applications without using wires in circuits because the boards can be easily connected via built-in connectors. It is a safe practice, especially now that you are new to embedded and PCB burn-outs should be avoided. But remember that in the office you will be often required to solder some wires on the PCB with all the necessary safety measures!

    You can watch/read on about the Human-Body Model used in electrostatic discharges here:

    - [Understanding Electrostatic Discharge (ESD) for Technicians - YouTube](https://www.youtube.com/watch?v=y5FswkQ4bi0&t=288s)
    - [What is ESD? Learn more about the basics of electrostatic charge - YouTube](https://www.youtube.com/watch?v=bWXNOemu2j4)
    - [Human-body model - Wikipedia](https://en.wikipedia.org/wiki/Human-body_model)
    - [Human-Body Model and Electrostatic Discharge (ESD) Tests - In Compliance Magazine](https://incompliancemag.com/article/human-body-model-and-electrostatic-discharge-esd-tests/)

---

## Objective 2: Knowing your extension board (OLED1)

*(you can get help by opening User Guide for OLED1 Xplained PRO)*

!!! warning
    DO NOT CONNECT the extension board to the main board yet!!! Follow the exercises!!!

- **121** — **CORE** —  Search and identify OLED display.
- **122** — **CORE** —  Search and identify LED1, LED2 and LED3 that you will program to lit.
- **123** — **CORE** —  Search and identify BUTTON 1, BUTTON 2 and BUTTON 3.
- **124** — **CORE** —  Search and identify the extension header.
- **125** — **CORE** —  Search and identify GND and VCC pin on the header.
- **126** — **CORE** —  Now, follow this 3-steps procedure: (1) unplug the USB cable from PC/laptop!!! (2) connect OLED1 board to EXT1 header from the main board and (3) finally reconnect the USB cable to the PC/laptop. You must ALWAYS follow this procedure when you want to connect something to the main board!

---

## Objective 3: Knowing your extension board (IO1)

*(you can get help by opening User Guide for IO1 Xplained PRO)*

!!! warning
    DO NOT CONNECT the extension board to the main board yet!!! Follow the exercises!!!

- **131** — **CORE** —  Search and identify the light sensor.
- **132** — **CORE** —  Search and identify the temperature sensor.
- **133** — **CORE** —  Search and identify the lowpass filter.
- **134** — **CORE** —  Search and identify the microSD card slot.
- **135** — **CORE** —  Search and identify the LED on the board.
- **136** — **CORE** —  Search and identify the extension header.
- **137** — **CORE** —  Search and identify GND and VCC pin on the header.
- **138** — **CORE** —  Now, follow this 3-steps procedure: (1) unplug the USB cable from PC/laptop!!! (2) connect IO1 board to EXT4 header from the main board and (3) finally reconnect the USB cable to the PC/laptop. You must ALWAYS follow this procedure when you want to connect something to the main board!

---

## Objective 4: Build a new project with IAR Embedded Workbench IDE

- **141** — **CORE** —  Install IAR Embedded Workbench on your computer (see Guide on how to do this).
- **142** — **CORE** —  First steps to follow when creating a new project in IAR EW are described in the same Guide.
- **143** — **CORE** —  Write the following code in `main.c` file. It will be programmed (flashed/downloaded) on the ATmega 324PB microcontroller by selecting **Download and Debug**. Once you do this you are in DEBUGGING mode. To exit DEBUGGING mode you select the icon **Stop debugging**.
- **144** — **STRETCH** —  Try out the functionality of all buttons used for debugging (the blue buttons) to get familiar with their effects, e.g. RESET, RUN UNTIL CURSOR, STEP OVER, etc.
- **145** — **STRETCH** —  Try out the windows in IDE: observe in Watch window the variables (right-click to change the format in decimal or hexa), check the Memory window for placement of those variables in memory (at what address they are?), observe in the Registers window the changing PC (Program Counter) and SP (Stack Pointer) as you go through the program step wise.
- **146** — **CORE** —  Now that you are finishing Objective 4, you must upload your project files to [github.com](http://github.com/) as instructed on your personal branch.

??? info "Additional materials — FOR YOUR INFO"
    In high level programming (e.g. languages like C++, C#, Java) you will find the function `main( )` as first function in the program that is executed and where all other functions callings are happening. Well, in embedded, there is a world before `main( )` (therefore the `main( )` function becomes a trivial function like any other), the entry point in the execution of the program it is another code that is executed before the `main( )` function. This code usually is dubbed as **startup code**. You can visualize this startup code in the Disassembly window of IAR EW.

    - [Git Tutorial (w3schools.com)](https://www.w3schools.com/git/default.asp)

---

## Objective 5: Refresh your C programming language know-how

- **151** — **CORE** —  How to handle the different numeration systems (binary, decimal, hexadecimal). Watch the materials below, then: *are you able to create a single question for testing your colleague's knowledge on these topics?* The question you create will be used later to build up a quiz for the students group and must be of type "multiple choices - single answer" or "true-false" (include the correct answer also). *( <<< your question here )*

    - [Why Do Computers Use 1s and 0s? Binary and Transistors Explained. - YouTube](https://www.youtube.com/watch?v=Xpk67YzOn5w)
    - [How To Convert Binary to Hexadecimal - YouTube](https://www.youtube.com/watch?v=tSLKOKGQq0Y)
    - [How To Convert Hexadecimal To Binary - YouTube](https://www.youtube.com/watch?v=D_YC6DSPpQE)
    - [How To Convert Decimal to Binary - YouTube](https://www.youtube.com/watch?v=rsxT4FfRBaM)
    - [How To Add and Subtract Binary Numbers - YouTube](https://www.youtube.com/watch?v=C5EkxfNEMjE)
    - [Binary Addition and Subtraction With Negative Numbers, 2's Complements & Signed Magnitude - YouTube](https://www.youtube.com/watch?v=sJXTo3EZoxM)

- **152** — **CORE** —  In the program code above insert comments explaining what the program does (sum up two numbers). The preprocessor will output files with extension `.i`. Check how the preprocessor works using the settings showed. Visualize the `.i` files and observe how the code comments are preprocessed for your `main.c` file. *( <<< write down your observations here )*

    !!! note
        From this exercise on you must upload your project files to [github.com](http://github.com/) as instructed to your personal branch. You do this after each exercise so that we can check the differences between exercices.

- **153** — **CORE** —  Now you must delete the code from the previous exercise in IAR EW (because the exercises are not linked together). For the code below, what value will have the `VAR` constant? (you can easily see this if you store the `VAR` into a variable and look at `main.i` preprocessed file)

    ```c
    #if MAX == 1
    #define VAR 4
    #else
    #define VAR 5
    #endif
    ```

- **154** — **CORE** —  What this code will do?

    ```c
    #define MAX 10
    void main (void)
    {
    int x=2;
    #define MAX 55
    x=MAX;
    }
    ```

- **155** — **CORE** —  What this code will do? Verify it by checking the `.i` preprocessed file.

    ```c
    #define MAX 100
    void main (void)
    {
    int MAX = 10;
    }
    ```

    *You are still pushing your project to github after each exercise, right ?!*

- **156** — **STRETCH** —  How the following code will work? Verify it in your `main.c` file by comparing it with `main.i` (the preprocessed file).

    ```c
    #define MAX(i, limit) do \
    { \
        if (i < limit) \
        { \
            i++; \
        } \
    } while(1)

    void main(void)
    {
        MAX(0,3);
    }
    ```

    *You do remember github.com right?! :))*

- **157** — **STRETCH** —  Implement macros for the following functions: `max (a, b)`, `average (a, b)`.
- **158** — **STRETCH** —  Exemplify into your program code a situation for:
    - `static` keyword usage (explain the use case in the comments)
    - `volatile` keyword usage (explain the use case in the comments)
- **159** — **STRETCH** —  Define a structure `student` with the following elements: an array and two `unsigned char` data. Keep your name within the array; the first `unsigned char` keeps your age, the second `unsigned char` keeps your height. Initialize the structure defined.

??? info "Additional materials — FOR YOUR INFO"
    Embedded C difference:

    - [What Actually is Embedded C/C++? Is it different from C/C++? - YouTube](https://www.youtube.com/watch?v=KQBBWvY-s0o)

    Why you should master the hexadecimal system:

    - [Why do programmers use hexadecimal numbers? - YouTube](https://www.youtube.com/watch?v=dPxCGlW9lfM)

    Quick presentation on compiler:

    - [How do computers read code? - YouTube](https://www.youtube.com/watch?v=QXjU9qTsYCc)

    About assembly language:

    - [Why should I learn assembly language = complete waste of time?](https://www.youtube.com/watch?v=iYRl50gtprA)

    An interesting crash course on computer science:

    - [Crash Course Computer Science Preview - YouTube](https://www.youtube.com/watch?v=tpIctyqH29Q&list=PL8dPuuaLjXtNlUrzyH5r6jN9ulIgZBpdo)

---

## Objective 6: Refresh your microcontrollers know-how

- **161** — **CORE** —  Usually a microcontroller (MCU) comes with a datasheet explaining how it works and different other specifications which engineers are looking for understanding them. Go to ATmega324PB datasheet and familiarize yourself with the block diagram showing the internal components as blocks, with external pinout and finally with the CPU core. Try to identify what is interesting for you or makes you curious about.

    - [How to Read a Microcontroller Datasheet: Introduction and First Steps - allaboutcircuits.com](https://www.allaboutcircuits.com/technical-articles/how-to-read-a-microcontroller-datasheet-introduction-and-first-steps2/)
    - [How to Read a Datasheet | Education | Analog Devices](https://www.analog.com/en/education/education-library/webcasts/how-to-read-datasheet.html)

- **162** — **CORE** —  Check the endian architecture of ATMega324PB microcontroller (is it little endian or big endian?). Re-write the first program code (the one with the sum) and assign to variable `b` the value 257, then compile again, download and run your program and you should see the sum to be 258 or `0x0102` in hexadecimal. Now open a Watch window and a Memory window and compare the content from variable `c` address. Is it the same? *( <<< describe what you see )*
    - Little endian = MSB is stored in memory to the highest address and LSB to the lowest address.
    - Big endian = MSB is stored to the lowest address and LSB to the highest address.
- **163** — **CORE** —  Open the header file `iom324pb.h` and visualize its content at this comment section:

    ```c
    /* ======================== */
    /* Predefined SFR Addresses */
    /* ======================== */
    ```

    You will find in the code comments two examples of a macro named `SFR_B( )`. The role of this macro is to make the connection between the physical address of the SFR register (Special Function Register) and a software variable in C program. With other words, its role is to interface software with hardware. Remember: this interface is the lowest level of interface in an embedded environment!!! Once the interface is done by this macro using the `@` character, you will be able to use the software variable to manipulate/control the content of the physical register directly from your program.

    Observe in the code comment how the macro will expand after the header file `iom324PB.h` is preprocessed. You will find the example of an imaginary register `TCCR2` (this register does not exist inside the microcontroller, therefore it is imaginary, it is there just as an example).

    ```c
    SFR_B_N(0x25, TCCR2, FOC2, WGM20, COM21, COM20, WGM21, CS22, CS21, CS20)
    ```

    Finally, open the datasheet of the ATMega324PB microcontroller and find the register `TCCR2B`, a real register!!! Compare the information found in the datasheet with the macro of the register `TCCR2B`. What is your conclusion? *( <<< write down your conclusion here )*

- **164** — **CORE** —  By analogy with the expansion example above, write in the `main.c` file as comments (!) how you understood the following macro registers will be expanded:

    ```c
    SFR_B_N(0x08,PORTC,PORTC7,PORTC6,PORTC5,PORTC4,PORTC3,PORTC2,PORTC1,PORTC0)
    SFR_B_N(0x07, DDRC, DDRC7, DDRC6, DDRC5, DDRC4, DDRC3, DDRC2, DDRC1, DDRC0)
    SFR_B_N(0x06, PINC, PINC7, PINC6, PINC5, PINC4, PINC3, PINC2, PINC1, PINC0)
    ```

    After you finish this task, upload the entire Project to github => Project repository. This will be your first upload to github: Congrats! From now on you should make a commit to github after each exercise: remember the rule of inserting a comment at the beginning of the file showing about what exercise is about.

- **165** — **CORE** —  Include the header file `iom324pb.h` in your `main.c` file. Compile. Check with preprocessed files (`main.i`) how the macros or `#define`s are expanded. Is this confirming your knowledge acquired so far? How the comments are preprocessed?
- **166** — **OPTIONAL** — Compare contents of the file `iom324PB.h` vs. datasheet microcontroller vs. register view of IAR EW. Here it is how you can do it:
    1. identify in the file `iom324pb.h` just 3 registers with their name and size;
    2. then open datasheet and recognize the registers you have chosen above;
    3. then open Registers View from IAR EW and recognize the registers identified above;
    4. use support file `YOUR_NAME_Registers_Compare_324_328.xls`.

    What is your conclusion? *( <<< write down your conclusion here )*

- **167** — **OPTIONAL** — Can you find the same 3 registers in the ATmega328PB (search the internet for ATmega328PB datasheet and the `iom328pb.h` file in the same manner you found `iom324pb.h`)? If YES, then this means you can write portable code, the same code works for both microcontrollers, ATmega324PB and ATmega328PB. *( <<< write down your conclusion here )* For this exercise you can also use the support file `YOUR_NAME_Registers_Compare_324_328.xls`.
- **168** — **OPTIONAL** — You can extend your search for the same registers to see if they are compatible with ATmega328P which is the exact microcontroller used by Arduino. *( <<< write down your conclusion here )*

??? info "Additional materials — FOR YOUR INFO"
    Explore how microcontrollers work here:

    - [How a CPU Works - YouTube](https://www.youtube.com/watch?v=cNN_tTXABUA)

    How computers do math:

    - [How COMPUTERS do MATH - YouTube](https://www.youtube.com/watch?v=VBDoT8o4q00)

    More on endianness and why are they important, here:

    - [Dealing with Endianness Issues in your Programs - YouTube](https://www.youtube.com/watch?v=OoHich9BPxg)
    - [Free Code Camp on endianness](https://www.freecodecamp.org/news/what-is-endianness-big-endian-vs-little-endian/)
    - [Embedded Zone tutorial](https://embetronicx.com/tutorials/p_language/c/little-endian-and-big-endian/)

    Every time you are in an unknown territory you need a map. For embedded systems, when programming the microcontroller you need its registers map in order to correctly interface your software program with the hardware peripherals. The file `iom324pb.h` is that kind of map and it is essential (*sine qua non*) because it contains the registers map for microcontroller ATMega324PB. It can be found on the installation path of the cross-compiler and libraries at `C:\Program Files (x86)\IAR Systems\Embedded Workbench 8.0\avr\inc`.

    You could also read from Compiler Guide page 222 about accessing SFR registers. Accessing Compiler Guide is easy: go to the HELP menu from IAR EW IDE and there you find it!

    This is quite interesting, because ATmega328P is the same microcontroller used by Arduino. So you could write code here which is compatible with Arduino.

---

## Objective 7: Refresh your knowledge on basic electronics

- **181** — **CORE** —  How to connect a LED in a circuit? LED = Light Emitting Diode is a diode, which under direct polarization (voltage U applied from + to -) produces light. If you apply a reverse polarization (voltage U applied from - to +) the LED lights will not work, so it will not emit light. Physically, if you look at the LED capsule, you will notice a short leg and a long leg: the long leg is called the anode (+), and the short leg is called the cathode (-).

    A LED connected in direct polarization between + and - will try to consume the maximum energy for which it was designed for. At the limit, this will result in burning the LED. To protect it against this phenomenon it should be placed an adequate resistor in series. Its role is to limit the quantity of current that circulate through the LED.

    The Ohm law: `I = U / R` (the current through a resistor is directly proportional to the applied voltage and inversely proportional to its resistance).

- **182** — **STRETCH** —  Watch the following:

    - [What is a microcontroller and how microcontroller works - YouTube](https://www.youtube.com/watch?v=JwCTkm43CxQ)
    - [DIODES! All Sorts of Them and How They Work (ElectroBOOM101-010) - YouTube](https://www.youtube.com/watch?v=l2y-w9aS98k)
    - [How does a Diode work? - YouTube](https://www.youtube.com/watch?v=JNi6WY7WKAI)
    - [https://www.youtube.com/watch?v=7ukDKVHnac4](https://www.youtube.com/watch?v=7ukDKVHnac4)
    - [How Transistors Work - YouTube](https://www.youtube.com/watch?v=CQtSS6g00h0)
    - [Starter Guide to BJT Transistors (ElectroBOOM101 - 011) - YouTube](https://www.youtube.com/watch?v=2uowMENwiHQ)
    - [https://www.youtube.com/watch?v=0CvdruTMH1c](https://www.youtube.com/watch?v=0CvdruTMH1c)
    - [https://www.youtube.com/watch?v=IcrBqCFLHIY](https://www.youtube.com/watch?v=IcrBqCFLHIY)

    Now, first, which video you liked the most? Which video explained the topic in such a way you are now able to freely talk on the subject? Second, are you able to create a single question for testing your colleague's knowledge on these topics? The question you create will be used later to build up a quiz for the students group and must be of type "multiple choices - single answer" or "true-false" (include the correct answer also). *( <<< your question here )*

??? info "Additional materials — FOR YOUR INFO"
    Explore a great invention:

    - [Transistors - The Invention That Changed The World - YouTube](https://www.youtube.com/watch?v=OwS9aTE2Go4)

    A general presentation for what skills you need in embedded systems:

    - [How To Become An Embedded Software Engineer? - YouTube](https://www.youtube.com/watch?v=HFmGk4oufj8)
    - [Embedded Systems Engineering VS Embedded Software Engineering - YouTube](https://www.youtube.com/watch?v=7ahkBz3BSRs)
    - [Should You Become An Embedded Systems Engineer? 5 Skills Required & Career Advantages - YouTube](https://www.youtube.com/watch?v=xf1GyrtkaE8)
