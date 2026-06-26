# Week 1 Review Quiz (From PDF)

Source PDF filename: Week 1 Review - Google Forms.pdf (repository root)

This page is a Markdown transfer of the quiz found in the root PDF. Some non-text visual elements from the original Google Form export are noted where text extraction was incomplete.

## Questions

1. What would be the final value of `x` after executing the code?

```c
void func(void) {
    static int x = 1;
    x++;
}

void main(void) {
    func();
    func();
    func();
}
```

- 0
- 4
- 3
- 1

2. What is the output/result of the shown expression/snippet?

Note: The question text in the PDF was not fully extractable from the exported form layout.

3. For what purpose is `volatile` keyword used in C language?

- to declare a variable that might change in a volatile way
- to reserve a special area in memory for this type of variables
- to prevent compiler optimizations for variables that are not changed by the program
- to allow a variable to be initialized without an explicit value

4. Can you give example of a General Purpose Register?

- Program Counter (PC)
- Stack Pointer (SP)
- PORTA
- R16

5. What implements the following line of code?

```c
short internship @ 0x000121
```

- defines an 8bit variable at address 0x000121
- declares an non-initialized integer variable named "internship"
- declares a 16bit variable at address 0x000121
- defines a 16bit variable at address 0x000121

6. GND means...

- earth link
- 3.3V
- ESD protection
- 0V

7. What is the value of ADSC bit after microcontroller's reset occurs?

- 6
- R/W
- 0
- 1

8. What does Ohm's law say about current intensity?

- it is perpendicular to resistance
- it is somehow parallel to resistance
- it is in series to resistance
- it is inversely proportional to resistance

9. What's this?

Note: The original question appears to reference an image/diagram in the PDF export that was not extracted as text.

- a direct forward voltage with a sign for direction
- a direct polarized voltage
- a direct polarized LED
- a direct polarized diode

10. How you will store in a little endian architecture the following unsigned long variable `0x05 F5 E0 FF`?

- FF 0E 5F 50
- FF E0 F5 05
- E0 FF 05 F5
- 05 F5 E0 FF

11. Having this bit order translate the number to decimal:

- 227
- 151
- 233
- 158

12. How you will store in a little endian architecture the following 8bit number `0xFE`?

- 0xEF
- 0xFE

13. What's wrong here?

```c
#define CPU_FREQUENCY 5;
```

- nothing, it compiles just fine
- the semicolon at the end could interfere with the actual code and produce errors
- the CPU_FREQUENCY is not expressed in MHz here
- the number 5 is missing the parentheses in order to avoid potential errors

## Note

This content is transcribed from the provided PDF export and kept close to source wording.